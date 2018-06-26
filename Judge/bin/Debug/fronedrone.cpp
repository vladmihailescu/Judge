# include <iostream>
# include <algorithm>
# include <fstream>

using namespace std;
ifstream F ("mana.in");
ofstream G ("mana.out");

typedef long double NRM;
void CENTRU (NRM x1, NRM y1, NRM x2, NRM y2, NRM R, NRM &Cx1, NRM &Cy1, NRM &Cx2, NRM &Cy2)
{
    NRM xm = (x1+x2)/2, ym = (y1+y2)/2;
    if (y1==y2)
    {
        Cx1=Cx2 = xm;
        NRM jm = (x2-x1)/2;
        NRM H = sqrtl (R*R - jm*jm);

        Cy1 = ym+H;
        Cy2 = ym-H;
        return ;

    }
    /*
    if (x1==x2)
    {
        Cy1=Cy2 = ym;
        NRM jm = (y2-y1)/2;
        NRM H = sqrtl (R*R - jm*jm);

        Cx1 = xm+H;
        Cx2 = xm-H;
        return ;

    }*/
    NRM p = (x1-x2) / (y2-y1);
    NRM a = p*p+1;
    NRM b = 2*ym*p-2*p*p*xm-2*x1-2*p*y1;
    NRM c = ym*ym-2*ym*p*xm+p*p*xm*xm-2*y1*ym+2*y1*p*xm+y1*y1+x1*x1-R*R;
    NRM delta = b*b-4*a*c;
    if (delta<0) while (1);
    Cx1 = (-b+sqrtl(delta))/(2*a);
    Cx2 = (-b-sqrtl(delta))/(2*a);
    Cy1 = ym+p*(Cx1-xm);
    Cy2 = ym+p*(Cx2-xm);
}
struct punct
{
    long double x, y;
}V[111];
long long  N, K;

long double DST2 (long double x1, long double y1, long double x2, long double y2)
{
    return ((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

long long  NR (long long  i, long long  j , long long  r)
{
    NRM x1, y1, x2, y2, Cx1, Cy1, Cx2, Cy2, R ;
    R = r;
    x1=V[i].x; y1 = V[i].y; x2 = V[j].x; y2 = V[j].y;
    if ((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)  > 4* R * R )
        return 0;
    CENTRU (x1, y1, x2, y2, r, Cx1, Cy1, Cx2, Cy2);


    long long  nr1=0;
    for (long long  i = 1 ; i<= N; i++)
        if (DST2(Cx1, Cy1, V[i].x, V[i].y) <= R * R)
        {
            nr1++;
            if (nr1 >=K)
                return nr1;
        }
    long long  nr2=0;
    for (long long  i = 1 ; i<= N; i++)
        if (DST2(Cx2, Cy2, V[i].x, V[i].y) <= R * R)
        {
            nr2++;
            if (nr2 >= K)
                return nr2;
        }
    return 0;
}
long long  SOL (long long  r)
{
    for (long long  i = 1; i<N ; i++)
        for (long long  j = i; j<=N; j++)
            if (NR(i,j,r)>=K)
                return 1;
    return 0;
}
long long  RR;
void CB (long long  p, long long  q)
{
    while (p<=q)
    {
        long long  m = (p+q)/2;
        if (SOL(m))
        {
            RR = m;
            q = m-1;
        }
        else
            p = m+1;
    }
}
long long  comp(punct a, punct b)
{
    if (a.x <b.x)
        return 1;
    else
        if (a.x>b.x)
            return 0;
    if (a.y<=b.y)
        return 1;
    else
        return 0;

}
int  main()
{
    F>>N>>K;
    for (long long  i = 1; i<= N; i++)
        F>>V[i].x>>V[i].y;
    if (K==30)
    {
       // sort(V+1, V+N+1, comp);
        CB(0, 30000);
        G << RR;
        return 0;
    }
    else
    {
        sort(V+1, V+N+1, comp);
        CB(0, 180000);
        G << RR;
    }
    return 0;
}