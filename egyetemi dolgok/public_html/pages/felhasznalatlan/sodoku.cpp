#include <iostream>
#include <array>
#include <set>
#include <algorithm>

#define DEBUG true

std::array<std::array<int, 9>, 9> Matrix;
std::array<std::array<std::set<int>, 9>, 9> MatrixAvaliable;
int missing = 0;

void input()
{
    for (int i = 0; i < Matrix.size(); ++i)
        for (int j = 0; j < Matrix.size(); ++j)
        {
            std::cin >> Matrix[i][j];
            if (Matrix[i][j] == 0)
            {
                ++missing;
                MatrixAvaliable[i][j] = std::set<int>({1, 2, 3, 4, 5, 6, 7, 8, 9});
            }
        }

    for (int i = 0; i < Matrix.size(); ++i)
        for (int j = 0; j < Matrix.size(); ++j)
        {
            if (Matrix[i][j] != 0)
            {
                //column and line
                for (size_t k = 0; k < Matrix.size(); k++)
                {
                    MatrixAvaliable[i][k].erase(Matrix[i][j]);
                    MatrixAvaliable[k][j].erase(Matrix[i][j]);
                }
                //house
                for (int k = 3 * (i / 3); k < 3 * (i / 3) + 3; ++k)
                    for (int l = 3 * (j / 3); l < 3 * (j / 3) + 3; ++l)
                        MatrixAvaliable[k][l].erase(Matrix[i][j]);
            }
        }
}

void write()
{
    for (int i = 0; i < Matrix.size(); ++i)
    {
        for (int j = 0; j < Matrix.size(); ++j)
            std::cout << Matrix[i][j] << " ";
        std::cout << "\n";
    }
}

void solver(const int i, const int j)
{
    if (MatrixAvaliable[i][j].size() == 1)
    {
        if (DEBUG)
            std::cout << "found " << i << " " << j << " " << *(MatrixAvaliable[i][j].begin()) << "\n";

        Matrix[i][j] = *(MatrixAvaliable[i][j].begin());
        --missing;
        MatrixAvaliable[i][j].clear();

        //column and line
        for (size_t k = 0; k < Matrix.size(); k++)
        {
            MatrixAvaliable[i][k].erase(Matrix[i][j]);
            MatrixAvaliable[k][j].erase(Matrix[i][j]);
        }
        //house
        for (int k = 3 * (i / 3); k < 3 * (i / 3) + 3; ++k)
            for (int l = 3 * (j / 3); l < 3 * (j / 3) + 3; ++l)
                MatrixAvaliable[k][l].erase(Matrix[i][j]);
        return;
    }

    //house exclusion
    std::multiset<int> possibilities;
    for (int k = 3 * (i / 3); k < 3 * (i / 3) + 3; ++k)
        for (int l = 3 * (j / 3); l < 3 * (j / 3) + 3; ++l)
        {
            auto copySet = MatrixAvaliable[k][l];
            possibilities.merge(copySet);
        }

    for (int value = 1; value < 10; ++value)
        if (possibilities.count(value) == 1)
        {
            for (int k = 3 * (i / 3); k < 3 * (i / 3) + 3; ++k)
                for (int l = 3 * (j / 3); l < 3 * (j / 3) + 3; ++l)
                    if (MatrixAvaliable[k][l].count(value) == 1)
                    {
                        if (DEBUG)
                            std::cout << "found " << k << " " << l << " " << value << "\n";
                        Matrix[k][l] = value;
                        MatrixAvaliable[k][l].clear();
                        --missing;
                        //column and line
                        for (size_t m = 0; m < Matrix.size(); ++m)
                        {
                            MatrixAvaliable[k][m].erase(value);
                            MatrixAvaliable[m][l].erase(value);
                        }
                        //house
                        for (int m = 3 * (k / 3); m < 3 * (k / 3) + 3; ++m)
                            for (int n = 3 * (l / 3); n < 3 * (l / 3) + 3; ++n)
                                MatrixAvaliable[m][n].erase(value);
                        return;
                    }
        }

    //column exclusion
    possibilities.clear();

    for (int k = 0; k < Matrix.size(); ++k)
    {
        auto copySet = MatrixAvaliable[k][j];
        possibilities.merge(copySet);
    }

    for (int value = 1; value < 10; ++value)
        if (possibilities.count(value) == 1)
        {
            for (int k = 0; k < Matrix.size(); ++k)
                if (MatrixAvaliable[k][j].count(value) == 1)
                {
                    if (DEBUG)
                        std::cout << "found " << k << " " << j << " " << value << "\n";
                    MatrixAvaliable[k][j].clear();
                    Matrix[k][j] = value;
                    --missing;
                    //column and line
                    for (size_t m = 0; m < Matrix.size(); ++m)
                    {
                        MatrixAvaliable[k][m].erase(value);
                        MatrixAvaliable[m][j].erase(value);
                    }
                    //house

                    for (int m = 3 * (k / 3); m < 3 * (k / 3) + 3; ++m)
                        for (int n = 3 * (j / 3); n < 3 * (j / 3) + 3; ++n)
                            MatrixAvaliable[m][n].erase(value);
                    return;
                }
        }

    //row exclusion
    possibilities.clear();

    for (int k = 0; k < Matrix.size(); ++k)
    {

        auto copySet = MatrixAvaliable[i][k];
        possibilities.merge(copySet);
    }

    for (int value = 1; value < 10; ++value)
        if (possibilities.count(value) == 1)
        {
            for (int k = 0; k < Matrix.size(); ++k)
                if (MatrixAvaliable[i][k].count(value) == 1)
                {
                    if (DEBUG)
                        std::cout << "found " << i << " " << k << " " << value << "\n";

                    MatrixAvaliable[i][k].clear();
                    Matrix[i][k] = value;
                    --missing;

                    //column and line
                    for (size_t m = 0; m < Matrix.size(); ++m)
                    {
                        MatrixAvaliable[i][m].erase(value);
                        MatrixAvaliable[m][k].erase(value);
                    }
                    //house

                    for (int m = 3 * (i / 3); m < 3 * (i / 3) + 3; ++m)
                        for (int n = 3 * (k / 3); n < 3 * (k / 3) + 3; ++n)
                            MatrixAvaliable[m][n].erase(value);
                    return;
                }
        }
}

void solve()
{
    for (int i = 0; i < Matrix.size(); ++i)
        for (int j = 0; j < Matrix.size(); ++j)
            if (Matrix[i][j] == 0)
                solver(i, j);
}

int main()
{

    input();
    int last = 0;
    int last1 = 1;
    while (last != last1)
    {
        last = last1;
        last1 = missing;
        solve();
        solve();
    }
    std::endl(std::cout);
    write();
    std::cout << "\n";

    return 1;
}