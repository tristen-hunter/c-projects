#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

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

  // 1.1 open port 8080 after ending program
  int opt = 1;

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
  {
    perror("setsockopt");
    close(server_fd);
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

  printf("Listening on port 8080...\n");

  // 4. accept the connection (just 1) 
  int client_fd = accept(server_fd, NULL, NULL);

  if (client_fd == -1){
    perror("socket");
    close(server_fd);
    return 1;
  }

  printf("Client connected!\n");


  // 5. read the client request
  char buffer[4096];

  ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

  if (bytes_read == -1)
  {
    perror("read");
    close(client_fd);
    close(server_fd);
    return 1;
  }

  buffer[bytes_read] = '\0';

  // printf("\nRequest recieved:\n\n %s", buffer);


  // 6. parsing
  char method[16];
  char path[256];
  char version[16];

  sscanf(buffer, "%15s %255s %15s", method, path, version);

  printf("Method: %s\n", method);
  printf("Path: %s\n", path);
  printf("Version: %s\n", version);


  // 7. bring file into memory
  FILE *index_p = fopen("index.html", "r");

  if (index_p == NULL)
  {
    perror("fopen");
    close(server_fd);
    close(client_fd);
    return 1;
  }

  fseek(index_p, 0, SEEK_END);
  long file_size = ftell(index_p);
  fseek(index_p, 0, SEEK_SET);

  char *body = malloc(file_size + 1);

  fread(body, 1, file_size, index_p);
  body[file_size] = '\0';

  fclose(index_p);

  // 8. Two part response (header & body)
  char response[1024];

  int response_size = snprintf(
    response, 
    sizeof(response), 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: %ld\r\n"
    "\r\n",    
    file_size
  );

  //9. Send response
  ssize_t bytes_sent = write(client_fd, response, response_size);

  if (bytes_sent == -1)
  {
      perror("write");
      free(body);
      close(client_fd);
      close(server_fd);
      return 1;
  }

  bytes_sent = write(client_fd, body, file_size);

  if (bytes_sent == -1)
  {
      perror("write");
      free(body);
      close(client_fd);
      close(server_fd);
      return 1;
  }

  free(body);
  close(client_fd);
  close(server_fd);

  return 0;
}
