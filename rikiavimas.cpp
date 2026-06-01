#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX = 50000;

long long palyginimai = 0;
long long sukeitimai = 0;

int a[MAX];
int atsarga[MAX];

// ======================= DUOMENŲ GENERAVIMAS =======================

void generuoti_atsitiktini(int n) {
    for (int i = 0; i < n; i++)
        atsarga[i] = rand() % 10000;
}

void generuoti_surikiuota(int n) {
    for (int i = 0; i < n; i++)
        atsarga[i] = i;
}

void generuoti_atvirkscia(int n) {
    for (int i = 0; i < n; i++)
        atsarga[i] = n - i;
}

void kopijuoti(int n) {
    for (int i = 0; i < n; i++)
        a[i] = atsarga[i];
}

void nulinti() {
    palyginimai = 0;
    sukeitimai = 0;
}

// ======================= SELECTION SORT =======================

void selection_sort(int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_id = i;
        for (int j = i + 1; j < n; j++) {
            palyginimai++;
            if (a[j] < a[min_id])
                min_id = j;
        }
        if (min_id != i) {
            swap(a[i], a[min_id]);
            sukeitimai++;
        }
    }
}

// ======================= MERGE SORT =======================

void merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = a[left + i];
    for (int i = 0; i < n2; i++) R[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        palyginimai++;
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void merge_sort(int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;

    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    merge(left, mid, right);
}

// ======================= TESTAVIMAS =======================

void testuoti(int pasirinkimas, int n, const char* pavadinimas) {
    kopijuoti(n);
    nulinti();

    clock_t pradzia = clock();

    if (pasirinkimas == 1)
        selection_sort(n);
    else if (pasirinkimas == 2)
        merge_sort(0, n - 1);

    clock_t pabaiga = clock();
    double laikas = (double)(pabaiga - pradzia) / CLOCKS_PER_SEC;

    cout << pavadinimas << endl;
    cout << "  Laikas:      " << laikas << " s" << endl;
    cout << "  Palyginimai: " << palyginimai << endl;
    cout << "  Sukeitimai:  " << sukeitimai << endl;
    cout << endl;
}

// ======================= SAUGI ĮVESTIS =======================

int saugus_ivedimas(int min, int max) {
    int x;
    while (!(cin >> x) || x < min || x > max) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Neteisinga ivestis! Bandykite dar karta: ";
    }
    return x;
}

// ======================= MENIU =======================

int main() {
    srand(time(0));

    int tipas, dydis, algoritmas;
    int n = 0;

    cout << "=== RIKIAVIMO ALGORITMU ANALIZE ===" << endl << endl;

    // 1. Duomenų tipas
    cout << "Pasirinkite duomenu tipa:" << endl;
    cout << "  1 - Atsitiktiniai" << endl;
    cout << "  2 - Surikiuoti" << endl;
    cout << "  3 - Atvirksciai surikiuoti" << endl;
    cout << "Pasirinkimas: ";
    tipas = saugus_ivedimas(1, 3);

    // 2. Masyvo dydis
    cout << endl;
    cout << "Pasirinkite masyvo dydi:" << endl;
    cout << "  1 - 5000" << endl;
    cout << "  2 - 10000" << endl;
    cout << "  3 - 50000" << endl;
    cout << "Pasirinkimas: ";
    dydis = saugus_ivedimas(1, 3);

    if (dydis == 1) n = 5000;
    else if (dydis == 2) n = 10000;
    else n = 50000;

    // Generavimas
    if (tipas == 1) generuoti_atsitiktini(n);
    else if (tipas == 2) generuoti_surikiuota(n);
    else generuoti_atvirkscia(n);

    // 3. Algoritmas
    cout << endl;
    cout << "Pasirinkite algoritma:" << endl;
    cout << "  1 - Selection sort" << endl;
    cout << "  2 - Merge sort" << endl;
    cout << "  3 - Abu (palyginimui)" << endl;
    cout << "Pasirinkimas: ";
    algoritmas = saugus_ivedimas(1, 3);

    cout << endl << "--- REZULTATAI (n = " << n << ") ---" << endl << endl;

    if (algoritmas == 1)
        testuoti(1, n, "Selection sort");
    else if (algoritmas == 2)
        testuoti(2, n, "Merge sort");
    else {
        testuoti(1, n, "Selection sort");
        testuoti(2, n, "Merge sort");
    }

    cout << "Programa baigta." << endl;

    // ======================= PAUZE PRIES UŽDARYMĄ =======================
    cout << "Spauskite ENTER, kad uzdaryti...";
    cin.ignore();
    cin.get();

    return 0;
}
