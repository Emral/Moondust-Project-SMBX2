#ifndef LVL_HISTORY_MANAGER_H
#define LVL_HISTORY_MANAGER_H

#include <QObject>
#include "lvl_scene.h"
#include "items/item_block.h"
#include "items/item_bgo.h"
#include "items/item_npc.h"
#include "items/item_water.h"
#include "items/item_door.h"
#include "items/item_playerpoint.h"

/*
 * NOTE: when use History with Doors, LevelDoors MUST be posted individual.
 * If Door Entrance: LevelDoors.isSetIn = true and LevelDoors.isSetOut = false
 * If Door Exit: LevelDoors.isSetOut = true and LevelDoors.isSetIn = false
 *
 */
class LvlHistoryManager : public QObject
{
    Q_OBJECT

    friend class LvlScene;
    LvlScene* m_scene;
    bool    historyChanged;
    int     historyIndex;
    QList<QSharedPointer<IHistoryElement> > operationList;
public:
    explicit LvlHistoryManager(LvlScene* scene, QObject* parent = nullptr);

    void addRemove(LevelData removedItems);
    void addPlace(LevelData placedItems);
    void addOverwrite(LevelData removedItems, LevelData placedItems);
    void addPlace(LevelDoor door, bool isEntrance);
    void addMove(LevelData sourceMovedItems, LevelData targetMovedItems);

    void addChangeSettings(LevelData modifiedItems, HistorySettings::LevelSettingSubType subType, QVariant extraData);
    void addResizeSection(int sectionID, long oldLeft, long oldTop, long oldRight, long oldBottom,
                                 long newLeft, long newTop, long newRight, long newBottom);

    void addResizeBlock(LevelBlock bl, long oldLeft, long oldTop, long oldRight, long oldBottom,
                               long newLeft, long newTop, long newRight, long newBottom);
    void addResizePhysEnv(LevelPhysEnv wt, long oldLeft, long oldTop, long oldRight, long oldBottom,
                               long newLeft, long newTop, long newRight, long newBottom);

    void addAddWarp(int array_id, int listindex, int doorindex);
    void addRemoveWarp(LevelDoor removedDoor);
    void addChangeWarpSettings(int array_id, HistorySettings::LevelSettingSubType subtype, QVariant extraData);

    void addChangedNewLayer(LevelData changedItems, LevelLayer newLayer);
    void addAddLayer(int array_id, QString name);
    void addRenameLayer(int array_id, QString oldName, QString newName);
    void addRemoveLayer(LevelData modData);
    void addChangedLayer(LevelData changedItems, QString newLayerName);

    void addAddEvent(LevelSMBX64Event ev);
    void addDuplicateEvent(LevelSMBX64Event newDuplicate);
    void addRemoveEvent(LevelSMBX64Event ev);
    void addRenameEvent(int array_id, QString oldName, QString newName);
    void addRemoveLayerAndSaveItems(LevelData modData);
    void addMergeLayer(LevelData mergedData, QString newLayerName);
    void addChangeEventSettings(int array_id, HistorySettings::LevelSettingSubType subtype, QVariant extraData);

    void addChangeSectionSettings(int sectionID, HistorySettings::LevelSettingSubType subtype, QVariant extraData);
    void addChangeLevelSettings(HistorySettings::LevelSettingSubType subtype, QVariant extraData);
    void addPlacePlayerPoint(PlayerPoint plr, QVariant oldPos);

    void addRotate(LevelData rotatedItems, LevelData unrotatedItems);
    void addFlip(LevelData flippedItems, LevelData unflippedItems);

    void addTransform(LevelData transformedItems, LevelData sourceItems);

public slots:
    //history modifiers
    void historyBack();
    void historyForward();
    void updateHistoryBuffer();
    //history information
    int  getHistroyIndex();
    bool canUndo();
    bool canRedo();

signals:
    void refreshHistoryButtons();
    void showStatusMessage(QString text, int delay=2000);
};


#endif // LVL_HISTORY_MANAGER_H
