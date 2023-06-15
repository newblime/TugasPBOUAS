#ifndef _FRONTEND_HEADER
#define _FRONTEND_HEADER

#include "vector"
#include "string"
#include "windows.h"

#include "backend.h"

using namespace std;


class frontend{
  public:
    frontend();

    void tampilkan_menu(pengguna &costumer);
    void tampilkan_struk(keranjang &struk);
    void tampilkan_total_struk(perhitungan::perhitungan_data hasil_perhitungan);
    void tampilkan_databarang(barang &brg);
    void tampilkan_stok(barang &brg);
    void tampilkan_pengguna(pengguna &pengguna);
    void tampilkan_member(member &pengguna);
    void tampilkan_list_barang(vector<barang*> &list);
    void tampilkan_kalimat(string kalimat);
    void tampilkan_error(string kalimat);
    void tampilkan_akhiran();
    
    void hapus_display();
    
    void pause_display();
    
    bool tanyakan_yatidak(string pertanyaan);
    string tanyakan_username(); 
    string tanyakan_password();
    int tanyakan_idbarang();
    int tanyakan_menu();
    int tanyakan_stok();
};

#endif