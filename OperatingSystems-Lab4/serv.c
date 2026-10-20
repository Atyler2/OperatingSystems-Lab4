#include <netinet/in.h> //structure for storing address information 
#include <stdio.h> 
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/socket.h> //for socket APIs 
#include <sys/types.h> 
#include "list.h"

#define PORT 9001
#define ACK "ACK"

list_t *mylist = NULL;
int servSockD = -1;
int clientSocket = -1;

void handle_sigint(int sig){
  if(mylist) list_free(mylist);
  if (clientSocket >= 0) close(clientSocket);
  if (servSockD >= 0) close(servSockD);
  exit(0);
}
  
int main(int argc, char const* argv[]) 
{ 
  
	  int n, val, idx;
    // create server socket similar to what was done in 
    // client program 
  
    // string store data to recv/send to/from client 
    char buf[1024];
		char sbuf[1024];
    char* token;
    char* str;

    signal(SIGINT, handle_sigint);
    servSockD = socket(AF_INET, SOCK_STREAM, 0); 

    int opt = 1;
    setsockopt(servSockD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // define server address 
    struct sockaddr_in servAddr; 
  
	  // list
		


    servAddr.sin_family = AF_INET; 
    servAddr.sin_port = htons(PORT); 
    servAddr.sin_addr.s_addr = INADDR_ANY; 
  
    // bind socket to the specified IP and port 
    bind(servSockD, (struct sockaddr*)&servAddr, 
         sizeof(servAddr)); 
  
    // listen for connections 
    listen(servSockD, 1); 
  
    // integer to hold client socket. 
    clientSocket = accept(servSockD, NULL, NULL); 

    mylist = list_alloc();  // create the list

    while(1){
        // recvs messages from client socket 
        memset(buf, '\0', sizeof(buf));
        n = recv(clientSocket, buf, sizeof(buf)-1, 0);
				if (n<= 0){
          break;
        }
        buf[n] = '\0';
        
        token = strtok(buf, " ");
        if (token == NULL) continue;
        strcpy(sbuf, "Unknown command");

        if  (strcmp(token, "exit")==0){
          break;
        }
        
				else if(strcmp(token,"get_length") == 0){
					// Make a Call
					val = list_length(mylist);
					sprintf(sbuf,"%s%d", "Length = ", val);
				}
				else if(strcmp(token,"add_front") == 0){
					token = strtok(NULL, " ");  // get next token (value)
					if (token){
          val = atoi(token);
					// Make a Call
					list_add_to_front(mylist,val);
          strcpy(sbuf,ACK);
        }
				
        else{
          strcpy(sbuf, "Error: missing value");
        }
        }
        else if (strcmp(token, "add_back") == 0) {
          token = strtok(NULL, " ");
          if (token){
            val = atoi(token);
            list_add_to_back(mylist, val);
            strcpy(sbuf, ACK);
          }
        else{
          strcpy(sbuf, "Error: missing value");
        }
        }
        else if (strcmp(token, "add_position") == 0){
          char *t1 = strtok(NULL, " ");
          char *t2 = strtok(NULL, " ");
          if (t1 && t2){
            idx = atoi(t1);
            val = atoi(t2);
            list_add_at_index(mylist, val, idx);
            strcpy(sbuf, ACK);
          }
          else{
            strcpy(sbuf, "Error: usage add_position <index> <value>");
          }
        }
        else if (strcmp(token, "remove_back") == 0){
          val = list_remove_from_back(mylist);
          sprintf(sbuf, "%d", val);
        }
        else if (strcmp(token, "remove_front")== 0){
          val = list_remove_from_front(mylist);
          sprintf(sbuf, "%d", val);
        }
        
				else if(strcmp(token,"remove_position") == 0){
					token = strtok(NULL, " ");
					if (token){
            val = atoi(token);
            list_remove_at_index(mylist, val);
            sprintf(sbuf, "%s%d", ACK, val);
          }
          else{
            strcpy(sbuf, "Error: missing index");
          }
				}
        else if (strcmp(token, "get")== 0){
          token = strtok(NULL, " ");
          if (token){
            idx = atoi(token);
            val = list_get_elem_at(mylist, idx);
            sprintf(sbuf, "%d", val);
          }
          else{
            strcpy(sbuf, "Error: missing index");
          }
        }
       
				else if(strcmp(token,"print") == 0){
            str = listToString(mylist);
            snprintf(sbuf, sizeof(sbuf), "%s", str);
            free(str);            
						}
        else if (strcmp(token, "menu") == 0){
          strcpy(sbuf, "OK");
        }
						// ADD THE OTHER OPERATIONS


                // send's messages to client socket 
        send(clientSocket, sbuf, sizeof(sbuf), 0);
        
				
    }
    list_free(mylist);
    mylist = NULL;
    close(clientSocket);
    close(servSockD);
    return 0; 
}
