#include <iostream>
#include <fstream>

struct no_copy
{
    no_copy() = default;
    ~no_copy() = default;
    no_copy(const no_copy&) = delete;
    no_copy(no_copy&&) = default;
    no_copy& operator=(const no_copy&) = delete;
    no_copy& operator=(no_copy&&) = delete;
};

struct no_move
{
    no_move() = default;
    ~no_move() = default;
    no_move(const no_move&) = default;
    no_move(no_move&&) = delete;
    no_move& operator=(const no_move&) = delete;
    no_move& operator=(no_move&&) = delete;
};


auto foo(std::ofstream& strm)
{
    auto dump = [nc = no_copy(), nm = no_move(), &strm] () { strm << "Is everything fine?" << std::endl; };
    dump();
    return dump;
}

int main()
{
    std::ofstream out("output.txt");

    auto dumb = foo(out);

    out.close();

    // suicide
    dumb();

    return 0;
}
