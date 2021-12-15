#include<iostream>
#include<set>
using namespace std;
int T, N, M;
int* messenger;
int* answer;
int main() {
	cin >> T;
	while (T--) {
		cin >> N >> M;
		messenger = new int[M + 1];
		answer = new int[M + 1];
		for (int i = 1; i <= M; i++)
			cin >> messenger[i];
		set<int> readers;
		for (int i = M; i >= 1; i--) {
			if (readers.find(messenger[i]) == readers.end())
				readers.insert(messenger[i]);
			answer[i] = N - readers.size();
		}
		for (int i = 1; i <= M; i++)
			cout << answer[i] << "\n";
	
	}
}