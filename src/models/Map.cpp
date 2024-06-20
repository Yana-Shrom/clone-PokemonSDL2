#include "Map.h"
#include <iostream>

const char map[19][143] = 
{
    "#############0ttt6##############################              ##### ------##############--------#####################       ##################",
    "#############l5b2d##############################              ####  ------##############----------##################         #################",
    "#############34y34#####################0ttt6####-             ###   -------##############----------##############             ################",
    "#########|  ggggggg |####  ########0ttt1+++d####--            ###     r #---  -############--------############    p           #### ##########",
    "#########|  ggggggg | ##     ######l+++++++d###---          #####      ##-------#############-------########                          ########", 
    "######## |  $ggggg$ |          ##0t1+++5bbb4##----           ###    r  ### ------##############-----#######                              #####",        
    "######   |  ggggggg |          0t1+++5b4   ##-----           ##       #####  -- #################---####                      ##   r       ###",
    "####  .  |  $g$g$g$ |          32+++54     ##----- ##        #      ########    #################-  ##                      ####   r        ##",
    "#    ....|          |           l+++d      ##-----####  r  #    r   ######## r   ########   ##                      #############  r   r    ##",
    "    .....u##__| |___i     ##    3bbb4      ###-- #####    ##       #######       ####             r              ##################r       ###",
    "     ....#### | |p        ###    ###        ##   #####    ##      #######             r                        ####################       ####",
    "####  .  ####             #####  ####        # r ####    ##       #######                                    #######################    ######",
    "######    p##             ####    ###            ###                ####                                    ##################################",
    "#######          ..  ..  ..##                    ###                                                     #####################################",
    "########                                                                                               #######################################",
    "#############                      ##                                                            #############################################",
    "##############..  ..  ..   ###   # #####   #               ##                    r  ##   #####################################################",
    "########################################## ###        ###########         ###   ##############################################################",
    "##############################################################################################################################################",
};

Map::Map()
{
    width = 143;
    height = 19;
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
        {
            switch (map[y][x])
            {
            case '#':
                cells[y][x] = TREE;
                break;
            case 'r':
                cells[y][x] = ROCK;
                break;
            case '$':
                cells[y][x] = BUSH;
                break;
            case 'g':
                cells[y][x] = GROUND;
                break;
            case ' ':
                cells[y][x] = GRASS;
                break;
            case '+':
                cells[y][x] = WATER;
                break;
            case '|':
                cells[y][x] = REMPARTV;
                break;
            case '_':
                cells[y][x] = REMPARTH;
                break;
            case 't':
                cells[y][x] = TOP;
                break;
            case 'b':
                cells[y][x] = BOTTOM;
                break;
            case 'd':
                cells[y][x] = RIGHT;
                break;
            case 'l':
                cells[y][x] = LEFT;
                break;
            case '-':
                cells[y][x] = LOTUS;
                break;
            case '.':
                cells[y][x] = FLOWER;
                break;
            case '0':
                cells[y][x] = TOPLEFT;
                break;
            case '6':
                cells[y][x] = TOPRIGHT;
                break;
            case '4':
                cells[y][x] = BOTTOMRIGHT;
                break;
            case '3':
                cells[y][x] = BOTTOMLEFT;
                break;
            case '5':
                cells[y][x] = CORNERUPLEFT;
                break;
            case '1':
                cells[y][x] = CORNERBOTTOMRIGHT;
                break;
            case '2':
                cells[y][x] = CORNERTOPRIGHT;
                break;
            case 'p':
                cells[y][x] = PANNEAUX;
                break;
            case 'y':
                cells[y][x] = TEMPLE;
                break;
            case 'u':
                cells[y][x] = REMPART1;
                break;
            case 'i':
                cells[y][x] = REMPART2;
                break;
            }
        }
}

bool Map::estPositionValide(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        // Vérifie si la case correspondante est praticable
        return cells[y][x] == GRASS || cells[y][x] == FLOWER || cells[y][x] == LOTUS;
    }
    // En dehors des limites de la carte
    return false;
}


