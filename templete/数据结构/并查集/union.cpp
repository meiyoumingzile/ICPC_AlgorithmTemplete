#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
#define dd double
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

struct Union{
	int fa[MAX],h[MAX];
	Union(int n){
		init(n);
	}
	void init(int n){//��ʼ�� ,���1��n
		for(int i=1;i<=n;i++){
			fa[i]=i;
			h[i]=1;
		}
	}
	int getRoot(int x){
		for(;fa[x]!=x;x=fa[x]);
        return x;
	}
	bool isSame(int x,int y){//�ǲ���ͬһ������
        return getRoot(x)==getRoot(y);
	}
	void vioMerge(int x, int y){//��ͨ�ϲ�����y���x���������ܽ��Ͳ�ѯЧ�ʣ����ǿ��Կ��Ƹ��ڵ����ĸ�
        fa[y]=x;
    }
	void merge(int x,int y){//�ϲ�
		int rx=getRoot(x);
		int ry=getRoot(y);
		if(h[rx]>h[ry]){
			fa[ry]=rx;
		}else if(h[rx]<h[ry]){
			fa[rx]=ry;
		}else{
			fa[rx]=ry;
			h[ry]++;
		}
	}
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,n,m;
	n=10;
	//Union *un=new Union(n);
	Union un(n);
return 0;
}


