#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QTextStream>
#include <QtGlobal>
#include <QTime>
#include <QTextCodec>
static int total = 6;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readFile();
    ui->textEdit->setText("抽奖");
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setAlignment(Qt::AlignHCenter);     //设置edit文字居中显示
    connect(timer,SIGNAL(timeout()),this,SLOT(srand()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readFile()
{
    //构造一个以data1.txt为文件名的QFile对象
    QFile file("C:\\Users\\LENOVO\\Desktop\\name.txt");
    //指定为GBK
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    //文件以只读方式打开 || 在读取时，将行结束符转换成 \n
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<< "open file failure";
        return;
    }
    else
    {
        QString array;
//        //当未到达文件结束位置
//        while(!file.atEnd())
//        {
//             //读取一行文本数据
//             QByteArray line = file.readLine();
//             //将读取到的行数据转换为Unicode
//             QString str = codec->toUnicode(line);
//             //将得到的字符设置到编辑框中显示
//             qDebug()<<str;
//         }
       // 创建QTextStream流操作对象，与QFile对象file连接
        QTextStream in(&file);
        in.setCodec(codec);
        //读取所有文本
        array = in.readAll();
        //trimmed()：移除字符串两端空白符，simplified()：移除字符串两端的空白字符，
        //使用单个空格字符“ ”代替字符串中出现的空白字符。
        array = array.trimmed();
        //qDebug()<<array;
        array = array.simplified();
        //qDebug()<<array;

        int i=0,k=0;
        while(i<array.size())
        {
            //.at(int position)：返回当前字符的位置index
            name_data[k] += array.at(i);
            name_data[k]=name_data[k].trimmed();
            //qDebug()<<name_data[k];
            if(array.at(i) == " ")
            {
                k++;
            }
            i++;
        }
    }
    file.close();
}

void MainWindow::on_start_Btn_clicked()
{
    if(total == 1)
    {
       //qDebug()<<"meila" ;
       ui->textEdit->setText("没人啦！");
       return;
    }
    qDebug() << total ;
    timer->start(100);
}

void MainWindow::on_stop_Btn_clicked()
{
    timer->stop();

    int num=0;
    QString str = ui->textEdit->toPlainText();
    if(total == 1)
    {
       ui->textEdit->setText("没人啦！");
       return;
    }
    for(int i=0;i<total;i++)
    {
        if(str == name_data[i])
        {
            num = i;
            break;
        }
    }
    for(int i=0;i<total-1;i++)
    {
        if(i>=num)
        {
            name_data[i]=name_data[i+1];
        }
    }
    total--;
    qDebug() << total ;
}

void MainWindow::srand()
{
    //QTime(int h,int m, int s, int ms):构造一个具有初始时间的QTime对象
    //.msecsTo(QTime::curentTime()):计算距离当前时间的毫秒数
    //qsrand()使用非固定值来作为种子，希望函数在每次调用(间隔大于1ms)时生成的随机数不一样。
    qsrand(QTime(0,0,0,0).msecsTo((QTime::currentTime())));
    ui->textEdit->clear();
    int num = qrand()%(total-1);
    ui->textEdit->setText(name_data[num]);
}
