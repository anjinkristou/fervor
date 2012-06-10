#ifndef FVUPDATECHECKINGDIALOG_H
#define FVUPDATECHECKINGDIALOG_H

#include <QDialog>

namespace Ui {
class FvUpdateCheckingDialog;
}

class FvUpdateCheckingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FvUpdateCheckingDialog(QWidget *parent = 0);
    ~FvUpdateCheckingDialog();
    
    void updateProgressBar(int profress);

    void closeEvent(QCloseEvent *event);
private:
    Ui::FvUpdateCheckingDialog *m_ui;
};

#endif // FVUPDATECHECKINGDIALOG_H
