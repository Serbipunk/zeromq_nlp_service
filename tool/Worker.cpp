//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>

#include "cppMSGmodule.hpp"

#include "TC_process.h"

#include <string>
#include "titlebook.pb.h"

using namespace std;

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    CateTeller ct;
 
    while(true) {
        //// get Request from Python Client
        zmq::message_t request;
        //  Wait for next request from client
        socket.recv (&request);
        // std::cout << "Received Request" << std::endl;
        std::string req_str = std::string (static_cast<char*>(request.data()), request.size());
        std::cout << "Received:\n  " << req_str << std::endl;

        // parse string to char* array
        char** pca;
        int count;
        if( CppMsgModule::msgStrToPcharArray(pca, count, req_str) ) {
            for(int i=0; i<count; ++i) {
                cout << i << "  " << pca[i] << endl;
            }
        }
        else {
            cerr << "cannot parse form string" << endl;
            return -1;
        }
        int* pid = new int [count];
        for(int i=0; i<count; ++i) {
            pid[i] = 0;
        }

        //// NLP module
        ct.tell(pca, count, pid);


        ////  send Reply to Python Client
        // encode id_array to msgstr
        string out_msg;
        if( CppMsgModule::idArrayToMsgStr(out_msg, pid, count) ) {
            cout << out_msg << endl;
        }
        else {
            cerr << "cannot serialize object" << endl;
            return -1;
        }
        std::string server_rep = out_msg;
        zmq::message_t reply (server_rep.length());
        memcpy (reply.data (), server_rep.c_str(), server_rep.length());

        socket.send (reply);


        // do some cleanup
        for(int i=0; i<count; ++i) {
            delete [] pca[i];
        }
        delete [] pca;
        delete [] pid;
    }

    return 0;
}
