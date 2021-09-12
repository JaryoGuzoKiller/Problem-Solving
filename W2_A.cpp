#include<iostream>
#include<queue>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	while (T--) {
		int N, M;//3 7
		cin >> N >> M;

		string* temp = new string[M];

		queue<string> sentence;

		for (int i = 0; i < M; i++) {
			cin >> temp[i];
			sentence.push(temp[i]);
		}

		queue<string>* word = new queue<string>[N];
		for (int i = 0; i < N; i++) {
			int k;
			cin >> k;

			string* stemp = new string[k];
			for (int j = 0; j < k; j++) {
				cin >> stemp[j];
				word[i].push(stemp[j]);
			}
		}
		int not_in_word = 0;
		for (int i = 0; i < M; i++) {

			if (sentence.front() == word[i].front()) {
				sentence.pop();
				word[i].pop();
				i = -1;
				not_in_word = 0;
				if (sentence.empty()) {
					cout << "1" << "\n";
					break;
				}
			}
			else {
				not_in_word++;
				if (not_in_word == N) {
					cout << "0" << "\n";
					break;
				}
			}

		}
	}
}