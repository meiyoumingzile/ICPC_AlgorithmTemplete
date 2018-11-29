import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

class v2{
	int x,y;
	v2(int x,int y){
		this.x=x;
		this.y=y;
	}
}

class cmp implements Comparator<v2> { //Comparator是java内部的类，自定义的cmp继承它 
    /*  
     * 因为上面指定了类型<he>，所以此处可以直接(he A,he B) 否则要写成(Object A,Object  
     * B)，再强制转换成he类型：((he)A).x  
     */    
    public int compare(v2 a,v2 b){///compare是sort比较函数,重载它
    	if(a.x<b.x){//返回 -1代表已经按顺序，不换；   1代表没有按顺序,所以要换 
    		return -1;    
        }else if(a.x==b.x){
        	if(a.y<b.y){
        		return -1;
        	}else{
        		return 1;
        	}
        }
        return 1;
    }
}    

public class Main3 {
	public static void main(String[] args) {
		int i,j,N,k;
		Scanner in=new Scanner(System.in);    
		while(in.hasNext()){//相当于while(~scanf())
			N=in.nextInt();//相当于while(~scanf())
	
			v2 A[]=new v2[N];
			for(i=0;i<N;i++){
				A[i]=new v2(in.nextInt(),in.nextInt());
			}
			Arrays.sort(A,0,A.length,new cmp());//排序函数,自定义定义cmp，重载sort所在的类
			for(i=0;i<N;i++){
				System.out.println(A[i].x+" "+A[i].y);
			}
			
		}
			
		
	}

}
/*测试样例
10
2 3
2 0
99 7
23342 7
345 497 
37 44
11 13
2331 2
4 2344999
1000007 9997
*/