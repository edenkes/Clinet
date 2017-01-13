#include "../include/BidiMessegeEncoderDecoder.h"//
// Created by rotem on 07/01/17.
//

#include "../include/BidiMessegeEncoderDecoder.h"

BidiMessegeEncoderDecoder::BidiMessegeEncoderDecoder() {
    bytes=chars.data();


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

char* BidiMessegeEncoderDecoder::encode(Packet messege) {

}
Packet BidiMessegeEncoderDecoder::decode(char *bytesArr) {

}
void BidiMessegeEncoderDecoder::setOpCode() {
    opcode=bytesToShort(bytes);
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