#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>
#include <string>
#include <cstdlib>
#include <ctime>

// Функция для безопасного ввода целого числа
int GetInputInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Ошибка! Пожалуйста, введите целое число.\n";
        } else if (value <= 0) {
            std::cerr << "Ошибка! Число должно быть положительным.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Функция для безопасного ввода выбора меню
int GetInputChoice(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Ошибка! Пожалуйста, введите число.\n";
        } else if (value < min || value > max) {
            std::cerr << "Ошибка! Выберите вариант от " << min << " до " << max << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Функция для безопасного ввода double
double GetInputDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Ошибка! Пожалуйста, введите число.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

double** CreateMatrixA(int rows, int columns) {
    double** matrixA = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrixA[i] = new double[columns];
    }
    return matrixA;
}

double* CreateMatrixBAuto(double** matrixA, int rows, int columns) {
    double* matrixB = new double[rows];
    for (int i = 0; i < rows; i++) {
        matrixB[i] = 0;
        for (int j = 0; j < columns; j++) {
            matrixB[i] += matrixA[i][j];
        }
    }
    return matrixB;
}

double* CreateMatrixBManual(int rows) {
    double* matrixB = new double[rows];
    std::cout << "=== Ручной ввод вектора свободных членов ===" << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << "Элемент B[" << i << "]: ";
        matrixB[i] = GetInputDouble("");
    }
    return matrixB;
}

double* CreateMatrixBRandom(int rows) {
    double* matrixB = new double[rows];
    std::cout << "=== Случайное заполнение вектора свободных членов ===" << std::endl;
    for (int i = 0; i < rows; i++) {
        matrixB[i] = rand() % 100;
    }
    return matrixB;
}

double** CreateAugmentedMatrix(double** matrixA, double* matrixB, int rows, int columns) {
    double** AugmentedMatrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        AugmentedMatrix[i] = new double[columns + 1];
        for (int j = 0; j < columns; j++) {
            AugmentedMatrix[i][j] = matrixA[i][j];
        }
        AugmentedMatrix[i][columns] = matrixB[i];
    }
    return AugmentedMatrix;
}

double** CopyMatrixA(double** matrixA, int rows, int columns) {
    double** copy_matrixA = new double*[rows];
    for (int i = 0; i < rows; i++) {
        copy_matrixA[i] = new double[columns];
        for (int j = 0; j < columns; j++) {
            copy_matrixA[i][j] = matrixA[i][j];
        }
    }
    return copy_matrixA;
}

double* CopyMatrixB(double* matrixB, int rows) {
    double* copy_matrixB = new double[rows];
    for (int i = 0; i < rows; i++) {
        copy_matrixB[i] = matrixB[i];
    }
    return copy_matrixB;
}

void DeleteMatrixA(double** matrixA, int rows) {
    if (matrixA) {
        for (int i = 0; i < rows; i++) {
            delete[] matrixA[i];
        }
        delete[] matrixA;
    }
}

void DeleteMatrixB(double* matrixB) {
    if (matrixB) {
        delete[] matrixB;
    }
}

void DeleteAugmentedMatrix(double** matrix, int rows) {
    if (matrix) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

void PrintMatrixA(double** matrixA, int rows, int columns) {
    std::cout << "Матрица коэффициентов:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrixA[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PrintAugmentedMatrix(double** AugmentedMatrix, int rows, int columns) {
    std::cout << "Расширенная матрица:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns + 1; j++) {
            std::cout << AugmentedMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PrintMatrixB(double* matrixB, int rows) {
    std::cout << "Вектор свободных членов:" << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << matrixB[i] << std::endl;
    }
    std::cout << std::endl;
}

void PrintMatrixX(double* matrixX, int rows) {
    std::cout << "Решение СЛАУ методом Гаусса: " << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << "x" << (i + 1) << " = " << matrixX[i] << std::endl;
    }
    std::cout << std::endl;
}

double GaussianMethod(double** matrixA, double* matrixB, double*& matrixX, int rows, int columns) {
    double** copy_matrixA = CopyMatrixA(matrixA, rows, columns);
    double* copy_matrixB = CopyMatrixB(matrixB, rows);
    double** augmentedMatrix = CreateAugmentedMatrix(copy_matrixA, copy_matrixB, rows, columns);

    // Прямой ход метода Гаусса
    for (int col = 0, row = 0; col < columns && row < rows; col++) {
        // Поиск главного элемента в текущем столбце
        int max_row = row;
        double max_val = std::abs(augmentedMatrix[row][col]);
        for (int i = row + 1; i < rows; i++) {
            if (std::abs(augmentedMatrix[i][col]) > max_val) {
                max_val = std::abs(augmentedMatrix[i][col]);
                max_row = i;
            }
        }

        // Проверка на вырожденность
        if (std::abs(augmentedMatrix[max_row][col]) < 1e-15) {
            // Освобождение памяти перед возвратом
            DeleteMatrixA(copy_matrixA, rows);
            DeleteMatrixB(copy_matrixB);
            DeleteAugmentedMatrix(augmentedMatrix, rows);
            return -1; // Матрица вырождена
        }

        // Перестановка строк
        if (max_row != row) {
            std::swap(augmentedMatrix[row], augmentedMatrix[max_row]);
        }

        // Нормализация текущей строки
        double elem = augmentedMatrix[row][col];
        for (int j = col; j <= columns; j++) {
            augmentedMatrix[row][j] /= elem;
        }

        // Исключение переменной из других строк
        for (int i = 0; i < rows; i++) {
            if (i != row) {
                double factor = augmentedMatrix[i][col];
                for (int j = col; j <= columns; j++) {
                    augmentedMatrix[i][j] -= augmentedMatrix[row][j] * factor;
                }
            }
        }
        row++;
    }

    matrixX = new double[rows];

    // Извлекаем решение из последнего столбца расширенной матрицы
    for (int i = 0; i < rows; i++) {
        matrixX[i] = augmentedMatrix[i][columns];
    }

    // Вычисление невязки r = b - A*x
    double r = 0.0;
    for (int i = 0; i < rows; i++) {
        double r_i = matrixB[i];
        for (int j = 0; j < columns; j++) {
            r_i -= matrixA[i][j] * matrixX[j];
        }
        r += r_i * r_i;
    }
    r = std::sqrt(r);

    // Освобождение временной памяти
    DeleteMatrixA(copy_matrixA, rows);
    DeleteMatrixB(copy_matrixB);
    DeleteAugmentedMatrix(augmentedMatrix, rows);

    return r;
}

int main() {
    int rows, columns;

    std::cout << "=== Ввод размеров матрицы ===" << std::endl << std::endl;

    rows = GetInputInt("Введите кол-во строк матрицы: ");
    std::cout << std::endl;
    columns = GetInputInt("Введите кол-во столбцов матрицы: ");
    std::cout << std::endl;

    double** MatrixA = CreateMatrixA(rows, columns);
    double* MatrixB = nullptr;
    double* MatrixX = nullptr;
    double** AugmentedMatrix = nullptr;

    try {
        // Выбор способа заполнения матрицы A
        std::cout << "=== Заполнение матрицы коэффициентов ===" << std::endl;
        std::cout << "Выберите способ заполнения: " << std::endl;
        std::cout << "1. Вручную" << std::endl;
        std::cout << "2. Случайными числами" << std::endl;
        std::cout << "3. Завершить программу" << std::endl;

        int choiceA = GetInputChoice("Ваш выбор: ", 1, 3);
        std::cout << std::endl;

        switch (choiceA) {
            case 1:
                std::cout << "=== Ручной ввод матрицы ===" << std::endl;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        std::cout << "Элемент [" << i << "][" << j << "]: ";
                        MatrixA[i][j] = GetInputDouble("");
                    }
                }
                break;

            case 2:
                std::cout << "=== Случайное заполнение матрицы ===" << std::endl;
                srand(time(nullptr));
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        MatrixA[i][j] = rand() % 100;
                    }
                }
                break;

            case 3:
                std::cout << "Завершение программу" << std::endl;
                DeleteMatrixA(MatrixA, rows);
                return 0;

            default:
                break;
        }

        std::cout << "=== Матрица A ===" << std::endl;
        PrintMatrixA(MatrixA, rows, columns);

        // Выбор способа заполнения вектора B
        std::cout << "=== Заполнение вектора свободных членов ===" << std::endl;
        std::cout << "Выберите способ заполнения: " << std::endl;
        std::cout << "1. Автоматически (сумма строк матрицы A)" << std::endl;
        std::cout << "2. Вручную" << std::endl;
        std::cout << "3. Случайными числами" << std::endl;

        int choiceB = GetInputChoice("Ваш выбор: ", 1, 3);
        std::cout << std::endl;

        switch (choiceB) {
            case 1:
                MatrixB = CreateMatrixBAuto(MatrixA, rows, columns);
                std::cout << "Вектор свободных членов создан автоматически (сумма строк матрицы A)" << std::endl;
                break;

            case 2:
                MatrixB = CreateMatrixBManual(rows);
                break;

            case 3:
                MatrixB = CreateMatrixBRandom(rows);
                std::cout << "Вектор свободных членов заполнен случайными числами" << std::endl;
                break;

            default:
                break;
        }

        std::cout << "=== Матрица B ===" << std::endl;
        PrintMatrixB(MatrixB, rows);

        AugmentedMatrix = CreateAugmentedMatrix(MatrixA, MatrixB, rows, columns);
        std::cout << "=== Расширенная матрица ===" << std::endl;
        PrintAugmentedMatrix(AugmentedMatrix, rows, columns);

        std::cout << "=== Решение системы ===" << std::endl;
        double residual = GaussianMethod(MatrixA, MatrixB, MatrixX, rows, columns);
        if (residual == -1) {
            std::cout << "Ошибка: матрица вырождена!" << std::endl;
        } else {
            std::cout << "Значение невязки r = " << residual << std::endl << std::endl;

            std::cout << "=== Решение X ===" << std::endl;
            PrintMatrixX(MatrixX, rows);
        }

    } catch (...) {
        std::cerr << "Произошла ошибка!" << std::endl;
    }

    // Освобождение памяти
    DeleteMatrixA(MatrixA, rows);
    DeleteMatrixB(MatrixB);
    DeleteMatrixB(MatrixX);
    DeleteAugmentedMatrix(AugmentedMatrix, rows);

    return 0;
}
