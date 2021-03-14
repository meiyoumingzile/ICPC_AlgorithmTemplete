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
const int MAX=200010;
const int mod=1e9+7;
/*
δ�ڽڵ㱣��˵㣬���Ƿ��ڵݹ麯����(����tl,tr)����ʡ�ռ�
*/
struct Node{
    int sum,son[2];
};
struct PersistentLineTree{
    int size,rlen,up;
    int root[MAX];//��ʾ���ڵ㼯�ϣ�root[0]������ԭʼ����
    Node tree[MAX<<5];
    void build(int l,int r){
        size=rlen=1;
        root[0]=__build(l,r);
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
    void insert(int tl,int tr,int x){//�����޸�,�����°汾������xλ�ü�1,x����ɢ��֮�����ֵ
        int last=root[rlen-1];
        root[rlen++]=__insert(last,tl,tr,x);
    }
    int __insert(int other,int tl,int tr, int x){//�����޸�,��other�汾�����Ļ����ϵ�xλ�ü�1,x����ɢ��֮�����ֵ
        int now=size++;
        Node &t=tree[now];//tȥ����tree[now]���Ժ�t����tree[now]
        t=tree[other];//����ʷ�汾��һ�����Ƹ�tree[now]
        t.sum++;
        if(tr-tl>1){
            int mid=(tl+tr)/2;
            if(x<mid){//�ڵ�������ߣ�������
                t.son[0]=__insert(tree[other].son[0],tl,mid,x);
            }else{//�ڵ������ұߣ�������
                t.son[1]=__insert(tree[other].son[1],mid,tr,x);
            }
        }
        return now;
    }
    int searchKi(int l,int r,int tl,int tr,int k){//��ѯ����[l,r]�ĵ�kС
        return __searchKi(root[l-1],root[r],tl,tr,k);
    }
    int __searchKi(int root1,int root2,int tl,int tr,int k){//��ѯ�����kС���÷����ĵ�
        if (tr-tl<=1)//��Ҷ�ӽ��
            return tl;
        int tl1=tree[root1].son[0];
        int tl2=tree[root2].son[0];
        int x=tree[tl2].sum - tree[tl1].sum;
        int mid=(tl+tr)/2;
        if(x>=k)
            return __searchKi(tl1,tl2,tl,mid,k);
        else
            return __searchKi(tree[root1].son[1],tree[root2].son[1],mid,tr,k-x);
    }
};
PersistentLineTree tr;
struct v2{
    int x,y;
};
v2 A[MAX];
int disA[MAX];//��ɢ��֮���ԭ����
int discrete(v2 *A,int *disA,int n){//��ɢ��
    sort(A,A+n,[](const v2 &a,const v2 &b){
         return a.x<b.x;
    });
    int k=0;
    disA[A[0].y]=k;
    for(int i=1;i<n;i++){
        k+=A[i].x!=A[i-1].x;
        disA[A[i].y]=k;
        A[k]=A[i];
    }
    return k+1;
}
int main(){
	int i,l,r,k,n,m,up,ans;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++){
        scanf("%d",&A[i].x);
        A[i].y=i;
	}
    tr.up=discrete(A,disA,n);
    tr.build(0,tr.up);
    for(i=0;i<n;i++){
        tr.insert(0,up,disA[i]);
    }
    for(i=0;i<m;i++){
        scanf("%d%d%d",&l,&r,&k);//l��r��1��ʼ
        ans=tr.searchKi(l,r,0,up,k);
        printf("%d\n",A[ans].x);
    }
return 0;
}
