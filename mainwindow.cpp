#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_add.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DBConnector("system.db");
    treeModel = new TreeModel(db->getAll());
    treeDelegate = new TreeItem({});
    ui->treeView->setUniformRowHeights(true);
    ui->treeView->setItemDelegate(treeDelegate);
    ui->treeView->setModel(treeModel);
    ui->treeView->viewport()->setAttribute(Qt::WA_Hover);
    editor = new DialogAdd();
    editor->setDb(db);
    connecting();
}

MainWindow::~MainWindow()
{
    delete treeModel;
    delete treeDelegate;
    delete db;
    delete editor;
    delete ui;
}

void MainWindow::connecting()
{
    connect(treeDelegate, &TreeItem::plusClickOperator, this, &MainWindow::clickPlusOperator);
    connect(treeDelegate, &TreeItem::changeOperator, this, &MainWindow::changeOperator);
    connect(editor, &DialogAdd::updateUI, this, &MainWindow::updateUI);
}

void MainWindow::clickPlusOperator(const QString& mcc, const QString& mnc)
{
    qDebug() << "connect click plus" << mcc << mnc;
}

void MainWindow::changeOperator(const QString& name, const QString& mcc, const QString& mnc,
                                const QModelIndex& index)
{
    editor->setParam(name, mcc, mnc, index);
    editor->show();
}

void MainWindow::updateUI(const QString& mcc, const QString& mnc, const QString& name,
                          const QModelIndex& _index, const bool& isEdit)
{
    if (isEdit)
    {
        treeModel->setData(_index, name + " (" + mcc + "," + mnc + ")", 0);
        ui->treeView->update();
    }
    else
    {
        QString code = db->getCountyCode(mcc);
        treeModel->addRow(code, mcc, mnc, name);
        ui->treeView->update();
    }
}

void MainWindow::on_pushButton_add_clicked()
{
    editor->show();
}
