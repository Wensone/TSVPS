#include <cstdio>
#include <climits>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct Point {
    int vertex;
    int height;
};

const int N = 6;

const long INF = ( INT_MAX / 10 );

int record,
    mass,
    operations_bb,
    operations_bust;

int matrix[N][N];

vector<Point> final_path;

int recordFind(vector<int> path) {
    int newN;
    int h = 0;
    newN = static_cast<int>(N - (path.size() - 1));
    auto **a = new int *[N];
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
            a[path[i]][j] = INF;
            operations_bb++;
        }

        for (int k = 0; k < N; ++k) {
            a[k][path[i + 1]] = INF;
            operations_bb++;
        }
    }

    int min;
    for (int i = 0; i < N; i++) {
        min = INF;
        for (int j = 0; j < N; j++) {
            if (a[i][j] < min) min = a[i][j];
        }
        if (min != INF) {
            operations_bb++;
            h += min;
            for (int j = 0; j < N; j++)
                if (a[i][j] != INF) a[i][j] -= min;
        }
    }

    for (int i = 0; i < N; i++) {
        min = INF;
        for (int j = 0; j < N; j++) {
            if (a[j][i] < min) min = a[j][i];
        }
        if (min != INF) {
            operations_bb++;
            h += min;
        }

    }


    return h;
}

vector<int> isVisited(int startV) {
    int min, ind = startV;
    bool passed[N], check = true;
    vector<int> v;

    for (bool &i : passed) i = false;
    passed[startV] = true;

    for (int i = startV; check; i = ind) {
        min = INF * 10;
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

bool isVertex(vector<Point> path, int vertex) {
    for (auto &i : path) {
        if (i.vertex == vertex) {
            return true;
        }
    }

    return false;
}

void branchBorder(vector<Point> path, int count = N - 1) {
    Point x{}, min{};
    vector<int> tmp;
    auto pSize = static_cast<int>(path.size()), ind = 0;
    vector<Point> tmpPath[count];
    min.height = INF;
    for (int i = 0; i < pSize; ++i) {
        tmp.push_back(path.at(static_cast<unsigned long>(i)).vertex);
    }

    for (int i = 0; i < count; ++i) {
        tmpPath[i] = path;
    }

    tmp.push_back(0);
    auto tSize = static_cast<int>(tmp.size() - 1);

    for (int i = 0; i < N; ++i) {
        operations_bb++;

        if (!isVertex(path, i)) {
            tmp.at(static_cast<unsigned long>(tSize)) = i;
            x.height = recordFind(tmp);
            x.vertex = i;

            operations_bb++;
            if (x.height <= record) {
                operations_bb++;
                min.height = x.height;
                min.vertex = x.vertex;
                tmpPath[ind].push_back(min);
                branchBorder(tmpPath[ind], count - 1);
                ind++;
            }
        }
    }

    auto s = static_cast<int>(tmpPath[0].size() - 1);
    if (count == 1) {
        operations_bb++;
        if (tmpPath[0].at(static_cast<unsigned long>(s)).height <= record) {
            operations_bb++;
            final_path = tmpPath[0];
            record = tmpPath[0].at(static_cast<unsigned long>(s)).height;
        }
    }

}

void bustMethod(vector<Point> path, int count = N - 1, int m = 0) {
    Point x{}, min{};
    vector<int> tmp;
    int pSize = static_cast<int>(path.size()), ind = 0, mas;
    vector<Point> tmpPath[count];
    min.height = INF;
    for (int i = 0; i < pSize; ++i) {
        tmp.push_back(path.at(static_cast<unsigned long>(i)).vertex);

    }

    for (int i = 0; i < count; ++i) {
        tmpPath[i] = path;
    }

    tmp.push_back(0);
    auto tSize = static_cast<int>(tmp.size() - 1);

    for (int i = 0; i < N; ++i) {
        operations_bust++;
        if (!isVertex(path, i)) {
            operations_bust++;
            mas = m;
            tmp.at(static_cast<unsigned long>(tSize)) = i;
            mas += matrix[path.at(static_cast<unsigned long>(pSize - 1)).vertex][i];
            if (mas >= 0) {
                operations_bust++;
                x.height = mas;
                x.vertex = i;
                tmpPath[ind].push_back(x);
                bustMethod(tmpPath[ind],
                           count - 1,
                           m + matrix[path.at(static_cast<unsigned long>(pSize - 1)).vertex][i]);
                ind++;
            }
        }
    }

    auto s = static_cast<int>(tmpPath[0].size() - 1);
    if (count == 1) {
        tmpPath[0].at(static_cast<unsigned long>(s)).height +=
                matrix[tmpPath[0].at(static_cast<unsigned long>(s)).vertex][tmpPath[0].at(0).vertex];
        if (tmpPath[0].at(static_cast<unsigned long>(s)).height < mass) {
            operations_bust++;
            final_path = tmpPath[0];
            mass = tmpPath[0].at(static_cast<unsigned long>(s)).height;
        }
    }

}

void printPath(vector<Point> path) {
    for (auto &i : path) {
        cout << i.vertex + 1;
        cout << " -> ";
    }
    cout << path.at(0).vertex + 1;
    cout << "\nRecord(H) = " << path.at(path.size() - 1).height << "\n\n";
}

int main() {
    vector<Point> search_vertex;
    int start_vertex;
    Point final_point{};

    cout << "Enter start vertex: ";
    cin >> start_vertex;
    start_vertex -= 1;
    final_point.vertex = start_vertex;

    mass = INF;
    ifstream fin("../input");

    for (auto &i : matrix)
        for (int &j : i) {
            int tmp;
            fin >> tmp;
            if(tmp == 999){
                j = INF;
            } else {
                j = tmp;
            }
        }

    for (auto &i : matrix) {
        for (int j : i) {
            if (j == INF) cout << "b ";
            else cout << " " << j;
        }
        cout << endl;
    }

    search_vertex.push_back(final_point);

    record = recordFind(isVisited(start_vertex));
    cout << "\nH init = " << record << "\n";
    operations_bb = 0;

    branchBorder(search_vertex);
    cout << "Branches & borders method\nPath: ";
    printPath(final_path);

    bustMethod(search_vertex);
    cout << "Bust Method method\nPath: ";
    printPath(final_path);
    cout << "\nbustMethod operations = " << operations_bust << "\nB&B method = " << operations_bb << "\n";

    return 0;
}
