#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_fileOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), QDir::currentPath(),"*.txt");
    if(filePath.isEmpty()) return;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    QString s; bool ok;
    for(int h = 0; h < SIZE; h++)
    {
        arr_visited_point[h] = 0;
        arr_previous_point[h] = -1;
        stack[h] = -1;
        for(int j = 0; j < SIZE; j++)
        {
            in >> s;
            inc_Matrix[h][j] = s.toInt(&ok, 10);
        }
    }
    file.close();
    fClosed = true;
    ui->statusBar->showMessage("Файл был открыт");
}
void MainWindow::on_fileSave_triggered()
{
    if(!fClosed)
    {
        QString filePath = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), QDir::currentPath(), ".txt");
        if(filePath.isEmpty()) return;
        QFile file(filePath.append(".txt"));
        if(!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }
        file.close();
        ui->statusBar->showMessage("Файл сохранён");
    }
    else
    {
    QString filePath = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), QDir::currentPath(), ".txt");
    if(filePath.isEmpty()) return;
    QFile file(filePath.append(".txt"));
    bool ok;
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream out(&file);
    out << QString("Вершины: ");
    for(int i = 0; i < SIZE; i++)
    {
        out << i << " ";
    }
    out << QString("\r\nПуть: ") << " ";
    int index = arr_previous_point[end.toInt(&ok, 10)];
    out << end;
    do
    {
        out << " <- ";
        out << index;
        index = arr_previous_point[index];
    } while (index != -1);
    file.close();
    ui->statusBar->showMessage("Файл сохранён");
    }
}
void MainWindow::on_pushButton_clicked()
{
    ui->label_3->clear();
    ui->label_4->clear();
    bool ok;
    start = ui->lineEdit->text();
    end = ui->lineEdit_2->text();

    QRegExp e("\\d+");
    if(!fClosed)
        QMessageBox::information(0, "Предупреждение", "Откройте файл");
    else if(e.exactMatch(start) && e.exactMatch(end) && start.toInt(&ok, 10) >= 0 && start.toInt(&ok, 10) < SIZE && end.toInt(&ok, 10) >= 0 && end.toInt(&ok, 10) < SIZE)
    {
        if(start.toInt(&ok, 10) == end.toInt(&ok, 10))
            QMessageBox::information(0, "Предупреждение", "Вершины совпадают");
        else
        {
            arr_previous_point[start.toInt(&ok, 10)] =- 1;
            arr_visited_point[start.toInt(&ok, 10)] = 1;
            stack[place] = start.toInt(&ok, 10);
            place--;
            int point;
            while(stack[SIZE - 1] != -1)
            {
                point = stack[place + 1];
                arr_visited_point[point] = 1;
                stack[place + 1] = -1;
                place++;
                for(int j = SIZE - 1; j > 0; j--)
                {
                    if(inc_Matrix[point][j] != 0 && arr_visited_point[j] != 1)
                    {
                        if(arr_previous_point[j] == -1)
                        {
                            stack[place] = j;
                            place--;
                            arr_previous_point[j] = point;
                        }
                        else  arr_previous_point[j] = point;
                    }
                }
            }
            arr_previous_point[start.toInt(&ok, 10)] =- 1;

            QString str;
            for(int i = 0; i < SIZE; i++)
            {
                str += QString::number(i) + " ";
            }
            ui->label_3->setText(str);

            int index = arr_previous_point[end.toInt(&ok, 10)];
            QString s;
            s = end;
            do
            {
                s += " <- " + QString::number(index);
                index = arr_previous_point[index];
            }while(index !=- 1);
            ui->label_4->setText(s);
            ui->statusBar->showMessage("Поиск выполнен, сохраните файл");
        }
    }
    else
        QMessageBox::information(0, "Предупреждение", "Неверный формат ввода");
}
void MainWindow::function(int point, int last)
{
    arr_visited_point[point] = 1;
    arr_previous_point[point] = last;
    for(int i = 0; i < SIZE; i++)
    {
        if(arr_visited_point[i] == 0 && inc_Matrix[point][i] == 1)
        function(i, point);
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->label_3->clear();
    ui->label_4->clear();
    bool ok;
    start = ui->lineEdit->text();
    end = ui->lineEdit_2->text();

    QRegExp e("\\d+");
    if(!fClosed)
        QMessageBox::information(0, "Предупреждение", "Откройте файл");
    else if(e.exactMatch(start) && e.exactMatch(end) && start.toInt(&ok, 10) >= 0 && start.toInt(&ok, 10) < SIZE && end.toInt(&ok, 10) >= 0 && end.toInt(&ok, 10) < SIZE)
    {
        if(start.toInt(&ok, 10) == end.toInt(&ok, 10))
            QMessageBox::information(0, "Предупреждение", "Вершины совпадают");
        else
        {
            int lst = -1;
            function(start.toInt(&ok, 10), lst);


            QString str;
            for(int i = 0; i < SIZE; i++)
            {
                str += QString::number(i) + " ";
            }
            ui->label_3->setText(str);

            int index = arr_previous_point[end.toInt(&ok, 10)];
            QString s;
            s = end;
            do
            {
                s += " <- " + QString::number(index);
                index = arr_previous_point[index];
            }while(index !=- 1);
            ui->label_4->setText(s);
            ui->statusBar->showMessage("Поиск выполнен, сохраните файл");
        }
    }
    else
        QMessageBox::information(0, "Предупреждение", "Неверный формат ввода");
}
