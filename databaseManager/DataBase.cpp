#include "DataBase.h"
#include "DatabaseConnector.h"
#include <QVariant>
#include <QDebug>

DataBase::~DataBase()
{
    releaseDatabase();
}

void DataBase::setDatabase(const QString& nameDB)
{
    releaseDatabase();
    try {
        connector.reset(new DatabaseConnector(nameDB));
        m_db = connector.data()->connectToDatabase();
    }
    catch(const ::Exception<QString> &err) {
        qCritical() << err.what();
    }
}

void DataBase::releaseDatabase()
{
    if(m_db.isOpen())
        m_db.close();
}

void DataBase::commit()
{
    m_db.commit();
}

void DataBase::transaction()
{
    m_db.transaction();
}

void DataBase::rollback()
{
    m_db.rollback();
}

void DataBase::insert(const QString &sql, QMap<QString, QVariant> params, bool &ok)
{
    QMutexLocker locker(&m_mutex);
    QSqlQuery query(m_db);

    query.prepare(sql);
    QList<QString> keys = params.keys();

    for(const auto &key : keys)
        query.bindValue(key, params[key]);

    ok = true;

    transaction();
    if(!query.exec())
    {
        ok = false;
        rollback();
    }
    commit();
}

void DataBase::update(const QString &sql, QMap<QString, QVariant> params, bool &ok)
{
    QMutexLocker locker(&m_mutex);
    QSqlQuery query(m_db);

    query.prepare(sql);
    QList<QString> keys = params.keys();

    for(const auto &key : keys)
        query.bindValue(key, params[key]);

    ok = true;

    transaction();
    if(!query.exec())
    {
        ok = false;
        rollback();
    }
    commit();
}

QSqlQuery DataBase::select(const QString &sql, QMap<QString, QVariant> params, bool &ok)
{
    QMutexLocker locker(&m_mutex);
    QSqlQuery query(m_db);
    query.setForwardOnly(true);

    query.prepare(sql);
    QList<QString> keys = params.keys();

    for(const auto &key : keys)
        query.bindValue(key, params[key]);
    ok = true;

    if(!query.exec())
        ok = false;

    return query;
}

DataBase::DataBase() : m_db()
{
    ///
}
