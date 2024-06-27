//#include "tcp_sponge_socket.hh"
#include "tcp_sponge_socket.hh"
#include "util.hh"

#include <cstdlib>
#include <iostream>

using namespace std;

/// @brief Apply for resources from host's path
/// @param host host address
/// @param path resources path
void get_URL(const string &host, const string &path) {
    //TODO:Lab0
    // Your code here.

    // You will need to connect to the "http" service on
    // the computer whose name is in the "host" string,
    // then request the URL path given in the "path" string.

    // Then you'll need to print out everything the server sends back,
    // (not just one call to read() -- everything) until you reach
    // the "eof" (end of file).
    
    //init socket 
    TCPSocket socket{};
    //connect socket to a specified peer address
    //Address' construction function requires a socketaddr pointer #*addr and a size
    //The source funtion locates at libsponge/util/address.cc
    socket.connect(Address(host,"http"));

    //The two following lines write in the head of a http request, second one has "Connection: Close", 
    //which means close connection immediately after the server response, avoiding waste of resouces

    //socket.write("GET "+path+" HTTP/1.1\r\nHost: "+host+"\r\n\r\n");
    socket.write("GET "+path+" HTTP/1.1\r\nHost: "+host+"\r\nConnection: close\r\n\r\n");
    socket.shutdown(SHUT_WR);

    while(!socket.eof())
    {
        cout<<socket.read();
    }
    socket.close();

    cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
    cerr << "Warning: get_URL() has not been implemented yet.\n";

    return;

    // FullStackSocket socket;
    // socket.connect(Address(host, "http"));
    // string message;
    // message += "GET " + path + " HTTP/1.1\r\n";
    // message += "Host: " + host + "\r\n";
    // message += "Connection: close\r\n\r\n";
    // socket.write(message);
    // while (!socket.eof()) {
    //     cout << socket.read();
    // }
    // socket.wait_until_closed();
    // cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
    // cerr << "Warning: get_URL() has not been implemented yet.\n";
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 0) {
            abort();  // For sticklers: don't try to access argv[0] if argc <= 0.
        }

        // The program takes two command-line arguments: the hostname and "path" part of the URL.
        // Print the usage message unless there are these two arguments (plus the program name
        // itself, so arg count = 3 in total).
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " HOST PATH\n";
            cerr << "\tExample: " << argv[0] << " stanford.edu /class/cs144\n";
            return EXIT_FAILURE;
        }

        // Get the command-line arguments.
        const string host = argv[1];
        const string path = argv[2];

        // Call the student-written function.
        get_URL(host, path);
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
