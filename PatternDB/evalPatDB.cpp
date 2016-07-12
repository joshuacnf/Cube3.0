#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include "../globals.h"

#define DEPTH 20

uc buffer[M1024] = {0};
ull P[21], cnt = 0;
long double num[21][18], sum[21];

void initSum()
{
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
}

void loadDB(const char *file_name)
{
    FILE *in; ull file_size;

    in = fopen(file_name, "rb");
    fseek(in, 0, SEEK_END);
    file_size = ftell(in);

    fseek(in, 0, SEEK_SET);
    while (file_size)
    {
	ull block_size = min_(M1024, file_size);
	fread(buffer, block_size, 1, in);
	for (int i = 0; i < block_size; i++)
	{
	    P[buffer[i] & MASK4]++;
	    P[(buffer[i] >> 4) & MASK4]++;
	}
	cnt += block_size << 1;
	file_size -= block_size;
    }
    fclose(in);
}

void init()
{
    memset(P, 0, sizeof(P));
    memset(num, 0, sizeof(num));
    memset(sum, 0, sizeof(sum));

    initSum();
    loadDB("databaseC.in");
    loadDB("databaseS.in");
    
    for (int i = 1; i < 21; i++)
	P[i] += P[i - 1];
}

void work()
{
    printf("Distribution Table:\n");
    printf("Heuristic Value\t\tProbability\n");
    for (int i = 0; i < 21; i++)
	printf("%d\t\t%.4lf%%\n", i, P[i] / (double)cnt * 100.0);
    printf("\n");
    
    for (int d = 10; d <= DEPTH; d++)
    {
	ull nodes_cnt = 0;
	for (int i = 0; i <= d; i++)
	    nodes_cnt += sum[i] * (P[d - i] / (double)cnt);
	printf("Depth %d: %llu nodes\n", d, nodes_cnt);
    }
}

int main()
{
    init();
    work();
    printf("\n");
    return 0;
}
