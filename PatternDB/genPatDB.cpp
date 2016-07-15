#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <queue>
#include "../cube.h"
using namespace std;

#define N 40320ULL //8!
#define M 2188ULL //3^7 + 1

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
        T[idx >> 1][cantor(k)] |= v << ((idx & 1) << 2);
    }

    inline uc load(ull k)
    {
	ui idx = index(k);
	return (T[idx >> 1][cantor(k)] >> ((idx & 1) << 2)) & MASK4;
    }
    
    void write()
    {
	FILE *out = fopen("databaseC.in", "w");
	fwrite(T, (M >> 1) * N, 1, out);
	fclose(out);
    }
    
private:
    uc T[M >> 1][N]; ui cnt;
        
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

#define NUM 8 //number of cubies
#define N 19958400ULL //(12!)/(4!)
#define M 256ULL //2^8

struct databaseS_
{
    databaseS_(): cnt(0)
    {
	memset(T1, 0, sizeof(T1));
	memset(T2, 0, sizeof(T2));
	memset(com, 0, sizeof(com));

	for (int i = 0; i < NUM; i++)
	    for (int j = 0; j < 11; j++)
		com[i][j] = combination(11 - j, NUM - 1 - i);
    }

    inline ull size() const
    {
	return cnt;
    }

    inline void store1(ull k, uc v)
    {
	cnt++;
	ui idx1, idx2;
	trans(k); index(idx1, idx2);
	T1[idx2 >> 1][idx1] |= v << ((idx2 & 1) << 2);
    }
    
    inline void store2(ull k, uc v)
    {
	cnt++;
	ui idx1, idx2;	
	trans(k >> ((12 - NUM) * 5)); index(idx1, idx2);
	T2[idx2 >> 1][idx1] |= v << ((idx2 & 1) << 2);
    }

    inline bool load1(ull k)
    {
	ui idx1, idx2;
	trans(k); index(idx1, idx2);
	return (T1[idx2 >> 1][idx1] >> ((idx2 & 1) << 2)) & MASK4;
    }
    
    inline bool load2(ull k)
    {
	ui idx1, idx2;
	trans(k >> ((12 - NUM) * 5)); index(idx1, idx2);
	return (T2[idx2 >> 1][idx1] >> ((idx2 & 1) << 2)) & MASK4;
    }
    
    void write()
    {
	FILE *out = fopen("databaseS.in", "w");
	fwrite(T1, (M >> 1) * N, 1, out);
	fwrite(T2, (M >> 1) * N, 1, out);
	fclose(out);
    }
    
private:
    uc T1[M >> 1][N], T2[M >> 1][N]; ull cnt;
    uc tmp[NUM]; bool s[12]; ui com[NUM][12]; //com: some numbers of combinations
    
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
    
    inline void index(ui &idx1, ui &idx2)
    {
	memset(s, 0, 12);
	idx1 = idx2 = 0;
	
	for (int i = 0; i < NUM; i++)
	{
	    idx2 += ((tmp[i] / 12) & 1) << i;
	    tmp[i] %= 12, s[tmp[i]] = true;
	}
	
	idx1 += ((tmp[0] > tmp[1]) + (tmp[0] > tmp[2]) + (tmp[0] > tmp[3]) +
		 (tmp[0] > tmp[4]) + (tmp[0] > tmp[5]) + (tmp[0] > tmp[6]) +
		 (tmp[0] > tmp[7])) * 5040;
	idx1 += ((tmp[1] > tmp[2]) + (tmp[1] > tmp[3]) + (tmp[1] > tmp[4]) +
		 (tmp[1] > tmp[5]) + (tmp[1] > tmp[6]) + (tmp[1] > tmp[7])) * 720;
	idx1 += ((tmp[2] > tmp[3]) + (tmp[2] > tmp[4]) + (tmp[2] > tmp[5]) +
		 (tmp[2] > tmp[6]) + (tmp[2] > tmp[7])) * 120;
	idx1 += ((tmp[3] > tmp[4]) + (tmp[3] > tmp[5]) + (tmp[3] > tmp[6]) +
		 (tmp[3] > tmp[7])) * 24;
	idx1 += ((tmp[4] > tmp[5]) + (tmp[4] > tmp[6]) + (tmp[4] > tmp[7])) * 6;
	idx1 += ((tmp[5] > tmp[6]) + (tmp[5] > tmp[7])) * 2;
	idx1 += (tmp[6] > tmp[7]);
	
	ui t = 0; uc i, j;
	for (i = j = 0; i < NUM; j++)
	    if (!s[j]) t += com[i][j];
	    else i++;
	
	idx1 += t * 40320; //8!
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

clock_t time_cnt, st;
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
    if ((clock() - time_cnt) / (CLOCKS_PER_SEC * 1.0) <= 3) 
	return;
    time_cnt = clock();
    printf("Corner Database: %.2lf%%\n", DBC_.size() / (double)881798.4);
}

inline void updateStatusS()
{
    if ((clock() - time_cnt) / (CLOCKS_PER_SEC * 1.0) <= 3) 
	return;
    time_cnt = clock();
    printf("Side Database: %.2lf%%\n", DBS_.size() / (double)102187008);
}

void bfsC()
{
    printf("Genrating Pattern Database for corner cubies...\n");
    st = time_cnt = 0; maxd = 0;
    
    cube A;
    Q.push(A.C); uQ.push(18); dQ.push(0);

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
    DBC_.store(A.C, 0);
    
    printf("Total Positions of 8 corner cubies: %d\n", DBC_.size());
    printf("Max Heuristic Value: %d\n", maxd);
    printf("Time: %lf seconds\n", (clock() - st) / ((double)CLOCKS_PER_SEC));
}

void bfsS()
{
    printf("Genrating Pattern Database for side cubies...\n");
    st = time_cnt = 0; maxd = 0;
    cube A;
    
    Q.push(A.S); uQ.push(18); dQ.push(0);

    ull S; uc u, d;
    while(!Q.empty())
    {
	S = Q.front(), u = uQ.front(), d = dQ.front();
	Q.pop(); uQ.pop(); dQ.pop();

	for (uc v = 0; v < 18; v++)
	    if(G[u][v])
	    {
		ull S0 = S; turnS(S, v);
		if (!DBS_.load1(S))
		{
		    DBS_.store1(S, d + 1);
		    //maxd = max_(maxd, (uc)(d + 1));
		    Q.push(S); uQ.push(v); dQ.push(d + 1);
		}
		S = S0;
	    }
	
	updateStatusS();
    }
    DBS_.store1(A.S, 0); //T1

    
    Q.push(A.S); uQ.push(18); dQ.push(0);

    while(!Q.empty())
    {
	S = Q.front(), u = uQ.front(), d = dQ.front();
	Q.pop(); uQ.pop(); dQ.pop();

	for (uc v = 0; v < 18; v++)
	    if(G[u][v])
	    {
		ull S0 = S; turnS(S, v);
		if (!DBS_.load2(S))
		{
		    DBS_.store2(S, d + 1);
		    //maxd = max_(maxd, (uc)(d + 1));
		    Q.push(S); uQ.push(v); dQ.push(d + 1);
		}
		S = S0;
	    }
	
	updateStatusS();
    }
    DBS_.store2(A.S, 0); //T2

    
    printf("Total Positions of 2 sets of %d side cubies: %llu\n", NUM, DBS_.size());
    printf("Max Heuristic Value: %d\n", maxd);
    printf("Time: %lf seconds\n", (clock() - st) / ((double)CLOCKS_PER_SEC));
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
    if (maxd > 15) { fprintf(stderr, "Fatal Error: max heuristic value > 15\n"); exit(0); }
    return 0;
}
