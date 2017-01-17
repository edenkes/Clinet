//
// Created by rotem on 07/01/17.
//

#ifndef BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
#define BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
#include "connectionHandler.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class BidiMessegeEncoderDecoder {
private:
    char* outputToUser;
    char* outputToServer;
    vector<char> dataFromUser;
    vector<char> dataFromServer;
    int output_data_length;
    int fromServerDataLength;
    int fromUserDatalength;
    int messegeSize;
    string filenameFromUser;
    string fileNameFromServer;
    //    ofstream _outputStream;
    bool msgIsReady;
    short opcode;
    char* opcodeInBytes;
    ConnectionHandler* _chandler;
    bool waitingForData;
    bool waitingForDir;
    bool waitingForAck;
    short typeOfLastPacket;


public:
    BidiMessegeEncoderDecoder(ConnectionHandler* ch);
    virtual ~BidiMessegeEncoderDecoder();
    vector<char>* decodeNextByte(char nextChar); //maybe need other thing then char.
    void pushCharFromServer(char nextChar);
    void encode(char* messege);
    char* getEncodedMsg();
    void createMsgWithZero (short opcode, int fileSize ,char* msg);
    void createSmallMsg (short opcode);
    int getMsgSize();
    void decode(char* bytesArr);
    void decode(short msgOpcode);
    void decodeDATA();
    void decodeERROR();
    void decodeBCAST();
    void uptadeLastSentPacket(short opcodeSent);
    void setOpCode();
    void setBytesOpcode(short num);
    void initDecode();
    void proccess(short currentOpcode);
    short valueOfTwoCells(char* bytesArr, int first, int second);
    short getShort();
    short bytesToShort(char* bytesArr);
    void shortToBytes(short num, char* bytesArr);
    char* concat(std::vector<char*> &arrays);

};


#endif //BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
