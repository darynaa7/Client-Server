module;

#include <iostream>
#include <vector>

export module Network;
import NetworkUtils;

namespace Network
{
    export class Server
    {
    private:
        int serverSocket = NULL;
        int clientSocket = NULL;
    public:
        void createConnection()
        {
            const auto serverUtil = new NetworkUtils::ServerUtil();
            if( serverSocket = serverUtil->createSocket(); !serverSocket ) return; //creating socket
            const auto bind = serverUtil->bindServerAddress(); //binding
            serverUtil->listenForServerSocket(); //listen
            if( clientSocket = serverUtil->connectToClientSocket(bind); !clientSocket ) return; //connect to client
            serverUtil->communicate_server(); //communicate
        }

        void closeConnection() const
        {
            NetworkUtils::closeSockets({ serverSocket, clientSocket });
        }
    };


    export class Client
    {
    private:
        int clientSocket = NULL;
    public:
        Client() = default;

        void createConnection()
        {
            const auto clientUtil = new NetworkUtils::ClientUtil();
            if( clientSocket = clientUtil->createSocket(); !clientSocket ) return; //creating socket
            clientUtil->connectToServerSocket(clientUtil->bindClientAddress()); //connecting to server
        }

        void sendMessages() const
        {
            const auto clientUtil = new NetworkUtils::ClientUtil(clientSocket);
            clientUtil->communicate(); //communicating
        }

        void sendImage(FILE* imageFile) const
        {
            // func will send screenshots to server
        }

        void closeConnection() const
        {
            NetworkUtils::closeSockets({ clientSocket });
        }
    };
};

