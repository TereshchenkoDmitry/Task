QT += core gui widgets sql

CONFIG += c++11

INCLUDEPATH += databaseManager/
HEADERS += $$INCLUDEPATH/DataBase.h \
           $$INCLUDEPATH/DatabaseConnector.h \
           $$INCLUDEPATH/DatabaseManager.h \
    AddOperatorDialog.h \
    IEditDialog.h \
    Task.h


SOURCES += $$INCLUDEPATH/DataBase.cpp \
           $$INCLUDEPATH/DatabaseConnector.cpp \
           $$INCLUDEPATH/DatabaseManager.cpp \
    AddOperatorDialog.cpp \
    IEditDialog.cpp \
    Task.cpp

SOURCES += \
    CustomTreeView.cpp \
    Delegate.cpp \
    EditOperatorDialog.cpp \
    TreeItem.cpp \
    TreeModel.cpp \
    main.cpp

HEADERS += \
    CustomTreeView.h \
    Delegate.h \
    EditOperatorDialog.h \
    OperatorsInfo.h \
    TreeItem.h \
    TreeModel.h

FORMS += \
    EditOperatorDialog.ui \
    Task.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc
