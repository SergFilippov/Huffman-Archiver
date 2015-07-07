#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include "archiver.h"
#include "dearchiver.h"
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog();
    QString fileName = fileDialog->getOpenFileName();
    ui->lineEdit->setText(fileName);
}

void Widget::on_pushButton_2_clicked()
{
    string fileName = ui->lineEdit->text().toStdString();
    if (!fileName.empty())
    {
    Archiver A;
    A.compress(fileName, fileName + ".huff", fileName + ".key");
    QMessageBox::information(NULL,QObject::tr("Информация"),tr("Архивирование завершено!"));
    }
}

void Widget::on_pushButton_4_clicked()
{
    QFileDialog *fileDialog = new QFileDialog();
    QString archiveName = fileDialog->getOpenFileName();
    ui->lineEdit_2->setText(archiveName);
}

void Widget::on_pushButton_3_clicked()
{
    string filename = ui->lineEdit_2->text().toStdString();
    filename = filename.substr(0, filename.size() - 5);

    if (!filename.empty())
    {
        DeArchiver D;
        D.unpack(filename + ".huff", filename + ".key", filename);
        QMessageBox::information(NULL,QObject::tr("Информация"),tr("Распаковка завершена!"));
    }
}
