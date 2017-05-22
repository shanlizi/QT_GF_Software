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
    TableView/c7373h.cpp


HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    typedefine.h \
    bin.h \
    TableView/c7373h.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    TableView/c7373h.ui

RESOURCES += \
    terminal.qrc
