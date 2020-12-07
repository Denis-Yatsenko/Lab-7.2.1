#include <iostream>
#include <Windows.h>
#include <time.h>
#include <iomanip>

using namespace std;

void Create(int** mas, const int row, const int column, const int Min, const int Max) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            mas[i][j] = Min + rand() % (Max - Min + 1);
}

void Print(int** mas, const int row, const int column) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << setw(4) << mas[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// Найбільший з мінімальний елементів по парних стовпцях

int FindMaxFromMinEvenColumn(int** mas, const int row, const int column) {
    int col = 0, k = 0;
    if (column % 2 == 0) {
        col = column / 2;
    }
    else if (column % 2 == 1) {
        col = (column - 1) / 2;
    }

    int* n = new int[col];

    for (int c = column - 2; c >= 1;) { // Знаходимо мінімальні
        int EvenColumn = c;
        int min = mas[0][EvenColumn];

        for (int i = 0; i < row; i++) {
            if (mas[i][EvenColumn] < min) {
                min = mas[i][EvenColumn];
            }
        }

        n[k] = min;
        k++;
        c -= 2;
    }

    int MaxFromMin = n[0];

    for (int p = 0; p < col; p++) { // Знаходимо найбільший з мінімальних
        if (n[p] > MaxFromMin)
            MaxFromMin = n[p];
    }

    delete[] n;
    return MaxFromMin;
}

// Найменьший з максимальних елементів по непарних стовпцях

int FindMinFromMaxOddColumn(int** mas, const int row, const int column) {
    int col = 0, k = 0;

    if (column % 2 == 0) {
        col = column / 2;
    }
    else if (column % 2 == 1) {
        col = (column + 1) / 2;
    }

    int* n = new int[col];

    for (int c = column - 1; c >= 0;) { // Знаходимо максимальні
        int OddColumn = c;
        int max = mas[0][OddColumn];

        for (int i = 0; i < row; i++) {
            if (mas[i][OddColumn] > max) {
                max = mas[i][OddColumn];
            }
        }
        n[k] = max;
        k++;
        c -= 2;
    }

    int MinFromMax = n[0];

    for (int p = 0; p < col; p++) { // Знаходимо найменьший з максимальних
        if (n[p] < MinFromMax) {
            MinFromMax = n[p];
        }
    }

    delete[] n;
    return MinFromMax;
}

void Replace(int** mas, const int row, const int column) {
    int indexImax = 0, indexKmax = 0, MaxFromMin = FindMaxFromMinEvenColumn(mas, row, column);
    int indexImin = 0, indexKmin = 0, MinFromMax = FindMinFromMaxOddColumn(mas, row, column);

    int help = 0;

    for (int k = 0; k < column; k++) {
        if (k % 2 == 0) {
            for (int i = 0; i < row; i++) {
                if (mas[i][k] == MinFromMax) {
                    indexImin = i;
                    indexKmin = k;
                    break;
                }
            }
        }
        else if (k % 2 == 1) {
            for (int i = 0; i < row; i++) {
                if (mas[i][k] == MaxFromMin) {
                    indexImax = i;
                    indexKmax = k;
                    break;
                }
            }
        }
    }

    help = mas[indexImin][indexKmin];
    mas[indexImin][indexKmin] = mas[indexImax][indexKmax];
    mas[indexImax][indexKmax] = help;
}

int main()
{
    srand((unsigned)time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int k, n, Min, Max;
    cout << " Введіть кількість рядків матриці: "; cin >> k;
    cout << " Введіть кількість стовпців матриці: "; cin >> n; cout << endl;
    cout << " Введіть мінімальне можливе значення у матриці: "; cin >> Min;
    cout << " Введіть максимальне можливе значення у матриці: "; cin >> Max; cout << endl;

    int** a = new int* [k];
    for (int i = 0; i < k; i++) {
        a[i] = new int[n];
    }

    Create(a, k, n, Min, Max);
    Print(a, k, n);
    cout << " Найбільший з мінімальних елементів парних стовпців: " << FindMaxFromMinEvenColumn(a, k, n) << endl;
    cout << " Найменьший з максимальних елементів непарних стовпців: " << FindMinFromMaxOddColumn(a, k, n) << endl;
    cout << endl << " Ці елементи поміняно місцями: " << endl << endl;

    Replace(a, k, n);
    Print(a, k, n);

    for (int i = 0; i < k; i++) {
        delete[] a[i];
    }
    delete[] a;

    cin.get();
    return 0;
}