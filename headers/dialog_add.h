#ifndef DIALOGADD_H
#define DIALOGADD_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include "dbconnector.h"

namespace Ui {
class DialogAdd;
}

class DialogAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdd(QWidget *parent = nullptr);
    ~DialogAdd();
    void setParam(const QString &name, const QString &mcc, const QString &mnc, const QModelIndex &_index);
    void setDb(DBConnector *value);

signals:
    void updateUI(const QString &mcc, const QString &mnc, const QString &name, const QModelIndex &_index,
                  const bool &isEdit);

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();

    void on_textEdit_mcc_textChanged();

    void on_textEdit_mnc_textChanged();

private:
    void clear();
    void updateIcon();

    Ui::DialogAdd *ui;
    DBConnector *db;

    const QString standartPathIcon = ":/icons/ques.png";
    QString oldName = "";
    QModelIndex index;
};

#endif // DIALOGADD_H
