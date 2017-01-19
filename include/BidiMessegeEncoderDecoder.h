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
    string filenameFromUser;
    string fileNameFromServer;
    bool serverMsgIsReady;
    short opcode;
    char* opcodeInBytes;
    ConnectionHandler* _chandler;
    bool isSendingData;
    bool isRecevingData;
    bool iswaitingForData;
    bool iswaitingForDir;
    bool iswaitingForAck;
    short typeOfLastPacket;
    string fileName;
    string recSendFilename;
    ofstream outputFile;
    bool iswaitingForDisc;
    bool isItFirstPacket;
    bool shouldterminate=false;
    bool keyboardTerminate=false;
    short packetSize;
    ifstream inFile;
    short numberOfBlocksSent;
    short recievedCounter;
    short ackBlock;

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
    void uptadeLastSentPacket(short opcodeSent);
    void setOpCode();
    void setBytesOpcode(short num);
    void initEncoder();
    void proccess(short currentOpcode);
    short valueOfTwoCells(char* bytesArr, int first, int second);
    short getShort();
    short bytesToShort(char* bytesArr);
    void shortToBytes(short num, char* bytesArr);
    void createDataPacket (short blockNum, short packetSize);
    bool shouldTerminate ();
    bool keyboardShouldTerminate();
    bool serverMessegeIsReady();




    /*
 * using namespace std;
class EncodeDecode {
private:
    short _port;
    string _addr;
    ConnectionHandler& _chandler;
    vector<char> recievedData;
    char* _outBytes;
    string filename;
    ofstream _outf;
    bool isInialized=false;
    void logReadWriteDel(short opCode,string& name);
    void dirqDisc(short opCode);
public:
    short bytesToShort(char* bytesArr);
    void shortToBytes(short num, char* bytesArr);
    EncodeDecode(short port,string host,ConnectionHandler& chandler);
    virtual ~EncodeDecode();
    short getOpcode(string& opcode);
    void inputFromKeyboard(short opCode,string& name);
    void getMessage();
    int _outBytesSize;
    char* getOutBytes(){return _outBytes;}
    void resetOutBytes(){_outBytes=0;}
    int sendReqType;//1 for RRQ, 2 for WRQ , 6 for DIRQ

    void outputProceedReadOpcode(short opcode);
};


 */

    void crateFile();


};


#endif //BOOST_ECHO_CLIENT_BIDIMESSEGEENCODERDECODER_H
