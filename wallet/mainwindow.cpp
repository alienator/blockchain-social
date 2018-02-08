#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lblPubKey->setVisible(false);
    model = new QStandardItemModel(this);
    model->setColumnCount(2);

    wallet = new Wallet();

    connect(wallet,
            SIGNAL(updated(QList<Tx>)),
            this,
            SLOT(on_wallet_updated(QList<Tx>)));

    wallet->init();

    ui->lblPubKey->setText(wallet->getPubKey());

    ui->tableTx->setModel(model);
    ui->tableTx->setColumnWidth(0, 340);
    ui->tableTx->setColumnWidth(1, 40);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_wallet_updated(QList<Tx> txs)
{
    //QList<Tx> txs = wallet->getCredits();
    model->clear();

    for (int i = 0; i < txs.size(); i++) {
        QList<QStandardItem *> row;

        QString strValue = QString::number(txs.value(i).getValue());
        quint32 state = txs.value(i).getState();
        if (state == UNSPENT ||
            state == SPENT) {
            //credits
        }
        else if (state == SENDED) {
            //debits
            strValue = "-" + strValue;
        }
        else if (state == CHANGE ||
                 state == CHANGE_SPENT) {
            //change are hidden
            continue;
        }

        QStandardItem *item = new QStandardItem(txs.value(i).getHash());
        QStandardItem *value = new QStandardItem(strValue);

        row.append(item);
        row.append(value);

        model->appendRow(row);
    }

    ui->lblBalance->setText(QString::number(wallet->getBalance()));

    ui->tableTx->setModel(model);
    ui->tableTx->setColumnWidth(0, 340);
    ui->tableTx->setColumnWidth(1, 40);
}

void MainWindow::on_btnSend_clicked()
{
    QString target = ui->txtTarget->text();
    double amount = ui->txtAmount->text().toDouble();

    wallet->send(target, amount);
}
