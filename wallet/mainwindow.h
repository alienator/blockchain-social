#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "wallet.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    Wallet *wallet;

private slots:
    void on_btnSend_clicked();
    void on_wallet_updated(QList<Tx> txs);
};

#endif // MAINWINDOW_H
