#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H
#include <QSqlDatabase>
#include <QMultiMap>

namespace {
    template<class Type>
    class Exception
    {
    public:
        Exception(const Type& arg) : m_err(arg){}
        Exception(const Exception& ex) : m_err(ex.m_err){}
        Type what() const {return m_err;}
    private:
        QString m_err;
    };
}

///////////////////////////////////////

class DatabaseConnector;
class DatabaseConnectorPrivate{
    friend class DatabaseConnector;
public:
    DatabaseConnectorPrivate();
    virtual ~DatabaseConnectorPrivate(){}
    virtual QSqlDatabase connect() = 0;
    virtual QString prepareDb() const final;

protected:
    QString      m_dbName;
    QSqlDatabase m_db;
};

///////////////////////////////////////

class DatabaseConnector{
public:
    enum DBExtension{
        SQLITE_EXTENTION,
        POSTGRES_EXTENTION,
        MYSQL_EXTENTION
    };
    DatabaseConnector(const QString& dbName);
    ~DatabaseConnector(){}
    QSqlDatabase connectToDatabase();

private:
    DatabaseConnectorPrivate* m_impl;
    QMultiMap<QString, DBExtension> m_dbTypesContainer;
};

///////////////////////////////////////

class DatabaseConnectorSQLite : public DatabaseConnectorPrivate{
public:
    DatabaseConnectorSQLite(const QString& dbName);
    QSqlDatabase connect() override;
};

///////////////////////////////////////

class DatabaseConnectorPostgres : public DatabaseConnectorPrivate{
public:
    DatabaseConnectorPostgres(const QString& dbName);
    QSqlDatabase connect() override;
};


#endif // DATABASECONNECTOR_H
