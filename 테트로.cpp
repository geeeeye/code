#include<iostream>

using namespace std;

int n, m;
int map[501][501];
int visit[501][501];
int dy[3] = { 0,1,0 };
int dx[3] = { 1,0,-1 };
int maxnum = -1;
int max(int a, int b) {
	if (a > b) return a;
	else return b;
}
void func(int d, int y, int x, int check, int sum) {

	if (d == 4) {
		maxnum = max(maxnum, sum);
		return;
	}

	for (int i = 0; i < 3; ++i) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
		if (d != 3) {
			if (visit[ny][nx] == 1) continue;
		}
		if (d == 3 && check == 0 && visit[ny][nx] == 1) { // 다시돌아갈수있음
			func(d, ny, nx, 1, sum);
		}
		if (visit[ny][nx] == 1) continue;
		visit[ny][nx] = 1;
		func(d + 1, ny, nx, 0, sum + map[ny][nx]);
		visit[ny][nx] = 0;
	}

}
int main() {

	while (1) {
		cin >> n; m = n;
		maxnum = -2e9;
		if (n == 0) break;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> map[i][j];
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				visit[i][j] = 1;
				func(1, i, j, 0, map[i][j]);
				//if (maxnum == 20) cout << i << j;
				visit[i][j] = 0;
			}
		}
		cout << maxnum<<endl;
	}
}