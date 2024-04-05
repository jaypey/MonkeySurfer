TEMPLATE     = vcapp
TARGET       = monkeysurfergui
CONFIG      += warn_on qt debug windows console
HEADERS     += \
			jeuWorker.h
SOURCES     += \
			MonkeySurferGUI.cpp \
			jeuWorker.cpp
INCLUDEPATH += . ../MonkeySurfer/
LIBS        += 
QT          += widgets