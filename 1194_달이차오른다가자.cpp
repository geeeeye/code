#include<iostream>
#include<queue>
#define MAX 50
#define MAX_KEY 64
using namespace std;

int n, m;
char map[MAX + 1][MAX + 1];
int visit[MAX + 1][MAX + 1][MAX_KEY + 1];
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int sy, sx, ey, ex;
struct info {
	int y;
	int x;
	int w;
	int key;
};

bool isKey(char ch) {
	if (ch >= 'a' && ch <= 'z') return true;
	else return false;
}

bool isGate(char ch) {
	if (ch >= 'A' && ch <= 'Z') return true;
	else return false;
}
int solve() {
	queue<struct info> q;
	q.push({ sy,sx,0,0 });
	visit[sy][sx][0] = 1;

	while(!q.empty()){
		int cy = q.front().y;
		int cx = q.front().x;
		int cw = q.front().w;
		int ck = q.front().key;
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			int nk = ck;
			if (ny < 0 || ny >= n || nx < 0 || nx >= m ||map[ny][nx]=='#'|| visit[ny][nx][ck] == 1)continue;
			if (isKey(map[ny][nx])) { //key get
				nk |= (1 <<( map[ny][nx] - 'a'));
				q.push({ ny, nx, cw + 1, nk });
				visit[ny][nx][nk] = 1;
			}
			else if (isGate(map[ny][nx])) {
				char needkey = map[ny][nx] + ('a' - 'A');
				int needkeytmp = needkey - 'a';
				if ((nk & (1 << needkeytmp)) != 0) {
					//해당 열쇠 있다면
					q.push({ ny,nx,cw + 1, nk });
					visit[ny][nx][nk] = 1;
				}
			}
			else if (map[ny][nx] == '.' ) {
				visit[ny][nx][nk] = 1;
				q.push({ ny, nx, cw + 1, nk });
			}
			else if (map[ny][nx] == '1') return cw+1;
		}
	
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> map[i];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] == '0') {
				sy = i; sx = j;
				map[i][j] = '.';
			}
			else if (map[i][j] == '1') {
				ey = i; ex = j;
			}
		}
	}
	cout << solve();

}