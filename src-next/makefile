CC = g++

CFLAGS = -Wall

MAIN = main.cpp
COMPONENT = component/component.cpp
ENTITY    = entity/entity.cpp
MONITOR   = monitor/monitor.cpp
SYSTEM    = system/system.cpp                                                                          system/systemManager.cpp

COMPONENT_DEPS = component/component.hpp component/components/health.hpp component/components/kick.hpp
ENTITY_DEPS    = entity/entity.hpp
MONITOR_DEPS   = monitor/monitor.hpp
SYSTEM_DEPS    = system/system.hpp system/systems/systemHealth.hpp system/systems/systemKick.hpp       system/systemManager.hpp

OBJS = ${COMPONENT}      ${ENTITY}      ${MONITOR}      ${SYSTEM}      
DEPS = ${COMPONENT_DEPS} ${ENTITY_DEPS} ${MONITOR_DEPS} ${SYSTEM_DEPS}

clear:
	bash -c "clear"

main: ${MAIN} ${DEPS}
	${CC} -o main ${MAIN} ${CFLAGS}

clean:
	rm -f ${OBJS}

all: clear main clean

.PHONY: clear clean main all

