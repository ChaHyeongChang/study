import java.util.Scanner;

public class InputExample {
    public static void main(String[] args) {
        Scanner sin = new Scanner(System.in);

        System.out.print("정수를 입력하세요: ");
        int price = sin.nextInt(); //정수형 입력받기
        System.out.println("입력한 정수: " + price);

        System.out.print("정수를 입력하세요: ");
        double weight = sin.nextDouble(); //정수형 입력받기
        System.out.println("입력한 정수: " + price);

    }
}
