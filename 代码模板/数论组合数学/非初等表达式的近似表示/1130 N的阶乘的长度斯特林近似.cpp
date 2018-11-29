#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
const int lim=1e5;
const double PI=3.141592653589;
const double E= 2.718281828459;
double Stirling(int n){
    double ans=log10(PI*2*n)/2;
    ans+=log10((double)n/E)*n;
    return ans+1.0;
}
double vio(int n){
    double i,ans=0;
    for(i=2;i<=n;i++){
        ans+=log10(i);
    }
    return ans+1;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j ,T,n;
    double ans=0;
    cin>>T;
    while(T--){
        scanf("%d",&n);
        if(n<lim){
            ans=vio(n);
        }else{
            ans=Stirling(n);
        }
        printf("%.0lf\n",floor(ans));
    }
return 0;
}
