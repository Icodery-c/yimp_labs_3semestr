#include <iostream>
#include <iomanip>
#include <limits>

struct TreeNode {

	int value;

	TreeNode *left;
	TreeNode *right;

};

TreeNode* CreateNode (int value) {

	TreeNode * node = new TreeNode;
	node->value = value;
	node->left = nullptr;
	node->right = nullptr;
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
	TreeNode* root = nullptr;

	int N;
	int value;

	std::cout << "Введите кол-во элементов: ";
	N = getIntInput();

	std::cout << "Введите элементы бинарного дерева:" << std::endl;

	for (int i = 0; i < N; i++) {
			value = getValInput();
			TreeNode* result = insertRecursive(root, value);

			if (result == nullptr) {
					std::cout << "Элемент " << value << " уже существует в дереве и не был добавлен." << std::endl;
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

            default:
                std::cerr << "Неверный выбор! Пожалуйста, выберите 0-2.\n";
                continue;
        }
    }

    DeleteTree(root);
    return 0;
}
