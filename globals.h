#ifndef globals_h
#define globals_h

#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

//////////////////////////////MACROS & CONSTANTS///////////////////////

#define FRONT 0
#define BACK 1
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5

#define MASK4 0xFULL
#define MASK5 0x1FULL
#define MASK10 0x3FFULL
#define MASK15 0x7FFFULL
#define MASK20 0xFFFFFULL

typedef unsigned int ui;
typedef unsigned long long ull;
typedef unsigned short us;
typedef unsigned char uc;

const std::string turnName[] = { "F", "B", "U", "D", "L", "R", "F'", "B'",
    "U'", "D'", "L'", "R'", "FF", "BB", "UU", "DD", "LL", "RR" };

const bool G[19][18] =
{
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, },
    {0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, },
    {1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, },
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, },
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, },
    {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, },
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, },
    {0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, },
    {1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, },
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, },
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, },
    {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, },
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, },
    {0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, },
    {1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, },
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, },
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, },
    {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, },
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
};  //G[18][]: feasible turns when there is no previous turn

const ui revTurn[18] = { 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 12, 13, 14,
    15, 16, 17 };

us sM[18][760] = {0};
us cM[18][760] = {0};

void __attribute__ ((constructor)) initTurnMap()
{
    FILE *in = fopen("map.in", "r");
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 760; j++)
            fscanf(in, "%hu", &sM[i][j]);
    
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 760; j++)
            fscanf(in, "%hu", &cM[i][j]);
    fclose(in);
}


////////////////////////////////////FUNCTIONS/////////////////////////////////

template <typename T>
inline void swap_(T &x, T &y) { T z = y; y = x; x = z; }

template <typename T>
inline T min_(const T &x, const T &y) { return x < y? x: y; }

template <typename T>
inline T max_(const T &x, const T &y) { return x > y? x: y; }

template <typename T>
inline T abs_(const T &x) { return x < 0? -x: x; }

template <typename T>
inline void sort7(T *A)
{
    for (int i = 1; i < 7; i++)
	for (int j = i; j > 0; j--)
	    if (A[j] < A[j - 1])
		swap_(A[j], A[j - 1]);
	    else break;
}

inline int fac_(int n)
{
    int ans = 1;
    for (int i = 1; i <= n; i++)
	ans *= i;
    return ans;
}

inline int combination(int n, int k)
{
    if (n < k) return 0;
    return fac_(n) / (fac_(n - k) * fac_(k));
}

inline int minint_(const int &x, const int &y)
{
    long long m = (x - y) >> 31;
    return (y & ~m) | (x & m);
}

inline int maxint_(const int &x, const int &y)
{
    long long m = (x - y) >> 31;
    return (y & m) | (x & ~m);
}

/////////////////////////////////DATA STRUCTURES///////////////////////////////

template <typename type>
struct hash_table
{
    struct node
    {
	type v;
	node *next;
    };

    hash_table(const int &k = 23) //size of the table: 2^k
    {
	TSIZE = 1ULL << k;

	A = (node*)malloc(sizeof(node) * TSIZE);
	T = (node**)malloc(sizeof(node*) * TSIZE);
	
        I = cnt = 0;
        memset(A, 0, sizeof(node) * TSIZE);
        memset(T, 0, sizeof(node*) * TSIZE);
    }

    ~hash_table()
    {
	free(A);
	free(T);
    };

    inline void insert(const type &x)
    {
        if (inTable(x)) return;
        
        int k = x.hash() & (TSIZE - 1);
        node *p = newNode(x); p->next = T[k]; T[k] = p;
        cnt++;
    }
    
    inline int size()
    {
        return cnt;
    }
    
    inline void clear()
    {
        I = cnt = 0;
	memset(T, 0, sizeof(node*) * TSIZE);
    }
    
private:
    ull TSIZE;
    node *A; int I;
    node **T; int cnt;
    
    inline node* newNode(const type &x)
    {
	A[I].v = x;
        return &A[I++];
    }
    
    inline bool inTable(const type &x)
    {
        int k = x.hash() & (TSIZE - 1);
        for (node *p = T[k]; p; p = p->next)
            if (p->v == x)
                return true;
        return false;
    }
};


#define N 40320 //8!: 40320
#define M 2187 //3^7: 2187

struct databaseC
{
    databaseC()
    { 
	FILE *in = fopen("databaseC.in", "r");
	if (!in)
	{
	    fprintf(stderr, "Failed to initialize pattern database C.\n");
	    exit(0);
	}
	for (int i = 0; i < N; i++)
	    for (int j = 0; j < (M >> 1); j++)
		fscanf(in, "%hhu", &T[i][j]);
	fclose(in);
    }

    inline uc load(ull k)
    {
	ui idx = index(k);
	return (T[cantor(k)][idx >> 1] >> ((idx & 1) << 2)) & MASK4;
    }

private:
    uc T[N][M >> 1];
        
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

	idx += ((k >>= 3) & 3);
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

struct databaseS
{
    databaseS()
    {
	FILE *in = fopen("databaseS.in", "r");
	if (!in)
	{
	    fprintf(stderr, "Failed to initialize pattern database S.\n");
	    exit(0);
	}
	for (int i = 0; i < N; i++)
	    for (int j = 0; j < (M >> 1); j++)
		fscanf(in, "%hhu", &T[i][j]);
	fclose(in);
	
	memset(sum, 0, sizeof(sum));	

	for (int i = 0; i < 7; i++)
	    for (int j = 1; j <= 11; j++)
		sum[i][j] = sum[i][j - 1] + combination(12 - j, 6 - i);
    }
    
    inline uc load(ull k)
    {
	ui idx1, idx2;
	index(idx1, idx2, k);
	return (T[idx1][idx2 >> 1] >> ((idx2 & 1) << 2)) & MASK4;
    }
    
private:
    uc T[N][M >> 1];
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


#endif /* globals_h */
