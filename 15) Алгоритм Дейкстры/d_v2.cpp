#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>

using namespace std;
int count_vertex, count_edges, trudoemkost = 0;
vector <int> p;
vector <int> vershiny;

struct edge {
    int x, y, w;
};

int search_index_min(vector <int> m) {
    int index = 0;
    int min = m[0];
    for (int i = 1; i < m.size(); i++) {
        if (m[i] < min) {
            min = m[i];
            index = i;
        }
    }
    return index;
}

vector <int> raznost(vector <int> a, vector <int> b) {
    vector <int> c;
    vector <int>::iterator it;
    for (int i = 1; i < a.size(); i++) {
        if (find(a.begin(), a.end(), a[i]) != a.end() && find(b.begin(), b.end(), a[i]) == b.end()) {
            it = find(a.begin(), a.end(), a[i]);
            c.push_back(it[0]);
        }
    }
    return c;
}

int cost_of_transit(vector <edge> e, int x, int y) {
    if (x == y) return 0;
    for (int i = 0; i < count_edges; i++) {
        if ((x == e[i].x && y == e[i].y) || (x == e[i].y && y == e[i].x)) {
            return e[i].w;
        }
    }
    return (int) pow(10, 5);
}

bool equal_check(vector <int> a, vector <int> b) {
    int count = 0;
    if (a.size() == b.size()) {
        for (int i = 0; i < a.size(); i++) {
            if (find(b.begin(), b.end(), a[i]) != b.end()) count++;
        }
        if (count == a.size()) return true;
        else return false;
    }
    else return false;
}

vector <int> deikstra(vector <edge> e) {
    vector <int> S, D(count_vertex + 1), v_s, weights;
    S.push_back(1);
    for (int i = 1; i <= count_vertex; i++) {
        D[i] = cost_of_transit(e, 1, i);
        if (i != count_vertex) p[i + 1] = 1;
    }
    v_s = raznost(vershiny, S);
    while (!equal_check(vershiny, S)) {
        trudoemkost++;
        for (int i = 0; i < v_s.size(); i++) {
            weights.push_back(D[v_s[i]]);
        }
        int index = search_index_min(weights);
        int w = v_s[index];
        S.push_back(w);
        v_s = raznost(vershiny, S);
        for (int i = 0; i < v_s.size(); i++) {
            trudoemkost += 2;
            int cost = cost_of_transit(e, w, v_s[i]);
            if (D[v_s[i]] < D[w] + cost) continue;
            else {
                D[v_s[i]] = D[w] + cost;
                p[v_s[i]] = w;
            }
        }
        weights.clear();
    }
    return D;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    fscanf(file, "%d %d", &count_edges, &count_vertex);
    vector <edge> edges(count_edges);
    vector <int> length_paths, path;
    vershiny.resize(count_vertex);
    p.resize(count_vertex + 1);
    for (int i = 0; i < count_vertex; i++) {
        vershiny[i] = i + 1;
    }
    int temp = 0;
    while (!feof(file)) {
        fscanf(file, "%d %d %d", &edges[temp].x, &edges[temp].y, &edges[temp].w);
        temp++;
    }
    length_paths = deikstra(edges);
    printf("Source graph: \n");
    for (int i = 0; i < count_edges; i++) {
        printf("[%d,%d] %d\n", edges[i].x, edges[i].y, edges[i].w);
    }
    printf("\n");
    for (int i = 2; i <= count_vertex; i++) {
        // Start - 1; Vertex - i; weight - length_paths[i];
        for (int k = i; ; k = p[k]) {
            path.push_back(k);
            if (k == 0) break;
        }
        reverse(path.begin(), path.end());
        printf("Path from 1 to %d: ", i);
        for (int k = 1; k < path.size(); k++) {
            printf("%d ", path[k]);
            if (k != path.size() - 1) printf(" ");
        }
        printf("\n");
        path.clear();
    }
    printf("Operations: %d\n", trudoemkost);

    return 0;
}
