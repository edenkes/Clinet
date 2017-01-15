#include "../include/BidiMessegeEncoderDecoder.h"//
// Created by rotem on 07/01/17.
//

#include "../include/BidiMessegeEncoderDecoder.h"

BidiMessegeEncoderDecoder::BidiMessegeEncoderDecoder() {

    std::cout<<"BidiEncoderDecoder constructor"<< std::endl;
    opcodeInBytes=new char[2];


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
    char* ans;
    int ansLength=0;
    short msgOpcode;
    int counter;
    std::string command(userInput.substr(0,userInput.find(" ")));
    unsigned int spaceIndex=userInput.find(" ");
    std::cout <<"user input is:"<<userInput<< std::endl;
    std::cout <<"command is:"<<command<< std::endl;



    if (userInput.find("RRQ") != std::string::npos) {
        std::cout << "found RRQ!" << '\n';
        msgOpcode=1;
        setBytesOpcode(msgOpcode);
        //std::cout<<"user input:"<<userInput<<" space index:"<<spaceIndex<<std::endl;
        std::string fileName=(userInput.substr(spaceIndex+1));
        //std::cout<<"username:"<<userName<<std::endl;
        ansLength=2+fileName.size()+1;
        ans=new char[ansLength];
        ans[0]=opcodeInBytes[0];
        ans[1]=opcodeInBytes[1];
        for (int i=0;i<fileName.size();i++ ){
            ans[i+2]=fileName[i];
        }
        std::cout<<std::endl;
        ans[ansLength-1]='0'; //zero in the end
        for (int i=0;i<ansLength;i++ ){
            std::cout<<" "<<(short)ans[i];
        }
    }
    else if (userInput.find("WRQ") != std::string::npos) {
        std::cout << "found WRQ!" << '\n';
        msgOpcode=2;
        setBytesOpcode(msgOpcode);
        //std::cout<<"user input:"<<userInput<<" space index:"<<spaceIndex<<std::endl;
        std::string fileName=(userInput.substr(spaceIndex+1));
        //std::cout<<"username:"<<userName<<std::endl;
        ansLength=2+fileName.size()+1;
        ans=new char[ansLength];
        ans[0]=opcodeInBytes[0];
        ans[1]=opcodeInBytes[1];
        for (int i=0;i<fileName.size();i++ ){
            ans[i+2]=fileName[i];
        }
        std::cout<<std::endl;
        ans[ansLength-1]='0'; //zero in the end
        for (int i=0;i<ansLength;i++ ){
            std::cout<<" "<<(short)ans[i];
        }

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
        msgOpcode=6;
        setBytesOpcode(msgOpcode);
        //std::cout<<"user input:"<<userInput<<" space index:"<<spaceIndex<<std::endl;
        //std::cout<<"username:"<<userName<<std::endl;
        ansLength=2;
        ans=new char[ansLength];
        ans[0]=opcodeInBytes[0];
        ans[1]=opcodeInBytes[1];
    }
    else if (userInput.find("LOGRQ") != std::string::npos) {
        std::cout << "found LOGRQ!" << '\n';
        msgOpcode=7;
        setBytesOpcode(msgOpcode);
        //std::cout<<"user input:"<<userInput<<" space index:"<<spaceIndex<<std::endl;
        std::string userName=(userInput.substr(spaceIndex+1));
        //std::cout<<"username:"<<userName<<std::endl;
        ansLength=2+userName.size()+1;
        ans=new char[ansLength];
        ans[0]=opcodeInBytes[0];
        ans[1]=opcodeInBytes[1];
        for (int i=0;i<userName.size();i++ ){
            ans[i+2]=userName[i];
        }
        std::cout<<std::endl;
        ans[ansLength-1]='0'; //zero in the end
        for (int i=0;i<ansLength;i++ ){
            std::cout<<" "<<(short)ans[i];
        }
        return ans;




// Or . . .
     //   for (int n = 0; n != wordString.end(); n++)
      //  {
      //      cout << wordString[n] << endl;
      //  }

    }
    else if (userInput.find("DELRQ") != std::string::npos) {
        std::cout << "found DELRQ!" << '\n';
        msgOpcode=8;
        setBytesOpcode(msgOpcode);
        //std::cout<<"user input:"<<userInput<<" space index:"<<spaceIndex<<std::endl;
        std::string fileName=(userInput.substr(spaceIndex+1));
        //std::cout<<"username:"<<userName<<std::endl;
        ansLength=2+fileName.size()+1;
        ans=new char[ansLength];
        ans[0]=opcodeInBytes[0];
        ans[1]=opcodeInBytes[1];
        for (int i=0;i<fileName.size();i++ ){
            ans[i+2]=fileName[i];
        }

        std::cout<<std::endl;
        ans[ansLength-1]='0'; //zero in the end
        for (int i=0;i<ansLength;i++ ){
            std::cout<<" "<<(short)ans[i];
        }

    }
    else  if (userInput.find("BCAST") != std::string::npos) {
        std::cout << "found BCAST!, will creat a bad packet" << '\n';
        msgOpcode=11;
        setBytesOpcode(msgOpcode);
        //std::cout<<"user input:"<<userInput<<" space index:"<<spaceIndex<<std::endl;
        //std::cout<<"username:"<<userName<<std::endl;
        ansLength=2;
        ans=new char[ansLength];
        ans[0]=opcodeInBytes[0];
        ans[1]=opcodeInBytes[1];
    }
    else  if (userInput.find("DISC") != std::string::npos) {
        std::cout << "found DISC!" << '\n';
        msgOpcode=10;
        setBytesOpcode(msgOpcode);
        //std::cout<<"user input:"<<userInput<<" space index:"<<spaceIndex<<std::endl;
        //std::cout<<"username:"<<userName<<std::endl;
        ansLength=2;
        ans=new char[ansLength];
        ans[0]=opcodeInBytes[0];
        ans[1]=opcodeInBytes[1];

    }
    else {
        std::cout << "need to create BAD packet" << '\n';
        msgOpcode=11;
        setBytesOpcode(msgOpcode);
        //std::cout<<"user input:"<<userInput<<" space index:"<<spaceIndex<<std::endl;
        //std::cout<<"username:"<<userName<<std::endl;
        ansLength=2;
        ans=new char[ansLength];
        ans[0]=opcodeInBytes[0];
        ans[1]=opcodeInBytes[1];
    }



    //std::cout<< (userInput.find("LOGRQ"));

    std::cout<<"finished encode, ans size:"<<std::endl;
    return ans;



}
Packet BidiMessegeEncoderDecoder::decode(char *bytesArr) {


}
void BidiMessegeEncoderDecoder::setOpCode() {
    opcode=bytesToShort(bytes);
}

void BidiMessegeEncoderDecoder::setBytesOpcode(short num ){
    shortToBytes(num,opcodeInBytes);
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
void BidiMessegeEncoderDecoder::shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

char* BidiMessegeEncoderDecoder::concat(std::vector<char*> &arrays)
{

}




