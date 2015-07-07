#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include "node.h"
using namespace std;

struct MyCompare
{
    bool operator()(const Node* l, const Node* r) const // Функция для сортировки алементов типа Node* в List
    {
        return ( l->count < r->count);                  // Сравнение по полю count
    }
};


class Archiver
{
public:
    void compress(string fileName, string archiveName, string keyFileName);

private:
    void countBytes();                  // Подсчитать число вхождений каждого блока
    void createList();                  // Записать полученные данные в список
    void buildTree();                   // Построить дерево на основе алгоритма Хаффмана
    void createTable(Node* root);       // Создать ассоциативный массив "Блок - Двоичный код"
    void writeArchive();                // Запись исходного файла в файл архива на основе таблицы "Блок - Двоичный код"
    void writeKeyFile();                // Запись дерева в файл для разархивирования

    string _fileName;                   // Имя файла
    string _archiveName;                // Имя архива
    string _keyFile;                    // Имя файла-ключа
    map<char, int> _counts;             // Ассоциативный массив "Блок - Количество вхождений"
    list<Node*> _list;                  // Список объектов класса Node ( Для построения дерева )
    Node* _root;                        // Корень дерева
    map<char, vector<bool> > _table;    // Ассоциативный массив "Блок - Двоичный код"
    vector<bool> _treeCode;             // Ключ в виде двоичного массива
    void formTreeCode(Node* root);      // Рекурсивный проход по дереву
    vector<bool> _code;                 // вспомогательная переменная для рекурсии
};

#endif // ARCHIVER_H

