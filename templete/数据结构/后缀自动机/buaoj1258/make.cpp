#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

char str1[MAX],str2[MAX];
void rands(char *s,int n){//n小于1e5
    memset(s,0,sizeof(s));
    for(int i=0;i<n;i++){
        s[i]=rand()%26+'a';
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    freopen("test4.in","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    srand(time(NULL));//有的OJ不能加这句话
	rg int i,n,len,k;
    n=10;
    len=1e5;
    k=n;
    printf("%d\n",n);
    while(n>k){
        rands(str1,len);
        rands(str2,len/4);
        printf("%s\n%s\n",str1,str2);
        n--;
    }
    while(n--){
        rands(str1,len);
        rands(str2,len);
        printf("%s\n%s\n",str1,str2);
    }

return 0;
}
/*
sdssdsdaasdsadsaddawdadsads
sadsssasdsssssssssssssssssssssssssssssssss
*/
