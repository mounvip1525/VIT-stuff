import java.io.*;
import java.util.Scanner;

class Sales {
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int i=0,j=0,row_total=0;
		int[][] sales=new int [8][9]; /* EID DAY1 DAY2 DAY3 DAY4 DAY5 DAY6 DAY7 TOTAL */
		//For inputing the entries and calculating the total sales for each employee
		for(i=0;i<8;i++) {
			System.out.print((i+1) + ". Enter the employee ID: ");
			j=0; row_total=0;
			sales[i][j]=Integer.parseInt(sc.next());
			for(j=1;j<8;j++) {
				System.out.print("Enter the sales of the day "+ (j) + " of the first week: ");
				sales[i][j]=Integer.parseInt(sc.next());
				row_total += sales[i][j];
			}
			sales[i][8]=row_total;
		}
		//Displaying the data employee-wise
		for(i=0;i<8;i++) {
			System.out.println("Employee ID: " + sales[i][0]);
			System.out.print("Sales of the week- [ ");
			for(j=1;j<8;j++) {
				System.out.print(" " + sales[i][j] + " ");
			}
			System.out.println(" ]");
		}
		//Calculating the minimum and maximum sales 
		int max_sales=0,max_index=0;
		int min_sales=sales[0][8],min_index=0;
		for(i=0;i<8;i++) {
			if(sales[i][8]>max_sales) {
				max_sales=sales[i][8];
				max_index=i;
			}
			if(sales[i][8]<min_sales) {
				min_sales=sales[i][8];
				min_index=i;
			}
		}
		System.out.println("Max sales are "+ max_sales +" by employee ID: "+ sales[max_index][0]);
		System.out.println("Min sales are "+ min_sales +" by employee ID: "+ sales[min_index][0]);
	}
}
