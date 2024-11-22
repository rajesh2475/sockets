#include <stdio.h>         // For input/output functions like printf()
#include <stdlib.h>        // For general utility functions like exit()
#include <sys/types.h>     // For socket-related data types
#include <sys/socket.h>    // For socket functions (socket(), bind(), listen(), accept())
#include <netinet/in.h>    // For sockaddr_in structure and INADDR_ANY


int main(){

    /*
        What it does: Declares a character array server_message to store the message that the server will send to the client.
        Why is this needed? The server needs a message buffer to send data to the client.
    */
    char server_message[256] = "Message from server";

    /*
        What it does:
            Creates a socket for the server using the socket() function.
            server_socket holds the file descriptor for the created socket.
        Parameters of socket():
            AF_INET: IPv4 address family.
            SOCK_STREAM: Specifies TCP (reliable, connection-based communication).
            0: Automatically selects the TCP protocol.
        Why is this needed? The server uses this socket to communicate with clients.
    */
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // What it does: Declares a structure server_address of type sockaddr_in to store the server's IP address and port.
    struct sockaddr_in server_address;
    // What it does: Sets the address family for the server to IPv4 (AF_INET).
    server_address.sin_family = AF_INET;
    // What it does: Sets the port number for the server to 9602 and converts it to network byte order using htons().
    server_address.sin_port = htons(9602);
    // What it does: Sets the server's IP address to INADDR_ANY, which means the server will accept connections on any available network interface.
    server_address.sin_addr.s_addr = INADDR_ANY;

    /*
        What it does:
            Binds the server socket to the specified IP address and port (server_address).
        Parameters:
            server_socket: The socket to bind.
            (struct sockaddr *) &server_address: Pointer to the address structure.
            sizeof(server_address): Size of the server_address structure.
        Why is this needed? Binding links the server socket to the specified IP and port, making it ready to listen for connections.
    */
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0){
        perror("Bind failed");
        exit(1);
    }

    /*
        What it does:
            Puts the server socket into listening mode, allowing it to accept incoming client connections.
        Parameters:
            server_socket: The socket to listen on.
            5: The backlog, which specifies the maximum number of pending connections the socket can handle.
            Why is this needed? Listening allows the server to handle incoming client connections.
    */
    if (listen(server_socket, 5) < 0){
        perror("Listen failed");
        exit(1);
    }

    /*
        What it does:
            Accepts an incoming client connection on the server socket.
        Parameters:
            server_socket: The listening socket.
            NULL: No specific client address structure is needed here.
            NULL: No specific length is needed for the client address.
        Return Value:
            Returns a new socket (client_socket) for communicating with the connected client.
        Why is this needed? The accept() function establishes a connection with a client and creates a new socket specifically for that client.
    */
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    /*
        What it does:
            Sends the server_message to the connected client through client_socket.
        Parameters:
            client_socket: The socket for the client connection.
            server_message: Pointer to the message buffer.
            sizeof(server_message): Size of the message buffer.
            0: No special flags are used.
        Why is this needed? This sends the specified message to the client.
    */
    /*
        Flag	            Function	Effect
        MSG_CONFIRM	        send()	    Confirms peer reachability (mostly for connectionless protocols like UDP).
        MSG_DONTWAIT	    Both	    Makes the call non-blocking.
        MSG_EOR	            send()	    Marks the end of a record.
        MSG_MORE	        send()	    Delays transmission for packet optimization.
        MSG_NOSIGNAL	    send()	    Prevents SIGPIPE when the connection is broken.
        MSG_PEEK	        recv()	    Allows peeking at data without consuming it.
        MSG_WAITALL	        recv()	    Blocks until the requested number of bytes is received.
        MSG_TRUNC	        recv()	    Allows receiving truncated data when the buffer is smaller than the incoming data.
        MSG_ERRQUEUE	    recv()	    Retrieves error messages from the socket's error queue.
        MSG_CMSG_CLOEXEC	recv()	    Ensures received file descriptors are not inherited by child processes during exec() calls.
    */
    send(client_socket, server_message, sizeof(server_message), 0);

    close(server_socket);
    return 0;
}