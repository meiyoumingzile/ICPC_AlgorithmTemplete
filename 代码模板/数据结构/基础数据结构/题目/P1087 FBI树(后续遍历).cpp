#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=2010;
const int mod=1e9+7;
char str[MAX];


char ind[3];
char dfs(int left,int right){
    char a,b,c;
    if(left+1==right){
        a=ind[(int)(str[left]-'0')];
        printf("%c",a);
        return a;
    }
    int mid=(left+right)/2;
    a=dfs(left,mid);
    if(a==dfs(mid,right)){
        printf("%c",a);
    }else{
        printf("%c",'F');
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int N;
    ind[0]='B';
    ind[1]='I';
    cin>>N>>str;
    dfs(0,strlen(str));
    printf("\n");
return 0;
}
