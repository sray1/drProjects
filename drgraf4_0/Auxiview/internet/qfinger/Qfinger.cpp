#include	<winsock.h>				// Winsock header file

#define PROG_NAME "Simple Finger Query"

#define HOST_NAME "ocf.berkeley.edu"	 	// This can be any valid host name
#define WINSOCK_VERSION 0x0101		// Program requires Winsock version 1.1
#define FINGER_QUERY "rayd"		// This can be a login name or real name
#define DEFAULT_PROTOCOL 0				// No protocol specified, use default
#define SEND_FLAGS 0							// No send() flags specified
#define RECV_FLAGS 0							// No recv() flags specified

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, 
			LPSTR lpszCmdParam, int nCmdShow)
	{
		WSADATA wsaData;							// Winsock implementation details
		LPHOSTENT lpHostEnt;					// Internet host information structure
		SOCKET nSocket;						 		// Socket handle used by this program
		SOCKADDR_IN sockAddr;					// Socket address structure
		LPSERVENT lpServEnt;			 		// Service information structure
		short iFingerPort;						// Well-known port assignment is 79
		char szFingerInfo[5000];	 		// Buffer to hold finger information
		char szFingerQuery[100];			// Buffer to hold finger query
		int nCharSent;								// Number of characters transmitted
		int nCharRecv;								// Number of characters received
		int nConnect;								 	// Socket connection results
																 
		if (WSAStartup(WINSOCK_VERSION, &wsaData))
			MessageBox(NULL, "Could not load Windows Sockets DLL.", 
						PROG_NAME, MB_OK|MB_ICONSTOP);
						
		else 	// Resolve the host name
			{
				lpHostEnt = gethostbyname(HOST_NAME);
				
				if (!lpHostEnt)
					MessageBox(NULL, "Could not get IP address!", HOST_NAME, 
								MB_OK|MB_ICONSTOP);
								
				else	// Create the socket	
					{
						nSocket = socket(PF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
						
						if (nSocket == INVALID_SOCKET)
							MessageBox(NULL, "Invalid socket!!", PROG_NAME, 
										MB_OK|MB_ICONSTOP);
										
						else	// Configure the socket
							{ 
								// Get the finger service information
								lpServEnt = getservbyname("finger", NULL);
						
								if (lpServEnt == NULL)
									iFingerPort = htons(IPPORT_FINGER);	// Use the well-known port
								else
									iFingerPort = lpServEnt->s_port;

								// Define the socket address	
								sockAddr.sin_family = AF_INET;	// Internet address family
								sockAddr.sin_port = iFingerPort;
								sockAddr.sin_addr = *((LPIN_ADDR)*lpHostEnt->h_addr_list);
						
								// Connect the socket
								nConnect = connect(nSocket, (LPSOCKADDR) &sockAddr, 
											sizeof(sockAddr));
											
								if (nConnect)
									MessageBox(NULL, "Error connecting socket!!", PROG_NAME, 
												MB_OK|MB_ICONSTOP);
												
								else	// Format and send the finger query
									{ 
										wsprintf(szFingerQuery,"%s\n", (LPSTR)FINGER_QUERY);
										
										nCharSent = send(nSocket, szFingerQuery, 
													lstrlen(szFingerQuery), SEND_FLAGS);
													
										if (nCharSent == SOCKET_ERROR)
											MessageBox(NULL, "Error occurred during send()!", 
														PROG_NAME, MB_OK|MB_ICONSTOP);
														
										else	// Get the finger information from the host
											{ 
										    do
										    	{
										    		nCharRecv = recv(nSocket, 
										    					(LPSTR)&szFingerInfo[nConnect], 
										    					sizeof(szFingerInfo) - nConnect, 
										    					RECV_FLAGS);
										    		nConnect+=nCharRecv;
										    	}
										    		while (nCharRecv > 0);
															
												if (nCharRecv == SOCKET_ERROR)
													MessageBox(NULL, "Error occurred during recv()!", 
																PROG_NAME, MB_OK|MB_ICONSTOP);
																
												else	// Display the finger information
													{
														wsprintf(szFingerQuery,"%s@%s", (LPSTR)FINGER_QUERY, 
																	(LPSTR)HOST_NAME);
														MessageBox(NULL, szFingerInfo, szFingerQuery, 
																	MB_OK|MB_ICONINFORMATION);
													}
											}
									}
							}
					}
			}
		WSACleanup();	// Free all allocated program resources and exit
		return(NULL); 
	}

