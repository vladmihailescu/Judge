#include <iostream>
#include <fstream>
using namespace std;
ifstream f("ghiozdan.in");
ofstream x("ghiozdan.out");
int main()
{
    int d,k,t,a[100001],i,g,dmax=0,dmax2=0;
f>>d>>k>>t;
if(t==0)
    if(k==0)
{g=d;
x<<g;
    return 0;
}
a[0]=0;
a[k+1]=d;

for(i=1;i<=k;i++)
    f>>a[i];
for(i=1;i<=k+1;i++)
    if(a[i]-a[i-1]>dmax)
    dmax=a[i]-a[i-1];


for(i=1;i<=k+1;i++)
    if((a[i]-a[i-1]>dmax2)&&(a[i]-a[i-1]<=dmax))
    dmax2=a[i]-a[i-1];
g=dmax2;
x<<g;
    return 0;

}