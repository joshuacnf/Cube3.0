#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <string>
#include "omp.h"
#include "cube.h"
using namespace std;

#define MAXTURN 15
#define BFS_DEPTH 3
#define STATE_NUM 5832

databaseC DBC;
databaseS DBS;
//databaseCS DBCS;

struct hashCube
{
    ull operator()(const cube &B) const
    {
	return B.S % 10000007ULL;
    }
};
queue<uc> dQ, uQ;
queue<cube> cubeQ;
unordered_map<cube, string, hashCube> path;

bool solved;
cube I[STATE_NUM]; ui state_num;
char seq[MAXTURN] = {0}, ans[STATE_NUM][20];
ull nodes_cnt; ui cutoff, ans_no, ans_len;
double time_cnt;

ui avg_len = 0;
double avg_time = 0;
ull avg_nodes = 0;

void scramble(cube &A)
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
	if (i % 20 == 0 && i) printf("\n");
	printf("%s ", turnName[seq[i]].c_str());
    }
    printf("\n");
    
    solved = false;
}

void bfs(cube A)
{
    path.clear();
    
    path[A] = "";
    cubeQ.push(A); dQ.push(0); uQ.push(18);
    
    uc d, u;
    while (1)
    {
	if ((d = dQ.front()) == BFS_DEPTH) 
	    break;
	A = cubeQ.front(); u = uQ.front();
	cubeQ.pop(); dQ.pop(); uQ.pop();
	
	ull C0, S0;
	for (uc v = 0; v < 18; v++)
	    if (G[u][v])
	    {
		cube A0 = A; A.turn(v);
		if (path.find(A) == path.end())
		{
		    path[A] = (path[A0] + (char)(v));
		    cubeQ.push(A); dQ.push(d + 1); uQ.push(v);
		}
		A = A0;
	    }
    }
    
    state_num = 0;
    while (!cubeQ.empty())
    {
	I[state_num] = cubeQ.front();
	for (int i = 0; i < BFS_DEPTH; i++)
	    ans[state_num][i] = path[cubeQ.front()][i];
	cubeQ.pop(); dQ.pop(); uQ.pop();
	state_num++;
    }
}

bool dfs(const ui no, const cube &A, uc u, uc d, ull &cnt)
{
    cnt = 1;
    if (A.solved())
    {
	ans[no][BFS_DEPTH + d] = -1;
	return true;
    }
    
    if (DBC.load(A.C) + d > cutoff) return false;
    if (DBS.load1(A.S) + d > cutoff) return false;
    if (DBS.load2(A.S) + d > cutoff) return false;
    //if (DBCS.load(A.C, A.S) + d > cutoff) return false;
    
    for (uc v = 0; v < 18; v++)
	if (G[u][v])
	{
	    cube A0 = A; A0.turn(v); ull cnt0;
	    bool res = dfs(no, A0, v, d + 1, cnt0);
	    cnt += cnt0;

	    if (res)
	    {
	        ans[no][BFS_DEPTH + d] = v;
		return true;
	    }
	}
    
    return false;
}

void IDA_omp()
{
    printf("\nSearching...\n");
    
    clock_t s = clock();
    ans_no = 0, ans_len = 0;
    nodes_cnt = 0, cutoff = 0;
    while (!solved)
    {
#pragma omp parallel for reduction (+:nodes_cnt)
	for (int i = 0; i < state_num; i++)
	{
	    if (solved) continue;
	    ull cnt = 0;
	    if (dfs(i, I[i], ans[i][BFS_DEPTH - 1], 0, cnt))
		solved = true, ans_no = i;
	    nodes_cnt += cnt;
	}
	cutoff++;
    }
    time_cnt = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
    
    printf("Time: %.2lf seconds\n", time_cnt);
    printf("Nodes generated: %llu (%llu nodes/second)\n", nodes_cnt, (ull)(nodes_cnt / time_cnt));
    printf("\n");
}

void check(cube A)
{
#define ans ans[ans_no]
    
    for (ans_len = 0; ans[ans_len] != -1; ans_len++);
    for (int i = 0; i < ans_len; i++)
	A.turn(ans[i]);
    
    if (A.solved())
    {
	printf("Optimal Solution: %d turns\n", ans_len);
	for (int i = 0; i < ans_len; i++)
	    printf("%s ", turnName[ans[i]].c_str());
	printf("\n");
    }
    else printf("Cube not solved.\n");
    printf("\n");

#undef ans
}

void statistics(int T)
{
    avg_len += ans_len;
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

	cube A;
	scramble(A);
	bfs(A);
	IDA_omp();
	check(A);
	statistics(T);

	printf("\n==================================================================\n");
    }
    printf("\n");
    return 0;
}

#undef MAXTURN
