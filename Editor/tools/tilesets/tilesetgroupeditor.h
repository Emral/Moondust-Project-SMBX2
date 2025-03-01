#pragma once
#ifndef TILESETGROUPEDITOR_H
#define TILESETGROUPEDITOR_H

#include <QDialog>
#include <QSharedPointer>

#include <common_features/flowlayout.h>
#include <data_configs/obj_tilesets.h>

#include "tileset.h"

namespace Ui {
class TilesetGroupEditor;
}

class DataConfig;
class QSettings;
class TilesetGroupEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TilesetGroupEditor(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~TilesetGroupEditor();

    SimpleTilesetGroup toSimpleTilesetGroup();
    static void SaveSimpleTilesetGroup(const QString &path, const SimpleTilesetGroup &tileset);
    static bool OpenSimpleTilesetGroup(const QString &path, SimpleTilesetGroup &tileset);

    static QString categoryName(QString catName);

private slots:
    void on_addTileset_clicked();
    void on_RemoveTileset_clicked();
    void on_Open_clicked();
    void on_Save_clicked();
    void on_tilesetUp_clicked();
    void on_tilesetDown_clicked();
    void on_category_currentIndexChanged(const QString &arg1);
    void on_category_editTextChanged(const QString &arg1);
    void on_categoryWeight_editingFinished();

    void movedTileset( const QModelIndex & sourceParent, int sourceStart, int sourceEnd, const QModelIndex & destinationParent, int destinationRow );

private:
    void fetchCategories(QString path);

    static QString lastFileName;
    FlowLayout *layout = nullptr;
    QSharedPointer<QSettings> m_categories;
    Ui::TilesetGroupEditor *ui = nullptr;
    void redrawAll();
    QGraphicsScene *scn = nullptr;
    QList<QPair<QString,SimpleTileset> > tilesets;
    DataConfig *m_configs = nullptr;
};

#endif // TILESETGROUPEDITOR_H
