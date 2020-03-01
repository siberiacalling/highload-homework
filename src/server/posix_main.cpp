#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "server.hpp"
#include <fstream>
#include "config.hpp"

#if !defined(_WIN32)

#include <pthread.h>
#include <signal.h>


int main(int argc, char *argv[]) {
    try {
        // Block all signals for background thread.
        sigset_t new_mask;
        sigfillset(&new_mask);
        sigset_t old_mask;
        pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);

        Config conf;
        std::size_t num_threads = std::stoi(conf.thread_limit);
        std::string port = conf.port;
        std::string address = conf.address;
        std::string document_root = conf.document_root;
        http::server3::server s(address, port, document_root, num_threads);
        boost::thread t(boost::bind(&http::server3::server::run, &s));

        // Restore previous signals.
        pthread_sigmask(SIG_SETMASK, &old_mask, 0);

        // Wait for signal indicating time to shut down.
        sigset_t wait_mask;
        sigemptyset(&wait_mask);
        sigaddset(&wait_mask, SIGINT);
        sigaddset(&wait_mask, SIGQUIT);
        sigaddset(&wait_mask, SIGTERM);
        pthread_sigmask(SIG_BLOCK, &wait_mask, 0);
        int sig = 0;
        sigwait(&wait_mask, &sig);

        // Stop the server.
        std::cerr << "Server stopped" << std::endl;
        s.stop();
        t.join();
    }
    catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}

#endif // !defined(_WIN32)