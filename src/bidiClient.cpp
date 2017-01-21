//
// Created by rotem on 16/01/17.
//

#include <stdlib.h>
#include "../include/connectionHandler.h"
#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "../include/BidiMessegeEncoderDecoder.h"
#include "../include/keyboardInput.h"
#include "../include/serverInput.h"
#include <fstream>
#include <string>
using std::ofstream;


using boost::thread;
using namespace std;




int main (int argc, char *argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    std::cout << "Host: " << host << " Port:" << port << std::endl;
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    BidiMessegeEncoderDecoder encdec(&connectionHandler);

    keyboardInput keyboard(&connectionHandler,&encdec);
    serverInput serverListener(&connectionHandler,&encdec);


    boost::thread th1(boost::bind(&keyboardInput::run,&keyboard));
    boost::thread th2(boost::bind(&serverInput::run,&serverListener));

    th1.join();
    th2.join();

    cout<<"Client is closed"<<endl;


    return 0;
}








 





