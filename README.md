# Client-Server
Simple client server application, where client can do "print-screen" each 60 seconds (loop for 4 times).
Screenshots are stored in Client app folder.
Works both for Windows and Linux(I hope so, can`t check;__))

Server.cpp -  use network.ixx to do server part

Client.cpp -  use network.ixx to do client part

Screenshots.cpp/.h - files contain logic of making screenshots

Network.ixx - module that contains network dependent code

NetworkUtils.ixx - module that contains platform dependent code

21.09.2023, 12:30 
Soon will be updated so Server will be able to request screens by names.
Going to do cmake and .bat file to run the files.
