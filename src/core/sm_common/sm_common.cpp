#include "common/sm_debug.h"
#include "core/utils.h"

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

	void sleep(int secs) {
#if defined(_WIN32)
		::Sleep(secs * 1000);
#elif defined(__unix) || defined(__APPLE)
		::sleep(secs);
#endif //defined(_WIN32)
	}
}
