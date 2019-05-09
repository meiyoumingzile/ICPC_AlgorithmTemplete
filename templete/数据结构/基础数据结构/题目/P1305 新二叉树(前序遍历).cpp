#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=10010;
const int mod=1e9+7;
char s[5];
struct Node{
    char val;
    Node(char a){
        val=a;
        left=NULL;
        right=NULL;
    }
    Node *left,*right;
};


Node *ind[MAX];
int getC(char a){
    return a-'a';
}

void print(Node *now){
    printf("%c",now->val);
    if(now->left!=NULL){
        print(now->left);
    }
    if(now->right!=NULL){
        print(now->right);
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int N,i,a,b,c;
    cin>>N;
    Node *now,*le,*ri,*head;
    for(i=0;i<N;i++){
        ind[i]=NULL;
    }
    for(i=0;i<N;i++){
        scanf("%s",s);
        a=getC(s[0]);
        b=getC(s[1]);
        c=getC(s[2]);
        if(ind[a]==NULL){
            now=new Node(s[0]);
            ind[a]=now;
            if(i==0){
                head=now;
            }
        }else{
            now=ind[a];
        }
        if(s[1]!='*'){
            if(ind[b]==NULL&&s[1]!='*'){
                le=new Node(s[1]);
                ind[b]=le;
            }else{
                le=ind[b];
            }
        }else{
            le=NULL;
        }
        if(s[2]!='*'){
            if(ind[c]==NULL){
                ri=new Node(s[2]);
                ind[c]=ri;
            }else{
                ri=ind[c];
            }
        }else{
            ri=NULL;
        }
        now->left=le;
        now->right=ri;
    }
    print(head);
    printf("\n");
return 0;
}
