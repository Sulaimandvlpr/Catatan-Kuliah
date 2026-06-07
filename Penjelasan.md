# Proyek 3: Sistem Login dan Riwayat Aktivitas Pengguna

ADT yang digunakan: **Linked List**, **Stack**, **Hash Table (Division Method)**

---

## Daftar Isi
1. [Konstanta & Struct](#1-konstanta--struct)
2. [Variabel Global](#2-variabel-global)
3. [Stack](#3-stack)
4. [Hash Table](#4-hash-table)
5. [Linked List](#5-linked-list)
6. [Helper: catat()](#6-helper-catat)
7. [Fitur Sistem](#7-fitur-sistem)
8. [Menu & Main](#8-menu--main)

---

## 1. Konstanta & Struct

### Konstanta
```cpp
const int TABLE_SIZE = 20, MAX_HISTORY = 10;
```
- `const` artinya nilainya **tidak bisa diubah** sepanjang program berjalan
- `TABLE_SIZE = 20` → hash table punya 20 slot
- `MAX_HISTORY = 10` → setiap akun menyimpan maksimal 10 riwayat aktivitas

---

### Struct Stack
```cpp
struct Stack {
    string data[MAX_HISTORY];
    int top;
};
```
`struct` adalah cetakan/template untuk membuat sebuah objek. `Stack` adalah cetakan untuk menyimpan riwayat aktivitas user.

| Baris | Penjelasan |
|---|---|
| `string data[MAX_HISTORY]` | Array berisi 10 kotak, masing-masing kotak menyimpan satu teks aktivitas seperti `"Login"`, `"Edit profil"`, dll |
| `int top` | Angka penunjuk — menunjuk slot kosong berikutnya. Bukan tempat simpan aktivitas, hanya penanda posisi |

Visualisasi stack milik Andi setelah login dan lihat profil:
```
data[0] = "Login"         ← aktivitas pertama
data[1] = "Lihat profil"  ← aktivitas kedua
data[2] = ""              ← top = 2, slot kosong berikutnya di sini
data[3] = ""
...
data[9] = ""
```

---

### Struct AkunNode
```cpp
struct AkunNode {
    string username, password;
    Stack histori;
    AkunNode* next;
};
```
Cetakan untuk satu node di dalam hash table. Setiap akun yang registrasi akan membuat satu `AkunNode`.

| Baris | Penjelasan |
|---|---|
| `string username, password` | Menyimpan username dan password akun |
| `Stack histori` | Setiap akun punya stack histori **sendiri-sendiri** |
| `AkunNode* next` | Pointer ke node berikutnya, dipakai saat terjadi collision (chaining) |

---

### Struct ProfilNode
```cpp
struct ProfilNode {
    string username, nama, email, noHp;
    ProfilNode* next;
};
```
Cetakan untuk satu node di dalam linked list profil. Setiap akun yang registrasi juga membuat satu `ProfilNode`.

| Baris | Penjelasan |
|---|---|
| `string username, nama, email, noHp` | Menyimpan data diri user |
| `ProfilNode* next` | Pointer ke node profil berikutnya di linked list |

---

## 2. Variabel Global

```cpp
AkunNode*  hashTable[TABLE_SIZE];
ProfilNode* headProfil = nullptr;
string userLogin = "";
```

| Baris | Penjelasan |
|---|---|
| `AkunNode* hashTable[TABLE_SIZE]` | Array berisi 20 pointer, masing-masing menunjuk ke node akun (atau `nullptr` kalau slot kosong) |
| `ProfilNode* headProfil = nullptr` | Pointer ke node pertama linked list profil. `nullptr` artinya list masih kosong |
| `string userLogin = ""` | Menyimpan username yang sedang login. Kalau kosong `""` artinya belum ada yang login |

---

## 3. Stack

### stackCreate
```cpp
void stackCreate(Stack& s) { s.top = 0; }
```
Dipanggil saat akun baru dibuat. Set `top = 0` artinya stack masih kosong, belum ada satu aktivitas pun.

`Stack& s` → tanda `&` artinya fungsi mengakses stack **asli**, bukan salinannya. Perubahan `top = 0` benar-benar mengubah stack yang dikirim.

---

### stackIsEmpty & stackIsFull
```cpp
bool stackIsEmpty(Stack& s) { return s.top == 0; }
bool stackIsFull(Stack& s)  { return s.top == MAX_HISTORY; }
```
Dua fungsi penjaga. Keduanya mengembalikan `true` atau `false`.

- `s.top == 0` → kalau `top` masih 0 berarti belum ada isi → return `true`
- `s.top == MAX_HISTORY` → kalau `top` sudah 10 berarti semua slot penuh → return `true`

Dipakai sebagai pengecekan sebelum push dan pop:
```
Sebelum Push → cek stackIsFull
Sebelum Pop  → cek stackIsEmpty
```

---

### stackPush
```cpp
void stackPush(Stack& s, string aktivitas) {
    if (stackIsFull(s)) {
        for (int i = 0; i < MAX_HISTORY - 1; i++) s.data[i] = s.data[i + 1];
        s.data[MAX_HISTORY - 1] = aktivitas;
    } else {
        s.data[s.top++] = aktivitas;
    }
}
```
Dipanggil otomatis oleh sistem setiap kali user melakukan sesuatu. User tidak perlu input manual, sistem yang memanggil fungsi ini di belakang layar.

#### Kondisi ELSE — stack belum penuh
```cpp
s.data[s.top++] = aktivitas;
```
`s.top++` artinya: pakai nilai `top` dulu untuk menyimpan, **baru naikkan** setelah selesai. Ini penulisan ringkas dari:
```cpp
s.data[s.top] = aktivitas; // simpan dulu
s.top++;                   // baru naik
```

**Contoh:** Andi baru login, `top = 0`.

Sistem panggil `stackPush(s, "Login")`:
```
s.data[0] = "Login"   ← disimpan di index 0
top: 0 → naik → 1

Kondisi array:
data[0] = "Login"
data[1] = ""          ← top = 1, giliran ini berikutnya
...
```

Andi lihat profil, `top = 1`. Sistem panggil `stackPush(s, "Lihat profil")`:
```
s.data[1] = "Lihat profil"
top: 1 → naik → 2

Kondisi array:
data[0] = "Login"
data[1] = "Lihat profil"
data[2] = ""              ← top = 2
...
```

#### Kondisi IF — stack sudah penuh (top = 10)
```cpp
for (int i = 0; i < MAX_HISTORY - 1; i++) s.data[i] = s.data[i + 1];
s.data[MAX_HISTORY - 1] = aktivitas;
```
Karena tidak ada slot kosong, aktivitas paling lama dibuang, semua digeser ke bawah, lalu yang baru masuk di index 9.

**Kenapa `MAX_HISTORY - 1` di kondisi loop?**
Di dalam loop ada `i + 1`. Kalau `i` sampai 9 maka `i + 1 = 10` dan index 10 tidak ada (array hanya sampai 9). Makanya loop berhenti sebelum `i = 9`, yaitu maksimal `i = 8`.

**Contoh:** Stack sudah penuh, Andi lakukan aktivitas baru `"Ganti password"`.

Kondisi sebelum:
```
data[0] = "Login"           ← akan hilang
data[1] = "Lihat profil"
data[2] = "Edit profil"
data[3] = "Cari Budi"
data[4] = "Lihat histori"
data[5] = "Edit profil"
data[6] = "Cari Cici"
data[7] = "Lihat profil"
data[8] = "Undo"
data[9] = "Cari Dodi"
top = 10
```

Loop berjalan, setiap slot ditimpa oleh slot di atasnya:
```
i=0: data[0] = data[1] → data[0] jadi "Lihat profil"  ("Login" hilang)
i=1: data[1] = data[2] → data[1] jadi "Edit profil"
i=2: data[2] = data[3] → data[2] jadi "Cari Budi"
...
i=8: data[8] = data[9] → data[8] jadi "Cari Dodi"
```

Setelah loop, `data[9]` masih isi lama. Baris berikutnya timpa dengan yang baru:
```cpp
s.data[MAX_HISTORY - 1] = aktivitas;
// s.data[9] = "Ganti password"
```

Hasil akhir:
```
data[0] = "Lihat profil"
data[1] = "Edit profil"
...
data[8] = "Cari Dodi"
data[9] = "Ganti password"  ← aktivitas baru masuk
top = 10                    ← top tidak berubah
```

---

### stackPop
```cpp
string stackPop(Stack& s) {
    if (stackIsEmpty(s)) return "";
    string hasil = s.data[--s.top];
    s.data[s.top] = "";
    return hasil;
}
```
Dipanggil saat user memilih fitur Undo. Mengambil dan menghapus aktivitas paling baru.

| Baris | Penjelasan |
|---|---|
| `if (stackIsEmpty(s)) return ""` | Kalau stack kosong, langsung kembalikan string kosong, tidak ada yang dihapus |
| `string hasil = s.data[--s.top]` | `--s.top` artinya turunkan `top` dulu **baru** ambil. Kebalikan dari `top++`. Hasilnya disimpan ke `hasil` |
| `s.data[s.top] = ""` | Kosongkan slot yang tadi diambil |
| `return hasil` | Kembalikan teks aktivitas yang dihapus, supaya bisa ditampilkan ke user |

**Contoh:** Stack berisi 3 aktivitas, `top = 3`. Andi pencet Undo.
```
Sebelum:
data[0] = "Login"
data[1] = "Lihat profil"
data[2] = "Edit profil"    ← top = 3 (menunjuk ke sini sebagai slot kosong)

--s.top → top turun jadi 2
hasil = data[2] = "Edit profil"
data[2] = ""   (dikosongkan)

Sesudah:
data[0] = "Login"
data[1] = "Lihat profil"   ← top = 2 sekarang
data[2] = ""
```
Layar menampilkan: `'Edit profil' berhasil di-undo.`

---

### stackDisplay
```cpp
void stackDisplay(Stack& s) {
    if (stackIsEmpty(s)) { cout << "  (belum ada aktivitas)\n"; return; }
    for (int i = s.top - 1; i >= 0; i--)
        cout << "  " << (s.top - i) << ". " << s.data[i] << "\n";
}
```
Menampilkan histori dari **terbaru ke terlama** (dari atas tumpukan ke bawah).

Loop mulai dari `s.top - 1` (index paling atas yang terisi) mundur sampai `i = 0`.

**Contoh:** Stack berisi 3 aktivitas, `top = 3`.
```
i=2: tampilkan data[2] = "Edit profil"   → nomor 1 (terbaru)
i=1: tampilkan data[1] = "Lihat profil"  → nomor 2
i=0: tampilkan data[0] = "Login"         → nomor 3 (terlama)
```

Output di layar:
```
===== HISTORI AKTIVITAS =====
  1. Edit profil
  2. Lihat profil
  3. Login
```

---

## 4. Hash Table

### hashInit
```cpp
void hashInit() { for (int i = 0; i < TABLE_SIZE; i++) hashTable[i] = nullptr; }
```
Dipanggil sekali di `main()` saat program pertama jalan. Mengisi semua 20 slot hash table dengan `nullptr` (kosong).

---

### hashFunction
```cpp
int hashFunction(string key) {
    int total = 0;
    for (int i = 0; i < (int)key.length(); i++) total += tolower(key[i]) - 'a';
    return total % TABLE_SIZE;
}
```
Mengubah username menjadi angka index (0–19) menggunakan **Division Method**.

Cara kerjanya:
1. Setiap huruf username diubah ke huruf kecil dengan `tolower()`
2. Dikurangi `'a'` untuk dapat nilai angkanya: `a=0, b=1, c=2, ..., z=25`
3. Semua nilai dijumlahkan
4. Hasilnya di-modulus dengan `TABLE_SIZE (20)` untuk dapat index 0–19

**Contoh:** username `"Andi"`
```
A → tolower → 'a' → 'a' - 'a' = 0
n → tolower → 'n' → 'n' - 'a' = 13
d → tolower → 'd' → 'd' - 'a' = 3
i → tolower → 'i' → 'i' - 'a' = 8

total = 0 + 13 + 3 + 8 = 24
index = 24 % 20 = 4

Andi disimpan di hashTable[4]
```

---

### hashCari
```cpp
AkunNode* hashCari(string username) {
    AkunNode* cur = hashTable[hashFunction(username)];
    while (cur != nullptr) {
        if (cur->username == username) return cur;
        cur = cur->next;
    }
    return nullptr;
}
```
Mencari akun berdasarkan username. Return pointer ke node akun jika ditemukan, `nullptr` jika tidak ada.

| Baris | Penjelasan |
|---|---|
| `AkunNode* cur = hashTable[hashFunction(username)]` | Hitung index username, lalu langsung lompat ke slot itu |
| `while (cur != nullptr)` | Telusuri linked list di slot itu (bisa lebih dari satu karena chaining) |
| `if (cur->username == username) return cur` | Kalau ketemu, langsung kembalikan pointer node-nya |
| `cur = cur->next` | Kalau belum ketemu, lanjut ke node berikutnya |
| `return nullptr` | Kalau sudah habis dan tidak ketemu, kembalikan nullptr |

**Contoh:** Andi login, sistem cari `"Andi"`.
```
hashFunction("Andi") = 4
cur = hashTable[4]   → menunjuk ke node Andi

cur->username = "Andi" == "Andi" ? IYA → return node Andi
```

---

### hashInsert
```cpp
bool hashInsert(string username, string password) {
    if (hashCari(username) != nullptr) return false;
    int index = hashFunction(username);
    AkunNode* baru = new AkunNode();
    baru->username = username; baru->password = password;
    baru->next = nullptr; stackCreate(baru->histori);
    if (hashTable[index] == nullptr) {
        hashTable[index] = baru;
    } else {
        AkunNode* cur = hashTable[index];
        while (cur->next != nullptr) cur = cur->next;
        cur->next = baru;
    }
    return true;
}
```
Menambah akun baru ke hash table.

| Baris | Penjelasan |
|---|---|
| `if (hashCari(username) != nullptr) return false` | Cek dulu, kalau username sudah ada langsung tolak |
| `AkunNode* baru = new AkunNode()` | Buat node akun baru di memori |
| `baru->username = ...` | Isi data node dengan username dan password yang diinput |
| `baru->next = nullptr` | Node baru belum punya sambungan ke mana-mana |
| `stackCreate(baru->histori)` | Inisialisasi stack histori untuk akun ini (`top = 0`) |
| `if (hashTable[index] == nullptr)` | Kalau slot kosong, langsung taruh di situ |
| `else { ... cur->next = baru }` | Kalau slot sudah ada isi (collision), sambungkan di ujung linked list (chaining) |

**Contoh — tanpa collision:** Andi registrasi, index = 4, `hashTable[4]` masih kosong.
```
hashTable[4] = nullptr → langsung taruh
hashTable[4] → [Andi | pass123 | histori | nullptr]
```

**Contoh — collision:** Budi registrasi, ternyata index Budi juga = 4.
```
hashTable[4] sudah ada Andi → masuk else
Telusuri sampai ujung: Andi->next = nullptr
Sambungkan: Andi->next = node Budi

hashTable[4] → [Andi] → [Budi] → nullptr
```

---

## 5. Linked List

### profilTambah
```cpp
void profilTambah(string username, string nama, string email, string noHp) {
    ProfilNode* baru = new ProfilNode();
    baru->username = username; baru->nama = nama;
    baru->email = email; baru->noHp = noHp; baru->next = nullptr;
    if (headProfil == nullptr) { headProfil = baru; return; }
    ProfilNode* cur = headProfil;
    while (cur->next != nullptr) cur = cur->next;
    cur->next = baru;
}
```
Menambah profil baru di **ujung belakang** linked list.

| Baris | Penjelasan |
|---|---|
| `ProfilNode* baru = new ProfilNode()` | Buat node profil baru di memori |
| `baru->next = nullptr` | Node baru belum tersambung ke mana-mana |
| `if (headProfil == nullptr)` | Kalau list masih kosong, node baru langsung jadi kepala |
| `while (cur->next != nullptr) cur = cur->next` | Kalau list sudah ada isi, jalan terus sampai node paling akhir |
| `cur->next = baru` | Sambungkan node baru di ujung |

**Contoh:** Andi registrasi, list masih kosong.
```
headProfil = nullptr → headProfil = node Andi

headProfil → [Andi | Andi Saputra | andi@gmail.com | 08111 | nullptr]
```

Budi registrasi, list sudah ada Andi.
```
Telusuri: Andi->next = nullptr → ini ujungnya
Andi->next = node Budi

headProfil → [Andi] → [Budi] → nullptr
```

---

### profilCari
```cpp
ProfilNode* profilCari(string username) {
    ProfilNode* cur = headProfil;
    while (cur != nullptr) {
        if (cur->username == username) return cur;
        cur = cur->next;
    }
    return nullptr;
}
```
Menelusuri linked list dari kepala sampai ketemu node yang usernamenya cocok.

**Contoh:** Cari profil `"Budi"`. List: Andi → Budi → Cici.
```
cur = Andi → "Andi" == "Budi"? TIDAK → cur = cur->next
cur = Budi → "Budi" == "Budi"? IYA  → return node Budi
```

---

### tampilProfil
```cpp
void tampilProfil(ProfilNode* p) {
    cout << "  Username : " << p->username << "\n"
         << "  Nama     : " << p->nama     << "\n"
         << "  Email    : " << p->email    << "\n"
         << "  No HP    : " << p->noHp     << "\n";
}
```
Menerima pointer ke node profil, lalu tampilkan semua datanya ke layar. `p->username` artinya akses field `username` dari node yang ditunjuk pointer `p`.

---

## 6. Helper: catat()

```cpp
void catat(string aktivitas) {
    AkunNode* akun = hashCari(userLogin);
    if (akun != nullptr) stackPush(akun->histori, aktivitas);
}
```
Fungsi pembantu yang dipanggil di setiap fitur. Tugasnya mencatat aktivitas ke stack milik user yang sedang login.

| Baris | Penjelasan |
|---|---|
| `hashCari(userLogin)` | Cari node akun berdasarkan username yang sedang login |
| `if (akun != nullptr)` | Pastikan akun ditemukan sebelum push |
| `stackPush(akun->histori, aktivitas)` | Push teks aktivitas ke stack milik akun itu |

**Contoh:** Andi sedang login (`userLogin = "Andi"`), lalu buka lihat profil.
```
catat("Lihat profil") dipanggil
→ hashCari("Andi") → dapat node Andi
→ stackPush(node_Andi->histori, "Lihat profil")
→ "Lihat profil" tersimpan di stack Andi
```

---

## 7. Fitur Sistem

### registrasi()
```cpp
void registrasi() {
    ...
    if (!hashInsert(username, password)) { cout << "[!] Username sudah terdaftar!\n"; return; }
    profilTambah(username, nama, email, noHp);
    cout << "[v] Registrasi berhasil!\n";
}
```
User mengisi username, password, nama, email, no HP.

- `hashInsert` → simpan username + password ke hash table, sekaligus inisialisasi stack histori
- `profilTambah` → simpan data diri ke linked list
- Kalau `hashInsert` return `false` (username sudah ada), registrasi ditolak

---

### login()
```cpp
bool login() {
    ...
    AkunNode* akun = hashCari(username);
    if (akun == nullptr || akun->password != password) {
        cout << "[!] Username atau password salah!\n"; return false;
    }
    userLogin = username;
    catat("Login");
    ...
}
```
- `hashCari(username)` → cari akun di hash table
- Cek dua kondisi: akun tidak ada (`nullptr`) **atau** password tidak cocok
- Kalau lolos: simpan username ke `userLogin`, catat aktivitas "Login"

---

### editProfil()
```cpp
void editProfil() {
    ProfilNode* p = profilCari(userLogin);
    ...
    p->nama = nama; p->email = email; p->noHp = noHp;
    catat("Edit profil");
}
```
- Cari node profil user yang sedang login di linked list
- Langsung ubah field `nama`, `email`, `noHp` di node tersebut
- Catat aktivitas "Edit profil" ke stack

---

### lihatHistori()
```cpp
void lihatHistori() {
    stackDisplay(hashCari(userLogin)->histori);
}
```
- Cari node akun user yang sedang login
- Akses field `histori` (stack) dari node itu
- Tampilkan isi stack dari terbaru ke terlama

---

### undo()
```cpp
void undo() {
    string terakhir = stackPop(hashCari(userLogin)->histori);
    if (terakhir.empty()) cout << "[!] Tidak ada aktivitas untuk di-undo.\n";
    else cout << "[v] '" << terakhir << "' berhasil di-undo.\n";
}
```
- `stackPop` mengambil dan menghapus aktivitas paling baru dari stack
- Kalau return string kosong `""` → stack memang kosong, tidak ada yang di-undo
- Kalau return teks → tampilkan ke user aktivitas apa yang berhasil di-undo

---

### cariAkun()
```cpp
void cariAkun() {
    ...
    AkunNode* akun = hashCari(username);
    if (akun == nullptr) { cout << "[!] Akun tidak ditemukan.\n"; return; }
    tampilProfil(profilCari(username));
    catat("Cari akun: " + username);
}
```
- Cari akun di hash table berdasarkan username yang diinput
- Kalau tidak ditemukan, tampilkan pesan error
- Kalau ditemukan, ambil profilnya dari linked list dan tampilkan
- Catat aktivitas pencarian ke stack

---

## 8. Menu & Main

### menuLogin()
```cpp
void menuLogin() {
    int p;
    do {
        ...
        if (p == 1) registrasi();
        else if (p == 2) { if (login()) return; }
    } while (p != 0);
}
```
Loop terus tampilkan menu sampai user pilih `0` (keluar) atau berhasil login. Kalau `login()` return `true` (berhasil), fungsi ini langsung `return` dan program lanjut ke `menuUser()`.

---

### menuUser()
```cpp
void menuUser() {
    int p;
    do {
        ...
        switch (p) {
            case 1: tampilProfil(profilCari(userLogin)); catat("Lihat profil"); break;
            case 2: editProfil();   break;
            ...
            case 6: logout(); return;
        }
    } while (true);
}
```
Loop terus sampai user pilih `6` (logout). Setiap pilihan memanggil fungsi fitur yang sesuai. Kalau logout, `userLogin` dikosongkan dan fungsi ini `return`, program balik ke `menuLogin()`.

---

### main()
```cpp
int main() {
    hashInit();
    ...
    while (true) {
        menuLogin();
        if (userLogin.empty()) break;
        menuUser();
    }
    ...
}
```
| Baris | Penjelasan |
|---|---|
| `hashInit()` | Inisialisasi semua slot hash table ke `nullptr` sebelum program jalan |
| `while (true)` | Loop utama program, jalan terus sampai ada kondisi `break` |
| `menuLogin()` | Tampilkan menu login. Fungsi ini return kalau login berhasil atau user pilih keluar |
| `if (userLogin.empty()) break` | Kalau `userLogin` masih kosong setelah `menuLogin()` return, berarti user pilih keluar → hentikan program |
| `menuUser()` | Kalau sudah login, masuk ke menu user |

---

## Alur Program Lengkap

```
Program mulai → hashInit()
      ↓
  menuLogin()
  ├── Pilih 1 → registrasi() → hashInsert() + profilTambah()
  ├── Pilih 2 → login() → hashCari() → userLogin = username
  └── Pilih 0 → userLogin kosong → break → program selesai
      ↓
  menuUser()
  ├── Pilih 1 → tampilProfil(profilCari()) + catat()
  ├── Pilih 2 → editProfil() → profilCari() → ubah data + catat()
  ├── Pilih 3 → lihatHistori() → stackDisplay()
  ├── Pilih 4 → undo() → stackPop()
  ├── Pilih 5 → cariAkun() → hashCari() + profilCari() + catat()
  └── Pilih 6 → logout() → catat() → userLogin = "" → balik ke menuLogin()
```
