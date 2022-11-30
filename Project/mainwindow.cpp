#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    outInequal("/home/wangjingyue/LabData/output1/inequal.csv"),
    outEqual("/home/wangjingyue/LabData/output1/equal.csv"),
    outDoubt("/home/wangjingyue/LabData/output1/doubt.csv")
{
    ui->setupUi(this);

//页面初始化
    ui->comboBox->setCurrentIndex(-1);
    ui->BtnStart->setEnabled(true);
    ui->BtnAssure->setEnabled(false);
    ui->LabelFilename1->setText(" ");
    ui->LabelFilename2->setText(" ");

//信号与槽
    connect(ui->BtnStart,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->BtnStart,SIGNAL(clicked()), this,SLOT(CompareFile()));

    connect(ui->BtnAssure,SIGNAL(clicked()), this,SLOT(StoreResult()));

    connect(this,SIGNAL(GoNextPairs()), this,SLOT(CompareFile()));

    connect(ui->comboBox,SIGNAL(activated(int)),this,SLOT(BtnSetClickable()));


//打开输入文件
    QFile inputFile("/home/wangjingyue/LabData/output/inequal.csv");
    if (!inputFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::about(NULL, "文件", "文件打开失败");
    }
    cnt = 0;

    QTextStream txtInput(&inputFile);
    QString line1 = txtInput.readLine();
/*
    while(txtInput.atEnd()){
        Lines << txtInput.readLine();
    }
*/
    int i = 0;
    while(i < 60){
        Lines.insert(i,txtInput.readLine());
        i++;
    }

//打开输出文件
    bool ok1 = outInequal.open(QIODevice::Append | QIODevice::Text);
    bool ok2 = outEqual.open(QIODevice::Append | QIODevice::Text);
    bool ok3 = outDoubt.open(QIODevice::Append | QIODevice::Text);


    inputFile.close();
}

MainWindow::~MainWindow()
{
    outInequal.close();
    outEqual.close();
    outDoubt.close();
    delete ui;
}


void MainWindow::CompareFile()
{
    ui->TextCode1->clear();
    ui->TextCode2->clear();
    currentLine = Lines.at(cnt);
    QStringList list = currentLine.split(",");
    QString FileName1 = list[0];
    QString FileName2 = list[1];
    ui->LabelFilename1->setText(FileName1);
    ui->LabelFilename2->setText(FileName2);

    QFile file1("/home/wangjingyue/LabData/"+FileName1);
    QFile file2("/home/wangjingyue/LabData/"+FileName2);

    if (file1.open(QIODevice ::ReadOnly | QIODevice ::Text))
    {
        QTextStream textStream(&file1);
        while (!textStream.atEnd()){
            ui->TextCode1->append(textStream.readLine());
        }
    }
    if (file2.open(QIODevice ::ReadOnly | QIODevice ::Text))
    {
        QTextStream textStream(&file2);
        while (!textStream.atEnd()){
            ui->TextCode2->append(textStream.readLine());
        }
    }
    file1.close();
    file2.close();
    cnt++;
    this->ui->BtnAssure->setEnabled(false);
    this->ui->comboBox->setCurrentIndex(-1);

}


void MainWindow::BtnSetClickable()
{
    this->ui->BtnAssure->setEnabled(true);
}

void MainWindow::start()
{
    this->ui->BtnStart->hide();

    //下拉框初始化
    this->ui->comboBox->addItem(QString::asprintf("等价",0));
    this->ui->comboBox->addItem(QString::asprintf("不等价",1));
    this->ui->comboBox->addItem(QString::asprintf("存疑",2));
    ui->comboBox->setCurrentIndex(-1);
}

void MainWindow::StoreResult()
{
    currentLine = currentLine + "\n";
    if(this->ui->comboBox->currentIndex() == 0){
        this->outEqual.write(currentLine.toUtf8());
    }
    else if(this->ui->comboBox->currentIndex() == 1){
        this->outInequal.write(currentLine.toUtf8());
    }
    else{
        this->outDoubt.write(currentLine.toUtf8());
    }
    emit GoNextPairs();
}









