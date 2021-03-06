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


int ans[MAX];
const int CHARCNT=26;
inline int toInt(const char &a){
    return a-'a';
}
struct SAM{
    int root,last,size;
    int p[MAX*2],nodelen[MAX*2],son[MAX*2][CHARCNT],eplen[MAX*2],du[MAX*2];
    //eplen[i]是编号为i的节点endpos集合元素个数,du是只看p指针的每个点入度数
    SAM(){
       clear();
    }
    void clear(){//初始化
        root=last=0;//根节点编号是0
        memset(son[0],-1,sizeof(son[0]));
        memset(du,0,sizeof(du));
        p[0]=-1;
        nodelen[0]=0;
        size=1;
    }
    int addNode(int len,bool isMain){//按照编号顺序添加节点
        int sz=size++;
        memset(son[sz],-1,sizeof(son[sz]));
        nodelen[sz]=len;
        eplen[sz]=isMain;
        return sz;
    }
    int push(const char &a){
        int f=toInt(a),now=last,node,q,nq;
        node=addNode(nodelen[last]+1,1);
        while(now!=-1&&son[now][f]==-1){
            son[now][f]=node;
            now=p[now];
        }
        if(now!=-1){
            q=son[now][f];
            if(nodelen[now]+1==nodelen[q]){
                p[node]=q;
                du[q]++;
            }else{
                nq=addNode(nodelen[now]+1,0);
                memcpy(son[nq], son[q], sizeof son[q]);
                p[nq]=p[q];
                p[q]=p[node]=nq;
                du[nq]+=2;
                while(now!=-1&&son[now][f]==q){
                    son[now][f]= nq;
                    now=p[now];
                }
            }

        }else{
             p[node]=root;
             du[root]++;
        }
        last=node;
        return nodelen[node]- nodelen[p[node]];
    }
    void getEplen(){//后缀自动机的拓扑排序求eplen
        rg int i,now;
        stack<int>st;
        for(i=1;i<size;i++){
            if(du[i]==0)
                st.push(i);
        }
        while(!st.empty()){
            now=st.top();
            st.pop();
            eplen[p[now]]+=eplen[now];
            if(--du[p[now]]==0){
                st.push(p[now]);
            }
        }
    }
};
SAM sam;

char str[MAX];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	rg int i,n,len;
	scanf("%s",str);
    len=strlen(str);
    for(i=0;i<len;i++){
        n=sam.push(str[i]);
    }
    sam.getEplen();
    memset(ans,0,sizeof ans);
    for(i=2*len;i>0;i--){
        if(sam.eplen[i]>0){
            ans[sam.nodelen[i]]=max(ans[sam.nodelen[i]],sam.eplen[i]);
           // printf("(%d %d) ",i,sam.eplen[i]);
        }
    }//printf("\n");
    for(i=len-1;i>0;i--){
        ans[i]=max(ans[i],ans[i+1]);
    }
    for(i=1;i<=len;i++){
        printf("%d\n",ans[i]);
    }

return 0;
}
