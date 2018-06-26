#include <fstream>
#include <iomanip>
#include <math.h>
#include <climits>

using namespace std;

ifstream f("mana.in");
ofstream g("mana.out");

float midx[105*105], midy[105*105];
float dist[105*105];
float x[105], y[105];
int nr;
float d;
int n,k,i,j;
float a,aa,o,oo;
float aux;
int contor=0;
long long int Min=LLONG_MAX;

int main()
{
    f>>n>>k;

    for(i=1; i<=n; i++)
        f>>x[i]>>y[i];

    for(i=1; i<n; i++)
        for(j=i+1; j<=n; j++)
            if(x[i]>x[j])
            {
                swap(x[i],x[j]);
                swap(y[i],y[j]);
            }
            else if(x[i]==x[j] && y[i]>y[j])
            {
                swap(x[i],x[j]);
                swap(y[i],y[j]);
            }

    for(i=1; i<n; i++)
        for(j=i+1; j<=n; j++)
        {
            midx[++contor]=(x[i]+x[j])/2;
            midy[contor]=(y[i]+y[j])/2;

            a=x[i];
            o=y[i];
            aa=midx[contor];
            oo=midy[contor];

            dist[contor]=sqrt((a-aa)*(a-aa) + (o-oo)*(o-oo));
        }

    //g<<setprecision(3)<<fixed;
    for(i=1; i<=contor; i++)
    {
        //g<<midx[i]<<' '<<midy[i]<<' '<<dist[i]<<'\n';
        nr=0;
        aa=midx[i];
        oo=midy[i];
        for(j=1; j<=n; j++)
        {
            a=x[j];
            o=y[j];
            d=sqrt((a-aa)*(a-aa) + (o-oo)*(o-oo));
            if(d<=dist[i])
                nr++;
        }
        //g<<dist[i]<<' '<<nr<<'\n';
        if(nr>=k)
        {
            aux=dist[i];
            aux++;
            if(int(aux)<Min)
                Min=(int)aux;
        }
    }
    g<<Min<<'\n';
    return 0;
}