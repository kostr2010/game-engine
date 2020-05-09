
CC = g++

CFLAGS = -Wall -std=c++17 -g 

MAIN_TEST     = main.test.o
MAIN          = main.o
COMPONENT     = component/component.o
ENTITY        = entity/entity.o
SYSTEM        = system/system.o 
SYSMAN        = system/systemManager.o
LOG           = utils/log.o 
DLL           = utils/dll.o

COMPONENT_S   = component/component.cpp
ENTITY_S      = entity/entity.cpp
SYSTEM_S      = system/system.cpp 
SYSMAN_S      = system/systemManager.cpp
LOG_S         = utils/log.cpp
DLL_S         = utils/dll.cpp

COMPONENT_HDR = component/component.hpp
ENTITY_HDR    = entity/entity.hpp
SYSTEM_HDR    = system/system.hpp 
SYSMAN_HDR    = system/systemManager.hpp
LOG_HDR       = utils/log.hpp
DLL_HDR       = utils/dll.hpp
UTILS_HDR     = utils/assembly.hpp utils/dsl.hpp utils/response.hpp utils/vec2.hpp

SYS_PATH = system/systems
DLL_PATH = ../dll
COMP_PATH = component/components

SYSTEMS = ${SYS_PATH}/systemHealth.o ${SYS_PATH}/systemGameZero.o

SYS_HEALTH_DYN_SRC   = ${SYS_PATH}/systemHealth.cpp
SYS_HEALTH_DYN_OBJ   = ${SYS_PATH}/systemHealth.o
SYS_HEALTH_DYN_HDR   = ${SYS_PATH}/systemHealth.hpp
SYS_HEALTH_DYN_SO    = ${DLL_PATH}/libsystemHealth.so

SYS_GAME_ZERO_DYN_SRC   = ${SYS_PATH}/systemGameZero.cpp 
SYS_GAME_ZERO_DYN_OBJ   = ${SYS_PATH}/systemGameZero.o 
SYS_GAME_ZERO_DYN_HDR   = ${SYS_PATH}/systemGameZero.hpp 
SYS_GAME_ZERO_DYN_SO    = ${DLL_PATH}/libsystemGameZero.so

COMP_HEALTH_DYN_SRC  = ${COMP_PATH}/componentHealth.cpp
COMP_HEALTH_DYN_OBJ  = ${COMP_PATH}/componentHealth.o
COMP_HEALTH_DYN_HDR = ${COMP_PATH}/componentHealth.hpp
COMP_HEALTH_DYN_SO  = ${DLL_PATH}/libcomponentHealth.so

SRCS = ${COMPONENT_S}   ${ENTITY_S}   ${SYSTEM_S}   ${SYSMAN_S}   ${LOG_S}   ${DLL_S}
OBJS = ${COMPONENT}     ${ENTITY}     ${SYSTEM}     ${SYSMAN}     ${LOG}     ${DLL} 
HDRS = ${COMPONENT_HDR} ${ENTITY_HDR} ${SYSTEM_HDR} ${SYSMAN_HDR} ${LOG_HDR} ${DLL_HDR} ${UTILS_HDR} 

compile_her: ${OBJS} ${HDRS}
	# compiling systems to .o
	$(SYSTEMS): %.o: %.cpp
		${CC} ${CFLAGS} -c -fPIC %< -o $@
	# g++ -c -fPIC ${SYS_HEALTH_DYN_SRC} -o ${SYS_HEALTH_DYN_OBJ} ${CFLAGS}
	# g++ -c -fPIC ${SYS_GAME_ZERO_DYN_SRC} -o ${SYS_GAME_ZERO_DYN_OBJ} ${CFLAGS}

	# compiling systems to .so
	g++ -shared ${OBJS} ${SYS_HEALTH_DYN_OBJ} -o ${SYS_HEALTH_DYN_SO} ${CFLAGS}
	g++ -shared ${OBJS} ${SYS_HEALTH_DYN_SO} ${SYS_GAME_ZERO_DYN_OBJ} -o ${SYS_GAME_ZERO_DYN_SO} ${CFLAGS}

	# compiling components to .o
	g++ -c -fPIC ${COMP_HEALTH_DYN_SRC} -o ${COMP_HEALTH_DYN_OBJ} ${CFLAGS}	
	
	# compiling components to .so
	g++ -shared ${COMP_HEALTH_DYN_OBJ} -o ${COMP_HEALTH_DYN_SO} ${CFLAGS}
	
	# compiling engine
	g++ -c -fPIC ${COMPONENT_S} -o ${COMPONENT} ${CFLAGS}
	g++ -c -fPIC ${ENTITY_S} -o ${ENTITY} ${CFLAGS}
	g++ -c -fPIC ${SYSTEM_S} -o ${SYSTEM} ${CFLAGS}
	g++ -c -fPIC ${SYSMAN_S} -o ${SYSMAN} ${CFLAGS}
	g++ -c -fPIC ${LOG_S} -o ${LOG} ${CFLAGS}
	g++ -c -fPIC ${DLL_S} -o ${DLL} ${CFLAGS}	


	# compiling main file
	g++ main.cpp ${OBJS} -ldl -o main.out ${CFLAGS}

compile_dll: ${SYS_HEALTH_DYN_SRC} ${SYS_HEALTH_DYN_HDR}
	g++ -fPIC -shared ${SYS_HEALTH_DYN_SRC} -o ${SYS_HEALTH_DYN_SO}

clear:
	bash -c "clear"

main: ${MAIN} ${HDRS} ${OBJS}
	${CC} -L${RPATH} -Wl,-rpath=${RPATH} ${CFLAGS} -ldl -o main.out ${MAIN} ${OBJS}
 
clean:
	rm -f ${OBJS} main.o ${MAIN_TEST}

debug:
	gdb main.out

all: clear main

all_debug: clear main debug

test: ${MAIN_TEST} ${HDRS}
	${CC} -o test.out ${MAIN_TEST} ${CFLAGS}

all_test: clear test

.PHONY: clear clean main all

