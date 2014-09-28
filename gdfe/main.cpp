
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

#pragma comment(lib, "Shlwapi.lib")

#include <iostream>
#include <Shlwapi.h>
#include "grimdawn.h"

#define GDFE_VERSION_STRING "1.0.0"

/**
 * @brief Application entry point.
 *
 * @param argc      Number of arguments.
 * @param argv      Pointer to the array of arguments.
 *
 * @return Non-important return value.
 */
int __cdecl main(int argc, char* argv[])
{
    std::cout
        << "============================================================"
        << std::endl << "Grim Dawn File Extractor (gdfe) by atom0s"
        << std::endl << "============================================================"
        << std::endl << "Contact : atom0s@live.com"
        << std::endl << "Version : " << GDFE_VERSION_STRING
        << std::endl << "============================================================"
        << std::endl << std::endl;


    // To allow drag and drop we must alter the working folder..
    char szWorkingDirectory[MAX_PATH] = { 0 };
    strcpy_s(szWorkingDirectory, argv[0]);
    ::PathRemoveFileSpec(szWorkingDirectory);
    ::SetCurrentDirectoryA(szWorkingDirectory);
    
    // Ensure we have the required module to continue..
    if (::GetFileAttributes(TARGET_FILE_NAME) == INVALID_FILE_ATTRIBUTES)
    {
        std::cout << "[ERROR] gdfe requires important game files to work!\n";
        std::cout << "[ERROR] Be sure you have placed gdfe.exe inside your Grim Dawn game folder!\n";

        std::cin.sync();
        std::cin.ignore();
        return 0;
    }

    // Ensure we have at least one command argument..
    if (argc < 2)
    {
        std::cout << "[ERROR] You must give at least 1 .arc file to extract!\n";

        std::cin.sync();
        std::cin.ignore();
        return 0;
    }

    // Load the engine module..
    auto engine = ::LoadLibrary(TARGET_FILE_NAME);
    if (engine == NULL)
    {
        std::cout << "[ERROR] Failed to load Engine.dll! Cannot continue!\n";

        std::cin.sync();
        std::cin.ignore();
        return 0;
    }

    // Obtain the required function pointers..
    auto GAME_Archive_ctor = (GAME_Archive_Ctor_t)::GetProcAddress(engine, MAKEINTRESOURCEA(EngineOrdinals::GAME_Archive_Ctor));
    auto GAME_Archive_dtor = (GAME_Archive_Dtor_t)::GetProcAddress(engine, MAKEINTRESOURCEA(EngineOrdinals::GAME_Archive_Dtor));
    auto GAME_Archive_Open = (GAME_Archive_Open_t)::GetProcAddress(engine, MAKEINTRESOURCEA(EngineOrdinals::GAME_Archive_Open));
    auto GAME_Archive_Close = (GAME_Archive_Close_t)::GetProcAddress(engine, MAKEINTRESOURCEA(EngineOrdinals::GAME_Archive_Close));
    auto GAME_Archive_GetNumFiles = (GAME_Archive_GetNumFiles_t)::GetProcAddress(engine, MAKEINTRESOURCEA(EngineOrdinals::GAME_Archive_GetNumFiles));
    auto GAME_Archive_ExtractAll = (GAME_Archive_ExtractAll_t)::GetProcAddress(engine, MAKEINTRESOURCEA(EngineOrdinals::GAME_Archive_ExtractAll));

    if (GAME_Archive_ctor == NULL || GAME_Archive_dtor == NULL || GAME_Archive_Open == NULL || GAME_Archive_Close == NULL || GAME_Archive_GetNumFiles == NULL || GAME_Archive_ExtractAll == NULL)
    {
        ::FreeLibrary(engine);
        std::cout << "[ERROR] Failed to obtain one or more required function pointers! Cannot continue!\n";

        std::cin.sync();
        std::cin.ignore();
        return 0;
    }

    // Loop each given argument and try to extract the archive file..
    for (auto x = 1; x < argc; x++)
    {
        std::cout << "\n\n[INFO] Processing: " << argv[x] << std::endl;

        // Create an instance of the archive handler..
        auto class_data = new unsigned char[120];
        auto archive = GAME_Archive_ctor(class_data);

        // Attempt to open the given archive file..
        auto opened = GAME_Archive_Open(archive, argv[x], 1);

        if (opened)
        {
            std::cout << "[INFO] --> Opened file successfully!\n";
            std::cout << "[INFO] --> File count in archive: " << GAME_Archive_GetNumFiles(archive) << std::endl;

            // Build output path to new extracted folder..
            char szCurrentDirectory[MAX_PATH] = { 0 };
            ::GetCurrentDirectoryA(MAX_PATH, szCurrentDirectory);
            strcat_s(szCurrentDirectory, "//extracted//");

            // Attempt to dump the file..
            if (GAME_Archive_ExtractAll(archive, szCurrentDirectory, NULL))
                std::cout << "[INFO] File contents extracted successfully!\n";
            else
                std::cout << "[INFO] There was an error while extracting!\n";
        }
        else
        {
            std::cout << "[INFO] --> Failed to open file as Grim Dawn archive!\n";
        }

        // Cleanup..
        GAME_Archive_Close(archive, false);
        GAME_Archive_dtor(archive);
        delete[] class_data;
    }

    // Cleanup..
    ::FreeLibrary(engine);

    std::cout << "\n\n[INFO] Done! Files can be found within the /extracted/ folder.\n";
    std::cout << "[INFO] Press enter to exit.";

    std::cin.sync();
    std::cin.ignore();

    return 0;
}
