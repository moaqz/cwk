#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_LENGTH 512
#define PORT 4000

char *to_uppercase(char buff[BUFFER_LENGTH])
{
  int i = 0, j = 0;

  while (buff[i] != '\0')
  {
    i++;
  }

  char *message = (char *)malloc(sizeof(char) * (i + 1));
  if (message == NULL)
  {
    return NULL;
  }

  while (j < i)
  {
    if (buff[j] >= 'a' && buff[j] <= 'z')
    {
      message[j] = buff[j] - 32;
    }
    else
    {
      message[j] = buff[j];
    }

    j++;
  }

  message[j] = '\0';
  return message;
}

/**
 * C Implementation of the UDP Server from the book 'Computer Networking: A Top-Down Approach'
 */
int main()
{
  int sfd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_size = sizeof(client_addr);
  char buf[BUFFER_LENGTH];

  if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
  {
    exit(EXIT_FAILURE);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
  {
    exit(EXIT_FAILURE);
  };

  while (1)
  {
    printf("Waiting for data...\n");
    memset(buf, 0, BUFFER_LENGTH);
    
    int bsize = recvfrom(sfd, buf, BUFFER_LENGTH, 0, (struct sockaddr *)&client_addr, &client_addr_size);
    if (bsize == -1)
    {
      continue;
    }

    printf("⇝ Received %d bytes from %d - Message: %s", bsize, ntohs(client_addr.sin_port), buf);

    char *message = to_uppercase(buf);
    if (message != NULL)
    {
      sendto(sfd, message, strlen(message), 0, (struct sockaddr *)&client_addr, client_addr_size);
      free(message);
    }
  }

  close(sfd);
  return 0;
}
