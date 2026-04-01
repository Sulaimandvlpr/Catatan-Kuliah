import java.util.Scanner;

public class Perpus1 {
    public static void main (String[] args) {
        Scanner perpus1 = new Scanner (System.in);
        int status, sewa = 0, buku, lama;
        double total, disc;
        
        System.out.print ("Status peminjam = ");
        status = perpus1.nextInt();
        System.out.print ("Jumlah buku = ");
        buku = perpus1.nextInt();
        System.out.print ("Lama pinjam = ");
        lama = perpus1.nextInt();
        
        System.out.println("-------------------------");
        
        switch (status) {
            case 1:
                System.out.println ("Pelajar");
                sewa = 500 * lama * buku;
                break;
            case 2:
                System.out.println ("Mahasiswa");
                sewa = 1000 * lama * buku;
                break;
            default :
                System.out.println ("Masyarakat Umum");
                sewa = 1500 * lama * buku;
                break;
        }
        
        if (buku > 10 && buku <= 15) {
            disc = sewa/100*5;
            total = sewa-disc;
            System.out.println ("Total yang Dibayar = "+ (int)total);
        } else if (buku > 5 && buku <= 10){
            disc = sewa/100*2.5;
            total = sewa-disc;
            System.out.println ("Total yang Dibayar = "+(int)total);
        } else if (buku > 0 && buku <= 5) { 
            System.out.println ("Total yang Dibayar = "+sewa);
        } else if (lama > 7){
            System.out.println ("Lama Pinjam/jumlah buku terlalu banyak");
        } else if (buku > 15) {
            System.out.println ("Lama Pinjam/jumlah buku terlalu banyak");
        }
    }
}