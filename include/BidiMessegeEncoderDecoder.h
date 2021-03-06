//
// Created by rotem on 07/01/17.
//

#ifndef BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
#define BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
#include "connectionHandler.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int

using namespace std;
class BidiMessegeEncoderDecoder {
private:
    char* outputToServer;
    vector<char> dataFromUser;
    vector<char> dataFromServer;
    size_t outputDatalength;
    int totalNumberOfBlocksToSend;
    int blockesSent;
    char* oData;

    int fromServerDataLength;
    int messegeSize;
    bool serverMsgIsReady;
    char* opcodeInBytes;
    ConnectionHandler* _chandler;
    bool isSendingData;
    bool isRecevingData;
    bool continueSend;
    bool iswaitingForDir;
    bool iswaitingForAck;
    short typeOfLastPacket;
    string fileName="";
    string recSendFilename="";
    ofstream outputFile;
    //
    bool iswaitingForDisc;
    bool isItFirstPacket;
    bool shouldterminate;
    bool keyboardTerminate;
    short packetSize;
    ifstream inFile;
    short numberOfBlocksSent;
    short recievedCounter;
    short ackBlock;
    short dataBlockNum;

    //Const


public:
    BidiMessegeEncoderDecoder(ConnectionHandler* ch);
    //Copy Constructor
    BidiMessegeEncoderDecoder(const BidiMessegeEncoderDecoder& source);

    //Overloaded Assignment
    BidiMessegeEncoderDecoder& operator=(const BidiMessegeEncoderDecoder& source);

    //Desstructor
    virtual ~BidiMessegeEncoderDecoder();
    vector<char>* decodeNextByte(char nextChar); //maybe need other thing then char.
    void pushCharFromServer(char nextChar);
    void encode(char* messege);
    char* getEncodedMsg();
    void createMsgWithZero (short opcode, int fileSize ,char* msg);
    void createSmallMsg (short opcode);
    void createACK (short block);
    int getMsgSize();
    void decode(char* bytesArr);
    void decode(short msgOpcode);
    void decodeDATA();
    void decodeERROR();
    void decodeBCAST();
    void initEncoder();
    void proccess(short currentOpcode);
    short getShort();
    short bytesToShort(char* bytesArr);
    void shortToBytes(short num, char* bytesArr);
    void createDataPacket (short blockNum, short packetSize);
    bool shouldTerminate ();
    bool keyboardShouldTerminate();
    bool serverMessegeIsReady();

};


#endif //BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
