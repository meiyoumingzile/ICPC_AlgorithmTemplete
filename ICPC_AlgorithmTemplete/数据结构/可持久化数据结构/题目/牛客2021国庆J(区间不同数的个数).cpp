#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=200010;
const int mod=1e9+7;
inline void scan(int &x){
    char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}


/*
δ�ڽڵ㱣��˵㣬���Ƿ��ڵݹ麯����(����tl,tr)����ʡ�ռ�
*/
struct Node{
    int sum,son[2];
};
struct PersistentLineTree{
    int size,rlen,up;
    int root[MAX*3];//��ʾ���ڵ㼯�ϣ�root[0]������ԭʼ����
    Node tree[MAX<<6];
    void init(int n){
        size=rlen=1;
        root[0]=__init(0,n);
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
    void insert(int tl,int tr,int x,int ad=1){//�����޸�,�����°汾������xλ�ü�1,x����ɢ��֮�����ֵ
        int last=root[rlen-1];
        root[rlen++]=__insert(last,tl,tr,x,ad);
    }
    int __insert(int other,int tl,int tr, int x,int ad){//�������,��other�汾�����Ļ����ϵ�xλ�ü�1,x����ɢ��֮�����ֵ
        int now=size++;
        Node &t=tree[now];//tȥ����tree[now]���Ժ�t����tree[now]
        t=tree[other];//����ʷ�汾��һ�����Ƹ�tree[now]
        t.sum+=ad;
        if(tr-tl>1){
            int mid=(tl+tr)/2;
            if(x<mid){//�ڵ�������ߣ�������
                t.son[0]=__insert(tree[other].son[0],tl,mid,x,ad);
            }else{//�ڵ������ұߣ�������
                t.son[1]=__insert(tree[other].son[1],mid,tr,x,ad);
            }
        }
        return now;
    }
    int getSum(int other,int l,int r,int tl,int tr){//��ѯ����other�汾[l,r]�ĺ�
        return __getSum(root[other],l,r,tl,tr);
    }
    int __getSum(int now,int l,int r,int tl,int tr){//��ѯ�����kС���÷����ĵ�
        Node &t=tree[now];//tȥ����tree[other]���Ժ�t����tree[other]
        if(l==tl&&r==tr){
            return t.sum;
        }
        int mid=(tl+tr)/2;
        if(r<=mid){
            return __getSum(t.son[0],l,r,tl,mid);
        }else if(l>=mid){
            return __getSum(t.son[1],l,r,mid,tr);
        }else{
            return __getSum(t.son[0],l,mid,tl,mid)+__getSum(t.son[1],mid,r,mid,tr);
        }
    }
    void print(int other,int tl,int tr){
        __print(root[other],tl,tr);
        printf("\n");
    }
    void __print(int now,int tl,int tr){
        Node &t=tree[now];//tȥ����tree[other]���Ժ�t����tree[other]
        printf("(%d~%d %d)",tl,tr,t.sum);
        int mid=(tl+tr)/2;
        if(tr-tl>1){
            __print(t.son[0],tl,mid);
            __print(t.son[1],mid,tr);
        }
    }
};
PersistentLineTree tr;

int ind[MAX],A[MAX],version[MAX];
int main(int argc,char *argv[]){
	int i,j,t,n,m,a,ans,l,r;
	while(~scanf("%d%d",&n,&m)){
        memset(ind,-1,sizeof(ind));
        for(i=0;i<n;i++){
            scan(A[i]);
            A[i+n]=A[i];
        }
        n*=2;
        tr.init(n);
        for(i=0;i<n;i++){
            tr.insert(0,n,i,1);
            if(ind[A[i]]>-1){//�����°汾�޸�
                tr.insert(0,n,ind[A[i]],-1);
            }
            version[i]=tr.rlen-1;
            ind[A[i]]=i;
        }
        for(i=0;i<m;i++){
            scan(l);
            scan(r);
            t=l;
            l=r;
            r=t+n/2;
            ans=tr.getSum(version[r-1],0,r,0,n)-tr.getSum(version[r-1],0,l-1,0,n);
            printf("%d\n",ans);
        }
	}

return 0;
}
/*
6 8
1 2 3 4 3 5
1 2
3 5
2 6
1 1
2 2
3 3
4 4
1 5
*/
