import java.util.Scanner;

public class belanja {
    public static void main (String[] args){
        Scanner belanja = new Scanner (System.in);
        int disc, bayar, tbelanja;
        String nama, nomor;
        
        System.out.print("Nama = ");
        nama = belanja.nextLine();
        System.out.print("Nomor = ");
        nomor = belanja.nextLine();
        System.out.print("Total Belanja = ");
        tbelanja = belanja.nextInt();
        
        System.out.println("===========================");
        
        if (tbelanja >= 800000){
            disc = tbelanja * 25/100;
            bayar = tbelanja - disc;
        } else if (tbelanja >= 600000) {
            disc = tbelanja * 20/100;
            bayar = tbelanja - disc;
        } else if (tbelanja >= 400000) {
            disc = tbelanja * 15/100;
            bayar = tbelanja - disc;
        } else if (tbelanja >= 200000) {
            disc = tbelanja * 10/100;
            bayar = tbelanja - disc;
        } else {
            disc = tbelanja * 0;
            bayar = tbelanja - disc;
        }
        
        System.out.println("===========================");
        System.out.println("Nama Kasir: "+nama);
        System.out.println("No.Induk Kasir: "+nomor);
        System.out.println("Total Belanja: "+ tbelanja +" Rupiah");
        System.out.println("Total Diskon: "+ disc +" Rupiah");
        System.out.println("Total Dibayar: "+ bayar +" Rupiah");
    }
}