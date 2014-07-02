// findfile.cpp : コンソール アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "main.h"
#include <io.h>


int find_recursive( wchar_t *pszPath, size_t len, const wchar_t *pszName );

//---------------------------------------------------------------
// cformat main routine
//---------------------------------------------------------------
int findfile( const wchar_t *pszDir, const wchar_t *pszName, OPTION &opt )
{
	int retval = 0;
	wchar_t buffer[MAX_PATH] = {0};

	wcscpy(buffer, pszDir);
	
	retval = find_recursive( buffer, wcslen(buffer), pszName ); 

	return retval;
}


int find_recursive( wchar_t *pszPath, size_t len, const wchar_t *pszName )
{
	int found_num = 0;
	long lHandle = 0;
	struct _tfinddata_t tFiles = {0};
	size_t suffix_len = 0;

	wcscpy( pszPath + len, L"\\*" );

	lHandle = _wfindfirst( pszPath, &tFiles );
	if ( lHandle != -1L )
	{
		do {
			if ( wcscmp( tFiles.name, L"." ) == 0 ) continue;
			if ( wcscmp( tFiles.name, L".." ) == 0 ) continue;

			if ( tFiles.attrib & _A_SUBDIR ) 
			{
				/* find subdirectory */
				suffix_len = wcslen(tFiles.name);
				wcscpy( pszPath + len + 1, tFiles.name );
				find_recursive( pszPath, len + 1 + suffix_len, pszName );
			}
			else 
			{
				/* find file */
				if ( wcsicmp( tFiles.name, pszName ) == 0 ) {
					/* found target file! */
					wcscpy( pszPath + len + 1, tFiles.name );
					fwprintf( stdout, L"%s\n", pszPath );
					found_num++;
					break;
				}
			}
		} while ( _wfindnext( lHandle, &tFiles ) == 0 );

		_findclose( lHandle );
	}
	
	return found_num;
}


	
	
