#ifndef DATABASE_H
#define DATABASE_H
#include <QMap>
#include <QSqlQuery>
#include <QMutexLocker>
#include <QScopedPointer>

class DatabaseConnector;
class DataBase{
public:
    DataBase();
    ~DataBase();
    void setDatabase(const QString& nameDB);
    void releaseDatabase();
    void insert(const QString &sql, QMap<QString, QVariant> params, bool &ok);
    void update(const QString &sql, QMap<QString, QVariant> params, bool &ok);
    QSqlQuery select(const QString &sql, QMap<QString, QVariant> params, bool &ok);


private:
    void commit();
    void transaction();
    void rollback();

private:
    QScopedPointer<DatabaseConnector> connector;
    QSqlDatabase m_db;
    QMutex       m_mutex;
};

#endif // DATABASE_H
