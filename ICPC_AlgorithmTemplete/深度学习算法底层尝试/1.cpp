#include<bits/stdc++.h>
#include <stdarg.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

struct Tensor{//’≈¡ø
    Tensor(){}
    Tensor(int n,...){
//        init();
        va_list vl;
        va_start(vl,n);

        for(int i=0;i<n;i++){
            double val=va_arg(vl,double);
            printf ("%lf ",val);

        }
    }
    Tensor shape(){

    }
    int sum(int cnt, ...) {
      int sum = 0;
      va_list ap;
      va_start(ap, cnt);
      printf("%d\n",ap.size());
      for (int i = 0; i < cnt+1; ++i) {
        sum += va_arg(ap, int);
      }
      va_end(ap);
      return sum;
    }
};



int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m;
    Tensor a;
    cout<<a.sum(2,5,6,9);
return 0;
}

