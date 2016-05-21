#include <cstdio>
#include <string>
#include "utilities.h"
using namespace std;

ull sM0[18][32] = {0};
ull cM0[18][32] = {0};

ull sM[18][1048576] = {0};
ull cM[18][1048576] = {0};

string mapName[] =
{ "F", "B", "U", "D", "L", "R", "F_", "B_", "U_", "D_", "L_", "R_", "FF", "BB", "UU", "DD", "LL", "RR" };

cube A;

void updateTable()
{
    ull S0, C0;
    for (uc u = 0; u < 18; u++)
    {
        S0 = A.S, C0 = A.C;
        turnCube(&A, u);
        
        for (int i = 0; i < 12; i++, S0 >>= 5)
        {
            uc s1 = S0 & MASK5, s2 = 0, j;
            for (j = 0; j < 12; j++)
            {
                s2 = (A.S >> (j * 5)) & MASK5;
                if (s1 % 12 == s2 % 12)
                    break;
            }
            s1 = (s1 / 12) * 12 + i, s2 = (s2 / 12) * 12 + j;
            sM0[u][s1] = s2;
        }
        
        for (int i = 0; i < 8; i++, C0 >>= 5)
        {
            uc c1 = C0 & MASK5, c2 = 0, j;
            for (j = 0; j < 8; j++)
            {
                c2 = (A.C >> (j * 5)) & MASK5;
                if (c1 % 8 == c2 % 8)
                    break;
            }
            c1 = (c1 / 8) * 8 + i, c2 = (c2 / 8) * 8 + j;
            cM0[u][c1] = c2;
        }
        
        turnCube(&A, revTurn[u]);
    }
}

void dfs(uc d, uc u)
{
    if (d > 5) return;
    
    updateTable();
    
    ull S0, C0;
    for (uc v = 0; v < 18; v++)
    {
        if (!G[u][v]) continue;
        
        S0 = A.S, C0 = A.C;
        turnCube(&A, v); dfs(d + 1, v);
        A.S = S0, A.C = C0;
    }
}

void work()
{
    for (int t = 0; t < 18; t++)
        for (ull i = 0; i < 24; i++)
            for (ull j = 0; j < 24; j++)
	    {
		sM[t][i | (j << 5)] = sM0[t][i] | (sM0[t][j] << 5);
		cM[t][i | (j << 5)] = cM0[t][i] | (cM0[t][j] << 5);
	    }
}

void print()
{
    int m = 760;
    printf("%d\n", m);
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < m; j++)
            printf("%llu ", sM[i][j]);
    
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < m; j++)
            printf("%llu ", cM[i][j]);
}

int main()
{
    freopen("map.in", "w", stdout);
    dfs(0, 18);
    work();
    print();
    return 0;
}
