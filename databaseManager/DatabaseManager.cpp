#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include "DataBase.h"

DatabaseManager::DatabaseManager()
    : m_database(new DataBase())
{
    m_database.data()->setDatabase(QString("system.db"));
}

DatabaseManager::~DatabaseManager()
{
    m_database.data()->releaseDatabase();
}

void DatabaseManager::operatorsData(OperatorInfo &info)
{
    QString sql(" SELECT "
                " countries.name AS countryName, "
                " operators.name AS operatorName, "
                " countries.mcc, "
                " operators.mnc "
                "   FROM [countries] "
                "   LEFT JOIN [operators] ON countries.mcc = operators.mcc ");

    bool ok;
    QSqlQuery query = m_database.data()->select(sql, QMap<QString, QVariant>(), ok);

    if(!ok)
        return;

    QSqlRecord rec = query.record();
    const int ix_countryName = rec.indexOf("countryName");
    const int ix_operatorName = rec.indexOf("operatorName");
    const int ix_mcc = rec.indexOf("mcc");
    const int ix_mnc = rec.indexOf("mnc");

    while (query.next())
    {
        auto& operatorsList = info[query.value(ix_countryName).toString()];

        Operator newOperator;
        newOperator.name = query.value(ix_operatorName).toString();
        newOperator.mcc = query.value(ix_mcc).toInt();
        newOperator.mnc = query.value(ix_mnc).toInt();

        operatorsList.append(newOperator);
        info.insert(query.value(ix_countryName).toString(), operatorsList);

    }
}

bool DatabaseManager::updateOperator(const Operator &oper)
{
    QString sql(" UPDATE [operators] "
                " SET name = :name "
                "   WHERE mcc = :mcc AND mnc = :mnc ");

    QMap<QString, QVariant> params;
    params[":name"] = oper.name;
    params[":mcc"] = oper.mcc;
    params[":mnc"] = oper.mnc;

    bool ok;
    m_database.data()->update(sql, params, ok);

    return ok;
}

bool DatabaseManager::addOperator(const Operator &oper)
{
    QString sql("SELECT * FROM[countries] WHERE mcc = :mcc");
    bool ok;

    QMap<QString, QVariant> params;
    params[":mcc"] = oper.mcc;
    QSqlQuery query = m_database.data()->select(sql, params, ok);

    if(!ok)
        return false;

    if(!query.first())
        return false;

    QString insert(" INSERT INTO [operators] "
                " (name, mcc, mnc) "
                " VALUES(:name, :mcc, :mnc) ");

    params[":name"] = oper.name;
    params[":mnc"] = oper.mnc;

    m_database.data()->insert(insert, params, ok);
    return ok;
}
