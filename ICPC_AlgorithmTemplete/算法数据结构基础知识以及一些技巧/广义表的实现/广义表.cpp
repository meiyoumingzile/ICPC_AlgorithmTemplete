#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;



enum AtomType{ATOM,LIST};
template<class Data>struct Node{
	AtomType type;//枚举类型，也可以直接用ool表示
	union{//联合体用于节省内存，内部二者只能有一个同时存在
		Data atom;
		Node *hp;//下一层表
	};
	Node *tp;//下一个元素
};


int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m;

return 0;
}

