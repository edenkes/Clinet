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
    bool isSendingData;
    bool isRecevingData;
    bool iswaitingForData;
    bool iswaitingForDir;
    bool iswaitingForAck;
    short typeOfLastPacket;
//    vector data;
    string fileName;
    ofstream outputFile;
    bool iswaitingForDisc;
    bool isItFirstPacket;

    //Const


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
    void createDataPacket (short blockNum, short packetSize, string* _s);




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
