//
// Created by rotem on 07/01/17.
//

#ifndef BOOST_ECHO_CLIENT_PACKET_H
#define BOOST_ECHO_CLIENT_PACKET_H
#include <string>

class Packet {
private:
    short opcode;
public:
    short getOpcode();
};


class RRQPacket : public Packet {
private:

public:

};

class WRQPacket : public Packet {
private:
public:

};

class DataPacket : public Packet {
private:
public:

};

class ACKPacket : public Packet {
private:
public:

};

class ErrorPacket : public Packet {
private:
public:

};

class DIRPacket : public Packet {

public:

};

class LoginPacket : public Packet {
private:
public:

};

class DeletePacket : public Packet {
private:
public:

};

class BCASTPacket : public Packet {

public:

};
class DISCPacket : public Packet {

public:

};



#endif //BOOST_ECHO_CLIENT_PACKET_H
