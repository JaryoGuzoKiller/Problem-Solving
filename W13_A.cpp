#include<iostream>
#include<vector>
using namespace std;
int N, M;
int* F;
void failureFunction(string P) {
	F = new int[P.size()];
	F[0] = 0;
	int i = 1, j = 0;
	int n = N;
	int m = P.size();

	while (i < m) {
		if (P[i] == P[j]) {
			F[i] = j + 1;
			i++;
			j++;
		}
		else if (j > 0)
			j = F[j - 1];
		else {
			F[i] = 0;
			i++;
		}
	}
}
int kmp(string P, string T) {
	failureFunction(P);
	int i = 0, j = 0;
	int n = T.size();
	int m = P.size();

	while (i < n) {
		if (T[i] == P[j]) {
			if (j == m - 1)
				return 1;
			else {
				i++;
				j++;
			}
		}
		else if (T[i] != P[j]) {
			if (j > 0)
				j = F[j - 1];
			else
				i++;
		}
	}
	delete F;
	return 0;
}

int main() {

	cin >> N >> M;

	char** map = new char* [N];
	for (int i = 0; i < N; i++) {
		map[i] = new char[N];
	}

	string row;
	for (int i = 0; i < N; i++) {
		cin >> row;
		for (int j = 0; j < N; j++) {
			map[i][j] = row[j];
		}
	}
	vector<string> text;
	//¼¼·Î
	for (int i = 0; i < N; i++) {
		string word;
		for (int j = 0; j < N; j++) {
			word += map[i][j];
		}
		text.push_back(word);
	}

	//°¡·Î		
	for (int i = 0; i < N; i++) {
		string word;
		for (int j = 0; j < N; j++) {
			word += map[j][i];
		}
		text.push_back(word);
	}
	//´ë°¢¼±
	int i = -1, j = N - 2;
	int k = j;
	string word;
	while (1) {
		i++;
		j++;
		word += map[i][j];

		if (j == N - 1) {
			if (k == -1) break;

			i = -1;
			k--;
			j = k;

			text.push_back(word);
			word.clear();
		}
	}
	i = 0, j = -1;
	k = i;
	while (1) {
		i++;
		j++;
		word += map[i][j];

		if (i == N - 1) {
			if (k == N - 2) break;

			j = -1;
			k++;
			i = k;

			text.push_back(word);
			word.clear();
		}
	}
	while (M--) {
		string pattern;
		cin >> pattern;

		bool exist = false;
		for (int i = 0; i < text.size(); i++) {
			if (kmp(pattern, text[i]) == 1) {
				cout << "1" << "\n";
				exist = true;
				break;
			}
		}
		if (!exist) cout << "0" << "\n";
	}
}