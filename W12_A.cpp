#include<iostream>
#include<vector>
using namespace std;
int T, N;
int** num;
int** path;
int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		num = new int* [N + 1];
		path = new int* [N + 1];
		for (int i = 0; i < N + 1; i++) {
			num[i] = new int[N + 1];
			path[i] = new int[N + 1];
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= i; j++) {
				cin >> num[i][j];
			}
		}
		path[1][1] = num[1][1];
		for (int i = 2; i <= N; i++) {
			path[i][1] = path[i - 1][1] + num[i][1];
			for (int j = 2; j < i; j++)
				path[i][j] = min(path[i - 1][j-1], path[i - 1][j]) + num[i][j];
			path[i][i] = path[i - 1][i - 1] + num[i][i];
		}
		int answer = path[N][1];
		for (int j = 2; j <= N; j++)
			answer = min(answer, path[N][j]);
		cout << answer << "\n";
	}
}