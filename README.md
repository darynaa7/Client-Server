# Client-Server
Simple client server application, where client can do "print-screen" each 60 seconds.
Screenshots are stored in Client app folder.

Server.cpp -  use network.ixx to do server part

Client.cpp -  use network.ixx to do client part

Screenshots.cpp/.h - files contain logic of making screenshots

Network.ixx - module that contains network dependent code

NetworkUtils.ixx - module that contains platform dependent code

Soon will be updated so Server will be able to request screens by names.
