// agar header tidak ke include lagi
#ifndef _HEADER_DENGAN_CODE
#define _HEADER_DENGAN_CODE

#include "stdio.h"

// koding seperti biasa seperti di main.cpp
// jika sudah diinclude kodingan ini (kasarannya) bakal
//  ditaruh di main.cpp tanpa mengubah file main.cpp

void test_function(){
  printf("test\n");
}

class test_kotak{
  private:
    int sisi, tinggi;

  public:
    test_kotak(int sisi, int tinggi){
      this->sisi = sisi;
      this->tinggi = tinggi;
    }

    int hasil_kali(){
      return sisi * tinggi;
    }
};

#endif