//
// Created by rotem on 16/01/17.
//

#include "../include/serverInput.h"

serverInput::serverInput(ConnectionHandler *ch, BidiMessegeEncoderDecoder *encdec):
_ch(ch), _encdec(encdec){}



void serverInput::run(){
//    cout<<"started serverListener"<<endl;
    while (1) {
        if (!_ch->getBytes(opcodeArr, 2)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        short opc = (_encdec->bytesToShort(opcodeArr));
        //cout << "opcode from server:" << opc << endl;
        //need to handle BCAST, DATA, DISC, ACK.
        _encdec->decode(opc);
        _encdec->proccess(opc);
        if (_encdec->shouldTerminate()) {
            break;
        }
        if (_encdec->serverMessegeIsReady()) {
            char *msgToSend = _encdec->getEncodedMsg();
            // TODO: after sending the msg need to delete the msgToSend;
            //now need to convert the user input to the format for the server (using encoderDevoder).
            int len = _encdec->getMsgSize();
            // std::cout << "length:\n" << len <<std::endl;
            if (!_ch->sendBytes(msgToSend, len)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;

            }
            _encdec->initEncoder();
        }
    }

        // cout<<"server input - closing connection"<<endl;
        _ch->close();
      //  cout<<"connection terminated"<<endl;


}
