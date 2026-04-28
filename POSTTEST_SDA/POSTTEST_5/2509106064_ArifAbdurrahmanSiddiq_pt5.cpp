#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk Circular Linked List Toko Sembako
struct BarangNode
{
    string namaBarang;
    int stok;
    BarangNode *next;

    // Constructor
    BarangNode(string nama, int jumlah)
    {
        namaBarang = nama;
        stok = jumlah;
        next = nullptr;
    }
};

// Fungsi insert di akhir Circular Linked List untuk membangun data
BarangNode *tambahBarang(BarangNode *head, string nama, int jumlah)
{
    BarangNode *newNode = new BarangNode(nama, jumlah);
    if (head == nullptr)
    {
        newNode->next = newNode; // Menunjuk ke dirinya sendiri (Sirkuler)
        return newNode;
    }

    BarangNode *temp = head;
    while (temp->next != head)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

/**
 * @brief Fungsi untuk menampilkan semua barang dalam Circular Linked List.
 * @param head Pointer ke node pertama (head) dari circular linked list.
 * @logic
 * 1. Base case: Jika head adalah nullptr, cetak "Gudang kosong." dan return.
 * 2. Gunakan pointer sementara (temp) yang dimulai dari head.
 * 3. Lakukan perulangan (do-while disarankan) untuk mencetak namaBarang dan stok.
 * 4. Pindah ke node selanjutnya (temp = temp->next).
 * 5. Berhenti ketika temp kembali menunjuk ke head.
 */
void tampilkanStokSembako(BarangNode *head)
{
    if (head == nullptr) // kondisi nullptr jika gudang kosong/linked list kosong
    {
        cout << "Gudang kosong." << endl; // output kondisinya
        return;                           // keluar dari fungsi
    }

    BarangNode *temp = head; // pointer sementara dimulai dari head

    do // perulangan do-while untuk mencetak semua barang
    {
        cout << "- " << temp->namaBarang << ": " << temp->stok << endl; // tiap stok barang ditampilkan dengan jumlahnya
        temp = temp->next;                                              // pindah ke node selanjutnya
    } while (temp != head); // berhenti ketika temp kembali menunjuk ke head karena circular linked list
}
int main()
{
    BarangNode *head = nullptr;

    head = tambahBarang(head, "Beras", 50);
    head = tambahBarang(head, "Minyak Goreng", 30);
    head = tambahBarang(head, "Gula Pasir", 20);
    head = tambahBarang(head, "Tepung Terigu", 15);

    cout << "Daftar Stok Sembako:" << endl;
    tampilkanStokSembako(head);
    /* Harusnya output:
       - Beras: 50
       - Minyak Goreng: 30
       - Gula Pasir: 20
       - Tepung Terigu: 15
    */

    return 0;
}