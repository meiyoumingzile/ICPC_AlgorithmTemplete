import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Scanner;


public class Main2 {
	
	public static void main(String[] args) {
		int i,j,N,k;
		N=10;
		double A[]={0,99,85,8,10,-11.9,3.1415926,4,1,-666.777};
		Arrays.sort(A,1,A.length-1);//���������Զ���cmp������ָ��λ��,Ĭ�ϴ�С���
		//��һ��������ʼ��֮������ֹΪֹ��������[1,length-1]
		for(i=0;i<A.length;i++){
			System.out.print(A[i]+"  ");
		}System.out.println();
			
		
	}

}
