//
// Created by rotem on 16/01/17.
//

#ifndef CLIENT_KEYBOARDINPUT_H
#define CLIENT_KEYBOARDINPUT_H
#include "connectionHandler.h"
#include "serverInput.h"
#include "BidiMessegeEncoderDecoder.h"


class keyboardInput {
private:
    ConnectionHandler* _ch;
    BidiMessegeEncoderDecoder* _encdec;
    const short bufsize=1024;
public:
    keyboardInput(ConnectionHandler* connectionHandler, BidiMessegeEncoderDecoder* encdec);
    void run();
};


#endif //CLIENT_KEYBOARDINPUT_H
