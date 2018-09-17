#----------------------------------------------------------------------------
#
# Platformer Game Engine by Wohlstand, a free platform for game making
# Copyright (c) 2014-2016 Vitaly Novichkov <admin@wohlnet.ru>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#----------------------------------------------------------------------------
#
# Project created by QtCreator 2014-03-18T16:09:15
#
#----------------------------------------------------------------------------

QT       += gui widgets network concurrent qml
QT       -= opengl dbus svg testlib

win32: {
    QT += winextras
} else {
    QT -= winextras
}

include($$PWD/../_common/dest_dir.pri)
include($$PWD/../_common/build_props.pri)
include($$PWD/languages.pri)

DEFINES += PGE_EDITOR USE_SDL_MIXER

android:{
    themes.path = /assets/themes
    themes.files = $$PWD/../Content/themes/*
    INSTALLS += themes
    ANDROID_EXTRA_LIBS += \
        $$PWD/../_Libs/_builds/android/lib/libSDL2.so \
        $$PWD/../_Libs/_builds/android/lib/libSDL2_mixer_ext.so
}


!macx:  TARGET = pge_editor
macx:   TARGET = "PGE Editor"
TEMPLATE = app

CONFIG += c++14

CONFIG += static
CONFIG += thread

macx: QMAKE_CXXFLAGS += -Wno-header-guard
!macx: {
    QMAKE_LFLAGS += -Wl,-rpath=\'\$\$ORIGIN\'
    QMAKE_LFLAGS_RELEASE += -static-libgcc -static-libstdc++
}

include($$PWD/../_common/strip_garbage.pri)
include($$PWD/../_common/lib_destdir.pri)
include($$PWD/../_Libs/SDL_Mixer_X/SDL_Mixer_X_link.pri)

INCLUDEPATH += $$PWD/../_Libs/_builds/$$TARGETOS/include
LIBS += -L$$PWD/../_Libs/_builds/$$TARGETOS/lib

INCLUDEPATH += $$PWD/../_Libs/SDL2_mixer_modified
INCLUDEPATH += $$PWD $$PWD/_includes "$$PWD/../_Libs" "$$PWD/../_common"

win32: {
    RC_FILE = _resources/pge_editor.rc
    LIBS += -lSDL2 $$SDL_MIXER_X_LIBS_DYNAMIC
    LIBS += -lSDL2main
    LIBS += libversion -ldbghelp libwinmm
}

linux-g++||unix:!macx:!android: {
    LIBS += -lSDL2 $$SDL_MIXER_X_LIBS_DYNAMIC
    LIBS += -static-libgcc -static-libstdc++
}
android: {
    LIBS += -lSDL2 $$SDL_MIXER_X_LIBS_DYNAMIC
}
macx: {
    ICON = $$PWD/_resources/cat_builder.icns
    QMAKE_INFO_PLIST = $$PWD/_resources/pge_editor.plist
    DEFINES += DEFINE_Q_OS_MACX # Workaround for inability of MOC to see this macro
    APP_FILEICON_FILES.files = \
            $$PWD/_resources/file_lvl.icns \
            $$PWD/_resources/file_lvlx.icns \
            $$PWD/_resources/file_wld.icns \
            $$PWD/_resources/file_wldx.icns
    APP_FILEICON_FILES.path  = Contents/Resources
    QMAKE_BUNDLE_DATA += APP_FILEICON_FILES

    LIBS += -lSDL2 $$SDL_MIXER_X_LIBS_STATIC
    LIBS += -framework CoreAudio -framework CoreVideo \
            -framework AudioToolbox -framework AudioUnit \
            -framework IOKit -framework Cocoa -framework Carbon \
            -framework ForceFeedback -framework Metal -framework CoreFoundation
}

LIBS += -lfreeimagelite

# Common code
include($$PWD/../_common/ConfigPackManager/PGE_ConfigPackManager.pri)
include($$PWD/../_common/DirManager/dirman.pri)
include($$PWD/../_common/FileMapper/FileMapper.pri)
DEFINES += INI_PROCESSING_ALLOW_QT_TYPES
include($$PWD/../_common/IniProcessor/IniProcessor.pri)
include($$PWD/../_common/PGE_File_Formats/File_FormatsQT.pri)
include($$PWD/../_common/Utf8Main/utf8main.pri)
include($$PWD/../_common/Utils/Utils.pri)
include($$PWD/../_Libs/QtPropertyBrowser.pri)

win32: include($$PWD/main_window/testing/luna_tester.pri)
win32: include($$PWD/../_common/StackWalker/StackWalker.pri)

SOURCES += \
    audio/music_player.cpp \
    audio/sdl_music_player.cpp \
    ../_common/data_functions/smbx64_validation_messages.cpp \
    common_features/animation_timer.cpp \
    common_features/app_path.cpp \
    common_features/bool_reseter.cpp \
    common_features/crashhandler.cpp \
    common_features/dir_copy.cpp \
    common_features/edit_mode_base.cpp \
    common_features/flowlayout.cpp \
    common_features/graphics_funcs.cpp \
    common_features/graphicsworkspace.cpp \
    common_features/grid.cpp \
    common_features/installer.cpp \
    common_features/item_rectangles.cpp \
    common_features/items.cpp \
    common_features/logger_sets.cpp \
    common_features/main_window_ptr.cpp \
    common_features/npc_animator.cpp \
    common_features/proxystyle.cpp \
    common_features/resizer/corner_grabber.cpp \
    common_features/resizer/item_resizer.cpp \
    common_features/safe_msg_box.cpp \
    common_features/simple_animator.cpp \
    common_features/spash_screen.cpp \
    common_features/themes.cpp \
    common_features/timecounter.cpp \
    common_features/util.cpp \
    common_features/version_cmp.cpp \
    data_configs/config_status/config_status.cpp \
    data_configs/conf_music.cpp \
    data_configs/conf_rotation_tables.cpp \
    data_configs/conf_sound.cpp \
    data_configs/conf_wld_level.cpp \
    data_configs/conf_wld_path.cpp \
    data_configs/conf_wld_scene.cpp \
    data_configs/conf_wld_tile.cpp \
    data_configs/custom_data.cpp \
    data_configs/data_configs.cpp \
    data_configs/obj_BG.cpp \
    data_configs/obj_bgo.cpp \
    data_configs/obj_block.cpp \
    data_configs/obj_npc.cpp \
    data_configs/obj_player.cpp \
    data_configs/obj_tilesets.cpp \
    data_configs/selection_dialog/config_manager.cpp \
    dev_console/devconsole.cpp \
    editing/_components/history/historyelementaddlayer.cpp \
    editing/_components/history/historyelementaddwarp.cpp \
    editing/_components/history/historyelementchangednewlayer.cpp \
    editing/_components/history/historyelementitemsetting.cpp \
    editing/_components/history/historyelementlayerchanged.cpp \
    editing/_components/history/historyelementmainsetting.cpp \
    editing/_components/history/historyelementmergelayer.cpp \
    editing/_components/history/historyelementmodification.cpp \
    editing/_components/history/historyelementmodifyevent.cpp \
    editing/_components/history/historyelementnewlayer.cpp \
    editing/_components/history/historyelementplacedoor.cpp \
    editing/_components/history/historyelementremovelayerandsave.cpp \
    editing/_components/history/historyelementremovelayer.cpp \
    editing/_components/history/historyelementremovewarp.cpp \
    editing/_components/history/historyelementrenameevent.cpp \
    editing/_components/history/historyelementrenamelayer.cpp \
    editing/_components/history/historyelementreplaceplayerpoint.cpp \
    editing/_components/history/historyelementresizeblock.cpp \
    editing/_components/history/historyelementresizesection.cpp \
    editing/_components/history/historyelementresizewater.cpp \
    editing/_components/history/historyelementsettingsevent.cpp \
    editing/_components/history/historyelementsettingssection.cpp \
    editing/_components/history/historyelementsettingswarp.cpp \
    editing/_components/history/ihistoryelement.cpp \
    editing/_components/history/itemsearcher.cpp \
    editing/_dialogs/itemselectdialog.cpp \
    editing/_dialogs/levelfilelist.cpp \
    editing/_dialogs/musicfilelist.cpp \
    editing/_dialogs/savingnotificationdialog.cpp \
    editing/_dialogs/user_data_edit.cpp \
    editing/_dialogs/wld_setpoint.cpp \
    editing/edit_level/level_edit.cpp \
    editing/edit_level/levelprops.cpp \
    editing/edit_level/lvl_clone_section.cpp \
    editing/edit_level/lvl_draw.cpp \
    editing/edit_level/lvl_edit_control.cpp \
    editing/edit_level/lvl_files_io.cpp \
    editing/edit_npc/npc_data_sets.cpp \
    editing/edit_npc/npcedit.cpp \
    editing/edit_npc/npceditscene.cpp \
    editing/edit_npc/npctxt_controls.cpp \
    editing/edit_npc/npctxt_files_io.cpp \
    editing/edit_world/wld_draw.cpp \
    editing/edit_world/wld_edit_control.cpp \
    editing/edit_world/wld_files_io.cpp \
    editing/edit_world/world_edit.cpp \
    editing/_scenes/level/data_manager/lvl_animators.cpp \
    editing/_scenes/level/data_manager/lvl_custom_gfx.cpp \
    editing/_scenes/level/edit_modes/mode_circle.cpp \
    editing/_scenes/level/edit_modes/mode_erase.cpp \
    editing/_scenes/level/edit_modes/mode_fill.cpp \
    editing/_scenes/level/edit_modes/mode_hand.cpp \
    editing/_scenes/level/edit_modes/mode_line.cpp \
    editing/_scenes/level/edit_modes/mode_place.cpp \
    editing/_scenes/level/edit_modes/mode_resize.cpp \
    editing/_scenes/level/edit_modes/mode_select.cpp \
    editing/_scenes/level/edit_modes/mode_square.cpp \
    editing/_scenes/level/itemmsgbox.cpp \
    editing/_scenes/level/items/item_bgo.cpp \
    editing/_scenes/level/items/item_block.cpp \
    editing/_scenes/level/items/item_door.cpp \
    editing/_scenes/level/items/item_npc.cpp \
    editing/_scenes/level/items/item_playerpoint.cpp \
    editing/_scenes/level/items/item_water.cpp \
    editing/_scenes/level/items/lvl_base_item.cpp \
    editing/_scenes/level/items/lvl_items_aligning.cpp \
    editing/_scenes/level/items/lvl_items_modify.cpp \
    editing/_scenes/level/items/lvl_items_place.cpp \
    editing/_scenes/level/lvl_clipboard.cpp \
    editing/_scenes/level/lvl_collisions.cpp \
    editing/_scenes/level/lvl_control.cpp \
    editing/_scenes/level/lvl_history_manager.cpp \
    editing/_scenes/level/lvl_init_filedata.cpp \
    editing/_scenes/level/lvl_item_placing.cpp \
    editing/_scenes/level/lvl_scene.cpp \
    editing/_scenes/level/lvl_section.cpp \
    editing/_scenes/level/lvl_setup.cpp \
    editing/_scenes/level/newlayerbox.cpp \
    editing/_scenes/level/resizers/lvl_resizer_block.cpp \
    editing/_scenes/level/resizers/lvl_resizer_img_shoot.cpp \
    editing/_scenes/level/resizers/lvl_resizer_physenv.cpp \
    editing/_scenes/level/resizers/lvl_resizers.cpp \
    editing/_scenes/level/resizers/lvl_resizer_section.cpp \
    editing/_scenes/level/resizers/lvl_resizer_section_evnt.cpp \
    editing/_scenes/world/data_manager/wld_animators.cpp \
    editing/_scenes/world/data_manager/wld_custom_gfx.cpp \
    editing/_scenes/world/edit_modes/wld_mode_circle.cpp \
    editing/_scenes/world/edit_modes/wld_mode_erase.cpp \
    editing/_scenes/world/edit_modes/wld_mode_fill.cpp \
    editing/_scenes/world/edit_modes/wld_mode_hand.cpp \
    editing/_scenes/world/edit_modes/wld_mode_line.cpp \
    editing/_scenes/world/edit_modes/wld_mode_place.cpp \
    editing/_scenes/world/edit_modes/wld_mode_resize.cpp \
    editing/_scenes/world/edit_modes/wld_mode_select.cpp \
    editing/_scenes/world/edit_modes/wld_mode_setpoint.cpp \
    editing/_scenes/world/edit_modes/wld_mode_square.cpp \
    editing/_scenes/world/items/item_level.cpp \
    editing/_scenes/world/items/item_music.cpp \
    editing/_scenes/world/items/item_path.cpp \
    editing/_scenes/world/items/item_point.cpp \
    editing/_scenes/world/items/item_scene.cpp \
    editing/_scenes/world/items/item_tile.cpp \
    editing/_scenes/world/items/wld_base_item.cpp \
    editing/_scenes/world/items/wld_items_aligning.cpp \
    editing/_scenes/world/items/wld_items_modify.cpp \
    editing/_scenes/world/items/wld_items_place.cpp \
    editing/_scenes/world/resizers/wld_resizer_img_shoot.cpp \
    editing/_scenes/world/resizers/wld_resizers.cpp \
    editing/_scenes/world/wld_clipboard.cpp \
    editing/_scenes/world/wld_collisions.cpp \
    editing/_scenes/world/wld_control.cpp \
    editing/_scenes/world/wld_history_manager.cpp \
    editing/_scenes/world/wld_init_filedata.cpp \
    editing/_scenes/world/wld_item_placing.cpp \
    editing/_scenes/world/wld_point_selector.cpp \
    editing/_scenes/world/wld_scene.cpp \
    editing/_scenes/world/wld_setup.cpp \
    js_engine/pge_jsengine.cpp \
    js_engine/proxies/js_common.cpp \
    js_engine/proxies/js_file.cpp \
    js_engine/proxies/js_ini.cpp \
    js_engine/proxies/js_lua_preproc.cpp \
    main.cpp\
    main_window/about_dialog/aboutdialog.cpp \
    mainwindow.cpp \
    main_window/dock/bookmarks_box.cpp \
    main_window/dock/debugger.cpp \
    main_window/dock/_dock_vizman.cpp \
    main_window/dock/itembox_list_model.cpp \
    main_window/dock/lvl_events_box.cpp \
    main_window/dock/lvl_item_properties.cpp \
    main_window/dock/lvl_item_toolbox.cpp \
    main_window/dock/lvl_layers_box.cpp \
    main_window/dock/lvl_sctc_props.cpp \
    main_window/dock/lvl_search_box.cpp \
    main_window/dock/lvl_warp_props.cpp \
    main_window/dock/mwdock_base.cpp \
    main_window/dock/tileset_item_box.cpp \
    main_window/dock/variables_box.cpp \
    main_window/dock/wld_item_props.cpp \
    main_window/dock/wld_item_toolbox.cpp \
    main_window/dock/wld_search_box.cpp \
    main_window/dock/wld_settings_box.cpp \
    main_window/edit/edit_clipboard.cpp \
    main_window/edit/edit_history.cpp \
    main_window/edit/edit_items.cpp \
    main_window/edit/edit_mode.cpp \
    main_window/edit/edit_mode_placing.cpp \
    main_window/edit/edit_placing_switch.cpp \
    main_window/edit/edit_resize.cpp \
    main_window/events.cpp \
    main_window/file/file_export_image.cpp \
    main_window/file/file_new.cpp \
    main_window/file/file_open.cpp \
    main_window/file/file_recent.cpp \
    main_window/file/file_reload.cpp \
    main_window/file/file_save.cpp \
    main_window/file/lvl_export_image.cpp \
    main_window/file/wld_export_image.cpp \
    main_window/global_settings.cpp \
    main_window/greeting_dialog/greeting_dialog.cpp \
    main_window/help.cpp \
    main_window/level/level_locks.cpp \
    main_window/level/level_props.cpp \
    main_window/level/level_sections.cpp \
    main_window/level/level_sections_mods.cpp \
    main_window/mainw_plugins.cpp \
    main_window/mainw_themes.cpp \
    main_window/menubar.cpp \
    main_window/plugins/pge_editorplugininfo.cpp \
    main_window/plugins/pge_editorpluginitem.cpp \
    main_window/plugins/pge_editorpluginmanager.cpp \
    main_window/script/script_editor.cpp \
    main_window/script/script_luafiles.cpp \
    main_window/_settings/defaults.cpp \
    main_window/_settings/settings_io.cpp \
    main_window/sub_windows.cpp \
    main_window/testing/testing.cpp \
    main_window/testing/testing_settings.cpp \
    main_window/tip_of_day/tip_of_day.cpp \
    main_window/tools/app_settings.cpp \
    main_window/tools/data_configs_mgr.cpp \
    main_window/tools/main_clean_npc_gargage.cpp \
    main_window/tools/main_tool_cdata_cleaner.cpp \
    main_window/tools/main_tool_cdata_import.cpp \
    main_window/tools/main_tool_cdata_lazyfix.cpp \
    main_window/tools_menu.cpp \
    main_window/translator.cpp \
    main_window/updater/check_updates.cpp \
    main_window/view/view.cpp \
    main_window/view/view_zoom.cpp \
    main_window/windows_extras.cpp \
    main_window/world/world_locks.cpp \
    networking/engine_intproc.cpp \
    SingleApplication/editor_application.cpp \
    SingleApplication/localserver.cpp \
    SingleApplication/singleapplication.cpp \
    tools/async/asyncstarcounter.cpp \
    tools/debugger/custom_counter.cpp \
    tools/debugger/custom_counter_gui.cpp \
    tools/external_tools/audiocvt_sox_gui.cpp \
    tools/external_tools/gifs2png_gui.cpp \
    tools/external_tools/lazyfixtool_gui.cpp \
    tools/external_tools/png2gifs_gui.cpp \
    tools/math/blocksperseconddialog.cpp \
    tools/smart_import/smartimporter.cpp \
    tools/tilesets/piecesmodel.cpp \
    tools/tilesets/tileset_editor.cpp \
    tools/tilesets/tileset.cpp \
    tools/tilesets/tilesetgroupeditor.cpp \
    tools/tilesets/tilesetitembutton.cpp

HEADERS  += \
    audio/music_player.h \
    audio/sdl_music_player.h \
    ../_common/data_functions/smbx64_validation_messages.h \
    common_features/animation_timer.h \
    common_features/app_path.h \
    common_features/bool_reseter.h \
    common_features/crashhandler.h \
    common_features/data_array.h \
    common_features/dir_copy.h \
    common_features/edit_mode_base.h \
    common_features/flowlayout.h \
    common_features/graphics_funcs.h \
    common_features/graphicsworkspace.h \
    common_features/grid.h \
    common_features/installer.h \
    common_features/item_rectangles.h \
    common_features/items.h \
    common_features/logger.h \
    common_features/logger_sets.h \
    common_features/main_window_ptr.h \
    common_features/npc_animator.h \
    common_features/number_limiter.h \
    common_features/proxystyle.h \
    common_features/resizer/corner_grabber.h \
    common_features/resizer/item_resizer.h \
    common_features/RTree.h \
    common_features/safe_msg_box.h \
    common_features/simple_animator.h \
    common_features/spash_screen.h \
    common_features/themes.h \
    common_features/timecounter.h \
    common_features/util.h \
    common_features/version_cmp.h \
    data_configs/config_status/config_status.h \
    data_configs/custom_data.h \
    data_configs/data_configs.h \
    data_configs/obj_BG.h \
    data_configs/obj_bgo.h \
    data_configs/obj_block.h \
    data_configs/obj_npc.h \
    data_configs/obj_player.h \
    data_configs/obj_rotation_table.h \
    data_configs/obj_tilesets.h \
    data_configs/obj_wld_items.h \
    data_configs/selection_dialog/config_manager.h \
    defines.h \
    dev_console/devconsole.h \
    editing/_components/history/historyelementaddlayer.h \
    editing/_components/history/historyelementaddwarp.h \
    editing/_components/history/historyelementchangednewlayer.h \
    editing/_components/history/historyelementitemsetting.h \
    editing/_components/history/historyelementlayerchanged.h \
    editing/_components/history/historyelementmainsetting.h \
    editing/_components/history/historyelementmergelayer.h \
    editing/_components/history/historyelementmodification.h \
    editing/_components/history/historyelementmodifyevent.h \
    editing/_components/history/historyelementnewlayer.h \
    editing/_components/history/historyelementplacedoor.h \
    editing/_components/history/historyelementremovelayerandsave.h \
    editing/_components/history/historyelementremovelayer.h \
    editing/_components/history/historyelementremovewarp.h \
    editing/_components/history/historyelementrenameevent.h \
    editing/_components/history/historyelementrenamelayer.h \
    editing/_components/history/historyelementreplaceplayerpoint.h \
    editing/_components/history/historyelementresizeblock.h \
    editing/_components/history/historyelementresizesection.h \
    editing/_components/history/historyelementresizewater.h \
    editing/_components/history/historyelementsettingsevent.h \
    editing/_components/history/historyelementsettingssection.h \
    editing/_components/history/historyelementsettingswarp.h \
    editing/_components/history/history_manager.h \
    editing/_components/history/ihistoryelement.h \
    editing/_components/history/itemsearcher.h \
    editing/_dialogs/itemselectdialog.h \
    editing/_dialogs/levelfilelist.h \
    editing/_dialogs/musicfilelist.h \
    editing/_dialogs/savingnotificationdialog.h \
    editing/_dialogs/user_data_edit.h \
    editing/_dialogs/wld_setpoint.h \
    editing/edit_level/level_edit.h \
    editing/edit_level/levelprops.h \
    editing/edit_level/lvl_clone_section.h \
    editing/edit_npc/npcedit.h \
    editing/edit_npc/npceditscene.h \
    editing/edit_world/world_edit.h \
    editing/_scenes/level/edit_modes/mode_circle.h \
    editing/_scenes/level/edit_modes/mode_erase.h \
    editing/_scenes/level/edit_modes/mode_fill.h \
    editing/_scenes/level/edit_modes/mode_hand.h \
    editing/_scenes/level/edit_modes/mode_line.h \
    editing/_scenes/level/edit_modes/mode_place.h \
    editing/_scenes/level/edit_modes/mode_resize.h \
    editing/_scenes/level/edit_modes/mode_select.h \
    editing/_scenes/level/edit_modes/mode_square.h \
    editing/_scenes/level/itemmsgbox.h \
    editing/_scenes/level/items/item_bgo.h \
    editing/_scenes/level/items/item_block.h \
    editing/_scenes/level/items/item_door.h \
    editing/_scenes/level/items/item_npc.h \
    editing/_scenes/level/items/item_playerpoint.h \
    editing/_scenes/level/items/item_water.h \
    editing/_scenes/level/items/lvl_base_item.h \
    editing/_scenes/level/lvl_history_manager.h \
    editing/_scenes/level/lvl_item_placing.h \
    editing/_scenes/level/lvl_scene.h \
    editing/_scenes/level/newlayerbox.h \
    editing/_scenes/world/edit_modes/wld_mode_circle.h \
    editing/_scenes/world/edit_modes/wld_mode_erase.h \
    editing/_scenes/world/edit_modes/wld_mode_fill.h \
    editing/_scenes/world/edit_modes/wld_mode_hand.h \
    editing/_scenes/world/edit_modes/wld_mode_line.h \
    editing/_scenes/world/edit_modes/wld_mode_place.h \
    editing/_scenes/world/edit_modes/wld_mode_resize.h \
    editing/_scenes/world/edit_modes/wld_mode_select.h \
    editing/_scenes/world/edit_modes/wld_mode_setpoint.h \
    editing/_scenes/world/edit_modes/wld_mode_square.h \
    editing/_scenes/world/items/item_level.h \
    editing/_scenes/world/items/item_music.h \
    editing/_scenes/world/items/item_path.h \
    editing/_scenes/world/items/item_point.h \
    editing/_scenes/world/items/item_scene.h \
    editing/_scenes/world/items/item_tile.h \
    editing/_scenes/world/items/wld_base_item.h \
    editing/_scenes/world/wld_history_manager.h \
    editing/_scenes/world/wld_item_placing.h \
    editing/_scenes/world/wld_point_selector.h \
    editing/_scenes/world/wld_scene.h \
    js_engine/pge_jsengine.h \
    js_engine/proxies/js_common.h \
    js_engine/proxies/js_file.h \
    js_engine/proxies/js_ini.h \
    js_engine/proxies/js_lua_preproc.h \
    js_engine/proxies/js_utils.h \
    main_window/about_dialog/aboutdialog.h \
    main_window/dock/bookmarks_box.h \
    main_window/dock/debugger.h \
    main_window/dock/_dock_vizman.h \
    main_window/dock/itembox_list_model.h \
    main_window/dock/lvl_events_box.h \
    main_window/dock/lvl_item_properties.h \
    main_window/dock/lvl_item_toolbox.h \
    main_window/dock/lvl_layers_box.h \
    main_window/dock/lvl_sctc_props.h \
    main_window/dock/lvl_search_box.h \
    main_window/dock/lvl_warp_props.h \
    main_window/dock/mwdock_base.h \
    main_window/dock/tileset_item_box.h \
    main_window/dock/toolboxes.h \
    main_window/dock/toolboxes_protos.h \
    main_window/dock/variables_box.h \
    main_window/dock/wld_item_props.h \
    main_window/dock/wld_item_toolbox.h \
    main_window/dock/wld_search_box.h \
    main_window/dock/wld_settings_box.h \
    main_window/file/lvl_export_image.h \
    main_window/file/wld_export_image.h \
    main_window/global_settings.h \
    main_window/greeting_dialog/greeting_dialog.h \
    mainwindow.h \
    main_window/plugins/pge_editorplugininfo.h \
    main_window/plugins/pge_editorpluginitem.h \
    main_window/plugins/pge_editorpluginmanager.h \
    main_window/script/script_editor.h \
    main_window/testing/testing_settings.h \
    main_window/tip_of_day/tip_of_day.h \
    main_window/tools/app_settings.h \
    main_window/updater/check_updates.h \
    main_window/updater/updater_links.h \
    networking/engine_intproc.h \
    SingleApplication/editor_application.h \
    SingleApplication/localserver.h \
    SingleApplication/semaphore_winapi.h \
    SingleApplication/singleapplication.h \
    tools/async/asyncstarcounter.h \
    tools/debugger/custom_counter_gui.h \
    tools/debugger/custom_counter.h \
    tools/external_tools/audiocvt_sox_gui.h \
    tools/external_tools/gifs2png_gui.h \
    tools/external_tools/lazyfixtool_gui.h \
    tools/external_tools/png2gifs_gui.h \
    tools/math/blocksperseconddialog.h \
    tools/smart_import/smartimporter.h \
    tools/tilesets/piecesmodel.h \
    tools/tilesets/tileset_editor.h \
    tools/tilesets/tilesetgroupeditor.h \
    tools/tilesets/tileset.h \
    tools/tilesets/tilesetitembutton.h \
    version.h \
    main_window/dock/item_tooltip_make.hpp

FORMS    += \
    common_features/crashhandler.ui \
    data_configs/config_status/config_status.ui \
    data_configs/selection_dialog/config_manager.ui \
    dev_console/devconsole.ui \
    editing/_dialogs/itemselectdialog.ui \
    editing/_dialogs/levelfilelist.ui \
    editing/_dialogs/musicfilelist.ui \
    editing/_dialogs/savingnotificationdialog.ui \
    editing/_dialogs/user_data_edit.ui \
    editing/_dialogs/wld_setpoint.ui \
    editing/edit_level/leveledit.ui \
    editing/edit_level/levelprops.ui \
    editing/edit_level/lvl_clone_section.ui \
    editing/edit_npc/npcedit.ui \
    editing/edit_world/world_edit.ui \
    editing/_scenes/level/itemmsgbox.ui \
    editing/_scenes/level/tonewlayerbox.ui \
    main_window/about_dialog/aboutdialog.ui \
    main_window/dock/bookmarks_box.ui \
    main_window/dock/debugger.ui \
    main_window/dock/lvl_events_box.ui \
    main_window/dock/lvl_item_properties.ui \
    main_window/dock/lvl_item_toolbox.ui \
    main_window/dock/lvl_layers_box.ui \
    main_window/dock/lvl_sctc_props.ui \
    main_window/dock/lvl_search_box.ui \
    main_window/dock/lvl_warp_props.ui \
    main_window/dock/tileset_item_box.ui \
    main_window/dock/variables_box.ui \
    main_window/dock/wld_item_props.ui \
    main_window/dock/wld_item_toolbox.ui \
    main_window/dock/wld_search_box.ui \
    main_window/dock/wld_settings_box.ui \
    main_window/file/lvl_export_image.ui \
    main_window/file/wld_export_image.ui \
    main_window/greeting_dialog/greeting_dialog.ui \
    main_window/plugins/pge_editorplugininfo.ui \
    main_window/script/script_editor.ui \
    main_window/testing/testing_settings.ui \
    main_window/tip_of_day/tip_of_day.ui \
    main_window/tools/app_settings.ui \
    mainwindow.ui \
    main_window/updater/check_updates.ui \
    tools/debugger/custom_counter_gui.ui \
    tools/external_tools/audiocvt_sox_gui.ui \
    tools/external_tools/gifs2png_gui.ui \
    tools/external_tools/lazyfixtool_gui.ui \
    tools/external_tools/png2gifs_gui.ui \
    tools/math/blocksperseconddialog.ui \
    tools/tilesets/tileset_editor.ui \
    tools/tilesets/tilesetgroupeditor.ui

RESOURCES += \
    _resources/editor.qrc

OTHER_FILES += \
    images/01.png \
    images/02.png \
    images/03.png \
    images/04.png \
    images/05.png \
    images/06.png \
    images/07.png \
    images/08.png \
    images/09.png \
    images/10.png \
    images/11.png \
    images/12.png \
    images/13.png \
    images/14.png \
    images/15.png \
    images/16.png \
    images/17.png \
    images/18.png \
    images/19.png \
    images/20.png \
    images/21.png \
    images/arrow.png \
    images/coin.png \
    images/cur_pasta.png \
    images/cur_rubber.png \
    images/doors.png \
    images/draw_sand.png \
    images/draw_water.png \
    images/edit_copy.png \
    images/edit_cut.png \
    images/edit_paste.png \
    images/edit_redo.png \
    images/edit_undo.png \
    images/generator_proj.png \
    images/generator_warp.png \
    images/grid.png \
    images/hand.png \
    images/layers.png \
    images/level16.png \
    images/level.png \
    images/lock_bgo_cl.png \
    images/lock_bgo_op.png \
    images/lock_block_cl.png \
    images/lock_block_op.png \
    images/lock_door_cl.png \
    images/lock_door_op.png \
    images/lock_npc_cl.png \
    images/lock_npc_op.png \
    images/lock_water_cl.png \
    images/lock_water_op.png \
    images/mac/mushroom.hqx \
    images/mac/mushroom.icns \
    images/mushroom16.png \
    images/mushroom.png \
    images/new.png \
    images/open.png \
    images/player1_point.png \
    images/player1_start.png \
    images/player2_point.png \
    images/player2_start.png \
    images/playmusic.png \
    images/reload_data.png \
    images/reset_pos.png \
    images/rubber.png \
    images/saveas.png \
    images/save.png \
    images/section16.png \
    images/section.png \
    images/select_only.png \
    images/splash.png \
    images/warp_entrance.png \
    images/warp_exit.png \
    images/world16.png \
    images/world.png \
    _resources/mushroom.icns \
    _resources/mushroom.ico \
    _resources/pge_editor.rc \
    _resources/splash.png

DISTFILES += \
    ../changelog.editor.txt

