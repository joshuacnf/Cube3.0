#include <cstdio>
#include <cstdlib>
#include <queue>
#include "../globals.h"
using namespace std;

#define N 10003333

queue<ull> Q;
disk_queue dQ(5, 233333);

int main()
{
    ull x, a, b;
    
    for (int i = 0; i < N; i++)
    {
	x = (ull)rand() * (ull)rand();
	Q.push(x);
	dQ.push(x);
    }

    for (int i = 0; i < N; i++)
    {
	a = Q.front(); Q.pop();
	b = dQ.front(); dQ.pop();
	
	if ((a & MASK32) != (b & MASK32))
	{
	    fprintf(stderr, "%d ERROR: %llu %llu\n", i, a & MASK32, b & MASK32);
	    return 0;
	}

	if (i % 5 == 0)
	{
	    x = (ull)rand() * (ull)rand();
	    Q.push(x);
	    dQ.push(x);
	}
    }
    
    while (!Q.empty()) Q.pop();
    while (!dQ.empty()) dQ.pop();
    
    for (int i = 0; i < N; i++)
    {
	x = (ull)rand() * (ull)rand();
	Q.push(x);
	dQ.push(x);
    }

    for (int i = 0; i < N; i++)
    {
	a = Q.front(); Q.pop();
	b = dQ.front(); dQ.pop();
	
	if ((a & MASK32) != (b & MASK32))
	{
	    fprintf(stderr, "%d ERROR: %llu %llu\n", i, a & MASK32, b & MASK32);
	    return 0;
	}
	
	if (i % 5 == 0)
	{
	    x = (ull)rand() * (ull)rand();
	    Q.push(x);
	    dQ.push(x);
	}
    }

    fprintf(stderr, "Disk Queue correctly implemented.\n");

    return 0;
}
