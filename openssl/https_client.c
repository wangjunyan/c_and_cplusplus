//gcc -o https https_client.c -lssl -lcrypto

#include<stdio.h>
#include<memory.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

#include<openssl/crypto.h>
#include<openssl/x509.h>
#include<openssl/pem.h>
#include<openssl/ssl.h>
#include<openssl/err.h>

void main(int argc, char **argv)
{
    SSL *ssl;
    SSL_CTX *ctx;
    SSL_METHOD *client_method;
    X509 *server_cert;
    int sd, err;
    char *str, *hostname, outbuf[4096], inbuf[4096], host_header[512];
    struct hostent *host_entry;
    struct sockaddr_in server_socket_address;
    struct in_addr ip;

    SSLeay_add_ssl_algorithms();
    client_method = SSLv3_client_method();
    SSL_load_error_strings();
    ctx = SSL_CTX_new(client_method);
    printf("(1) SSL context initialized\n\n");

    hostname = argv[1];
    host_entry = gethostbyname(hostname);
    bcopy(host_entry->h_addr, &(ip.s_addr), host_entry->h_length);
    printf("(2) '%s' has ip address '%s'\n\n", hostname, inet_ntoa(ip));

    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_socket_address, '\0', sizeof(server_socket_address));
    server_socket_address.sin_family = AF_INET;
    server_socket_address.sin_port = htons(443);
    memcpy(&(server_socket_address.sin_addr.s_addr), host_entry->h_addr, host_entry->h_length);
    err= connect(sd, (struct sockaddr*)&server_socket_address, sizeof(server_socket_address));
    if (err < 0)
    {
        perror("can't connect to server port");
        exit(1);
    }
    printf("(3) TCP connection open to host '%s', port %d\n\n", hostname, server_socket_address.sin_port);

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sd);
    err = SSL_connect(ssl);
    printf("(4) SSL endpoint created & handshake completed\n\n");

    printf("(5) SSL connected with cipher: %s\n\n", SSL_get_cipher(ssl));

    server_cert = SSL_get_peer_certificate(ssl);
    printf("(6) server's certificate was received:\n\n");
    str = X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0);
    printf("    subject: %s\n", str);
    str = X509_NAME_oneline(X509_get_issuer_name(server_cert), 0, 0);
    printf("    issuer: %s\n\n", str);

    X509_free(server_cert);

    sprintf(host_header, "Host: %s:443\r\n", hostname);
    strcpy(outbuf, "GET / HTTP/1.1\r\n");
    strcat(outbuf, host_header);
    strcat(outbuf, "Connection: close\r\n");
    strcat(outbuf, "\r\n");

    err = SSL_write(ssl, outbuf, strlen(outbuf));
    //shutdown(sd, 1);
    printf("(7) sent HTTP request over encrypted channel:\n\n%s\n", outbuf);

    err = SSL_read(ssl, inbuf, sizeof(inbuf) - 1);
    inbuf[err] = "\0";
    printf("(8) got back %d bytes of HTTP response:\n\n%s\n", err, inbuf);

    SSL_shutdown(ssl);
    close(sd);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    printf("(9) all done, cleaned up and closed connection\n\n");
    return;
}
