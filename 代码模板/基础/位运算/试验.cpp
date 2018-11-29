#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
int getAi(int a,int i){//二进制下a的第i位,下标从1开始
    return (a>>(i-1))&1;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n;
	for(i=0;i<20;i++)
        printf("%d",getAi(2212,i));
return 0;
}

