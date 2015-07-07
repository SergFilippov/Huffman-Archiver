#include "dearchiver.h"

void DeArchiver::unpack(string archiveName, string keyFileName, string fileName)
{
    _archiveName = archiveName;
    _fileName = fileName;
    _keyFile = keyFileName;
    readKeyFile();                          // Сформировать массив _treeCode
    buildTree();                            // Построить дерево для алгоритма Хаффмана
    writeFile();                            // Расшифровать архив
}

void DeArchiver::readKeyFile()
{
    ifstream keyFile(_keyFile, ios_base::in | ios_base::binary);
    char byte = 0;
    bool bit = false;
    while (!keyFile.eof())
    {
        keyFile.read((char*)&byte, 1);
        for (int i = 7; i >= 0; i--)
        {
            bit = byte & (1 << i);
            _treeCode.push_back(bit);
        }
    }
    keyFile.close();
}

void DeArchiver::buildTree()
{
    stack<Node*> st;
    char byte;
    for (int i = 0; i < _treeCode.size();)
    {
        if (_treeCode[i] == 1)
        {
            byte = 0;
            for (int j = 7; j >= 0; j--)
            {
                i++;
                byte = byte | _treeCode[i] << j;
            }
            Node* temp = new Node();
            temp->byte = byte;
            st.push(temp);
            i++;
        }
        if (_treeCode[i] == 0)
        {
            if (st.size() == 1)
            {
                _root = st.top();
                return;
            }
            Node* temp = new Node();
            temp->right = st.top();
            st.pop();
            temp->left = st.top();
            st.pop();
            st.push(temp);

            i++;
        }
    }
    //_root = st.top();
}

void DeArchiver::writeFile()
{
    ifstream archiveFile(_archiveName, ios_base::in | ios_base::binary);
    ofstream someFile(_fileName, ios_base::out | ios_base::binary);
    Node *temp = _root;
    int count = 0;
    char byte;
    archiveFile.read((char*)&byte, 1);
    while(!archiveFile.eof())
    {
        bool b = byte & (1 << (7-count));

        if (b == 1)
            temp = temp->right;
        else temp = temp->left;

        if (temp->left == nullptr && temp->right == nullptr)
        {
            someFile.write((char*)&temp->byte, 1);
            temp = _root;
        }
        count++;

        if (count == 8)
        {
            archiveFile.read((char*)&byte, 1);
            count = 0;
        }
    }

    archiveFile.close();
    someFile.close();
}
