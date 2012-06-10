#include "fvupdatecheckingdialog.h"
#include "ui_fvupdatecheckingdialog.h"

#include "fvupdater.h"
#include <QCloseEvent>

FvUpdateCheckingDialog::FvUpdateCheckingDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FvUpdateCheckingDialog)
{
    m_ui->setupUi(this);

    // Delete on close
    setAttribute(Qt::WA_DeleteOnClose, true);
    connect(m_ui->cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

FvUpdateCheckingDialog::~FvUpdateCheckingDialog()
{
    delete m_ui;
}

void FvUpdateCheckingDialog::updateProgressBar(int progress)
{
    m_ui->progressBar->setValue(progress);
}

void FvUpdateCheckingDialog::closeEvent(QCloseEvent* event)
{
    FvUpdater::sharedUpdater()->updateCheckingDialogWasClosed();
    event->accept();
}
