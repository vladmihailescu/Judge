#include <fstream>
using namespace std;
ifstream  fin("ghiozdan.in");
ofstream  fout("ghiozdan.out");
int d,k,t,lo,hi,mi,a[100010],ok(int);
int main()
{
    fin>>d>>k>>t;
    for(int i=1;i<=k;i++)
        fin>>a[i];
    a[k+1]=d;
    lo=0;
    hi=d+1;
    while(hi-lo>1)
    {
        mi=(lo+hi)/2;
        if(ok(mi))
            hi=mi;
        else
            lo=mi;
    }
    fout<<hi;
    return 0;
}
int ok(int g)
{
    int r=t;
    for(int i=0;i<=k;i++)
    {
        if(a[i+1]-a[i]>g)
            r-=a[i+1]-a[i]-g;
        if(r<0)
            return 0;
    }
    return 1;
}