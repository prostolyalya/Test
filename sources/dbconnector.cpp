#include "headers/dbconnector.h"

DBConnector::DBConnector(const QString &db_name)
{
    DB_name = db_name;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_name);
    QSqlQuery query;
    db.open();
    query.exec(QString("CREATE TABLE IF NOT EXISTS " + DB_tableName_country
                       + " ("
                         "mcc          INTEGER, "
                         "code         TEXT , "
                         "name         TEXT , "
                         "mnc_length   INTEGER ); "));
    query.exec(QString("CREATE TABLE IF NOT EXISTS " + DB_tableName_operator
                       + " ("
                         "mcc   TEXT, "
                         "mnc   TEXT, "
                         "name  TEXT ); "));
    db.close();
}

void DBConnector::add(const QString &mcc, const QString &mnc, const QString &name)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO " + DB_tableName_operator
                  + " (mcc, mnc, name)"
                    "VALUES (:mcc, :mnc, :name)");
    query.bindValue(":mcc", mcc);
    query.bindValue(":mnc", mnc);
    query.bindValue(":name", name);
    query.exec();
    db.close();
}

QList<DBConnector::listCountry> DBConnector::getAll()
{
    QList<listCountry> res;
    db.open();
    QSqlQuery query;
    query.exec("SELECT * FROM " + DB_tableName_operator);
    QMultiMap<QString, DBConnector::Operator> operators;
    while (query.next())
    {
        QString mcc = query.value(0).toString();
        QString mnc(query.value(1).toString());
        QString name(query.value(2).toString());
        operators.insert(mcc, { mcc, mnc, name });
    }
    for (auto el = operators.begin(); el != operators.end();)
    {
        if (el.key() == "" || el.key() == "0")
        {
            operators.remove((el).key());
            el = operators.begin();
            continue;
        }
        query.exec("SELECT * FROM " + DB_tableName_country + " WHERE mcc = '" + el.key() + "' ;");
        query.next();
        QString code = query.value(1).toString();
        QString country = query.value(2).toString();
        if (country.isEmpty())
        {
            operators.remove((el).key());
            el = operators.begin();
            continue;
        }
        res.append({ country, code, operators.values(el.key()) });
        operators.remove((el).key());
        el = operators.begin();
    }

    db.close();
    return res;
}

QString DBConnector::getCountyCode(const QString &mcc)
{
    db.open();
    QSqlQuery query;
    query.exec("SELECT code FROM " + DB_tableName_country + " WHERE mcc = '" + mcc + "' ;");
    query.next();
    QString code = "";
    code = query.value(0).toString();
    db.close();
    return code;
}

void DBConnector::edit(const QString &_mcc, const QString &_mnc, const QString &_name, const QString &oldName)
{
    db.open();
    QSqlQuery query;
    query.exec("UPDATE operators SET name = '" + _name + "' WHERE mnc = " + _mnc + " AND mcc = " + _mcc
               + " AND name = '" + oldName + "' ; ");
    db.close();
}
