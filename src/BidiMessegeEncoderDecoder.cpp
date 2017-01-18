#include <list>
#include "../include/BidiMessegeEncoderDecoder.h"
#include <fstream>
// Created by rotem on 07/01/17.
//



BidiMessegeEncoderDecoder::BidiMessegeEncoderDecoder(ConnectionHandler& ch): _chandler(ch) {

    cout<<"BidiEncoderDecoder constructor"<< std::endl;
    opcodeInBytes=new char[2];
    dataFromServer.reserve(1024);
    dataFromUser.reserve(1024);
    fromServerDataLength=0;
    fromUserDatalength=0;
    isSendingData=false;
    isRecevingData=false;
    iswaitingForData=false;
    iswaitingForDir=false;
    iswaitingForAck=false;
    iswaitingForDisc = false;
    isItFirstPacket = true;
    typeOfLastPacket=-1; //put false value
//    data = new vector;
    fileName = "";

}

BidiMessegeEncoderDecoder::~BidiMessegeEncoderDecoder() {

}


vector<char>* BidiMessegeEncoderDecoder::decodeNextByte(char nextChar) {
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
//    cout <<"user input is:"<<userInput<< std::endl;
//    cout <<"command is:"<<command<< std::endl;

    if (userInput.find("RRQ") != std::string::npos) {
//        std::cout << "found RRQ!" << '\n';
        msgOpcode=1;
        //setBytesOpcode(msgOpcode); //opcodeInBytes is set.
        fileName=(userInput.substr(spaceIndex+1));
        isRecevingData = true;
        isItFirstPacket = true;
        createMsgWithZero(msgOpcode,fileName.size(),messege);

    }
    else if (userInput.find("WRQ") != std::string::npos) {
//        std::cout << "found WRQ!" << '\n';
        msgOpcode=2;
        //setBytesOpcode(msgOpcode); //opcodeInBytes is set.
        fileName=(userInput.substr(spaceIndex+1));
        isSendingData = true;
        createMsgWithZero(msgOpcode,fileName.size(),messege);
    }
    else if (userInput.find("DATA") != std::string::npos) {
//        std::cout << "found DATA, will creat a bad packet!" << '\n';
        //no need to handle it.
        createSmallMsg(11);

    }
    else if (userInput.find("ACK") != std::string::npos) {
//        std::cout << "found ACK!, will creat a bad packet" << '\n';
        //no need to handle it.
        createSmallMsg(11);


    }
    else if (userInput.find("Error") != std::string::npos) {
//        std::cout << "found Error!" << '\n';
        isRecevingData = false;
        isSendingData = false;
        createSmallMsg(11);
    }
    else if (userInput.find("DIRQ") != std::string::npos) {
//        std::cout << "found DIRQ!" << '\n';
        createSmallMsg(6);
    }
    else if (userInput.find("LOGRQ") != std::string::npos) {
//        std::cout << "found LOGRQ!" << '\n';
        msgOpcode=7;
        //setBytesOpcode(msgOpcode); //opcodeInBytes is set.
        string fileName=(userInput.substr(spaceIndex+1));
        createMsgWithZero(msgOpcode,fileName.size(),messege);
    }
    else if (userInput.find("DELRQ") != std::string::npos) {
//        std::cout << "found DELRQ!" << '\n';
        msgOpcode=8;
        //setBytesOpcode(msgOpcode); //opcodeInBytes is set.
        string fileName=(userInput.substr(spaceIndex+1));
        createMsgWithZero(msgOpcode,fileName.size(),messege);

    }
    else  if (userInput.find("BCAST") != std::string::npos) {
//        std::cout << "found BCAST!, will creat a bad packet" << '\n';
        createSmallMsg(11);

    }
    else  if (userInput.find("DISC") != std::string::npos) {
//        std::cout << "found DISC!" << '\n';
        iswaitingForDisc = true;
        createSmallMsg(10);

    }
    else {
//        std::cout << "need to create BAD packet" << '\n';
        createSmallMsg(11);
    }



    //std::cout<< (userInput.find("LOGRQ"));

//    std::cout<<"finished encode, ans size:"<<std::endl;




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
//    std::cout<<std::endl;
    outputToServer[messegeSize-1]='0'; //zero in the end
    //for (int i=0;i<messegeSize;i++ ){
    //    std::cout<<" "<<(short)outputToServer[i];
    //}
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
/**
 * this function gets the opcode msg of the given msg from the server and decide how to handle it.
 * need to take care for data,ack,bcast and disc packets.
 * @param msgOpcode
 */
void BidiMessegeEncoderDecoder::decode(short msgOpcode){
//    cout<<"function: decoder, decode packet type #"<<msgOpcode<<endl;
    if (msgOpcode==3)
        decodeDATA();
    else if (msgOpcode==4){
        short block=getShort();
//        cout<<"ACK "<<block<<endl;
    }
    else if (msgOpcode==5)
        decodeERROR();
    else if (msgOpcode==9)
        decodeBCAST();
    else
        cout<<"problem, didnt find any option for this opcode"<<endl;

}
void BidiMessegeEncoderDecoder::decodeDATA(){
    int counter=0;
    char singleByte[1];
    short packetSize=getShort();
    short blockNum=getShort();
    if (packetSize>0) {
        while (_chandler.getBytes(singleByte, 1) && counter < packetSize) {
            dataFromServer.push_back(singleByte[0]);
            counter++;
        }
    }
//    cout<< "DATA block number:"<<blockNum <<" packet size:"<<packetSize<<endl;

}
void BidiMessegeEncoderDecoder::decodeERROR() {
    char singleByte[1];
    int counter = 0;
    short error=getShort();
    while (_chandler.getBytes(singleByte, 1)&& singleByte[0]!='0') {
        dataFromServer.push_back(singleByte[0]);
        counter++;
    }

    string errormsg="";
    for (int i = 0; i < counter; i++) {
        errormsg+=dataFromServer[i];
    }
//    cout<<"ERROR "<<error<<" Error messege:"<<errormsg<<endl;
}

void BidiMessegeEncoderDecoder::decodeBCAST(){
    string addStatus="waiting for info";
    int counter = 0;
    char singleByte[1];
    _chandler.getBytes(singleByte,1);
    if (singleByte[0]==1)
        addStatus="add";
    else if (singleByte[0]==0)
        addStatus="del";
    while (_chandler.getBytes(singleByte, 1)&& singleByte[0]!='0') {
        dataFromServer.push_back(singleByte[0]);
        counter++;
    }
    string fileName[counter];
    for (int i = 0; i < counter; i++) {
        fileName[i]=dataFromServer[i];
    }
//    cout<<"BCAST "<<addStatus<<" "<<fileName<<endl;
}
/**
 * this is ont of the main indicators for the handle function.
 * @param opcodeSent
 */
void BidiMessegeEncoderDecoder::uptadeLastSentPacket(short opcodeSent){
    typeOfLastPacket=opcodeSent;
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

/**
 * this is the proccess function.
 * using theese varibles in order to hold the states:
 *  bool waitingForData;
    bool waitingForDir;
    bool waitingForAck;
    short typeOfLastPacket;
 */
void BidiMessegeEncoderDecoder::proccess(short currentOpcode){






























    if (currentOpcode == 3){    //Data
        if(iswaitingForDir){
            string fileNames = "";
            iswaitingForDir = false;
            for (int i = 0; i < dataFromServer.size(); ++i) {
                if(dataFromServer.at(i) != 0){
                    fileNames += dataFromServer.at(i);
                }else{
//                    cout << fileNames << std::endl;
                    fileNames = "";
                }
            }
        }
        else if (isRecevingData){
            if(isItFirstPacket){
                isItFirstPacket = false;
                outputFile.open(fileName);

            }

            for (int i = 0; i < dataFromServer.size(); ++i) {
                outputFile << dataFromServer.at(i);
            }
            if(dataFromServer.size() < 512){
                outputFile.close();
//                cout<< "RRQ " << fileName << " complete" << endl;
            }


        }else{
//            cout<< "Problem with process the data" << endl;

        }

    }else if(currentOpcode == 4){   //Acknowledgment
        if(iswaitingForDisc){
            //TODO
        }
//        ifstream fileBuffer;
        else  if(isSendingData){
            if(isItFirstPacket) {
                isItFirstPacket = false;
                ifstream fileBuffer(fileName, ios::in|ios::binary);

                outputFile.open(fileName);
            }
                /* fileBuffer.seekg (0, ios::end);
                 int length = fileBuffer.tellg();
                 fileBuffer.seekg (0, ios::beg);
                 fileBuffer = new char [length];
                 input.read (buffer,length);*/

                /*string line;
                ifstream myfile ("example.txt");
                if (myfile.is_open())
                {
                    while ( getline (myfile,line) )
                    {
                        cout << line << '\n';
                    }

                    myfile.close();
                }
        */
            else cout << "Unable to open file";
        }



    }else if(currentOpcode == 5){   //Error
        if(iswaitingForDisc){
            createSmallMsg(10);
        }
        iswaitingForDisc = false;
        isSendingData = false;
        isRecevingData = false;
//        iswaitingForAck = false;
//        iswaitingForData = false;
        iswaitingForDir = false;
    }else{  //Broadcast
        //Do noting
    }
    //TODO:need to implement.
}

short BidiMessegeEncoderDecoder::valueOfTwoCells(char *bytesArr, int first, int second) {
    short result = (short)((bytesArr[first] & 0xff) << 8);
    result += (short)(bytesArr[second] & 0xff);
    return result;
}


short BidiMessegeEncoderDecoder::getShort(){
    char numInBytes[2];
    _chandler.getBytes(numInBytes,2);
    short error=0;
    return(bytesToShort(numInBytes));
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
//info is
void BidiMessegeEncoderDecoder::createDataPacket (short blockNum, short packetSize, string* _s){
    messegeSize=6+packetSize;
    outputToServer=new char[messegeSize];
    char encodedBytes[2];

    short opc=3;
    shortToBytes(opc,encodedBytes);
    outputToServer[0]=encodedBytes[0];
    outputToServer[1]=encodedBytes[1];
    shortToBytes(packetSize,encodedBytes);
    outputToServer[2]=encodedBytes[0];
    outputToServer[3]=encodedBytes[1];
    shortToBytes(blockNum,encodedBytes);
    outputToServer[4]=encodedBytes[0];
    outputToServer[5]=encodedBytes[1];
    for (int i=0;i<packetSize;i++){
        outputToServer[i+6]=_s->at(i);
    }





    msgIsReady=true;
}
