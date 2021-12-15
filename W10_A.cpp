#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int T, A, B;
vector<int>* road = new vector<int>[10000];
int* check = new int[10000];
queue<int> q;

int main() {
	for (int i = 0; i < 10000; i++) {
		if (i != 0)
			road[i].push_back(i - 1);
		if (i != 9999)
			road[i].push_back(i + 1);
		int num = 0, temp = i;

		for (int j = 0; j <= 3; j++) {
			num = num * 10 + temp % 10;
			temp /= 10;
		}
		road[i].push_back(num);
	}

	cin >> T;
	while (T--) {
		for (int i = 0; i < 10000; i++) {
			check[i] = -1;
		}
		cin >> A >> B;
		check[A] = 0;
		q.push(A);
		
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			
			for (int i = 0; i < road[cur].size(); i++) {
				if (check[road[cur][i]] == -1) {
					q.push(road[cur][i]);
					check[road[cur][i]] = check[cur] + 1;
				}
				if (road[cur][i] == B) {
					while (!q.empty())
						q.pop();
					break;
				}
			}
		}
		cout << check[B] << "\n";
	}
}