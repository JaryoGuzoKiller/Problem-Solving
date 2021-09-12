#include<iostream>
#include<vector>
using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector<char*> zigList;
	while (n--) {
		int row;
		string word;
		cin >> word;
		cin >> row;


		word.c_str();

		int numOfzig = word.size() / row;
		if (word.size() % row != 0)
			numOfzig++;

		char** zig = new char* [row + 1];
		for (int i = 0; i < row + 1; ++i) {
			zig[i] = new char[numOfzig + 1];
			
		}

		for (int i = 0; i < row; i++) {                       //확인위해 0부터 차례로 값넣어줍니다.

			for (int j = 0; j < numOfzig + 1; j++) {

				zig[i][j] = NULL;

			}

		}
		int i = 0, j = 1;
		int flag = 1;
		for (int m = 0; m < word.size(); m++) {

			if (m % row == 0) {

				if (m != 0 && flag % 2 == 1) {
					j++;
					i++;
					flag++;
				}
				else if (m != 0 && flag % 2 == 0) {
					i--;
					j++;
					flag++;
				}
			}

			if (flag % 2 == 1) {
				i++;
			}
			else {
				i--;
			}
			zig[i][j] = word[m];
		}

		for (int i = 1; i < row+1; i++) {
			for (int j = 1; j < numOfzig+1; j++) {
				if (zig[i][j] != NULL) {
					cout << zig[i][j];
				}
			}
		}
		cout << "\n";
	}
	//
}