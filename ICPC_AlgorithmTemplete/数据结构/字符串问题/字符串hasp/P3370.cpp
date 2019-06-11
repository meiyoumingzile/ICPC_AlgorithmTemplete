#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
#define dd double
typedef unsigned long long ull;
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

const ull base=255;
ull li[MAX];//ull类型可以自动取模
char s[MAX];
ull getHashKey(char *s){
    int i,len=strlen(s);
    ull ans=0;
    for(i=0;i<len;i++)
        ans=ans*base+ull(s[i]);
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n,cnt=0;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%s",s);
        li[i]=getHashKey(s);
    }
    sort(li,li+n);
    for(cnt=i=1;i<n;i++){
        if(li[i]!=li[i-1]){
            cnt++;
        }
    }
    printf("%d\n",cnt);
return 0;
}

