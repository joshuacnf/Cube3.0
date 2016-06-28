#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "cube.h"

#define MAXTURN 15

cube A;
databaseS DBS; databaseC DBC;
ui cnt; uc cutoff = 0, d = 0;
uc ans[MAXTURN] = {0}, len = 0;

void init()
{
    printf("Scramble Sequence:\n");
    for (int i = 0; i < MAXTURN; i++)
    {
	int k = random() % 18;
	A.turn(k);
	printf("%s ", turnName[k].c_str());
    }
    printf("\n");
}

bool dfs(uc u)
{
    cnt++;
    if (A.solved()) return true;
    
    if (DBC.load(A.C) + d > cutoff) return false;
    if (DBS.load1(A.S) + d > cutoff) return false;
    if (DBS.load2(A.S) + d > cutoff) return false;

    for (uc v = 0; v < 18; v++)
	if (G[u][v])
	{
	    ull S0 = A.S, C0 = A.C; d++; 
	    A.turn(v); bool solved = dfs(v); 
	    A.S = S0, A.C = C0; d--;

	    if (solved)
	    {
		ans[d] = v;
		len = len == 0? d + 1: len;
		return true;
	    }
	}

    return false;
}

void IDA()
{
    printf("\nSearching...\n");
    
    clock_t s = clock();
    cnt = 0; cutoff = 0;
    while (!dfs(18))
	cutoff++;
    double t = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
    
    printf("Time: %lf\n", t);
    printf("Nodes generated: %u (%u nodes/second)\n", cnt, (int)(cnt / t));
}

void check()
{
    for (int i = 0; i < len; i++)
	A.turn(ans[i]);
    
    if (A.solved())
    {
	printf("Optimal Solution:\n");
	for (int i = 0; i < len; i++)
	    printf("%s ", turnName[ans[i]].c_str());
	printf("\n");
    }
    else printf("Cube not solved.\n");
}

int main()
{
    init();
    IDA();
    check();
    printf("\n");
    return 0;
}

#undef MAXTURN
