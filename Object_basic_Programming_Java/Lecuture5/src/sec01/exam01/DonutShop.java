package sec01.exam01;

public class DonutShop {
    public String shopName = "미라클 도넛";

    public void openShop() {
        System.out.println(shopName + " OPEN!");
    }

    public static void main(String[] args) {
        DonutShop shop = new DonutShop();
        shop.openShop();
    }
}