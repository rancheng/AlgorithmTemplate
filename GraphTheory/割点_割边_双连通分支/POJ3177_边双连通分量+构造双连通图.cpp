//POJ 3177 ��˫��ͨ���� + ����˫��ͨ��ͼ
/* ����Ȼ������Ҫ���ͼ����һ����˫��ͨͼ��������ͨ�Ȳ�С��2��
 | �ҵķ�������ԭͼ��DFS������е��ţ�Ȼ��ɾ����Щ�űߣ�ʣ�µ�ÿ����ͨ�鶼��һ��˫��ͨ��ͼ��
 | ��ÿ��˫��ͨ��ͼ����Ϊһ�����㣬�ٰ��ű߼ӻ������������ͼһ����һ����������ͨ��Ϊ1��
 | ͳ�Ƴ����ж�Ϊ1�Ľڵ�ĸ�������ΪҶ�ڵ�ĸ�������Ϊleaf��
 | �������������(leaf+1)/2���ߣ�����ʹ���ﵽ�߶���ͨ�����Խ������(leaf+1)/2��
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
using namespace std;

const int MAXN = 5011;
const int MAXM = 20011;

int now[MAXN], dfn[MAXN], low[MAXN], d[MAXN], color[MAXN];
int pre[MAXM], son[MAXM], vis[MAXM];

stack<int> st;

int n, edgeCnt, dfnCnt, ebccCnt;

void addEdge(int u, int v)
{
    vis[edgeCnt] = 0;
    pre[edgeCnt] = now[u]; son[edgeCnt] = v; now[u] = edgeCnt ++;
}

void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++ dfnCnt;
    st.push(u);
    for (int p = now[u]; p != -1; p = pre[p])
    {
        if (vis[p]) continue;
        vis[p] = vis[p ^ 1] = true;

        int v = son[p];
        if (!dfn[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
        else
            low[u] = min(low[u], dfn[v]);

    }

    if (dfn[u] == low[u])
    {
        ++ ebccCnt;
        while (st.top() != u)
        {
            color[st.top()] = ebccCnt;
            st.pop();
        }
        color[u] = ebccCnt;
        st.pop();
    }
}

void init()
{
    edgeCnt = dfnCnt = ebccCnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(now, 255, sizeof(now));
    memset(color, 255, sizeof(color));

    int m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
}

void solve()
{
    dfs(1, 0);

    memset(d, 0, sizeof(d));
    for (int i = 1; i <= n; ++ i)
    {
        for (int p = now[i]; p != -1; p = pre[p])
            if (color[i] != color[son[p]])
                d[color[i]] ++;
    }

    int leafCnt = 0;
    for (int i = 1; i <= ebccCnt; ++ i)
        if (d[i] == 1)
            leafCnt ++;
    printf("%d\n", (leafCnt + 1) / 2);
}

int main()
{
    init();
    solve();
    return 0;
}
