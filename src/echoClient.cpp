#include <stdlib.h>
#include "../include/connectionHandler.h"
#include "../include/BidiMessegeEncoderDecoder.h"

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/

int main (int argc, char *argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << "192.168.2.112" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    std::cout << "Host: " << host << " Port:" <<port << std::endl;
    ConnectionHandler connectionHandler(host, port);
    ConnectionHandler* _ch=&connectionHandler;
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
	BidiMessegeEncoderDecoder* encdec=new BidiMessegeEncoderDecoder(*_ch);
	//From here we will see the rest of the ehco client implementation:
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cout << "waiting for user input\n" << std::endl;
        std::cin.getline(buf, bufsize);
        encdec->encode(buf);
        char* msgToSend=encdec->getEncodedMsg();
        //now need to convert the user input to the format for the server (using encoderDevoder).
		int len=encdec->getMsgSize();
       // std::cout << "length:\n" << len <<std::endl;
        if (!connectionHandler.sendBytes(msgToSend,len)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        //std::cout << "Sent " << len+1 << " bytes to server" << std::endl;


        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character

        char opcodeArr[2];
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler.getBytes(opcodeArr,2))  {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        short opc=(encdec->bytesToShort(opcodeArr));
        cout<<"opcode from server:"<<opc<<endl;
        //need to handle BCAST, DATA, DISC, ACK.
        encdec->decode(opc);


        //len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        //answer.resize(len-1);
        /*
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
         */
    }
    return 0;

}