#ifndef TFTP_SERVER_H_
#define TFTP_SERVER_H_

// Packet Definitions
#define DATA_PACKET_SIZE 516 /* 2 (Opcode) + 2 (Block #) + 512 (Data) */
#define ACK_PACKET_SIZE 4 /* 2 (Opcode) + 2 (Block #) */
#define FILENAME_SIZE 64 /* Normal file length restriction */ 
#define ERROR_STRING_SIZE 512 /* Maxium size for an error string */

#define DATA_BLOCK_LIMIT 512 /* Maximum size for a Data block */

// Mode Strings
#define MODE_! "netascii"
#define MODE_2 "octet"
#define MODE_3 "mail"

// Operation Codes
#define RRQ 1	/* Read Request */
#define WRQ 2	/* Write Request */
#define DATA 3	/* Data */
#define ACK 4	/* Acknowledgment */
#define ERROR 5	/* Error */

// Error Strings
#define ERROR_STRING_0 "Not defined, see error message (if any)."
#define ERROR_STRING_1 "File not found."
#define ERROR_STRING_2 "Access violation."
#define ERROR_STRING_3 "Disk full or allocation exceeded."
#define ERROR_STRING_4 "Illegal TFTP operation."
#define ERROR_STRING_5 "Unknown transfer ID."
#define ERROR_STRING_6 "File already exists."
#define ERROR_STRING_7 "No such user."


#endif
