#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// Перечисление содержит константы для обозначения классов символьных лексем: ЦИФРА, ЗНАК, ПРОБЕЛ, ОШИБКА, КОНЕЦ.
enum SymbolicTokenClass { Digit, Sign, Space, Error, EndOfFile };

// Перечисление содержит константы для обозначения состояний автомата и одну дополнительную константу s_Stop.
enum States { s_A1, s_B1, s_C1, s_D1, s_Stop };

// Структура для представления символьной лексемы.
struct SymbolicToken
{
    SymbolicTokenClass token_class; // Класс лексемы.
    int value;                      // Значение лексемы.
};

// Глобальные переменные, используемые процедурами автомата.
SymbolicToken s;    // Символьная лексема.
int sign;           // Регистр знака.
int number;         // Регистр числа.
vector<int> vect;
vector<char> vect_variable;
vector<int> vect_variable_mean;

// Функция транслитерации символа.
SymbolicToken transliterator(int ch)
{
    SymbolicToken s;
    s.value = 0;
    if (isdigit(ch))
    {
        s.token_class = Digit;
        s.value = ch - '0';
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    {
        s.token_class = Sign;
        s.value = ch;
    }
    else if (ch == ' ' || ch == '\t')
    {
        s.token_class = Space;
    }
    else if (ch == EOF)
    {
        s.token_class = EndOfFile;
    }
    else
    {
        s.token_class = Error;
    }
    return s;
}

//Процедуры автомата (от A1 до Exit1).
int A1()
{
    return s_A1;
}

int B1()
{
    return s_B1;
}

int B1a()
{
    if (s.value == '+') sign = 1;
    else sign = -1;
    return s_B1;
}

int B1b()
{
    if (s.value == '-') sign = -sign;
    return s_B1;
}

int C1a()
{
    sign = 1;
    number = s.value;
    return s_C1;
}

int C1b()
{
    number = s.value;
    return s_C1;
}

int C1c()
{
    number = 10 * number + s.value;
    return s_C1;
}
//
int D1()
{
    vect.push_back(number);
    number = 0;
    return s_D1;
}

int Error1()
{
    cout << "Обнаружена ошибка" << endl;
    return s_Stop;
}

int Exit1()
{
    if (sign == -1) number = -number;
    if (number != 0)
    {
        vect.push_back(number);
        number = 0;
    }
    return s_Stop;
}

// Функция для выполнения арифметических операций.
void perform_operation(string operation)
{
    if (vect.size() < 2)
    {
        cout << "Недостаточно элементов в стеке для операции." << endl;
        return;
    }
    int b = vect.back(); vect.pop_back(); // Второй операнд
    int a = vect.back(); vect.pop_back(); // Первый операнд
    int result;

    if (operation.compare("+") == 0)
    {
        result = a + b;
    }
    if (operation.compare("-") == 0)
    {
        result = a - b;
    }
    if (operation.compare("*") == 0)
    {
        result = a * b;
    }
    if (operation.compare("/") == 0)
    {
        if (b == 0)
        {
            cout << "Ошибка: деление на ноль." << endl;
            vect.push_back(a); // Возвращаем операнды в стек в случае ошибки
            vect.push_back(b);
            return;
        }
        result = a / b;
    }
    if (operation.compare("%") == 0)
    {
        if (b == 0)
        {
            cout << "Ошибка: деление на ноль." << endl;
            vect.push_back(a); // Возвращаем операнды в стек в случае ошибки
            vect.push_back(b);
            return;
        }
        result = a % b;
    }
    if (operation.compare(">\n") == 0)
        result = a > b;
    if (operation.compare("<\n") == 0)
        result = a < b;
    if (operation.compare("=\n") == 0)
        result = a == b;
    if (operation.compare("!=") == 0)
        result = a != b;
    if (operation.compare(">=") == 0)
        result = a >= b;
    if (operation.compare("<=") == 0)
        result = a <= b;

    vect.push_back(result); // Помещаем результат обратно в стек
}

// Размеры таблицы автомата.
const int state_number = 4; // Число состояний (без s_Stop).
const int class_number = 5; // Число символов входного алфавита.

// Таблица указателей на процедуры автомата.
typedef int (*function_pointer)();
function_pointer table[state_number][class_number];

// Функция инициализации таблицы указателей на процедуры автомата.
void initialize_table()
{
    for (int i = 0; i < state_number; i++)
        for (int j = 0; j < class_number; j++)
            table[i][j] = Error1;

    table[s_A1][Digit] = C1a; table[s_A1][Sign] = B1a; table[s_A1][Space] = A1;
    table[s_B1][Digit] = C1b; table[s_B1][Sign] = B1b; table[s_B1][Space] = B1;

    table[s_C1][Digit] = C1c; table[s_C1][Space] = D1; table[s_C1][EndOfFile] = Exit1;
    table[s_D1][Space] = D1; table[s_D1][EndOfFile] = Exit1;
}

// Основная функция анализа. Функция запускает конечный автомат на тексте из файла filename.
void parse(const char* filename)
{
    ifstream in(filename);
    if (!in)
    {
        cout << "Не удалось открыть файл " << filename << endl;
        return;
    }

    int state = s_A1;
    int ch;
    string str;

    while (state != s_Stop)
    {
        state = s_A1;
        ch = in.get();
        if (ch == '\n')
            ch = in.get();
        if (ch == ';')
        {
            string st;
            st = "";
            getline(in, st);
            ch = in.get();
        }
        if (!isdigit(ch) && ch != '+' && ch != '-' && ch != '/' && ch != '*' && ch != '\n' && ch != '<' && ch != '>' && ch != '=' && ch != '!' && ch != '%')
        {
            str += ch;
            while ((ch = in.get()) != ' ' && ch != EOF && ch != '\n') {
                str += ch;
            }
            if (str == "push") {
                ch = in.get();
                if (isdigit(ch))
                {
                    while (isdigit(ch) || ch == '+' || ch == '-') {
                        s = transliterator(ch);
                        state = (*table[state][s.token_class])();
                        ch = in.get();
                    }
                    if (sign == -1)
                        number = -number;
                    vect.push_back(number);
                    number == 0;
                    sign = 0;
                    str.clear();
                }
                else
                {
                    int i = 0;
                    while (i < vect_variable.size())
                    {
                        if (vect_variable[i] == ch)
                        {
                            vect.push_back(vect_variable_mean[i]);
                            break;
                        }
                        i++;
                    }
                }
            }
            else if (str == " ;")
            {
                string st;
                st = "";
                getline(in, st);

            }
            else if (str == "write")
            {
                for (int num : vect) {
                    cout << num << " ";
                }

                cout << endl;
            }
            else if (str == "pop")
            {
                ch = in.get();
                int h = -1;
                for (int i = 0; i < vect_variable.size(); i++)
                {
                    if (vect_variable[i] == ch)
                    {
                        h = i;
                    }
                }
                if (h == -1)
                {
                    vect_variable.push_back(ch);
                    vect_variable_mean.push_back(vect[vect.size() - 1]);
                    vect.pop_back();
                }
                else
                {
                    vect_variable_mean[h] = vect[vect.size() - 1];
                    vect.pop_back();
                }
            }
            else if (str == "end") {
                cout << "Завершение работы." << endl;
                break;
            }
            else if (str == "read")
            {
                ch = in.get();
                while (isdigit(ch) || ch == '+' || ch == '-') {
                    s = transliterator(ch);
                    state = (*table[state][s.token_class])();
                    ch = in.get();
                }
                if (sign == -1)
                    number = -number;
                vect.push_back(number);
                number == 0;
                sign = 0;
                str.clear();
            }
            else if (str == "ji")
            {
                ch = in.get();
                while (isdigit(ch))
                {
                    s = transliterator(ch);
                    state = (*table[state][s.token_class])();
                    ch = in.get();
                }
                if (vect[vect.size() - 1] > 0)
                {
                    string st;
                    in.seekg(0);
                    int i = number;
                    while (i - 1)
                    {
                        st = "";
                        getline(in, st);
                        i--;
                    }
                    vect.pop_back();
                }
                else
                {
                    vect.pop_back();
                }
            }
            else if (str == "jmp")
            {
                ch = in.get();
                while (isdigit(ch))
                {
                    s = transliterator(ch);
                    state = (*table[state][s.token_class])();
                    ch = in.get();
                }
                string st;
                in.seekg(0);
                int i = number;
                while (i - 1)
                {
                    st = "";
                    getline(in, st);
                    i--;
                }

            }
            else {
                cout << "Неизвестная команда: " << str << endl;
            }
            str.clear();
        }
        else if (isdigit(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '<' || ch == '>' || ch == '>=' || ch == '<=' || ch == '=' || ch == '!=' || ch == '%')
        {
            string op;
            op.push_back(ch);
            if (ch == '>' || ch == '<' || ch == '!' || ch == '=')
            {
                ch = in.get();
                op.push_back(ch);
            }
            perform_operation(op); // Выполняем операцию
        }
    }
    in.close();
}

// Вызов программы имеет вид ./имя-исполняемого-файла имя-входного-файла.
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUS");

    char f_name[] = "input6.txt"; // Имя входного файла. 
    initialize_table();
    parse(f_name);

    return 0;
}