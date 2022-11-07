#include <stdio.h>
#include <sys/socket.h>

#define DEBUG_ENABLED 1
#define LOG(message) fprintf(stdout, (message))
#define ERR(message) fprintf(stderr, (message))
#define DEBUG(message) if (DEBUG) \
    fprintf(stdout, (message))

int main(int argc, char** argv) {
    if (argc < 3) {
        ERR("Missing required parameters\n");
        return 1;
    }

    /* parse `from` addr and `to` addr */
    DEBUG("Parsing arguments\n");
    int from = 0;
    struct hostent *to = NULL;

    char* to_addr;
    strcpy(to_addr, argv[2]);
    char* to_ip = strtok(to_addr, ":");
    int to_port = atoi(strtok(NULL, ":"));
    to = gethostbyname(to_ip);
    if (to == NULL) {
        ERR("`to` server addr is invalid\n");
        return 1;
    }

    from = atoi(argv[2]);
    if (from < 1024) {
        ERROR("`from` addr is invalid\n");
        return 1;
    }

    /* open a connection to `to` server */
    DEBUG("Open a connection to `to` server\n");
    struct sockaddr_in to_server; 
    to_server.sin_family      = AF_INET;
    to_server.sin_port        = htons(to_port);
    to_server.sin_addr.s_addr = *((unsigned long*)to->h_addr);

    int to_client;
    if ((s = sock(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error occurs when creating `to_client` socket");
        return 1;
    }

    if (connect(s, (struct sockaddr* )&server, sizeof(server)) < 0) {
        perror("Error occurs when connecting to `to_server`");
        return 1;
    }

    /* create tcp server and forward any message to `to_server` via `to_client` */
    DEBUG("create tcp server and forward any message to `to_server` via `to_client`");
    struct sockaddr_in from_server;
    from_server.sin_family      = AF_INET;
    from_server.sin_port        = htons(from);
    from_server.sin_addr.s_addr = INADDR_ANY;

    int from_s;
    if (bind(from_s, (struct sockaddr *)&from_server, sizeof(server)) < 0) {
        perror("Error occurs when create `from_socket` for `from_server`");
        return 1;
    }
    


    return 0;
}
