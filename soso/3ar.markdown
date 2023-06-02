# webserv

# Steps for create a basic webserv 
- Here are the general steps you can follow to create a basic web server:
    * Create a socket using a specific protocol (e.g. TCP/IP) and bind it to a port number that the server will listen to for incoming requests.
    * Listen for incoming client requests on the socket by calling the listen() method on the socket object.
    * Accept incoming client requests using the accept() method on the socket object. This will create a new socket object that can be used to communicate with the client.
    * Receive and parse the client's request message (e.g. HTTP request) using the new socket object.
    * Generate a response message (e.g. HTTP response) based on the request message.
    * Send the response message to the client using the new socket object.
    * Close the new socket object once the response has been sent.
    * Continue listening for incoming client requests by going back to step 3.
Note that this is a simplified overview of the steps involved in creating a web server, and there are many additional details and considerations to take into account depending on the specific requirements of your application. Additionally, it's worth noting that there are many existing web frameworks and libraries that can simplify the process of creating a web server in various programming languages.
================================================================================

# OSI Model
    The OSI (Open Systems Interconnection) model is a conceptual framework that describes how data is transmitted between different devices in a network.
    The OSI model is made up of seven layers, each representing a specific function of the communication process. These layers are:
        - Physical layer: This layer deals with the physical connection between devices and the transmission of data over a physical medium such as copper cables, fiber optic cables, or wireless signals.
        - Data link layer: This layer is responsible for the transfer of data between adjacent network nodes and includes protocols that define how data is framed, transmitted, and received.
        - Network layer: This layer is responsible for routing and forwarding data between different networks, and includes protocols such as IP (Internet Protocol).
        - Transport layer: This layer provides end-to-end communication services such as reliability, flow control, and error recovery.
        - Session layer: This layer establishes, manages, and terminates communication sessions between devices.
        - Presentation layer: This layer handles data formatting and conversion between different data formats, so that data can be understood by the receiving device.
        - Application layer: This layer provides services to applications and includes protocols such as HTTP, FTP, and SMTP.
    The OSI model is used as a standard for network communication protocols because it provides a common language for different network devices to communicate with each other. By dividing the communication process into different layers, it also allows for easier development and maintenance of network protocols, as changes can be made to one layer without affecting the other layers. Additionally, it enables different vendors to create compatible hardware and software that can communicate with each other over a network.

# what's a TCP and UDP and what's diff between them ?
    TCP (Transmission Control Protocol) and UDP (User Datagram Protocol) are two different network protocols used for transmitting data over a network.
    -TCP is a connection-oriented protocol that ensures reliable delivery of data. It creates a connection between two endpoints and guarantees that data is delivered in the correct order and without loss or corruption. TCP provides mechanisms for error detection and correction, and it includes flow control and congestion control to optimize network performance.
    - UDP, on the other hand, is a connectionless protocol that does not provide reliability guarantees. It sends datagrams, or small packets of data, to the destination without establishing a connection first. UDP does not provide error correction or flow control, which means that data may be lost, duplicated, or received out of order. However, UDP is faster and more efficient than TCP because it does not have the overhead of establishing and maintaining a connection.
    * Here are some key differences between TCP and UDP:
        - Connection-oriented vs. connectionless: TCP is a connection-oriented protocol that establishes a connection before transmitting data, while UDP is a connectionless protocol that does not establish a connection.
        - Reliability: TCP provides reliable delivery of data, while UDP does not guarantee reliability.
        - Ordering: TCP guarantees that data is delivered in the correct order, while UDP does not.
        - Error correction: TCP includes error detection and correction mechanisms, while UDP does not.
        - Flow control and congestion control: TCP provides flow control and congestion control mechanisms to optimize network performance, while UDP does not.
    
# what's a endpoint !
    In networking, an endpoint is a combination of an IP address and a port number that represents a specific communication channel between two networked applications. Endpoints allow applications to send and receive data over a network and provide a way for multiple applications to share a single network interface.   
    * For example:
        when two applications communicate over the Internet, each application has its own endpoint. The sending application specifies the IP address and port number of the receiving endpoint, and the data is transmitted over the network to the receiving endpoint. The receiving application then reads the data from its endpoint.
    Endpoints are identified by unique combinations of IP addresses and port numbers, which provide a way for multiple applications to use the same network interface without interfering with each other. By using endpoints, applications can communicate with each other over a network, even if they are running on different computers or operating systems.

# What's diff between OSI, TCP and UDP
    the OSI model provides a conceptual framework for understanding how network protocols interact with each other, while TCP and UDP are actual protocols that are used for communication between network devices at the transport layer.
    - but OSI also a protocols for communication between applications ?
        Yes, that is correct. The OSI model is a reference model that provides a conceptual framework for understanding how communication systems operate, and it defines a set of protocols for communication between applications. However, OSI is a theoretical model that is not directly used in practice, while TCP and UDP are actual protocols that are commonly used for communication over the internet. TCP and UDP operate at the transport layer of the TCP/IP protocol stack, while the OSI model includes additional layers such as the session and presentation layers, which are not directly represented in the TCP/IP protocol stack.

# Socket :
    - socket is a software construct that represents an endpoint for communication between two programs running on a network.
    When two programs want to communicate with each other over a network, they establish a socket connection. One program acts as a server, which listens for incoming socket connections, while the other program acts as a client, which initiates the socket connection.
    Once the socket connection is established, the two programs can exchange data in both directions, sending and receiving messages. This allows for real-time, two-way communication between the programs.
    Sockets are a fundamental component of computer networks and are used extensively in internet communications. They provide a reliable, flexible, and efficient means of communication between programs and enable real-time data exchange between different devices and systems on a network.
    - Here are some of the reasons why we use sockets:
        * Two-way communication: Sockets enable two-way communication between programs running on a network. This allows programs to send and receive data in      real-time and enables them to communicate with each other seamlessly.
        * Platform independence: Sockets are platform-independent and can be used on different operating systems and programming languages. This makes them ideal for network programming, where different devices and systems may be involved.
        * Flexibility: Sockets provide a flexible and customizable communication channel, allowing programmers to define the protocol and parameters of the communication link according to their requirements.
        * Low-level access: Sockets provide low-level access to the network layer, allowing programmers to control and manage network traffic in detail.
    Overall, sockets play a vital role in network communication because they provide a standard way for programs to communicate with each other over a network. They enable programs to establish connections and exchange data in real-time, facilitating seamless communication and collaboration between different devices and systems on a network.

# so basically if a socket is communication between two programs so why we need to use TCP or UDP ?
    - That's a great question. While sockets provide a way for two programs to communicate with each other over a network, they do not define how the data should be transmitted. That's where protocols like TCP and UDP come into play.
    So, when using sockets, you can choose between TCP and UDP depending on your specific requirements. If you need reliable and ordered data transmission, you can use TCP, but if you need faster transmission with no guarantees of data delivery or order, you can use UDP.

# so how can to socket  provide a way for two programs to communicate with each other over a network  
    Sockets provide a standard interface for two programs to establish a network connection and communicate with each other over that connection. Here's how it works:
        Each program creates a socket that is bound to a specific port on the local machine. The socket is like a phone number or a mailbox address that allows other programs to send data to that program.
        One program (usually the server) starts listening for incoming connections on the socket. When a client program tries to connect to the server, the server accepts the connection, and a communication channel is established between the two programs.
        Once the connection is established, the two programs can exchange data through the socket. Each program can send data to the other program by writing data to the socket, and can receive data from the other program by reading data from the socket.
        When the communication is complete, either program can close the socket to terminate the connection.
    This process of creating a socket, establishing a connection, and exchanging data is the basis for most network communications. Sockets provide a standard interface that allows programs to communicate with each other over the network, regardless of the underlying network hardware or software.
    It's important to note that sockets are only a means of establishing a connection and transmitting data between two programs. The actual content and format of the data being transmitted depends on the application protocol being used, such as HTTP, FTP, or SMTP, to name a few. The socket merely provides the channel through which the data is transmitted.

# System call
    - system call is a mechanism provided by the operating system that allows user-level processes or programs to request services from the kernel or operating system. System calls are usually provided through a special software interrupt instruction or a trap instruction that switches the CPU from user mode to kernel mode. In kernel mode, the operating system has direct access to hardware resources and can perform privileged operations on behalf of user-level processes.
    Examples of common system calls include opening and closing files, creating and managing processes, allocating and deallocating memory, and managing input/output operations. System calls provide an interface between user-level applications and the operating system, allowing them to access and utilize the underlying hardware resources in a safe and controlled manner.
    In the context of socket programming, the socket() function is an example of a system call that allows a process to request the creation of a new socket endpoint for communication over a network. Similarly, other socket-related system calls such as bind(), listen(), accept(), connect(), send(), and recv() provide mechanisms for managing the lifecycle and communication of socket endpoints.

# DNS
    like a cahier of IP adress chaque IP adress have a domaine name (like youtube or google or something like that)
# IPv4 Vs IPv6 :

# RFC

# What's a internet 
    billions of connected computing devices(any thing have a cpu (calculer very specefec) like smartphone , ps , tablet , computer , smartwatch, cars and smartTv)
network application : 
