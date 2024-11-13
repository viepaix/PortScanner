#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <map>
#include <string>
#include <iomanip>
#include <thread>
#include <vector>
#include <chrono>

std::string CLS = "\033[2J\033[1;1H"; //clear screen
std::string Default = "\033[0m"; // default gray & reset background
std::string White = "\033[37;1m"; // bright white
std::string Red = "\033[31;1m";
std::string Pink = "\x1B[38;5;213m";
std::string Green = "\033[32;1m";
std::string SeaGreen = "\x1B[38;5;158m";
std::string Yellow = "\033[33;1m";
std::string Navy = "\033[34;1m";
std::string Blue = "\x1B[38;5;117m";
std::string Cyan = "\033[36;1m";
std::string Purple = "\x1B[38;5;171m";
std::string Orange = "\x1B[38;5;208m";
std::string Coral = "\x1B[38;5;204m";

std::string BlackOnRed = "\033[41m\033[1m\033[30m";
std::string WhiteOnGreen = "\033[42;1m";
std::string WhiteOnYellow = "\033[43;1m";
std::string WhiteOnBlue = "\033[44;1m";
std::string WhiteOnPurple = "\033[45;1m";
std::string WhiteOnCyan = "\033[46;1m";

int topPorts[100] = {20, 21, 22, 23, 25, 53, 67, 68, 69, 80, 110, 119, 123, 143, 161, 162, 194, 443, 445, 465, 514, 515, 543, 544, 587, 631, 636, 993, 995, 1080, 1194, 1433, 1434, 1521, 1600, 1723, 17500, 2049, 2222, 3306, 3389, 3690, 4444, 4567, 5060, 5061, 5432, 5555, 5900, 6000, 6660, 6661, 6662, 6663, 6699, 7000, 7001, 8000, 8080, 8443, 8888, 9000, 9090, 10000, 11211, 12345, 12222, 13333, 14345, 14900, 16000, 17001, 17500, 18000, 1863, 19132, 19200, 19302, 20000, 21000, 22222, 23456, 25000, 26208, 27888, 30000, 31415, 33000, 35000, 36888, 37888, 39000, 40000, 42000, 44444, 45500, 50000, 51000, 52000, 53000};

std::string getPortPurpose(int port){
  std::map<int, std::string> portPurpose = {
    {1, "TCP Port Service Multiplexer (TCPMUX)"},
    {7, "Echo Protocol"},
    {9, "Discard Protocol"},
    {13, "Daytime Protocol"},
    {17, "Quote of the Day Protocol (QOTD)"},
    {19, "Character Generator Protocol (CHARGEN)"},
    {20, "File Transfer Protocol (FTP) - Data"},
    {21, "File Transfer Protocol (FTP) - Command Control"},
    {22, "Secure Shell (SSH)"},
    {23, "Telnet"},
    {25, "Simple Mail Transfer Protocol (SMTP)"},
    {26, "RSFTP (Alternate FTP)"},
    {37, "Time Protocol"},
    {39, "Resource Location Protocol (RLP)"},
    {42, "Host Name Server Protocol (HNSP)"},
    {43, "WHOIS Protocol"},
    {49, "TACACS Login Host Protocol"},
    {53, "Domain Name System (DNS)"},
    {67, "Dynamic Host Configuration Protocol (DHCP) - Server"},
    {68, "Dynamic Host Configuration Protocol (DHCP) - Client"},
    {69, "Trivial File Transfer Protocol (TFTP)"},
    {70, "Gopher Protocol"},
    {79, "Finger Protocol"},
    {80, "Hypertext Transfer Protocol (HTTP)"},
    {88, "Kerberos"},
    {95, "SUPDUP"},
    {101, "NIC Hostname Protocol"},
    {102, "ISO-TSAP (Transport Service Access Point)"},
    {107, "Remote TELNET Service"},
    {109, "Post Office Protocol (POP2)"},
    {110, "Post Office Protocol (POP3)"},
    {111, "Remote Procedure Call (RPC)"},
    {113, "Identification Protocol (IDENT)"},
    {115, "Simple File Transfer Protocol (SFTP)"},
    {117, "UUCP Path Service"},
    {119, "Network News Transfer Protocol (NNTP)"},
    {123, "Network Time Protocol (NTP)"},
    {135, "Microsoft EPMAP (End Point Mapper)"},
    {137, "NetBIOS Name Service"},
    {138, "NetBIOS Datagram Service"},
    {139, "NetBIOS Session Service"},
    {143, "Internet Message Access Protocol (IMAP)"},
    {161, "Simple Network Management Protocol (SNMP)"},
    {162, "SNMP Trap"},
    {163, "CMIP over TCP"},
    {179, "Border Gateway Protocol (BGP)"},
    {194, "Internet Relay Chat (IRC)"},
    {201, "AppleTalk Routing Maintenance"},
    {202, "AppleTalk Name Binding"},
    {204, "AppleTalk Echo"},
    {206, "AppleTalk Zone Information"},
    {209, "Quick Mail Transfer Protocol"},
    {213, "IPX"},
    {218, "Message Processing Module (MPP)"},
    {220, "Internet Message Access Protocol (IMAP3)"},
    {245, "Link Local Multicast Name Resolution (LLMNR)"},
    {347, "Fatmen File Service Protocol"},
    {369, "RADIUS Protocol"},
    {389, "Lightweight Directory Access Protocol (LDAP)"},
    {427, "Service Location Protocol (SLP)"},
    {443, "HTTP Secure (HTTPS)"},
    {444, "SNPP (Simple Network Paging Protocol)"},
    {445, "Microsoft-DS (Directory Services)"},
    {464, "Kerberos Change Password"},
    {465, "SMTP over SSL"},
    {500, "Internet Key Exchange (IKE)"},
    {512, "rexec (Remote Execution)"},
    {513, "rlogin (Remote Login)"},
    {514, "rsh (Remote Shell)"},
    {515, "Line Printer Daemon (LPD)"},
    {520, "Routing Information Protocol (RIP)"},
    {524, "NetWare Core Protocol (NCP)"},
    {530, "RPC (Remote Procedure Call)"},
    {543, "Kerberos Login"},
    {544, "kshell (Kerberos Shell)"},
    {546, "DHCPv6 Client"},
    {547, "DHCPv6 Server"},
    {548, "Apple Filing Protocol (AFP)"},
    {554, "Real Time Streaming Protocol (RTSP)"},
    {587, "SMTP (Mail Submission)"},
    {593, "Microsoft DCOM Service Control Manager"},
    {631, "Internet Printing Protocol (IPP)"},
    {636, "LDAP over SSL (LDAPS)"},
    {639, "Multicast Transport Protocol"},
    {646, "Label Distribution Protocol (LDP)"},
    {647, "DHCP Failover"},
    {660, "Mac OS X Server Administration"},
    {666, "Doom (gaming protocol)"},
    {674, "ACAP (Application Configuration Access Protocol)"},
    {688, "REALM-RUSD (Protocol)"},
    {690, "VxWorks RPC"},
    {700, "EPP (Extensible Provisioning Protocol)"},
    {705, "AgentX (SNMP Agent)"},
    {711, "Cisco TDP"},
    {720, "Z39.50"},
    {749, "Kerberos (kadmin)"},
    {750, "Kerberos IV"},
    {873, "rsync"},
    {992, "Telnet over SSL"},
    {993, "IMAP over SSL"},
    {995, "POP3 over SSL"},
    {1080, "SOCKS Proxy"},
    {1194, "OpenVPN"},
    {1433, "Microsoft SQL Server"},
    {1434, "Microsoft SQL Server Monitor"},
    {1701, "L2TP (Layer 2 Tunneling Protocol)"},
    {1723, "PPTP (Point-to-Point Tunneling Protocol)"},
    {2049, "Network File System (NFS)"},
    {2082, "cPanel"},
    {2083, "cPanel over SSL"},
    {3306, "MySQL Database Service"},
    {3389, "Remote Desktop Protocol (RDP)"},
    {5060, "Session Initiation Protocol (SIP)"},
    {5432, "PostgreSQL Database Service"},
    {5900, "Virtual Network Computing (VNC)"}
  };

  if (portPurpose.find(port) != portPurpose.end()){
    return portPurpose[port];
  }
  return "Unknown Service.";

}

void scanningPort(const std::string& ipTarget, int port){
  
  int sock;

  struct sockaddr_in address;
  std::string purpose = getPortPurpose(port);

  sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock < 0){
    //std::cerr << "\n[x] Socket Creation Error\n on " << port << " port in the address " << ipTarget << std::endl;
    return;
  }

  address.sin_family = AF_INET;
  address.sin_port = htons(port);

  // Convert text (ip) to binary:

  if (inet_pton(AF_INET, ipTarget.c_str(), &address.sin_addr) <= 0){
    std::cerr << Red << "\n[x] Invalid address or not supported" << Default << std::endl;
    close(sock);
    return exit(1);
  }

  int connection = connect(sock, (struct sockaddr *)&address, sizeof(address));

  if (connection == 0){
    std::cout << Blue << "[+] Port | "  << SeaGreen << std::setw(3) << port << std::setw(3) << Blue << " | " << SeaGreen << "[open]" << Pink << std::setw(15) << "(" << purpose << ")" << Default << std::endl;
  }
  else {
    //std::cout << "Port -> " << port << " is closed" << std::endl;
    return;
  }

  close(sock);
  //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void threadCalc(const std::string& ipTarget, int startingPort, int endPort){
    int threadsCount = 50;
    int portPerThread, remainder, currentPort;
    std::vector<std::thread> threads;
    // calculate the number of ports each thread

    portPerThread = (endPort - startingPort + 1) / threadsCount;
    remainder = (endPort - startingPort + 1) % threadsCount;

    currentPort = startingPort;

    std::cout << Blue << "\n[~] Scanning ports " << Green << startingPort << Blue << "-" << Green << endPort << Blue << " on " << Red << ipTarget << Default << "\n\n";
    for (int i = 0; i < threadsCount; i++){
      int currentEndPort = currentPort + portPerThread -1;
      if(remainder > 0){
        currentEndPort++;
        remainder--;
      }
    
      threads.push_back(std::thread([=](){
        for(int port = currentPort; port <= currentEndPort; port++){
          //std::cout << "\n\nTarget: " << ipTarget << "\tPort: " << port << std::endl;
          scanningPort(ipTarget, port);
          std::this_thread::sleep_for(std::chrono::milliseconds(700));
          }
      }));
      currentPort = currentEndPort + 1;
    }

    for (auto& t : threads){
      t.join();
    }
}

int main(int argc, char* argv[]){
  
  int startingPort, endPort;

  if (argc < 3){
      std::cerr << Red <<"\n[!] Usage " << Blue << argv[0] << SeaGreen << " <ip target> <start port> <end port>\n" << std::setw(46) << "--top-100 " << Pink << "(use 100 most common ports)" << std::endl << std::setw(47) << SeaGreen << "--all" << Pink << " (scan all ports)" << Default << std::endl;
      return 1;
  }

  std::string ipTarget = argv[1];
  std::string top = argv[2];

  if (argc == 4){
    startingPort = std::stoi(argv[2]);
    endPort = std::stoi(argv[3]);
    threadCalc(ipTarget,startingPort, endPort);
  }
  else if (argc == 3 && std::string(argv[2]) == "--top-100"){
  
    for (int i = 0; i < 100; i++){
      scanningPort(ipTarget, topPorts[i]);
    }

  }
  else if (argc == 3 && std::string(argv[2]) == "--all"){
    startingPort = 1;
    endPort = 65355;
    threadCalc(ipTarget,startingPort, endPort);
  }
  else {
    std::cerr << Red << "[x] Invalid arguments.\nUse " << SeaGreen << argv[0] << Red << " To see the help menu\n\n" << Default;
    return 1;
  } 
  return 0;
}
