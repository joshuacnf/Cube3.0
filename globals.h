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
#define MASK32 0xFFFFFFFFULL
#define MASK40 0xFFFFFFFFFFULL

#define M32 0x2000000ULL
#define M64 0x4000000ULL
#define M128 0x8000000ULL
#define M256 0x10000000ULL
#define M512 0x20000000ULL
#define M1024 0x40000000ULL
#define G1 0x40000000ULL
#define G2 0x80000000ULL
#define G4 0x100000000ULL
#define G8 0x200000000ULL
#define G16 0x400000000ULL
#define G32 0x800000000ULL
#define G64 0x1000000000ULL

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
    if (!in)
    { 
	fprintf(stderr, "Warning: Turn Map uninitialized.\n");
	return;
    }

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

template <typename T>
inline void sort4(T *A)
{
    for (int i = 1; i < 4; i++)
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

//////////////////////////////////DATA STRUCTURES///////////////////////////////

struct mem_queue
{
    mem_queue(const ull &block_size_,
	      const ull &mem_usg_ = M512):
	block_size(block_size_), head(0), tail(0), cnt(0)
    {
	array_len = (mem_usg_ / block_size) * block_size;
	T = (char*)malloc(array_len);
    }

    ~mem_queue()
    {
	free(T);
    }

    inline bool empty()
    {
	return cnt == 0;
    }

    inline bool full()
    {
	return cnt && head == tail;
    }

    inline ull size()
    {
	return cnt;
    }
    
    inline ull front()
    {
	return *((ull*)(T + head));
    }
    
    inline void push(ull x)
    {	
	memcpy(T + tail, (char*)(&x), block_size);
	tail += block_size; cnt++;
	if (tail == array_len) tail = 0;
    }
    
    inline void pop()
    {
	head += block_size; cnt--;
	if (head == array_len) head = 0;
    }

    inline ull write(FILE *out)
    {
	fwrite(T + head, array_len - head, 1, out);
	fwrite(T, tail, 1, out);
	head = tail = cnt = 0;
	return array_len;
    }
    
private:
    char *T;
    ull head, tail, cnt;
    ull array_len, block_size;
};

ui DISK_QUEUE_ID = 0;

struct disk_queue
{
    disk_queue(const ui &block_size_,
	       const ull &mem_usg_ = M512):
	buffer(block_size_, mem_usg_),
	block_size(block_size_), head(0), tail(0), cnt(0)
    {
	snprintf(file_name, 8, "queue%d", DISK_QUEUE_ID++);
	handle = fopen(file_name, "wb+");
	block = (uc*)malloc(block_size);
    }
    
    ~disk_queue()
    {
	fclose(handle);
	remove(file_name);
	free(block);
    }
    
    inline bool empty()
    {
	return buffer.empty();
    }

    inline ull size()
    {
	return cnt;
    }

    inline ull mem_size()
    {
	return buffer.size();
    }

    inline ull disk_size()
    {
	return (tail - head) / block_size;
    }

    inline ull front()
    {
	if (file_empty())
	    return buffer.front();
	
	fseek(handle, head, SEEK_SET);
	fread(block, block_size, 1, handle);
	return *((ull*)block);
    }

    inline void push(ull x)
    {
	cnt++;
	if (buffer.full())
	{
	    fseek(handle, tail, SEEK_SET);
	    tail += buffer.write(handle);
	}
	buffer.push(x);
    }

    inline void pop()
    {
	cnt--;
	if (file_empty())
	{
	    buffer.pop();
	    return;
	}
	head += block_size;
	
	if (head / (double)(tail - head) > 0.1)
	    clear();
    }
    
private:
    FILE *handle; char file_name[8];
    ull head, tail, cnt;
    ull block_size; uc *block;
    mem_queue buffer;
    
    inline bool file_empty()
    {
	return head == tail;
    }
    
#define PAGE_SIZE M512 //512M
    inline void clear()
    {
	uc *tmp = (uc*)malloc(min_(tail - head, PAGE_SIZE));
	
	ull tail_ = 0, len = 0; 
	while (head < tail)
	{
	    len = min_(tail - head, PAGE_SIZE);
	    
	    fseek(handle, head, SEEK_SET);
	    fread(tmp, len, 1, handle);
	    
	    fseek(handle, tail_, SEEK_SET); 
	    fwrite(tmp, len, 1, handle);
	    
	    head += len, tail_ += len;
	}

	head = 0; tail = tail_;
	free(tmp);
    }
#undef PAGE_SIZE
};


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


#define N 40320ULL //8!: 40320
#define M 2188ULL //3^7: 2187

struct databaseC
{
    databaseC()
    { 
	FILE *in = fopen("databaseC.in", "rb");
	if (!in)
	{
	    fprintf(stderr, "Failed to initialize pattern database C.\n");
	    exit(0);
	}
	fread(T, (M >> 1) * N, 1, in);
	fclose(in);
    }

    inline uc load(ull k)
    {
	ui idx = index(k);
	return (T[idx >> 1][cantor(k)] >> ((idx & 1) << 2)) & MASK4;
    }

private:
    uc T[M >> 1][N];
        
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

#define NUM 8 //number of cubies
#define N 19958400ULL //(12!)/(4!)
#define M 256ULL //2^8

struct databaseS
{
    databaseS()
    {
	FILE *in = fopen("databaseS.in", "rb");
	if (!in)
	{
	    fprintf(stderr, "Failed to initialize pattern database S.\n");
	    exit(0);
	}
	fread(T1, (M >> 1) * N, 1, in);
	fread(T2, (M >> 1) * N, 1, in);
	fclose(in);
	
	memset(com, 0, sizeof(com));

	for (int i = 0; i < NUM; i++)
	    for (int j = 0; j < 11; j++)
		com[i][j] = combination(11 - j, NUM - 1 - i);
    }
    
    inline uc load1(ull k)
    {
	ui idx1, idx2;
	trans(k); index(idx1, idx2);
	return (T1[idx2 >> 1][idx1] >> ((idx2 & 1) << 2)) & MASK4;
    }

    inline uc load2(ull k)
    {
	ui idx1, idx2;
	trans(k >> ((12 - NUM) * 5)); index(idx1, idx2);
	return (T2[idx2 >> 1][idx1] >> ((idx2 & 1) << 2)) & MASK4;
    }
    
private:
    uc T1[M >> 1][N], T2[M >> 1][N];
    ui com[NUM][12]; //com: some numbers of combinations
    bool s[12]; uc tmp[NUM];

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
	idx1 = 0, idx2 = 0;
	
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


#endif /* globals_h */
