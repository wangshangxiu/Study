#include<iostream>
using namespace std;

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void do_read(int efd, int sock) {
    cout << "do_read" << endl;
    char buf[1024] = {0};
    int ret = read(sock, buf, sizeof buf);
    if (ret == -1) {
        cout << "read error" << endl;
    }

    epoll_event ev;
    ev.events |= EPOLLOUT;
//    ev.events |= EPOLLIN;
    ev.data.fd = sock;

    ret = epoll_ctl(efd, EPOLL_CTL_MOD, sock, &ev);
//    ret = epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ev);
    if (ret == -1) {
        cout << "epoll_ctl error" << endl;
        cout << strerror(errno) << endl;
    }

    buf[ret] = '\0';
    cout << buf << endl;
}

void do_write(int efd, int sock) {
    cout << "do_write" << endl;
    char buf[1024] = {0};
    memcpy(buf, "hello!", 6);
    int ret = write(sock, buf, sizeof buf);
    if (ret == -1) {
        cout << "write  error" << endl;
        return;
    }

    epoll_event ev;
    ev.events |= EPOLLOUT;
    ev.data.fd = sock;
    ret = epoll_ctl(efd, EPOLL_CTL_DEL, sock, &ev);

    if (ret == -1) {
        cout << "epoll_ctl error" << endl;
    }
}

int main(int argc, char *argv[]) {
    int listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == -1) {
        cout << "socket error" << endl;
        return -1;
    }


    sockaddr_in addr;
    addr.sin_family = AF_INET;
//    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_addr.s_addr = inet_addr("10.10.10.181");
//    addr.sin_addr.s_addr = inet_network("127.0.0.1");
//    addr.sin_addr.s_addr = inet_network("10.10.10.181");

    addr.sin_port = htons(7000);

    int ret = bind(listenSock, (sockaddr*)&addr, sizeof addr);
    if (ret == -1) {
        cout << "bind error" << endl;
        cout << strerror(errno) << endl;
        return -1;
    }

    if (listen(listenSock, 128) == -1) {
        cout << "listen error" << endl;
        return -1;
    }

    int efd = epoll_create(1024);
    if (efd == -1) {
        cout << "epoll_create error" << endl;
        return -1;
    }

    epoll_event evr, evw;
    epoll_event events[1024] = {0};
    evr.events |= EPOLLIN;
    evr.data.fd = listenSock;

    evw.events |= EPOLLOUT;
    evw.data.fd = listenSock;

    if (epoll_ctl(efd, EPOLL_CTL_ADD, listenSock, &evr) == -1) {
        cout << "epoll_ctl error" << endl;
        return -1;
    }
//    if (epoll_ctl(efd, EPOLL_CTL_ADD, listenSock, &evw) == -1) {
//        return -1;
//    }

    while (true) {
        static int cnt = 0;
        int num = epoll_wait(efd, events, 1024, 1000);
        cnt++;
        for (int i = 0; i < num; i++) {
            if (events[i].events & EPOLLIN) {
                int clientSock;
                sockaddr clientAddr;
                socklen_t len = sizeof clientAddr;
                if (events[i].data.fd == listenSock) {
                    clientSock = accept(listenSock, &clientAddr, &len);
                    if (clientSock== -1) {
                        cout << "accept error" << endl;
                        return -1;
                    } else {
                        epoll_event evr;
                        evr.events |= EPOLLIN;
//                        evr.events |= EPOLLOUT;
                        evr.data.fd = clientSock;
                        if (epoll_ctl(efd, EPOLL_CTL_ADD, clientSock, &evr) == -1) {
                            cout << "internal epoll_ctl error" << endl;
                            return -1;
                        }

//                        epoll_event listenEv;
//                        listenEv.events |= EPOLLIN;
//                        listenEv.data.fd = listenSock;
//                        if (epoll_ctl(efd, EPOLL_CTL_DEL, listenSock, &listenEv) == -1) {

//                        }

                        cout << "accept new connection!" << endl;
                    }
                } else {
                    do_read(efd, events[i].data.fd);
                }
            }

            if (events[i].events & EPOLLOUT) {
                 do_write(efd, events[i].data.fd);
            }
        }

        cout << "cnt = " << cnt << endl;
    }
}
