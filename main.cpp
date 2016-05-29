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

#define B(num) Texture( TextureType::TT_Blue, num )
#define G(num) Texture( TextureType::TT_Green, num )
#define Y(num) Texture( TextureType::TT_Yellow, num )

#define eq(t1,t2) (t1.type == t2.type)
#define is3Triple(t1,t2,t3) (eq(t1,t2)&&eq(t1,t3))
#define is3Double(t1,t2,t3) (eq(t1,t2)&&!eq(t1,t3))
#define is3Single(t1,t2,t3) (!eq(t1,t2)&&!eq(t1,t3)&&!eq(t2,t3))
#define is2Double(t1,t2) (eq(t1,t2))
#define is2Single(t1,t2) (!eq(t1,t2))

#define min(a,b) ((a)<(b)?(a):(b))
#define MIN(a,b,c) min(min(a,b),min(b,c))

inline void clean(std::queue<Texture> &q) {
    if(!q.empty()&&q.front().num == 0) {
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
        std::cout << "\t" << q.front().toString();
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

    t1.push( B(45) ); t1.push( Y(10) );
    t2.push( G(10) ); t2.push( B(20) ); t2.push( Y(34) );
    t3.push( Y(28) ); t3.push( B(12) ); t3.push( G(17) );

    int cost = 0;
    while (!t1.empty() || !t2.empty() || !t3.empty()) {
        print(t1, "\n\nt1");
        print(t2, "t2");
        print(t3, "t3");

        if (!t1.empty() && !t2.empty() && !t3.empty()) {
            if (is3Triple(t1.front(), t2.front(), t3.front())) { cost += on3Triple(t1, t2, t3); continue; }
            if (is3Single(t1.front(), t2.front(), t3.front())) { cost += on3Single(t1, t2, t3); continue; }
            if (is3Double(t1.front(), t2.front(), t3.front())) { cost += on3Double(t1, t2, t3); continue; }
            if (is3Double(t1.front(), t3.front(), t2.front())) { cost += on3Double(t1, t3, t2); continue; }
            if (is3Double(t2.front(), t3.front(), t1.front())) { cost += on3Double(t2, t3, t1); continue; }
        }

        if (t1.empty() && t2.empty()) { cost += on1(t3); continue; }
        if (t1.empty() && t3.empty()) { cost += on1(t2); continue; }
        if (t2.empty() && t3.empty()) { cost += on1(t1); continue; }

#define DOUBLE_SINGLE(t1,t2,t3) \
        if (t1.empty()) { \
            if(is2Double(t2.front(),t3.front())){ \
                cost += on2Double(t2, t3); continue; \
            } else { \
                cost += on2Single(t2, t3); continue; \
            } \
        }
        DOUBLE_SINGLE(t1,t2,t3)
        DOUBLE_SINGLE(t2,t1,t3)
        DOUBLE_SINGLE(t3,t1,t2)
#undef DOUBLE_SINGLE
    }
    std::cout << "\n** Used " << cost << " minutes. **\n";

    return 0;
}

int on3Triple(std::queue<Texture> &qx1, std::queue<Texture> &qx2, std::queue<Texture> &qx3)
{
    int m3 = MIN(qx1.front().num, qx2.front().num, qx3.front().num);
    if (qx1.front().num == m3) { qx1.front().ripOff(m3); clean(qx1); return m3; }
    if (qx2.front().num == m3) { qx2.front().ripOff(m3); clean(qx2); return m3; }
    if (qx3.front().num == m3) { qx3.front().ripOff(m3); clean(qx3); return m3; }
    std::cout << "\t\t\t\t1/3: " << m3 << std::endl;
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
    std::cout << "\t\t\t\t2/3: " << m3 << std::endl;
    return m3;
}
int on3Single(std::queue<Texture> &qx, std::queue<Texture> &qy, std::queue<Texture> &qz)
{
    int m3 = MIN(qx.front().num, qy.front().num, qz.front().num);
    qx.front().ripOff(m3); clean(qx);
    qy.front().ripOff(m3); clean(qy);
    qz.front().ripOff(m3); clean(qz);
    std::cout << "\t\t\t\t3/3: " << m3 << std::endl;
    return m3;
}
int on2Double(std::queue<Texture> &qx1, std::queue<Texture> &qx2)
{
    int m2 = min(qx1.front().num, qx2.front().num);
    if (qx1.front().num == m2) { qx1.front().ripOff(m2); clean(qx1); return m2; }
    if (qx2.front().num == m2) { qx2.front().ripOff(m2); clean(qx2); return m2; }
    std::cout << "\t\t\t\t1/2: " << m2 << std::endl;
}
int on2Single(std::queue<Texture> &qx, std::queue<Texture> &qy)
{
    int m2 = min(qx.front().num, qy.front().num);
    qx.front().ripOff(m2); clean(qx);
    qy.front().ripOff(m2); clean(qy);
    std::cout << "\t\t\t\t2/2: " << m2 << std::endl;
    return m2;
}
int on1(std::queue<Texture> &q)
{
    int cnt = 0;
    while (!q.empty()) {
        cnt += q.front().num;
        q.pop();
    }
    std::cout << "\t\t\t\t1/1: " << cnt << std::endl;
    return cnt;
}