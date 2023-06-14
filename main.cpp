#include <iostream>
#include "frontend.h"
#include "stringformat.h"

using namespace std;

penyimpanan_barang _barang("../data/barang");
penyimpanan_pengguna _pengguna("../data/pengguna");

keranjang _keranjangPengguna;
perhitungan _penghitung;

frontend penampil;

pengguna *_datapengguna;

bool _login = false;


int main(int, char**){
  _datapengguna = _pengguna.ambil_pengguna_default();

  bool _tetaploop = true;
  while(_tetaploop){
    penampil.hapus_display();
    penampil.tampilkan_menu(*_datapengguna);

    int input = penampil.tanyakan_menu();
    penampil.hapus_display();
    switch (input){
      case 1:{
        string nama = penampil.tanyakan_username();
        string password = penampil.tanyakan_password();

        member *_member = _pengguna.ambil_data_member(nama, password);

        // jika member ada
        if(_member != NULL){
          _datapengguna = (pengguna*)_member;
          _login = true;
        }
        // jika member tidak ada atau password salah
        else{
          penampil.tampilkan_error("Username tidak ditemukan, atau Password salah.");
        }
        
        break;
      }

      case 2:{
        auto _list = _barang.list_barang();
        penampil.tampilkan_list_barang(_list);

        break;
      }

      case 3:{
        int id = penampil.tanyakan_idbarang();
        barang *data = datadata_barang()->ambil_data_barang(id);
        if(data != NULL)
          penampil.tampilkan_databarang(*data);
        else
          penampil.tampilkan_error("Barang tidak ditemukan.");
        break;
      }

      case 4:{
        int id = penampil.tanyakan_idbarang();
        barang *data = datadata_barang()->ambil_data_barang(id);
        if(data != NULL)
          penampil.tampilkan_stok(*data);
        else
          penampil.tampilkan_error("Barang tidak ditemukan.");
        break;
      }

      case 5:{
        int id = penampil.tanyakan_idbarang();
        int jumlah = penampil.tanyakan_stok();
        _keranjangPengguna.tambahkan_barang(id, jumlah);

        string _hasilakhir; _formatstring(_hasilakhir, "Jumlah akhir barang: %d", _keranjangPengguna.total_barang(id));
        penampil.tampilkan_kalimat(_hasilakhir);
        break;
      }

      case 6:{
        int id = penampil.tanyakan_idbarang();
        int jumlah = penampil.tanyakan_stok();
        _keranjangPengguna.kurangi_barang(id, jumlah);

        string _hasilakhir; _formatstring(_hasilakhir, "Jumlah akhir barang: %d", _keranjangPengguna.total_barang(id));
        penampil.tampilkan_kalimat(_hasilakhir);
        break;
      }

      case 7:{
        int id = penampil.tanyakan_idbarang();
        _keranjangPengguna.hapus_item(id);

        barang *_databrg = _barang.ambil_data_barang(id);

        string _hasilakhir; _formatstring(_hasilakhir, "Item '%s' dihapus dari keranjang.", _databrg->NamaBarang().c_str());
        penampil.tampilkan_kalimat(_hasilakhir);
        break;
      }

      case 8:{
        auto _hasil = _penghitung.lakukan_perhitungan(_keranjangPengguna);
        penampil.tampilkan_struk(_keranjangPengguna);
        penampil.tampilkan_total_struk(_hasil);
        break;
      }

      case 9:{
        if(_login){
          penampil.tampilkan_member(*(member*)_datapengguna);
        }
        else{
          penampil.tampilkan_error("Pengguna bukan member");
        }

        break;
      }

      case 10:{
        auto _list_item = _keranjangPengguna.list_idbarang();
        for(int i = 0; i < _list_item.size(); i++){
          barang *_brg = _barang.ambil_data_barang(_list_item[i]);
          _brg->KurangiStok(_keranjangPengguna.total_barang(_list_item[i]));
        }

        bool _pakai_poin = false;
        if(_login){
          member *_mbr = (member*)_datapengguna;
          int poin = _mbr->MemberPoin();

          string _prompt; _formatstring(_prompt, "Poin anda %d (penggunaan poin maksimal: %d). Apakah ingin memakai poin?", poin, _penghitung.maksimal_penggunaan_member_poin());
          if(poin > 0 && penampil.tanyakan_yatidak(_prompt)){
            _pakai_poin = true;
          }
        }

        auto _hasil = _penghitung.lakukan_perhitungan(_keranjangPengguna, _datapengguna, _pakai_poin);
        if(_login){
          member *_mbr = (member*)_datapengguna;
          _mbr->KurangiPoin(_hasil.penggunaan_poin);
          _mbr->TambahPoin(_hasil.tambahan_member_poin);

          cout << "hasil akhir poin "<< _mbr->MemberPoin() << endl;
        }

        penampil.tampilkan_struk(_keranjangPengguna);
        penampil.tampilkan_total_struk(_hasil);
        penampil.tampilkan_akhiran();

        _tetaploop = false;
        break;
      }

      default:{
        penampil.tampilkan_error("Angka menu salah!");
        break;
      }
    }

    penampil.pause_display();
  }

  penampil.hapus_display();
}

penyimpanan_barang *datadata_barang(){
  return &_barang;
}

penyimpanan_pengguna *datadata_pengguna(){
  return &_pengguna;
}