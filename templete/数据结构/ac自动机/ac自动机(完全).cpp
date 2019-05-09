#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;


char word[100];//输入单词 模式串
char str[1000010];// 需要查找的 主串
struct ACautomaton{
    const int kind=26;
    vector<char>sonChar;////处理的所有小写字母
    map<char,int>sonInd;//索引某个字符在第几个
    struct Node{
        string char_end;
        Node *danger=NULL;
        Node **son;//Trie每个节点的26个子节点，NULL表示不存在
        Node *fail=NULL; //失败指针
        Node(int cnt){//参数是子节点个数,一般是kind；
            son=new Node*[cnt];
            char_end="";
            for(int i=0;i<cnt;i++)
                son[i]=NULL;
        }
    };


    Node *root;//根节点
    ACautomaton(int n){
        s=new string[n];
        this->init();
        root=new Node(kind);
    }


    string *s;
    map<string,int>letter_number;//记录某个单词个数

    int s_i=0;
    //map<string,int>pos;//记录位置

    void init(){//////////////////////更改init可以实现不同字符的维护
        for(int i=0;i<kind;i++){//默认是小写字母
            sonChar[i]='a'+i;
            sonInd[sonChar[i]]=i;
        }
    }
    void AC_insert(char *word){
         int index;
         int len=strlen(word);
         Node *tree=root;
         for(int i=0;i<len;i++ ){
             index=word[i]-'a';//判断是第几个字母
             if(!tree->son[index]){//如果该字符节点不存在，加入树中
                Node *newNode=new Node(kind);
                tree->son[index]=newNode;//加入树中
             }
             tree=tree->son[index];//指针移动至下一层
         }
         //pos[word]=s_i;
         tree->char_end=s[s_i++]=word;  //单词结尾节点count+1做标记
    }

    void build_ac_automation(){//bfs连接字典树的fali路按照一下原则：从它父节点开始走fali的路，如果走到哪个节点的子节点和当前节点字母相等，就连接它们
        queue<Node*>Q;
        Q.push(root);//把头入队
        Node *que_temp,*p,*tree;
        while(!Q.empty()){
            que_temp=Q.front();//获取队首，再出队列
            Q.pop();
            for(int i=0;i<kind;i++){//逐个看刚才的出对节点的子节点是否存在
                if(que_temp->son[i]!=NULL){//如果这个字母存在
                    if(que_temp==root){//如果那个出队的节点是根·，根的fali路都直接到根就可以
                        que_temp->son[i]->fail=root;
                    }else{//注意要连的fali路是当前出队列的子节点而不是当前出对的节点
                        p=que_temp->fail;//注意要连的fali路是当前出队列的子节点而不是当前出对的，所以根据规则应当沿着当前fail走
                        while(p!=NULL){//直到p是空节点为止，即根节点的fail才是空的
                           if(p->son[i]!=NULL){//如果某个节点的子节点和要找的节点相同，把它们连接
                               que_temp->son[i]->fail=p->son[i];
                               break;
                           }
                           p=p->fail;//继续沿着fail走
                        }
                        if(p==NULL){//如果经历了上面while到了根节点还没有找到,就说明应该直接去连接根节点就好了
                            que_temp->son[i]->fail=root;
                        }else if(que_temp->son[i]->fail->char_end!=""&&que_temp->son[i]->char_end==""){
                            que_temp->son[i]->danger=que_temp->son[i]->fail;
                        }
                    }
                    Q.push(que_temp->son[i]);//广搜，继续入对
                 }
             }
         }
    }

    int query(){
        int i=0,cnt=0,index,j=0,
            len=strlen(str);//获取主串长度
        Node *p=root;
        for(i=0;i<len;i++){
            index=str[i]-'a';//还是获取第几个
            Node *nowDanger=p;
            while(nowDanger->danger!=NULL){
                letter_number[nowDanger->danger->char_end]++;
                cnt++;
                nowDanger=nowDanger->danger;
            }
            while(p->son[index]==NULL&&p!=root)//如果主串当前字母在非根某节点的分叉里不存在，这样不能直接回根而是沿着fail路走继续匹配，类似kmp沿着son数组找
                p=p->fail;
            p=p->son[index];//找到后p指向该节点，反正就是匹配一个，是否成功看下一行吧
            if(p==NULL)//如果到了根都没有，或者是没找到也就是上面的son[index]是空的，只能从根找
                p=root;
            Node *temp=p;//匹配该节点后，沿其失败指针回溯，判断其他节点是否匹配
            while(temp!=root&&temp->char_end!=""){//回到根了结束
                letter_number[temp->char_end]++;
                cnt++;
                temp=temp->fail;//回溯失败指针继续寻找下一个满足条件的节点
            }
        }
        return cnt;
    }
    void print(int n){
        for(int i=0;i<n;i++){
            cout<<s[i];
            printf("  %d\n",letter_number[s[i]]);
        }
    }
};


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    	int n,i;
	while(~scanf("%d",&n),n>0){
        ACautomaton *ac=new ACautomaton(n);
		for(i=0;i<n;i++){
			scanf("%s",word);
			ac-> AC_insert(word);
		}
		ac->build_ac_automation();
		scanf("%s",str);
		ac->query();
        delete ac;
	}
return 0;
}

