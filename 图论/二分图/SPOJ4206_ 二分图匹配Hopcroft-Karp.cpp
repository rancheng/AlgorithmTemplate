//SPOJ 4206 MATCHING ����ͼƥ�� Hopcroft-karp�㷨 O(E * V ^ 0.5)
/*
 | Hopcroft-Karp����������Ψһ���������������ÿ��ֻ��һ������·(������DFSʵ��),
 | ��Hopcroft-Karp������BFS�ҳ�����������·, Ȼ��ѡ�����е�һЩ��������.
 | ��Щ����·���ܻ��ص�, ���ǲ�Ҫ��, Hopcroft-Karp������������㷨�еĲ��ͼ����,
 | ��BFS��ʱ���ȸ�BFS��ÿ���еĿ��е���б��, ���ÿ��+1,
 | �ҳ���������·����ѡ���������DFS, ÿ�ΰ��ձ�ŵ�����˳���ҵ�һ������·,
 | ��Ű�1������֤������·��һ����BFS�е�һ����Ч·��,
 | ����ÿ�������Ժ�·���ϵĵ��ƥ�����, �Է�ֹ��һ��DFS��ʱ�������ظ��ĵ�,
 | ����һ��ÿ��BFS�Ժ��������ҵ�һ������·, �����õĻ�, ����һ����ȫͼ, ��ôֻҪһ��BFS�����ҳ����ƥ��.
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAXX = 50010;
const int MAXY = 50010;

int n, m, p;
vector<int> e[MAXX];
int matx[MAXX], maty[MAXY];
int dx[MAXX], dy[MAXY];

bool bfs() {
    bool foundAug = false;
    memset(dx, 0, sizeof(dx));
    memset(dy, 0, sizeof(dy));

    queue<int> q;
    for (int i = 1; i <= n; ++ i)
        if (matx[i] == -1)
            q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = 0; i < e[x].size(); ++ i) {
            int y = e[x][i];
            if (dy[y] == 0) {
                dy[y] = dx[x] + 1;
                if (maty[y] == -1) {
                    foundAug = true;
                } else {
                    dx[maty[y]] = dy[y] + 1;
                    q.push(maty[y]);
                }
            }
        }
    }
    return foundAug;
}

bool find(int x) {
    for (int i = 0; i < e[x].size(); ++ i) {
        int y = e[x][i];
        if (dy[y] == dx[x] + 1) {
            dy[y] = 0;
            if (maty[y] == -1 || find(maty[y])) {
                matx[x] = y;
                maty[y] = x;
                return true;
            }
        }
    }
    return false;
}

void hopcroftKarp() {
    memset(matx, 255, sizeof(matx));
    memset(maty, 255, sizeof(maty));
    int ans = 0;
    while (bfs()) {
        for (int i = 1; i <= n; ++ i)
            if (matx[i] == -1 && find(i))
                ans ++;
    }
    printf("%d\n", ans);
}

void init() {
    scanf("%d%d%d", &n, &m, &p);

    for (int i = 0; i <= n; ++ i)
        e[i].clear();
    while (p --) {
        int x, y;
        scanf("%d%d", &x, &y);
        e[x].push_back(y);
    }
}

int main() {
    init();
    hopcroftKarp();
    return 0;
}
