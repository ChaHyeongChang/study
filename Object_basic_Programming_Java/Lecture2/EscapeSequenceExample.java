public class EscapeSequenceExample {
    public static  void main(String[] args){
        char quotes = '\"';

        System.out.println("\t탭 \n");
        System.out.println(quotes + " 따옴표 \'와 \u0041와 \\ " + quotes);
    }
    
}  