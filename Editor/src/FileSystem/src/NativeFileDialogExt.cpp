//
// Created by Darren Tynan on 16/03/2025.
//

#ifndef EDITOR_NATIVEFILEDIALOGEXT_CPP
#define EDITOR_NATIVEFILEDIALOGEXT_CPP

#include <nfd.h>
#include <stdio.h>
#include <stdlib.h>

class NativeFileDialogExt
{

    int main(void)
    {

        NFD_Init();

        nfdu8char_t *outPath;
        nfdu8filteritem_t filters[2] = { { "Source code", "c,cpp,cc" }, { "Headers", "h,hpp" } };
        nfdopendialogu8args_t args = {0};
        args.filterList = filters;
        args.filterCount = 2;
        nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
        if (result == NFD_OKAY)
        {
            puts("Success!");
            puts(outPath);
            NFD_FreePathU8(outPath);
        }
        else if (result == NFD_CANCEL)
        {
            puts("User pressed cancel.");
        }
        else
        {
            printf("Error: %s\n", NFD_GetError());
        }

        NFD_Quit();
        return 0;
    }
};


#endif //EDITOR_NATIVEFILEDIALOGEXT_CPP
