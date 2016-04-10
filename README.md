# TFTP Server

## THEORY
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
* If a packet gets lost in the network, the intended recipient will timeout and may retransmit his last packet (which may be data or an acknowledgment), thus causing the sener of the lost packet to retransmit that lost packet.
* The sender only needs to keep one packet for retransmission because last step guarentes that all old packets have been received.
* Both machines are considered senders ad receivers.
* One machine sends data and receives acknowledgments and the other sends acknowledgments and receives data.
* Terminate connection upon most error signalled by sending an error packet (not an acknowledgment or retransmitted).
   * There is one error condition that does not cause termination
      * The source port of a received packet being incorrect, error packet is sent t originating host
* Timeouts are used to detect error packet has been lost.
* Three events that cause errors
   * Not being able to satisfy the request
      * file not found; access violation; no such user
   * Receiving a packet which can't be explained by a delay or duplication in the network
      * incorrectly formed packet 
   * Losing access to a necessary resource
      * disk full; access denied during

<pre>

          ---------------------------------------------------
         |  Local Medium  |  Internet  |  Datagram  |  TFTP  |
          ---------------------------------------------------

                      Order of Headers

		* Datagram is implemented on Internet protocol, Packet has
		   * Internet Header (no values specified)
		   * Datagram Header (source and destination port fields)
		   * TFTP Header (2 byte opcode field indicating the packet's type (e.g., DATA, ERROR, etc.))
		   * Local Trasport Medium (Optional)

</pre>
* TID = Transfer Identifiers
   * 0 - 65535
   * Used by TFTP to pass to the Datagram layer to be used as ports

**Iniitial Connection Protocol**
* A transfer is established by sending a request and receiving a positive reply.
   * WRQ - write onto a foreign file system
      * Acknowledgment packet
   * RQ - read from a foreign file system
      * First data packet
* Data packets have a block number such that they are consecutive and starting at 1.
* Acknowledgment Packets are special, Block number = 0

* Each end of connection randomly chooses a TID for iteself
* Every packet has two (source and ddestination) TID's associated with it of the ends of the connection.
* TID's handed to the UDP as source and destination ports.

* Initially send request to known TID 69 on serving host.
   * Response request uses TID chosen by server as its source TID and TID chosen for previous message by requestor as its destination TID.
   * The two TID's are used for rest of transfer.

* Steps to establish a connection to write a file.
   1. Host A sends a "WRQ" to host B with source = A's TID and destination = 69
   2. Host B sends an "ACK" (with, block number = 0) to host A with source = B's TID and destination = A's TID
   3. Connection is established.
      * The first data packet sent by Host A with sequence number 1.
      * All following steps should make sure the source TID matches the value previously agreed upon
         * If not, discard packet as erroneously sent from somewhere else and reply to sender with an error packet without disturbing transfer.


**Example of correct operation**
1. Host A sends a request to B
2. Somewhere in the network, the request packet is duplicated, and as a result two acknowledgments are returned to host A, with different TID's chosen on host B in response to the two requests.
3. When first response arrives, host A continues the connection
4. When the second response to the request arrives, it should be rejected without terminating first connection.

**TFTP Packets**
* 5 types of packets
* OpCode contained in TFTP header

| OpCode        | Operation            |
|:-------------:|:--------------------:|
| 1             | Read Request (RRQ)   |
| 2             | Write Request (WRQ)  |
| 3             | Data (DATA)          |
| 4             | Acknowledgment (ACK) |
| 5             | Error (ERROR)        |


**TFTP Formats**

   Type   Op #     Format without header

<pre>
          2 bytes    string   1 byte     string   1 byte
          (Opcode) 
          -----------------------------------------------
   RRQ/  | 01/02 |  Filename  |   0  |    Mode    |   0  |
   WRQ    -----------------------------------------------
</pre>

* Mode contains string
   1. "netascii"
   2. "octet"
   3. "mail"

<pre>
          2 bytes    2 bytes       n bytes
          (Opcode)
          ---------------------------------
   DATA  | 03    |   Block #  |    Data    |
          ---------------------------------
</pre>

* Block numbers begin with one and increase by one for each new block of data
   * Allows program to discriminate between new and duplicate packets with a single number.
* Data field is from 0 to 512 bytes
   * If 512 bytes long, block is not last block of data
   * If data is less than 512, signal end of transfer 

<pre>
          2 bytes    2 bytes
          (Opcode)
          -------------------
   ACK   | 04    |   Block #  |
          --------------------
</pre>

* Echos the block number of the DATA packet that is being acknowledged.
* WRQ is acknowledged with an ACK packet having a block number of zero.


<pre>
          2 bytes  2 bytes        string    1 byte
          (Opcode)
          ----------------------------------------
   ERROR | 05    |  ErrorCode |   ErrMsg   |   0  |
          ----------------------------------------   
</pre>

* Can be the acknowledgment of any other type of packet
* Integer ErrorCode indicating error
* List of Errors 

| Value         | Meaning              |
|:-------------:|:--------------------:|
| 0             | Not defined, see error message (if any)   |
| 1             | File not found  |
| 2             | Access violation          |
| 3             | Disk full or allocation exceeded |
| 4             | Illegal TFTP operation        |
| 5             | Unknown transfer ID        |
| 6             | File already exists        |
| 7             | No such user        |


* ErrorMsg terminated by 0 byte


**Termination**
* Normal
   * End marked by DATA packet that contains between 0 and 511 bytes.
      * Acknowledged by ACK
   * 

* Note
   * The host can close

* Premature
   * 

## IPLEMENTATION
**Data Structures**

**Algorithms**

## References
* [RFC 1350](https://www.ietf.org/rfc/rfc1350.txt)
 
