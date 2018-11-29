#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
int nex[MAX];
char s1[MAX],s2[MAX];
void getnext1(int *nex,char *word) {//nexk,用来匹配第一次的位置
    int j=0,k=-1,len=strlen(word);
    nex[0]=-1;
    while(j<len){
        if(k==-1 || word[j]==word[k]){
            nex[++j]=++k;
        }else{
            k=nex[k];
        }
    }
}
void KMP(char *s1,char *s2,int *nex){//在s1中找s2,s2相当于word
	int i=0,j=0,len1=(int)strlen(s1),len2=(int)strlen(s2);
	while(i<len1&&j<len2){
		if(j==-1||s1[i]==s2[j]){
            i++;
            j++;
        }else{
            j=nex[j];
        }
		if(j==len2){
            printf("%d\n",i+1-len2);
            j=nex[j];
        }
	}
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n,len;
	scanf("%s%s",s1,s2);
	getnext1(nex,s2);
	len=strlen(s2);
	KMP(s1,s2,nex);
	for(i=1;i<=len;i++){
        printf("%d ",nex[i]);
	}printf("\n");
return 0;
}

