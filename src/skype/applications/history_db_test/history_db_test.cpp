#include <iostream>

#include "history_main_db.hpp"
#include "litesql.hpp"

#include "common/time_calculator.h"

int main (int argc, char **argv) {
    using namespace HistoryDB;
    using namespace litesql;
    using namespace std;
    try {
        cout << "HistoryDB test..." << endl;
        HistoryDB::history db("sqlite3", "database=history.db");
        int mcnt = select<Messages>(db).count();
        cout << "Messages count: " << mcnt << endl;
        
        cout << "Select 20 latest messages and associated info..." << endl;
        auto ms = select<Messages>(db).orderBy(Messages::Skype_timestamp, false).all();
        for (int i = 0; i < 20 && i < mcnt; i++) {
            Messages m = ms.at(i);
            auto convs = m.conversation().get().all();
            Conversations conv = convs.at(0);
            auto usrs = conv.users().get().all();
            
            cout << "Message: " << m.id << endl;
            cout << "\tBody: "  << m.body << endl;
            cout << "\tConversation: " << conv.friendlyname << endl;
            cout << "\tConversation users: ";
            for (Users usr : usrs) cout << " " << usr.name;
            cout << ";" << endl;
        }
        
        cout << "Cashing the whole data..." << endl;
        int percent = 0, counter = 0;
        Boss::uint64 ctime = Boss::GetTimeMs64();
        for (Messages m : ms) {
            percent = counter * 100 / mcnt;
            cout << "\r" << percent << "%" << flush;
            auto convs = m.conversation().get().all();
            assert(convs.size() == 1);
            auto conv = convs.at(0);
            auto usrs = conv.users().get().all();
            counter++;
        }
        cout << endl;
        cout << "Caching finished, elaped time ms: " << Boss::GetTimeMs64() - ctime << endl;
        
    } catch (const Except &e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}

