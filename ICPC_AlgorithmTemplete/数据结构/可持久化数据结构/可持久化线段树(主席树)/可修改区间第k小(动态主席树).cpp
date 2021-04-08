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
struct PersistentLineTree{//��̬�־û����߶���
    int size,rlen,up;
    int root[MAX];//��ʾ���ڵ㼯�ϣ�root[0]������ԭʼ����
    Node tree[MAX<<5];
    int BITtree[MAX];
    //��״����ڵ�,ά��root[]����,��root[]������ڵ㼯�ϵĵ�ַ������BITtree[i]��������״������Ϊi�Ľڵ��Ӧ����ϯ���еĸ��ڵ�ĵ�ַ
    int path[MAX];//path[i]��������״������Ϊi�Ľڵ��Ӧ����ϯ���еĸ��ڵ�ĵ�ַ
    int lowbit(int x){
        return x&(-x);
    }

    void init(int n){//����һ�̿յ���ϯ��
        size=rlen=1;
        root[0]=__init(0,n);
        up=n;
        memset(BITtree,0,sizeof BITtree);
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
    void BIT_insert(int BITx,int n,int pos,int val){
        //���߶������пɳ־û���ӣ�������״�����·����BITx����״����ڵ�ţ�n����״����ڵ������pos��λ�ã�val������
        for(int i=BITx;i<=n;i+=lowbit(i))//iҪ����0
            BITtree[i]+=__insert(BITtree[i],0,up,pos,val);//�־û����룬�������°汾
    }
    void insert(int x,int cnt=1){//�����޸�,�����°汾������xλ�ü�1,x����ɢ��֮�����ֵ
        root[rlen++]=__insert(root[rlen-1],0,up,x,cnt);//���°汾
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
    int searchKi(int root1,int root2,int tl,int tr,int k){//��ѯ�����kС���ǵݹ��ѯ
        if (tr-tl<=1)//��Ҷ�ӽ��
            return tl;
       /* auto getLeftSum=[](int now){//�õ���ǰ�ڵ����ڵ��sumֵ
            int ans=0;
            for(int i=now;i>0;i-=lowbit(i))//iҪ����0
                ans+=this->BITtree[i];
            return ans;

        };*/
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
    int ind(int x){//ѹ�����ݱ�Ϊ��ʵ����
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

    tr.init(up);
    for(i=0;i<n;i++){
        tr.insert(0,data.ind(A[i]));
    }
    for(i=0;i<m;i++){
        if(question[i].k!=-1){
            l=question[i].x;
            r=question[i].y;
            k=question[i].k;
            ans=tr.searchKi(tr.root[l-1],tr.root[r],0,up,k);
            printf("%d\n",data.toval[ans]);
        }else{
            tr.insert(x,-1);
            A[question[i].x]=question[i].y;
            x=data.ind(question[i].y);//���ö��ֲ��Һ�����x����ɢ���������
            tr.insert(x);
        }
    }
return 0;
}
