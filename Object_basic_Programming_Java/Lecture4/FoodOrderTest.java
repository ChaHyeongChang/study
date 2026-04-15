package Object_basic_Programming_Java.Lecture4;

class FoodOrder {
    String storeName;
    int foodPrice;
    int deliveryFee;

    // 생성자: 가게이름, 음식가격, 배달료를 초기화
    FoodOrder(String storeName, int foodPrice, int deliveryFee) {
        this.storeName = storeName;
        this.foodPrice = foodPrice;
        this.deliveryFee = deliveryFee;
    }

    // 정보를 출력하는 메서드
    void showOrderInfo() {
        int total = foodPrice + deliveryFee; // 총 결제 금액 계산
        
        System.out.println("[" + storeName + "]");
        System.out.println("음식 가격: " + foodPrice + "원");
        System.out.println("배달료: " + deliveryFee + "원");
        System.out.println("총 결제 금액: " + total + "원");
        System.out.println(); // 줄바꿈
    }
}

public class FoodOrderTest {
    public static void main(String[] args) {
        // 1. 김밥천국 객체 생성
        FoodOrder order1 = new FoodOrder("김밥천국", 12000, 2000);
        order1.showOrderInfo();

        // 2. 버거킹 객체 생성
        FoodOrder order2 = new FoodOrder("버거킹", 9000, 3000);
        order2.showOrderInfo();

        // 3. 피자스쿨 객체 생성
        FoodOrder order3 = new FoodOrder("피자스쿨", 13000, 0);
        order3.showOrderInfo();
    }
}