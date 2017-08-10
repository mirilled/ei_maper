#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (&timerProperty, SIGNAL(timeout()), this, SLOT(updateProperty()));
    timerProperty.start(100);
    this->ui->horizontalSlider->setVisible(false);
    this->ui->horizontalSlider_2->setVisible(false);
    this->ui->horizontalSlider_3->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    this->ui->widget->name = "brick";
    this->ui->widget->width = 0.5;
    this->ui->widget->length = 1;
    this->ui->widget->height = 0.3;
    this->ui->widget->update();
    this->ui->horizontalSlider->setVisible(false);
    this->ui->horizontalSlider_2->setVisible(false);
    this->ui->horizontalSlider_3->setVisible(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    this->ui->widget->name = "big cube";
    this->ui->widget->width = 2;
    this->ui->widget->length = 2;
    this->ui->widget->height = 2;
    this->ui->widget->update();
    this->ui->horizontalSlider->setVisible(false);
    this->ui->horizontalSlider_2->setVisible(false);
    this->ui->horizontalSlider_3->setVisible(false);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->ui->widget->name = "column";
    this->ui->widget->width = 0.3;
    this->ui->widget->length = 0.3;
    this->ui->widget->height = 1.4;
    this->ui->widget->update();
    this->ui->horizontalSlider->setVisible(false);
    this->ui->horizontalSlider_2->setVisible(false);
    this->ui->horizontalSlider_3->setVisible(false);
}

void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox msg;
    msg.setText("Input\nRight Mouse Button - rotate object\nMouse wheel - zoom object\nW,S - move depth camera\nA,D - move side camera\nQ,E - move height camera\n\nNote: check keyboard layout and click on viewport if key buttons don't work");
    msg.exec();
}

void MainWindow::updateProperty(){
    this->ui->label->setText("Object "+this->ui->widget->name+" has "+QString::number(this->ui->widget->triangles)+" triangle(s).\nProperty: "+
                             "length="+QString::number(this->ui->widget->length)+" width="+QString::number(this->ui->widget->width)+" height="+QString::number(this->ui->widget->height)+"." );
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->ui->widget->width = (float)value/10;
    this->ui->widget->update();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    this->ui->widget->length = (float)value/10;
    this->ui->widget->update();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    this->ui->widget->height = (float)value/10;
    this->ui->widget->update();
}

void MainWindow::on_pushButton_6_clicked()
{
    this->ui->widget->name = "custom box";
    this->ui->horizontalSlider->setVisible(true);
    this->ui->horizontalSlider_2->setVisible(true);
    this->ui->horizontalSlider_3->setVisible(true);
    this->ui->widget->width = (float)this->ui->horizontalSlider->value()/10;
    this->ui->widget->length = (float)this->ui->horizontalSlider_2->value()/10;
    this->ui->widget->height = (float)this->ui->horizontalSlider_3->value()/10;
    this->ui->widget->update();
}

