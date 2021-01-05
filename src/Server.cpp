#include "../include/Server.hpp" 

using namespace std;

static void* t_sendMessage(void* m_socket)
{
	char Message[1024];
	cout<<"Server >";
	cin>>Message;
	send((long)m_socket, (char *)Message, strlen(Message), 0);
	return NULL;
}

static void* t_recvMessage(void* m_socket)
{
	char buffer[1024] = {0};
	int valread = read((long)m_socket, buffer, 1024);
	cout<<"Client >"<<buffer<<endl;
	return NULL;
}

	
void ServerSetup::t_LogError(const char*log)
{
	perror(log);
	exit(EXIT_FAILURE);
}

void ServerSetup::t_Messaging(void)
{
     	pthread_attr_init(&attr);
    	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
	while(1)
	{
		pthread_create(&thread1, &attr, t_sendMessage,(void *)m_socket);
     		pthread_create(&thread2, &attr, t_recvMessage,(void *)m_socket);
     		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
	}
}

ServerSetup::ServerSetup(int port)
{
	signal(SIGPIPE, SIG_IGN);
	int option = 1;
	if((m_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		t_LogError("Socket Failed");
	}

	if(setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option)))
	{
		t_LogError("SetSockOpt Failed");
	}

	m_server_add.sin_family = AF_INET;
	m_server_add.sin_addr.s_addr = INADDR_ANY;
	m_server_add.sin_port = htons(port);

	if(bind(m_server_fd, (struct sockaddr*)&m_server_add, sizeof(m_server_add)) < 0)
	{
		t_LogError("Bind Faliure");
	}

	if(listen(m_server_fd, 3) < 0)
	{
		t_LogError("Listen Error");
	}

	m_sockadd_len = sizeof(m_server_add);
	if((m_socket = accept(m_server_fd, (struct sockaddr *)&m_server_add, (socklen_t*)&m_sockadd_len)) < 0)
	{
		t_LogError("Accept Error");
	}
}


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout<<"Usage - ./Server <port>"<<endl;
		exit(0);
	}

	ServerSetup Serv(stoi(argv[1]));
	Serv.t_Messaging();
	return 0;
}

