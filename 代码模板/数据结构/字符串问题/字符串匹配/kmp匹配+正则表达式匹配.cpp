#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=10010;
const int mod=1e9+7;
char s1[MAX],s2[MAX];
int nex[MAX];
vector<int>ind;
void getnext2(int *nex,char *word) {//next2,用来匹配所有的位置
    nex[0]=-1;
	int k=-1,j=0, num=(int)strlen(word);
	while(j<num){
		if(k==-1||word[j]==word[k]){
			j++;
			k++;
			nex[j]=k;
		}else k=nex[k];
	}
}
void getnext1(int *nex,char *word) {//next1,用来匹配第一次的位置
    nex[0]=-1;
	int k=-1,j=0, num=(int)strlen(word);
	while(j<num){
		if(k==-1||word[j]==word[k]){
			j++;k++;
			nex[j]=k;
		}else k=nex[k];
	}
}
int KMP1(char *s1,char *s2,int *nex){//在s1中找s2,找第一次出现位置
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
            return i-len2;
        }
	}
}
void KMP2(char *s1,char *s2,int *nex){//在s1中找s2,找全部出现位置
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
    while(~scanf("%s%s",s1,s2)){//查找s2中所有匹配的s1，s2是个
        getnext2(nex,s1);
        len=strlen(s2);
        for(i=0;i<len;i++){
            printf("%d ",nex[i]);
        }printf("\n");
        KMP2(s1,s2,nex);
    }
return 0;
}
