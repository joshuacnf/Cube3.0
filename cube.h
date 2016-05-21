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
	    S0 |= ((ull)sM[u][(S >> i) & MASK10]) << i;
	    C0 |= ((ull)cM[u][(C >> i) & MASK10]) << i;
	}
	for (; i < 60; i += 10)
	    S0 |= ((ull)sM[u][(S >> i) & MASK10]) << i;
	
        S = S0, C = C0; 
/*
	S = (ull)sM[u][S & MASK10] 
	    | ((ull)sM[u][(S >> 10) & MASK10] << 10)
	    | ((ull)sM[u][(S >> 20) & MASK10] << 20)
	    | ((ull)sM[u][(S >> 30) & MASK10] << 30)
	    | ((ull)sM[u][(S >> 40) & MASK10] << 40)
	    | ((ull)sM[u][(S >> 50) & MASK10] << 50);
	
	C = (ull)cM[u][C & MASK10]
	    | ((ull)cM[u][(C >> 10) & MASK10] << 10)
	    | ((ull)cM[u][(C >> 20) & MASK10] << 20)
	    | ((ull)cM[u][(C >> 30) & MASK10] << 30);
*/
/*
	for (i = 0; i < 60; i += 10)
	    S0 |= (ull)sM[u][(S >> i) & MASK10] << i;
	for (i = 0; i < 40; i += 10)
	C0 |= (ull)cM[u][(C >> i) & MASK10] << i;	
*/    
    }
};

#endif /* cube_h */
