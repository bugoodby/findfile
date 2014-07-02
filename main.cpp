// getverinfo.cpp : コンソール アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "main.h"

void usage(void);
bool parse_cmdline( int argc, wchar_t **argv, OPTION &opt );

//--------------------------------------------------------------
// main
//--------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	OPTION opt = {0};
	int i = 0;
	int retval = 0;
	FILE *console = stderr;

	setlocale(LC_CTYPE, "japanese");

	/* parse */
	if ( !parse_cmdline(argc, argv, opt) ) {
		goto EXIT;
	}

	if ( opt.num < 2 ) {
		fwprintf(console, L"[ERROR] too few arguments.\n");
		GET_ERROR_VAL(retval);
	}
	else {
		/* main */
		retval = findfile( opt.argv[0], opt.argv[1], opt );
		if ( retval < 0 ) {
			fwprintf(console, L"[ERROR] fail.\n");
			GET_ERROR_VAL(retval);
		}
	}

EXIT:
	return retval;
}

//--------------------------------------------------------------
// show usage
//--------------------------------------------------------------
void usage(void)
{
	fwprintf(stderr, L"[ %s Version %s ]\n", MODULENAME_STRING, VERSION_STRING);
	fwprintf(stderr, L"find file from a specified directory.\n");
	fwprintf(stderr, L"\n");
	fwprintf(stderr, L"Usage : %s [option...] <target dir> <file name>\n", MODULENAME_STRING);
	fwprintf(stderr, L"        <target dir>     : target directory path\n");
	fwprintf(stderr, L"        <file name>      : target file name\n");
}

//--------------------------------------------------------------
// parse command line
//--------------------------------------------------------------
bool parse_cmdline( int argc, wchar_t **argv, OPTION &opt )
{
	bool ret = true;
	wchar_t *s = NULL;

	/* initialize */

	/* parse */
	while ( --argc > 0 ) {
		s = *++argv;
		if ( *s == L'-' || *s == L'/' ) {
			switch ( *++s )
			{
			case L'h':
			case L'?':
				usage();
				ret = false;
				break;
			default:
				fwprintf(stderr, L"Unknown parameter : -%s\n", s);
				ret = false;
				break;
			}
		}
		else {
			opt.num = argc;
			opt.argv = argv;
			break;
		}
	}

	return ret;
}


