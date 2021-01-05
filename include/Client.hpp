#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>

#include "Common.hpp"

class ClientSetup
{
	private:
		struct sockaddr_in m_client_add;
		pthread_t thread1, thread2;
    		pthread_attr_t attr;
		void t_LogError(const char*);
		int m_client_fd;
	public:
		void t_Messaging(void);
		ClientSetup(int , char*);
};

#endif
