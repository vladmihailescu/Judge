#include <iostream>
#include <fstream>

using namespace std;
ifstream fin ("ghiozdan.in");
ofstream fout ("ghiozdan.out");

void quicksort (int st, int dr, int v[100001])
{
    int i=st, j=dr, pivot=v[(st+dr)/2], aux;
    while(i<=j)
    {
        while(v[i]>pivot)
            i++;
        while(v[j]<pivot)
            j--;
        if(i<=j)
        {
            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
            i++;
            j--;
        }
    }
    if(j>st)
        quicksort(st,j,v);
    if(i<dr)
        quicksort(i,dr,v);
}

int Pr(int t, int v[100002])
{
    int i, lungM, elemM,j;
    while(t)
    {
    i=1;
    while(v[i]==v[i+1])
        i++;
    lungM=i;
    elemM=v[i];
    if(lungM>t)
        return elemM;
    if(lungM*(elemM-v[i+1])>t)
        return elemM-t/lungM;
    for(j=1;j<=i;j++)
       {
           v[j]--;
           t--;
       }
    }
    return v[1];
}

int main()
{
    int d,k,t,x,v[100002],i,y=0;
    fin>>d>>k>>t;
    for(i=1;i<=k;i++)
    {
        fin>>x;
        v[i]=x-y;
        y=x;
    }
    k++;
    v[k]=d-y;
    quicksort(1,k,v);
    //for(i=1;i<=k;i++)
    //    cout<<v[i]<<" ";
    fout<<Pr(t,v);


    return 0;
}