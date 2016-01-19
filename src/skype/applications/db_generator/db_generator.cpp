/*
 * db_generator.cpp
 *
 *  Created on: 10 нояб. 2015 г.
 *      Author: ilia
 */

#include <iostream>
#include <sstream>
#include "litesql.hpp"
#include "skype_main_db.hpp"

#include "common/sm_debug.h"

using namespace std;
using namespace sm;
namespace {
	void print_usage() {
		dcout << "Usage: ./db_generator dbfile" << endl;
	}
} //namespace

int main (int argc, char **argv) {

	if (argc < 1) {
		print_usage();
		return 1;
	}

	string filename(argv[1]);
	using namespace SkypeDB;
	using namespace litesql;
	stringstream ss;
	ss << "database=" << filename;

	try {
		Database db("sqlite3", ss.str());

		auto mess = select<Messages>(db).all();
		auto contacts = select<Contacts>(db).all();

	} catch (const std::exception &e) {
		dcout << e.what() << endl;
		return 1;
	}


	return 0;
}


