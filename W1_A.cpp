#include<iostream>
#include<vector>
using namespace std;
int T;
string s;
int k;
vector<char>* arr = { NULL, };

int main() {
	cin >> T;
	while (T--) {
		cin >> s;
		cin >> k;
		arr = new vector<char>[k+1];

		
		int garo;
		if (s.size() % k != 0)
			garo = s.size() / k + 1;
		else
			garo = s.size() / k;

		for (int i = 1; i <= k; i++) {
			for (int j = 1; j <= garo; j++) {
				if (j == 1&& (j * i - 1) < s.size())
					arr[i].push_back(s[j * i - 1]);
				else if (j % 2 == 0&&(j * k - i)<s.size())
					arr[i].push_back(s[j * k - i]);
				else if(j % 2 != 0&& ((j - 1) * k + i - 1)<s.size())
					arr[i].push_back(s[(j - 1) * k + i - 1]);
			}
		}
		for (int i = 1; i <= k; i++) {
			for (int j = 0; j < arr[i].size(); j++) {
				if(arr[i][j]!=NULL)
					cout << arr[i][j];
			}
		}
		cout << "\n";
	}
}
