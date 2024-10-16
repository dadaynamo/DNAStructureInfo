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
	@read -p "Enter output name: " outputname; \
	read -p "Enter TOTsize: " totSize; \
	./$(TARGET) --outputName $$outputname --totSize $$totSize --type R
individual : $(TARGET)
	@read -p "Enter output name: " outputname; \
	read -p "Enter TOTsize: " totSize; \
	./$(TARGET) --outputName $$outputname --totSize $$totSize --type R

# DA FARE COMPARISON E INDIVIDUAL. NON UTILIZZARE ANCORA

help: $(TARGET)
	./$(TARGET) --help

version: $(TARGET)
	./$(TARGET) --version

# Pulire i file oggetto e l'eseguibile
clean:
	rm -f $(TARGET)
