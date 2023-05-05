#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<bitset>
#include<algorithm>
#include<functional>
#include<deque>
#include<math.h>
using namespace std;
// typedef
typedef long long lli;
typedef unsigned long long ull;
// const variable
#define MAX_N 10005
#define MAX_M 1000
#define INF 2e9
#define NONE -1
#define MAX(x, y, z) {	return max(max(x,y),z);	}
#define MIN(x, y, z) {	return min(min(x,y),z);	}
#define LEFT 0
#define RIGHT 1
const double PI = 2.0 * acos(0.0);
// main
int T[MAX_N + 1];
int arrive[MAX_N + 1];
int main(){ // not AC yet
	int t;
	scanf("%d", &t);
	while (t--){
		queue< pair<int, int> > L, R;
		int n, m, t;
		scanf("%d%d%d", &n, &t, &m);
		for (int i = 1; i <= m; i++){
			char S[50];
			scanf("%d%s", T + i, S);
			if (S[0] == 'l')
				L.push(make_pair(T[i], i));
			else
				R.push(make_pair(T[i], i));
		}
		L.push(make_pair(INF, m + 1));
		R.push(make_pair(INF, m + 2));
		int time = 0, side = LEFT, load = 0;
		while (L.size() > 1 || R.size() > 1){
			load = 0;
			time = max(time, min(L.front().first, R.front().first));
			if (side == LEFT){
				while (!L.empty() && L.front().first <= time && load < n)
					load++, arrive[L.front().second] = time + t, L.pop();
				time += t, side = RIGHT;
			}
			else{
				while (!R.empty() && R.front().first <= time && load < n)
					load++, arrive[R.front().second] = time + t, R.pop();
				time += t, side = LEFT;
			}
		}
		while (!L.empty())	L.pop();
		while (!R.empty())	R.pop();
		for (int i = 1; i <= m; i++)
			printf("%d\n", arrive[i]);
		if (t)	putchar('\n');
	}
	return 0;
}
