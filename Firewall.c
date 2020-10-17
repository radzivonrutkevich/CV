/*
* SPLPv1.c
* The file is part of practical task for System programming course.
* This file contains validation of SPLPv1 protocol.
*/


/*
  Руткевич Родион Александрович
  13 группа
 */



 /*
 ---------------------------------------------------------------------------------------------------------------------------
 # |      STATE      |         DESCRIPTION       |           ALLOWED MESSAGES            | NEW STATE | EXAMPLE
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 1 | INIT            | initial state             | A->B     CONNECT                      |     2     |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 2 | CONNECTING      | client is waiting for con-| A<-B     CONNECT_OK                   |     3     |
 |                 | nection approval from srv |                                       |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 3 | CONNECTED       | Connection is established | A->B     GET_VER                      |     4     |
 |                 |                           |        -------------------------------+-----------+----------------------
 |                 |                           |          One of the following:        |     5     |
 |                 |                           |          - GET_DATA                   |           |
 |                 |                           |          - GET_FILE                   |           |
 |                 |                           |          - GET_COMMAND                |           |
 |                 |                           |        -------------------------------+-----------+----------------------
 |                 |                           |          GET_B64                      |     6     |
 |                 |                           |        ------------------------------------------------------------------
 |                 |                           |          DISCONNECT                   |     7     |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 4 | WAITING_VER     | Client is waiting for     | A<-B     VERSION ver                  |     3     | VERSION 2
 |                 | server to provide version |          Where ver is an integer (>0) |           |
 |                 | information               |          value. Only a single space   |           |
 |                 |                           |          is allowed in the message    |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 5 | WAITING_DATA    | Client is waiting for a   | A<-B     CMD data CMD                 |     3     | GET_DATA a GET_DATA
 |                 | response from server      |                                       |           |
 |                 |                           |          CMD - command sent by the    |           |
 |                 |                           |           client in previous message  |           |
 |                 |                           |          data - string which contains |           |
 |                 |                           |           the following allowed cha-  |           |
 |                 |                           |           racters: small latin letter,|           |
 |                 |                           |           digits and '.'              |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 6 | WAITING_B64_DATA| Client is waiting for a   | A<-B     B64: data                    |     3     | B64: SGVsbG8=
 |                 | response from server.     |          where data is a base64 string|           |
 |                 |                           |          only 1 space is allowed      |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 7 | DISCONNECTING   | Client is waiting for     | A<-B     DISCONNECT_OK                |     1     |
 |                 | server to close the       |                                       |           |
 |                 | connection                |                                       |           |
 ---------------------------------------------------------------------------------------------------------------------------

 IN CASE OF INVALID MESSAGE THE STATE SHOULD BE RESET TO 1 (INIT)

 */

#include <stdlib.h>
#include "splpv1.h"
#include "string.h"

 /* FUNCTION:  validate_message
 *
 * PURPOSE:
 *    This function is called for each SPLPv1 message between client
 *    and server
 *
 * PARAMETERS:
 *    msg - pointer to a structure which stores information about
 *    message
 *
 * RETURN VALUE:
 *    MESSAGE_VALID if the message is correct
 *    MESSAGE_INVALID if the message is incorrect or out of protocol
 *    state
 */

const char base64[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const char data[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const char* comms[] = { "GET_DATA", "GET_FILE", "GET_COMMAND" };

short Condition = 1;
short Commnd;

enum test_status validate_message(struct Message* msg) {
	char* message = msg->text_message;
	if (msg->direction == 0) {
		if (Condition == 1) {
			if (!strcmp(message, "CONNECT")){
				Condition = 2;
				return MESSAGE_VALID;
			}
		}
		else if (Condition == 3) {
			if (!strcmp(message, "GET_VER")) {
				Condition = 4;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_DATA")) {
				Commnd = 0;
				Condition = 5;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_FILE")) {
				Commnd = 1;
				Condition = 5;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_COMMAND")) {
				Commnd = 2;
				Condition = 5;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_B64")) {
				Condition = 6;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "DISCONNECT")) {
				Condition = 7;
				return MESSAGE_VALID;
			}
		}
	}

	else if (msg->direction == 1) {
		if (Condition == 2) {
			if (!strcmp(message, "CONNECT_OK")) {
				Condition = 3;
				return MESSAGE_VALID;
			}
		}
		else if (Condition == 7) {
			if (!strcmp(message, "DISCONNECT_OK")) {
				Condition = 1;
				return MESSAGE_VALID;
			}
		}

		else if (Condition == 4) {
			if (!strncmp(message, "VERSION ", 8)) {
				message += 8;
				if (*message > 48 && *message < 58) {
					for (++message; *message != '\0'; message++) 
						if (*message < 48 || *message > 57) {
							Condition = 1;
							return MESSAGE_INVALID;
						}
					Condition = 3;
					return MESSAGE_VALID;
				}
			}
		}

		else if (Condition == 5) {
			if (!strncmp(message, comms[Commnd], strlen(comms[Commnd])))
			{
				message += strlen(comms[Commnd]); 
				if (*message == ' ') 
				{
					message++; 
					char* checker;
					for (; data[*message]; ++message); 
					if (checker = (*message == ' ')) { 
						checker = message + 1; 
					}
					if (checker) {
						if (!strcmp(checker, comms[Commnd])) { 
							Condition = 3;
							return MESSAGE_VALID;
						}
					}
				}
			}
		}
		
		else if (Condition == 6 && !strncmp(message, "B64: ", 5)) {
			message += 5;
			char* begin = message;
			for (; base64[*message]; ++message);
			char check = 0;
			for (; (check < 2) && (message[check] == '='); ++check); 
			if ((message - begin + check) % 4 == 0 && !message[check]) { 
				Condition = 3;
				return MESSAGE_VALID;
			}
		}
	}
	Condition = 1;
	return MESSAGE_INVALID;
}
