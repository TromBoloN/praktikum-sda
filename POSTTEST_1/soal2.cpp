#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa
{
    string nama;
    string nim;
    float ipk;
};

int main()
{
    Mahasiswa mhs[5];
    cout << "===== Input Data Mahasiswa =====" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "\nMahasiswa ke-" << i + 1 << endl;
        cout << "Nama : ";
        cin.ignore();
        getline(cin, mhs[i].nama);
        cout << "NIM  : ";
        getline(cin, mhs[i].nim);
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
    }

    int indexMax = 0;
    for (int i = 1; i < 5; i++)
    {
        if (mhs[i].ipk > mhs[indexMax].ipk)
        {
            indexMax = i;
        }
    }

    cout << "\n==== Mahasiswa dengan IPK Tertinggi ====" << endl;
    cout << "Nama : " << mhs[indexMax].nama << endl;
    cout << "NIM  : " << mhs[indexMax].nim << endl;
    cout << "IPK  : " << mhs[indexMax].ipk << endl;

    return 0;
}