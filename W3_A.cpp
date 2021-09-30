#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Node {
public:
	string name;
	int num;
	Node* par;

	Node(int num) {
		this->name = "";
		this->num = num;
		this->par = NULL;
	}
	void setParent(Node* par) {
		this->par = par;
	}
	void setName(string name) {
		this->name = name;
	}

};
bool compare(Node* node1, Node* node2) {
	return node1->num < node2->num;
}
class Tree {
public:
	Node* root;
	vector<Node*>node_list;

	Tree(int num) {
		Node* node = new Node(num);
		root = node;
		node_list.push_back(node);
	}
	void insertNode(int par_num, int num) {
		for (int i = 0; i < node_list.size(); i++) {
			if (node_list[i]->num == par_num) {
				for (int j = 0; j < node_list.size(); j++) {
					if (node_list[j]->num == num) {
						node_list[j]->setParent(node_list[i]);
					
						return;
					}
				}
				Node* node = new Node(num);
				node->setParent(node_list[i]);
							
				node_list.push_back(node);
				return;
			}
		}
		Node* newNode = new Node(par_num);
		Node* node = new Node(num);

		node->setParent(newNode);
		
		node_list.push_back(newNode);
		node_list.push_back(node);
	}
	void print() {
		for (int i = 0; i < node_list.size(); i++) {
			Node* node = node_list[i];
			int length = 0;
			length += node_list[i]->name.size();
			while (node != root) {
				node = node->par;
				length += node->name.size() + 1;
			}	
			cout << length << "\n";
		}
		
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		int temp = N;
		Tree tree(1);

		N--;
		while (N--) {
			int par_num, num;
			cin >> par_num >> num;
			tree.insertNode(par_num, num);
		}
		sort(tree.node_list.begin(), tree.node_list.end(), compare);
		string data;
		for (int i = 0; i < temp; i++) {
			cin >> data;
			tree.node_list[i]->name = data;
		}
		tree.print();
	}

	return 0;
}