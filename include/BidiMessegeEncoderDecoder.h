//
// Created by rotem on 07/01/17.
//

#ifndef BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
#define BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
#include "Packet.h"
#include <vector>
#include <iostream>

class BidiMessegeEncoderDecoder {
private:
    char* bytes;
    int length;
    bool zeroInTheEnd;
    short opcode;
    char* opcodeInBytes;
    std::vector<char> chars;
public:
    BidiMessegeEncoderDecoder();
    virtual ~BidiMessegeEncoderDecoder();
    Packet* decodeNextByte(char nextChar); //maybe need other thing then char.
    void pushChar(char nextChar);
    char* encode(Packet messege);
    Packet decode(char* bytesArr);
    void setOpCode();
    void initDecode();
    short valueOfTwoCells(char* bytesArr, int first, int second);
    short bytesToShort(char* bytesArr);
    void shortToBytes(short num, char* bytesArr);



};


#endif //BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
