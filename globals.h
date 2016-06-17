#ifndef globals_h
#define globals_h

#include <string>
#include <cstring>
#include <cstdlib>

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


#define N 40320 //8!
#define M 2187 //3^7

struct database
{
    database()
    { 
	FILE *in = fopen("database.in", "r");
	if (!in) 
	    fprintf(stderr, "Pattern Database Initialization Failed.\n");
	for (int i = 0; i < N; i++)
	    for (int j = 0; j < M; j++)
		fscanf(in, "%hhu", &T[i][j]);
	fclose(in);
	
	fac[0] = pow3[0] = 1;
	for (int i = 1; i < 10; i++)
	    fac[i] = fac[i - 1] * i;
	for (int i = 1; i < 10; i++)
	    pow3[i] = pow3[i - 1] * 3;
    }

    inline uc load(ull k)
    {
	trans(k);
	int idx = index();
	return (T[cantor()][idx >> 1] >> ((idx & 1) << 2)) & MASK4;
    }

private:
    uc T[N][M];
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

#undef N
#undef M

////////////////////////////////////FUNCTIONS/////////////////////////////////

template <typename T>
inline void swap_(T &x, T &y) { T z = y; y = x; x = z; }

template <typename T>
inline T min_(const T &x, const T &y) { return x < y? x: y; }

template <typename T>
inline T max_(const T &x, const T &y) { return x > y? x: y; }

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

#endif /* globals_h */
