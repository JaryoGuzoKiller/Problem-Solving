#include<iostream>
#include<vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;

		vector<int> a;
		vector<int> b;

		for (int i = 0; i < N; i++) {
			int num1, num2;
			cin >> num1 >> num2;

			a.push_back(num1);
			b.push_back(num2);
		}

		int diff = 0, temp = 0;
		int a_result = 0, b_result = 0;
		bool flag = true;
		int max = a[0] - b[0];
		while (!a.empty()) {
			for (int i = 0; i < a.size(); i++) {

				if (flag == true)
					diff = a[i] - b[i];
				else {
					diff = (a[i] - b[i]) * -1;
					max = max * -1;
				}
				if (max <= diff) {
					temp = i;
					max = diff;
				}
			}
			max = a[0] - b[0];
			if (flag == true) {
				a_result = a_result + a[temp];
				a.erase(a.begin() + temp);
				b.erase(b.begin() + temp);
				flag = false;
			}
			else if (flag == false) {
				b_result = b_result + b[temp];
				a.erase(a.begin() + temp);
				b.erase(b.begin() + temp);
				flag = true;
			}
			
		}
		cout << a_result - b_result << "\n";
	}
}
