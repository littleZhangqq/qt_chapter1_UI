#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("强哥计算器");
    this->setFixedSize(width,height);

    resultLabel.setParent(this);
    resultLabel.setGeometry(0,0,width,80);
    resultLabel.setText("计算结果");
    resultLabel.setStyleSheet("background-color:#ffffff");

    QFont font;
    font.setBold(true);
    font.setPointSize(33);
    resultLabel.setFont(font);
    resultLabel.setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    btnbg.setParent(this);
    btnbg.setGeometry(10,100,width-20,height-120);

    QPushButton *backZero = new QPushButton();
    backZero->setText("Clear");
    backZero->setStyleSheet("QPushButton{background-color:#333333;color:#ffffff;border-radius:4px}" "QPushButton::pressed{background-color: #666666}");
    backZero->setParent(&btnbg);
    backZero->setGeometry(0,height-120-40,width-20,40);
    connect(backZero,SIGNAL(clicked(bool)),this,SLOT(calculateButtonClick()));

    int fix = 10;
    float itemW = ((width-20)-fix*3)/4;
    float itemH = 40;
    float fixH = (height-120-50-itemH*4)/3;
    int count = 4;
    QVector<QString> array = {"7","8","9","+","4","5","6","-","1","2","3","x","0",".","=","/"};

    for (int i = 0; i < 16; ++i) {
        QPushButton *button = new QPushButton();
        button->setParent(&btnbg);
        button->setGeometry((itemW+fix)*(i%count),(fixH+itemH)*(i/count),itemW,itemH);
        button->setText(array.at(i));
        button->setStyleSheet("QPushButton { background-color: #333333; color: #ffffff; border-radius: 4px; }" "QPushButton::pressed { background-color: #666666; }");
        button->setProperty("tag",i+1000);

        QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(button);
        shadowEffect->setBlurRadius(5);
        shadowEffect->setColor(QColor(0, 0, 0, 80));
        shadowEffect->setOffset(2, 2);
        button->setGraphicsEffect(shadowEffect);
        connect(button,SIGNAL(clicked(bool)),this,SLOT(calculateButtonClick()));
    }
}

void MainWindow::calculateButtonClick(){
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString title = button->text();
    qDebug() <<"点击了按钮：" << title;
    int value = title.toInt();
    if(value > 0){
        this->toCalculateResult(title);
    }else{
        if(title == "0"){
            this->toCalculateResult(title);
        }else if(title == "Clear"){
            this->clearAllValue();
        }else{
            this->toChangeCalculateMode(title);
        }
    }
}

void MainWindow::toCalculateResult(QString value){
    qDebug() <<"传递数值" << value;
    if(symbol.isEmpty()){
        //如果还没有输入符号，就给frontvalue赋值
        if(frontValue.toInt() == 0){
            //frontvalue是空时，输入值不为0就给他拼上
            if(value == 0){
                return;
            }else{
                frontValue.append(value);
                resultLabel.setText(frontValue);
            }
        }else if(frontValue.contains(".")){
            //frontvalue不是空时，如果有小数点了那么输入值不是小数点就给他拼上
            if(value == "."){
                return;
            }else{
                frontValue.append(value);
                resultLabel.setText(frontValue);
            }
        }else{
            frontValue.append(value);
            resultLabel.setText(frontValue);
        }

    }else{
        //如果已经输入了符号，那么给backvalue赋值
        if(backValue.toInt() == 0){
            //backValue是空时，输入值不为0就给他拼上
            if(value == 0){
                return;
            }else{
                backValue.append(value);
                resultLabel.setText(backValue);
            }
        }else if(backValue.contains(".")){
            //frontvalue不是空时，如果有小数点了那么输入值不是小数点就给他拼上
            if(value == "."){
                return;
            }else{
                backValue.append(value);
                resultLabel.setText(backValue);
            }
        }else{
            backValue.append(value);
            resultLabel.setText(backValue);
        }
    }
    qDebug() << "前向值：" << frontValue << "后向值：" << backValue;
}

void MainWindow::toChangeCalculateMode(QString value){
    qDebug() <<"传递格式" << value;
    if(value == "="){
        if(backValue.isEmpty()){
            return;
        }else{
            this->outputResult();
        }
    }else{}
    symbol = value;
}

void MainWindow::outputResult(){
    float result = 0;
    if(symbol == "+"){
        result = frontValue.toFloat() + backValue.toFloat();
    }else if(symbol == "-"){
        result = frontValue.toFloat() - backValue.toFloat();
    }else if(symbol == "x"){
        result = frontValue.toFloat() * backValue.toFloat();
    }else if(symbol == "/"){
        result = frontValue.toFloat() / backValue.toFloat();
    }
    resultLabel.setText(QString::number(result));
    frontValue = QString::number(result);
    backValue = "";
    symbol = "";
}

void MainWindow::clearAllValue(){
    frontValue = "";
    backValue = "";
    symbol = "";
    resultLabel.setText(QString::number(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}
