# -------------------------------------------------
# Project created by QtCreator 2009-10-21T20:18:13
# -------------------------------------------------
TARGET = TrollEditor
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    document_tabs.cpp \
    document_scene.cpp \
    block.cpp \
    hide_block_button.cpp \
    analyzer.cpp \
    tree_element.cpp \ # helpbrowser.cpp \
# settingsdialog.cpp \
# settingspages.cpp \ # \
    paired_tree_element.cpp

# language_manager.cpp
HEADERS += mainwindow.h \
    document_tabs.h \
    document_scene.h \
    block.h \
    hide_block_button.h \
    analyzer.h \
    tree_element.h \ # helpbrowser.h \
# settingsdialog.h \
# settingspages.h \
    paired_tree_element.h

# language_manager.h
RESOURCES += resources.qrc
INCLUDEPATH += "lua\include"
LIBS += "lua\lua5.1.dll"