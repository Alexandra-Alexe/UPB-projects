# Exemplu de Makefile pentru temă. "Rezolvați" comentariul de mai jos.

# Parametri pentru compilare.
CCFLAGS := -std=c++17 -Wall -Wextra -O0 -lm
JFLAGS := -Xlint:unchecked

# Directorul care conține sursele voastre, și cel unde punem binarele.
SRC_DIR := ./src
OUT_DIR := .

# Compilăm *toate* sursele găsite în $(SRC_DIR).
# Modificați doar dacă vreți să compilați alte surse.
CC_SRC := $(wildcard $(SRC_DIR)/*.cpp)
JAVA_SRC := $(wildcard $(SRC_DIR)/*.java)

CC_EXECS := $(CC_SRC:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%)
JAVA_CLASSES := $(JAVA_SRC:$(SRC_DIR)/%.java=$(OUT_DIR)/%.class)
TARGETS := $(CC_EXECS) $(JAVA_CLASSES)


.PHONY: build clean

build: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OUT_DIR)/*.class

# TODO: Apelați soluția fiecărei probleme. Puteți completa regulile astfel:
# Pentru C++
#	$(OUT_DIR)/<nume_problemă>
# Pentru Java
#	java -cp $(OUT_DIR) <NumeProblemă>
run-p1:
	$(OUT_DIR)/feribot
run-p2:
	$(OUT_DIR)/nostory
run-p3:
	$(OUT_DIR)/sushi
run-p4:
	$(OUT_DIR)/semnale


# Reguli pentru compilare. Probabil nu e nevoie să le modificați.

$(CC_EXECS): $(OUT_DIR)/%: $(SRC_DIR)/%.cpp
	g++ -o $@ $^ $(CCFLAGS)

$(JAVA_CLASSES): $(OUT_DIR)/%.class: $(SRC_DIR)/%.java
	javac $< -d $(OUT_DIR) -cp $(SRC_DIR) $(JFLAGS)
