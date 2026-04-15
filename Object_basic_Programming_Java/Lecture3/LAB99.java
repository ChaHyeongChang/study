

import java.util.Scanner;

public class LAB99 {
    public static void main(String[] args) {
        Scanner sin = new Scanner(System.in);

        
        System.out.print("첫 번째 숫자를 입력하세요: ");
        double a = sin.nextDouble();

        System.out.print("두 번째 숫자를 입력하세요: ");
        double b = sin.nextDouble();

        System.out.println("덧셈 결과: " + (a+b));
        System.out.println("뺄셈 결과: " + (a-b));
        System.out.println("곱셈 결과: " + (a*b));
        System.out.println("나눗셈 결과: " + (a/b));

        sin.close();

        
    }
}
