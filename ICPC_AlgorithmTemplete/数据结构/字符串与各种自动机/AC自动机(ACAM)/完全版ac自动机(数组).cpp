#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
char str[MAX],word[MAX];//str要查找的主串  word输入单词 模式串

const int wordCnt=10010;
const int kind=26;
struct ACautomaton{
    struct Node{
        int id,fail,son[kind];//id是以这个节点为结尾的字符串编号，从0开始，-1代表没有
        void init(){//参数是子节点个数,一般是kind；
            id=-1;
            fail=0;
            memset(son,0,sizeof son);
        }
    };
    Node node[MAX];
    int size,slen;//根节点
    string s[wordCnt];//单词
    int ind[wordCnt];//ind[i]代表了id是i的字符出现几次
    void init(){//////////////////////更改init可以实现不同字符的维护
        slen=size=0;
        node[0].init();//初始化根节点
    }
    int toInt(char a){
        return a-'a';
    }
    void insert(char *word){
        int c,now=0,len=strlen(word);
        for(int i=0;i<len;i++ ){
            c=toInt(word[i]);//判断是第几个字母
            if(node[now].son[c]==0){//如果该字符节点不存在，加入树中
                node[now].son[c]=++size;
                node[size].init();
            }
            now=node[now].son[c];//指针移动至下一层
        }
        node[now].id=slen;
        s[slen++]=word;
    }
    void buildFail(){//bfs连接字典树的fali路按照一下原则：从它父节点开始走fali的路，如果走到哪个节点的子节点和当前节点字母相等，就连接它们
        queue<int>que;
        for(int i=0;i<kind;i++){//遍历根节点子树
            int rs=node[0].son[i];
            if(rs){
                node[rs].fail=0;
                que.push(rs);
            }
        }
        while(!que.empty()){
            int now=que.front();//获取队首，再出队列
            que.pop();
            for(int i=0;i<kind;i++){//逐个看刚才的出对节点的子节点是否存在
                int &rs=node[now].son[i];
                if(rs){//如果这个字母存在
                    node[rs].fail=node[node[now].fail].son[i];
                    que.push(rs);//广搜，继续入对
                }else{
                    rs=node[node[now].fail].son[i];
                }
            }
        }
    }
    int query(char *str){
        memset(ind,0,sizeof ind);
        int i,t,cnt=0,now=0,len=strlen(str);//获取主串长度
        for(i=0;i<len;i++){
            now=node[now].son[toInt(str[i])];
            for(t=now;t;t=node[t].fail){
                if(node[t].id!=-1){
                    cnt++;
                    ind[node[t].id]++;
                }
            }
        }
        for(i=0;i<slen;i++){
            printf("%s %d\n",s[i].c_str(),ind[i]);
        }
        return cnt;
    }
};
ACautomaton ac;
int main(int argc,char *argv[]){
	int n,i;
	while(~scanf("%d",&n),n>0){
        ac.init();
		for(i=0;i<n;i++){
			scanf("%s",word);
			ac.insert(word);
		}
		ac.buildFail();
		scanf("%s",str);
		ac.query(str);
	}
return 0;
}
/*
6
beta
alpha
haha
delta
dede
tata
dedeltalphahahahototatalpha
*/
