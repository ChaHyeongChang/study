package sec02.exam07; // 패키지명은 본인 환경에 맞게

// 1. Donut 클래스를 독립적으로 선언 (또는 static class로 선언)
class Donut {
    String name;
    int price;
    String taste;

    Donut(String name, int price, String taste) {
        this.name = name;
        this.price = price;
        this.taste = taste;
    }

    void show() { System.out.println(name); }
    void show(int price) { System.out.println(name + ", 가격: " + price + "원"); }
    void show(int price, String taste) { System.out.println(name + ", 가격: " + price + "원, 맛: " + taste); }
}

// 2. 실행 클래스를 별도로 작성
public class MethodOverloadExample {
    public static void main(String[] args) {
        Donut d1 = new Donut("초코 도넛", 1500, "달콤함");

        d1.show();
        // 반드시 d1.price 와 같이 객체명을 명시하세요!
        d1.show(d1.price);
        d1.show(d1.price, d1.taste);
    }
}