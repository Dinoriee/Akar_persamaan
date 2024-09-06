#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

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
            cout << "Masukkan nilai a, b, c untuk persamaan polinomial (satu-persatu!): ";
            cin >> a >> b >> c;
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
                    cout << "Masukkan nilai a, b, c untuk persamaan sinusoidal (satu-persatu!): ";
                    cin >> a >> b >> c;
                    return [a, b, c](double x) {
                        return a * sin(b * x) + c;
                    };
                case 2:
                    cout << "Masukkan nilai a, b, c untuk persamaan sinusoidal (satu-persatu!): ";
                    cin >> a >> b >> c;
                    return [a, b, c](double x) {
                        return a * cos(b * x) + c;
                    };
                case 3:
                    cout << "Masukkan nilai a, b, c untuk persamaan sinusoidal (satu-persatu!): ";
                    cin >> a >> b >> c;
                    return [a, b, c](double x) {
                        return a * tan(b * x) + c;
                    };
                case 4:
                    cout << "Masukkan nilai a, b, c untuk persamaan eksponensial (satu-persatu!): ";
                    cin >> a >> b >> c;
                    return [a, b, c](double x) {
                        return a * exp(b * x) + c;
                    };
                case 5:
                    cout << "Masukkan nilai a, b, c untuk persamaan logaritma (satu-persatu!): ";
                    cin >> a >> b >> c;
                    return [a, b, c](double x) {
                        return a * log(b * x) + c;
                    };
                default:
                    cout << "Masukkan nilai yang valid!\n";
                    return [](double x) { return x; };
            }

        case 3:
            cout << "Masukkan nilai a, b, c untuk persamaan kuadrat: ";
            cin >> a >> b >> c;
            return [a, b, c](double x) {
                return a * pow(x, 2) + b * x + c;
            };

        default:
            cout << "Pilihan tidak valid. Menggunakan fungsi default f(x) = x.\n";
            return [](double x) { return x; };
    }
}

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

int main() {
    double range_awal, range_akhir, step;
    cout << "Masukkan nilai range awal: ";
    cin >> range_awal;
    cout << "Masukkan nilai range akhir: ";
    cin >> range_akhir;
    cout << "Masukkan Step: ";
    cin >> step;

    std::function<double(double)> persamaan = akar();

    tabel(range_awal, range_akhir, step, persamaan);

    return 0;
}
