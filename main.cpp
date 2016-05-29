#include <iostream>
#include <string>
#include <queue>

enum TextureType { TT_Blue, TT_Green, TT_Yellow };
struct Texture {
    TextureType type;
    int num;
    Texture( TextureType tt, int n ) : type(tt) , num(n) {}
    std::string toString() {
        char buf[20];
        sprintf( buf, "(%s, %02d)",
                 type == TT_Blue ? "B" : type == TT_Green ? "G" : "Y", num );
        return buf;
    }
    void ripOff( int n ) { num -= n; }
};

#define BT( num ) Texture( TextureType::TT_Blue, num )
#define GT( num ) Texture( TextureType::TT_Green, num )
#define YT( num ) Texture( TextureType::TT_Yellow, num )
#define isG( t ) ( t.type == TextureType::TT_Green )
#define isB( t ) ( t.type == TextureType::TT_Blue )
#define isY( t ) ( t.type == TextureType::TT_Yellow )
#define eq(t1,t2) ( t1.type == t2.type )

#define isXXX(t1,t2,t3,x1,x2,x3) ( is##x1(t1) && is##x2(t2) && is##x3(t3) )
#define isBBB(t1,t2,t3) isXXX(t1,t2,t3,B,B,B)
#define isGGG(t1,t2,t3) isXXX(t1,t2,t3,G,G,G)
#define isYYY(t1,t2,t3) isXXX(t1,t2,t3,Y,Y,Y)
#define is3Triple(t1,t2,t3) (\
    isBBB(t1,t2,t3)||\
    isGGG(t1,t2,t3)||\
    isYYY(t1,t2,t3))
#define isBBG(t1,t2,t3) isXXX(t1,t2,t3,B,B,G)
#define isBBY(t1,t2,t3) isXXX(t1,t2,t3,B,B,Y)
#define isGGB(t1,t2,t3) isXXX(t1,t2,t3,G,G,B)
#define isGGY(t1,t2,t3) isXXX(t1,t2,t3,G,G,Y)
#define isYYB(t1,t2,t3) isXXX(t1,t2,t3,Y,Y,B)
#define isYYG(t1,t2,t3) isXXX(t1,t2,t3,Y,Y,G)
#define is3Double(t1,t2,t3) (!is3Triple(t1,t2,t3)&&eq(t1,t2))
#define isBGY(t1,t2,t3) isXXX(t1,t2,t3,B,G,Y)
#define isBYG(t1,t2,t3) isXXX(t1,t2,t3,B,Y,G)
#define isYGB(t1,t2,t3) isXXX(t1,t2,t3,Y,G,B)
#define isYBG(t1,t2,t3) isXXX(t1,t2,t3,Y,B,G)
#define isGBY(t1,t2,t3) isXXX(t1,t2,t3,G,B,Y)
#define isGYB(t1,t2,t3) isXXX(t1,t2,t3,G,Y,B)
#define is3Single(t1,t2,t3) (\
    isBGY(t1,t2,t3)||\
    isBYG(t1,t2,t3)||\
    isYGB(t1,t2,t3)||\
    isYBG(t1,t2,t3)||\
    isGBY(t1,t2,t3)||\
    isGYB(t1,t2,t3))

#define isXX(t1,t2,x1,x2) ( is##x1(t1) && is##x2(t2) )
#define isBB(t1,t2) isXX(t1,t2,B,B)
#define isGG(t1,t2) isXX(t1,t2,G,G)
#define isYY(t1,t2) isXX(t1,t2,Y,Y)
#define is2Double(t1,t2) (\
    isBB(t1,t2)||\
    isGG(t1,t2)||\
    isYY(t1,t2))
#define isBG(t1,t2) isXX(t1,t2,B,G)
#define isGB(t1,t2) isXX(t1,t2,G,B)
#define isBY(t1,t2) isXX(t1,t2,B,Y)
#define isYB(t1,t2) isXX(t1,t2,Y,B)
#define isGY(t1,t2) isXX(t1,t2,G,Y)
#define isYG(t1,t2) isXX(t1,t2,Y,G)
#define is2Single(t1,t2) (!(is2Double(t1,t2)))

#define min(a,b) ((a)<(b)?(a):(b))
#define MIN(a,b,c) min(min(a,b),min(b,c))

inline void clean(std::queue<Texture> &q) {
    if (q.empty()) { return; }
    if(q.front().num == 0) {
        q.pop();
    }
}

void print( const std::queue<Texture> &q0,
            const std::string &before = "",
            const std::string &after = "\n" )
{
    std::cout << before;
    std::queue<Texture> q = q0;
    while( !q.empty() ) {
        Texture t = q.front();
        std::cout << "\t" << t.toString();
        q.pop();
    }
    std::cout << after;
}

int on3Triple(std::queue<Texture> &qx1, std::queue<Texture> &qx2, std::queue<Texture> &qx3);
int on3Double(std::queue<Texture> &qx1, std::queue<Texture> &qx2, std::queue<Texture> &qy );
int on3Single(std::queue<Texture> &qx,  std::queue<Texture> &qy,  std::queue<Texture> &qz );
int on2Double(std::queue<Texture> &qx1, std::queue<Texture> &qx2);
int on2Single(std::queue<Texture> &qx,  std::queue<Texture> &qy);
int on1(std::queue<Texture> &q);

int main ( int argc, char **argv )
{
    std::queue<Texture> t1, t2, t3;

    t1.push( BT(45) ); t1.push( YT(10) );
    t2.push( GT(10) ); t2.push( BT(20) ); t2.push( YT(34) );
    t3.push( YT(28) ); t3.push( BT(12) ); t3.push( GT(17) );

    int cnt = 0;
    while (!t1.empty() || !t2.empty() || !t3.empty()) {
        print(t1, "\n\nt1");
        print(t2, "t2");
        print(t3, "t3");

        if (!t1.empty() && !t2.empty() && !t3.empty()) {
            if (is3Triple(t1.front(), t2.front(), t3.front())) { cnt += on3Triple(t1, t2, t3); continue; }
            if (is3Single(t1.front(), t2.front(), t3.front())) { cnt += on3Single(t1, t2, t3); continue; }
            if (is3Double(t1.front(), t2.front(), t3.front())) { cnt += on3Double(t1, t2, t3); continue; }
            if (is3Double(t1.front(), t3.front(), t2.front())) { cnt += on3Double(t1, t3, t2); continue; }
            if (is3Double(t2.front(), t3.front(), t1.front())) { cnt += on3Double(t2, t3, t1); continue; }
        }

        if (t1.empty() && t2.empty()) { cnt += on1(t3); continue; }
        if (t1.empty() && t3.empty()) { cnt += on1(t2); continue; }
        if (t2.empty() && t3.empty()) { cnt += on1(t1); continue; }

        if (t1.empty()) {
            if(is2Double(t2.front(),t3.front())){
                cnt += on2Double(t2, t3); continue;
            } else {
                cnt += on2Single(t2, t3); continue;
            }
        }
        if (t2.empty()) {
            if(is2Double(t1.front(),t3.front())){
                cnt += on2Double(t1, t3); continue;
            } else {
                cnt += on2Single(t1, t3); continue;
            }
        }
        if (t3.empty()) {
            if(is2Double(t1.front(),t2.front())){
                cnt += on2Double(t1, t2); continue;
            } else {
                cnt += on2Single(t1, t2); continue;
            }
        }
        std::cout << "you are fucked!\n"; break;
    }
    std::cout << "num is " << cnt << std::endl;

    return 0;
}

int on3Triple(std::queue<Texture> &qx1, std::queue<Texture> &qx2, std::queue<Texture> &qx3)
{
    int m3 = MIN(qx1.front().num, qx2.front().num, qx3.front().num);
    if (qx1.front().num == m3) { qx1.front().ripOff(m3); clean(qx1); return m3; }
    if (qx2.front().num == m3) { qx2.front().ripOff(m3); clean(qx2); return m3; }
    if (qx3.front().num == m3) { qx3.front().ripOff(m3); clean(qx3); return m3; }
    std::cout << "\t\t\t1/3: " << m3 << std::endl;
}
int on3Double(std::queue<Texture> &qx1, std::queue<Texture> &qx2, std::queue<Texture> &qy)
{
    int m3 = MIN(qx1.front().num, qx2.front().num, qy.front().num);
    qy.front().ripOff(m3); clean(qy);
    if (qx1.front().num < qx2.front().num ) {
        qx1.front().ripOff(m3); clean(qx1);
    } else {
        qx2.front().ripOff(m3); clean(qx2);
    }
    std::cout << "\t\t\t2/3: " << m3 << std::endl;
    return m3;
}
int on3Single(std::queue<Texture> &qx, std::queue<Texture> &qy, std::queue<Texture> &qz)
{
    int m3 = MIN(qx.front().num, qy.front().num, qz.front().num);
    qx.front().ripOff(m3); clean(qx);
    qy.front().ripOff(m3); clean(qy);
    qz.front().ripOff(m3); clean(qz);
    std::cout << "\t\t\t3/3: " << m3 << std::endl;
    return m3;
}
int on2Double(std::queue<Texture> &qx1, std::queue<Texture> &qx2)
{
    int m2 = min(qx1.front().num, qx2.front().num);
    if (qx1.front().num == m2) { qx1.front().ripOff(m2); clean(qx1); return m2; }
    if (qx2.front().num == m2) { qx2.front().ripOff(m2); clean(qx2); return m2; }
    std::cout << "\t\t\t1/2: " << m2 << std::endl;
}
int on2Single(std::queue<Texture> &qx, std::queue<Texture> &qy)
{
    int m2 = min(qx.front().num, qy.front().num);
    qx.front().ripOff(m2); clean(qx);
    qy.front().ripOff(m2); clean(qy);
    std::cout << "\t\t\t2/2: " << m2 << std::endl;
    return m2;
}
int on1(std::queue<Texture> &q)
{
    int cnt = 0;
    while (!q.empty()) {
        cnt += q.front().num;
        q.pop();
    }
    std::cout << "\t\t\t1/1: " << cnt << std::endl;
    return cnt;
}
