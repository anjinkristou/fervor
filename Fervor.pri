QT += core gui webkit network

isEmpty(FV_APP_NAME) {
	warning("Fervor: falling back to application name '$$TARGET'")
	DEFINES += FV_APP_NAME=\\\"$$TARGET\\\"
} else {
	message("Fervor: building for application name '$$FV_APP_NAME'")
	DEFINES += FV_APP_NAME=\\\"$$FV_APP_NAME\\\"
}

isEmpty(FV_APP_VERSION) {
	warning("Fervor: falling back to application version '$$VERSION'")
	DEFINES += FV_APP_VERSION=\\\"$$VERSION\\\"
} else {
	message("Fervor: building for application version '$$FV_APP_VERSION'")
	DEFINES += FV_APP_VERSION=\\\"$$FV_APP_VERSION\\\"
}

# Unit tests
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
        fvupdatecheckingdialog.cpp \
    ../fvautoupdater.cpp

HEADERS += fvupdatewindow.h \
	fvupdater.h \
	fvversioncomparator.h \
	fvplatform.h \
	fvignoredversions.h \
	fvavailableupdate.h \
	fvupdateconfirmdialog.h \
        fvautoupdateconfirmdialog.h \
        fvupdatecheckingdialog.h \
    ../fvautoupdater.h

FORMS += fvupdatewindow.ui \
	fvupdateconfirmdialog.ui \
        fvautoupdateconfirmdialog.ui \
        fvupdatecheckingdialog.ui

TRANSLATIONS += fervor_lt.ts \
        fervor_ja.ts \
        fervor_fr.ts
CODECFORTR = UTF-8

RESOURCES += Farvor.qrc
