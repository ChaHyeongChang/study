package Object_basic_Programming_Java.Lecture3;

import java.util.Scanner;

public class IfElseIfExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("쿠폰 수 입력: ");
        int coupon = scanner.nextInt();

        if (coupon >= 10){
            System.out.println("도넛 4개 무료");
        } else if (coupon >= 3) {
            System.out.println("무료 음료");
            
        } else {
            System.out.println("다음 기회에");
        }

        scanner.close();
    }
}
