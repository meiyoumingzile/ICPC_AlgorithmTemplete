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
void getnext1(int *nex,char *word) {//next1���飬������ƥ�������λ�ã�˼��ʷƥ�䵽����ûƥ�䵽
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

void getnext2(int *nex,char *word) {//next2,����ƥ���һ�ε�λ��
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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    string a,b;
    int i,j,len;
    while(1){//����s1������ƥ���s2
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
