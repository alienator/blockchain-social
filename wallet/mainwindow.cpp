#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(this);
    QList<QStandardItem *> rows;
    QList<QStandardItem *> columns;

    QStandardItem *h = new QStandardItem("5feceb66ffc86f38d952786c6d696c79c2dbc239dd4e91b46729d73a27fb57e9");
    columns.append(h);
    columns.append(new QStandardItem("0.025"));

    model->setColumnCount(2);
    model->appendRow(columns);        

    ui->tableTx->setModel(model);
    ui->tableTx->setColumnWidth(0, 300);
    ui->tableTx->setColumnWidth(1, 40);
}

MainWindow::~MainWindow()
{
    delete ui;
}
