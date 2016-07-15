#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <string>
#include "../cube.h"
using namespace std;

#define N 100000000

cube A;
int seq[N] = {0}, rseq[N] = {0};

void genSeq()
{
    for (int i = 0; i < N; i++)
        seq[i] = i % 1;
    for (int i = 0; i < N >> 1; i++)
        swap_(seq[rand() % N], seq[rand() % N]);
    
    for (int i = 0; i < N; i++)
        rseq[i] = revTurn[seq[N - 1 - i]];
}

void testSingleTurns()
{
    for (int i = 0; i < 18; i++)
    {
        A.turn(i);
        A.turn(revTurn[i]);
        if (!A.solved())
        {
            printf("%s/%s error!\n", turnName[i].c_str(), turnName[revTurn[i]].c_str());
            exit(0);
        }
    }
    //brief test
    
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 9; j++)
            A.turn(i);
        A.turn(revTurn[i]);
        if (!A.solved())
        {
            printf("%s/%s error!\n", turnName[i].c_str(), turnName[revTurn[i]].c_str());
            exit(0);
        }
        
        for (int j = 0; j < 2; j++)
            A.turn(i);
        for (int j = 0; j < 2; j++)
            A.turn(revTurn[i]);
        if (!A.solved())
        {
            printf("%s/%s error!\n", turnName[i].c_str(), turnName[revTurn[i]].c_str());
            exit(0);
        }
    }
    //test 90-degree turns
    
    for (int i = 12; i < 18; i++)
    {
        A.turn(i);
        for (int j = 0; j < 2; j++)
            A.turn(i - 12);
        if (!A.solved())
        {
            printf("%s/%s error!\n", turnName[i].c_str(), turnName[revTurn[i]].c_str());
            exit(0);
        }
        
        A.turn(i);
        for (int j = 0; j < 2; j++)
            A.turn(i - 6);
        if (!A.solved())
        {
            printf("%s/%s error!\n", turnName[i].c_str(), turnName[revTurn[i]].c_str());
            exit(0);
        }
    }
    //test 180-degree turns
}

void testComposedTurns()
{
    genSeq();
    for (int i = 0; i < N; i++)
        A.turn(seq[i]);
    for (int i = N - 1; i >= 0; i--)
        A.turn(rseq[i]);
    if (!A.solved())
        printf("Randomized cube-turn error!\n\n");
    else printf("Cube-turn correctly implemented.\n\n");
}

void testTurnSpeed()
{
    double t;
    time_t s = clock();
    for (int i = 0; i < N; i++)
        A.turn(seq[i]);
    for (int i = 0; i < N; i++)
        A.turn(seq[i]);
    if (!A.solved()) return;
    t = (clock() - s) / (CLOCKS_PER_SEC * 1.0);
    printf("Time: %lf\n", t);
    printf("%d turns/second\n", (int)((N << 1) / t));
}

int main()
{
    testSingleTurns();
    testComposedTurns();
    //testSpeed();
    return 0;
}
