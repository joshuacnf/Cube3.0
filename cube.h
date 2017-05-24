#ifndef cube_h
#define cube_h

#include <map>
#include <string>
#include <algorithm>
#include "globals.h"
using namespace std;

void transcode(char f[6][3][3], ull &C, ull &S);

struct cube
{
    ull S, C;
    //side & corner cubies
    
    inline cube(): S(0), C(0)
    {
        for (ull i = 0; i < 12; i++) S |= i << (5 * i);
        for (ull i = 0; i < 8; i++) C |= i << (5 * i);
    }

    inline void encode(char faces[6][3][3])
    {
	transcode(faces, C, S);
    }
    
    inline bool solved() const
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
    }
};

bool operator ==(const cube &A, const cube &B)
{
    return A.C == B.C && A.S == B.S;
}


///////////////////////////////////////Encode Rubik's Cube based on face-representation/////////////////////////////////


int orientation_corner_cubie(int pos, char f)
{
    if (0 <= pos && pos < 4 && f == 'U') return 2;
    if (4 <= pos && pos < 8 && f == 'D') return 2;
    
    int m[8][128];
    m[0]['B'] = m[1]['R'] = m[2]['F'] = m[3]['L'] = 0;
    m[0]['L'] = m[1]['B'] = m[2]['R'] = m[3]['F'] = 1;
    m[4]['B'] = m[5]['R'] = m[6]['F'] = m[7]['L'] = 0;
    m[4]['L'] = m[5]['B'] = m[6]['R'] = m[7]['F'] = 1;
    
    return m[pos][f];
}

int orientation_side_cubie(int pos, char f)
{
    if (0 <= pos && pos < 4) return f == 'U'? 1: 0;
    if (8 <= pos && pos < 12) return f == 'D'? 1: 0;
    
    if (f == 'L' && (pos == 4 || pos == 7)) return 1;
    if (f == 'R' && (pos == 5 || pos == 6)) return 1;
    return 0;
}

void transcode(char faces[6][3][3], ull &C, ull &S)
{
#define F faces[0]
#define R faces[1]
#define B faces[2]
#define L faces[3]
#define U faces[4]
#define D faces[5]
    
    map<char, char> m1;
    m1[F[1][1]] = 'R'; m1[R[1][1]] = 'B'; m1[B[1][1]] = 'O';
    m1[L[1][1]] = 'G'; m1[U[1][1]] = 'W'; m1[D[1][1]] = 'Y';
    
    for (int t = 0; t < 6; t++)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                faces[t][i][j] = m1[faces[t][i][j]];
    
    map<string, int> m2;
    m2["GOW"] = 0; m2["BOW"] = 1; m2["BRW"] = 2;
    m2["GRW"] = 3; m2["GOY"] = 4; m2["BOY"] = 5;
    m2["BRY"] = 6; m2["GRY"] = 7;
    m2["OW"] = 0; m2["BW"] = 1; m2["RW"] = 2; m2["GW"] = 3;
    m2["GO"] = 4; m2["BO"] = 5; m2["BR"] = 6; m2["GR"] = 7;
    m2["OY"] = 8; m2["BY"] = 9; m2["RY"] = 10; m2["GY"] = 11;
    
    map<int, char> m3c;
    m3c[0] = 'O'; m3c[1] = 'B'; m3c[2] = 'R'; m3c[3] = 'G';
    m3c[4] = 'O'; m3c[5] = 'B'; m3c[6] = 'R'; m3c[7] = 'G';
    
    map<int, char> m3s;
    m3s[0] = 'O'; m3s[1] = 'B'; m3s[2] = 'R'; m3s[3] = 'G';
    m3s[4] = 'O'; m3s[5] = 'O'; m3s[6] = 'R'; m3s[7] = 'R';
    m3s[8] = 'O'; m3s[9] = 'B'; m3s[10] = 'R'; m3s[11] = 'G';
    
    string str;
    char t, f; ull pos, idx, ori;
    C = 0, S = 0;
    
    pos = 0;
    str = ""; str += U[0][0]; str += B[0][2]; str += L[0][0]; sort(str.begin(), str.end());
    idx = m2[str]; t = m3c[idx];
    if (U[0][0] == t) f = 'U'; else if (B[0][2] == t) f = 'B'; else f = 'L';
    ori = orientation_corner_cubie(pos, f);
    C |= (pos + ori * 8ULL) << (idx * 5);
    
    pos = 1;
    str = ""; str += U[0][2]; str += R[0][2]; str += B[0][0]; sort(str.begin(), str.end());
    idx = m2[str]; t = m3c[idx];
    if (U[0][2] == t) f = 'U'; else if (R[0][2] == t) f = 'R'; else f = 'B';
    ori = orientation_corner_cubie(pos, f);
    C |= (pos + ori * 8ULL) << (idx * 5);
    
    pos = 2;
    str = ""; str += F[0][2]; str += U[2][2]; str += R[0][0]; sort(str.begin(), str.end());
    idx = m2[str]; t = m3c[idx];
    if (F[0][2] == t) f = 'F'; else if (U[2][2] == t) f = 'U'; else f = 'R';
    ori = orientation_corner_cubie(pos, f);
    C |= (pos + ori * 8ULL) << (idx * 5);
    
    pos = 3;
    str = ""; str += F[0][0]; str += U[2][0]; str += L[0][2]; sort(str.begin(), str.end());
    idx = m2[str]; t = m3c[idx];
    if (F[0][0] == t) f = 'F'; else if (U[2][0] == t) f = 'U'; else f = 'L';
    ori = orientation_corner_cubie(pos, f);
    C |= (pos + ori * 8ULL) << (idx * 5);
    
    pos = 4;
    str = ""; str += L[2][0]; str += B[2][2]; str += D[2][0]; sort(str.begin(), str.end());
    idx = m2[str]; t = m3c[idx];
    if (L[2][0] == t) f = 'L'; else if (B[2][2] == t) f = 'B'; else f = 'D';
    ori = orientation_corner_cubie(pos, f);
    C |= (pos + ori * 8ULL) << (idx * 5);
    
    pos = 5;
    str = ""; str += R[2][2]; str += B[2][0]; str += D[2][2]; sort(str.begin(), str.end());
    idx = m2[str]; t = m3c[idx];
    if (R[2][2] == t) f = 'R'; else if (B[2][0] == t) f = 'B'; else f = 'D';
    ori = orientation_corner_cubie(pos, f);
    C |= (pos + ori * 8ULL) << (idx * 5);
    
    pos = 6;
    str = ""; str += F[2][2]; str += R[2][0]; str += D[0][2]; sort(str.begin(), str.end());
    idx = m2[str]; t = m3c[idx];
    if (F[2][2] == t) f = 'F'; else if (R[2][0] == t) f = 'R'; else f = 'D';
    ori = orientation_corner_cubie(pos, f);
    C |= (pos + ori * 8ULL) << (idx * 5);
    
    pos = 7;
    str = ""; str += F[2][0]; str += L[2][2]; str += D[0][0]; sort(str.begin(), str.end());
    idx = m2[str]; t = m3c[idx];
    if (F[2][0] == t) f = 'F'; else if (L[2][2] == t) f = 'L'; else f = 'D';
    ori = orientation_corner_cubie(pos, f);
    C |= (pos + ori * 8ULL) << (idx * 5);
    /* coner cubies */
    
    
    pos = 0;
    str = ""; str += U[0][1]; str += B[0][1]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = U[0][1] == t? 'U': 'B';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 1;
    str = ""; str += U[1][2]; str += R[0][1]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = U[1][2] == t? 'U': 'R';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 2;
    str = ""; str += U[2][1]; str += F[0][1]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = U[2][1] == t? 'U': 'F';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 3;
    str = ""; str += U[1][0]; str += L[0][1]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = U[1][0] == t? 'U': 'L';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 4;
    str = ""; str += L[1][0]; str += B[1][2]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = L[1][0] == t? 'L': 'B';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 5;
    str = ""; str += R[1][2]; str += B[1][0]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = R[1][2] == t? 'R': 'B';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 6;
    str = ""; str += F[1][2]; str += R[1][0]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = F[1][2] == t? 'F': 'R';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 7;
    str = ""; str += F[1][0]; str += L[1][2]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = F[1][0] == t? 'F': 'L';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 8;
    str = ""; str += B[2][1]; str += D[2][1]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = B[2][1] == t? 'B': 'D';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 9;
    str = ""; str += R[2][1]; str += D[1][2]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = R[2][1] == t? 'R': 'D';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 10;
    str = ""; str += F[2][1]; str += D[0][1]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = F[2][1] == t? 'F': 'D';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    
    pos = 11;
    str = ""; str += L[2][1]; str += D[1][0]; if (str[0] > str[1]) swap(str[0], str[1]);
    idx = m2[str]; t = m3s[idx]; f = L[2][1] == t? 'L': 'D';
    ori = orientation_side_cubie(pos, f);
    S |= (pos + ori * 12ULL) << (idx * 5);
    /* side cubies */

#undef F
#undef R
#undef B
#undef L
#undef U
#undef D
}

#endif /* cube_h */
