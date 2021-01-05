#include "../include/Common.hpp"

int main(int argc, int *argv[])
{
#ifdef CLIENT

	if(argc != 3)
	{
		cout<<"Usage - ./Client <port> <IP>"<<endl;
		exit(0);
	}

	ClientSetup Client(stoi(argv[1]), argv[2]);
	Client.t_Messaging();
	return 0;
#else 
	if(argc != 2)
	{
		cout<<"Usage - ./Server <port>"<<endl;
		exit(0);
	}

	ServerSetup Serv(stoi(argv[1]));
	Serv.t_Messaging();
	return 0;
#endif
}
