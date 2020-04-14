#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <stack>

#include <expat.h>

using std::string;

// структура для хранения пользовательских данных
struct MyData 
{
    // заголовки новостей
    std::pair<std::vector<string>, std::vector<string>> news;
    
    // текущий открытый тег
    std::stack<string> openTag;
    std::stack<string> text;

    // текст внутри тега title
    string title;
};

// вызывается для открывающего тега
// el - имя тега
// attr - аттрибуты тега
void start( void * data, const char * el, const char ** attr )
{
    MyData & d = *static_cast<MyData *>(data);

    d.openTag.push(el);
}

// вызывается для закрывающего тега
// el - имя тега
void end( void * data, const char * el )
{
    MyData & d = *static_cast<MyData *>(data);

    std::cout << d.openTag.top() << std::endl;
    std::cout << d.text.top() << std::endl;
    // d.text.pop();
    // d.openTag.pop();
    std::cout << std::endl;
}

// вызывается для текста внутри тегов
void text(void * data, const char *s, int len)
{
    MyData & d = *static_cast<MyData *>(data);

    d.text.push(string(s, len));
}

int main()
{
    // создаём XML парсер
    XML_Parser p_title = XML_ParserCreate(0);

    // открываем файл с XML в бинарном режиме
    std::ifstream f("rss.xml", std::ifstream::binary);

    // обработка ошибки открытия файла
    if (!f.is_open())
    {
        std::cerr << "Can not open 'rss.xml' for reading\n";
        return 1;        
    }

    // устанавливаем указатель на функции, которые
    // будут вызывать при встрече открывающего тега 
    // (start) и закрывающего тега (end)
    XML_SetElementHandler(p_title, start, end);

    // устанавливаем указатель на функцию для обработки 
    // текста внутри XML тегов
    XML_SetCharacterDataHandler(p_title, text);

    // пользовательские данные, которые мы будем использовать
    // при парсинге XML
    MyData data;

    // устанавливаем указатель на пользовательские данные 
    XML_SetUserData(p_title, &data);
        
    // будем считывать по 1Кб за раз
    char buff[1024];
          
    // читаем данные из файла
    while(f.read(buff, sizeof(buff)))
    {
        // колличество считанных байтов
        size_t len = f.gcount();
        
        // парсим прочитанный кусочек
        if (!XML_Parse(p_title, buff, len, f.eof()))
        {
            // обработка ошибок при парсинге
            std::cerr << "Parser error at line " 
                      << XML_GetCurrentLineNumber(p_title) << ": "
                      << XML_ErrorString(XML_GetErrorCode(p_title))
                      << std::endl;    
            return 1;
        }        
    }                                                   

    std::cout << data.news.first.size() << std::endl;

    // выводим все заголовки на стандартный вывод
    // for (size_t i = 0; i != data.news.first.size(); ++i) {
    //     std::cout << data.news.first[i] << std::endl;
        // std::cout << data.news.second[i] << std::endl << std::endl;
    // }

    return 0;    
}