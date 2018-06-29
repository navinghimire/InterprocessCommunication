#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
	using namespace std;

#define REQ_LOG 0
#define REQ_BAL 1
#define REQ_DEP 2
#define REQ_WIT 3
#define REQ_CLO 4

int main() {	
	int PORT = 8020;
	int requestType, account;
	double amount = 0;

	cout << "Enter port number: ";
	cin >> PORT;
	cout << "Enter account number: ";
	cin >> account ;

	int clientsocket;
	char buffer[1024] = {0};
	struct sockaddr_in serveraddress;
	clientsocket = socket(AF_INET,SOCK_STREAM, 0);
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(PORT);	
	inet_pton(AF_INET,"127.0.0.1",&serveraddress.sin_addr);
	connect(clientsocket,(struct sockaddr *)&serveraddress,sizeof(serveraddress));
	int loggedIn = false;
	
		
	string request;
	// create login request:
	requestType = REQ_LOG;

	request = to_string(requestType) + " " + to_string(account) + " " +  to_string(amount);
	cout << request << endl;
	send(clientsocket,request.c_str() ,request.length(),0);
	int valread = read(clientsocket,buffer,1024);

	// if login successfull 
	if (valread = 1) {
			while (true) {
			}
	}
	printf("%s",buffer);
}
