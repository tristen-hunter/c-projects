// Setup phase (once):
  // 1.1 Create a socket → get a file descriptor for it
  // 1.2 Set an option so you can restart the server quickly without "address already in use" errors
  // 1.3 Bind that socket to an address + port — this is you claiming "I own port 8080 on this machine"
  // 1.4 Listen on it — this turns the socket into one that can accept incoming connections, and sets a backlog queue size

// Loop phase (repeats):
  // 5. Accept — this blocks until a client connects, 
     // then hands you a new, separate socket just for talking to 
     // that one client (your original listening socket stays free to accept more later)
  // 6. Read the request off the new connection socket
  // 7. Write your HTTP response back
  // 8. Close the connection socket
  // 9. (loop back to accept — but for now, just exit)

#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 1



int main(void)
{
  // 1. create the listening socket (internet socket)
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_fd == -1) 
  {
    perror("socket");
    return 1;
  }

  // 2. bind to port 8080
  struct sockaddr_in address;

  address.sin_family = AF_INET; // IPv4
  address.sin_addr.s_addr = INADDR_ANY; // 4 byte internet address
  address.sin_port = htons(8080); // port number
  
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
  {
    perror("bind");
    close(server_fd);
    return 1;
  }

  // 3. listen on port 8080 for a connection request
  if (listen(server_fd, BACKLOG) == -1) 
  {
    perror("listen");
    close(server_fd);
    return 1;
  }

  return 0;
}
