# Soal Shift Sisop 2021 Modul 4

Kelompok D-04
- Thomas Felix Brilliant (05111940000062)
- Muhammad Rizky Widodo (05111940000216)
- Fiodhy Ardito Narawangsa (05111940000218)

## PENDAHULUAN ##

Sebelum mengerjakan soal, membuat terlebih dahulu FUSE <i>filesystem</i> dengan mengimplementasikan <i>system call</i> yang diperlukan untuk soal yang akan dikerjakan. Implementasi-implementasinya adalah sebagai berikut.
```C
static const struct fuse_operations _oper = {
    .getattr	= xmp_getattr,
    .access	= xmp_access,
    .readlink	= xmp_readlink,
    .readdir	= xmp_readdir,
    .mkdir	= xmp_mkdir,
    .symlink	= xmp_symlink,
    .unlink	= xmp_unlink,
    .rmdir	= xmp_rmdir,
    .rename	= xmp_rename,
    .link	= xmp_link,
    .chmod	= xmp_chmod,
    .chown	= xmp_chown,
    .truncate	= xmp_truncate,
    .utimens	= xmp_utimens,
    .open	= xmp_open,
    .create 	= xmp_create,
    .read	= xmp_read,
    .write	= xmp_write,
    .statfs	= xmp_statfs,
    .release	= xmp_release,
};
```

Seluruh <i>system call</i> tersebut pada dasarnya hanya memanggil <i>system call</i> Linux dengan mengganti <b><i>path</i></b> yang diinputkan <i>system call</i> tersebut menjadi <b><i>path</i></b> pada <i>mount</i>-<i>point</i>-nya, yaitu variabel `dirpath`.
  - `xmp_getattr()`: untuk mendapatkan <b><i>stat</i></b> dari <b><i>path</i></b> yang diinputkan.
  - `xmp_access()`: untuk mengakses <b><i>path</i></b> yang diinputkan.
  - `xmp_readlink()`: untuk membaca <i>symbolic link</i> dari <b><i>path</i></b>.
  - `xmp_mkdir()`: untuk membuat direktori pada <b><i>path</i></b>.
  - `xmp_symlink`: untuk membuat <i>symbolic link</i> pada <b><i>path</i></b>.
  - `xmp_unlink()`: untuk menghapus sebuah <i>file</i> dari <b><i>path</i></b>.
  - `xmp_rmdir()`: untuk menghapus direktori pada <b><i>path</i></b>.
  - `xmp_rename()`: untuk me-<i>rename</i> dari <b><i>path</i></b> awal menjadi <b><i>path</i></b> tujuan.
  - `xmp_link()`: untuk membuat <i>hard</i>-<i>link</i> pada <b><i>path</i></b>.
  - `xmp_chmod()`: untuk mengubah mode (hak akses) dari <b><i>path</i></b>.
  - `xmp_chown()`: untuk mengubah kepemilikan (user dan <i>group</i>) dari <b><i>path</i></b>.
  - `xmp_truncate()`: untuk melakukan <i>truncate</i> (membesarkan atau mengecilkan <i>size</i>) dari <b><i>path</i></b>.
  - `xmp_utimens()`: untuk mengubah status <i>time</i> dari <b><i>path</i></b>.
  - `xmp_open()`: untuk membuka <b><i>path</i></b>.
  - `xmp_create()`: untuk membuat <b><i>path</i></b> berdasarkan mode yang diinputkan.
  - `xmp_read()`: untuk membaca isi dari <b><i>path</i></b>.
  - `xmp_write()`: untuk menulis (<i>writing</i>) ke dalam <b><i>path</i></b>.
  - `xmp_statfs()`: untuk melakukan <b><i>stat</i></b> terhadap <i>file</i> yang diinputkan.
  - `xmp_release`: untuk <i>release</i> memori yang dialokasikan untuk <i>system call</i> `xmp_open()`.
 
```C
static const char *dirpath = "/home/thomasfelix/Downloads";
```

Nantinya, ketika <i>filesystem</i> di-<i>mount</i> akan memiliki <i>root</i> pada `dirpath` tersebut. Lalu, <i>filesystem</i> tersebut bisa diedit untuk melakukan operasi sesuai keinginan untuk menjawab soal Shift. Mengambil referensi dari [passthrough.c](https://github.com/libfuse/libfuse/blob/master/example/passthrough.c "passthrough.c").

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

## JAWABAN ##

Membuat enkripsi yaitu dengan cara tiap <i>system call</i> `xmp_readdir()` membaca sebuah direktori yang memiliki awalan `/AtoZ`, maka nama yang diinputkan pada <i>buffer</i> akan dienkripsi terlebih dahulu. Untuk mengatasi <i>entry</i> yang telah terenkripsi, seluruh <i>system call</i> akan mengecek terlebih dahulu apakah <i>path</i> yang diinputkan memiliki direktori dengan awalan `/AtoZ`. Jika ada maka akan melakukan dekripsi pada <i>path</i> tersebut.

Membuat beberapa fungsi yang akan digunakan untuk menyelesaikan soal ini.
  - `atbashCode()`: untuk melakukan enkripsi maupun dekripsi menggunakan metode <b>Atbash Cipher</b>.
  - `getDirAndFile()`: untuk mendapatkan <i><b>directory</b></i> dan <i><b>filename</b></i> dari <i><b>path</b></i> yang telah diinputkan.
  - `changePath()`: untuk mengganti <i><b>path</b></i> yang diinputkan menjadi <i>mount</i>-<i>mount</i> yang telah diset. Fungsi ini juga berfungsi untuk mengecek apakah perlu melakukan dekripsi (direktori berawalan `/AtoZ`) pada <i><b>path</b></i> yang diinputkan. Dan juga untuk melakukan enkripsi, melakukannya langsung pada <i>system call</i> `xmp_readdir()`.

`Fungsi atbashCode`
```C
void atbashCode(char *string) {
    int i = 0;

    while (string[i] != '\0') {
	if (string[i] >= 'A' && string[i] <= 'Z') {
	    string[i] = 'Z' + 'A' - string[i];
	}

	else if (string[i] >= 'a' && string[i] <= 'z') {
	    string[i] = 'z' + 'a' - string[i];
	}

	i++;
    }
}
```
Fungsi ini memiliki satu argumen, yaitu `string` sebagai alamat yang akan dienkripsi ataupun didekripsi. Untuk metode <b>Atbash Cipher</b> bisa dilihat pada referensi-referensi yang ada di internet, salah satunya [di sini](http://www.cprograms4future.com/p/program-213atbash-cipher_3.html, "di sini"). Logika yang digunakan untuk proses enkripsi dan dekripsi sama, jadi tidak perlu membuat fungsi lagi atau memisahkan proses enkripsi dan dekripsi.

`Fungsi getDirAndFile`
```C
void getDirAndFile(char *dir, char *file, char *path) {
    char buff[1000];
  	
    memset(dir, 0, 1000);
    memset(file, 0, 1000);
    strcpy(buff, path);
  	
    char *token = strtok(buff, "/");
	
    while(token != NULL) {
        sprintf(file, "%s", token);
    	token = strtok(NULL, "/");
	
	if (token != NULL) {
    	    sprintf(dir, "%s/%s", dir, file);
    	}
    }
}
```
Fungsi ini akan membagi `path` yang diinputkan menjadi `dir` dan `file` berdasarkan lokasi `/` terakhir. Pertama, deklarasi variabel `buff` untuk menyimpan `path`, lalu agar tidak mengubah isinya memakai `strtok()`. `dir` dan `file` di-`memset()` supaya isinya menjadi kosong. Kemudian, `path` akan di-`strcpy()` ke dalam `buff`. Buat `token` dengan `strtok()` pada `buff` dengan <i>delimiter</i> `"/"`, diiterasi untuk masing-masing `token`. Tiap iterasi akan meng-<i>copy</i> isi `token` ke dalam variabel `file` menggunakan `sprintf()`, lalu, `token` akan diiterasi ke `token` selanjutnya. Di akhir iterasi akan dicek apakah `token` tersebut belum `token` terakhir, jika belum, maka akan <i>update</i> variabel `dir` agar menjadi `dir/file` menggunakan `sprintf()`

`Fungsi changePath`
```C
void changePath(char *fpath, const char *path, int isWriteOperation, int isFileAsked) {
    char *ptr = strstr(path, "/AtoZ_");
    int state = 0;
  	
    if (ptr != NULL) {
        if (strstr(ptr + 1, "/") != NULL) {
	    state = 1;
	}
    }
    
    . . .
}
```
Fungsi ini didefinisikan dengan empat argumen. Argumen pertama, `fpath` untuk <i>buffer</i> hasil perubahan `path` menjadi <i>path</i> yang baru. Argumen kedua, `path` untuk diinput ke masing-masing <i>system call</i> dan mengubah <i>path</i>-nya sesuai <b><i>mount</i>-<i>point</i></b> atau metode enkripsi <b>Atbash Cipher</b>. Argumen ketiga, `isWriteOperation` untuk mendefinisikan <i>system call</i> yang memanggil fungsi apakah operasi <i>write</i> (karena ketika ingin membuat <i>file</i> pada direktori yang terenkripsi dengan `/AtoZ`, maka <i>path</i> untuk <i>filename</i> yang di-<i>write</i> tidak dienkripsi maupun dienkripsi). Argument keempat, `isFileAsked` untuk mendefinisikan apakah <i>system call</i> yang memanggil fungsi ingin melakukan dekripsi pada sebuah <i>file</i> atau direktori (pada direktori, dekripsi akan dilakukan langsung, sementara pada <i>file</i> harus mengecek ekstensinya terlebih dahulu.

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
