#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<bitset>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;
bool vis[MAX];
char sp[MAX];
int p[MAX];
int p_num;
ll fac[MAX];
void getFac(int N){
    fac[0]=fac[1]=1;
    for(int i=2;i<=N;i++){
        fac[i]=fac[i-1]*i;
    }
}

void dfs(int nowLen,int m,int n){
    int i;
    if(nowLen==n){
        /*for(i=0;i<n;i++){
            printf("%d",p[i]);
        }printf("  %d\n",p_num++);*/
        p_num++;
        return;
    }
    for(i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=true;
            p[nowLen]=i;
            dfs(nowLen+1,i,n);
            vis[i]=false;
        }
    }
}

bool v[1000];
vector<int> getArr(int N,int n){
    vector<int>res;
    memset(v,0,sizeof(0));
    int i,j,k,m,l;
    for(i=N-1;i>=0;i--){
        k=n/fac[i];
        n=n%fac[i];
        //printf("%d %d\n",k,n);
        for(j=0,l=1;j<=k;l++){
            if(!v[l]){
                j++;
            }
        }
        res.push_back(l-2);
        v[l-1]=true;
    }

    return res;
}
int codeArr(int *A,int N){
    int ans=0,i,j,cnt;
    for(i=0;i<N-1;i++){
        for(j=i+1,cnt=0;j<N;j++){
            if(A[i]>A[j]){
                cnt++;
            }
        }
        ans+=cnt*fac[N-i-1];
    }
    return ans;
}
int codeArr(vector<int>A,int N){
    int ans=0,i,j,cnt;
    for(i=0;i<N-1;i++){
        for(j=i+1,cnt=0;j<N;j++){
            if(A[i]>A[j]){
                cnt++;
            }
        }
        ans+=cnt*fac[N-i-1];
    }
    return ans;
}

int main(int argc,char *argv[]){

    //freopen("debug\\in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("debug\\out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//OJ���еĵط����ܼ���仰
    int i,j,N,n;
    scanf("%d",&N);
    getFac(N);
    memset(vis,0,sizeof(vis));
    p_num=0;
    dfs(0,1,N);
    printf("%d��\n",p_num);
    printf("�������\n");
    while(~scanf("%d",&n)){
        if(n>=p_num){
            printf("����\n");
        }else{
            vector<int>get=getArr(N,n);
            for(i=0;i<get.size();i++){
                printf("%d",get[i]);
            }printf("\n");
        }
    }
    printf("��������\n");
    while(~scanf("%s",sp)){
        int *A=new int[N];
        for(i=0;i<N;i++){
            A[i]=sp[i]-'0';
            printf("%d",A[i]);
        }printf("\n");

        printf("%d\n",codeArr(A,N));
    }

return 0;
}
