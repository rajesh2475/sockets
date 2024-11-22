// Basic TCP client, will print out any data that we get from an remote connection


// stdio.h is used for functions like printf() and scanf().
#include <stdio.h>
// stdlib.h provides memory management (malloc, free) and other utility functions like exit().
#include <stdlib.h>

// sys/types.h: Defines data types like size_t and socklen_t used in socket operations.
#include <sys/types.h>

/* sys/socket.h: Contains the main socket API used for creating and managing sockets 
(e.g., socket(), bind(), connect(), etc.). */
#include <sys/socket.h>

/* Provides structures and constants specific to Internet Protocol (IP) addresses, 
like sockaddr_in, which is used to store address information for IPv4.*/
#include <netinet/in.h>

int main(){
    // Declares an integer variable network_socket. 
    // This will hold the file descriptor (a unique ID) of the created socket.
    int network_socket;

    /* 
        AF_INET:
            Meaning: Address Family for IPv4 (Internet Protocol version 4).
            Why use it? Tells the socket to work with IPv4 addresses (like 127.0.0.1 or 192.168.1.1).

        SOCK_STREAM:
            Meaning: Specifies the type of socket, in this case, a TCP (Transmission Control Protocol) socket.
            Why use it? TCP provides reliable, connection-oriented communication between devices. If you need a UDP (datagram-based) socket, you'd use SOCK_DGRAM.    
    
        0:
            Meaning: Protocol type, defaulted to 0 for most cases.
            Why use it? Since AF_INET and SOCK_STREAM already imply TCP, 0 lets the system automatically select the appropriate protocol. You could also explicitly specify IPPROTO_TCP for TCP.
    */

    /* 
        socket() creates an endpoint for communication and returns a file descriptor.
            - AF_INET: Address family for IPv4.
            - SOCK_STREAM: Use TCP (reliable connection).
            - 0: Automatically selects the TCP protocol.
    */
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify the address for the socket
    /*
        What it does: Declares a structure variable server_address of type sockaddr_in.
        What is sockaddr_in?
            It is a structure defined in <netinet/in.h> that is used to specify the address and port information for IPv4 sockets.
        Fields in sockaddr_in:
            sin_family: Address family (e.g., AF_INET for IPv4).
            sin_port: Port number in network byte order.
            sin_addr: The IP address.

    */
    struct sockaddr_in server_address;
    /*
        What it does: Sets the address family to AF_INET (IPv4).
        Why is this needed?
            The sin_family field tells the socket that it will use IPv4 addresses.
        Header involved: <netinet/in.h>
    */
    server_address.sin_family = AF_INET;
    /*
        What it does: Assigns the port number 9602 to the sin_port field in network byte order.
        What is htons()?
            htons() stands for host-to-network short. It converts a 16-bit integer (the port number) from the host's byte order (little-endian) to the network byte order (big-endian), which is required for communication over a network.
            Header involved: <arpa/inet.h>
        Why is this needed?
            Systems may use different internal byte orders (little-endian vs. big-endian), but the network expects data in big-endian. htons() ensures compatibility.
    */
    server_address.sin_port = htons(9602);
    /*
        What it does: Sets the s_addr field of sin_addr to INADDR_ANY.
        What is INADDR_ANY?
            It is a constant that tells the socket to accept connections from any IP address on the local machine (e.g., 0.0.0.0).
            Header involved: <netinet/in.h>
        Why is this needed?
            When you’re setting up a client or server, using INADDR_ANY makes it flexible to bind to any available network interface.
    */
    server_address.sin_addr.s_addr = INADDR_ANY;
    /*
        What it does: Attempts to connect the client socket (network_socket) to the server specified by server_address.
        Breakdown of the connect() function:
            Parameters:
                network_socket: The socket file descriptor created earlier using socket().
                (struct sockaddr *) &server_address: The address of the server (typecast to struct sockaddr *, as required by the connect() function).
                sizeof(server_address): The size of the server_address structure.
                Return value:
                    Returns 0 if the connection is successful.
                    Returns -1 if the connection fails (and sets errno to indicate the error).
        Header involved: <sys/socket.h>
        Why is this needed?
            connect() establishes a connection between the client socket and the server at the specified IP address and port.
    */
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_status < 0){
        printf("Failed to connect to server");
    }

        // Summary of Important Functions and Headers
        // Function/Structure	Purpose	Header
        // socket()	Creates a socket	<sys/socket.h>
        // connect()	Connects the client socket to a server	<sys/socket.h>
        // htons()	Converts host byte order to network byte order	<arpa/inet.h>
        // sockaddr_in	Stores address and port information for IPv4	<netinet/in.h>
        // INADDR_ANY	Binds to any available network interface	<netinet/in.h>
        // printf()	Prints error messages or logs	<stdio.h>/

    // receive data form server
    /*
        What it does: Declares a character array server_response with a size of 256 bytes to store the data received from the server.
        Why is this needed?
            The recv() function requires a buffer to store the incoming data from the server.
        server_response is where the data will be written.
            recv(network_socket, &server_response, sizeof(server_response), 0);
        What it does: Receives data from the server through the socket network_socket and stores it in the server_response array.

        Breakdown of the recv() function:

        Prototype:
            size_t recv(int sockfd, void *buf, size_t len, int flags);
                sockfd: The socket file descriptor (network_socket) through which the data is received.
                buf: A pointer to the buffer where the received data will be stored. Here, it is &server_response.
                len: The size of the buffer, specified as sizeof(server_response) (256 bytes in this case).
                flags: Optional flags for modifying the behavior of the recv() call. A value of 0 means "no special behavior."
            Return Value:

        If successful, recv() returns the number of bytes received (≥ 0).
        If it fails, it returns -1 and sets errno to indicate the error.
        Header involved: <sys/socket.h> for the recv() function.
    */
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    printf("The server_response is %s", server_response);

    close(network_socket);


    return 0;
}
