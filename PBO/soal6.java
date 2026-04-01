public class Polakotak {
    public static void main(String[] args) {
        int ukuran = 5;
        for (int i = 1; i <= ukuran; i++) {
            for (int j = 1; j <= ukuran; j++) {
                // Cetak simbol hanya di pinggir kotak
                if (i == 1 || i == ukuran || j == 1 || j == ukuran) {
                    System.out.print("#");
                } else {
                    System.out.print(" "); // Cetak spasi untuk bagian tengah
                }
            }
            System.out.println(); // Pindah baris
        }
    }
}