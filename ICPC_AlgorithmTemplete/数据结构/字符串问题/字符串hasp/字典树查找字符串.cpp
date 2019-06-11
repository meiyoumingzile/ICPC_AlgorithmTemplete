#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;
const int kind=26;
struct Node{
    list<int>li;
    string s="";
    Node *son[kind];
    Node(Node *r=NULL){//�������ӽڵ����,һ����kind��
        for(int i=0;i<kind;i++)
            son[i]=r;
    }
};
struct Tire{
    Node *root=new Node(NULL);
    Node* insert(char *word){
        int c;
        int len=strlen(word);
        Node *now=root,*pre=NULL;
        for(int i=0;i<len;i++ ){
            c=word[i]-'a';//�ж��ǵڼ�����ĸ
            if(now->son[c]==NULL){//������ַ��ڵ㲻���ڣ���������
                now->son[c]=new Node(NULL);
            }
            pre=now;
            now=now->son[c];//ָ���ƶ�����һ��
        }
        return pre;
    }
    Node* matchWord(char *word){
        int c;
        int len=strlen(word);
        Node *now=root,*pre=NULL;
        for(int i=0;i<len;i++){
            c=word[i]-'a';//�ж��ǵڼ�����ĸ
            if(now->son[c]==NULL){//������ַ��ڵ㲻����
                return NULL;
            }
            pre=now;
            now=now->son[c];//ָ���ƶ�����һ��
        }
        return pre;
    }
};
char str[MAX];
vector<Node *>strlist;
Tire dir,errodir;
void dfs(Node *now){
    if(now->li.size()>0){
        strlist.push_back(now);
    }
    for(int i=0;i<kind;i++){
        if(now->son[i]){
            dfs(now->son[i]);
        }
    }
}
bool cmp(const Node *a,const Node *b){
    int len1=a->li.size();
    int len2=b->li.size();
    if(len1==len2){
        a->s>b->s;
    }
    return len1>len2;
}
void strlwr(char *s){
    int len=strlen(s);
    for(int i=0;i<len;i++){
        if(s[i]>='A'&&s[i]<='Z')
            s[i]-=32;
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,len;
	//freopen("dir.txt","r",stdin); //�����ض����������ݽ���dir.txt�ļ��ж�ȡ
    while(~scanf("%s",str)){//�����ֵ�
        dir.insert(str);
    }
   // freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    int pos=0;
    vector<int>li;
    while(~scanf("%s",str)){//��������
        len=strlen(str);
        strlwr(str);
        for(i=len-1;i>=0&&(str[i]<'a'||str[i]>'z');i--){
            str[i]=0;
        }
        if(dir.matchWord(str)==0){
            Node *now=errodir.insert(str);
            now->li.push_back(pos);
            now->s=str;
        }
        pos+=len+1;
    }
    dfs(errodir.root);
    sort(strlist.begin(),strlist.end(),cmp);
    for(i=0;i<strlist.size();i++){
        string &s=strlist[i]->s;
        printf("%s %d",s.c_str(),strlist[i]->li.size());
        for(auto a:strlist[i]->li){
            printf(" %d",a);
        }printf("\n");
    }
return 0;
}
/*
hh jj kkk lkj
ss sad das sad kkk hh ddd
*/
