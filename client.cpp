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
#define LOGIN_PASS 1;
#define LOGIN_FAIL 0;
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
	int loggedIn = -1 ;
		
	string request;
	// create login request:
	requestType = REQ_LOG;
	request = to_string(requestType) + " " + to_string(account) + " " +  to_string(amount);
	cout << request << endl;
	send(clientsocket,request.c_str() ,request.length(),0);
	int valread = read(clientsocket,buffer,1024);
	// if login successfull 
	if (atoi(buffer) == 1) {
			while (loggedIn) {
					cout << "Available Transactions\n"
							<< "\t 1. Balance\n" 
							<< "\t 2. Deposit\n"
							<< "\t 3. Withdraw\n"
							<< "\t 4. Logont\n";
					cout << "Transaction: ";
					cin >> requestType;

					if (requestType == 0 || requestType == 4) {
						cout << "Account number: ";
						cin >> account;
					}
					if (requestType == 0 || requestType == 1 || requestType == 4) {
						amount = 0.0;
					} else {
						cout << "Amount: ";
						cin >> amount;
					}
					request = to_string(requestType) + " " + to_string(account) + " " +  to_string(amount);
					send(clientsocket,request.c_str() ,request.length(),0);
			}
	}
	printf("%s",buffer);
}
