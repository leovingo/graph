#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include <sstream> 

using namespace std;
bool visited[1001];
int parent[1001];

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
                AdjL.adj[k].push_back(i/2);
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
void numberofEandV(AdjMatrix AdjM)
{
    int nV = 0;
    cout << "Number of Edges: " << AdjM.n << endl;
    if (checkDirorUndirGraph(AdjM.arr, AdjM.n)) {
        for (int i = 0; i < AdjM.n; i++)
        {
            for (int j = i; j < AdjM.n; j++)
            {
                if (AdjM.arr[i][j] == 1) nV += AdjM.arr[i][j];
            }
        }
    }
    else {
        for (int i = 0; i < AdjM.n; i++)
        {
            for (int j = 0; j < AdjM.n; j++)
            {
                if (AdjM.arr[i][j] == 1) nV += AdjM.arr[i][j];
            }
        }
    }
    cout << "Number of Vertices: " << nV << endl;
}
void findDegree(AdjMatrix AdjM) {
    int nD;
    int nDI[1001];
    int nDO[1001];
    if (checkDirorUndirGraph(AdjM.arr, AdjM.n)) {
        for (int i = 0; i < AdjM.n; i++)
        {
            nD = 0;
            for (int j = 0; j < AdjM.n; j++)
            {
                nD += AdjM.arr[i][j];
            }
            cout << i+1 << "\t" << nD << "\n";
        }
    }
    else {
        for (int i = 0; i < AdjM.n; i++)
        {
            nDO[i] = 0;
            for (int j = 0; j < AdjM.n; j++)
            {
                if (AdjM.arr[i][j] == 1) nDO[i] += AdjM.arr[i][j];
            }
        }
        for (int i = 0; i < AdjM.n; i++)
        {
            nDI[i] = 0;
            for (int j = 0; j < AdjM.n; j++)
            {
                if (AdjM.arr[j][i] == 1) nDI[i] += AdjM.arr[j][i];
            }
        }
        for (int i = 0; i < AdjM.n; i++)
        {
            cout << i + 1 << "\t" << nDI[i] << "\t" << nDO[i] << endl;;
        }
    }
}
void listIsolatedandLeaf(AdjMatrix AdjM) {
    int checkIso, checkLeaf;
    for (int i = 0; i < AdjM.n; i++)
    {
        checkIso = 0;
        for (int j = 0; j < AdjM.n; j++)
        {
            if (!(AdjM.arr[i][j] == 0)) checkIso++;
        }
        if (checkIso == 0) cout << i+1 << "\t";

    }
    cout << endl;
    if (checkDirorUndirGraph(AdjM.arr, AdjM.n)) {
        for (int i = 0; i < AdjM.n; i++)
        {
            checkLeaf = 0;
            for (int j = 0; j < AdjM.n; j++)
            {
                if (AdjM.arr[i][j] == 0) checkLeaf++;

            }
            if (checkLeaf == AdjM.n - 1) cout << i+1 << "\t";
        }
        cout << endl;
    }
    else {
        for (int i = 0; i < AdjM.n; i++)
        {
            checkLeaf = 0;
            for (int j = 0; j < AdjM.n; j++)
            {
                if ((AdjM.arr[i][j] == 0) || (AdjM.arr[j][i] == 0)) checkLeaf++;
            }
            if (checkLeaf == 2 * AdjM.n - 1) cout << i+1 << "\t";
        }
        cout << endl;
    }
}
bool checkCompleteGraph(AdjMatrix AdjM) {
    if (checkDirorUndirGraph(AdjM.arr, AdjM.n)) {
        for (int i = 0; i < AdjM.n; i++) {
            if (AdjM.arr[i][i] != 0) return false;
            for (int j = i + 1; j < AdjM.n; j++) {
                if (AdjM.arr[i][j] != 1) return false;
            }
        }
        return true;
    }
    return false;
}
void dirToUndirGraph(AdjMatrix AdjM) {
    if (!checkDirorUndirGraph(AdjM.arr, AdjM.n)) {
        for (int i = 0; i < AdjM.n; i++)
        {
            for (int j = 0; j < AdjM.n; j++)
            {
                if (AdjM.arr[i][j] == 1) AdjM.arr[j][i] = 1;
            }
        }
        cout << "Undirected Graph:\n";
        for (int i = 0; i < AdjM.n; i++)
        {
            for (int j = 0; j < AdjM.n; j++)
            {
                cout << AdjM.arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    else cout << "Matrix is Undirected Graph\n";
}
void complementGraph(AdjMatrix AdjM, AdjMatrix& AdjCom) {
    if (checkDirorUndirGraph(AdjM.arr, AdjM.n))
    {
        AdjCom.n = AdjM.n;
        for (int i = 0; i < AdjCom.n; i++) {
            for (int j = 0; j < AdjCom.n; j++) {
                if ((i != j) && (AdjM.arr[i][j] == 0)) AdjCom.arr[i][j] = 1;
                else AdjCom.arr[i][j] = 0;
            }
        }
        cout << "complement Graph:\n";
        for (int i = 0; i < AdjCom.n; i++) {
            for (int j = 0; j < AdjCom.n; j++) {
                cout << AdjCom.arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    else cout << "Directed Graph \n";
}
void converseGraph(AdjMatrix AdjM, AdjMatrix& AdjCon)
{
    if (!checkDirorUndirGraph(AdjM.arr, AdjM.n))
    {
        AdjCon.n = AdjM.n;
        for (int i = 0; i < AdjCon.n; i++) {
            for (int j = 0; j < AdjCon.n; j++) {
                AdjCon.arr[i][j] = 0;
            }
        }
        for (int i = 0; i < AdjCon.n; i++) {
            for (int j = 0; j < AdjCon.n; j++) {
                if (AdjM.arr[i][j] == 1)
                {
                    AdjCon.arr[i][j] = 0;
                    AdjCon.arr[j][i] = 1;
                }
            }
        }
        cout << "converse Graph\n";
        for (int i = 0; i < AdjCon.n; i++) {
            for (int j = 0; j < AdjCon.n; j++) {
                cout << AdjCon.arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    else cout << "Matrix is Undirected Graph\n";
}
int main()
{
    AdjMatrix AdjM;
    AdjMatrix AdjCom, AdjCon;
    AdjList AdjL;
    input(AdjL, AdjM);
    /*if (checkDirorUndirGraph(AdjM.arr, AdjM.n)) cout << "Undirected Graph \n";
    else cout << "Directed Graph \n";*/
    /*numberofEandV(AdjM);
    findDegree(AdjM);*/
    //listIsolatedandLeaf(AdjM);
    /*if (checkCompleteGraph(AdjM)) cout << "Complete Graph \n";
    else cout << "Not Complete Graph \n";*/
    //dirToUndirGraph(AdjM);
    //complementGraph(AdjM, AdjCom);
    //converseGraph(AdjM, AdjCon);
    memset(visited, false, sizeof(visited));
    return 0;
}
