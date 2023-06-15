#include "frontend.h"
#include "iostream"

#include "stringformat.h"

using namespace std;


string to_lower(string _str){
  string _res;
  for(int i = 0; i < _str.size(); i++){
    char _c = _str[i];
    if(_c <= 'Z' && _c >= 'A')
      _c = 'a' + (_c - 'A');

    _res += _c;
  }

  return _res;
}

frontend::frontend(){
  HANDLE ohnd = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleMode(ohnd, ENABLE_PROCESSED_OUTPUT | 0x0004);
}

void frontend::tampilkan_menu(pengguna &costumer){
        // warna kuning
        string _color = "\x1B[48;5;221m";
        if(costumer.TipePengguna() == TIPE_PENGGUNA_MEMBER)
          // warna hijau
          _color = "\x1B[48;5;113m";

        string greeting; _formatstring(
          greeting, 
          "=== Selamat Datang %s%s%s di Self-Service Cashier ===",
          _color.c_str(),
          costumer.NamaPengguna().c_str(),
          "\x1B[0m"
        );

        cout << greeting << endl;
        cout << "Pilih menu: " << endl;
        cout << "1. Masuk Sebagai Member" << endl;
        cout << "2. List semua barang" << endl;
        cout << "3. Lihat Data Barang" << endl;
        cout << "4. Lihat Stok" << endl;
        cout << "5. Tambahkan ke Keranjang" << endl;
        cout << "6. Kurangi Barang di Keranjang" << endl;
        cout << "7. Hapus Item di Keranjang" << endl;
        cout << "8. Lihat Struk" << endl;
        cout << "9. Informasi Member" << endl;
        cout << "10. Selesai pembelian" << endl;
}
void frontend::tampilkan_databarang(barang &brg){
        // warna kuning
        cout << "\x1B[48;5;113m" << "ID BARANG " << brg.IdBarang() << "\x1B[0m" << endl;
        cout << "NAMA BARANG\t\t" << brg.NamaBarang() << endl;
        cout << "HARGA BARANG\t\t" << brg.HargaBarang() << endl;
        cout << "STOK BARANG\t\t" << brg.StokBarang() << endl;
}
void frontend::tampilkan_stok(barang &brg){
        cout << "Stoknya ada " << brg.StokBarang() << endl;
}

void frontend::tampilkan_struk(keranjang &struk){
  auto _list = struk.list_idbarang();
  for(int i = 0; i < _list.size(); i++){
    int idbarang = _list[i];

    auto barang = datadata_barang()->ambil_data_barang(idbarang);
    int total_item = struk.total_barang(idbarang);

    int total_harga = total_item * barang->HargaBarang();

        cout << "Nama Barang = " << barang->NamaBarang() << endl;
        cout << "Harga Barang = " << barang->HargaBarang() << endl;
        cout << "Total Barang = " << total_item << endl;     
        cout << "Total Harga = " << total_harga << endl;
        cout << endl;
  }
}

void frontend::tampilkan_total_struk(perhitungan::perhitungan_data _hasilPerhitungan){
  cout << "Total dari semua barang: " << _hasilPerhitungan.total_harga << endl;

  if(_hasilPerhitungan.apakah_member){
    if(_hasilPerhitungan.penggunaan_poin > 0){
      cout << endl;
      cout << "Poin telah digunakan, Poin dikurangi: " << _hasilPerhitungan.penggunaan_poin << endl;
      cout << "Harga potongan: " << abs(_hasilPerhitungan.total_harga - _hasilPerhitungan.total_harga_member) << endl;
      cout << "Harga akhir: " << _hasilPerhitungan.total_harga_member << endl;                   
    }

    cout << endl;
    cout << "Anda mendapatkan poin: " << _hasilPerhitungan.tambahan_member_poin << endl;
  }
}

void frontend::tampilkan_member(member &pengguna){
        cout << "Nama : " << pengguna.NamaPengguna() << endl;
        cout << "Poin : " << pengguna.MemberPoin() << endl;
}

void frontend::tampilkan_list_barang(vector<barang*> &list){
  cout << "LIST BARANG" << endl;
  for(int i = 0; i < list.size(); i++){
    barang *_brg = list[i];
    tampilkan_databarang(*_brg);
    cout << endl;
  }
}

void frontend::tampilkan_error(string error){
  // warna merah
  cout << "\x1B[38;5;0m";
  cout << "\x1B[48;5;196m";
  cout << error;
  // reset warna
  cout << "\x1B[0m";
  cout << endl;
}

void frontend::tampilkan_kalimat(string kalimat){
  cout << kalimat << endl;
}

void frontend::hapus_display(){
  // cursor ke home
  printf("\x1B[H");
  // clear semua line
  printf("\x1B[2J");
}

void frontend::pause_display(){
  cout << "Pencet enter untuk lanjut...";
  cin.ignore();
  string _dmp; getline(cin, _dmp);
}

string frontend::tanyakan_username(){
    string nama;

    cout << "Masukkan Nama : ";
    cin.ignore();
    getline(cin, nama);

    return nama;
}
string frontend::tanyakan_password(){
    string pw;

    cout << "Masukkan Password : ";
    getline(cin, pw);

    return pw;
}
int frontend::tanyakan_idbarang(){
    int idb;

    cout << "Masukkan ID Barang : ";
    cin >> idb;

    return idb;
}
int frontend::tanyakan_menu(){
    int menu;

    cout << "Pilih Menu : ";
    cin >> menu;

    return menu;
}

int frontend::tanyakan_stok(){
    int stuk;

    cout << "Berapa jumlah yang anda inginkan : ";
    cin >> stuk;

    return stuk;
}

void frontend::tampilkan_akhiran()
{
    cout << "Terima kasih telah berbelanja" << endl;
}

bool frontend::tanyakan_yatidak(string prompt){
  cout << prompt << " (Ya/Tidak) ";
  string _val;
  
  cin.ignore();
  getline(cin, _val);

  _val = to_lower(_val);
  if(_val == "ya")
    return true;
  else
    return false;
}