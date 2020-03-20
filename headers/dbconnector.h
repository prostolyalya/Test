#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QString>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QList>
#include <QDebug>

class DBConnector
{
public:
    struct Operator
    {
        QString mcc;
        QString mnc;
        QString name;
    };
    struct listCountry
    {
        QString country;
        QString code;
        QList<Operator> operators;
    };

    DBConnector(const QString &db_name = "system.db");

    void add(const QString &mcc, const QString &mnc, const QString &name);
    void edit(const QString &_mcc, const QString &_mnc, const QString &name, const QString &oldName);
    QList<listCountry> getAll();
    QString getCountyCode(const QString &mcc);

private:
    QSqlDatabase db;

    QString DB_name = "system.db";
    const QString DB_tableName_country = "countries";
    const QString DB_tableName_operator = "operators";
};

#endif // DBCONNECTOR_H
