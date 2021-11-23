#include<iostream>
using namespace std;

class Node {
public:
	bool isLeaf = false; //leaf 노드 인지 여부
	bool isBlack = true; //노드의 색, true이면 black, false 이면 red, 기본값은 black

	int id;      //id
	string name; //이름
	int mb;      //용량
	int price;   //가격

	int depth = 0;

	Node* leftChild = NULL;  //왼쪽 자식노드의 포인터
	Node* rightChild = NULL; //오른쪽 자식노드의 포인터
	Node* par = NULL;        //부모 노드의 포인터

	Node(int id, string name, int mb, int price) { //정보를 입력 받을 경우 생성자
		this->id = id;
		this->name = name;
		this->mb = mb;
		this->price = price;
	}
	Node() { //leaf node 생성자
		this->isLeaf = true;
	}
};

class Tree {
public:
	Node* root;	
	Tree() {
		root = NULL;
	}
	void insertNode(int id, string name, int mb, int price) { //노드 삽입
		Node* newNode = new Node(id, name, mb, price); //입력받은 정보로 새로운 노드 생성
		Node* curNode = root; //현재 노드위치를 root로 설정
		Node* left_leaf=new Node(); //왼쪽 leaf 노드
		Node* right_leaf=new Node();//오른쪽 leaf 노드


		if (root == NULL) { //트리가 비어있으면
			root = newNode; //삽입된 노드가 root가 된다
		
			root->leftChild = left_leaf; 
			root->rightChild = right_leaf; //root의 양쪽자식에 leaf노드 추가
			left_leaf->par = root;
			right_leaf->par = root;//추가된 양쪽 leaf노드의 부모를 root로 설정
			left_leaf->depth = root->depth + 1; 
			right_leaf->depth = root->depth + 1; //추가된 양쪽 leaf노드의 깊이를 root의 깊이보다 +1
			curNode = newNode; //현재 노드의 위치를 삽입된 노드로 설정
		}
		else {
			while (1) { //삽입할 노드의 자리 찾기
				newNode->par = curNode; //만약 위치를 찾을 경우 새로운 노드의 부모가 curNode가 되므로 계속 업데이트 해줌
				newNode->depth++; //한 칸 내려갈 때마다 새로운 노드의 깊이 +1
				if (curNode->id < newNode->id)     //새로운 노드가 현재위치의 노드보다 id가 크면
					curNode = curNode->rightChild; //rightchild로 이동
				else                               //새로운 노드가 현재위치의 노드보다 id가 작으면
					curNode = curNode->leftChild;  //leftchild로 이동

				if (curNode->isLeaf==true) //현재위치가 leaf노드일 경우 탈출(위치 찾음)
					break;
			}
			newNode->isBlack = false; //red 색상의 노드 추가
			if (newNode->par->id < newNode->id) //새로운 노드가 rightchild인지 leftchild인지 결정
				newNode->par->rightChild = newNode;
			else
				newNode->par->leftChild = newNode;
			curNode = newNode; //현재위치를 새로운 노드로 설정

			curNode->leftChild = left_leaf; //새롭게 추가된 노드의 양쪽에 leaf노드 자식 추가
			curNode->rightChild = right_leaf;
			left_leaf->par = curNode;
			right_leaf->par = curNode; //leaf노드의 부모 설정
			left_leaf->depth = curNode->depth + 1;
			right_leaf->depth = curNode->depth + 1; //leaf노드의 깊이 설정
			check(curNode); //restruct, recolor 여부 결정
		}
		cout << curNode->depth << "\n";
	}
	Node* findNode(int id) {
		Node* curNode = root; //현재위치를 root로 설정
		
		while (1) {
			if (curNode == NULL||curNode->isLeaf==true) //트리가 비었거나(root==NULL) leaf노드 까지 내려갔을 경우
				return NULL;                            //찾으려는 노드가 존재하지 않음을 뜻함

			if (curNode->id == id) {  //id가 일치하면 현재위치의 노드를 찾은 노드라고 return
				return curNode;
			}
			if (curNode->id < id)     //현재위치노드의 id와 대소비교하여 left로 내려갈지 right로 내려갈지 결정
				curNode = curNode->rightChild;
			else if (curNode->id > id)
				curNode = curNode->leftChild;			
		}
	}
	void discount(int x, int y, int p) {  //할인해주는 함수
		Node* curNode = root; //현재위치를 root로 설정
		inorderTraversal(curNode, x, y, p); //중위순회를 이용하여 범위내 값 할인해주는 함수
	}
	void inorderTraversal(Node* curNode,int x,int y,int p) {
		if (curNode->isLeaf!= true) {                      //현재위치가 leaf가 아닐 때
			inorderTraversal(curNode->leftChild, x, y, p); //왼쪽 자식부터 순회
			if (x <= curNode->id && curNode->id <= y)                //[x, y]범위일 경우
				curNode->price = (curNode->price) * (100 - p) / 100; //할인
			else if (curNode->id > y)                                //id가 y보다 클 경우 함수 종료
				return;
			inorderTraversal(curNode->rightChild, x, y, p); //오른쪽 자식 순회
		}
	}
	void check(Node* curNode) { //restruct, recolor여부 결정해주는 함수
		if (curNode->par->par != NULL) { //검사하려는 노드의 할아버지 노드가 존재할 경우에만 확인
			Node* uncleNode;//uncle 노드생성
			if (curNode->par->par->leftChild != curNode->par) //할아버지노드의 왼쪽자식이 자신의 부모와 일치하지 않으면
				uncleNode = curNode->par->par->leftChild;     //그 왼쪽 자식은 자신의 uncle
			else                                              //할아버지노드의 오른쪽자식이 자신의 부모와 일치하지 않으면
				uncleNode = curNode->par->par->rightChild;    //그 오른쪽 자식은 자신의 uncle
			if (curNode->par->isBlack == false) {             //자신은 새롭게 추가되었거나 더블레드가 발생한 노드이므로 red,
															  //자신의 부모도 red이면 더블레드 발생이므로 uncle노드 색상 탐지
				if (uncleNode->isBlack == true)               //uncle노드가 black이면 restruct  
					reStruct(curNode);
				else if (uncleNode->isBlack == false)         //uncle노드가 red이면 recolor
					reColor(curNode);
			}
		}
	}
	void reStruct(Node* curNode) {
		Node* grandpar = curNode->par->par; //할아버지 노드 가리킴
		Node* Ta = NULL;                    //restruct할 때 이동하는 subgraph 4개 생성
		Node* Tb = NULL;
		Node* Tc = NULL;
		Node* Td = NULL;															//화살표 방향이 부모 방향
		if ((curNode->id < curNode->par->id && curNode->par->id < grandpar->id) ||  //2->4->6 또는
			(curNode->id > curNode->par->id && curNode->par->id > grandpar->id)) {  //2<-4<-6 인 구조일 경우
			//1. Ta Tb Tc Td 설정
			if (curNode->id < curNode->par->id && curNode->par->id < grandpar->id) { //2->4->6
				Ta = curNode->leftChild;
				Tb = curNode->rightChild;
				Tc = curNode->par->rightChild;
				Td = grandpar->rightChild;
			}
			else if (curNode->id > curNode->par->id && curNode->par->id > grandpar->id) { // 2<-4<-6
				Ta = grandpar->leftChild;
				Tb = curNode->par->leftChild;
				Tc = curNode->leftChild;
				Td = curNode->rightChild;
			}
			//2. 가운데 노드 black
			Node* newRoot = curNode->par; //가운데 노드인 4가 새로운 root가 될 것이므로(이 subgraph에서) 현재노드의 부모를 newRoot로 설정
			newRoot->isBlack = true;      //newRoot는 가운데로 가므로 black색상이 된다
			//3. 가운데 노드 부모설정			
			newRoot->par = grandpar->par; //newRoot의 부모는 기존 curNode의 할아버지 노드의 부모이다
			if (grandpar->par == NULL) {  //만약 granpar가 전체트리의 root일 경우(부모가 더 없을 경우)
				newRoot->depth = 0;       //newRoot가 전체트리의 root가 되므로 depth=0
				root = newRoot;           //전체트리의 root로 설정
			}
			else                          //그렇지 않으면 newRoot의 깊이는 그 부모의 깊이보다 +1
				newRoot->depth = newRoot->par->depth + 1;
			//4.가운데노드가 그 부모의 left인지 right인지
			if (grandpar->par != NULL) {
				if (newRoot->par->rightChild->id == grandpar->id)
					newRoot->par->rightChild = newRoot;
				else
					newRoot->par->leftChild = newRoot;
			}
			
			//5. 가운데 노드의 left, right 자식 설정. 6. 자식의 부모를 가운데노드로 설정 7. 자식들 red로 설정
			if (curNode->id < curNode->par->id && curNode->par->id < grandpar->id) { //2->4->6
				newRoot->rightChild = grandpar;
				newRoot->rightChild->isBlack = false;
				grandpar->par = newRoot;
			}
			else if (curNode->id > curNode->par->id && curNode->par->id > grandpar->id) {// 2<-4<-6
				newRoot->leftChild = grandpar;
				newRoot->leftChild->isBlack = false;
				grandpar->par = newRoot;
			}
			//자식들의 깊이 설정
			newRoot->leftChild->depth = newRoot->depth + 1;
			newRoot->rightChild->depth = newRoot->depth + 1;
			//8. ta tb tc td 적용, 부모자식 관계 설정, depth 업데이트
			newRoot->leftChild->leftChild = Ta;
			Ta->par = newRoot->leftChild;
			Ta->depth = Ta->par->depth + 1;
			updateDepth(Ta);

			newRoot->leftChild->rightChild = Tb;
			Tb->par = newRoot->leftChild;
			Tb->depth = Tb->par->depth + 1;
			updateDepth(Tb);

			newRoot->rightChild->leftChild = Tc;
			Tc->par = newRoot->rightChild;
			Tc->depth = Tc->par->depth + 1;
			updateDepth(Tc);

			newRoot->rightChild->rightChild = Td;
			Td->par = newRoot->rightChild;
			Td->depth = Td->par->depth + 1;
			updateDepth(Td);
		}
		else { //위 과정과 비슷함
			if (curNode->id > grandpar->id) {// 2<-6<-4
				Ta = grandpar->leftChild;
				Tb = curNode->leftChild;
				Tc = curNode->rightChild;
				Td = curNode->par->rightChild;
			}
			else if (curNode->id < grandpar->id) { // 6<-2<-4
				Ta = curNode->par->leftChild;
				Tb = curNode->leftChild;
				Tc = curNode->rightChild;
				Td = grandpar->rightChild;
			}
			curNode->isBlack = true;
			curNode->par = grandpar->par;
			if (grandpar->par == NULL) {			
				curNode->depth = 0;
				root = curNode;
			}
			else
				curNode->depth = curNode->par->depth + 1;
			if (grandpar->par != NULL) {
				if (curNode->par->rightChild->id == grandpar->id)
					curNode->par->rightChild = curNode;
				else
					curNode->par->leftChild = curNode;
			}
			
			if (curNode->id > grandpar->id) {// 2<-6<-4
				curNode->leftChild = grandpar;
				curNode->rightChild = grandpar->rightChild;						
			}
			else if (curNode->id < grandpar->id) { // 6<-2<-4
				curNode->leftChild = grandpar->leftChild;
				curNode->rightChild = grandpar;				
			}
			curNode->leftChild->par = curNode;
			curNode->rightChild->par = curNode;
			curNode->leftChild->depth = curNode->depth + 1;
			curNode->rightChild->depth = curNode->depth + 1;

			grandpar->isBlack = false;
			curNode->leftChild->leftChild = Ta;
			Ta->par = curNode->leftChild;
			Ta->depth = Ta->par->depth + 1;
			updateDepth(Ta);

			curNode->leftChild->rightChild = Tb;
			Tb->par = curNode->leftChild;
			Tb->depth = Tb->par->depth + 1;
			updateDepth(Tb);

			curNode->rightChild->leftChild = Tc;
			Tc->par = curNode->rightChild;
			Tc->depth = Tc->par->depth + 1;
			updateDepth(Tc);

			curNode->rightChild->rightChild = Td;
			Td->par = curNode->rightChild;
			Td->depth = Td->par->depth + 1;
			updateDepth(Td);
		}	
	}
	void updateDepth(Node* Tx) { //위치가 바뀐 서브트리들 ta,tb,tc,td노드들의 깊이 업데이트
		if (Tx->isLeaf == true) //leaf노드까지 내려가면 종료
			return;
		Tx->depth = Tx->par->depth + 1; //본인의 부모노드의 깊이보다 +1
		updateDepth(Tx->leftChild);     //재귀로 양쪽자식 모두 업데이트
		updateDepth(Tx->rightChild);
	}
	void reColor(Node* curNode) {
		Node* grandpar = curNode->par->par;
		if(root!=grandpar) //만약 할아버지노드가 전체트리의 root이면 그대로 black, 아니라면 red
			grandpar->isBlack = false;
		grandpar->leftChild->isBlack = true; //할아버지노드의 두 자식의 색은 black으로 뒤집음
		grandpar->rightChild->isBlack = true;

		if (grandpar->par != NULL) {              //할아버지의 부모가 존재하면
			if (grandpar->par->isBlack == false)  //또 더블레드가 발생하면
				check(grandpar);                  //recolor, restruct 여부 결정
		}
	}
};
int main() {
	int T; // 테스트케이스의 수
	cin >> T;
	Tree t; //Tree 클래스 객체 생성

	int id;
	string name;
	int mb;
	int price;
	while (T--) {
		char input;
		cin >> input;

		switch (input) {
		case 'I': // 노드 삽입
			cin >> id >> name >> mb >> price;
			
			if (t.findNode(id) != NULL) // 기존에 있는 노드일 경우 그 노드의 깊이만 출력
				cout << t.findNode(id)->depth << "\n";
			else
				t.insertNode(id, name, mb, price); //트리에 노드를 삽입하고 노드의 깊이를 출력
			break;
		case 'F':  // 노드 검색
			cin >> id;
			if (t.findNode(id) != NULL) { //노드를 찾으면 해당 노드 정보 출력
				cout << t.findNode(id)->depth << " " << t.findNode(id)->name
					<< " " << t.findNode(id)->mb << " " << t.findNode(id)->price << "\n";
			}
			else // 리턴값이 NULL이면 노드가 존재하지 않으므로 NULL 출력
				cout << "NULL" << "\n";
			break;
		case 'R':// 노드 업데이트
			cin >> id >> name >> mb >> price;
			if (t.findNode(id) != NULL) { //해당 노드를 찾으면 정보 업데이트 후 노드의 깊이 출력
				t.findNode(id)->name = name;
				t.findNode(id)->mb = mb;
				t.findNode(id)->price = price;
				cout << t.findNode(id)->depth << "\n";
			}
			else// 리턴값이 NULL이면 노드가 존재하지 않으므로 NULL 출력
				cout << "NULL" << "\n";
			break;
		case 'D'://할인
			int x, y, p; //x:범위의 시작, y:범위의 끝, P:할인율
			cin >> x >> y >> p;
			t.discount(x, y, p);
		}

	}
}
