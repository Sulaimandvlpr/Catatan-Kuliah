import java.util.Scanner;

class hitungvokall {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("Hitung Huruf Vokal & Konsonan");
        System.out.println("-------");
        System.out.print("Masukkan Kalimat : ");
        String kalimat = in.nextLine();

        int jmv = 0; 

        int jmk = 0; 

        for(int i = 0; i < kalimat.length(); i++) {
            char huruf = kalimat.charAt(i);

            if (Character.isLetter(huruf)) {
                String cekHuruf = String.valueOf(huruf);
                if(cekHuruf.equalsIgnoreCase("a") ||
                   cekHuruf.equalsIgnoreCase("i") ||
                   cekHuruf.equalsIgnoreCase("u") ||
                   cekHuruf.equalsIgnoreCase("e") ||
                   cekHuruf.equalsIgnoreCase("o") ) {
                    jmv++;
                } else {
                    jmk++;
                }
            }
        }

        System.out.println("\nBanyaknya Vokal : " + jmv);
        System.out.println("Banyaknya Konsonan: " + jmk);
        in.close(); 

    }
}