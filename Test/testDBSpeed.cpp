#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "../cube.h"

#define N 100000007

cube A;
databaseS DBS;
databaseC DBC;

ui cnt;
FILE *out;
uc seq[N] = {0};

void scramble(cube &C)
{
    uc u = 18, v;
    for (int i = 0; i < 1; i++)
    {
	
	C.turn(v); u = v;
    }
}

void init()
{
    srand(time(0));
    
    uc u = 18, v;
    for (int i = 0; i < N; i++)
    {
	do{
	    v = (random() % 10007) % 18;
	}while(!G[u][v]);
	seq[i] = v; u = v;
    }
    
    out = fopen("/usr/tmp", "w");
}

void testDBC()
{
    cnt = 0;
    clock_t s = 0;
    for (int i = 0; i < N; i++)
    {
	A.turn(seq[i]);
	cnt += DBC.load(A.C);
    }
    double t = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
    printf("databaseC: %u loads / second (time: %lf seconds)\n",
	   (ui)(N / t), t);
    fprintf(out, "%d\n", cnt);
}

void testDBS()
{
    cnt = 0;
    clock_t s = 0;
    for (int i = 0; i < N; i++)
    {
	A.turn(seq[i]);
	cnt += DBS.load1(A.S);
    }
    double t = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
    printf("databaseS: %u loads / second (time: %lf seconds)\n",
	   (ui)(N / t), t);
    fprintf(out, "%d\n", cnt);
}

void testDBCS()
{
    cnt = 0;
    clock_t s = 0;
    for (int i = 0; i < N; i++)
    {
	A.turn(seq[i]);
	cnt += DBC.load(A.C);
	cnt += DBS.load1(A.S);
	cnt += DBS.load2(A.S);
    }
	    
    double t = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
    printf("database C&S: %u loads / second (time: %lf seconds)\n",
	   (ui)(N / t), t);
    fprintf(out, "%d\n", cnt);
}

int main()
{
    init();

    testDBC();
    testDBS();
    testDBCS();

    printf("\n");
    fclose(out);
    return 0;
}
