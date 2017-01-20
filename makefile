CC=g++    
CFLAGS=-g -Wall -Weffc++ -std=c++11 -c -Iinclude
LDFLAGS:=-lboost_system -lboost_locale -lboost_filesystem -lboost_thread


all: TFTPclient

TFTPclient: bin/bidiClient.o bin/connectionHandler.o bin/BidiMessegeEncoderDecoder.o bin/keyboardInput.o bin/serverInput.o 
	$(CC)	bin/bidiClient.o bin/connectionHandler.o bin/BidiMessegeEncoderDecoder.o bin/keyboardInput.o bin/serverInput.o -o bin/TFTPclient $(LDFLAGS)

	
bin/bidiClient.o: src/bidiClient.cpp
	$(CC) $(CFLAGS) -o bin/bidiClient.o src/bidiClient.cpp
	
bin/BidiMessegeEncoderDecoder.o: src/BidiMessegeEncoderDecoder.cpp include/BidiMessegeEncoderDecoder.h
	$(CC) $(CFLAGS) -o bin/BidiMessegeEncoderDecoder.o src/BidiMessegeEncoderDecoder.cpp

bin/connectionHandler.o: src/connectionHandler.cpp include/connectionHandler.h
	$(CC) $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp


bin/keyboardInput.o:src/keyboardInput.cpp include/keyboardInput.h
	$(CC) $(CFLAGS) -o bin/keyboardInput.o src/keyboardInput.cpp
	
bin/serverInput.o: src/serverInput.cpp include/serverInput.h
	$(CC) $(CFLAGS) -o bin/serverInput.o src/serverInput.cpp


	
clean:
	rm -rf bin/*o bin/TFTPclient
