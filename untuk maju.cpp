#include <iostream>
#include <string>

using namespace std;

struct UserProfile {
    string username;
    string fullName;
    string bio;
    UserProfile* next;
};

struct HistoryNode {
    string activityLog;
    HistoryNode* next;
};

struct ActivityStack {
    HistoryNode* top;
    
    void init() {
        top = nullptr;
    }

    void push(string log) {
        //lihat_profil pt4 (Proses Push data riwayat ke dalam tumpukan Stack)
        HistoryNode* newNode = new HistoryNode(); 
        newNode->activityLog = log; 
        newNode->next = top; 
        top = newNode; 
    }

    string pop() {
        //undo pt3 (Algoritma LIFO: Mengambil data teratas tumpukan lalu menghapus nodenya dari RAM)
        if (top == nullptr) return "";
        HistoryNode* temp = top; 
        string log = temp->activityLog; 
        top = top->next; 
        delete temp; 
        return log; 
    }

    void display() { 
        //lihat_profil pt3 (Logika Traversal Stack: Menggunakan pointer 'current' agar pointer 'top' tidak rusak)
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

struct UserAccount {
    string username; 
    string password; 
    UserProfile* profileRef; 
    ActivityStack history;   
    UserAccount* next;       
};

struct AuthSystem { 
    const int TABLE_SIZE = 10; 
    UserAccount* hashTable[TABLE_SIZE];
    UserProfile* headProfile; 

    int hashFunction(string key); 
    void init(); 
    bool registerAccount(string username, string password, string fullName, string bio);
    UserAccount* loginAccount(string username, string password); 
    void editProfile(UserAccount* account, string newName, string newBio);
    void undoActivity(UserAccount* account);
    UserAccount* searchAccount(string username); 
    void displayUserInfo(UserAccount* account);
};

int AuthSystem::hashFunction(string key) {
    //cari_akun pt2 (Fungsi Hashing: Menjumlahkan ASCII nilai karakter lalu dimodulus TABLE_SIZE)
    int sum = 0;
    for (char ch : key) { 
        sum += ch;
    }
    return sum % TABLE_SIZE;
}

void AuthSystem::init() { 
    for (int i = 0; i < TABLE_SIZE; i++) { 
        hashTable[i] = nullptr;
    }
    headProfile = nullptr;
}

bool AuthSystem::registerAccount(string username, string password, string fullName, string bio) {
    //registrasi pt2 (Validasi apakah username sudah terdaftar menggunakan fungsi searchAccount)
    if (searchAccount(username) != nullptr) { 
        cout << "\n[Gagal] Username '" << username << "' sudah terdaftar!\n";
        return false; 
    }

    //registrasi pt3 (Alokasi memori dinamis untuk membuat node UserProfile baru di Linked List global)
    UserProfile* newProfile = new UserProfile(); 
    newProfile->username = username; 
    newProfile->fullName = fullName;
    newProfile->bio = bio;
    newProfile->next = headProfile; 
    headProfile = newProfile; 

    //registrasi pt4 (Alokasi memori node UserAccount baru, hashing index, dan Chaining jika terjadi Collision)
    int index = hashFunction(username); 
    UserAccount* newAccount = new UserAccount(); 
    newAccount->username = username; 
    newAccount->password = password;
    newAccount->profileRef = newProfile; 
    newAccount->history.init(); 
    newAccount->next = hashTable[index]; 
    hashTable[index] = newAccount; 

    newAccount->history.push("Melakukan registrasi akun."); 
    cout << "\n[Sukses] Akun berhasil didaftarkan!\n";
    return true;
}

UserAccount* AuthSystem::loginAccount(string username, string password) {
    //login pt2 (Fungsi login memanggil fungsi searchAccount untuk validasi keberadaan username)
    UserAccount* account = searchAccount(username); 
    
    //login pt3 (Validasi eksplisit: Memastikan akun tidak kosong dan password di memori cocok dengan input)
    if (account != nullptr && account->password == password) { 
        account->history.push("Berhasil login ke sistem."); 
        return account; 
    }
    return nullptr;
}

void AuthSystem::editProfile(UserAccount* account, string newName, string newBio) { 
    //edit_profil pt2 (Akses penunjukan pointer berantai untuk mengubah nilai data fisik profil di Linked List)
    if (account == nullptr || account->profileRef == nullptr) return; 
    
    account->profileRef->fullName = newName; 
    account->profileRef->bio = newBio; 
    
    account->history.push("Mengubah informasi profil.");
    cout << "\n[Sukses] Profil berhasil diperbarui!\n";
}

void AuthSystem::undoActivity(UserAccount* account) { 
    //undo pt2 (Memanggil fungsi pop() dari struct Stack untuk mengambil log aktivitas terakhir)
    if (account == nullptr) return; 
    string undoneAction = account->history.pop(); 
    if (undoneAction == "") { 
        cout << "\n[Info] Tidak ada aktivitas yang bisa di-undo.\n";
    } else {
        cout << "\n[Undo Berhasil] Aktivitas dibatalkan: \"" << undoneAction << "\"\n"; 
    }
}

UserAccount* AuthSystem::searchAccount(string username) { 
    //cari_akun pt1 (Mendapatkan indeks array lewat hashFunction, lalu melakukan penelusuran linier di laci hashTable)
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

void AuthSystem::displayUserInfo(UserAccount* account) { 
    //lihat_profil pt2 (Mencetak data profil lewat pointer berantai, lalu mendelegasikan cetak riwayat ke fungsi display milik Stack)
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

int main() {
    AuthSystem systemAuth; 
    systemAuth.init(); 
    
    UserAccount* loggedInUser = nullptr; 
    int choice; 

    while (true) {
        if (loggedInUser == nullptr) {
            cout << "\n=== SISTEM AUTENTIKASI UTAMA ===\n";
            cout << "1. Registrasi Akun (Fitur 1)\n";
            cout << "2. Login Akun (Fitur 2)\n";
            cout << "3. Cari Akun Berdasarkan Username (Fitur 6)\n";
            cout << "4. Keluar Aplikasi\n";
            cout << "Pilih menu: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                //registrasi pt1 (Menerima input data pendaftaran dari pengguna di main menu sebelum login)
                string uname, pwd, name, bio;
                cout << "\n--- REGISTRASI ---\n";
                cout << "Masukkan Username : "; cin >> uname;
                cout << "Masukkan Password : "; cin >> pwd;
                cin.ignore();
                cout << "Masukkan Nama Lengkap: "; getline(cin, name);
                cout << "Masukkan Bio Singkat : "; getline(cin, bio);
                systemAuth.registerAccount(uname, pwd, name, bio);

            } else if (choice == 2) {
                //login pt1 (Menerima input data login dan melemparkannya ke fungsi loginAccount)
                string uname, pwd;
                cout << "\n--- LOGIN ---\n";
                cout << "Username: "; cin >> uname;
                cout << "Password: "; cin >> pwd;
                loggedInUser = systemAuth.loginAccount(uname, pwd);
                if (loggedInUser != nullptr) {
                    cout << "\n[Sukses] Selamat datang kembali, " << loggedInUser->profileRef->fullName << "!\n";
                } else {
                    cout << "\n[Gagal] Username atau password salah!\n";
                }

            } else if (choice == 3) {
                string uname;
                cout << "\n--- CARI AKUN (HASHING) ---\n";
                cout << "Masukkan Username yang dicari: "; cin >> uname;
                UserAccount* found = systemAuth.searchAccount(uname);
                if (found != nullptr) {
                    cout << "\n[Ketemu] Akun '" << uname << "' terdaftar di sistem!\n";
                    cout << "Nama Lengkap: " << found->profileRef->fullName << "\n";
                    cout << "Bio         : " << found->profileRef->bio << "\n";
                } else {
                    cout << "\n[Info] Akun dengan username tersebut tidak ditemukan.\n";
                }

            } else if (choice == 4) {
                cout << "\nTerima kasih telah menggunakan sistem ini!\n";
                break;
            } else {
                cout << "\nPilihan tidak valid!\n";
            }
        } else {
            cout << "\n=== MENU DASHBOARD KONTROL (" << loggedInUser->username << ") ===\n";
            cout << "1. Lihat Profil & Tampilkan Histori (Fitur 4)\n";
            cout << "2. Edit Profil (Fitur 3)\n";
            cout << "3. Undo Aktivitas Terakhir (Fitur 5)\n";
            cout << "4. Cari Akun Lain Berdasarkan Username (Fitur 6)\n";
            cout << "5. Logout\n";
            cout << "Pilih menu: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                //lihat_profil pt1 (Menambahkan catatan aksi melihat profil ke Stack, lalu memanggil fungsi displayUserInfo)
                loggedInUser->history.push("Melihat profil dan menampilkan histori.");
                systemAuth.displayUserInfo(loggedInUser);

            } else if (choice == 2) {
                //edit_profil pt1 (Menerima input teks profil baru di main menu setelah login)
                string newName, newBio;
                cout << "\n--- EDIT PROFIL ---\n";
                cout << "Nama Baru: "; getline(cin, newName);
                cout << "Bio Baru : "; getline(cin, newBio);
                systemAuth.editProfile(loggedInUser, newName, newBio);

            } else if (choice == 3) {
                //undo pt1 (Menerima perintah aksi undo dari menu dashboard kontrol)
                systemAuth.undoActivity(loggedInUser);

            } else if (choice == 4) {
                string uname;
                cout << "\n--- CARI AKUN (HASHING) ---\n";
                cout << "Masukkan Username yang dicari: "; cin >> uname;
                UserAccount* found = systemAuth.searchAccount(uname);
                if (found != nullptr) {
                    cout << "\n[Ketemu] Akun terdaftar!\n";
                    cout << "Nama Lengkap: " << found->profileRef->fullName << "\n";
                } else {
                    cout << "\n[Info] Akun tidak ditemukan.\n";
                }

            } else if (choice == 5) {
                loggedInUser->history.push("Melakukan logout.");
                cout << "\n[Sukses] Anda telah logout.\n";
                loggedInUser = nullptr;
            } else {
                cout << "\nPilihan tidak valid!\n";
            }
        }
    }
    return 0;
}
