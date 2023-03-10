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
struct PersistentLineTree{//��̬�־û����߶���
    int size,rlen,n;//n����״��������ޣ���һ�������߶���Ҷ�ӽڵ����
    int root[MAX];//��ʾ���ڵ㼯�ϣ�root[0]������ԭʼ����
    Node tree[MAX<<6];
    int BITtree[MAX];//BITtree[i]�����i��Ȩֵ�߶����ĸ��ڵ���root�еı��
    //��״����ڵ�,ά��root[]����,��root[]������ڵ㼯�ϵĵ�ַ������BITtree[i]��������״������Ϊi�Ľڵ��Ӧ����ϯ���еĸ��ڵ�ĵ�ַ

    int BITpath[2][MAX];//��¼��״�����·��,���������kСʱ����
    int BITpath_len[2];
    int rememberBITpath(int pos,int *path){//��¼·������
        int len=0;
        for(int i=pos;i>0;i-=lowbit(i)){
            path[len++]=root[i];
        }
        return len;
    }
    void updateBITpath(int *path,int len,int fp){//����·������
        for(int i=0;i<len;i++){
            path[i]=tree[path[i]].son[fp];
        }
    }
    int getSumBITpath(int *path,int len,int fp){//��״�����ѯ��ǰposλ�õ��߶����У�x�ĳ��ִ���
        int ans=0;
        for(int i=0;i<len;i++){
            ans+=tree[tree[path[i]].son[fp]].sum;
        }
        return ans;
    }
    int lowbit(int x){
        return x&(-x);
    }

    void init(int n,int m){//����һ�̿յ���ϯ��,n����״�������ޣ�m���߶������
        size=rlen=1;
        this->n=n;
        root[0]=__init(0,m);
        memset(BITtree,0,sizeof BITtree);//��ʼ�׶���״����Ϊ�գ�ȫ��ָ��root[0]
    }
    int __init(int l,int r){
        int now=size++,mid=(l+r)/2;
        tree[now].sum=0;
        if(r-l>1){
            tree[now].son[0]=__init(l,mid);
            tree[now].son[1]=__init(mid, r);
        }
        return now;
    }
    void insert(int pos,int x,int val,int up){//�����޸�,�����°汾������xλ�ü�1,x����ɢ��֮�����ֵ
        for(int i=pos;i<=n;i+=lowbit(i)){//iҪ����0
            int last=root[i];
            root[i]=__insert(root[i],0,up,x,val);//���°汾
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

    int searchKi(int l,int r,int k,int up){//��ѯ����[l,r]�ĵ�kС��,ʹ����״����ĸ���
        BITpath_len[0]=rememberBITpath(l,BITpath[0]);
        BITpath_len[1]=rememberBITpath(r,BITpath[1]);
        return __searchKi(root[l],root[r],0,up,k);
    }

    int __searchKi(int root1,int root2,int tl,int tr,int k){//��ѯ�����kС���÷����ĵ�
        if (tr-tl<=1)//��Ҷ�ӽ��
            return tl;
        int tl1=tree[root1].son[0];
        int tl2=tree[root2].son[0];
        int x=getSumBITpath(BITpath[1],BITpath_len[1],0)-getSumBITpath(BITpath[0],BITpath_len[0],0);
        int mid=(tl+tr)/2;
        if(x>=k){
            updateBITpath(BITpath[0],BITpath_len[0],0);//����·������
            updateBITpath(BITpath[1],BITpath_len[1],0);
            return __searchKi(tl1,tl2,tl,mid,k);
        }else{
            updateBITpath(BITpath[0],BITpath_len[0],1);//����·������
            updateBITpath(BITpath[1],BITpath_len[1],1);
            return __searchKi(tree[root1].son[1],tree[root2].son[1],mid,tr,k-x);
        }
    }
};
PersistentLineTree tr;

struct v2{
    int x,y,k;
};
v2 question[MAX];
int A[MAX*2];//��������


struct DataCompress{//����ѹ����
    int *toval;
    int up;
    int compress(int *A,int n){//������ɢ�������
        int i,k=1,t;
        toval=new int[n];
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
        up=k;
        return k;
    }
    int ind(int x){//������ɢ��������
        return lower_bound(toval,toval+up,x)-toval;//���ö��ֲ��Һ�����x����ɢ��������ݣ�Ҳ������mapʵ�֡�
    }
};
DataCompress data;//����ѹ����

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
    up=data.compress(A,up);
    //�������������ɢ�������濪ʼ����̬ʱ�־û��߶���

    tr.init(n,up);
    for(i=0;i<n;i++){//�±�[1,n]
        tr.insert(i+1,data.ind(A[i]),1,up);
    }
    for(i=0;i<m;i++){
        if(question[i].k!=-1){
            l=question[i].x;
            r=question[i].y;
            k=question[i].k;
            ans=tr.searchKi(l-1,r,k,up);
            printf("%d\n",data.toval[ans]);
        }else{
            tr.insert(question[i].x,data.ind(A[question[i].x-1]),-1,up);
            A[question[i].x-1]=question[i].y;
            tr.insert(question[i].x,data.ind(question[i].y),1,up);
        }
    }
return 0;
}
/*
5 5
25957 6405 15770 26287 26465
Q 2 2 1
Q 3 4 1
Q 4 5 1
Q 1 2 2
Q 4 4 1
*/
