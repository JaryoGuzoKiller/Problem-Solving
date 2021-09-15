#include<iostream>
#include<utility>
#include<algorithm>
using namespace std;

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
	return a.first + a.second > b.first + b.second;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;


	while (T--) {
		int N;
		cin >> N;

		pair<int, int>* src = new pair<int, int>[N];

		int a_src, b_src;
		for (int i = 0; i < N; i++) {
			cin >> a_src >> b_src;
			src[i].first = a_src;
			src[i].second = b_src;
		}
		sort(&src[0], &src[N], compare); //두 자원의 합으로 내림차순 정렬

		int inha_src = 0, dragon_src = 0;

		int flag = 0;
		for (int i = 0; i < N; i++) {
			if (flag == 0) {
				inha_src += src[i].first;
				flag = 1;
			}
			else if (flag == 1) {
				dragon_src += src[i].second;
				flag = 0;
			}
		}
		cout << inha_src - dragon_src << "\n";
	}
}
