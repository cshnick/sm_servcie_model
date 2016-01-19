#include <iostream>
#include "litesql.hpp"
#include "skype_main_db.hpp"
#include "common/sm_debug.h"
#include <random>

// no name collisions expected
using namespace litesql;
using namespace SkypeDB;
using namespace std;
using namespace sm;

int misc_test() {
	SkypeDB::main db("sqlite3", "database=/Users/ilia/Library/Application Support/Skype/sc.ryabokon.ilia/main.db");
	SkypeDB::main gen_db("sqlite3", "database=gen_main.db");
	// create tables, sequences and indexes
	db.verbose = true;
	auto ds = select<Messages>(db, Messages::Id > 100 && Messages::Id < 200);
	SelectQuery q;
	q.result("max(id)");
	q.source(SkypeDB::Messages::table__);
	int r1 = atoi(db.query(q)[0][0]);

	return r1;
}

int expand_database() {
    try {
        int messages_bound = 120000;
        int package = 1000;
        SkypeDB::main db("sqlite3", "database=/Users/ilia/Library/Application Support/Skype/sc.ryabokon.ilia/main.db");
        SkypeDB::main gen_db("sqlite3", "database=/home/ilia/Development/cmake_sm/bin/gen_main.db");
        
        /*if (gen_db.needsUpgrade()) {
         gen_db.upgrade();
         }*/
        
        std::default_random_engine generator;
        
        int dest_count = select<SkypeDB::Messages>(gen_db).count();
        int delta = messages_bound - dest_count;
        
        if (delta <= 0) {
            dcout << "The base is big enough" << endl;
            return 0;
        }
        
        auto m_vec = select<SkypeDB::Messages>(db).all();
        std::uniform_int_distribution<int> m_dist(0, m_vec.size() - 1);
        for (int i = 0, bound = delta; delta; delta--,i++) {
            
            if (i % package == 0) {
                gen_db.begin();
                //dcout << "gen_db.begin" << endl;
            }
            
            SkypeDB::Messages ins_candidate(gen_db);
            SkypeDB::Messages donor = m_vec.at(m_dist(generator));
            
            ins_candidate.is_permanent = donor.is_permanent;
            ins_candidate.convo_id = donor.convo_id;
            ins_candidate.author_was_live = donor.author_was_live;
            ins_candidate.guid = donor.guid;
            ins_candidate.timestamp = donor.timestamp;
            ins_candidate.sending_status = donor.sending_status;
            ins_candidate.consumption_status = donor.consumption_status;
            ins_candidate.edited_timestamp = donor.edited_timestamp;
            ins_candidate.param_key = donor.param_key;
            ins_candidate.param_value = donor.param_value;
            ins_candidate.leavereason = donor.leavereason;
            ins_candidate.participant_count = donor.participant_count;
            ins_candidate.error_code = donor.error_code;
            ins_candidate.chatmsg_type = donor.chatmsg_type;
            ins_candidate.chatmsg_status = donor.chatmsg_status;
            ins_candidate.body_is_rawxml = donor.body_is_rawxml;
            ins_candidate.oldoptions = donor.oldoptions;
            ins_candidate.newoptions = donor.newoptions;
            ins_candidate.newrole = donor.newrole;
            ins_candidate.pk_id = donor.pk_id;
            ins_candidate.crc = donor.crc;
            ins_candidate.remote_id = donor.remote_id;
            
            ins_candidate.update();
            
            dcout << "\r" << i << " - " << i * 100 / bound  << "%";
            if ((i % package == package - 1) || (delta == 1)) {
                gen_db.commit();
                //dcout << "gen_db.commit" << endl;
            }
        }
        
        dcout << endl << "New base elements count: " << select<SkypeDB::Messages>(gen_db).count() << endl;
        
    } catch (const Except &e) {
        std::cerr << "Error: " << e << std::endl;
    }
    
    return 0;
}

int main(int argc, char **argv) {
	
    return misc_test();
}

