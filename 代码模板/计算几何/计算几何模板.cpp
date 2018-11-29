#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

	struct v2{
	    double x,y;
	    v2(){}
	    v2(cdou x,cdou y){
	        sett(x,y);
	    }
	    void sett(cdou x,cdou y){
	        this->x=x;
	        this->y=y;
	    }
	    bool operator == (cv2 t){
	         return (t.x==this->x&&t.y==this->y);
	    }
	    v2 operator - (cv2 t) const {
            return v2(x-t.x,y-t.y);
        }
	};
	int com(cdou x,double y=0){
	    if(abs(x-y)<=inf)
	        return 0;
	    if(x-y>inf)
	        return 1;
	    return -1;
	}
	int lineFp(const v2 &a,const v2 &b,const v2 &c){//a和bc线段位置的方向关系
        v2 ba(b.x-a.x,b.y-a.y),ca(c.x-a.x,c.y-a.y);
        return com(ba.x*ca.y-ba.y*ca.x);//叉积和0的关系
    }
	int contain(v2 p,v2 a,v2 b,v2 c){//叉积法判别点和三角形关系,1代表内部，-1外部，0在三角形边或者定点上
        v2 pa=a-p,pb=b-p,pc=c-p;
        double m1=pa.cp(pb);
        double m2=pb.cp(pc);
        double m3=pc.cp(pa);
        if(com(m1)==0||com(m2)==0||com(m3)==0)
            return 0;
        if(com(m1)==com(m2)&&com(m2)==com(m3))
            return 1;
        return -1;
    }

	//得到距离
	double dis2(cv2 a,cv2 b){
	    double ans=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
	    return ans;
	}
	double dis2(cdou x1,cdou y1,cdou x2,cdou y2){
	    double ans=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	    return ans;
	}
	double dis(cv2 a,cv2 b){
	    return sqrt(dis2(a,b));
	}
	double dis(cdou x1,cdou y1,cdou x2,cdou y2){
	    return sqrt(dis2(x1,y1,x2,y2));
	}

	//得到中点
	v2 getMid(cv2 a,cv2 b){
	    v2 ans;
	    ans.sett((a.x+b.x)/2,(a.y+b.y)/2);
	    return ans;
	}
	v2 getMid(cdou x1,cdou y1,cdou x2,cdou y2){
	    v2 ans;
	    ans.sett((x1+x2)/2,(y1+y2)/2);
	    return ans;
	}
	//勾股定理已知AB求C
	double pygAB(cdou A,cdou B){
	    return sqrt(A*A+B*B);
	}
	 //勾股定理已知CB求A
	double pygCB(cdou C,cdou B){
	    return sqrt(C*C-B*B);
	}
	double getCos(cdou a,cdou b,cdou c){//余弦定理
	    return (a*a+b*b-c*c)/(2*a*b);
	}
	double heron(cdou a,cdou b,cdou c){//海伦公式求面积
	    double p=(a+b+c)/2;
	    return sqrt(p*(p-a)*(p-b)*(p-c));
	}
	const double DINF=INF*1.0;
	struct Line{
	    v2 u,v;//u是起始点，v终止点
	    double k,b;//在斜截式里面y=kx+b的k和b
	    double A,B,C;//标准式
	    void init(v2 u,v2 v){//已知直线上两点
	        this->v=v;
	        this->u=u;
	        if((com(u.x,0)==0&&com(u.y,0)==0)||(com(v.x,0)==0&&com(v.y,0)==0)){
	            C=0;
	            if(com(u.x,v.x)==0){
	                A=1;
	                B=0;
	            }else if(com(u.y,v.y)==0){
	                A=0;
	                B=1;
	            }else{
	                A=1;
	                B=com(u.x,0)==0?(-v.x*A/v.y):(-u.x*A/u.y);
	            }
	        }else{
	            C=-1;
	            A=getA(u,v);
	            B=getB(u,v);
	        }
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
	        return C*(v.y-u.y)/(v.x*u.y-u.x*v.y);
	    }
	    double getB(v2 u,v2 v){
	        return C*(v.x-u.x)/(u.x*v.y-v.x*u.y);
	    }
	    static double  dis(Line l,v2 u){
	        double ans=u.x*l.A+u.y*l.B+l.C;
	        return abs(ans)/sqrt(l.A*l.A+l.B*l.B);
	    }
	};
	struct Cir{
	    v2 o;
	    double r;
	    double getDis(cv2 b){
	        return dis(o,b)-r;
	    }
	    double getDis(const Cir &b){
	        return dis(o,b.o)-r-b.r;
	    }
	};


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,T;
return 0;
}

