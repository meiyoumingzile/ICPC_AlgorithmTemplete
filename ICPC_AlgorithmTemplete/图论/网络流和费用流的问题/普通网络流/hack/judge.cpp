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
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

struct v2{
    int x,y;
	v2(){}
	v2(const int &x,const int &y){
		sett(x,y);
	}
    void sett(const int &x,const int &y){
        this->x=x;
        this->y=y;
    }
};
bool cmp(const v2 &a,const v2 &b){
    return a.x<b.x;
}
void println(int *arr,int b,int e,char *s=""){//[b,e)
    printf("%s (%d:%d)",s,b,arr[b]);
    for(int i=b+1;i<e;i++){
        printf(" (%d:%d)",i,arr[i]);
    }printf("\n");
}
int ac[100000],wa[100000];
int main(int argc,char *argv[]){
	int cas,i,j,k,t,n,m,s,u,v,val;
	freopen("ac.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
	i=0;
    while(~scanf("%d",&ac[i++]));
    freopen("wa.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
	i=0;
    while(~scanf("%d",&wa[i++]));
    n=i;
    for(i=0;i<n;i++){
        if(ac[i]!=wa[i]){
            printf("在i=%d ---- ac:%d  wa:%d",i,ac[i],wa[i]);
            return 0;
        }
    }
    printf("正确！！");
return 0;
}

