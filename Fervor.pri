QT += core gui webkit network

DEFINES += FV_APP_NAME=\\\"$$TARGET\\\"
DEFINES += FV_APP_VERSION=\\\"$$VERSION\\\"



# FIXME unit tests
#DEFINES += FV_DEBUG=1
#DEPENDPATH += "$$PWD/tests/"
#INCLUDEPATH += "$$PWD/tests/"
#CONFIG += qtestlib
#SOURCES += tests/fvversioncomparatortest.cpp
#HEADERS += tests/fvversioncomparatortest.h



DEPENDPATH += "$$PWD"
INCLUDEPATH += "$$PWD"

SOURCES += fvupdatewindow.cpp \
	fvupdater.cpp \
	fvversioncomparator.cpp \
	fvplatform.cpp \
	fvignoredversions.cpp \
	fvavailableupdate.cpp \
	fvupdateconfirmdialog.cpp \
        fvautoupdateconfirmdialog.cpp \
        fvupdatecheckingdialog.cpp

HEADERS += fvupdatewindow.h \
	fvupdater.h \
	fvversioncomparator.h \
	fvplatform.h \
	fvignoredversions.h \
	fvavailableupdate.h \
	fvupdateconfirmdialog.h \
        fvautoupdateconfirmdialog.h \
        fvupdatecheckingdialog.h

FORMS += fvupdatewindow.ui \
	fvupdateconfirmdialog.ui \
        fvautoupdateconfirmdialog.ui \
        fvupdatecheckingdialog.ui

TRANSLATIONS += fervor_lt.ts \
        fervor_ja.ts \
        fervor_fr.ts
CODECFORTR = UTF-8

RESOURCES += Farvor.qrc
