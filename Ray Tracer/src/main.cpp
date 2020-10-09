#include <windows.h>

#include <iostream>

#include "CustomExcept.h"
#include "Scene.h"

int main()
{
    try {
        Scene scene;
        scene.composeScene();
        scene.render();
    }
    catch( const CustomExcept& e ) {
        MessageBoxA( nullptr, e.what(), e.getType(), MB_OK | MB_ICONEXCLAMATION );
    }
    catch( const std::exception& e ) {
        MessageBoxA( nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION );
    }
    catch( ... ) {
        MessageBoxA( nullptr, "Unknown exception.", "Unknown exception", MB_OK | MB_ICONEXCLAMATION );
    }

    return 0;
}