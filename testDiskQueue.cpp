#include <cstdio>
#include <cstdlib>
#include <queue>
#include "globals.h"
using namespace std;

#define N 134217728

queue<int> Q;
disk_queue dQ(4);

int main()
{
    int x;
    for (int i = 0; i < N; i++)
    {
	x = rand() % (N << 2);
	Q.push(x);
	dQ.push(x);
    }

    int a, b;
    for (int i = 0; i < N; i++)
    {
	a = Q.front(); Q.pop();
	b = dQ.front(); dQ.pop();
	
	if (a != b)
	{
	    fprintf(stderr, "ERROR: %d %d\n", a, b);
	    exit(0);
	}

	if (i % 20 == 0)
	{
	    x = rand() % (N << 2);
	    Q.push(x);
	    dQ.push(x);
	}
    }

    fprintf(stderr, "Disk Queue correctly implemented.\n");

    return 0;
}
