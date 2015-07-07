    #include "archiver.h"

void Archiver::compress(string fileName, string archiveName, string keyFileName)
{
    _fileName = fileName;
    _archiveName = archiveName;
    _keyFile = keyFileName;
    countBytes();           // Подсчитать число вхождений каждого блока
    createList();           // Записать полученные данные в список
    buildTree();            // Построить дерево на основе алгоритма Хаффмана
    createTable(_root);     // Создать ассоциативный массив "Блок - Двоичный код"
    writeArchive();         // Запись исходного файла в файл архива на основе таблицы "Блок - Двоичный код"
    writeKeyFile();         // Запись дерева в файл для разархивирования
}

void Archiver::countBytes()
{
    ifstream someFile(_fileName, ios_base::in | ios_base::binary);
    char byte;
    while (!someFile.eof())
    {
        someFile.read((char*) &byte, 1);
        _counts[byte]++;
    }
    someFile.close();
}

void Archiver::createList()
{
    for (map<char, int>::iterator iter = _counts.begin(); iter != _counts.end(); iter++)
    {
        Node* temp = new Node();
        temp->byte = iter->first;
        temp->count = iter->second;
        _list.push_back(temp);
    }
}

void Archiver::buildTree()
{
    while (_list.size() != 1)
    {
        _list.sort(MyCompare());
        Node* left = _list.front();
        _list.pop_front();
        Node* right = _list.front();
        _list.pop_front();
        Node* temp = new Node(left, right);
        _list.push_back(temp);
    }
    _root = _list.front();
}

void Archiver::createTable(Node* root)
{
    if (root->left != nullptr)
    {
        _code.push_back(0);
        createTable(root->left);
    }
    if (root->right != nullptr)
    {
        _code.push_back(1);
        createTable(root->right);
    }
    if ((root->left == nullptr) && (root->right == nullptr))
        _table[root->byte] = _code;

    _code.pop_back();
}

void Archiver::writeArchive()
{
    ifstream inFile(_fileName, ios_base::in | ios_base::binary);
    ofstream outFile(_archiveName, ios_base::out | ios_base::binary);
    int count = 0;
    char byte;
    char buffer = 0;
    vector<bool> code;
    while (!inFile.eof())
    {
        inFile.read((char*)&byte, 1);
        code = _table[byte];
        for (int i = 0; i < code.size(); i++)
        {
            buffer = buffer | code[i] << (7 - count);
            count++;
            if (count == 8)
            {
                outFile.write((char*)&buffer, 1);
                buffer = 0;
                count = 0;
            }
        }
    }
    outFile.close();
    inFile.close();
}

void Archiver::writeKeyFile()
{
    ofstream keyFile(_keyFile, ios_base::out | ios_base::binary);

    formTreeCode(_root);
    int count = 0;
    char byte = 0;
    for (int i = 0; i < _treeCode.size(); i++)
    {
        byte = byte | (_treeCode[i] << (7 - (i % 8)));
        count++;
        if (count == 8)
        {
            keyFile.write((char*) &byte, 1);
            count = 0;
            byte = 0;
        }
    }
    keyFile.write((char*) &byte, 1);
    keyFile.close();
}

void Archiver::formTreeCode(Node* root)
{
    if ((root->left == nullptr) && (root->right == nullptr))
    {
        _treeCode.push_back(1);
        for (int i = 0; i < 8; i++)
            _treeCode.push_back(root->byte & (1 << (7 - i)));
    }
    if ((root->left != nullptr) || (root->right != nullptr))
    {
        formTreeCode(root->left);
        formTreeCode(root->right);
        _treeCode.push_back(0);
    }
}
