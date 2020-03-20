#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTreeWidgetItem>
#include <QMainWindow>
#include "headers/treemodel.h"
#include "headers/dbconnector.h"
#include "headers/dialog_add.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void clickPlusOperator(const QString &mcc, const QString &mnc);
    void changeOperator(const QString &name, const QString &mcc, const QString &mnc,
                        const QModelIndex &index);
    void updateUI(const QString &mcc, const QString &mnc, const QString &name, const QModelIndex &_index,
                  const bool &isEdit);

private slots:
    void on_pushButton_add_clicked();

private:
    Ui::MainWindow *ui;
    DialogAdd *editor;
    TreeModel *treeModel;
    TreeItem *treeDelegate;
    DBConnector *db;

    void connecting();
};
#endif // MAINWINDOW_H
