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
int Warning = 0;
// Перечисление содержит константы для обозначения классов символьных лексем: ЦИФРА, ЗНАК, ПРОБЕЛ, ОШИБКА, КОНЕЦ.
enum SymbolicTokenClass {Symbol, Digit, Arithmetic, Comparison, EndOfLine, Semicolon, Space, Error, EndOfFile };

// Перечисление содержит константы для обозначения состояний автомата и одну дополнительную константу Stop.
enum States { 
    A1, /*начало*/
    Sy_B1, /*все лексемы*/
    Sy_D8, Sy_D2, /*Константа*/
    Sy_E4, Sy_F4, /*Числа*/
    Ar_B1, /*проверка до ;*/
    Co_B2, /* < >*/
    Sy_Z1, /* pop */
    Sy_Z2, /*write*/
    Sy_Z3, /*read*/
    Sy_Z4, /*end*/
    Sy_Z5, /*jmp*/
    Sy_Z6, /*push*/
    Sy_E2, /*push x || push 1*/
    Sy_Z7,/*shiftl*/
    Sy_Z8, /*shiftr*/
    Sy_Z9, /*+,-,%,>=,<=.....*/
    Sy_Z10,/*ji*/
    Sy_Z11,/*subvec*/
    Sy_Z12,/*concat*/
    Stop };

// Структура для представления символьной лексемы.
struct SymbolicToken
{
    SymbolicTokenClass token_class; // Класс лексемы.
    int value;                      // Значение лексемы.
    char value_c;

};
//Word:
// push число = 1
// push значение = 2
// pop = 3
// write = 4
// read = 5
// end = 6
// ji = 7
// jmp = 8
// = = 9
// != = 10
// >= = 11
// <= = 12
// + = 13
// - = 14
// * = 15
// % = 16
// / = 17
// > = 18
// < = 19
// shiftr = 20
// shiftl =21
// concat = 22
// subvec = 23
// ; = 24
// & = 25
struct Lexeme
{
    int number_line = 0;
    vector<int> Word;
    int value_int;
    string value_char;
    int int_or_char = -1; // Если символ-0, если цифра-1

};


void See_number(int number)
{
    if (number == 1)
        cout << "push";
    if (number == 2)
        cout << "push";
    if (number == 3)
        cout << "pop";
    if (number == 4)
        cout << "write";
    if (number == 5)
        cout << "read";
    if (number == 6)
        cout << "end";
    if (number == 7)
        cout << "ji";
    if (number == 8)
        cout << "jmp";
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
}

void Print_Table_Lex(Lexeme* Table)
{
    cout << left << setw(10) << "Номер" << setw(10) << "Лексема" << right << setw(10) << "Значение" << endl;
    for (int i = 0; i < size_ + 1; i++)
    {

        if (Table[i].int_or_char == 0)
        {
            cout << left << setw(10) << Table[i].number_line << right << setw(15);
            for (int j = 0; j < Table[i].Word.size(); j++)
            {
                cout << left << setw(1);
                See_number(Table[i].Word[j]);
            }
            cout << right << setw(8);
            cout << " " << right << setw(5);
            cout << Table[i].value_char << endl;
        }
        else if (Table[i].int_or_char == 1)
        {
            cout << left << setw(10) << Table[i].number_line << right << setw(15);
            for (int j = 0; j < Table[i].Word.size(); j++)
            {
                cout << left << setw(1);
                See_number(Table[i].Word[j]);
            }
            cout << right << setw(8);
            cout << " " << right << setw(5);
            cout << Table[i].value_int << endl;

        }
        else
        {
            cout << left << setw(10) << Table[i].number_line << right << setw(15);
            for (int j = 0; j < Table[i].Word.size(); j++)
            {
                cout << left << setw(1);
                See_number(Table[i].Word[j]);
            }
            cout << endl;
        }
    }
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
    else if (ch == '=' || ch == '!' || ch == '<' || ch == '>')
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
    else if (ch == ';')
    {
        s.token_class = Semicolon;
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
    Lexeme* New_Table = new Lexeme[size_*2];
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

struct Initial_vector
{
    char symbol;
    int detection;
};
void Initial_Vect(Initial_vector* vec_)
{
    vec_[0].symbol = 'p';
    vec_[0].detection = 6;
    vec_[1].symbol = 'w';
    vec_[1].detection = 14;
    vec_[2].symbol = 'r';
    vec_[2].detection = 11;
    vec_[3].symbol = 'e';
    vec_[3].detection = 1;
    vec_[4].symbol = 'j';
    vec_[4].detection = 3;
    vec_[5].symbol = 's';
    vec_[5].detection = 23;
    vec_[6].symbol = 'c';
    vec_[6].detection = 18;
}
struct Detection_Table
{
    int state = Sy_B1;
    char symbol;
    int alternative = 0;
};

void Detection_Tab(Detection_Table* table_)
{
    table_[0].state = Error;
    table_[1].symbol = 'n';
    table_[2].symbol = 'd';
    table_[2].state = Sy_Z4;
    table_[3].symbol = 'i';
    table_[3].alternative = 4;
    table_[3].state = Sy_Z10;
    table_[4].symbol = 'm';
    table_[5].symbol = 'p';
    table_[5].state = Sy_Z5;
    table_[6].symbol = 'o';
    table_[6].alternative = 8;
    table_[7].symbol = 'p';
    table_[7].state = Sy_Z1;
    table_[8].symbol = 'u';
    table_[9].symbol = 's';
    table_[10].symbol = 'h';
    table_[10].state = Sy_Z6;
    table_[11].symbol = 'e';
    table_[12].symbol = 'a';
    table_[13].symbol = 'd';
    table_[13].state = Sy_Z3;
    table_[14].symbol = 'r';
    table_[15].symbol = 'i';
    table_[16].symbol = 't';
    table_[17].symbol = 'e';
    table_[17].state = Sy_Z2;
    table_[18].symbol = 'o';
    table_[19].symbol = 'n';
    table_[20].symbol = 'c';
    table_[21].symbol = 'a';
    table_[22].symbol = 't';
    table_[22].state = Sy_Z12;
    table_[23].symbol = 'h';
    table_[23].alternative = 29;
    table_[24].symbol = 'i';
    table_[25].symbol = 'f';
    table_[26].symbol = 't';
    table_[27].symbol = 'l';
    table_[27].state = Sy_Z7;
    table_[27].alternative = 28;
    table_[28].symbol = 'r';
    table_[28].state = Sy_Z8;
    table_[29].symbol = 'u';
    table_[30].symbol = 'b';
    table_[31].symbol = 'v';
    table_[32].symbol = 'e';
    table_[33].symbol = 'c';
    table_[33].state = Sy_Z11;
}
Lexeme* Lexical_analyzer(const char* filename)
{
    ifstream in(filename);
    if (!in)
    {
        cout << "Не удалось открыть файл " << filename << endl;
    }
    int count_line = 0;
    Initial_vector vec_[7];
    Initial_Vect(vec_);
    Detection_Table table_[34]; 
    Detection_Tab(table_);
    Lexeme* Table_Of_Lexemes = new Lexeme[size_];
    int ch;             
    string Lex;        
    SymbolicToken s;  
    int detection = 0;
    int alternative = 0;
    int state = A1;
    string number_c = "";
    bool stop = false; 
    while (!stop)
    {
        ch = in.get();
        s = transliterator(ch);
        switch (state)
        {
        case A1:
            Table_Of_Lexemes[count_line].number_line = count_line + 1;
            switch (s.token_class)
            {
            case Symbol:
                Lex += ch;
                for (int j = 0; j < 7; j++)
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
                    state = Stop;
                    break;
                }
                break;
            case Arithmetic:
                state = Sy_Z9;
                Lex += ch;
                break;

            case Space:
                break;

            case Semicolon:
                while (ch != '\n' && ch != EOF)
                    ch = in.get();
                Table_Of_Lexemes[count_line].Word.push_back(24);
                if (ch == EOF)
                    stop = true;
                else
                {
                    if (count_line >= size_ - 1)
                        Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                    count_line++;
                }
                state = A1;
                Lex = "";
                break;

            case Comparison:
                if (ch == '=')
                {
                    Lex += ch;
                    state = Sy_Z9;
                    break;
                }
                else
                {
                    Lex += ch;
                    state = Co_B2;
                    break;
                }

            default:
                state = Stop;
                break;
            }
            break;
        case Sy_B1:
        {
            switch (s.token_class)
            {
            case Symbol:
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
            }
            break;
            default:
                state = Stop;
                break;
            }
        }
        break;
        case Sy_Z9:
            int zn;
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
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(zn);
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(zn);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(zn);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Co_B2: // >= <= !=
            int zn_;
            if (Lex == ">")
                zn_ = 18;
            if (Lex == "<")
                zn_ = 19;
            switch (s.token_class)
            {
            case Comparison:
                if (ch == '=')
                {
                    Lex += ch;
                    state = Sy_Z9;
                }
                break;
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(zn_);
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(zn_);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            default:
                state = Stop;
                break;
            }
            break;

        case Ar_B1: // +-*/%
            switch (s.token_class)
            {
            case Space:
                state = Ar_B1;
                break;
            case EndOfLine:
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case Semicolon:
                while (ch != '\n' && ch != EOF)
                    ch = in.get();
                Table_Of_Lexemes[count_line].Word.push_back(24);
                if (ch == EOF)
                {
                    stop = true;
                }
                else
                {
                    if (count_line >= size_ - 1)
                        Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                    count_line++;
                }
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z6:
            switch (s.token_class)
            {
            case Space:
                state = Sy_E2;
                break;
            case EndOfLine:
                state = Error;
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_E2: //push
            switch (s.token_class)
            {
            case Space:
                break;

            case Symbol:
                Table_Of_Lexemes[count_line].Word.push_back(2);
                Table_Of_Lexemes[count_line].int_or_char = 0;
                state = Sy_D8;
                number_c = ch;
                break;
            case Digit:
                Table_Of_Lexemes[count_line].Word.push_back(1);
                Table_Of_Lexemes[count_line].int_or_char = 1;
                Table_Of_Lexemes[count_line].value_int = s.value;
                state = Sy_F4;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z1:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(3);
                state = Sy_D2;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(3);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(3);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_D2:
            switch (s.token_class)
            {
            case Space:
                break;
            case Symbol:

                Table_Of_Lexemes[count_line].int_or_char = 0;
                number_c = s.value_c;
                state = Sy_D8;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_D8:
            switch (s.token_class)
            {
            case Space:
                for (int j = 0, i = 0; j < 7; j++)
                {
                    if (number_c[i] == vec_[j].symbol)
                    {
                        detection = vec_[j].detection;
                        j = 7;
                        i++;
                        while (detection != 0 && detection != 2 && detection != 3 && detection != 5 && detection != 7 && detection != 10 && detection != 13 && detection != 17 && detection != 22 && detection != 27 && detection != 28 && detection != 33)
                        {
                            if (number_c[i] == table_[detection].symbol)
                            {
                                detection++;
                                i++;
                            }
                            else
                            {
                                detection = table_[detection].alternative;
                            }
                        }
                        if (detection == 0)
                        {
                            Table_Of_Lexemes[count_line].value_char = number_c;
                            state = Ar_B1;
                            Lex = "";
                            break;
                        }
                        else
                        {
                            if (number_c.size() <= i + 1)
                            {
                                state = Stop;
                                break;
                            }
                            else
                            {
                                Table_Of_Lexemes[count_line].value_char = number_c;
                                state = Ar_B1;
                                Lex = "";
                                break;
                            }
                        }
                    }
                }
                Table_Of_Lexemes[count_line].value_char = number_c;
                state = Ar_B1;
                Lex = "";
                break;
            case EndOfLine:
                for (int j = 0,i = 0; j < 7; j++)
                {
                    if (number_c[i] == vec_[j].symbol)
                    {
                        detection = vec_[j].detection;
                        j = 7;
                        i++;
                        while (detection != 0 && detection != 2 && detection != 3 && detection != 5 && detection != 7 && detection != 10 && detection != 13 && detection != 17 && detection != 22 && detection != 27 && detection != 28 && detection != 33)
                        {
                            if (number_c[i] == table_[detection].symbol)
                            {
                                detection++;
                                i++;
                            }
                            else
                            {
                                detection = table_[detection].alternative;
                            }
                        }
                        if (detection == 0)
                        {
                            Table_Of_Lexemes[count_line].value_char = number_c;
                            state = A1;
                            Lex = "";
                            break;
                        }
                        else
                        {
                            if (number_c.size() <= i+1)
                            {
                                state = Stop;
                                if (count_line >= size_ - 1)
                                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                                count_line++;
                                break;
                            }
                            else
                            {
                                Table_Of_Lexemes[count_line].value_char = number_c;
                                state = A1;
                                Lex = "";
                                break;
                            }
                        }
                    }
                }
                Table_Of_Lexemes[count_line].value_char = number_c;
                state = A1;
                Lex = "";
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                break;    
            case EndOfFile:
                for (int j = 0, i = 0; j < 7; j++)
                {
                    if (number_c[i] == vec_[j].symbol)
                    {
                        detection = vec_[j].detection;
                        j = 7;
                        i++;
                        while (detection != 0 && detection != 2 && detection != 3 && detection != 5 && detection != 7 && detection != 10 && detection != 13 && detection != 17 && detection != 22 && detection != 27 && detection != 28 && detection != 33)
                        {
                            if (number_c[i] == table_[detection].symbol)
                            {
                                detection++;
                                i++;
                            }
                            else
                            {
                                detection = table_[detection].alternative;
                            }
                        }
                        if (detection == 0)
                        {
                            Table_Of_Lexemes[count_line].value_char = number_c;
                            state = A1;
                            Lex = "";
                            break;
                        }
                        else
                        {
                            if (number_c.size() <= i + 1)
                            {
                                state = Stop;
                                break;
                            }
                            else
                            {
                                Table_Of_Lexemes[count_line].value_char = number_c;
                                state = A1;
                                Lex = "";
                                break;
                            }
                        }
                    }
                }
                Table_Of_Lexemes[count_line].value_char = number_c;
                state = A1;
                Lex = "";
                break;
                break;
            case Symbol:
                number_c += ch;
                break;
            case Digit:
                number_c += ch;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z2:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(4);
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(4);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(4);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z3:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(5);
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(5);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(5);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_E4:
            switch (s.token_class)
            {
            case Space:
                state = Sy_E4;
                break;
            case Digit:
                Table_Of_Lexemes[count_line].int_or_char = 1;
                Table_Of_Lexemes[count_line].value_int = s.value;
                state = Sy_F4;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_F4:
            switch (s.token_class)
            {
            case Space:
                state = Ar_B1;
                break;
            case Digit:
                Table_Of_Lexemes[count_line].value_int = Table_Of_Lexemes[count_line].value_int * 10 + s.value;
                break;
            case EndOfLine:
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z4:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(6);
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(6);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(6);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z11:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(23);
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(23);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(23);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z12:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(22);
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(22);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(22);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z5:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(8);
                state = Sy_E4;
                break;

            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(8);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(8);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z10:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(7);
                state = Sy_E4;
                break;

            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(7);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(7);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z7:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(21);
                state = Sy_E4;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(21);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(21);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z8:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word.push_back(20);
                state = Sy_E4;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word.push_back(20);
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word.push_back(20);
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;

        case Stop:
            cout << "Обнаружена ошибка в строке №" << count_line + 1 << endl;
            Warning = 1;
            while (ch != '\n' && ch != EOF)
                ch = in.get();
            if (ch == EOF)
            {
                stop = true;
            }
            else
            {
                if (count_line >= size_-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
            }
            state = A1;
            Lex = "";
            break;
        }
    }
    size_ = count_line;
    return Table_Of_Lexemes;
    in.close();
}

struct Variable
{
    string name = "";
    int type = -1;
    int integer_value;
    Vector vector_value;
};
void Interpreter_int(Lexeme* Table_Lex)
{
    char ch = 0;
    stack<Variable> st;
    vector<Variable> vect_variable_mean;
    int line = 0;
    while (Table_Lex[line].Word.empty())
        line++;
    while (line < size_ && Table_Lex[line].Word.back() != 6)
    {
        if (Table_Lex[line].Word[0] == 5)
        {
            Variable value;
            if(cin.peek() == '[')
            {          
                cin >> value.vector_value;
                value.type = 0;//символ
                st.push(value);
                cin.ignore();
            }
            else
            {
                cin >> value.integer_value;
                value.type = 1;
                st.push(value);
            }
            line++;
        }
        else if (Table_Lex[line].Word[0] == 1 || Table_Lex[line].Word[0] == 2)
        {
            if (Table_Lex[line].int_or_char == 0)//символ
            {
                int h = -1;
                for (int i = 0; i < vect_variable_mean.size(); i++)
                {
                    if (vect_variable_mean[i].name == Table_Lex[line].value_char)
                    {
                        st.push(vect_variable_mean[i]);
                        h = 1;
                        break;
                    }
                }
            }
            if (Table_Lex[line].int_or_char == 1)//цифра
            {
                Variable value;
                value.integer_value = Table_Lex[line].value_int;
                value.type = 1;
                st.push(value);
            }
            line++;
        }

        else if (Table_Lex[line].Word[0] == 3)
        {
            if (Table_Lex[line].int_or_char == 0)
            {
                int h = -1;
                for (int i = 0; i < vect_variable_mean.size(); i++)
                {
                    if (vect_variable_mean[i].name == Table_Lex[line].value_char)
                    {
                        h = i;
                    }
                }
                if (h == -1)
                {
                    Variable c;
                    c = st.top(); st.pop();
                    c.name = Table_Lex[line].value_char;
                    vect_variable_mean.push_back(c);
                }
                else
                {
                    Variable c;
                    c = st.top(); st.pop();
                    c.name = vect_variable_mean[h].name;
                    vect_variable_mean[h] = c;
                }
            }
            line++;
        }

        else if (Table_Lex[line].Word[0] == 7)
        {
            if (Table_Lex[line].int_or_char == 1)
            {
                Variable val = st.top();
                if (val.integer_value == 0)
                {
                    line++;
                    st.pop();
                }
                else
                {
                    line = Table_Lex[line].value_int-1;
                    st.pop();
                }
            }
            else
            {
                line++;
            }
        }

        else if (Table_Lex[line].Word[0] == 8)
        {
            if (Table_Lex[line].int_or_char = 1)
            {
                line = Table_Lex[line].value_int-1;
            }
            else
            {
                line++;
            }
        }

        else if (Table_Lex[line].Word[0] == 13 || Table_Lex[line].Word[0] == 14 || Table_Lex[line].Word[0] == 15 || Table_Lex[line].Word[0] == 16 || Table_Lex[line].Word[0] == 17 || Table_Lex[line].Word[0] == 25)
        {
            Variable b = st.top(); st.pop();
            Variable a = st.top(); st.pop();
            Variable c;
            if (a.type == 1 && b.type == 1)
            {
                c.type = 1;

                if (Table_Lex[line].Word[0] == 13)
                {
                    c.integer_value = a.integer_value + b.integer_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 14)
                {
                    c.integer_value = a.integer_value - b.integer_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 15)
                {
                    c.integer_value = a.integer_value * b.integer_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 17)
                {
                    if (b.integer_value == 0)
                    {
                        cout << "На ноль делить нельзя" << endl;
                        st.push(b);
                        st.push(a);
                        cout << "Значения были возвращенны в стек";
                    }
                    else
                    {
                        c.integer_value = a.integer_value / b.integer_value;
                        st.push(c);
                    }
                }
                else if (Table_Lex[line].Word[0] == 16)
                {
                    if (b.integer_value == 0)
                    {
                        cout << "На ноль делить нельзя" << endl;
                        st.push(b);
                        st.push(a);
                        cout << "Значения были возвращенны в стек";
                    }
                    else
                    {
                        c.integer_value = a.integer_value % b.integer_value;
                        st.push(c);
                    }
                }
            }
            else if(a.type == 0 && b.type == 0)
            {
                c.type = 0;
                if (Table_Lex[line].Word[0] == 13)
                {
                    c.vector_value = a.vector_value + b.vector_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 14)
                {
                    c.vector_value = a.vector_value - b.vector_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 15)
                {
                    c.vector_value = a.vector_value * b.vector_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 17)
                {
                    c.vector_value = a.vector_value / b.vector_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 16)
                {
                    c.vector_value = a.vector_value % b.vector_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 25)
                {
                    c.integer_value = a.vector_value & b.vector_value;
                    c.type = 1;
                    st.push(c);
                }
            }
            line++;
        }
        else if (Table_Lex[line].Word[0] == 20 || Table_Lex[line].Word[0] == 21)
        {
            int a = Table_Lex[line].value_int;
            Variable c = st.top(); st.pop();
            if (Table_Lex[line].Word[0] == 20)
            {
                c.vector_value.Shift_right(a);
                st.push(c);
            }
            else
            {
                c.vector_value.Shift_left(a);
                st.push(c);
            }
            line++;
        }
        else if (Table_Lex[line].Word[0] == 22)
        {
            Variable a = st.top(); st.pop();
            Variable b = st.top(); st.pop();
            Variable c;
            c.type = 0;
            c.vector_value = b.vector_value.Concatenation(a.vector_value);
            st.push(c);
            line++;
        }
        else if (Table_Lex[line].Word[0] == 23)
        {
            Variable to = st.top(); st.pop();
            Variable from = st.top(); st.pop();
            Variable a = st.top(); st.pop();
            Variable c;
            c.type = 0;
            c.vector_value = a.vector_value.Subvector_Selection(from.integer_value, to.integer_value);
            st.push(c);
            line++;
        }
        else if (Table_Lex[line].Word[0] == 9 || Table_Lex[line].Word[0] == 10 || Table_Lex[line].Word[0] == 11 || Table_Lex[line].Word[0] == 12 || Table_Lex[line].Word[0] == 18 || Table_Lex[line].Word[0] == 19)
        {
            Variable b = st.top(); st.pop();
            Variable a = st.top(); st.pop();
            Variable c;
            if (a.type == 1 && b.type == 1)
            {
                c.type = 1;
                if (Table_Lex[line].Word[0] == 9)
                {
                    c.integer_value = a.integer_value == b.integer_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 18)
                {
                    c.integer_value = a.integer_value > b.integer_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 19)
                {
                    c.integer_value = a.integer_value < b.integer_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 11)
                {
                    c.integer_value = a.integer_value >= b.integer_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 12)
                {
                    c.integer_value = a.integer_value <= b.integer_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 10)
                {
                    c.integer_value = a.integer_value != b.integer_value;
                    st.push(c);
                }
            }
            else if (a.type == 1 && b.type == 1)
            {
                c.type = 1;
                if (Table_Lex[line].Word[0] == 9)
                {
                    c.integer_value = a.vector_value == b.vector_value;
                    st.push(c);
                }
                else if (Table_Lex[line].Word[0] == 10)
                {
                    c.integer_value = a.vector_value != b.vector_value;
                    st.push(c);
                }
            }
            line++;
        }

        else if (Table_Lex[line].Word[0] == 4)
        {
            Variable c = st.top(); st.pop();
            if (c.type == 0)
                cout << c.vector_value << endl;
            else
                cout << c.integer_value << endl;
            line++;
        }

        else
        {
            line++;
        }
        while (Table_Lex[line].Word.empty())
            line++;
    }
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUS");
    Lexeme* Table = new Lexeme[size_];
    char file_name[] = "input2_vector.txt";
    Table = Lexical_analyzer(file_name);
    Print_Table_Lex(Table);
    if (!Warning)
    {
        Interpreter_int(Table);
    }
    return 0;
}