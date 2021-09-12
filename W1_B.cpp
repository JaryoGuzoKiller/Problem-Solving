#include<iostream>
#include<vector>
using namespace std;

void print(vector<int> list) {
	int max = 1;
	int min = 1000;
	for (int i = 0; i < list.size(); i++) {
		if (max < list[i])
			max = list[i];
		if (min > list[i])
			min = list[i];
	}

	cout << min << " " << max << "\n";
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

		vector<int> tower;
		while (N--) {
			int q;
			cin >> q;

			if (q == 1) {
				int num;
				cin >> num;

				tower.push_back(num);

				print(tower);
			}
			else if (q == 2) {
				if(!tower.empty())
					tower.pop_back();
			}			
		}
	}
	return 0;
}