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
string task2() {
    const int SIZE = 9;
    int a[SIZE][SIZE]; // ������� ������
    int d[SIZE]; // ����������� ����������
    int v[SIZE]; // ���������� �������
    int temp, minindex, min;
    int begin_index = rand() % 9 + 1 - 1; //������ ��������� �������, ������� - 1
    int end = rand() % 9 + 1 - 1; // ������ �������� �������, �������� - 1
    // ������������� ������� ������
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

    std::cout << "����� ���������� ���� �� ������� " << begin_index + 1 << " �� ������� " << end + 1 << "\n������� ����������:\n";
    // ����� ������� ������
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            std::cout << setw(2) << a[i][j] << " ";
        } 
        std::cout << "\n";
    }
    //������������� ������ � ����������
    for (int i = 0; i < SIZE; i++)
    {
        d[i] = 10000;
        v[i] = 1;
    }
    d[begin_index] = 0;
    // ��� ���������
    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < SIZE; i++)
        { // ���� ������� ��� �� ������ � ��� ������ min
            if ((v[i] == 1) && (d[i] < min))
            { // ��������������� ��������
                min = d[i];
                minindex = i;
            }
        }
        // ��������� ��������� ����������� ���
        // � �������� ���� �������
        // � ���������� � ������� ����������� ����� �������
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

    // �������������� ����
    int ver[SIZE]; // ������ ���������� ������
    ver[0] = end + 1; // ��������� ������� - �������� �������
    int k = 1; // ������ ���������� �������
    int weight = d[end]; // ��� �������� �������

    while (end != begin_index) // ���� �� ����� �� ��������� �������
    {
        for (int i = 0; i < SIZE; i++) // ������������� ��� �������
            if (a[i][end] != 0)   // ���� ����� ����
            {
                int temp = weight - a[i][end]; // ���������� ��� ���� �� ���������� �������
                if (temp == d[i]) // ���� ��� ������ � ������������
                {                 // ������ �� ���� ������� � ��� �������
                    weight = temp; // ��������� ����� ���
                    end = i;       // ��������� ���������� �������
                    ver[k] = i + 1; // � ���������� �� � ������
                    k++;
                }
            }
    }
    string st = "";
    std::cout << "\n����� ����������� ����\n";
    for (int i = k - 1; i >= 0; i--) {
        st += to_string(ver[i]);
    }
    cout << st << '\n';
    return st;
}

void randvec(vector<vector<int>>& g, int n, int m) {
    //n, m ������ �������, ����� x y ������
    int k; //��������� ����� ��� ���������� �������
    int f; //��������� ���-�� ���������� �� �������
    //n = rand() % 10 + 1; m = rand() % 10 + 1;
    /*vector<vector<int>> g(n);*/
    for (int i = 0; i < n; i++) {
        f = rand() % (m + 1);
        int p = m; //���=�� ��������� � ������� � ���������� ���������
        vector<int> nums; //������
        for (int o = 0; o < p; o++) { //���������� ����� �������
            nums.push_back(o);
        }

        for (int j = 0; j < f; j++) {
            k = rand() % p;
            g[i].push_back(nums[k]);
            p--;
            nums.erase(nums.begin() + k);
        }
    }

    //for (int i = 0; i < n; i++) { //���� �������, ����� ������� ���������
    //    for (auto j : g[i]) {
    //        cout << j << ' ';
    //    }
    //    cout << '\n';
    //}
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
int task7() {
    int n, k;
    n = rand() % 10 + 1;
    k = rand() % 10 + 1;
    vector < vector<int> > g(n);
    vector<int> mt;
    vector<char> used;
    vector<int> nums;
    randvec(g, n, k);
    std::cout << "������� ����������:\n";
    for (int i = 0; i < n; i++) {
        if (g[i].empty()) {
            std::cout << '-' << '\n';
        }
        else {
            for (auto j : g[i]) {
                std::cout << j << ' ';
            }
            std::cout << '\n';
        }
    }
    std::cout << '\n';

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
    int maxi = 0; //����� ������������� �������������
    for (int i = 0; i < k; ++i) //����� ������� 
        if (mt[i] != -1) {
            std::cout << "\n";
            printf("%d %d\n", mt[i] + 1, i + 1);
            maxi++;
        }
    cout << maxi << '\n';
    return maxi;
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    int choise = 0;
    std::cout << "����� ������ ������?\n1 - ������ 2\n2 - ������ 7\n";
    std::cout << "�������: ";
    cin >> choise;
    if (choise == 1) {
        string right_ans;
        right_ans = task2();
        string ans;
        cout << "\n������� �����: ";
        cin >> ans;
        cout << ans;
        if (ans == right_ans) {
            cout << "\n����� ������";
        }
        else {
            cout << "\n����� �� ������";
        }
    }
    else {
        int right_ans;
        right_ans = task7();
        int ans;
        cout << "\n������� �����: ";
        cin >> ans;
        cout << ans;
        if (ans == right_ans) {
            cout << "\n����� ������";
        }
        else {
            cout << "\n����� �� ������";
        }
    }
    return 0;
}