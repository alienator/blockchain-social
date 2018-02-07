#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lblPubKey->setText(wallet.getPubKey());
    ui->lblBalance->setText(QString::number(wallet.getBalance()));

    QStandardItemModel *model = new QStandardItemModel(this);

    QList<Block> blocks = wallet.getBlocks();
    for (int i = 0; i < blocks.size(); i++) {
        QList<QStandardItem *> row;

        TransferenceTransaction *tx = dynamic_cast<TransferenceTransaction *> (blocks.value(i).getTransactions().value(0));
        QStandardItem *item = new QStandardItem(QString(tx->getHash().toHex()));
        QStandardItem *value = new QStandardItem(QString::number(tx->getOutputs().value(0)->getValue()));
        row.append(item);
        row.append(value);
        model->appendRow(row);
    }

    model->setColumnCount(2);

    ui->tableTx->setModel(model);
    ui->tableTx->setColumnWidth(0, 340);
    ui->tableTx->setColumnWidth(1, 40);

    //get balance tx
    //get history tx
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSend_clicked()
{
    QString target = ui->txtTarget->text();
    double amount = ui->txtAmount->text().toDouble();


}
