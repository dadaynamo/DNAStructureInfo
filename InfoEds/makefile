# Definisco le variabili per i nomi degli eseguibili
CC = g++
CFLAGS = -Wall -std=c++11

# Definisco i nomi degli eseguibili
EXEC1 = decodeFile
EXEC2 = encodeFile
EXEC3 = statRun
EXEC4 = runMaxSearch

# Compilazione dei singoli file .cpp
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

$(EXEC1): decodeFile.cpp
	$(CC) $(CFLAGS) -o $(EXEC1) decodeFile.cpp

$(EXEC2): encodeFile.cpp
	$(CC) $(CFLAGS) -o $(EXEC2) encodeFile.cpp

$(EXEC3): statRun.cpp
	$(CC) $(CFLAGS) -o $(EXEC3) statRun.cpp

$(EXEC4): runMaxSearch.cpp
	$(CC) $(CFLAGS) -o $(EXEC4) runMaxSearch.cpp

# Pulizia dei file compilati
clean:
	rm -f $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

# Esegui il make di default
.PHONY: all clean
