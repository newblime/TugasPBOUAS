#include "backend.h"
#include "iostream"


pengguna::pengguna(string namapengguna){
    tipe_pengguna = TIPE_PENGGUNA_PENGGUNA;
    nama = namapengguna;
}

string pengguna::NamaPengguna()
{
    return nama;
}

TIPE_PENGGUNA pengguna::TipePengguna(){
  return tipe_pengguna;
}

member::member(string namapengguna, int poin): pengguna(namapengguna){
    tipe_pengguna = TIPE_PENGGUNA_MEMBER;
    point = poin;
}

int member::MemberPoin()
{
    return point;
} 

void member::TambahPoin(int poin)
{
    point += poin;
}

void member::KurangiPoin(int poin){
  point -= poin;
  if(point < 0)
    point = 0;
}