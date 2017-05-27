greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET = terminal
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    binParser.cpp \
    TableView/c7373h.cpp \
    TableView/fastcmd.cpp \
    TableView/csenddialog.cpp \
    TableView/crecvdialog.cpp \
    TableView/crecv35hdialog.cpp


HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    typedefine.h \
    bin.h \
    TableView/c7373h.h \
    TableView/fastcmd.h \
    TableView/csenddialog.h \
    TableView/crecvdialog.h \
    TableView/crecv35hdialog.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    TableView/c7373h.ui \
    TableView/fastcmd.ui \
    TableView/csenddialog.ui \
    TableView/crecvdialog.ui \
    TableView/crecv35hdialog.ui

RESOURCES += \
    terminal.qrc
