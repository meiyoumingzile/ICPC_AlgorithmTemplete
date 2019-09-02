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
#define dd double
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=2e5+10;
const int mod=1e9+7;

struct Node{
    int l,r,c;//c�������
    ll sum;
};
struct LineTree{
    Node tree[MAX*4];
    void buildTree(int now,int l,int r){
        Node &t=tree[now];
        t.l=l;
        t.r=r;
        t.sum=t.c=0;
        if(r==l+1){
            return;
        }
        int mid=(l+r)>>1;
        buildTree(now*2,l,mid);
        buildTree(now*2+1,mid,r);
    }
    void addCnt(int now,int l,int c,ll val=0){//������£�val�������������ֵ
        Node &t=tree[now];
        if(t.l==l&&t.r==l+1){
            t.c+=c;
            if(t.c<0)
                t.c=0;
            t.sum=val*t.c;
        }else{
            int mid=(t.l+t.r)>>1;
            if(mid<=l){
                addCnt(now*2+1,l,c,val);
            }else{
                addCnt(now*2,l,c,val);
            }
            t.sum=tree[now*2].sum+tree[now*2+1].sum;
            t.c=tree[now*2].c+tree[now*2+1].c;
        }
    }
    int searchSum(int now,int l,int r){//��ѯĳ����Χ������֮��
        Node &t=tree[now];
        if(t.r==r&&t.l==l){
            return t.sum;
        }else{
            int mid=(t.l+t.r)>>1;
            if(mid>=r){
                return searchSum(now<<1,l,r);
            }else if(mid<=l){
                return searchSum(now*2+1,l,r);
            }else{
                return searchSum(now*2+1,mid,r)+searchSum(now<<1,l,mid);
            }
        }
    }
    int searchCnt(int now,int l,int r){//��ѯĳ����Χ�����ݸ���֮��
        Node &t=tree[now];
        if(t.r==r&&t.l==l){
            return t.c;
        }else{
            int mid=(t.l+t.r)>>1;
            if(mid>=r){
                return searchCnt(now<<1,l,r);
            }else if(mid<=l){
                return searchCnt(now*2+1,l,r);
            }else{
                return searchCnt(now*2+1,mid,r)+searchCnt(now<<1,l,mid);
            }
        }
    }

    //-------------------------�õ���չ����
    int getRank(int k){//�õ�����
        return searchCnt(1,0,k)+1;
    }
    int findRankNum(int rank,int now=1){//��ѯ��kС
        int next=now*2;
        int mid=(tree[next].l+tree[next+1].r)/2;
        Node &t=tree[now];
        if(t.r==t.l+1){
            return t.l;
        }
        if(tree[next].c>=rank){
            return findRankNum(rank,next);
        }else{
            return findRankNum(rank-tree[next].c,next+1);
        }
    }
    int preNum(int k){//ǰ����ǰ���������������-1����
        return findRankNum(searchCnt(1,0,k));
    }
    int nextNum(int k){//��̣������Ҫ��������治���ڣ����ھ�����������+1������������������������
        int c=searchCnt(1,k,k+1);
        return findRankNum(searchCnt(1,0,k)+c+1);
    }
};

int id[MAX],A[MAX];

unordered_map<int,int>ind;
int toval[MAX];
int compress(int *A,int n){//������ɢ�������
    int i,k=0,t;
    for(i=0;i<n;i++){
        toval[i]=A[i];
    }
    sort(toval,toval+n);
    ind[toval[0]]=k++;
    t=toval[0];
    for(i=1;i<n;i++){
        if(toval[i]!=t){
            t=toval[i];
            toval[k]=toval[i];
            ind[toval[i]]=k++;
        }
    }
    return k;
}


int main(int argc,char *argv[]){
    //freopen("testdata.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("myout.out","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,k,T,n;
    Node *e;
    scanf("%d",&T);
    LineTree *tr=new LineTree();
    for(i=0;i<T;i++){
        scanf("%d%d",&id[i],&A[i]);
    }
    n=compress(A,T);
    tr->buildTree(1,0,n);

    for(i=0;i<T;i++){
        if(id[i]==1){
            tr->addCnt(1,ind[A[i]],1,A[i]);
        }else if(id[i]==2){
            tr->addCnt(1,ind[A[i]],-1,A[i]);
        }else if(id[i]==3){
            printf("%d\n",tr->getRank(ind[A[i]]));
        }else if(id[i]==4){
            printf("%d\n",toval[tr->findRankNum(A[i])]);
        }else if(id[i]==5){
            printf("%d\n",toval[tr->preNum(ind[A[i]])]);
        }else if(id[i]==6){
            printf("%d\n",toval[tr->nextNum(ind[A[i]])]);
        }
    }
return 0;
}


