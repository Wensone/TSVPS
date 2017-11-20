#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
int ind, trudoemkost = 0;
vector <int> set;

int search_min(vector <int> m) {
    int min = m[0];
    for (int i = 1; i < m.size(); i++) {
        if (m[i] < min) min = m[i];
    }
    return min;
}

double search_max(vector <double> m) {
    double max = m[0];
    for (int i = 1; i < m.size(); i++) {
        if (m[i] > max) {
            max = m[i];
            ind = i;
        }
    }
    return max;
}

vector <int> get_set_products(vector <int> prev, vector <int> m, int W) {
    vector <int> indexes;
    int weight = W;
    while (weight != 0) {
        int temp = m[prev[weight]];
        if (weight - temp < 0) break;
        indexes.push_back(prev[weight]);
        weight -= temp;
    }
    return indexes;
}

double task_about_bag(vector <int> m, vector <double> c, int W, int n) {
    vector <double> f, sums;
    vector <int> prev;
    int min_mass = search_min(m);
    for (int i = 0; i < W; i++) {
        if (i < min_mass) {
            f.push_back(0);
            prev.push_back(0);
        }
        else break;
    }
    for (size_t i = f.size(); i <= W; i++) {
        trudoemkost++;
        for (int k = 0; k < n; k++) {
            trudoemkost++;
            int temp = i - m[k];
            if (temp < 0) sums.push_back(-1);
            else sums.push_back(f[i - m[k]] + c[k]);
        }
        double max = search_max(sums);
        prev.push_back(ind);
        f.push_back(max);
        sums.clear();
        ind = 0;
    }
    set = get_set_products(prev, m, W);
    return f[f.size() - 1];
}

int main() {
    int W, N;
    char ch;
    int num;
    double num_1;
    vector <int> masses;
    vector <double> costs;
    FILE *file = fopen("input.txt", "r");
    fscanf(file, "%d %d", &W, &N);
    while (!feof(file)) {
        fscanf(file, "%d", &num);
        masses.push_back(num);
        ch = getc(file);
        if (ch == '\n') {
            while (!feof(file)) {
                fscanf(file, "%lf", &num_1);
                costs.push_back(num_1);
            }
        }
    }
    double max_cost = task_about_bag(masses, costs, W, N);
    printf("Carrying capacity W: %d, count of products N: %d\n\n", W, N);
    printf("Masses: ");
    for (int i = 0; i < masses.size(); i++) {
        printf("%lf ", (double) masses[i]);
    }
    printf("\nCosts: ");
    for (int i = 0; i < costs.size(); i++) {
        printf("%lf ", costs[i]);
    }
    printf("\n\nIn set include:\n");
    for (int i = 0; i < set.size(); i++) {
        printf("%d) %d product with m = %d, c = %lf\n", i + 1, set[i] + 1, masses[set[i]], costs[set[i]]);
    }
    printf("\nMaximum cost for current W: %lf\n\n", max_cost);
    printf("Trudoemkost: %d\n\n", trudoemkost);
    system("pause");
}