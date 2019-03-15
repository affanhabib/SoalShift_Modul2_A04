# Laporan Penjelasan

1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

	**Jawab** [source code](/soal1/soal1.c) 
	
	Program untuk membuat nama file menjadi “[namafile]_grey.png”
	```c
	struct dirent *de;
        char nama_awal[100], name[100];
    	char opo[100] = "/home/affan/modul2/gambar/";
    	char opo1[100];
    	char apa1[100];

    	DIR *dr = opendir("/home/affan/modul2/gambar"); 

        if (dr != NULL)	{
            while ((de = readdir(dr)) != NULL) {
                char *end = strrchr(de->d_name, '.');
                if(strcmp(end, ".png") == 0) {	
                    strcpy(opo1, opo);
                    strcpy(apa1, opo);
                     
                    strcpy(nama_awal, de->d_name);
                    de->d_name[strlen(de->d_name)-4]='\0';
                    strcpy(name, de->d_name);
                    
                    strcat(name,"_grey.png");
                    strcat(opo1, name);
                    strcat(apa1, nama_awal);
                     
                    rename(apa1, opo1);
                }
            }
        }
        
        else { 
            printf("Could not open current directory"); 
        } 

        closedir(dr);
	```
	
	Sedangkan untuk menjalankan secara otomatis menggunakan Daemon.

2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

	**Jawab** [source code](/soal2/hatiku/soal2.c) 
	
	Menghapus dengan *code* sebagai berikut
	
	```c
	if ((dir = opendir ("/home/affan/modul2/hatiku/")) != NULL) {
		while ((rent = readdir(dir))!=NULL){
			strcpy(file, rent->d_name);
			struct stat st={0};
			struct passwd *owner = getpwuid(st.st_uid);
			struct group *group = getgrgid(st.st_gid);
			if (strcmp(file,"elen.ku")==0 && strcmp(owner->pw_name,"www-data")==0 && strcmp(group->gr_name,"www-data")==0){
				printf("%s %s\n",owner->pw_name,group->gr_name);
				chmod(file,0777);
				remove(file);
			}
		}
    		closedir(dir);
	}
	```
	
	Karena menghapus tiap 3 detik, daemon di-*setting* `sleep(3);`.

3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
	i. mengekstrak file zip tersebut.
	ii. menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
	Catatan:
	* Gunakan fork dan exec.
	* Gunakan minimal 3 proses yang diakhiri dengan exec.
	* Gunakan pipe
	* Pastikan file daftar.txt dapat diakses dari text editor
	
	**Jawab** [source code](/soal3/soal3.c) 

4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

	Contoh:
	File makan_enak.txt terakhir dibuka pada detik ke-1
	Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

	Catatan: 
	- dilarang menggunakan crontab
	- Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

	**Jawab** [source code](/soal4/soal4.c) 
	
	Untuk memeriksa dan membuat file makan_sehat#.txt
	
	```c
	time_t now;
	time(&now);
	struct stat st = {0};
	double diff = difftime(now,st.st_atime);
	if(diff <= 30){
		FILE *remind;
		snprintf(newfile, 13,"%d.txt",count);

		strcat(dir,newfile);
		remind = fopen(dir,"w+");
		fclose(remind);
		count++;
	}
	```
	Untuk memeriksa setiap 5 detik, pada daemon ditulis `sleep(5);`.

5. Kerjakan poin a dan b di bawah:
	a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
	* Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
	* Per menit memasukkan log#.log ke dalam folder tersebut
	‘#’ : increment per menit. Mulai dari 1
	b. Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

	**Jawab** [source code](/soal5/soal5.c) 