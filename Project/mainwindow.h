#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int cnt;
    QStringList Lines;
    QString currentLine;
    QFile outEqual;
    QFile outInequal;
    QFile outDoubt;


//信号和槽都没有返回值
signals:
    void GoNextPairs();


private slots:    
    void start();
    void BtnSetClickable();
    void CompareFile();
    void StoreResult();

private:
    Ui::MainWindow *ui;
};







#endif // MAINWINDOW_H
