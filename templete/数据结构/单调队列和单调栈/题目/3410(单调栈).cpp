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
int A[MAX],ind[MAX];//û���ظ�����
void clear(){
    while(!st.empty()){
        st.pop();
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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

