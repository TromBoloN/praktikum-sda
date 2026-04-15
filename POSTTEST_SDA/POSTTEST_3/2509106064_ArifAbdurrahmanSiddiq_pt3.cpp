#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <string>
#include <limits>
using namespace std;

const int MAX = 100;

struct Kereta
{
    int nomor;
    string nama;
    string asal;
    string tujuan;
    string jam;
    int harga;
};

struct AntrianTiket
{
    string namaPenumpang;
    Kereta keretaDipilih;
};

struct RiwayatTransaksi
{
    string namaPenumpang;
    Kereta keretaDipilih;
};

void tampilData(Kereta *arr, int n)
{
    if (n == 0)
    {
        cout << "\nData masih kosong.\n";
        return;
    }

    cout << "\n====================================================================================================\n";
    cout << left << setw(10) << "Nomor"
         << setw(20) << "Nama Kereta"
         << setw(15) << "Asal"
         << setw(18) << "Tujuan"
         << setw(15) << "Jam"
         << setw(12) << "Harga" << endl;
    cout << "====================================================================================================\n";

    for (int i = 0; i < n; i++)
    {
        cout << left << setw(10) << (arr + i)->nomor
             << setw(20) << (arr + i)->nama
             << setw(15) << (arr + i)->asal
             << setw(18) << (arr + i)->tujuan
             << setw(15) << (arr + i)->jam
             << setw(12) << (arr + i)->harga << endl;
    }
}

void swapKereta(Kereta *a, Kereta *b)
{
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

Kereta *cariKeretaByNomor(Kereta *arr, int n, int nomor)
{
    for (int i = 0; i < n; i++)
    {
        if ((arr + i)->nomor == nomor)
        {
            return arr + i;
        }
    }
    return nullptr;
}

void tambahData(Kereta *&arr, int &n)
{
    if (n >= MAX)
    {
        cout << "\nData penuh!\n";
        return;
    }

    cout << "\n=== Tambah Data Kereta ===\n";
    cout << "Nomor Kereta   : ";
    cin >> arr[n].nomor;
    cin.ignore();

    cout << "Nama Kereta    : ";
    getline(cin, arr[n].nama);

    cout << "Asal           : ";
    getline(cin, arr[n].asal);

    cout << "Tujuan         : ";
    getline(cin, arr[n].tujuan);

    cout << "Jam Berangkat  : ";
    getline(cin, arr[n].jam);

    cout << "Harga Tiket    : ";
    cin >> arr[n].harga;

    n++;
    cout << "\nData berhasil ditambahkan!\n";
}

void linearSearchRute(Kereta *arr, int n, string asalCari, string tujuanCari)
{
    bool ketemu = false;

    cout << "\n=== Proses Linear Search ===\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Iterasi ke-" << i + 1 << " -> "
             << (arr + i)->asal << " - " << (arr + i)->tujuan << endl;

        if ((arr + i)->asal == asalCari && (arr + i)->tujuan == tujuanCari)
        {
            if (!ketemu)
            {
                cout << "\nData ditemukan:\n";
                cout << "====================================================================================================\n";
                cout << left << setw(10) << "Nomor"
                     << setw(20) << "Nama Kereta"
                     << setw(15) << "Asal"
                     << setw(15) << "Tujuan"
                     << setw(15) << "Jam"
                     << setw(12) << "Harga" << endl;
                cout << "====================================================================================================\n";
            }

            cout << left << setw(10) << (arr + i)->nomor
                 << setw(20) << (arr + i)->nama
                 << setw(15) << (arr + i)->asal
                 << setw(15) << (arr + i)->tujuan
                 << setw(15) << (arr + i)->jam
                 << setw(12) << (arr + i)->harga << endl;

            ketemu = true;
        }
    }

    if (!ketemu)
    {
        cout << "\nData tidak ditemukan.\n";
    }
}

void merge(Kereta arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    Kereta L[100], R[100];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i].nama <= R[j].nama)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortNama(Kereta arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSortNama(arr, l, m);
        mergeSortNama(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void selectionSortHarga(Kereta *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if ((arr + j)->harga < (arr + minIdx)->harga)
            {
                minIdx = j;
            }
        }
        if (minIdx != i)
        {
            swapKereta(arr + i, arr + minIdx);
        }
    }
}

void tampilAntrian(AntrianTiket *queue, int front, int rear)
{
    if (front == -1 || front > rear)
    {
        cout << "\nAntrian tiket masih kosong.\n";
        return;
    }

    cout << "\n===================================== ANTRIAN PEMBELIAN TIKET =====================================\n";
    cout << left << setw(6) << "No"
         << setw(25) << "Penumpang"
         << setw(20) << "Kereta"
         << setw(15) << "Asal"
         << setw(18) << "Tujuan"
         << setw(12) << "Jam" << endl;
    cout << "====================================================================================================\n";

    int nomorUrut = 1;
    // Iterasi antrian dari front ke rear memakai pointer aritmatika.
    for (AntrianTiket *ptr = queue + front; ptr <= queue + rear; ptr++)
    {
        cout << left << setw(6) << nomorUrut++
             << setw(25) << ptr->namaPenumpang
             << setw(20) << ptr->keretaDipilih.nama
             << setw(15) << ptr->keretaDipilih.asal
             << setw(18) << ptr->keretaDipilih.tujuan
             << setw(12) << ptr->keretaDipilih.jam << endl;
    }
}

void tampilRiwayat(RiwayatTransaksi *stack, int top)
{
    if (top == -1)
    {
        cout << "\nRiwayat transaksi masih kosong.\n";
        return;
    }

    cout << "\n====================================== RIWAYAT TRANSAKSI ==========================================\n";
    cout << left << setw(6) << "No"
         << setw(25) << "Penumpang"
         << setw(20) << "Kereta"
         << setw(15) << "Asal"
         << setw(18) << "Tujuan"
         << setw(12) << "Harga" << endl;
    cout << "====================================================================================================\n";

    int nomorUrut = 1;
    // Riwayat ditampilkan dari bawah stack sampai top.
    for (RiwayatTransaksi *ptr = stack; ptr <= stack + top; ptr++)
    {
        cout << left << setw(6) << nomorUrut++
             << setw(25) << ptr->namaPenumpang
             << setw(20) << ptr->keretaDipilih.nama
             << setw(15) << ptr->keretaDipilih.asal
             << setw(18) << ptr->keretaDipilih.tujuan
             << setw(12) << ptr->keretaDipilih.harga << endl;
    }
}

void enqueueTiket(AntrianTiket *queue, int &front, int &rear, Kereta *dataKereta, int n)
{
    // Enqueue menambahkan pemesan baru di posisi rear.
    if (rear == MAX - 1)
    {
        cout << "\nQueue overflow: antrian tiket penuh.\n";
        return;
    }

    string namaPenumpang;
    int nomorKereta;

    cout << "\n=== Tambah Antrian Pembelian Tiket ===\n";
    tampilData(dataKereta, n);

    cout << "\nNama penumpang        : ";
    getline(cin, namaPenumpang);
    cout << "Nomor kereta dipilih  : ";
    cin >> nomorKereta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Kereta *keretaDipilih = cariKeretaByNomor(dataKereta, n, nomorKereta);
    if (keretaDipilih == nullptr)
    {
        cout << "\nNomor kereta tidak ditemukan.\n";
        return;
    }

    if (front == -1)
    {
        front = 0;
    }

    rear++;
    (queue + rear)->namaPenumpang = namaPenumpang;
    (queue + rear)->keretaDipilih = *keretaDipilih;

    cout << "\nPenumpang berhasil masuk antrian.\n";
    cout << "Nama   : " << (queue + rear)->namaPenumpang << endl;
    cout << "Rute   : " << (queue + rear)->keretaDipilih.asal << " -> "
         << (queue + rear)->keretaDipilih.tujuan << endl;
}

void pushRiwayat(RiwayatTransaksi *stack, int &top, const AntrianTiket &antrian)
{
    // Setiap tiket yang diproses disalin ke stack riwayat.
    if (top == MAX - 1)
    {
        cout << "\nStack overflow: riwayat transaksi penuh.\n";
        return;
    }

    top++;
    (stack + top)->namaPenumpang = antrian.namaPenumpang;
    (stack + top)->keretaDipilih = antrian.keretaDipilih;
}

void dequeueTiket(AntrianTiket *queue, int &front, int &rear, RiwayatTransaksi *stack, int &top)
{
    // Dequeue selalu memproses penumpang paling depan.
    if (front == -1 || front > rear)
    {
        cout << "\nQueue underflow: antrian tiket kosong.\n";
        return;
    }

    AntrianTiket diproses = *queue;

    cout << "\n=== Proses Tiket ===\n";
    cout << "Nama penumpang : " << diproses.namaPenumpang << endl;
    cout << "Kereta         : " << diproses.keretaDipilih.nama << endl;
    cout << "Rute           : " << diproses.keretaDipilih.asal
         << " -> " << diproses.keretaDipilih.tujuan << endl;

    pushRiwayat(stack, top, diproses);

    // Geser elemen queue ke depan dengan dereferensi pointer.
    for (int i = 0; i < rear; i++)
    {
        *(queue + i) = *(queue + i + 1);
    }

    rear--;
    if (rear < 0)
    {
        front = -1;
        rear = -1;
    }
}

void popRiwayat(RiwayatTransaksi *stack, int &top)
{
    // Pop menghapus transaksi terakhir dari riwayat.
    if (top == -1)
    {
        cout << "\nStack underflow: riwayat transaksi kosong.\n";
        return;
    }

    cout << "\nTransaksi terakhir dibatalkan/dihapus:\n";
    cout << "Nama penumpang : " << (stack + top)->namaPenumpang << endl;
    cout << "Kereta         : " << (stack + top)->keretaDipilih.nama << endl;
    cout << "Rute           : " << (stack + top)->keretaDipilih.asal
         << " -> " << (stack + top)->keretaDipilih.tujuan << endl;
    top--;
}

void peekData(AntrianTiket *queue, int front, int rear, RiwayatTransaksi *stack, int top)
{
    // Peek hanya melihat data terdepan dan teratas tanpa menghapus.
    cout << "\n=== Peek Data ===\n";

    if (front == -1 || front > rear)
    {
        cout << "Antrian terdepan : antrian kosong.\n";
    }
    else
    {
        cout << "Antrian terdepan : " << (queue + front)->namaPenumpang
             << " | " << (queue + front)->keretaDipilih.asal
             << " -> " << (queue + front)->keretaDipilih.tujuan << endl;
    }

    if (top == -1)
    {
        cout << "Riwayat terakhir : riwayat kosong.\n";
    }
    else
    {
        cout << "Riwayat terakhir : " << (stack + top)->namaPenumpang
             << " | " << (stack + top)->keretaDipilih.asal
             << " -> " << (stack + top)->keretaDipilih.tujuan << endl;
    }
}

void enter()
{
    cout << "\nTekan Enter untuk Lanjut";
    cin.get();
}

int main()
{
    Kereta data[MAX] = {
        {101, "Argo Bromo", "Jakarta", "Surabaya", "08:00", 350000},
        {105, "Taksaka", "Yogyakarta", "Jakarta", "09:30", 275000},
        {102, "Lodaya", "Bandung", "Solo", "07:15", 220000},
        {106, "Matarmaja", "Malang", "Jakarta", "13:00", 180000},
        {108, "Sancaka", "Surabaya", "Yogyakarta", "06:45", 200000},
        {103, "Shinkansen Hikari", "Tokyo", "Osaka", "06:00", 850000},
        {104, "Shinkansen Nozomi", "Kyoto", "Nagoya", "07:20", 780000},
        {107, "KTX Express", "Seoul", "Busan", "09:10", 650000},
        {109, "Mugunghwa", "Daegu", "Seoul", "11:00", 420000},
        {115, "TGV Atlantique", "Paris", "Lyon", "08:30", 910000},
        {112, "Eurostar", "London", "Paris", "10:15", 1250000},
        {117, "ICE Sprinter", "Berlin", "Munich", "12:40", 980000},
        {110, "AVE Madrid", "Madrid", "Barcelona", "07:50", 870000},
        {111, "Frecciarossa", "Rome", "Milan", "09:45", 930000},
        {119, "Sapsan", "Moscow", "Saint Petersburg", "06:30", 890000},
        {113, "Amtrak Acela", "Washington", "New York", "08:20", 1100000},
        {116, "VIA Rail", "Toronto", "Montreal", "13:15", 760000},
        {118, "The Ghan", "Adelaide", "Alice Springs", "15:00", 1400000},
        {114, "Blue Train", "Pretoria", "Cape Town", "16:45", 1700000},
        {120, "Eastern Express", "Ankara", "Kars", "18:10", 690000}};

    Kereta *p = data;
    AntrianTiket antrian[MAX];
    RiwayatTransaksi riwayat[MAX];
    int n = 20;
    int pilih;
    int front = -1, rear = -1;
    int top = -1;

    do
    {
        system("cls");
        cout << "\n========== SISTEM INFORMASI KERETA API ==========\n";
        cout << "1. Tampilkan semua jadwal kereta\n";
        cout << "2. Tambah data kereta baru\n";
        cout << "3. Cari berdasarkan rute (Linear Search)\n";
        cout << "4. Cari berdasarkan nomor kereta (Jump Search)\n";
        cout << "5. Urutkan berdasarkan nama kereta (Merge Sort)\n";
        cout << "6. Urutkan berdasarkan harga tiket (Selection Sort)\n";
        cout << "7. Tambah ke antrian beli tiket (Enqueue)\n";
        cout << "8. Proses tiket terdepan (Dequeue)\n";
        cout << "9. Tampilkan peek antrian & riwayat\n";
        cout << "10. Tampilkan semua antrian\n";
        cout << "11. Tampilkan semua riwayat\n";
        cout << "12. Hapus transaksi terakhir (Pop)\n";
        cout << "13. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilih;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilih)
        {
        case 1:
            tampilData(p, n);
            enter();
            break;

        case 2:
            tambahData(p, n);
            enter();
            break;

        case 3:
        {
            string asalCari, tujuanCari;
            cout << "\nMasukkan asal   : ";
            getline(cin, asalCari);
            cout << "Masukkan tujuan : ";
            getline(cin, tujuanCari);

            linearSearchRute(p, n, asalCari, tujuanCari);
            enter();
            break;
        }

        case 4:
        {
            int target;
            cout << "\nMasukkan nomor kereta yang dicari: ";
            cin >> target;

            for (int i = 0; i < n - 1; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if ((p + i)->nomor > (p + j)->nomor)
                    {
                        swapKereta(p + i, p + j);
                    }
                }
            }

            // Jump Search
            int step = sqrt(n);
            int prev = 0;
            int ketemu = -1;

            cout << "\n==== Proses Jump Search ====\n";

            while (p[min(step, n) - 1].nomor < target)
            {
                cout << "Blok dicek dari index " << prev
                     << " sampai " << min(step, n) - 1
                     << " | nilai akhir blok = " << p[min(step, n) - 1].nomor << endl;

                prev = step;
                step += sqrt(n);

                if (prev >= n)
                {
                    break;
                }
            }

            if (prev < n)
            {
                cout << "Target kemungkinan ada di blok index "
                     << prev << " sampai " << min(step, n) - 1 << endl;

                while (prev < min(step, n))
                {
                    cout << "Cek index " << prev
                         << " -> nomor = " << p[prev].nomor << endl;

                    if (p[prev].nomor == target)
                    {
                        ketemu = prev;
                        break;
                    }
                    prev++;
                }
            }

            if (ketemu != -1)
            {
                cout << "\nData ditemukan:\n";
                cout << "Nomor   : " << p[ketemu].nomor << endl;
                cout << "Nama    : " << p[ketemu].nama << endl;
                cout << "Asal    : " << p[ketemu].asal << endl;
                cout << "Tujuan  : " << p[ketemu].tujuan << endl;
                cout << "Jam     : " << p[ketemu].jam << endl;
                cout << "Harga   : " << p[ketemu].harga << endl;
            }
            else
            {
                cout << "\nData tidak ditemukan.\n";
            }
            enter();
            break;
        }

        case 5:
            mergeSortNama(data, 0, n - 1);
            cout << "\nData berhasil diurutkan berdasarkan nama kereta.\n";
            tampilData(p, n);
            enter();
            break;

        case 6:
            selectionSortHarga(p, n);
            cout << "\nData berhasil diurutkan berdasarkan harga tiket termurah.\n";
            tampilData(p, n);
            enter();
            break;

        case 7:
            enqueueTiket(antrian, front, rear, p, n);
            enter();
            break;

        case 8:
            dequeueTiket(antrian, front, rear, riwayat, top);
            enter();
            break;

        case 9:
            peekData(antrian, front, rear, riwayat, top);
            enter();
            break;

        case 10:
            tampilAntrian(antrian, front, rear);
            enter();
            break;

        case 11:
            tampilRiwayat(riwayat, top);
            enter();
            break;

        case 12:
            popRiwayat(riwayat, top);
            enter();
            break;

        case 13:
            cout << "\nProgram selesai.\n";
            break;

        default:
            cout << "\nPilihan tidak valid.\n";
            enter();
        }

    } while (pilih != 13);

    return 0;
}
