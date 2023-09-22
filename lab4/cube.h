#ifndef CUBE
#define CUBE
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

int char_to_int(char c)
{
    if (c == 'w')
        return 0;
    if (c == 'r')
        return 2;
    if (c == 'o')
        return 4;
    if (c == 'y')
        return 5;
    if (c == 'g')
        return 3;
    if (c == 'b')
        return 1;
    return -1;
}
char int_to_char(int c)
{
    if (c == 0)
        return 'w';
    if (c == 1)
        return 'b';
    if (c == 2)
        return 'r';
    if (c == 3)
        return 'g';
    if (c == 4)
        return 'o';
    if (c == 5)
        return 'y';
    return 'n';
}

std::string compact_string(std::string ans)
{
    std::string tmp;
    char color, vector_turn;
    int mem[4];
    int it = -1;
    for (int i = 0; i < ans.size(); i += 3)
    {
        color = ans[i];
        vector_turn = ans[i + 1];
        int ind = 0;
        if (color == 'B')
            ind += 1;
        if (color == 'R')
            ind += 2;
        if (color == 'G')
            ind += 3;
        if (color == 'O')
            ind += 4;
        if (color == 'Y')
            ind += 5;
        if (vector_turn == 'r')
            ind += 6;
        if (it == -1)
        {
            it++;
            mem[it] = ind;
        }
        else if (mem[it] == ind)
        {
            if (it == 3)
            {
                // mem[0] = (mem[0] + 6) % 12;
                it = 0;
            }
            else
            {
                it++;
                mem[it] = ind;
            }
        }
        else
        {
            if (it != 3)
            {
                for (int i = 0; i <= it; ++i)
                {
                    if (it == 2)
                        mem[i] = (mem[i] + 6) % 12;
                    if (mem[i] % 6 == 0)
                        tmp += "W";
                    if (mem[i] % 6 == 1)
                        tmp += "B";
                    if (mem[i] % 6 == 2)
                        tmp += "R";
                    if (mem[i] % 6 == 3)
                        tmp += "G";
                    if (mem[i] % 6 == 4)
                        tmp += "O";
                    if (mem[i] % 6 == 5)
                        tmp += "Y";
                    if (mem[i] / 6 == 0)
                        tmp += "l";
                    if (mem[i] / 6 == 1)
                        tmp += "r";
                    tmp += " ";
                }
            }
            it = 0;
            mem[it] = ind;
        }
    }

    for (int i = 0; i <= it; ++i)
    {
        if (mem[i] % 6 == 0)
            tmp += "W";
        if (mem[i] % 6 == 1)
            tmp += "B";
        if (mem[i] % 6 == 2)
            tmp += "R";
        if (mem[i] % 6 == 3)
            tmp += "G";
        if (mem[i] % 6 == 4)
            tmp += "O";
        if (mem[i] % 6 == 5)
            tmp += "Y";
        if (mem[i] / 6 == 0)
            tmp += "l";
        if (mem[i] / 6 == 1)
            tmp += "r";
        tmp += " ";
    }

    return tmp;
}

class side
{
private:
public:
    int c[8];
    side()
    {
        for (int i = 0; i < 8; ++i)
        {
            c[i] = -1;
        }
    }
    side(int new_c[8])
    {
        for (int i = 0; i < 8; ++i)
        {
            c[i] = new_c[i];
        }
    }
    ~side() = default;
    inline const int &operator[](int i) const
    {
        return this->c[i];
    }
    void right_turn()
    {
        int tmp1 = c[0];
        c[0] = c[5];
        c[5] = c[7];
        c[7] = c[2];
        c[2] = tmp1;
        tmp1 = c[1];
        c[1] = c[3];
        c[3] = c[6];
        c[6] = c[4];
        c[4] = tmp1;
    }
    void left_turn()
    {
        int tmp1 = c[0];
        c[0] = c[2];
        c[2] = c[7];
        c[7] = c[5];
        c[5] = tmp1;
        tmp1 = c[1];
        c[1] = c[4];
        c[4] = c[6];
        c[6] = c[3];
        c[3] = tmp1;
    }
};

class cube
{
private:
    side sides[6];

public:

    cube(std::string file_name)
    {    
        std::ifstream istrm(file_name, std::ios::binary);
        
        bool side_key[6];
        for (int i = 0; i < 6; ++i)
        {
            side_key[i] = 0;
        }
        for (int i = 0; i < 6; ++i)
        {
            int tmp[8];
            int number;
            for (int j = 0; j < 9; ++j)
            {
                char c;
                istrm >> c;
                int key = char_to_int(c);
                if (j == 4)
                {
                    number = key;
                    if(key != -1){
                        side_key[number] = 1;
                    }
                }
                else if (j < 4)
                    tmp[j] = key;
                else
                    tmp[j - 1] = key;
            }
            side new_side(tmp);
            if(number != -1)sides[number] = new_side;
        }
        for (int i = 0; i < 6; ++i)
        {
            if (!side_key[i])
            {
                std::ofstream ostrm("error.txt", std::ios::binary);
                ostrm << "Not all sides initializated." << '\n';
                exit(0);
            }
        }
    };

    cube(const side sidess[6])
    {
        for (int i = 0; i < 6; ++i)
        {
            sides[i] = sidess[i];
        }
    }

    bool comp(int a1, int a2, int a3) const
    {
        int key = 0;
        int check_color[6];
        for (int i = 0; i < 6; ++i)
        {
            check_color[i] = 0;
        }
        check_color[a1]++;
        check_color[a2]++;
        check_color[a3]++;
        for (int i = 0; i < 6; ++i)
        {
            if (check_color[i] > 1)
                key = 1;
        }
        if (check_color[0] && check_color[5])
            key = 1;
        if (check_color[1] && check_color[3])
            key = 1;
        if (check_color[2] && check_color[4])
            key = 1;

        return key;
    }

    bool cube_is_correct() const
    {
        int blocks[20];
        for (int i = 0; i < 20; ++i)
        {
            blocks[i] = 0;
        }
        int sum_ZZ = 0;
        std::vector<std::pair<int, int>> b_c;
        b_c.push_back({sides[0][1], sides[2][6]});
        b_c.push_back({sides[0][3], sides[1][6]});
        b_c.push_back({sides[0][4], sides[3][6]});
        b_c.push_back({sides[0][6], sides[4][6]});

        b_c.push_back({sides[5][1], sides[4][1]});
        b_c.push_back({sides[5][3], sides[1][1]});
        b_c.push_back({sides[5][4], sides[3][1]});
        b_c.push_back({sides[5][6], sides[2][1]});

        b_c.push_back({sides[2][3], sides[1][4]});
        b_c.push_back({sides[2][4], sides[3][3]});
        b_c.push_back({sides[4][3], sides[3][4]});
        b_c.push_back({sides[4][4], sides[1][3]});

        for (int i = 0; i < 12; ++i)
        {
            if (b_c[i].first == b_c[i].second || (b_c[i].first % 5 == 0 && b_c[i].second % 5 == 0) || (b_c[i].first % 5 != 0 && b_c[i].second % 5 != 0 && abs(b_c[i].first - b_c[i].second) == 2))
            {
                std::ofstream ostrm("error.txt", std::ios::binary);
                ostrm << "Cube is incorrect.";
                return 0;
            }
            if (b_c[i].second % 5 == 0 || (b_c[i].first % 5 != 0 && b_c[i].second % 2 == 0))
            {
                sum_ZZ++;
                int tmp_ZZ = b_c[i].first;
                b_c[i].first = b_c[i].second;
                b_c[i].second = tmp_ZZ;
            }
            if (b_c[i].first == 0 && b_c[i].second == 1)
                blocks[0]++;
            if (b_c[i].first == 0 && b_c[i].second == 2)
                blocks[1]++;
            if (b_c[i].first == 0 && b_c[i].second == 3)
                blocks[2]++;
            if (b_c[i].first == 0 && b_c[i].second == 4)
                blocks[3]++;
            if (b_c[i].first == 5 && b_c[i].second == 1)
                blocks[4]++;
            if (b_c[i].first == 5 && b_c[i].second == 2)
                blocks[5]++;
            if (b_c[i].first == 5 && b_c[i].second == 3)
                blocks[6]++;
            if (b_c[i].first == 5 && b_c[i].second == 4)
                blocks[7]++;
            if (b_c[i].first == 2 && b_c[i].second == 1)
                blocks[8]++;
            if (b_c[i].first == 2 && b_c[i].second == 3)
                blocks[9]++;
            if (b_c[i].first == 4 && b_c[i].second == 1)
                blocks[10]++;
            if (b_c[i].first == 4 && b_c[i].second == 3)
                blocks[11]++;
        }

        std::vector<std::vector<int>> b_t_c(8);
        for (int i = 0; i < 8; ++i)
        {
            b_t_c[i].resize(3);
        }
        b_t_c[0][0] = sides[0][0];
        b_t_c[0][1] = sides[2][5];
        b_t_c[0][2] = sides[1][7];
        b_t_c[1][0] = sides[0][2];
        b_t_c[1][1] = sides[3][5];
        b_t_c[1][2] = sides[2][7];
        b_t_c[2][0] = sides[0][7];
        b_t_c[2][1] = sides[4][5];
        b_t_c[2][2] = sides[3][7];
        b_t_c[3][0] = sides[0][5];
        b_t_c[3][1] = sides[1][5];
        b_t_c[3][2] = sides[4][7];
        b_t_c[4][0] = sides[5][5];
        b_t_c[4][1] = sides[1][2];
        b_t_c[4][2] = sides[2][0];
        b_t_c[5][0] = sides[5][7];
        b_t_c[5][1] = sides[2][2];
        b_t_c[5][2] = sides[3][0];
        b_t_c[6][0] = sides[5][2];
        b_t_c[6][1] = sides[3][2];
        b_t_c[6][2] = sides[4][0];
        b_t_c[7][0] = sides[5][0];
        b_t_c[7][1] = sides[4][2];
        b_t_c[7][2] = sides[1][0];

        int sum_turns = 0;
        for (int i = 0; i < 8; ++i)
        {
            if (comp(b_t_c[i][0], b_t_c[i][1], b_t_c[i][2]))
            {
                std::ofstream ostrm("error.txt", std::ios::binary);
                ostrm << "Cube is incorrect.";
                return 0;
            }
            while (b_t_c[i][0] % 5 != 0)
            {
                sum_turns++;
                int tmpp = b_t_c[i][0];
                b_t_c[i][0] = b_t_c[i][1];
                b_t_c[i][1] = b_t_c[i][2];
                b_t_c[i][2] = tmpp;
            }
            if (b_t_c[i][0] == 0)
            {
                if (b_t_c[i][1] == 2 && b_t_c[i][2] == 1)
                    blocks[12]++;
                if (b_t_c[i][1] == 3 && b_t_c[i][2] == 2)
                    blocks[13]++;
                if (b_t_c[i][1] == 4 && b_t_c[i][2] == 3)
                    blocks[14]++;
                if (b_t_c[i][1] == 1 && b_t_c[i][2] == 4)
                    blocks[15]++;
            }
            else if (b_t_c[i][0] == 5)
            {
                if (b_t_c[i][1] == 1 && b_t_c[i][2] == 2)
                    blocks[16]++;
                if (b_t_c[i][1] == 2 && b_t_c[i][2] == 3)
                    blocks[17]++;
                if (b_t_c[i][1] == 3 && b_t_c[i][2] == 4)
                    blocks[18]++;
                if (b_t_c[i][1] == 4 && b_t_c[i][2] == 1)
                    blocks[19]++;
            }
        }
        for (int i = 0; i < 20; ++i)
        {
            if (blocks[i] != 1)
            {
                std::ofstream ostrm("error.txt", std::ios::binary);
                ostrm << "Cube is incorrect.";
                return 0;
            }
        }

        if (sum_ZZ % 2 == 1 || sum_turns % 3 != 0)
        {
            std::ofstream ostrm("error.txt", std::ios::binary);
            ostrm << "This cube can not be solved.";
            return 0;
        }

        cube b(sides);

        b.first_step();
        b.second_step();
        b.third_step();
        b.fourth_step();
        b.fifth_step();

        int count_true_b = 0;

        if ((b.sides[5][0] * b.sides[1][0] * b.sides[4][2]) == 20)
            count_true_b++;
        if ((b.sides[5][2] * b.sides[4][0] * b.sides[3][2]) == 60)
            count_true_b++;
        if ((b.sides[5][5] * b.sides[2][0] * b.sides[1][2]) == 10)
            count_true_b++;
        if ((b.sides[5][7] * b.sides[3][0] * b.sides[2][2]) == 30)
            count_true_b++;

        if (count_true_b == 2)
        {
            std::ofstream ostrm("error.txt", std::ios::binary);
            ostrm << "This cube can not be solved.";
            return 0;
        }

        return 1;
    }

    std::vector<int> down_row() const
    {
        std::vector<int> tmp(3);
        tmp[0] = 5;
        tmp[1] = 6;
        tmp[2] = 7;
        return tmp;
    }
    std::vector<int> left_row() const
    {
        std::vector<int> tmp(3);
        tmp[0] = 0;
        tmp[1] = 3;
        tmp[2] = 5;
        return tmp;
    }
    std::vector<int> right_row() const
    {
        std::vector<int> tmp(3);
        tmp[0] = 7;
        tmp[1] = 4;
        tmp[2] = 2;
        return tmp;
    }
    std::vector<int> up_row() const
    {
        std::vector<int> tmp(3);
        tmp[0] = 2;
        tmp[1] = 1;
        tmp[2] = 0;
        return tmp;
    }

    std::vector<int> index_row(char i) const
    {
        if (i == 'u')
            return up_row();
        if (i == 'l')
            return left_row();
        if (i == 'd')
            return down_row();
        return right_row();
    }

    void change_rows(int i, int j, int k, int l, char i1, char j1, char k1, char l1)
    {
        std::vector<int> i2 = index_row(i1);
        std::vector<int> j2 = index_row(j1);
        std::vector<int> k2 = index_row(k1);
        std::vector<int> l2 = index_row(l1);
        int tmp1 = sides[i][i2[0]];
        int tmp2 = sides[i][i2[1]];
        int tmp3 = sides[i][i2[2]];
        sides[i].c[i2[0]] = sides[l][l2[0]];
        sides[i].c[i2[1]] = sides[l][l2[1]];
        sides[i].c[i2[2]] = sides[l][l2[2]];
        sides[l].c[l2[0]] = sides[k][k2[0]];
        sides[l].c[l2[1]] = sides[k][k2[1]];
        sides[l].c[l2[2]] = sides[k][k2[2]];
        sides[k].c[k2[0]] = sides[j][j2[0]];
        sides[k].c[k2[1]] = sides[j][j2[1]];
        sides[k].c[k2[2]] = sides[j][j2[2]];
        sides[j].c[j2[0]] = tmp1;
        sides[j].c[j2[1]] = tmp2;
        sides[j].c[j2[2]] = tmp3;
    }

    void RR()
    {
        sides[2].right_turn();
        change_rows(5, 3, 0, 1, 'd', 'l', 'u', 'r');
    }
    void RL()
    {
        sides[2].left_turn();
        change_rows(5, 1, 0, 3, 'd', 'r', 'u', 'l');
    }
    void GR()
    {
        sides[3].right_turn();
        change_rows(5, 4, 0, 2, 'r', 'l', 'r', 'r');
    }
    void GL()
    {
        sides[3].left_turn();
        change_rows(5, 2, 0, 4, 'r', 'r', 'r', 'l');
    }
    void BR()
    {
        sides[1].right_turn();
        change_rows(5, 2, 0, 4, 'l', 'l', 'l', 'r');
    }
    void BL()
    {
        sides[1].left_turn();
        change_rows(5, 4, 0, 2, 'l', 'r', 'l', 'l');
    }
    void OR()
    {
        sides[4].right_turn();
        change_rows(5, 1, 0, 3, 'u', 'l', 'd', 'r');
    }
    void OL()
    {
        sides[4].left_turn();
        change_rows(5, 3, 0, 1, 'u', 'r', 'd', 'l');
    }
    void YR()
    {
        sides[5].right_turn();
        change_rows(4, 3, 2, 1, 'u', 'u', 'u', 'u');
    }
    void YL()
    {
        sides[5].left_turn();
        change_rows(4, 1, 2, 3, 'u', 'u', 'u', 'u');
    }
    void WR()
    {
        sides[0].right_turn();
        change_rows(2, 3, 4, 1, 'd', 'd', 'd', 'd');
    }
    void WL()
    {
        sides[0].left_turn();
        change_rows(2, 1, 4, 3, 'd', 'd', 'd', 'd');
    }

    bool check1() const
    {
        bool key = 1;
        key &= (sides[1][3] == 1);
        key &= (sides[1][4] == 1);
        key &= (sides[2][3] == 2);
        key &= (sides[2][4] == 2);
        key &= (sides[3][3] == 3);
        key &= (sides[3][4] == 3);
        key &= (sides[4][3] == 4);
        key &= (sides[4][4] == 4);
        return key;
    }

    bool check2() const
    {
        bool key = 1;
        key &= check1();
        int sum = 0;
        for (int i = 0; i < 8; ++i)
            sum += sides[0][i];
        key &= (sum == 0);
        sum = 0;
        for (int i = 5; i < 8; ++i)
            sum += sides[1][i];
        key &= (sum == 3);
        sum = 0;
        for (int i = 5; i < 8; ++i)
            sum += sides[2][i];
        key &= (sum == 6);
        sum = 0;
        for (int i = 5; i < 8; ++i)
            sum += sides[3][i];
        key &= (sum == 9);
        sum = 0;
        for (int i = 5; i < 8; ++i)
            sum += sides[4][i];
        key &= (sum == 12);
        return key;
    }

    bool check3() const
    {
        bool key = 1;
        for (int i = 0; i < 8; ++i)
            key &= (sides[0][i] == 0);
        for (int i = 3; i < 8; ++i)
            key &= (sides[1][i] == 1);
        for (int i = 3; i < 8; ++i)
            key &= (sides[2][i] == 2);
        for (int i = 3; i < 8; ++i)
            key &= (sides[3][i] == 3);
        for (int i = 3; i < 8; ++i)
            key &= (sides[4][i] == 4);

        key &= (sides[1][1] == 1);
        key &= (sides[2][1] == 2);
        key &= (sides[3][1] == 3);
        key &= (sides[4][1] == 4);
        return key;
    }

    bool check4() const
    {
        bool key = 1;
        for (int i = 0; i < 8; ++i)
            key &= (sides[0][i] == 0);
        for (int i = 0; i < 8; ++i)
            key &= (sides[1][i] == 1);
        for (int i = 0; i < 8; ++i)
            key &= (sides[2][i] == 2);
        for (int i = 0; i < 8; ++i)
            key &= (sides[3][i] == 3);
        for (int i = 0; i < 8; ++i)
            key &= (sides[4][i] == 4);
        for (int i = 0; i < 8; ++i)
            key &= (sides[5][i] == 5);

        return key;
    }

    std::string first_step()
    {
        std::string tmp;
        int key = 0;
        while (!(sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0))
        {
            if (sides[4][1] == 0)
            {
                OL();
                YR();
                GL();
                tmp += "Ol Yr Gl ";
            }
            if (sides[3][1] == 0)
            {
                GL();
                YR();
                RL();
                tmp += "Gl Yr Rl ";
            }
            if (sides[2][1] == 0)
            {
                RL();
                YR();
                BL();
                tmp += "Rl Yr Bl ";
            }
            if (sides[1][1] == 0)
            {
                BL();
                YR();
                OL();
                tmp += "Bl Yr Ol ";
            }
            if (sides[1][6] == 0)
            {
                while (sides[5][3] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                BL();
                tmp += "Bl ";
                while (sides[5][6] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                RR();
                tmp += "Rr ";
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
                while (sides[5][3] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                BR();
                YL();
                RL();
                tmp += "Br Yl Rl ";
            }
            if (sides[0][3] == 0)
            {
                while (sides[5][3] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                BL();
                BL();
                tmp += "Bl Bl ";
            }
            if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
            {
                return tmp;
            }

            for (int i = 1; i < 4; ++i)
            {
                WL();
                tmp += "Wl ";
                if (sides[1][6] == 0)
                {
                    while (sides[5][3] == 0)
                    {
                        YL();
                        tmp += "Yl ";
                    }
                    BL();
                    tmp += "Bl ";
                    while (sides[5][6] == 0)
                    {
                        YL();
                        tmp += "Yl ";
                    }
                    RR();
                    tmp += "Rr ";
                    if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                    {
                        return tmp;
                    }
                    while (sides[5][3] == 0)
                    {
                        YL();
                        tmp += "Yl ";
                    }
                    BR();
                    YL();
                    RL();
                    tmp += "Br Yl Rl ";
                }
                if (sides[0][3] == 0)
                {
                    while (sides[5][3] == 0)
                    {
                        YL();
                        tmp += "Yl ";
                    }
                    BL();
                    BL();
                    tmp += "Bl Bl ";
                }
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
            }

            if (sides[1][4] == 0)
            {
                while (sides[5][6] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                RR();
                tmp += "Rr ";
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
                while (sides[5][6] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                RL();
                tmp += "Rl ";
            }
            if (sides[1][3] == 0)
            {
                while (sides[5][1] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                OL();
                tmp += "Ol ";
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
                while (sides[5][1] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                OR();
                tmp += "Or ";
            }

            if (sides[2][4] == 0)
            {
                while (sides[5][4] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                GR();
                tmp += "Gr ";
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
                while (sides[5][4] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                GL();
                tmp += "Gl ";
            }
            if (sides[2][3] == 0)
            {
                while (sides[5][3] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                BL();
                tmp += "Bl ";
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
                while (sides[5][3] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                BR();
                tmp += "Br ";
            }

            if (sides[3][4] == 0)
            {
                while (sides[5][1] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                OR();
                tmp += "Or ";
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
                while (sides[5][1] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                OL();
                tmp += "Ol ";
            }
            if (sides[3][3] == 0)
            {
                while (sides[5][6] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                RL();
                tmp += "Rl ";
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
                while (sides[5][6] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                RR();
                tmp += "Rr ";
            }

            if (sides[4][4] == 0)
            {
                while (sides[5][3] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                BR();
                tmp += "Br ";
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
                while (sides[5][3] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                BL();
                tmp += "Bl ";
            }
            if (sides[4][3] == 0)
            {
                while (sides[5][4] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                GL();
                tmp += "Gl ";
                if (sides[5][1] == 0 && sides[5][3] == 0 && sides[5][4] == 0 && sides[5][6] == 0)
                {
                    return tmp;
                }
                while (sides[5][4] == 0)
                {
                    YL();
                    tmp += "Yl ";
                }
                GR();
                tmp += "Gr ";
            }
            key++;
            if (key > 20)
                break;
        }

        return tmp;
    }

    std::string second_step()
    {
        std::string tmp;

        while (sides[1][1] != 1 || sides[5][3] != 0)
        {
            YL();
            tmp += "Yl ";
        }
        BL();
        BL();
        tmp += "Bl Bl ";

        while (sides[2][1] != 2 || sides[5][6] != 0)
        {
            YL();
            tmp += "Yl ";
        }
        RL();
        RL();
        tmp += "Rl Rl ";

        while (sides[3][1] != 3 || sides[5][4] != 0)
        {
            YL();
            tmp += "Yl ";
        }
        GL();
        GL();
        tmp += "Gl Gl ";

        while (sides[4][1] != 4 || sides[5][1] != 0)
        {
            YL();
            tmp += "Yl ";
        }
        OL();
        OL();
        tmp += "Ol Ol ";

        return tmp;
    }

    std::string third_step()
    {
        std::string tmp;

        if (sides[0][0] * sides[1][7] * sides[2][5] == 0)
        {
            while (sides[1][2] * sides[2][0] * sides[5][5] == 0)
            {
                YL();
                tmp += "Yl ";
            }
            BL();
            YL();
            BR();
            tmp += "Bl Yl Br ";
        }

        if (sides[0][2] * sides[2][7] * sides[3][5] == 0)
        {
            while (sides[2][2] * sides[3][0] * sides[5][7] == 0)
            {
                YL();
                tmp += "Yl ";
            }
            RL();
            YL();
            RR();
            tmp += "Rl Yl Rr ";
        }

        if (sides[0][7] * sides[3][7] * sides[4][5] == 0)
        {
            while (sides[3][2] * sides[4][0] * sides[5][2] == 0)
            {
                YL();
                tmp += "Yl ";
            }
            GL();
            YL();
            GR();
            tmp += "Gl Yl Gr ";
        }

        if (sides[0][5] * sides[4][7] * sides[1][5] == 0)
        {
            while (sides[4][2] * sides[1][0] * sides[5][0] == 0)
            {
                YL();
                tmp += "Yl ";
            }
            OL();
            YL();
            OR();
            tmp += "Ol Yl Or ";
        }

        while ((sides[1][2] * sides[1][2] * sides[1][2]) + (sides[2][0] * sides[2][0] * sides[2][0]) + (sides[5][5] * sides[5][5] * sides[5][5]) != 9)
        {
            YL();
            tmp += "Yl ";
        }
        RR();
        YR();
        RL();
        YL();
        tmp += "Rr Yr Rl Yl ";
        while (sides[0][0] != 0)
        {
            RR();
            YR();
            RL();
            YL();
            RR();
            YR();
            RL();
            YL();
            tmp += "Rr Yr Rl Yl Rr Yr Rl Yl ";
        }

        while ((sides[2][2] * sides[2][2] * sides[2][2]) + (sides[3][0] * sides[3][0] * sides[3][0]) + (sides[5][7] * sides[5][7] * sides[5][7]) != 35)
        {
            YL();
            tmp += "Yl ";
        }
        GR();
        YR();
        GL();
        YL();
        tmp += "Gr Yr Gl Yl ";
        while (sides[0][2] != 0)
        {
            GR();
            YR();
            GL();
            YL();
            GR();
            YR();
            GL();
            YL();
            tmp += "Gr Yr Gl Yl Gr Yr Gl Yl ";
        }

        while ((sides[3][2] * sides[3][2] * sides[3][2]) + (sides[4][0] * sides[4][0] * sides[4][0]) + (sides[5][2] * sides[5][2] * sides[5][2]) != 91)
        {
            YL();
            tmp += "Yl ";
        }
        OR();
        YR();
        OL();
        YL();
        tmp += "Or Yr Ol Yl ";
        while (sides[0][7] != 0)
        {
            OR();
            YR();
            OL();
            YL();
            OR();
            YR();
            OL();
            YL();
            tmp += "Or Yr Ol Yl Or Yr Ol Yl ";
        }

        while ((sides[4][2] * sides[4][2] * sides[4][2]) + (sides[1][0] * sides[1][0] * sides[1][0]) + (sides[5][0] * sides[5][0] * sides[5][0]) != 65)
        {
            YL();
            tmp += "Yl ";
        }
        BR();
        YR();
        BL();
        YL();
        tmp += "Br Yr Bl Yl ";
        while (sides[0][5] != 0)
        {
            BR();
            YR();
            BL();
            YL();
            BR();
            YR();
            BL();
            YL();
            tmp += "Br Yr Bl Yl Br Yr Bl Yl ";
        }

        return tmp;
    }

    std::string fourth_step()
    {
        std::string tmp;

        int key = 0;
        while (!check1() && key < 5)
        {
            if (sides[5][3] != 5 && sides[1][1] != 5)
            {
                if (sides[5][3] == 1)
                {
                    if (sides[1][1] == 4)
                    {
                        YR();
                        YR();
                        BR();
                        YR();
                        BL();
                        YL();
                        OL();
                        YL();
                        OR();
                        tmp += "Yr Yr Br Yr Bl Yl Ol Yl Or ";
                    }
                    else
                    {
                        YL();
                        YL();
                        BL();
                        YL();
                        BR();
                        YR();
                        RR();
                        YR();
                        RL();
                        tmp += "Yl Yl Bl Yl Br Yr Rr Yr Rl ";
                    }
                }
                else if (sides[5][3] == 2)
                {
                    if (sides[1][1] == 1)
                    {
                        YR();
                        RR();
                        YR();
                        RL();
                        YL();
                        BL();
                        YL();
                        BR();
                        tmp += "Yr Rr Yr Rl Yl Bl Yl Br ";
                    }
                    else
                    {
                        YR();
                        RL();
                        YL();
                        RR();
                        YR();
                        GR();
                        YR();
                        GL();
                        tmp += "Yr Rl Yl Rr Yr Gr Yr Gl ";
                    }
                }
                else if (sides[5][3] == 3)
                {
                    if (sides[1][1] == 2)
                    {
                        GR();
                        YR();
                        GL();
                        YL();
                        RL();
                        YL();
                        RR();
                        tmp += "Gr Yr Gl Yl Rl Yl Rr ";
                    }
                    else
                    {
                        GL();
                        YL();
                        GR();
                        YR();
                        OR();
                        YR();
                        OL();
                        tmp += "Gl Yl Gr Yr Or Yr Ol ";
                    }
                }
                else
                {
                    if (sides[1][1] == 3)
                    {
                        YL();
                        OR();
                        YR();
                        OL();
                        YL();
                        GL();
                        YL();
                        GR();
                        tmp += "Yl Or Yr Ol Yl Gl Yl Gr ";
                    }
                    else
                    {
                        YL();
                        OL();
                        YL();
                        OR();
                        YR();
                        BR();
                        YR();
                        BL();
                        tmp += "Yl Ol Yl Or Yr Br Yr Bl ";
                    }
                }
                key = 0;
            }
            if (key == 4)
            {
                if ((sides[1][4] != 1 || sides[2][3] != 2))
                {
                    RR();
                    YR();
                    RL();
                    YL();
                    BL();
                    YL();
                    BR();
                    tmp += "Rr Yr Rl Yl Bl Yl Br ";
                    key = -1;
                }
                else if ((sides[2][4] != 2 || sides[3][3] != 3))
                {
                    GR();
                    YR();
                    GL();
                    YL();
                    RL();
                    YL();
                    RR();
                    tmp += "Gr Yr Gl Yl Rl Yl Rr ";
                    key = -1;
                }
                else if ((sides[3][4] != 3 || sides[4][3] != 4))
                {
                    OR();
                    YR();
                    OL();
                    YL();
                    GL();
                    YL();
                    GR();
                    tmp += "Or Yr Ol Yl Gl Yl Gr ";
                    key = -1;
                }
                else if ((sides[4][4] != 4 || sides[1][3] != 1))
                {
                    BR();
                    YR();
                    BL();
                    YL();
                    OL();
                    YL();
                    OR();
                    tmp += "Br Yr Bl Yl Ol Yl Or ";
                    key = -1;
                }
            }
            key++;
            YL();
            tmp += "Yl ";
        }

        return tmp;
    }

    std::string fifth_step()
    {
        std::string tmp;

        if (sides[5][1] + sides[5][3] + sides[5][4] + sides[5][6] < 20)
        {
            if (sides[5][1] != 5 && sides[5][3] != 5 && sides[5][4] != 5 && sides[5][6] != 5)
            {
                BR();
                RR();
                YR();
                RL();
                YL();
                BL();
                tmp += "Br Rr Yr Rl Yl Bl ";
            }

            if (sides[5][1] + sides[5][3] == 10)
            {
                RR();
                GR();
                YR();
                GL();
                YL();
                RL();
                tmp += "Rr Gr Yr Gl Yl Rl ";
            }
            else if (sides[5][3] + sides[5][6] == 10)
            {
                GR();
                OR();
                YR();
                OL();
                YL();
                GL();
                tmp += "Gr Or Yr Ol Yl Gl ";
            }
            else if (sides[5][6] + sides[5][4] == 10)
            {
                OR();
                BR();
                YR();
                BL();
                YL();
                OL();
                tmp += "Or Br Yr Bl Yl Ol ";
            }
            else if (sides[5][4] + sides[5][1] == 10)
            {
                BR();
                RR();
                YR();
                RL();
                YL();
                BL();
                tmp += "Br Rr Yr Rl Yl Bl ";
            }

            if (sides[5][1] + sides[5][6] == 10)
            {
                BR();
                RR();
                YR();
                RL();
                YL();
                BL();
                tmp += "Br Rr Yr Rl Yl Bl ";
            }
            else if (sides[5][3] + sides[5][4] == 10)
            {
                RR();
                GR();
                YR();
                GL();
                YL();
                RL();
                tmp += "Rr Gr Yr Gl Yl Rl ";
            }
        }

        while (sides[1][1] != 1)
        {
            YL();
            tmp += "Yl ";
        }

        if (sides[3][1] != 3 || sides[2][1] != 2 || sides[4][1] != 4)
        {
            if (sides[3][1] == 3)
            {
                RR();
                YR();
                RL();
                YR();
                RR();
                YL();
                YL();
                RL();
                tmp += "Rr Yr Rl Yr Rr Yl Yl Rl ";
                BR();
                YR();
                BL();
                YR();
                BR();
                YL();
                YL();
                BL();
                YR();
                tmp += "Br Yr Bl Yr Br Yl Yl Bl Yr ";
            }
            else if (sides[2][1] == 2)
            {
                BR();
                YR();
                BL();
                YR();
                BR();
                YL();
                YL();
                BL();
                YR();
                tmp += "Br Yr Bl Yr Br Yl Yl Bl Yr ";
            }
            else if (sides[4][1] == 4)
            {
                OR();
                YR();
                OL();
                YR();
                OR();
                YL();
                YL();
                OL();
                YR();
                tmp += "Or Yr Ol Yr Or Yl Yl Ol Yr ";
            }
            else if (sides[4][1] == 2)
            {
                YL();
                GR();
                YR();
                GL();
                YR();
                GR();
                YL();
                YL();
                GL();
                YR();
                tmp += "Yl Gr Yr Gl Yr Gr Yl Yl Gl Yr ";
            }
            else
            {
                YR();
                RR();
                YR();
                RL();
                YR();
                RR();
                YL();
                YL();
                RL();
                YR();
                tmp += "Yr Rr Yr Rl Yr Rr Yl Yl Rl Yr ";
            }
        }

        return tmp;
    }

    std::string sixth_step()
    {
        std::string tmp;

        int key = 0;
        while ((sides[5][0] * sides[1][0] * sides[4][2]) != 20)
        {
            GR();
            YL();
            BL();
            YR();
            GL();
            YL();
            BR();
            YR();
            tmp += "Gr Yl Bl Yr Gl Yl Br Yr ";
            key++;
            if (key % 3 == 2)
            {
                OR();
                YL();
                RL();
                YR();
                OL();
                YL();
                RR();
                YR();
                tmp += "Or Yl Rl Yr Ol Yl Rr Yr ";
            }
        }
        while ((sides[5][2] * sides[3][2] * sides[4][0]) != 60)
        {
            RR();
            YL();
            OL();
            YR();
            RL();
            YL();
            OR();
            YR();
            tmp += "Rr Yl Ol Yr Rl Yl Or Yr ";
        }

        return tmp;
    }

    std::string seventh_step()
    {
        std::string tmp;

        int key = 0;
        while (key < 4)
        {
            while (sides[5][0] != 5)
            {
                OR();
                WR();
                OL();
                WL();
                tmp += "Or Wr Ol Wl ";
                key = 0;
            }
            YL();
            tmp += "Yl ";
            key++;
        }
        while (sides[1][1] != 1)
        {
            YL();
            tmp += "Yl ";
        }

        return tmp;
    }

    std::string solve()
    {
        std::string ans;

        if(!cube_is_correct()){
            ans = "Cube is not correct.\n";
            return ans;
        }

        ans += first_step();
        ans += second_step();
        ans += third_step();
        ans += fourth_step();
        ans += fifth_step();
        ans += sixth_step();
        ans += seventh_step();

        ans = compact_string(ans);
        
        return ans;
    }

    void output_solve_in_file(std::string file_name)
    {
        std::ofstream ostrm(file_name, std::ios::binary);
        
        std::string solv = compact_string(solve());

        for (int i = 0; i < solv.size(); ++i)
        {
            ostrm << solv[i];
            if (i % 30 == 29)
            {
                ostrm << '\n';
            }
        }
    }

    void output()
    {
        std::cout << "..." << int_to_char(sides[5][0]) << int_to_char(sides[5][1]) << int_to_char(sides[5][2]) << "......\n";
        std::cout << "..." << int_to_char(sides[5][3]) << 'y' << int_to_char(sides[5][4]) << "......\n";
        std::cout << "..." << int_to_char(sides[5][5]) << int_to_char(sides[5][6]) << int_to_char(sides[5][7]) << "......\n";
        for (int j = 1; j < 5; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                std::cout << int_to_char(sides[j][i]);
            }
        }
        std::cout << '\n';
        for (int j = 1; j < 5; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                if (i == 1)
                {
                    if (j == 1)
                        std::cout << 'b';
                    if (j == 2)
                        std::cout << 'r';
                    if (j == 3)
                        std::cout << 'g';
                    if (j == 4)
                        std::cout << 'o';
                }
                else
                    std::cout << int_to_char(sides[j][i + 3 - (i / 2)]);
            }
        }
        std::cout << '\n';
        for (int j = 1; j < 5; ++j)
        {
            for (int i = 5; i < 8; ++i)
            {
                std::cout << int_to_char(sides[j][i]);
            }
        }
        std::cout << '\n';
        std::cout << "..." << int_to_char(sides[0][0]) << int_to_char(sides[0][1]) << int_to_char(sides[0][2]) << "......\n";
        std::cout << "..." << int_to_char(sides[0][3]) << 'w' << int_to_char(sides[0][4]) << "......\n";
        std::cout << "..." << int_to_char(sides[0][5]) << int_to_char(sides[0][6]) << int_to_char(sides[0][7]) << "......\n";
    }

    void output_in_file(std::string file_name)
    {
        std::ofstream ostrm(file_name, std::ios::binary);
        
        ostrm << "..." << int_to_char(sides[5][0]) << int_to_char(sides[5][1]) << int_to_char(sides[5][2]) << "......\n";
        ostrm << "..." << int_to_char(sides[5][3]) << 'y' << int_to_char(sides[5][4]) << "......\n";
        ostrm << "..." << int_to_char(sides[5][5]) << int_to_char(sides[5][6]) << int_to_char(sides[5][7]) << "......\n";
        for (int j = 1; j < 5; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                ostrm << int_to_char(sides[j][i]);
            }
        }
        ostrm << '\n';
        for (int j = 1; j < 5; ++j)
        {
            for (int i = 0; i < 3; ++i)
            {
                if (i == 1)
                {
                    if (j == 1)
                        ostrm << 'b';
                    if (j == 2)
                        ostrm << 'r';
                    if (j == 3)
                        ostrm << 'g';
                    if (j == 4)
                        ostrm << 'o';
                }
                else
                    ostrm << int_to_char(sides[j][i + 3 - (i / 2)]);
            }
        }
        ostrm << '\n';
        for (int j = 1; j < 5; ++j)
        {
            for (int i = 5; i < 8; ++i)
            {
                ostrm << int_to_char(sides[j][i]);
            }
        }
        ostrm << '\n';
        ostrm << "..." << int_to_char(sides[0][0]) << int_to_char(sides[0][1]) << int_to_char(sides[0][2]) << "......\n";
        ostrm << "..." << int_to_char(sides[0][3]) << 'w' << int_to_char(sides[0][4]) << "......\n";
        ostrm << "..." << int_to_char(sides[0][5]) << int_to_char(sides[0][6]) << int_to_char(sides[0][7]) << "......\n";
    }

    cube generate()
    {
        int tmp1[8];
        int tmp2[8];
        int tmp3[8];
        int tmp4[8];
        int tmp5[8];
        int tmp6[8];
        for (int i = 0; i < 8; ++i)
        {
            tmp1[i] = 0;
            tmp2[i] = 1;
            tmp3[i] = 2;
            tmp4[i] = 3;
            tmp5[i] = 4;
            tmp6[i] = 5;
        }
        side a1(tmp1);
        side a2(tmp2);
        side a3(tmp3);
        side a4(tmp4);
        side a5(tmp5);
        side a6(tmp6);
        side n[] = {a1, a2, a3, a4, a5, a6};
        cube new_cube(n);
        new_cube.random_shuffle();
        return new_cube;
    }

    void random_shuffle()
    {
        int k = 0;
        for (int i = 0; i < 10; ++i)
        {
            k += rand() % 20;
        }
        for (int i = 0; i < k; ++i)
        {
            int t = rand() % 12;
            if (t % 6 == 0)
            {
                if (t / 6 == 0)
                    WL();
                else
                    WR();
            }
            if (t % 6 == 1)
            {
                if (t / 6 == 0)
                    RL();
                else
                    RR();
            }
            if (t % 6 == 2)
            {
                if (t / 6 == 0)
                    YL();
                else
                    YR();
            }
            if (t % 6 == 3)
            {
                if (t / 6 == 0)
                    OL();
                else
                    OR();
            }
            if (t % 6 == 4)
            {
                if (t / 6 == 0)
                    GL();
                else
                    GR();
            }
            if (t % 6 == 5)
            {
                if (t / 6 == 0)
                    BL();
                else
                    BR();
            }
        }
    }

    ~cube() = default;
    inline const side &operator[](int i) const
    {
        return this->sides[i];
    }
};

#endif