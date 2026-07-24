#include <string>
#include <conio.h>
#include <format>
#include <iostream>

#include "TitleDrawer.h"

using namespace std;

void TitleDrawer::ProcessTitle()
{
    string title = R"(
  ____    ____       _       ____    ___    _   _
 |  _ \  |  _ \     / \     / ___|  / _ \  | \ | |
 | | | | | |_) |   / _ \   | |  _  | | | | |  \| |
 | |_| | |  _ <   / ___ \  | |_| | | |_| | | |\  |
 |____/  |_| \_\ /_/   \_\  \____|  \___/  |_| \_|

  ____   _          _      __   __  _____  ____
 / ___| | |        / \     \ \ / / | ____| |  _ \
 \___ \ | |       / _ \     \ V /  |  _|   | |_) |
  ___) || |___   / ___ \     | |   | |___  |  _ <
 |____/ |_____| /_/   \_\    |_|   |_____| |_| \_\


              +-------------------+
              |   DRAGON SLAYER   |
              +-------------------+

                  Press Any Key
)";

    cout << title;
    _getch();
}
