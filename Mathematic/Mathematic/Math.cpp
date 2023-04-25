#include <iostream>
#include <vector>
#include<queue>
#include<stack>
using namespace std;

int fun(int var, int a, int b) {
    return (var * (a * a + b * b) + a * a + b * b + a + b) % 10;
}
void task2(int Var) {
    const int SIZE = 9;
    int a[SIZE][SIZE]; // матрица св€зей
    int d[SIZE]; // минимальное рассто€ние
    int v[SIZE]; // посещенные вершины
    int temp, minindex, min;
    int begin_index = 0;
    // »нициализаци€ матрицы св€зей
    for (int i = 0; i < SIZE; i++)
    {
        a[i][i] = 0;
        for (int j = i + 1; j < SIZE; j++) {

            if ((i + 1) == 1) {
                if ((j + 1) == 2 or (j + 1) == 8 or (j + 1) == 9) {
                    temp = fun(Var, i + 1, j + 1);
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else if((j + 1) == 7){
                    a[i][j] = fun(Var, i + 1, j + 1);
                    a[j][i] = 1000;
                }
                else {
                    temp = 1000;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 2) {
                if ((j + 1) == 3 or (j + 1) == 7 or (j + 1) == 9) {
                    temp = fun(Var, i + 1, j + 1);
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 1000;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 3) {
                if ((j + 1) == 4 or (j + 1) == 6 or (j + 1) == 9) {
                    temp = fun(Var, i + 1, j + 1);
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 1000;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 4) {
                if ((j + 1) == 7) {
                    temp = fun(Var, i + 1, j + 1);
                    a[i][j] = temp;
                    a[j][i] = temp;
                }else if ((j + 1) == 5 or (j + 1) == 6) {
                    a[i][j] = fun(Var, i + 1, j + 1);
                    a[j][i] = 1000;
                }
                else {
                    temp = 1000;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 5) {
                if ((j + 1) == 6) {
                    temp = fun(Var, i + 1, j + 1);
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 1000;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 6) {
                if ((j + 1) == 7 or (j + 1) == 8 or (j + 1) == 9) {
                    temp = fun(Var, i + 1, j + 1);
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 1000;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 7) {
                if ((j + 1) == 9) {
                    temp = fun(Var, i + 1, j + 1);
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 1000;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else {
                if ((j + 1) == 9) {
                    temp = fun(Var, i + 1, j + 1);
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 1000;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
        }
    }
    // ¬ывод матрицы св€зей

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) {
            std::cout << a[i][j] << " ";
        } 
        std::cout << "\n";
    }

    //»нициализаци€ вершин и рассто€ний
    for (int i = 0; i < SIZE; i++)
    {
        d[i] = 10000;
        v[i] = 1;
    }
    d[begin_index] = 0;
    // Ўаг алгоритма
    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < SIZE; i++)
        { // ≈сли вершину ещЄ не обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min))
            { // ѕереприсваиваем значени€
                min = d[i];
                minindex = i;
            }
        }
        // ƒобавл€ем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != 10000)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (a[minindex][i] > 0)
                {
                    temp = min + a[minindex][i];
                    if (temp < d[i])
                    {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < 10000);
    cout << d[5];
}

void task3() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n); // список инцидентных ребер каждой вершины
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }

    // ѕроверка нечетности
    int count_odd = 0;
    for (int i = 0; i < n; i++)
        if (g[i].size() % 2 == 1)
            count_odd++;

    // ѕодсчет количества "больших" компонент
    int count_big_comp = 0;
    vector<bool> use(n, false); // хранит состо€ни€ "посещенности" дл€ всех вершин

    // ѕеребор всех вершин дл€ нахождени€ всех компонент
    for (int i = 0; i < n; i++)
    {
        if (use[i]) // ѕроверка вершины на посещенность в какой-то из прошлых компонент
            continue;
        if (g[i].size() == 0) // ѕроверка вершины на изолированность
            // ¬ообще тут по логике должна быть строка use[i] = true, но ее можно опустить
            continue;

        count_big_comp++;

        // bfs от i-той вершины
        queue<int> q;
        q.push(i);
        use[i] = true;

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            for (int to : g[v])
            {
                if (use[to])
                    continue;
                q.push(to);
                use[to] = true;
            }
        }
    }

    if (count_odd <= 2 && count_big_comp <= 1)
        cout << "YES\n";
    else
        cout << "NO\n";
}
void task31() {
    int n = 0;//должно быть int n;
    vector < vector<int> > g(n, vector<int>(n));

    vector<int> deg(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            deg[i] += g[i][j];

    int first = 0;
    while (!deg[first])  ++first;

    int v1 = -1, v2 = -1;
    bool bad = false;
    for (int i = 0; i < n; ++i)
        if (deg[i] & 1)
            if (v1 == -1)
                v1 = i;
            else if (v2 == -1)
                v2 = i;
            else
                bad = true;

    if (v1 != -1)
        ++g[v1][v2], ++g[v2][v1];

    stack<int> st;
    st.push(first);
    vector<int> res;
    while (!st.empty())
    {
        int v = st.top();
        int i;
        for (i = 0; i < n; ++i)
            if (g[v][i])
                break;
        if (i == n)
        {
            res.push_back(v);
            st.pop();
        }
        else
        {
            --g[v][i];
            --g[i][v];
            st.push(i);
        }
    }

    if (v1 != -1)
        for (size_t i = 0; i + 1 < res.size(); ++i)
            if (res[i] == v1 && res[i + 1] == v2 || res[i] == v2 && res[i + 1] == v1)
            {
                vector<int> res2;
                for (size_t j = i + 1; j < res.size(); ++j)
                    res2.push_back(res[j]);
                for (size_t j = 1; j <= i; ++j)
                    res2.push_back(res[j]);
                res = res2;
                break;
            }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (g[i][j])
                bad = true;

    if (bad)
        puts("-1");
    else
        for (size_t i = 0; i < res.size(); ++i)
            printf("%d ", res[i] + 1);
}
//void findpath(int graph[][5], int n)
//{
//    vector<int> numofadj;
//
//    // Find out number of edges each vertex has
//    for (int i = 0; i < n; i++)
//        numofadj.push_back(accumulate(graph[i],
//            graph[i] + 5, 0));
//
//    // Find out how many vertex has odd number edges
//    int startpoint = 0, numofodd = 0;
//    for (int i = n - 1; i >= 0; i--)
//    {
//        if (numofadj[i] % 2 == 1)
//        {
//            numofodd++;
//            startpoint = i;
//        }
//    }
//
//    // If number of vertex with odd number of edges
//    // is greater than two return "No Solution".
//    if (numofodd > 2)
//    {
//        cout << "No Solution" << endl;
//        return;
//    }
//
//    // If there is a path find the path
//    // Initialize empty stack and path
//    // take the starting current as discussed
//    stack<int> stack;
//    vector<int> path;
//    int cur = startpoint;
//
//    // Loop will run until there is element in the stack
//    // or current edge has some neighbour.
//    while (!stack.empty() or
//        accumulate(graph[cur],
//            graph[cur] + 5, 0) != 0)
//    {
//        // If current node has not any neighbour
//        // add it to path and pop stack
//        // set new current to the popped element
//        if (accumulate(graph[cur],
//            graph[cur] + 5, 0) == 0)
//        {
//            path.push_back(cur);
//            cur = stack.top();
//            stack.pop();
//        }
//
//        // If the current vertex has at least one
//        // neighbour add the current vertex to stack,
//        // remove the edge between them and set the
//        // current to its neighbour.
//        else
//        {
//            for (int i = 0; i < n; i++)
//            {
//                if (graph[cur][i] == 1)
//                {
//                    stack.push(cur);
//                    graph[cur][i] = 0;
//                    graph[i][cur] = 0;
//                    cur = i;
//                    break;
//                }
//            }
//        }
//    }
//
//    // print the path
//    for (auto ele : path) cout << ele << " -> ";
//    cout << cur << endl;
//}

bool try_kuhn(int v, vector<char>& used, vector<int>& mt, vector<vector<int>>& g) {
    if (used[v])  return false;
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 || try_kuhn(mt[to], used, mt, g)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}
void task7() {
    int n, k, m;
    cin >> n >> k >> m;//колво вершин левой доли, правой, кол-во ребер
    vector < vector<int> > g(n);
    vector<int> mt;
    vector<char> used;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;//номера свзанных вершин, ребра
        g[u - 1].push_back(v - 1);
    }
    mt.assign(k, -1);
    vector<char> used1(n);
    for (int i = 0; i < n; ++i)
        for (size_t j = 0; j < g[i].size(); ++j)
            if (mt[g[i][j]] == -1) {
                mt[g[i][j]] = i;
                used1[i] = true;
                break;
            }
    for (int i = 0; i < n; ++i) {
        if (used1[i])  continue;
        used.assign(n, false);
        try_kuhn(i, used, mt, g);
    }

    for (int i = 0; i < k; ++i)
        if (mt[i] != -1) {
            cout << "\n";
            printf("%d %d\n", mt[i] + 1, i + 1);
        }
}


int main()
{
    setlocale(LC_ALL, "ru");
    task7();
    return 0;
}