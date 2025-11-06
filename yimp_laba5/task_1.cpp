#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <limits>

struct Edge {
    int u;
    int v;
};

bool readGraph(const std::string& filename, std::vector<Edge>& edges, int& n) {
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
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int u;
        ss >> u;
        int v;
        while (ss >> v) {
            edges.push_back({u, v});
        }
    }

    file.close();
    std::cout << "Граф успешно считан из файла: " << std::filesystem::absolute(filename) << std::endl;
    return true;
}

void addEdge(std::vector<Edge>& edges, int u, int v) {
    for (auto& e : edges) {
        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            std::cout << "Ребро уже существует" << std::endl;
            return;
        }
    }

    edges.push_back({u, v});
    edges.push_back({v, u});
    std::cout << "Ребро (" << u << ", " << v << ") добавлено." << std::endl;
}

void removeEdge(std::vector<Edge>& edges, int u, int v) {
    auto it = std::remove_if(edges.begin(), edges.end(),
        [&](Edge& e) {
            return (e.u == u && e.v == v) || (e.u == v && e.v == u);
        });

    if (it != edges.end()) {
        edges.erase(it, edges.end());
        std::cout << "Ребро (" << u << ", " << v << ") удалено." << std::endl;
    } else {
        std::cout << "Ребро (" << u << ", " << v << ") не найдено." << std::endl;
    }
}

void printAdjList(const std::vector<Edge>& edges, int n) {
    std::vector<std::vector<int>> adj(n);

    for (const auto& e : edges) {
        adj[e.u].push_back(e.v);
    }

    std::cout << "\nСписок смежности графа:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << i << ": ";
        for (int neighbor : adj[i])
            std::cout << neighbor << " ";
        std::cout << std::endl;
    }
}

void saveAsMatrix(const std::filesystem::path& filepath, const std::vector<Edge>& edges, int n) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Ошибка записи в файл " << filepath << std::endl;
        return;
    }

    file << n << "\n";

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    for (const auto& e : edges) {
        if (e.u < n && e.v < n) {
            matrix[e.u][e.v] = 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            file << matrix[i][j] << " ";
        file << "\n";
    }

    file.close();
    std::cout << "Матрица смежности сохранена: " << std::filesystem::absolute(filepath) << std::endl;
}

void saveGraph(const std::filesystem::path& filepath, const std::vector<Edge>& edges, int n) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Ошибка записи в файл " << filepath << std::endl;
        return;
    }

    file << n << "\n";

    std::vector<std::vector<int>> adj(n);
    for (auto& e : edges)
        adj[e.u].push_back(e.v);

    for (int i = 0; i < n; ++i) {
        file << i;
        for (int neighbor : adj[i])
            file << " " << neighbor;
        file << "\n";
    }

    file.close();
    std::cout << "Граф сохранён в файл: " << std::filesystem::absolute(filepath) << std::endl;
}

int getValInput() {
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод. Пожалуйста, введите число: ";
    }
    return value;
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

char getCharInput() {
    char value;
    std::cin >> value;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

int main() {
    std::vector<Edge> edges;
    int n = 0;
    std::string filename;


    std::cout << "Введите имя файла для использования графа: ";
    std::cin >> filename;

    if (!readGraph(filename, edges, n)) {
        std::cout << "Создание пустого графа. Введите количество вершин: ";
        n = getIntInput();
    }

    while (true) {
        int choice;
        int u, v;

        std::cout << "\n===== МЕНЮ =====" << std::endl;
        std::cout << "1. Показать граф" << std::endl;
        std::cout << "2. Добавить ребро" << std::endl;
        std::cout << "3. Удалить ребро" << std::endl;
        std::cout << "4. Сохранить граф в файл" << std::endl;
        std::cout << "5. Сохранить как матрицу смежности" << std::endl;
        std::cout << "0. Выход из программы" << std::endl;
        std::cout << "Ваш выбор: ";

        choice = getIntInput();

        if (choice == 0) {
            std::cout << "Программа завершена.\n";
            break;
        }

        switch (choice) {
            case 1:
                printAdjList(edges, n);
                break;
            case 2:
                std::cout << "Введите вершины (u v): ";
                u = getValInput();
                v = getValInput();
                if (u >= 0 && u < n && v >= 0 && v < n) {
                    addEdge(edges, u, v);
                } else {
                    std::cout << "Ошибка: вершины должны быть в диапазоне [0, " << n-1 << "]" << std::endl;
                }
                break;
            case 3:
                std::cout << "Введите вершины (u v): ";
                u = getValInput();
                v = getValInput();
                if (u >= 0 && u < n && v >= 0 && v < n) {
                    removeEdge(edges, u, v);
                } else {
                    std::cout << "Ошибка: вершины должны быть в диапазоне [0, " << n-1 << "]" << std::endl;
                }
                break;
            case 4:
                std::cout << "Введите имя файла для сохранения: ";
                std::cin >> filename;
                saveGraph(filename, edges, n);
                break;
            case 5:
                std::cout << "Введите имя файла для сохранения матрицы: ";
                std::cin >> filename;
                saveAsMatrix(filename, edges, n);
                break;
            default:
                std::cerr << "Неверный выбор! Пожалуйста, выберите 0-5.\n";
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
