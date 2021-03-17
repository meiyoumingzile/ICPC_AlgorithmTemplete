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
    int p,h,son[2];//维护并查集对应节点父亲是谁以及当前节点深度
    Node(){
        son[0]=son[1]=0;
    }
};
struct Per_union{
    int size,rlen,up;
    int root[MAX];//
    Node tree[MAX<<5];
    void init(int n){//并查集节点下标从0开始
        size=rlen=1;//size从1开始，0空余代表空
        root[0]=__build(0,n);
        up=n;
    }
    int __build(int l,int r){//[l,r)
        int now=size++,mid=(l+r)/2;
        if(r-l>1){
            tree[now].son[0]=__build(l,mid);
            tree[now].son[1]=__build(mid, r);
        }else{
            tree[now].h=1;
            tree[now].p=l;
        }
        return now;
    }

    int getPos(int now,int tl,int tr,int pos){//查询某个版本的并查集节点pos的信息,返回地址
        if(tr-tl==1){
            return now;
        }
        int mid=(tl+tr)/2;
        if(pos<mid){//�ڵ�������ߣ�������
            return getPos(tree[now].son[0],tl,mid,pos);
        }else{//�ڵ������ұߣ�������
            return getPos(tree[now].son[1],mid,tr,pos);
        }
    }

    void per_updateP(int verID,int pos,int pval){//修改第verID版本的并查集pos位置所储存的父亲为pval
        root[rlen++]=__per_updateP(root[verID],0,up,pos,pval);
    }
    int __per_updateP(int now,int tl,int tr,int pos ,int pval){//把pos位置改为pval，持久化修改,返回根
        int r=size++;
        Node &t=tree[r];//t去引用tree[r]，以后t就是tree[r]
        t=tree[now];//把历史版本的一个复制给tree[r]
        if(tr-tl==1){
            t.p=pval;
            t.h=tree[now].h;
            return r;
        }
        int mid=(tl+tr)/2;
        if(pos<mid){//向左走，复制了历史版本，但复制节点的左儿子要更新
            t.son[0]=__per_updateP(tree[now].son[0],tl,mid,pos,pval);
        }else{//向右走，复制了历史版本，但复制节点的右儿子要更新
            t.son[1]=__per_updateP(tree[now].son[1],mid,tr,pos,pval);
        }
        return r;
    }
    void updateH(int verID,int pos){
        __updateH(root[verID],0,up,pos);
    }
    void __updateH(int now,int tl,int tr,int pos){//把pos位置节点代表的并查集节点深度加一,非持久化修改
        if(tr-tl==1){
            tree[now].h++;
            return;
        }
        int mid=(tl+tr)/2;
        if(pos<mid){//
            __updateH(tree[now].son[0],tl,mid,pos);
        }else{//�ڵ������ұߣ�������
            __updateH(tree[now].son[1],mid,tr,pos);
        }
    }

	int getRoot(int verID,int pos){//得到可持久化并查集中某个并查集节点的根,这个跟是持久化线段树对应节点的地址，而非并查集的节点编号
	    int now=getPos(root[verID],0,up,pos);
	    while(tree[now].p!=pos){//得到根
            pos=tree[now].p;
            now=getPos(root[verID],0,up,pos);
	    }
        return now;
	}
	bool isSame(int verID,int x,int y){//是不是同一个集合
        return tree[getRoot(verID,x)].p==tree[getRoot(verID,y)].p;
	}

	bool merge(int verID,int x,int y){//合并版本verID所在集合,verID不应该超过rlen,否则输入非法
		int tx=getRoot(verID,x);//持久化线段树节点编号
		int ty=getRoot(verID,y);
		int ux=tree[tx].p;//并查集节点编号
		int uy=tree[ty].p;
		if(ux==uy){//合并失败,因为本来就是同一个集合
            return false;
		}
		if(tree[tx].h>tree[ty].h){
			per_updateP(verID,uy,ux);
		}else if(tree[tx].h<tree[ty].h){
			per_updateP(verID,ux,uy);
		}else{
			per_updateP(verID,ux,uy);
			updateH(verID,uy);
		}
		return true;
	}
};
Per_union tr;

int main(){
   // freopen("P3402_2.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
	int i,l,r,k,n,m,ans,ver;
	scanf("%d%d",&n,&m);
    tr.init(n);
	while(m--){
        scanf("%d",&k);
        if(k==1){
            scanf("%d%d",&l,&r);
            if(!tr.merge(tr.rlen-1,l-1,r-1)){//tr.rlen-1永远是最新版本
                tr.root[tr.rlen]=tr.root[tr.rlen-1];//合并失败也添加新版本
                tr.rlen++;
            }
        }else if(k==2){
            scanf("%d",&ver);
            tr.root[tr.rlen]=tr.root[ver];
            tr.rlen++;
        }else if(k==3){
            scanf("%d%d",&l,&r);
            tr.root[tr.rlen]=tr.root[tr.rlen-1];
            tr.rlen++;
            printf("%d\n", tr.isSame(tr.rlen-1,l-1,r-1));
        }
	}
return 0;
}
