/*
 * skype_main_methods.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: ilia
 */
#include "history_main_db.hpp"

namespace HistoryDB {

litesql::Field<std::string> Chats::* Chats::cache_field() {
	return &Chats::name;
}

litesql::Field<std::string> Users::* Users::cache_field() {
	return &Users::name;
}

litesql::Field<int> Messages::* Messages::cache_field() {
	return &Messages::skype_id;
}

} //namespace HistoryDB



