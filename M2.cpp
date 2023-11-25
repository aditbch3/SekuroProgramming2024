#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

class Simulator {
private:
    double x, y;
    vector<pair<double, double>> log;
    size_t index_log;

public:
    Simulator() : x(0.0), y(0.0), index_log(0) {}

    void lokasi() const {
        cout << fixed << setprecision(2);
        cout << "(" << x << ", " << y << ")" << endl;
    }

    void gerak(double deltaX, double deltaY) {
        x += deltaX;
        y += deltaY;
        update_log();
    }

    void gerak_2(double v, double t, double theta) {
        double deltaX = v * t * cos(theta * M_PI / 180.0);
        double deltaY = v * t * sin(theta * M_PI / 180.0);
        x += deltaX;
        y += deltaY;
        update_log();
    }

    void undo() {
        if (index_log > 0) {
            index_log--;
            x = log[index_log].first;
            y = log[index_log].second;
        } else {
            cout << "Undo tidak dapat dilakukan lagi." << endl;
        }
    }

    void redo() {
        if (index_log < log.size() - 1) {
            index_log++;
            x = log[index_log].first;
            y = log[index_log].second;
        } else {
            cout << "Redo tidak dapat dilakukan lagi." << endl;
        }
    }

private:
    void update_log() {
        // Hapus bagian log setelah index_log
        log.resize(index_log + 1);
        log.push_back(make_pair(x, y));
        index_log++;
    }
};

int main() {
    Simulator drone;

    int choice;
    double deltaX, deltaY, v, t, theta;

    do {
        cout << "Simulasi Drone URO." << endl;
        cout << "1. Cek Lokasi Drone" << endl;
        cout << "2. Gerak Drone" << endl;
        cout << "3. Gerak Drone dengan Kecepatan dan Waktu" << endl;
        cout << "4. Undo" << endl;
        cout << "5. Redo" << endl;
        cout << "6. Exit" << endl;
        cout << "Pilih menu (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                drone.lokasi();
                break;
            case 2:
                cout << "Masukkan perubahan koordinat x: ";
                cin >> deltaX;
                cout << "Masukkan perubahan koordinat y: ";
                cin >> deltaY;
                drone.gerak(deltaX, deltaY);
                cout << "Drone telah bergerak." << endl;
                break;
            case 3:
                cout << "Masukkan kecepatan: ";
                cin >> v;
                cout << "Masukkan waktu: ";
                cin >> t;
                cout << "Masukkan sudut (derajat): ";
                cin >> theta;
                drone.gerak_2(v, t, theta);
                cout << "Drone telah bergerak." << endl;
                break;
            case 4:
                drone.undo();
                cout << "Undo dilakukan." << endl;
                break;
            case 5:
                drone.redo();
                cout << "Redo dilakukan." << endl;
                break;
            case 6:
                cout << "Program berakhir. Terima kasih!" << endl;
                break;
            default:
                cout << "Menu tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
