public class PolaDiamond {
    public static void main(String[] args) {
        int n = 5; // Ukuran setengah diamond
        
        // Bagian Atas (Piramida)
        for (int i = 1; i <= n; i++) {
            // Cetak Spasi
            for (int j = i; j < n; j++) {
                System.out.print(" ");
            }
            // Cetak Simbol
            for (int k = 1; k <= (2 * i - 1); k++) {
                System.out.print("*");
            }
            System.out.println();
        }
        
        // Bagian Bawah (Piramida Terbalik)
        for (int i = n - 1; i >= 1; i--) {
            // Cetak Spasi
            for (int j = n; j > i; j--) {
                System.out.print(" ");
            }
            // Cetak Simbol
            for (int k = 1; k <= (2 * i - 1); k++) {
                System.out.print("*");
            }
            System.out.println();
        }
    }
}