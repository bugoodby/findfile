#ifndef __MAIN_H__
#define __MAIN_H__

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define GET_ERROR_VAL( val )	((val) = -1 * __LINE__)


/*----------------------------------------*/
/* プログラム名、バージョン               */
/*----------------------------------------*/
#define MODULENAME_STRING	L"findfile"
#define VERSION_STRING		L"0.01"


/*----------------------------------------*/
/* コマンドライン解析結果を格納する構造体 */
/*----------------------------------------*/
typedef struct tagOPTION {
	int			num;					/* number of input files */
	_TCHAR**	argv;					/* pointer to a file name array */
} OPTION;

/*----------------------------------------*/
/* 関数のプロトタイプ宣言                 */
/*----------------------------------------*/
int findfile( const wchar_t *pszDir, const wchar_t *pszName, OPTION &opt );

#endif /* __MAIN_H__ */
