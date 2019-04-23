#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QString>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_fileOpen_triggered();
    void on_fileSave_triggered();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    static const int SIZE = 12;
    QString start = "-1"; QString end = "-1";
    int arr_visited_point[SIZE];//массив пройденных вершин
    int arr_previous_point[SIZE];//массив предыдущих вершин
    int stack[SIZE];
    int inc_Matrix[SIZE][SIZE];//матрица инцидентности
    int place = SIZE - 1;
    bool fClosed = false;
    void function(int point, int last);
    //int lst = -1;
};

#endif // MAINWINDOW_H
