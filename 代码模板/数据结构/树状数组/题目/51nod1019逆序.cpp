#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

struct BIT{
    int n;
    int tree[MAX];
    void init(int n){
        this->n=n;
        memset(tree,0,sizeof(tree));
    }
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,int y){//����x�±�����y,x�±��1��ʼ
        for(int i=x;i<=n;i+=lowbit(i))
            tree[i]+=y;
    }
    int getsum(int x){//�õ�ǰ׺��
        int ans=0;
        if(x>0){
            for(int i=x;i;i-=lowbit(i))//iҪ����0
                ans+=tree[i];
        }
        return ans;
    }
    int getsum(int x,int y){//�õ�����[x,y]�ĺͣ�x��y�±��1��ʼ
        if(x>y)
            return 0;
        return getsum(y)-getsum(x-1);
    }
};

struct v2{
    int x,y;

    void sett(int x,int y){
        this->x=x;
        this->y=y;
    }
};
v2 A[MAX];
int rankk[MAX];
bool cmp1(const v2 &a,const v2 &b){
    return a.x < b.x;
}
bool cmp2(const v2 &a,const v2 &b){
    return a.y < b.y;
}
BIT bi;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,n,cnt;
    cin>>n;
    for(i=0;i<n;i++){
        scanf("%d",&A[i].x);
        A[i].y=i+1;
    }
    sort(A,A+n,cmp1);
    for(i=1,rankk[0]=1;i<n;i++){
        rankk[i]=A[i-1].x==A[i].x?rankk[i-1]:rankk[i-1]+1;
    }
    for(i=0;i<n;i++){
        A[i].x=rankk[i];
    }
    sort(A,A+n,cmp2);

    bi.init(n);
    for(i=0,cnt=0;i<n;i++){
        bi.add(A[i].x,1);
        cnt+=i+1-bi.getsum(A[i].x);
    }
    printf("%d\n",cnt);

return 0;
}
/*
5 6
2 3 4 5 6
1 0 4

*/
