#include <iostream>
#include <string>
using namespace std; 

// ============================================================
// KONSTANTA & STRUCT
// ============================================================
const int TABLE_SIZE = 20, MAX_HISTORY = 10;

struct Stack {
    string data[MAX_HISTORY];
    int top;
};

struct AkunNode {
    string username, password;
    Stack histori;
    AkunNode* next;
};

struct ProfilNode {
    string username, nama, email, noHp;
    ProfilNode* next;
};

// ============================================================
// VARIABEL GLOBAL
// ============================================================
AkunNode*  hashTable[TABLE_SIZE];
ProfilNode* headProfil = nullptr;
string userLogin = "";

// ============================================================
// STACK
// ============================================================
void stackCreate(Stack& s)      { s.top = 0; }
bool stackIsEmpty(Stack& s)     { return s.top == 0; }
bool stackIsFull(Stack& s)      { return s.top == MAX_HISTORY; }

void stackPush(Stack& s, string aktivitas) {
    if (stackIsFull(s)) {
        for (int i = 0; i < MAX_HISTORY - 1; i++) s.data[i] = s.data[i + 1];
        s.data[MAX_HISTORY - 1] = aktivitas;
    } else {
        s.data[s.top++] = aktivitas;
    }
}

string stackPop(Stack& s) {
    if (stackIsEmpty(s)) return "";
    string hasil = s.data[--s.top];
    s.data[s.top] = "";
    return hasil;
}

void stackDisplay(Stack& s) {
    if (stackIsEmpty(s)) { cout << "  (belum ada aktivitas)\n"; return; }
    for (int i = s.top - 1; i >= 0; i--)
        cout << "  " << (s.top - i) << ". " << s.data[i] << "\n";
}

// ============================================================
// HASH TABLE
// ============================================================
void hashInit() { for (int i = 0; i < TABLE_SIZE; i++) hashTable[i] = nullptr; }

int hashFunction(string key) {
    int total = 0;
    for (int i = 0; i < (int)key.length(); i++) total += tolower(key[i]) - 'a';
    return total % TABLE_SIZE;
}

AkunNode* hashCari(string username) {
    AkunNode* cur = hashTable[hashFunction(username)];
    while (cur != nullptr) {
        if (cur->username == username) return cur;
        cur = cur->next;
    }
    return nullptr;
}

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

// ============================================================
// LINKED LIST
// ============================================================
void profilTambah(string username, string nama, string email, string noHp) {
    ProfilNode* baru = new ProfilNode();
    baru->username = username; baru->nama = nama;
    baru->email = email; baru->noHp = noHp; baru->next = nullptr;
    if (headProfil == nullptr) { headProfil = baru; return; }
    ProfilNode* cur = headProfil;
    while (cur->next != nullptr) cur = cur->next;
    cur->next = baru;
}

ProfilNode* profilCari(string username) {
    ProfilNode* cur = headProfil;
    while (cur != nullptr) {
        if (cur->username == username) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void tampilProfil(ProfilNode* p) {
    cout << "  Username : " << p->username << "\n"
         << "  Nama     : " << p->nama     << "\n"
         << "  Email    : " << p->email    << "\n"
         << "  No HP    : " << p->noHp     << "\n";
}

// ============================================================
// HELPER: catat aktivitas user yang sedang login
// ============================================================
void catat(string aktivitas) {
    AkunNode* akun = hashCari(userLogin);
    if (akun != nullptr) stackPush(akun->histori, aktivitas);
}

// ============================================================
// FITUR
// ============================================================
void registrasi() {
    cout << "\n===== REGISTRASI =====\n";
    string username, password, nama, email, noHp;
    cout << "Username : "; cin >> username;
    cout << "Password : "; cin >> password;
    cin.ignore();
    cout << "Nama     : "; getline(cin, nama);
    cout << "Email    : "; cin >> email;
    cout << "No HP    : "; cin >> noHp;
    if (!hashInsert(username, password)) { cout << "[!] Username sudah terdaftar!\n"; return; }
    profilTambah(username, nama, email, noHp);
    cout << "[v] Registrasi berhasil!\n";
}

bool login() {
    cout << "\n===== LOGIN =====\n";
    string username, password;
    cout << "Username : "; cin >> username;
    cout << "Password : "; cin >> password;
    AkunNode* akun = hashCari(username);
    if (akun == nullptr || akun->password != password) { cout << "[!] Username atau password salah!\n"; return false; }
    userLogin = username;
    catat("Login");
    cout << "[v] Selamat datang, " << username << "!\n";
    return true;
}

void logout() { catat("Logout"); cout << "[v] Sampai jumpa, " << userLogin << "!\n"; userLogin = ""; }

void editProfil() {
    cout << "\n===== EDIT PROFIL =====\n";
    ProfilNode* p = profilCari(userLogin);
    cout << "Data saat ini:\n"; tampilProfil(p);
    string nama, email, noHp;
    cin.ignore();
    cout << "\nNama baru  : "; getline(cin, nama);
    cout << "Email baru : "; cin >> email;
    cout << "No HP baru : "; cin >> noHp;
    p->nama = nama; p->email = email; p->noHp = noHp;
    catat("Edit profil");
    cout << "[v] Profil berhasil diupdate.\n";
}

void lihatHistori() {
    cout << "\n===== HISTORI AKTIVITAS =====\n";
    stackDisplay(hashCari(userLogin)->histori);
}

void undo() {
    cout << "\n===== UNDO =====\n";
    string terakhir = stackPop(hashCari(userLogin)->histori);
    if (terakhir.empty()) cout << "[!] Tidak ada aktivitas untuk di-undo.\n";
    else cout << "[v] '" << terakhir << "' berhasil di-undo.\n";
}

void cariAkun() {
    cout << "\n===== CARI AKUN =====\n";
    string username;
    cout << "Username : "; cin >> username;
    AkunNode* akun = hashCari(username);
    if (akun == nullptr) { cout << "[!] Akun tidak ditemukan.\n"; return; }
    cout << "[v] Akun ditemukan:\n";
    tampilProfil(profilCari(username));
    catat("Cari akun: " + username);
}

// ============================================================
// MENU & MAIN
// ============================================================
void menuLogin() {
    int p;
    do {
        cout << "\n=== MENU UTAMA ===\n1. Registrasi\n2. Login\n0. Keluar\nPilihan: "; cin >> p;
        if (p == 1) registrasi();
        else if (p == 2) { if (login()) return; }
    } while (p != 0);
}

void menuUser() {
    int p;
    do {
        cout << "\n=== MENU [" << userLogin << "] ===\n"
             << "1. Lihat Profil\n2. Edit Profil\n3. Histori Aktivitas\n"
             << "4. Undo\n5. Cari Akun\n6. Logout\nPilihan: "; cin >> p;
        switch (p) {
            case 1: tampilProfil(profilCari(userLogin)); catat("Lihat profil"); break;
            case 2: editProfil();   break;
            case 3: lihatHistori(); break;
            case 4: undo();         break;
            case 5: cariAkun();     break;
            case 6: logout(); return;
            default: cout << "[!] Pilihan tidak valid.\n";
        }
    } while (true);
}

int main() {
    hashInit();
    cout << "====================================\n"
         << " Proyek 3: Sistem Login & Aktivitas\n"
         << "====================================\n";
    while (true) {
        menuLogin();
        if (userLogin.empty()) break;
        menuUser();
    }
    cout << "Terima kasih!\n";
    return 0;
}
