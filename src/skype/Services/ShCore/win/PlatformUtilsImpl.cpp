#include "../PlatformUtilsImpl.h"

#include <direct.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <codecvt>
#include <Shlobj.h>

#include "core/error_codes.h"
#include "common/string.h"
#include "common/string_helper.h"
#include "common/enum.h"
#include "common/sm_debug.h"

namespace skype_sc {
using namespace std;
using namespace Boss;
using namespace sm;

PlatformUtilsImpl::PlatformUtilsImpl() {
	// TODO Auto-generated constructor stub
}

PlatformUtilsImpl::~PlatformUtilsImpl() {
	// TODO Auto-generated destructor stub
}

Boss::RetCode BOSS_CALL PlatformUtilsImpl::SkypeLocation(Boss::IString **result_string) {
	dcout << "PlatformUtils::SkypeLocation" << endl;
	wchar_t wide_path[_MAX_PATH]; PWSTR buf_str = wide_path;
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT_PATH, NULL, &buf_str);
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;	std::string u8_buf = converter.to_bytes(buf_str);
	u8_buf.append("\\Skype");
	auto location = Base<String>::Create(u8_buf);

	return location.QueryInterface(result_string);
}
Boss::RetCode BOSS_CALL PlatformUtilsImpl::UserSettingsDir(Boss::IString **result_string)  {
	dcout << "PlatformUtils::UserSettingsDir" << endl;
	wchar_t wide_path[_MAX_PATH]; PWSTR buf_str = wide_path;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DEFAULT_PATH, NULL, &buf_str);
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;	std::string u8_buf = converter.to_bytes(buf_str);
	auto location = Base<String>::Create(u8_buf);

	return location.QueryInterface(result_string);
}

namespace {
	Boss::RetCode CheckStat(Boss::IString *filename, bool *result, bool(*check_mode)(DWORD file_attrs)) {
		std::string std_name = StringHelper(filename).GetString<IString::AnsiString>();
		*result = false;
		DWORD attrs = -1;

		std::string std_file = StringHelper(filename).GetString<>();
		WIN32_FIND_DATA fd;
		HANDLE hFind = FindFirstFile(std_file.c_str(), &fd);

		if (hFind != INVALID_HANDLE_VALUE) {
			attrs = fd.dwFileAttributes;
		}

		if (check_mode(attrs)) {
			*result = true;
		}

		return Status::Ok;
	}
	int do_mkdir(const char *path)
	{
		DWORD           attrs = -1;
		WIN32_FIND_DATA fd;
		int             status = 0;

		if (FindFirstFile(path, &fd) == INVALID_HANDLE_VALUE) {
			if (_mkdir(path) != 0 && errno != EEXIST) 
				status = -1;
		}
		else {
			DWORD attrs = fd.dwFileAttributes;
			if (!(attrs & FILE_ATTRIBUTE_DIRECTORY)) {
				errno = ENOTDIR;
				status = -1;
			}
		}

		return(status);
	}
	int mkpath(const char *path)
	{
		char *pp = nullptr, *sp = nullptr;
		int status = -1;
		char *copypath = strdup(path), *parsed_path = copypath;
		for (; *parsed_path; ++parsed_path) {
			switch (*parsed_path) {
			case '\\':
				*parsed_path = '/';
				break;
			}
		}
		status = 0;
		pp = copypath;
		while (status == 0 && (sp = strchr(pp, '/')) != 0) {
			if (sp != pp) {
				*sp = '\0';
				status = do_mkdir(copypath);
				*sp = '/';
			}
			pp = sp + 1;
		}
		if (status == 0)
			status = do_mkdir(path);
		free(copypath);
		return (status);
		return 0;
	} 
} //namespace

Boss::RetCode BOSS_CALL PlatformUtilsImpl::Exists(Boss::IString *filename, bool *exists) {
	dcout << "PlatformUtilsImpl::Exists" << endl;
	*exists = false;
	return CheckStat(filename, exists, [](DWORD attrs) -> bool {
		return (attrs != -1) && 
			   ((attrs &  FILE_ATTRIBUTE_DIRECTORY) || (attrs &  FILE_ATTRIBUTE_NORMAL));
	});
	return Status::Ok;
}

Boss::RetCode BOSS_CALL PlatformUtilsImpl::IsDir(Boss::IString *filename, bool *exists) {
	dcout << "PlatformUtilsImpl::IsDir" << endl;
	*exists = false;
	return CheckStat(filename, exists, [](DWORD attrs) -> bool {
		return (attrs != -1) &&
			   (attrs &  FILE_ATTRIBUTE_DIRECTORY);
	});
	return Status::Ok;
}
Boss::RetCode BOSS_CALL PlatformUtilsImpl::IsFile(Boss::IString *filename, bool *exists) {
	dcout << " PlatformUtilsImpl::IsFile" << endl;
	*exists = false;
	return CheckStat(filename, exists, [](DWORD attrs) -> bool {
		return (attrs != -1) &&
			   (attrs &  FILE_ATTRIBUTE_NORMAL);
	});
	return Status::Ok;
}
Boss::RetCode BOSS_CALL PlatformUtilsImpl::MkPath(Boss::IString *path, bool *ok) {
	dcout << "PlatformUtilsImpl::MkPath" << endl;
	*ok = !mkpath(StringHelper(path).GetString<>().c_str());
	return Status::Ok;
}
Boss::RetCode BOSS_CALL PlatformUtilsImpl::FindAccounts(Boss::IEnum **result_enum) {
	dcout << "PlatformUtilsImpl::FindAccounts" << endl;
	return Boss::Status::NotImplemented;
}
RetCode PlatformUtilsImpl::Children(IString *parent, IEnum **children) {
	dcout << "PlatformUtilsImpl::Children" << endl;
	auto result = Base<Enum>::Create();
	std::string std_parent = StringHelper(parent).GetString();
	std_parent.append("\\*");
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(std_parent.c_str(), &ffd);
	if (hFind == INVALID_HANDLE_VALUE) {
		result.QueryInterface(children);
		return Status::Ok;
	}
	do {
		if (!strcmp(ffd.cFileName, ".") || !strcmp(ffd.cFileName, "..")) {
			continue;
		}
		result->AddItem(Base<String>::Create(ffd.cFileName));
		//dcout << "next filename: " << ffd.cFileName << std::endl;
	} while (FindNextFile(hFind, &ffd));
	FindClose(hFind);

	return result.QueryInterface(children);
}

} /* namespace skype_sc */
