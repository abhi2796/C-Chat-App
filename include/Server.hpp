#ifndef SERVER_H
#define SERVER_H

#include "Common.hpp"

class ServerSetup
{

	private:
		int m_server_fd, m_socket;
		struct sockaddr_in m_server_add;
		int m_sockadd_len;
		pthread_t thread1, thread2;
    		pthread_attr_t attr;
		void t_LogError(const char*);
	public:
		void t_Messaging(void);
		ServerSetup(int);
};

#endif
