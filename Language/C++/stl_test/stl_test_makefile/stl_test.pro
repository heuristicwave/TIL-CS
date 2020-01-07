TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -ldl
SOURCES += \
	stl_test.cpp \
	gmemfunc.cpp \
	gmemhook.cpp \
	gmemmgr.cpp

