import java.util.Scanner;

public class WhileExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int sum = 0;

        System.out.print("숫자를 입력하세요 (0을 입력하면 종료):");
        int number = scanner.nextInt();

        while(number != 0){
            sum = sum + number;
            System.out.println("현재 합계: " + sum);

            System.out.print("숫자를 입력하세요(0을 입력하면 종료):");
            number = scanner.nextInt();

        }   

        System.out.println("최종 합계는 : " + sum + "입니다.");
        scanner.close();
    }
}
