#include "fvautoupdateconfirmdialog.h"
#include "ui_fvautoupdateconfirmdialog.h"

#include "fvupdater.h"
#include <QCloseEvent>

FvAutoUpdateConfirmDialog::FvAutoUpdateConfirmDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FvAutoUpdateConfirmDialog)
{
    m_ui->setupUi(this);

    // Delete on close
    setAttribute(Qt::WA_DeleteOnClose, true);

    // stay on top
    setWindowFlags( Qt::WindowStaysOnTopHint );

    // Set the application name in string
    QString closeReopenString = m_ui->checkForUpdatesLabel->text().arg(QApplication::applicationName());
    m_ui->checkForUpdatesLabel->setText(closeReopenString);

    connect(m_ui->checkAutomaticallyButton, SIGNAL(clicked()),
            FvUpdater::sharedUpdater(), SLOT(checkAutomaticallyForUpdates()));
    connect(m_ui->dontCheckButton, SIGNAL(clicked()),
            FvUpdater::sharedUpdater(), SLOT(dontCheckAutomaticallyForUpdates()));
}

FvAutoUpdateConfirmDialog::~FvAutoUpdateConfirmDialog()
{
    delete m_ui;
}

void FvAutoUpdateConfirmDialog::closeEvent(QCloseEvent* event)
{
    FvUpdater::sharedUpdater()->autoUpdateConfirmationDialogWasClosed();
    event->accept();
}
