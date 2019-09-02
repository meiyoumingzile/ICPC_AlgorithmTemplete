#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;
/*
δ�ڽڵ㱣��˵㣬���Ƿ��ڵݹ麯����(����tl,tr)����ʡ�ռ�
*/
struct Node{
    int sum,son[2];
};
struct PersistentLineTree{
    int size,rlen;
    int root[MAX];//��ʾ���ڵ㼯�ϣ�root[0]������ԭʼ����
    Node tree[MAX<<5];
    int lowbit(int x){
        return x&(-x);
    }
    int getsum(int x){//�õ�ǰ׺��
        int ans=0;
        if(x>0){
            for(int i=x;i;i-=lowbit(i))//iҪ����0
                ans+=BITtree[i];
        }
        return ans;
    }
    void build(int l,int r){
        size=rlen=1;
        root[0]=__build(l,r);
        memset(BITtree,0,sizeof BITtree);
    }
    int __build(int l,int r){
        int now=size++,mid=(l+r)/2;
        tree[now].sum=0;
        if(r-l>1){
            tree[now].son[0]=__build(l,mid);
            tree[now].son[1]=__build(mid, r);
        }
        return now;
    }
    void insert(int tl,int tr,int x,int cnt=1){//�����޸�,�����°汾������xλ�ü�1,x����ɢ��֮�����ֵ
        int last=root[rlen-1];
        for(int i=x;i<=n;i+=lowbit(i)){
            root[rlen++]=__insert(last,tl,tr,x,cnt);
        }
    }
    int __insert(int other,int tl,int tr,int x,int cnt){//�����޸�,��other�汾�����Ļ����ϵ�xλ�ü�1,x����ɢ��֮�����ֵ
        int now=size++;
        Node &t=tree[now];//tȥ����tree[now]���Ժ�t����tree[now]
        t=tree[other];//����ʷ�汾��һ�����Ƹ�tree[now]
        t.sum+=cnt;
        if(tr-tl>1){
            int mid=(tl+tr)/2;
            if(x<mid){//�ڵ�������ߣ�������
                t.son[0]=__insert(tree[other].son[0],tl,mid,x,cnt);
            }else{//�ڵ������ұߣ�������
                t.son[1]=__insert(tree[other].son[1],mid,tr,x,cnt);
            }
        }
        return now;
    }
    int searchKi(int root1,int root2,int tl,int tr,int k){//��ѯ�����kС���÷����ĵ�
        if (tr-tl<=1)//��Ҷ�ӽ��
            return tl;
        int tl1=tree[root1].son[0];
        int tl2=tree[root2].son[0];
        int x=tree[tl2].sum - tree[tl1].sum;
        int mid=(tl+tr)/2;
        if(x>=k)
            return searchKi(tl1,tl2,tl,mid,k);
        else
            return searchKi(tree[root1].son[1],tree[root2].son[1],mid,tr,k-x);
    }
};
PersistentLineTree tr;

struct v2{
    int x,y,k;
};
v2 question[MAX];

int toval[MAX*2],A[MAX*2];
int compress(int *A,int n){//������ɢ�������
    int i,k=1,t;
    for(i=0;i<n;i++){
        toval[i]=A[i];
    }
    sort(toval,toval+n);
    t=toval[0];
    for(i=1;i<n;i++){
        if(toval[i]!=t){
            t=toval[i];
            toval[k++]=toval[i];
        }
    }
    return k;
}


int main(){
    char kind;
	int i,l,r,k,n,m,up,ans,x;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++){
        scanf("%d",&A[i]);
	}
	up=n;
	for(i=0;i<m;i++){
        getchar();
        scanf("%c",&kind);//l��r��1��ʼ
        if(kind=='Q'){
            scanf("%d%d%d",&question[i].x,&question[i].y,&question[i].k);//l��r��1��ʼ
        }else if(kind=='C'){
            scanf("%d%d",&question[i].x,&question[i].y);
            question[i].k=-1;//y��-1�����޸�
            A[up++]=question[i].y;
        }
    }
    up=compress(A,up);
    tr.build(0,up);
    for(i=0;i<n;i++){
        x=lower_bound(toval,toval+up,A[i])-toval;//���ö��ֲ��Һ�����x����ɢ��������ݣ�Ҳ������map
        tr.insert(0,up,x);
    }
    for(i=0;i<m;i++){
        if(question[i].k!=-1){
            l=question[i].x;
            r=question[i].y;
            k=question[i].k;
            ans=tr.searchKi(tr.root[l-1],tr.root[r],0,up,k);
            printf("%d\n",toval[ans]);
        }else{
            tr.insert(0,up,x,-1);
            A[question[i].x]=question[i].y;
            x=lower_bound(toval,toval+up,question[i].y)-toval;//���ö��ֲ��Һ�����x����ɢ���������
            tr.insert(0,up,x);
        }
    }
return 0;
}
