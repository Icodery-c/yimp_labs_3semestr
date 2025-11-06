#include <iostream>
#include <iomanip>
#include <limits>
#include <climits>
#include <cmath>
#include <string>
#include <fstream>
#include <random>
#include <chrono>

struct TreeNode {

	int value;

	TreeNode* parent;

	TreeNode *left;
	TreeNode *right;


};

TreeNode* CreateNode (int value) {

	TreeNode * node = new TreeNode;

	node->value = value;

	node->left = nullptr;
	node->right = nullptr;

	node->parent = nullptr;

	return node;

}

void DeleteTree (TreeNode* root) {

	if (!root) { return; }

	DeleteTree (root->left);
	DeleteTree (root->right);

	delete root;
}

TreeNode* insertRecursive(TreeNode* root, int value) {
    if (!root)
        return CreateNode(value);

    if (value < root->value) {
        TreeNode* result = insertRecursive(root->left, value);
        if (result == nullptr) return nullptr;
        root->left = result;
    }
    else if (value > root->value) {
        TreeNode* result = insertRecursive(root->right, value);
        if (result == nullptr) return nullptr;
        root->right = result;
    }
    else {
        return nullptr;
    }

    return root;
}

TreeNode* searchRecursive(TreeNode* root, int value) {
    if (root == nullptr || root->value == value)
        return root;

    if (value < root->value)
        return searchRecursive(root->left, value);
    else
        return searchRecursive(root->right, value);
}

TreeNode* searchIterative(TreeNode* root, int value) {
    TreeNode* current = root;
    while (current != nullptr && current->value != value) {
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}

void preorderTravesal (TreeNode* root) {

	if (root) {

		std::cout << root->value << " ";
                preorderTravesal(root->left);
                preorderTravesal(root->right);

        }

}

void inorderTravesal (TreeNode* root) {

	if (root) {

		inorderTravesal(root->left);
		std::cout << root->value << " ";
		inorderTravesal(root->right);

	}
}

void postorderTravesal (TreeNode* root) {

	if (root) {

		postorderTravesal(root->left);
		postorderTravesal(root->right);
		std::cout << root->value << " ";

	}
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

int getValInput() {
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод. Пожалуйста, введите число: ";
    }
    return value;
}

void Procedure1 (TreeNode* root) {

	if (!root) { return; }

	if (!root->left	&& !root->right) { std::cout << root->value << " "; }

	Procedure1(root->left);
	Procedure1(root->right);

}

void Procedure2 (TreeNode* root, int k) {

	if (!root) { return; }

	if (k == 0) { std::cout << root->value << " "; }

	else {
		Procedure2(root->left, k-1);
		Procedure2(root->right, k-1);
	}
}

void Procedure3 (TreeNode* root, int k = 0) {

	if (!root) { return; }

	std::cout << std::string(k * 4, ' ') << root->value << std::endl;

	Procedure3(root->left, k + 1);
	Procedure3(root->right, k + 1);


}

int Procedure4 (TreeNode* root) {

	if (!root) { return 0; }

	if (!root->left && !root->right) { return 1; }

	return Procedure4(root->left) + Procedure4(root->right);

}

int Procedure5 (TreeNode* root) {

	if (!root) { return 0; }

	if (!root->left && !root->right) { return root->value; }

	return Procedure5(root->left) + Procedure5(root->right);

}

int Procedure6 (TreeNode* root, int k) {

	if (!root) { return 0; }

	if (k == 0) { return 1; }

	return Procedure6(root->left, k - 1) + Procedure6(root->right, k - 1);


}

int Procedure7 (TreeNode* root, int k) {

	if (!root) { return INT_MIN; }

	if (k == 0) { return root->value; }

	return std::max(Procedure7(root->left, k - 1), Procedure7(root->right, k - 1));
}

int Procedure8 (TreeNode* root, int k) {

	if (!root) { return 0; }

	if (k == 0) { return root->value; }

	return Procedure8(root->left, k - 1) + Procedure8(root->right, k - 1);

}

int Procedure9Sum(TreeNode* root) {
    if (!root) { return 0; }
    return root->value + Procedure9Sum(root->left) + Procedure9Sum(root->right);
}

TreeNode* Procedure9Find(TreeNode* root, int target) {
    if (!root) {
        return nullptr;
    }

    // Вычисляем сумму текущего поддерева
    int sum = Procedure9Sum(root);

    // Отладочная информация
    std::cout << "Проверяем узел " << root->value << ", сумма поддерева: " << sum << std::endl;

    if (sum == target) {
        std::cout << "\n!!! Поддерево с суммой " << target << " найдено. Корень: " << root->value << std::endl;
        std::cout << "Структура поддерева:" << std::endl;
        Procedure3(root);
        std::cout << "-----------------------------" << std::endl;
        return root;
    }

    // Ищем в левом поддереве
    std::cout << "Ищем в левом поддереве узла " << root->value << std::endl;
    TreeNode* left = Procedure9Find(root->left, target);
    if (left) {
        return left;
    }

    // Ищем в правом поддереве
    std::cout << "Ищем в правом поддереве узла " << root->value << std::endl;
    TreeNode* right = Procedure9Find(root->right, target);
    if (right) {
        return right;
    }

    return nullptr;
}

int Procedure10 (TreeNode* root) {

	if (!root) return 0;

	return 1 + std::max(Procedure10(root->left), Procedure10(root->right));

}

int Procedure11(TreeNode* root, int current, int maxDepth, std::string path = "") {
    if (!root) return 0;

    if (!path.empty()) path += " -> ";
    path += std::to_string(root->value);

    if (!root->left && !root->right) {
        if (current == maxDepth) {
            std::cout << "Ветвь макс. длины: " << path << std::endl;
            return 1;
        }
        return 0;
    }

    return Procedure11(root->left, current + 1, maxDepth, path) +
           Procedure11(root->right, current + 1, maxDepth, path);
}

bool Procedure12 (TreeNode* root, int& height) {

	if (!root) { height = 0; return true; }

	int lh, rh;

	bool leftFlag = Procedure12(root->left, lh);
	bool rightFlag = Procedure12(root->right, rh);

	height = std::max(lh, rh) + 1;

	return	std::abs(lh - rh) <= 1 && leftFlag && rightFlag;

}

bool Procedure13 (TreeNode* root, int target) {

	if (!root) { return false; }

	std::cout << root->value << " ";

	if (root->value == target && !root->left && !root->right) { return true; }

	if (Procedure13(root->left, target) || Procedure13(root->right, target)) { return true; }

	std::cout << "\b\b";
	return false;

}

void Procedure14(TreeNode* root, std::ofstream& out, int level = 0) {

		if (!root) return;

		out << std::string(level * 4, ' ') << root->value << std::endl;

		Procedure14(root->left, out, level + 1);
    Procedure14(root->right, out, level + 1);

}

TreeNode* LCA(TreeNode* root, int a, int b) {
    if (!root) return nullptr;
    if (root->value == a || root->value == b) return root;

    TreeNode* left = LCA(root->left, a, b);
    TreeNode* right = LCA(root->right, a, b);

    if (left && right) return root;
    return left ? left : right;
}

int distance(TreeNode* root, int val, int depth = 0) {
    if (!root) return -1;
    if (root->value == val) return depth;
    int left = distance(root->left, val, depth + 1);
    if (left != -1) return left;
    return distance(root->right, val, depth + 1);
}

int Procedure15(TreeNode* root, int a, int b) {
    TreeNode* lca = LCA(root, a, b);
    if (!lca) return -1;
    return distance(lca, a) + distance(lca, b);
}

int main() {
	TreeNode* root = nullptr;

	int N;
	int value;

	std::cout << "Введите кол-во элементов: ";
	N = getIntInput();



	//std::cout << "Введите элементы бинарного дерева:" << std::endl;

	for (int i = 0; i < N; i++) {
    // Генерация случайного числа
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(-100, 100);
    value = distribution(generator);

    TreeNode* result = insertRecursive(root, value);

    if (result == nullptr) {
        std::cout << "Элемент " << value << " уже существует в дереве и не был добавлен." << std::endl;
        i--;
    } else {
        root = result;
        std::cout << "Элемент " << value << " успешно добавлен." << std::endl;
    }
	}


    while (true) {
        int mainChoice;

        std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
        std::cout << "1. Обход дерева" << std::endl;
        std::cout << "2. Поиск в дереве" << std::endl;
				std::cout << "3. Процедуры " << std::endl;
        std::cout << "0. Выход из программы" << std::endl;
        std::cout << "Ваш выбор: ";

        mainChoice = getIntInput();

        if (mainChoice == 0) {
            std::cout << "Программа завершена.\n";
            break;
        }

        switch (mainChoice) {
            case 1: {
                while (true) {
                    int traversalChoice;

                    std::cout << "\nВыберите метод обхода:" << std::endl;
                    std::cout << "1. Прямой обход" << std::endl;
                    std::cout << "2. Симметричный обход" << std::endl;
                    std::cout << "3. Обратный обход" << std::endl;
                    std::cout << "0. Назад в главное меню" << std::endl;
                    std::cout << "Ваш выбор: ";

                    traversalChoice = getIntInput();

                    if (traversalChoice == 0) {
                        break;
                    }

                    switch (traversalChoice) {
                        case 1:
                            std::cout << "Прямой обход по бинарному дереву:" << std::endl;
                            preorderTravesal(root);
                            std::cout << std::endl;
                            break;

                        case 2:
                            std::cout << "Симметричный обход по бинарному дереву:" << std::endl;
                            inorderTravesal(root);
                            std::cout << std::endl;
                            break;

                        case 3:
                            std::cout << "Обратный обход по бинарному дереву:" << std::endl;
                            postorderTravesal(root);
                            std::cout << std::endl;
                            break;

                        default:
                            std::cerr << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
                            continue;
                    }
                }
                break;
            }

            case 2: {
                while (true) {
                    int searchChoice;
                    int val;
                    TreeNode* found = nullptr;

                    std::cout << "\nВыберите метод поиска:" << std::endl;
                    std::cout << "1. Итеративный поиск" << std::endl;
                    std::cout << "2. Рекурсивный поиск" << std::endl;
                    std::cout << "0. Назад в главное меню" << std::endl;
                    std::cout << "Ваш выбор: ";

                    searchChoice = getIntInput();

                    if (searchChoice == 0) {
                        break;
                    }

                    if (searchChoice == 1 || searchChoice == 2) {
                        std::cout << "Введите элемент для поиска: ";
                        val = getValInput();

                        if (searchChoice == 1) {
                            found = searchIterative(root, val);
                        } else {
                            found = searchRecursive(root, val);
                        }

                        if (found)
                            std::cout << "Элемент " << val << " найден в дереве.\n";
                        else
                            std::cout << "Элемент " << val << " не найден в дереве.\n";
                    } else {
                        std::cerr << "Неверный выбор! Пожалуйста, выберите 0-2.\n";
                    }
                }
                break;
            }

						case 3: {

							while (true) {


				        int procedureChoice;

								int k;

								int depth;

								int count;

								int h;

								int s;

								int l;

								TreeNode* f;

								int a, b;

								//std::ofstream file("tree.txt");


				        std::cout << "\nВыберите процедуру, которой вы хотите воспользоватся:" << std::endl;
				        std::cout << "1. Распечатать все концевые элементы (листья)" << std::endl;
				        std::cout << "2. Распечатать элементы, лежащие на уровне k" << std::endl;
				        std::cout << "3. Модифицируйте функции печати из задачи 3-3-5 так, чтобы элементы к-го уровня располагались в k-м столбце." << std::endl;
				        std::cout << "4. Вычислить кол-во концевых элементов (листьев)" << std::endl;
				        std::cout << "5. Вычислить сумму концевых элементов (листьев)" << std::endl;
				        std::cout << "6. Определить кол-во элементов, лежащих на уровне k" << std::endl;
				        std::cout << "7. Найти максимальный элемент среди всех элементов k-го уровня" << std::endl;
				        std::cout << "8. Вычислить сумму элементов, лежащих на уровне k" << std::endl;
				        std::cout << "9. Найти поддерево, для которого сумма элементов совпадает с указанным числом" << std::endl;
				        std::cout << "10. Определить глубину дерева (т. е. длину максимальной ветви)" << std::endl;
				        std::cout << "11. Определить количество ветвей, имеющих максимальную длину " << std::endl;
				        std::cout << "12. Проверить, является ли бинарное дерево идеально сбалансированным." << std::endl;
				        std::cout << "13. Распечатать ветвь дерева (исходящую из корня) с заданным значением листа" << std::endl;
				        std::cout << "14. Вывести наглядное представление дерева целых чисел в текстовой файл" << std::endl;
				        std::cout << "15. Определить длину связного пути между двумя вершинами с заданными значениями неупорядоченного дерева" << std::endl;
				        std::cout << "0. Назад в главное меню" << std::endl;
				        std::cout << "Ваш выбор: ";

				        procedureChoice = getIntInput();

				        if (procedureChoice == 0) { break; }

				        switch (procedureChoice) {
				          case 1:
										std::cout << "Конечные элементы (листья): ";
										Procedure1(root);
										std::cout << std::endl;
				            break;
				          case 2:
										std::cout << "Введите уровень k, чтобы вывести элементы на этом уровне: ";
										k = getIntInput();

										depth = Procedure10(root);

										if (k < 0 || k >= depth) {
    										std::cout << "Ошибка: уровень k выходит за пределы глубины дерева ("
         								<< depth - 1 << ")." << std::endl;
										} else {
    										std::cout << "Элементы на уровне " << k << ": ";
    										Procedure2(root, k);
    										std::cout << std::endl;
										}
				            break;
				          case 3:
										//std::cout << "Введите уровень k, чтобы вывести элементы на этом уровне: ";
										// k = getIntInput();
										//
										// depth = Procedure10(root);
										//
										// if (k < 0 || k >= depth) {
										// 	std::cout << "Ошибка: уровень k выходит за пределы глубины дерева ("
										// 	<< depth - 1 << ")." << std::endl;
										// } else {
										// 	std::cout << "Элементов на уровне " << k << ": ";
										// 	Procedure3(root, k);
										// 	std::cout << std::endl;
										// }

										Procedure3(root);
				            break;
				          case 4:
										std::cout << "Количество концевых элементов (листьев): " << Procedure4(root) << std::endl;
				            break;
				          case 5:
										std::cout << "Сумма концевых элементов (листьев): " << Procedure5(root) << std::endl;
				            break;
				          case 6:
										std::cout << "Введите уровень k, чтобы определить количество элементов на этом уровне: ";
										k = getIntInput();

										depth = Procedure10(root);

										if (k < 0 || k >= depth) {
											std::cout << "Ошибка: уровень k выходит за пределы глубины дерева ("
											<< depth - 1 << ")." << std::endl;
										} else {
												std::cout << "Количество элементов на уровне " << k << ": ";
												std::cout << Procedure6(root, k);
												std::cout << std::endl;
											}
				            break;
				          case 7:
										std::cout << "Введите уровень k, чтобы определить максмальный элемент на этом уровне: ";
										k = getIntInput();

										depth = Procedure10(root);

										if (k < 0 || k >= depth) {
											std::cout << "Ошибка: уровень k выходит за пределы глубины дерева ("
											<< depth - 1 << ")." << std::endl;
										} else {
											std::cout << "Максимальный элемент на уровне " << k << ": ";
											std::cout << Procedure7(root, k);
											std::cout << std::endl;
										}
				            break;
				          case 8:
										std::cout << "Введите уровень k, чтобы определить сумму элементов на этом уровне: ";
										k = getIntInput();

										depth = Procedure10(root);

										if (k < 0 || k >= depth) {
											std::cout << "Ошибка: уровень k выходит за пределы глубины дерева ("
											<< depth - 1 << ")." << std::endl;
										} else {
											std::cout << "Сумма элементов на уровне " << k << ": ";
											std::cout << Procedure8(root, k);
											std::cout << std::endl;
										}
				            break;
				          case 9:
										std::cout << "Введите число, которое является суммой поддерева: ";
										s = getValInput();

										f = Procedure9Find(root, s);

										if (!f) { std::cout << "Поддерево с суммой " << s << " не найдено." << std::endl; }


				            break;
				          case 10:
										std::cout << "Максимальная глубина дерева: " << Procedure10(root) << std::endl;
				            break;
				          case 11:
										depth =  Procedure10(root);
										std::cout << "Максимальная глубина дерева: " << depth << std::endl;

										count = Procedure11(root, 1, depth);
										std::cout << "Количество ветвей макс. длины: " << count << std::endl;
				            break;
				          case 12:
										std::cout << "\n12. Сбалансировано: " << (Procedure12(root, h) ? "Да" : "Нет");
				            break;
				          case 13:
										std::cout << "Конечные элементы (листья): ";
										Procedure1(root);
										std::cout << std::endl;
										std::cout << "Выберите конечный элемент, для которого вы хотите найти путь (ветвь) до заданного листа: ";

										l = getValInput();

										std::cout << std::endl << "Путь до листа со значением " << l << ": ";

										std::cout << Procedure13(root,l) << std::endl;

				            break;

										case 14: {
									    std::ofstream file("tree.txt");
									    if (!file.is_open()) {
									        std::cout << "\nОшибка: не удалось открыть файл tree.txt для записи";
									        break;
									    }
									    Procedure14(root, file);
									    file.close();
									    std::cout << "\n14. Дерево сохранено в tree.txt";
									    break;
										}

				            break;
				          case 15:
										std::cout << "Вершины данного деревья: ";
										inorderTravesal(root);
										std::cout << std::endl;

										std::cout << "Введите первую вершину: ";
										a = getValInput();
										std::cout << std::endl;

										std::cout << "Введите вторую вершину: ";
										b= getValInput();
										std::cout << std::endl;

										std::cout << "Расстояние между вершинами " << a << " " << b << " = " << Procedure15(root, a, b) << std::endl;

				            break;

									default:
					           std::cerr << "Неверный выбор! Пожалуйста, выберите 0-15.\n";
					           continue;

						}
        	}
    	}

			default:
					std::cerr << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
					continue;

		}
	}

    DeleteTree(root);

		return 0;
}
