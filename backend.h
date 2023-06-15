#ifndef _HEADER_BACKEND
#define _HEADER_BACKEND


#include "vector"
#include "string"
#include "map"

using namespace std;


enum TIPE_PENGGUNA{
  TIPE_PENGGUNA_PENGGUNA,
  TIPE_PENGGUNA_MEMBER
};

class pengguna{
  private:
    string nama;

  protected:
    TIPE_PENGGUNA tipe_pengguna;

  public:
    pengguna(){}
    pengguna(string namapengguna);
    string NamaPengguna();
    TIPE_PENGGUNA TipePengguna();
};

class member: public pengguna{
  private:
    int point;
  
  public:
    member(string namapengguna, int poin);
    int MemberPoin();

    void TambahPoin(int poin);
    void KurangiPoin(int poin);
};


class barang{
  private:
    int id;
    int harga;
    string nama;
    int stok;

  public:
    barang(int idbarang, int hargabarang, string namabarang, int stokbarang);
    
    int IdBarang();
    int HargaBarang();
    string NamaBarang();
    int StokBarang();
    void TambahStok(int unit);
    void KurangiStok(int unit);
};


class keranjang{
  // id, stok
  map<int, int> _list_barang;


  public:
    void tambahkan_barang(int idbarang, int stok);
    void kurangi_barang(int idbarang, int stok);
    void hapus_item(int idbarang);

    vector<int> list_idbarang();
    int total_barang(int id);
};


class perhitungan{
  public:
    struct perhitungan_data{
      public:
        int total_harga;

        bool apakah_member;
        int penggunaan_poin;
        int total_harga_member;

        int tambahan_member_poin;
    };


    perhitungan_data lakukan_perhitungan(keranjang &struk, pengguna *pengguna = NULL, bool pakaipoin = false);
    int maksimal_penggunaan_member_poin();
};


class penyimpanan_pengguna{
  private:
    struct user_data{
      public:
        user_data(){}

        string password;
        pengguna *data_pengguna;
    };

    string _folderpath;
    map<string, user_data*> mapping_user;
  

  public:
    penyimpanan_pengguna(string folderpath);
    ~penyimpanan_pengguna();
    
    member *ambil_data_member(string login, string password);
    pengguna *ambil_pengguna_default();
};

class penyimpanan_barang{
  private:
    string _folderpath;
    map<int, barang*> _databarang;

  public:
    penyimpanan_barang(string folderpath);
    ~penyimpanan_barang();

    barang *ambil_data_barang(int idbarang);

    // list berdasarkan nama barang
    vector<barang*> list_barang();
};



penyimpanan_barang *datadata_barang();
penyimpanan_pengguna *datadata_pengguna();

#endif