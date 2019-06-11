#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=11000001;
const int mod=1e9+7;

char str[MAX];

char s[MAX*2+1];
int p[MAX*2+1];
int Manacher(char *str){
    int i,len,ls,maxRight,pos,ans=2;
    len=strlen(str);
    ls=len*2+1;
    memset(s,'#',sizeof(char)*ls);
    for(i=0;i<len;i++)
        s[i*2+1]=str[i];
    maxRight=2;
    pos=1;
    p[0]=1;
    p[1]=2;
    for(i=2;i<ls;i++){
        p[i]=i<maxRight?min(p[2*pos-i],maxRight-i):1;
        while(i-p[i]>=0&&i+p[i]<ls&&s[i-p[i]]==s[i+p[i]])
            p[i]++;
        if(maxRight<i+p[i]){
            maxRight=i+p[i];
            pos=i;
        }
        ans=max(ans,p[i]);
    }
    return ans-1;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    cin>>str;
    printf("%d\n",Manacher(str));
return 0;
}

