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

class cmp implements Comparator<v2> { //Comparator��java�ڲ����࣬�Զ����cmp�̳��� 
    /*  
     * ��Ϊ����ָ��������<he>�����Դ˴�����ֱ��(he A,he B) ����Ҫд��(Object A,Object  
     * B)����ǿ��ת����he���ͣ�((he)A).x  
     */    
    public int compare(v2 a,v2 b){///compare��sort�ȽϺ���,������
    	if(a.x<b.x){//���� -1�����Ѿ���˳�򣬲�����   1����û�а�˳��,����Ҫ�� 
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
		while(in.hasNext()){//�൱��while(~scanf())
			N=in.nextInt();//�൱��while(~scanf())
	
			v2 A[]=new v2[N];
			for(i=0;i<N;i++){
				A[i]=new v2(in.nextInt(),in.nextInt());
			}
			Arrays.sort(A,0,A.length,new cmp());//������,�Զ��嶨��cmp������sort���ڵ���
			for(i=0;i<N;i++){
				System.out.println(A[i].x+" "+A[i].y);
			}
			
		}
			
		
	}

}
/*��������
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