#include	<winsock.h>					// Winsock header file

#define PROG_NAME "Simple DNS Lookup"

#define HOST_NAME "cdfsg6.lbl.gov"		// This can be any valid host name
#define WINSOCK_VERSION 0x0101		// Program requires Winsock version 1.1
#define PF_INET_LENGTH 4					// Address length for Internet protocol
																	// family is always 4 bytes
#define HOST_ADDR "128.32.191.249"	// apocalypse.ocf.berkeley.edu

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, 
			LPSTR lpszCmdParam, int nCmdShow)
	{
		WSADATA wsaData;							// Winsock implementation details
		LPHOSTENT lpHostEnt;						// Internet host information structure
		DWORD dwIPAddr;								// IP address as an unsigned long
		LPSTR szIPAddr;								// IP address as a dotted decimal string
	
		if (WSAStartup(WINSOCK_VERSION, &wsaData))
			MessageBox(NULL, "Could not load Windows Sockets DLL.", PROG_NAME, 
						MB_OK|MB_ICONSTOP);
						
		else	// Resolve the host name
			{	
				lpHostEnt = gethostbyname(HOST_NAME);
				
				if (!lpHostEnt)
					MessageBox(NULL, "Could not get IP address!", HOST_NAME, 
								MB_OK|MB_ICONSTOP);
								
				else // Convert the IP address into a dotted-decimal string
					{	
						szIPAddr = inet_ntoa(*(LPIN_ADDR)*(lpHostEnt->h_addr_list));
						
						MessageBox(NULL, szIPAddr, lpHostEnt->h_name, 
									MB_OK|MB_ICONINFORMATION);
					}
				
				// Convert a dotted-decimal string into a 32-bit IP address
				dwIPAddr = inet_addr(HOST_ADDR);
				
				if (dwIPAddr == INADDR_NONE)				 		
					MessageBox(NULL, "Invalid Internet address!", HOST_ADDR, 
								MB_OK|MB_ICONSTOP);
								
				else	// Resolve the IP address
					{ 
						lpHostEnt = gethostbyaddr((LPSTR) &dwIPAddr, PF_INET_LENGTH, 
									PF_INET);
									
						if (!lpHostEnt)
							MessageBox(NULL, "Could not get host name!", HOST_ADDR, 
										MB_OK|MB_ICONSTOP);
						else
							MessageBox(NULL, lpHostEnt->h_name, HOST_ADDR, 
										MB_OK|MB_ICONINFORMATION);
					}
			}
		WSACleanup();	// Free all allocated program resources and exit
		return(NULL);
	}

