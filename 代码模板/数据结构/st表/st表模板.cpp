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
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

int A[MAX];
int st[MAX][17];//st[i][j]��ʾ�ӵ�i������ʼ��������2^j���������ֵ
void getST(cint n){
    rg int i,j,k,up=log2(n);
    for(i=0;i<n;i++){
        st[i][0]=A[i];
    }
    for(j=1;j<=up;j++){
        k=1<<(j-1);
        for(i=0;i+k*2<=n;i++){
            st[i][j]=max(st[i][j-1],st[i+k][j-1]);
        }
    }

}
int query(cint l,cint r){//����[l,r]���ֵ
    int k=log2((r-l+1));
    return max(st[l][k],st[r+1-(1<<k)][k]);
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	rg int i,j,k,t,T,n,m,l,r;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++){
        scanf("%d",&A[i]);
	}
    getST(n);
	while(m--){
        scanf("%d%d",&l,&r);
        printf("%d\n",query(l-1,r-1));
	}
return 0;
}

