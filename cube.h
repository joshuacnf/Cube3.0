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
        uc i;
        ull S0 = 0, C0 = 0;
        
        for (i = 0; i < 40; i += 10)
        {
            S0 |= ((ull)sM[(S >> i) & MASK10][u]) << i;
            C0 |= ((ull)cM[(C >> i) & MASK10][u]) << i;
        }
        for (; i < 60; i += 10)
            S0 |= ((ull)sM[(S >> i) & MASK10][u]) << i;
        
        S = S0, C = C0;
    }
};

#endif /* cube_h */
