#include <iostream>
#include <future>

#include "common/filewatcher.h"
#include "common/time_calculator.h"

namespace {
#ifndef __APPLE__
	constexpr const char *watch_file_skype_1 = "/home/ilia/.Skype/sc.ryabokon.ilia/main.db";
	constexpr const char *watch_file_skype_2 = "/home/ilia/.Skype/luxa_ryabic/main.db";
#else
	constexpr const char *watch_file_skype_1 = "/Users/ilia/Library/Application Support/Skype/sc.ryabokon.ilia/main.db";
    constexpr const char *watch_file_skype_2 = "/Users/ilia/Library/Application Support/Skype/luxa_ryabic/main.db";
#endif //__APPLE__
} //namespace

using namespace Boss;
using namespace std;
int main (int argc, char **argv) {
	uint64 ct = 0;
    {
		sm::filewatcher fw(watch_file_skype_1, [](const std::string &path, int) {
            std::cout << "Callback retrieved, incoming path: " << path << std::endl;
        });
        
        cout << "Attempting to start filewatcher" << endl;
        fw.start();
        cout << "fw.start() returned, catching events" << endl;
        sleep(30);
        cout << "Attempting to stop filewatcher" << endl;

        ct = GetTimeMs64();
        fw.stop();
        cout << "fw.stop() returned, elapsed time " << GetTimeMs64() - ct << "; catching events stopped. Ensuring stop watching" << endl;
        cout << "Finished, cleaning thread" << endl;
        ct = GetTimeMs64();
    }
    cout << "Watcher 1 is free; elapsed time: " << human_readable(GetTimeMs64() - ct) << endl;
    {
    	cout << "Creating new filewatcher" << endl;
    	sm::filewatcher fw(watch_file_skype_2, [](const std::string &path, int) {
    		std::cout << "Callback retrieved, incoming path: " << path << std::endl;
    	});
    	sleep(30);
    	cout << "Cleaning next fw" << endl;
    	ct = GetTimeMs64();
    }
    cout << "Cleaning finished; elapsed time: " << human_readable(GetTimeMs64() - ct) << endl;

    
    return 0;
}
