#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFont>
#include <QFileDialog>
#include <QInputDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString stt1,ed1;
    //实例化画家对象
    double dis(QPoint a,QPoint b);
    void mousePressEvent(QMouseEvent *event);
    int isin(QPoint x, QPoint y, double n);
    void clr();
private slots:
    void on_pushButton_clicked();
    void paintEvent(QPaintEvent*);

  //  void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
