#include <iostream>

#include "history_main_db.hpp"
#include "litesql.hpp"
#include "plugin/loader.h"
#include "ifaces.h"
#include "class_ids.h"
#include "skype_helpers.h"

#include "common/time_calculator.h"
#include "common/sm_debug.h"

using namespace sm;

int main (int argc, char **argv) {
	using namespace Boss;
    using namespace HistoryDB;
    using namespace litesql;
    using namespace std;
    using namespace skype_sc;

    Boss::Loader Ldr("sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
    		                       MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory"));

    try {
    	auto settings = CreateObject<ISettings>(service::id::Settings);
    	Settings_hlpr shlpr(settings);
    	std::string hdbpath = shlpr.Accounts().at(shlpr.DefaultAccount()).HistoryDBPath();

        dcout << "HistoryDB test..." << endl;
        string hdbfile = std::string("database=") + (hdbpath.empty() ? "history.db" : hdbpath + "/history.db");
        dcout << "HistoryDB file: " << hdbfile;
        HistoryDB::history db("sqlite3", hdbfile);
        int mcnt = select<Messages>(db).count();
        dcout << "Messages count: " << mcnt << endl;
        
        dcout << "Select 20 latest messages and associated info..." << endl;
        auto ms = select<Messages>(db).orderBy(Messages::Skype_timestamp, false).all();
        for (int i = 0; i < 20 && i < mcnt; i++) {
            Messages m = ms.at(i);
            auto convs = m.conversation().get().all();
            Conversations conv = convs.at(0);
            auto usrs = conv.users().get().all();
            
            dcout << "Message: " << m.id << endl;
            dcout << "\tBody: "  << m.body << endl;
            dcout << "\tConversation: " << conv.friendlyname << endl;
            dcout << "\tConversation users: ";
            for (Users usr : usrs) dcout << " " << usr.name;
            dcout << ";" << endl;
        }
        
        dcout << "Cashing the whole data..." << endl;
        int percent = 0, counter = 0;
        Boss::uint64 ctime = Boss::GetTimeMs64();
        for (Messages m : ms) {
            percent = counter * 100 / (mcnt - 1);
            dcout << "\r" << percent << "%" << flush;
            auto convs = m.conversation().get().all();
            assert(convs.size() == 1);
            auto conv = convs.at(0);
            auto usrs = conv.users().get().all();
            counter++;
        }
        dcout << endl;
        dcout << "Caching finished, elapsed time ms: " << Boss::GetTimeMs64() - ctime << endl;
        
    } catch (const Except &e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}

