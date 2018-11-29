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
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;
int P;
struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int &e,const int &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V,E,S,T,size;
    int head[MAX];
    Edge edge[MAX*2];
    Graphic(){}
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;//������
ll val[MAX];//��Ȩֵ

struct Node{
    int r,l;
    ll sum,lz;
    void addlz(ll a){
        lz=(lz+a)%P;
    }
    void addsum(ll a){
        sum=(sum+a*(r-l)%P)%P;
    }
};
struct LineTree{//��������� ��[)
    Node tree[MAX*4];
    void mergeSon(cint now){
        tree[now].sum=(tree[now*2].sum+tree[now*2+1].sum)%P;
    }
    void buildTree(int now,ll *b,int l,int r){//����
        tree[now].l=l;
        tree[now].r=r;
        tree[now].lz=0;
        if(r-l==1){
            tree[now].sum=b[l]%P;
            return;
        }
        int mid=(l+r)/2,next=now*2;
        buildTree(next,b,l,mid);
        buildTree(next+1,b,mid,r);
        mergeSon(now);
    }

    void downLz(cint now){
        cint next=now*2;
        if(tree[now].lz!=0){
            tree[next].addlz(tree[now].lz);
            tree[next+1].addlz(tree[now].lz);
            tree[next].addsum(tree[now].lz);
            tree[next+1].addsum(tree[now].lz);
        }
        tree[now].lz=0;
    }
    void add(int now,int l,int r,ll a){
        Node &t=tree[now];
        const int mid=(t.r+t.l)/2,next=now*2;
        if(t.l==l&&t.r==r){
            t.addlz(a);
            t.addsum(a);
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
             mergeSon(now);
        }
    }
    ll searchSum(int now,int l,int r){
        Node &t=tree[now];
        const int mid=(t.r+t.l)/2,next=now*2;
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

namespace Split{
    int sz[MAX],//�ӽڵ���Ŀ,��������
        p[MAX],//���ڵ���
        h[MAX],//�߶�
        top[MAX],//��ǰ������˵ĵ�
        shv[MAX],//�ӽڵ����ؽڵ���
        id[MAX];//�±��
    ll newVal[MAX];//������ʡ�ռ���Բ�Ҫ
    int cnt;
    inline void dfs1(cint now,cint f,cint deep){//���4�����ԣ�sz,p,j,shv,���ڵ��p��-1��deep��0
        h[now]=deep;
        p[now]=f;//���ÿ����ĸ���
        sz[now]=1;//���ÿ����Ҷ�ӽڵ��������С
        int maxsz=-1;//��¼����sz��
        for(int i=g.head[now];i!=-1;i=g.edge[i].k){
            cint e=g.edge[i].e;
            if(e!=f){
                dfs1(e,now,deep+1);
                sz[now]+=sz[e];//���϶��ӵĴ�С
                if(sz[e]>maxsz){
                    shv[now]=e;
                    maxsz=sz[e];
                }
            }
        }
    }
    inline void dfs2(cint now,cint tnow){//x��ǰ�ڵ㣬topf��ǰ������˵Ľڵ㣬���ڵ��topf���Լ���cnt��0��ʼ
        id[now]=cnt;//���ÿ������±��
        newVal[cnt++]=val[now];//��ÿ����ĳ�ʼֵ�����±������
        top[now]=tnow;//������������Ķ���
        if(shv[now]){////����ж���
            dfs2(shv[now],tnow);//���ȴ����ض��ӣ��ٴ�������ӵ�˳��ݹ鴦��
            for(int i=g.head[now];i!=-1;i=g.edge[i].k){
                cint e=g.edge[i].e;
                if(e!=p[now]&&e!=shv[now]){//���Ǹ��ڵ�Ҳ�����ؽڵ�
                    dfs2(e,e);//����ÿһ������Ӷ���һ�������Լ���ʼ����
                }
            }
        }
    }
    void split(int root){//����������
        dfs1(root,-1,0);
        cnt=0;
        dfs2(root,root);
    }
    void add(int x,int y,ll a){//����x��y���·,����a
        while(top[x]!=top[y]){
            int &now=h[top[x]]>h[top[y]]?x:y;
            if(top[now]){
                tr.add(1,id[top[now]],id[now]+1,a);
                now=p[top[now]];
            }else{
                tr.add(1,id[now],id[now]+1,a);
                now=p[now];
            }
        }
        x=id[x];
        y=id[y];
        if(x>y)
            swap(x,y);
        tr.add(1,x,y+1,a);
    }
    ll getSum(int x,int y){//�õ�����x��y���·�ϵ��ֵ
        ll sum=0;
        while(top[x]!=top[y]){
            int &now=h[top[x]]>h[top[y]]?x:y;
            if(top[now]){
                sum=(sum+tr.searchSum(1,id[top[now]],id[now]+1))%P;
                now=p[top[now]];
            }else{
                sum=(sum+tr.searchSum(1,id[now],id[now]+1))%P;;
                now=p[now];
            }
        }
        x=id[x];
        y=id[y];
        if(x>y)
            swap(x,y);
        sum=(sum+tr.searchSum(1,x,y+1))%P;
        return sum;
    }
}
int main(int argc,char *argv[]){
    //freopen("in1.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    rg int i,j,k,t,T,n,m,root,u,v,x,y,z;
    ll sum;
    scanf("%d%d%d%d",&n,&m,&root,&P);
    for(i=1;i<=n;i++){
        scanf("%lld",&val[i]);
    }
    g.clear();
    for(i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        g.push(u,v,0);
        g.push(v,u,0);
    }
    Split::split(root);
    tr.buildTree(1,Split::newVal,0,n);// �������齨���߶���
    for(i=0;i<m;i++){
        scanf("%d",&k);
        if(k==1){
            scanf("%d%d%d",&x,&y,&z);
            Split::add(x,y,z);
        }else if(k==2){
            scanf("%d%d",&x,&y);
            printf("%lld\n",Split::getSum(x,y));
        }else if(k==3){
            scanf("%d%d",&x,&z);
            tr.add(1,Split::id[x],Split::id[x]+Split::sz[x],z);
        }else if(k==4){
            scanf("%d",&x);
            sum=tr.searchSum(1,Split::id[x],Split::id[x]+Split::sz[x]);
            printf("%lld\n",sum);
        }
    }
return 0;
}
