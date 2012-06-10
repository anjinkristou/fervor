#include <QtGui/QApplication>
#include "mainwindow.h"
#include "fvupdater.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Prerequisite for the Fervor updater
	QApplication::setOrganizationName("pypt");
	QApplication::setOrganizationDomain("pypt.lt");
    QApplication::setApplicationName("Sample App");
    QApplication::setApplicationVersion("1.0");

	// Set feed URL before doing anything else
	FvUpdater::sharedUpdater()->SetFeedURL("https://raw.github.com/pypt/fervor/master/sample/Appcast.xml");

	// Check for updates automatically
    //FvUpdater::sharedUpdater()->CheckForUpdatesSilent();
    FvUpdater::sharedUpdater()->initAutoUpdater();
    FvUpdater::sharedUpdater()->AskForAutoUpdateConfirmations();


	// Show main window
	MainWindow w;
	w.show();
	
	return a.exec();
}
