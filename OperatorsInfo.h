#ifndef OPERATORSINFO_H
#define OPERATORSINFO_H
#include <QString>
#include <QMap>

struct Operator
{
    Operator() : name(), mcc(), mnc(){}
    QString name;
    int mcc;
    int mnc;
};

typedef QString CountryName;
typedef QMap<CountryName, QList<Operator>> OperatorInfo;

#endif // OPERATORSINFO_H
