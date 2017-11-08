#include <cmath>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
	int a, b, cost;
};
 
int n, m, v;
vector<edge> e;
const int INF = 1000000;

void solve() {
    vector<int> d (n, INF);
    d[v] = 0;
    vector<int> p (n, -1);
    for (;;) {
        bool any = false;
        for (int j=0; j<m; ++j)
            if (d[e[j].a] < INF)
                if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                    d[e[j].b] = d[e[j].a] + e[j].cost;
                    p[e[j].b] = e[j].a;
                    any = true;
                }
        if (!any) break;
    }
    int t = 1;
    if (d[t] == INF)
        cout << "No path from " << v << " to " << t << ".";
    else {
        for(int j = 1; j < n; j++) {
            vector<int> path;
            for (int cur = j; cur != -1; cur = p[cur])
                path.push_back(cur);
            reverse(path.begin(), path.end());

            cout << "Path from " << v << " to " << t << ": ";
            for (int i = 0; i < path.size(); ++i)
                cout << path[i] << ' ';
            cout << endl;
        }
    }
}

int main(){
	ifstream fin("input.txt");
	fin >> n >> m >> v;

	e.reserve(m);

	for(int i = 0; i < m; i++){
		fin >> e[i].a >> e[i].b >> e[i].cost;
	}

	solve();
	cout << endl;

	fin.close();
	return 0;
}