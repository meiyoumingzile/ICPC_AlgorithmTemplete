#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
struct v2{
    int x,y,i;
	v2(){}
	v2(const int &x,const int &y){
		sett(x,y);
	}
    void sett(const int &x,const int &y){
        this->x=x;
        this->y=y;
    }
};
bool cmp1(const v2 &a,const v2 &b){
    return a.y<b.y;
}
bool cmp2(const v2 &a,const v2 &b){
    return a.i<b.i;
}
v2 in[MAX];
int main(int argc,char *argv[]){
    //freopen("testdata.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("in4.in","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,id,T=30,t;
    printf("%d\n",T);
    for(i=0;i<T;i++){
        printf("%d %d\n",rand()%2+1,rand()%100);
    }
return 0;
}
