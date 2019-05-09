#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=100010;
const int mod=1e9+7;
char s1[MAX],s2[MAX];
int next1[MAX],next2[MAX];
void getnext1(int *nex,char *s2){//原始next[0]=0数组
    int j,k,len2=strlen(s2);
    nex[0]=0;
    for(j=1;j<len2;j++){
        k=nex[j-1];
        while(k>0&&s2[k]!=s2[j]){
            k=nex[k-1];
        }
        if(s2[k]!=s2[j]){
            nex[j]=k;
        }else{
            nex[j]=k+1;
        }
    }
}
void getnext1_1(int *nex,char *word){
    int i,k,len=strlen(word);//模版字符串长度
    nex[0] = 0;
    for(i=1,k=0;i<len;i++){
        while(k&&word[i]!=word[k])
            k=nex[k-1];
        if(word[i]==word[k]){
            k++;
        }
        nex[i] = k;
    }
}
void getnext2(int *nex,char *s2){//原始next[0]=-1数组
    int j,k,len2=strlen(s2);
    nex[0]=-1;
    for(j=1;j<len2;j++){
        k=nex[j-1];
        while(k>-1&&s2[k]!=s2[j-1]){
            k=nex[k];
        }
        nex[j]=k+1;
    }
}
void getnext2_1(int *nex,char *word){
    nex[0]=-1;
	int k=-1,j=0, num=(int)strlen(word);
	while(j<num){
		if(k==-1||word[j]==word[k]){
			j++;k++;
			nex[j]=k;
		}else k=nex[k];
	}
}
void getnext3(int *nex,char *s2){//nextval数组
    int j,k,len2=strlen(s2);
    nex[0]=-1;k=-1;
    for(j=1;j<len2;j++){
        while(k>-1&&s2[k]!=s2[j-1]){
            k=nex[k];
        }
        k++;
        nex[j]=s2[k]==s2[j]?nex[k]:k;
    }
}
void getnext3_1(int *nex,char *word) {
    nex[0]=-1;
	int k=-1,j=0, num=(int)strlen(word);
	while(j<num){
		if(k==-1||word[j]==word[k]){
			j++;k++;
			if(word[j]!=word[k]) nex[j]=k;
			else nex[j]=nex[k];
		}else k=nex[k];
	}
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    string a,b;
    int i,j,len;
    while(1){//查找s1中所有匹配的s2
        scanf("%s",s2);
        len=strlen(s2);
        getnext1(next2,s2);
        for(i=0;i<len;i++){
            printf("%d ",next2[i]);
        }printf("\n");
        getnext2(next2,s2);
        for(i=0;i<len;i++){
            printf("%d ",next2[i]);
        }printf("\n");
        getnext3(next2,s2);
        for(i=0;i<len;i++){
            printf("%d ",next2[i]);
        }printf("\n");
    }
return 0;
}
