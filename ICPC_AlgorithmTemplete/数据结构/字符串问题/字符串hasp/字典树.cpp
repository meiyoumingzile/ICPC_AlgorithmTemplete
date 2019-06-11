#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;
const int kind=26;
struct Node{
    Node *son[kind];
    Node(Node *r=NULL){//参数是子节点个数,一般是kind；
        for(int i=0;i<kind;i++)
            son[i]=r;
    }
};
struct Tire{
    Node *root=new Node(NULL);
    Node* insert(char *word){
        int c;
        int len=strlen(word);
        Node *now=root,*pre;
        for(int i=0;i<len;i++ ){
            c=word[i]-'a';//判断是第几个字母
            if(now->son[c]==NULL){//如果该字符节点不存在，加入树中
                now->son[c]=new Node(NULL);
            }
            pre=now;
            now=now->son[c];//指针移动至下一层
        }
        return pre;
    }
    bool matchWord(char *word){
        int c;
        int len=strlen(word);
        Node *now=root;
        for(int i=0;i<len;i++){
            c=word[i]-'a';//判断是第几个字母
            if(now->son[c]==NULL){//如果该字符节点不存在
                return false;
            }
            now=now->son[c];//指针移动至下一层
        }
        return 1;
    }
};
char str[MAX];
vector<string>strlist;
map <string,vector<int> >ind;
bool cmp(const string &s1,const string &s2){
    int len1=ind[s1].size();
    int len2=ind[s2].size();
    if(len1==len2){
        s1>s2;
    }
    return len1>len2;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,len;
	Tire dir;
	//freopen("dir.txt","r",stdin); //输入重定向，输入数据将从dir.txt文件中读取
    while(~scanf("%s",str)){//输入字典
        dir.insert(str);
    }
   // freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    int pos=0;
    vector<int>li;
    while(~scanf("%s",str)){//输入数据
        len=strlen(str);
        strlwr(str);
        for(i=len-1;i>=0&&str[i]>='a'&&str[i]<='z';i--){
            str[i]=0;
        }
        if(dir.matchWord(str)==0){
            if(ind.count(str)>0){
                ind[str].push_back(pos);
            }else{
                strlist.push_back(str);
                ind[str]=li;
                ind[str].push_back(pos);
            }
        }
        pos+=len+1;
    }
    sort(strlist.begin(),strlist.end(),cmp);
    for(i=0;i<strlist.size();i++){
        string &s=strlist[i];
        printf("%s %d",s,ind[s].size());
        len=ind[s].size();
        for(j=0;j<len;j++){
            printf("%d ",ind[s][j]);
        }printf("\n");
    }
return 0;
}

