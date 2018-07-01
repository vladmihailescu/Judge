#include <iostream>

using namespace std;

int main(){
int l,i,n,pf,lmax,v[1001];
l=0;
lmax=0;
cin>>n;
for(i=1;i<=n;i++){
    cin>>v[i];
}
for(i=1;i<=n-1;i++){
    if(v[i]+v[i+1]==0){
        l++;
    }
    else
    if(l>lmax&&lmax!=l){
        lmax=l;
        pf=i;
        l=1;
    }

}
if(l>lmax&&lmax!=l){
    lmax=l;
    pf=i;
}
cout<<pf-lmax+1<<" "<<pf;
return 0;
}