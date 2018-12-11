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
void getnext1(int *nex,char *word) {//next1数组，用来求匹配的所有位置，思想史匹配到当做没匹配到
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

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    string a,b;
    int i,j,len;
    while(1){//查找s1中所有匹配的s2
        scanf("%s",s2);
        len=strlen(s2);
        getnext2(next2,s2);
        for(i=0;i<=len;i++){
            printf("%d ",next2[i]);
        }printf("\n");
        getnext1(next1,s2);
        for(i=0;i<=len;i++){
            printf("%d ",next1[i]);
        }printf("\n");
    }
return 0;
}
