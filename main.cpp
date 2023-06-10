#include <iostream>
#include "header_dengan_code.h"
#include "header_tanpa_code.h"

using namespace std;


int main(int, char**){
  cout << "Hello, from TugasPBOUAS!" << endl;

  // manggil test_function dari header_dengan_code.h
  test_function();

  // bikin kelas test_kotak dari header_dengan_code.h
  test_kotak tk(2, 10);

  // panggil fungsi hasil_kali dari kelas test_kotak
  cout << "Hasil kali: " << tk.hasil_kali() << endl;

  // bikin kelas testclass dari header_tanpa_code.h
  testclass tclass;

  // tampilkan kata Hallo
  tclass.tampilkan_kalimat("Hallo!");
  // tampilkan nomor 100
  tclass.tampilkan_nomor(100);
}
