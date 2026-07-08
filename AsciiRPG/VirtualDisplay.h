// VirtualDisplay.h 수정
#ifndef VIRUTAL_DISPLAY_H
#define VIRUTAL_DISPLAY_H

#define _HAS_STD_BYTE 0
#define WIN32_LEAN_AND_MEAN  // 추가
#include <Windows.h>
    
class VirtualDisplay
{
public: 
    VirtualDisplay();
    ~VirtualDisplay();
    void Render();

private:
    char** buffer;
};

#endif // ! VIRUTAL_DISPLAY_H

