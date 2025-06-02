#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
using namespace std;

char menu;
int tambah = 0;
int jumlah = 0;
string carinama,namafile;

struct sepatu{
    string nama;
    string kode;
    int harga;
    int stok;
};
const int max_jumlah = 100;
sepatu daftarsepatu[max_jumlah];
sepatu daftarsort[max_jumlah];

bool adasort = false;
sepatu Namaasc[max_jumlah];
sepatu Namadesc[max_jumlah];
sepatu Hargaasc[max_jumlah];
sepatu Hargadesc[max_jumlah];
sepatu Stokasc[max_jumlah];
sepatu Stokdesc[max_jumlah];
int jumlahsort=0;

void salindata() {
    for (int i = 0; i < jumlah; i++) {
        daftarsort[i] = daftarsepatu[i];
    }
    jumlahsort = jumlah;
    adasort=true;
}

void filesort(sepatu data[], int n, string filename) {
    FILE *file = fopen(filename.c_str(), "w");
    if (file == NULL) {
        cout << "Gagal membuka file " << filename << " untuk ditulis.\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%s,%d,%d\n", data[i].nama.c_str(), data[i].kode.c_str(), data[i].harga, data[i].stok);
    }
    fclose(file);
}

void bacafile(sepatu data[], int &n, string filename) {
    FILE *file = fopen(filename.c_str(), "r");
    if (file == NULL) {
        cout << "\nFile " << filename << " TIDAK ditemukan!\n";
        n = 0;
        return;
    }
    char line[256];
    n = 0;
    while (fgets(line, sizeof(line), file) && n < max_jumlah) {
        char *nama = strtok(line, ",");
        char *kode = strtok(NULL,",");
        char *harga = strtok(NULL, ",");
        char *stok = strtok(NULL, "\n");

        if (nama && kode && harga && stok) {
            data[n].nama = nama;
            data[n].kode = kode;
            data[n].harga = atoi(harga);
            data[n].stok = atoi(stok);
            n++;
        } else {
            cout<<"Baris Tidak Valid atau Dilewati!\n";
        }
    }
    fclose(file);
}

void tulisdata() {
    FILE *file = fopen(namafile.c_str(), "w"); 
    if (file == NULL) {
        printf("Gagal membuka file untuk ditulis.\n");
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        fprintf(file, "%s,%s,%d,%d\n", daftarsepatu[i].nama.c_str(), daftarsepatu[i].kode.c_str(), daftarsepatu[i].harga, daftarsepatu[i].stok);
    }

    fclose(file);
    printf("Data berhasil ditulis ke file.\n");
}

void tambahdata() {
    FILE *file = fopen(namafile.c_str(), "a"); 
    if (file == NULL) {
        printf("Gagal membuka file untuk menambahkan data.\n");
        return;
    }

    for (int i = jumlah - tambah; i < jumlah; i++) {
        fprintf(file, "%s,%s,%d,%d\n", daftarsepatu[i].nama.c_str(), daftarsepatu[i].kode.c_str(), daftarsepatu[i].harga, daftarsepatu[i].stok);
    }
   
    fclose(file);
    printf("Data berhasil ditambahkan ke file.\n");

}


void bacadata() {
    FILE *file = fopen(namafile.c_str(), "r");
    if (file == NULL) {
        printf("File tidak ditemukan. Mulai dengan data kosong.\n");
        return;
    }

    char line[256];
    jumlah = 0;
    while (fgets(line, sizeof(line), file) && jumlah < max_jumlah) {
        char *nama = strtok(line, ",");
        char *kode = strtok(NULL, ",");
        char *harga = strtok(NULL, ",");
        char *stok = strtok(NULL, "\n");

        if (nama && harga && stok) {
            daftarsepatu[jumlah].nama = nama;
            daftarsepatu[jumlah].kode = kode;
            daftarsepatu[jumlah].harga = atoi(harga);
            daftarsepatu[jumlah].stok = atoi(stok);
            jumlah++;
        } else {
            cout<<"Baris Tidak Valid atau Dilewati!\n";
        }
    }

    fclose(file);
    printf("Data berhasil dibaca dari file.\n");
}

void input(){
    system ("cls");
    cout<<"|| INPUT SEPATU ||\n";
    do {
        cout<<"Masukkan jumlah barang : ";cin>>tambah;
        cout<<endl;
        
        if (tambah < 0 || jumlah + tambah > max_jumlah) {
            cout << "Jumlah tidak valid atau melebihi batas!\n";
        } else if (tambah = 0){
            cout<<"Kembali ke menu? (y/n) : ";cin>>menu;
        }
        
    } while(tambah < 0 || jumlah + tambah > max_jumlah);
    cin.ignore();
    
    for(int i = jumlah; i < jumlah + tambah; i++)
    {
        cout << "Produk ke-"<<i+1<<endl;
        cout << "Nama produk  : "; getline(cin, daftarsepatu[i].nama);
        cout << "Kode produk  : "; getline(cin, daftarsepatu[i].kode);
        cout << "Harga produk : "; cin >> daftarsepatu[i].harga;
        cout << "Stok produk  : "; cin >> daftarsepatu[i].stok; 
        cin.ignore();
        cout << endl;
    }
    jumlah += tambah;
    tambahdata();
    cout<<"Kembali ke menu? (y/n) : ";cin>>menu;
}

void lihat() {
    system("cls");
    cout<<"[LIHAT BARANG]\n";
    if (jumlah == 0)
    {
        cout << "\n[Belum ada produk yang ditambahkan]\n\n";
    }
    
    int pilihanLihat;
    cout << "Pilih data yang ingin dilihat:\n";
    cout << "1. Data asli (inputan awal)\n";
    cout << "2. Data hasil sort nama ascending\n";
    cout << "3. Data hasil sort nama descending\n";
    cout << "4. Data hasil sort harga ascending\n";
    cout << "5. Data hasil sort harga descending\n";
    cout << "6. Data hasil sort stok ascending\n";
    cout << "7. Data hasil sort stok descending\n";
    cout << "8. Keluar\n";
    cout << "Pilihan: ";cin >> pilihanLihat;

    sepatu *tampilArray = nullptr;
    int n = jumlah;
    switch (pilihanLihat) {
    case 1:
        tampilArray = daftarsepatu;
        n = jumlah;
        break;
    case 2:
        bacafile(daftarsort, n, "nama_asc.txt");
        tampilArray = daftarsort;
        break;
    case 3:
        bacafile(daftarsort, n, "nama_desc.txt");
        tampilArray = daftarsort;
        break;
    case 4:
        bacafile(daftarsort, n, "harga_asc.txt");
        tampilArray = daftarsort;
        break;
    case 5:
        bacafile(daftarsort, n, "harga_desc.txt");
        tampilArray = daftarsort;
        break;
    case 6:
        bacafile(daftarsort, n, "stok_asc.txt");
        tampilArray = daftarsort;
        break;
    case 7:
        bacafile(daftarsort, n, "stok_desc.txt");
        tampilArray = daftarsort;
        break;
    default:
        cout << "Pilihan tidak valid!\n";
        return;
    }

    cout << endl;
    cout << "+------------------------------------------------------------------+\n";
    cout << "| No | Nama             | Kode      | Harga         | Stok         |\n";
    cout << "+------------------------------------------------------------------+\n";
    for (int i = 0; i < n; i++){
        cout << "| " << setw(2) << i + 1 << " | "
            << setw(16) << left << tampilArray[i].nama << " | "
            << setw(9) << left << tampilArray[i].kode << " | "
            << setw(13) << left << tampilArray[i].harga << " | "
            << setw(11) << right << tampilArray[i].stok << " | \n";
    }
     cout << "+------------------------------------------------------------------+\n\n";
    
    cout << "Kembali ke menu? (y/n) : "; cin >> menu;
    return;
}

void cari(){
    system ("cls");
    cout<<"|| CARI SEPATU ||\n";
    bool found = false;
    cout << "Masukan nama produk yang ingin dicari : "; 
    cin.ignore();
    getline(cin,carinama);
    cout << "\nBarang yang ditemukan : \n";
    cout << "+------------------------------------------------------------------+\n";
    cout << "| No | Nama             | Kode      | Harga         | Stok         |\n";
    cout << "+------------------------------------------------------------------+\n";
    for (int i = 0; i < jumlah; i++) {
        if ( daftarsepatu[i].nama == carinama){
        cout << "| " << setw(2) << i + 1 << " | "
        << setw(16) << left << daftarsepatu[i].nama << " | "
        << setw(9) << left << daftarsepatu[i].kode << " | "
        << setw(13) << left << daftarsepatu[i].harga << " | "
        << setw(11) << right << daftarsepatu[i].stok << " | \n";
        found = true;
    }
} 
cout << "+------------------------------------------------------------------+\n";
if (!found) {
    cout << "\ndata tidak ditemukan!" << endl;
    }
    cout << "\nIngin kembali ke menu? y/n : ";
    cin >> menu;
}

void sort(){
    system ("cls");
    int sort1,sort2;
    int n = jumlah;
    cout<<"|| SORTING SEPATU ||\n\n";
    salindata();
    do{
        cout << "+------------------------------------------------------------------+\n";
        cout << "| No | Nama             | Kode      | Harga         | Stok         |\n";
        cout << "+------------------------------------------------------------------+\n";
        for (int i = 0; i < jumlah; i++){
            cout << "| " << setw(2) << i + 1 << " | "
                << setw(16) << left << daftarsepatu[i].nama << " | "
                << setw(9) << left << daftarsepatu[i].kode << " | "
                << setw(13) << left << daftarsepatu[i].harga << " | "
                << setw(11) << right << daftarsepatu[i].stok << " | \n";
            }
            cout << "+------------------------------------------------------------------+\n\n";
            cout<<"Urutkan Berdasarkan :\n 1. Nama Sepatu\n 2. Harga Sepatu\n 3. Stok Sepatu\n";
            cout<<"Input pilihan : ";cin>>sort1;
            cout<<"\nUrutkan Dari :\n 1. Kecil -> Besar\n 2. Besar -> Kecil\n";
            cout<<"Input pilihan : ";cin>>sort2;
            switch(sort1){
                case 1 :
                for(int i=0;i<n-1;i++){
                    for(int j=0;j<n-i-1;j++){
                        if((sort2 == 1 && daftarsort[j].nama>daftarsort[j+1].nama)||(sort2 == 2 && daftarsort[j].nama<daftarsort[j+1].nama)){
                            sepatu temp = daftarsort[j];
                            daftarsort[j] = daftarsort[j+1];
                            daftarsort[j+1] = temp;
                        } 
                    }
                }
                if(sort2 == 1){
                    memcpy(Namaasc, daftarsort, sizeof(sepatu) * jumlahsort);
                    filesort(Namaasc, jumlahsort, "nama_asc.txt");
                } else if (sort2 == 2){
                    memcpy(Namadesc, daftarsort, sizeof(sepatu) * jumlahsort);
                    filesort(Namadesc, jumlahsort, "nama_desc.txt");
                }
                cout<<"Hasil Sort :\n";
                break;
                case 2 :
                for(int i=0;i<n-1;i++){
                    for(int j=0;j<n-i-1;j++){
                        if((sort2 == 1 && daftarsort[j].harga>daftarsort[j+1].harga)||(sort2 == 2 && daftarsort[j].harga<daftarsort[j+1].harga)){
                            sepatu temp = daftarsort[j];
                            daftarsort[j] = daftarsort[j+1];
                            daftarsort[j+1] = temp;
                        } 
                    }
                }
                if(sort2 == 1){
                    memcpy(Hargaasc, daftarsort, sizeof(sepatu) * jumlahsort);
                    filesort(Hargaasc, jumlahsort, "harga_asc.txt");
                } else if (sort2 == 2){
                    memcpy(Hargadesc, daftarsort, sizeof(sepatu) * jumlahsort);
                    filesort(Hargadesc, jumlahsort, "harga_desc.txt");
                }
                cout<<"Hasil Sort :\n";
                break;
                case 3 :
                for(int i=0;i<n-1;i++){
                    for(int j=0;j<n-i-1;j++){
                        if((sort2 == 1 && daftarsort[j].stok>daftarsort[j+1].stok)||(sort2 == 2 && daftarsort[j].stok<daftarsort[j+1].stok)){
                            sepatu temp = daftarsort[j];
                            daftarsort[j] = daftarsort[j+1];
                            daftarsort[j+1] = temp;
                        } 
                    }
                }
                if(sort2 == 1){
                    memcpy(Stokasc, daftarsort, sizeof(sepatu) * jumlahsort);
                    filesort(Stokasc, jumlahsort, "stok_asc.txt");
                } else if (sort2 == 2){
                    memcpy(Stokdesc, daftarsort, sizeof(sepatu) * jumlahsort);
                    filesort(Stokdesc, jumlahsort, "stok_desc.txt");
                }
                cout<<"Hasil Sort :\n";
                break;
                default :
                cout<<"Pilihan Tidak Valid!\n";
                return;
            } 
            
            cout << "+------------------------------------------------------------------+\n";
            cout << "| No | Nama             | Kode      | Harga         | Stok         |\n";
            cout << "+------------------------------------------------------------------+\n";
            for (int i = 0; i < jumlah; i++){
               cout << "| " << setw(2) << i + 1 << " | "
                 << setw(16) << left << daftarsepatu[i].nama << " | "
                 << setw(9) << daftarsepatu[i].kode << " | "
                 << setw(13) << daftarsepatu[i].harga << " | "
                 << setw(11) << daftarsepatu[i].stok << " |\n";
            }
        cout << "+------------------------------------------------------------------+\n\n";
    }while (sort1 > 4 || sort1 < 1);    
    tulisdata();
    if(sort2 != 1 && sort2 != 2){
        cout<<"Pilihan Tidak Valid!";
            return;
        }
        cout << "Kembali ke menu? (y/n) : "; cin >> menu;
}

void update() {
    system("cls");
    cout << "|| UPDATE DATA SEPATU ||\n";

    if (jumlah == 0) {
        cout << "\nBelum ada data sepatu untuk diupdate.\n";
        cout << "\nKembali ke menu? (y/n): "; cin >> menu;
        return;
    }

    cout << "\nDaftar sepatu:\n";
    cout << "+------------------------------------------------------------------+\n";
    cout << "| No | Nama             | Kode      | Harga         | Stok         |\n";
    cout << "+------------------------------------------------------------------+\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "| " << setw(2) << i + 1 << " | "
             << setw(16) << left << daftarsepatu[i].nama << " | "
             << setw(9) << daftarsepatu[i].kode << " | "
             << setw(13) << left << daftarsepatu[i].harga << " | "
             << setw(11) << right << daftarsepatu[i].stok << "  |\n";
    }
    cout << "+------------------------------------------------------------------+\n";

    int index;
    cout << "\nMasukkan nomor sepatu yang ingin diupdate: ";
    cin >> index;

    if (index < 1 || index > jumlah) {
        cout << "Nomor tidak valid!\n";
        cout << "\nKembali ke menu? (y/n): "; cin >> menu;
        return;
    }

    int pilihan;
    cout << "\nPilih data yang ingin diupdate:\n";
    cout << "1. Nama\n2. Kode\n3. Harga\n4. Stok\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore();
    cout<<endl;

    switch (pilihan) {
        case 1:
            cout << "Masukkan nama baru: ";
            getline(cin, daftarsepatu[index - 1].nama);
            break;
        case 2:
            cout << "Masukkan kode baru: ";
            getline(cin, daftarsepatu[index - 1].kode);
            break;
        case 3:
            cout << "Masukkan harga baru: ";
            cin >> daftarsepatu[index - 1].harga;
            break;
        case 4:
            cout << "Masukkan stok baru: ";
            cin >> daftarsepatu[index - 1].stok;
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            return;
    }

    tulisdata(); 
    cout << "Data berhasil diperbarui!\n";
    cout << "\nKembali ke menu? (y/n): "; cin >> menu;
}

void hapus() {
    system("cls");
    cout << "|| HAPUS DATA SEPATU BERDASARKAN KODE ||\n";

    if (jumlah == 0) {
        cout << "Belum ada data yang bisa dihapus.\n";
        cout << "Kembali ke menu? (y/n) : "; cin >> menu;
        return;
    }

    cout << "+------------------------------------------------------------------+\n";
    cout << "| No | Nama             | Kode      | Harga         | Stok         |\n";
    cout << "+------------------------------------------------------------------+\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "| " << setw(2) << i + 1 << " | "
             << setw(16) << left << daftarsepatu[i].nama << " | "
             << setw(9) << left << daftarsepatu[i].kode << " | "
             << setw(13) << left << daftarsepatu[i].harga << " | "
             << setw(11) << right << daftarsepatu[i].stok << " | \n";
    }
    cout << "+------------------------------------------------------------------+\n";

    string kodehapus;
    cin.ignore();
    cout << "Masukkan kode produk yang ingin dihapus: ";
    getline(cin, kodehapus);

    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++) {
        if (daftarsepatu[i].kode == kodehapus) {
            for (int j = i; j < jumlah - 1; j++) {
                daftarsepatu[j] = daftarsepatu[j + 1];
            }
            jumlah--;
            ditemukan = true;
            tulisdata();
            cout << "Data dengan kode \"" << kodehapus << "\" berhasil dihapus.\n\n";
            break;
        }
    }

    if (!ditemukan) {
        cout << "Data dengan kode \"" << kodehapus << "\" tidak ditemukan.\n";
    }

    cout << "Kembali ke menu? (y/n) : ";
    cin >> menu;
}

void Menu(){
    int pilih;
    do{
        system ("cls");
        cout<<"-[ GUDANG SEPATU ]-\n\n";
        cout<<" Menu :\n";
        cout<<"  1. Input barang\n  2. Lihat Barang\n  3. Cari Barang\n  4. Sorting Barang\n  5. Update Barang\n  6. Hapus Barang\n  7. Keluar\n\n";
        cout<<" Pilih menu : ";cin>>pilih;
        switch(pilih){
            case 1 :
                input();
                break;
            case 2 :
                lihat();
                break;
            case 3 :
                cari();
                break;
            case 4 :
                sort();
                break;
            case 5 :
                update();
                break;
            case 6 :
                hapus();
                break;
            case 7 :
                exit(0);
        }
    } while ( menu == 'y' || menu == 'Y');
}

int main() {
    system("cls");
    cout<< "|| GUDANG SEPATU ||\n\n";
    cout<<"Tulis Nama File Utama (.txt) : ";getline(cin,namafile);
    bacadata();
    Menu();
    return 0;
}