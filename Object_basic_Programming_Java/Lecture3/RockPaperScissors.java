
import java.util.Scanner;


public class RockPaperScissors {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("가위(0), 바위(1), 보(2) 중 선택: ");
        int user = sc.nextInt();

        int computer = (int) (Math.random() * 3);
        System.out.println("컴퓨터의 선택: " + computer);

        if (user == computer) {
            System.out.println("비김");
        } else if((user == 0 && computer == 2) || (user ==1 && computer == 0) || (user == 2 && computer == 1)) {
            System.out.println("사용자 승리");
        } else{
            System.out.println("컴퓨터 승리");
        }

        sc.close();


    }
    
}
