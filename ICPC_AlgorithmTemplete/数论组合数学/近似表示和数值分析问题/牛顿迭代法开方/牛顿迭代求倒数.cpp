#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
const double h=0x5f3759df;

int getDight(int n){
    int i;
    for(i=0;n!=0;n/=10,i++);
    return i;
}

double fen(double n){
    printf("%.14f\n",1/n);
    double i=0.0000089015,j;
    for(j=0;j<18;j++){
        printf("%.12f ",n*i);
        i=(2-n*i)*i;
    }
    return i;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    double n,m,t;
    ll a,i,j,k;
   while( cin>>n)
    printf("%.12f\n",fen(n));
return 0;
}
