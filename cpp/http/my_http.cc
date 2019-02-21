#include <stdio.h>  
#include <stdlib.h>  
#include <arpa/inet.h>  
#include <netdb.h>  
#include <string.h>  
#include <unistd.h>
  
#include "my_http.h"  
  
#define BUFFER_SIZE 1024  
#define HTTP_POST "POST /%s HTTP/1.1\r\nHOST: %s:%d\r\nAccept: */*\r\n"\
    "Content-Type:application/x-www-form-urlencoded\r\nContent-Length: %d\r\n\r\n%s"  
#define HTTP_GET "GET /%s HTTP/1.1\r\nHOST: %s:%d\r\nAccept: */*\r\n\r\n"  
  
  
static int http_tcp_client_create(const char *host, const int &port){  
    struct hostent *he;  
    struct sockaddr_in server_addr;   
    int socket_fd;  
  
    if((he = gethostbyname(host)) == NULL){  
        return -1;  
    }  
  
   server_addr.sin_family = AF_INET;  
   server_addr.sin_port = htons(port);  
   server_addr.sin_addr = *((struct in_addr *)he->h_addr);  
  
    if((socket_fd = socket(AF_INET,SOCK_STREAM, 0)) == -1){  
        return -1;  
    }  
  
    if(connect(socket_fd, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1){  
        return -1;  
    }  
  
    return socket_fd;  
}  
  
static void http_tcp_client_close(int socket){  
    close(socket);  
}  
  
static int http_parse_url(const char *url, char *host, char *file, int &port)  
{  
    char *phost, *pfile;  
    int len = 0;  
    if(url == NULL || host == NULL || file == NULL || port != 0){  
        return -1;  
    }  
  
    phost = (char *)url;  
  
    if(!strncmp(phost, "http://", strlen("http://"))){  
        phost += strlen("http://");  
    }else{  
        return -1;  
    }  
  
    pfile = strchr(phost, '/');  
    if(pfile != NULL){  
        len = strlen(phost) - strlen(pfile);  
        memcpy(host, phost, len);  
        host[len] = '\0';  
        if(*(pfile + 1)){  
            memcpy(file, pfile + 1, strlen(pfile) - 1);  
            file[strlen(pfile) - 1] = '\0';  
        }  
    }else{  
        memcpy(host,phost,strlen(phost));  
        host[strlen(phost)] = '\0';  
    }  
    //get host and ip  
    phost = strchr(host,':');  
    if(phost != NULL){  
        *phost++ = '\0';  
        port = atoi(phost);  
    }else{  
        port = MY_HTTP_DEFAULT_PORT;  
    }  
  
    return 0;  
}  
  
  
static int http_tcp_client_recv(int socket, char *lpbuff){  
    int recv_num = 0;  
  
    recv_num = recv(socket, lpbuff,BUFFER_SIZE * 4, 0);  
  
    return recv_num;  
}  
  
static int http_tcp_client_send(int socket, char *buff, const int &size){  
    int sent=0, tmpres=0;  
  
    while(sent < size){  
        tmpres = send(socket, buff+sent, size-sent, 0);  
        if(tmpres == -1){  
            return -1;  
        }  
        sent += tmpres;  
    }  
    return sent;  
}  
  
static char *http_parse_result(const char* lpbuf)  
{  
    char *ptmp = NULL;   
    char *response = NULL;  
    ptmp = (char*)strstr(lpbuf,"HTTP/1.1");  
    if(ptmp == NULL){  
        printf("http/1.1 not faind\n");  
        return NULL;  
    }  
    if(atoi(ptmp + 9) != 200){  
        printf("result:\n%s\n",lpbuf);  
        return NULL;  
    }  
  
    ptmp = (char*)strstr(lpbuf, "\r\n\r\n");  
    if(ptmp == NULL){  
        printf("ptmp is NULL\n");  
        return NULL;  
    }  
    response = (char *)malloc(strlen(ptmp)+1);  
    if(response == NULL){  
        printf("malloc failed \n");  
        return NULL;  
    }  
    strcpy(response, ptmp+4);  
    return response;  
}  
  
char * http_post(const char *url,const char *post_str){  
  
    char post[BUFFER_SIZE] = {'\0'};  
    int socket_fd = -1;  
    char lpbuf[BUFFER_SIZE*4] = {'\0'};  
    char *ptmp;  
    char host_addr[BUFFER_SIZE] = {'\0'};  
    char file[BUFFER_SIZE] = {'\0'};  
    int port = 0;  
    int len=0;  
    char *response = NULL;  
  
    if(url == NULL || post_str == NULL){  
        printf("failed!\n");  
        return NULL;  
    }  
  
    if(http_parse_url(url, host_addr, file, port)){  
        printf("http_parse_url failed!\n");  
        return NULL;  
    }  
    //printf("host_addr : %s\tfile:%s\t,%d\n",host_addr,file,port);  
  
    socket_fd = http_tcp_client_create(host_addr, port);  
    if(socket_fd < 0){  
        printf("http_tcp_client_create failed\n");  
        return NULL;  
    }  
       
    sprintf(lpbuf, HTTP_POST, file, host_addr, port, strlen(post_str), post_str);  
  
    if(http_tcp_client_send(socket_fd, lpbuf, strlen(lpbuf)) < 0){  
        printf("http_tcp_client_send failed..\n");  
        return NULL;  
    }  
    //printf("发送请求:\n%s\n",lpbuf);  
  
    /*it's time to recv from server*/  
    if(http_tcp_client_recv(socket_fd, lpbuf) <= 0){  
        printf("http_tcp_client_recv failed\n");  
        return NULL;  
    }  
  
    http_tcp_client_close(socket_fd);  
  
    return http_parse_result(lpbuf);  
}  
  
char * http_get(const char *url)  
{  
  
    char post[BUFFER_SIZE] = {'\0'};  
    int socket_fd = -1;  
    char lpbuf[BUFFER_SIZE*4] = {'\0'};  
    char *ptmp;  
    char host_addr[BUFFER_SIZE] = {'\0'};  
    char file[BUFFER_SIZE] = {'\0'};  
    int port = 0;  
    int len=0;  
  
    if(url == NULL){  
        printf("failed!\n");  
        return NULL;  
    }  
  
    if(http_parse_url(url, host_addr, file, port)){  
        printf("http_parse_url failed!\n");  
        return NULL;  
    }  
    //printf("host_addr : %s\tfile:%s\t,%d\n",host_addr,file,port);  
  
    socket_fd =  http_tcp_client_create(host_addr, port);  
    if(socket_fd < 0){  
        printf("http_tcp_client_create failed\n");  
        return NULL;  
    }  
  
    sprintf(lpbuf, HTTP_GET, file, host_addr, port);  
  
    if(http_tcp_client_send(socket_fd, lpbuf, strlen(lpbuf)) < 0){  
        printf("http_tcp_client_send failed..\n");  
        return NULL;  
    }  
//  printf("发送请求:\n%s\n",lpbuf);  
  
    if(http_tcp_client_recv(socket_fd,lpbuf) <= 0){  
        printf("http_tcp_client_recv failed\n");  
        return NULL;  
    }  
    http_tcp_client_close(socket_fd);  
  
    return http_parse_result(lpbuf);  
} 
