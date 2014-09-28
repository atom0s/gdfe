
/**
 * Copyright (c) 2014 atom0s [atom0s@live.com]
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/
 *
 * This file is part of gdfe source code.
 */

#ifndef __GRIMDAWN_H_INCLUDED__
#define __GRIMDAWN_H_INCLUDED__

#pragma once

#include <Windows.h>

/**
 * @brief The target file to load to obtain the archive functions from.
 */
#define TARGET_FILE_NAME    "Engine.dll"

/**
 * @brief Function ordinals inside the engine module.
 */
enum EngineOrdinals
{
    GAME_Archive_Ctor = 22,
    GAME_Archive_Dtor = 502,
    GAME_Archive_AddFileFromDisk = 1192,
    GAME_Archive_AddFileFromMemory = 1193,
    GAME_Archive_ArchiveFileHandle = 1309,
    GAME_Archive_ArchiveFileMode = 1310,
    GAME_Archive_BlockSize = 1354,
    GAME_Archive_CalcStats = 1370,
    GAME_Archive_Close = 1445,
    GAME_Archive_Compact = 1473,
    GAME_Archive_ExtractAll = 1939,
    GAME_Archive_ExtractFileToDisk = 1940,
    GAME_Archive_ExtractFileToMemory = 1941,
    GAME_Archive_FindFile = 1965,
    GAME_Archive_FindMatchingFilesEnd = 1973,
    GAME_Archive_FreeFileBuffer = 2000,
    GAME_Archive_GetFileEntry = 2397,
    GAME_Archive_GetNumFiles = 2797,
    GAME_Archive_Open = 4003,
    GAME_Archive_ReOpen = 4206,
    GAME_Archive_ReadFromFile = 4240,
    GAME_Archive_RemoveFile = 4343,
};

/**
 * @brief Function prototypes for the engine archive functions.
 */
typedef void* (__thiscall *GAME_Archive_Ctor_t)(void*); // GAME::Archive::Archive()
typedef void* (__thiscall *GAME_Archive_Dtor_t)(void*); // GAME::Archive::~Archive()
typedef bool(__thiscall *GAME_Archive_Open_t)(void*, LPCSTR, int); // GAME::Archive::Open()
typedef void(__thiscall *GAME_Archive_Close_t)(void*, bool); // GAME::Archive::Close()
typedef bool(__thiscall *GAME_Archive_ExtractAll_t)(void*, char const*, LPVOID); // GAME::Archive::ExtractAll()
typedef int(__thiscall *GAME_Archive_GetNumFiles_t)(void*); // GAME::Archive::GetNumFiles()

#endif // __GRIMDAWN_H_INCLUDED__
