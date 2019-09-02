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
    int st[MAX][17];//st[i][j]表示从第i个数开始，往后找2^j个数的最大值
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
    int query(int l,int r){//区间[l,r]最大值
        int k=log2((r-l+1));
        return max(st[l][k],st[r+1-(1<<k)][k]);
    }
};
ST st;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
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

