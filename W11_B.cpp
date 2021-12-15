#include<iostream>
using namespace std;
char** paper;
int T, N;
struct paperInfo {
	int redNum=0, redSize=0, blueNum=0, blueSize=0;
};
paperInfo solution(int x, int y, int size) {
	paperInfo ret;
	if (size == 1) {
		if (paper[x][y] == 'R')
			ret.redNum = ret.redSize = 1;
		else
			ret.blueNum = ret.blueSize = 1;
		return ret;
	}
	paperInfo status[5];
	status[1] = solution(x, y, size / 2);
	status[2] = solution(x + size / 2, y, size / 2);
	status[3] = solution(x, y + size / 2, size / 2);
	status[4] = solution(x + size / 2, y + size / 2, size / 2);

	for (int i = 1; i <= 4; i++) {
		ret.redNum += status[i].redNum;
		ret.redSize += status[i].redSize;
		ret.blueNum += status[i].blueNum;
		ret.blueSize += status[i].blueSize;
	}
	if (ret.redNum == 0)
		ret.blueNum = 1;
	if (ret.blueNum == 0)
		ret.redNum = 1;
	return ret;
}
int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		paper = new char* [N];
		for (int i = 0; i < N; i++) {
			paper[i] = new char[N];
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> paper[i][j];
			}
		}
		paperInfo answer = solution(0, 0, N);
		cout << answer.redNum << " " << answer.redSize << " " <<
			answer.blueNum << " " << answer.blueSize << "\n";
	}
}