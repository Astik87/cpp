#include <iostream>
#include <clocale>
#include <windows.h>

void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

float det2x2(float** A) {

    int det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    return det;

}

float detAll(float** A, int m, int n) {
    
    if (m == n and n == 2) {
        return det2x2(A);
    }

    int res = 0;

    for (int f = 0; f < n; f++) {

        float** B = new float* [m-1];
        for (int i = 0; i < n-1; i++) B[i] = new float[n-1];

        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j != f) {
                    int pM = i-1;
                    int pN = j;
                    if (j > f) pN = j-1;

                    B[pM][pN] = A[i][j];

                }
            }
        }
        res += pow(-1, f) * A[0][f] * detAll(B, m-1, n-1);

    }

    return res;

}

float** sum(float** A, float** B, int m, int n) {

    float** C = new float* [m];

    for (int i = 0; i < m; i++) C[i] = new float[n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;

}

float** difference(float** A, float** B, int m, int n) {

    float** C = new float* [m];

    for (int i = 0; i < m; i++) C[i] = new float[n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;

}

float** composition(float** A, float** B, int m, int n, int g, int h) {

    float** C = new float* [m];

    for (int i = 0; i < m; i++) C[i] = new float[h];

    for (int i = 0; i < m; i++) {
        for (int f = 0; f < h; f++) {
            float sum = 0;
            for (int j = 0; j < n; j++) {
                sum += A[i][j] * B[j][f];
            }
            C[i][f] = sum;
        }
    }

    return C;

}

float** transposition(float** A, int m, int n) {

    float** C = new float* [m];
    for (int i = 0; i < m; i++) C[i] = new float[n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[j][i] = A[i][j];
        }
    }

    return C;

}

float** multiplyByNumber(float** A, int m, int n, float num) {

    float** C = new float* [m];
    for (int i = 0; i < m; i++) C[i] = new float [n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] * num;
        }
    }

    return C;

}

float** divideByNumber(float** A, int m, int n, float num) {

    float** C = new float* [m];
    for (int i = 0; i < m; i++) C[i] = new float[n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] / num;
        }
    }

    return C;

}


int main()
{
    setlocale(LC_CTYPE, "rus");

    size_t m;
    size_t n;

    std::cout << "Введите количество строк матрицы A: ";
    std::cin >> m;
    std::cout << "Введите количество столбцов матрицы A: ";
    std::cin >> n;

    std::cout << "Введите элементы матрицы A по очереди: \n";

    float** A = new float* [m];

    for (int i = 0; i < n; i++) A[i] = new float[n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> A[i][j];
        }
    }

    int g, h;

    std::cout << "Введите количество строк матрицы B: ";
    std::cin >> g;
    std::cout << "Введите количество столбцов матрицы B: ";
    std::cin >> h;

    std::cout << "Введите элементы матрицы B по очереди: \n";

    float** B = new float* [g];

    for (int i = 0; i < h; i++) B[i] = new float[h];
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < h; j++) {
            std::cin >> B[i][j];
        }
    }

    ClearScreen();

    std::cout << "Матрица A:" << "\n";

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << A[i][j] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "Матрица B:" << "\n";
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < h; j++) {
            std::cout << B[i][j] << "  ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
    std::cout << "1. Найти сумму" << "\n";
    std::cout << "2. Найти разность" << "\n";
    std::cout << "3. Найти произведение" << "\n";
    std::cout << "4. Найти определитель" << "\n";
    std::cout << "5. Транспонировать матрицы" << "\n";
    std::cout << "6. Умножить на число N" << "\n";
    std::cout << "7. Разделить на число N" << "\n";

    int act;

    std::cout << "Выберите действие(1-5): ";
    std::cin >> act;

    if (act == 1) {
        
        if (m == g and n == h) {
            float** C = sum(A, B, m, n);

            std::cout << "Матрица A + B: " << "\n";

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < h; j++) {
                    std::cout << C[i][j] << "  ";
                }
                std::cout << "\n";
            }
        }
        else {
            std::cout << "Ошибка: Матрицы А и В разной размерности.";
        }

    }

    if (act == 2) {

        if (m == g and n == h) {
            float** C = difference(A, B, m, n);

            std::cout << "Матрица A - B: " << "\n";

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < h; j++) {
                    std::cout << C[i][j] << "  ";
                }
                std::cout << "\n";
            }
        }
        else {
            std::cout << "Ошибка: Матрицы А и В разной размерности.";
        }

    }

    if (act == 3) {

        if (n == g) {
            float** C = composition(A, B, m, n, g, h);

            std::cout << "Матрица A * B: " << "\n";

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < h; j++) {
                    std::cout << C[i][j] << "  ";
                }
                std::cout << "\n";
            }
        }
        else {
            std::cout << "Ошибка: Число столбцов матрицы А не совпадает с числом строк В";
        }

    }

    if (act == 4) {
        if (m == n) {
            std::cout << "det A = " << detAll(A, m,n) << "\n";
        }
        else {
            std::cout << "Ошибка: Матрица А не квадратная.";
        }

        if (g == h) {
            std::cout << "det B = " << detAll(B, g, h) << "\n";
        }
        else {
            std::cout << "Ошибка: Матрица B не квадратная.";
        }
    }

    if (act == 5) {
        
        float** C = transposition(A, m, n);
        
        std::cout << "A':" << "\n";

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < h; j++) {
                std::cout << C[i][j] << "  ";
            }
            std::cout << "\n";
        }

        C = transposition(B, g, h);

        std::cout << "B':" << "\n";

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < h; j++) {
                std::cout << C[i][j] << "  ";
            }
            std::cout << "\n";
        }

    }

    if (act == 6) {

        float num;

        std::cout << "Введите число N: ";
        std::cin >> num;

        float** C = multiplyByNumber(A, m, n, num);
        
        std::cout << num << "A:\n";

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < h; j++) {
                std::cout << C[i][j] << "  ";
            }
            std::cout << "\n";
        }

        C = multiplyByNumber(B, g, h, num);

        std::cout << num << "B:\n";

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < h; j++) {
                std::cout << C[i][j] << "  ";
            }
            std::cout << "\n";
        }

    }

    if (act == 7) {

        float num;

        std::cout << "Введите число N: ";
        std::cin >> num;

        float** C = divideByNumber(A, m, n, num);

        std::cout << "A/" << num << ":\n";

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < h; j++) {
                std::cout << C[i][j] << "  ";
            }
            std::cout << "\n";
        }

        C = divideByNumber(B, g, h, num);

        std::cout << "B/" << num << ":\n";

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < h; j++) {
                std::cout << C[i][j] << "  ";
            }
            std::cout << "\n";
        }

    }

}