#include <iostream>
#include <vector>
#include<queue>
#include<stack>
#include<string>
#include<random>
#include<time.h>
#include<iomanip>
using namespace std;

int fun() {
    return rand() % 100 + 1;
}
void task2() {
    const int SIZE = 9;
    int a[SIZE][SIZE]; // матрица связей
    int d[SIZE]; // минимальное расстояние
    int v[SIZE]; // посещенные вершины
    int temp, minindex, min;
    int begin_index = 0;
    // Инициализация матрицы связей
    for (int i = 0; i < SIZE; i++)
    {
        a[i][i] = 0;
        for (int j = i + 1; j < SIZE; j++) {

            if ((i + 1) == 1) {
                if ((j + 1) == 2 or (j + 1) == 8 or (j + 1) == 9) {
                    temp = fun();
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else if((j + 1) == 7){
                    a[i][j] = fun();
                    a[j][i] = 0;
                }
                else {
                    temp = 0;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 2) {
                if ((j + 1) == 3 or (j + 1) == 7 or (j + 1) == 9) {
                    temp = fun();
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 0;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 3) {
                if ((j + 1) == 4 or (j + 1) == 6 or (j + 1) == 9) {
                    temp = fun();
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 0;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 4) {
                if ((j + 1) == 7) {
                    temp = fun();
                    a[i][j] = temp;
                    a[j][i] = temp;
                }else if ((j + 1) == 5 or (j + 1) == 6) {
                    a[i][j] = fun();
                    a[j][i] = 0;
                }
                else {
                    temp = 0;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 5) {
                if ((j + 1) == 6) {
                    temp = fun();
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 0;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 6) {
                if ((j + 1) == 7 or (j + 1) == 8 or (j + 1) == 9) {
                    temp = fun();
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 0;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else if ((i + 1) == 7) {
                if ((j + 1) == 9) {
                    temp = fun();
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 0;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
            else {
                if ((j + 1) == 9) {
                    temp = fun();
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
                else {
                    temp = 0;
                    a[i][j] = temp;
                    a[j][i] = temp;
                }
            }
        }
    }

    cout << "Найти кратчайший пути от вершины 1 до вершины 4\nМатрица смежностей:\n";
    // Вывод матрицы связей
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            std::cout << setw(2) << a[i][j] << " ";
        } 
        std::cout << "\n";
    }
    //Инициализация вершин и расстояний
    for (int i = 0; i < SIZE; i++)
    {
        d[i] = 10000;
        v[i] = 1;
    }
    d[begin_index] = 0;
    // Шаг алгоритма
    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < SIZE; i++)
        { // Если вершину ещё не обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min))
            { // Переприсваиваем значения
                min = d[i];
                minindex = i;
            }
        }
        // Добавляем найденный минимальный вес
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

    // Восстановление пути
    int ver[SIZE]; // массив посещенных вершин
    int end = 3; // индекс конечной вершины = 5 - 1
    ver[0] = end + 1; // начальный элемент - конечная вершина
    int k = 1; // индекс предыдущей вершины
    int weight = d[end]; // вес конечной вершины

    while (end != begin_index) // пока не дошли до начальной вершины
    {
        for (int i = 0; i < SIZE; i++) // просматриваем все вершины
            if (a[i][end] != 0)   // если связь есть
            {
                int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
                if (temp == d[i]) // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    end = i;       // сохраняем предыдущую вершину
                    ver[k] = i + 1; // и записываем ее в массив
                    k++;
                }
            }
    }
    string st = "";
    cout << "\nВывод кратчайшего пути\n";
    for (int i = k - 1; i >= 0; i--) {
        st += to_string(ver[i]);
    }
    cout << st;
}

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
    int n, k;
    n = rand() % 10 + 1;
    k = rand() % 10 + 1;
    vector < vector<int> > g(n);
    vector<int> mt;
    vector<char> used;
    vector<int> nums;
    cout << n << ' ' << k << '\n';
    for (int i = 0; i < n; i++) {
        int p = rand() % k+1;
        for (int j = 0; j < k; j++) {
            cout << '\n' << j << '\n';
            g[i].push_back(0);
        }

        /*nums.clear();*/
    }
    /*cout << n << ' ' << k << '\n';
    for (int i = 0; i < n; i++)
    {
        int p = rand() % k;
        cout << p << "\n";
        vector<int> nums{1,2,3,4,5,6,7,8,9,10};
        for (int j = 0; j < p; k++) {
            int l = rand() % nums.size() + 1;
            cout << l << '\n';
            int u = i, v = nums[l - 1];
            cout << u << " " << v << '\n';
            g[u].push_back(v - 1);

            auto iter = nums.begin();
            nums.erase(iter + l - 1);
        }
    }*/
    cout << "\nМатрица смежностей:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << setw(2) << g[i][j];
        }
        cout << '\n';
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
    srand(time(NULL));
    setlocale(LC_ALL, "ru");
    task7();
    /*int n, k;
    n = rand() % 10 + 1;
    k = rand() % 10 + 1;
    cout << n << " " << k << "\n";
    vector < vector<int> > g(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << i << " " << j << ' ';
            g[i].push_back(j);
        }
        cout << "\n";
    }*/

    //cout << "\nМатрица смежностей:\n";
    //for (int i = 0; i < n; i++) {
    //    for (int j = 0; j < k; j++) {
    //        cout << setw(2) << g[i][j];
    //    }
    //    cout << '\n';
    //}
    return 0;
}