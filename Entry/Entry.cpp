#include "../Com/Conf.h"
#include "../EpollSys/EPollSystem.h"
#include "../OpCenter/OpCenter.h"
#include "../Real/Terminal.h"
#include "../Runner/DoPoll.h"

#include <sys/resource.h>

using namespace std;

//hello

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
            err = setrlimit (RLIMIT_NOFILE, &lim);
            if (err == -1)
                Syslog::err("setrlimit failed");
        }
        else {
            getrlimit (RLIMIT_NOFILE, &lim);
            lim.rlim_cur = lim.rlim_max;
            err = setrlimit (RLIMIT_NOFILE, &lim);
            if (err == -1)
                Syslog::err("setrlimit failed");
        }

        getrlimit (RLIMIT_NOFILE, &lim);
        Syslog::log("Max open file :" + to_string(lim.rlim_cur));
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp("-daemon", argv[1]) == 0)
        daemon(0, 0);

    init();
    int epollfd = epoll_create1(0);
    TerminalFactory* terminalFactory = new TerminalFactory();
    OpCenter* ePollCenter = new OpCenter(epollfd, terminalFactory);
    new EPollSystem(epollfd, ePollCenter);
    new DoPoll(ePollCenter);

    while (true) pause();
    return 0;
}
