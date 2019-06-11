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
const int MAX=100010;
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
v2 res[MAX];
stack<int>st;
int A[MAX],ind[MAX];//没有重复数字
void clear(){
    while(!st.empty()){
        st.pop();
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n;
    cin>>T;
    for(t=1;t<=T;t++){
        scanf("%d",&n);
        for(i=1;i<=n;i++){
            scanf("%d",&A[i]);
            ind[A[i]]=i;
        }
        clear();
        for(i=1;i<=n;i++){
            if(st.empty()||st.top()>A[i]){
                res[i].x=0;
            }else{
                while(!st.empty()&&st.top()<A[i]){
                    k=st.top();
                    st.pop();
                }
                res[i].x=ind[k];
            }
            st.push(A[i]);
        }
        clear();
        for(i=n;i>0;i--){
            if(st.empty()||st.top()>A[i]){
                res[i].y=0;
            }else{
                while(!st.empty()&&st.top()<A[i]){
                    k=st.top();
                    st.pop();
                }
                res[i].y=ind[k];
            }
            st.push(A[i]);
        }
        printf("Case %d:\n",t);
        for(i=1;i<=n;i++){
            printf("%d %d\n",res[i].x,res[i].y);
        }
    }
return 0;
}

