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

		int choice;

		std::cout << "Выберите метод обхода:" << std::endl;
		std::cout << "1. Прямой обход" << std::endl;
	  std::cout << "2. Симметричный обход" << std::endl;
	  std::cout << "3. Обратный обход" << std::endl;
		std::cout << "0) Выход из программы" << std::endl;
		std::cout << "Ваш выбор: ";

		choice = getIntInput();

		if (choice == 0) {
				std::cout << "Программа завершена.\n";
				break;
		}

		switch (choice) {

			case 1:
				std::cout << "Прямой обход по бинарному дереву:" << std::endl;
				preorderTravesal(root);
				break;

			case 2:
				std::cout << "Симметричный обход по бинарному дереву:" << std::endl;
				inorderTravesal(root);
				break;

			case 3:
				std::cout << "Обратный обход по бинарному дереву:" << std::endl;
				postorderTravesal(root);
				break;

			default:
				std::cerr << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
				continue;


		}

		while (true) {
				std::cout << "\nХотите воспользоваться другим методом обхода? (y/n): ";
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

	DeleteTree(root);

	return 0;

}
