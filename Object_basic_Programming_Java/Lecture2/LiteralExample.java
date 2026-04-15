public class LiteralExample {
    public static void mian(String[] args) {
        long longprice = 25L; //long 10진수
        int octal = 031; //8진수 (031은 10진수로 25)
        int hex = 0x19; // 16진수(0x19는 10진수로 25)
        int binary = 0b11001; // 2진수 (0b11001은 10진수로 25)
        double standardFloat = 25.75; //소수점이 있는 실수
        double exponential =  2.575e1; //지수 표기법 (2.575 * 10^1)
        float lowFloat = 25.75F; //소수점이 있는 실수

        System.out.println("long 10진수 : " + longprice);
        System.out.println("8진수 : " + octal);
        System.out.println("16진수 : " + hex);
        System.out.println("2진수 : " + binary);
        System.out.println("소수점 표기 : " + standardFloat);
        System.out.println("지수표기법 : " + exponential);
        System.out.println("낮은 정밀도 실수 : " + lowFloat);

    }
    
}
