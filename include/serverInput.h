//
// Created by rotem on 16/01/17.
//

#ifndef CLIENT_SERVERINPUT_H
#define CLIENT_SERVERINPUT_H
#include "BidiMessegeEncoderDecoder.h"
#include "connectionHandler.h"
#include <string>
#include <vector>

class serverInput {
private:
    ConnectionHandler* _ch;
    BidiMessegeEncoderDecoder* _encdec;
    char opcodeArr[2];
public:
    serverInput(ConnectionHandler* _ch, BidiMessegeEncoderDecoder* encdec);
    void run();


};


#endif //CLIENT_SERVERINPUT_H
