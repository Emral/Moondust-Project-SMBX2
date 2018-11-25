#pragma once
#ifndef WLD_SETTINGS_BOX_H
#define WLD_SETTINGS_BOX_H

#include <QDockWidget>
#include <QCheckBox>
#include <QMap>
#include <QSet>
#include "mwdock_base.h"

class MainWindow;
struct WorldLevelTile;

namespace Ui
{
    class WorldSettingsBox;
}

class WorldSettingsBox : public QDockWidget, public MWDock_Base
{
    Q_OBJECT

    friend class MainWindow;
    explicit WorldSettingsBox(QWidget *parent = 0);
    ~WorldSettingsBox();
public slots:
    void re_translate();
    void setCurrentWorldSettings();
private slots:
    void on_WorldSettingsBox_visibilityChanged(bool visible);

    void on_WLD_Title_editingFinished();
    void on_WLD_NoWorldMap_clicked(bool checked);
    void updateLevelIntroLabel();
    void on_WLD_RestartLevel_clicked(bool checked);
    void on_WLD_AutostartLvl_editingFinished();
    void on_WLD_AutostartLvlBrowse_clicked();
    void on_WLD_Stars_valueChanged(int arg1);
    void on_WLD_DoCountStars_clicked();
    void on_WLD_Credirs_textChanged();
    void characterActivated(bool checked);

signals:
    void countedStar(int);
private:
    Ui::WorldSettingsBox *ui;
    bool world_settings_lock_fields;
    QMap<QCheckBox *, int> WLD_CharacterCheckBoxes;

    //for star counter
    unsigned long doStarCount(QString dir, QList<WorldLevelTile > levels, QString introLevel);
    unsigned long StarCounter_checkLevelFile(QString FilePath, QSet<QString> &exists);
    bool StarCounter_canceled;
};

#endif // WLD_SETTINGS_BOX_H
