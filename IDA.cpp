#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "cube.h"

#define MAXTURN 50

cube A;
databaseS DBS; databaseC DBC;

ui nodes_cnt;
uc cutoff, d;
uc seq[MAXTURN] = {0}, ans[MAXTURN] = {0}, len;
double time_cnt;

ui avg_len = 0;
double avg_time = 0;
ull avg_nodes = 0;

void scramble()
{
    uc u = 18, v;
    for (int i = 0; i < MAXTURN; i++)
    {
	do{
	    v = (random() % 10007) % 18;
	}while(!G[u][v]);
	seq[i] = v; A.turn(v);
	u = v;
    }

    printf("Scramble Sequence: %d turns\n", MAXTURN);
    for (int i = 0; i < MAXTURN; i++)
    {
    	printf("%s ", turnName[seq[i]].c_str());
	if (i % 25 == 0 && i) printf("\n");
    }
    printf("\n");
}

bool dfs(uc u)
{
    nodes_cnt++;
    if (A.solved()) { len = d; return true; }

    if (cutoff - d >= 10)
    {
	if (DBS.load1(A.S) + d > cutoff) return false;
	if (DBS.load2(A.S) + d > cutoff) return false;
	if (DBC.load(A.C) + d > cutoff) return false;
    }
    else
    {
	if (DBC.load(A.C) + d > cutoff) return false;
	if (DBS.load1(A.S) + d > cutoff) return false;
	if (DBS.load2(A.S) + d > cutoff) return false;
    }

    for (uc v = 0; v < 18; v++)
	if (G[u][v])
	{
	    ull S0 = A.S, C0 = A.C; d++; 
	    A.turn(v); bool solved = dfs(v); 
	    A.S = S0, A.C = C0; d--;

	    if (solved)
	    {
		ans[d] = v;
		return true;
	    }
	}

    return false;
}

void IDA()
{
    printf("\nSearching...\n");
    
    clock_t s = clock();
    d = 0, nodes_cnt = 0, cutoff = 0;
    while (!dfs(18))
	cutoff++;
    time_cnt = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
    
    printf("Time: %.2lf seconds\n", time_cnt);
    printf("Nodes generated: %u (%u nodes/second)\n", nodes_cnt, (int)(nodes_cnt / time_cnt));
    printf("\n");
}

void check()
{
    for (int i = 0; i < len; i++)
	A.turn(ans[i]);
    
    if (A.solved())
    {
	printf("Optimal Solution: %d turns\n", len);
	for (int i = 0; i < len; i++)
	    printf("%s ", turnName[ans[i]].c_str());
	printf("\n");
    }
    else printf("Cube not solved.\n");
    printf("\n");
}

void statistics(int T)
{
    avg_len += len;
    avg_time += time_cnt;
    avg_nodes += nodes_cnt;

    printf("Average time: %.2lf seconds\n", avg_time / (double)T);
    printf("Average nodes generated: %llu\n", avg_nodes / T);
    printf("Average solution length: %.1lf\n", avg_len / (double)T);
}

int main()
{
    srand(time(0));
    for (int T = 1; T <= 50; T++)
    {
	printf("Trial #%d:\n", T);
	
	scramble();
	IDA();
	check();
	statistics(T);

	printf("\n============================================================\n");
    }
    printf("\n");
    return 0;
}

#undef MAXTURN
