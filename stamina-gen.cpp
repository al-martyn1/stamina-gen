#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <cstdlib>

int getRandomVal( int range )
{
    return std::rand()*range/RAND_MAX;
}


bool isPairedChar( char ch )
{
    switch(ch)
    {
        case '{':
        case '}':
        case '<':
        case '>':
        case '[':
        case ']':
        case '(':
        case ')':
                 return true;
        default: return false;
    }
}

bool isOpChar( char ch )
{
    switch(ch)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '|':
        case '^':
        case '&':
                 return true;
        default: return false;
    }
}

char getLeftPair( char ch )
{
    switch(ch)
    {
        case '{':
        case '}': return '{';
        case '<':
        case '>': return '<';
        case '[':
        case ']': return '[';
        case '(':
        case ')': return '(';
        default : return 0;
    }
}

char getRightPair( char ch )
{
    switch(ch)
    {
        case '{':
        case '}': return '}';
        case '<':
        case '>': return '>';
        case '[':
        case ']': return ']';
        case '(':
        case ')': return ')';
        default : return 0;
    }
}


bool ruMode = false;


char getRandomSpecianChar()
{
    static std::string specialsRu = "\"\xB9;%?*()+=/";
    static std::string specialsEn = ";:\'\"|\\(){}[]/?@#$%^&*()+=";

    const std::string &chars = ruMode ? specialsRu : specialsEn;

    int idx = getRandomVal( chars.size() );

    return chars[idx];
}


std::string processWord(std::string &w)
{

    if (w.empty())
        return w;


    std::string res;

    // Кирилица в кодировке 1251
    // 0xC0 - 0xDF - прописные
    // 0xE0 - 0xFF - строчные

    // Первым делом надо привыкать к Паскаль/кэмел идентификаторам - делаем заглавную букву.
    if (w.size()>1)
    {
        unsigned char ch = (unsigned char)w[0];
        if (ch>=0xE0 && ch<=0xFF)
            w[0] = (char)(ch - 0xE0 + 0xC0);
        if (w[0]>='a' && w[0]<='z')
            w[0] = w[0] - 'a' + 'A';
    }


    // Какие варианты могут быть?

    // Если слово содержит '-', ',', '!', '?' или '.' - ничего не делаем

    if (w.find_first_of("-,.!?")!=w.npos)
    {
        res.swap(w);
        return res;
    }

    // Надо привыкать также к snake_case
    //std::cerr << snake_case
    if (w.size()>3)
    {
        int n = 0;
        int insertedUnders = 0;

        std::string::size_type i = 0;
        for(; i!=w.size(); ++i, ++n)
        {
            auto rnd = getRandomVal( std::max(0, (8-n)));
            //std::cerr << "N: " << n << ", rnd: " << rnd << "\n";
            if (insertedUnders<2 && rnd==0)
            {
                insertedUnders++;
                res.append(1,'_');
                n = 0;
            }
            res.append(1,w[i]);
        }

        res.swap(w);
        res.clear();
    }


    char randomSpecianChar = getRandomSpecianChar();

    if (isPairedChar( randomSpecianChar ) && getRandomVal(3)==0)
    {
        w.append(1,getLeftPair ( randomSpecianChar ));
        if (getRandomVal(3)==0)
        {
            w.append(std::to_string(getRandomVal(10000)));
        }
        w.append(1,getRightPair( randomSpecianChar ));
    }
    else
    {
        w.append(1, randomSpecianChar );
        if (isOpChar(randomSpecianChar) && getRandomVal(3)==0)
        {
            w.append(std::to_string(getRandomVal(10000)));
        }
    }

    res.swap(w);
    return res;
}



int main(int argc, char* argv[])
{
    if (argc>1 && std::string(argv[1])=="ru")
    {
        ruMode = true;
    }

    char ch = 0;

    std::string str;


    while(std::cin.get(ch))
    {
        //std::cerr << getRandomVal(6) << "\n";
        switch(ch)
        {
            case ' ':
            case '\n':
            case '\r ':
            case '\t':
                 std::cout << processWord(str) << ch;
                 break;

            default:
                 str.append(1, ch);
        }

        //std::cout << ch;
    }

    std::cout << processWord(str);


// int get();
// istream& get (char& c);
// c-string (2)	
// istream& get (char* s, streamsize n);
// istream& get (char* s, streamsize n, char delim);
// stream buffer (3)	
// istream& get (streambuf& sb);
// istream& get (streambuf& sb, char delim);

}