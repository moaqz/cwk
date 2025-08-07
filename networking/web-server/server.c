#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int setup_server(int port);

int main(int argc, char *argv[])
{
  int port;

  if (argc != 2)
  {
    printf("Usage: %s <port>\n", argv[0]);
    exit(EXIT_SUCCESS);
  }
  else
  {
    port = atoi(argv[1]);
  }

  int sfd = setup_server(port);
  if (sfd == -1)
  {
    exit(EXIT_FAILURE);
  }

  printf("SERVER INFO: TCP server listening in port %d...\n", port);
  printf("SERVER INFO: Waiting for connections...\n");
  while (1)
  {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    client_addr.sin_family = AF_INET;

    int cfd = accept(sfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (cfd == -1)
    {
      perror("SERVER ERROR: socket accept error");
      continue;
    }

    const char *message = "OK\n";
    int b;
    if ((b = send(cfd, message, strlen(message), 0)) == -1)
    {
      perror("SERVER ERROR: Sending message to client");
    };

    close(cfd);
    printf("SERVER INFO: Client socket closed\n");
  }

  close(sfd);
  return EXIT_SUCCESS;
}

int setup_server(int port)
{
  int sfd;
  struct sockaddr_in server_addr;

  server_addr.sin_port = htons(port);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    return -1;
  };

  if (bind(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
  {
    perror("SERVER ERROR: socket bind error");
    close(sfd);
    return -1;
  }

  if (listen(sfd, 10) == -1)
  {
    perror("SERVER ERROR: socket listen");
    close(sfd);
    return -1;
  };

  return sfd;
}
