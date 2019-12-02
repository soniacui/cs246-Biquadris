CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla
OBJECTS = main.o board.o controller.o info.o level.o subject.o tetromino.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = Biquadris.exe

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
