#include "pc/lua/smlua.h"

/* |description|Retured whether external functions are allowed by the user|descriptionEnd| */
bool mod_socket_allowed(void);

/* |description|Initializes the current socket with the provided IP, Port, and TCP/UDP state|descriptionEnd| */
bool mod_socket_init(const char* ip, int port, bool TCP);

/* |description|Disconnect from the current socket if it exists|descriptionEnd|*/
void mod_socket_disconnect(void);

/* |description|Sends a string to the current external socket|descriptionEnd|*/
void mod_socket_send(const char* data);

/* |description|Returns whether the current socket is open or not|descriptionEnd| */
bool mod_socket_is_connected(void);

void mod_socket_update(void); // Called in network.c, excluded from smlua