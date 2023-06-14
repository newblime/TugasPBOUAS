#include "backend.h"


void keranjang::tambahkan_barang(int idbarang, int stok){
  auto _iter = _list_barang.find(idbarang);
  if(_iter != _list_barang.end())
    _iter->second += stok;
  else
    _list_barang[idbarang] = stok;
}

void keranjang::kurangi_barang(int idbarang, int stok){
  auto _iter = _list_barang.find(idbarang);
  if(_iter != _list_barang.end()){
    _iter->second -= stok;
    if(_iter->second <= 0)
      _list_barang.erase(idbarang);
  }
}

void keranjang::hapus_item(int idbarang){
  auto _iter = _list_barang.find(idbarang);
  if(_iter != _list_barang.end())
    _list_barang.erase(idbarang);
}

vector<int> keranjang::list_idbarang(){
  vector<int> _res; _res.reserve(_list_barang.size());
  for(auto pair : _list_barang)
    _res.insert(_res.end(), pair.first);

  return _res;
}

int keranjang::total_barang(int id){
  auto _iter = _list_barang.find(id);
  if(_iter != _list_barang.end())
    return _iter->second;

  return 0;
}