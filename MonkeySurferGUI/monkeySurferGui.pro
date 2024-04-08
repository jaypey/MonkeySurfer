TEMPLATE     = vcapp
TARGET       = monkeysurfergui
CONFIG      += warn_on qt debug windows console
HEADERS     += \
			affichagegui.h \
			pausemenugui.h \
			mainwindow.h \
			../MonkeySurfer/affichage.h \
			../MonkeySurfer/aleatoire.h \
			../MonkeySurfer/banane.h \
			../MonkeySurfer/bouclier.h \
			../MonkeySurfer/collectible.h \
			../MonkeySurfer/direction.h \
			../MonkeySurfer/elementaleatoire.h \
			../MonkeySurfer/elementjeu.h \
			../MonkeySurfer/harpieferoce.h \
			../MonkeySurfer/jeu.h \
			../MonkeySurfer/joueur.h \
			../MonkeySurfer/jsonSerial.h \
			../MonkeySurfer/menu.h \
			../MonkeySurfer/networking.h \
			../MonkeySurfer/nullstream.h \
			../MonkeySurfer/obstacle.h \
			../MonkeySurfer/obstaclefixe.h \
			../MonkeySurfer/piece.h \
			../MonkeySurfer/playerdata.h \
			../MonkeySurfer/projectile.h \
			../MonkeySurfer/serpent.h \
			../MonkeySurfer/skin.h
SOURCES     += \
			MonkeySurferGUI.cpp \
			affichagegui.cpp \
			pausemenugui.cpp \
			mainwindow.cpp \
			../MonkeySurfer/affichage.cpp \
			../MonkeySurfer/aleatoire.cpp \
			../MonkeySurfer/banane.cpp \
			../MonkeySurfer/bouclier.cpp \
			../MonkeySurfer/collectible.cpp \
			../MonkeySurfer/elementaleatoire.cpp \
			../MonkeySurfer/elementjeu.cpp \
			../MonkeySurfer/harpieferoce.cpp \
			../MonkeySurfer/jeu.cpp \
			../MonkeySurfer/joueur.cpp \
			../MonkeySurfer/jsonSerial.cpp \
			../MonkeySurfer/menu.cpp \
			../MonkeySurfer/networking.cpp \
			../MonkeySurfer/nullstream.cpp \
			../MonkeySurfer/obstacle.cpp \
			../MonkeySurfer/obstaclefixe.cpp \
			../MonkeySurfer/piece.cpp \
			../MonkeySurfer/playerdata.cpp \
			../MonkeySurfer/projectile.cpp \
			../MonkeySurfer/serpent.cpp \
			../MonkeySurfer/skin.cpp
INCLUDEPATH += \
			../MonkeySurfer/ \
			../MonkeySurfer/lib
LIBS        += -L../MonkeySurfer/lib enet64.lib winmm.lib
DEFINES     += USE_QT
QT          += widgets