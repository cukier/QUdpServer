QT = core network

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        models/addressmodel.cpp \
        models/endpointmodel.cpp \
        models/mappedaddressmodel.cpp \
        models/stunattributemodel.cpp \
        models/stunheadermodel.cpp \
        main.cpp \
        stunclient.cpp \
        qudpserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    models/addressmodel.h \
    models/endpointmodel.h \
    models/mappedaddressmodel.h \
    models/stunattributemodel.h \
    models/stunheadermodel.h \
    stunclient.h \
    qudpserver.h
