#include <iostream>
#include <string>

using namespace std;


// 1. LINKED LIST: Menyimpan Profil Pengguna
struct UserProfile {
    string username;
    string fullName;
    string bio;
    UserProfile* next;
};

// 3. STACK: Menyimpan Histori Aktivitas
struct HistoryNode {
    string activityLog;
    HistoryNode* next;
};

struct ActivityStack {
    HistoryNode* top;
    
    // Constructor
    void init() {
        top = nullptr;
    }

    // Fungsi untuk Fitur 4: Simpan Histori Aktivitas
    void push(string log) {
        HistoryNode* newNode = new HistoryNode(); //Kan user membuat node baru, lalu disimpan di pointer newNode
        newNode->activityLog = log; // berarti sekarang kan newnode ada di salam historynode, lalu dia masuk ke activitylog dan menyimpan log yang dilakukan user
        newNode->next = top; // nah sekarang newnode masuk ke top, lalu dia menyalin alamat top
        top = newNode; // lalu newnode dipindahkan ke top
    }

    // Fungsi untuk Fitur 5: Undo Aktivitas Terakhir
    string pop() {
        if (top == nullptr) return "";
        HistoryNode* temp = top; // Alamat top yang sekarang disimpan sementara di temp, nah berarti temp sekarang ini ada top atau puncaknya
        string log = temp->activityLog; // lalu temp melakukan pengecekan ke log aktivitas teratas dan menyimpan di log, misalnya "Berhasil login ke sistem."
        top = top->next; // lalu top nya akan menunjuk ke next nya nih, berarti node dibawahnya, nah lalu dia dijadikan top
        delete temp; //karena temp sudah tidak dipakai maka bisa dihapus
        return log; //kembalikan nih sekarang log ada apa saja
    }

    void display() { //ini prosedur untuk menampilkan riwayat
        if (top == nullptr) {
            cout << "   (Belum ada riwayat aktivitas)\n";
            return;
        }
        HistoryNode* current = top; // Alamat top yang sekarang disimpan sementara di current, knp gak pake top? kan top untuk penanda tumpukan teratas, kalo digeser nanti bakal berantakan
        int i = 1;
        while (current != nullptr) {
            cout << "   " << i++ << ". " << current->activityLog << "\n"; //"cetak i++ (nomor urut) dan isi log aktivitasnya apa"
            current = current->next; //cur pindah ke node selanjutnya lalu dijadikan posisi terbaru
        }
    }
};

// 2. HASH TABLE: Menyimpan Akun Login (Sesuai Spesifikasi Soal 2)
struct UserAccount {
    string username; //kredensial akun pengguna.
    string password; //kredensial akun pengguna.
    UserProfile* profileRef; // Menghubungkan ke node profil di Linked List
    ActivityStack history;   // barangnya langsung dimasukkan ke dalam kotak akun. Karena setiap kotak user punya buku diari masing-masing, maka catatan aktivitasnya dijamin tidak akan tertukar.
    UserAccount* next;       // Untuk handling collision menggunakan Chaining
};

// Deklarasi struktur untuk Auth System
struct AuthSystem { //Manajer Pusat atau sistem utama yang mengelola seluruh proses autentikasi dan penyimpanan data
    const int TABLE_SIZE = 10; //digunakan agar nilai konstanta TABLE_SIZE dapat diakses langsung oleh kompiler sebagai aturan global untuk menentukan ukuran array Hash Table,
    UserAccount* hashTable[TABLE_SIZE];
    UserProfile* headProfile; // head yang memegang alamat dari node profil pertama di dalam memori, sehingga sistem dapat melakukan penelusuran (traversal) seluruh profil dengan mudah.

    // Fungsi Hash (Sum ASCII % TABLE_SIZE)
    int hashFunction(string key); 
    
    // Inisialisasi
    void init(); //Ini fungsi buat bersih-bersih lemari pas aplikasi baru dinyalain.
    
    // [FITUR 1]: Registrasi Akun
    bool registerAccount(string username, string password, string fullName, string bio);

    // [FITUR 2]: Login Akun
    UserAccount* loginAccount(string username, string password); //Inputnya username dan password. Outputnya adalah alamat memori si akun (UserAccount*) kalo pw dan email benar maka akan masuk ke alamat memori//

    // [FITUR 3]: Edit Profil
    void editProfile(UserAccount* account, string newName, string newBio);

    // [FITUR 5]: Undo Aktivitas Terakhir
    void undoActivity(UserAccount* account);

    // [FITUR 6]: Cari Akun Berdasarkan Username (Menggunakan Hashing)
    UserAccount* searchAccount(string username); //Inputnya username yang mau dicari, outputnya alamat memori akun yang ketemu

    // Fungsi pembantu untuk cetak info profil & riwayat Stack
    void displayUserInfo(UserAccount* account);
};

// =========================================================================
// IMPLEMENTASI FUNGSI AUTHSYSTEM
// =========================================================================

int AuthSystem::hashFunction(string key) {
    int sum = 0;
    for (char ch : key) { //perulangan untuk membongkar kata username (yang dioper ke dalam variabel key) huruf demi huruf ke ASCII
        sum += ch;
    }
    return sum % TABLE_SIZE;
}

void AuthSystem::init() { //:: itu ada di oop, jadi buat cakupan class nya, jadi disini init ditentukan digunakan khusus untuk AuthSystem
    for (int i = 0; i < TABLE_SIZE; i++) { //untuk mendatangi satu per satu laci Hash Table milik kita, lalu diisi dengan nullptr
        hashTable[i] = nullptr;
    }
    headProfile = nullptr;
}

bool AuthSystem::registerAccount(string username, string password, string fullName, string bio) {
    if (searchAccount(username) != nullptr) { //Jika username yang dimasukkan tidak null berarti akun ini ada
        cout << "\n[Gagal] Username '" << username << "' sudah terdaftar!\n";
        return false; //Register gagal
    }

    // Simpan ke Linked List Profil
    UserProfile* newProfile = new UserProfile(); //Membuat node profil baru di memori dan alamatnya disimpan di pointer newProfile
    newProfile->username = username; //useraname yang diinput user akan disimpan di pointer username
    newProfile->fullName = fullName;
    newProfile->bio = bio;
    newProfile->next = headProfile; // Pointer next dari node baru menyimpan alamat memori yang sedang ditunjuk oleh headProfile saat ini
    headProfile = newProfile; // Pointer headProfile menunjuk node newProfile sebagai kepala antrean baru

    // Simpan ke Hash Table
    int index = hashFunction(username); //deklarasi variabel index untuk menyimpan hasil hash dari username yang diinput user saat daftar akun
    UserAccount* newAccount = new UserAccount(); //membuat node useraccount baru dan alamatnya disimpan di pointer newAccount
    newAccount->username = username; //username nya akan disimpan di pointer username
    newAccount->password = password;
    newAccount->profileRef = newProfile; //Menghubungkan akun di Hash Table dengan profilnya yang ada di Linked List global
    newAccount->history.init(); //memberi perintah jika history akun yang baru didaftarkan akan ini akan di kosongkan riwayatnya supaya tidak ada pointer random
    newAccount->next = hashTable[index]; // Pointer next dari node baru menyimpan alamat memori yang sedang ditunjuk oleh hashTable[index] saat ini
    hashTable[index] = newAccount; //sekarang newaccount disimpan di hashTableindex tersbut

    // [FITUR 4]: Simpan histori aktivitas (Otomatis saat registrasi)
    newAccount->history.push("Melakukan registrasi akun."); //penulisan riwayat pertama kali setelah tadi di kosongkan
    cout << "\n[Sukses] Akun berhasil didaftarkan!\n";
    return true;
}

UserAccount* AuthSystem::loginAccount(string username, string password) {//menggunakan prosedur loginaccount khusus untuk AuthSystem
    UserAccount* account = searchAccount(username); // username yang diinput user akan disimpan di pointer account
    if (account != nullptr && account->password == password) { // jika username tidak null dan passwordnya harus sama
        
        // [FITUR 4]: Simpan histori aktivitas (Otomatis saat login)
        account->history.push("Berhasil login ke sistem."); //karena berhasil login maka akan disimpan di riwayat akun
        return account; //kembalikan data data akun ke menu utama
    }
    return nullptr;
}

void AuthSystem::editProfile(UserAccount* account, string newName, string newBio) { //menggunakan prosedur editprofile khusus untuk AuthSystem
    if (account == nullptr || account->profileRef == nullptr) return; //Jika akunnya KOSONG, ATAU alamat profilnya KOSONG, maka batalkan proses (langsung pulang
    
    account->profileRef->fullName = newName; // nama dan bio yang saat ini dignti dengan yang baru
    account->profileRef->bio = newBio;
    
    // [FITUR 4]: Simpan histori aktivitas (Otomatis saat edit profil)
    account->history.push("Mengubah informasi profil.");
    cout << "\n[Sukses] Profil berhasil diperbarui!\n";
}

void AuthSystem::undoActivity(UserAccount* account) { //mneggunkan prosedur undoactivity khusus untuk AuthSystem
    if (account == nullptr) return; // jika akunya kosong, maka batalkan proses
    string undoneAction = account->history.pop(); // hapus riwayat terakhir lalu kasih sampah itu ke underedAction
    if (undoneAction == "") { // sampahnya kosong gak?
        cout << "\n[Info] Tidak ada aktivitas yang bisa di-undo.\n";
    } else {
        cout << "\n[Undo Berhasil] Aktivitas dibatalkan: \"" << undoneAction << "\"\n"; 
    }
}

UserAccount* AuthSystem::searchAccount(string username) { //menggunakan prosedur searchaccount khusus untuk AuthSystem
    int index = hashFunction(username); // username yang sudah di hash akan disimpan di variabel index
    UserAccount* current = hashTable[index]; // sekarang lagi di index ke berapa lalu letkkan current disitu
    while (current != nullptr) { // ketika current tidak diposisi null
        if (current->username == username) { // jika username di current sama dengan username yang diinput
            return current; // kembalikan data akun nya ke layar utama
        }
        current = current->next; // lalu letakkan current di posisi selanjutnya jika username nya belum sama
    }
    return nullptr; // jika sudah sampai melalui semua akun, maka kembalikan null
}

void AuthSystem::displayUserInfo(UserAccount* account) { //menggunakan prosedur displayuserinfo khusus untuk AuthSystem
    if (account == nullptr) return; // jika akun tidak akhtif, maka batalkan proses
    cout << "\n=== PROFIL PENGGUNA ===\n";
    cout << "Username  : " << account->profileRef->username << "\n";
    cout << "Nama      : " << account->profileRef->fullName << "\n";
    cout << "Bio       : " << account->profileRef->bio << "\n";
    cout << "-----------------------\n";
    cout << "Histori Aktivitas (Terbaru di atas):\n";
    account->history.display();
    cout << "=======================\n";
}

// =========================================================================
// MAIN FUNCTION / INTERFACE PROGRAM
// =========================================================================

int main() {
    AuthSystem systemAuth; // membuat variabel dengan tipe data AuthSystem
    systemAuth.init(); // Bersihkan semua index di dalam hashTable agar siap digunakan (bebas nilai sampah)
    
    UserAccount* loggedInUser = nullptr; // menyiapkan 1 pointer untuk penanda sesi  dan diset kosong terlebih dahulu
    int choice; // Variabel untuk menampung nomor menu pilihan pengguna nanti

    while (true) {
        if (loggedInUser == nullptr) {// ini benar karena kan di atas kita null kan
            // MENU SEBELUM LOGIN
            cout << "\n=== SISTEM AUTENTIKASI UTAMA ===\n";
            cout << "1. Registrasi Akun (Fitur 1)\n";
            cout << "2. Login Akun (Fitur 2)\n";
            cout << "3. Cari Akun Berdasarkan Username (Fitur 6)\n";
            cout << "4. Keluar Aplikasi\n";
            cout << "Pilih menu: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                string uname, pwd, name, bio;
                cout << "\n--- REGISTRASI ---\n";
                cout << "Masukkan Username : "; cin >> uname;
                cout << "Masukkan Password : "; cin >> pwd;
                cin.ignore();
                cout << "Masukkan Nama Lengkap: "; getline(cin, name);
                cout << "Masukkan Bio Singkat : "; getline(cin, bio);
                systemAuth.registerAccount(uname, pwd, name, bio);

            } else if (choice == 2) {
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
            // MENU SETELAH BERHASIL LOGIN (DASHBOARD KONTROL)
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
                // PERBAIKAN: Masukkan aksi melihat profil ke dalam Stack sebelum ditampilkan
                loggedInUser->history.push("Melihat profil dan menampilkan histori.");
                systemAuth.displayUserInfo(loggedInUser);

            } else if (choice == 2) {
                string newName, newBio;
                cout << "\n--- EDIT PROFIL ---\n";
                cout << "Nama Baru: "; getline(cin, newName);
                cout << "Bio Baru : "; getline(cin, newBio);
                systemAuth.editProfile(loggedInUser, newName, newBio);

            } else if (choice == 3) {
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
        cout << "\n====================================\n";
    }
    return 0;
}
