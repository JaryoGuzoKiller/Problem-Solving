#include<iostream>
using namespace std;

class Node {
public:
	bool isLeaf = false; //leaf ��� ���� ����
	bool isBlack = true; //����� ��, true�̸� black, false �̸� red, �⺻���� black

	int id;      //id
	string name; //�̸�
	int mb;      //�뷮
	int price;   //����

	int depth = 0;

	Node* leftChild = NULL;  //���� �ڽĳ���� ������
	Node* rightChild = NULL; //������ �ڽĳ���� ������
	Node* par = NULL;        //�θ� ����� ������

	Node(int id, string name, int mb, int price) { //������ �Է� ���� ��� ������
		this->id = id;
		this->name = name;
		this->mb = mb;
		this->price = price;
	}
	Node() { //leaf node ������
		this->isLeaf = true;
	}
};

class Tree {
public:
	Node* root;	
	Tree() {
		root = NULL;
	}
	void insertNode(int id, string name, int mb, int price) { //��� ����
		Node* newNode = new Node(id, name, mb, price); //�Է¹��� ������ ���ο� ��� ����
		Node* curNode = root; //���� �����ġ�� root�� ����
		Node* left_leaf=new Node(); //���� leaf ���
		Node* right_leaf=new Node();//������ leaf ���


		if (root == NULL) { //Ʈ���� ���������
			root = newNode; //���Ե� ��尡 root�� �ȴ�
		
			root->leftChild = left_leaf; 
			root->rightChild = right_leaf; //root�� �����ڽĿ� leaf��� �߰�
			left_leaf->par = root;
			right_leaf->par = root;//�߰��� ���� leaf����� �θ� root�� ����
			left_leaf->depth = root->depth + 1; 
			right_leaf->depth = root->depth + 1; //�߰��� ���� leaf����� ���̸� root�� ���̺��� +1
			curNode = newNode; //���� ����� ��ġ�� ���Ե� ���� ����
		}
		else {
			while (1) { //������ ����� �ڸ� ã��
				newNode->par = curNode; //���� ��ġ�� ã�� ��� ���ο� ����� �θ� curNode�� �ǹǷ� ��� ������Ʈ ����
				newNode->depth++; //�� ĭ ������ ������ ���ο� ����� ���� +1
				if (curNode->id < newNode->id)     //���ο� ��尡 ������ġ�� ��庸�� id�� ũ��
					curNode = curNode->rightChild; //rightchild�� �̵�
				else                               //���ο� ��尡 ������ġ�� ��庸�� id�� ������
					curNode = curNode->leftChild;  //leftchild�� �̵�

				if (curNode->isLeaf==true) //������ġ�� leaf����� ��� Ż��(��ġ ã��)
					break;
			}
			newNode->isBlack = false; //red ������ ��� �߰�
			if (newNode->par->id < newNode->id) //���ο� ��尡 rightchild���� leftchild���� ����
				newNode->par->rightChild = newNode;
			else
				newNode->par->leftChild = newNode;
			curNode = newNode; //������ġ�� ���ο� ���� ����

			curNode->leftChild = left_leaf; //���Ӱ� �߰��� ����� ���ʿ� leaf��� �ڽ� �߰�
			curNode->rightChild = right_leaf;
			left_leaf->par = curNode;
			right_leaf->par = curNode; //leaf����� �θ� ����
			left_leaf->depth = curNode->depth + 1;
			right_leaf->depth = curNode->depth + 1; //leaf����� ���� ����
			check(curNode); //restruct, recolor ���� ����
		}
		cout << curNode->depth << "\n";
	}
	Node* findNode(int id) {
		Node* curNode = root; //������ġ�� root�� ����
		
		while (1) {
			if (curNode == NULL||curNode->isLeaf==true) //Ʈ���� ����ų�(root==NULL) leaf��� ���� �������� ���
				return NULL;                            //ã������ ��尡 �������� ������ ����

			if (curNode->id == id) {  //id�� ��ġ�ϸ� ������ġ�� ��带 ã�� ����� return
				return curNode;
			}
			if (curNode->id < id)     //������ġ����� id�� ��Һ��Ͽ� left�� �������� right�� �������� ����
				curNode = curNode->rightChild;
			else if (curNode->id > id)
				curNode = curNode->leftChild;			
		}
	}
	void discount(int x, int y, int p) {  //�������ִ� �Լ�
		Node* curNode = root; //������ġ�� root�� ����
		inorderTraversal(curNode, x, y, p); //������ȸ�� �̿��Ͽ� ������ �� �������ִ� �Լ�
	}
	void inorderTraversal(Node* curNode,int x,int y,int p) {
		if (curNode->isLeaf!= true) {                      //������ġ�� leaf�� �ƴ� ��
			inorderTraversal(curNode->leftChild, x, y, p); //���� �ڽĺ��� ��ȸ
			if (x <= curNode->id && curNode->id <= y)                //[x, y]������ ���
				curNode->price = (curNode->price) * (100 - p) / 100; //����
			else if (curNode->id > y)                                //id�� y���� Ŭ ��� �Լ� ����
				return;
			inorderTraversal(curNode->rightChild, x, y, p); //������ �ڽ� ��ȸ
		}
	}
	void check(Node* curNode) { //restruct, recolor���� �������ִ� �Լ�
		if (curNode->par->par != NULL) { //�˻��Ϸ��� ����� �Ҿƹ��� ��尡 ������ ��쿡�� Ȯ��
			Node* uncleNode;//uncle ������
			if (curNode->par->par->leftChild != curNode->par) //�Ҿƹ�������� �����ڽ��� �ڽ��� �θ�� ��ġ���� ������
				uncleNode = curNode->par->par->leftChild;     //�� ���� �ڽ��� �ڽ��� uncle
			else                                              //�Ҿƹ�������� �������ڽ��� �ڽ��� �θ�� ��ġ���� ������
				uncleNode = curNode->par->par->rightChild;    //�� ������ �ڽ��� �ڽ��� uncle
			if (curNode->par->isBlack == false) {             //�ڽ��� ���Ӱ� �߰��Ǿ��ų� �����尡 �߻��� ����̹Ƿ� red,
															  //�ڽ��� �θ� red�̸� ������ �߻��̹Ƿ� uncle��� ���� Ž��
				if (uncleNode->isBlack == true)               //uncle��尡 black�̸� restruct  
					reStruct(curNode);
				else if (uncleNode->isBlack == false)         //uncle��尡 red�̸� recolor
					reColor(curNode);
			}
		}
	}
	void reStruct(Node* curNode) {
		Node* grandpar = curNode->par->par; //�Ҿƹ��� ��� ����Ŵ
		Node* Ta = NULL;                    //restruct�� �� �̵��ϴ� subgraph 4�� ����
		Node* Tb = NULL;
		Node* Tc = NULL;
		Node* Td = NULL;															//ȭ��ǥ ������ �θ� ����
		if ((curNode->id < curNode->par->id && curNode->par->id < grandpar->id) ||  //2->4->6 �Ǵ�
			(curNode->id > curNode->par->id && curNode->par->id > grandpar->id)) {  //2<-4<-6 �� ������ ���
			//1. Ta Tb Tc Td ����
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
			//2. ��� ��� black
			Node* newRoot = curNode->par; //��� ����� 4�� ���ο� root�� �� ���̹Ƿ�(�� subgraph����) �������� �θ� newRoot�� ����
			newRoot->isBlack = true;      //newRoot�� ����� ���Ƿ� black������ �ȴ�
			//3. ��� ��� �θ���			
			newRoot->par = grandpar->par; //newRoot�� �θ�� ���� curNode�� �Ҿƹ��� ����� �θ��̴�
			if (grandpar->par == NULL) {  //���� granpar�� ��üƮ���� root�� ���(�θ� �� ���� ���)
				newRoot->depth = 0;       //newRoot�� ��üƮ���� root�� �ǹǷ� depth=0
				root = newRoot;           //��üƮ���� root�� ����
			}
			else                          //�׷��� ������ newRoot�� ���̴� �� �θ��� ���̺��� +1
				newRoot->depth = newRoot->par->depth + 1;
			//4.�����尡 �� �θ��� left���� right����
			if (grandpar->par != NULL) {
				if (newRoot->par->rightChild->id == grandpar->id)
					newRoot->par->rightChild = newRoot;
				else
					newRoot->par->leftChild = newRoot;
			}
			
			//5. ��� ����� left, right �ڽ� ����. 6. �ڽ��� �θ� ������� ���� 7. �ڽĵ� red�� ����
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
			//�ڽĵ��� ���� ����
			newRoot->leftChild->depth = newRoot->depth + 1;
			newRoot->rightChild->depth = newRoot->depth + 1;
			//8. ta tb tc td ����, �θ��ڽ� ���� ����, depth ������Ʈ
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
		else { //�� ������ �����
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
	void updateDepth(Node* Tx) { //��ġ�� �ٲ� ����Ʈ���� ta,tb,tc,td������ ���� ������Ʈ
		if (Tx->isLeaf == true) //leaf������ �������� ����
			return;
		Tx->depth = Tx->par->depth + 1; //������ �θ����� ���̺��� +1
		updateDepth(Tx->leftChild);     //��ͷ� �����ڽ� ��� ������Ʈ
		updateDepth(Tx->rightChild);
	}
	void reColor(Node* curNode) {
		Node* grandpar = curNode->par->par;
		if(root!=grandpar) //���� �Ҿƹ�����尡 ��üƮ���� root�̸� �״�� black, �ƴ϶�� red
			grandpar->isBlack = false;
		grandpar->leftChild->isBlack = true; //�Ҿƹ�������� �� �ڽ��� ���� black���� ������
		grandpar->rightChild->isBlack = true;

		if (grandpar->par != NULL) {              //�Ҿƹ����� �θ� �����ϸ�
			if (grandpar->par->isBlack == false)  //�� �����尡 �߻��ϸ�
				check(grandpar);                  //recolor, restruct ���� ����
		}
	}
};
int main() {
	int T; // �׽�Ʈ���̽��� ��
	cin >> T;
	Tree t; //Tree Ŭ���� ��ü ����

	int id;
	string name;
	int mb;
	int price;
	while (T--) {
		char input;
		cin >> input;

		switch (input) {
		case 'I': // ��� ����
			cin >> id >> name >> mb >> price;
			
			if (t.findNode(id) != NULL) // ������ �ִ� ����� ��� �� ����� ���̸� ���
				cout << t.findNode(id)->depth << "\n";
			else
				t.insertNode(id, name, mb, price); //Ʈ���� ��带 �����ϰ� ����� ���̸� ���
			break;
		case 'F':  // ��� �˻�
			cin >> id;
			if (t.findNode(id) != NULL) { //��带 ã���� �ش� ��� ���� ���
				cout << t.findNode(id)->depth << " " << t.findNode(id)->name
					<< " " << t.findNode(id)->mb << " " << t.findNode(id)->price << "\n";
			}
			else // ���ϰ��� NULL�̸� ��尡 �������� �����Ƿ� NULL ���
				cout << "NULL" << "\n";
			break;
		case 'R':// ��� ������Ʈ
			cin >> id >> name >> mb >> price;
			if (t.findNode(id) != NULL) { //�ش� ��带 ã���� ���� ������Ʈ �� ����� ���� ���
				t.findNode(id)->name = name;
				t.findNode(id)->mb = mb;
				t.findNode(id)->price = price;
				cout << t.findNode(id)->depth << "\n";
			}
			else// ���ϰ��� NULL�̸� ��尡 �������� �����Ƿ� NULL ���
				cout << "NULL" << "\n";
			break;
		case 'D'://����
			int x, y, p; //x:������ ����, y:������ ��, P:������
			cin >> x >> y >> p;
			t.discount(x, y, p);
		}

	}
}