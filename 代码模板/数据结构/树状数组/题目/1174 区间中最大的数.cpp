#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

int tree[MAX],A[MAX];
int N,Q;
int lowbit(int x){
    return x&(-x);
}

void update(int x,int y){
    for(int i=x;i<=N;i+=lowbit(i)){
        tree[i]=max(y,tree[i]);
    }
}

int getMax(int l,int r){//��ѯ[l,r]��ֵ
    int ans=0;
    while(1){
         ans = max(A[r],ans);
         if(r==l) break;
         for(r--; r-lowbit(r)>=l; r -= lowbit(r))
             ans =max(ans,tree[r]);
    }
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,a,b;
    cin>>N;
    for(i=1;i<=N;i++){
        scanf("%d",&A[i]);
        update(i,A[i]);
    }
    cin>>Q;
    for(i=0;i<Q;i++){
        scanf("%d%d",&a,&b);
        printf("%d\n",getMax(a+1,b+1));
    }
return 0;
}
