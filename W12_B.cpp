#include<iostream>
#include<algorithm>
using namespace std;

int main() {
	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		pair<int, int>* list = new pair<int, int>[N];
		int score, dist;
		for (int i = 0; i < N; i++) {
			cin >> score >> dist;
			list[i].first = score;
			list[i].second = dist;
		}
		sort(&list[0], &list[N]);
	
		int min_dist = list[N - 1].second;
		int count = 1;
		for (int i = N-2; i >= 0; i--) {		
			if (list[i].second < min_dist) {
				count++;
				min_dist = list[i].second;
			}
		}
		cout << count << "\n";
	}
}