#include "fvautoupdater.h"
#include "fvupdater.h"

#include <QSettings>

// QSettings key for auto update confirmation
#define FV_AUTO_UPDATE_CONFIRMATION_KEY	"FVAutoUpdateConfirmation"
#define FV_AUTO_UPDATE_STARTS_KEY       "FVAutoUpdateStart"

FvAutoUpdater::FvAutoUpdater(QObject *parent) :
    QObject(parent)
{
    m_skipStarts = 1;
    m_updateInterval = 60*60*1000; // every 1 hour
}

void FvAutoUpdater::AutoUpdateAccepted()
{
    QSettings settings;
    settings.setValue(FV_AUTO_UPDATE_CONFIRMATION_KEY, true);
    initAutoUpdater();

}

void FvAutoUpdater::AutoUpdateRefused()
{
    QSettings settings;
    settings.setValue(FV_AUTO_UPDATE_CONFIRMATION_KEY, false);
}

void FvAutoUpdater::initAutoUpdater()
{
    bool ask = shoudAskForConfirmation();
    if(ask){
        printf("skippedApplicationStarts\n");
        markApplicationStart();
        int skippedApplicationStarts = lastApplicationStart();
        printf("skippedApplicationStarts[%d]\n", skippedApplicationStarts);
        if(skippedApplicationStarts > m_skipStarts){
            FvUpdater::sharedUpdater()->showAutoUpdateConfirmationDialog();
        }
    }else{
        bool automaticUpdate = shouldStartAutomaticUpdate();
        if(automaticUpdate){
            FvUpdater::sharedUpdater()->setAutoUpdateTimerInterval(m_updateInterval);
            FvUpdater::sharedUpdater()->startAutoUpdateTimer();
        }else{
            FvUpdater::sharedUpdater()->stopAutoUpdateTimer();
        }
    }
}

bool FvAutoUpdater::shoudAskForConfirmation()
{
    QSettings settings;
    return !settings.contains(FV_AUTO_UPDATE_CONFIRMATION_KEY);
}

int FvAutoUpdater::lastApplicationStart()
{
    QSettings settings;
    if(!settings.contains(FV_AUTO_UPDATE_STARTS_KEY)){
        return 0;
    }

    return settings.value(FV_AUTO_UPDATE_STARTS_KEY).toInt();
}

void FvAutoUpdater::markApplicationStart()
{
    QSettings settings;
    if(!settings.contains(FV_AUTO_UPDATE_STARTS_KEY)){
        settings.setValue(FV_AUTO_UPDATE_STARTS_KEY, 1);
        return;
    }

    int starts = settings.value(FV_AUTO_UPDATE_STARTS_KEY).toInt();
    starts += 1;
    settings.setValue(FV_AUTO_UPDATE_STARTS_KEY, starts);
}

bool FvAutoUpdater::shouldStartAutomaticUpdate()
{
    QSettings settings;
    if(settings.contains(FV_AUTO_UPDATE_CONFIRMATION_KEY)){
        return settings.value(FV_AUTO_UPDATE_CONFIRMATION_KEY).toBool();
    }

    return false;
}

