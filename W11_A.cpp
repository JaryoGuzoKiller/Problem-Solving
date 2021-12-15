#include<iostream>
#include<vector>
using namespace std;
int* score;
int** needAlphabet;
int** restAlphabet;
int M, answer;
string word;
int* getScore;
int main() {
	cin >> M;
	score = new int[M + 1];
	needAlphabet = new int*[M + 1];
	for (int i = 0; i < M + 1; i++) {
		needAlphabet[i] = new int[26 + 1];
	}

	int k = 1;
	for (int i = 0; i < M; i++) {
		k *= 2;
	}
	restAlphabet = new int* [k + 1];
	for (int i = 0; i < k + 1; i++) {
		restAlphabet[i] = new int[26 + 1];
	}
	getScore = new int[k + 1];

	for (int i = 1; i <= 26; i++) {
		cin >> restAlphabet[0][i];
	}

}