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
const int MAX=1000010;
const int mod=1e9+7;


const int CHARCNT=26;
inline int toInt(const char &a){
    return a-'a';
}
struct SAM{
    int root,last,size;
    int fail[MAX*2],nodelen[MAX*2],son[MAX*2][CHARCNT];
    SAM(){
       clear();
    }
    void clear(){
        root=last=0;//根节点编号是0
        memset(son[0],-1,sizeof(son[0]));
        fail[0]=-1;
        nodelen[0]=0;
        size=1;
    }
    int addNode(int len){//按照编号顺序添加节点
        memset(son[size],-1,sizeof(son[size]));
        nodelen[size]=len;
        return size++;
    }
    int push(const char &a){
        int f=toInt(a),now=last,node,q,nq;
        node=addNode(nodelen[last]+1);
        while(now!=-1&&son[now][f]==-1){
            son[now][f]=node;
            now=fail[now];
        }
        if(now!=-1){
            q=son[now][f];
            if(nodelen[now]+1==nodelen[q]){
                fail[node]=q;
            }else{
                nq=addNode(nodelen[now]+1);
                memcpy(son[nq], son[q], sizeof son[q]);
                fail[nq]=fail[q];
                fail[q]=fail[node]=nq;
                while(now!=-1&&son[now][f]==q){
                    son[now][f]= nq;
                    now=fail[now];
                }
            }

        }else{
             fail[node]=root;
        }
        last=node;
        return nodelen[node]- nodelen[fail[node]];
    }
};
SAM sam;

char str[MAX];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	rg int i,n,len;
	ll ans=0;
	scanf("%s",str);
    len=strlen(str);
    for(i=0;i<len;i++){
        n=sam.push(str[i]);
        printf("%d\n",n);
        ans+=n;
    }
    printf("%lld\n",ans);
return 0;
}
