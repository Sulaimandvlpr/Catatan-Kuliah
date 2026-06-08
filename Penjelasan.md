Baik, mari kita ubah pendekatannya menjadi lebih formal, akademis, dan terstruktur, selayaknya sebuah **Presentasi Proyek Tugas Akhir atau Ujian Praktikum** di hadapan dosen penguji.

Kita akan membedah kode ini menggunakan terminologi struktur data yang baku (seperti *Abstract Data Type*, *Memory Allocation*, dan *Collision Handling*), namun tetap mempertahankan alur penjelasan yang mengalir dari deklarasi *blueprint* hingga ke implementasi fungsi.

---

# LAPORAN STRUKTUR DATA: SISTEM AUTENTIKASI DAN MANAJEMEN PROFIL

Selamat pagi/siang Bapak/Ibu Dosen. Pada kesempatan ini, saya akan mempresentasikan rancangan program Sistem Autentikasi Pengguna (*AuthSystem*) yang mengintegrasikan tiga struktur data utama secara hibrida, yaitu: **Linked List**, **Hash Table dengan Chaining**, dan **Stack**.

Berikut adalah penjelasan komprehensif mengenai kode implementasi yang telah saya susun:

---

## 1. STRUKTUR DATA DAN ABSTRAKSI MEMORI (*STRUCT*)

Sistem ini didasarkan pada tiga buah komponen entitas (*blueprint*) objek yang saling terhubung di dalam memori:

### A. Komponen Profil Pengguna (`struct UserProfile`)

```cpp
struct UserProfile {
    string username;
    string fullName;
    string bio;
    UserProfile* next;
};

```

Di sini, saya mendefinisikan `UserProfile` sebagai sebuah node tunggal untuk *Singly Linked List*. Struktur ini berfungsi khusus sebagai *storage* representasi data sosial pengguna (*Profile Management*). Node ini mengalokasikan memori untuk variabel `username`, `fullName`, dan `bio`. Pointer `next` di sini bertindak sebagai pengait dinamis ke node profil pengguna berikutnya di dalam memori heap.

### B. Komponen Riwayat Aktivitas (`struct HistoryNode` & `ActivityStack`)

```cpp
struct HistoryNode {
    string activityLog;
    HistoryNode* next;
};

```

Untuk mengimplementasikan fitur pencatatan aktivitas, saya terlebih dahulu membangun `HistoryNode` sebagai entitas pembentuk rantai tumpukan. Setiap node akan menyimpan satu *string* log aktivitas dan pointer ke log sebelumnya.

```cpp
struct ActivityStack {
    HistoryNode* top;
    
    void init() {
        top = nullptr;
    }

```

Selanjutnya, saya membungkus node-node tersebut ke dalam ADT (*Abstract Data Type*) bernama `ActivityStack`. Di dalam *struct* ini, saya mendeklarasikan pointer `top` sebagai penanda puncak tumpukan. Fungsi `init()` di sini bertindak sebagai *pseudo-constructor* untuk memastikan bahwa saat objek *stack* pertama kali diinstansiasi, `top` diinisialisasi ke `nullptr` (keadaan *stack* kosong).

```cpp
    void push(string log) {
        HistoryNode* newNode = new HistoryNode();
        newNode->activityLog = log;
        newNode->next = top;
        top = newNode;
    }

```

* **Operasi `push**`: Prosedur ini melakukan alokasi memori dinamis (`new`) untuk membuat node aktivitas baru. Mekanisme pengaitannya menggunakan prinsip *Insert First*, di mana pointer `next` dari node baru diarahkan ke node yang sedang ditunjuk oleh `top`. Kemudian, alamat `top` diperbarui ke node baru tersebut. Operasi ini memiliki kompleksitas waktu $O(1)$.

```cpp
    string pop() {
        if (top == nullptr) return "";
        HistoryNode* temp = top;
        string log = temp->activityLog;
        top = top->next;
        delete temp;
        return log;
    }

```

* **Operasi `pop**`: Fungsi ini mengembalikan nilai *string* dari log yang dihapus (untuk kebutuhan konfirmasi *undo*). Pertama, sistem melakukan pengecekan kondisi *Underflow* (`top == nullptr`). Jika aman, pointer `temp` digunakan untuk memegang alamat node puncak sementara, nilai `top` digeser ke node di bawahnya (`top->next`), dan memori node lama didealokasikan menggunakan perintah `delete` untuk mencegah terjadinya *memory leak*.

```cpp
    void display() {
        if (top == nullptr) {
            cout << "   (Belum ada riwayat aktivitas)\n";
            return;
        }
        HistoryNode* current = top;
        int i = 1;
        while (current != nullptr) {
            cout << "   " << i++ << ". " << current->activityLog << "\n";
            current = current->next;
        }
    }
};

```

* **Operasi `display**`: Di sini saya menerapkan algoritma *Linked List Traversal*. Pointer eksternal `current` melakukan penelusuran secara sequensial dari elemen `top` hingga menemukan `nullptr`, memformat keluaran indeks secara inkremental ($i++$), dengan kompleksitas waktu sebesar $O(n)$.

---

### C. Komponen Akun Utama (`struct UserAccount`)

```cpp
struct UserAccount {
    string username;
    string password;
    UserProfile* profileRef; 
    ActivityStack history;   
    UserAccount* next;       
};

```

Ini adalah struktur data inti dari sistem autentikasi. Di dalam `UserAccount`, saya menggabungkan beberapa konsep sekaligus:

1. Kredensial login (`username` dan `password`).
2. **Pointer Referensi (`profileRef`)**: Sebuah pointer yang menunjuk secara silang (*cross-reference*) ke node `UserProfile` yang berada di Linked List profil. Ini menghemat memori karena kita tidak melakukan duplikasi data profil di dalam akun.
3. **Komposisi Objek (`history`)**: Setiap objek akun memiliki instansi *stack*-nya sendiri secara independen.
4. **Pointer Suksesor (`next`)**: Pointer ini murni digunakan untuk menangani masalah *Collision* pada Hash Table dengan metode penambatan rantai (*Separate Chaining*).

---

## 2. ARSITEKTUR KELAS UTAMA (`struct AuthSystem`)

```cpp
struct AuthSystem {
    static const int TABLE_SIZE = 10;
    UserAccount* hashTable[TABLE_SIZE];
    UserProfile* headProfile; 

```

Pada bagian perancangan sistem manajemen utama, saya mendeklarasikan kontainer `hashTable` berupa *array of pointers* dengan ukuran statis `TABLE_SIZE = 10`. Selain itu, terdapat pointer `headProfile` yang berfungsi sebagai *entry point* (kepala) dari struktur data *Singly Linked List* yang menampung seluruh data profil pengguna global.

Di bawah baris ini, saya mendeklarasikan *prototype* dari seluruh *method* atau fungsi modular sistem, yang memisahkan antara fase deklarasi dengan fase implementasi untuk menjaga kerapian kode (*clean code*).

---

## 3. IMPLEMENTASI METODE DAN ALGORITMA

### A. Algoritma Transformasi Kunci Kriptografi / Hashing (`hashFunction`)

```cpp
int AuthSystem::hashFunction(string key) {
    int sum = 0;
    for (char ch : key) {
        sum += ch;
    }
    return sum % TABLE_SIZE;
}

```

Di sini saya menerapkan algoritma **Component Sum** dikombinasikan dengan metode **Division (Modulo)**. Fungsi ini melakukan iterasi terhadap setiap karakter pada parameter `key` (username), mengonversinya menjadi nilai integer berbasis ASCII, dan menjumlahkannya ke variabel `sum`.

Hasil penjumlahan kemudian di-modulo dengan `TABLE_SIZE` (10) untuk memetakan string dengan panjang dinamis tersebut menjadi indeks array yang valid (berada pada rentang rentang $0 \dots 9$).

### B. Prosedur Inisialisasi Memori Global (`init`)

```cpp
void AuthSystem::init() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = nullptr;
    }
    headProfile = nullptr;
}

```

Prosedur `init` bertanggung jawab untuk melakukan *clearing* memori sebelum sistem beroperasi. Array `hashTable` dipastikan bersih dengan mengisi seluruh indeksnya dengan `nullptr`, begitu pula dengan status `headProfile`. Langkah ini sangat krusial dalam bahasa C++ untuk menghindari *wild pointer* (pointer yang menunjuk ke alamat acak di memori).

### C. Validasi Keunikan Data pada Fitur Registrasi (`registerAccount`)

```cpp
bool AuthSystem::registerAccount(string username, string password, string fullName, string bio) {
    if (searchAccount(username) != nullptr) {
        cout << "\n[Gagal] Username '" << username << "' sudah terdaftar!\n";
        return false;
    }

```

Pada bagian awal fungsi `registerAccount`, saya menerapkan aspek **Integritas Data**. Sebelum mengalokasikan ruang memori untuk akun baru, sistem wajib memanggil fungsi `searchAccount(username)` untuk melakukan pencarian di dalam Hash Table.

Jika hasil pencarian mengembalikan sebuah objek (`!= nullptr`), ini menjadi indikasi terjadinya duplikasi data (*username-collision* pada level bisnis aplikasi). Sistem secara preventif akan menolak proses registrasi, mengeluarkan pesan kesalahan, dan mengembalikan nilai boolean `false` ke *driver program*.

*(Catatan: Jika fungsi ini lolos validasi, alur program selanjutnya akan melakukan operasi pemesanan memori dinamis untuk `UserProfile` dan `UserAccount`, menghubungkan pointer referensi keduanya, menghitung indeks hash, dan menaruh objek akun tersebut di barisan depan slot hash table terkait via teknik chaining).*

---

## KESIMPULAN ANALISIS

Secara keseluruhan, arsitektur kode ini berhasil mengombinasikan keunggulan **Hash Table** dalam melakukan operasi pencarian (*searching*) dan autentikasi dengan kompleksitas rata-rata $O(1)$, fleksibilitas penyisipan data dinamis pada **Linked List** tanpa perlu menggeser elemen memori, serta ketepatan fungsi *undo* berbasis kronologis terbalik menggunakan karakteristik LIFO dari struktur **Stack**.

Demikian penjelasan teknis mengenai arsitektur kode program yang saya buat, Terima kasih, Bapak/Ibu Dosen.



Baik, mari kita lanjutkan presentasi akademis ini untuk membedah sisa fungsi logika bisnis aplikasi beserta alur program utamanya (`main function`).

Saya akan menjelaskan kode-kode ini dengan memposisikan diri sebagai mahasiswa yang mempertahankan arsitektur sistem di hadapan Bapak/Ibu Dosen penguji.

---

## 3. IMPLEMENTASI METODE DAN ALGORITMA (LANJUTAN)

### D. Kelanjutan Prosedur Registrasi Akun (`registerAccount`)

```cpp
    UserProfile* newProfile = new UserProfile();
    newProfile->username = username;
    newProfile->fullName = fullName;
    newProfile->bio = bio;
    newProfile->next = headProfile;
    headProfile = newProfile;

```

Di sini saya melanjutkan proses instansiasi setelah lolos validasi keunikan username. Langkah pertama adalah memesan memori dinamis untuk objek `UserProfile`. Pengisian data sosial dilakukan secara manual. Guna efisiensi waktu, saya menerapkan metode **Insert First** pada *Singly Linked List* profil global, di mana node baru ditunjuk ke `headProfile` saat ini, kemudian pointer `headProfile` digeser untuk menunjuk node baru ini. Kompleksitasnya adalah $O(1)$.

```cpp
    int index = hashFunction(username);
    UserAccount* newAccount = new UserAccount();
    newAccount->username = username;
    newAccount->password = password;
    newAccount->profileRef = newProfile;
    newAccount->history.init();

```

Langkah kedua adalah menentukan pemetaan memori pada *Hash Table* dengan memanggil `hashFunction(username)` untuk mendapatkan nilai variabel `index`. Setelah memori untuk `UserAccount` dialokasikan, sistem melakukan teknik **Cross-Referencing**, yaitu mengikat pointer `profileRef` langsung ke alamat memori `newProfile` yang baru saja dibuat. Di sini saya juga menginisialisasi tumpukan aktivitas khusus akun tersebut melalui fungsi `history.init()`.

```cpp
    newAccount->next = hashTable[index];
    hashTable[index] = newAccount;

    newAccount->history.push("Melakukan registrasi akun.");
    cout << "\n[Sukses] Akun berhasil didaftarkan!\n";
    return true;
}

```

Langkah ketiga adalah mengatasi masalah *Collision* menggunakan teknik **Separate Chaining**. Di sini saya memilih metode *Insert First* di level slot array. Node akun baru diarahkan untuk menunjuk elemen awal yang berada di slot `hashTable[index]`, baru kemudian `hashTable[index]` diperbarui ke alamat akun yang baru.

Sebelum fungsi mengembalikan nilai `true`, sistem secara otomatis melakukan trigger operasi `push` pada objek *stack* internal milik akun untuk mencatat log registrasi.

---

### E. Fungsi Otentikasi dan Autentikasi Pengguna (`loginAccount`)

```cpp
UserAccount* AuthSystem::loginAccount(string username, string password) {
    UserAccount* account = searchAccount(username);
    if (account != nullptr && account->password == password) {
        account->history.push("Berhasil login ke sistem.");
        return account;
    }
    return nullptr;
}

```

Fungsi `loginAccount` bertindak sebagai gerbang validasi akses (keamanan). Fungsi ini memanfaatkan metode pencarian cepat `searchAccount` yang berbasis Hashing.

Apabila objek akun ditemukan (`!= nullptr`) **dan** string kredensial `password` yang tersimpan di dalam memori heap cocok dengan parameter input, maka autentikasi dinyatakan valid. Sistem langsung mencatatkan riwayat login ke dalam *stack* personal user tersebut, lalu mengembalikan alamat pointer akun tersebut untuk dialokasikan pada sesi login aktif di fungsi utama. Jika gagal, fungsi mengembalikan nilai `nullptr`.

---

### F. Prosedur Mutasi Data Profil (`editProfile`)

```cpp
void AuthSystem::editProfile(UserAccount* account, string newName, string newBio) {
    if (account == nullptr || account->profileRef == nullptr) return;
    
    account->profileRef->fullName = newName;
    account->profileRef->bio = newBio;
    
    account->history.push("Mengubah informasi profil.");
    cout << "\n[Sukses] Profil berhasil diperbarui!\n";
}

```

Pada prosedur `editProfile`, saya menerapkan konsep **Data Pointer Mutator**. Fungsi ini menerima alamat objek akun yang sedang aktif. Sebelum melakukan mutasi, sistem melakukan tindakan preventif pertahanan kode (*defensive programming*) untuk memastikan tidak terjadi *Null Pointer Dereference Error*.

Melalui jembatan pointer referensi (`account->profileRef->`), sistem langsung menuju alamat fisik memori node `UserProfile` di Linked List untuk mengubah isi variabel `fullName` dan `bio`. Tindakan pembaruan ini diakhiri dengan pencatatan otomatis ke dalam log riwayat aktivitas.

---

### G. Implementasi Mekanisme Pembatalan Aksi (`undoActivity`)

```cpp
void AuthSystem::undoActivity(UserAccount* account) {
    if (account == nullptr) return;
    string undoneAction = account->history.pop();
    if (undoneAction == "") {
        cout << "\n[Info] Tidak ada aktivitas yang bisa di-undo.\n";
    } else {
        cout << "\n[Undo Berhasil] Aktivitas dibatalkan: \"" << undoneAction << "\"\n";
    }
}

```

Prosedur `undoActivity` merepresentasikan pemanfaatan struktur data **Stack (Last In, First Out)** secara riil. Fungsi ini memanggil operasi `pop()` dari objek *stack* internal akun pengguna.

Nilai kembalian berupa string ditampung dalam variabel `undoneAction`. Jika string yang kembali dalam keadaan kosong `""`, artinya tumpukan memori riwayat memang sudah kosong (*Underflow*). Sebaliknya, jika ada string aktivitas yang berhasil di-*pop*, data tersebut dikeluarkan dari memori dan sistem mencetak pemberitahuan aksi apa yang berhasil dibatalkan secara kronologis terbalik.

---

### H. Algoritma Pencarian Berbasis Hash dan Chaining (`searchAccount`)

```cpp
UserAccount* AuthSystem::searchAccount(string username) {
    int index = hashFunction(username);
    UserAccount* current = hashTable[index];
    while (current != nullptr) {
        if (current->username == username) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

```

Fungsi `searchAccount` adalah modul yang sangat krusial dalam menentukan efisiensi sistem. Algoritma pencariannya tidak melakukan *Linear Search* dari indeks array 0 hingga akhir, melainkan langsung menuju target lokasi lewat perhitungan `hashFunction(username)`.

Setelah melompat ke slot array `hashTable[index]`, sistem mengantisipasi kemungkinan adanya *Collision* dengan melakukan *Traversal* penelusuran berantai (`while(current != nullptr)`) di sepanjang tautan rantai *chaining* tersebut. Jika string `username` ditemukan cocok, pointer alamat akun langsung dikembalikan ($O(1)$ pada kondisi rata-rata/ideal). Jika rantai putus dan tidak ditemukan, fungsi mengembalikan `nullptr`.

---

### I. Prosedur Representasi Informasi Pengguna (`displayUserInfo`)

```cpp
void AuthSystem::displayUserInfo(UserAccount* account) {
    if (account == nullptr) return;
    cout << "\n=== PROFIL PENGGUNA ===\n";
    cout << "Username  : " << account->profileRef->username << "\n";
    cout << "Nama      : " << account->profileRef->fullName << "\n";
    cout << "Bio       : " << account->profileRef->bio << "\n";
    cout << "-----------------------\n";
    cout << "Histori Aktivitas (Terbaru di atas):\n";
    account->history.display();
    cout << "=======================\n";
}

```

Prosedur `displayUserInfo` berfungsi sebagai komponen penampil data (*View Handler*). Di sini terjadi pemanggilan berantai, di mana sistem menampilkan identitas sosial yang diakses dari referensi Linked List profil (`account->profileRef`), sekaligus memicu delegasi fungsi `account->history.display()` untuk mencetak grafik tumpukan riwayat aktivitas yang tersimpan di dalam objek *stack*.

---

## 4. ALUR PROGRAM UTAMA (`int main`)

Fungsi `main()` di sini bertindak sebagai *Driver Program* sekaligus pengendali antarmuka pengguna berbasis menu tekstual (*Command Line Interface*).

```cpp
int main() {
    AuthSystem systemAuth;
    systemAuth.init();
    UserAccount* loggedInUser = nullptr;
    int choice;

```

Di awal fungsi `main`, saya menginstansiasi objek `systemAuth` dan langsung memicu fungsi alokasi `init()`. Variabel `loggedInUser` bertindak sebagai **State Indicator** berbasis pointer. Status pointer ini sangat krusial: jika nilainya `nullptr`, berarti sistem berada dalam *State* "Belum Login". Jika berisi alamat memori, artinya sistem berada dalam *State* "Sesi Pengguna Aktif".

### Konsep State Machine pada Loop `while(true)`

Saya menerapkan struktur perulangan tak terbatas (`while(true)`) yang didalamnya dibagi menjadi dua percabangan logika kondisi *State Indikator*:

#### 1. Menu Pra-Login (`if (loggedInUser == nullptr)`)

Pada blok ini, pengguna hanya diberikan hak akses fungsionalitas terbatas:

* **Menu 1 (Registrasi)**: Mengambil input string via `cin` dan `getline` (dengan pembersihan buffer `cin.ignore()`), lalu melemparkannya ke fungsi `registerAccount`.
* **Menu 2 (Login)**: Menerima masukan kredensial, dan memperbarui *State Indikator* `loggedInUser = systemAuth.loginAccount()`. Jika sukses, pointer tidak lagi `nullptr`.
* **Menu 3 (Cari Akun Global)**: Memungkinkan pencarian cepat eksistensi akun pengguna lain di sistem tanpa hak mutasi.

#### 2. Menu Pasca-Login / Dashboard Kontrol (`else`)

Ketika status `loggedInUser` mendeteksi adanya alamat memori aktif, sistem otomatis mengalihkan visualisasi menu ke fungsionalitas privat pengguna:

* **Menu 1 (Lihat Profil)**: Menambahkan log melihat profil ke dalam *stack* secara dinamis, lalu menyajikan data profil terintegrasi.
* **Menu 2 (Edit Profil)**: Menangkap string nama dan bio baru, kemudian memanggil metode mutasi `editProfile` terhadap pointer sesi yang aktif.
* **Menu 3 (Undo)**: Mengeksekusi fungsi pembatalan aksi kronologis berbasis LIFO.
* **Menu 5 (Logout)**: Langkah krusial di mana sistem mengamankan log penutupan sesi ke dalam *stack*, lalu menghancurkan sesi dengan mengembalikan nilai indikator pointer `loggedInUser` kembali ke status primitifnya yaitu `nullptr`. Ini mengembalikan alur program secara otomatis ke menu pra-login.

---

## KESIMPULAN PERTAHANAN KODE

Melalui rancangan fungsi `main` ini, kontrol alur program menjadi sangat aman karena akses terhadap fungsi-fungsi sensitif seperti `editProfile` dan `undoActivity` dikunci secara struktural dan hanya bisa dieksekusi apabila parameter *State Indikator* `loggedInUser` terbukti memegang referensi alamat objek memori akun yang valid hasil dari proses autentikasi fungsi `loginAccount`.

Demikian penjelasan lengkap mengenai seluruh baris kode dan implementasi sistem hibrida struktur data yang saya susun. Terima kasih atas perhatian Bapak/Ibu Dosen.
