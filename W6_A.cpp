#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct counter {
	int sec = 0;
	int price = 0;
	//bool empty = true;
};
struct guest {
	int sec;
	int price;
};
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	cin >> N >> M;

	vector<counter> counter_arr;
	for (int i = 0; i < N; i++) {
		counter_arr.push_back({ 0,0 });
	}

	queue<guest> guest_q;
	int s, p;

	for (int i = 0; i < M; i++) {	
		cin >> s >> p;
		guest_q.push({ s,p });
	}
	int sec = 0;
	while (1) {		
		sec++;

		for (int i = 0; i < N; i++) {
			if (counter_arr[i].sec == 0&&!guest_q.empty()) {
				counter_arr[i].sec += guest_q.front().sec;
				counter_arr[i].price += guest_q.front().price;
				guest_q.pop();
				if(counter_arr[i].sec>=1)
					counter_arr[i].sec--;
			}
			else
				if (counter_arr[i].sec >= 1)
					counter_arr[i].sec--;
		}
		bool all_clear = true;
		for (int i = 0; i < N; i++) {
			if (counter_arr[i].sec != 0) {
				all_clear = false;
				break;
			}
		}
		if (guest_q.empty() && all_clear == true) {
			cout << sec << "\n";
			for (int i = 0; i < N; i++) {
				cout << counter_arr[i].price << "\n";
			}
			break;
		}
	}
	return 0;
}