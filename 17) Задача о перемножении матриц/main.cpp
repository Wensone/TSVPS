#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n, last_i, last_j;

vector <int> search_position(string str) {
    vector <int> pos(n + 1);
    int temp = 1;
    for (int i = 1; i < str.size(); i++) {
        int num = str[i] - '0';
        if (num == temp) {
            pos[temp++] = i + 1;
        }
    }
    return pos;
}

string bracket_alignment(string &str, int a, int b, vector <int> **indexes) {
    vector <int> pos(n + 1);
    pos = search_position(str);
    last_i = indexes[a][b][2], last_j = indexes[a][b][3];
    while (a != b) {
        for (int i = 0; i < indexes[a][b].size(); i += 2) {
            int sk_1 = indexes[a][b][i];
            int sk_2 = indexes[a][b][i + 1];
            if (sk_1 == sk_2) continue;
            str.insert(pos[sk_1] - 2, "(");
            str.insert(pos[sk_2] + 1, ")");
            pos = search_position(str);
        }
        int ind_1 = indexes[a][b][0], ind_2 = indexes[a][b][1];
        a = ind_1, b = ind_2;
    }

    return str;
}

string task_multiply_matrix(vector <int> sizes, int *optimal_trud) {
    string str;
    int minimum;
    vector <int> **indexes;
    indexes = new vector <int> *[n + 1];
    for (int i = 0 ; i <= n; i++) indexes[i] = new vector <int> [2 * n - 1];
    int f[n + 1][2 * n - 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            f[i][j] = 0;
        }
    }
    for (int t = 1; t < n; t++) {
        for (int k = 1; k < n; k++) {
            if (k + t <= n) {
                last_i = k, last_j = k + t;
                for (int j = k; j <= k + t - 1; j++) {
                    int opt_trud = f[k][j] + f[j + 1][k + t] + sizes[k - 1] * sizes[j] * sizes[k + t];
                    if (j == k) {
                        minimum = opt_trud;
                        indexes[k][k + t].push_back(k);
                        indexes[k][k + t].push_back(j);
                        indexes[k][k + t].push_back(j + 1);
                        indexes[k][k + t].push_back(k + t);
                    }
                    if (j != k && opt_trud < minimum) {
                        minimum = opt_trud;
                        indexes[k][k + t].clear();
                        indexes[k][k + t].push_back(k);
                        indexes[k][k + t].push_back(j);
                        indexes[k][k + t].push_back(j + 1);
                        indexes[k][k + t].push_back(k + t);
                    }
                }
                f[k][k + t] = minimum;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        str += "m";
        str += to_string(i);
        if (i != n) str += "*";
    }
    *optimal_trud = f[last_i][last_j];
    if (last_i != last_j) str = bracket_alignment(str, last_i, last_j, indexes);
    if (last_i != last_j) str = bracket_alignment(str, last_i, last_j, indexes);
    return str;
}

int main() {
    string str;
    int index = 0, opt_trud = 0;
    FILE *file = fopen("input", "r");
    fscanf(file, "%d", &n);
    pair <int, int> sizes[n];
    while (!feof(file)) {
        fscanf(file, "%d %d", &sizes[index].first, &sizes[index].second);
        index++;
    }

    vector <int> size_matrix;
    for (int i = 0; i < n; i++) size_matrix.push_back(sizes[i].first);
    size_matrix.push_back(sizes[n - 1].second);
    str = task_multiply_matrix(size_matrix, &opt_trud);
    printf("\n");
    printf("Bracket: %s\nOperations: %d\n\n", str.c_str(), opt_trud);

    return 0;
}
    // printf("Dimensions:\n");
    /*for (int i = 0; i < n; i++) {printf("%d %d\n", sizes[i].first, sizes[i].second);}*/