#ifndef cube_h
#define cube_h

#include "globals.h"

struct cube
{
    ull S, C;
    int sc, cc;
    //side & corner cubies
    
    inline cube():S(0), C(0), sc(0), cc(0)
    {
        for (ull i = 0; i < 12; i++)
            S |= i << (i * 5);
        for (ull i = 0; i < 8; i++)
            C |= i << (i * 5);
    }
    
    inline bool solved()
    {
        return S == 0x5a928398a418820ULL &&
            C == 0x398a418820ULL && sc == 0 && cc == 0;
    }
    
    inline int evaluate()
    {
        return maxint_((sc >> 2) + !!(sc & 3), (cc >> 2) + !!(cc & 3)); //((sc + cc) >> 3) + !!((sc + cc) & 0x7);
    }
    
    inline void F()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xff83ff003fff83ffULL;
        k = (S0 >> 10) & MASK5; S |= k << 30, sc += sCost[0][2][k];
        k = (S0 >> 30) & MASK5; S |= k << 50, sc += sCost[0][6][k];
        k = (S0 >> 50) & MASK5; S |= k << 35, sc += sCost[0][10][k];
        k = (S0 >> 35) & MASK5; S |= k << 10, sc += sCost[0][7][k];
        
        C0 = C;
        C &= 0xffffff003ff003ffULL;
        k = (C0 >> 15) & MASK5; C |= cF[3][k] << 10, cc += cCost[0][3][k];
        k = (C0 >> 10) & MASK5; C |= cF[2][k] << 30, cc += cCost[0][2][k];
        k = (C0 >> 30) & MASK5; C |= cF[6][k] << 35, cc += cCost[0][6][k];
        k = (C0 >> 35) & MASK5; C |= cF[7][k] << 15, cc += cCost[0][7][k];
    }
    
    inline void B()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xffffe0ffc00fffe0ULL;
        k = S0 & MASK5; S |= k << 20, sc += sCost[1][0][k];
        k = (S0 >> 20) & MASK5; S |= k << 40, sc += sCost[1][4][k];
        k = (S0 >> 40) & MASK5; S |= k << 25, sc += sCost[1][8][k];
        k = (S0 >> 25) & MASK5; S |= k; sc += sCost[1][5][k];
        //sides
        
        C0 = C;
        C &= 0xffffffffc00ffc00ULL;
        k = (C0 >> 5) & MASK5; C |= cB[1][k], cc += cCost[1][1][k];
        k = C0 & MASK5; C |= cB[0][k] << 20, cc += cCost[1][0][k];
        k = (C0 >> 20) & MASK5; C |= cB[4][k] << 25, cc += cCost[1][4][k];
        k = (C0 >> 25) & MASK5; C |= cB[5][k] << 5, cc += cCost[1][5][k];
        //corners
    }
    
    inline void U()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xfffffffffff00000ULL;
        k = S0 & MASK5; S |= k << 5, sc += sCost[2][0][k];
        k = (S0 >> 5) & MASK5; S |= k << 10, sc += sCost[2][1][k];
        k = (S0 >> 10) & MASK5; S |= k << 15, sc += sCost[2][2][k];
        k = (S0 >> 15) & MASK5; S |= k, sc += sCost[2][3][k];
        //sides
        
        C0 = C;
        C &= 0xfffffffffff00000ULL;
        k = C0 & MASK5; C |= k << 5, cc += cCost[2][0][k];
        k = (C0 >> 5) & MASK5; C |= k << 10, cc += cCost[2][1][k];
        k = (C0 >> 10) & MASK5; C |= k << 15, cc += cCost[2][2][k];
        k = (C0 >> 15) & MASK5; C |= k, cc += cCost[2][3][k];
        //corners
    }
    
    inline void D()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xf00000ffffffffffULL;
        k = (S0 >> 40) & MASK5; S |= k << 55, sc += sCost[3][8][k];
        k = (S0 >> 55) & MASK5; S |= k << 50, sc += sCost[3][11][k];
        k = (S0 >> 50) & MASK5; S |= k << 45, sc += sCost[3][10][k];
        k = (S0 >> 45) & MASK5; S |= k << 40, sc += sCost[3][9][k];
        //sides
        
        C0 = C;
        C &= 0xffffff00000fffffULL;
        k = (C0 >> 35) & MASK5; C |= k << 30, cc += cCost[3][7][k];
        k = (C0 >> 30) & MASK5; C |= k << 25, cc += cCost[3][6][k];
        k = (C0 >> 25) & MASK5; C |= k << 20, cc += cCost[3][5][k];
        k = (C0 >> 20) & MASK5; C |= k << 35, cc += cCost[3][4][k];
        //corners
    }
    
    inline void L()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xf07fff07fe007fffULL;
        k = (S0 >> 15) & MASK5; S |= sL[3][k] << 35, sc += sCost[4][3][k];
        k = (S0 >> 35) & MASK5; S |= sL[7][k] << 55, sc += sCost[4][7][k];
        k = (S0 >> 55) & MASK5; S |= sL[11][k] << 20, sc += sCost[4][11][k];
        k = (S0 >> 20) & MASK5; S |= sL[4][k] << 15, sc += sCost[4][4][k];
        //sides
        
        C0 = C;
        C &= 0xffffff07fe007fe0ULL;
        k = C0 & MASK5; C |= cL[0][k] << 15, cc += cCost[4][0][k];
        k = (C0 >> 15) & MASK5; C |= cL[3][k] << 35, cc += cCost[4][3][k];
        k = (C0 >> 35) & MASK5; C |= cL[7][k] << 20, cc += cCost[4][7][k];
        k = (C0 >> 20) & MASK5; C |= cL[4][k], cc += cCost[4][4][k];
        //corners
    }
    
    inline void R()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xfffc1ff801fffc1fULL;
        k = (S0 >> 5) & MASK5; S |= sR[1][k] << 25, sc += sCost[5][1][k];
        k = (S0 >> 25) & MASK5; S |= sR[5][k] << 45, sc += sCost[5][5][k];
        k = (S0 >> 45) & MASK5; S |= sR[9][k] << 30, sc += sCost[5][9][k];
        k = (S0 >> 30) & MASK5; S |= sR[6][k] << 5, sc += sCost[5][6][k];
        //sides
        
        C0 = C;
        C &= 0xfffffff801ff801fULL;
        k = (C0 >> 10) & MASK5; C |= cR[2][k] << 5, cc += cCost[5][2][k];
        k = (C0 >> 5) & MASK5; C |= cR[1][k] << 25, cc += cCost[5][1][k];
        k = (C0 >>25) & MASK5; C |= cR[5][k] << 30, cc += cCost[5][5][k];
        k = (C0 >> 30) & MASK5; C |= cR[6][k] << 10, cc += cCost[5][6][k];
        //corners
    }
    
    inline void F_()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xff83ff003fff83ffULL;
        k = (S0 >> 10) & MASK5; S |= k << 35, sc += sCost[6][2][k];
        k = (S0 >> 35) & MASK5; S |= k << 50, sc += sCost[6][7][k];
        k = (S0 >> 50) & MASK5; S |= k << 30, sc += sCost[6][10][k];
        k = (S0 >> 30) & MASK5; S |= k << 10, sc += sCost[6][6][k];
        //sides
        
        C0 = C;
        C &= 0xffffff003ff003ffULL;
        k = (C0 >> 10) & MASK5; C |= cF_[2][k] << 15, cc += cCost[6][2][k];
        k = (C0 >> 15) & MASK5; C |= cF_[3][k] << 35, cc += cCost[6][3][k];
        k = (C0 >> 35) & MASK5; C |= cF_[7][k] << 30, cc += cCost[6][7][k];
        k = (C0 >> 30) & MASK5; C |= cF_[6][k] << 10, cc += cCost[6][6][k];
        //corners
    }
    
    inline void B_()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xffffe0ffc00fffe0ULL;
        k = S0 & MASK5; S |= k << 25, sc += sCost[7][0][k];
        k = (S0 >> 25) & MASK5; S |= k << 40, sc += sCost[7][5][k];
        k = (S0 >> 40) & MASK5; S |= k << 20, sc += sCost[7][8][k];
        k = (S0 >> 20) & MASK5; S |= k, sc += sCost[7][4][k];
        //sides
        
        C0 = C;
        C &= 0xffffffffc00ffc00ULL;
        k = C0 & MASK5; C |= cB_[0][k] << 5, cc += cCost[7][0][k];
        k = (C0 >> 5) & MASK5; C |= cB_[1][k] << 25, cc += cCost[7][1][k];
        k = (C0 >> 25) & MASK5; C |= cB_[5][k] << 20, cc += cCost[7][5][k];
        k = (C0 >> 20) & MASK5; C |= cB_[4][k], cc += cCost[7][4][k];
        //corners
    }
    
    inline void U_()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xfffffffffff00000ULL;
        k = S0 & MASK5; S |= k << 15, sc += sCost[8][0][k];
        k = (S0 >> 15) & MASK5; S |= k << 10, sc += sCost[8][3][k];
        k = (S0 >> 10) & MASK5; S |= k << 5, sc += sCost[8][2][k];
        k = (S0 >> 5) & MASK5; S |= k, sc += sCost[8][1][k];
        //sides
        
        C0 = C;
        C &= 0xfffffffffff00000ULL;
        k = C0 & MASK5; C |= k << 15, cc += cCost[8][0][k];
        k = (C0 >> 15) & MASK5; C |= k << 10, cc += cCost[8][3][k];
        k = (C0 >> 10) & MASK5; C |= k << 5, cc += cCost[8][2][k];
        k = (C0 >> 5) & MASK5; C |= k, cc += cCost[8][1][k];
        //corners
    }
    
    inline void D_()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xf00000ffffffffffULL;
        k = (S0 >> 40) & MASK5; S |= k << 45, sc += sCost[9][8][k];
        k = (S0 >> 45) & MASK5; S |= k << 50, sc += sCost[9][9][k];
        k = (S0 >> 50) & MASK5; S |= k << 55, sc += sCost[9][10][k];
        k = (S0 >> 55) & MASK5; S |= k << 40, sc += sCost[9][11][k];
        //sides
        
        C0 = C;
        C &= 0xffffff00000fffffULL;
        k = (C0 >> 20) & MASK5; C |= k << 25, cc += cCost[9][4][k];
        k = (C0 >> 25) & MASK5; C |= k << 30, cc += cCost[9][5][k];
        k = (C0 >> 30) & MASK5; C |= k << 35, cc += cCost[9][6][k];
        k = (C0 >> 35) & MASK5; C |= k << 20, cc += cCost[9][7][k];
        //corners
    }
    
    inline void L_()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xf07fff07fe007fffULL;
        k = (S0 >> 15) & MASK5; S |= sL[3][k] << 20, sc += sCost[10][3][k];
        k = (S0 >> 20) & MASK5; S |= sL[4][k] << 55, sc += sCost[10][4][k];
        k = (S0 >> 55) & MASK5; S |= sL[11][k] << 35, sc += sCost[10][11][k];
        k = (S0 >> 35) & MASK5; S |= sL[7][k] << 15, sc += sCost[10][7][k];
        //sides
        
        C0 = C;
        C &= 0xffffff07fe007fe0ULL;
        k = (C0 >> 15) & MASK5; C |= cL_[3][k], cc += cCost[10][3][k];
        k = C0 & MASK5; C |= cL_[0][k] << 20, cc += cCost[10][0][k];
        k = (C0 >> 20) & MASK5; C |= cL_[4][k] << 35, cc += cCost[10][4][k];
        k = (C0 >> 35) & MASK5; C |= cL_[7][k] << 15, cc += cCost[10][7][k];
        //corners
    }
    
    inline void R_()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xfffc1ff801fffc1fULL;
        k = (S0 >> 5) & MASK5; S |= sR[1][k] << 30, sc += sCost[11][1][k];
        k = (S0 >> 30) & MASK5; S |= sR[6][k] << 45, sc += sCost[11][6][k];
        k = (S0 >> 45) & MASK5; S |= sR[9][k] << 25, sc += sCost[11][9][k];
        k = (S0 >> 25) & MASK5; S |= sR[5][k] << 5, sc += sCost[11][5][k];
        //sides
        
        C0 = C;
        C &= 0xfffffff801ff801fULL;
        k = (C0 >> 5) & MASK5; C |= cR_[1][k] << 10, cc += cCost[11][1][k];
        k = (C0 >> 10) & MASK5; C |= cR_[2][k] << 30, cc += cCost[11][2][k];
        k = (C0 >> 30) & MASK5; C |= cR_[6][k] << 25, cc += cCost[11][6][k];
        k = (C0 >> 25) & MASK5; C |= cR_[5][k] << 5, cc += cCost[11][5][k];
        //corners
    }
    
    inline void FF()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xff83ff003fff83ffULL;
        k = (S0 >> 10) & MASK5; S |= k << 50, sc += sCost[12][2][k];
        k = (S0 >> 50) & MASK5; S |= k << 10, sc += sCost[12][10][k];
        k = (S0 >> 30) & MASK5; S |= k << 35, sc += sCost[12][6][k];
        k = (S0 >> 35) & MASK5; S |= k << 30, sc += sCost[12][7][k];
        //sides
        
        C0 = C;
        C &= 0xffffff003ff003ffULL;
        k = (C0 >> 15) & MASK5; C |= cFF[3][k] << 30, cc += cCost[12][3][k];
        k = (C0 >> 30) & MASK5; C |= cFF[6][k] << 15, cc += cCost[12][6][k];
        k = (C0 >> 10) & MASK5; C |= cFF[2][k] << 35, cc += cCost[12][2][k];
        k = (C0 >> 35) & MASK5; C |= cFF[7][k] << 10, cc += cCost[12][7][k];
        //corners
    }
    
    inline void BB()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xffffe0ffc00fffe0ULL;
        k = S0 & MASK5; S |= k << 40, sc += sCost[13][0][k];
        k =(S0 >> 40) & MASK5; S |= k, sc +=sCost[13][8][k];
        k = (S0 >> 20) & MASK5; S |= k << 25, sc += sCost[13][4][k];
        k = (S0 >> 25) & MASK5; S |= k << 20, sc += sCost[13][5][k];
        //sides
        
        C0 = C;
        C &= 0xffffffffc00ffc00ULL;
        k = C0 & MASK5; C |= cBB[0][k] << 25, cc += cCost[13][0][k];
        k = (C0 >> 25) & MASK5; C |= cBB[5][k], cc += cCost[13][5][k];
        k = (C0 >> 5) & MASK5; C |= cBB[1][k] << 20, cc += cCost[13][1][k];
        k = (C0 >> 20) & MASK5; C |= cBB[4][k] << 5, cc += cCost[13][4][k];
        //corners
    }
    
    inline void UU()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xfffffffffff00000ULL;
        k = S0 & MASK5; S |= k << 10, sc += sCost[14][0][k];
        k = (S0 >> 10) & MASK5; S |= k, sc += sCost[14][2][k];
        k = (S0 >> 5) & MASK5; S |= k << 15, sc += sCost[14][1][k];
        k = (S0 >> 15) & MASK5; S |= k << 5, sc += sCost[14][3][k];
        //sides
        
        C0 = C;
        C &= 0xfffffffffff00000ULL;
        k = C0 & MASK5; C |= k << 10, cc += cCost[14][0][k];
        k = (C0 >> 10) & MASK5; C |= k, cc += cCost[14][2][k];
        k = (C0 >> 5) & MASK5; C |= k << 15, cc += cCost[14][1][k];
        k = (C0 >> 15) & MASK5; C |= k << 5, cc += cCost[14][3][k];
        //corners
    }
    
    inline void DD()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xf00000ffffffffffULL;
        k = (S0 >> 40) & MASK5; S |= k << 50, sc += sCost[15][8][k];
        k = (S0 >> 50) & MASK5; S |= k << 40, sc += sCost[15][10][k];
        k = (S0 >> 45) & MASK5; S |= k << 55, sc += sCost[15][9][k];
        k = (S0 >> 55) & MASK5; S |= k << 45, sc += sCost[15][11][k];
        //sides
        
        C0 = C;
        C &= 0xffffff00000fffffULL;
        k = (C0 >> 20) & MASK5; C |= k << 30, cc += cCost[15][4][k];
        k = (C0 >> 30) & MASK5; C |= k << 20, cc += cCost[15][6][k];
        k = (C0 >> 25) & MASK5; C |= k << 35, cc += cCost[15][5][k];
        k = (C0 >> 35) & MASK5; C |= k << 25, cc += cCost[15][7][k];
        //corners
    }
    
    inline void LL()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xf07fff07fe007fffULL;
        k = (S0 >> 15) & MASK5; S |= k << 55, sc += sCost[16][3][k];
        k = (S0 >> 55) & MASK5; S |= k << 15, sc += sCost[16][11][k];
        k = (S0 >> 20) & MASK5; S |= k << 35, sc += sCost[16][4][k];
        k = (S0 >> 35) & MASK5; S |= k << 20, sc += sCost[16][7][k];
        //sides
        
        C0 = C;
        C &= 0xffffff07fe007fe0ULL;
        k = C0 & MASK5; C |= cLL[0][k] << 35, cc += cCost[16][0][k];
        k = (C0 >> 35) & MASK5; C |= cLL[7][k], cc += cCost[16][7][k];
        k = (C0 >> 15) & MASK5; C |= cLL[3][k] << 20, cc += cCost[16][3][k];
        k = (C0 >> 20) & MASK5; C |= cLL[4][k] << 15, cc += cCost[16][4][k];
        //corners
    }
    
    inline void RR()
    {
        ull S0, C0, k;
        
        S0 = S;
        S &= 0xfffc1ff801fffc1fULL;
        k = (S0 >> 5) & MASK5; S |= k << 45, sc += sCost[17][1][k];
        k = (S0 >> 45) & MASK5; S |= k << 5, sc += sCost[17][9][k];
        k = (S0 >> 25) & MASK5; S |= k << 30, sc += sCost[17][5][k];
        k = (S0 >> 30) & MASK5; S |= k << 25, sc += sCost[17][6][k];
        //sides
        
        C0 = C;
        C &= 0xfffffff801ff801fULL;
        k = (C0 >> 5) & MASK5; C |= cRR[1][k] << 30, cc += cCost[17][1][k];
        k = (C0 >> 30) & MASK5; C |= cRR[6][k] << 5, cc += cCost[17][6][k];
        k = (C0 >> 10) & MASK5; C |= cRR[2][k] << 25, cc += cCost[17][2][k];
        k = (C0 >> 25) & MASK5; C |= cRR[5][k] << 10, cc += cCost[17][5][k];
        //corners
    }
};

#endif /* cube_h */