#include<iostream>
#include<vector>
using namespace std;

struct Node {
	int par = 0;
	vector<int> children;
	int length = 0;
};
int T, N;
Node* Tree;
int dir[50001];

void TreeTraversal(int u) {
	if (u == 1)
		dir[u] = 4;
	else
		dir[u] = dir[Tree[u].par]+Tree[u].length + 1;

	for (int i = 0; i < Tree[u].children.size(); i++) {
		TreeTraversal(Tree[u].children[i]);
	}
}

int main() {
	cin >> T;
	while (T--) {
		cin >> N;	
		Tree = new Node[N+1];
		for (int i = 1; i < N; i++) {
			int a, b;
			cin >> a >> b;
			Tree[a].children.push_back(b);
			Tree[b].par = a;
		}
		
		string s;
		for (int i = 1; i <= N; i++) {
			cin >> s;
			Tree[i].length = s.size();
		}
		TreeTraversal(1);

		for (int i = 1; i <= N; i++) {
			cout << dir[i] << "\n";
		}
	}
}
