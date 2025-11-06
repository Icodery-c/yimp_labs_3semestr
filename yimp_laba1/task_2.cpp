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

double** CreateMatrix(int rows, int columns) {
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[columns];
    }
    return matrix;
}

double** CreateAugmentedMatrix(double** matrix, int rows, int columns) {
    double** AugmentedMatrix = new double*[rows];

    for (int i = 0; i < rows; i++) {
        AugmentedMatrix[i] = new double[2 * columns];

        for (int j = 0; j < columns; j++) {
            AugmentedMatrix[i][j] = matrix[i][j];
        }

        for (int j = columns; j < 2 * columns; j++) {
            AugmentedMatrix[i][j] = (j == columns + i) ? 1.0 : 0.0;
        }
    }

    return AugmentedMatrix;
}

void DeleteMatrix(double** matrix, int rows) {
    if (matrix) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

void PrintMatrix(double** matrix, int rows, int columns) {
    std::cout << "Матрица коэффициентов:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PrintInverseMatrix(double** inversematrix, int rows, int columns) {
    std::cout << "Обратная матрица:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << inversematrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double** CopyMatrix(double** matrix, int rows, int columns) {
    double** copy_matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        copy_matrix[i] = new double[columns];
        for (int j = 0; j < columns; j++) {
            copy_matrix[i][j] = matrix[i][j];
        }
    }
    return copy_matrix;
}

double GaussianDeterminantMethod(double** matrix, int rows, int columns) {
    if (rows != columns) {
        throw std::invalid_argument("Matrix must be square for determinant calculation");
    }

    if (rows == 1) { return matrix[0][0]; }
    if (rows == 2) { return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]); }

    double** tempMatrix = CopyMatrix(matrix, rows, columns);
    double det = 1.0;

    try {
        for (int i = 0; i < rows; i++) {
            // Поиск максимального элемента в столбце
            int maxRow = i;
            double maxVal = fabs(tempMatrix[i][i]);

            for (int k = i + 1; k < rows; k++) {
                if (fabs(tempMatrix[k][i]) > maxVal) {
                    maxVal = fabs(tempMatrix[k][i]);
                    maxRow = k;
                }
            }

            // Если максимальный элемент близок к нулю - определитель 0
            if (fabs(tempMatrix[maxRow][i]) < 1e-12) {
                DeleteMatrix(tempMatrix, rows);
                return 0.0;
            }

            // Перестановка строк
            if (maxRow != i) {
                std::swap(tempMatrix[i], tempMatrix[maxRow]);
                det *= -1.0;  // При перестановке строк определитель меняет знак
            }

            // Исключение Гаусса
            for (int j = i + 1; j < rows; j++) {
                double factor = tempMatrix[j][i] / tempMatrix[i][i];
                for (int k = i + 1; k < columns; k++) {
                    tempMatrix[j][k] -= factor * tempMatrix[i][k];
                }
            }

            // Умножаем на диагональный элемент ПОСЛЕ исключения
            det *= tempMatrix[i][i];
        }
    } catch (...) {
        DeleteMatrix(tempMatrix, rows);
        throw;
    }

    DeleteMatrix(tempMatrix, rows);
    return det;
}

double InverseMatrix(double** matrix, double**& inversematrix, int rows, int columns) {
    if (rows != columns) {
        throw std::invalid_argument("Matrix must be square for inverse calculation");
    }

    double det = GaussianDeterminantMethod(matrix, rows, columns);
    //std::cout << "Определитель матрицы: " << det << std::endl;

    if (fabs(det) < 1e-12) {
        return -1.0; // Матрица вырожденная
    }

    double** augmentedMatrix = CreateAugmentedMatrix(matrix, rows, columns);

    try {
        // Прямой ход метода Гаусса
        for (int i = 0; i < rows; i++) {
            int pivot_row = i;
            double max_val = fabs(augmentedMatrix[i][i]);

            for (int k = i + 1; k < rows; k++) {
                if (fabs(augmentedMatrix[k][i]) > max_val) {
                    max_val = fabs(augmentedMatrix[k][i]);
                    pivot_row = k;
                }
            }

            if (pivot_row != i) {
                std::swap(augmentedMatrix[i], augmentedMatrix[pivot_row]);
            }

            double pivot = augmentedMatrix[i][i];
            for (int j = i; j < 2 * columns; j++) {
                augmentedMatrix[i][j] /= pivot;
            }

            for (int k = 0; k < rows; k++) {
                if (k != i) {
                    double factor = augmentedMatrix[k][i];
                    for (int j = i; j < 2 * columns; j++) {
                        augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
                    }
                }
            }
        }

        // Выделение памяти для обратной матрицы и копирование результата
        inversematrix = CreateMatrix(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                inversematrix[i][j] = augmentedMatrix[i][columns + j];
            }
        }

        PrintInverseMatrix(inversematrix, rows, columns);

        // Проверка точности: A * A^(-1) должно быть близко к единичной матрице
        double norm = 0.0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                double element = 0.0;
                for (int k = 0; k < rows; k++) {
                    element += inversematrix[i][k] * matrix[k][j];
                }
                double diff = (i == j ? 1.0 - element : -element);
                norm += diff * diff;
            }
        }

        DeleteMatrix(augmentedMatrix, rows);
        return sqrt(norm);

    } catch (...) {
        DeleteMatrix(augmentedMatrix, rows);
        throw;
    }
}

int main() {
    int rows, columns;

    std::cout << "=== Ввод размеров матрицы ===" << std::endl << std::endl;

    rows = GetInputInt("Введите кол-во строк матрицы: ");
    std::cout << std::endl;
    columns = GetInputInt("Введите кол-во столбцов матрицы: ");
    std::cout << std::endl;

    // Проверка на квадратность матрицы для определителя и обратной матрицы
    if (rows != columns) {
        std::cout << "Предупреждение: матрица не квадратная." << std::endl;
        std::cout << "Определитель и обратная матрица могут быть вычислены только для квадратных матриц." << std::endl;
        std::cout << std::endl;
    }

    double** Matrix = CreateMatrix(rows, columns);
    double** InverseMatrixPtr = nullptr;

    try {
        // Выбор способа заполнения матрицы
        std::cout << "=== Заполнение матрицы ===" << std::endl;
        std::cout << "Выберите способ заполнения: " << std::endl;
        std::cout << "1. Вручную" << std::endl;
        std::cout << "2. Случайными числами" << std::endl;
        std::cout << "3. Завершить программу" << std::endl;

        int choice = GetInputChoice("Ваш выбор: ", 1, 3);
        std::cout << std::endl;

        switch (choice) {
            case 1:
                std::cout << "=== Ручной ввод матрицы ===" << std::endl;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        std::cout << "Элемент [" << i << "][" << j << "]: ";
                        Matrix[i][j] = GetInputDouble("");
                    }
                }
                break;

            case 2:
                std::cout << "=== Случайное заполнение матрицы ===" << std::endl;
                srand(time(nullptr));
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        Matrix[i][j] = rand() % 100;
                    }
                }
                break;

            case 3:
                std::cout << "Завершение программы" << std::endl;
                DeleteMatrix(Matrix, rows);
                return 0;

            default:
                break;
        }

        std::cout << "=== Исходная матрица ===" << std::endl;
        PrintMatrix(Matrix, rows, columns);

        // Вычисление определителя (только для квадратных матриц)
        if (rows == columns) {
            std::cout << "=== Вычисление определителя ===" << std::endl;
            try {
                double determinant = GaussianDeterminantMethod(Matrix, rows, columns);
                std::cout << "Определитель матрицы det = " << determinant << std::endl << std::endl;

                // Вычисление обратной матрицы (только если определитель не нулевой)
                if (fabs(determinant) > 1e-12) {
                    std::cout << "=== Вычисление обратной матрицы ===" << std::endl;

                    InverseMatrixPtr = CreateMatrix(rows, columns);
                    double norm = InverseMatrix(Matrix, InverseMatrixPtr, rows, columns);

                    if (norm >= 0) {
                        std::cout << "Норма невязки: " << norm << std::endl;
                    } else {
                        std::cout << "Матрица вырожденная, обратной не существует" << std::endl;
                    }
                } else {
                    std::cout << "Матрица вырожденная (определитель = 0), обратной матрицы не существует" << std::endl;
                }

            } catch (const std::exception& e) {
                std::cout << "Ошибка при вычислении: " << e.what() << std::endl;
            }
        } else {
            std::cout << "=== Операции с матрицей ===" << std::endl;
            std::cout << "Матрица не квадратная, поэтому определитель и обратная матрица не могут быть вычислены." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Освобождение памяти
    DeleteMatrix(Matrix, rows);
    if (InverseMatrixPtr != nullptr) {
        DeleteMatrix(InverseMatrixPtr, rows);
    }

    return 0;
}
