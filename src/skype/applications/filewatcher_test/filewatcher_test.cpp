#include <iostream>
#include <future>

#include "common/filewatcher.h"

namespace {
#ifndef __APPLE__
	constexpr const char *watch_file = "/home/ilia/.Skype/sc.ryabokon.ilia/main.db";
#else
	constexpr const char *watch_file = "/Users/ilia/Library/Application Support/Skype/sc.ryabokon.ilia/main.db";
#endif //__APPLE__
} //namespace

int main (int argc, char **argv) {
    {
        using namespace std;
        
        sm::filewatcher fw(watch_file, [](const std::string &path, int) {
            std::cout << "Callback retrieved, incoming path: " << path << std::endl;
        });
        
        cout << "Attempting to start filewatcher" << endl;
        fw.start();
        cout << "fw.start() returned, catching events" << endl;
        sleep(60);
        cout << "Attempting to stop filewatcher" << endl;
        fw.stop();
        cout << "fw.stop() returned, catching events stopped. Ensuring stop watching" << endl;
        sleep(5);
        cout << "Finished, cleaning thread" << endl;
    }
    
    return 0;
}
