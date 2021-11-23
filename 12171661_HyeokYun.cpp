#include<iostream>
#include<vector>
using namespace std;

struct vertex { //���� ����ü
	int num; //���� ��ȣ
	int weight; //����ġ
	int from; //��� �������� ���� ������
	bool unseen = true; //unseen ����
	bool in_tree = false; //tree�� ���ԵǾ����� ����
	vertex* next = NULL; //��ũ�帮��Ʈ ������ ���� ������
	vertex() { //����ִ� ������ ����� ������
		this->num = -1;
		this->weight = -1;
		this->from = -1;
	}
	vertex(int num, int weight, int from) { //���� �Է¹޾� ������ �����ϴ� ������
		this->num = num;
		this->weight = weight;
		this->from = from;
	}
};

class min_PQ { //������ ������ �ּ� �켱����ť
public:
	vector<vertex*> heap;

	min_PQ() {
		vertex* empty_vertex = new vertex(); //����ִ� ������ �����
		heap.push_back(empty_vertex); //0��° �ε����� ������ �� �ֱ�, ���� �����ϱ� ����
	}

	int size() { //�� ���� ������ ��, heap[0]�� ������ ���� ��������Ƿ� -1�� ���ش�
		return heap.size() - 1;
	}

	bool empty() { //heap�� ����ִ��� ����,  heap[0]�� ������ ��
		if (heap.size() == 1)
			return true;
		else
			return false;
	}

	void push(vertex* v) { //���ο� ������ ���� �߰�
		heap.push_back(v); //���Ϳ� push���ְ�
		int idx = heap.size() - 1; //�ش� ������ �ε����� heap ������ -1
		upHeap(idx); //�켱����ť�� �����ϱ� ���� upheap ����
	}

	vertex* top() { //min_PQ�̹Ƿ� ������ �ּ� ����ġ�� ������ ��ȯ, �ּ� ����ġ�� ���������
		            //������ȣ�� ���� ������ ��ȯ
		return heap[1];
	}
	void downHeap(int idx) { //idx�� 1�� �� downheap�� ����(��Ʈ������)
		int left = idx * 2; //���� �ڽ�
		int right = idx * 2 + 1; //������ �ڽ�
		if (right <= heap.size()-1) { //������ �ڽ��� �����ϸ� ���� �ڽ��� ��
			if (heap[left]->weight < heap[right]->weight) { //���� �ڽ��� ����ġ�� �� ������
				if (heap[left]->weight < heap[idx]->weight) { //���� �ڽİ� �θ��� ����ġ�� ����
					swap(heap[left], heap[idx]);              //���� �ڽ��� ����ġ�� �� ������ swap(���� �ڽ�<->�θ�) �� 
					downHeap(left);                           //���� �ڽ��� �ε����� downheap ����
				}
				else if (heap[left]->weight == heap[idx]->weight) { //���� �ڽ��� ����ġ�� ������ �ڽ��� ����ġ�� ������
					if (heap[left]->num < heap[idx]->num) {         //���� �ڽİ� �θ��� ������ȣ�� ����
						swap(heap[left], heap[idx]);                //���� �ڽ��� ��ȣ�� �� ������ swap(���� �ڽ�<->�θ�) ��
						downHeap(left);                             //���� �ڽ��� �ε����� downheap ����
					}
				}
				else return; //�� �� ��� ��� �ƴѰ�� downHeap ������ �ʿ� ����, �Լ� ����
			}
			//���� �ڽĺ��� ������ �ڽ��� ����ġ�� �� ���� ��� ����<->���������� ���� �����ϰ� ����
			else if (heap[left]->weight > heap[right]->weight) {  //���� ���� ����
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
			else if (heap[left]->weight == heap[right]->weight) { //���� �ڽ��� ����ġ�� ������ �ڽ��� ����ġ�� ������
				if (heap[left]->weight > heap[idx]->weight) //���� �ƹ��ų�(����)�� ����ġ�� �θ��� ����ġ���� ũ��
					return;                                 //downHeap�� �ʿ� �����Ƿ� �Լ� ����

				else if (heap[left]->weight == heap[idx]->weight) { //���� �ƹ��ų�(����)�� ����ġ�� �θ��� ����ġ�� ������
					if (heap[left]->num < heap[right]->num) { //���� �ڽ��� �� ������ȣ�� ���� �ڽ��� �˾Ƴ�
						if (heap[left]->num < heap[idx]->num) { //���� �ڽ��� ��ȣ�� �� �۴ٸ� �θ�� ��ȣ�� ���� �� ������
							swap(heap[left], heap[idx]);        //swap(���� �ڽ�<->�θ�) ��
							downHeap(left);                     //���� �ڽ��� �ε����� downHeap ����
						}
					}
					else if(heap[left]->num > heap[right]->num) { //�ݴ�� ������ �ڽ��� ��ȣ�� �� �۴ٸ�
						if (heap[right]->num < heap[idx]->num) {  //�θ�� ��ȣ�� ���� ������ �ڽ��� ��ȣ�� �� ������
							swap(heap[right], heap[idx]);         //swap(������ �ڽ�<->�θ�) ��
							downHeap(right);                      //������ �ڽ��� �ε����� downHeap ����
						}
					}
				}

				else if (heap[left]->weight < heap[idx]->weight) { //���� �ƹ��ų�(����)�� ����ġ�� �θ��� ����ġ���� ������
					if (heap[left]->num < heap[right]->num) {      //���� �ڽ��� ���� ������ ����ġ�� �� ������
						swap(heap[left], heap[idx]);               //swap(���� �ڽ�<->�θ�) ��
						downHeap(left);                            //���� �ڽ��� �ε����� downHeap ����
					}
					else if (heap[left]->num > heap[right]->num) { //���� �ڽ��� ���� ������ ����ġ�� �� ������
						swap(heap[right], heap[idx]);              //swap(������ �ڽ�<->�θ�) ��
						downHeap(right);						   //������ �ڽ��� �ε����� downHeap ����
					}
				}
			}
		}
		else if (left <= heap.size()-1) {                  //���� �ڽĸ� ������ ���       
			if (heap[left]->weight < heap[idx]->weight) {  //���� �ڽİ� �θ��� ����ġ�� ���� ���� �ڽ��� �� �۴ٸ�
				swap(heap[left], heap[idx]);			   //swap(���� �ڽ�<->�θ�) ��
				downHeap(left);							   //���� �ڽ��� �ε����� downHeap ����
			}
			else if (heap[left]->weight == heap[idx]->weight) { //���� �ڽİ� �θ��� ����ġ�� ���� ���ٸ��
				if (heap[left]->num < heap[idx]->num) {         //���� ��ȣ�� ���� ���� �ڽ��� ��ȣ�� �� �۴ٸ�
					swap(heap[left], heap[idx]);                //swap(���� �ڽ�<->�θ�) ��
					downHeap(left);								//���� �ڽ��� �ε����� downHeap ����
				}
			}
			else return;  //�� ��� ��� �ƴѰ�� �Լ� ����                     
		}
		else return; //���� �ڽ� ��� ���ٸ� �� �̻� downHeap �������� �ʱ� ������ �Լ� ����
	}
	void pop() { //������ ��Ʈ��带 �����ϴ� �Լ�
		heap[1] = heap[heap.size()-1]; //��Ʈ�� ���� ���� ������ ������ �����Ѵ�
		heap.pop_back(); //������ ������ �ε����� ������ �����Ѵ�
		downHeap(1); //��Ʈ������ downHeap �����Ͽ� �ٽ� sort
	}
	void upHeap(int idx) { //�Ʒ����� ���� �ö󰡸� sort
		if (idx/2 < 1) //�θ� �������� ���� ��� �Լ� ����
			return;
		if (heap[idx]->weight < heap[idx / 2]->weight) { //�θ𺸴� ����ġ�� ������
			swap(heap[idx], heap[idx / 2]);              //swap(�ڽ�<->�θ�) ��
			upHeap(idx / 2);                             //�θ��� �ε����� upHeap ����
		}
		else if (heap[idx]->weight == heap[idx / 2]->weight) { //�θ�� ����ġ�� ������
			if (heap[idx]->num < heap[idx / 2]->num) {         //�θ�� ������ȣ�� ���Ͽ� �� ������
				swap(heap[idx], heap[idx / 2]);				   //swap(�ڽ�<->�θ�) ��
				upHeap(idx / 2);							   //�θ��� �ε����� upHeap ����
			}
		}
		else      //������ ���� upHeap�� �ʿ� �����Ƿ� �Լ� ����
			return;
	}
};
class Graph { //�׷��� Ŭ����
public:
	vector<vertex*>adj_info; //���������� ����ִ� ��������Ʈ
	vector<int>tree;         //prim�˰��� ���� tree�� ���Ե� ������ ����Ʈ
	min_PQ fringe;           //unseen->fringe�� �� ������ �ּ� �켱����ť
	int totalCost = 0;       //�� ��å�� ������ ���
	bool first = true;       //prim�� �ش� ���ǿ��� ó�� �����ϴ��� ����

	Graph() {
		vertex* v = new vertex(); //����ִ� vertex �ϳ� ����
		adj_info.push_back(v);    //0��° �ε����� �� vertex ���� (index�� ���Ǹ� ����)
	}

	void create_adj_info(int num) { //��������Ʈ ����
		for (int i = 1; i <= num; i++) { //�Է¹��� ������ ���� ��ŭ ����Ʈ ����
			vertex* v = new vertex(i, -1, -1); //���� ��ȣ�� i, �������� -1�� �ʱ�ȭ
			adj_info.push_back(v);
		}
	}

	void insert_vertex(int src, int dest, int weight) { //������ �����ϰ� �������踦 �����ϴ� �Լ�
		vertex* v = adj_info[src]; //������ ������ ������ ��� ����
		vertex* new_vertex = new vertex(dest, weight, src); //num=dest, src=from �� vertex ����

		while (v->next != NULL) { //������������ ��ũ�帮��Ʈ�� �ڸ� ã��
			if (v->next->num > dest) 
				break;
			v = v->next;
		}

		new_vertex->next = v->next; //��ġ�� ã���� ��ũ�帮��Ʈ�� ����
		v->next = new_vertex;       //v->���ο� ����->(v->next)

		//�����ϰ� dest src ���� �ٲ㼭 ����, 
		//���� ���� ����(�Է��� 1 2 40�̸� 1�� ��������Ʈ�� 2�� �߰��ϰ� �ݴ�� 2�� ��������Ʈ���� 1�� �߰� �ؾ���)
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
	void initialize() { //�� ���ǰ� ���� �� �������� �ʱ�ȭ ���ִ� �Լ�
		while (!tree.empty())
			tree.pop_back(); //Ʈ���� �� ������ Ʈ������� ��� ����
		totalCost = 0; //����� 0���� �ʱ�ȭ
		first = true;  //ó������ ���θ� true�� �ʱ�ȭ
		for (int i = 1; i < adj_info.size(); i++) {
			adj_info[i]->unseen = true; //�� ������ unseen���θ� ��� true�� �ʱ�ȭ
			adj_info[i]->in_tree = false;//�� ������ tree�� ���ԵǾ����� ���θ� ��� false�� �ʱ�ȭ
		}
	}
	void prim(int start_num) { //prim �˰���
		tree.push_back(start_num); //�Է¹��� ��ȣ�� ������ tree�� ���� ��Ų��
		adj_info[start_num]->in_tree = true; //�ش� ������ in_tree ������ true�� ����

		if (first==false&&fringe.empty()) { //ù ����(��� ����)�� �ƴϰ� fringe�� ����� ���
			cout << totalCost << " "; //�� ����� ���
			for (int i = 0; i < tree.size(); i++) {
				cout << tree[i] << " "; //���� ������� ������� ���
			}
			cout << "\n";		
			return;
		}
		first = false; //�Լ��� 1ȸ�� ����Ǹ� �� �̻� ���ʽ����� �ƴ��� ��Ÿ��
		               //fringe�� �� ó���� ����־ �ٷ� ����ϴ� ���� ������
		vertex* v = adj_info[start_num]; //������ġ�� ����
		while (v->next != NULL) { //������ ������ ��� �����ϸ�
			v = v->next; //�ش� ������ ������ ������

			if (adj_info[v->num]->in_tree != true) { //�ش� ������ tree�� ���ԵǾ����� ������
				for (int i = 1; i < fringe.heap.size(); i++) { //fringe�� ��ȣ�� ���� ������ �̹� �ִ��� Ȯ��
					if (fringe.heap[i]->num == v->num) { //��ȣ�� ���� ������ �ִٸ�
						if (fringe.heap[i]->weight > v->weight) { //����ġ�� ���� �� ������ ����ġ�� �� ������
							fringe.heap[i] = v; //����ġ�� ���� ��ΰ� ���� �������� ������Ʈ
							fringe.upHeap(i); //����ġ�� �ٲ������ �ش� �ε������� upHeap �����Ͽ� ������
							adj_info[v->num]->unseen = false; //unseen->fringe �Ƿ� unseen ������ false�� ����
						}
					}
				}
				if ( adj_info[v->num]->unseen == true) { //fringe�� �ش� ������ ��� unseen�� ���
					fringe.push(v); //fringe�� �߰�
					adj_info[v->num]->unseen = false; //unseen->fringe �Ƿ� unseen ������ false�� ����
				}
			}
		}

		totalCost += fringe.top()->weight; //�� ��뿡 fringe���� �ּ� ����ġ�� ������ ����ġ�� �� �Ѵ�
		start_num = fringe.top()->num; //pop�ϱ� ���� top�� ������ȣ�� ������ ����(���� ����)
		fringe.pop(); //fringe.top()�� ���� �� ������
		prim(start_num); //������ �����س��� �������� �ٽ� prim �˰��� ��� ����
	}
};
int main(){
	int n;//vertex ��
	int m;//edge ��
	int q_num;//������ ��
	int src, dest, weight; //���, ��ǥ, ����ġ

	cin >> n >> m >> q_num; //�� ������ ��, ������ ��, ������ �� �Է�

	Graph G;
	G.create_adj_info(n); //������ ����ŭ ��������Ʈ ����

	while (m--) { //������ ����ŭ �Է� ����
		cin >> src >> dest >> weight;
		G.insert_vertex(src, dest, weight); // ������ ��������Ʈ ����
	}

	char q;
	int start_num;
	while (q_num--) {
		cin >> q >> start_num; //���ǿ� prim�� ���� �� ���� ������ ��ȣ�� �Է�
		G.prim(start_num);	//prim�˰��� ����
		G.initialize();     //��� ������ ���� ���Ǹ� ���� �ʱ�ȭ
	}
}