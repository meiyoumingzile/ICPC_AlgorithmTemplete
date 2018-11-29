#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<set>
//#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define dd double
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

struct v2{
    int x,y;

    void sett(int x,int y){
        this->x=x;
        this->y=y;
    }
    bool operator == (const v2 &t){
         return (t.x==this->x&&t.y==this->y);
    }
};


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int n,m,i,j,k,t,T;
    scanf("%d",&T);
    for(t=1;t<=T;t++){
        scanf("%d%d",&n,&m);


    }
return 0;
}
