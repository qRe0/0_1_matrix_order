#include <iostream>
#include <vector>
#include <fstream>
#include <climits> // Для использования INT_MAX

using namespace std;

int main() {
    ifstream input("input.txt"); // Открываем файл "input.txt" для чтения
    ofstream output("output.txt"); // Открываем файл "output.txt" для записи результатов

    int num_matrices; // Количество матриц
    input >> num_matrices; // Читаем количество матриц из файла

    vector<pair<int, int>> matrix_sizes(num_matrices); // Создаем вектор пар (ширина, высота) матриц
    for (int i = 0; i < num_matrices; i++) {
        input >> matrix_sizes[i].first >> matrix_sizes[i].second; // Читаем размеры каждой матрицы из файла
    }

    vector<vector<int>> dp(num_matrices, vector<int>(num_matrices, INT_MAX)); // Создаем двумерный вектор для хранения результатов вычислений

    // Инициализируем диагональ элементов dp нулями, так как умножение матрицы на саму себя не требует операций
    for (int i = 0; i < num_matrices; i++) {
        dp[i][i] = 0;
    }

    // Рассматриваем длины последовательных подотрезков матриц, начиная с коротких и постепенно увеличивая длину
    for (int length = 2; length <= num_matrices; length++) {
        for (int i = 0; i <= num_matrices - length; i++) {
            int j = i + length - 1;

            // Находим оптимальное место для разбиения последовательности матриц на два подотрезка
            for (int k = i; k < j; k++) {
                // Сравниваем и обновляем dp[i][j], выбирая минимальную стоимость разбиения
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + matrix_sizes[i].first * matrix_sizes[k].second * matrix_sizes[j].second);
            }
        }
    }

    // Выводим результат (минимальную стоимость объединения всех матриц) в файл "output.txt"
    output << dp[0][num_matrices - 1] << endl;

    input.close(); // Закрываем файлы
    output.close();

    return 0;
}
