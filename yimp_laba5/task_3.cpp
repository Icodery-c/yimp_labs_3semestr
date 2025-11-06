#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <limits>
#include <iomanip>

bool readGraph(const std::string& filename, std::vector<std::vector<double>>& matrix, int& n) {
    if (!std::filesystem::exists(filename)) {
        std::cerr << "Ошибка: файл '" << filename << "' не найден!" << std::endl;
        return false;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return false;
    }

    file >> n;
    matrix.resize(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matrix[i][j];
        }
    }

    file.close();
    std::cout << "Взвешенный граф успешно считан из файла: " << std::filesystem::absolute(filename) << std::endl;
    return true;
}

void addEdge(std::vector<std::vector<double>>& matrix, int u, int v, double weight) {
    if (u < 0 || u >= matrix.size() || v < 0 || v >= matrix.size()) {
        std::cout << "Ошибка: неверные номера вершин!" << std::endl;
        return;
    }

    if (matrix[u][v] != 0.0) {
        std::cout << "Ребро уже существует с весом: " << matrix[u][v] << std::endl;
        return;
    }

    matrix[u][v] = weight;
    std::cout << "Ребро (" << u << ", " << v << ") с весом " << weight << " добавлено." << std::endl;
}

void removeEdge(std::vector<std::vector<double>>& matrix, int u, int v) {
    if (u < 0 || u >= matrix.size() || v < 0 || v >= matrix.size()) {
        std::cout << "Ошибка: неверные номера вершин!" << std::endl;
        return;
    }

    if (matrix[u][v] == 0.0) {
        std::cout << "Ребро (" << u << ", " << v << ") не найдено." << std::endl;
        return;
    }

    matrix[u][v] = 0.0;
    std::cout << "Ребро (" << u << ", " << v << ") удалено." << std::endl;
}

void printAdjList(const std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    std::cout << "\nСписок смежности взвешенного графа:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << i << ": ";
        bool hasNeighbors = false;
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != 0.0) {
                std::cout << j << "(" << matrix[i][j] << ") ";
                hasNeighbors = true;
            }
        }
        if (!hasNeighbors) {
            std::cout << "";
        }
        std::cout << std::endl;
    }
}

void printMatrix(const std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    std::cout << "\nМатрица смежности взвешенного графа:\n";
    std::cout << "   ";
    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(8) << i;
    }
    std::cout << std::endl;

    for (int i = 0; i < n; ++i) {
        std::cout << i << ": ";
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void saveGraph(const std::string& filename, const std::vector<std::vector<double>>& matrix) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка записи в файл " << filename << std::endl;
        return;
    }

    int n = matrix.size();
    file << n << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << std::fixed << std::setprecision(2) << matrix[i][j] << " ";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Взвешенный граф сохранён в файл: " << std::filesystem::absolute(filename) << std::endl;
}

void saveAsAdjList(const std::string& filename, const std::vector<std::vector<double>>& matrix) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка записи в файл " << filename << std::endl;
        return;
    }

    int n = matrix.size();
    file << n << "\n";
    for (int i = 0; i < n; ++i) {
        file << i;
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != 0.0) {
                file << " " << j << " " << std::fixed << std::setprecision(2) << matrix[i][j];
            }
        }
        file << "\n";
    }

    file.close();
    std::cout << "Список смежности сохранён в файл: " << std::filesystem::absolute(filename) << std::endl;
}

int getIntInput() {
    int value;
    while (!(std::cin >> value) || value < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (value < 0) {
            std::cout << "Число должно быть неотрицательным. Пожалуйста, введите число >= 0: ";
        } else {
            std::cout << "Неверный ввод. Пожалуйста, введите число: ";
        }
    }
    return value;
}

double getDoubleInput() {
    double value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод. Пожалуйста, введите число: ";
    }
    return value;
}

char getCharInput() {
    char value;
    std::cin >> value;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

int main() {

    std::vector<std::vector<double>> matrix;
    int n = 0;
    std::string filename;

    std::cout << "Введите имя файла для использования графа: ";
    std::cin >> filename;

    if (!readGraph(filename, matrix, n)) {
        std::cout << "Создание пустого взвешенного графа. Введите количество вершин: ";
        n = getIntInput();
        matrix.resize(n, std::vector<double>(n, 0.0));
    }

    while (true) {
        int choice;
        int u, v;
        double weight;

        std::cout << "\n===== МЕНЮ ВЗВЕШЕННОГО ГРАФА =====" << std::endl;
        std::cout << "1. Показать граф (список смежности)" << std::endl;
        std::cout << "2. Показать граф (матрица смежности)" << std::endl;
        std::cout << "3. Добавить ребро" << std::endl;
        std::cout << "4. Удалить ребро" << std::endl;
        std::cout << "5. Сохранить граф в файл (матрица)" << std::endl;
        std::cout << "6. Сохранить граф в файл (список смежности)" << std::endl;
        std::cout << "0. Выход из программы" << std::endl;
        std::cout << "Ваш выбор: ";

        choice = getIntInput();

        if (choice == 0) {
            std::cout << "Программа завершена.\n";
            break;
        }

        switch (choice) {
            case 1:
                printAdjList(matrix);
                break;
            case 2:
                printMatrix(matrix);
                break;
            case 3:
                std::cout << "Введите вершины и вес (u v weight): ";
                u = getIntInput();
                v = getIntInput();
                weight = getDoubleInput();
                addEdge(matrix, u, v, weight);
                break;
            case 4:
                std::cout << "Введите вершины (u v): ";
                u = getIntInput();
                v = getIntInput();
                removeEdge(matrix, u, v);
                break;
            case 5:
                std::cout << "Введите имя файла для сохранения: ";
                std::cin >> filename;
                saveGraph(filename, matrix);
                break;
            case 6:
                std::cout << "Введите имя файла для сохранения: ";
                std::cin >> filename;
                saveAsAdjList(filename, matrix);
                break;
            default:
                std::cerr << "Неверный выбор! Пожалуйста, выберите 0-6.\n";
                continue;
        }

        while (true) {
            std::cout << "\nХотите продолжить работу? (y/n): ";
            char continue_choice = getCharInput();

            if (continue_choice == 'n' || continue_choice == 'N') {
                std::cout << "Программа завершена.\n";
                return 0;
            }
            else if (continue_choice == 'y' || continue_choice == 'Y') {
                break;
            }
            else {
                std::cout << "Неверный ввод. Пожалуйста, введите 'y' или 'n'.\n";
            }
        }
    }

    return 0;
}
