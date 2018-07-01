#include <fstream>
#include <cmath>
#define ld long double
using namespace std;
ifstream f("mana.in");
ofstream g("mana.out");
const int NMax=105;
const ld eps=1e-9;
struct point
{
 ld x,y;
};
point a[NMax];
point C1,C2;
int n,k;
ld dist2(point A,point B)
{
 return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}
void center(point A,point B,ld r)
{
 ///2 * r trebuie sa fie mai mic decat dist(A,B)!!!
 if(A.y!=B.y)
 {
 ///constantele care ne usureaza calculul
 ld Cc=A.x*A.x-B.x*B.x+A.y*A.y-B.y*B.y;
 ld Ac=Cc/(2*(A.y-B.y));
 ld Bc=(A.x-B.x)/(A.y-B.y);
 ld C2c=A.x*A.x+B.x*B.x+A.y*A.y+B.y*B.y;
 ///EC DE GR2 in x0 (x-ul centrului cercului)
 ld a=2+2*Bc*Bc;
 ld b=(-2*A.x-2*B.x-4*Ac*Bc+2*A.y*Bc+2*B.y*Bc);
 ld c=C2c+2*Ac*Ac-2*A.y*Ac-2*B.y*Ac-2*r*r;
 ld sqrtDelta=sqrt(b*b-4*a*c);
 ld x01=(-b+sqrtDelta)/(2*a);
 ld y01=Ac-Bc*x01;
 ld x02=(-b-sqrtDelta)/(2*a);
 ld y02=Ac-Bc*x02;
 C1.x=x01;C1.y=y01;
 C2.x=x02;C2.y=y02;
 }
 else
 {
 ld x01=(A.x+B.x)/2;
 ld a=1;
 ld b=-2*A.y;
 ld c=A.x*A.x+x01*x01-2*x01*A.x-r*r+A.y*A.y;
 ld sqrtDelta=sqrt(b*b-4*a*c);
 ld y01=(-b-sqrtDelta)/(2*a);
 ld y02=(-b+sqrtDelta)/(2*a);
 C1.x=x01;C1.y=y01;
 C2.x=x01;C2.y=y02;
 }
}
bool inside(point C,ld r,point a)
{
 if((dist2(C,a)-r*r)<=eps)
 return 1;
 return 0;
}
bool verif(ld r)
{
 for(int i=1;i<=n;++i)
 for(int j=i+1;j<=n;++j)
 {
 if(i==j)
 continue;
 ld radius=r;
 if((2*r)*(2*r)-dist2(a[i],a[j])<0)
 continue;
 C1.x=0;C1.y=0;C2.x=0;C2.y=0;
 center(a[i],a[j],radius);
 int ans1=0;
 for(int t=1;t<=n;++t)
 if(inside(C1,r,a[t]))
 ++ans1;
 if(ans1>=k)
 return 1;
 int ans2=0;
 for(int t=1;t<=n;++t)
 if(inside(C2,r,a[t]))
 ++ans2;
 if(ans2>=k)
 return 1;
 }
 return 0;
}
int cautbin(int lo,int hi)
{
 int mid;
 while(lo<=hi)
 {
 mid=(lo+hi)/2;
 int ok1=verif(1.0*mid);
 int ok2=verif(1.0*(mid-1));
 if(ok1==1&&ok2==0)
 return mid;
 else
 if(ok1==1)
 hi=mid-1;
 else
 if(ok2==0)
 lo=mid+1;
 }
 return 0;
}
int main()
{
 f>>n>>k;
 for(int i=1;i<=n;++i)
 f>>a[i].x>>a[i].y;
 if(k==1)
 {
 g<<1<<'\n';
 return 0;
 }
 g<<cautbin(1,150000)<<'\n';
 return 0;
}