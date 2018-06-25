#include <iostream>

using namespace std;

int main()
{
    int mers,g,ghiozdan,i,mancat,v[100001],d,k,t;
    cin>>d>>k>>t;
    for(i=1; i<=k; i++)
        cin>>v[i];
    mers=0;
    i=1;
    mancat=0;
    g=0;
    ghiozdan=0;
    while(mers<d)
    {
        if(mancat==t-1)
        {
            mancat=0;
            if(g==0)
                ghiozdan++;
            else
                g--;
        }
        else
            mancat++;
        mers++;
        if(i<=k)
            if(v[i]==mers)
            {
                g=ghiozdan;
                i++;
            }
    }
    cout<<ghiozdan;
    return 0;
}