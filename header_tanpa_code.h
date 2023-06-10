// agar header tidak ke include lagi
#ifndef _HEADER_TANPA_CODE
#define _HEADER_TANPA_CODE


// beritahu main jika ada kelas testclass
class testclass{

  public:

    // isi dari fungsi kelas ini sengaja di kosongkan,
    //  karena akan diisi di file kodingan header_tanpa_code.cpp
    void tampilkan_nomor(int n);
    void tampilkan_kalimat(const char *str);
};

#endif