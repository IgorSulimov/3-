#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
#include <stack>
#include "Vector.hpp"
#include <variant>
using namespace std;
int size_ = 5;
// Перечисление содержит константы для обозначения классов символьных лексем: ЦИФРА, ЗНАК, ПРОБЕЛ, ОШИБКА, КОНЕЦ.
enum SymbolicTokenClass {Symbol, Digit, Arithmetic, Comparison, EndOfLine, Semicolon, Space, Error, EndOfFile };

// Перечисление содержит константы для обозначения состояний автомата и одну дополнительную константу Stop.
enum States { A1, 
    Sy_B1, Sy_C1, Sy_D1, Sy_E1, Sy_E2, Sy_F1,
    Sy_C2, Sy_D2,
    Sy_B2, Sy_C3, Sy_D3, Sy_E3,
    Sy_B3, Sy_C4, Sy_D4, Sy_E4, Sy_F4,
    Sy_B4, Sy_C5,
    Sy_B5, Sy_C6,
    Ar_B1, 
    Co_B2,
    Sy_B6,Sy_C7,Sy_D7,Sy_E7,Sy_F7,
    Sy_B7,Sy_C8,Sy_D8,Sy_E8,Sy_F8,
    Sy_C9,Sy_D9,Sy_E9,Sy_F9,Sy_G9,Sy_H9,
    Sy_Z1, Sy_Z2, Sy_Z3, Sy_Z4, Sy_Z5, Sy_Z6,Sy_Z7,Sy_Z8,Sy_Z9,
    Stop };

// Структура для представления символьной лексемы.
struct SymbolicToken
{
    SymbolicTokenClass token_class; // Класс лексемы.
    int value;                      // Значение лексемы.
    char value_c;

};

struct Lexeme
{
    int number_line;
    string Word = "";
    int value_int;
    char value_char;
    int int_or_char = -1; // Если символ, то 0, если цифра, то 1
    char semicolon_ = '-';

};


void Print_Table_Lex(Lexeme* Table)
{
    cout << left << setw(6) << "Номер" << setw(7) << "Лексема" << right << setw(7) << ";" << setw(10) << "Значение" << endl;
    for (int i = 0; i < size_ + 1; i++)
    {
        right;
        if (Table[i].int_or_char == 0)
        {
            cout << left << setw(6) << Table[i].number_line << setw(7) << Table[i].Word << right << setw(7) << Table[i].semicolon_ << setw(7) << Table[i].value_char << endl;
        }
        else if (Table[i].int_or_char == 1)
        {
            cout << left << setw(6) << Table[i].number_line << setw(7) << Table[i].Word << right << setw(7) << Table[i].semicolon_ << setw(7) << Table[i].value_int << endl;
        }
        else
        {
            cout << left << setw(6) << Table[i].number_line << setw(7) << Table[i].Word << right << setw(7) << Table[i].semicolon_ << endl;
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
    else if (ch >= 'a' && ch <= 'z')
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
        New_Table[i].semicolon_ = Table[i].semicolon_;
        New_Table[i].value_char = Table[i].value_char;
        New_Table[i].value_int = Table[i].value_int;
    }
    size_ *= 2;
    delete[] Table;
    Table = New_Table;
    return Table;

}



Lexeme* Lexical_analyzer(const char* filename)
{
    ifstream in(filename);
    if (!in)
    {
        cout << "Не удалось открыть файл " << filename << endl;
    }
    int count_line = 0;
    Lexeme* Table_Of_Lexemes = new Lexeme[size_];
    int ch;             
    string Lex;        
    SymbolicToken s;   
    int state = A1;
    char number_c;         
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
                if (ch == 'p')
                {
                    state = Sy_B1;
                    break;
                }
                else if (ch == 'w')
                {
                    state = Sy_B2;
                    break;
                }
                else if (ch == 'r')
                {
                    state = Sy_B3;
                    break;
                }
                else if (ch == 'e')
                {
                    state = Sy_B4;
                    break;
                }
                else if (ch == 'j')
                {
                    state = Sy_B5;
                    break;
                }
                else if (ch == 's')
                {
                    state = Sy_B6;
                    break;
                }
                else if (ch == 'c')
                {
                    state = Sy_B7;
                    break;
                }
                else
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
                if (ch == EOF)
                    stop = true;
                else
                {
                    if (count_line >= size_-1)
                        Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                    count_line++;
                }
                Table_Of_Lexemes[count_line].semicolon_ = '+';
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
                    Table_Of_Lexemes[count_line].Word = Lex;
                    state = Co_B2;
                    break;
                }

            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z9:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word = Lex;
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word = Lex;
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word = Lex;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;

        case Co_B2: // >= <= !=
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
                state = Ar_B1;
                break;
            case EndOfLine:
                if (count_line >= size_-1)
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
                if (count_line >= size_-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case Semicolon:
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
                Table_Of_Lexemes[count_line].semicolon_ = '+';
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

        case Sy_B1: // push or pop
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'u')//push
                {
                    Lex += ch;
                    state = Sy_C1;
                    break;
                }
                else if (ch == 'o') //pop
                {
                    Lex += ch;
                    state = Sy_C2;
                    break;
                }
                else
                {
                    state = Stop;
                    break;
                }
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_C1: // push
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 's')
                {
                    Lex += ch;
                    state = Sy_D1;
                    break;
                }
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_D1: // push
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'h')
                {
                    Lex += ch;
                  
                    state = Sy_E1;
                    break;
                }
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_E1:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word = Lex;
                state = Sy_E2;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word = Lex;
                if (count_line >= size_-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word = Lex;
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
                state = Sy_Z7;
                number_c = ch;
                break;
            case Digit:
                Table_Of_Lexemes[count_line].int_or_char = 1;
                Table_Of_Lexemes[count_line].value_int = s.value;
                state = Sy_F1;
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
                Table_Of_Lexemes[count_line].int_or_char = 0;
                Table_Of_Lexemes[count_line].value_char = number_c;
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].int_or_char = 0;
                Table_Of_Lexemes[count_line].value_char = number_c;
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].int_or_char = 0;
                Table_Of_Lexemes[count_line].value_char = number_c;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_F1: // push
            switch (s.token_class)
            {
            case Space:
                state = Ar_B1;
                break;
            case Digit:
                Table_Of_Lexemes[count_line].value_int = Table_Of_Lexemes[count_line].value_int * 10 + s.value;
                break;
            case EndOfLine:
                if (count_line >= size_-1)
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
        case Sy_C2: // pop
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'p')
                {
                    Lex += ch;
                    state = Sy_Z1;
                    break;
                }
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_Z1:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word = Lex;
                state = Sy_D2;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word = Lex;
                if (count_line >= size_-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word = Lex;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_D2: // pop
            switch (s.token_class)
            {
            case Space:
                break;
            case Symbol:

                Table_Of_Lexemes[count_line].int_or_char = 0;
                number_c = s.value_c;
                state = Sy_Z8;
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
                Table_Of_Lexemes[count_line].value_char = number_c;
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].value_char = number_c;
                if (count_line >= size_-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].value_char = number_c;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_B2: // write
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'r')
                {
                    Lex += ch;
                    state = Sy_C3;
                }
            }
            break;
        case Sy_C3: // write
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'i')
                {
                    Lex += ch;
                    state = Sy_D3;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_D3: // write
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 't')
                {
                    Lex += ch;
                    state = Sy_E3;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_E3: // write
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'e')
                {
                    Lex += ch;
                    state = Sy_Z2;
                }
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
                Table_Of_Lexemes[count_line].Word = Lex;
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word = Lex;
                if (count_line >= size_-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word = Lex;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_B3: // read
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'e')
                {
                    Lex += ch;
                    state = Sy_C4;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_C4: // read
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'a')
                {
                    Lex += ch;
                    state = Sy_D4;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_D4: // read
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'd')
                {
                    Lex += ch;
                    state = Sy_Z3;
                    break;
                }
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
                Table_Of_Lexemes[count_line].Word = Lex;
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word = Lex;
                if (count_line >= size_-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word = Lex;
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
                Table_Of_Lexemes[count_line].value_int = Table_Of_Lexemes[count_line].value_int*10 + s.value;
                state = Sy_F4;
                break;
            case EndOfLine:
                if (count_line >= size_-1)
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
        case Sy_B4: // end
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'n')
                {
                    Lex += ch;
                    state = Sy_C5;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_C5: // end                                     
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'd')
                {
                    Lex += ch;
                    state = Sy_Z4;
                    break;
                }
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
                Table_Of_Lexemes[count_line].Word = Lex;
                state = Ar_B1;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word = Lex;
                if (count_line >= size_-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word = Lex;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_B5: // ji jmp
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'i')
                {
                    Lex += ch;
                    state = Sy_Z5;
                    break;
                }
                if (ch == 'm')
                {
                    Lex += ch;
                    state = Sy_C6;
                    break;
                }
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
                Table_Of_Lexemes[count_line].Word = Lex;
                state = Sy_E4;
                break;

            case EndOfLine:
                Table_Of_Lexemes[count_line].Word = Lex;
                if (count_line >= size_-1-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word = Lex;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_C6:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'p')
                {
                    Lex += ch;
                    state = Sy_Z5;
                    break;
                }
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
                Table_Of_Lexemes[count_line].Word = Lex;
                state = Sy_E4;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word = Lex;
                if (count_line >= size_-1-1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word = Lex;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_B6:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'u')
                {
                    Lex += ch;
                    state = Sy_C7;
                    break;
                }
                else if (ch == 'h')
                {
                    Lex += ch;
                    state = Sy_C9;
                    break;
                }
                else
                {
                    state = Stop;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_C7:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'b')
                {
                    Lex += ch;
                    state = Sy_D7;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_D7:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'v')
                {
                    Lex += ch;
                    state = Sy_E7;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_E7:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'e')
                {
                    Lex += ch;
                    state = Sy_F7;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_F7:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'c')
                {
                    Lex += ch;
                    state = Sy_Z4;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_B7:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'o')
                {
                    Lex += ch;
                    state = Sy_C8;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_C8:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'n')
                {
                    Lex += ch;
                    state = Sy_D8;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_D8:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'c')
                {
                    Lex += ch;
                    state = Sy_E8;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_E8:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'a')
                {
                    Lex += ch;
                    state = Sy_F8;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_F8:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 't')
                {
                    Lex += ch;
                    state = Sy_Z4;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_C9:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'i')
                {
                    Lex += ch;
                    state = Sy_D9;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_D9:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'f')
                {
                    Lex += ch;
                    state = Sy_E9;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_E9:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 't')
                {
                    Lex += ch;
                    state = Sy_F9;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_F9:
            switch (s.token_class)
            {
            case Symbol:
                if (ch == 'l' || ch == 'r')
                {
                    Lex += ch;
                    state = Sy_G9;
                    break;
                }
                else
                {
                    state = Stop;
                    break;
                }
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_G9:
            switch (s.token_class)
            {
            case Space:
                Table_Of_Lexemes[count_line].Word = Lex;
                state = Sy_H9;
                break;
            case EndOfLine:
                Table_Of_Lexemes[count_line].Word = Lex;
                if (count_line >= size_ - 1)
                    Table_Of_Lexemes = Inc_size(Table_Of_Lexemes);
                count_line++;
                state = A1;
                Lex = "";
                break;
            case EndOfFile:
                Table_Of_Lexemes[count_line].Word = Lex;
                stop = true;
                break;
            default:
                state = Stop;
                break;
            }
            break;
        case Sy_H9:
            switch (s.token_class)
            {
            case Space:
                break;

            case Digit:
                Table_Of_Lexemes[count_line].int_or_char = 1;
                Table_Of_Lexemes[count_line].value_int = s.value;
                state = Sy_F1;
                break;
            default:
                state = Stop;
                break;
            }
            break;

        case Stop:
            cout << "Обнаружена ошибка в строке №" << count_line + 1 << endl;
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

void Interpreter_int(Lexeme* Table_Lex)
{
    vector<int> vect;
    vector<char> vect_variable;
    vector<int> vect_variable_mean;
    stack<int> st;
    int line = 0;
    while (line < size_ && Table_Lex[line].Word != "end")
    {
        if (Table_Lex[line].Word == "read")
        {
            int value;
            cin >> value;
            st.push(value);
            line++;
        }
        else if (Table_Lex[line].Word == "push")
        {
            if (Table_Lex[line].int_or_char == 0)//символ
            {
                for (int i = 0; i < vect_variable.size(); i++)
                {
                    if (vect_variable[i] == Table_Lex[line].value_char)
                    {
                        st.push(vect_variable_mean[i]);
                        break;
                    }
                }
            }
            if (Table_Lex[line].int_or_char == 1)//цифра
            {
                st.push(Table_Lex[line].value_int);
            }
            line++;
        }

        else if (Table_Lex[line].Word == "pop")
        {
            if (Table_Lex[line].int_or_char == 0)
            {
                int h = -1;
                for (int i = 0; i < vect_variable.size(); i++)
                {
                    if (vect_variable[i] == Table_Lex[line].value_char)
                    {
                        h = i;
                    }
                }
                if (h == -1)
                {
                    vect_variable.push_back(Table_Lex[line].value_char);
                    vect_variable_mean.push_back(st.top()); st.pop();
                }
                else
                {
                    vect_variable_mean[h] = st.top(); st.pop();
                }
            }
            line++;
        }

        else if (Table_Lex[line].Word == "ji")
        {
            if (Table_Lex[line].int_or_char == 1)
            {
                if (st.top() == 0)
                {
                    line++;
                    st.pop();
                }
                else
                {
                    line = Table_Lex[line].value_int - 1;
                    st.pop();
                }
            }
            else
            {
                line++;
            }
        }

        else if (Table_Lex[line].Word == "jmp")
        {
            if (Table_Lex[line].int_or_char = 1)
            {
                line = Table_Lex[line].value_int - 1;
            }
            else
            {
                line++;
            }
        }

        else if (Table_Lex[line].Word == "+" || Table_Lex[line].Word == "-" || Table_Lex[line].Word == "*" || Table_Lex[line].Word == "/" || Table_Lex[line].Word == "%")
        {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();

            if (Table_Lex[line].Word == "+")
            {
                st.push(a + b);
            }
            else if (Table_Lex[line].Word == "-")
            {
                st.push(a - b);
            }
            else if (Table_Lex[line].Word == "*")
            {
                st.push(a * b);
            }
            else if (Table_Lex[line].Word == "/")
            {
                if (b == 0)
                {
                    cout << "На ноль делить нельзя" << endl;
                    st.push(b);
                    st.push(a);
                    cout << "Значения были возвращенны в стек";
                }
                else
                {
                    st.push(a / b);
                }
            }
            else if (Table_Lex[line].Word == "%")
            {
                if (b == 0)
                {
                    cout << "На ноль делить нельзя" << endl;
                    st.push(b);
                    st.push(a);
                    cout << "Значения были возвращенны в стек";
                }
                else
                {
                    st.push(a % b);
                }
            }
            line++;
        }

        else if (Table_Lex[line].Word == "=" || Table_Lex[line].Word == ">=" || Table_Lex[line].Word == "<" || Table_Lex[line].Word == ">" || Table_Lex[line].Word == "!=" || Table_Lex[line].Word == "<=")
        {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            if (Table_Lex[line].Word == "=")
            {
                st.push(a == b);
            }
            else if (Table_Lex[line].Word == ">")
            {
                st.push(a > b);
            }
            else if (Table_Lex[line].Word == "<")
            {
                st.push(a < b);
            }
            else if (Table_Lex[line].Word == ">=")
            {
                st.push(a >= b);
            }
            else if (Table_Lex[line].Word == "<=")
            {
                st.push(a <= b);
            }
            else if (Table_Lex[line].Word == "!=")
            {
                st.push(a != b);
            }
            line++;
        }

        else if (Table_Lex[line].Word == "write")
        {
            cout << st.top() << endl;
            line++;
        }

        else
        {
            line++;
        }
    }

}

void Interpreter_vect(Lexeme* Table_Lex)
{
    stack<variant<int, Vector>> st;
    int line = 0;
    int fl = 1;
    while (line < size_ && Table_Lex[line].Word != "end")
    {

        if (Table_Lex[line].Word == "push")
        {
            if (Table_Lex[line].int_or_char == 0)//символ
            {
                //Vector v;
                //cin >> v;
                //st.push(v);
                //line++;
                int d[] = {1,2,3,4,5,6};
                Vector v(d, 6);
                st.push(v);
                line++;
            }
            else if (Table_Lex[line].int_or_char == 1)//цифра
            {
                st.push(Table_Lex[line].value_int);
                line++;
            }
            else
            {
                line++;
            }
            
            
        }
        else if (Table_Lex[line].Word == "+" || Table_Lex[line].Word == "-" || Table_Lex[line].Word == "*" || Table_Lex[line].Word == "/" || Table_Lex[line].Word == "%" || Table_Lex[line].Word == "&")
        {
            Vector b = get<Vector>(st.top()); st.pop();
            Vector a = get<Vector>(st.top()); st.pop();

            if (Table_Lex[line].Word == "+")
            {
                st.push(a + b);
                fl = 1;
            }
            else if (Table_Lex[line].Word == "-")
            {
                st.push(a - b);
                fl = 1;
            }
            else if (Table_Lex[line].Word == "*")
            {
                st.push(a * b);
                fl = 1;
            }
            else if (Table_Lex[line].Word == "/")
            {
                st.push(a / b);
                fl = 1;
            }
            else if (Table_Lex[line].Word == "%")
            {
                st.push(a % b);
                fl = 1;
            }
            else if (Table_Lex[line].Word == "&")
            {
                st.push(a & b);
                fl = 0;
            }
            line++;
        }
        else if (Table_Lex[line].Word == "shiftl" || Table_Lex[line].Word == "shiftr")
        {
            int a = Table_Lex[line].value_int;
            Vector b = get<Vector>(st.top()); st.pop();
            if (Table_Lex[line].Word == "shiftl")
                st.push(b.Shift_left(a));
            if (Table_Lex[line].Word == "shiftr")
                st.push(b.Shift_right(a));
            fl = 1;
            line++;
        }
        else if (Table_Lex[line].Word == "concat")
        {
            Vector b = get<Vector>(st.top()); st.pop();
            Vector a = get<Vector>(st.top()); st.pop();

            st.push(b.Сoncatenation(a));
            fl = 1;
            line++;
        }
        else if (Table_Lex[line].Word == "subvec")
        {
            
            int to = get<int>(st.top()); st.pop();
            int from = get<int>(st.top()); st.pop();
            Vector a = get<Vector>(st.top()); st.pop();

            st.push(a.Subvector_Selection(from,to));
            fl = 1;
            line++;
        }
        else if (Table_Lex[line].Word == "write")
        {
            if (fl == 1)
            {
                cout << get<Vector>(st.top());
                st.pop();
            }
            else
            {
                cout << get<int>(st.top());
                st.pop();
            }
            line++;
        }
    }
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUS");
    /*Vector x, y;
    cin >> x >> y;
    cout << x / y << endl;
    return 0;*/

    Lexeme* Table = new Lexeme[size_];
    char file_name[] = "input_1.txt";
    Table = Lexical_analyzer(file_name);
    Print_Table_Lex(Table);
    Interpreter_int(Table);

    return 0;
}