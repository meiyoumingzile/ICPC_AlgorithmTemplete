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
stack<int>st;//��������ջ
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
        if(st.empty()){//i��ɸ�
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

inline ll quickmi(ll a,ll b,const ll &mod){//���д��
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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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

