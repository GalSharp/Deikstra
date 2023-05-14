#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

const int INF = std::numeric_limits<int>::max();

void dijkstra(std::vector<std::vector<int>>& adj_matrix, int start, int end, std::vector<int>& result) {
    int n = adj_matrix.size();
    std::vector<int> fiks(n, 0);
    std::vector<int> min_weg(n, INF);
    std::vector<int> von_punkt(n, start);

    min_weg = adj_matrix[start];
    fiks[start] = 1;
    min_weg[start] = 0;

    for (int i = 1; i < n; ++i) {
        int min_weg_index = -1;
        for (int j = 0; j < n; ++j) {
            if (fiks[j] == 0 && (min_weg_index == -1 || min_weg[j] < min_weg[min_weg_index])) {
                min_weg_index = j;
            }
        }

        if (min_weg_index == -1) {
            break;
        }

        fiks[min_weg_index] = 1;

        for (int k = 0; k < n; ++k) {
            if (adj_matrix[min_weg_index][k] != INF && min_weg[min_weg_index] + adj_matrix[min_weg_index][k] < min_weg[k]) {
                min_weg[k] = min_weg[min_weg_index] + adj_matrix[min_weg_index][k];
                von_punkt[k] = min_weg_index;
            }
        }
    }

    result.clear();
    int current = end;
    while (current != start) {
        result.push_back(current);
        current = von_punkt[current];
    }
    result.push_back(start);
    std::reverse(result.begin(), result.end());
}

// Входные данные
int main() {

    system("chcp 1251");
    system("cls");

    std::ifstream file("матрица.txt");
    std::vector<std::vector<int>> adj_matrix;
    int n;
    file >> n;
    adj_matrix.resize(n);
    for (int i = 0; i < n; ++i) {
        adj_matrix[i].resize(n);
        for (int j = 0; j < n; ++j) {
            file >> adj_matrix[i][j];
            if (adj_matrix[i][j] == -1) {
                adj_matrix[i][j] = INF;
            }
        }
    }

    int start, end;

    std::cout << "Введите стартовую вершину" << std::endl;
    std::cin >> start;
    std::cout << "Введите конечную вершину" << std::endl;
    std::cin >> end;

    std::vector<int> result;
    dijkstra(adj_matrix, start - 1, end - 1, result);

    std::ofstream output_file("результаты.txt");

    output_file << "Кратчайший путь от " << start << " до " << end << ": ";
    for (int i = 0; i < result.size(); ++i) {
        output_file << result[i];
        if (i < result.size() - 1) {
            output_file << " -> ";
        }
    }
    output_file << std::endl;

    std::cout << "Кратчайший путь от " << start << " до " << end << ": ";
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] + 1;
        if (i < result.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    return 0;
}