#include <bits/stdc++.h>
#define fr(x) scanf("%d", &x)
using namespace std;

char inp[100];
vector<int> col[100];
vector<int> row[100];
int state[100][100];
char *pch;
int cnt[100], numcnt;

void brute(int pos, int givenpos, int numspaces, int n, const vector<int> &given, vector<int> &curstate, vector<int> &tempstate) {
	if(pos == n) {
		++numcnt;
		for(int i=0; i<n; ++i) {
			if(tempstate[i]) ++cnt[i];
		}
		return;
	}
	if(numspaces and curstate[pos] != 1) brute(pos+1, givenpos, numspaces - 1, n, given, curstate, tempstate);
	if(givenpos == given.size()) return;
	for(int i=0; i<given[givenpos]; ++i) {
		tempstate[pos + i] = 1;
	}
	bool validmove = true;
	for(int i=0; i<=given[givenpos]; ++i) {
		int idx = i + pos;
		if(idx >= tempstate.size()) break;
		if(curstate[idx] != -1 and curstate[idx] != tempstate[idx]) {
			validmove = false;
			break;
		}
	}
	if(validmove) brute(min(n, pos + given[givenpos] + 1), givenpos + 1, numspaces, n, given, curstate, tempstate);
	for(int i=0; i<given[givenpos]; ++i) {
		tempstate[pos + i] = 0;
	}
}

void apply(int n, const vector<int> &given, vector<int> &curstate) {
	vector<int> tempstate;
	tempstate.resize(n);
	numcnt = 0;
	for(int i=0; i<n; ++i) cnt[i] = 0;
	if(given.size() == 1 and given[0] == 0) {
		for(int i=0; i<n; ++i) {
			curstate[i] = 0;
		}
		return;
	}
	int sum = 0;
	for(int i=0; i<given.size(); ++i) sum += given[i];
	brute(0, 0, n - sum - given.size() + 1, n, given, curstate, tempstate);
	for(int i=0; i<n; ++i) {
		if(cnt[i] == 0) curstate[i] = 0;
		else if(cnt[i] == numcnt) curstate[i] = 1;
	}
}

bool solved(int n) {
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			if(state[i][j] == -1) return false;
		}
	}
	return true;
}

int main() {
	int n;
	fr(n);
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			state[i][j] = -1;
		}
	}
	cout << "Enter values for each column" << endl;
	for(int i=1; i<=n; ++i) {
		scanf(" %[^\n]", &inp[0]);
		pch	= strtok(&inp[0], " ");
		while(pch) {
			int temp = atoi(pch);
			col[i-1].push_back(temp);
			pch	= strtok(NULL, " ");
		}
	}
	cout << "Enter values for each row" << endl;
	for(int i=1; i<=n; ++i) {
		scanf(" %[^\n]", &inp[0]);
		pch	= strtok(&inp[0], " ");
		while(pch) {
			int temp = atoi(pch);
			row[i-1].push_back(temp);
			pch	= strtok(NULL, " ");
		}
	}
	while(!solved(n)) {
		vector<int> temp;
		for(int i=0; i<n; ++i) {
			for(int j=0; j<n; ++j) {
				temp.push_back(state[i][j]);
			}
			auto it = find (temp.begin(), temp.end(), -1);
			if (it != temp.end()) {
				apply(n, row[i], temp);
			}
			for(int j=0; j<n; ++j) {
				state[i][j] = temp[j];
			}
			temp.clear();
		}
		for(int j=0; j<n; ++j) {
			for(int i=0; i<n; ++i) {
				temp.push_back(state[i][j]);
			}
			auto it = find (temp.begin(), temp.end(), -1);
			if (it != temp.end()) {
				apply(n, col[j], temp);
			}
			for(int i=0; i<n; ++i) {
				state[i][j] = temp[i];
			}
			temp.clear();
		}
		// for(int i=0; i<n; ++i) {
		// 	for(int j=0; j<n; ++j) {
		// 		printf("%d", state[i][j]);
		// 	}
		// 	puts("");
		// }
	}
	cout<<"Found Answer:" << endl;
	for(int j=-2; j<n; ++j) {
		printf("\033[43m  \033[0m");
	}
	puts("");
	for(int i=0; i<n; ++i) {
		printf("\033[43m  \033[0m");
		for(int j=0; j<n; ++j) {
			printf("%s", (state[i][j]==0?"\033[47m  \033[0m":"  "));
		}
		printf("\033[43m  \033[0m");
		puts("");
	}
	for(int j=-2; j<n; ++j) {
		printf("\033[43m  \033[0m");
	}
	puts("\n");
	return 0;
}