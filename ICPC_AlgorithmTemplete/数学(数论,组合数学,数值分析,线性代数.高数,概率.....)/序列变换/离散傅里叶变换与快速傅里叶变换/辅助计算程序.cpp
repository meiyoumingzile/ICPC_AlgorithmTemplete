#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cd complex<double>
const int MAX=10000;
const double PI=3.1415926;

cd getWn(int n){
    double k=2*PI/n;
    cd ans(cos(k),-sin(k));
    return ans;
}

int main(){
    int i,j,k,N,n;
    cd wn,wnk,e,o;
    double a,b;
    while(1){
        printf("输出wn的k次方:\n");
        scanf("%d%d",&n,&k);
        wn=getWn(n);
        wnk=pow(wn,k);
        printf("分别输入偶数和奇数的复数对：E,O\n");
        scanf("%lf%lf",&a,&b);
        e.real()=a;
        e.imag()=b;
        scanf("%lf%lf",&a,&b);
        o.real()=a;
        o.imag()=b;
        cd ans=e+wnk*o;
        printf("%.10lf %.10lf\n",ans.real(),ans.imag());
    }
    return 0;
}
