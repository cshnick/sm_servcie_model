/*
 * skype_main_methods.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: ilia
 */
#include "skype_main_db.hpp"

namespace SkypeDB {

litesql::Field<std::string> Chats::* Chats::cache_field() {
	return &Chats::name;
}
litesql::Field<std::string> Contacts::* Contacts::cache_field() {
	return &Contacts::skypename;
}

} //namespace SkypeDB



