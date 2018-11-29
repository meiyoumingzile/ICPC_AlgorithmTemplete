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
struct Node{
    Node *p=NULL,*son[CHARCNT];
    int len;
    Node(int len=0){
        for(rg int i=0;i<CHARCNT;i++)
            son[i]=NULL;
        this->len=len;
    }
};
inline int toInt(const char &a){
    return a-'a';
}
struct SAM{
    Node *root;
    Node *last;
    SAM(){
        root=new Node();
        last=root;
    }
    int push(const char &a){
        int f=toInt(a);
        Node *now=last,*q;
        Node *node=new Node(last->len+1);
        while(now&&now->son[f]==NULL){
            now->son[f]= node;
            now=now->p;
        }
        if(now){
            q=now->son[f];
            if(now->len+1==q->len){
                node->p=q;
            }else{
                Node *nq=new Node(now->len+1);
                for(rg int i=0;i<26;i++)
                    nq->son[i]=q->son[i];
                nq->p=q->p;
                q->p=node->p=nq;
                while(now&&now->son[f]==q){
                    now->son[f]= nq;
                    now=now->p;
                }
            }

        }else{
             node->p=root;
        }
        last=node;
        return node->len - node->p->len;
    }
};
SAM *sam=new SAM();

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
        ans+=sam->push(str[i]);
    }
    printf("%lld\n",ans);
return 0;
}
/*
ababababdaedsrfhkl
*/
