# Variabili
CXX = g++
CXXFLAGS = -Wall -Wextra -O2
TARGET = main2DNAStructureInfo
SRC = main2DNAStructureInfo.cpp

# Obiettivo principale
all: $(TARGET)

# Regola per creare l'eseguibile
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Pulizia dei file generati
clean:
	rm -f $(TARGET)
	rm -f *.o

.PHONY: all clean
