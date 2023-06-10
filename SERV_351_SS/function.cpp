#include "function.h"
#include <QString>
#include <QStringList>

struct US;
struct satan;


const int N = 410000; //N - максимальная длина строки s
char s[N];
int n, q, sqrtn, k, Log2[N], pos[N][26], pre[N], nxt[N], mn[N];

QByteArray parse(QString msg,int position){
    QStringList bufer = msg.split(" ");

    if(bufer[0] == "reg"){
        bufer.removeFirst();
        return sign_up(bufer).toUtf8();
    }
    else if(bufer[0] == "auth"){
        bufer.removeFirst();
        bufer.append(" "+ QString::number(position));
        return sign_in(bufer).toUtf8();
    }
    else if(bufer[0] == "point"){
        bufer.removeFirst();
        return get_point(bufer).toUtf8();
    }
    else if(bufer[0] == "get"){
        bufer.removeFirst();
        return get_tack(bufer).toUtf8();
    }
    else if(bufer[0]=="ans"){
        bufer.removeFirst();
        erase(bufer,"");

        if (bufer[0]==bufer[1]){
            bufer.removeFirst();
            bufer.removeFirst();
            bufer[1]="+1";
            task_toBD(bufer);
            return bufer[1].toUtf8();
        }
        else{
            bufer.removeFirst();
            bufer.removeFirst();
            bufer[1]="-1";
            task_toBD(bufer);
            return bufer[1].toUtf8();
        }
    }
    //ans2 otvet right_size task2 -/+1 log
    else if(bufer[0]=="ans2" ){
        bufer.removeFirst();
        erase(bufer,"");

        if(dolgrap(bufer[0]) and bufer[0].size()/2==bufer[1].toInt()){
            bufer.removeFirst();
            bufer.removeFirst();
            bufer[1]="+1";
            task_toBD(bufer);
            return bufer[1].toUtf8();
        }
        else{
            bufer.removeFirst();
            bufer.removeFirst();
            bufer[1]="-1";
            task_toBD(bufer);
            return bufer[1].toUtf8();
        }
    }
    else if(bufer[0]=="ans3"){//ans3 4 1 2 3 4 5 6 7 8 1 1 1 1 task3 -/+1 log
        bufer.removeFirst();//4 1 2 3 4 5 6 7 8 1 1 1 1 task3 -/+1 log
        erase(bufer,"");

        if(bufer[0].toInt()*3==bufer.count()-4)//4!! 1 2 3 4 5 6 7 8 1 1 1 1 task3 -/+1 log 4*3=12
        {
            int flag=1;

            QStringList list;
            QString str;

            for(int i = 0;i < bufer[0].toInt(); i++){
                str.append(QString::number(calc(bufer[1].toInt(),bufer[2].toInt()))+" ");
                bufer.removeAt(1);
                bufer.removeAt(1);//4 1 1 1 1 task3 -/+1 log + list = { 1 1 1 1 }
            }

            list=str.split(" ");

            for(int i = 0;i < bufer[0].toInt(); i++){
                if(list[i]!=bufer[i+1]){
                    flag=0;
                    break;
                }
            }

            for(int i = 0;i < bufer[0].toInt(); i++) bufer.removeAt(1);

            bufer.removeFirst();

            if(flag==1){    // task3 -/+1 log
                bufer[1]="+1";
                task_toBD(bufer);
                return bufer[1].toUtf8();
            }
            else{
                bufer[1]="-1";
                task_toBD(bufer);
                return bufer[1].toUtf8();
            }
        }

        else{
            bufer.remove(0,bufer.count()-3);
            bufer[1]="-1";
            task_toBD(bufer);
            return bufer[1].toUtf8();
        }
    }
    else if(bufer[0]=="dis")
    {
        bufer.removeFirst();
        dis(bufer);
        return "";
    }
    else
    {
        bufer.clear();
        return "error";
    }
}

void dis(QStringList temp){
    qDebug()<<"UPDATE User set Unique_Num = 'null' where Unique_Num = '"+ temp[0]+"'";
    QStringList Ubdate = singletonBD::getInstance()->getValue("UPDATE User set Unique_Num = NULL where Unique_Num = '"+ temp[0]+"'");

    if(Ubdate.size()>0) qDebug()<<"Ne good";
}

QString get_point(QStringList temp){
    QStringList ans = singletonBD::getInstance()->getValue("Select "+ temp[0] +" from User where Login = '" + temp[1]+"'");
    return ans[0];
}

QString sign_in(QStringList temp){
    QStringList ans = singletonBD::getInstance()->getValue("select Login, Password, Unique_Num from User where Login = '" + temp[0] + "' and Password= '"+ temp[1]+"'");
    //здесь у нас отправляется запрос на БД с проверкой существования пользователя

    if(ans.size()>0 && ans[0]!="eror" && (ans[2]=="null" || ans[2]== "")){//если хоть что-то пришло значит "гуд"
        QStringList Ubdate = singletonBD::getInstance()->getValue("UPDATE User set Unique_Num = "+temp[2]+" where Login = '"+ temp[0]+"'");
        return "auth&+";
        }
    else    return "auth&-";
}

QString sign_up(QStringList temp) {
    QStringList ans = singletonBD::getInstance()->getValue("INSERT INTO User(Login, Password, Mail, task1, task2, task3) VALUES ('" + temp[0] + "','" + temp[1] + "','" + temp[2] + "',0,0,0)");

    if(ans.size()>0)//если пришла ошибка, то не гуд
        return "reg&-";
    else    return "reg&+";
}

void task_toBD(QStringList temp){
    QString water;
    water.append("UPDATE User set "+temp[0]+" = "+temp[0]+" "+temp[1]+ " where Login = '"+ temp[2]+"'");
    QStringList ans = singletonBD::getInstance()->getValue(water);
}





void randvec(std::vector<std::vector<int>>& g, int n, int m) {
    //n, m размер матрицы, колво x y вершин
    int k; //случайное число для заполнения матрицы
    int f; //случайнок кол-во соединений от вершины
    //n = rand() % 10 + 1; m = rand() % 10 + 1;
    /*vector<vector<int>> g(n);*/

    for (int i = 0; i < n; i++) {
        f = rand() % (m + 1);
        int p = m; //кол=во элементов в векторе с доступными вершинами
        std::vector<int> nums; //вектор

        for (int o = 0; o < p; o++) { //заполнение этого вектора
            nums.push_back(o);
        }

        for (int j = 0; j < f; j++) {
            k = rand() % p;
            g[i].push_back(nums[k]);
            p--;
            nums.erase(nums.begin() + k);
        }
    }

}



bool try_kuhn(int v, std::vector<char>& used, std::vector<int>& mt, std::vector<std::vector<int>>& g) {

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


int fun()
{
    return rand() % 100 + 1;
}

bool dolgrap(QString answer) {
    int len_ans = answer.length();//длина строки
    std::set<QString> chet;//значения вершин х
    std::set<QString> nechet;//значения вершин y
    int n = 0;

    if (len_ans % 2 == 0) {//если все по парам, то может быть паросочетаниями

        for (auto a : answer) {

            if (n % 2 == 0) {//для различия заполнения x и y
                chet.insert(a);
            }
            else {
                nechet.insert(a);
            }
            n++;
        }

        int pol_ans = len_ans / 2;//если не совпадали и это паросочетания,
        //то должно быть по половине строки

        if (chet.size() == pol_ans and nechet.size() == pol_ans) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}


/* Умными словами: struct satan реализует алгоритм суффиксного массива (ну не приставочного же),
который позволяет эффективно решать множество задач на строках, таких как поиск наибольшей общей подстроки,
подстроки наибольшей длины, количества различных подстрок и т.д.*/

struct satan {

    int f[N], g[N], a[N], h[N], val[20][N];
    int satan[N], rk[N], oldrk[N];

    void build() { /*Умными словами: строим суффиксный массив для заданной строки s
    Как сказали на Хабре, хранить сами суффиксы смысла нет, достаточно хранить позицию начала данного суффикса */

        memset(f, 0, sizeof(f)); //заполняем нулями sizeof(f) байтов, указатель на f
        int t; //ленточка, представленная как строка

        for (int i = 1; i <= n; i++) {
            f[s[i] - 'a' + 1] = 1;
            //s[i] - цвет клетки латинскими буквами
            //s[i] - 'a' + 1 - какая это буква по алфавиту, если считать с 1
        }

        for (int i = 1; i <= 26; i++) {
            //cout << f[i] << " " << f[i-1] << " ";
            /* если рассматривать первый тест из примера, то первые пять значений
            в f это буквы a, b, c, d, e и все они равны 1, оставшиеся - нули
            */
            /* Умными словами:
            Массив f значениями 0 и 1 в зависимости от наличия соответствующей буквы в строке*/
            f[i] += f[i - 1]; //после этой операции в f будут значения 1, 2, 3, 4, 5 а дальше 5
            /* мы вычисляем префиксные суммы массива f, чтобы получить количество различных символов в строке */
        }

        t = f[26]; //количество различных цветов в ленте, т.е. различных символов в строке

        /* Для каждого символа s[i] мы устанавливаем rk[i] равным f[s[i]-'a'+1]*/
        for (int i = 1; i <= n; i++) {
            rk[i] = f[s[i] - 'a' + 1]; /* Умными словами:
            массив rk, который перенумеровывает символы строки согласно их порядку по возрастанию в алфавите*/

            //меняем буквы на цвета, если была строка abfe, то станет 1243,

            // т.е. это порядок не по алфавиту, а по возрастанию

            /* Умными словами:
            rk[i] - ранг суффикса, начинающегося в позиции i
            т.е. то место, которое займет суффикс при сортировке, т.е. его позиция в суффиксном массиве*/
        }

        for (int i = 1; i < n; i <<= 1) { //i<<=1 это присваивание i значения i<<1, т.е. степеней двойки

            for (int j = 1; j <= n; j++) oldrk[j] = rk[j]; //копируем значения из прошлого массива

            for (int j = 1; j <= n; j++) {
                a[j] = j + i <= n ? rk[j + i] : 0; /* массив a заполняется значениями, соответствующими порядку
                символов на расстоянии i от текущей позиции*/
                //cout << a[j] << ' ';
            }
            //тернарный оператор, если j+i <= n, то a[j] = rk[j+i], если нет, то a[j]=0

            /*
            если рассматривать 1 тест из примера, то при i=1, j=1, a[j] = a[1] = rk[2] = 2,
            где rk - порядок букв по возрастанию, 2 по возрастанию буква - b, т.е. 2

            */

            /* Функция "memset" используется для заполнения области памяти определенным значением,
            которое передается вторым аргументом, третий аргумент - количество байт, которое нужно заполнить. */

            memset(f, 0, sizeof(f));

            for (int j = 1; j <= n; j++) f[a[j]]++;

            for (int j = 1; j <= t; j++) f[j] += f[j - 1];

            for (int j = 1; j <= n; j++) g[f[a[j]]--] = j;

            memset(f, 0, sizeof(f));

            for (int j = 1; j <= n; j++) f[rk[j]]++;

            for (int j = 1; j <= t; j++) f[j] += f[j - 1];

            for (int j = n; j >= 1; j--) satan[f[rk[g[j]]]--] = g[j];

            t = 0;

            for (int j = 1; j <= n; j++) {
                t += oldrk[satan[j]] > oldrk[satan[j - 1]] || (oldrk[satan[j]] == oldrk[satan[j - 1]] && a[satan[j]] > a[satan[j - 1]]);
                rk[satan[j]] = t;
            }

        }

        for (int j = 1; j <= n; j++) satan[rk[j]] = j;

        int j = 0;

        for (int i = 1; i <= n; i++) {
            if (rk[i] == n) j = 0;
            else {
                if (j) j--;
                while (s[i + j] == s[satan[rk[i] + 1] + j]) j++;
            }
            h[rk[i]] = j; //массив h, который содержит длины наибольших общих префиксов соседних суффиксов
        }

        for (int i = 1; i <= n; i++) val[0][i] = h[i];

        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                val[j][i] = std::min(val[j - 1][i], val[j - 1][i + (1 << (j - 1))]);
        //используем массив val для хранения таблицы наименьших общих предков для массива lcp
    }

    /* ниже функция, которая находит длину наибольшего общего префикса (lcp) для суффиксов, начинающихся в позициях x и y */

    int lcp(int x, int y) {

        //находим ранг суффикса, начинающегося в позиции x, и ранг суффикса, начинающегося в позиции y
        x = rk[x]; y = rk[y];

        if (x > y) std::swap(x, y);

        y--;
        //Находим k - максимальную степень двойки, такую что (y-x+1) >= 2^k, не зря же логарифмы учили
        int k = Log2[y - x + 1];
        return std::min(val[k][x], val[k][y - (1 << k) + 1]);
        //используем массив rk для получения рангов суффиксов и массив val для быстрого вычисления lcp
    }

} A, B;

/* Код ниже определяет структуру данных "Disjoint Set Union" (DSU) и содержит два экземпляра этой структуры - L и R.
Структура данных DSU представляет собой коллекцию непересекающихся множеств, которые могут объединяться и разделяться.
Каждое множество представлено одним из его элементов (представителем), который выбирается произвольно.
*/

struct US {

    int fa[N], val[N];

    void init() {
        for (int i = 1; i <= n; i++) fa[i] = i, val[i] = n + 1;
    }

    /* findset(x) находит представителя множества, которому принадлежит элемент x.
    Если x не является представителем, то метод рекурсивно вызывает себя для его родителя,
    обновляя его родителя, чтобы он указывал на представителя множества. */

    int findset(int x) {
        if (x != fa[x]) fa[x] = findset(fa[x]);
        return fa[x];
    }

    /* Метод work(v, l, r) объединяет множества, содержащие элементы l и r
    и устанавливает значение val для каждого элемента множества, равное v.
    Сначала метод находит представителей множеств, содержащих l и r, затем он перебирает элементы первого множества,
    обновляя их значения val и fa, чтобы они указывали на следующий элемент в множестве, пока не достигнет
    представителя второго множества. */

    void work(int v, int l, int r) {
        v <<= 1; l = findset(l); r = findset(r);
        while (l != r) {
            val[l] = v;
            fa[l] = l + 1; l = findset(l);
        }
    }

    /*Таким образом, метод work() объединяет две половины отрезка в один отрезок
    и устанавливает значение val для каждого элемента этого отрезка.*/

} L, R;

int calc(int l, int r) {
    bool flag = false;

    /* Если ни один из символов, находящихся в позициях от l до r, не имеет следующего вхождения в строке,
    функция возвращает -1*/

    /* Для этого перебираются все символы (предполагается, что строка состоит только из маленьких латинских букв)
    и проверяется, есть ли следующее вхождение символа в диапазоне от l до r. Если такой символ есть, устанавливается
    флаг flag в true.*/

    for (int i = 0; i < 26; i++)
        if (nxt[pos[l][i]] <= r) flag = true;
    if (!flag) return -1;

    /* Если строка от l до r является периодом строки (т.е. можно ее повторить несколько раз, чтобы получить всю строку),
    функция возвращает 1*/

    /* Для этого производится факторизация длины строки len=r-l+1 на простые множители. Затем для каждого простого
    множителя i проверяется, можно ли разбить строку на i блоков одинаковой длины, так что каждый блок является
    повторением одной и той же подстроки. Если да, то функция возвращает 1. Если ни для одного простого
    множителя i это не выполняется, то функция продолжает проверку для следующего простого множителя.
    Если все простые множители были проверены и ни для одного из них не выполняется условие, то функция переходит
    к следующему шагу.
    */

    int len = r - l + 1, x = len;

    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) {
            int y = len / i;
            if (A.lcp(l, l + y) >= len - y) return 1;
            while (x % i == 0) x /= i;
        }

    if (x != 1) {
        int y = len / x;
        if (A.lcp(l, l + y) >= len - y) return 1;
    }

    /* Если строка от l до r является подстрокой, которая встречается как минимум дважды в строке
    (возможно, перекрываясь), функция возвращает 2 */

    /*
    Для этого проверяются несколько условий:

    - Если хотя бы один из начальных символов от l до r является началом какой-то другой подстроки в строке,
    которая перекрывается с исходной подстрокой, то функция возвращает 2.

    - Если хотя бы один из конечных символов от l до r является концом какой-то другой подстроки в строке,
    которая перекрывается с исходной подстрокой, то функция возвращает 2.

    - Если хотя бы один из префиксов или суффиксов строки от l до r имеет длину, меньшую или равную len,
    то функция возвращает 2.

    - Если хотя бы один из последних символов от l до r встречается где-то после r или перед l, то функция возвращает 3.

    - Если хотя бы один из первых символов от l до r встречается где-то после r или перед l, то функция возвращает 3.

    - Если существует такая позиция x, что l < x <= r и строка от l до x является префиксом строки от x до r,
    то функция возвращает 2.
    */

    if (L.val[l] <= len || R.val[r] <= len) return 2;

    for (int i = 1; i <= sqrtn + 1 && r - i + 1 > l; i++)
        if (A.lcp(l, r - i + 1) >= i) return 2;

    for (int i = std::max(A.rk[l] - sqrtn, 1); i <= std::min(A.rk[l] + sqrtn, n); i++) {
        int x = A.satan[i];
        if (l < x && x <= r && A.lcp(l, x) >= r - x + 1) return 2;
    }

    /* Если строка от l до r содержит как минимум одно вхождение символа, который также встречается где-то после r
    или перед l, функция возвращает 3*/
    if (nxt[l] <= r || pre[r] >= l) return 3;

    /* Во всех остальных случаях функция возвращает 4 */
    if (mn[l] <= r) return 3;

    return 4;
}









QString get_tack(QStringList temp)
{
    QString ans;
    QString buf;

    if(temp[0]=="task1")
    {

        const int SIZE = 9;
        int a[SIZE][SIZE]; // матрица связей
        int d[SIZE]; // минимальное расстояние
        int v[SIZE]; // посещенные вершины
        int temp, minindex, min;
        int begin_index = rand() % 9 + 1 - 1; //индекс начальной вершины, вершина - 1
        int end = rand() % 9 + 1 - 1; // индекс конечной вершины, вершиина - 1
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
                    else if ((j + 1) == 7) {
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
                    }
                    else if ((j + 1) == 5 or (j + 1) == 6) {
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

        ans.append("Найти кратчайший пути от вершины " + QString::number(begin_index + 1) + " до вершины " + QString::number(end + 1) + "\nМатрица смежностей:\n");
        // Вывод матрицы связей
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                ans.append(QString::number(a[i][j]) + "  ");
            }
            ans.append("\n");
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
        ans.append("||");
        QString st = "";
        //std::cout << "\nВывод кратчайшего пути\n";
        for (int i = k - 1; i >= 0; i--)
        {
            st.append(QString::number((ver[i])));
        }
        //cout << st << '\n';

        ans.append(st);
        return ans;

    }
    else if(temp[0]=="task2")
    {
        int n, k;
            n = rand() % 9 + 1;
            k = rand() % 9 + 1;
            std::vector < std::vector<int> > g(n);
            std::vector<int> mt;
            std::vector<char> used;
            std::vector<int> nums;
            randvec(g, n, k);
            ans.append("Матрица смежностей: \n");
            for (int i = 0; i < n; i++) {
                if (g[i].empty()) {
                    ans.append("- \n");
                }
                else {
                    for (auto j : g[i]) {
                        ans.append(QString::number(j + 1)+ " ");
                    }
                    ans.append("\n");
                }
            }
            ans.append("\n");

            mt.assign(k, -1);
            std::vector<char> used1(n);
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
            int maxi = 0; //длина максимального паросочетания
            for (int i = 0; i < k; ++i) //потом удалить
                if (mt[i] != -1) {
                   maxi++;
                }
            ans.append("||");
            ans.append(QString::number(maxi));
            return ans;
    }
    else if(temp[0]=="task3")
    {

        std::ios::sync_with_stdio(false);
        std::cin.tie(0); std::cout.tie(0);
        srand(time(NULL));

        n = rand() % 30 + 1; // генерация числа от 1 до 30
        ans.append("n = "+QString::number(n)+"\n");
        //cin >> n; //количество клеточек в ленте
        sqrtn = sqrt(n); //мне норм

        ans.append("s = ");
        for (int i = 1; i <= n; i++) { //индексы делаем с 1, потому что условие составляли добрые люди
            s[i] = 'a' + rand() % 26;
            ans.append(s[i]);
        }
        ans.append("\n");
        //cin >> q;
        q = rand() % 10 + 1; // генерация числа от 1 до 10 если я умру то удвлять и ставить 1
        ans.append("q = " + QString::number(q)+"\n");
        buf.append(QString::number(q)+"||");
        Log2[0] = -1; //зря что ли математику учили

        for (int i = 1; i <= n; i++) //как же меня бесят индексы с 1
            //типа мы крутые и умеем быстро получать степени 2
            //1 << 2 = 4 = 2 в степени 2, 1 << n = 2 в степени n
            Log2[i] = Log2[i >> 1] + 1; //первый элемент в массиве log2 будет всегда 0, последний - 1
        //Log2[i] - это в какую максимальную степень можно возвести 2, 2^i не было больше i

    /* Cтроим две суффиксных структуры данных для этой строки - одну для самой строки, а другую для ее реверса*/

        A.build(); //лента в нормальном порядке
        std::reverse(s + 1, s + n + 1);

        B.build(); //реверс ленты
        std::reverse(s + 1, s + n + 1);

        L.init();
        R.init();

        /* Перебираем все возможные длины подстрок (от 1 до n/2) и для каждой длины и каждой пары индексов i и j
        находим наибольший общий префикс между i и j в первой структуре данных и наибольший общий суффикс между
        i и j во второй структуре данных. Если сумма этих длин больше длины подстроки, то он запоминаем эту подстроку.
        */

        for (int len = 1; len <= n / 2; len++)
            for (int i = len, j = len << 1; j <= n; i += len, j += len) {
                int lcp = std::min(A.lcp(i, j), len), lcs = std::min(B.lcp(n - i + 2, n - j + 2), len - 1);
                int t = lcp + lcs - len + 1;
                if (t > 0) {
                    R.work(len, j + lcp - t, j + lcp);
                    L.work(len, i - lcs, i - lcs + t);
                }
            }

        /* Строим массив mn, где mn[i] - это минимальный индекс j, такой что подстрока s[i..j] является
        наибольшей общей подстрокой для какой-то пары индексов i и j. Строим массивы nxt и pre,
        где nxt[i] - это минимальный индекс j, такой что s[i..j] является наибольшей общей подстрокой
        для какой-то пары индексов i и j, а pre[i] - это максимальный индекс j, такой что s[j..i]
        является наибольшей общей подстрокой для какой-то пары индексов i и j.
        */

        mn[n + 1] = n + 1;
        for (int i = n; i >= 1; i--) mn[i] = std::min(mn[i + 1], i + L.val[i] - 1);

        for (int c = 0; c < 26; c++) pos[n + 1][c] = n + 1;
        for (int i = n; i >= 1; i--) {
            for (int c = 0; c < 26; c++) pos[i][c] = pos[i + 1][c];
            nxt[i] = pos[i][s[i] - 'a']; pre[pos[i][s[i] - 'a']] = i;
            pos[i][s[i] - 'a'] = i;
        }

        nxt[n + 1] = n + 1;

        int l, r; //левая и правая границы отрезка

        while (q--) { //выводим результаты на каждый запрос
            l = rand() % n + 1;
            r = rand() % (n - l + 1) + l;
            ans.append("l = "+ QString::number(l) +" r = " +QString::number(r) + "\n");
            buf.append(QString::number(l) + " " + QString::number(r)+ " ");
            //cout << "ответ на запрос: " << calc(l, r) << "\n";//вот тут штука для проверки не забыть !!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        ans.append("Ответ писать через пробел");
        ans.append("||");
        ans.append(buf);
        return ans;
    }
}




