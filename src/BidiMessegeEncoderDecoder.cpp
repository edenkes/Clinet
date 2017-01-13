#include "../include/BidiMessegeEncoderDecoder.h"//
// Created by rotem on 07/01/17.
//

#include "../include/BidiMessegeEncoderDecoder.h"

BidiMessegeEncoderDecoder::BidiMessegeEncoderDecoder() {
std::cout<<"BidiEncoderDecoder constructor"<< std::endl;


}

BidiMessegeEncoderDecoder::~BidiMessegeEncoderDecoder() {

}


Packet* BidiMessegeEncoderDecoder::decodeNextByte(char nextChar) {
    Packet* res;



    return res;
}

void BidiMessegeEncoderDecoder::pushChar(char nextChar) {
    chars.push_back(nextChar);
    length++;
}

char* BidiMessegeEncoderDecoder::encode(char* messege) {
    std::string userInput(messege);
    std::string command(userInput.substr(0,userInput.find(" ")));
    std::string check("hello");
    unsigned int spaceIndex=userInput.find(" ");
    std::cout <<"user input is:"<<userInput<< std::endl;
    std::cout <<"command is:"<<command<< std::endl;
    std::cout <<command.compare("hello");


    if (userInput.find("RRQ") != std::string::npos) {
        std::cout << "found RRQ!" << '\n';
    }
    else if (userInput.find("WRQ") != std::string::npos) {
        std::cout << "found WRQ!" << '\n';
    }
    else if (userInput.find("DATA") != std::string::npos) {
        std::cout << "found DATA!" << '\n';
    }
    else if (userInput.find("ACK") != std::string::npos) {
        std::cout << "found ACK!" << '\n';
    }
    else if (userInput.find("Error") != std::string::npos) {
        std::cout << "found Error!" << '\n';
    }
    else if (userInput.find("DIRQ") != std::string::npos) {
        std::cout << "found DIRQ!" << '\n';
    }
    else if (userInput.find("LOGRQ") != std::string::npos) {
        std::cout << "found LOGRQ!" << '\n';
        //setBytesOpcode((short)7);
        std::string userName=(userInput.substr(spaceIndex+1));
        std::cout<<"username:"<<userName<<std::endl;
        //use c_str();



    }
    else if (userInput.find("DELRQ") != std::string::npos) {
        std::cout << "found DELRQ!" << '\n';
    }
    else  if (userInput.find("BCAST") != std::string::npos) {
        std::cout << "found BCAST!" << '\n';
    }
    else  if (userInput.find("DISC") != std::string::npos) {
        std::cout << "found DISC!" << '\n';
    }


    //std::cout<< (userInput.find("LOGRQ"));


    return bytes;



}
Packet BidiMessegeEncoderDecoder::decode(char *bytesArr) {

}
void BidiMessegeEncoderDecoder::setOpCode() {
    opcode=bytesToShort(bytes);
}

void BidiMessegeEncoderDecoder::setBytesOpcode(short num){
    shortToBytes(num,bytes);
}
void BidiMessegeEncoderDecoder::initDecode() {
    length=0;
    zeroInTheEnd=false;
    opcode=0;


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
void BidiMessegeEncoderDecoder::shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}