# Pertemuan 1: Konsep dan Perkembangan Rekayasa Perangkat Lunak

Saya membuat catatan ini berdasarkan materi yang kamu lampirkan (slide **RPL Pertemuan 1**) dan menata ulang supaya **lengkap, jelas, mudah dipahami, dan lebih detail**. Sumber asli: file **RPL Pertemuan 1.pptx**. 

---

# 1. Ringkasan singkat pertemuan

* Tujuan mata kuliah: mengenalkan prinsip, metode, dan tahapan rekayasa perangkat lunak (RPL) sepanjang siklus hidup software, dari perencanaan sampai pembuatan proyek. 
* Metode pembelajaran: ceramah, diskusi, PBL (Problem-Based Learning), praktik, ujian. Evaluasi: aktivitas partisipatif (20%), hasil proyek (40%), tugas & UTS (40%). 

---

# 2. Apa itu *Software* (Perangkat Lunak)?

**Definisi ringkas:**
Software adalah kumpulan instruksi program (semantik) yang, saat dijalankan, menyediakan fitur, fungsi, dan kinerja yang diinginkan; termasuk juga struktur data dan dokumentasi deskriptif yang menggambarkan pengoperasian dan penggunaan program. 

**Poin penting:**

* **Instruksi program** → perilaku yang dijalankan mesin.
* **Struktur data (tipe data)** → cara menyimpan & memanipulasi informasi.
* **Informasi deskriptif** → dokumentasi (manual, help, diagram) yang menjelaskan cara penggunaan dan operasi. 

---

# 3. Karakteristik khusus software

* **Dikembangkan / direkayasa**, bukan diproduksi seperti barang fisik.
* Software jarang “usang” secara fisik; lebih sering berevolusi (pemeliharaan & pembaruan).
* Banyak software dibuat berdasarkan kebutuhan spesifik (custom) meskipun muncul juga produk massal dan berbasis komponen. 

---

# 4. Peranan perangkat lunak (contoh konkret)

1. **Menggantikan peran manusia** — otomatisasi (mis. proses billing otomatis).
2. **Memperkuat peran manusia** — alat bantu (mis. spreadsheet untuk analisis).
3. **Restrukturisasi tugas** — merancang ulang proses kerja (mis. ERP mengganti alur manual).
4. **Hiburan & game** — aplikasi interaktif yang meniru dunia nyata. 

---

# 5. Kategori perangkat lunak (dengan contoh)

* **System software**: compiler, OS, driver, utilitas.
* **Application software**: POS, aplikasi manufaktur real-time.
* **Engineering/scientific software**: CAD, simulasi.
* **Embedded software**: firmware microwave, ECU mobil.
* **Product-line software**: office suite, multimedia apps.
* **WebApps** dan **AI software**: aplikasi web, sistem pakar, pengenalan citra. 

---

# 6. Kriteria perangkat lunak yang baik

1. **Maintainability** — mudah dipelihara/diubah.
2. **Dependability** — dapat diandalkan (keamanan, keakuratan).
3. **Efisiensi** — penggunaan sumber daya optimal.
4. **Usability** — mudah digunakan sesuai kebutuhan pengguna. 

> Contoh: aplikasi perbankan yang sulit di-maintain → biaya perbaikan & risiko kegagalan meningkat.

---

# 7. Sejarah singkat RPL (pointer waktu)

* **1940-an**: awal pemrograman langsung (PC awal).
* **1950-an**: lahirnya compiler & bahasa tingkat tinggi.
* **1960-an**: istilah *software engineering* mulai digunakan.
* **1970-an**: perangkat pengembangan dan minikomputer.
* **1990-an**: OOP, munculnya Agile.
* **2000-an**: platform modern (Java, .NET, PHP), berkembangnya Web & Mobile. 

---

# 8. Model proses pengembangan perangkat lunak

Jelaskan model-model utama yang disebutkan di materi:

### 8.1 Model Waterfall (linear, tradisional)

Tahapan berurutan:

```
Requirements → Design → Implementation → Testing → Deployment → Maintenance
```

* Kelebihan: jelas, mudah diatur, cocok untuk proyek dengan kebutuhan stabil.
* Kekurangan: sulit menangani perubahan kebutuhan, iterasi terbatas. 

### 8.2 Model Iteratif / Incremental

* Pengembangan bertahap: tiap iterasi menambahkan fitur baru. Lebih fleksibel terhadap perubahan.

### 8.3 Model Spiral

* Berulang dengan fokus manajemen risiko di setiap putaran (analisis risiko intensif).

### 8.4 Model Berbasis Komponen

* Menggabungkan komponen/servis yang sudah ada untuk merakit aplikasi baru (mengurangi effort pembuatan dari nol). 

---

# 9. Jenis-jenis kebutuhan perangkat lunak

### 9.1 Kebutuhan fungsional

* Menjelaskan **apa** yang harus dilakukan sistem: fitur, cara pengolahan, input/output, skenario khusus.
* Contoh: “Sistem harus bisa menyimpan data pelanggan dan menghasilkan laporan bulanan.”

### 9.2 Kebutuhan non-fungsional

* Kriteria kualitas sistem: performa (kecepatan), keamanan, kapasitas, batasan bahasa pemrograman atau platform.
* Contoh: “Sistem harus merespon dalam < 2 detik untuk 95% request.” 

---

# 10. Kurva kegagalan: hardware vs software (intuisi)

* **Hardware**: biasanya memiliki kurva kegagalan yang jelas (infant mortality → stabil → aus).
* **Software**: kegagalan sering muncul setelah penggunaan / saat perubahan, karena bug logika; lebih berkaitan dengan kondisi penggunaan dan perubahan eksternal. (Catatan: materi menekankan perbedaan karakter kegagalan.) 

---

# 11. Praktik rekayasa perangkat lunak yang baik (ringkasan action items)

1. **Analisis kebutuhan yang jelas** — jangan langsung coding; lakukan elicitation.
2. **Desain yang modular & berbasis komponen** — memudahkan maintainability.
3. **Coding sesuai standar & review** — code review, linting, test-driven development.
4. **Pengujian menyeluruh** — unit, integrasi, sistem, acceptance.
5. **Perencanaan pemeliharaan** — dokumentasi, versi, CI/CD.
6. **Manajemen risiko** — identifikasi & mitigasi sejak awal. 

---

# 12. Integritas akademik & etika penggunaan AI (dari materi)

* Integritas akademik = komitmen pada kejujuran, tanggung jawab, keadilan, etika.
* Pelanggaran: plagiarisme, menyontek, kolaborasi tidak sah, pemalsuan data, penyalahgunaan AI.
* Mahasiswa diharapkan menghasilkan karya orisinal dan menggunakan teknologi secara etis; pelanggaran kena sanksi sesuai aturan kampus. 

---

# 13. Contoh soal / latihan (untuk pemahaman)

1. **Jelaskan perbedaan kebutuhan fungsional dan non-fungsional dengan contoh masing-masing.**
2. **Bandingkan model Waterfall dan Incremental — kapan kamu pilih masing-masing?**
3. **Berikan tiga karakteristik software yang baik dan jelaskan mengapa penting.**
4. **Buatlah sketsa rencana proyek singkat (3 iterasi) untuk aplikasi “toko online” menggunakan model incremental.**

---

# 14. Tugas & proyek yang direkomendasikan

* **Tugas kecil:** tulis dokumen SRS (Software Requirements Specification) sederhana untuk aplikasi kasir (2–3 halaman).
* **Proyek kelompok:** buat prototype aplikasi berbasis web selama 6 minggu; gunakan model incremental: setiap minggu deliverable fitur baru + demo.
* **Praktik:** lakukan code review peer-to-peer; buat checklist pengujian. 

---

# 15. Ringkasan singkat (one-pager)

* **Software** = instruksi + struktur data + dokumentasi.
* **Goal RPL** = kembangkan software berkualitas melalui metode & tahap yang terkontrol.
* **Model**: Waterfall (linear) vs Iterative/Incremental/Spiral (lebih fleksibel).
* **Kebutuhan**: fungsional (apa) vs non-fungsional (bagaimana/berapa baik).
* **Praktik**: analisis, desain modular, coding standar, testing, pemeliharaan, etika. 

---

# 16. Referensi yang direkomendasikan (dari slide)

* Sommerville, Ian — *Engineering Software Products / Software Engineering* (Pearson).
* Pressman, Roger S. — *Software Engineering: A Practitioner’s Approach*. 

---

Kalau mau, aku bisa lanjut ke salah satu hal berikut (pilih salah satu, atau minta semuanya):

1. **Buatkan SRS contoh** untuk aplikasi sederhana (lengkap dengan requirement fungsional & non-fungsional).
2. **Susun ringkasan slide** (PowerPoint) yang rapi berisi poin-poin ini sehingga siap dipresentasikan.
3. **Beri contoh langkah-langkah praktis** untuk tugas proyek (timeline, deliverables, checklist testing).

Mau lanjut ke mana?
