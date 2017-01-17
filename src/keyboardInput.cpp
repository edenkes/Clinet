//
// Created by rotem on 16/01/17.
//

#include "../include/keyboardInput.h"

keyboardInput::keyboardInput(ConnectionHandler *connectionHandler, BidiMessegeEncoderDecoder *encdec):
        _ch(connectionHandler), _encdec(encdec) {}

void keyboardInput::run() {
    while (1) {
        char buf[bufsize];
        std::cout << "waiting for user input\n" << std::endl;
        std::cin.getline(buf, bufsize);
        _encdec->encode(buf);
        char *msgToSend = _encdec->getEncodedMsg();
        // TODO: after sending the msg need to delete the msgToSend;
        //now need to convert the user input to the format for the server (using encoderDevoder).
        int len = _encdec->getMsgSize();
        // std::cout << "length:\n" << len <<std::endl;
        if (!_ch->sendBytes(msgToSend, len)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
    }
}

