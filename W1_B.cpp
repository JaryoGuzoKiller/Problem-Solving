#include<iostream>
#include<vector>
#include<stack>
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

		stack<int> tower;
		stack<int> min;
		stack<int> max;
		while (N--) {
			int q;
			cin >> q;

			if (q == 1) {
				int num;
				cin >> num;
				tower.push(num);

				if (min.empty())
					min.push(num);
				else if(min.top() >= num)
					min.push(num);

				if (max.empty())
					max.push(num);
				else if(max.top() <= num)
					max.push(num);

				cout << min.top() << " " << max.top() << "\n";
			}
			else if (q == 2) {
				if (!tower.empty()) {
					if (min.top() == tower.top())
						min.pop();
					if (max.top() == tower.top())
						max.pop();

					tower.pop();			
				}
			}			
		}
	}
	return 0;
}
