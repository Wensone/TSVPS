#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

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
   	ifstream fin("input.txt");

   	fin >> W >> N;
   	for(int i = 0; i < N; i++){
   		int tmp;
   		fin >> tmp;
   		masses.push_back(tmp);
   		fin >> tmp;
   		costs.push_back(tmp);
   	}

    double max_cost = task_about_bag(masses, costs, W, N);
// set[i] + 1 == продукт по счету
    for (int i = 0; i < set.size(); i++) {
        printf("Weight\t\t %d\t\t Сost\t\t %d\n", masses[set[i]], (int)costs[set[i]]);
    }
    cout << "----------------------------------" << endl;
    printf("Total weight %d\t\t Total cost %d\n", W, (int)max_cost);


    printf("\nOperations: %d\n\n", trudoemkost);
    
    return 0;
}