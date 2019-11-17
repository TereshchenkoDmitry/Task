#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDir>
#include <QFile>
#include <QScopedPointer>
#include "OperatorsInfo.h"

class DataBase;
class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
    void operatorsData(OperatorInfo &info);
    bool updateOperator(const Operator& oper);
    bool addOperator(const Operator& oper);

private:
    QScopedPointer<DataBase> m_database;
};

#endif //DATABASEMANAGER_H
