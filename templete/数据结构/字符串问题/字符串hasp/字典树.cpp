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
        Node *now=root,*pre;
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
    bool matchWord(char *word){
        int c;
        int len=strlen(word);
        Node *now=root;
        for(int i=0;i<len;i++){
            c=word[i]-'a';//�ж��ǵڼ�����ĸ
            if(now->son[c]==NULL){//������ַ��ڵ㲻����
                return false;
            }
            now=now->son[c];//ָ���ƶ�����һ��
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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,len;
	Tire dir;
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

