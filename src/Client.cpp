#include "../include/Client.hpp"

using namespace std;

static void* t_sendMessage(void* m_socket)
{
	char Message[1024];
	cout<<"Client >";
	cin>>Message;
	send((long)m_socket, (char *)Message, strlen(Message), 0);
	return NULL;
}

static void* t_recvMessage(void* m_socket)
{
	char buffer[1024] = {0};
	int valread = read((long)m_socket, buffer, 1024);
	cout<<"Server >"<<buffer<<endl;
	return NULL;
}

		
void ClientSetup::t_LogError(const char*log)
{
	perror(log);
	exit(EXIT_FAILURE);
}

void ClientSetup::t_Messaging(void)
{
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
	while(1)
	{
		pthread_create(&thread1, &attr, t_sendMessage, (void *)m_client_fd);
     		pthread_create(&thread2, &attr, t_recvMessage, (void *)m_client_fd);
     		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
	}
}

ClientSetup::ClientSetup(int port, char* IPAddress)
{
	signal(SIGPIPE, SIG_IGN);
	if((m_client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		t_LogError("Socket Failed");
	}
	m_client_add.sin_family = AF_INET;
	m_client_add.sin_port = htons(port);
	if(inet_pton(AF_INET, IPAddress, &m_client_add.sin_addr) <= 0)
	{
		t_LogError("Invalid Address/ Address not supported");
	}
	if(connect(m_client_fd, (struct sockaddr*)&m_client_add, sizeof(m_client_add)) < 0)
	{
		t_LogError("Conection Failed");
	}
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout<<"Usage - ./Client <port> <IP>"<<endl;
		exit(0);
	}

	ClientSetup Client(stoi(argv[1]), argv[2]);
	Client.t_Messaging();
	return 0;
}	
