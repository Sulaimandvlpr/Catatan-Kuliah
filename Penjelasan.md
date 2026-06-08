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
