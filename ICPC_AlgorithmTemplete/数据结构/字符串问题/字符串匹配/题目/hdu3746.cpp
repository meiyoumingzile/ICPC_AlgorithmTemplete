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
int KMP1(char *s1,char *s2,int *nex){//在s1中找s2,找第一次出现位置，next[0]=-1可用
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
	return -1;
}
void KMP2(char *s1,char *s2,int *nex){//在s1中找s2,找全部出现位置，next[0]=-1可用
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
int KMP3(char *s1,char *s2,int *nex){//在s1中找s2,找第一次出现的位置，next[0]=0可用
	int i=0,j=0,len1=(int)strlen(s1),len2=(int)strlen(s2);
	while(i<len1){
		if(s1[i]==s2[j]){
            i++;
            j++;
        }else{
            if(j==0){
                i++;
            }else{
                j=nex[j-1];
            }
        }
		if(j==len2)
            return i-j;
	}
	return -1;
}
bool vioMatch(char *s1,char *s2) {//暴力匹配
    int len1=strlen(s1);
    int len2=strlen(s2);
    if(len1<len2){
        swap(len1,len2);
        swap(s1,s2);
    }
    int i=0,j=0;
	while(i<len1){
        printf("(%d %d)",i,j);
		if(s1[i]==s2[j]){
			i++;j++;
		}else{
		    i-=j-1;//退回去
		    j=0;
		}
        if(j==len2)
            return i-j;
	}
	return 0;
}
int main(int argc,char *argv[]){
    int i,len,j;
    //cin>>T;
    while(~scanf("%s%s",s1,s2)){//查找s1中所有匹配的s2
        len=strlen(s2);
        s2[len]='z';
        getnext1(nex,s2);
        for(i=0;i<=len;i++){
            printf("%d ",nex[i]);
        }printf("\n");
        getnext3(nex,s2);
        for(i=0;i<=len;i++){
            printf("%d ",nex[i]);
        }printf("\n");
        //printf("%d\n",KMP2(s1,s2,nex));
        KMP2(s1,s2,nex);
    }
return 0;
}
