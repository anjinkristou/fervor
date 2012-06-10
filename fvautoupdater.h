#ifndef FVAUTOUPDATER_H
#define FVAUTOUPDATER_H

#include <QObject>

class FvAutoUpdater: public QObject
{
    Q_OBJECT

public:
    explicit FvAutoUpdater(QObject *parent = 0);
    void AutoUpdateAccepted();
    void AutoUpdateRefused();
    void initAutoUpdater();
    void markApplicationStart();
    bool shoudAskForConfirmation();
    int lastApplicationStart();
    bool shouldStartAutomaticUpdate();

private:
    int m_skipStarts;
    int m_updateInterval;
};

#endif // FVAUTOUPDATER_H
