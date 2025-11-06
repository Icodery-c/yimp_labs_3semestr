#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>

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
        } else if (value < 0.0) {
            std::cerr << "Ошибка! p должно быть неотрицательным.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

std::vector<std::vector<double>> CreateMatrix(int n) {
    return std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
}

void PrintMatrix(const std::vector<std::vector<double>>& A) {
    std::cout << "\nМатрица A:\n";
    for (const auto& row : A) {
        for (double val : row)
            std::cout << std::setw(12) << val << " ";
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void FillTridiagonalMatrix(std::vector<std::vector<double>>& A, int N, double h, double p) {
    double h2 = 1.0 / (h * h);
    int n = N + 1; // Размерность матрицы

    // Первая строка
    A[0][0] = 2.0 * h2 + p;
    A[0][1] = -2.0 * h2;

    // Последняя строка
    A[N][N-1] = -2.0 * h2;
    A[N][N] = 2.0 * h2 + p;

    // Внутренние строки
    for (int i = 1; i < N; ++i) {
        A[i][i-1] = -h2;
        A[i][i] = 2.0 * h2 + p;
        A[i][i+1] = -h2;
    }
}

std::vector<double> ComputeEigenVector(int N, int m, double h) {
    std::vector<double> phi(N + 1); // Размер N+1
    for (int k = 0; k <= N; ++k)
        phi[k] = std::cos(m * k * h);
    return phi;
}

double ComputeEigenValue(int m, double h, double p) {
    return 4.0 / (h * h) * std::sin(m * h / 2.0) * std::sin(m * h / 2.0) + p;
}

std::vector<double> MultiplyMatrixVector(const std::vector<std::vector<double>>& A,
                                        const std::vector<double>& v) {
    int n = v.size();
    std::vector<double> result(n, 0.0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result[i] += A[i][j] * v[j];
    return result;
}

double ComputeError(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i)
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    return std::sqrt(sum);
}

int main() {
    std::cout << "=== Проверка собственных векторов матрицы A ===\n";

    int N = GetInputInt("Введите N (число узлов): ");
    double p = GetInputDouble("Введите параметр p >= 0: ");

    double h = M_PI / N;
    std::cout << "h = " << h << std::endl;

    int matrix_size = N + 1;
    auto A = CreateMatrix(matrix_size);
    FillTridiagonalMatrix(A, N, h, p);
    PrintMatrix(A);

    std::cout << std::fixed << std::setprecision(25);
    std::cout << "\nПроверка собственных векторов φ^(m):\n";

    for (int m = 0; m <= N; ++m) {
        auto phi = ComputeEigenVector(N, m, h);
        auto Aphi = MultiplyMatrixVector(A, phi);
        double lambda = ComputeEigenValue(m, h, p);

        std::vector<double> lambdaPhi(matrix_size);
        for (int i = 0; i < matrix_size; ++i)
            lambdaPhi[i] = lambda * phi[i];

        double error = ComputeError(Aphi, lambdaPhi);

        // Выводим дополнительную информацию для анализа
        std::cout << "m = " << m
                  << "   λ(m) = " << lambda
                  << "   (Aφ)0 = " << Aphi[0]
                  << "   ||Aφ - λφ|| = " << error << std::endl;
    }

    return 0;
}
