#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=3000010;
const int mod=1e9+7;

struct v2{
    int x,y;
	v2(){}
	v2(const int &x,const int &y){
		sett(x,y);
	}
    void sett(const int &x,const int &y){
        this->x=x;
        this->y=y;
    }
};
bool cmp(const v2 &a,const v2 &b){
    return a.x<b.x;
}
void println(int *arr,int b,int e){//[b,e)
    printf("(%d:%d)",b,arr[b]);
    for(int i=b+1;i<e;i++){
        printf(" (%d:%d)",i,arr[i]);
    }printf("\n");
}
struct LCT{
    int n,p[MAX],son[MAX][2],val[MAX],st[MAX],xsum[MAX];
    //p[i]��i���ڵ㣬son[i]��i���Ҷ���,val[i]�ǵ�uȨֵ��st[i]  ,xsum[i]��i����
    void pushdown(){

    }
    void pushup(){
    }
    void reverse(){
    }
    bool isroot(int now){
    }
    void rotate(int x){

    }

};
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,n;
return 0;
}

