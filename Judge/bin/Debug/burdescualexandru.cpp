#include<fstream>
#include<algorithm>
using namespace std;
int d,k,t;
int a[100005];
int j;
ifstream fin("ghiozdan.in");
ofstream fout("ghiozdan.out");
int main()
{
    fin>>d>>k>>t;
    for(int i=1;i<=k;i++)
    {
        fin>>a[i];
    }
    k++;
    a[k]=d;
    for(j=k;j>=1;j--)
    {
        a[j]=a[j]-a[j-1];
    }
    sort(a+1,a+k+1);
    int r=k;
    int cat;
    while(t>0)
    {
        if(a[r]==a[r-1])
        {
            r--;
        }
        else
        {
            if(t>(a[r]-a[r-1])*(k-r+1))
            {
                t=t-(a[r]-a[r-1])*(k-r+1);
            }
            else
            {
                cat=t/(k-r+1);
                t=0;
            }
        }
    }
    fout<<a[r]-cat;
    fin.close();
    fout.close();
    return 0;
}