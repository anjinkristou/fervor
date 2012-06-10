#ifndef FVUPDATER_H
#define FVUPDATER_H

#include <QObject>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QXmlStreamReader>
#include <QTimer>
class FvUpdateWindow;
class FvUpdateConfirmDialog;
class FvAvailableUpdate;
class FvAutoUpdateConfirmDialog;
class FvUpdateCheckingDialog;
class FvAutoUpdater;


class FvUpdater : public QObject
{
	Q_OBJECT

public:

	// Singleton
	static FvUpdater* sharedUpdater();
	static void drop();

	// Set / get feed URL
	void SetFeedURL(QUrl feedURL);
	void SetFeedURL(QString feedURL);
	QString GetFeedURL();
	
public slots:

	// Check for updates
	bool CheckForUpdates(bool silentAsMuchAsItCouldGet = true);

	// Aliases
	bool CheckForUpdatesSilent();
	bool CheckForUpdatesNotSilent();

    bool AskForAutoUpdateConfirmations();
    void initAutoUpdater();

	//
	// ---------------------------------------------------
	// ---------------------------------------------------
	// ---------------------------------------------------
	// ---------------------------------------------------
	//

protected:

    friend class FvUpdateWindow;            // Uses GetProposedUpdate() and others
    friend class FvUpdateConfirmDialog;     // Uses GetProposedUpdate() and others
    friend class FvAutoUpdateConfirmDialog;	// Uses GetProposedUpdate() and others
    friend class FvUpdateCheckingDialog;	// Uses GetProposedUpdate() and others
    friend class FvAutoUpdater;
	FvAvailableUpdate* GetProposedUpdate();


protected slots:

	// Update window button slots
	void InstallUpdate();
	void SkipUpdate();
	void RemindMeLater();

	// Update confirmation dialog button slots
	void UpdateInstallationConfirmed();
	void UpdateInstallationNotConfirmed();

    // Auto update confirmation dialog button slots
    void checkAutomaticallyForUpdates();
    void dontCheckAutomaticallyForUpdates();

    // Update timer process
    void updateTimerPerformer();

private:

	//
	// Singleton business
	//
	// (we leave just the declarations, so the compiler will warn us if we try
	//  to use those two functions by accident)
	FvUpdater();							// Hide main constructor
	~FvUpdater();							// Hide main destructor
	FvUpdater(const FvUpdater&);			// Hide copy constructor
	FvUpdater& operator=(const FvUpdater&);	// Hide assign op

	static FvUpdater* m_Instance;			// Singleton instance


	//
	// Windows / dialogs
	//
	FvUpdateWindow* m_updaterWindow;								// Updater window (NULL if not shown)
	void showUpdaterWindowUpdatedWithCurrentUpdateProposal();		// Show updater window
	void hideUpdaterWindow();										// Hide + destroy m_updaterWindow
	void updaterWindowWasClosed();									// Sent by the updater window when it gets closed

	FvUpdateConfirmDialog* m_updateConfirmationDialog;						// Update confirmation dialog (NULL if not shown)
	void showUpdateConfirmationDialogUpdatedWithCurrentUpdateProposal();	// Show update confirmation dialog
	void hideUpdateConfirmationDialog();									// Hide + destroy m_updateConfirmationDialog
	void updateConfirmationDialogWasClosed();								// Sent by the update confirmation dialog when it gets closed

    FvAutoUpdateConfirmDialog* m_autoupdateConfirmationDialog;		// Auto Update confirmation dialog (NULL if not shown)
    void showAutoUpdateConfirmationDialog();                        // Show Auto update confirmation dialog
    void hideAutoUpdateConfirmationDialog();						// Hide + destroy m_autoUpdateConfirmationDialog
    void autoUpdateConfirmationDialogWasClosed();					// Sent by the auto update confirmation dialog when it gets closed
    void initAutoU5pdater();

    FvUpdateCheckingDialog* m_updateCheckingDialog;					// Update checking dialog (NULL if not shown)
    void showUpdateCheckingDialog();                                // Show update checking dialog
    void hideUpdateCheckingDialog();								// Hide + destroy m_updateCheckingDialog
    void updateCheckingDialogWasClosed();							// Sent by the update checking dialog when it gets closed
    void updateCheckingDialogUpdateProgress(int progress);                // Update the progress bar

    // Auto updater logic
    FvAutoUpdater* m_autoUpdater;
    QTimer* m_updateTimer;
    void setAutoUpdateTimerInterval(int interval);
    void startAutoUpdateTimer();
    void stopAutoUpdateTimer();

	// Available update (NULL if not fetched)
	FvAvailableUpdate* m_proposedUpdate;

	// If true, don't show the error dialogs and the "no updates." dialog
	// (silentAsMuchAsItCouldGet from CheckForUpdates() goes here)
	// Useful for automatic update checking upon application startup.
	bool m_silentAsMuchAsItCouldGet;

	// Dialogs (notifications)
	void showErrorDialog(QString message, bool showEvenInSilentMode = false);			// Show an error message
	void showInformationDialog(QString message, bool showEvenInSilentMode = false);		// Show an informational message


	//
	// HTTP feed fetcher infrastructure
	//
	QUrl m_feedURL;					// Feed URL that will be fetched
	QNetworkAccessManager m_qnam;
	QNetworkReply* m_reply;
	int m_httpGetId;
	bool m_httpRequestAborted;

	void startDownloadFeed(QUrl url);	// Start downloading feed
	void cancelDownloadFeed();			// Stop downloading the current feed

private slots:

	void httpFeedReadyRead();
	void httpFeedUpdateDataReadProgress(qint64 bytesRead,
										qint64 totalBytes);
	void httpFeedDownloadFinished();


private:

	//
	// XML parser
	//
	QXmlStreamReader m_xml;				// XML data collector and parser
	bool xmlParseFeed();				// Parse feed in m_xml
	bool searchDownloadedFeedForUpdates(QString xmlTitle,
										QString xmlLink,
										QString xmlReleaseNotesLink,
										QString xmlPubDate,
										QString xmlEnclosureUrl,
										QString xmlEnclosureVersion,
										QString xmlEnclosurePlatform,
										unsigned long xmlEnclosureLength,
										QString xmlEnclosureType);


	//
	// Helpers
	//
	void installTranslator();			// Initialize translation mechanism

};

#endif // FVUPDATER_H
