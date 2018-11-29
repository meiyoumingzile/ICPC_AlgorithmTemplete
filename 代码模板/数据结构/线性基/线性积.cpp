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
const int MAX=100010;
const int mod=1e9+7;
struct lineBase{
	ll p[70];
	ll up;
	void clear(){
		up=0;
		memset(p,0,sizeof(p));
	}
	void push(ll a){
		ll n=a,i;
		for(i=0;n;i++,n>>=1);
		up=max(up,i);
		for(i--;i>=0;i--){
			if(a>>i){
				if(p[i]==0){
					p[i]=a;
					return;
				}
				a^=p[i];
			}
		}
	}
	ll getMax(){
		ll ans=0;
		for(int i=up-1;i>=0;i--){
			if((ans^p[i])>ans)
				ans^=p[i];
		}
		return ans;
	}
	bool check(ll x){
        for(int i=up-1;i>=0;i--){
            if(x&(1ll<<i)){
                if(!p[i]){
                    return 0;
                }
                x^=p[i];
            }
        }
        return 1;
    }
};
lineBase linb;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n;
	ll a;
	linb.clear();
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%lld",&a);
		linb.push(a);
	}
	/*for(i=0;i<10;i++){
		printf("%d\n",linb.p[i]);
	}*/
	printf("%lld\n",linb.getMax());
return 0;
}


