CC = g++

CFLAGS = -Wall -std=c++17 -g -ldl

RPATH          = ./system/systems/systemDynamic/

MAIN_TEST     = main.test.o
MAIN          = main.o
COMPONENT     = component/component.o
ENTITY        = entity/entity.o
MONITOR       = monitor/monitor.o
SYSTEM        = system/system.o system/systemManager.o
UTILS         = utils/log.o utils/dll.o

COMPONENT_HDR = component/component.hpp component/components/health.hpp component/components/kick.hpp
ENTITY_HDR    = entity/entity.hpp
MONITOR_HDR   = monitor/monitor.hpp
SYSTEM_HDR    = system/system.hpp system/systemManager.hpp
UTILS_HDR     = utils/assembly.hpp utils/dll.hpp utils/dsl.hpp utils/log.hpp utils/response.hpp utils/vec2.hpp

DYNAMIC_SRC   = system/systems/systemDynamic/systemHealth.cpp
DYNAMIC_HDR   = system/systems/systemDynamic/systemHealth.hpp
DYNAMIC_SO    = system/systems/systemDynamic/libsystemHealth.so

OBJS = ${COMPONENT}      ${ENTITY}      ${SYSTEM}      ${UTILS} 
HDRS = ${COMPONENT_HDR}  ${ENTITY_HDR}  ${SYSTEM_HDR}  ${UTILS_HDR} 

compile_dll: ${DYNAMIC_SRC} ${DYNAMIC_HDR}
	g++ -fPIC -shared ${DYNAMIC_SRC} -o ${DYNAMIC_SO}

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

