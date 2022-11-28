#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<queue>

using namespace std;
bool visited[1001];
int parent[1001];
int degree[1001];
int color[1001];

struct AdjMatrix
{
    int n = 0;
    int arr[100][100];
};
    struct AdjList
    {
        int n = 0;
        vector<int> adj[1001];
    };

    void bai1(ifstream& filein, string filename, AdjList& AdjL)
    {
        filein.open(filename, ios::in);
        if (!filein.is_open()) {
            cerr << "Could not open the file - '" << endl;
        }
        string line;
        getline(filein, line, '\n');

        int x = stoi(line);
        AdjL.n = x;
        int k = 0;
        while ((getline(filein, line, '\n')))
        {

            for (int i = 0; i < (int)line.size(); i++)
            {
                if (line[i] == '1')
                {
                    AdjL.adj[k].push_back(i / 2);
                    degree[i/2]++;
                }
            }
            k++;
        }
    }
void bai2(ifstream& filein, string filename, AdjMatrix& AdjM)
{
    filein.open(filename, ios::in);
    if (!filein.is_open()) {
        cerr << "Could not open the file - '" << endl;
    }
    string line;
    getline(filein, line, '\n');
    AdjM.n = int(line[0]) - 48;
    for (int i = 0; i < AdjM.n; i++)
    {
        for (int j = 0; j < AdjM.n; j++)
        {
            AdjM.arr[i][j] = 0;
        }
    }

    int i = 0;
    while ((getline(filein, line, '\n')))
    {
        for (int j = 0; j < line.size(); j += 2)
        {
            int k = int(line[j]) - 48;
            AdjM.arr[i][k] = 1;
        }
        i++;
    }

}
void createdAdjList(AdjList& AdjL, AdjMatrix& AdjM) {
    AdjL.n = AdjM.n;
    for (int i = 0; i < AdjM.n; i++)
    {
        for (int j = 0; j < AdjM.n; j++)
        {
            if (AdjM.arr[i][j] > 0) {
                AdjL.adj[i].push_back(j);
                degree[j]++;
            }
        }
    }
}
void createdAdjMatrix(AdjList& AdjL, AdjMatrix& AdjM) {
    AdjM.n = AdjL.n;
    for (int i = 0; i < AdjM.n; i++)
    {
        for (int j = 0; j < AdjM.n; j++)
        {
            AdjM.arr[i][j] = 0;
        }
    }

    int i = 0;
    for (int i = 0; i < AdjM.n; i++)
    {
        for (int x : AdjL.adj[i])
        {
            AdjM.arr[i][x] = 1;
        }
    }
}
void input(AdjList& AdjL, AdjMatrix& AdjM) {
    ifstream filein1, filein2;
    string filename1 = "graph1.txt";
    string filename2 = "graph2.txt";
    int choice = 0;
    cout << "Adjacency matrix(1) or Adjacency list(2)? ";
    cin >> choice;
    if (choice == 1)
    {
        bai1(filein1, filename1, AdjL);
        createdAdjMatrix(AdjL, AdjM);
        for (int i = 0; i < AdjM.n; i++)
        {
            for (int j = 0; j < AdjM.n; j++) {
                cout << AdjM.arr[i][j] << " ";
            }
            cout << endl;
        }
        for (int i = 0; i < AdjL.n; i++) {
            cout << i << " : ";
            for (int x : AdjL.adj[i]) {
                cout << x << " ";
            }
        }
    }
    else if (choice == 2) {

        bai2(filein2, filename2, AdjM);
        cout << AdjM.n << endl;
        createdAdjList(AdjL, AdjM);
        for (int i = 0; i < AdjL.n; i++) {
            cout << i << " : ";
            for (int x : AdjL.adj[i]) {
                cout << x << " ";
            }
            cout << endl;
        }
    }
    filein1.close();
    filein2.close();
}
bool checkDirorUndirGraph(int arr[][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i != j) && (arr[i][j] != arr[j][i])) return false;
        }
    }
    return true;
}
bool DFS1(int u, AdjList AdjL) {
    visited[u] = true;
    for (int v : AdjL.adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            if (DFS1(v, AdjL)) return true;
        }
        else if (v != parent[u]) {
            return true;
        }
    }
    return false;
}
bool dfs1(int u, AdjList AdjL) {
    color[u] = 1;
    for (int v : AdjL.adj[u]) {
        if (!color[v]) {
            if (dfs1(v, AdjL)) return true;
        }
        else if (color[v] == 1) return true;
    }
    color[u] = 2;
    return false;
}
bool checkcirculargraph1(AdjList AdjL) {
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= AdjL.n; i++) {
        if (!visited[i]) {
            if (DFS1(i, AdjL)) {
                return true;
            }
        }
    }
    return false;
}
bool checkcirculargraph2(AdjList AdjL) {
    queue<int> q;
    for (int i = 0; i < AdjL.n; i++) {
        if (degree[i] == 0) q.push(i);
    }
    int cnt = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        ++cnt;
        for (int x : AdjL.adj[v]) {
            degree[x]--;
            if (!degree[x]) q.push(x);
        }
    }
    cout << cnt << endl;
    if (cnt == AdjL.n) {
        return false;
    }
    return true;
}


bool bipartite = true;
const int maxn = 1001;
int color[maxn];
bool dfs(int u, int par, AdjList AdjL) {
    color[u] = 1 - color[par];
    for (int v : AdjL.adj[u]) {
        if (color[v] == -1) {
            if (!dfs(v, u, AdjL)) return false; // return dfs(v, u)
        }
        else if (color[v] == color[u]) return false;
    }
    return true;
}
bool checkBigraph(AdjList AdjL) {
    memset(color, -1, sizeof(color));
    bool check = true;
    color[0] = 1;
    for (int i = 1; i <= AdjL.n; i++) {
        if (color[i] == -1) {
            if (!dfs(i, 0, AdjL)) {
                check = false; break;
            }
        }
    }
    return check;
}
int main()
{
    AdjMatrix AdjM;
    AdjMatrix AdjCom, AdjCon;
    AdjList AdjL;
    input(AdjL, AdjM);
    if (checkDirorUndirGraph(AdjM.arr, AdjM.n))
    {
        if (checkcirculargraph1(AdjL)) cout << "hu";
    }
    else if (checkcirculargraph2(AdjL)) cout << "hi";
    return 0;
}


