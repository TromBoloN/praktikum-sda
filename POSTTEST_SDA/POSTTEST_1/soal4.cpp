#include <iostream>
using namespace std;

void swap(int *ptr1, int *ptr2)
{
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int main()
{
    int a, b;

    cout << "Masukkan bilangan pertama: ";
    cin >> a;
    cout << "Masukkan bilangan kedua: ";
    cin >> b;

    cout << "--- Program Penukar Nilai ---" << endl;
    cout << "Nilai awal: A = " << a << ", B = " << b << endl;

    swap(&a, &b);

    cout << "Nilai akhir: A = " << a << ", B = " << b << endl;
    return 0;
}