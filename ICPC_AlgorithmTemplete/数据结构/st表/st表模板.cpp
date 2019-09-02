#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;


int A[MAX];
struct ST{
    int st[MAX][17];//st[i][j]��ʾ�ӵ�i������ʼ��������2^j���������ֵ
    void getST(int *A,int n){
        int i,j,k,up=log2(n);
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
    int query(int l,int r){//����[l,r]���ֵ
        int k=log2((r-l+1));
        return max(st[l][k],st[r+1-(1<<k)][k]);
    }
};
ST st;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,n,m,l,r;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++){
        scanf("%d",&A[i]);
	}
    st.getST(A,n);
	while(m--){
        scanf("%d%d",&l,&r);
        printf("%d\n",st.query(l-1,r-1));
	}
return 0;
}

