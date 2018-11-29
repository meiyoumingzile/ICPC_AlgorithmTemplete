import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Scanner;


public class Main1 {
	
	public static void main(String[] args) {
		int i,j,N,k;
		Scanner in=new Scanner(System.in);    
		while(in.hasNext()){//相当于while(~scanf())
			N=in.nextInt();//相当于while(~scanf())
			
			int A[]=new int[N];
			for(i=0;i<N;i++){
				A[i]=in.nextInt();
			}
			Arrays.sort(A);//排序函数不定义cmp
			for(i=0;i<N;i++){
				System.out.print(A[i]+" ");
			}System.out.println();
			
		}
	}

}
