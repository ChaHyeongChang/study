package Object_basic_Programming_Java.Lecture3;

public class NestedIfExample {
    public static void main(String[] args) {
        int price = 25000;
        boolean isMember = true;

        if(price >= 20000){
            if(isMember == true){
                System.out.println("쿠폰 2장");
            } else {
                System.out.println("쿠폰 1장");
            }
        } else{
            System.out.println("쿠폰 없음");
        }
    }
    
}
