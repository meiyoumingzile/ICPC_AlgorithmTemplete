#include<bits/stdc++.h>
//#include<windows.h>
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
        int cnt;//几个单词以这个为结尾
        Node *dan,*fail,*son[kind];
        Node(){//参数是子节点个数,一般是kind；
            cnt=0;
            fail=dan=NULL;
            for(int i=0;i<kind;i++)
                son[i]=NULL;
        }
    };
    Node *root;//根节点
    char sonChar[kind];////处理的所有小写字母
    ACautomaton(int n){
        init();
        root=new Node();
    }
    void init(){//////////////////////更改init可以实现不同字符的维护
        for(int i=0;i<kind;i++){//默认是小写字母
            sonChar[i]='a'+i;
        }
    }
    void insert(char *word){
         int c;
         int len=strlen(word);
         Node *now=root;
         for(int i=0;i<len;i++ ){
             c=word[i]-'a';//判断是第几个字母
             if(!now->son[c]){//如果该字符节点不存在，加入树中
                now->son[c]=new Node();//加入树中
             }
             now=now->son[c];//指针移动至下一层
         }
         now->cnt++;
    }

    void buildFail(){//bfs连接字典树的fali路按照一下原则：从它父节点开始走fali的路，如果走到哪个节点的子节点和当前节点字母相等，就连接它们
        queue<Node*>que;
        Node *now,*p,*next;
        root->fail=root;
        for(int i=0;i<kind;i++){//遍历根节点子树
            if(root->son[i]){
                root->son[i]->fail=root;
                que.push(root->son[i]);
            }
        }
        while(!que.empty()){
            now=que.front();//获取队首，再出队列
            que.pop();
            for(int i=0;i<kind;i++){//逐个看刚才的出对节点的子节点是否存在
                next=now->son[i];
                p=now->fail;
                if(next){//如果这个字母存在
                    next->fail=p->son[i];
                    que.push(next);//广搜，继续入对
                }else{
                    now->son[i]=p->son[i];
                }
            }
        }
    }

    int query(char *str){
        int i=0,cnt=0,index,j=0,len=strlen(str);//获取主串长度
        Node *now=root,*t;
        for(i=0;i<len;i++){
            index=str[i]-'a';//还是获取第几个
            now=now->son[index];
            for(t=now;t&&t->cnt!=-1;t=t->fail){
                cnt+=t->cnt;
                t->cnt=-1;
            }
        }
        return cnt;
    }
};


int main(int argc,char *argv[]){
	int n,i;
	while(~scanf("%d",&n)){
		ACautomaton *ac=new ACautomaton(n);
		for(i=0;i<n;i++){
			scanf("%s",word);
			ac->insert(word);
		}
		ac->buildFail();
		scanf("%s",str);
		printf("%d\n",ac->query(str));
		delete ac;
	}
return 0;
}

