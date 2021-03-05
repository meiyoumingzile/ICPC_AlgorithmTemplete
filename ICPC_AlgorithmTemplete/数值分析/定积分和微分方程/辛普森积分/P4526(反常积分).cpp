#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-10
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

double a;
double ff(double x){//被积函数
    if(x==0)//0处极限是0
        return 0;
    double b=a/x-x;
    return pow(x,b);
}
double simpson(double l,double r){
    return (ff(l)+ff(r)+4*ff((r+l)/2))*(r-l)/6;
}
double binsim(double l,double r,double pre){
    double m=(l+r)/2;
    double ml=simpson(l,m);
    double mr=simpson(m,r);
    if(fabs(ml+mr-pre)<=inf)
        return  (ml+mr+pre)/2;
    return  binsim(l,m,ml)+binsim(m,r,mr);
}
//以上是辛普森法计算过程

int main(int argc,char *argv[]){
    cin>>a;
    if(a<0){//a<0时，函数在x=0处发散
        printf("orz\n");
    }else{
        int r=15;
        printf("%.5lf\n",binsim(0,r,simpson(0,r)));
    }
return 0;
}

