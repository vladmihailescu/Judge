#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define mp make_pair
#define f first
#define s second
#define pb push_back

ifstream fin("mana.in");
ofstream fout("mana.out");

vector <pair<double,double> >v;

inline long double dist(double x, double y, double a, double b)
{
    return (x-a)*(x-a)+(y-a)*(y-a);
}

int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int n,k,i;

    int ans = 200000;
    fin>>n>>k;
    for(i=1; i<=n; ++i)
    {
        int a,b;
        fin>>a>>b;
        v.pb(mp(a,b));
    }
    for(i=1; i<=ans; i<<=1);
    for( ; i; i>>=1)
    if(ans-i>0)
    {
        long double now =  (ans-i)*(ans-i);
        int ok = 1;
        for(auto it:v)
        {
            for(auto it2:v)
            {
                long double x = (double)(it.f+it2.f)/2;
                long double y = (double)(it.s+it2.s)/2;
                int curr = 0;
                for(auto it3:v)
                    if(dist(x,y,it3.f,it3.s)<now)
                        ++curr;
                if(curr>=k)
                {
                    ans-=i;
                    ok=0;
                }
                if(!ok)
                    break;
            }
            if(!ok)
                break;
        }
    }
    fout<<ans;
}