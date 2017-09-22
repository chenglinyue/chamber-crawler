CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = cc3k
OBJECTS = main.o board.o boostatk.o boostdef.o caption.o chamber.o character.o controller.o dragon.o drow.o dwarf.o elf.o enemy.o goblin.o halfling.o human.o item.o merchant.o orcs.o player.o poisonhealth.o restorehealth.o shade.o treasure.o troll.o vampire.o woundatk.o wounddef.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
