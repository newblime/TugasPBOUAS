#include "backend.h"

int _maksimal_penggunaanPoin = 50;

int _div_pendapatanPoin = 15000;
int _mult_pemotonganPoin = 1000;

perhitungan::perhitungan_data perhitungan::lakukan_perhitungan(keranjang &struk, pengguna *_pengguna, bool pakaipoin)
{
  perhitungan_data _result;
  _result.total_harga = 0;
  _result.apakah_member = false;
  
  auto list = struk.list_idbarang();
  // barang
  for (int i = 0; i < list.size(); i++)
    _result.total_harga += datadata_barang()->ambil_data_barang(list[i])->HargaBarang() * struk.total_barang(list[i]);

  if(_pengguna && _pengguna->TipePengguna() == TIPE_PENGGUNA_MEMBER){
    _result.apakah_member = true;
    _result.penggunaan_poin = 0;
    _result.total_harga_member = _result.total_harga;
    _result.tambahan_member_poin = 0;

    member *_member = (member*)_pengguna;
    int poinMember = min(_member->MemberPoin(), _maksimal_penggunaanPoin);
    if(pakaipoin && poinMember > 0){
      _result.penggunaan_poin = poinMember;
      _result.total_harga_member -= poinMember * _mult_pemotonganPoin;
    }

    _result.tambahan_member_poin = _result.total_harga_member/_div_pendapatanPoin;
  }

  return _result;
}

int perhitungan::maksimal_penggunaan_member_poin(){
  return _maksimal_penggunaanPoin;
}