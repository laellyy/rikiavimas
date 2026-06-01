#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;

// Maksimalus masyvo dydis
const int MAX = 50000;

// Skaitikliai palyginimams ir sukeitimams
long long palyginimai = 0;
long long sukeitimai = 0;

// Darbiniai masyvai
int a[MAX];
int atsarga[MAX];

// ======================= DUOMENŲ GENERAVIMAS =======================

// Atsitiktiniai duomenys
void generuoti_atsitiktini(int n) {
    for (int i = 0; i < n; i++)
        atsarga[i] = rand() % 10000;
}

// Surikiuoti duomenys
void generuoti_surikiuota(int n) {
    for (int i = 0; i < n; i++)
        atsarga[i] = i;
}

// Atvirkščiai surikiuoti duomenys
void generuoti_atvirkscia(int n) {
    for (int i = 0; i < n; i++)
        atsarga[i] = n - i;
}

// Kopijuoja atsargą į darbinį masyvą
void kopijuoti(int n) {
    for (int i = 0; i < n; i++)
        a[i] = atsarga[i];
}

// Nulinti skaitiklius
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

// ======================= VIENO TESTO PALEIDIMAS =======================

void testuoti(int algoritmas, int n, const char* pavadinimas) {
    kopijuoti(n);
    nulinti();

    auto start = chrono::high_resolution_clock::now();

    if (algoritmas == 1)
        selection_sort(n);
    else
        merge_sort(0, n - 1);

    auto end = chrono::high_resolution_clock::now();
    long long laikas = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << pavadinimas << endl;
    cout << "  Laikas (us): " << laikas << endl;
    cout << "  Palyginimai: " << palyginimai << endl;
    cout << "  Sukeitimai:  " << sukeitimai << endl << endl;
}

// ======================= AUTOMATINIS EKSPERIMENTAS =======================

void automatinis_eksperimentas() {
    int dydziai[3] = {5000, 10000, 50000};

    for (int t = 1; t <= 3; t++) {
        cout << "\n=== DUOMENU TIPAS: ";
        if (t == 1) cout << "ATSITIKTINIAI ===\n";
        if (t == 2) cout << "SURIKIUOTI ===\n";
        if (t == 3) cout << "ATVIRKSCIAI SURIKIUOTI ===\n";

        for (int d = 0; d < 3; d++) {
            int n = dydziai[d];
            cout << "\n--- Masyvo dydis: " << n << " ---\n";

            for (int alg = 1; alg <= 2; alg++) {
                long long sum_laikas = 0;
                long long sum_palyg = 0;
                long long sum_sukeit = 0;

                for (int kartas = 0; kartas < 5; kartas++) {
                    if (t == 1) generuoti_atsitiktini(n);
                    if (t == 2) generuoti_surikiuota(n);
                    if (t == 3) generuoti_atvirkscia(n);

                    kopijuoti(n);
                    nulinti();

                    auto start = chrono::high_resolution_clock::now();

                    if (alg == 1) selection_sort(n);
                    else merge_sort(0, n - 1);

                    auto end = chrono::high_resolution_clock::now();
                    long long laikas = chrono::duration_cast<chrono::microseconds>(end - start).count();

                    sum_laikas += laikas;
                    sum_palyg += palyginimai;
                    sum_sukeit += sukeitimai;
                }

                cout << (alg == 1 ? "Selection sort" : "Merge sort") << endl;
                cout << "  Vidutinis laikas (us): " << sum_laikas / 5 << endl;
                cout << "  Vid. palyginimai:      " << sum_palyg / 5 << endl;
                cout << "  Vid. sukeitimai:       " << sum_sukeit / 5 << endl << endl;
            }
        }
    }
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

// ======================= PAGRINDINIS MENIU =======================

int main() {
    srand(time(0));

    while (true) {
        cout << "\n=== RIKIAVIMO ALGORITMU ANALIZE ===\n";
        cout << "1 - Paleisti automatini eksperimenta\n";
        cout << "2 - Rankinis testavimas\n";
        cout << "3 - Iseiti\n";
        cout << "Pasirinkimas: ";

        int pasirinkimas = saugus_ivedimas(1, 3);

        if (pasirinkimas == 1) {
            automatinis_eksperimentas();
        }

        else if (pasirinkimas == 2) {
            int tipas, dydis, alg;
            int n = 0;

            cout << "\nDuomenu tipas:\n1 - Atsitiktiniai\n2 - Surikiuoti\n3 - Atvirksciai\nPasirinkimas: ";
            tipas = saugus_ivedimas(1, 3);

            cout << "\nDydis:\n1 - 5000\n2 - 10000\n3 - 50000\nPasirinkimas: ";
            dydis = saugus_ivedimas(1, 3);

            if (dydis == 1) n = 5000;
            if (dydis == 2) n = 10000;
            if (dydis == 3) n = 50000;

            if (tipas == 1) generuoti_atsitiktini(n);
            if (tipas == 2) generuoti_surikiuota(n);
            if (tipas == 3) generuoti_atvirkscia(n);

            cout << "\nAlgoritmas:\n1 - Selection sort\n2 - Merge sort\nPasirinkimas: ";
            alg = saugus_ivedimas(1, 2);

            testuoti(alg, n, alg == 1 ? "Selection sort" : "Merge sort");
        }

        else if (pasirinkimas == 3) {
            cout << "Programa baigta.\n";
            break;
        }
    }

    cout << "Spauskite ENTER, kad uzdaryti...";
    cin.ignore();
    cin.get();

    return 0;
}
