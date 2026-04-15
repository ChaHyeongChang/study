public class Donut{
    int price;

    Donut(){
        this.price = 2000;
    }

    public int getPrice(){
        return this.price;
    }
    
    public int getDiscount(int discount){
        int result = this.price - discount;
        return result;
    }
    

    
}