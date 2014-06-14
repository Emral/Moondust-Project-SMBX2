/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QMdiArea>
#include <QPixmap>
#include <QAbstractListModel>
#include <QList>
#include <QPoint>
#include <QString>
#include <QStringList>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QFile>
#include <QSettings>
#include <QTranslator>
#include <QLocale>
#include <QSplashScreen>

#include "file_formats/lvl_filedata.h"
#include "file_formats/wld_filedata.h"
#include "file_formats/npc_filedata.h"

#include "edit_level/leveledit.h"
#include "edit_npc/npcedit.h"

#include "about_dialog/aboutdialog.h"
#include "edit_level/levelprops.h"

#include "data_configs/data_configs.h"

#include "common_features/musicfilelist.h"
#include "common_features/logger.h"


QT_BEGIN_NAMESPACE
    class QMimeData;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QMdiArea *parent = 0);
    ~MainWindow();
    //dataconfigs *getConfigs();
    void openFilesByArgs(QStringList args);

    dataconfigs configs; // Global objects configucrations

    //Sub Windows
    int activeChildWindow();
    npcedit *activeNpcEditWin();
    leveledit *activeLvlEditWin();
    void showStatusMsg(QString msg, int time=2000);

    void LvlItemProps(int Type, LevelBlock block, LevelBGO bgo, LevelNPC npc, bool newItem=false);
    long blockPtr; //ArrayID of editing item (-1 - use system)
    long bgoPtr; //ArrayID of editing item
    long npcPtr; //ArrayID of editing item
    bool isHistoryChangingData;

protected:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);

public slots:
    //Clipboard
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();

    //Common functions
    void save();
    void save_as();
    void close_sw();
    void save_all();
    void refreshHistoryButtons();

    void OpenFile(QString FilePath);
    void SyncRecentFiles();
    void AddToRecentFiles(QString FilePath);

    void updateMenus(bool force=false);
    void updateWindowMenu();

    void setLevelSectionData();
    void setMusic(bool checked);
    void setMusicButton(bool checked);

    void setItemBoxes(bool setCat=false);
    void UpdateCustomItems();

    void DragAndDroppedLayer(QModelIndex sourceParent,int sourceStart,int sourceEnd,QModelIndex destinationParent,int destinationRow);

    //SubWindow functions
    npcedit *createNPCChild();
    leveledit *createLvlChild();
    void setActiveSubWindow(QWidget *window);
    void SWCascade();
    void SWTile();


    //LevelEdit functions
    void SetCurrentLevelSection(int SctId, int open=0);
    void setDoorsToolbox();
    void setDoorData(long index=-1);
    void SwitchToDoor(long arrayID);
    void setLayersBox();
    void setLayerLists();
    void EventListsSync();

    //LvlDoorProps Functions
    QComboBox* getWarpList();
    void setWarpRemoveButtonEnabled(bool isEnabled);
    void removeItemFromWarpList(int index);

    void on_ResizeSection_clicked();
    void on_applyResize_clicked();
    void on_cancelResize_clicked();


    //EditMode switch
    void on_actionSelect_triggered();
    void on_actionSelectOnly_triggered();
    void on_actionEriser_triggered();
    void on_actionHandScroll_triggered();

    void on_actionSetFirstPlayer_triggered();
    void on_actionSetSecondPlayer_triggered();

    void on_actionDrawWater_triggered();
    void on_actionDrawSand_triggered();


    //void on_LVLPropsMusicPlay_toggled(bool checked);
    void on_actionPlayMusic_triggered(bool checked);
    void on_LVLPropsMusicCustom_textChanged(const QString &arg1);
    void on_actionReset_position_triggered();
    void on_actionGridEn_triggered(bool checked);
    void on_LVLPropsBackImage_currentIndexChanged(int index);
    void on_actionReload_triggered();

private slots:

    //void TickTack();

    //Actions
    void on_LevelSectionSettings_visibilityChanged(bool visible);
    void on_LevelToolBox_visibilityChanged(bool visible);
	void on_WorldToolBox_visibilityChanged(bool visible);
    void on_OpenFile_triggered();
    void on_Exit_triggered();
    void on_actionAbout_triggered();
    void on_actionLVLToolBox_triggered();
    void on_actionWLDToolBox_triggered();
    void on_actionLevelProp_triggered();
    void on_actionSection_Settings_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionClose_triggered();
    void on_actionSave_all_triggered();
    void on_actionSection_1_triggered();
    void on_actionSection_2_triggered();
    void on_actionSection_3_triggered();
    void on_actionSection_4_triggered();
    void on_actionSection_5_triggered();
    void on_actionSection_6_triggered();
    void on_actionSection_7_triggered();
    void on_actionSection_8_triggered();
    void on_actionSection_9_triggered();
    void on_actionSection_10_triggered();
    void on_actionSection_11_triggered();
    void on_actionSection_12_triggered();
    void on_actionSection_13_triggered();
    void on_actionSection_14_triggered();
    void on_actionSection_15_triggered();
    void on_actionSection_16_triggered();
    void on_actionSection_17_triggered();
    void on_actionSection_18_triggered();
    void on_actionSection_19_triggered();
    void on_actionSection_20_triggered();
    void on_actionSection_21_triggered();
    void on_actionLoad_configs_triggered();
    void on_actionExport_to_image_triggered();


    void on_LVLPropsMusicNumber_currentIndexChanged(int index);
    void on_LVLPropsMusicCustomEn_toggled(bool checked);
    void on_LVLPropsMusicCustomBrowse_clicked();

    void on_actionApplication_settings_triggered();


    //Locks
    void on_actionLockBlocks_triggered(bool checked);
    void on_actionLockBGO_triggered(bool checked);
    void on_actionLockNPC_triggered(bool checked);
    void on_actionLockWaters_triggered(bool checked);
    void on_actionLockDoors_triggered(bool checked);

    void on_LVLPropsLevelWarp_clicked(bool checked);
    void on_actionLevWarp_triggered(bool checked);
    void on_LVLPropsOffScr_clicked(bool checked);
    void on_actionLevOffScr_triggered(bool checked);
    void on_LVLPropsNoTBack_clicked(bool checked);
    void on_actionLevNoBack_triggered(bool checked);
    void on_LVLPropsUnderWater_clicked(bool checked);
    void on_actionLevUnderW_triggered(bool checked);

    void on_actionAnimation_triggered(bool checked);
    void on_actionCollisions_triggered(bool checked);

    //RecentFiles Items
    void on_action_recent1_triggered();
    void on_action_recent2_triggered();
    void on_action_recent3_triggered();
    void on_action_recent4_triggered();
    void on_action_recent5_triggered();
    void on_action_recent6_triggered();
    void on_action_recent7_triggered();
    void on_action_recent8_triggered();
    void on_action_recent9_triggered();
    void on_action_recent10_triggered();

    //History
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();


    void on_actionWarpsAndDoors_triggered(bool checked);
    void on_DoorsToolbox_visibilityChanged(bool visible);

    void on_WarpList_currentIndexChanged(int index); //Door list

    void on_WarpAdd_clicked();
    void on_WarpRemove_clicked();
    void on_WarpSetEntrance_clicked();
    void on_WarpSetExit_clicked();
    void on_WarpNoYoshi_clicked(bool checked);
    void on_WarpAllowNPC_clicked(bool checked);
    void on_WarpLock_clicked(bool checked);
    void on_WarpType_currentIndexChanged(int index);
    void on_WarpNeedAStars_valueChanged(int arg1);
    void on_Entr_Down_clicked();
    void on_Entr_Right_clicked();
    void on_Entr_Up_clicked();
    void on_Entr_Left_clicked();
    void on_Exit_Up_clicked();
    void on_Exit_Left_clicked();
    void on_Exit_Right_clicked();
    void on_Exit_Down_clicked();
    void on_WarpToMapX_textEdited(const QString &arg1);
    void on_WarpToMapY_textEdited(const QString &arg1);
    void on_WarpGetXYFromWorldMap_clicked();
    void on_WarpLevelExit_clicked(bool checked);
    void on_WarpLevelEntrance_clicked(bool checked);
    void on_WarpLevelFile_textChanged(const QString &arg1);
    void on_WarpToExitNu_valueChanged(int arg1);

    //void on_goToWarpDoor_clicked();


    void on_LevelLayers_visibilityChanged(bool visible);
    void on_actionLayersBox_triggered(bool checked);

    void on_BGOUniform_clicked(bool checked);
    void on_BlockUniform_clicked(bool checked);

    void on_NPCUniform_clicked(bool checked);
    void on_BlockCatList_currentIndexChanged(const QString &arg1);
    void on_BGOCatList_currentIndexChanged(const QString &arg1);
    void on_NPCCatList_currentIndexChanged(const QString &arg1);

    void on_actionNewNPC_config_triggered();

    void on_AddLayer_clicked();
    void on_LvlLayerList_itemChanged(QListWidgetItem *item);

    void on_RemoveLayer_clicked();


    void on_LvlLayerList_customContextMenuRequested(const QPoint &pos);

    void on_MainWindow_customContextMenuRequested(const QPoint &pos);

    void on_BlockItemsList_itemClicked(QListWidgetItem *item);

    void slotLanguageChanged(QAction *action);

    void on_BGOItemsList_itemClicked(QListWidgetItem *item);
    void on_NPCItemsList_itemClicked(QListWidgetItem *item);
    void on_PROPS_BlockResize_clicked();

    void on_PROPS_BlockSquareFill_clicked(bool checked);
    void on_PROPS_BlockInvis_clicked(bool checked);
    void on_PROPS_BlkSlippery_clicked(bool checked);
    void on_PROPS_BlockIncludes_clicked();
    void on_PROPS_BlockLayer_currentIndexChanged(const QString &arg1);
    void on_PROPS_BlkEventDestroy_currentIndexChanged(const QString &arg1);
    void on_PROPS_BlkEventHited_currentIndexChanged(const QString &arg1);
    void on_PROPS_BlkEventLayerEmpty_currentIndexChanged(const QString &arg1);

    void on_actionGo_to_Section_triggered();

    void on_PROPS_BGOLayer_currentIndexChanged(const QString &arg1);

    void on_PROPS_NPCDirLeft_clicked();
    void on_PROPS_NPCDirRand_clicked();
    void on_PROPS_NPCDirRight_clicked();
    void on_PROPS_NpcFri_clicked(bool checked);
    void on_PROPS_NPCNoMove_clicked(bool checked);
    void on_PROPS_NpcBoss_clicked(bool checked);
    void on_PROPS_NpcTMsg_clicked();
    void on_PROPS_NPCSpecialSpin_valueChanged(int arg1);
    void on_PROPS_NPCContaiter_clicked();
    void on_PROPS_NPCSpecialBox_currentIndexChanged(int index);
    void on_PROPS_NpcGenerator_clicked(bool checked);
    void on_PROPS_NPCGenType_currentIndexChanged(int index);
    void on_PROPS_NPCGenTime_valueChanged(double arg1);
    void on_PROPS_NPCGenUp_clicked();
    void on_PROPS_NPCGenLeft_clicked();
    void on_PROPS_NPCGenDown_clicked();
    void on_PROPS_NPCGenRight_clicked();
    void on_PROPS_NpcLayer_currentIndexChanged(const QString &arg1);
    void on_PROPS_NpcAttachLayer_currentIndexChanged(const QString &arg1);
    void on_PROPS_NpcEventActivate_currentIndexChanged(const QString &arg1);
    void on_PROPS_NpcEventDeath_currentIndexChanged(const QString &arg1);
    void on_PROPS_NpcEventTalk_currentIndexChanged(const QString &arg1);
    void on_PROPS_NpcEventEmptyLayer_currentIndexChanged(const QString &arg1);

    void on_PROPS_BGO_smbx64_sp_valueChanged(int arg1);

    void on_actionNewLevel_triggered();

    void on_actionNewWorld_map_triggered();

    void on_PROPS_BGOSquareFill_clicked(bool checked);

    void on_actionLevelEvents_triggered(bool checked);

    void on_LevelEventsToolBox_visibilityChanged(bool visible);

private:

    LevelEditingSettings LvlOpts;
    bool AnimationEnabled; //Animator switch

    LevelData LvlBuffer; // The Clipboarc for Level objects

    QString LastOpenDir;
    int lastWinType;
    bool LevelToolBoxVis; //Level toolbox
    bool SectionToolBoxVis; //Section Settings
    bool LevelDoorsBoxVis; //Doors box
    bool LevelLayersBoxVis; //Layers box
    bool LevelEventsBoxVis; //Events box
    bool WorldToolBoxVis;
    bool autoPlayMusic;


    // ////////////Layer Functions///////////////////
    void RemoveCurrentLayer(bool moveToDefault);
    void RemoveLayerItems(QString layerName);
    void RemoveLayerFromListAndData(QListWidgetItem * layerItem);
    void ModifyLayer(QString layerName, bool visible);
    void ModifyLayer(QString layerName, QString newLayerName);
    void ModifyLayer(QString layerName, QString newLayerName, bool visible);
    //Direct List Functions
    void AddNewLayer(QString layerName, bool setEdited);
    void ModifyLayerItem(QListWidgetItem *item, QString oldLayerName, QString newLayerName, bool visible);
    // //////////////////////////////////////////////

    QMediaPlayer * MusicPlayer;

    QMdiSubWindow *findMdiChild(const QString &fileName);
    QSignalMapper *windowMapper;

//    QTimer * TickTackTimer; //Scene Events detector
//    bool TickTackLock;      //Scene Events detector locker

//    QThread * thread1;

    QList<QString> recentOpen; //Recent files list

    //Application Settings
    void setDefaults();
    void setUiDefults();

    void resetEditmodeButtons();

    void loadSettings();
    void saveSettings();

    //CategorySorted
    QString cat_blocks;
    QString cat_bgos;
    QString cat_npcs;


    //Miltilanguage
    void loadLanguage(const QString& rLanguage);
    void setDefLang();
    bool switchTranslator(QTranslator &translator, const QString &filename);
    void langListSync();
    QTranslator     m_translator;   /**< contains the translations for this application */
    QTranslator     m_translatorQt; /**< contains the translations for qt */
    QString         m_currLang;     /**< contains the currently loaded language */
    QString         m_langPath;     /**< Path of language files. This is always fixed to /languages. */


    void setPointer();

    Ui::MainWindow *ui;

};





////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
