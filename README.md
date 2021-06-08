# Soal Shift Sisop 2021 Modul 4

Kelompok D-04
- Thomas Felix Brilliant (05111940000062)
- Muhammad Rizky Widodo (05111940000216)
- Fiodhy Ardito Narawangsa (05111940000218)

## SOAL 1 ##

Di suatu jurusan, terdapat admin lab baru yang super duper gabut, ia bernama Sin. Sin baru menjadi admin di lab tersebut selama 1 bulan. Selama sebulan tersebut ia bertemu orang-orang hebat di lab tersebut, salah satunya yaitu Sei. Sei dan Sin akhirnya berteman baik. Karena belakangan ini sedang ramai tentang kasus keamanan data, mereka berniat membuat <i>filesystem</i> dengan metode <i>encode</i> yang mutakhir. Berikut adalah <i>filesystem</i> rancangan Sin dan Sei:

```
Semua file yang berada pada direktori harus ter-encode menggunakan Atbash Cipher (mirror).
Misalkan terdapat file bernama kucinglucu123.jpg pada direktori DATA_PENTING.

"AtoZ_folder/DATA_PENTING/kucinglucu123.jpg" → "AtoZ_folder/WZGZ_KVMGRMT/pfxrmtofxf123.jpg"

Filesystem berfungsi normal layaknya Linux pada umumnya, mount source (root) filesystem adalah direktori /home/[USER]/Downloads, dalam penamaan file '/' diabaikan, dan ekstensi tidak perlu di-encode.
```

### 1A ###

- <b>SOAL</b>

  Jika sebuah direktori dibuat dengan awalan `AtoZ_`, maka direktori tersebut akan menjadi direktori ter-<i>encode</i>.

### 1B ###

- <b>SOAL</b>

  Jika sebuah direktori di-<i>rename</i> dengan awalan `AtoZ_`, maka direktori tersebut akan menjadi direktori ter-<i>encode</i>.

### 1C ###

- <b>SOAL</b>

  Apabila direktori yang terenkripsi di-<i>rename</i> menjadi tidak ter-<i>encode</i>, maka isi direktori tersebut akan ter-<i>decode</i>.

### 1D ###

- <b>SOAL</b>

  Setiap pembuatan direktori ter-<i>encode</i> (<b><i>mkdir</i></b> atau <b><i>rename</i></b>) akan tercatat ke sebuah <i>log</i>. Format: `/home/[USER]/Downloads/[Nama Direktori]` → `/home/[USER]/Downloads/AtoZ_[Nama Direktori]`.

### 1E ###

- <b>SOAL</b>

  Metode <i>encode</i> pada suatu direktori juga berlaku terhadap direktori yang ada di dalamnya (rekursif).

## SOAL 2 ##

Selain itu Sei mengusulkan untuk membuat metode enkripsi tambahan agar data pada komputer mereka semakin aman. Berikut rancangan metode enkripsi tambahan yang dirancang oleh Sei:

### 2A ###

- <b>SOAL</b>

  Jika sebuah direktori dibuat dengan awalan `RX_[Nama]`, maka direktori tersebut akan menjadi direktori ter-<i>encode</i> beserta isinya dengan perubahan nama isi sesuai kasus nomor 1 dengan algoritma tambahan <b>ROT13</b> (<b>Atbash</b> + <b>ROT13</b>).

### 2B ###

- <b>SOAL</b>

  Jika sebuah direktori di-<i>rename</i> dengan awalan `RX_[Nama]`, maka direktori tersebut akan menjadi direktori ter-<i>encode</i> beserta isinya dengan perubahan nama isi sesuai dengan kasus nomor 1 dengan algoritma tambahan <b>Vigenere Cipher</b> dengan <i>key</i> `SISOP` (<i>Case</i>-<i>sensitive</i>, <b>Atbash</b> + <b>Vigenere</b>).
  
### 2C ###

- <b>SOAL</b>

  Apabila direktori yang terencode di-<i>rename</i> (dihilangkan `RX_`-nya), maka folder menjadi tidak ter-<i>encode</i> dan isi direktori tersebut akan ter-<i>decode</i> berdasarkan nama aslinya.

### 2D ###

- <b>SOAL</b>

  Setiap pembuatan direktori terencode (<b><i>mkdir</i></b> atau <b><i>rename</i></b>) akan tercatat ke sebuah <i>log file</i> beserta <i>method</i>-nya (apakah itu <b><i>mkdir</i></b> atau <b><i>rename</i></b>).
  
### 2E ###

- <b>SOAL</b>

  Pada metode enkripsi ini, <i>file</i>-<i>file</i> pada direktori asli akan menjadi terpecah menjadi <i>file</i>-<i>file</i> kecil sebesar 1024 bytes, sementara jika diakses melalui <i>filesystem</i> rancangan Sin dan Sei akan menjadi normal. Sebagai contoh, `Suatu_File.txt` berukuran 3 kiloBytes pada direktori asli akan menjadi 3 <i>file</i> kecil yakni:
  ```
  Suatu_File.txt.0000
  Suatu_File.txt.0001
  Suatu_File.txt.0002
  ```
  
  Ketika diakses melalui <i>filesystem</i> hanya akan muncul `Suatu_File.txt`.

## SOAL 3 ##

Karena Sin masih super duper gabut akhirnya dia menambahkan sebuah fitur lagi pada <i>filesystem</i> mereka.

### 3A ###

- <b>SOAL</b>

  Jika sebuah direktori dibuat dengan awalan `A_is_a_`, maka direktori tersebut akan menjadi sebuah direktori spesial.

### 3B ###

- <b>SOAL</b>

  Jika sebuah direktori di-<i>rename</i> dengan memberi awalan `A_is_a_`, maka direktori tersebut akan menjadi sebuah direktori spesial.
  
### 3C ###

- <b>SOAL</b>

  Apabila direktori yang terenkripsi di-<i>rename</i> dengan menghapus `A_is_a_` pada bagian awal nama folder maka direktori tersebut menjadi direktori normal.
  
### 3D ###

- <b>SOAL</b>

  Direktori spesial adalah direktori yang mengembalikan enkripsi/<i>encoding</i> pada direktori `AtoZ_` maupun `RX_`, namun masing-masing aturan mereka tetap berjalan pada direktori di dalamnya (sifat rekursif `AtoZ_` dan `RX_` tetap berjalan pada sub-direktori).
  
### 3E ###

- <b>SOAL</b>

  Pada direktori spesial, semua nama <i>file</i> (tidak termasuk ekstensi) pada FUSE akan berubah menjadi <i>lowercase insensitive</i> dan diberi ekstensi baru berupa nilai desimal dari biner perbedaan namanya.
  
  Contohnya jika pada direktori asli nama <i>file</i>-nya adalah `FiLe_CoNtoH.txt` maka pada FUSE akan menjadi `file_contoh.txt.1321`. 1321 berasal dari biner 10100101001.

## SOAL 4 ##

Untuk memudahkan dalam memonitor kegiatan pada <i>filesystem</i> mereka, Sin dan Sei membuat sebuah <i>log system</i> dengan spesifikasi sebagai berikut:

### 4A ###

- <b>SOAL</b>

  <i>Log system</i> yang akan terbentuk bernama `SinSeiFS.log` pada direktori <i>home</i> pengguna (`/home/[user]/SinSeiFS.log`). <i>Log system</i> ini akan menyimpan daftar perintah <i>system call</i> yang telah dijalankan pada <i>filesystem</i>.
  
### 4B ###

- <b>SOAL</b>

  Karena Sin dan Sei suka kerapian, maka <i>log</i> yang dibuat akan dibagi menjadi dua level, yaitu INFO dan WARNING.

### 4C ###

- <b>SOAL</b>

  Untuk <i>log</i> level WARNING, digunakan untuk mencatat <i>syscall</i> <b><i>rmdir</i></b> dan <b><i>unlink</i></b>.
  
### 4D ###

- <b>SOAL</b>

  Sisanya, akan dicatat pada level INFO.

### 4E ###

- <b>SOAL</b>

  Format untuk <i>logging</i> yaitu:
  ```
  [Level]::[dd][mm][yyyy]-[HH]:[MM]:[SS]:[CMD]::[DESC :: DESC]
  ```
  
  <b>Level</b>: level <i>logging</i>, <b>dd</b>: 2 digit tanggal, <b>mm</b>: 2 digit bulan, <b>yyyy</b>: 4 digit tahun, <b>HH</b>: 2 digit jam (format 24 Jam), <b>MM</b>: 2 digit menit, <b>SS</b>: 2 digit detik, <b>CMD</b>: <i>system call</i> yang terpanggil, <b>DESC</b>: informasi dan parameter tambahan
  ```
  INFO::28052021-10:00:00:CREATE::/test.txt
  INFO::28052021-10:01:00:RENAME::/test.txt::/rename.txt
  ```
