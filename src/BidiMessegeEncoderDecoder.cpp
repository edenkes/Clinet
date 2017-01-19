#include <list>
#include "../include/BidiMessegeEncoderDecoder.h"
#include <fstream>
// Created by rotem on 07/01/17.
//



BidiMessegeEncoderDecoder::BidiMessegeEncoderDecoder(ConnectionHandler* ch): _chandler(ch),blockesSent(0), messegeSize(0), recievedCounter(1) {

//    cout<<"BidiEncoderDecoder constructor"<< std::endl;
    opcodeInBytes=new char[2];
    dataFromServer.reserve(1024);
    dataFromUser.reserve(1024);
    fromServerDataLength=0;
    isSendingData=false;
    isRecevingData=false;
    iswaitingForDir=false;
    iswaitingForAck=false;
    iswaitingForDisc = false;
    isItFirstPacket = true;
    keyboardTerminate=false;
    typeOfLastPacket=-1; //put false value
    fileName = "";
    shouldterminate=false;


    serverMsgIsReady=false;
    numberOfBlocksSent=0;
    recievedCounter=0;
    ackBlock=0;
    totalNumberOfBlocksToSend=0;
    continueSend=false;



}


//Copy Constructor
BidiMessegeEncoderDecoder::BidiMessegeEncoderDecoder(const BidiMessegeEncoderDecoder& source):  _chandler(source._chandler){
    opcodeInBytes=new char[2];
    dataFromServer.reserve(1024);
    dataFromUser.reserve(1024);
    fromServerDataLength=0;
    isSendingData=false;
    isRecevingData=false;
    iswaitingForDir=false;
    iswaitingForAck=false;
    iswaitingForDisc = false;
    isItFirstPacket = true;
    keyboardTerminate=false;
    typeOfLastPacket=-1; //put false value
    fileName = "";
    shouldterminate=false;
    recievedCounter=1;
    blockesSent=0;
    messegeSize=0;
    serverMsgIsReady=false;
    numberOfBlocksSent=0;
    recievedCounter=0;
    ackBlock=0;
    continueSend=false;
}

//Overloaded Assignment
BidiMessegeEncoderDecoder& BidiMessegeEncoderDecoder::operator=(const BidiMessegeEncoderDecoder& source) {
    if(this == &source)
        return *this;


    return *this;

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
        recSendFilename=fileName;
        createMsgWithZero(msgOpcode,fileName.size(),messege);

    }
    else if (userInput.find("WRQ") != std::string::npos) {
//        std::cout << "found WRQ!" << '\n';
        msgOpcode=2;
        //setBytesOpcode(msgOpcode); //opcodeInBytes is set.
        fileName=(userInput.substr(spaceIndex+1));
        isSendingData = true;
        recSendFilename=fileName;
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
        //isRecevingData = false;
        //isSendingData = false;
        createSmallMsg(11);
    }
    else if (userInput.find("DIRQ") != std::string::npos) {
//        std::cout << "found DIRQ!" << '\n';
        iswaitingForDir=true;
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
        keyboardTerminate=true;

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
    serverMsgIsReady=false;

}
//called only by keyboard
void BidiMessegeEncoderDecoder::createSmallMsg (short opcode){
    messegeSize=2;
    outputToServer=new char[2];
    shortToBytes(opcode,outputToServer);
    serverMsgIsReady=false;
}
//called only by serverlistener.
void BidiMessegeEncoderDecoder::createACK (short block){
    messegeSize=4;
    outputToServer=new char[messegeSize];
    shortToBytes(4,outputToServer);
    char blackInbytes[2];
    shortToBytes(block,blackInbytes);
    outputToServer[2]=blackInbytes[0];
    outputToServer[3]=blackInbytes[1];
    serverMsgIsReady=true;
    cout<<"created ack packet, block number:"<<block<<endl;
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
        cout<<"ACK "<<block<<endl;
        ackBlock=block;
    }
    else if (msgOpcode==5)
        decodeERROR();
    else if (msgOpcode==9)
        decodeBCAST();
    else
        cout<<"problem, didnt find any option for this opcode"<<endl;

}
void BidiMessegeEncoderDecoder::decodeDATA(){

     //waiting for data.
        int counter = 0;
        char singleByte[1];
        packetSize = getShort();
        short blockNum = getShort();
        cout << "recieved data packet. size:" << packetSize << " block:" << blockNum << endl;

            while ((counter < packetSize)  ) {
                _chandler->getBytes(singleByte, 1);
                dataFromServer.push_back(singleByte[0]);
                counter++;
            }

        //cout<< "DATA block number:"<<blockNum <<" packet size:"<<packetSize<<endl;


}
void BidiMessegeEncoderDecoder::decodeERROR() {
    char singleByte[1];
    int counter = 0;
    short error=getShort();
    while (_chandler->getBytes(singleByte, 1)&& singleByte[0]!='0') {
        dataFromServer.push_back(singleByte[0]);
        counter++;
    }

    string errormsg="";
    for (int i = 0; i < counter; i++) {
        errormsg+=dataFromServer[i];
    }
    cout<<"ERROR "<<error<<" Error messege:"<<errormsg<<endl;
    dataFromServer.clear();
    serverMsgIsReady=false;
}

void BidiMessegeEncoderDecoder::decodeBCAST(){
    string addStatus="waiting for info";
    int counter = 0;
    char singleByte[1];
    _chandler->getBytes(singleByte,1);
    if (singleByte[0]==1)
        addStatus="add";
    else if (singleByte[0]==0)
        addStatus="del";
    while (_chandler->getBytes(singleByte, 1)&& singleByte[0]!='0') {
        dataFromServer.push_back(singleByte[0]);
        counter++;
    }
    string bcastString="";
    for (int i = 0; i < counter; i++) {
        bcastString+=dataFromServer[i];
    }
    cout<<"BCAST "<<addStatus<<" "<<bcastString<<endl;
    dataFromServer.clear();
    serverMsgIsReady=false;
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
void BidiMessegeEncoderDecoder::initEncoder() {
    *outputToServer=0; //this way?
    serverMsgIsReady=false;
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

            for (int i = 0; i < packetSize; ++i) {
                if(dataFromServer[i] != '\0'){
                    fileNames += dataFromServer[i];
                }else{
                    cout << fileNames << std::endl;
                    fileNames = "";
                }
            }
            createACK(recievedCounter);
            dataFromServer.clear();
            if (packetSize<512) {
                iswaitingForDir = false;
                recievedCounter=1;
            }
            else{
                recievedCounter++;
                cout<<"waiting for another dir msg"<<endl;
            }

        }
        else if (isRecevingData){
            if(isItFirstPacket){
                recievedCounter=1;
                isItFirstPacket = false;
                outputFile.open(recSendFilename);
                cout<<"recieving new file in the folder, name:"<<recSendFilename<<endl;

            }

            string s="";
            for (int i = 0; i < packetSize; i++) {
                s+=(char)dataFromServer[i];
                outputFile << dataFromServer[i];
            }
            cout<<"file is:"<<s<<endl;
            createACK(recievedCounter);
            recievedCounter++;
            if(packetSize < 512){
                outputFile.close();
                isRecevingData=false;
                recievedCounter=1;
                cout<< "RRQ " << recSendFilename << " complete" << endl;
            }

            dataFromServer.clear();

        }else{
            cout<< "Problem with process the data" << endl;

        }

    }else if(currentOpcode == 4){   //Acknowledgment
        if(iswaitingForDisc){
            shouldterminate=true;
        }
        else  if(isSendingData) {
            /*
             *  size_t outputDatalength;
                int totalNumberOfBlocksToSend;
                int blockesSent;
                char* oData;
             */

            if (isItFirstPacket) {
                isItFirstPacket = false;
                std::ifstream checkFile(recSendFilename);
                if (checkFile.good()){
                    inFile.open(recSendFilename, ios::in | ios::binary | ios::ate);
                    inFile.seekg(0, ios::end); // set the pointer to the end
                    outputDatalength = inFile.tellg(); // get the length of the file
                    cout << "Size of file: " << outputDatalength;
                    totalNumberOfBlocksToSend = (outputDatalength / 512) + 1;
                    blockesSent = 0;

                    inFile.seekg(0, ios::beg); // set the pointer to the beginning
                    oData = new char[outputDatalength];
                    inFile.read(oData, outputDatalength); //now all the file is in the oData.
                    inFile.close();
                    continueSend=true;
                }
                else {
                    createSmallMsg(11);
                    continueSend=false;
                    serverMsgIsReady=true;
                }


            }
            if (continueSend) {
                int bytesLeft = outputDatalength - (ackBlock * 512);
                int thisDataSize;
                if (bytesLeft > 512) {
                    outputToServer = new char[518];
                    thisDataSize = 512;
                } else {
                    outputToServer = new char[bytesLeft + 6];
                    thisDataSize = bytesLeft;
                }
                //set size of output a array;
                size_t startIndex = 512 * blockesSent;
                int counter = 6;


                for (size_t i = startIndex; i < startIndex + thisDataSize; i++) {
                    outputToServer[counter] = oData[i];
                }
                createDataPacket(blockesSent + 1, thisDataSize);
                if (thisDataSize < 512) {
                    isSendingData = false;
                    blockesSent = 0;
                    //TODO:need to delete oData.
                } else {
                    blockesSent++;
                }

            }

        }

    }else if(currentOpcode == 5){   //Error
        if(iswaitingForDisc){
            createSmallMsg(10);
            serverMsgIsReady=true;
        }
        else
            serverMsgIsReady=false;
        iswaitingForDisc = false;
        isSendingData = false;
        isRecevingData = false;
//        iswaitingForAck = false;
//        iswaitingForData = false;
        iswaitingForDir = false;
    }else{  //Broadcast
        //Do noting
    }
}

short BidiMessegeEncoderDecoder::valueOfTwoCells(char *bytesArr, int first, int second) {
    short result = (short)((bytesArr[first] & 0xff) << 8);
    result += (short)(bytesArr[second] & 0xff);
    return result;
}


short BidiMessegeEncoderDecoder::getShort(){
    char numInBytes[2];
    _chandler->getBytes(numInBytes,2);

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


//info is
void BidiMessegeEncoderDecoder::createDataPacket (short blockNum, short packetSize){
    messegeSize=6+packetSize;
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
    serverMsgIsReady=true;
}

bool BidiMessegeEncoderDecoder::shouldTerminate (){
    return shouldterminate;
}

bool BidiMessegeEncoderDecoder::keyboardShouldTerminate(){
    return (keyboardTerminate);
}

bool BidiMessegeEncoderDecoder::serverMessegeIsReady() {
    return (serverMsgIsReady);
}

/*
char* readFileBytes(const char *name)
{
    char* ret;
    string s="config1.txt";
    char* c=new char[11];
    for (int i=0;i<11;i++){
        c[i]=s.at(i);
    }

    ifstream fl(c);

    if (fl.is_open())
        cout << "opened" << endl;
    else
        cout<<"not opened"<<endl;

        fl.seekg( 0, ios::end );
        size_t len = fl.tellg();
        ret = new char[len];
        fl.seekg(0, ios::beg);
        fl.read(ret, len);
        fl.close();
    return ret;
}

void writefile(){

    ofstream stream;
    char charArray[] = "Some stuff in a char array.";
    string s ="secondURL.txt";
    stream.open(s);
    if( !stream )
        cout << "Opening file failed" << endl;
    // use operator<< for clarity
    stream << charArray << endl;
    // test if write was succesful - not *really* necessary
    if( !stream )
        cout << "Write failed" << endl;
    stream.close();

}

void secondfile(){
    ofstream ofs;
    ofs.open( "./secondURL.txt");
    char charArray[] = "Some stuff in a char array.";

    ofs.write( (char*)charArray, 13 );
    ofs.close();

}

*/