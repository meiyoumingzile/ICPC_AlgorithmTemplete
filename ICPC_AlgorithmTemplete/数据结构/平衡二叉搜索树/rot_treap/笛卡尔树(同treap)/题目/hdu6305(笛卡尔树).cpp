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
const int MAX=2000010;
const int mod=1e9+7;

int A[MAX],sonCnt[MAX],son[MAX][2];
stack<int>st;//当做单调栈
inline void dfs(int now){
    int l=son[now][0],r=son[now][1];
    sonCnt[now]=1;
    if(l>0){
        dfs(l);
        sonCnt[now]+=sonCnt[l];
    }
    if(r>0){
        dfs(r);
        sonCnt[now]+=sonCnt[r];
    }
}
void buildDescartes(int n){
    rg int i,j,root=1,tr;
    while(!st.empty())
        st.pop();
    st.push(1);
    son[1][0]=son[1][1]=0;
    for(i=2;i<=n;i++){
        tr=0;
        while(!st.empty()&&A[st.top()]<A[i]){
            tr=st.top();
            st.pop();
        }
        if(st.empty()){//i变成根
            son[i][0]=root;
            root=i;
        }else{
            son[i][0]=tr;
            son[st.top()][1]=i;
        }
        son[i][1]=0;
        st.push(i);
    }
    dfs(root);
}

inline ll quickmi(ll a,ll b,const ll &mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	rg int i,j,k,t,T,n;
	ll ans;
	scan(T);
	while(T--){
        scan(n);
        for(i=1;i<=n;i++){
            scan(A[i]);
        }
        ans=1;
        buildDescartes(n);
        for(i=1;i<=n;i++){
            ans=ans*sonCnt[i]%mod;
        }
        printf("%lld\n",n*quickmi(ans*2%mod,mod-2,mod)%mod);
	}
return 0;
}

