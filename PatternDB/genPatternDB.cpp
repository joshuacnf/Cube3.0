#include <cstdio>
#include <cstring>
#include <ctime>
#include <queue>
#include "../cube.h"
using namespace std;

#define N 40320 //8!
#define M 2187 //3^7

struct database_
{
    database_(): cnt(0)
    { 
	memset(T, 0, sizeof(T));

	fac[0] = 1;
	for (int i = 1; i < 10; i++)
	    fac[i] = fac[i - 1] * i;

	pow3[0] = 1;
	for (int i = 1; i < 10; i++)
	    pow3[i] = pow3[i - 1] * 3;
    }

    inline ui size()
    {
	return cnt;
    }

    inline void store(ull k, uc v)
    {
	cnt++;
	trans(k);
	int idx = index();
	T[cantor()][idx >> 1] |= v << ((idx & 1) << 2);
    }

    inline uc load(ull k)
    {
	trans(k);
	int idx = index();
	return (T[cantor()][idx >> 1] >> ((idx & 1) << 2)) & MASK4;
    }
    
    void write()
    {
	FILE *out = fopen("database.in", "w");
	for (int i = 0; i < N; i++)
	    for (int j = 0; j < M; j++)
		fprintf(out, "%hhu ", T[i][j]);
	fclose(out);
    }
    
private:
    uc T[N][M]; ui cnt;
    ui fac[10], pow3[10]; uc tmp[10];
    
    inline void trans(ull k)
    {
	tmp[0] = k & MASK5;
	tmp[1] = (k >> 5) & MASK5;
	tmp[2] = (k >> 10) & MASK5;
	tmp[3] = (k >> 15) & MASK5;
	tmp[4] = (k >> 20) & MASK5;
	tmp[5] = (k >> 25) & MASK5;
	tmp[6] = (k >> 30) & MASK5;
	tmp[7] = (k >> 35) & MASK5;
    }
    
    inline ui cantor()
    {
	ui idx = 0;
	for (uc i = 0; i < 7; i++)
	{
	    uc t = 0;
	    for (uc j = i + 1; j < 8; j++)
		t += (tmp[j] & 7) < (tmp[i] & 7);
	    idx += t * fac[7 - i];
	}
	return idx;
    }

    inline ui index()
    {
	ui idx = 0;
	for (uc i = 0; i < 7; i++)
	    idx += pow3[i] * (tmp[i] >> 3);
	return idx;
    }
};

database_ DB_;
queue<ull> CQ;
queue<uc> uQ, dQ;

clock_t st = 0;

inline ull turnC(ull C, uc u)
{
    ull C0 = 0;
    for (uc i = 0; i < 40; i += 10)
    	C0 |= ((ull)cM[u][(C >> i) & MASK10]) << i;
    return C0;
}

inline void updateStatus()
{
    if ((clock() - st) / (CLOCKS_PER_SEC * 1.0) <= 3) 
	return;
    st = clock();
    printf("Progress: %.2lf%%\n", DB_.size() / (double)881798.4);
}

void bfs()
{
    cube A;
    CQ.push(A.C); uQ.push(18); dQ.push(0);

    ull C0; uc u, d;
    while(!CQ.empty())
    {
	C0 = CQ.front(), u = uQ.front(), d = dQ.front();
	CQ.pop(); uQ.pop(); dQ.pop();
	for (uc v = 0; v < 18; v++)
	    if(G[u][v])
	    {
		ull C = turnC(C0, v);
		if (!DB_.load(C))
		{
		    DB_.store(C, d + 1);
		    CQ.push(C); uQ.push(v); dQ.push(d + 1);
		}
	    }
	updateStatus();
    }
    
    DB_.store(A.C, 0);
}

int main()
{
    printf("Genrating Pattern Database...\n")
    bfs();
    DB_.write();
    printf("Total Positions: %d\n", DB_.size());
    return 0;
}
