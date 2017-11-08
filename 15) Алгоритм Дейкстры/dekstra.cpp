#include <cmath>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000000;


int main(){
	ifstream fin("input.txt");

    int n;
    fin >> n;
    vector < vector < pair<int,int> > > g (n);
    for(int i = 0; i < n; i++){
        // читаем матрицу
    }
    int s = 1; // стартовая вершина

    vector<int> d (n, INF),  p (n);
    d[s] = 0;
    vector<char> u (n);
    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == INF)
            break;
        u[v] = true;

        for (size_t j=0; j<g[v].size(); ++j) {
            int to = g[v][j].first,
                    len = g[v][j].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }

    for(int j = 1; j < n; j++){
        vector<int> path;
        for (int v=j; v!=s; v=p[v])
            path.push_back (v);
        path.push_back (s);
        reverse (path.begin(), path.end());

        cout << "Path from " << s << " to " << j << ": ";
        for (int i = 0; i < path.size(); ++i)
            cout << path[i] << ' ';
        cout << endl;
    }

	return 0;
}