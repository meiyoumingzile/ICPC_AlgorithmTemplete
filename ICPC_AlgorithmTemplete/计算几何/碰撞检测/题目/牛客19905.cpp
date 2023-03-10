#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-7
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

const double DINF=2147483647.0;////2139062143
const double PI=acos(-1);
struct v2{
    double x,y;
    v2(){}
    v2(cdou x,cdou y){
        init(x,y);
    }
    v2(int x,int y){
        init(x,y);
    }
    void init(cdou x,cdou y){
        this->x=x;
        this->y=y;
    }
    bool operator == (cv2 t){
         return fabs(t.x-this->x)<inf&&fabs(t.y-this->y)<inf;
    }
    bool operator != (cv2 t){
         return fabs(t.x-this->x)>=inf||fabs(t.y-this->y)>=inf;
    }
    v2 operator - (cv2 t) const {
        return v2(x-t.x,y-t.y);
    }
    v2 operator + (cv2 t) const {
        return v2(x+t.x,y+t.y);
    }
    double operator * (cv2 t) const {//返回a*b
        return x*t.x+y*t.y;
    }
    v2 operator * (double t) const {//返回a*b
        return v2(x*t,y*t);
    }
    double X(cv2 t){//返回aXb
        return x*t.y-t.x*y;
    }
    double dis(){//返回aXb
        return sqrt(x*x+y*y);
    }
    double dis2(){//返回aXb
        return x*x+y*y;
    }
    double ccos(){//返回cos值,如果向量在34象限，则取反-2，是的cos值按照从小到大排序是顺时针，范围[-2,2]
        if(y<0){
            return -x/dis()-1;
        }
        return x/dis()+1;
    }
    void scan(){
        cin>>x>>y;
    }
    void print(){
        printf("(%lf %lf) ",this->x,this->y);
    }

};


//得到中点
v2 getMid(cv2 a,cv2 b){
    v2 ans((a.x+b.x)/2,(a.y+b.y)/2);
    return ans;
}
int com(cdou x,double y=0){
    if(abs(x-y)<=inf)
        return 0;
    if(x-y>inf)
        return 1;
    return -1;
}
v2 getCentre(const vector<v2> &li){//对凸多边形点集的质心
    double x=li[0].x,y=li[0].y;
    int n=li.size();
    for(int i=1;i<n;i++){
        x+=li[i].x;
        y+=li[i].y;
    }
    return v2(x/n,y/n);
}

void dotSort(vector<v2> &li){//对凸多边形点集按照顺时针或逆时针排序,
    v2 o=getCentre(li);
    sort(li.begin(),li.end(),[&](const v2 &a,const v2 &b){//[&]意思是捕获外部的o
        return (a-o).ccos()<(b-o).ccos();
    });
}
void dotDup(vector<v2> &li){//对点集去重
    dotSort(li);
    int j=1,n=li.size();
    for(int i=1;i<n;i++){
        if(li[i]!=li[i-1]){
            li[j++]=li[i];
        }
    }
    for(;j<n;j++){
        li.pop_back();
    }
}
struct Line{//直线
    v2 u,v;//u是起始点，v终止点
    double k,b;//在斜截式里面y=kx+b的k和b
    double A,B,C;//标准式
    Line(){}
    Line(v2 u,v2 v){
        init(u,v);
    }
    void init(v2 u,v2 v){//已知直线上两点
        this->v=v;
        this->u=u;
        A=getA(u,v);
        B=getB(u,v);
        C=getC(u,v);
    }
    void init(v2 u,double k){//已知一点u和斜率K，K是DINF是表示垂直
        this->u=u;
        if(com(k,DINF)==0){//垂直
            B=0;
            A=1;
            C=-u.x;
        }else if(com(k,0)==0){
            A=0;
            B=1;
            C=-u.y;
    }else{
            B=1;
            A=-k;
            C=k*u.x-u.y;
        }
    }
    Line verticalSelf(v2 u){//返回和自己垂直的直线
        Line l;
        if(com(B,0)==0){
            l.init(u,DINF);
        }else{
            l.init(u,B/A);
        }
        return l;
    }
    double getk(v2 u,v2 v){
        return (u.y-v.y)/(u.x-v.x);
        //return com(u.y,v.y)?(u.x-v.x)/(u.y-v.y):INF;
    }
    double getb(v2 u,v2 v){
        return u.y-getk(u,v)*u.x;
    }
    double getb(v2 u,double k){
        return u.y-k*u.x;
    }
    double getA(v2 u,v2 v){
        return u.y-v.y;
    }
    double getB(v2 u,v2 v){
        return v.x-u.x;
    }
    double getC(v2 u,v2 v){
        return u.x*(v.y-u.y)-u.y*(v.x-u.x);
    }
    double  dotToLinedis(v2 u){
        double ans=u.x*A+u.y*B+C;
        return fabs(ans)/sqrt(A*A+B*B);
    }

};

int lineFp(const v2 &b,const v2 &c,const v2 &a){//a和bc线段位置的方向关系
    v2 bc=c-b,ba=a-b;
    return com(bc.x*ba.y-bc.y*ba.x);//叉积和0的关系
}
int lineContain(const v2 &b,const v2 &c,const v2 &a){//假设a和bc线段共线，看a是否在bc上,1代表在a在bc中，0代表a正好等于b或c,-1代表没交点
    v2 ab=b-a,ac=c-a;
    return -com(ab*ac);//点乘和0的关系
}
vector<v2> lineFp(const v2 &a,const v2 &b,const v2 &c,const v2 &d){//线段ab和cd位置关系，有交点返回交点,没交点返回空
    vector<v2> ans;
    int i,j,li[4]={lineFp(a,b,c),lineFp(a,b,d),lineFp(c,d,a),lineFp(c,d,b)};
    v2 dot[4]={c,d,a,b};
    int cnt0=0;
    for(i=0;i<4;i++){
        if(li[i]==0){
            cnt0++;
            j=i;
        }
    }
    if(cnt0==0){
        if(li[0]*li[1]==-1&&li[2]*li[3]==-1){//互相在线段两侧
            Line l=Line(c,d);
            double d1=l.dotToLinedis(a);
            double d2=l.dotToLinedis(b);
            double rate=d1/(d1+d2);
            v2 ab=b-a;
            ans.push_back(a+ab*rate);
        }
    }else if(cnt0==1){
        if(j<2&&lineContain(a,b,dot[j])>=0||j>=2&&lineContain(c,d,dot[j])>=0){
            ans.push_back(dot[j]);
        }
    }else{
        if(lineContain(a,b,c)>=0){
            ans.push_back(c);
        }
        if(lineContain(a,b,d)>=0){
            ans.push_back(d);
        }
        if(lineContain(c,d,a)>=0){
            ans.push_back(a);
        }
        if(lineContain(c,d,b)>=0){
            ans.push_back(b);
        }
        //dotDup(ans);
    }
    return ans;//叉积和0的关系
}

struct Rect{//矩形
    v2 d[6];//溢出2个,存放首尾
    void init(v2 *arr){
        for(int i=1;i<=4;i++){
            d[i]=arr[i-1];
        }
        d[0]=arr[4];
        d[5]=arr[1];
    }
    void scan(){
        for(int i=1;i<=4;i++){
            d[i].scan();
        }

        d[0]=d[4];
        d[5]=d[0];
    }


    double area(){
        return (d[0]-d[1]).dis()*(d[2]-d[1]).dis();
    }
    v2 getCentre(){
        return getMid(getMid(d[1],d[2]),getMid(d[3],d[4]));
    }
    int dotPos(cv2 p){//判断点和矩形位置关系,0打板上，1代表内，-1代表外
        double pre=(d[1]-d[0]).X(p-d[0]);
        if(fabs(pre)<inf){
            if((p-d[0])*(p-d[1])>inf){
                return -1;
            }
            return 0;
        }
        for(int i=2;i<=4;i++){
            double now=(d[i]-d[i-1]).X(p-d[i-1]);
            if(fabs(now)<inf){
                if((p-d[i-1])*(p-d[i])>inf){
                    return -1;
                }
                return 0;
            }else if(now*pre<0){
                return -1;
            }
            pre=now;
        }
        return 1;
    }

    void __collision__2(Rect &a,Rect &b,vector<int> &in1,vector<v2> &ans){//返回碰撞顶点列表的第二个方法
        if(in1[0]>in1[1]||in1[0]==1&&in1[1]==4)
            swap(in1[0],in1[1]);
        for(int i=1;i<=4;i++){
            vector<v2> now=lineFp(a.d[i],a.d[i-1],b.d[in1[0]],b.d[in1[0]-1]);
            if(now.size()>0){
                ans.push_back(now[0]);
                break;
            }
        }
        for(int i=1;i<=4;i++){
            vector<v2> now=lineFp(a.d[i],a.d[i-1],b.d[in1[1]],b.d[in1[1]+1]);
            if(now.size()>0){
                ans.push_back(now[0]);
                break;
            }
        }
        ans.push_back(b.d[in1[0]]);
        ans.push_back(b.d[in1[1]]);
    }
    void __collision__1(Rect &a,Rect &b,int in_i,vector<v2> &ans){//返回碰撞顶点列表的第二个方法
        for(int i=1;i<=4;i++){
            vector<v2> now=lineFp(a.d[i],a.d[i-1],b.d[in_i],b.d[in_i+1]);
            if(now.size()>0){
                ans.push_back(now[0]);
                break;
            }
        }
        for(int i=1;i<=4;i++){
            vector<v2> now=lineFp(a.d[i],a.d[i-1],b.d[in_i],b.d[in_i-1]);
            if(now.size()>0){
                ans.push_back(now[0]);
                break;
            }
        }
        ans.push_back(b.d[in_i]);
        ans.push_back(ans[0]+ans[1]-b.d[in_i]);
    }
    vector<v2> collision(Rect &other){//返回碰撞顶点列表
        int i,j,k;
        vector<int>in1,in2;
        vector<v2>coll1,coll2,ans;
        for(i=1;i<=4;i++){
            for(j=1;j<=4;j++){
                k=dotPos(other.d[i]);
                if(k>0)
                    in1.push_back(i);
                else if(k==0)
                    coll1.push_back(other.d[i]);
                k=other.dotPos(d[i]);
                if(k>0)
                    in2.push_back(i);
                else if(k==0)
                    coll2.push_back(d[i]);
            }
        }
        if(in1.size()==0&&in2.size()==0){//如果没有内部的点
            v2 centre1=this->getCentre();
            v2 centre2=other.getCentre();
            if(dotPos(centre2)==1||other.dotPos(centre1)==1){//中心在内部说明有重叠部分
                for(i=1;i<=4;i++){
                    for(j=1;j<=4;j++){
                        vector<v2> now=lineFp(d[i],d[i-1],other.d[j],other.d[j-1]);
                        if(now.size()>0){
                            auto iter=find(ans.begin(),ans.end(),now[0]);
                            if(iter==ans.end()){//没找到就添加
                                ans.push_back(now[0]);
                            }
                        }
                    }
                }
            }else if(coll1.size()>0||coll2.size()>0){//否则看是否有交点,把两个交点类别
                for(auto b:coll2){//合并且去重
                    auto iter=find(coll1.begin(),coll1.end(),b);
                    if(iter==coll1.end()){//没找到就添加
                        coll1.push_back(b);
                    }
                }
                return coll1;
            }
        }else if(in1.size()==1){//如果有1个点在内部，则找到这点，然后判断它两侧的点
            __collision__1(*this,other,in1[0],ans);
        }else if(in2.size()==1){//如果有1个点在内部，则找到这点，然后判断它两侧的点
            __collision__1(other,*this,in2[0],ans);
        }else if(in1.size()==2){
            __collision__2(*this,other,in2,ans);
        }else if(in2.size()==2){
            __collision__2(other,*this,in1,ans);
        }else if(in1.size()==4){
            for(i=1;i<=4;i++){
                ans.push_back(other.d[i]);
            }
        }else if(in2.size()==4){
            for(i=1;i<=4;i++){
                ans.push_back(d[i]);
            }
        }
        if(ans.size()>0)
            dotSort(ans);//整理这4个点,变成顺时针
        return ans;
    }
};
//struct Circle{//椭圆
//    double r1,r2;
//    v2 o;
//    void init(cv2 o,double r1,double r2){
//        this->o=o;
//        this->r1=r1;
//        this->r2=r2;
//    }
//    double area(){
//        return PI*r1*r2;
//    }
//    vector<v2> collision(Circle &other){//另一个椭圆
//        return PI*r1*r2;
//    }
//};
struct Polygon{//多边形,保证是凸多边形
    v2 *d;
    int n;
    Polygon(){}
    void init(v2 *arr,int len){
        n=len;
        d=new v2[len+2];
        for(int i=1;i<=len;i++){
            d[i]=arr[i-1];
        }
        d[0]=d[len];
        d[len+1]=d[1];
    }
    void init(vector<v2>&arr,int len){
        n=len;
        d=new v2[len+2];
        for(int i=1;i<=len;i++){
            d[i]=arr[i-1];
        }
        d[0]=d[len];
        d[len+1]=d[1];
    }
    ~Polygon(){
        delete []d;
    }
    double getArea(){
        double ans=0;
        v2 pre=d[2]-d[1];
        for(int i=3;i<=n;i++){
            v2 now=d[i]-d[1];
            ans+=fabs(pre.X(now))/2;
            pre=now;
        }
        return ans;
    }
    int dotPos(v2 p){//判断点和矩形位置关系,0上，1内，-1外
        double pre=(d[1]-d[0]).X(p-d[0]);
        if(fabs(pre)<inf){
            if((p-d[0])*(p-d[1])>inf){
                return -1;
            }
            return 0;
        }
        for(int i=2;i<=n;i++){
            double now=(d[i]-d[i-1]).X(p-d[i-1]);
            if(fabs(now)<inf){
                if((p-d[i-1])*(p-d[i])>inf){
                    return -1;
                }
                return 0;
            }else if(now*pre<0){
                return -1;
            }
            pre=now;
        }
        return 1;
    }
    Polygon *collision(Polygon *other){//返回碰撞后的另一个多边形
        Polygon *ans=new Polygon();
        int i,j,k;
        vector<v2> dotList;
        for(i=1;i<=n;i++){
            if(other->dotPos(d[i])>0){
                dotList.push_back(d[i]);
            }
            for(j=1;j<=other->n;j++){
                vector<v2> c=lineFp(d[i],d[i-1],other->d[j],other->d[j-1]);
                if(c.size()==1){
                    dotList.push_back(c[0]);
                }
            }
        }
        for(i=1;i<=other->n;i++){

            if(dotPos(other->d[i])>0){
                dotList.push_back(other->d[i]);
            }
        }
        if(dotList.size()==0){
            ans->n=0;
            return ans;
        }
        dotDup(dotList);
        ans->init(dotList,dotList.size());
        //去重
        return ans;
    }
    void println(){
        for(int i=0;i<=n+1;i++){
            printf("(%lf %lf) ",d[i].x,d[i].y);
        }printf("\n");
    }
};



Polygon *arr[55];
v2 dot[55];
int main(int argc,char *argv[]){
	int i,j,k,T,n,m,x,y;
	cin>>m;
	for(i=0;i<m;i++){
        scanf("%d",&n);
        for(j=0;j<n;j++){
            scanf("%d%d",&x,&y);
            dot[j].init(x,y);
        }
        arr[i]=new Polygon();
        arr[i]->init(dot,n);
	}
//	arr[0]->println();
//	arr[1]->println();
	Polygon *ans=arr[0];
	for(i=1;i<m;i++){
        Polygon *t=ans->collision(arr[i]);
        //t->println();
        delete ans;
        ans=t;
	}
	printf("%.3lf",ans->getArea());
return 0;
}
/*
2
6
-2 0
-1 -2
1 -2
2 0
1 2
-1 2
4
0 -3
1 -1
2 2
-1 0
*/
