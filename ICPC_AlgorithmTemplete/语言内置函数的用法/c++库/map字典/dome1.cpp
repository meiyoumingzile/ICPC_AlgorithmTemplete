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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,T;
    dir["sss"]=1;
    dir["����"]=2;
    dir["�Ǻ�"]=223;
    for(auto &e:dir){//��������Ҫc++11
        printf("(%s %d) ",e.first.c_str(),e.second);
    }
return 0;
}

