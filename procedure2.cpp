#include <iostream>
#include <string>
#include <queue>
#include <vector>

#define ORDER(a,b) (((a)<(b))?1:((a)==(b))?0:-1)
#define Ipij(p,i,j) (I[p][i][j] = ORDER(v##p##i, v##p##j))
#define enumerateI(a,b,c,d,e,f,g,h,i) \
    do { \
        int v11=a, v12=b, v13=c; \
        int v21=d, v22=e, v23=f; \
        int v31=g, v32=h, v33=i; \
                                 \
        Ipij(1,1,1); Ipij(1,1,2); Ipij(1,1,3); \
        Ipij(1,2,1); Ipij(1,2,2); Ipij(1,2,3); \
        Ipij(1,3,1); Ipij(1,3,2); Ipij(1,3,3); \
                                               \
        Ipij(2,1,1); Ipij(2,1,2); Ipij(2,1,3); \
        Ipij(2,2,1); Ipij(2,2,2); Ipij(2,2,3); \
        Ipij(2,3,1); Ipij(2,3,2); Ipij(2,3,3); \
                                               \
        Ipij(3,1,1); Ipij(3,1,2); Ipij(3,1,3); \
        Ipij(3,2,1); Ipij(3,2,2); Ipij(3,2,3); \
        Ipij(3,3,1); Ipij(3,3,2); Ipij(3,3,3); \
    } while(false)

struct Moderator {
    std::vector<int[4][4][4]> Is;
    std::vector<int[4][4][4]> Ds;
};

void mock(int T[4][4], int R[4][4][4], int S[4][4], int I[4][4][4], Moderator &m);

int main()
{
    // 已知 T[i][p]（耗时）, R[p][i][j]（顺序关系）
    // 枚举 I[p][i][j]（处理顺序），计算 S[i]+T[i] 的最大值，记为 D[k], k = 1..p*i*j
    // 如果这个 I[p][i][j] 不满足约束，D[k] = infinity
    // 找最小的 D[k]，打印输出处理流程

    Moderator mod;

    // T_{ip}: time duration of *i*th texture on *p*th machine
    int T[4][4];
    T[1][1] =  0; T[2][1] = 10; T[3][1] = 17;
    T[1][2] = 45; T[2][2] = 20; T[3][2] = 12;
    T[1][3] = 10; T[2][3] = 34; T[3][3] = 28;

    // R_{ipq}: dependency relationship,
    //  if *i*th texture goes into *p*th machine before *q*th ---> 1, else ---> 0
    int R[4][4][4];
    R[1][1][1] = 0; R[1][1][2] = 0; R[1][1][3] = 0;
    R[1][2][1] = 0; R[1][2][2] = 0; R[1][2][3] = 1;
    R[1][3][1] = 0; R[1][3][2] = 0; R[1][3][3] = 0;

    R[2][1][1] = 0; R[2][1][2] = 1; R[2][1][3] = 1;
    R[2][2][1] = 0; R[2][2][2] = 0; R[2][2][3] = 1;
    R[2][3][1] = 0; R[2][3][2] = 0; R[2][3][3] = 0;

    R[3][1][1] = 0; R[3][1][2] = 0; R[3][1][3] = 0;
    R[3][2][1] = 0; R[3][2][2] = 0; R[3][2][3] = 1;
    R[3][3][1] = 0; R[3][3][2] = 0; R[3][3][3] = 0;

    // S_{ip}: start time of *i*th texture on *p*th machine (platform)
    int S[4][4];

    // I_{pij}: Indicator of processing procedure,
    //  if *i*th texture goes before *j*th on *p*th platform ---> 1, else ---> 0
    //  we brute-forcely try all possibilities: 3 * 3 * 3
    int I[4][4][4];

    // 3 * 3 * 3 possibilities

    // (S[i][p] + T[i][p] - S[j][p]) * I[p][i][j] <= 0
    // 6 combinations: 1,2,3; 1,3,2; 2,1,3; 2,3,1; 3,1,2; 3,2,1
    // expand to 36 combinations

    enumerateI( 3,2,1,  1,2,3,  1,3,2); mock(T, R, S, I, mod);
    return 0;
}

void mock(int T[4][4], int R[4][4][4], int S[4][4], int I[4][4][4], Moderator &m)
{
    for (int p = 1; p <= 3; ++p) {
        for (int i = 1; i <= 3; ++i) {
            for (int j = 1; j <= 3; ++j) {
                std::cout << "\t" << I[p][i][j];
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }
}