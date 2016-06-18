#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "cube.h"

#define MAXTURN 14

database DB; cube A;
uc ans[MAXTURN] = {0}, len = 0;
uc d = 0, cutoff = 0, cutoff_ = 0;
ui cnt = 0;

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

    uc cost = DB.load(A.C) + d;
    if (cost > cutoff)
    {
	cutoff_ = cutoff_ > cost? cost: cutoff_;
	return false;
    }

    for (uc v = 0; v < 18; v++)
	if (G[u][v])
	{
	    ull S0 = A.S, C0 = A.C; d++; 
	    A.turn(v); bool solved = dfs(v); 
	    A.S = S0, A.C = C0, d--;

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
    do
    {
	cutoff = cutoff_;
	cutoff_ = 21;
    }while (!dfs(18));
    double t = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
    
    printf("Time: %lf\n", t);
    printf("Nodes generated: %d (%d nodes/second)\n", cnt, (int)(cnt / t));
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
