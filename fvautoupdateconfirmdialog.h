#ifndef FVAUTOUPDATECONFIRMDIALOG_H
#define FVAUTOUPDATECONFIRMDIALOG_H

#include <QDialog>

namespace Ui {
class FvAutoUpdateConfirmDialog;
}

class FvAutoUpdateConfirmDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FvAutoUpdateConfirmDialog(QWidget *parent = 0);
    ~FvAutoUpdateConfirmDialog();
    
    void closeEvent(QCloseEvent *event);
private:
    Ui::FvAutoUpdateConfirmDialog *m_ui;
};

#endif // FVAUTOUPDATECONFIRMDIALOG_H
