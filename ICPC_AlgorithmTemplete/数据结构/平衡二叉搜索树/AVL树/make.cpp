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
v2 A[MAX];
int main(int argc,char *argv[]){
    //freopen("data1.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("myout.out","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int id,k,T,temp,i,j;
    scanf("%d",&T);
    for(i=0;i<T;i++){
        scanf("%d%d",&A[i].x,&A[i].y);
        A[i].i=i;
    }
    sort(A,A+T,cmp1);
    temp=A[0].y;
    A[0].y=0;
    for(i=1;i<T;i++){
        if(temp==A[i].y){
            temp=A[i].y;
            A[i].y=A[i-1].y;
        }else{
            temp=A[i].y;
            A[i].y=A[i-1].y+1;
        }
    }
    sort(A,A+T,cmp2);
    printf("%d\n",T);
    for(i=0;i<T;i++){
        printf("%d %d\n",A[i].x,A[i].y);
    }
return 0;
}
/*
11
1 964673
1 915269
1 53283
1 162641
1 948119
2 915269
2 53283
1 531821
1 967521
2 531821
1 343410

*/
