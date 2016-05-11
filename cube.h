#ifndef cube_h
#define cube_h

#include "globals.h"

struct cube
{
    ull S, C;
    //side & corner cubies
    
    inline cube(): S(0), C(0)
    {
        for (ull i = 0; i < 12; i++) S |= i << (5 * i);
        for (ull i = 0; i < 8; i++) C |= i << (5 * i);
    }
    
    inline bool solved()
    {
        return S == 0x05a928398a418820ULL &&
                C == 0x000000398a418820ULL;
    }
    
    inline void turn(uc u)
    {   
        ull S1(0), C1(0);
        
        for (uc i = 0; i < 60; i += 5)
            S1 |= sM[u][(S >> i) & MASK5] << i;
        
        for (uc i = 0; i < 40; i += 5)
            C1 |= cM[u][(C >> i) & MASK5] << i;
        
        S = S1, C = C1;
    }
};

#endif /* cube_h */