#TFTP Server

##THEORY
**Trivial File Transfer Protocol (TFTP)**
* Simple protocol for transfering files. 
* Implemented on top of User Datagram Protocol (UDP).
* Move files between machines on different UDP implemented networks.
* Lacks features of FTP
* Only can read/write/mail from/to remote server.
* No user authentication
* No directory listing

**Overview**
* Begin transfer with request to read/write a file.
* If server grants the request, connection is opened, file is sent in fixed length blocks of 512 bytes.
* Termination of transfer is signaled by a data packet of less than 512 bytes


##IPLEMENTATION
**Data Structures**

**Algorithms**

**References**
* [RFC 1350](https://www.ietf.org/rfc/rfc1350.txt)
 
