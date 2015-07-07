#ifndef DEARCHIVER_H
#define DEARCHIVER_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stack>
#include "node.h"

using namespace std;

class DeArchiver
{
public:
    void unpack(string archiveName, string keyFileName, string fileName);

private:
    void readKeyFile();             // Сформировать массив _treeCode
    void buildTree();               // Построить дерево для алгоритма Хаффмана
    void writeFile();               // Расшифровать архив

    string _fileName;               // Имя файла
    string _archiveName;            // Имя архива
    string _keyFile;                // Имя файла-ключа
    vector<bool> _treeCode;         // Ключ для построения дерева в виде двоичного массива
    Node* _root;                    // Корень дерева
};

#endif // DEARCHIVER_H
