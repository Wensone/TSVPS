#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;
int count_vertex, count_edges, trudoemkost = 0;

struct edge {
    int x, y, w;
};

vector <int> links;

bool comparator_weight(edge &a, edge &b) {
    return a.w < b.w;
}

int get_links(int vertex) {
    trudoemkost++;
    if (vertex == links[vertex]) return vertex;
    return get_links(links[vertex]);
}

int union_vertex(int vertex_1, int vertex_2) {
    vertex_1 = get_links(vertex_1);
    vertex_2 = get_links(vertex_2);
    trudoemkost++;
    if (vertex_1 == vertex_2) return 0;
    if (vertex_2 > vertex_1) swap(vertex_1, vertex_2);
    trudoemkost++;
    links[vertex_1] = vertex_2;
    return 1;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    fscanf(file, "%d %d", &count_edges, &count_vertex);
    vector <edge> e(count_edges);
    int temp = 0;
    while (!feof(file)) {
        fscanf(file, "%d %d %d", &e[temp].x, &e[temp].y, &e[temp].w);
        temp++;
    }
    for (int i = 0; i < count_edges; i++) {
        e[i].x--;
        e[i].y--;
    }
    sort(e.begin(), e.end(), comparator_weight);
    links.resize(count_vertex);
    for (int i = 0; i < count_vertex; i++) {
        links[i] = i;
    }
    vector <edge> result;
    for (int i = 0; i < count_edges; i++) {
        int x = e[i].x, y = e[i].y;
        if (union_vertex(x, y) == 1) {
            trudoemkost++;
            result.push_back(e[i]);
        }
    }
    int sum_of_weights = 0;
    for (int i = 0; i < result.size(); i++) {
        sum_of_weights += result[i].w;
    }
    printf("Source graph:\n");
    for (int i = 0; i < e.size(); i++) {
        printf("V1: %d V2: %d w: %d\n", e[i].x + 1, e[i].y + 1, e[i].w);
    }
    printf("\n");
    printf("Ostov tree:\n");
    for (int i = 0; i < result.size(); i++) {
        printf("V1: %d V2: %d weight: %d\n", result[i].x + 1, result[i].y + 1, result[i].w);
    }
    printf("\nSum of weights of ostov tree: %d\n\n", sum_of_weights);
    printf("Trudoemkost: %d\n", trudoemkost);
    return 0;
}