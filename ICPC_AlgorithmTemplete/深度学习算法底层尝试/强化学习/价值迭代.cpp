#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-2
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
const double e=2.71828182;

ll fac[100];
int value_up=21;
int move_up=5;

double GA=0.9;//γ
double REWARD=10;
double COST=-2;
double value[2][21][21];//value matrix
int policy[2][21][21];//policy policy
int VST=0,PST=0;//value and policy^s array index
vector<int> act;

int com(double a,double b){
    if(abs(a-b)<=inf)
        return 0;
    return a>b?1:-1;
}
bool value_leg(){//Judge the equality of two matrices
    for(int j=0;j<value_up;j++)
        for(int k=0;k<value_up;k++)
            if(com(value[0][j][k],value[1][j][k])!=0)
                return 0;
    return 1;
}
bool policy_leg(){//Judge the equality of two matrices
    for(int j=0;j<value_up;j++)
        for(int k=0;k<value_up;k++)
            if(com(policy[0][j][k],policy[1][j][k])!=0)
                return 0;
    return 1;
}
bool value_mulGA(int st){
    for(int j=0;j<value_up;j++)
        for(int k=0;k<value_up;k++)
            value[st][j][k]*=GA;
}
double bo(double lan,int n){// Poisson distribution calc
    return pow(lan,n)/fac[n]*exp(-lan);
}
void print_value(){
    for(int j=0;j<value_up;j++){
        for(int k=0;k<value_up;k++){
            printf("%f ",value[VST][j][k]);
        }printf("\n");
    }printf("\n");
}
void print_policy(){
    for(int j=0;j<value_up;j++){
        for(int k=0;k<value_up;k++){
            printf("%d ",policy[PST][j][k]);
        }printf("\n");
    }printf("\n");
}

void begin_data(){//begin data
    int i,j,k;
    VST=PST=0;
    fac[0]=1;
    for(int i=1;i<22;i++)
        fac[i]=fac[i-1]*i;
    for(int i=-move_up;i<=move_up;i++)
        act.push_back(i);
}
double exp_reward(int *cnt, int action){//len(cnt)=2,reward calc
    double ans=-2*abs(action);
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            double prob = bo(3,i) * bo(4,j);
            int next_i = min(cnt[0]-action, 20);
            int next_j = min(cnt[1]+action, 20);
            int rental_i = min(next_i, i);
            int rental_j = min(next_j, j);
            int reward =(rental_j+rental_i)*10;
            next_i -= rental_i;
            next_j -= rental_j;
            next_i =min(next_i+3,20);
            next_j =min(next_j+2,20);
            ans += prob * (reward+GA*value[VST][next_i][next_j]);
        }
    }
    return ans;
}

void evaluationAndPromotion(){
    int i,j,k;
    do{
        for(i=0;i<value_up;i++){
            for(j=0;j<value_up;j++){
                double maxVal=-INF;
                for(k=0;k<act.size();k++){//Enumerate each action to get the maximum expected value
                    auto &a=act[k];
                    if(a>=0&&a<=i || a<=0&&a>=-j){
                        int cnt[2]={i,j};
                        maxVal=max(maxVal,exp_reward(cnt, a));
                    }
                }
                value[VST^1][i][j]= maxVal;
            }
        }
        VST^=1;//Scroll array update
    }while(!value_leg());
    //Output strategy matrix according to value matrix
    for(i=0;i<value_up;i++){
        for(j=0;j<value_up;j++){
            double maxVal=-INF;
            int maxk=-INF;
            for(k=0;k<act.size();k++){
                auto &a=act[k];
                if(a>=0&&a<=i || a<=0&&a>=-j){
                    int cnt[2]={i,j};
                    double re=exp_reward(cnt, a);
                    if(re>maxVal){
                        maxVal=re;
                        maxk=k;
                    }
                }
            }
            policy[PST^1][i][j]= act[maxk];
        }
    }
    PST^=1;//Scroll array update
}
void value_iteration(){//
    begin_data();
    int i=0;
    for(i=0;!policy_leg()||!i;i++){
        evaluationAndPromotion();
        //print_value();
        //print_policy();
    }
    printf("iteration cnt is %d\n",i);
    printf("polic mat is :\n");
    print_policy();
    printf("value mat is :\n");
    print_value();
}
int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m;
    value_iteration();
return 0;
}
