public class LAB161 {
    public static void main(String[] args) {
        int[] horse = new int[7];

        int win = -1;

        boolean go = true;

        System.out.println("---- 경마 게임 시작 ----");

        while (go){
            System.out.println("\n---------------------------");
            
            for(int i = 0; i < horse.length; i++){
                horse[i] += (int) (Math.random()*10);

                for(int j = 0; j < horse[i]; j++ ){
                    System.out.println(" ");
                }
                System.out.println(i + ">");

                if(horse[i] >= 100){
                    win = i;
                    go = false;
                    break;
                }
            }
        }
        System.out.println("\n===========================");
        System.out.println("< " + win + "번 말 승리! >");
        System.out.println("\n===========================");
    }
}
