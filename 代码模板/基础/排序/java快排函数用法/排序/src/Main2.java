import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Scanner;


public class Main2 {
	
	public static void main(String[] args) {
		int i,j,N,k;
		N=10;
		double A[]={0,99,85,8,10,-11.9,3.1415926,4,1,-666.777};
		Arrays.sort(A,1,A.length-1);//排序函数不自定义cmp，但是指定位置,默认从小大大
		//第一个代表起始，之后是终止为止，这里是[1,length-1]
		for(i=0;i<A.length;i++){
			System.out.print(A[i]+"  ");
		}System.out.println();
			
		
	}

}
