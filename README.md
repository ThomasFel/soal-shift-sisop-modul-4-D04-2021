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

- Jika sebuah direktori dibuat dengan awalan `AtoZ_`, maka direktori tersebut akan menjadi direktori ter-<i>encode</i>.

### 1B ###

- Jika sebuah direktori di-<i>rename</i> dengan awalan `AtoZ_`, maka direktori tersebut akan menjadi direktori ter-<i>encode</i>.

### 1C ###

- Apabila direktori yang terenkripsi di-<i>rename</i> menjadi tidak ter-<i>encode</i>, maka isi direktori tersebut akan ter-<i>decode</i>.

### 1D ###

- Setiap pembuatan direktori ter-<i>encode</i> (<b><i>mkdir</i></b> atau <b><i>rename</i></b>) akan tercatat ke sebuah <i>log</i>. Format: `/home/[USER]/Downloads/[Nama Direktori]` → `/home/[USER]/Downloads/AtoZ_[Nama Direktori]`.

### 1E ###

- Metode <i>encode</i> pada suatu direktori juga berlaku terhadap direktori yang ada di dalamnya (rekursif).

### JAWABAN ###

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
Fungsi ini akan membagi `path` yang diinputkan menjadi `dir` dan `file` berdasarkan lokasi `/` terakhir. Pertama, deklarasi variabel `buff` untuk menyimpan `path`, lalu agar tidak mengubah isinya memakai `strtok`. `dir` dan `file` di-`memset` supaya isinya menjadi kosong. Kemudian, `path` akan di-`strcpy` ke dalam `buff`. Buat `token` dengan `strtok` pada `buff` dengan <i>delimiter</i> `"/"`, diiterasi untuk masing-masing `token`. Tiap iterasi akan meng-<i>copy</i> isi `token` ke dalam variabel `file` menggunakan `sprintf()`, lalu, `token` akan diiterasi ke `token` selanjutnya. Di akhir iterasi akan dicek apakah `token` tersebut belum `token` terakhir, jika belum, maka akan <i>update</i> variabel `dir` agar menjadi `dir/file` menggunakan `sprintf`

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
Fungsi ini didefinisikan dengan empat argumen. Argumen pertama, `*fpath` untuk <i>buffer</i> hasil perubahan `path` menjadi <i>path</i> yang baru. Argumen kedua, `path` untuk diinput ke masing-masing <i>system call</i> dan mengubah <i>path</i>-nya sesuai <b><i>mount</i>-<i>point</i></b> atau metode enkripsi <b>Atbash Cipher</b>. Argumen ketiga, `isWriteOperation` untuk mendefinisikan <i>system call</i> yang memanggil fungsi apakah operasi <i>write</i> (karena ketika ingin membuat <i>file</i> pada direktori yang terenkripsi dengan `/AtoZ`, maka <i>path</i> untuk <i>filename</i> yang di-<i>write</i> tidak dienkripsi maupun dienkripsi). Argument keempat, `isFileAsked` untuk mendefinisikan apakah <i>system call</i> yang memanggil fungsi ingin melakukan dekripsi pada sebuah <i>file</i> atau direktori (pada direktori, dekripsi akan dilakukan langsung, sementara pada <i>file</i> harus mengecek ekstensinya terlebih dahulu.

Variabel `*ptr` digunakan untuk menunjuk posisi `/AtoZ` pada <b><i>path</i></b> menggunakan fungsi `strstr()` (contoh: `/contoh/AtoZ_Vivy/wangy` -> `/AtoZ_Vivy/wangy`). Deklarasi variabel `state` untuk memastikan apakah <b><i>path</i></b> yang diinputkan berisi direktori di dalamnya atau hanya `/AtoZ` (contoh: `/contoh/AtoZ_Vivy` tidak akan didekripsi, sementara `/contoh/AtoZ_Vivy/wangy` akan didekripsi). Lalu cek apakah <i>string</i> setelah karakter pertama dari `ptr` memiliki karakter `/`, jika iya, maka `state` akan diset menjadi 1.

```C
char fixPath[1000];
      	
memset(fixPath, 0, sizeof(fixPath));
  	
if (ptr != NULL && state) {
    ptr = strstr(ptr + 1, "/");
    char pathAtoZDirBuff[1000];
    char pathEncryptedBuff[1000];
    	
    strcpy(pathEncryptedBuff, ptr);
    strncpy(pathAtoZDirBuff, path, ptr - path);
    
    . . .
}

. . .
```
Pendefinisian <i>buffer</i> `fixpath()` yang digunakan untuk menyimpan <i>proccessed path</i> dari tiap kondisi yang berbeda. `if()` akan berjalan ketika terdapat <i>substring</i> `/AtoZ_` pada <b><i>path</i></b> dengan kondisi `state` <b>TRUE</b>. `ptr` akan diset menjadi <i>path</i> setelah `/AtoZ_` (contoh: `/AtoZ_Vivy/wangy` akan menjadi `/wangy` pada `ptr`). Lalu didefinisikan juga `pathEncryptedBuff` untuk menyimpan <i>path</i> `*ptr` yang telah dicari menggunakan `strcpy()`, dan juga `pathAtoZDirBuff` untuk menyimpan <b><i>path</i></b> yang tidak didekripsi menggunakan `strncpy()` dari karakter pertama <b><i>path</i></b> sampai `ptr` - `path` (contoh: `/dir/AtoZ_Vivy/wangy` akan disimpan menjadi `/dir/AtoZ_Vivy` pada `pathAtoZDirBuff` dan `/wangy` pada `pathEncryptedBuff`).

```C
if (isWriteOperation) {
    char pathFileBuff[1000];
    char pathDirBuff[1000];
				
    getDirAndFile(pathDirBuff, pathFileBuff, pathEncryptedBuff);
    atbashCode(pathDirBuff);
    sprintf(fixPath, "%s%s/%s", pathAtoZDirBuff, pathDirBuff, pathFileBuff);
}
```
Dalam kondisi `isWriteOperation`, yang didekripsi hanya <i>path</i> direktorinya saja, sehingga `pathEncryptedBuff` perlu dipisah menggunakan fungsi `getDirAndFile()` dan disimpan ke `pathDirBuff` dan `pathFileBuff`. Lalu menjalankan fungsi `atbashCode()` pada `pathDirBuff` saja. Setelah itu, seluruh <i>path</i> akan dijadikan satu ke dalam <i>buffer</i> `fixPath` dengan urutan `pathAtoZDirBuff` (<i>path</i> tidak terenkripsi), `pathDirBuff` (<i>path</i> yang terenkripsi), dan terakhir `pathFileBuff` (nama <i>file</i>).

```C
. . .

else if (isFileAsked) {
    char pathFileBuff[1000];
    char pathDirBuff[1000];
    char pathExtBuff[1000];
    
    getDirAndFile(pathDirBuff, pathFileBuff, pathEncryptedBuff);
    
    char *whereIsExtension = strrchr(pathFileBuff, '.');
			
    if (whereIsExtension - pathFileBuff < 1) {
        atbashCode(pathDirBuff);
	atbashCode(pathFileBuff);
	sprintf(fixPath, "%s%s/%s", pathAtoZDirBuff, pathDirBuff, pathFileBuff);
    }
    
    . . .
```
Bagian ini berjalan untuk kondisi ketika bukan `isWriteOperation` dan yang diminta merupakan `isFileAsked`. Lalu deklarasi `pathFileBuff`, `pathDirBuff`, dan `pathExtBuff` untuk menyimpan <i>file</i>, directori, dan ekstensi dari `pathEncryptedBuff`. Pertama, <i>path</i> direktori dan <i>path file</i> dipisah terlebih dahulu menggunakan fungsi `getDirAndFile()`. Untuk mencari ekstensinya, dideklarasikan <i>pointer</i> `*whereIsExtension` untuk menunjuk karakter `'.'` terakhir pada `pathFileBuff` menggunakan fungsi `strrchr`. Lalu dicek apakah karakter `'.'` terakhir ini merupakan karakter pertama, jika iya, `pathFileBuff` berarti tidak memiliki ektensi seperti <i>file</i> dengan nama `.wangy`).

Jika tidak terdapat ekstensi, maka `pathDirBuff` dan `pathFileBuff` akan didekripsi menggunakan fungsi `atbashCode()` dan disatukan kembali pada variabel `fixPath` sesuai format. Jika ternyata ada, maka akan dideklarasi `pathJustFileBuff` untuk menyimpan nama <i>file</i>-nya saja menggunakan `snprintf` dan isi <i>value</i> `pathExtBuff` dengan ekstensi saja. `pathDirBuff` dan `pathJustFileBuff` akan didekripsi menggunakan fungsi `atbashCode()` dan disatukan kembali pada variabel `fixPath` sesuai format.

```C
. . .
    
    else {
        char pathJustFileBuff[1000];
				
        memset(pathJustFileBuff, 0, sizeof(pathJustFileBuff));
        strcpy(pathExtBuff, whereIsExtension);
        snprintf(pathJustFileBuff, whereIsExtension - pathFileBuff + 1, "%s", pathFileBuff);
        atbashCode(pathDirBuff);
        atbashCode(pathJustFileBuff);
        sprintf(fixPath, "%s%s/%s%s", pathAtoZDirBuff, pathDirBuff, pathJustFileBuff, pathExtBuff);
    }

else {
    atbashCode(pathEncryptedBuff);
    sprintf(fixPath, "%s%s", pathAtoZDirBuff, pathEncryptedBuff);
}

. . .

if (strcmp(path, "/") == 0) {
    sprintf(fpath, "%s", dirpath);
}
	
else {
    sprintf(fpath, "%s%s", dirpath, fixPath);
}
```
`else` pertama untuk kondisi bukan `isWriteOperation` dan yang diminta bukan merupakan `isFileAsked` atau direktori sehingga isi dalam <i>buffer</i> `pathEncryptedBuff` akan langsung didekripsi dan disimpan ke dalam `fixPath`.

`else` kedua untuk kondisi `state` sama dengan 0 atau tidak ada karakter `AtoZ_` sehingga isi dari `fixPath` akan sama dengan `path` karena tidak ada metode enkripsi dan dekripsi yang dijalankan.

Selanjutnya adalah mengubah `fixPath` menjadi `fpath` dengan mengisi <b><i>mount</i></b>-<b><i>point</i></b> yang telah dideklarasi pada variabel `dirpath`. Caranya yaitu jika <b><i>path</i></b> yang diinputkan merupakan <i>root</i> `"/"`, maka `dirpath` langsung di-<i>copy</i> ke dalam `fpath`, jika bukan, maka akan diformat agar `fixPath` menuju <b><i>mount</i></b>-<b><i>point</i></b> yang terletak pada `dirpath`.

`System call readdir`
```C
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
char fpath[1000];
	
changePath(fpath, path, 0, 0);

DIR *dp;
struct dirent *de;
(void) offset;
(void) fi;

dp = opendir(fpath);
	
if (dp == NULL) {
    const char *desc[] = {path};
    fileLog("INFO", "READDIR", 1, desc);
    
    return -errno;
}

while ((de = readdir(dp)) != NULL) {
    struct stat st;
		
    memset(&st, 0, sizeof(st));
			
    st.st_ino = de->d_ino;
    st.st_mode = de->d_type << 12;
			
    if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
        continue;
    }
			
    if (strstr(path, "/AtoZ_") != NULL) {
        char encodeThis[1000];
				
        strcpy(encodeThis, de->d_name);
				
	if (de->d_type == DT_REG) {
	    char *whereIsExtension = strrchr(encodeThis, '.');
					
	    if (whereIsExtension - encodeThis < 1) {
		atbashCode(encodeThis);
	    }
					
	    else {
	        char pathFileBuff[1000];
		char pathExtBuff[1000];
						
		strcpy(pathExtBuff, whereIsExtension);
		snprintf(pathFileBuff, whereIsExtension - encodeThis + 1, "%s", encodeThis);
		atbashCode(pathFileBuff);
		memset(encodeThis, 0, sizeof(encodeThis));
		sprintf(encodeThis, "%s%s", pathFileBuff, pathExtBuff);
	    }
	}   
						
	else if (de->d_type == DT_DIR) {
	    atbashCode(encodeThis);
	}

	if (filler(buf, encodeThis, &st, 0)) {
	    break;
	}
    }

. . .
```
<i>System call</i> `xmp_readdir()` ini digunakan untuk melakukan enkripsi pada <i>entry</i> yang berada pada direktori `/AtoZ_`. Pada fungsi di atas, jika pada <i>path</i> terdapat `/AtoZ_`, maka akan dilakukan enkripsi.

Pertama, mendeklarasikan variabel `encodeThis` dengan mengambil nama dari <i>entry</i>-nya (`de->d_name`). Jika <i>entry</i> tersebut merupakan `DT_REG` (<i>file</i> reguler), maka akan dilakukan enkripsi <i>file</i> (ekstensi tidak terenkripsi). Pertama, akan dicari lokasi ekstensi menggunakan <i>pointer</i> `*whereIsExtension` untuk menunjuk lokasinya dan fungsi `strrchr`. Dicek apakah <i>file</i> tersebut memiliki ekstensi atau tidak. Jika tidak, maka `encodeThis` akan langsung dienkripsi dengan fungsi `atbashCode()`. Jika terdapat ekstensi, maka antara nama <i>file</i> dan ekstensinya dipisah ke dalam `pathFileBuff` dan `pathExtBuff` menggunakan cara yang sama pada fungsi `changePath()`. Lalu, `pathFileBuff` akan dienkripsi menggunakan fungsi `atbashCode()`, nama <i>file</i> dan ekstensinya disatukan kembali dan disimpan dalam variabel `encodeThis`.

Jika ternyata tipe dari <i>entry</i> tersebut `DT_DIR`, maka `encodeThis` akan langsung dienkripsi. Setelah proses enkripsi selesai, dimasukkan ke dalam `buf` menggunakan fungsi `filler()`.

Jika <i>path</i> yang dimasukkan tidak memiliki `/AtoZ_` di dalamnya, maka nama <i>entry</i> (`de->d_name`) akan langsung dimasukkan ke dalam `buf` menggunakan fungsi `filler()`.

`Implementasi system call write operation (xmp_mkdir)`
```C
static int xmp_mkdir(const char *path, mode_t mode) {
    char fpath[1000];

    changePath(fpath, path, 1, 0);

    char *ptr = strrchr(path, '/');
    char *filePtr = strstr(ptr, "/AtoZ_");
  	
    if (filePtr != NULL) {
        if (filePtr - ptr == 0) {
      	    const char *desc[] = {path};
      	    fileLog("INFO", "MKDIR", 1, desc);
    	}
    }
    
    . . .
    
    int res;

    res = mkdir(fpath, mode);

    const char *desc[] = {path};
    fileLog("INFO", "MKDIR", 1, desc);
    
    if (strstr(path, "/AtoZ_") != NULL || strstr(path, "/RX_") != NULL) {
        fileLogv2("MKDIR", fpath, fpath);
    }

    if (res == -1) {
	return -errno;
    }

    return 0;
}
```
Pada <i>system call</i> di atas dilakukan `changePath()` terhadap `path` untuk mendapatkan `fpath`, argument `isWriteOperation` sama dengan 1 karena <b>mkdir</b> merupakan operasi <i>write</i> (membuat). Setiap pembuatan direktori `/AtoZ_` harus di-log. Untuk melakukan <i>logging</i>, kami menggunakan fungsi `fileLog` yang akan dijelaskan pada soal 4. Setelah itu <b>mkdir</b> akan dijalankan seperti biasa dan hasilnya akan di-<i>return</i>. <i>Logging</i> tersebut juga dilakukan pada <i>system call</i> `xmp_rename()` dengan metode yang sama.

`Implementasi system call read operation (xmp_getattr)`
```C
static int xmp_getattr(const char *path, struct stat *stbuf) {
    char fpath[1000];
  	
    changePath(fpath, path, 0, 1);
  	
    if (access(fpath, F_OK) == -1) {
    	memset(fpath, 0, sizeof(fpath));
    	changePath(fpath, path, 0, 0);
    }

    int res;

    res = lstat(fpath, stbuf);

    const char *desc[] = {path};
    fileLog("INFO", "GETATTR", 1, desc);

    if (res == -1) {
	return -errno;
    }

    return 0;
}
```
Pada <i>system call</i> di atas dilakukan `changePath()` terhadap `path` untuk mendapatkan `fpath`. Karena ketika <b><i>path</i></b> yang dimasukkan tidak tahu apakah <i>file</i>-nya merupakan <i>file</i> biasa atau malah direktori, maka ubah terlebih dahulu dengan asumsi bahwa <b><i>path</i></b> tersebut merupakan <i>file</i> sehingga argumen `isFileAsked` sama dengan 1. Lalu, akan dicoba di-<i>access</i>, jika tidak bisa, maka akan dilakukan `changePath` kembali dengan argumen `isFileAsked` sama dengan 0 (direktori). Proses <b>getattr</b> akan berlangsung pada `fpath` tersebut.

### OUTPUT ###

### KESULITAN ###

- Kesulitan sewaktu <i>debug</i>.
- Kesulitan sewaktu enkripsi dan dekripsi yang menyebabkan <i>file</i> atau direktori tidak terbaca.
- Masih ada <i>warning</i> untuk alokasi memori variabel pada program, namun progam masih bisa berjalan dengan baik. 

## SOAL 2 ##

Selain itu Sei mengusulkan untuk membuat metode enkripsi tambahan agar data pada komputer mereka semakin aman. Berikut rancangan metode enkripsi tambahan yang dirancang oleh Sei:

### 2A ###

- Jika sebuah direktori dibuat dengan awalan `RX_[Nama]`, maka direktori tersebut akan menjadi direktori ter-<i>encode</i> beserta isinya dengan perubahan nama isi sesuai kasus nomor 1 dengan algoritma tambahan <b>ROT13</b> (<b>Atbash</b> + <b>ROT13</b>).

### 2B ###

- Jika sebuah direktori di-<i>rename</i> dengan awalan `RX_[Nama]`, maka direktori tersebut akan menjadi direktori ter-<i>encode</i> beserta isinya dengan perubahan nama isi sesuai dengan kasus nomor 1 dengan algoritma tambahan <b>Vigenere Cipher</b> dengan <i>key</i> `SISOP` (<i>Case</i>-<i>sensitive</i>, <b>Atbash</b> + <b>Vigenere</b>).
  
### 2C ###

- Apabila direktori yang terencode di-<i>rename</i> (dihilangkan `RX_`-nya), maka folder menjadi tidak ter-<i>encode</i> dan isi direktori tersebut akan ter-<i>decode</i> berdasarkan nama aslinya.

### 2D ###

- Setiap pembuatan direktori terencode (<b><i>mkdir</i></b> atau <b><i>rename</i></b>) akan tercatat ke sebuah <i>log file</i> beserta <i>method</i>-nya (apakah itu <b><i>mkdir</i></b> atau <b><i>rename</i></b>).
  
### 2E ###

- Pada metode enkripsi ini, <i>file</i>-<i>file</i> pada direktori asli akan menjadi terpecah menjadi <i>file</i>-<i>file</i> kecil sebesar 1024 bytes, sementara jika diakses melalui <i>filesystem</i> rancangan Sin dan Sei akan menjadi normal. Sebagai contoh, `Suatu_File.txt` berukuran 3 kiloBytes pada direktori asli akan menjadi 3 <i>file</i> kecil yakni:
  ```
  Suatu_File.txt.0000
  Suatu_File.txt.0001
  Suatu_File.txt.0002
  ```
  
  Ketika diakses melalui <i>filesystem</i> hanya akan muncul `Suatu_File.txt`.

## SOAL 3 ##

Karena Sin masih super duper gabut akhirnya dia menambahkan sebuah fitur lagi pada <i>filesystem</i> mereka.

### 3A ###

- Jika sebuah direktori dibuat dengan awalan `A_is_a_`, maka direktori tersebut akan menjadi sebuah direktori spesial.

### 3B ###

- Jika sebuah direktori di-<i>rename</i> dengan memberi awalan `A_is_a_`, maka direktori tersebut akan menjadi sebuah direktori spesial.
  
### 3C ###

- Apabila direktori yang terenkripsi di-<i>rename</i> dengan menghapus `A_is_a_` pada bagian awal nama folder maka direktori tersebut menjadi direktori normal.
  
### 3D ###

- Direktori spesial adalah direktori yang mengembalikan enkripsi/<i>encoding</i> pada direktori `AtoZ_` maupun `RX_`, namun masing-masing aturan mereka tetap berjalan pada direktori di dalamnya (sifat rekursif `AtoZ_` dan `RX_` tetap berjalan pada sub-direktori).
  
### 3E ###

- Pada direktori spesial, semua nama <i>file</i> (tidak termasuk ekstensi) pada FUSE akan berubah menjadi <i>lowercase insensitive</i> dan diberi ekstensi baru berupa nilai desimal dari biner perbedaan namanya.
  
  Contohnya jika pada direktori asli nama <i>file</i>-nya adalah `FiLe_CoNtoH.txt` maka pada FUSE akan menjadi `file_contoh.txt.1321`. 1321 berasal dari biner 10100101001.

## SOAL 4 ##

Untuk memudahkan dalam memonitor kegiatan pada <i>filesystem</i> mereka, Sin dan Sei membuat sebuah <i>log system</i> dengan spesifikasi sebagai berikut:

### 4A ###

- <i>Log system</i> yang akan terbentuk bernama `SinSeiFS.log` pada direktori <i>home</i> pengguna (`/home/[user]/SinSeiFS.log`). <i>Log system</i> ini akan menyimpan daftar perintah <i>system call</i> yang telah dijalankan pada <i>filesystem</i>.
  
### 4B ###

- Karena Sin dan Sei suka kerapian, maka <i>log</i> yang dibuat akan dibagi menjadi dua level, yaitu INFO dan WARNING.

### 4C ###

- Untuk <i>log</i> level WARNING, digunakan untuk mencatat <i>syscall</i> <b><i>rmdir</i></b> dan <b><i>unlink</i></b>.
  
### 4D ###

- Sisanya, akan dicatat pada level INFO.

### 4E ###

- Format untuk <i>logging</i> yaitu:
  ```
  [Level]::[dd][mm][yyyy]-[HH]:[MM]:[SS]:[CMD]::[DESC :: DESC]
  ```
  
  <b>Level</b>: level <i>logging</i>, <b>dd</b>: 2 digit tanggal, <b>mm</b>: 2 digit bulan, <b>yyyy</b>: 4 digit tahun, <b>HH</b>: 2 digit jam (format 24 Jam), <b>MM</b>: 2 digit menit, <b>SS</b>: 2 digit detik, <b>CMD</b>: <i>system call</i> yang terpanggil, <b>DESC</b>: informasi dan parameter tambahan
  ```
  INFO::28052021-10:00:00:CREATE::/test.txt
  INFO::28052021-10:01:00:RENAME::/test.txt::/rename.txt
  ```
