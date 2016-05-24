#ifndef globals_h
#define globals_h

#include <string>
#include <cstring>

//////////////////////////////MACROS & CONSTANTS///////////////////////

#define FRONT 0
#define BACK 1
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5

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
};  //G[19][]: feasible turns when there is no previous turn

const ui revTurn[18] = { 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 12, 13, 14,
    15, 16, 17 };

us sM[18][760] = {0};
us cM[18][760] = {0};

/////////////////////////////////DATA STRUCTURES///////////////////////////////


#define N 0x800000
struct hash_table
{
    struct node
    {
        ull S, C;
        node *next;
        
        inline node() {}
        inline node(const ull S_, const ull C_):S(S_), C(C_), next(0) {}
    };
    
    hash_table()
    {
        I = cnt = 0;
        memset(A, 0, sizeof(A));
        memset(T, 0, sizeof(T));
    }
    
    inline void insert(ull S, ull C)
    {
        if (inTable(S, C)) return;
        
        int k = S & (N - 1);
        node *p = newNode(S, C); p->next = T[k]; T[k] = p;
        cnt++;
    }
    
    inline int size()
    {
        return cnt;
    }
    
    inline void clear()
    {
        I = cnt = 0;
        memset(T, 0, sizeof(T));
    }
    
private:
    node *T[N]; int cnt;
    node A[N]; int I;
    
    inline node* newNode(ull S, ull C)
    {
        A[I].S = S, A[I].C = C;
        return &A[I++];
    }
    
    inline bool inTable(ull S, ull C)
    {
        int k = S & (N - 1);
        for (node *p = T[k]; p; p = p->next)
            if (p->S == S && p->C == C)
                return true;
        return false;
    }
};
#undef N



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
