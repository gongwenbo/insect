//
// Created by lenfien on 16-10-24.
//

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <cstring>
#include <atomic>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>
#include "Real/PackageListener.h"

using namespace std;
using namespace chrono;

enum Mode {
    BATCH, LOOP, ECHO, REAL
};

void init() {
    /* 信号 */
    {
        struct sigaction sa;
        sa.sa_handler = SIG_IGN;
        sigfillset (&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction (SIGPIPE, &sa, nullptr);
    }

    /* Resouce limit */
    {
        int err;
        struct rlimit lim;
        if (geteuid() == 0) {
            lim.rlim_max = 1000000;
            lim.rlim_cur = lim.rlim_max;
            setrlimit (RLIMIT_NOFILE, &lim);
        }
        else {
            getrlimit (RLIMIT_NOFILE, &lim);
            lim.rlim_cur = lim.rlim_max;
            setrlimit (RLIMIT_NOFILE, &lim);
        }

        getrlimit (RLIMIT_NOFILE, &lim);

        cout << "Rlimit opened file : " << lim.rlim_cur << endl;
    }
}


int main(int argc, char *argv[]) {

    const char *cmode;
    const char *host;

    if (argc == 1) {
        cmode = "echo";
        host = "localhost";
    }
    else if (argc == 2) {
        cmode = argv[1];
        host = "localhost";
    }
    else if (argc == 3) {
        host = argv[1];
        cmode = argv[2];
    }

    init ();

    addrinfo hint;
    memset (&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_flags = 0;
    hint.ai_protocol = IPPROTO_TCP;
    hint.ai_socktype = SOCK_STREAM;

    addrinfo *result = nullptr;

    int err;
    if ((err = getaddrinfo (host, "8080", &hint, &result)) != 0) {
        printf ("%s\n", gai_strerror(err));
        return 1 ;
    }

    Mode mode;
    if (strcmp(cmode, "batch") == 0)
        mode = BATCH;
    else if (strcmp(cmode, "loop") == 0)
        mode = LOOP;
    else if (strcmp(cmode, "echo") == 0)
        mode = ECHO;
    else if (strcmp(cmode, "real") == 0)
        mode = REAL;

    if (mode == BATCH) {
        std::vector<int> socks;
        for (int i = 0; i < 10240; ++i) {
            int sock = socket (result->ai_family, result->ai_socktype, result->ai_protocol);
            if (sock == -1) {
                perror ("Socket:");
                break;
            }

            if (connect (sock, result->ai_addr, result->ai_addrlen) == -1) {
                perror ("connect");
                return 3;
            }
            socks.push_back(sock);
        }

        for_each (socks.begin(), socks.end(), [](int sock) {close(sock);});
    }
    else if (mode == LOOP) {
        for (;;) {
            int sock = socket (result->ai_family, result->ai_socktype, result->ai_protocol);
            if (sock == -1) {
                perror ("Socket:");
                break;
            }

            if (connect (sock, result->ai_addr, result->ai_addrlen) == -1) {
                perror ("connect");
                return 3;
            }

            close (sock);
            usleep (1000);
        }
    }
    else if (mode == ECHO){
        for (int i = 0; i < 100; ++i) {
            if (fork() != 0)
                continue;

            char buf[128];
            ssize_t rn;
            std::chrono::time_point<steady_clock> beg, end;

            int sock = socket (result->ai_family, result->ai_socktype, result->ai_protocol);
            if (sock == -1) {
                perror ("socket");
                return 2;
            }

            if (connect (sock, result->ai_addr, result->ai_addrlen) == -1) {
                perror ("connect");
                return 3;
            }

            while (true) {
                ssize_t sn = send (sock, "a", 1, 0);
                beg = chrono::steady_clock::now();
                recv (sock, buf, sizeof(buf) - 1, 0);
                end = chrono::steady_clock::now();
                cout << (duration_cast<milliseconds>(end - beg)).count() << "ms" << endl;

                usleep ((__useconds_t) (500000 + (rand() % 500000)));
            }
        }
    }
    else if (mode == REAL) {
        PackageListener listener;

        int sock = socket (result->ai_family, result->ai_socktype, result->ai_protocol);
        if (sock == -1) {
            perror ("socket");
            return 2;
        }

        if (connect (sock, result->ai_addr, result->ai_addrlen) == -1) {
            perror ("connect");
            return 3;
        }

        char head[512] = "1 2 3 4 location 1024";
        vector<unsigned char> buffer(512 + 1024);
        for (int i = 0; i < sizeof(head); ++i)
            buffer[i] = head[i];

        shared_ptr<vector<unsigned char>> msg = listener.encode(buffer.begin(), buffer.end());
        for (;;) {
            send(sock, &(*msg->begin()), msg->size(), 0);
            getchar ();
            usleep (1000);
            cout << "ONE time" << endl;
        }
        close (sock);
    }
}
