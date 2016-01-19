#include "common/sm_debug.h"

namespace sm {
	dostream dcout;

	std::string cwd() {
		char res[FILENAME_MAX];
		if (!SM_GET_CWD(res, sizeof(res))) {
			return std::string();
		}
		return res;
	}

	std::pair<std::string, std::string> split_argv0(const std::string& str) {
		std::size_t found = str.find_last_of("/\\");
		return std::make_pair(str.substr(0, found), str.substr(found + 1));
	}
}