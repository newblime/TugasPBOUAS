#include "backend.h"

barang::barang(int idbarang, int hargabarang, string namabarang, int stokbarang)
{
    id = idbarang;
    harga = hargabarang;
    nama = namabarang;
    stok = stokbarang;
}

int barang::IdBarang()
{
    return id;
}

int barang::HargaBarang()
{
    return harga;
}

string barang::NamaBarang()
{
    return nama;
}

int barang::StokBarang()
{
    return stok;
}

void barang::TambahStok(int unit)
{
    stok += unit;
}

void barang::KurangiStok(int unit)
{
    stok -= unit;
}