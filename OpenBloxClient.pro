QT = core gui websockets
win32{
	LIBS += -lws2_32 -lcurldll -lidn
	TARGET = OpenBlox
}else{
	LIBS += -lcurl -lboost_system
	TARGET = openblox
}
LIBS += -lopenal -lalut -lcrypto -lssl -lz -lOgreMain -llua

RESOURCES += internalrc.qrc

HEADERS += engine/raknet/*.h engine/src/ob_lua/*.h engine/src/openblox/*.h engine/src/openblox/instance/*.h src/openblox/*.h
SOURCES += engine/raknet/*.cpp engine/src/ob_lua/*.cpp engine/src/openblox/*.cpp engine/src/openblox/instance/*.cpp src/openblox/*.cpp
CONFIG += c++11
DEFINES += GXX_EXPERIMENTAL_CXX0X
INCLUDEPATH += engine/src/ob_lua engine/src/openblox engine/src/openblox/instance src/openblox
