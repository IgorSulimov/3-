#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

// Типы токенов
enum TokenType {
    TERMINAL,
    NON_TERMINAL,
    END
};

// Структура токена
struct Token {
    TokenType type;
    string value;

    Token() : type(END), value("") {}
    Token(TokenType t, string v = "") : type(t), value(v) {}
};
//FIRST
struct F
{
    string NonTerm = " ";
    vector<string> Terms;
};

struct GrammarRule {
    string left;
    vector<string> right;

    GrammarRule(const string& l, const vector<string>& r) : left(l), right(r) {}
};
// Структура которая будет хранить КОН и НАЧ нетерминалов
struct Start_End
{
    string nonTerminals = " ";
    vector<string> Start;
    vector<string> End;

};
// Проверяет на повторы НАЧ и КОН
int Check_rep(vector<string> vec, string str)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == str)
        {
            return 0;
        }
    }
    return 1;
}
// Грамматика
class Grammar {
private:
    vector<GrammarRule> rules;
    set<string> nonTerminals;
    set<string> terminals;
    vector<string> ALL_SYM;
    vector<string> nonTermss;
    vector<string> termss;


public:
    void addRule(const string& left, const vector<string>& right) {
        rules.emplace_back(left, right);
        nonTerminals.insert(left);
        if(Check_rep(ALL_SYM,left))
            ALL_SYM.push_back(left);
        if (Check_rep(nonTermss, left))
            nonTermss.push_back(left);
        for (const auto& sym : right) {
            if (sym[0] != '<') {
                terminals.insert(sym);
                if (Check_rep(ALL_SYM, sym))
                    ALL_SYM.push_back(sym);
                if (Check_rep(termss, sym))
                    termss.push_back(sym);
            }
        }
    }
    vector<string> GET_NON()
    {
        return nonTermss;
    }
    vector<string> GET_TR()
    {
        return termss;
    }
    vector<string> Get_ALL()
    {
        return ALL_SYM;
    }
    const vector<GrammarRule>& getRules() const {
        return rules;
    }

    const set<string>& getNonTerminals() const {
        return nonTerminals;
    }

    const set<string>& getTerminals() const {
        return terminals;
    }


    void print() const {
        cout << "Правила:" << endl;
        for (const auto& rule : rules) {
            cout << rule.left << " -> ";
            for (const auto& sym : rule.right) {
                cout << sym << " ";
            }
            cout << endl;
        }
    }
};


class Lexer {
private:
    const set<string>& terminals;  

    public:
        Lexer(const set<string>& terms) : terminals(terms) {}

};

class Parser {
private:
    Grammar grammar;
    Lexer lexer;
    Token currentToken;
    stack<string> parseStack;
    map<pair<string, string>, char> precedenceTable;


    void buildPrecedenceTable(vector<Start_End> start_end, vector<F> FIRST)
    {
        const set <string>& terms = grammar.getTerminals();

        const set<string>& nonTerms = grammar.getNonTerminals();

        int fl_$ = 1;

        set<string> allSymbols = terms;
        allSymbols.insert(nonTerms.begin(), nonTerms.end());
        allSymbols.insert("$");


        for (const string& a : allSymbols) {
            for (const string& b : allSymbols) {
                precedenceTable[{a, b}] = '.';
            }
        }

        for (const GrammarRule& rule : grammar.getRules())
        {
            const vector<string>& right = rule.right;
            const size_t n = right.size();
            string left = rule.left;
            // Заполнение $ ------------
            if (fl_$)
            {
                int i = 0;
                for (i; left != start_end[i].nonTerminals; i++)
                {
                }
                for (int k = 0; k < start_end[i].Start.size(); k++)
                {
                    precedenceTable[{"$", start_end[i].Start[k] }] = '<';
                }
                for (int d = 0; d < start_end[i].End.size(); d++)
                {
                    precedenceTable[{start_end[i].End[d], "$" }] = '>';
                }
                fl_$ = 0;
            }
            for (int i = 0; i < n; i++)
            {
                const string& curr = right[i];
                bool currIsTerm = terms.count(curr);
                // = +++++++++
                if (i + 1 < n)
                {
                    const string& next = right[i + 1];
                    bool nextIsTerm = terms.count(next);
                    precedenceTable[{curr, next}] = '=';
                }
            }
        }
        for (const GrammarRule& rule : grammar.getRules()) {
            const vector<string>& right = rule.right;
            string left = rule.left;
            const size_t n = right.size();
            for (int i = 0; i < n; i++)
            {
                if (i - 1 >= 0)
                {
                    const string& a = right[i - 1];
                    const string& x = right[i];
                    //// < ++++++++++++
                    if (terms.count(a) && nonTerms.count(x))
                    {
                        int i = 0;
                        while (x != start_end[i].nonTerminals)
                        {
                            i++;
                        }
                        for (int k = 0; k < start_end[i].Start.size(); k++)
                        {
                            if (precedenceTable[{a, start_end[i].Start[k]}] != ('.') && precedenceTable[{a, start_end[i].Start[k]}] != ('<'))
                            {
                                cout << "ОШИБКА В ТАБЛИЦЕ Символы: " << a << "," << start_end[i].Start[k] << "||" << precedenceTable[{a, start_end[i].Start[k]}] << ",<" << endl;
                            }
                            else
                            {
                                precedenceTable[{a, start_end[i].Start[k]}] = '<';
                            }
                        }
                    }
                    if (nonTerms.count(a) && nonTerms.count(x))
                    {
                        int i = 0;
                        while (x != start_end[i].nonTerminals)
                        {
                            i++;
                        }
                        for (int k = 0; k < start_end[i].Start.size(); k++)
                        {
                            if (precedenceTable[{a, start_end[i].Start[k]}] != ('.') && precedenceTable[{a, start_end[i].Start[k]}] != ('<'))
                            {
                                cout << "ОШИБКА В ТАБЛИЦЕ Символы: " << a << "," << start_end[i].Start[k] << "||" << precedenceTable[{a, start_end[i].Start[k]}] << ",<" << endl;
                            }
                            else
                            {
                                precedenceTable[{a, start_end[i].Start[k]}] = '<';
                            }
                        }
                    }


                    // >
                    if (nonTerms.count(a) && terms.count(x))
                    {
                        int i = 0;
                        while (a != start_end[i].nonTerminals)
                        {
                            i++;
                        }
                        for (int k = 0; k < start_end[i].End.size(); k++)
                        {
                            if (precedenceTable[{start_end[i].End[k], x}] != ('.') && precedenceTable[{start_end[i].End[k], x}] != ('>'))
                            {
                                cout << "ОШИБКА В ТАБЛИЦЕ Символы: " << start_end[i].End[k] << "," << x << "||" << precedenceTable[{start_end[i].End[k], x}] << ",>" << endl;
                            }
                            else
                            {
                                precedenceTable[{start_end[i].End[k], x}] = '>';
                            }
                        }
                    }
                    if (nonTerms.count(a) && nonTerms.count(x))
                    {
                        int i = 0;
                        int p = 0;
                        while (a != start_end[i].nonTerminals)
                        {
                            i++;
                        }
                        while (x != FIRST[p].NonTerm)
                        {
                            p++;
                        }
                        for (int k = 0; k < start_end[i].End.size(); k++)
                        {
                            for (int l = 0; l < FIRST[p].Terms.size(); l++)
                            {
                                if (precedenceTable[{start_end[i].End[k], FIRST[p].Terms[l]}] != ('.') && precedenceTable[{start_end[i].End[k], FIRST[p].Terms[l]}] != ('<'))
                                {
                                    cout << "ОШИБКА В ТАБЛИЦЕ Символы: " << start_end[i].End[k] << "," << FIRST[p].Terms[l] << "||" << precedenceTable[{start_end[i].End[k], FIRST[p].Terms[l]}] << ",>" << endl;
                                }
                                else
                                {
                                    precedenceTable[{start_end[i].End[k], FIRST[p].Terms[l]}] = '>';
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // Функция для поиска прямой левой рекурсии
    void findDirectLeftRecursion(const Grammar& grammar) {
        cout << "\nПроверка на прямую левую рекурсию:\n";
        bool found = false;

        for (const GrammarRule& rule : grammar.getRules()) {
            if (!rule.right.empty() && rule.left == rule.right[0]) {
                cout << "Найдена прямая левая рекурсия: "
                    << rule.left << " -> " << rule.right[0] << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Прямой левой рекурсии не обнаружено.\n";
        }
    }

    // Функция для поиска косвенной левой рекурсии
    void findIndirectLeftRecursion(Grammar grammar) {
        cout << "\nПроверка на косвенную левую рекурсию:\n";
        vector<string> nonTerms = grammar.GET_NON();
        map<string, set<string>> firstSymbols;
        bool found = false;

        // Инициализация
        for (const string& nt : nonTerms) {
            firstSymbols[nt] = {};
        }

        // Находим первые символы для каждого нетерминала
        for (const GrammarRule& rule : grammar.getRules()) {
            if (!rule.right.empty()) {
                firstSymbols[rule.left].insert(rule.right[0]);
            }
        }

        // Проверяем на косвенную рекурсию
        for (const string& A : nonTerms) {
            stack<string> stack;
            set<string> visited;

            stack.push(A);
            visited.insert(A);

            while (!stack.empty()) {
                string current = stack.top();
                stack.pop();

                for (const string& B : firstSymbols[current]) {
                    if (grammar.getNonTerminals().count(B)) {
                        if (B == A) {
                            cout << "Найдена косвенная левая рекурсия: "
                                << A << " -> ... -> " << B << endl;
                            found = true;
                        }
                        if (visited.count(B) == 0) {
                            visited.insert(B);
                            stack.push(B);
                        }
                    }
                }
            }
        }

        if (!found) {
            cout << "Косвенной левой рекурсии не обнаружено.\n";
        }
    }

    // Функция для поиска e-правил
    void findEpsilonRules(const Grammar& grammar) {
        cout << "\nПоиск e-правил:\n";
        bool found = false;

        for (const GrammarRule& rule : grammar.getRules()) {
            if (rule.right.empty() || (rule.right.size() == 1 && rule.right[0] == "e")) {
                cout << "Найдено e-правило: " << rule.left << " -> e" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "e-правил не обнаружено.\n";
        }
    }
    void findUnreachableNonTerminals(Grammar grammar) {
        const vector<GrammarRule>& rules = grammar.getRules();
        const set<string>& nonTerms = grammar.getNonTerminals();
        const set<string>& terms = grammar.getTerminals();

        set<string> reachable;
        stack<string> toProcess;

        // Начинаем с начального символа (первого нетерминала в правилах)
        string startSymbol = rules[0].left;
        reachable.insert(startSymbol);
        toProcess.push(startSymbol);

        // Находим все достижимые нетерминалы
        while (!toProcess.empty()) {
            string current = toProcess.top();
            toProcess.pop();

            for (const GrammarRule& rule : rules) {
                if (rule.left == current) {
                    for (const string& symbol : rule.right) {
                        if (nonTerms.count(symbol) && !reachable.count(symbol)) {
                            reachable.insert(symbol);
                            toProcess.push(symbol);
                        }
                    }
                }
            }
        }

        // Находим недостижимые нетерминалы
        vector<string> unreachable;
        for (const string& nt : nonTerms) {
            if (!reachable.count(nt)) {
                unreachable.push_back(nt);
            }
        }

        // Выводим результат
        if (unreachable.empty()) {
            cout << "Недостижимых нетерминалов нет." << endl;
        }
        else {
            cout << "Недостижимые нетерминалы: ";
            for (const string& nt : unreachable) {
                cout << nt << " ";
            }
            cout << endl;
        }
    }

public:
    Parser(Grammar g, vector<Start_End> start_end, vector<F> FIRST) : grammar(g), lexer(grammar.getTerminals())
    {
        findUnreachableNonTerminals(grammar);
        findDirectLeftRecursion(grammar);
        findEpsilonRules(grammar);
        findIndirectLeftRecursion(grammar);

        buildPrecedenceTable(start_end, FIRST);
    }

    void printPrecedenceTable() {
        vector<string> allSymbols;
        vector<string> allSymbols2 = grammar.GET_TR();
        allSymbols = (grammar.GET_NON());
        for (int i = 0; i < allSymbols2.size(); i++)
        {
            allSymbols.push_back(allSymbols2[i]);
        }
        allSymbols.push_back("$");
        const int colWidth = 12;

        cout << "\nТаблица:\n";
            cout << string(colWidth, ' ');
        for (const string& colSymbol : allSymbols) {
            cout << setw(colWidth) << colSymbol;
        }
        cout << endl;


        for (const string& rowSymbol : allSymbols) {
            cout << setw(colWidth) << rowSymbol;

            for (const string& colSymbol : allSymbols) {
                pair<string, string> key = { rowSymbol, colSymbol };
                char relation = ' ';

                if (precedenceTable.count(key)) {
                    relation = precedenceTable[key];
                }

                cout << setw(colWidth) << relation;
            }
            cout << endl;
        }
    }
};



// Функция для чтения грамматики из файла
Grammar readGrammarFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    Grammar grammar;
    string line;


    while (getline(file, line)) {
        size_t arrowPos = line.find("->");
        if (arrowPos == string::npos) {
            continue; 
        }

        string left = line.substr(0, arrowPos);

        left.erase(remove_if(left.begin(), left.end(), ::isspace), left.end());

        string rightPart = line.substr(arrowPos + 2);
        vector<string> right;

        size_t start = 0;
        size_t end = rightPart.find(' ');
        while (end != string::npos) {
            string symbol = rightPart.substr(start, end - start);
            if (!symbol.empty()) {
                right.push_back(symbol);
            }
            start = end + 1;
            end = rightPart.find(' ', start);
        }

        string lastSymbol = rightPart.substr(start);
        if (!lastSymbol.empty()) {
            right.push_back(lastSymbol);
        }

        grammar.addRule(left, right);
    }
    return grammar;
}
//Функция возращает НАЧ и КОН всех не терминалов
vector<Start_End> Set_Start_End(Grammar grammar) {
    const set<string>& terms = grammar.getTerminals();
    const set<string>& nonTerms = grammar.getNonTerminals();
    vector<Start_End> start_end;
    // Цикл, который проставляет все НАЧ символы без смотра в другие нетерминалы, кроме исходного
    for (const GrammarRule& rule : grammar.getRules())
    {
        const vector<string>& right = rule.right;
        string left = rule.left;
        int i = 0;
        int fl = 0;
        // Проверка на то, есть ли нетерминал уже в векторе start_end  
        for (i; i < start_end.size(); i++)
        {
            if (left == start_end[i].nonTerminals)
            {
                if (Check_rep(start_end[i].Start, right[0]))
                    start_end[i].Start.push_back(right[0]);
                if (Check_rep(start_end[i].End, right[right.size() - 1]))
                    start_end[i].End.push_back(right[right.size() - 1]);
                fl = 1;
            }
        }
        if (fl == 0)
        {
            start_end.resize(start_end.size() + 1);
            start_end[i].nonTerminals = rule.left;
            start_end[i].Start.push_back(right[0]);
            start_end[i].End.push_back(right[right.size() - 1]);
        }
    }
    //цикл, который заполняет все НАЧ с другими нетерминалами
    for (int i = 0; i < start_end.size();i++)
    {
        for (int k = 0; k < start_end[i].Start.size(); k++)
        {
            if (nonTerms.count(start_end[i].Start[k]))
            {
                int p = 0;
                for (p; start_end[p].nonTerminals != start_end[i].Start[k]; p++);
                for (int l = 0; l < start_end[p].Start.size();l++)
                {
                    if (Check_rep(start_end[i].Start, start_end[p].Start[l]))
                    {
                        start_end[i].Start.push_back(start_end[p].Start[l]);
                    }
                }
            }
        }

    }
    for (int i = 0; i < start_end.size(); i++)
    {
        for (int k = 0; k < start_end[i].End.size(); k++)
        {
            if (nonTerms.count(start_end[i].End[k]))
            {
                int p = 0;
                for (p; start_end[p].nonTerminals != start_end[i].End[k]; p++);
                for (int l = 0; l < start_end[p].End.size(); l++)
                {
                    if (Check_rep(start_end[i].End, start_end[p].End[l]))
                    {
                        start_end[i].End.push_back(start_end[p].End[l]);
                    }
                }
            }
        }

    }
    return start_end;
}

vector<F> Find_FIRST(vector<F> FIRST,vector<Start_End> SE,Grammar grammar)
{
    const set<string>& terms = grammar.getTerminals();

    for (int i = 0; i < SE.size();i++)
    {
        FIRST.resize(FIRST.size() + 1);
        FIRST[i].NonTerm = SE[i].nonTerminals;
        for (int p = 0; p < SE[i].Start.size(); p++)
        {
            if (terms.count(SE[i].Start[p]))
            {
                FIRST[i].Terms.push_back(SE[i].Start[p]);
            }
        }
    }
    return FIRST;
}
void Print_FIRST(vector<F> FIRST)
{
    cout << '\n' << "FIRST" << endl;
    for (int i = 0; i < FIRST.size();i++)
    {
        cout << FIRST[i].NonTerm << ":";
        for (int p = 0; p < FIRST[i].Terms.size(); p++)
        {
            cout << FIRST[i].Terms[p] << "|";
        }
        cout << endl;
    }
}
void Print_SE(vector<Start_End> SE, Grammar grammar)
{
    cout << endl;
    cout << "НАЧ и КОН" << endl;
    int i = grammar.getNonTerminals().size();
    for (int p = 0; p < i; p++)
    {
        cout << SE[p].nonTerminals;
        cout << setw(5) << "{";
        for(int i =0; i < SE[p].Start.size(); i ++)
            cout << SE[p].Start[i] << "|";
        cout << "}" << setw(5) << "{";
        for (int i = 0; i < SE[p].End.size(); i++)
            cout << SE[p].End[i] << "|";
        cout << "}" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        // Чтение грамматики из файла
        Grammar grammar = readGrammarFromFile("3.txt");
        grammar.print();
        vector<Start_End> SE = Set_Start_End(grammar);
        //Print_SE(SE, grammar);

        vector<F> FIRST;
        FIRST = Find_FIRST(FIRST, SE, grammar);
        //Print_FIRST(FIRST);

         Parser parser(grammar,SE,FIRST);

         //Выводим таблицу предшествования (опционально)
        //parser.printPrecedenceTable();

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}