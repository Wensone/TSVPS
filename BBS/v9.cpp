#include <cstdio>
#include <climits>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

#define N 6
#define inf (INT_MAX/10)

int record, mass, operations_bb, operations_bust;
int matrix[N][N];

struct p {
    int v;
    int h;
};

vector<p> finPath;

int record_find(vector<int> path) {
    int newN;
    int h = 0;
    newN = N - (path.size() - 1);
    int **a = new int *[N];
    for (int i = 0; i < N; i++) {
        a[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            a[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < path.size() - 1; i++) {
        h += matrix[path[i]][path[i + 1]];
        operations_bb++;
        for (int j = 0; j < N; j++) {
            a[path[i]][j] = inf;
            operations_bb++;
        }

        for (int k = 0; k < N; ++k) {
            a[k][path[i + 1]] = inf;
            operations_bb++;
        }
    }

    int min;
    for (int i = 0; i < N; i++) {
        min = inf;
        for (int j = 0; j < N; j++) {
            if (a[i][j] < min) min = a[i][j];
        }
        if (min != inf) {
            operations_bb++;
            h += min;
            for (int j = 0; j < N; j++)
                if (a[i][j] != inf) a[i][j] -= min;
        }
    }

    for (int i = 0; i < N; i++) {
        min = inf;
        for (int j = 0; j < N; j++) {
            if (a[j][i] < min) min = a[j][i];
        }
        if (min != inf) {
            operations_bb++;
            h += min;
        }

    }


    return h;
}

vector<int> greedy(int startV) {
    int min, ind = startV;
    bool passed[N], check = true;
    vector<int> v;

    for (int i = 0; i < N; ++i) passed[i] = false;
    passed[startV] = true;

    for (int i = startV; check; i = ind) {
        min = inf * 10;
        check = false;

        for (int j = 0; j < N; ++j) {
            if (!passed[j]) {
                if (matrix[i][j] < min) {
                    min = matrix[i][j];
                    ind = j;
                }
                check = true;
            }

        }

        if (!check) {
            v.push_back(startV);
            break;
        }

        v.push_back(ind);
        passed[ind] = true;
    }

    operations_bb += N;

    return v;
}

bool presence(vector<p> path, int vertex) {
    for (int i = 0; i < path.size(); ++i) {
        if (path.at(i).v == vertex) {
            return true;
        }
    }

    return false;
}

void branch_border(vector<p> path, int count = N - 1) {
    p x, min;
    vector<int> tmp;
    int pSize = path.size(), ind = 0;
    vector<p> tmpPath[count];
    min.h = inf;
    for (int i = 0; i < pSize; ++i) {
        tmp.push_back(path.at(i).v);
    }

    for (int i = 0; i < count; ++i) {
        tmpPath[i] = path;
    }

    tmp.push_back(0);
    int tSize = tmp.size() - 1;

    for (int i = 0; i < N; ++i) {
        operations_bb++;
        if (!presence(path, i)) {
            tmp.at(tSize) = i;
            x.h = record_find(tmp);
            x.v = i;

            operations_bb++;
            if (x.h <= record) {
                operations_bb++;
                min.h = x.h;
                min.v = x.v;
                tmpPath[ind].push_back(min);
                branch_border(tmpPath[ind], count - 1);
                ind++;
            }
        }
    }

    int s = tmpPath[0].size() - 1;
    if (count == 1) {
        //puts("Lower floor");
        operations_bb++;
        if (tmpPath[0].at(s).h <= record) {
            operations_bb++;
            finPath = tmpPath[0];
            record = tmpPath[0].at(s).h;
        }
    }

}

void Bust(vector<p> path, int count = N - 1, int m = 0) {
    p x, min;
    vector<int> tmp;
    int pSize = path.size(), ind = 0, mas;
    vector<p> tmpPath[count];
    min.h = inf;
    for (int i = 0; i < pSize; ++i) {
        tmp.push_back(path.at(i).v);

    }

    for (int i = 0; i < count; ++i) {
        tmpPath[i] = path;
    }

    tmp.push_back(0);
    int tSize = tmp.size() - 1;

    for (int i = 0; i < N; ++i) {
        operations_bust++;
        if (!presence(path, i)) {
            operations_bust++;
            mas = m;
            tmp.at(tSize) = i;
            mas += matrix[path.at(pSize - 1).v][i];
            if (mas >= 0) {
                operations_bust++;
                x.h = mas;
                x.v = i;
                tmpPath[ind].push_back(x);
                Bust(tmpPath[ind], count - 1, m + matrix[path.at(pSize - 1).v][i]);
                ind++;
            }
        }
    }

    int s = tmpPath[0].size() - 1;
    if (count == 1) {
        tmpPath[0].at(s).h += matrix[tmpPath[0].at(s).v][tmpPath[0].at(0).v];
        if (tmpPath[0].at(s).h < mass) {
            operations_bust++;
            finPath = tmpPath[0];
            mass = tmpPath[0].at(s).h;
        }
    }

}

void path_print(vector<p> path) {
    for (int i = 0; i < path.size(); ++i) {
        cout << path.at(i).v + 1;
        cout << " -> ";
    }
    cout << path.at(0).v + 1;
    cout << "\nRecord(H) = " << path.at(path.size() - 1).h << "\n\n";
}

int main() {
    vector<p> v;
    int startV;
    p x;

    printf("Enter start vertex: ");
    cin >> startV;
    startV -= 1;
    x.v = startV;

    mass = inf;
    ifstream fin("../input");

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            int tmp;
            fin >> tmp;
            if(tmp == 999){
                matrix[i][j] = inf;
            } else {
                matrix[i][j] = tmp;
            }
        }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] == inf) printf("b ");
            else printf("%i ", matrix[i][j]);
        }
        puts("");
    }

    v.push_back(x);

    record = record_find(greedy(startV));
    printf("\nH init = %i\n", record);
    operations_bb = 0;
    branch_border(v);
    printf("Branches & borders method\nPath: ");
    path_print(finPath);
    Bust(v);
    printf("Bust method\nPath: ");
    path_print(finPath);
    printf("\nBust operations = %i\nB&B method = %i\n", operations_bust, operations_bb);

    return 0;
}
