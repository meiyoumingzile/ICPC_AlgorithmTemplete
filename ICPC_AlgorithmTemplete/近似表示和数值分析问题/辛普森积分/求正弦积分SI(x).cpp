#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-10
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;


double ff(double x){//被积函数
    if(x==0){
        return 1;
    }
    return sin(x)/x;
}
double simpson(double l,double r){
    return (ff(l)+ff(r)+4*ff((r+l)/2))*(r-l)/6;
}
double binsim(double l,double r,double pre){
    double m=(l+r)/2;
    double ml=simpson(l,m);
    double mr=simpson(m,r);
    if(fabs(ml+mr-pre)<=inf)
        return  ml+mr;
    return  binsim(l,m,ml)+binsim(m,r,mr);
}
//以上是辛普森法计算过程

int main(int argc,char *argv[]){
    double l,r;
    cin>>l>>r;
    printf("%.6lf\n",binsim(l,r,simpson(l,r)));
return 0;
}

