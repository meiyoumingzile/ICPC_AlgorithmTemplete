#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;
char s1[MAX],s2[MAX];
int nex[MAX];
vector<int>ind;
void getnext2(int *nex,char *word) {//next2,用来匹配第一次的位置
    nex[0]=-1;
	int k=-1,j=0, num=(int)strlen(word);
	while(j<num){
		if(k==-1||word[j]==word[k]){
			j++;k++;
			nex[j]=k;
		}else k=nex[k];
	}
}
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
            printf("%d\n",i-len2);
            j=nex[j];
        }
	}
}
int main(int argc,char *argv[]){
    int i,len;
    while(~scanf("%s%s",s1,s2)){//查找s1中所有匹配的s2
        getnext2(nex,s2);
        len=strlen(s2);
        for(i=0;i<len;i++){
            printf("%d ",nex[i]);
        }printf("\n");
        KMP(s1,s2,nex);
    }
return 0;
}
