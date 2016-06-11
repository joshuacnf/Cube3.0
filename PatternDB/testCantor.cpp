#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

#define N 8
#define M 40320

int P[M][N] = {0};
int F[N] = {1};

void init()
{
    for (int i = 0; i < N; i++) P[0][i] = i;

    for (int i = 1; i < M - 1; i++)
    {
	for (int j = 0; j < N; j++)
	    P[i][j] = P[i - 1][j];
	
	int j = N - 1, k = N - 1;
	while (P[i][j - 1] > P[i][j]) j--;
	while (P[i][k] < P[i][j - 1]) k--;
	swap(P[i][k], P[i][j - 1]);
	int p = ((j + N - 1) >> 1) - j;
	for (k = 0; k <= p; k++) swap(P[i][j + k], P[i][N - 1 - k]);
    }

    for (int i = 0; i < N; i++) P[M - 1][N - 1 - i] = i;
    //Permutation

    for (int i = 1; i < N; i++) F[i] = i * F[i - 1];
    //Factorial
}

inline int cantor(int *P)
{
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
	int cnt = 0;
	for (int j = i + 1; j < N; j++)
	    if (P[j] < P[i])
		cnt++;
	ans += cnt * F[N - 1 - i];
    }
    return ans;
}

void testSpeed()
{
    clock_t s = clock();
    for (int t = 0; t < 100; t++)
	for (int i = 0; i < M; i++)
	    if (cantor(P[i]) != i)
		printf("ERROR!\n");
    double time = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
    printf("Time: %lf\n%d calls / second\n", time, (int)(M * 100 / time));
}

int main()
{
    init();
    testSpeed();
    return 0;
}
