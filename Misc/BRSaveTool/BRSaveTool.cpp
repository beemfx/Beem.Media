// (c) 2019 Beem Media

#include <stdio.h>
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

typedef unsigned char bm_byte;
typedef wchar_t bm_char;
typedef std::wstring bm_string;
typedef std::vector<bm_byte> bm_bin_data;
#define countof( _a_ ) (sizeof(_a_)/sizeof(0[_a_]))

static bm_string BRSaveTool_GetDir()
{
	bm_char DirBuffer[_MAX_PATH];
	GetCurrentDirectoryW( countof(DirBuffer) , DirBuffer );

	return DirBuffer;
}

static void BRSaveTool_ReadFile( const bm_string Filename , bm_bin_data& DataOut )
{
	std::wcout << L"Reading " << Filename << std::endl;

	HANDLE File = CreateFileW( Filename.c_str() ,GENERIC_READ , FILE_SHARE_READ , NULL , OPEN_EXISTING , 0 , NULL );
	const DWORD FileSize = GetFileSize( File , NULL );

	if( INVALID_HANDLE_VALUE != File )
	{
		// std::wcout << L"The size is " << FileSize << " bytes " << std::endl;

		DataOut.resize( FileSize , 0 );

		if( DataOut.size() == FileSize )
		{
			DWORD BytesRead = 0;
			ReadFile( File , DataOut.data() , DataOut.size() , &BytesRead , NULL );
			if( BytesRead == DataOut.size() )
			{
				// std::wcout << L"Read all the data." << std::endl;
			}
			else
			{
				std::wcout << L"Did not read all the data." << std::endl;
				DataOut.clear();
			}
		}
		else
		{
			std::wcout << L"Could not allocate memory." << std::endl;
			DataOut.clear();
		}

		CloseHandle( File );
	}
	else
	{
		std::wcout << L"Could not open the file." << std::endl;
	}
}

int wmain( int argc , wchar_t* argv[] )
{
	const std::vector<bm_string> AllFiles 
	{
		L"3HHHH.SAV",
		L"3HRRR.SAV",
		L"H3HHR.SAV",
		L"H3HRH.SAV",
		L"H3HRH-2.SAV",
		L"HH3RR.SAV",
		L"HH3RR-2.SAV",
		L"R3HRR.SAV",
		L"R3RHH.SAV",
		L"RH3RR.SAV",
	};

	const bm_string SavesDir = BRSaveTool_GetDir() + L"\\SAVES\\";

	std::wcout << L"Working in: " << SavesDir << std::endl;

	std::vector<bm_bin_data> AllFileDatas;
	AllFileDatas.resize( AllFiles.size() );
	if( AllFiles.size() == AllFileDatas.size() )
	{
		for( DWORD i=0; i<AllFiles.size(); i++ )
		{
			BRSaveTool_ReadFile( SavesDir + AllFiles[i] , AllFileDatas[i] );
		}
	}

	const DWORD FileSize = [&AllFileDatas]() -> DWORD
		{
			const DWORD ExpectedSize = AllFileDatas.size() > 0 ? AllFileDatas[0].size() : -1;

			for( const bm_bin_data& File : AllFileDatas )
			{
				if( File.size() != ExpectedSize )
				{
					return 0;
				}
			}

			return ExpectedSize;
		}();

	// We want to find any case where the two same ones are the same, but every other file is different.
	const DWORD Same1Idx = 3;
	const DWORD Same2Idx = 4;

	std::vector<DWORD> AnomolyIndexes;

	for( DWORD ByteIdx=0; ByteIdx<FileSize; ByteIdx++ )
	{
		if( AllFileDatas[Same1Idx][ByteIdx] == AllFileDatas[Same2Idx][ByteIdx] )
		{
			const bm_byte SameByte = AllFileDatas[Same1Idx][ByteIdx];

			bool bAllDifferent = true;
			for( DWORD FileDataIdx=0; FileDataIdx<AllFileDatas.size(); FileDataIdx++ )
			{
				// Skip the two datas that we know are the same.
				if( FileDataIdx == Same1Idx || FileDataIdx == Same2Idx )
				{
					continue;
				}

				// Now check and if every other byte is different, log this one.
				const bm_byte Byte = AllFileDatas[FileDataIdx][ByteIdx];
				if( Byte == SameByte )
				{
					bAllDifferent = false;
				}
			}

			if( bAllDifferent )
			{
				AnomolyIndexes.push_back( ByteIdx );
			}
		}
	}

	wprintf( L"Found %d anomolies.\n" , AnomolyIndexes.size() );

	for( const DWORD& Anom : AnomolyIndexes )
	{
		wprintf( L"Anomoly found at %d\n" , Anom );
		for( DWORD FileDataIdx=0; FileDataIdx<AllFileDatas.size(); FileDataIdx++ )
		{
			wprintf( L"\tData %d: %02X (%s)\n" , FileDataIdx , AllFileDatas[FileDataIdx][Anom] , AllFiles[FileDataIdx].c_str() );
		}
	}

	/*
	BRSaveTool_ReadFile( SavesDir + L"H3HRH.SAV" , Same1 );
	BRSaveTool_ReadFile( SavesDir + L"H3HRH-2.SAV" , Same2 );

	BRSaveTool_ReadFile( SavesDir + L"3HHHH.SAV" , Compare1 );
	BRSaveTool_ReadFile( SavesDir + L"RH3RR.SAV" , Compare2 );

	if( Same1.size() == Same2.size() && Same2.size() == Compare1.size() && Compare1.size() == Compare2.size() )
	{
		const DWORD FileSize = Same1.size();

		std::wcout << L"Analyzing " << FileSize << L" bytes across 4 files." << std::endl;

		// We just want to find any bytes where 2 and 3 are the same but 1 is different.
		DWORD NumFound = 0;
		for( DWORD i=0; i<FileSize; i++ )
		{
			if( Same1[i] == Same2[i] && Compare1[i] != Same1[i] && Compare2[i] != Same2[i] )
			{
				NumFound++;
				wprintf( L"Anomoly %04d: %06d S:%02X , 1:%02X , 2:%02X \n" , NumFound , i , Same1[i] , Compare1[i] , Compare2[i] );
			}
		}
	}
	*/

	std::wcout << L"Press any key to continue." << std::endl;
	_getch();

	return 0;
}