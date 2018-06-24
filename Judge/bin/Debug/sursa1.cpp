#include <iostream>
#include <fstream>
using namespace std;

int main()
{   int d,k,t,g,a[100000],mx,i; 
    ifstream fin("ghiozdan.in"); 
    ofstream fout("ghiozdan.out");
    fin>>d>>k>>t; 
    for(i=1;i<=k;i++)
        fin>>a[i]; 
    //pp ca t=0 dist max va fi dist max intre 2 magazine consecutive 
    mx=a[1]; 
    a[k+1]=d;
    for(i=1;i<=k;i++)
        if(a[i+1]-a[i]>mx) 
        mx=a[i+1]-a[i];
    fout<<mx;
    
    return 0;
}