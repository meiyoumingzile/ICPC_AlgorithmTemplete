#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

list<int>adlist[MAX];
int high[MAX],binp[MAX][20],pLen[MAX],treeSize[MAX];//���Ͻڵ���Ⱥ����ϵı�������
struct Node{
    int sum,son[2];
};
struct PersistentLineTree{
    int size,rlen;
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

const int CHARCNT=26;
inline int toInt(const char &a){
    return a-'a';
}
struct SAM{
    int root,last,size;
    int p[MAX*2],nodelen[MAX*2],son[MAX*2][CHARCNT],pos[MAX];

    //eplen[i]�Ǳ��Ϊi�Ľڵ�endpos����Ԫ�ظ���,du��ֻ��pָ���ÿ���������
    SAM(){
       clear();
    }
    void clear(){//��ʼ��
        root=last=0;//���ڵ�����0
        memset(son[0],-1,sizeof(son[0]));
        memset(pos,0,sizeof(pos));
        p[0]=-1;
        nodelen[0]=0;
        size=1;
    }
    int addNode(int len,bool isMain){//���ձ��˳����ӽڵ�
        int sz=size++;
        memset(son[sz],-1,sizeof(son[sz]));
        nodelen[sz]=len;
        return sz;
    }
    int push(const char &a,int si){
        int f=toInt(a),now,node,q,nq;
        node=addNode(nodelen[last]+1,1);
        pos[node]=si;
        for(now=last;now!=-1&&son[now][f]==-1;now=p[now]){
            son[now][f]=node;
        }
        if(now!=-1){
            q=son[now][f];
            if(nodelen[now]+1==nodelen[q]){
                p[node]=q;
            }else{
                nq=addNode(nodelen[now]+1,0);
                memcpy(son[nq], son[q], sizeof son[q]);
                p[nq]=p[q];
                p[q]=p[node]=nq;
                while(now!=-1&&son[now][f]==q){
                    son[now][f]= nq;
                    now=p[now];
                }
            }
        }else{
             p[node]=root;
        }
        last=node;
        return nodelen[node]- nodelen[p[node]];
    }
};
SAM sam;
int LRDid[MAX],LRDlen;//����������
void dfsSAMTree(int now,int n){
    int i,k,j;
    treeSize[now]=1;
    for(auto next:adlist[now]){
    	high[next]=high[now]+1;
    	for(j=0;;j++){//���±�������
            k=binp[next][j];
            if(j<pLen[k]){
                binp[next][pLen[next]++]=binp[k][j];
            }else{
                break;
            }
        }
        dfsSAMTree(next,n);
        treeSize[now]+=treeSize[next];
    }
    tr.insert(0,sam.size,now);
    LRDid[now]=LRDlen++;
}
int findTargetNode(int now,int h){//���ر��
    int i;
    //printf("(%d %d)\n",now,h);
    while(high[now]>h){
        if(high[now]==h+1){
            return binp[now][0];
        }
        for(i=0;high[binp[now][i]]>h;i++);
        now=binp[now][i-1];
    }
    return now;
}

char str[MAX];
void init(int n){
    sam.clear();//��պ�׺�Զ���
    for(int i=0;i<=n;i++){
        adlist[i].clear();//����ڽӱ�
    }
    for(int i=0;i<n;i++){
        sam.push(str[i],i+1);
    }
    tr.build(0,sam.size);
    high[sam.root]=1;
    memset(pLen,0,sizeof(pLen));
    memset(binp,0,sizeof(binp));
    for(int i=1;i<sam.size;i++){//��ʼ���������飬�õ��ڽӱ�
        binp[i][pLen[i]++]=sam.p[i];
        adlist[sam.p[i]].push_back(i);
    }
    LRDlen=0;
    dfsSAMTree(sam.root,n);
   /* for(int i=0;i<sam.size;i++){
        printf("%d: ",i);
        for(auto next:adlist[i]){
            printf("%d ",next);
        }printf("\n");
    }printf("\n");
    for(int i=0;i<sam.size;i++){
        printf("%d,%d: ",pLen[i],i);
        for(int j=0;j<pLen[i];j++){
            printf("%d ",binp[i][j]);
        }printf("\n");
    }*/
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,n,j,len,m,T,l,r,k,id;
	cin>>T;
	while(T--){
        scanf("%d%d%s",&n,&m,str);
        init(n);
        for(i=0;i<m;i++){
            scanf("%d%d%d",&l,&r,&k);
            len=r-l+1;
            id=findTargetNode(r,len+1);
            printf("%d %d\n",id,r);
            printf("%d %d\n",treeSize[id],LRDid[id]);
			printf("%d\n",tr.searchKi(LRDid[id]-treeSize[id],LRDid[id]-1,0,sam.size,k));
        }
	}
return 0;
}
/*
11
7 7
aabbabd
2 3 1

*/
