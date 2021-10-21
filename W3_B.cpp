#include<iostream>
#include<vector>
using namespace std;

int T, N, answer;
struct roadInfo {
	int neighbor, distance;
};
vector<roadInfo>* house;
bool visited[2001] = { false, };
int getMax(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int treeSearch(int u) {
	int max = 0, secondMax = 0;
	int temp;

	visited[u] = true;
	for (int i = 0; i < house[u].size(); i++) {
		if (!visited[house[u][i].neighbor]) {
			temp = treeSearch(house[u][i].neighbor) + house[u][i].distance;
			if (temp > max) {
				int a;
				a = max;
				max = temp;
				temp = a;
			}
			if (temp > secondMax) {
				int a;
				a = secondMax;
				secondMax = temp;
				temp = a;
			}
		}		
	}
	answer = getMax(answer, max + secondMax);
	return max;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> N;
		house = new vector<roadInfo>[N+1];

		int u, v, d;
		for (int i = 1; i < N; i++) {
			cin >> u >> v >> d;
			house[u].push_back({ v,d });
			house[v].push_back({ u,d });
		}
		answer = 0;
		for (int i = 0; i < 2001; i++) {
			visited[i] = false;
		}
		treeSearch(1);
		
		cout << answer << "\n";
	}
}