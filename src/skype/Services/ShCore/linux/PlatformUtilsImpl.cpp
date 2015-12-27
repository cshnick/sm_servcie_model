/*
 * PlatformUtils.cpp
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: ilia
 */

#include "../PlatformUtilsImpl.h"
#include <iostream>
#include "core/error_codes.h"
#include "common/string.h"
#include "common/string_helper.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>


namespace skype_sc {
using namespace std;
using namespace Boss;

PlatformUtilsImpl::PlatformUtilsImpl() {
	// TODO Auto-generated constructor stub
	cout << "PlatformUtils::PlatformUtils()" <<  endl;
}

PlatformUtilsImpl::~PlatformUtilsImpl() {
	cout << "PlatformUtilsImpl::~PlatformUtilsImpl()" << endl;
	// TODO Auto-generated destructor stub
}

Boss::RetCode BOSS_CALL PlatformUtilsImpl::SkypeLocation(Boss::IString **res) {
	struct passwd *pw = getpwuid(getuid());
	std::string std_loc(pw->pw_dir);
	std_loc.append("/.Skype/");

	auto location = Base<String>::Create(std_loc);
	return location.QueryInterface(res);
}
Boss::RetCode BOSS_CALL PlatformUtilsImpl::UserSettingsDir(Boss::IString **res)  {
	cout << "PlatformUtils::UserSettingsDir" << endl;
	struct passwd *pw = getpwuid(getuid());
	std::string std_loc(pw->pw_dir);
	std_loc.append("/.local/");

	auto location = Base<String>::Create(std_loc);
	return location.QueryInterface(res);

	return Boss::Status::Ok;
}

namespace {
Boss::RetCode CheckStat(Boss::IString *filename, bool *result, bool (*check_mode)(const struct stat&)) {
	std::string std_name = StringHelper(filename).GetString<IString::AnsiString>();
	*result = false;
	struct stat sb;

	if (stat(std_name.c_str(), &sb) == -1) {
		*result = false;
		return Status::Ok;
	}

	if (check_mode(sb)) {
		*result = true;
	}

	return Status::Ok;
}
typedef struct stat Stat;
static int do_mkdir(const char *path, mode_t mode)
{
    Stat            st;
    int             status = 0;

    if (stat(path, &st) != 0) {
        /* Directory does not exist. EEXIST for race condition */
        if (mkdir(path, mode) != 0 && errno != EEXIST)
            status = -1;
    } else if (!S_ISDIR(st.st_mode)) {
        errno = ENOTDIR;
        status = -1;
    }

    return(status);
}
int mkpath(const char *path, mode_t mode)
{
    char           *pp;
    char           *sp;
    int             status;
    char           *copypath = strdup(path);

    status = 0;
    pp = copypath;
    while (status == 0 && (sp = strchr(pp, '/')) != 0) {
        if (sp != pp) {
            /* Neither root nor double slash in path */
            *sp = '\0';
            status = do_mkdir(copypath, mode);
            *sp = '/';
        }
        pp = sp + 1;
    }
    if (status == 0)
        status = do_mkdir(path, mode);
    free(copypath);
    return (status);
}
} //Private namespace

Boss::RetCode BOSS_CALL PlatformUtilsImpl::Exists(Boss::IString *filename, bool *exists) {
	return CheckStat(filename, exists, [](const struct stat &sb) -> bool {
		return S_ISREG(sb.st_mode) || S_ISDIR(sb.st_mode);
	});
}

Boss::RetCode BOSS_CALL PlatformUtilsImpl::IsFile(Boss::IString *filename, bool *exists) {
	return CheckStat(filename, exists, [](const struct stat &sb) -> bool {
		return S_ISREG(sb.st_mode);
	});
}

Boss::RetCode BOSS_CALL PlatformUtilsImpl::IsDir(Boss::IString *filename, bool *exists) {
	return CheckStat(filename, exists, [](const struct stat &sb) -> bool {
		return S_ISDIR(sb.st_mode);
	});
}

RetCode PlatformUtilsImpl::MkPath(Boss::IString *path, bool *ok) {
	int rc = mkpath(StringHelper(path).GetString<>().c_str(), 0755);
	*ok = !rc;
	return Status::Ok;
}

RetCode PlatformUtilsImpl::FindAccounts(Boss::IEnum **result_enum) {
	DIR *d;
	ref_ptr<Enum> res_enum = Base<Enum>::Create();
	struct dirent *dir;
	const std::string char_loc = pu_h.SkypeLocation();
	d = opendir(char_loc.c_str());
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (dir->d_type == DT_DIR) { //Directory
				if (!strcmp(dir->d_name, ".")) continue;
				if (!strcmp(dir->d_name, "..")) continue;
				DIR *subd;
				struct dirent *subdir;
				char buf[512];
				sprintf(buf, "%s/%s", char_loc.c_str(), dir->d_name);
				subd = opendir(buf);
				while ((subdir = readdir(subd)) != NULL) {
					if (subdir->d_type == DT_REG && !strcmp(subdir->d_name, "main.db")) {
						std::string hdbp = pu_h.UserSettingsDir() + "/SkyHistory/" + dir->d_name;
						pu_h.MkPath(hdbp);
						res_enum->AddItem(Base<AccountImpl>::Create(dir->d_name, std::string(buf) + "/main.db", hdbp));
						break;
					}
				}
				closedir(subd);
			}
		}
		closedir(d);
	}
	res_enum.QueryInterface(result_enum);
}


} /* namespace skype_sc */
