public class TanggaAngka {
    public static void main(String[] args) {
        int baris = 5;
        for (int i = 1; i <= baris; i++) {
            for (int j = 1; j <= i; j++) {
                System.out.print(j + " ");
            }
            System.out.println();
        }
    }
}