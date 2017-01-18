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
        cout << "opcode from server:" << opc << endl;
        //need to handle BCAST, DATA, DISC, ACK.
        _encdec->decode(opc);
        _encdec->proccess(opc);
        if (_encdec->shouldTerminate()) {
            break;
        }
    }

         cout<<"server input - closing connection"<<endl;
        _ch->close();
        cout<<"connection terminated"<<endl;


}
