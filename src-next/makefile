CC = g++

CFLAGS = -Wall -std=c++17 -g -ldl

RPATH         = ./system/systems/systemDynamic/

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

COMPONENT_HDR = component/component.hpp component/components/health.hpp component/components/kick.hpp
ENTITY_HDR    = entity/entity.hpp
SYSTEM_HDR    = system/system.hpp 
SYSMAN_HDR    = system/systemManager.hpp
LOG_HDR       = utils/log.hpp
DLL_HDR       = utils/dll.hpp
UTILS_HDR     = utils/assembly.hpp utils/dsl.hpp utils/response.hpp utils/vec2.hpp


SYS_HEALTH_DYN_SRC   = system/systems/systemDynamic/systemHealth.cpp
SYS_HEALTH_DYN_OBJ   = system/systems/systemDynamic/systemHealth.o
SYS_HEALTH_DYN_HDR   = system/systems/systemDynamic/systemHealth.hpp
SYS_HEALTH_DYN_SO    = system/systems/systemDynamic/libsystemHealth.so

COMP_HEALTH_DYN_SRC  = component/components/componentsDynamic/health.cpp
COMP_HEALTH_DYN_OBJ  = component/components/componentsDynamic/health.o
COMP_HEALTH_DYN_HDR = component/components/componentsDynamic/health.hpp
COMP_HEALTH_DYN_SO  = component/components/componentsDynamic/health.so

#TEST_PATH = system/systems/systemDynamic
DLL_PATH = ../dll/

SRCS = ${COMPONENT_S}   ${ENTITY_S}   ${SYSTEM_S}   ${SYSMAN_S}   ${LOG_S}   ${DLL_S}
OBJS = ${COMPONENT}     ${ENTITY}     ${SYSTEM}     ${SYSMAN}     ${LOG}     ${DLL} 
HDRS = ${COMPONENT_HDR} ${ENTITY_HDR} ${SYSTEM_HDR} ${SYSMAN_HDR} ${LOG_HDR} ${DLL_HDR} ${UTILS_HDR} 

compile_her: ${SRCS} ${HDRS}
	g++ -c -fPIC ${SYS_HEALTH_DYN_SRC} -o ${SYS_HEALTH_DYN_OBJ}
	g++ -c -fPIC ${COMPONENT_S} -o ${COMPONENT}
	g++ -c -fPIC ${ENTITY_S} -o ${ENTITY}
	g++ -c -fPIC ${SYSTEM_S} -o ${SYSTEM}
	g++ -c -fPIC ${SYSMAN_S} -o ${SYSMAN}
	g++ -c -fPIC ${LOG_S} -o ${LOG}
	g++ -c -fPIC ${DLL_S} -o ${DLL}
	g++ -c -fPIC ${COMP_HEALTH_DYN_SRC} -o ${COMP_HEALTH_DYN_OBJ}
	g++ -shared ${OBJS} ${SYS_HEALTH_DYN_OBJ} -o ${DLL_PATH}/libSystemHealth.so
	g++ -shared ${COMP_HEALTH_DYN_OBJ} -o ${DLL_PATH}/libComponentHealth.so
	#g++ -fPIC ${SRCS} -shared ${TEST_PATH}/sysDin.cpp -o ${TEST_PATH}/sysDin.so
	#g++ ${TEST_PATH}/class_user.cpp -ldl -o ${TEST_PATH}/class_user
	g++ main.cpp ${OBJS} -ldl -o main.out

compile_dll: ${SYS_HEALTH_DYN_SRC} ${SYS_HEALTH_DYN_HDR}
	g++ -fPIC -shared ${SYS_HEALTH_DYN_SRC} -o ${SYS_HEALTH_DYN_SO}

clear:
	bash -c "clear"

main: ${MAIN} ${HDRS} ${OBJS}
	${CC} -L${RPATH} -Wl,-rpath=${RPATH} ${CFLAGS} -o main.out ${MAIN} ${OBJS}
 
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

