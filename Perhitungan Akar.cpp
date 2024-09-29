#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

using namespace std;


void tabel(double range_awal, double range_akhir, double step, std::function<double(double)> persamaan) {
    double error = abs(persamaan(range_awal));
    double x = range_awal;

    while (range_awal <= range_akhir) {
        double fx = persamaan(range_awal);
        cout << "x: " << range_awal << "  f(x): " << fx << endl;

        if (abs(fx) < error) {
            error = abs(fx);
            x = range_awal;
        }

        range_awal += step;
    }

    cout << "Akar x: " << x << " memiliki error terkecil yakni: " << error << endl;
}

void bisection(double range_awal, double range_akhir, double tol, int maxIter, std::function<double(double)> persamaan) {
    double c;
    if (persamaan(range_awal) * persamaan(range_akhir) >= 0) {
        cout << "Tidak ada akar di interval [" << range_awal << ", " << range_akhir << "]" << endl;
        return;
    }

    cout << "Iterasi\t\ta\t\tb\t\tc\t\tf(c)\t\tError" << endl;
    for (int iter = 1; iter <= maxIter; iter++) {
        c = (range_awal + range_akhir) / 2;
        double error = fabs((persamaan(range_awal) - persamaan(range_akhir)) / 2);

        cout << fixed << setprecision(6);
        cout << iter << "\t\t" << range_awal << "\t" << range_akhir << "\t" << c << "\t" << persamaan(c) << "\t" << error << endl;

        if (abs(persamaan(c)) < tol || error < tol) {
            cout << "Akar ditemukan pada x = " << c << " dengan toleransi " << tol << endl;
            return;
        }

        if (persamaan(c) * persamaan(range_awal) < 0) {
            range_akhir = c;
        } else {
            range_awal = c;
        }
    }

    cout << "Iterasi maksimal tercapai, akar mendekati x = " << c << endl;
}

void falsi(double range_awal, double range_akhir, double tol, int maxIter, std::function<double(double)> persamaan) {
    double c;
    if (persamaan(range_awal) * persamaan(range_akhir) >= 0) {
        cout << "Tidak ada akar di interval [" << range_awal << ", " << range_akhir << "]" << endl;
        return;
    }

    cout << "Iterasi\t\ta\t\tb\t\tf(a)\t\tf(b)\t\tc\t\tf(c)" << endl;
    for (int iter = 1; iter <= maxIter; iter++) {
        c = range_awal - persamaan(range_awal) * fabs(((range_akhir-range_awal) / (persamaan(range_akhir) - persamaan(range_awal))));
        double error = fabs(persamaan(c));

        cout << fixed << setprecision(6);
        cout << iter << "\t\t" << range_awal << "\t" << range_akhir << "\t" << persamaan(range_awal) << "\t" << persamaan(range_akhir) << "\t" << c << "\t" << persamaan(c) << endl;

        if (abs(persamaan(c)) < tol || error < tol) {
            cout << "Akar ditemukan pada x = " << c << " dengan toleransi " << tol << endl;
            return;
        }

        if (persamaan(c) * persamaan(range_awal) < 0) {
            range_akhir = c;
        } else {
            range_awal = c;
        }
    }

    cout << "Iterasi maksimal tercapai, akar mendekati x = " << c << endl;
}

void metode(double range_awal, double range_akhir, std::function<double(double)> persamaan){
    int rumus;
    cout << "Pilih metode yang ingin digunakan (1.Tabel, 2.Bisection, 3. Falsi): ";
    cin >> rumus;
    switch(rumus){
        case 1:{
            double step;
            cout << "Masukkan Step: ";
            cin >> step;
            tabel(range_awal, range_akhir, step, persamaan);
            break;
        }

        case 2:{
            double tol;
            int maxIter;
            cout << "Masukkan nilai toleransi yang diinginkan: ";
            cin >> tol;
            cout << "Masukkan maksimal iterasi yang dilakukan: ";
            cin >> maxIter;

            bisection(range_awal, range_akhir, tol, maxIter, persamaan);
            break;
        }

        case 3:{
            double tol;
            int maxIter;
            cout << "Masukkan nilai toleransi yang diinginkan: ";
            cin >> tol;
            cout << "Masukkan maksimal iterasi yang dilakukan: ";
            cin >> maxIter;

            falsi(range_awal, range_akhir, tol, maxIter, persamaan);
            break;
        }

        default:
            cout << "Metode tidak valid." << endl;
            break;
    }
}


std::function<double(double)> akar() {
    cout << "Pilih fungsi non linear:\n";
    cout << "1. Bentuk-bentuk persamaan polinomial: a0 + a1 * x + a2 * x^2 + a3 * x^3 + … + an * x\n";
    cout << "2. Bentuk-bentuk persamaan transcedental: sin(x), cos(x), tan(x), exp(x), log(x)\n";
    cout << "3. Bentuk persamaan kuadrat: ax^2 + bx + c\n";
    cout << "Masukkan angka yang valid (1-3): ";

    int pilihan;
    cin >> pilihan;

    double a, b, c;

    switch (pilihan) {
        case 1:
            cout << "Masukkan nilai a, b, c untuk persamaan polinomial (satu-persatu!): " << endl;
            cout << "Masukkan nilai a: ";
            cin >> a;
            cout << "Masukkan nilai b: ";
            cin >> b;
            cout <<"Masukkan nilai c: ";
            cin >> c;
            int p;
            cout << "Masukkan nilai pangkat: ";
            cin >> p;
            return [a, b, c, p](double x) {
                return a * pow(x, p) + b * x + c;
            };

        case 2:
            int sinusoidal;
            cout << "Pilih jenis persamaan sinusoidal:\n1. Sin\n2. Cos\n3. Tan\n4. Eksponensial\n5. Logaritma\n";
            cin >> sinusoidal;
            switch (sinusoidal) {
                case 1:
                    cout << "Masukkan nilai a, b, c untuk persamaan polinomial (satu-persatu!): " << endl;
                    cout << "Masukkan nilai a: ";
                    cin >> a;
                    cout <<"Masukkan nilai b: ";
                    cin >> b;
                    cout <<"Masukkan nilai c: ";
                    cin >> c;
                    return [a, b, c](double x) {
                        return a * sin(b * x) + c;
                    };
                case 2:
                    cout << "Masukkan nilai a, b, c untuk persamaan polinomial (satu-persatu!): " << endl;
                    cout << "Masukkan nilai a: ";
                    cin >> a;
                    cout <<"Masukkan nilai b: ";
                    cin >> b;
                    cout <<"Masukkan nilai c: ";
                    cin >> c;
                    return [a, b, c](double x) {
                        return a * cos(b * x) + c;
                    };
                case 3:
                    cout << "Masukkan nilai a, b, c untuk persamaan polinomial (satu-persatu!): " << endl;
                    cout << "Masukkan nilai a: ";
                    cin >> a;
                    cout <<"Masukkan nilai b: ";
                    cin >> b;
                    cout <<"Masukkan nilai c: ";
                    cin >> c;
                    return [a, b, c](double x) {
                        return a * tan(b * x) + c;
                    };
                case 4:
                    cout << "Masukkan nilai a, b, c untuk persamaan polinomial (satu-persatu!): " << endl;
                    cout << "Masukkan nilai a: ";
                    cin >> a;
                    cout <<"Masukkan nilai b: ";
                    cin >> b;
                    cout <<"Masukkan nilai c: ";
                    cin >> c;
                    return [a, b, c](double x) {
                        return a * exp(b * x) + c;
                    };
                case 5:
                    cout << "Masukkan nilai a, b, c untuk persamaan polinomial (satu-persatu!): " << endl;
                    cout << "Masukkan nilai a: ";
                    cin >> a;
                    cout <<"Masukkan nilai b: ";
                    cin >> b;
                    cout <<"Masukkan nilai c: ";
                    cin >> c;
                    return [a, b, c](double x) {
                        return a * log(b * x) + c;
                    };
                default:
                    cout << "Masukkan nilai yang valid!\n";
                    return [](double x) { return x; };
            }

        case 3:
            cout << "Masukkan nilai a, b, c untuk persamaan polinomial (satu-persatu!): " << endl;
            cout << "Masukkan nilai a: ";
            cin >> a;
            cout << "Masukkan nilai b: ";
            cin >> b;
            cout << "Masukkan nilai c: ";
            cin >> c;
            return [a, b, c](double x) {
                return a * pow(x, 2) + b * x + c;
            };

        default:
            cout << "Pilihan tidak valid. Menggunakan fungsi default f(x) = x.\n";
            break;
            return [](double x) { return x; };
    }
}


int main() {
    double range_awal, range_akhir;
    cout << "Masukkan nilai range awal: ";
    cin >> range_awal;
    cout << "Masukkan nilai range akhir: ";
    cin >> range_akhir;



    std::function<double(double)> persamaan = akar();

    metode(range_awal, range_akhir, persamaan);

    return 0;
}
