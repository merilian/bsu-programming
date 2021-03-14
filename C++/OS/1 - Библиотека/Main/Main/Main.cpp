#include <iostream>
#include <windows.h> 
#include <stdio.h>

typedef int(__cdecl* MYPROC)();

int main(void)
{
    int b = 0;
    HINSTANCE hinstLib;
    MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    hinstLib = LoadLibrary(TEXT("../../DynamicLib/Output/DynamicLib.dll"));

    if (hinstLib != NULL)
    {
        ProcAdd = (MYPROC)GetProcAddress(hinstLib, "getB");

        // If the function address is valid, call the function.

        if (NULL != ProcAdd)
        {
            fRunTimeLinkSuccess = TRUE;
            b = (ProcAdd)();
        }
        // Free the DLL module.

        fFreeResult = FreeLibrary(hinstLib);
    }

    // If unable to call the DLL function, use an alternative.
    if (fRunTimeLinkSuccess)
    {
        std::cout << "The num b : " << b << "\n";
    }

    return 0;
}
