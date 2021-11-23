#include<iostream>
#include<vector>
using namespace std;

struct vertex { //정점 구조체
	int num; //정점 번호
	int weight; //가중치
	int from; //어느 정점으로 부터 오는지
	bool unseen = true; //unseen 여부
	bool in_tree = false; //tree에 포함되었는지 여부
	vertex* next = NULL; //링크드리스트 구현을 위한 포인터
	vertex() { //비어있는 정점을 만드는 생성자
		this->num = -1;
		this->weight = -1;
		this->from = -1;
	}
	vertex(int num, int weight, int from) { //값을 입력받아 정점을 생성하는 생성자
		this->num = num;
		this->weight = weight;
		this->from = from;
	}
};

class min_PQ { //힙으로 구현한 최소 우선순위큐
public:
	vector<vertex*> heap;

	min_PQ() {
		vertex* empty_vertex = new vertex(); //비어있는 정점을 만든다
		heap.push_back(empty_vertex); //0번째 인덱스에 쓰레기 값 넣기, 힙을 구현하기 위함
	}

	int size() { //힙 안의 정점의 수, heap[0]에 쓰레기 값이 들어있으므로 -1을 해준다
		return heap.size() - 1;
	}

	bool empty() { //heap이 비어있는지 여부,  heap[0]은 쓰레기 값
		if (heap.size() == 1)
			return true;
		else
			return false;
	}

	void push(vertex* v) { //새로운 정점을 힙에 추가
		heap.push_back(v); //벡터에 push해주고
		int idx = heap.size() - 1; //해당 정점의 인덱스는 heap 사이즈 -1
		upHeap(idx); //우선순위큐를 구현하기 위해 upheap 진행
	}

	vertex* top() { //min_PQ이므로 힙에서 최소 가중치의 정점을 반환, 최소 가중치가 여러개라면
		            //정점번호가 작은 순으로 반환
		return heap[1];
	}
	void downHeap(int idx) { //idx엔 1이 들어가 downheap을 진행(루트노드부터)
		int left = idx * 2; //왼쪽 자식
		int right = idx * 2 + 1; //오른쪽 자식
		if (right <= heap.size()-1) { //오른쪽 자식이 존재하면 양쪽 자식을 비교
			if (heap[left]->weight < heap[right]->weight) { //왼쪽 자식의 가중치가 더 작으면
				if (heap[left]->weight < heap[idx]->weight) { //왼쪽 자식과 부모의 가중치를 비교해
					swap(heap[left], heap[idx]);              //왼쪽 자식의 가중치가 더 작으면 swap(왼쪽 자식<->부모) 후 
					downHeap(left);                           //왼쪽 자식의 인덱스로 downheap 진행
				}
				else if (heap[left]->weight == heap[idx]->weight) { //왼쪽 자식의 가중치과 오른쪽 자식의 가중치가 같으면
					if (heap[left]->num < heap[idx]->num) {         //왼쪽 자식과 부모의 정점번호를 비교해
						swap(heap[left], heap[idx]);                //왼쪽 자식의 번호가 더 작으면 swap(왼쪽 자식<->부모) 후
						downHeap(left);                             //왼쪽 자식의 인덱스로 downheap 진행
					}
				}
				else return; //위 두 경우 모두 아닌경우 downHeap 진행할 필요 없음, 함수 종료
			}
			//왼쪽 자식보다 오른쪽 자식의 가중치가 더 작은 경우 왼쪽<->오른쪽으로 위와 동일하게 진행
			else if (heap[left]->weight > heap[right]->weight) {  //위와 설명 같음
				if (heap[right]->weight < heap[idx]->weight) {
					swap(heap[right], heap[idx]);
					downHeap(right);
				}
				else if (heap[right]->weight == heap[idx]->weight) {
					if (heap[right]->num < heap[idx]->num) {
						swap(heap[right], heap[idx]);
						downHeap(right);
					}
				}
				else return;
			}
			else if (heap[left]->weight == heap[right]->weight) { //왼쪽 자식의 가중치와 오른쪽 자식의 가중치가 같으면
				if (heap[left]->weight > heap[idx]->weight) //둘중 아무거나(왼쪽)의 가중치가 부모의 가중치보다 크면
					return;                                 //downHeap할 필요 없으므로 함수 종료

				else if (heap[left]->weight == heap[idx]->weight) { //둘중 아무거나(왼쪽)의 가중치가 부모의 가중치와 같으면
					if (heap[left]->num < heap[right]->num) { //양쪽 자식중 더 정점번호가 작은 자식을 알아냄
						if (heap[left]->num < heap[idx]->num) { //왼쪽 자식의 번호가 더 작다면 부모와 번호를 비교해 더 작으면
							swap(heap[left], heap[idx]);        //swap(왼쪽 자식<->부모) 후
							downHeap(left);                     //왼쪽 자식의 인덱스로 downHeap 진행
						}
					}
					else if(heap[left]->num > heap[right]->num) { //반대로 오른쪽 자식의 번호가 더 작다면
						if (heap[right]->num < heap[idx]->num) {  //부모과 번호를 비교해 오른쪽 자식의 번호가 더 작으면
							swap(heap[right], heap[idx]);         //swap(오른쪽 자식<->부모) 후
							downHeap(right);                      //오른쪽 자식의 인덱스로 downHeap 진행
						}
					}
				}

				else if (heap[left]->weight < heap[idx]->weight) { //둘중 아무거나(왼쪽)의 가중치가 부모의 가중치보다 작으면
					if (heap[left]->num < heap[right]->num) {      //양쪽 자식을 비교해 왼쪽의 가중치가 더 작으면
						swap(heap[left], heap[idx]);               //swap(왼쪽 자식<->부모) 후
						downHeap(left);                            //왼쪽 자식의 인덱스로 downHeap 진행
					}
					else if (heap[left]->num > heap[right]->num) { //양쪽 자식을 비교해 왼쪽의 가중치가 더 작으면
						swap(heap[right], heap[idx]);              //swap(오른쪽 자식<->부모) 후
						downHeap(right);						   //오른쪽 자식의 인덱스로 downHeap 진행
					}
				}
			}
		}
		else if (left <= heap.size()-1) {                  //왼쪽 자식만 존재할 경우       
			if (heap[left]->weight < heap[idx]->weight) {  //왼쪽 자식과 부모의 가중치를 비교해 왼쪽 자식이 더 작다면
				swap(heap[left], heap[idx]);			   //swap(왼쪽 자식<->부모) 후
				downHeap(left);							   //왼쪽 자식의 인덱스로 downHeap 진행
			}
			else if (heap[left]->weight == heap[idx]->weight) { //왼쪽 자식과 부모의 가중치를 비교해 같다면면
				if (heap[left]->num < heap[idx]->num) {         //둘의 번호를 비교해 왼쪽 자식의 번호가 더 작다면
					swap(heap[left], heap[idx]);                //swap(왼쪽 자식<->부모) 후
					downHeap(left);								//왼쪽 자식의 인덱스로 downHeap 진행
				}
			}
			else return;  //두 경우 모두 아닌경우 함수 종료                     
		}
		else return; //양쪽 자식 모두 없다면 더 이상 downHeap 진행하지 않기 때문에 함수 종료
	}
	void pop() { //힙에서 루트노드를 삭제하는 함수
		heap[1] = heap[heap.size()-1]; //루트에 힙의 가장 마지막 정점을 복사한다
		heap.pop_back(); //힙에서 마지막 인덱스의 정점을 삭제한다
		downHeap(1); //루트노드부터 downHeap 진행하여 다시 sort
	}
	void upHeap(int idx) { //아래에서 위로 올라가며 sort
		if (idx/2 < 1) //부모가 존재하지 않을 경우 함수 종료
			return;
		if (heap[idx]->weight < heap[idx / 2]->weight) { //부모보다 가중치가 작으면
			swap(heap[idx], heap[idx / 2]);              //swap(자식<->부모) 후
			upHeap(idx / 2);                             //부모의 인덱스로 upHeap 진행
		}
		else if (heap[idx]->weight == heap[idx / 2]->weight) { //부모와 가중치가 같으면
			if (heap[idx]->num < heap[idx / 2]->num) {         //부모와 정점번호를 비교하여 더 작으면
				swap(heap[idx], heap[idx / 2]);				   //swap(자식<->부모) 후
				upHeap(idx / 2);							   //부모의 인덱스로 upHeap 진행
			}
		}
		else      //나머지 경우는 upHeap할 필요 없으므로 함수 종료
			return;
	}
};
class Graph { //그래프 클래스
public:
	vector<vertex*>adj_info; //정점정보가 들어있는 정점리스트
	vector<int>tree;         //prim알고리즘 에서 tree에 포함된 정점의 리스트
	min_PQ fringe;           //unseen->fringe가 된 정점의 최소 우선순위큐
	int totalCost = 0;       //총 산책로 디자인 비용
	bool first = true;       //prim을 해당 질의에서 처음 수행하는지 여부

	Graph() {
		vertex* v = new vertex(); //비어있는 vertex 하나 생성
		adj_info.push_back(v);    //0번째 인덱스에 빈 vertex 삽입 (index상 편의를 위해)
	}

	void create_adj_info(int num) { //정점리스트 생성
		for (int i = 1; i <= num; i++) { //입력받은 정점의 개수 만큼 리스트 생성
			vertex* v = new vertex(i, -1, -1); //정점 번호는 i, 나머지는 -1로 초기화
			adj_info.push_back(v);
		}
	}

	void insert_vertex(int src, int dest, int weight) { //정점을 삽입하고 인접관계를 형성하는 함수
		vertex* v = adj_info[src]; //인접한 정점을 삽입할 출발 정점
		vertex* new_vertex = new vertex(dest, weight, src); //num=dest, src=from 로 vertex 생성

		while (v->next != NULL) { //오름차순으로 링크드리스트의 자리 찾기
			if (v->next->num > dest) 
				break;
			v = v->next;
		}

		new_vertex->next = v->next; //위치를 찾으면 링크드리스트에 삽입
		v->next = new_vertex;       //v->새로운 정점->(v->next)

		//동일하게 dest src 순서 바꿔서 진행, 
		//위와 설명 같음(입력이 1 2 40이면 1의 인접리스트에 2를 추가하고 반대로 2의 인접리스트에도 1을 추가 해야함)
		v = adj_info[dest];
		new_vertex = new vertex(src, weight, dest);

		while (v->next != NULL) {
			if (v->next->num > dest)
				break;
			v = v->next;
		}

		new_vertex->next = v->next;
		v->next = new_vertex;
	}
	void initialize() { //각 질의가 끝난 후 변수들을 초기화 해주는 함수
		while (!tree.empty())
			tree.pop_back(); //트리가 빌 때까지 트리목록을 모두 삭제
		totalCost = 0; //비용을 0으로 초기화
		first = true;  //처음인지 여부를 true로 초기화
		for (int i = 1; i < adj_info.size(); i++) {
			adj_info[i]->unseen = true; //각 정점의 unseen여부를 모두 true로 초기화
			adj_info[i]->in_tree = false;//각 정점의 tree에 포함되었는지 여부를 모두 false로 초기화
		}
	}
	void prim(int start_num) { //prim 알고리즘
		tree.push_back(start_num); //입력받은 번호의 정점을 tree에 포함 시킨다
		adj_info[start_num]->in_tree = true; //해당 정점의 in_tree 변수를 true로 변경

		if (first==false&&fringe.empty()) { //첫 삽입(출발 정점)이 아니고 fringe가 비었을 경우
			cout << totalCost << " "; //총 비용을 출력
			for (int i = 0; i < tree.size(); i++) {
				cout << tree[i] << " "; //정점 진행과정 순서대로 출력
			}
			cout << "\n";		
			return;
		}
		first = false; //함수가 1회라도 실행되면 더 이상 최초실행이 아님을 나타냄
		               //fringe가 맨 처음에 비어있어서 바로 출력하는 것을 방지함
		vertex* v = adj_info[start_num]; //현재위치의 정점
		while (v->next != NULL) { //인접한 정점이 계속 존재하면
			v = v->next; //해당 정점의 정보를 가져옴

			if (adj_info[v->num]->in_tree != true) { //해당 정점이 tree에 포함되어있지 않으면
				for (int i = 1; i < fringe.heap.size(); i++) { //fringe에 번호가 같은 정점이 이미 있는지 확인
					if (fringe.heap[i]->num == v->num) { //번호가 같은 정점이 있다면
						if (fringe.heap[i]->weight > v->weight) { //가중치를 비교해 이 간선의 가중치가 더 작으면
							fringe.heap[i] = v; //가중치가 작은 경로가 적힌 정점으로 업데이트
							fringe.upHeap(i); //가중치가 바뀌었으니 해당 인덱스부터 upHeap 진행하여 재정렬
							adj_info[v->num]->unseen = false; //unseen->fringe 므로 unseen 변수를 false로 설정
						}
					}
				}
				if ( adj_info[v->num]->unseen == true) { //fringe에 해당 정점이 없어서 unseen인 경우
					fringe.push(v); //fringe에 추가
					adj_info[v->num]->unseen = false; //unseen->fringe 므로 unseen 변수를 false로 설정
				}
			}
		}

		totalCost += fringe.top()->weight; //총 비용에 fringe에서 최소 가중치의 정점의 가중치를 더 한다
		start_num = fringe.top()->num; //pop하기 전에 top의 정점번호를 변수에 저장(다음 정점)
		fringe.pop(); //fringe.top()을 삭제 후 재정렬
		prim(start_num); //변수에 저장해놓은 정점에서 다시 prim 알고리즘 재귀 실행
	}
};
int main(){
	int n;//vertex 수
	int m;//edge 수
	int q_num;//질의의 수
	int src, dest, weight; //출발, 목표, 가중치

	cin >> n >> m >> q_num; //총 정점의 수, 간선의 수, 질의의 수 입력

	Graph G;
	G.create_adj_info(n); //정점의 수만큼 정점리스트 생성

	while (m--) { //간선의 수만큼 입력 받음
		cin >> src >> dest >> weight;
		G.insert_vertex(src, dest, weight); // 정점의 인접리스트 생성
	}

	char q;
	int start_num;
	while (q_num--) {
		cin >> q >> start_num; //질의와 prim을 진행 할 최초 정점의 번호를 입력
		G.prim(start_num);	//prim알고리즘 실행
		G.initialize();     //모두 끝나면 다음 질의를 위해 초기화
	}
}