#include "DatabaseConnector.h"
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDebug>

QSqlDatabase DatabaseConnectorPostgres::connect()
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setDatabaseName(prepareDb());

    if(!m_db.open())
        throw ::Exception<QString>("Database not open");
    return m_db;
}


DatabaseConnectorPrivate::DatabaseConnectorPrivate()
{

}

QString DatabaseConnectorPrivate::prepareDb() const
{
    const QString databaseLocation(QString(":/database/%1").arg(m_dbName));
    const QString standartPath = QString("%1%2").arg(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)).arg(qApp->applicationName());

    QDir standartPathDir(standartPath);
    if(!standartPathDir.exists() && !standartPathDir.mkpath(standartPath))
        throw ::Exception<QString>("Database not found");

    const QString fullPath(standartPath + "/" + QString("%1").arg(m_dbName));
    if(!QFile::exists(fullPath) && !QFile::copy(databaseLocation, fullPath))
        throw ::Exception<QString>("Database not copied");

    return fullPath;
}

DatabaseConnector::DatabaseConnector(const QString &dbName)
{
    m_dbTypesContainer.insert(QString("sqlite"), DBExtension::SQLITE_EXTENTION);
    m_dbTypesContainer.insert(QString("db"), DBExtension::SQLITE_EXTENTION);
    m_dbTypesContainer.insert(QString("pg"), DBExtension::POSTGRES_EXTENTION);
    m_dbTypesContainer.insert(QString("frm"), DBExtension::MYSQL_EXTENTION);

    QStringList splitter = dbName.split(".");
    if(m_dbTypesContainer.contains(splitter.at(1)))
    {
        if(splitter.at(1) == m_dbTypesContainer.key(DBExtension::SQLITE_EXTENTION))
            m_impl = new DatabaseConnectorSQLite(dbName);

        else if(splitter.at(1) == m_dbTypesContainer.key(DBExtension::POSTGRES_EXTENTION))
            m_impl = new DatabaseConnectorPostgres(dbName);

        else
            throw ::Exception<QString>(QString("This type of database is not supported"));
    }
}

QSqlDatabase DatabaseConnector::connectToDatabase()
{
    return m_impl->connect();
}

DatabaseConnectorSQLite::DatabaseConnectorSQLite(const QString &dbName)
{
    m_dbName = dbName;
}

QSqlDatabase DatabaseConnectorSQLite::connect()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(prepareDb());

    if(!m_db.open())
        throw ::Exception<QString>("Database not open");
    return m_db;
}

DatabaseConnectorPostgres::DatabaseConnectorPostgres(const QString &dbName)
{
    m_dbName = dbName;
}
