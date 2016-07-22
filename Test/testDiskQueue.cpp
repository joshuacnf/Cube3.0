#include <cstdio>
#include <cstdlib>
#include <queue>
#include "../globals.h"
using namespace std;

#define N M1024

queue<us> Q;
disk_queue dQ(2);

int main()
{
    ull x, a, b;
    
    for (int i = 0; i < N; i++)
    {
	x = rand() % (1ULL << 30);
	Q.push((us)x);
	dQ.push(x);
    }

    for (int i = 0; i < N; i++)
    {
	a = Q.front(); Q.pop();
	b = dQ.front(); dQ.pop();
	
	if ((us)a != (us)b)
	{
	    fprintf(stderr, "%d ERROR: %u %u\n", i, (us)a, (us)b);
	    return 0;
	}

	if (i % 20 == 0)
	{
	    x = rand() % (N << 2);
	    Q.push(x);
	    dQ.push(x);
	}
    }

    while (!Q.empty()) Q.pop();
    while (!dQ.empty()) dQ.pop();

    for (int i = 0; i < N; i++)
    {
	x = rand() % (1ULL << 30);
	Q.push((us)x);
	dQ.push(x);
    }

    for (int i = 0; i < N; i++)
    {
	a = Q.front(); Q.pop();
	b = dQ.front(); dQ.pop();
	
	if ((us)a != (us)b)
	{
	    fprintf(stderr, "ERROR: %u %u\n", (us)a, (us)b);
	    return 0;
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
