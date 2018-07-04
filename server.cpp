#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
	using namespace std;

#define PORT 8020
#define REQ_LOG 0
#define REQ_BAL 1
#define REQ_DEP 2
#define REQ_WIT 3
#define REQ_CLO 4
#define LOGIN_PASS 1
#define LOGIN_FAIL 0



// struct to hold the individual account information
struct account {
	int accountid;
	double amount;
	string username;
};
struct account accounts[3]; 
void handleConnection(int socket); 
int main(int argc, char const *argv[]) {
	int serverid, newsocket;
	// create server socket
	int opt = 1;
	int pid;
	char  buffer[1024] = {0};
	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(PORT);
	int addrlen = sizeof(my_addr);

// read account information from file	
	ifstream inFile("inputfile");
	if (inFile.is_open()) {
		for (int k = 0; k < 3; k++) {
			inFile >> accounts[k].accountid >> accounts[k].amount >> accounts[k].username;
		}
		inFile.close(); // close file after successful reading
	} else {
			cout << "Error opening file" << endl;
	}

	serverid = socket(AF_INET, SOCK_STREAM, 0);	
	setsockopt(serverid, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	bind(serverid, (struct sockaddr *) &my_addr, sizeof(my_addr));
	listen(serverid,3);
	while(true) {
		newsocket = accept(serverid, (struct sockaddr *)&my_addr,(socklen_t*)&addrlen);
		pid = fork();	
		if (pid == 0) {
			close(serverid);
			handleConnection(newsocket);
			exit(0);
		} else {
		close(newsocket);
		}

		}
}
void handleConnection(int socket) {
	int n;
	int requestType;
	int account;
	double amount;
	int loggedIn = -1;
	char buffer[1024];
	bzero(buffer,1024);
	n = read(socket,buffer,1024);
	printf("Message: %s\n",buffer);
	stringstream ss;
	ss << buffer;
	ss >> requestType >> account >> amount;

	if (loggedIn != -1)  { // if logged in 
					cout << endl << accounts[loggedIn].username << " logged in" << endl;
					send(socket,"Already In",10,1); 
	} else {
			if (requestType == REQ_LOG) {
				// if the request is login valid and send info back to the client
				for (int i = 0; i < 3; i++) {
					if (accounts[i].accountid == account) {
						loggedIn = i;
						break;
					}
				}
				if (loggedIn == -1){
					send(socket,"0", 2, 0); 
				} else {
					send(socket,"1",2,1); 
				}
			}
			switch (requestType) {
				case REQ_BAL:
						break;
				case REQ_DEP:
						break;
				case REQ_CLO:
						break;
			}

	}


}
