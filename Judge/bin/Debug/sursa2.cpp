#include<fstream>
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
    int c1=0;
    int c2=d;
    int mij;
    int ct;
    int ok;
    while(c1<c2)
    {
        ct=t;
        mij=(c1+c2)/2;
        for(int i=k;i>=1;i--)
        {
            if(mij<a[i])
            {
                ct=ct-(a[i]-mij);
            }
        }
        if(ct>=0)
        {
           ok=mij;
           c2=mij-1;
        }
        else
        {
            c1=mij+1;
        }
    }
    fout<<ok;
    fin.close();
    fout.close();
    return 0;
}