TEMPLATE = app
QT = core gui websockets
win32{
	LIBS += -lws2_32 -lcurldll -lidn
	TARGET = OpenBlox
}else{
	LIBS += -lcurl -lboost_system
	TARGET = openblox
}
LIBS += -lopenal -lalut -lcrypto -lssl -lz -lSDL2 -lSDL2_image -lOgreMain -llua

RESOURCES += internalrc.qrc

#SDL2 RenderSystem

!win32{
	LIBS += -lGL -lGLU
}

HEADERS = src/SDL2Plugin/*.h src/SDL2Plugin/SDL/*.h src/SDL2Plugin/GL/*.h src/SDL2Plugin/atifs/include/*.h src/SDL2Plugin/GLSL/include/*.h src/SDL2Plugin/StateCacheManager/*.h
SOURCES = src/SDL2Plugin/*.cpp src/SDL2Plugin/SDL/*.cpp src/SDL2Plugin/atifs/src/*.cpp src/SDL2Plugin/GLSL/src/*.cpp src/SDL2Plugin/StateCacheManager/*.cpp

HEADERS += engine/raknet/*.h engine/src/ob_lua/*.h engine/src/openblox/*.h engine/src/openblox/instance/*.h engine/src/openblox/type/*.h engine/src/openblox/enum/*.h #src/openblox/*.h 
SOURCES += engine/raknet/*.cpp engine/src/ob_lua/*.cpp engine/src/openblox/*.cpp engine/src/openblox/instance/*.cpp engine/src/openblox/type/*.cpp src/openblox/*.cpp engine/src/openblox/enum/*.cpp
CONFIG += c++11
DEFINES += GXX_EXPERIMENTAL_CXX0X
INCLUDEPATH += engine engine/src/ob_lua engine/src/openblox engine/src/openblox/instance src/openblox
