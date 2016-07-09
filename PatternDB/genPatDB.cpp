#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <queue>
#include "../cube.h"
using namespace std;

#define N 40320 //8!
#define M 2187 //3^7

struct databaseC_
{
    databaseC_(): cnt(0)
    { 
	memset(T, 0, sizeof(T));
    }

    inline ui size()
    {
	return cnt;
    }

    inline void store(ull k, uc v)
    {
	cnt++;
	ui idx = index(k);
        T[cantor(k)][idx >> 1] |= v << ((idx & 1) << 2);
    }

    inline uc load(ull k)
    {
	ui idx = index(k);
	return (T[cantor(k)][idx >> 1] >> ((idx & 1) << 2)) & MASK4;
    }
    
    void write()
    {
        T[0][0] &= ~MASK4;
	FILE *out = fopen("databaseC.in", "w");
	for (int i = 0; i < N; i++)
	    for (int j = 0; j < (M >> 1); j++)
		fprintf(out, "%hhu ", T[i][j]);
	fclose(out);
    }
    
private:
    uc T[N][M]; ui cnt;
        
    inline ui cantor(ull k)
    {
	ui idx = 0;
	uc t0, t1, t2, t3;
	
	t0 = k & 7; t1 = (k >>= 5) & 7; t2 = (k >>= 5) & 7; t3 = (k >>= 5) & 7;
		
	idx += t0 * 5040;
	idx += (t1 - (t0 < t1)) * 720;
	idx += (t2 - (t0 < t2) - (t1 < t2)) * 120;
	idx += (t3 - (t0 < t3) - (t1 < t3) - (t2 < t3)) * 24;
	
	t0 = (k >>= 5) & 7; t1 = (k >>= 5) & 7; t2 = (k >>= 5) & 7; t3 = (k >>= 5) & 7;
	
	idx += ((t0 > t1) + (t0 > t2) + (t0 > t3)) * 6;
	idx += ((t1 > t2) + (t1 > t3)) * 2;
	idx += (t2 > t3);
	
	return idx;
    }

    inline ui index(ull k)
    {
	ui idx = 0;

	idx += (k >>= 3) & 3;
	idx += ((k >>= 5) & 3) * 3;
	idx += ((k >>= 5) & 3) * 9;
	idx += ((k >>= 5) & 3) * 27;
	idx += ((k >>= 5) & 3) * 81;
	idx += ((k >>= 5) & 3) * 243;
	idx += ((k >>= 5) & 3) * 729;
	
	return idx;
    }
};

#undef N
#undef M


#define N 665280 //(12!)/(6!)
#define M 64 //2^6

struct databaseS_
{
    databaseS_(): cnt(0)
    {
	memset(T1, 0, sizeof(T1));
	memset(T2, 0, sizeof(T2));
	memset(com, 0, sizeof(com));	

	for (int i = 0; i < 6; i++)
	    for (int j = 0; j < 11; j++)
		com[i][j] = combination(11 - j, 5 - i);
    }

    inline ui size() const
    {
	return cnt;
    }

    inline void store1(ull k, uc v)
    {
	cnt++;
	ui idx1, idx2;
	trans(k); index(idx1, idx2);
	T1[idx1][idx2 >> 1] |= v << ((idx2 & 1) << 2);
    }
    
    inline void store2(ull k, uc v)
    {
	cnt++;
	ui idx1, idx2;	
	trans(k >> 30); index(idx1, idx2);
	T2[idx1][idx2 >> 1] |= v << ((idx2 & 1) << 2);
    }

    inline bool load1(ull k)
    {
	ui idx1, idx2;
	trans(k); index(idx1, idx2);
	return (T1[idx1][idx2 >> 1] >> ((idx2 & 1) << 2)) & MASK4;
    }
    
    inline bool load2(ull k)
    {
	ui idx1, idx2;
	trans(k >> 30); index(idx1, idx2);
	return (T2[idx1][idx2 >> 1] >> ((idx2 & 1) << 2)) & MASK4;
    }
    
    void write()
    {
	T1[0][0] &= ~MASK4; T2[0][0] &= ~MASK4;
	FILE *out = fopen("databaseS.in", "w");
	
	for (int i = 0; i < N; i++)
	    for (int j = 0; j < (M >> 1); j++)
		fprintf(out, "%hhu ", T1[i][j]);

	for (int i = 0; i < N; i++)
	    for (int j = 0; j < (M >> 1); j++)
		fprintf(out, "%hhu ", T2[i][j]);
	
	fclose(out);
    }
    
private:
    uc T1[N][M >> 1], T2[N][M >> 1]; ui cnt;
    uc tmp[6]; bool s[12]; ui com[6][12]; //com: some numbers of combinations    
    
    inline void trans(ull k)
    {
	tmp[0] = k & MASK5;
	tmp[1] = (k >> 5) & MASK5;
	tmp[2] = (k >> 10) & MASK5;
	tmp[3] = (k >> 15) & MASK5;
	tmp[4] = (k >> 20) & MASK5;
	tmp[5] = (k >> 25) & MASK5;
    }
    
    inline void index(ui &idx1, ui &idx2)
    {
	memset(s, 0, 12);
	idx1 = idx2 = 0;
	
	for (int i = 0; i < 6; i++)
	{
	    idx2 += ((tmp[i] / 12) & 1) << i;
	    tmp[i] %= 12, s[tmp[i]] = true;
	}
	
	idx1 += ((tmp[0] > tmp[1]) + (tmp[0] > tmp[2]) + (tmp[0] > tmp[3]) +
		 (tmp[0] > tmp[4]) + (tmp[0] > tmp[5])) * 120;
	idx1 += ((tmp[1] > tmp[2]) + (tmp[1] > tmp[3]) + (tmp[1] > tmp[4]) +
		 (tmp[1] > tmp[5])) * 24;
	idx1 += ((tmp[2] > tmp[3]) + (tmp[2] > tmp[4]) + (tmp[2] > tmp[5])) * 6;
	idx1 += ((tmp[3] > tmp[4]) + (tmp[3] > tmp[5])) * 2;
	idx1 += tmp[4] > tmp[5];
	
	ui t = 0; uc i, j;
	for (i = j = 0; i < 6; j++)
	    if (!s[j]) t += com[i][j];
	    else i++;
	
	idx1 += t * 720; //6!
    }
};

#undef N
#undef M

databaseC_ DBC_;
databaseS_ DBS_;
//queue<ull> Q;
//queue<uc> uQ, dQ;
disk_queue Q(8);
disk_queue uQ(1), dQ(1);

clock_t st = 0;
uc maxd = 0;

inline void turnC(ull &C, uc u)
{
    ull C0 = 0;
    for (int i = 0; i < 40; i += 10)
	C0 |= ((ull)cM[u][(C >> i) & MASK10]) << i;
    C = C0;
}

inline void turnS(ull &S, uc u)
{
    ull S0 = 0;
    for (int i = 0; i < 60; i += 10)
	S0 |= ((ull)sM[u][(S >> i) & MASK10]) << i;
    S = S0;
}

inline void updateStatusC()
{
    if ((clock() - st) / (CLOCKS_PER_SEC * 1.0) <= 3) 
	return;
    st = clock();
    printf("Corner Database: %.2lf%%\n", DBC_.size() / (double)881798.4);
}

inline void updateStatusS()
{
    if ((clock() - st) / (CLOCKS_PER_SEC * 1.0) <= 3) 
	return;
    st = clock();
    printf("Side Database: %.2lf%%\n", DBS_.size() / (double)851558.4);
}

void bfsC()
{
    printf("Genrating Pattern Database for corner cubies...\n");
    st = 0; maxd = 0;
    
    cube A;
    Q.push(A.C); uQ.push(18); dQ.push(0);
    DBC_.store(A.C, 0);

    ull C; uc u, d;
    while(!Q.empty())
    {
	C = Q.front(), u = uQ.front(), d = dQ.front();
	Q.pop(); uQ.pop(); dQ.pop();

	for (uc v = 0; v < 18; v++)
	    if(G[u][v])
	    {
		ull C0 = C;
		turnC(C, v);
		if (!DBC_.load(C))
		{
		    DBC_.store(C, d + 1);
		    maxd = max_(maxd, (uc)(d + 1));
		    Q.push(C); uQ.push(v); dQ.push(d + 1);
		}
		C = C0;
	    }
	
	updateStatusC();
    }

    printf("Total Positions of 8 corner cubies: %d\n", DBC_.size());
    printf("Max Heuristic Value: %d\n", maxd);
}

void bfsS()
{
    printf("Genrating Pattern Database for side cubies...\n");
    cube A; st = 0; maxd = 0;
    ull S, S0; uc u, d;
    
    Q.push(A.S); uQ.push(18); dQ.push(0);
    DBS_.store1(A.S, 0);

    while(!Q.empty())
    {
	S = Q.front(), u = uQ.front(), d = dQ.front();
	Q.pop(); uQ.pop(); dQ.pop();

	for (uc v = 0; v < 18; v++)
	    if(G[u][v])
	    {
		S0 = S; turnS(S, v);
		if (!DBS_.load1(S))
		{
		    DBS_.store1(S, d + 1);
		    maxd = max_(maxd, (uc)(d + 1));
		    Q.push(S); uQ.push(v); dQ.push(d + 1);
		}
		S = S0;
	    }
	
	updateStatusS();
    }
    
    Q.push(A.S); uQ.push(18); dQ.push(0);
    DBS_.store2(A.S, 0);

    while(!Q.empty())
    {
	S = Q.front(), u = uQ.front(), d = dQ.front();
	Q.pop(); uQ.pop(); dQ.pop();

	for (uc v = 0; v < 18; v++)
	    if(G[u][v])
	    {
		S0 = S; turnS(S, v);
		if (!DBS_.load2(S))
		{
		    DBS_.store2(S, d + 1);
		    maxd = max_(maxd, (uc)(d + 1));
		    Q.push(S); uQ.push(v); dQ.push(d + 1);
		}
		S = S0;
	    }
	
	updateStatusS();
    }

    printf("Total Positions of 2 sets of 6 side cubies: %d\n", DBS_.size());
    printf("Max Heuristic Value: %d\n", maxd);
    if (maxd > 15) { fprintf(stderr, "Fatal Error: max heuristic value > 15\n"); exit(0); }
}

int main(int argc, char *argv[])
{
    switch(*argv[1])
    {
	case 'C': bfsC(); DBC_.write(); break;
	case 'S': bfsS(); DBS_.write(); break;
	default: break;
    }
    printf("\n");
    return 0;
}
