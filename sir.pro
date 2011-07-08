TEMPLATE = app
LANGUAGE = C++
RESOURCES += application.qrc
QT += network

UI_DIR += .ui
MOC_DIR += .moc
OBJECTS_DIR += .obj

CONFIG += qt \
    release debug \
    warn_on
INCLUDEPATH += src/
LIBS += -lexiv2
SOURCES += src/main.cpp \
    src/convertdialog.cpp \
    src/previewdialog.cpp \
    src/optionsdialog.cpp \
    src/myqtreewidget.cpp \
    src/convertthread.cpp \
    src/aboutdialog.cpp \
    src/languageutils.cpp \
    src/sharedinformation.cpp \
    src/rawutils.cpp \
    src/networkutils.cpp \
    src/messagebox.cpp \
    src/metadatautils.cpp
FORMS += dialogs/convertdialog.ui \
    dialogs/about.ui \
    dialogs/optionsdialog.ui \
    dialogs/previewdialog.ui
HEADERS += src/main.h \
    src/convertdialog.h \
    src/previewdialog.h \
    src/optionsdialog.h \
    src/myqtreewidget.h \
    src/convertthread.h \
    src/aboutdialog.h \
    src/defines.h \
    src/languageutils.h \
    src/sharedinformation.h \
    src/rawutils.h \
    src/networkutils.h \
    src/messagebox.h \
    src/metadatautils.h
TRANSLATIONS += translations/sir_pt_BR.ts \
    translations/sir_de.ts \
    translations/sir_es.ts \
    translations/sir_sk.ts \
    translations/sir_ru_RU.ts \
    translations/sir_hu_HU.ts \
    translations/sir_pl.ts \
    translations/sir_nl.ts \
    translations/sir_ro_RO.ts \
    translations/sir_fr.ts \
    translations/sir_gr.ts \
    translations/sir_cz.ts
unix { 
    target.path += /usr/bin
    images.path = /usr/share/pixmaps
    images.files = images/sir*
    service.path = /usr/share/kde4/services/ServiceMenus
    service.files = sir_service.desktop
    desktop.path = /usr/share/applications
    desktop.files = sir.desktop
    INSTALLS += target
    INSTALLS += images
    INSTALLS += desktop
    INSTALLS += service
}
win32 { 
RC_FILE = windows/res.rc
}
