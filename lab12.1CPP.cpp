#include <iostream>
#include <fstream>
using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary); // відкриваємо файл для запису
    char ch;
    double number;

    do {
        cout << "Enter a number: ";
        cin >> number;
        fout.write((char*)&number, sizeof(number)); // записуємо число у файл
        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary); // відкриваємо файл для читання
    double number;

    cout << "Contents of " << fname << ":\n";
    while (fin.read((char*)&number, sizeof(number))) {
        cout << number << " ";
    }
    cout << endl;
}

void ProcessBIN(char* fname, char* gname) {
    ifstream fin(fname, ios::binary); // відкриваємо вхідний файл
    ofstream fout(gname, ios::binary); // відкриваємо вихідний файл

    double number;
    bool hasNegative = false, hasPositive = false;
    double maxNegative, minPositive;

    // Шукаємо найбільше від'ємне і найменше додатне
    while (fin.read((char*)&number, sizeof(number))) {
        if (number < 0) {
            if (!hasNegative || number > maxNegative) {
                maxNegative = number;
                hasNegative = true;
            }
        }
        else if (number > 0) {
            if (!hasPositive || number < minPositive) {
                minPositive = number;
                hasPositive = true;
            }
        }
    }

    // Записуємо результати у вихідний файл
    if (hasNegative) {
        fout.write((char*)&maxNegative, sizeof(maxNegative));
    }
    if (hasPositive) {
        fout.write((char*)&minPositive, sizeof(minPositive));
    }
}

int main() {
    char fname[100]; // ім'я вхідного файлу
    char gname[100]; // ім'я вихідного файлу

    cout << "Enter input file name: ";
    cin >> fname;
    CreateBIN(fname); // створюємо вхідний бінарний файл

    PrintBIN(fname); // виводимо вміст вхідного файлу

    cout << "Enter output file name: ";
    cin >> gname;
    ProcessBIN(fname, gname); // обробляємо файл

    PrintBIN(gname); // виводимо вміст вихідного файлу

    return 0;
}
