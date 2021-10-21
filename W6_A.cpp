#include<iostream>
#include<queue>
using namespace std;

struct customerInfo {
	int useTime, cost;
};

struct counterInfo {
	int endTime, number;

	bool operator<(const counterInfo c)const {
		if (this->endTime == c.endTime)
			return this->number > c.number;
		else
			return this->endTime > c.endTime;
	}
};

customerInfo* customer;
priority_queue<counterInfo> counterPQ;
int* costAnswer;
int N, M, timeAnswer;

int main() {
	cin >> N >> M;
	customer = new customerInfo[M + 1];
	costAnswer = new int[N + 1];
	for (int i = 1; i <= M; i++) {
		cin >> customer[i].useTime >> customer[i].cost;
	}

	for (int i = 1; i <= N;i++) {
		counterPQ.push({ customer[i].useTime,i });
		costAnswer[i] = customer[i].cost;
		timeAnswer = max(timeAnswer, customer[i].useTime);
	}

	for (int i = N + 1; i <= M; i++) {
		counterInfo counterTemp = counterPQ.top();
		counterPQ.pop();
		counterTemp.endTime += customer[i].useTime;
		costAnswer[counterTemp.number] += customer[i].cost;
		timeAnswer = max(timeAnswer, counterTemp.endTime);
		counterPQ.push(counterTemp);
	}
	cout << timeAnswer << "\n";
	for (int i = 1; i <= N; i++) {
		cout << costAnswer[i] << "\n";
	}
}
