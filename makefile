# Nome del programma eseguibile
TARGET = mainDNAStructureInfo

# Compilatore
CXX = g++

# Opzioni di compilazione
CXXFLAGS = -Wall -Wextra -std=c++11

# File sorgente
SRCS = mainDNAStructureInfo.cpp

# Regola di compilazione
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Regola per eseguire il programma con parametri passati
# Regola per eseguire il programma con parametri
comparison: $(TARGET)
	@read -p "Enter typeIn [E, T]: " typeIn; \
	read -p "Enter typeOut [C, T]: " typeOut; \
	read -p "Enter profile [A, G]: " profile; \
	read -p "Enter inOrigin: " inOrigin; \
	read -p "Enter outputName: " outputName; \
	read -p "Enter inListComp: " inListComp; \
	./$(TARGET) --type C --typeIn $$typeIn --typeOut $$typeOut --profile $$profile --inOrigin $$inOrigin --outputName $$outputName --inListComp $$inListComp

individual : $(TARGET)
	@read -p "Enter typeIn [E, T]: " typeIn; \
	read -p "Enter typeOut [C, T]: " typeOut; \
	read -p "Enter profile [A, G]: " profile; \
	read -p "Enter inOrigin: " inOrigin; \
	read -p "Enter outputName: " outputName; \
	read -p "Enter inListComp: " inListComp; \
	./$(TARGET) --type I --typeIn $$typeIn --typeOut $$typeOut --profile $$profile --inOrigin $$inOrigin --outputName $$outputName

# DA FARE COMPARISON E INDIVIDUAL. NON UTILIZZARE ANCORA

help: $(TARGET)
	./$(TARGET) --help

version: $(TARGET)
	./$(TARGET) --version

# Pulire i file oggetto e l'eseguibile
clean:
	rm -f $(TARGET)
