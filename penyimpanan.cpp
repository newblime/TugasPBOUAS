#include "fstream"
#include "iostream"
#include "functional"
#include "map"
#include "algorithm"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdarg.h>

#include "backend.h"
#include "stringformat.h"



enum PB_ENUM{
  PB_ID,
  PB_NAMA,
  PB_HARGA,
  PB_STOK
};

map<string, PB_ENUM> pb_list_key = {
  {"ID", PB_ID},
  {"NAMA", PB_NAMA},
  {"HARGA", PB_HARGA},
  {"STOK", PB_STOK}
};


enum PU_ENUM{
  PU_USERNAME,
  PU_PASSWORD,
  PU_POIN
};

map<string, PU_ENUM> pu_list_key = {
  {"USERNAME", PU_USERNAME},
  {"PASSWORD", PU_PASSWORD},
  {"POIN", PU_POIN}
};


pengguna _pengguna_default("Costumer Non-Member");



string _copystring(string str, int length, int offset = 0){
  string _newstr;
  for(int i = 0; i < length; i++)
    _newstr += str[offset+i];

  return _newstr;
}

void _iterasiFolder(string path, void *obj, void (*callback)(string, void*)){
  DIR *dir = opendir(path.c_str());
  dirent *ep;

  if(dir != NULL){
    cout << "dir is not null" << endl;
    while((ep = readdir(dir)) != NULL){
      string _newpath = path;
      _newpath += string("/") + ep->d_name;

      callback(_newpath, obj);
    }

    closedir(dir);
  }
}


/*    kelas penyimpanan_barang    */
penyimpanan_barang::penyimpanan_barang(string folderpath){
  _folderpath = folderpath;
  _databarang.clear();

  _iterasiFolder(folderpath, this, [](string path, void *obj) {
    penyimpanan_barang *kelas = (penyimpanan_barang*)obj;

    int idBarang = 0, hargaBarang = 0, stokBarang = 0;
    string namaBarang;

    ifstream _file(path);

    if(!_file.fail()){
      while(!_file.eof()){
        string _line; getline(_file, _line);

        int _pemisah = _line.find_first_of(' ');
        string _key = _copystring(_line, _pemisah);

        _pemisah += 1;
        string _value = _copystring(_line, _line.length() - _pemisah, _pemisah);

        auto _iterkey = pb_list_key.find(_key);
        if(_iterkey != pb_list_key.end()){
          PB_ENUM tipe = _iterkey->second;
          switch(tipe){
            break; case PB_ID:
              idBarang = atoi(_value.c_str());

            break; case PB_NAMA:
              namaBarang = _value;
            
            break; case PB_STOK:
              stokBarang = atoi(_value.c_str());

            break; case PB_HARGA:
              hargaBarang = atoi(_value.c_str());
          }
        }
      }

      kelas->_databarang[idBarang] = new barang(idBarang, hargaBarang, namaBarang, stokBarang);
    }
  });
}

penyimpanan_barang::~penyimpanan_barang(){
  for(auto pair : _databarang){
    barang *_brg = pair.second;
    
    string _filepath; _formatstring(_filepath, "%s/brg%d.txt", _folderpath.c_str(), _brg->IdBarang());

    ofstream ofs; ofs.open(_filepath);

    for(auto pair : pb_list_key){
      ofs << pair.first << " ";
      switch(pair.second){
        break; case PB_ID:
          ofs << _brg->IdBarang() << endl;

        break; case PB_NAMA:
          ofs << _brg->NamaBarang() << endl;

        break; case PB_HARGA:
          ofs << _brg->HargaBarang() << endl;

        break; case PB_STOK:
          ofs << _brg->StokBarang() << endl;
      }
    }

    ofs.close();
  }
}

barang *penyimpanan_barang::ambil_data_barang(int idbarang){
  auto _iterkey = _databarang.find(idbarang);
  if(_iterkey != _databarang.end())
    return _iterkey->second;

  return NULL;
}

vector<barang*> penyimpanan_barang::list_barang(){
  vector<barang*> _list; _list.reserve(_databarang.size());
  for(auto pair : _databarang)
    _list.insert(_list.end(), pair.second);

  sort(_list.begin(), _list.end(), [](barang* brg1, barang* brg2){
    return brg1->NamaBarang() < brg2->NamaBarang();
  });

  return _list;
}




/*    kelas penyimpanan_pengguna    */
penyimpanan_pengguna::penyimpanan_pengguna(string folderpath){
  _folderpath = folderpath;
  mapping_user.clear();

  _iterasiFolder(folderpath, this, [](string path, void *obj){
    penyimpanan_pengguna *kelas = (penyimpanan_pengguna*)obj;

    string username, password;
    int poin = 0;

    ifstream _file; _file.open(path);
    if(!_file.fail()){
      while(!_file.eof()){
        string _line; getline(_file, _line);

        int _pemisah = _line.find_first_of(' ');
        string _key = _copystring(_line, _pemisah);

        _pemisah += 1;
        string _value = _copystring(_line, _line.length() - _pemisah, _pemisah);

        auto _iterkey = pu_list_key.find(_key);
        if(_iterkey != pu_list_key.end()){
          PU_ENUM tipe = _iterkey->second;
          switch(tipe){
            break; case PU_USERNAME:
              username = _value;

            break; case PU_PASSWORD:
              password = _value;

            break; case PU_POIN:
              poin = atoi(_value.c_str());
              cout << "poin " << poin << endl;
          }
        }
      }

      penyimpanan_pengguna::user_data *_user = new penyimpanan_pengguna::user_data();
      _user->password = password;
      _user->data_pengguna = member(username, poin);

      kelas->mapping_user[username] = _user;
    }
  });
}

penyimpanan_pengguna::~penyimpanan_pengguna(){
  for(auto pair : mapping_user){

    string _filename; _formatstring(_filename, "%s/peng-%s.txt", _folderpath.c_str(), pair.first.c_str());
    ofstream ofs; ofs.open(_filename);

    switch(pair.second->data_pengguna.TipePengguna()){
      break; case TIPE_PENGGUNA_PENGGUNA:{
        pengguna *_p = &pair.second->data_pengguna;

        for(auto upair : pu_list_key){
          ofs << upair.first << " ";
          switch(upair.second){
            break; case PU_USERNAME:
              ofs << _p->NamaPengguna();

            break; case PU_PASSWORD:
              ofs << pair.second->password;
          }

          ofs << endl;
        }
      }

      break; case TIPE_PENGGUNA_MEMBER:{
        member *_m = (member*)&pair.second->data_pengguna;

        for(auto upair : pu_list_key){
          ofs << upair.first << " ";
          switch(upair.second){
            break; case PU_USERNAME:
              ofs << _m->NamaPengguna();

            break; case PU_PASSWORD:
              ofs << pair.second->password;

            break; case PU_POIN:
              ofs << _m->MemberPoin();
              cout << "member poin " << _m->MemberPoin() << endl;
          }

          ofs << endl;
        }
      }
    }
  }
}

member *penyimpanan_pengguna::ambil_data_member(string login, string password){
  auto _iterlogin = mapping_user.find(login);
  if(_iterlogin != mapping_user.end()){
    if(_iterlogin->second->password == password){
      return (member*)&_iterlogin->second->data_pengguna;
    }
  }

  return NULL;
}

pengguna *penyimpanan_pengguna::ambil_pengguna_default(){
  return &_pengguna_default;
}