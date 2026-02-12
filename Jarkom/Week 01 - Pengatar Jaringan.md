# Jaringan Komputer – Pertemuan 01

## Introduction to Networks v7.0 (ITN)

---

# 1. Administrative Issue

## 1.1 Register and Class Enrollment

Mahasiswa diwajibkan membuat akun pada platform **Netacad.com** (Cisco Networking Academy). Setelah membuat akun, mahasiswa harus melakukan enrollment kelas melalui link yang diberikan dosen.

Platform NetAcad digunakan untuk:

* Mengakses materi resmi Cisco
* Mengerjakan kuis dan final exam
* Mendapatkan sertifikat resmi

## 1.2 Marking Scheme (Format Penilaian)

Penilaian terdiri dari beberapa komponen:

| Komponen                   | Bobot      |
| -------------------------- | ---------- |
| Aktivitas Partisipatif     | 10%        |
| Project                    | 40%        |
| Tugas (6x Checkpoint Exam) | 30%        |
| UTS                        | 10%        |
| UAS                        | 10%        |
| Final Exam Netacad         | Sertifikat |

Project memiliki bobot terbesar karena menilai pemahaman praktis dan implementasi.

---

# 2. Module 1 – Networking Today

## 2.1 Networks Affect Our Lives

Komunikasi adalah kebutuhan dasar manusia. Dalam konteks modern, jaringan komputer memungkinkan komunikasi lintas kota, negara, bahkan benua secara instan.

Sebelum ada jaringan:

* Informasi dikirim melalui surat fisik.
* Komunikasi jarak jauh mahal dan lambat.

Setelah ada jaringan:

* Email menggantikan surat.
* Video call menggantikan pertemuan fisik.
* Transaksi keuangan dilakukan real-time.

Konsep penting:

* Global communities → komunitas global tanpa batas geografis.
* Human network → jaringan manusia yang terhubung melalui teknologi.

Contoh kasus:
Seorang mahasiswa di Indonesia bisa mengikuti kelas dari universitas di Amerika melalui jaringan internet.

---

# 3. Network Components

## 3.1 Host Roles

Setiap perangkat yang terhubung ke jaringan disebut **host** atau **end device**.

### Server

Server adalah komputer yang menyediakan layanan kepada komputer lain.

Contoh:

* Web server menyimpan website.
* Email server menyimpan dan mengelola email.
* File server menyimpan dokumen bersama.

Kasus:
Ketika kamu membuka website, browser kamu mengirim permintaan ke web server. Server mengirimkan halaman web sebagai respons.

### Client

Client adalah perangkat yang meminta layanan dari server.

Contoh:

* Laptop membuka Google.
* Smartphone mengambil email.

Hubungan client-server bersifat request-response.

---

## 3.2 Peer-to-Peer Network (P2P)

Dalam jaringan Peer-to-Peer, tidak ada server khusus. Setiap perangkat dapat berperan sebagai client sekaligus server.

Artinya:

* Komputer A bisa meminta file dari komputer B.
* Komputer B juga bisa meminta file dari komputer A.

### Contoh Kasus P2P

Dalam sebuah rumah dengan 3 komputer:

* Komputer 1 berbagi folder.
* Komputer 2 dan 3 bisa mengakses folder tersebut.
* Tidak ada server khusus.

Kelebihan:

* Murah.
* Mudah dikonfigurasi.

Kekurangan:

* Tidak cocok untuk jaringan besar.
* Keamanan dan manajemen sulit.
* Performa bergantung pada masing-masing perangkat.

Karena itu P2P direkomendasikan hanya untuk jaringan kecil.

---

## 3.3 End Devices

End device adalah titik awal dan akhir komunikasi data.

Alur komunikasi:

1. Data dibuat di end device.
2. Data dikirim melalui jaringan.
3. Data diterima oleh end device lain.

Contoh:
Kamu mengirim pesan WhatsApp → smartphone kamu adalah end device → pesan melewati jaringan → smartphone penerima adalah end device tujuan.

---

## 3.4 Intermediary Network Devices

Perangkat perantara bertugas menghubungkan end device.

Contoh perangkat:

* Switch
* Router
* Wireless Access Point
* Firewall

### Fungsi perangkat perantara:

1. Regenerate dan retransmit sinyal.
2. Menentukan jalur terbaik.
3. Mendeteksi error komunikasi.
4. Mengatur lalu lintas data.

Contoh kasus:
Ketika kamu mengakses website luar negeri:

* Router menentukan jalur terbaik.
* Switch menghubungkan perangkat dalam LAN.
* Firewall menyaring trafik berbahaya.

---

## 3.5 Network Media

Media adalah jalur fisik atau non-fisik tempat data bergerak.

Jenis:

* Kabel tembaga (UTP)
* Fiber optic
* Wireless (gelombang radio)

Contoh:
WiFi menggunakan media wireless, sedangkan kabel LAN menggunakan media tembaga.

---

# 4. Network Representations and Topologies

## 4.1 Network Representation

Jaringan direpresentasikan menggunakan diagram.

Istilah penting:

### Network Interface Card (NIC)

Perangkat keras yang menghubungkan komputer ke jaringan.

### Physical Port

Lubang fisik tempat kabel ditancapkan.

### Interface

Titik koneksi jaringan (bisa fisik atau logis).

Port dan interface sering dianggap sama, tetapi interface bisa bersifat virtual.

---

## 4.2 Topology Diagrams

### Physical Topology

Menunjukkan:

* Lokasi perangkat
* Jalur kabel fisik

Contoh:
Denah laboratorium komputer lengkap dengan jalur kabel.

### Logical Topology

Menunjukkan:

* Bagaimana data mengalir
* Skema IP addressing
* Hubungan logis antar perangkat

Contoh:
Diagram alur komunikasi router ke server.

---

# 5. Common Types of Networks

## 5.1 Berdasarkan Skala

1. Small Home Network
   Jaringan rumah dengan beberapa perangkat.

2. SOHO
   Jaringan rumah/kantor kecil yang terhubung ke jaringan perusahaan.

3. Medium/Large Network
   Digunakan perusahaan dengan ratusan komputer.

4. World Wide Network
   Contoh: Internet.

---

## 5.2 LAN dan WAN

### LAN (Local Area Network)

* Area kecil.
* Dimiliki satu organisasi.

Contoh:
Jaringan dalam kampus.

### WAN (Wide Area Network)

* Area luas.
* Menghubungkan banyak LAN.

Contoh:
Jaringan antar cabang bank nasional.

---

## 5.3 Internet

Internet adalah kumpulan LAN dan WAN yang terhubung global.

Tidak dimiliki satu pihak.

Organisasi penting:

* IETF (standar protokol)
* ICANN (pengelolaan domain dan IP)
* IAB (arsitektur internet)

---

## 5.4 Intranet dan Extranet

### Intranet

Jaringan internal perusahaan yang hanya bisa diakses karyawan.

Contoh:
Portal HRD internal.

### Extranet

Bagian intranet yang dapat diakses pihak luar tertentu.

Contoh:
Vendor bisa mengakses sistem pengadaan perusahaan.

---

# 6. Internet Connections

## 6.1 Home Connections

* DSL
* Cable
* Cellular
* Satellite

## 6.2 Business Connections

* Dedicated leased line
* Metro Ethernet
* Business DSL

Perusahaan membutuhkan:

* Bandwidth lebih besar
* Koneksi dedicated
* Layanan terkelola

---

## 6.3 Converged Network

Dulu:

* Telepon menggunakan jaringan sendiri.
* Video menggunakan jaringan sendiri.
* Data menggunakan jaringan sendiri.

Sekarang:
Semua layanan menggunakan satu infrastruktur berbasis IP.

Keuntungan:

* Lebih efisien.
* Biaya lebih rendah.
* Manajemen lebih mudah.

---

# 7. Reliable Networks

Empat karakteristik utama:

## 7.1 Fault Tolerance

Jaringan tetap berjalan meskipun ada perangkat gagal.

Menggunakan:

* Redundancy
* Multiple path

Contoh:
Jika satu kabel putus, data dialihkan ke jalur lain.

Perbedaan:

* Packet switching → data dipecah menjadi paket.
* Circuit switching → jalur tetap.

---

## 7.2 Scalability

Jaringan dapat diperluas tanpa mengganggu sistem lama.

Contoh:
Menambah 50 komputer tanpa mengganti seluruh infrastruktur.

---

## 7.3 Quality of Service (QoS)

Mengatur prioritas trafik.

Contoh:
Video conference diprioritaskan dibanding download file.

Tanpa QoS:
Video bisa delay atau patah-patah.

---

## 7.4 Security

Tiga tujuan utama:

1. Confidentiality → hanya pihak berwenang bisa membaca.
2. Integrity → data tidak diubah.
3. Availability → layanan selalu tersedia.

---

# 8. Network Trends

## 8.1 BYOD (Bring Your Own Device)

Karyawan menggunakan perangkat pribadi untuk bekerja.

Keuntungan:

* Fleksibel.
* Produktivitas meningkat.

Risiko:

* Keamanan data.

---

## 8.2 Online Collaboration

Contoh:

* WebEx
* Teams

Digunakan untuk:

* Meeting online
* Chat
* Berbagi file

---

## 8.3 Video Communication

Video conference memungkinkan komunikasi visual jarak jauh.

Digunakan untuk:

* Rapat perusahaan
* Kuliah online

---

## 8.4 Cloud Computing

Data disimpan di server internet.

Jenis:

1. Public Cloud
2. Private Cloud
3. Hybrid Cloud
4. Custom Cloud

Contoh:
Google Drive adalah public cloud.

---

## 8.5 Smart Home

Perangkat rumah terhubung internet.

Contoh:
AC bisa dikontrol dari smartphone.

---

## 8.6 Powerline Networking

Menggunakan kabel listrik sebagai media data.

Cocok jika WiFi tidak menjangkau seluruh rumah.

---

## 8.7 Wireless Broadband

Menggunakan teknologi seluler untuk internet rumah.

Umum di daerah rural.

---

# 9. Network Security

## 9.1 Security Threats

### External Threats

* Virus
* Worm
* Trojan
* DoS
* Zero-day

### Internal Threats

* Human error
* Perangkat hilang
* Karyawan jahat

---

## 9.2 Security Solutions

### Home

* Antivirus
* Firewall

### Enterprise

* Dedicated firewall
* ACL
* IPS
* VPN

Keamanan harus berlapis (defense in depth).

---

# 10. The IT Professional

## 10.1 CCNA

Sertifikasi dasar jaringan dari Cisco.

Fokus:

* IP
* Security
* Wireless
* Automation
* Network programmability

---

## 10.2 Networking Jobs

Melalui NetAcad tersedia akses:

* Talent Bridge
* Lowongan Cisco dan partner

---

# Ringkasan Akhir Modul

Materi ini membahas:

* Peran jaringan dalam kehidupan modern.
* Komponen jaringan (host, server, intermediary).
* LAN dan WAN.
* Koneksi internet rumah dan bisnis.
* Arsitektur jaringan yang andal.
* Tren teknologi modern.
* Keamanan jaringan.
* Sertifikasi dan peluang karier IT.
