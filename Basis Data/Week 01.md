# Rangkuman Materi: Sistem Basis Data

**Concept, Architecture and Methodology**

## 1. Pengertian Sistem Basis Data

**Basis Data (Database)** adalah kumpulan data yang saling berhubungan dan disimpan secara terorganisir sehingga dapat digunakan kembali dengan mudah.

Tujuan utama database:

* Menyimpan data
* Mengelola data
* Memudahkan akses data
* Mendukung pengambilan keputusan

Database biasanya digunakan oleh:

* organisasi
* perusahaan
* instansi
* sistem aplikasi

---

# 2. Mini World / Universe of Discourse (UoD)

Database merepresentasikan sebagian dari **dunia nyata** yang disebut:

**Miniworld / Universe of Discourse**

Contoh:
Sistem database **rumah sakit**

Miniworld yang disimpan:

* data pasien
* data dokter
* data obat
* data rekam medis

Jika terjadi perubahan di dunia nyata (miniworld), maka database juga harus diperbarui.

Contoh:

* pasien baru masuk → data ditambahkan
* pasien keluar → status berubah

---

# 3. Database Environment

**Lingkungan database** terdiri dari beberapa komponen utama:

1. **Database**

   * kumpulan data yang disimpan

2. **DBMS (Database Management System)**

   * software untuk mengelola database

3. **Application Program**

   * program yang menggunakan database

4. **User**

   * orang yang menggunakan sistem

Contoh:
Aplikasi kasir toko

User → kasir
Application → aplikasi kasir
DBMS → MySQL
Database → data produk, transaksi

---

# 4. Data dan Konteks Data

Data **tidak selalu bermakna jika berdiri sendiri**.

Contoh data:

```
12000
```

Tanpa konteks kita tidak tahu:

* harga?
* jumlah barang?
* jumlah uang?

Karena itu **konteks sangat penting** agar data menjadi informasi.

---

# 5. Data Menjadi Informasi

Data dapat diubah menjadi informasi menggunakan:

* tabel
* grafik
* chart
* laporan

Contoh:
Data penjualan per bulan → dibuat grafik

Manfaat:

* membantu manajer memahami data
* membantu pengambilan keputusan

---

# 6. Metadata

**Metadata** adalah data yang menjelaskan data.

Contoh metadata:

* tipe data
* ukuran field
* nilai yang diperbolehkan
* deskripsi data

Contoh tabel mahasiswa:

| NIM | Nama | Umur |
| --- | ---- | ---- |

Metadata:

* NIM → integer
* Nama → varchar(50)
* Umur → integer

---

# 7. Konsep Shared Organizational Database

Database modern biasanya digunakan **bersama oleh banyak pengguna dalam organisasi**.

Keuntungan:

* data tidak terpisah
* semua bagian organisasi menggunakan data yang sama
* konsistensi data lebih terjaga

Contoh:
Perusahaan memiliki database:

* HRD
* Keuangan
* Penjualan

Semua menggunakan database yang sama.

---

# 8. Sistem Lama: File Processing System

Sebelum DBMS populer, data disimpan dalam **file biasa**.

Contoh:

```
pegawai.txt
gaji.txt
absen.txt
```

Setiap program memiliki file sendiri.

---

# 9. Masalah File Processing System

Masalah utama sistem file:

### 1. Program-Data Dependence

Program tergantung pada struktur data.

Jika struktur file berubah:

* program harus diubah juga

---

### 2. Redundansi Data

Data yang sama disimpan di banyak tempat.

Contoh:
Nama pegawai disimpan di:

* file gaji
* file absensi
* file pegawai

Masalah:

* boros penyimpanan
* data bisa tidak konsisten

---

### 3. Sulit Mengambil Data

Jika ingin laporan baru:

* harus membuat program baru

---

### 4. Kurang Keamanan

Tidak ada kontrol akses yang baik.

---

# 10. Pendekatan Database (Database Approach)

Untuk mengatasi masalah file system, digunakan **database system**.

---

# 11. Keuntungan Database Approach

## 1. Data Sharing

Data bisa digunakan oleh banyak pengguna.

Contoh:
HRD dan keuangan menggunakan data pegawai yang sama.

---

## 2. Data Independence

Program tidak tergantung pada struktur data.

Jika struktur database berubah:

* program tidak harus diubah semua.

---

## 3. Controlled Redundancy

Redundansi data dapat dikontrol.

Data tidak disimpan berkali-kali.

---

## 4. Better Data Integrity

Konsistensi data lebih terjaga.

Contoh:
Umur tidak boleh negatif.

---

# 12. Kekurangan Database System

Walaupun banyak kelebihan, DBMS juga memiliki kekurangan:

1. **Biaya mahal**
2. **Kompleks**
3. **Membutuhkan hardware kuat**
4. **Membutuhkan tenaga ahli**

---

# 13. DBMS (Database Management System)

**DBMS** adalah software yang digunakan untuk:

* membuat database
* mengelola database
* mengakses database
* menjaga keamanan database

Contoh DBMS:

* MySQL
* Oracle
* PostgreSQL
* SQL Server

---

## Analogi DBMS

DBMS berfungsi seperti **sistem operasi untuk data**.

Sama seperti OS mengelola hardware:

* CPU
* RAM
* storage

DBMS mengelola:

* data
* query
* transaksi
* keamanan

---

# 14. Tujuan Database System

Tujuan utama sistem database:

1. mempermudah penyimpanan data
2. mempermudah pengambilan data
3. meningkatkan keamanan data
4. meningkatkan integritas data
5. meningkatkan efisiensi pengolahan data

---

# 15. Mode Penggunaan Database

Database dapat digunakan dengan **2 cara**:

### 1. Interactive Mode

User langsung menggunakan DBMS.

Contoh:

* SQL query
* phpMyAdmin

---

### 2. Programmatic Mode

Database digunakan melalui program aplikasi.

Contoh:

* aplikasi web
* aplikasi mobile
* sistem informasi

---

# 16. Bahasa dalam DBMS

DBMS menyediakan beberapa bahasa:

### 1. DDL (Data Definition Language)

Digunakan untuk membuat struktur database.

Contoh:

* CREATE TABLE
* ALTER TABLE
* DROP TABLE

---

### 2. DML (Data Manipulation Language)

Digunakan untuk mengelola data.

Contoh:

* INSERT
* UPDATE
* DELETE
* SELECT

---

### 3. Query Language

Digunakan untuk mengambil data dari database.

Contoh:
SQL Query.

---

# 17. DBMS Environment

Lingkungan DBMS terdiri dari:

1. Hardware
2. Software
3. Data
4. Procedure
5. Database access language
6. Users

---

# 18. Arsitektur Database dan Aplikasi

Database system memiliki beberapa jenis arsitektur.

---

# 19. Centralized DBMS Architecture

Pada arsitektur ini:

Semua komponen berada di **satu komputer**.

User mengakses langsung server database.

Kelebihan:

* sederhana

Kekurangan:

* tidak scalable

---

# 20. Client / Server Architecture

Sistem dibagi menjadi:

**Client**

* komputer pengguna

**Server**

* komputer database

Client mengirim request ke server.

---

# 21. Two-Tier Architecture

Arsitektur 2 layer:

```
Client → Database Server
```

Client:

* aplikasi
* user interface

Server:

* database

---

# 22. Three-Tier Architecture

Arsitektur 3 layer:

```
Client
↓
Application Server
↓
Database Server
```

Lapisan:

1. **Presentation Layer**

   * interface user

2. **Application Layer**

   * logika aplikasi

3. **Database Layer**

   * penyimpanan data

Ini adalah arsitektur **paling umum pada web modern**.

---

# 23. N-Tier Architecture

Pengembangan dari three-tier.

Digunakan pada:

* sistem besar
* cloud
* enterprise system

---

# 24. Data Model

**Data Model** adalah cara menggambarkan struktur database.

Data model menjelaskan:

* data
* hubungan data
* constraint

Contoh data model:

* Relational Model
* Hierarchical Model
* Network Model
* Object-Oriented Model

---

# 25. Tahapan Perancangan Database

Proses desain database terdiri dari beberapa tahap:

### 1. Requirement Analysis

Mengumpulkan kebutuhan sistem.

---

### 2. Conceptual Design

Membuat model data (biasanya ERD).

---

### 3. Logical Design

Mengubah ERD menjadi tabel relasional.

---

### 4. Physical Design

Menentukan cara penyimpanan di storage.

---

# 26. Three-Schema Architecture (ANSI/SPARC)

Database memiliki **3 level arsitektur**.

---

## 1. Internal Level

Level paling bawah.

Menjelaskan:

* penyimpanan fisik data
* struktur file
* indeks

---

## 2. Conceptual Level

Level tengah.

Menjelaskan:

* struktur keseluruhan database
* relasi antar tabel

Ini adalah **model database utama**.

---

## 3. External Level (View Level)

Level paling atas.

Menjelaskan **tampilan database untuk user tertentu**.

Contoh:

* HRD hanya melihat data pegawai
* keuangan hanya melihat data gaji

---

# 27. Data Independence

Data independence berarti **perubahan pada satu level tidak mempengaruhi level lain**.

---

## 1. Physical Data Independence

Kemampuan mengubah struktur fisik database tanpa mengubah struktur logis.

Contoh:

* mengubah cara penyimpanan
* menambah index

Program tidak perlu diubah.

---

## 2. Logical Data Independence

Kemampuan mengubah struktur logis database tanpa mengubah aplikasi.

Contoh:
menambah kolom baru pada tabel.

Program lama tetap bisa berjalan.

