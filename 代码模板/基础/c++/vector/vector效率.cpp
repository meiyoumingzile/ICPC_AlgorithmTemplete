#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=10000010;
const int mod=1e9+7;
int p[MAX],q[MAX];

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,T,a,b;

	for(i=0;i<MAX;i++){
        p[i]=i;
	}

	cin>>a>>b;
	printf("%d\n",a+b);
return 0;
}

