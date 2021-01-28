#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

const int CHARCNT=26;
inline int toInt(const char &a){
    return a-'a';
}
struct PAM{
    const int r0=0,r1=1;
    int size,last;
    int fail[MAX],nodelen[MAX],num[MAX],son[MAX][CHARCNT];//p代表fail指针，nodelen
    void clear(){
        last=0;
        memset(son[0],-1,sizeof(son[0]));
        fail[0]=1;fail[1]=-1;//0跟的fail必须到1，1没有fail
        nodelen[0]=0;nodelen[1]=-1;
        size=1;
    }

    void insert(char *s,int si){//插入s字符串的第几个位置
        int i,j,k,p=last;
        while(s[si-nodelen[p]-1]!=s[si]){//找到该插入的位置
            p=fail[p];
        }

    }
    void build(char *s){//用s构建回文自动记
        clear();
        /*len=strlen(str);
        for(int i=0;i<len;i++){
            pam.insert(str,i);
        }
        */
    }
};
PAM pam;

char str[MAX];
int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m,len;
    scanf("%s",str);
    len=strlen(str);
    k=0;
    for(i=0;i<len;i++){
        str[i]=(str[i]-97+k])%26+97;
        pam.insert(str,i);
        k=0;
    }

return 0;
}

