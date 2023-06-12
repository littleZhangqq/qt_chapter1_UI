#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calculateButtonClick();

private:
    Ui::MainWindow *ui;
    int height = 400;
    int width = 280;
    QWidget btnbg;
    QLabel resultLabel;
    QString frontValue;
    QString backValue;
    QString symbol;
    float result;
    void clearAllValue();
    void toCalculateResult(QString);
    void toChangeCalculateMode(QString);
    void outputResult();
};

#endif // MAINWINDOW_H
