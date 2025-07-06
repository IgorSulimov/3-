#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
#include <stack>
#include "Vector.hpp"
using namespace std;
int size_ = 5;
int Value_Word_Lexems = 0;
int size_array_ = 5;
// Перечисление содержит константы для обозначения классов символьных лексем: ЦИФРА, ЗНАК, ПРОБЕЛ, ОШИБКА, КОНЕЦ.
enum SymbolicTokenClass { Symbol, Digit, Arithmetic, Comparison, EndOfLine, Semicolon, Space, Error, EndOfFile };

// Перечисление содержит константы для обозначения состояний автомата и одну дополнительную константу Stop.
enum States {
    A1, /*начало*/
    Sy_B1, /*все лексемы*/
    Co_B2, /* < >*/
    Ar_A1, /*+,-,%,>=,<=.....*/
    Ar_B2, //Вектор

    Sy_L1, /*L*/
    Sy_J1,
    Sy_E1, /*end*/
    Sy_E3,
    Sy_E2,
    Sy_I1,
    Sy_I2,
    Sy_I3,
    Sy_W1,
    Sy_W2,
    Sy_C1,
    Sy_C2,
    Sy_C3,
    Sy_S1,
    Sy_S2,
    Sy_S3,
    Sy_S4,
    Sy_S5,
    Sy_T1,
    Sy_T2,
    Sy_R1,
    Sy_D1,
    Sy_F1,
    Sy_V1,
    Sy_O1,
    Sy_Z60,// константы
    Sy_Z50,// переменные

    Ar_C2,
    Ar_D2,
    Stop
};
// Структура для представления символьной лексемы.
struct SymbolicToken
{
    SymbolicTokenClass token_class; // Класс лексемы.
    int value;                      // Значение лексемы.
    char value_c;

};
struct Lexeme
{
    int number_line = 0;
    int Word;
    int value_int;
    string value_char;
    Vector value_vector;
    int int_or_char = -1; // имя переменной-0, если цифра-1

};


void See_number(int number = 0, string Lex_ = "", int value_int = 0)
{
    if (number == 1)
        cout << "if";
    if (number == 2)
        cout << "then";
    if (number == 3)
        cout << "else";
    if (number == 4)
        cout << "while";
    if (number == 5)
        cout << "each";
    if (number == 6)
        cout << "end";
    if (number == 7)
        cout << "in";
    if (number == 8)
        cout << "cin";
    if (number == 9)
        cout << "=";
    if (number == 10)
        cout << "!=";
    if (number == 11)
        cout << ">=";
    if (number == 12)
        cout << "<=";
    if (number == 13)
        cout << "+";
    if (number == 14)
        cout << "-";
    if (number == 15)
        cout << "*";
    if (number == 16)
        cout << "%";
    if (number == 17)
        cout << "/";
    if (number == 18)
        cout << ">";
    if (number == 19)
        cout << "<";
    if (number == 20)
        cout << "shiftr";
    if (number == 21)
        cout << "shiftl";
    if (number == 22)
        cout << "concat";
    if (number == 23)
        cout << "subvec";
    if (number == 24)
        cout << ";";
    if (number == 25)
        cout << "&";
    if (number == 26)
        cout << "set";
    if (number == 27)
        cout << "for";
    if (number == 28)
        cout << ">>";
    if (number == 29)
        cout << "<<";
    if (number == 30)
        cout << "cout";
    if (number == 31)
        cout << Lex_; // Вектор
    if (number == 32)
        cout << "jump";
    if (number == 33)
        cout << "switch";
    if (number == 34)
        cout << "when";
    if (number == 35)
        cout << "throw";
    if (number == 36)
        cout << "*Комментарий*";
    if (number == 37)
        cout << "int";
    if (number == 38)
        cout << "vector";
    if (number == 39)
        cout << Lex_; //переход к метке
    if (number == 40)
        cout << "do";
    if (number == 41)
        cout << Lex_;//Переменная
    if (number == 42)
        cout << "Ошибка";
    if (number == 43)
        cout << "(";
    if (number == 44)
        cout << ")";
    if (number == 45)
        cout << value_int; // константа
    if (number == 46)
        cout << Lex_; // сама метка
    if (number == 47)
        cout << "otherwise";
}

SymbolicToken transliterator(int ch)
{
    SymbolicToken s;
    s.value = 0;

    if (isdigit(ch))
    {
        s.token_class = Digit;
        s.value = ch - '0';
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '%' || ch == '/' || ch == '&')
    {
        s.token_class = Arithmetic;
    }
    else if (ch == '=' || ch == '!' || ch == '<' || ch == '>' || ch == ';' || ch == '(' || ch == ')' || ch == ':' || ch == '[' || ch == ']' || ch == ',')
    {
        s.token_class = Comparison;
    }
    else if (ch == ' ' || ch == '\t')
    {
        s.token_class = Space;
    }
    else if (ch == '\n')
    {
        s.token_class = EndOfLine;
    }
    else if (ch == EOF)
    {
        s.token_class = EndOfFile;
    }
    else if (ch >= 'A' && ch <= 'z')
    {
        s.token_class = Symbol;
        s.value_c = ch;
    }
    else
    {
        s.token_class = Error;
    }
    return s;
}


Lexeme* Inc_size(Lexeme* Table)
{
    Lexeme* New_Table = new Lexeme[size_ * 2];
    for (int i = 0; i < size_; i++)
    {
        New_Table[i].int_or_char = Table[i].int_or_char;
        New_Table[i].Word = Table[i].Word;
        New_Table[i].number_line = Table[i].number_line;
        New_Table[i].value_char = Table[i].value_char;
        New_Table[i].value_int = Table[i].value_int;
    }
    size_ *= 2;
    delete[] Table;
    Table = New_Table;
    return Table;

}
void Inc_arr(int* arr)
{
    delete[] arr;
    int* newArr = new int[size_array_ * 2];
    for (int i = 0; i < size_array_; i++) {
        newArr[i] = arr[i];
    }
    size_array_ *= 2;
    arr = new int[size_array_ * 2];
    for (int i = 0; i < size_array_; i++) {
        arr[i] = newArr[i];
    } // Возвращаем указатель на новый массив
}

void Print_Table_Lexem(Lexeme* Table, int size_)
{
    int j = 1;
    for (int i = 0; i < size_;)
    {
        cout << j;
        cout << "|";
        while (Table[i].number_line == j && i < size_)
        {
            See_number(Table[i].Word, Table[i].value_char, Table[i].value_int);
            cout << " ";
            i++;
        }
        j++;
        cout << endl;
    }
}
struct Initial_vector
{
    char symbol;
    int detection;
};
void Initial_Vect(Initial_vector* vec_)
{
    vec_[1].symbol = 'w';
    vec_[1].detection = 17;
    vec_[2].symbol = 'r';
    vec_[2].detection = 58;
    vec_[3].symbol = 'e';
    vec_[3].detection = 4;
    vec_[4].symbol = 'j';
    vec_[4].detection = 1;
    vec_[5].symbol = 's';
    vec_[5].detection = 34;
    vec_[6].symbol = 'c';
    vec_[6].detection = 24;
    vec_[7].symbol = 'd';
    vec_[7].detection = 60;
    vec_[8].symbol = 'f';
    vec_[8].detection = 61;
    vec_[9].symbol = 't';
    vec_[9].detection = 52;
    vec_[10].symbol = 'i';
    vec_[10].detection = 12;
    vec_[11].symbol = 'v';
    vec_[11].detection = 63;
    vec_[12].symbol = 'o';
    vec_[12].detection = 68;
}
struct Detection_Table
{
    int state = Sy_B1;
    char symbol;
    int alternative = 0;
};

void Detection_Tab(Detection_Table* table_)
{
    //Error
    table_[0].state = Error;

    //jump 
    table_[1].symbol = 'u';
    table_[2].symbol = 'm';
    table_[3].symbol = 'p';
    table_[3].state = Sy_J1;

    //end
    table_[4].symbol = 'n';
    table_[4].alternative = 6;
    table_[5].symbol = 'd';
    table_[5].state = Sy_E1;
    //else
    table_[6].symbol = 'l';
    table_[6].alternative = 9;
    table_[7].symbol = 's';
    table_[8].symbol = 'e';
    table_[8].state = Sy_E3;
    //each
    table_[9].symbol = 'a';
    table_[10].symbol = 'c';
    table_[11].symbol = 'h';
    table_[11].state = Sy_E2;

    //int
    table_[12].symbol = 'n';
    table_[12].alternative = 16;
    table_[13].symbol = 't';
    table_[13].alternative = 15;
    table_[13].state = Sy_I3;
    //in
    table_[14].symbol = 'n';
    table_[15].symbol = ' ';
    table_[15].state = Sy_I2;
    //if
    table_[16].symbol = 'f';
    table_[16].alternative = 13;
    table_[16].state = Sy_I1;

    //while
    table_[17].symbol = 'h';
    table_[18].symbol = 'i';
    table_[18].alternative = 22;
    table_[19].symbol = 'l';
    table_[20].symbol = 'e';
    table_[20].state = Sy_W1;
    //when
    table_[21].symbol = 'h';
    table_[22].symbol = 'e';
    table_[23].symbol = 'n';
    table_[23].state = Sy_W2;

    //concat
    table_[24].symbol = 'o';
    table_[24].alternative = 29;
    table_[25].symbol = 'n';
    table_[25].alternative = 32;
    table_[26].symbol = 'c';
    table_[27].symbol = 'a';
    table_[28].symbol = 't';
    table_[28].state = Sy_C1;
    //cin
    table_[29].symbol = 'i';
    table_[30].symbol = 'n';
    table_[30].state = Sy_C2;
    //cout
    table_[31].symbol = 'o';
    table_[32].symbol = 'u';
    table_[33].symbol = 't';
    table_[33].state = Sy_C3;


    //shiftl
    table_[34].symbol = 'h';
    table_[34].alternative = 40;
    table_[35].symbol = 'i';
    table_[36].symbol = 'f';
    table_[37].symbol = 't';
    table_[38].symbol = 'l';
    table_[38].state = Sy_S1;
    table_[38].alternative = 39;
    //shiftr
    table_[39].symbol = 'r';
    table_[39].state = Sy_S2;
    //subvec
    table_[40].symbol = 'u';
    table_[40].alternative = 45;
    table_[41].symbol = 'b';
    table_[42].symbol = 'v';
    table_[43].symbol = 'e';
    table_[44].symbol = 'c';
    table_[44].state = Sy_S3;
    //set
    table_[45].symbol = 'e';
    table_[45].alternative = 47;
    table_[46].symbol = 't';
    table_[46].state = Sy_S4;
    //switch
    table_[47].symbol = 'w';
    table_[48].symbol = 'i';
    table_[49].symbol = 't';
    table_[50].symbol = 'c';
    table_[51].symbol = 'h';
    table_[51].state = Sy_S5;

    //then
    table_[52].symbol = 'h';
    table_[53].symbol = 'e';
    table_[53].alternative = 55;
    table_[54].symbol = 'n';
    table_[54].state = Sy_T1;
    //throw
    table_[55].symbol = 'r';
    table_[56].symbol = 'o';
    table_[57].symbol = 'w';
    table_[57].state = Sy_T2;

    //rem
    table_[58].symbol = 'e';
    table_[59].symbol = 'm';
    table_[59].state = Sy_R1;

    //do
    table_[60].symbol = 'o';
    table_[60].state = Sy_D1;

    //for
    table_[61].symbol = 'o';
    table_[62].symbol = 'r';
    table_[62].state = Sy_F1;

    //vector
    table_[63].symbol = 'e';
    table_[64].symbol = 'c';
    table_[65].symbol = 't';
    table_[66].symbol = 'o';
    table_[67].symbol = 'r';
    table_[67].state = Sy_V1;

    //otherwise
    table_[68].symbol = 't';
    table_[69].symbol = 'h';
    table_[70].symbol = 'e';
    table_[71].symbol = 'r';
    table_[72].symbol = 'w';
    table_[73].symbol = 'i';
    table_[74].symbol = 's';
    table_[75].symbol = 'e';
    table_[75].state = Sy_O1;
}
Lexeme* Lexical_analyzer(const char* filename)
{
    ifstream in(filename);
    if (!in)
    {
        cout << "Не удалось открыть файл " << filename << endl;
    }
    int count_line = 1;
    Initial_vector vec_[13];
    Initial_Vect(vec_);
    int arr_vect[5];
    int size_arr_vect = 0;
    Detection_Table table_[76];
    Detection_Tab(table_);
    Lexeme* Table_Of_Lexemes = new Lexeme[size_];
    int ch;
    int zn = 0;
    string Lex;
    Vector a;
    SymbolicToken s;
    int detection = 0;
    int alternative = 0;
    int state = A1;
    bool stop = false;
    int date;
    while (!stop)
    {
        ch = in.get();
        s = transliterator(ch);
        switch (state)
        {
        case A1:
            Lex = "";
            if (Value_Word_Lexems >= size_ - 1)
            {
                Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
            }
            switch (s.token_class)
            {
            case Symbol:
                Lex += ch;
                for (int j = 0; j <= 12; j++)
                {
                    if (ch == vec_[j].symbol)
                    {
                        state = Sy_B1;
                        detection = vec_[j].detection;
                        break;
                    }
                }
                if (state != Sy_B1)
                {
                    if (ch >= 'A' && ch <= 'Z')
                    {
                        state = Sy_L1;
                    }
                    else
                    {
                        state = Sy_Z50;
                    }
                    break;
                }
                break;
            case Arithmetic:
                state = Ar_A1;
                Lex += ch;
                break;
            case Digit:
                state = Sy_Z60;
                date = ch - '0';
                break;
            case Space:
                break;

            case Comparison:
                if (ch == '=')
                {
                    Lex += ch;
                    state = Ar_A1;
                    break;
                }
                else if (ch == '[')
                {
                    Lex += ch;
                    state = Ar_B2;
                }
                else
                {
                    Lex += ch;
                    state = Co_B2;
                    break;
                }
                break;
            case EndOfLine:
                count_line++;
                break;
            case EndOfFile:
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_B1:
        {
            while (detection != 0)
            {
                if (ch == table_[detection].symbol)
                {
                    state = table_[detection].state;
                    detection++;
                    break;
                }
                else
                {
                    detection = table_[detection].alternative;
                }
            }
            if (detection == 0 && state == Sy_B1)
            {
                state = Sy_Z50;
                break;
            }
            if (state == Sy_I2)
            {
                Table_Of_Lexemes[Value_Word_Lexems].Word = 7;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            }
            Lex += ch;
        }
        break;
        case Ar_A1:

            if (Lex == "&")
                zn = 25;
            if (Lex == "+")
                zn = 13;
            if (Lex == "-")
                zn = 14;
            if (Lex == "*")
                zn = 15;
            if (Lex == "%")
                zn = 16;
            if (Lex == "/")
                zn = 17;
            if (Lex == "=")
                zn = 9;
            if (Lex == ">=")
                zn = 11;
            if (Lex == "<=")
                zn = 12;
            if (Lex == "!=")
                zn = 10;
            if (Lex == "<<")
                zn = 29;
            if (Lex == ">>")
                zn = 28;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;

                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                count_line++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Co_B2: // >= <= !=
            if (Lex == ">")
                zn = 18;
            if (Lex == "<")
                zn = 19;
            if (Lex == ";")
                zn = 24;
            if (Lex == "(")
                zn = 43;
            if (Lex == ")")
                zn = 44;
            switch (s.token_class)
            {
            case Comparison:
                if (ch == '=' || ch == '<' || ch == '>' || ch == ';')
                {
                    Lex += ch;
                    state = Ar_A1;
                }
                break;
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                count_line++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_L1:
        {
            if (zn != 46)
            {
                zn = 39;
            }
            switch (s.token_class)
            {
            case Comparison:
                if (ch == ':')
                {
                    Lex += ch;
                    zn = 46;
                    break;
                }
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].value_char = Lex;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 0;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                Lex = "";
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Table_Of_Lexemes[Value_Word_Lexems].value_char = Lex;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 0;
                count_line++;
                Value_Word_Lexems++;
                Lex = "";
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Table_Of_Lexemes[Value_Word_Lexems].value_char = Lex;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 0;
                Lex = "";
                Value_Word_Lexems++;
                stop = true;
                break;
            case Digit:
                Lex += ch;
                break;
            case Symbol:
                Lex += ch;
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_J1:
        {
            zn = 32;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_E1:
        {
            zn = 6;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_E3:
        {
            zn = 3;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_E2:
        {
            zn = 5;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_I1:
        {
            zn = 1;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_I3:
        {
            zn = 37;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_W1:
        {
            zn = 4;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_W2:
        {
            zn = 34;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_C1:
        {
            zn = 22;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_C2:
        {
            zn = 8;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_C3:
        {
            zn = 30;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_S1:
        {
            zn = 21;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_S2:
        {
            zn = 20;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_S3:
        {
            zn = 23;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_S4:
        {
            zn = 26;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_S5:
        {
            zn = 33;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_T1:
        {
            zn = 2;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_T2:
        {
            zn = 35;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_R1:
        {
            zn = 36;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                while (ch != '\n' && ch != EOF)
                    ch = in.get();
                if (ch == '\n')
                    count_line++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_F1:
        {
            zn = 27;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_V1:
        {
            zn = 38;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_O1:
        {
            zn = 47;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
            }
        }
        break;
        case Sy_D1:
        {
            zn = 40;
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = zn;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            case Digit:
                state = Sy_Z50;
                break;
            case Symbol:
                state = Sy_Z50;
                break;
            default:
                state = Stop;
                break;
            }
        }
        break;
        case Sy_Z50:
        {
            switch (s.token_class)
            {
            case Digit:
                Lex += ch;
                break;
            case Symbol:
                Lex += ch;
                break;
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 41;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 0;
                Table_Of_Lexemes[Value_Word_Lexems].value_char = Lex;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                Lex = "";
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 41;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 0;
                Table_Of_Lexemes[Value_Word_Lexems].value_char = Lex;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 41;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 0;
                Table_Of_Lexemes[Value_Word_Lexems].value_char = Lex;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                Lex = "";
                break;

            default:
                state = Stop;
                break;
            }
        }
        break;
        case Sy_Z60:
            switch (s.token_class)
            {
            case Digit:
                date = date * 10 + (ch - '0');
                break;
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 45;
                Table_Of_Lexemes[Value_Word_Lexems].value_int = date;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 1;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                date = 0;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 45;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Table_Of_Lexemes[Value_Word_Lexems].value_int = date;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 1;
                count_line++;
                Value_Word_Lexems++;
                date = 0;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 45;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Table_Of_Lexemes[Value_Word_Lexems].value_int = date;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 1;
                date = 0;
                stop = true;
                Value_Word_Lexems++;
                break;

            default:
                state = Stop;
                break;
            }
            break;
        case Ar_B2://число в массиве
            switch (s.token_class)
            {
            case Digit:
                arr_vect[size_arr_vect] = ch - '0';
                state = Ar_C2;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Ar_C2://увеличение числа в массиве
            switch (s.token_class)
            {
            case Digit:
                arr_vect[size_arr_vect] = 10 * arr_vect[size_arr_vect] + ch - '0';
                state = Ar_C2;
                break;
            case Space:
                break;
            case Comparison:
                if (ch == ',')
                {
                    state = Ar_B2;
                    size_arr_vect++;
                    if (size_arr_vect >= size_array_)
                    {
                        Inc_arr(arr_vect);
                    }
                }
                else if (ch == ']')
                    state = Ar_D2;
                else
                {
                    state = Stop;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Ar_D2:
            switch (s.token_class)
            {

            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 48;
                Table_Of_Lexemes[Value_Word_Lexems].value_vector.Vector_by_arr(arr_vect, size_arr_vect);
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 2;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 48;
                Table_Of_Lexemes[Value_Word_Lexems].value_vector.Vector_by_arr(arr_vect, size_arr_vect);
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 2;
                count_line++;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 48;
                Table_Of_Lexemes[Value_Word_Lexems].value_vector.Vector_by_arr(arr_vect, size_arr_vect);
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Table_Of_Lexemes[Value_Word_Lexems].int_or_char = 2;
                stop = true;
                Value_Word_Lexems++;
                break;

            default:
                state = Stop;
                break;
            }
            break;
        case Stop:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 42;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                state = A1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 42;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                Value_Word_Lexems++;
                count_line++;
                state = A1;
                break;
            case EndOfFile:
                Table_Of_Lexemes[Value_Word_Lexems].Word = 42;
                Table_Of_Lexemes[Value_Word_Lexems].number_line = count_line;
                stop = true;
                Value_Word_Lexems++;
                break;
            default:
                state = Stop;
                break;
            }
        }
    }
    return Table_Of_Lexemes;
    in.close();
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUS");
    Lexeme* Table = new Lexeme[size_];
    char file_name[] = "i.txt";
    Table = Lexical_analyzer(file_name);
    Print_Table_Lexem(Table, Value_Word_Lexems);
    return 0;
}