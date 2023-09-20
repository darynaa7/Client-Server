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
            if( serverSocket = serverUtil->createSocket(); !serverSocket ) return;
            const auto bind = serverUtil->bindServerAddress();
            serverUtil->listenForServerSocket();

            if( clientSocket = serverUtil->connectToClientSocket(bind); !clientSocket ) return;

            serverUtil->communicate_server();
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
            if( clientSocket = clientUtil->createSocket(); !clientSocket ) return;
            clientUtil->connectToServerSocket(clientUtil->bindClientAddress());
        }

        void sendMessages() const
        {
            const auto clientUtil = new NetworkUtils::ClientUtil(clientSocket);
            clientUtil->communicate();
        }

        void sendImage(FILE* imageFile) const
        {
            
        }

        void closeConnection() const
        {
            NetworkUtils::closeSockets({ clientSocket });
        }
    };
};

