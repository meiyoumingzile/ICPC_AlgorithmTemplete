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
const int MAX=1000010;
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
char str[100];
map<string,vector<int> >ind;
bool iseq(vector<int> &a,vector<int> &b){
    int i;
    if(a.size()==b.size()){
        for(i=0;i<a.size()&&a[i]==b[i];i++);
        return i==a.size();
    }
    return 0;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n,q,lens,stlen;
    scanf("%s%d",str,&q);
    lens=strlen(str);
    for(i=0;i<lens;i++){
        string s="";
        for(j=i;j<lens;j++){
            s+=str[j];
            ind[s].push_back(j);
        }
    }
    stlen=0;
    for(auto a : ind){
        sort(a.second.begin(),a.second.end());
    }
    string s,mins,maxs;
    while(q--){
        cin>>s;
        mins=maxs=s;
        for(auto a : ind){
            if(iseq(ind[s],ind[a.first])){
                if(mins.size()>a.first.size()){
                    mins=a.first;
                }
                if(maxs.size()<a.first.size()){
                    maxs=a.first;
                }
            }
        }
        printf("%s %s",mins.c_str(),maxs.c_str());
        for(i=0;i<ind[s].size();i++){
            printf(" %d",ind[s][i]+1);
        }printf("\n");

    }
    return 0;
}

