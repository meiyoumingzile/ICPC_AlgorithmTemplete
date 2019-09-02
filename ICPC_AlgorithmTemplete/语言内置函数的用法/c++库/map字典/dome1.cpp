#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register;
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

struct v2{
    int x,y;
	v2(){}
	v2(int x,int y){
		sett(x,y);
	}
    void sett(int x,int y){
        this->x=x;
        this->y=y;
    }
};
bool cmp(const v2 &a,const v2 &b){
    return a.x<b.x;
}
map<string,int>dir;//unordered_map
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,T;
    dir["sss"]=1;
    dir["哈哈"]=2;
    dir["呵呵"]=223;
    for(auto &e:dir){//遍历，需要c++11
        printf("(%s %d) ",e.first.c_str(),e.second);
    }
return 0;
}

