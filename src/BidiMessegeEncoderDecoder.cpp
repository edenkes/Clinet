#include "../include/BidiMessegeEncoderDecoder.h"
// Created by rotem on 07/01/17.
//



BidiMessegeEncoderDecoder::BidiMessegeEncoderDecoder() {

    cout<<"BidiEncoderDecoder constructor"<< std::endl;
    opcodeInBytes=new char[2];
    dataFromServer.reserve(1024);
    dataFromUser.reserve(1024);
    fromServerDataLength=0;
    fromUserDatalength=0;

}

BidiMessegeEncoderDecoder::~BidiMessegeEncoderDecoder() {

}


vector<char>* BidiMessegeEncoderDecoder::decodeNextByte(char nextChar) {
    //TODO:need to implement
    return (&dataFromServer) ;
}

void BidiMessegeEncoderDecoder::pushCharFromServer(char nextChar) {
    dataFromServer.push_back(nextChar);
    fromServerDataLength++;
}
/**
 * work with Data from user vector
 *writie ourput to char* outputToServer;
 * @param messege from user
 */
void BidiMessegeEncoderDecoder::encode(char* messege) {
    string userInput(messege);

    for (auto &&c  :userInput ) {
        dataFromUser.push_back(c);
    }

    int outputLength=0;
    short msgOpcode;
    int counter;
    std::string command(userInput.substr(0,userInput.find(" ")));
    unsigned int spaceIndex=userInput.find(" ");
    cout <<"user input is:"<<userInput<< std::endl;
    cout <<"command is:"<<command<< std::endl;

    if (userInput.find("RRQ") != std::string::npos) {
        std::cout << "found RRQ!" << '\n';
        msgOpcode=1;
        //setBytesOpcode(msgOpcode); //opcodeInBytes is set.
        string fileName=(userInput.substr(spaceIndex+1));
        createMsgWithZero(msgOpcode,fileName.size(),messege);

    }
    else if (userInput.find("WRQ") != std::string::npos) {
        std::cout << "found WRQ!" << '\n';
        msgOpcode=2;
        //setBytesOpcode(msgOpcode); //opcodeInBytes is set.
        string fileName=(userInput.substr(spaceIndex+1));
        createMsgWithZero(msgOpcode,fileName.size(),messege);
    }
    else if (userInput.find("DATA") != std::string::npos) {
        std::cout << "found DATA, will creat a bad packet!" << '\n';
        //no need to handle it.
        createSmallMsg(11);

    }
    else if (userInput.find("ACK") != std::string::npos) {
        std::cout << "found ACK!, will creat a bad packet" << '\n';
        //no need to handle it.
        createSmallMsg(11);


    }
    else if (userInput.find("Error") != std::string::npos) {
        std::cout << "found Error!" << '\n';
        //need to handle

    }
    else if (userInput.find("DIRQ") != std::string::npos) {
        std::cout << "found DIRQ!" << '\n';
        createSmallMsg(10);
    }
    else if (userInput.find("LOGRQ") != std::string::npos) {
        std::cout << "found LOGRQ!" << '\n';
        msgOpcode=7;
        //setBytesOpcode(msgOpcode); //opcodeInBytes is set.
        string fileName=(userInput.substr(spaceIndex+1));
        createMsgWithZero(msgOpcode,fileName.size(),messege);
    }
    else if (userInput.find("DELRQ") != std::string::npos) {
        std::cout << "found DELRQ!" << '\n';
        msgOpcode=8;
        //setBytesOpcode(msgOpcode); //opcodeInBytes is set.
        string fileName=(userInput.substr(spaceIndex+1));
        createMsgWithZero(msgOpcode,fileName.size(),messege);

    }
    else  if (userInput.find("BCAST") != std::string::npos) {
        std::cout << "found BCAST!, will creat a bad packet" << '\n';
        createSmallMsg(11);

    }
    else  if (userInput.find("DISC") != std::string::npos) {
        std::cout << "found DISC!" << '\n';
        createSmallMsg(10);

    }
    else {
        std::cout << "need to create BAD packet" << '\n';
        createSmallMsg(11);
    }



    //std::cout<< (userInput.find("LOGRQ"));

    std::cout<<"finished encode, ans size:"<<std::endl;




}
char* BidiMessegeEncoderDecoder::getEncodedMsg(){
    return outputToServer;
}

void BidiMessegeEncoderDecoder::createMsgWithZero (short opcode, int fileSize ,char* msg){
    messegeSize=3+fileSize; //2 for opcode ans 1 for zero.
    string userInput(msg);
    unsigned int spaceIndex=userInput.find(" ");
    string fileName=(userInput.substr(spaceIndex+1));
    outputToServer=new char[messegeSize];
    shortToBytes(opcode,outputToServer);

    for (int i=0;i<fileSize;i++ ){
        outputToServer[i+2]=fileName.at(i);
    }
    std::cout<<std::endl;
    outputToServer[messegeSize-1]='0'; //zero in the end
    for (int i=0;i<messegeSize;i++ ){
        std::cout<<" "<<(short)outputToServer[i];
    }
    msgIsReady=true;

}

void BidiMessegeEncoderDecoder::createSmallMsg (short opcode){
    messegeSize=2;
    outputToServer=new char[2];
    shortToBytes(opcode,outputToServer);
    msgIsReady=true;
}
int BidiMessegeEncoderDecoder::getMsgSize() {
    return messegeSize;
}


void BidiMessegeEncoderDecoder::decode(char *bytesArr) {



}
void BidiMessegeEncoderDecoder::setOpCode() {

}

void BidiMessegeEncoderDecoder::setBytesOpcode(short num ){
    shortToBytes(num,opcodeInBytes);
}
void BidiMessegeEncoderDecoder::initDecode() {
    *outputToServer=0; //this way?
    msgIsReady=false;
    opcode=0;
    dataFromUser.clear();
    messegeSize=0;
}

short BidiMessegeEncoderDecoder::valueOfTwoCells(char *bytesArr, int first, int second) {
    short result = (short)((bytesArr[first] & 0xff) << 8);
    result += (short)(bytesArr[second] & 0xff);
    return result;
}




short BidiMessegeEncoderDecoder::bytesToShort(char* bytesArr)
{
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}
void BidiMessegeEncoderDecoder::shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

char* BidiMessegeEncoderDecoder::concat(std::vector<char*> &arrays)
{

}




