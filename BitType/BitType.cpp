#include <iostream>
#include <string.h>
#include <windows.h>
#include <chrono>
#include <thread>

int doit(int argc, char* argv[])
{
	const char* arg0 = argv[0];
	const char* slash = strrchr(arg0, '\\');
	if (!slash)
		slash = strrchr(arg0, ':');
	const char* progname = (slash != NULL) ? (slash + 1) : arg0;

	if (argc < 2) {
		std::cout << "Usage: " << progname << " [executable filename]" << std::endl;
		return 1;
	}
	char* filename = argv[1];
	DWORD filetype;
	// https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getbinarytypea
	if (!GetBinaryTypeA(filename, &filetype)) {
		std::cout << "The file is not an executable: " << filename << std::endl;
		return 2;
	}
	std::cout << filename << std::endl;
	const char* txt;
	switch (filetype) {
	case SCS_64BIT_BINARY: txt = "A 64-bit Windows-based application."; break;
	case SCS_32BIT_BINARY: txt = "A 32-bit Windows-based application."; break;
	case SCS_DOS_BINARY:   txt = "An MS - DOS – based application."; break;
	case SCS_OS216_BINARY: txt = "A 16 - bit OS / 2 - based application."; break;
	case SCS_PIF_BINARY:   txt = "A PIF file that executes an MS - DOS – based application."; break;
	case SCS_POSIX_BINARY: txt = "A POSIX – based application."; break;
	case SCS_WOW_BINARY:   txt = "A 16 - bit Windows - based application."; break;
	default:               txt = "Unknown."; break;
	}
	std::cout << txt << std::endl;

	return 0;
}


int main(int argc, char* argv[])
{
	int rst = doit(argc, argv);
	std::chrono::milliseconds timespan(5000);
	std::this_thread::sleep_for(timespan);
	return rst;
}
