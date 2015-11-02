#include <iostream>
#include <future>

#include "common/filewatcher.h"

int main (int argc, char **argv) {
    {
        sm::filewatcher fw("/Users/ilia/Library/Application Support/Skype/sc.ryabokon.ilia/main.db", [](const std::string &path, int) {
            std::cout << "Callback retreived, incoming path: " << path << std::endl;
        });
        fw.start();
        sleep(300);
        fw.stop();
        sleep(5);
    }
    
    return 0;
}
