#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;
int P;
struct Node{
    int r,l;
    ll sum,lz1,lz2;//ά�������,lz1�����������ӵı��lz2��������˷��ı��
    int getDis(){
        return (r-l)%P;
    }
};

int A[MAX];
struct LineTree{//��������� ��[)
    Node tree[MAX*4];
    void buildTree(int now,int *b,int l,int r){//����
        tree[now].l=l;
        tree[now].r=r;
        tree[now].lz1=0;
        tree[now].lz2=1;
        if(r-l<=1){
            tree[now].sum=b[l]%P;
            return;
        }
        int mid=(l+r)/2,next=now*2;
        buildTree(next,b,l,mid);
        buildTree(next+1,b,mid,r);
        tree[now].sum=(tree[next].sum+tree[next+1].sum)%P;
    }

    void downLz2(const int &now){
        const int next=now<<1;
        if(tree[now].lz2!=1){
            tree[next].lz2=tree[next].lz2*tree[now].lz2%P;
            tree[next+1].lz2=tree[next+1].lz2*tree[now].lz2%P;
            tree[next].lz1=tree[next].lz1*tree[now].lz2%P;
            tree[next+1].lz1=tree[next+1].lz1*tree[now].lz2%P;
            tree[next].sum=tree[next].sum*tree[now].lz2%P;
            tree[next+1].sum=tree[next+1].sum*tree[now].lz2%P;
            tree[now].lz2=1;
        }
    }
    void downLz1(const int &now){
        const int next=now<<1;
        tree[next].lz1=(tree[next].lz1+tree[now].lz1)%P;
        tree[next+1].lz1=(tree[next+1].lz1+tree[now].lz1)%P;
        tree[next].sum=(tree[next].sum+tree[now].lz1*tree[next].getDis()%P)%P;
        tree[next+1].sum=(tree[next+1].sum+tree[now].lz1*tree[next+1].getDis()%P)%P;
        tree[now].lz1=0;
    }
    void downLz(const int &now){
        downLz2(now);
        downLz1(now);
    }
    void add(int now,int l,int r,ll a){
        Node &t=tree[now];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            t.lz1=(t.lz1+a)%P;
            t.sum=(t.sum+a*tree[now].getDis()%P)%P;
        }else{
            downLz(now);//û�ߵ����ڵ����
            if(mid>=r){
                add(next,l,r,a);
            }else if(mid<=l){
                add(next+1,l,r,a);
            }else{
                add(next,l,mid,a);
                add(next+1,mid,r,a);
            }
            t.sum=(tree[next].sum+tree[next+1].sum)%P;
        }
    }
    void mul(int now,int l,int r,ll a){
        Node &t=tree[now];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            t.lz2=t.lz2*a%P;
            t.lz1=t.lz1*a%P;
            t.sum=t.sum*a%P;
        }else{
            downLz(now);//û�ߵ����ڵ����
            if(mid>=r){
                mul(next,l,r,a);
            }else if(mid<=l){
                mul(next+1,l,r,a);
            }else{
                mul(next,l,mid,a);
                mul(next+1,mid,r,a);
            }
            t.sum=(tree[next].sum+tree[next+1].sum)%P;
        }
    }
    ll searchSum(int now,int l,int r){
        Node &t=tree[now];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            return t.sum;
        }else{
            downLz(now);
            if(mid>=r){
                return searchSum(next,l,r);
            }else if(mid<=l){
                return searchSum(next+1,l,r);
            }else{
                return (searchSum(next,l,mid)+searchSum(next+1,mid,r))%P;
            }
        }
    }
};
LineTree tr;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    register int i,j,k,m,n,l,r;
    ll val;
    while(~scanf("%d%d%d",&n,&m,&P)){
        for(i=0;i<n;i++){
            scanf("%d",&A[i]);
        }
        tr.buildTree(1,A,0,n);
        for(i=0;i<m;i++){//m��ѯ��
            scanf("%d",&k);
            if(k==1){
                scanf("%d%d%lld",&l,&r,&val);
                val%=P;
                tr.mul(1,l-1,r,val);
            }else if(k==2){
                scanf("%d%d%lld",&l,&r,&val);
                val%=P;
                tr.add(1,l-1,r,val);
            }else if(k==3){
                scanf("%d%d",&l,&r);
                printf("%lld\n",tr.searchSum(1,l-1,r));
            }
        }
    }
return 0;
}

