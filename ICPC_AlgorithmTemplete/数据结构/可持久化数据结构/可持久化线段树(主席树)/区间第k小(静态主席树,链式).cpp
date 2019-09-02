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
struct Node{//
    int sum=0;
    Node *son[2];
    Node* clone(){
        Node* now=new Node();
        now->sum=sum;
        now->son[0]=son[0];
        now->son[1]=son[1];
        return now;
    }
};
struct PersistentLineTree{
    int rlen=0;//root���鳤��
    Node* root[MAX];//��ʾ���ڵ㼯�ϣ�root[0]������ԭʼ����
    void build(int l,int r){//��һ�ſ���������λ����0
        rlen=0;
        root[rlen++]=__build(l,r);
    }
    Node* __build(int l,int r){//��һ�ſ���������λ����0
        int mid=(l+r)/2;
        Node *now=new Node();
        if(r-l>1){
            now->son[0]=__build(l,mid);
            now->son[1]=__build(mid, r);
        }
        return now;
    }
    void insert(int tl,int tr,int x){//�����޸�,�����°汾������xλ�ü�1,x����ɢ��֮�����ֵ
        Node *last=root[rlen-1];
        root[rlen++]=__insert(last,tl,tr,x);
    }
    Node* __insert(Node* other,int tl,int tr, int x){//�����޸�,��other�汾�����Ļ����ϵ�xλ�ü�1,x����ɢ��֮�����ֵ
        Node *now=other->clone();//��һһ���½ڵ�,��other�����λ�õĽڵ���ͬ
        now->sum++;//����һ��
        if(tr-tl>1){
            int mid=(tl+tr)/2;
            if(x<mid){//�ڵ�������ߣ�������
                now->son[0]=__insert(other->son[0],tl,mid,x);
            }else{//�ڵ������ұߣ�������
                now->son[1]=__insert(other->son[1],mid,tr,x);
            }
        }
        return now;
    }
    int searchKi(Node* root1,Node* root2,int tl,int tr,int k){//��ѯ�����kС���÷����ĵ�
        if (tr-tl<=1)//��Ҷ�ӽ��
            return tl;
        Node* tl1=root1->son[0];
        Node* tl2=root2->son[0];
        int x=tl2->sum - tl1->sum;
        int mid=(tl+tr)/2;
        if(x>=k)
            return searchKi(tl1,tl2,tl,mid,k);
        else
            return searchKi(root1->son[1],root2->son[1],mid,tr,k-x);
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
    up=discrete(A,disA,n);
    tr.build(0,up);
    for(i=0;i<n;i++){
        tr.insert(0,up,disA[i]);
    }
    for(i=0;i<m;i++){
        scanf("%d%d%d",&l,&r,&k);//l��r��1��ʼ
        ans=tr.searchKi(tr.root[l-1],tr.root[r],0,up,k);
        printf("%d\n",A[ans].x);
    }
return 0;
}
