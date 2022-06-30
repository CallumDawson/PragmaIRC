#include "Common.h"

CCore* g_pCore;

int main(void)
{
    SetConsoleTitle("PragmaIRC");
    printf("== PragmaIRC v%s ==\n\n", VERSION);

    g_pCore = new CCore();

    while(true)
    {
    }
    return 0;
}