#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define getName(xxx) #xxx
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
int QuoteCount=0;
void* operator new(size_t sz){
   //printf("operator new: %d Bytes\n",sz);
    void* m = malloc(sz);
    QuoteCount++;
   if(!m) puts("out of memory");
     return m;
}
void* operator new[](size_t sz){
   //printf("operator new: %d Bytes\n",sz);
    void* m = malloc(sz);
    memset(m,-1,sz);

    QuoteCount++;
   if(!m) puts("out of memory");
     return m;
}
void operator delete(void* m){
    //puts("operator delete");
    free(m);
    QuoteCount--;
}
void operator delete[](void* m){
    //puts("operator delete");
    free(m);
    QuoteCount--;
}
int fun(int x,int n=MAX){
    printf("%s=%d\n",getName(n),n);
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,T;
	for(i=0;i<100000;i++){
        ll *F=new ll[20000];
        delete []F;
	}
return 0;
}

