#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double t, double T, double alpha) {
    return -alpha * (pow(T, 4));
}

vector<pair<double, double>> metoda_Eulera(double T0, double t_koncowy, double h, double alpha) {
    vector<pair<double, double>> wyniki;

    double t = 0.0;
    double T = T0;

    wyniki.push_back({ t, T });

    while (t < t_koncowy) {
        if (t + h > t_koncowy) {
            h = t_koncowy - t;
        }

        // Euler step: T_new = T_old + h * f(t, T)
        double dT = h * f(t, T, alpha);
        T += dT;
        t += h;

        wyniki.push_back({ t, T });
    }

    return wyniki;
}

double sredni_blad_kwadratowy(const vector<pair<double, double>>& wyniki_dokladne,
    const vector<pair<double, double>>& wyniki_przyblizone) {
    double suma_kwadratow_bledu = 0.0;
    int liczba_punktow = 0;

    for (const auto& punkt_dokladny : wyniki_dokladne) {
        double t_dokladny = punkt_dokladny.first;
        double T_dokladny = punkt_dokladny.second;

        double min_roznica = INFINITY;
        double T_przyblizone = 0.0;

        // Find closest time point in approximated solution
        for (const auto& punkt_przyblizony : wyniki_przyblizone) {
            double t_przyblizony = punkt_przyblizony.first;
            double roznica = fabs(t_dokladny - t_przyblizony);

            if (roznica < min_roznica) {
                min_roznica = roznica;
                T_przyblizone = punkt_przyblizony.second;
            }
        }

        if (min_roznica < 1e-10) {
            suma_kwadratow_bledu += pow(T_dokladny - T_przyblizone, 2);
            liczba_punktow++;
        }
    }

    return (liczba_punktow > 0) ? suma_kwadratow_bledu / liczba_punktow : INFINITY;
}

void wyswietl_naglowek(const string& tytul) {
    cout << "\n" << string(60, '=') << endl;
    cout << tytul << endl;
    cout << string(60, '=') << endl;
}

void wyswietl_rozwiazanie(const vector<pair<double, double>>& wyniki, double h) {
    cout << setw(15) << left << "Time [s]" << setw(20) << "Temperature [K]" << endl;
    cout << string(35, '-') << endl;

    int max_punkty = 20;
    int liczba_punktow = wyniki.size();

    if (liczba_punktow > max_punkty) {
        // Display beginning
        for (int i = 0; i < 5; i++) {
            cout << fixed << setprecision(4) << setw(15) << left << wyniki[i].first << setw(20) << wyniki[i].second << endl;
        }

        cout << setw(35) << "..." << endl;

        // Display middle section
        int srodek = liczba_punktow / 2;
        for (int i = srodek - 2; i <= srodek + 2; i++) {
            if (i >= 0 && i < liczba_punktow) {
                cout << fixed << setprecision(4) << setw(15) << left << wyniki[i].first << setw(20) << wyniki[i].second << endl;
            }
        }

        cout << setw(35) << "..." << endl;

        // Display end
        for (int i = liczba_punktow - 5; i < liczba_punktow; i++) {
            cout << fixed << setprecision(4) << setw(15) << left << wyniki[i].first << setw(20) << wyniki[i].second << endl;
        }
    }
    else {
        for (const auto& punkt : wyniki) {
            cout << fixed << setprecision(4) << setw(15) << left << punkt.first << setw(20) << punkt.second << endl;
        }
    }
}

int main() {
    double T0 = 2379.0;          // Initial sphere temperature [K]
    double alpha = 9.0 * 1e-12;  // Cooling coefficient
    double t_koncowy = 100.0;    // Final time [s]

    vector<double> kroki = { 10.0, 1.0, 0.1, 0.01 , 0.001 };
    vector<vector<pair<double, double>>> wszystkie_wyniki;

    cout << "Final time: " << t_koncowy << " s" << endl;

    // Compute solutions for different step sizes
    for (double h : kroki) {
        vector<pair<double, double>> wyniki = metoda_Eulera(T0, t_koncowy, h, alpha);
        wszystkie_wyniki.push_back(wyniki);

        wyswietl_rozwiazanie(wyniki, h);

        cout << "\n-> Sphere temperature after " << t_koncowy << " seconds: "
            << fixed << setprecision(4) << wyniki.back().second << " K" << endl;
    }

    // Calculate mean square errors using finest solution as reference
    wyswietl_naglowek("MEAN SQUARE ERROR");
    cout << setw(20) << left << "Integration step [s]" << setw(30) << "Mean square error " << endl;
    cout << string(50, '-') << endl;

    const auto& wyniki_dokladne = wszystkie_wyniki.back();

    for (size_t i = 0; i < kroki.size(); ++i) {
        double blad = sredni_blad_kwadratowy(wyniki_dokladne, wszystkie_wyniki[i]);
        cout << fixed << setprecision(6) << setw(20) << left << kroki[i] << setw(30) << blad << endl;
    }

    wyswietl_naglowek("RESULTS SUMMARY");
    cout << "Initial sphere temperature: " << T0 << " K" << endl;
    cout << "Alpha coefficient: " << alpha << endl;
    cout << "Final time: " << t_koncowy << " s" << endl;
    cout << "\nFinal temperatures for different integration steps:" << endl;

    for (size_t i = 0; i < kroki.size(); ++i) {
        cout << "- Step h = " << kroki[i] << " s: "
            << fixed << setprecision(4) << wszystkie_wyniki[i].back().second << " K" << endl;
    }

    cout << "\nConclusion: Calculation accuracy increases with decreasing integration step." << endl;

    return 0;
}