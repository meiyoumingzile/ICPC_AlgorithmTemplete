#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
char str[MAX],word[MAX];//str要查找的主串  word输入单词 模式串
const int kind=26;
struct ACautomaton{
    struct Node{
        int id;//以这个节点为结尾的字符串编号，从0开始，-1代表没有
        Node *fail,*son[kind];
        Node(Node *r){//参数是子节点个数,一般是kind；
            id=-1;
            fail=r;
            for(int i=0;i<kind;i++)
                son[i]=r;
        }
    };
    Node *root;//根节点
    string s[1000];//单词
    int ind[1000];//ind[i]代表了id是i的字符出现几次
    int slen;
    ACautomaton(int n){
        init();
    }
    void init(){//////////////////////更改init可以实现不同字符的维护
        root=new Node(NULL);
        root->fail=root;
        slen=0;
        memset(ind,0,sizeof ind);
        for(int i=0;i<kind;i++){//默认是小写字母
            root->son[i]=root;
        }
    }
    void insert(char *word){
        int c;
        int len=strlen(word);
        Node *now=root;
        for(int i=0;i<len;i++ ){
            c=word[i]-'a';//判断是第几个字母
            if(now->son[c]==root){//如果该字符节点不存在，加入树中
                now->son[c]=new Node(root);
            }
            now=now->son[c];//指针移动至下一层
        }
        now->id=slen;
        s[slen++]=word;
    }

    void buildFail(){//bfs连接字典树的fali路按照一下原则：从它父节点开始走fali的路，如果走到哪个节点的子节点和当前节点字母相等，就连接它们
        queue<Node*>que;
        Node *now,*p,*next;
        for(int i=0;i<kind;i++){//遍历根节点子树
            if(root->son[i]!=root){
                root->son[i]->fail=root;
                que.push(root->son[i]);
            }
        }
        while(!que.empty()){
            now=que.front();//获取队首，再出队列
            que.pop();
            for(int i=0;i<kind;i++){//逐个看刚才的出对节点的子节点是否存在
                if(now->son[i]!=root){//如果这个字母存在
                    now->son[i]->fail=now->fail->son[i];
                    que.push(now->son[i]);//广搜，继续入对
                }else{
                    now->son[i]=now->fail->son[i];
                }
            }
        }
    }

    int query(char *str){
        int i,cnt=0,len=strlen(str);//获取主串长度
        Node *now=root,*t;
        int maxCnt=-1;
        for(i=0;i<len;i++){
            now=now->son[str[i]-'a'];
            for(t=now;t!=root;t=t->fail){
                if(t->id!=-1){
                    cnt++;
                    ind[t->id]++;
                    maxCnt=max(maxCnt,ind[t->id]);
                }
            }
        }
        printf("%d\n",maxCnt);
        for(i=0;i<slen;i++){
            if(maxCnt==ind[i]){
                printf("%s\n",s[i].c_str());
            }
        }
        return cnt;
    }
};


int main(int argc,char *argv[]){
	int n,i;
	while(~scanf("%d",&n),n>0){
        ACautomaton *ac=new ACautomaton(n);
		for(i=0;i<n;i++){
			scanf("%s",word);
			ac->insert(word);
		}
		ac->buildFail();
		scanf("%s",str);
		ac->query(str);
        delete ac;
	}
return 0;
}

