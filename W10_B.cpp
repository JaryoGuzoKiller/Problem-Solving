#include<iostream>
using namespace std;
int T, N, answer;
int* Matyro;
int* DP;

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		Matyro = new int[N + 1];
		DP= new int[N + 1];
		for (int i = 1; i <= N; i++) {
			cin >> Matyro[i];
		}
		answer = 0;
		for (int i = 1; i <= N; i++) {
			DP[i] = 1;
			for (int j = 1; j <= i - 1; j++) {
				if (Matyro[j] < Matyro[i])
					DP[i] = max(DP[i], DP[j] + 1);				
			}
			answer = max(DP[i], answer);
		}
		cout << answer << "\n";
	}
}