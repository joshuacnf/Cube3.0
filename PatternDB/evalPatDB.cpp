#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "../cube.h"

#define MAX_CUTOFF 15

database DB; cube A;
double P[21];
ull num[21][18], sum[21];
ui cnt = 0; uc d = 0, cutoff = 0;

void init()
{
    memset(P, 0, sizeof(P));
    memset(num, 0, sizeof(num));
    memset(sum, 0, sizeof(sum));
    
    num[0][0] = 1;
    for (int i = 0; i < 18; i++)
	num[1][i] = 1;
    for (int d = 2; d < 21; d++)
    {
	for (int u = 0; u < 18; u++)
	    for (int v = 0; v < 18; v++)
		if (G[u][v])
		    num[d][v] += num[d - 1][u];
    }

    for (int d = 0; d < 21; d++)
	for (int i = 0; i < 18; i++)
	    sum[d] += num[d][i];
    
    uc x;
    FILE *in = fopen("database.in", "r");
    while (fscanf(in, "%hhu", &x) != EOF)
	P[x]++, cnt++;
    fclose(in);

    for (int i = 1; i < 21; i++)
	P[i] += P[i - 1];
    for (int i = 0; i < 21; i++)
	P[i] /= (double)cnt;
}

void scramble()
{
    for (int i = 0; i < 50; i++)
	A.turn(random() % 18);
}

void dfs(uc u)
{
    if (d > cutoff) return;

    if (DB.load(A.C) + d > cutoff)
    	return;
    
    cnt++;
    for (uc v = 0; v < 18; v++)
	if (G[u][v])
	{
	    ull S0 = A.S, C0 = A.C; 
	    d++; A.turn(v); dfs(v); d--; 
	    A.S = S0, A.C = C0;
	}
}

void work()
{
    cutoff = 8;
    while (cutoff <= MAX_CUTOFF)
    {
	double cnt_thm = 0;
	for (int d = 0; d <= cutoff; d++)
	    cnt_thm += sum[d] * P[cutoff - d];

	double cnt_exp = 0;
	for (int t = 0; t < 1000; t++) 
	{
	    cnt = 0;
	    scramble();
	    dfs(18);
	    cnt_exp += cnt;
	}
	cnt_exp /= 1000.0;

	double error = abs_(cnt_exp - cnt_thm) / cnt_thm * 100.0;
	printf("Depth: %hhu Theoretical: %llu Experimental: %llu Error: %.3lf%%\n", 
	       cutoff, (ull)cnt_thm, (ull)cnt_exp, error);

	cutoff++;
    }
}

int main()
{
    init();
    work();
    printf("\n");
    return 0;
}

#undef MAX_CUTOFF
