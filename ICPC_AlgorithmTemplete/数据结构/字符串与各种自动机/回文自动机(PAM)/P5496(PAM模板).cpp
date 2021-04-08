#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=2000010;
const int mod=1e9+7;

const int CHARCNT=26;
inline int toInt(const char &a){
    return a-'a';
}
struct PAM{
    const int r0=0,r1=1;
    int size,last;//last代表当前最后一个节点
    char *str;
    struct Node{
        int fail,son[CHARCNT];//fail指针和son儿子,son如果为空则指向r0,因为r0=0
        int len;//代表从根走到当前节点字符串两倍构成的回文串的长度
        int num;//代表以当前节点为狐头的边所代表的字符位置结尾的回文后缀数量，比如abba的s[3]=‘a’的num是2

    };
    Node tree[MAX];
    bool init(char *str){//传入一个回文串
        int i,len=strlen(str);
        for(i=0;i<len/2&&str[i]==str[len-i-1];i++);
        if(i<len/2){//判断是不是回文串
            return false;
        }
        this->str=str;
        insert(str);
        init();
        return true;
    }
    void init(){
        last=0;
        size=2;
        tree[0].fail=1;//fail[0]指向奇数根
        tree[1].fail=0;//fail[1]指向0
        tree[0].len=0;
        tree[1].len=-1;//奇数节点的PAM是-1
        tree[0].num=0;
        tree[1].num=0;//初始点的num为0
    }
    int getFail(int now,int i){//得到插入第i个字符时，now的fail的位置，i从0开始
        while(i-tree[now].len-1<0||str[i-tree[now].len-1]!=str[i])
            now=tree[now].fail;
        return now;
    }
    void insert(char *s){//插入s字符串的第几个位置
        int i,len=strlen(s);
        for(i=0;i<len;i++){
            insert(s[i],i);
        }
    }
    void insert(char a,int i){//插入字符
        int pos=getFail(last,i);
        int k=toInt(a);
        str[i]=a;
        Node &posNode=tree[pos];
        if(!posNode.son[k]){//没有就新建一个
            Node &newNode= tree[size++];   //在posNode下新建节点，伪指针索引的新建节点，newNode为新节点引用，下面对newNode属性赋值
        	newNode.fail=tree[getFail(posNode.fail,i)].son[k];//失败指针指向
        	posNode.son[k]=size-1;//posNode的儿子指向新节点的地址
        	newNode.len=posNode.len+2;//新节点的len为父亲+2，因为一个节点代表在上一个字符串前后各加一个字符
            newNode.num=tree[newNode.fail].num+1;//当前字符为结尾的不同的回文串的数量，是它的fail指针所指节点的num+1
		}//不存在建立点，存在直接走过去
        last=posNode.son[k];
    }

};
PAM pam;

char str[MAX];
int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m,len,ans;
    scanf("%s",str);
    len=strlen(str);
    pam.init();
    pam.str=str;
    k=0;
    for(i=0;i<len;i++){
        if(i)
            str[i]=(str[i]-97+k)%26+97;
        pam.insert(str[i],i);
        k=pam.tree[pam.last].num;
        printf("%d%c",k,i==len-1?'\n':' ');
    }

return 0;
}

