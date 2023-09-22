#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include "cube.h"

inline bool IsKeyDown(int Key)
{
	return (GetKeyState(Key) & 0x8000) != 0;
}

int main()
{
    srand(time(0));
    std::string c = "cube.txt";
    std::string c_s = "solve.txt";
    std::string c_s_c = "cube_output.txt";
    cube a(c);

    while (1)
    {
        if (kbhit())
        {
            char button = _getch();
            if(button == 'q')a.WR();
            if(button == 'w')a.BR();
            if(button == 'e')a.RR();
            if(button == 'r')a.GR();
            if(button == 't')a.OR();
            if(button == 'y')a.YR();
            if(button == 'a')a.WL();
            if(button == 's')a.BL();
            if(button == 'd')a.RL();
            if(button == 'f')a.GL();
            if(button == 'g')a.OL();
            if(button == 'h')a.YL();
            if(button == 'z')std::cout << a.solve() << "\n";
            if(button == 'v')a.output_solve_in_file(c_s);
            if(button == 'c')a.output_in_file(c_s_c);
            if(button == 'x')a.output();
        }
    }
    

    //double mid = (double)count/5000;
    //std::cout << mid;

    return 0;
}