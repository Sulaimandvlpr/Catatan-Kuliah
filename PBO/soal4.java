import java.util.Scanner;

public class InversMatriks {
    public static void main(String[] args) {
        Scanner in = new Scanner (System.in);
        int baris, kolom;
        
        System.out.print("masukkan jumlah baris: ");
        baris = in.nextByte();
        System.out.print("masukan jumlah kolom: ");
        kolom = in.nextInt();
        
        System.out.println("data pada matriks");
        int matriks[][] = new int[baris][kolom];
        
        for (int i=0;i<baris;i++){
            for(int j=0;j<kolom;j++){
                System.out.print("data pada baris ke- "+i+" kolom ke- "+j+" : ");
                matriks[i][j]=in.nextInt();
            }
        }
        
        System.out.println();
        System.out.println("matriks sebelum diInvers");
        for (int i=0;i<baris;i++){
            for (int j=0;j<kolom;j++) {
                System.out.print(matriks[i][j]+" ");
            }
            System.out.println();
        }
        
        //proses invers
        float determinan = (matriks[0][0]*matriks[1][1]) - (matriks[1][0]*matriks[0][1]);
        System.out.println("Determinanya Adalah: "+determinan);
        
        int temp = matriks[0][0];
        matriks[0][0] = matriks[1][1];
        matriks[1][1] = temp;
        matriks[0][1] = matriks[0][1] * -1;
        matriks[1][0] = matriks[1][0] * -1;
        
        System.out.println("invers dari matriks tersebut adalah: ");
        for (int i=0;i<2;i++){
            System.out.print("| ");
            for (int j=0;j<2;j++){
                System.out.print(matriks[i][j]/determinan+" ");
            }
            System.out.println("|");
        }
    }
}