#include <iostream>
using namespace std;

void findMin(int A[], int n)
{
    int min = A[0];
    int minIndex = 0;

    for (int i = 1; i < n; i++)
    {
        if (A[i] < min)
        {
            min = A[i];
            minIndex = i;
        }
    }

    cout << "Nilai minimum: " << min << endl;
    cout << "Indeks minimum: " << minIndex << endl;
}

int main()
{
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = 8;

    findMin(A, n);

    return 0;
}
/*
Pseudocode dan Cost:

1. min ← A[0]        -> c1
2. for i ← 1 to n-1  -> c2
3.    if A[i] < min  -> c3
4.       min ← A[i]  -> c4
5. return min        -> c5

========================================
BEST CASE: Kondisi di c4 tidak jalan karna nilai kecil berada di index awal 0
Tmin(n) =
c1
+ (n-1)c2
+ (n-1)c3
+ c5

Tmin(n) = c1 + c5 + (n-1)(c2 + c3)
Tmin(n) = O(n)

========================================
WORST CASE: Kondisi di c4 jalan terus sebanyak n-1 karena nilai index selanjutnya selalu lebih kecil
Tmax(n) =
c1
+ (n-1)c2
+ (n-1)c3
+ (n-1)c4
+ c5

Tmax(n) = c1 + c5 + (n-1)(c2 + c3 + c4)

Tmax(n) = O(n)

========================================
KESIMPULAN:
Best Case  = O(n)
Worst Case = O(n)
*/