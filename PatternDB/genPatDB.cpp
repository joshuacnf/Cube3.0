#include <cstdio>
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


#define N 3991680 //(12!)/(5!)
#define M 128 //2^7

struct databaseS_
{
    databaseS_(): cnt(0)
    {
	memset(T, 0, sizeof(T));
	memset(sum, 0, sizeof(sum));	

	for (int i = 0; i < 7; i++)
	    for (int j = 1; j <= 11; j++)
		sum[i][j] = sum[i][j - 1] + combination(12 - j, 6 - i);
    }

    inline ui size()
    {
	return cnt;
    }

    inline void store(ull k, uc v)
    {
	cnt++;
	ui idx1, idx2;
	index(idx1, idx2, k);
	T[idx1][idx2 >> 1] |= v << ((idx2 & 1) << 2);
    }

    inline uc load(ull k)
    {
	ui idx1, idx2;
	index(idx1, idx2, k);
	return (T[idx1][idx2 >> 1] >> ((idx2 & 1) << 2)) & MASK4;
    }
    
    void write()
    {
	T[0][0] &= ~MASK4;
	FILE *out = fopen("databaseS.in", "w");
	for (int i = 0; i < N; i++)
	    for (int j = 0; j < (M >> 1); j++)
		fprintf(out, "%hhu ", T[i][j]);
	fclose(out);
    }
    
private:
    uc T[N][M >> 1]; ui cnt;
    uc tmp[7]; ui sum[7][12]; //sum: some sort of prefix sums of combinations
    
    inline void index(ui &idx1, ui &idx2, ull k)
    {
	idx1 = idx2 = 0;

	tmp[0] = k & MASK5; 
	tmp[1] = (k >>= 5) & MASK5; 
	tmp[2] = (k >>= 5) & MASK5;
	tmp[3] = (k >>= 5) & MASK5; 
	tmp[4] = (k >>= 5) & MASK5; 
	tmp[5] = (k >>= 5) & MASK5;
	tmp[6] = (k >>= 5) & MASK5;

	if (tmp[0] > 11) idx2 |= 1, tmp[0] -= 12;
	if (tmp[1] > 11) idx2 |= 2, tmp[1] -= 12;
	if (tmp[2] > 11) idx2 |= 4, tmp[2] -= 12;
	if (tmp[3] > 11) idx2 |= 8, tmp[3] -= 12;
	if (tmp[4] > 11) idx2 |= 16, tmp[4] -= 12;
	if (tmp[5] > 11) idx2 |= 32, tmp[5] -= 12;
	if (tmp[6] > 11) idx2 |= 64, tmp[6] -= 12;
	
	idx1 += ((tmp[0] > tmp[1]) + (tmp[0] > tmp[2]) + (tmp[0] > tmp[3]) +
		 (tmp[0] > tmp[4]) + (tmp[0] > tmp[5]) + (tmp[0] > tmp[6])) * 720;
	idx1 += ((tmp[1] > tmp[2]) + (tmp[1] > tmp[3]) + (tmp[1] > tmp[4]) +
		 (tmp[1] > tmp[5]) + (tmp[1] > tmp[6])) * 120;
	idx1 += ((tmp[2] > tmp[3]) + (tmp[2] > tmp[4]) + (tmp[2] > tmp[5]) +
		 (tmp[2] > tmp[6])) * 24;
	idx1 += ((tmp[3] > tmp[4]) + (tmp[3] > tmp[5]) + (tmp[3] > tmp[6])) * 6;
	idx1 += ((tmp[4] > tmp[5]) + (tmp[4] > tmp[6])) * 2;
	idx1 += tmp[5] > tmp[6];

	sort7(tmp);

	ui t = 0;

	t += sum[0][tmp[0]];
	t += sum[1][tmp[1]] - sum[1][tmp[0] + 1];
	t += sum[2][tmp[2]] - sum[2][tmp[1] + 1];	
	t += sum[3][tmp[3]] - sum[3][tmp[2] + 1];
	t += sum[4][tmp[4]] - sum[4][tmp[3] + 1];
	t += sum[5][tmp[5]] - sum[5][tmp[4] + 1];
	t += sum[6][tmp[6]] - sum[6][tmp[5] + 1];

	idx1 += t * 5040;
    }
};

#undef N
#undef M

databaseC_ DBC_;
databaseS_ DBS_;
queue<ull> Q;
queue<uc> uQ, dQ;

clock_t st = 0;

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
    printf("Side Database: %.2lf%%\n", DBS_.size() / (double)5109350.4);
}

void bfsC()
{
    printf("Genrating Pattern Database for corner cubies...\n");
    st = 0;
    
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
		    Q.push(C); uQ.push(v); dQ.push(d + 1);
		}
		C = C0;
	    }
	
	updateStatusC();
    }

    printf("Total Positions of 8 corner cubies: %d\n", DBC_.size());
}

void bfsS()
{
    printf("Genrating Pattern Database for side cubies...\n");
    st = 0;
    
    cube A;
    Q.push(A.S); uQ.push(18); dQ.push(0);
    DBS_.store(A.C, 0);

    ull S; uc u, d;
    while(!Q.empty())
    {
	S = Q.front(), u = uQ.front(), d = dQ.front();
	Q.pop(); uQ.pop(); dQ.pop();

	for (uc v = 0; v < 18; v++)
	    if(G[u][v])
	    {
		ull S0 = S; 
		turnS(S, v);
		if (!DBS_.load(S))
		{
		    DBS_.store(S, d + 1);
		    Q.push(S); uQ.push(v); dQ.push(d + 1);
		}		 		
		S = S0;
	    }
	
	updateStatusS();
    }

    printf("Total Positions of 7 side cubies: %d\n", DBS_.size());
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
	switch(*argv[i])
	{
	    case 'C': bfsC(); DBC_.write(); break;
	    case 'S': bfsS(); DBS_.write(); break;
	    default: break;
	}
    }
    printf("\n");
    return 0;
}
