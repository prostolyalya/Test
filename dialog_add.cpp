#include "dialog_add.h"
#include "ui_dialog_add.h"

DialogAdd::DialogAdd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAdd)
{
    ui->setupUi(this);
}

DialogAdd::~DialogAdd()
{
    delete ui;
}

void DialogAdd::setParam(const QString &name, const QString &mcc, const QString &mnc,
                         const QModelIndex &_index)
{
    ui->textEdit_name->setText(name);
    ui->textEdit_mcc->setText(mcc);
    ui->textEdit_mnc->setText(mnc);
    ui->textEdit_mcc->setEnabled(false);
    ui->textEdit_mnc->setEnabled(false);
    oldName = name;
    index = _index;
    updateIcon();
}

void DialogAdd::on_pushButton_save_clicked()
{
    QString name = ui->textEdit_name->toPlainText();
    QString mnc = ui->textEdit_mnc->toPlainText();
    QString mcc = ui->textEdit_mcc->toPlainText();
    bool isEdit = false;
    if (ui->textEdit_mcc->isEnabled())
    {
        if (name.isEmpty() || mnc.isEmpty() || mcc.isEmpty())
        {
            QMessageBox msg;
            msg.setText("Fill all fields");
            msg.setWindowTitle("Warning");
            msg.setStyleSheet("background-color: rgb(0, 0, 0);");
            msg.setStyleSheet("color: rgb(255, 255, 255);");
            msg.exec();
            return;
        }
        db->add(mcc, mnc, name);
    }
    else
    {
        db->edit(mcc, mnc, name, oldName);
        isEdit = true;
    }
    emit updateUI(mcc, mnc, name, index, isEdit);
    clear();
    this->hide();
}

void DialogAdd::on_pushButton_cancel_clicked()
{
    clear();
    this->hide();
}

void DialogAdd::setDb(DBConnector *value)
{
    db = value;
}

void DialogAdd::clear()
{
    ui->textEdit_name->clear();
    ui->textEdit_mcc->clear();
    ui->textEdit_mnc->clear();
    ui->textEdit_mcc->setEnabled(true);
    ui->textEdit_mnc->setEnabled(true);
    ui->icon_country->setPixmap(standartPathIcon);
    ui->icon_operator->setPixmap(standartPathIcon);
}

void DialogAdd::on_textEdit_mcc_textChanged()
{
    updateIcon();
}

void DialogAdd::on_textEdit_mnc_textChanged()
{
    updateIcon();
}

void DialogAdd::updateIcon()
{
    QString mcc = ui->textEdit_mcc->toPlainText();
    QString mnc = ui->textEdit_mnc->toPlainText();
    QString code = db->getCountyCode(mcc);
    QString pathIconCounty = standartPathIcon;
    QString pathIconOperator = standartPathIcon;
    if (QFile(":/icons/Countries/" + code + ".png").exists())
        if (!code.isEmpty())
            pathIconCounty = ":/icons/Countries/" + code + ".png";
    if (QFile(":/icons/Operators/" + mcc + "_" + mnc + ".png").exists())
        pathIconOperator = ":/icons/Operators/" + mcc + "_" + mnc + ".png";
    ui->icon_country->setPixmap(pathIconCounty);
    ui->icon_operator->setPixmap(pathIconOperator);
}
