module;

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif
#include <iostream>
#include <vector>
#include <thread>

export module NetworkUtils;

namespace NetworkUtils
{
	export void setup()
	{
#ifdef _WIN32
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
	}

	export void cleanup()
	{
#ifdef _WIN32
		WSACleanup();
#endif
	}

	export void receive(const int socket, char *buffer, const int length, const int flags)
	{
#ifdef _WIN32
		recv(socket, buffer, length, flags);
#else
		read(socket, buffer, length, flags);
#endif
	}

	export void closeSockets(const std::vector<int> &sockets)
	{
#ifdef _WIN32
		for( int socket : sockets )
		{
			closesocket(socket);
		}
		WSACleanup();
#else
		for( int socket : sockets )
		{
			close(socket);
		}
#endif
	}
	export class ServerUtil
    {
	private:
		int serverSocket = NULL;
		int clientSocket = NULL;
	public:
		ServerUtil() = default;

	    int createSocket()
		{
			setup();

			serverSocket = socket(AF_INET, SOCK_STREAM, 0);
			if( serverSocket == INVALID_SOCKET )
			{
				cleanup();
				std::cout << " nocreated socket";
				return NULL;
			}
			std::cout << " created socket";
			return serverSocket;
		}

		sockaddr_in bindServerAddress() const
		{
			sockaddr_in serverAddress;
			serverAddress.sin_family = AF_INET;
			serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
			serverAddress.sin_port = htons(5555);

			if( bind(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR )
			{
				std::cout << " nobinded socket";
				closeSockets({ serverSocket });
			}
			std::cout << " binded socket";
			return serverAddress;
		}

		void listenForServerSocket() const
		{
			std::cout << " listen socket";
			if( listen(serverSocket, 5) == SOCKET_ERROR )
			{
				std::cout << " close socket";
				closeSockets({ serverSocket });
				return;
			}
			std::cout << " listen44ed socket";
		}

		int connectToClientSocket(sockaddr_in serverAddress) 
		{
			socklen_t addressLength = sizeof(serverAddress);
			std::cout << " start socket";
			clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), &addressLength);
			if( clientSocket == INVALID_SOCKET )
			{
				closeSockets({ serverSocket });

				return NULL;
			}
			std::cout << " accepted";
			return clientSocket;
		}

		void communicate_server() const
		{
			
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

				char buffer[1024] = { 0 };
				receive(clientSocket, buffer, 1024, 0);

				std::cout << "connection...Client message: " << buffer << std::endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			
			const auto message = "Hello, client_util!\n";
			send(clientSocket, message, strlen(message), 0);
			std::cout << "Message to the client_util sent\n";
		}
	};


	export class ClientUtil
	{
	private:
		int clientSocket = NULL;

	public:
		ClientUtil() = default;
	    int createSocket()
		{
			NetworkUtils::setup();

			clientSocket = socket(AF_INET, SOCK_STREAM, 0);
			if( clientSocket == INVALID_SOCKET )
			{
				NetworkUtils::cleanup();
				return NULL;
			}

			return clientSocket;
		}

		static sockaddr_in bindClientAddress()
		{
			sockaddr_in serverAddress;
			serverAddress.sin_family = AF_INET;
			serverAddress.sin_port = htons(5555);
			inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

			return serverAddress;
		}


		void connectToServerSocket(sockaddr_in serverAddress) const
		{
			connect(clientSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress));

		}

		void communicate() const
		{
			

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			const auto message = "Hello, server_util!";
			send(clientSocket, message, strlen(message), 0);


			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			char buffer[1024] = { 0 };
			NetworkUtils::receive(clientSocket, buffer, 1024, 0);
			std::cout << "Server message: " << buffer << std::endl;
		}
	};
}