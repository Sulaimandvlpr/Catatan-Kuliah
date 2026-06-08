Ini kode yang berbeda dari punya kamu ya — ini punya teman atau contoh lain? Karena strukturnya beda, pakai `struct AuthSystem` dan `UserAccount`.

Tetap saya jelaskan per baris.

---

## Bagian Atas

```cpp
#include <iostream>
#include <string>
using namespace std;
```

`#include` itu mengimpor library. `iostream` untuk input/output (`cout`, `cin`), `string` untuk tipe data string. `using namespace std` supaya tidak perlu nulis `std::cout`, cukup `cout` saja.

---

## Struct UserProfile — Linked List

```cpp
struct UserProfile {
    string username;
    string fullName;
    string bio;
    UserProfile* next;
};
```

Cetakan node untuk linked list profil. Tiap node menyimpan data diri satu user.

| Baris | Penjelasan |
|---|---|
| `string username` | Menyimpan username pemilik profil ini |
| `string fullName` | Menyimpan nama lengkap |
| `string bio` | Menyimpan bio/deskripsi user |
| `UserProfile* next` | Pointer ke node profil berikutnya. `nullptr` kalau ini node terakhir |

```
headProfile → [Andi|Andi Saputra|suka coding|→] → [Budi|Budi S|suka game|nullptr]
```

---

## Struct HistoryNode

```cpp
struct HistoryNode {
    string activityLog;
    HistoryNode* next;
};
```

Cetakan untuk **satu node** di dalam stack histori. Berbeda dengan kode kamu yang pakai array, kode ini stack-nya pakai linked list.

| Baris | Penjelasan |
|---|---|
| `string activityLog` | Teks aktivitas yang dicatat, misal `"Login"`, `"Edit profil"` |
| `HistoryNode* next` | Pointer ke node histori di bawahnya |

---

## Struct ActivityStack — Stack

```cpp
struct ActivityStack {
    HistoryNode* top;
```
`top` di sini bukan angka seperti di kode kamu, tapi **pointer** yang langsung menunjuk ke node paling atas stack.

```cpp
    void init() {
        top = nullptr;
    }
```
Set `top = nullptr` artinya stack kosong, belum ada histori apapun.

---

### push
```cpp
void push(string log) {
    HistoryNode* newNode = new HistoryNode();
    newNode->activityLog = log;
    newNode->next = top;
    top = newNode;
}
```

| Baris | Penjelasan |
|---|---|
| `new HistoryNode()` | Buat node baru di memori |
| `newNode->activityLog = log` | Isi node dengan teks aktivitas |
| `newNode->next = top` | Node baru menunjuk ke node yang tadinya paling atas |
| `top = newNode` | Top sekarang pindah ke node baru |

**Contoh:** Andi login, lalu lihat profil.

Push `"Login"`:
```
newNode = [Login | nullptr]
newNode->next = top (nullptr)
top = newNode

top → [Login | nullptr]
```

Push `"Lihat profil"`:
```
newNode = [Lihat profil | →]
newNode->next = top (node Login)
top = newNode

top → [Lihat profil | →] → [Login | nullptr]
```

Ini bedanya dengan kode kamu — node baru selalu masuk **di depan**, bukan di belakang.

---

### pop
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

| Baris | Penjelasan |
|---|---|
| `if (top == nullptr) return ""` | Kalau stack kosong, kembalikan string kosong |
| `HistoryNode* temp = top` | Simpan dulu pointer ke node teratas sebelum dihapus |
| `string log = temp->activityLog` | Ambil teks aktivitasnya |
| `top = top->next` | Top pindah ke node di bawahnya |
| `delete temp` | Hapus node teratas dari memori |
| `return log` | Kembalikan teks aktivitas yang dihapus |

**Contoh:** Stack isi 2, Andi pencet Undo.
```
Sebelum:
top → [Lihat profil] → [Login] → nullptr

temp = node "Lihat profil"
log  = "Lihat profil"
top  = top->next → top pindah ke node Login
delete temp → node "Lihat profil" dihapus dari memori

Sesudah:
top → [Login] → nullptr

Output: 'Lihat profil' berhasil di-undo
```

---

### display
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
```

| Baris | Penjelasan |
|---|---|
| `if (top == nullptr)` | Kalau kosong, tampilkan pesan dan langsung keluar |
| `HistoryNode* current = top` | Mulai dari node paling atas |
| `int i = 1` | Nomor urut untuk tampilan |
| `while (current != nullptr)` | Telusuri sampai habis |
| `i++` | Naikkan nomor urut setiap iterasi |
| `current = current->next` | Pindah ke node berikutnya |

**Contoh output:**
```
1. Lihat profil   ← node paling atas (terbaru)
2. Login          ← node di bawahnya (terlama)
```

---

## Struct UserAccount — Hash Table

```cpp
struct UserAccount {
    string username;
    string password;
    UserProfile* profileRef;
    ActivityStack history;
    UserAccount* next;
};
```

| Baris | Penjelasan |
|---|---|
| `string username, password` | Data login akun |
| `UserProfile* profileRef` | Pointer yang **menunjuk langsung ke node profil** di linked list. Jadi tidak perlu cari dari awal linked list, langsung lompat ke node profilnya |
| `ActivityStack history` | Stack histori milik akun ini |
| `UserAccount* next` | Pointer ke akun berikutnya, dipakai saat collision chaining |

Ini yang membedakan dari kode kamu — ada `profileRef` yang jadi jembatan langsung antara akun di hash table dan profil di linked list.

---

## Struct AuthSystem

```cpp
struct AuthSystem {
    static const int TABLE_SIZE = 10;
    UserAccount* hashTable[TABLE_SIZE];
    UserProfile* headProfile;
    ...
};
```

| Baris | Penjelasan |
|---|---|
| `static const int TABLE_SIZE = 10` | Konstanta yang hanya ada di dalam struct ini. `static` artinya nilainya sama untuk semua objek AuthSystem |
| `UserAccount* hashTable[TABLE_SIZE]` | Array 10 pointer untuk hash table akun |
| `UserProfile* headProfile` | Kepala linked list profil |

---

## hashFunction

```cpp
int AuthSystem::hashFunction(string key) {
    int sum = 0;
    for (char ch : key) {
        sum += ch;
    }
    return sum % TABLE_SIZE;
}
```

`AuthSystem::` artinya fungsi ini **milik struct AuthSystem**. Ini cara C++ menulis fungsi yang dideklarasikan di dalam struct tapi implementasinya di luar.

`for (char ch : key)` — ini cara ringkas loop tiap karakter. `ch` adalah satu huruf dari `key` di setiap iterasi.

Bedanya dengan kode kamu — di sini pakai nilai ASCII langsung (`sum += ch`), bukan dikurangi `'a'`. Jadi huruf besar dan kecil nilai ASCII-nya berbeda.

**Contoh:** `"Andi"`
```
A = 65
n = 110
d = 100
i = 105

sum = 65 + 110 + 100 + 105 = 380
index = 380 % 10 = 0
```

---

## init

```cpp
void AuthSystem::init() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = nullptr;
    }
    headProfile = nullptr;
}
```

Inisialisasi awal sistem — semua slot hash table dikosongkan, linked list profil juga dikosongkan. Dipanggil sekali di awal program.

---

## registerAccount

```cpp
bool AuthSystem::registerAccount(string username, string password, string fullName, string bio) {
    if (searchAccount(username) != nullptr) {
        cout << "\n[Gagal] Username '" << username << "' sudah terdaftar!\n";
        return false;
    }
```

| Baris | Penjelasan |
|---|---|
| `searchAccount(username) != nullptr` | Cari dulu apakah username sudah ada. Kalau `searchAccount` return bukan `nullptr`, berarti sudah ada |
| `return false` | Registrasi gagal, fungsi berhenti di sini |

Kalau username belum ada, lanjut buat node akun dan node profil baru — tapi potongan kode itu belum ada di bagian yang kamu kirim.

---

Mau lanjut jelaskan sisa `registerAccount`, `loginAccount`, dan fungsi-fungsi lainnya?
