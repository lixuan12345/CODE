#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void readFile();

private slots:
    void on_start_Btn_clicked();
    void srand();
    void on_stop_Btn_clicked();

private:
    Ui::MainWindow *ui;
    QString name_data[41];
    QTimer *timer = new QTimer;
};

#endif // MAINWINDOW_H
