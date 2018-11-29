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
const int P=10007;
struct Node{
    int r,l;
    ll s1,s2,s3,lz1,lz2,lz3;//维护区间和 平方和 立方和,lz1增加的标记 lz2代表乘法的标记，lz3代表更新标记。
    int dis(){
        return r-l;
    }
    void init(){
        s1=s2=s3=0;
        lz1=lz3=0;
        lz2=1;
    }
    void calUpdate(cll a){
        ll a2=a*a%P;
        ll a3=a2*a%P;
        s1=dis()*a%P;
        s2=dis()*a2%P;
        s3=dis()*a3%P;
        lz3=a;
        lz2=1;
        lz1=0;
    }
    void calMul(cll a){
        ll a2=a*a%P;
        ll a3=a2*a%P;
        s1=s1*a%P;
        s2=s2*a2%P;
        s3=s3*a3%P;
        lz1=lz1*a%P;
        lz2=lz2*a%P;
    }
    void calAdd(cll a){
        ll a2=a*a%P;
        ll a3=a2*a%P;
        s3=(s3+dis()*a3+3*a2*s1+3*a*s2)%P;
        s2=(s2+dis()*a2+2*a*s1)%P;
        s1=(s1+dis()*a)%P;
        lz1=(lz1+a)%P;
    }
};

struct LineTree{//区间是左闭 左开[)
    Node tree[MAX*4];
    void buildTree(int now,int l,int r){//建树
        Node &t=tree[now];
        const int mid=(l+r)/2,next=now<<1;
        t.l=l;
        t.r=r;
        t.init();
        if(r-l>1){
            buildTree(next,l,mid);
            buildTree(next+1,mid,r);
        }
    }
    void downLz(const int &now){
        Node &t=tree[now],&tl=tree[now*2],&tr=tree[now*2+1];
        if(t.lz3!=0){
            tr.calUpdate(t.lz3);
            tl.calUpdate(t.lz3);
            t.lz3=0;
        }
        if(t.lz2!=1){
            tr.calMul(t.lz2);
            tl.calMul(t.lz2);
            t.lz2=1;
        }
        if(t.lz1!=0){
            tr.calAdd(t.lz1);
            tl.calAdd(t.lz1);
            t.lz1=0;
        }
    }
    void mergeSon(cint now){
        Node &t=tree[now],&tl=tree[now*2],&tr=tree[now*2+1];
        t.s1=(tl.s1+tr.s1)%P;
        t.s2=(tl.s2+tr.s2)%P;
        t.s3=(tl.s3+tr.s3)%P;
    }
    void seqAdd(int now,int l,int r,ll a){
        Node &t=tree[now],&tl=tree[now*2],&tr=tree[now*2+1];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            t.calAdd(a);
        }else{
            downLz(now);//没走到根节点更新
            if(mid>=r){
                seqAdd(next,l,r,a);
            }else if(mid<=l){
                seqAdd(next+1,l,r,a);
            }else{
                seqAdd(next,l,mid,a);
                seqAdd(next+1,mid,r,a);
            }
            mergeSon(now);
        }
    }
    void seqMul(int now,int l,int r,ll a){
        Node &t=tree[now],&tl=tree[now*2],&tr=tree[now*2+1];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            t.calMul(a);
        }else{
            downLz(now);//没走到根节点更新
            if(mid>=r){
                seqMul(next,l,r,a);
            }else if(mid<=l){
                seqMul(next+1,l,r,a);
            }else{
                seqMul(next,l,mid,a);
                seqMul(next+1,mid,r,a);
            }
            mergeSon(now);
        }
    }
    void update(int now,int l,int r,ll a){
        Node &t=tree[now],&tl=tree[now*2],&tr=tree[now*2+1];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            t.calUpdate(a);
        }else{
            downLz(now);//没走到根节点更新
            if(mid>=r){
                update(next,l,r,a);
            }else if(mid<=l){
                update(next+1,l,r,a);
            }else{
                update(next,l,mid,a);
                update(next+1,mid,r,a);
            }
            mergeSon(now);
        }
    }
    ll searchSum(int now,int l,int r,int k){
        Node &t=tree[now];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            if(k==1){
                return t.s1%P;
            }else if(k==2){
                return t.s2%P;
            }else if(k==3){
                return t.s3%P;
            }
            return 0;
        }else{
            downLz(now);
            ll ans;
            if(mid>=r){
                ans=searchSum(next,l,r,k);
            }else if(mid<=l){
                ans=searchSum(next+1,l,r,k);
            }else{
                ans=(searchSum(next,l,mid,k)+searchSum(next+1,mid,r,k))%P;
            }
            mergeSon(now);
            return ans;
        }
    }
};
LineTree tr;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n,m,l,r,c;
	while(~scanf("%d%d",&n,&m)){
        if(n==0&&m==0)
            break;
        tr.buildTree(1,0,n);
        for(i=0;i<m;i++){
            scanf("%d%d%d%d",&k,&l,&r,&c);
            if(k==1){
                tr.seqAdd(1,l-1,r,c);
            }else if(k==2){
                tr.seqMul(1,l-1,r,c);
            }else if(k==3){
                tr.update(1,l-1,r,c);
            }else if(k==4){
                printf("%lld\n",tr.searchSum(1,l-1,r,c)%P);
            }
        }
	}
return 0;
}
