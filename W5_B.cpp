#include<iostream>
#include<vector>
using namespace std;
int N, M, answer;
int* houseArr;
bool check(int length) {
	int house = 1;
	int count = 0;
	for (int i = 1; i <= N; i++) {
		if (house <= houseArr[i]) {
			house = houseArr[i] + length;
			count++;
		}
		if (count == M)
			return true;
	}
	return false;
}

int solution(int left, int right) {
	int mid;
	if (left == right)
		return left;
	if (left + 1 == right) {
		if (check(right))
			return right;
		else
			return left;
	}
	mid = (left + right) / 2;
	if (check(mid))
		return solution(mid, right);
	else
		return solution(left, mid - 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	houseArr = new int[N + 1];

	for (int i = 1; i <= N; i++)
		cin >> houseArr[i];
	answer = solution(1, houseArr[N] - 1);//거리의 최댓값 이므로 -1
	cout << answer;
}