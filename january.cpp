// My tidied up solutions to https://adventofcode.com/2017

#include <iostream>
#include <cassert>
#include <sstream>
#include <limits>
#include <vector>
#include <cmath>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cstdint>
#include <map>
#include <unordered_map>
#include <regex>
#include <deque>
#include <chrono>
#include <random>
#include <valarray>


#include "puzzle_input.h"




namespace day01 {

/*  Commentary: left in the spirit of my original solution, but removed
    some boundary tests that were superfluous to the idea of just doing
    the minimum needed to get the right answer to the given problem.
*/

std::string run(int part)
{
    struct local {
        // return the sum of all digits that match the next digit in 's'
        static int captcha(const std::string s)
        {
            char prev = s.back(); // the list is "circular"
            int sum = 0;
            for (auto c: s) {
                if (c == prev)
                    sum += c - '0';
                prev = c;
            }
            return sum;
        }

        // return the sum of all digits that match the digit halfway around the circular list 's'
        static int captcha2(const std::string s)
        {
            const int len = s.size();
            int sum = 0;
            for (int i = 0; i < len; ++i) {
                if (s[i] == s[(i + len / 2) % len])
                    sum += s[i] - '0';
            }
            return sum;
        }
    };

    if (part == 1) {
        assert(local::captcha("1122") == 3);
        assert(local::captcha("1111") == 4);
        assert(local::captcha("1234") == 0);
        assert(local::captcha("91212129") == 9);

        const int answer = local::captcha(input);
        assert(answer == 1390);
        return std::to_string(answer);
    }
    else {
        assert(local::captcha2("1212") == 6);
        assert(local::captcha2("1221") == 0);
        assert(local::captcha2("123425") == 4);
        assert(local::captcha2("123123") == 12);
        assert(local::captcha2("12131415") == 4);

        const int answer = local::captcha2(input);
        assert(answer == 1232);
        return std::to_string(answer);
    }
}

}


namespace day02 {

/*  Commentary: Since writing my original solution I've learned about
    std::istream_iterator<int>, to read the numbers into a vector, from
    https://github.com/willkill07/AdventOfCode2017/blob/master/include/Day02.hpp.
    I've used this in csum2 instead of my original solution's eachint().
*/

std::string run(int part)
{
    struct local {
        // return the checksum of the given input 's'
        static int csum(const char * s)
        {
            int result = 0;

            // "For each row, determine the difference between the largest
            // value and the smallest value; the checksum is the sum of all
            // of these differences."

            std::istringstream iss(s);
            for (std::string line; std::getline(iss, line); ) {
                int smallest = std::numeric_limits<int>::max();
                int biggest =  std::numeric_limits<int>::min();
                std::istringstream numbers(line);
                int n;
                while (numbers >> n) {
                    if (n < smallest)
                        smallest = n;
                    if (n > biggest)
                        biggest = n;
                }
                result += biggest - smallest;
            }

            return result;
        }

        // return the checksum of the given input 's'
        static int csum2(const char * s)
        {
            int result = 0;
            
            // Find the only two numbers in each line where the result of
            // a dividing one by the other is a whole number, divide them,
            // and sum all the quotients.

            auto even_dividers_divided = [](const std::vector<int> & v) -> int
            {
                for (std::vector<int>::size_type i = 0; i < v.size(); ++i)
                    for (std::vector<int>::size_type j = i + 1; j < v.size(); ++j)
                        if (v[i] < v[j]) {
                            if (v[j] % v[i] == 0)
                                return v[j] / v[i];
                        }
                        else {
                            if (v[i] % v[j] == 0)
                                return v[i] / v[j];
                        }
                return 0; // should never get here
            };

            std::istringstream ss(s);
            for (std::string line; std::getline(ss, line); ) {
                std::istringstream nums(line);
                const std::vector<int> v{std::istream_iterator<int>(nums), std::istream_iterator<int>()};
                result += even_dividers_divided(v);
            }

            return result;
        }
    };

    if (part == 1) {
        const char * test1 =
            "5 1 9 5\n"
            "7 5 3\n"
            "2 4 6 8\n";

        assert(local::csum(test1) == 18);

        const int answer = local::csum(input);
        assert(answer == 47136);
        return std::to_string(answer);
    }
    else {
        const char * test2 =
            "5 9 2 8\n"
            "9 4 7 3\n"
            "3 8 6 5\n";

        assert(local::csum2(test2) == 9);

        const int answer2 = local::csum2(input);
        assert(answer2 == 250);
        return std::to_string(answer2);
    }
}

}



namespace day03 {

/*  Commentary: I've left this solution untouched. It's ugly
    and I'm not proud of it. Just go and look at
    https://github.com/willkill07/AdventOfCode2017/blob/master/include/Day03.hpp.
*/


int square(int x)
{
    return x * x;
}


struct points {
    int x1, y1, xn, yn;
};

points lookup(int n)
{
    int len = 3;
    while (square(len) < n)
        len += 2;

    points result;
    result.x1 = result.y1 = len/2;

    int m = square(len-2) + len - 1;
    if (n <= m) {
        result.xn = len-1;
        result.yn = m - n;
        return result;
    }

    m += len - 1;
    if (n <= m) {
        result.xn = m - n;
        result.yn = 0;
        return result;
    }

    m += len - 1;
    if (n <= m) {
        result.xn = 0;
        result.yn = len - (m - n) - 1;
        return result;
    }

    result.xn = n - m;
    result.yn = len - 1;
    return result;
}

int manhattan_distance(points p)
{
    return std::abs(p.xn - p.x1) + std::abs(p.yn - p.y1);
}

int distance(int n)
{
    if (n == 1)
        return 0;

    return manhattan_distance(lookup(n));
}


struct matrix {
    std::vector<int> v;
    int origin_x;
    int origin_y;
    int width;
    int height;
};

int sum_neighbours(const matrix & m, int x, int y)
{
    int result = 0;

    if (x > 0) {
        result += m.v[y * m.width + x - 1];
        if (y > 0)
            result += m.v[(y - 1) * m.width + x - 1];
        if (y < m.height - 1)
            result += m.v[(y + 1) * m.width + x - 1];
    }
    if (x < m.width - 1) {
        result += m.v[y * m.width + x + 1];
        if (y > 0)
            result += m.v[(y - 1) * m.width + x + 1];
        if (y < m.height - 1)
            result += m.v[(y + 1) * m.width + x + 1];
    }
    if (y > 0)
        result += m.v[(y - 1) * m.width + x];
    if (y < m.height - 1)
        result += m.v[(y + 1) * m.width + x];

    return result;
}

void test_sum_neighbours()
{
    /*
        1  2  3
        4  5  6
        7  8  9
    */
    const matrix m{{1, 2, 3, 4, 5, 6, 7, 8, 9}, 1, 1, 3, 3};
    assert(sum_neighbours(m, 0, 0) == 11);
    assert(sum_neighbours(m, 1, 0) == 19);
    assert(sum_neighbours(m, 2, 0) == 13);
    assert(sum_neighbours(m, 0, 1) == 23);
    assert(sum_neighbours(m, 1, 1) == 40);
    assert(sum_neighbours(m, 2, 1) == 27);
    assert(sum_neighbours(m, 0, 2) == 17);
    assert(sum_neighbours(m, 1, 2) == 31);
    assert(sum_neighbours(m, 2, 2) == 19);
}

// call f(x, y) for each spiral address in turn, until f() returns false
template <typename func>
void eachaddress(int origin_x, int origin_y, func f)
{
    /*  "Each square on the grid is allocated in a spiral pattern starting
        at a location marked 1 and then counting up while spiraling outward."

        17  16  15  14  13
        18   5   4   3  12
        19   6   1   2  11
        20   7   8   9  10
        21  22  23---> ...
    */
    if (!f(origin_x, origin_y))
        return;

    int x = origin_x;
    int y = origin_y;
    int m = 1;
    for (int n = 2, len = 3; ; len += 2) {
        ++x;
        ++y;

        m += len - 1;
        while (n <= m) {
            if (!f(x, --y))
                return;
            ++n;
        }

        m += len - 1;
        while (n <= m) {
            if (!f(--x, y))
                return;
            ++n;
        }

        m += len - 1;
        while (n <= m) {
            if (!f(x, ++y))
                return;
            ++n;
        }

        m += len - 1;
        while (n <= m) {
            if (!f(++x, y))
                return;
            ++n;
        }
    }
}

void test_eachaddress()
{
    /*  10  11  12  13  14
    0   17  16  15  14  13
    1   18   5   4   3  12
    2   19   6   1   2  11
    3   20   7   8   9  10
    4   21  22  23---> ...
    */
    int expected[] = {
        12, 2,
        13, 2,
        13, 1,
        12, 1,
        11, 1,
        11, 2,
        11, 3,
        12, 3,
        13, 3,
        14, 3,
        14, 2,
        14, 1,
        14, 0,
        13, 0,
        12, 0,
        11, 0,
        10, 0,
        10, 1,
        10, 2,
        10, 3,
        10, 4,
        11, 4,
        12, 4,
        13, 4,
        14, 4,
        15, 4,
        15, 3,
        0};
    int i = 0;
    eachaddress(12, 2, [&](int x, int y) {
        assert(x == expected[i]);
        assert(y == expected[i + 1]);
        i += 2;
        return expected[i] != 0;
    });
}


std::string run(int part)
{
    if (part == 1) {
        /*
            17  16  15  14  13
            18   5   4   3  12
            19   6   1   2  11
            20   7   8   9  10
            21  22  23---> ...

            1 x 1   1..1
            3 x 3   2..9    2..3    3..5    5..7    7..9
            5 x 5   10..25  10..13  13..17  17..21  21..25
        */
        assert(distance(1) == 0);
        assert(distance(12) == 3);
        assert(distance(23) == 2);
        assert(distance(1024) == 31);

        assert(distance(17) == 4);
        assert(distance(16) == 3);
        assert(distance(15) == 2);
        assert(distance(14) == 3);
        assert(distance(13) == 4);

        assert(distance(18) == 3);
        assert(distance( 5) == 2);
        assert(distance( 4) == 1);
        assert(distance( 3) == 2);
        assert(distance(12) == 3);

        assert(distance(19) == 2);
        assert(distance( 6) == 1);
        assert(distance( 1) == 0);
        assert(distance( 2) == 1);
        assert(distance(11) == 2);

        assert(distance(21) == 4);
        assert(distance(22) == 3);
        assert(distance(23) == 2);
        assert(distance(24) == 3);
        assert(distance(25) == 4);

        const int answer = distance(368078);
        assert(answer == 371);
        return std::to_string(answer);
    }
    else {
        /*
            147  142  133  122   59
            304    5    4    2   57
            330   10    1    1   54
            351   11   23   25   26
            362  747  806--->   ...
        */
        test_sum_neighbours();
        test_eachaddress();

        int sum;
        const int width = 380 * 2;
        const int height = 380 * 2;
        matrix m{{}, width/2, height/2, width, height};
        m.v.resize(width * height, 0);
        eachaddress(m.origin_x, m.origin_y, [&](int x, int y) {
            sum = sum_neighbours(m, x, y);
            if (sum == 0)
                sum = 1;
            m.v[y * m.width + x] = sum;

            return sum <= 368078;
        });

        assert(sum == 369601);
        return std::to_string(sum);
    }
}

}


namespace day04 {

/*  Commentary: I think my original solution was ok, but looking at
    https://github.com/willkill07/AdventOfCode2017/blob/master/include/Day04.hpp
    I've learned of the existance of std::all_of() and that std::set::insert()
    returns a std::pair, the second element of which is true if a new element
    was inserted and false if the element already existed.
*/

// return true iff at least two words in given 's' are the same as each other 
bool contains_duplicate_words(const std::string s)
{
    std::set<std::string> dict;
    std::istringstream iss(s);
    for (std::string word; iss >> word; ) {
        if (!dict.insert(word).second)
            return true; // word is already in dict
    }
    return false;
}

// return true iff at least two words in given 's' are anagrams of each other 
bool contains_anagrams(const std::string s)
{
    std::set<std::string> dict;
    std::istringstream iss(s);
    for (std::string word; iss >> word; ) {
        std::sort(begin(word), end(word));
        if (!dict.insert(word).second)
            return true; // word is already in dict
    }
    return false;
}


std::string run(int part)
{
    if (part == 1) {
        int valid_count = 0;
        std::istringstream iss(input); // input from puzzle_input.h
        for (std::string line; std::getline(iss, line); )
            valid_count += !contains_duplicate_words(line);

        assert(valid_count == 455);
        return std::to_string(valid_count);
    }
    else {
        assert(!contains_anagrams("abcde fghij"));
        assert(contains_anagrams("abcde xyz ecdab"));
        assert(!contains_anagrams("a ab abc abd abf abj"));
        assert(!contains_anagrams("iiii oiii ooii oooi oooo"));
        assert(contains_anagrams("oiii ioii iioi iiio"));

        int valid_count = 0;
        std::istringstream iss(input); // input from puzzle_input.h
        for (std::string line; std::getline(iss, line); )
            valid_count += !contains_anagrams(line);

        assert(valid_count == 186);
        return std::to_string(valid_count);
    }
}

}


namespace day05 {

/*  Commentary: I think my original solution was ok, so I've left it alone */

// return the number of steps taken before jumping out of given 'tbl'
int jumps(std::vector<int> tbl)
{
    int steps = 0;
    for (int pc = 0; pc >= 0 && pc < static_cast<int>(tbl.size()); pc += tbl[pc]++)
        ++steps;
    return steps;
}

// return the number of steps taken before jumping out of given 'tbl'
uint64_t jumps2(std::vector<int> tbl)
{
    uint64_t steps = 0;
    for (int pc = 0; pc >= 0 && pc < static_cast<int>(tbl.size()); ) {
        int offset = tbl[pc];
        tbl[pc] += (offset >= 3) ? -1 : +1;
        pc += offset;
        ++steps;
    }
    return steps;
}

std::string run(int part)
{
    const std::vector<int> test{0, 3, 0, 1, -3};

    if (part == 1) {
        /*
        (0) 3  0  1  -3  - before we have taken any steps.
        (1) 3  0  1  -3  - jump with offset 0 (that is, don't jump at all). Fortunately, the instruction is then incremented to 1.
         2 (3) 0  1  -3  - step forward because of the instruction we just modified. The first instruction is incremented again, now to 2.
         2  4  0  1 (-3) - jump all the way to the end; leave a 4 behind.
         2 (4) 0  1  -2  - go back to where we just were; increment -3 to -2.
         2  5  0  1  -2  - jump 4 steps forward, escaping the maze.
         In this example, the exit is reached in 5 steps.
         */
        assert(jumps(test) == 5);

        const int steps = jumps(input); // input from puzzle_input.h
        assert(steps == 358309);
        return std::to_string(steps);
    }
    else {
        assert(jumps2(test) == 10);
        const uint64_t steps2 = jumps2(input); // input from puzzle_input.h
        assert(steps2 == 28178177);
        return std::to_string(steps2);
    }
}

}


namespace day06 {

/*  Commentary: I think my solution was ok. I've since learned about
    std::map::emplace(), which I've made use of in this version. I've
    also replaced my for loop with std::max_element().
*/


// return the number of redistribution cycles before a seeing a repeated configuration
int cycles_to_first_repeat(std::vector<int> banks)
{
    int cycle_count = 0;

    for (std::set<std::vector<int>> state; state.insert(banks).second; ++cycle_count) {
        auto pb = std::max_element(std::begin(banks), std::end(banks));
        int blocks = *pb;
        *pb++ = 0;
        for (;  blocks--; ++pb) {
            if (pb == std::end(banks))
                pb = std::begin(banks);
            ++*pb;
        }
    }

    return cycle_count;
}

// return the number of redistribution cycles between the first two repeated configurations
int cycles_between_repeats(std::vector<int> banks)
{
    int cycle_index = 0;

    std::map<std::vector<int>, int> state;
    while (state.emplace(banks, ++cycle_index).second) {
        auto pb = std::max_element(std::begin(banks), std::end(banks));
        int blocks = *pb;
        *pb++ = 0;
        for (;  blocks--; ++pb) {
            if (pb == std::end(banks))
                pb = std::begin(banks);
            ++*pb;
        }
    }

    return cycle_index - state[banks];
}


std::string run(int part)
{
    const std::vector<int> test{0, 2, 7, 0};
    const std::vector<int> input{
        0,	5,	10,	0,	11,	14,	13,	4,	11,	8,	8,	7,	1,	4,	12,	11};

    if (part == 1) {
        assert(cycles_to_first_repeat(test) == 5);

        const int cycle_count = cycles_to_first_repeat(input);
        assert(cycle_count == 7864);
        return std::to_string(cycle_count);
    }
    else {
        assert(cycles_between_repeats(test) == 4);

        const int cycle_count = cycles_between_repeats(input);
        assert(cycle_count == 1695);
        return std::to_string(cycle_count);
    }
}

}


namespace day07 {

/*  Commentary: I think my part 1 solution was ok. I've just ditched the
    std::regex parsing for simple stringstream reads (making it an order
    of magnitued faster). Part 2 is also ok in that it attacks the problem
    in a straightforward way, and gets the right answer!
*/

struct info {
    std::string name;
    int weight;
    std::vector<std::string> names;
};

// return an info structure containing the data in given 's'
// e.g. parse("luhxcq (68) -> xiwnu, gezqw") -> info{"luhxcq", 68, {"xiwnu", "gezqw"}}
info parse(std::string s)
{
    info result;

    std::locale loc;
    std::replace_if(std::begin(s), std::end(s),
        [&](char c){ return !std::isalnum(c, loc); },
        ' '); // replace all punctuation with whitespace
    std::istringstream iss(s);
    iss >> result.name >> result.weight;
    for (std::string child; iss >> child; )
        result.names.push_back(child);

    return result;
}

// return the name of the only node in the given 'input' that has
// no parent (i.e. the root node)
std::string find_orphan(const std::string input)
{
    std::set<std::string> parents, children;
    std::istringstream iss(input);
    for (std::string line; std::getline(iss, line); ) {
        const info i = parse(line);
        parents.insert(i.name);
        for (auto n: i.names)
            children.insert(n);
    }

    std::set<std::string> orphan;
    std::set_difference(
        parents.begin(), parents.end(),
        children.begin(), children.end(), 
        std::inserter(orphan, orphan.begin()));

    assert(orphan.size() == 1);
    return *orphan.begin();
}

// return the total weight of the tower called 'base'
int sum(const std::map<std::string, info> & data, std::string base)
{
    const info & i = data.at(base);
    int s = i.weight;
    for (auto n: i.names)
        s += sum(data, n);
    return s;
}

// find the overweight tower in the given 'tower_weights', if any
bool find_overweight_tower(const std::vector<int> & tower_weights, int & excess_weight, int & excess_tower_index)
{
    const int tower_count = static_cast<int>(tower_weights.size());
    if (tower_count == 0)
        return false;
    assert(tower_count > 1);

    int w = tower_weights.at(0);
    int i = 1;
    while (i < tower_count && tower_weights.at(i) == w)
        ++i;
    if (i == tower_count)
        return false; // all towers weigh the same

    // tower 0 does not weigh the same as tower i
    // ASSUME the heaver tower is the one and only fault
    if (w < tower_weights.at(i)) {
        excess_weight = tower_weights.at(i) - w;
        excess_tower_index = i;
    }
    else {
        excess_weight = w - tower_weights.at(i);
        excess_tower_index = 0;
    }
    return true;
}

// "Given that exactly one program is the wrong weight, what would its weight need to be to balance the entire tower?"
int balance(const std::map<std::string, info> & data, std::string base)
{
    int excess_weight = 0;

    for (;;) {
        const info & i = data.at(base);
        std::vector<int> tower_weights;
        for (auto n: i.names)
            tower_weights.push_back(sum(data, n));

        if (tower_weights.empty()) {
            // we are at a leaf node and it must be too heavy by excess_weight
            return i.weight - excess_weight;
        }
        else {
            // there are towers above this node
            int ew, excess_tower_index;
            if (find_overweight_tower(tower_weights, ew, excess_tower_index)) {
                // one of the towers above us is overweight - the one and only fault must lie above this node
                assert(excess_weight == 0 || ew == excess_weight);
                excess_weight = ew;
                base = i.names[excess_tower_index];
            }
            else {
                // everything above this node is balanced - the one and only fault must lie at this node
                return i.weight - excess_weight;
            }
        }
    }

    return 0;
}

int part2(const std::string input, std::string base)
{
    std::map<std::string, info> data;
    std::istringstream iss(input);
    for (std::string line; std::getline(iss, line); ) {
        const info i = parse(line);
        data[i.name] = i;
    }

    return balance(data, base);
}

std::string run(int part)
{
    std::string test{
        "pbga (66)\n"
        "xhth (57)\n"
        "ebii (61)\n"
        "havc (66)\n"
        "ktlj (57)\n"
        "fwft (72) -> ktlj, cntj, xhth\n"
        "qoyq (66)\n"
        "padx (45) -> pbga, havc, qoyq\n"
        "tknk (41) -> ugml, padx, fwft\n"
        "jptl (61)\n"
        "ugml (68) -> gyxo, ebii, jptl\n"
        "gyxo (61)\n"
        "cntj (57)\n"};

    if (part == 1) {
        assert(find_orphan(test) == "tknk");

        const std::string orphan = find_orphan(input); // input from puzzle_input.h
        assert(orphan == "fbgguv");
        return orphan;
    }
    else {
        assert(part2(test, "tknk") == 60);

        const int excess_weight = part2(input, "fbgguv"); // input from puzzle_input.h
        assert(excess_weight == 1864);
        return std::to_string(excess_weight);
    }
}

}


namespace day08 {

/*  Commentary: in essence this code is the same as my original solution. */

// return the highest value in any register after performing all ops in given 'input'
int compute(const char * input)
{
    // map reg name -> value
    std::map<std::string, int> regs;

    std::istringstream inputss(input);
    for (std::string line; std::getline(inputss, line); ) {
        // e.g. "b inc 5 if a > 1"
        // assume there is always a space between each symbol
        std::istringstream liness(line);
        std::string reg, op, ifsym, predreg, pred;
        int val, predval;
        liness >> reg >> op >> val >> ifsym >> predreg >> pred >> predval;

        bool perfom_op = false;
        if (pred == "<")        perfom_op = regs[predreg] <  predval;
        else if (pred == "<=")  perfom_op = regs[predreg] <= predval;
        else if (pred == "==")  perfom_op = regs[predreg] == predval;
        else if (pred == "!=")  perfom_op = regs[predreg] != predval;
        else if (pred == ">=")  perfom_op = regs[predreg] >= predval;
        else if (pred == ">")   perfom_op = regs[predreg] >  predval;
        else assert(false);
        if (perfom_op)
            regs[reg] += op == "inc" ? val : -val;
    }

    typedef const std::pair<std::string, int> pair;
    return std::max_element(std::begin(regs), std::end(regs),
        [](pair & a, pair &  b){ return a.second < b.second; })->second;
}

// return the highest value held in any register while performing all ops in given 'input'
int execute_find_highest(const char * input)
{
    int highest_value = 0;

    // map reg name -> value
    std::map<std::string, int> regs;

    std::istringstream inputss(input);
    for (std::string line; std::getline(inputss, line); ) {
        // e.g. "b inc 5 if a > 1"
        // assume there is always a space between each symbol
        std::istringstream liness(line);
        std::string reg, op, ifsym, predreg, pred;
        int val, predval;
        liness >> reg >> op >> val >> ifsym >> predreg >> pred >> predval;

        bool perfom_op = false;
        if (pred == "<")        perfom_op = regs[predreg] <  predval;
        else if (pred == "<=")  perfom_op = regs[predreg] <= predval;
        else if (pred == "==")  perfom_op = regs[predreg] == predval;
        else if (pred == "!=")  perfom_op = regs[predreg] != predval;
        else if (pred == ">=")  perfom_op = regs[predreg] >= predval;
        else if (pred == ">")   perfom_op = regs[predreg] >  predval;
        else assert(false);
        if (perfom_op)
            regs[reg] += op == "inc" ? val : -val;

        if (regs[reg] > highest_value)
            highest_value = regs[reg];
    }

    return highest_value;
}


std::string run(int part)
{
    const char * test = 
        "b inc 5 if a > 1\n"
        "a inc 1 if b < 5\n"
        "c dec -10 if a >= 1\n"
        "c inc -20 if c == 10\n";

    if (part == 1) {
        assert(compute(test) == 1);

        const int result = compute(input); // input from puzzle_input.h
        assert(result == 4066);
        return std::to_string(result);
    }
    else {
        assert(execute_find_highest(test) == 10);

        const int highest_value = execute_find_highest(input); // input from puzzle_input.h
        assert(highest_value == 4829);
        return std::to_string(highest_value);
    }
}

}


namespace day09 {

/*  Commentary: added comments, nothing else. */

// return the total score for all groups in given 'input'
int parse(const char * input)
{
    int score = 0;

    enum class states { start, in_garbage, cancel_next };
    states state = states::start;
    int group_depth = 0;

    for (const char * p = input; *p; ++p) {
        switch (state) {
            case states::start:
                if (*p == '<')
                    state = states::in_garbage;
                else if (*p == '{')
                    score += ++group_depth;
                else if (*p == '}')
                    --group_depth;
                break;
            case states::in_garbage:
                if (*p == '>')
                    state = states::start;
                else if (*p == '!')
                    state = states::cancel_next;
                break;
            case states::cancel_next:
                state = states::in_garbage;
                break;
        }
    }

    return score;
}

// return total number of non-canceled characters within the garbage in given 'input'
int count_cancelled(const char * input)
{
    int cancelled = 0;

    enum class states { start, in_garbage, cancel_next };
    states state = states::start;
    int group_depth = 0;

    for (const char * p = input; *p; ++p) {
        switch (state) {
            case states::start:
                if (*p == '<')
                    state = states::in_garbage;
                else if (*p == '{')
                    ++group_depth;
                else if (*p == '}')
                    --group_depth;
                break;
            case states::in_garbage:
                if (*p == '>')
                    state = states::start;
                else if (*p == '!')
                    state = states::cancel_next;
                else
                    ++cancelled;
                break;
            case states::cancel_next:
                state = states::in_garbage;
                break;
        }
    }

    return cancelled;
}

std::string run(int part)
{
    if (part == 1) {
        assert(parse("<>") == 0);                       // empty garbage.
        assert(parse("<random characters>") == 0);      // garbage containing random characters.
        assert(parse("<<<<>") == 0);                    // because the extra < are ignored.
        assert(parse("<{!>}>") == 0);                   // because the first > is canceled.
        assert(parse("<!!>") == 0);                     // because the second ! is canceled, allowing the > to terminate the garbage.
        assert(parse("<!!!>>") == 0);                   // because the second ! and the first > are canceled.
        assert(parse("<{o\"i!a,<{i<a>") == 0);          // which ends at the first >.

        assert(parse("{}") == 1);
        assert(parse("{{{}}}") == 6);                           // score of 1 + 2 + 3 = 6.
        assert(parse("{{},{}}") == 5);                          // score of 1 + 2 + 2 = 5.
        assert(parse("{{{},{},{{}}}}") == 16);                  // score of 1 + 2 + 3 + 3 + 3 + 4 = 16.
        assert(parse("{<a>,<a>,<a>,<a>}") == 1);                // score of 1.
        assert(parse("{{<ab>},{<ab>},{<ab>},{<ab>}}") == 9);    // score of 1 + 2 + 2 + 2 + 2 = 9.
        assert(parse("{{<!!>},{<!!>},{<!!>},{<!!>}}") == 9);    // score of 1 + 2 + 2 + 2 + 2 = 9.
        assert(parse("{{<a!>},{<a!>},{<a!>},{<ab>}}") == 3);    // score of 1 + 2 = 3.

        const int part1 = parse(input); // input from puzzle_input.h
        assert(part1 == 15922);
        return std::to_string(part1);
    }
    else {
        assert(count_cancelled("<>") == 0);
        assert(count_cancelled("<random characters>") == 17);
        assert(count_cancelled("<<<<>") == 3);
        assert(count_cancelled("<{!>}>") == 2);
        assert(count_cancelled("<!!>") == 0);
        assert(count_cancelled("<!!!>>") == 0);
        assert(count_cancelled("<{o\"i!a,<{i<a>") == 10);

        const int part2 = count_cancelled(input); // input from puzzle_input.h
        assert(part2 == 7314);
        return std::to_string(part2);
    }
}

}


namespace day10 {

/*  Commentary: original solution unchanged. */

/*
Suppose we instead only had a circular list containing five elements, 0, 1, 2, 3, 4, and were given input lengths of 3, 4, 1, 5.

The list begins as [0] 1 2 3 4 (where square brackets indicate the current position).
The first length, 3, selects ([0] 1 2) 3 4 (where parentheses indicate the sublist to be reversed).
After reversing that section (0 1 2 into 2 1 0), we get ([2] 1 0) 3 4.
Then, the current position moves forward by the length, 3, plus the skip size, 0: 2 1 0 [3] 4. Finally, the skip size increases to 1.
The second length, 4, selects a section which wraps: 2 1) 0 ([3] 4.
The sublist 3 4 2 1 is reversed to form 1 2 4 3: 4 3) 0 ([1] 2.
The current position moves forward by the length plus the skip size, a total of 5, causing it not to move because it wraps around: 4 3 0 [1] 2. The skip size increases to 2.
The third length, 1, selects a sublist of a single element, and so reversing it has no effect.
The current position moves forward by the length (1) plus the skip size (2): 4 [3] 0 1 2. The skip size increases to 3.
The fourth length, 5, selects every element starting with the second: 4) ([3] 0 1 2. Reversing this sublist (3 0 1 2 4 into 4 2 1 0 3) produces: 3) ([4] 2 1 0.
Finally, the current position moves forward by 8: 3 4 2 1 [0]. The skip size increases to 4.
In this example, the first two numbers in the list end up being 3 and 4; to check the process, you can multiply them together to produce 12.

*/



void reverse(std::vector<int> & string, int pos, int len)
{
    std::vector<int> cpy(len);
    for (int i = 0; i < len; ++i)
        cpy[i] = string[(pos + i) % string.size()];
    std::reverse(begin(cpy), end(cpy));
    for (int i = 0; i < len; ++i)
        string[(pos + i) % string.size()] = cpy[i];
}

int knot(std::vector<int> string, std::vector<int> input)
{
    int skip = 0;
    int pos = 0;
    for (int len: input) {
        reverse(string, pos, len);
        pos = (pos + len + skip) % string.size();
        ++skip;
    }
    assert(string.size() >= 2);
    return string[0] * string[1];
}

void knot2(std::vector<int> & string, std::vector<int> input, int & pos, int & skip)
{
    for (int len: input) {
        reverse(string, pos, len);
        pos = (pos + len + skip) % string.size();
        ++skip;
    }
}

std::string knothash(const char * input)
{
    std::vector<int> string(256);
    for (int i = 0; i < 256; ++i)
        string[i] = i;

    std::vector<int> length_sequence;
    for (const char * cp = input; *cp; ++cp)
        length_sequence.push_back(*reinterpret_cast<const unsigned char *>(cp));
    const std::vector<int> suffix{17, 31, 73, 47, 23};
    length_sequence.insert(std::end(length_sequence), std::begin(suffix), std::end(suffix));

    int skip = 0;
    int pos = 0;
    for (int round = 0; round < 64; ++round)
        knot2(string, length_sequence, pos, skip);

    std::vector<int> dense_hash(16);
    for (int i = 0; i < 16; ++i) {
        dense_hash[i] = string[i * 16];
        for (int j = 1; j < 16; ++j)
            dense_hash[i] ^= string[i * 16 + j];
    }

    std::string result;
    for (int i: dense_hash) {
        result.push_back("0123456789abcdef"[i >> 4]);
        result.push_back("0123456789abcdef"[i & 0x0f]);
    }

    return result;
}


std::string run(int part)
{
    if (part == 1) {
        std::vector<int> test_string{0, 1, 2, 3, 4};
        const std::vector<int> test_input{3, 4, 1, 5};
        assert(knot(test_string, test_input) == 12);

        std::vector<int> string(256);
        for (int i = 0; i < 256; ++i)
            string[i] = i;
        const int part1 = knot(string, {102,255,99,252,200,24,219,57,103,2,226,254,1,0,69,216});
        assert(part1 == 5577);
        return std::to_string(part1);
    }
    else {
        assert(knothash("") == "a2582a3a0e66e6e86e3812dcb672a272");
        assert(knothash("AoC 2017") == "33efeb34ea91902bb2f59c9920caa6cd");
        assert(knothash("1,2,3") == "3efbe78a8d82f29979031a4aa0b16a9d");
        assert(knothash("1,2,4") == "63960835bcdc130f0b66d7ff4f6a5a8e");

        const std::string answer2 = knothash("102,255,99,252,200,24,219,57,103,2,226,254,1,0,69,216");
        assert(answer2 == "44f4befb0f303c0bafd085f97741d51d");
        return answer2;
    }
}

}


namespace day11 {

/*  Commentary: original solution unchanged. */


// using "3D" "cube coordinates" described in https://www.redblobgames.com/grids/hexagons/

struct point {
    int x, y, z;
};

int manhattan_distance(point a, point b)
{
    //return std::max(std::abs(a.x - b.x), std::abs(a.y - b.y), std::abs(a.z - b.z));
    return (std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z)) / 2;
}

enum class dir {n, nw, ne, s, sw, se};

template <typename func>
void foreach_direction(const char * input, func f)
{
    const char * p = input;
    while (*p) {
        if (*p == 'n') {
            ++p;
            if (*p == 'w') {
                ++p;
                f(dir::nw);
            }
            else if (*p == 'e') {
                ++p;
                f(dir::ne);
            }
            else
                f(dir::n);
        }
        else if (*p == 's') {
            ++p;
            if (*p == 'w') {
                ++p;
                f(dir::sw);
            }
            else if (*p == 'e') {
                ++p;
                f(dir::se);
            }
            else
                f(dir::s);
        }
        else {
            assert(false);
        }
        assert(*p == '\0' || *p == ',');
        if (*p == ',')
            ++p;
    }
}


int final_distance(const char * input)
{
    const point start{0, 0, 0};
    point p = start;
    foreach_direction(input, [&](dir d) {
        switch (d) {
        case dir::n:    ++p.x; --p.z;   break;
        case dir::nw:   ++p.y; --p.z;   break;
        case dir::ne:   ++p.x; --p.y;   break;
        case dir::s:    ++p.z; --p.x;   break;
        case dir::sw:   ++p.y; --p.x;   break;
        case dir::se:   ++p.z; --p.y;   break;
        }
        assert(p.x + p.y + p.z == 0);
    });

    return manhattan_distance(start, p);
}

int furthest_distance(const char * input)
{
    int result = 0;

    const point start{0, 0, 0};
    point p = start;
    foreach_direction(input, [&](dir d) {
        switch (d) {
        case dir::n:    ++p.x; --p.z;   break;
        case dir::nw:   ++p.y; --p.z;   break;
        case dir::ne:   ++p.x; --p.y;   break;
        case dir::s:    ++p.z; --p.x;   break;
        case dir::sw:   ++p.y; --p.x;   break;
        case dir::se:   ++p.z; --p.y;   break;
        }
        assert(p.x + p.y + p.z == 0);
        const int dist = manhattan_distance(start, p);
        if (dist > result)
            result = dist;
    });

    return result;
}


std::string run(int part)
{
    if (part == 1) {
        assert(final_distance("ne,ne,ne") == 3);
        assert(final_distance("ne,ne,sw,sw") == 0);
        assert(final_distance("ne,ne,s,s") == 2);
        assert(final_distance("se,sw,se,sw,sw") == 3);
        assert(final_distance("n,sw,s,se,ne,n,nw,s") == 0);

        const int part1 = final_distance(input);
        assert(part1 == 812);
        return std::to_string(part1);
    }
    else {
        assert(furthest_distance("ne,ne,ne") == 3);
        assert(furthest_distance("ne,ne,sw,sw") == 2);
        assert(furthest_distance("ne,ne,s,s") == 2);
        assert(furthest_distance("se,sw,se,sw,sw") == 3);
        assert(furthest_distance("n,sw,s,se,ne,n,nw,s") == 1);

        const int part2 = furthest_distance(input);
        assert(part2 == 1603);
        return std::to_string(part2);
    }
}

}


namespace day12 {

/*  Commentary: original solution unchanged. */
    
// e.g. parse("2 <-> 0, 3, 4") -> set{0, 2, 3, 4}
std::set<int> parse(std::string line)
{
    std::set<int> result;

    std::locale loc;
    std::istringstream iss(line);
    for (std::string word; iss >> word; ) {
        if (std::isdigit(word[0], loc))
            result.insert(std::stoi(word));
    }

    return result;
}


// implements the UNION/FIND algorithm
class union_find {
public:
    // create 'size' elements named 0 .. size-1, with no connections between elements
    explicit union_find(int size)
    : element_(size)
    {
        for (int i = 0; i < size; ++i)
            element_[i] = i;
    }

    // return the name of the root element of the element named 'p'
    // (beneficial side-effect: the path from 'p' to the root is compressed)
    int find_root(int p)
    {
        // I found this a good place to learn about the UNION/FIND algorithm:
        // http://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf
        while (p != element_[p])
            p = element_[p] = element_[element_[p]];
        return p;
    }

    // return true iff given elements are in the same set
    bool find(int a, int b)
    {
        return find_root(a) == find_root(b);
    }

    // merge the set containing element 'a' into the set containing element 'b'
    void unite(int a, int b)
    {
        const int ra = find_root(a);
        element_[ra] = find_root(b);
    }

private:
    std::vector<int> element_;
};



int connected0(const char * input)
{
    std::vector<std::set<int>> mapping;
    std::istringstream iss(input);
    for (std::string line; std::getline(iss, line); )
        mapping.push_back(parse(line));

    const int num_nodes = static_cast<int>(mapping.size());
    union_find connected_sets(num_nodes);
    for (int i = 0; i < num_nodes; ++i) {
        for (int j: mapping[i])
            connected_sets.unite(i, j);
    }

    int count = 0;
    for (int i = 0; i < num_nodes; ++i) {
        if (connected_sets.find(0, i))
            ++count;
    }

    return count;
}

int connected_groups(const char * input)
{
    std::vector<std::set<int>> mapping;
    std::istringstream iss(input);
    for (std::string line; std::getline(iss, line); )
        mapping.push_back(parse(line));

    const int num_nodes = static_cast<int>(mapping.size());
    union_find connected_sets(num_nodes);
    for (int i = 0; i < num_nodes; ++i) {
        for (int j: mapping[i])
            connected_sets.unite(i, j);
    }

    std::set<int> count;
    for (int i = 0; i < num_nodes; ++i)
        count.insert(connected_sets.find_root(i));

    return count.size();
}

std::string run(int part)
{
    const char * test =
        "0 <-> 2\n"
        "1 <-> 1\n"
        "2 <-> 0, 3, 4\n"
        "3 <-> 2, 4\n"
        "4 <-> 2, 3, 6\n"
        "5 <-> 6\n"
        "6 <-> 4, 5\n";

    if (part == 1) {
        assert(connected0(test) == 6);

        const int part1 = connected0(input);
        assert(part1 == 130);
        return std::to_string(part1);
    }
    else {
        assert(connected_groups(test) == 2);

        const int part2 = connected_groups(input);
        assert(part2 == 189);
        return std::to_string(part2);
    }
}

}



namespace day13 {

/*  Commentary: in essence this solution has not changed from
    my original. It is an order of magnitude faster, however,
    because I no longer pass the vector of ranges to the
    gets_through_all_scanners() function by value - a simple
    oversight in my first attempt.
*/

// e.g. parse("92: 14") -> pair(92, 14)

// return true iff scanner is at the top of its given 'range' at given 'picosec'
bool caught(int range, int picosec)
{
    return range && (picosec % (2*range - 2)) == 0;
}

// return vector of ranges from given 'input'
std::vector<int> parse(const char * input)
{
    std::istringstream iss(input);
    int depth, range;
    char colon;
    // each line is "depth: range", e.g. "92: 14"
    // first find the deepest scanner
    int deepest = 0;
    while (iss >> depth >> colon >> range)
        if (depth > deepest)
            deepest = depth;

    // init vector such that ranges[depth] = range
    std::vector<int> ranges(deepest + 1, 0);
    iss.clear(); iss.seekg(0);
    while (iss >> depth >> colon >> range)
        ranges[depth] = range;

    return ranges;
}

// return total trip severity
int severity(const char * input)
{
    const std::vector<int> ranges(parse(input));

    int trip_severity = 0;
    for (int picosec = 0; picosec < static_cast<int>(ranges.size()); ++picosec) {
        if (caught(ranges[picosec], picosec))
            trip_severity += picosec * ranges[picosec];
    }

    return trip_severity;
}

// return true iff the packet gets through all levels withought being
// caught after delaying its start by 'delay_start' 
bool gets_through_all_scanners(const std::vector<int> & ranges, int delay_start)
{
    for (int in_layer = 0; in_layer < static_cast<int>(ranges.size()); ++in_layer)
        if (caught(ranges[in_layer], delay_start + in_layer))
            return false;
    return true;
}

int part2(const char * input)
{
    const std::vector<int> ranges(parse(input));

    int delay_start = 0;
    while (!gets_through_all_scanners(ranges, delay_start))
        ++delay_start;

    return delay_start;
}


std::string run(int part)
{
    const char * test =
        "0: 3\n"
        "1: 2\n"
        "4: 4\n"
        "6: 4\n";

    if (part == 1) {
        assert(severity(test) == 24);

        const int part1 = severity(input);
        assert(part1 == 3184);
        return std::to_string(part1);
    }
    else {
        assert(part2(test) == 10);

        const int answer2 = part2(input);
        assert(answer2 == 3878062);
        return std::to_string(answer2);
    }
}

}



namespace day14 {

/*  Commentary: original solution unchanged. */

uint8_t hexval(char c)
{
    if ('0' <= c && c <= '9')
        return c - '0';
    else if ('A' <= c && c <= 'F')
        return c - 'A' + 10;
    else if ('a' <= c && c <= 'f')
        return c - 'a' + 10;
    else {
        assert(false);
    }
    return 0;
}

std::vector<uint8_t> from_hex(std::string s)
{
    std::vector<uint8_t> result;
    int i = 0;
    if (s.size() & 1) {
        result.push_back(hexval(s[0]));
        i = 1;
    }
    while (i < static_cast<int>(s.size())) {
        result.push_back((hexval(s[i]) << 4) + hexval(s[i+1]));
        i += 2;
    }
    return result;
}


int popcount8(uint8_t x)
{
    x -= (x >> 1) & 0x55;               // put count of each 2 bits into those 2 bits
    x = (x & 0x33) + ((x >> 2) & 0x33); // put count of each 4 bits into those 4 bits 
    x = (x + (x >> 4)) & 0x0f;          // put count of each 8 bits into those 8 bits 
    return x;
}

int count_1bits(std::vector<uint8_t> vec)
{
    int count = 0;
    for (uint8_t n: vec) {
        count += popcount8(n);
    }
    return count;
}


int used(const char * input)
{
    int count = 0;
    for (int i = 0; i < 128; ++i) {
        std::ostringstream oss;
        oss << input << '-' << i;
        const std::string h(day10::knothash(oss.str().c_str()));
        const std::vector<uint8_t> bits(from_hex(h));
        count += count_1bits(bits);
    }
    return count;
}

std::vector<int> ints_from_bits(const std::vector<uint8_t> bits)
{
    std::vector<int> result;
    for (auto b: bits) {
        for (int i = 0; i < 8; ++i)
            result.push_back((b & (1 << (7 - i))) ? 1 : 0);
    }
    return result;
}

void erase_group(std::vector<std::vector<int>> & map, int r, int c)
{
    const int len = static_cast<int>(map.size());

    std::vector<std::pair<int, int>> queue;
    queue.push_back(std::make_pair(r, c));

    while (!queue.empty()) {
        int r = queue.back().first;
        int c = queue.back().second;
        queue.pop_back();

        if (map[r][c] == 0)
            continue;

        // skip back to the leftmost of this row's cells
        while (c > 0 && map[r][c-1])
            --c;

        // erase this row from the leftmost to the rightmost
        for (; c < len && map[r][c]; ++c) {
            map[r][c] = 0;                      // erase this cell
            if (r > 0 && map[r - 1][c])         // there is an adjacent cell above
                queue.push_back(std::make_pair(r-1, c));
            if (r < len - 1 && map[r + 1][c])   // there is an adjacent cell below
                queue.push_back(std::make_pair(r+1, c));
        }
    }
}

int regions(const char * input)
{
    int count = 0;

    const int len = 128;
    std::vector<std::vector<int>> map(len);
    for (int i = 0; i < len; ++i) {
        std::ostringstream oss;
        oss << input << '-' << i;
        const std::string h(day10::knothash(oss.str().c_str()));
        map[i] = ints_from_bits(from_hex(h));
    }

    for (int r = 0; r < len; ++r) {
        std::vector<int> & row = map[r];
        for (int c = 0; c < len; ++c) {
            if (row[c]) {
                ++count;    // we've found a group
                erase_group(map, r, c);
            }
        }
    }

    return count;
}


std::string run(int part)
{
    if (part == 1) {
        assert(used("flqrgnkx") == 8108);

        const int part1 = used("oundnydw");
        assert(part1 == 8106);
        return std::to_string(part1);
    }
    else {
        assert(regions("flqrgnkx") == 1242);

        const int part2 = regions("oundnydw");
        assert(part2 == 1164);
        return std::to_string(part2);
    }
}

}



namespace day15 {

/*  Commentary: the essence of this solution is the same. The main change
    is to replace my generator class with the standard library classes
    std::minstd_rand0 and std::minstd_rand, which I hitherto did not know
    about (thanks to willkill07 on Reddit). The code is slightly faster,
    but sadly I've been unable to bring the execution time for each part
    down from about 1 second (on a Xeon E5420 @ 2.4GHz, from 2008).

    And then I looked again at Reddit and found a bit twiddling solution,
    which brings the execution time down by half. See PLANB.
*/

#define PLANB

#ifdef PLANB
class nonstd_rand {
    uint64_t val_;
    uint64_t factor_;

public:
    nonstd_rand(uint64_t seed, uint64_t factor)
        : val_(seed), factor_(factor)
    {
    }

    inline uint32_t operator()()
    {
        // equivalent to return val_ = (val_ * factor_) % 2147483647ul;
        // Thanks to askalski on Reddit.
	    uint64_t prod = val_ * factor_;
	    val_ = (prod & 0x7fffffff) + (prod >> 31);
	    return static_cast<uint32_t>(val_ = (val_ + (val_ >> 31)) & 0x7fffffff);
    }
};
#endif

int part1(uint32_t seeda, uint32_t seedb)
{
    int count = 0;

#ifdef PLANB
    nonstd_rand gena(seeda, 16807);
    nonstd_rand genb(seedb, 48271);
#else
    // the generator A spec, n = (n * 16807) % 2147483647, matches std::minstd_rand0 exactly
    // the generator B spec, n = (n * 48271) % 2147483647, matches std::minstd_rand exactly
    std::minstd_rand0 gena(seeda);
    std::minstd_rand genb(seedb);
#endif
    for (int i = 0; i < 40000000; ++i)
        count += (gena() & 0xFFFF) == (genb() & 0xFFFF);

    return count;
}

int part2(uint32_t seeda, uint32_t seedb)
{
    int count = 0;

#ifdef PLANB
    nonstd_rand gena(seeda, 16807);
    nonstd_rand genb(seedb, 48271);
#else
    // the generator A spec, n = (n * 16807) % 2147483647, matches std::minstd_rand0 exactly
    // the generator B spec, n = (n * 48271) % 2147483647, matches std::minstd_rand exactly
    std::minstd_rand0 gena(seeda);
    std::minstd_rand genb(seedb);
#endif
    for (int i = 0; i < 5000000; ++i) {
        uint32_t a, b;
        do a = gena(); while (a & 0x0003);
        do b = genb(); while (b & 0x0007);
        count += (a & 0xFFFF) == (b & 0xFFFF);
    }

    return count;
}


std::string run(int part)
{
    if (part == 1) {
        assert(part1(65, 8921) == 588);

        const int answer1 = part1(618, 814);
        assert(answer1 == 577);
        return std::to_string(answer1);
    }
    else {
        assert(part2(65, 8921) == 309);
        
        const int answer2 = part2(618, 814);
        assert(answer2 == 316);
        return std::to_string(answer2);
    }
}

#undef PLANB

}



namespace day16 {

/*  Commentary: original solution unchanged. */

int readnum(const char *& p)
{
    std::locale loc;
    int result = 0;
    while (*p && std::isdigit(*p, loc))
        result = result * 10 + *p++ - '0';
    return result;
}

std::string dance(const char * s, const char * m)
{
    std::vector<char> v;
    while (*s)
        v.push_back(*s++);

    while (*m) {
        switch (*m++) {
        case 's':
            {
                // Spin, written sX, makes X programs move from the end to the front, but maintain
                // their order otherwise. (For example, s3 on abcde produces cdeab).
                const int x = readnum(m);
                std::rotate(v.begin(), v.begin() + v.size() - x, v.end());
            }
            break;

        case 'x':
            {
                // Exchange, written xA/B, makes the programs at positions A and B swap places.
                const int a = readnum(m);
                assert(*m == '/');
                ++m;
                const int b = readnum(m);
                std::swap(v[a], v[b]);
            }
            break;

        case 'p':
            {
                // Partner, written pA/B, makes the programs named A and B swap places.
                auto ia = std::find(begin(v), end(v), *m++);
                assert(ia != end(v));
                assert(*m == '/');
                ++m;
                auto ib = std::find(begin(v), end(v), *m++);
                assert(ib != end(v));
                std::swap(*ia, *ib);
            }
            break;

        default:
            assert(false);
            break;
        }
        assert(*m == '\0' || *m == ',');
        if (*m == ',')
            ++m;
    }

    assert(!v.empty());
    return std::string(std::begin(v), std::end(v));
}


enum cmd {spin, exchange, partner, end};

std::vector<int> compile(const char * m, int array_size)
{
    std::vector<int> bytecode;

    while (*m) {
        switch (*m++) {
        case 's':
            {
                // Spin, written sX, makes X programs move from the end to the front, but maintain
                // their order otherwise. (For example, s3 on abcde produces cdeab).
                bytecode.push_back(spin);
                bytecode.push_back(array_size - readnum(m));
            }
            break;

        case 'x':
            {
                // Exchange, written xA/B, makes the programs at positions A and B swap places.
                bytecode.push_back(exchange);
                bytecode.push_back(readnum(m));
                assert(*m == '/');
                ++m;
                bytecode.push_back(readnum(m));
            }
            break;

        case 'p':
            {
                // Partner, written pA/B, makes the programs named A and B swap places.
                bytecode.push_back(partner);
                bytecode.push_back(*m++);
                assert(*m == '/');
                ++m;
                bytecode.push_back(*m++);
            }
            break;

        default:
            assert(false);
            break;
        }
        assert(*m == '\0' || *m == ',');
        if (*m == ',')
            ++m;
    }

    bytecode.push_back(end);
    return bytecode;
}


void apply_dance(char * v, char * v_end, const int * bytecode, int itterations)
{
    for (int i = 0; i < itterations; ++i) {
        int pc = 0;
        while (bytecode[pc] != end) {
            switch (bytecode[pc]) {
            case spin:
                {
                    // Spin, written sX, makes X programs move from the end to the front, but maintain
                    // their order otherwise. (For example, s3 on abcde produces cdeab).
                    std::rotate(v, v + bytecode[pc+1], v_end);
                    pc += 2;
                }
                break;

            case exchange:
                {
                    // Exchange, written xA/B, makes the programs at positions A and B swap places.
                    std::swap(v[bytecode[pc+1]], v[bytecode[pc+2]]);
                    pc += 3;
                }
                break;

            case partner:
                {
                    // Partner, written pA/B, makes the programs named A and B swap places.
                    auto ia = std::find(v, v_end, static_cast<char>(bytecode[pc+1]));
                    assert(ia != v_end);
                    auto ib = std::find(v, v_end, static_cast<char>(bytecode[pc+2]));
                    assert(ib != v_end);
                    std::swap(*ia, *ib);
                    pc += 3;
                }
                break;

            default:
                assert(false);
                break;
            }
        }
    }
}

std::string dance2(const char * s, const char * m, int itterations)
{
    std::vector<char> v;
    while (*s)
        v.push_back(*s++);

    const std::vector<int> bytecode(compile(m, v.size()));
    apply_dance(&v[0], &v[0] + v.size(), &bytecode[0], itterations);

    assert(!v.empty());
    return std::string(std::begin(v), std::end(v));
}


std::string dance3(const char * s, const char * m, int itterations)
{
    std::vector<char> v;
    while (*s)
        v.push_back(*s++);
    const std::vector<char> vstart(v);

    const std::vector<int> bytecode(compile(m, v.size()));
    int i = 0;
    for (; i < itterations; ++i) {
        apply_dance(&v[0], &v[0] + v.size(), &bytecode[0], 1);
        if (v == vstart)
            break; // the pattern has returned to the start
    }
    if (i < itterations) {
        const int repeat_period = i + 1;
        v = vstart;
        apply_dance(&v[0], &v[0] + v.size(), &bytecode[0], itterations % repeat_period);
    }

    assert(!v.empty());
    return std::string(std::begin(v), std::end(v));
}

bool dancetest()
{
    for (int i = 0; i < 100; ++i) {
        if (dance2("abcdefghijklmnop", input, i) != dance3("abcdefghijklmnop", input, i))
            return false;
        std::cout << i+1 << "/100\n";
    }
    return true;
}


std::string run(int part)
{
    if (part == 1) {
        assert(dance("abcde", "s1,x3/4,pe/b") == "baedc");

        const std::string answer1 = dance("abcdefghijklmnop", input);
        assert(answer1 == "hmefajngplkidocb");
        return answer1;
    }
    else {
        assert(dance2("abcde", "s1,x3/4,pe/b", 1) == "baedc");
        assert(dance2("abcde", "s1,x3/4,pe/b", 2) == "ceadb");

        assert(dance3("abcde", "s1,x3/4,pe/b", 1) == "baedc");
        assert(dance3("abcde", "s1,x3/4,pe/b", 2) == "ceadb");

        assert(dancetest());
    
        const std::string answer2 = dance3("abcdefghijklmnop", input, 1000000000);
        assert(answer2 == "fbidepghmjklcnoa");
        return answer2;
    }
}

}


namespace day17 {

/*  Commentary: my part 1 was ok but part 2 did 50 million modulo ops.
    This version is an order of magnitude faster. (Thanks to willkill07
    for the inspiration.)
*/

int part1(int skip, int insert_count)
{
    std::vector<int> buf;
    buf.reserve(insert_count + 1);
    int pos = 0;
    int i = 0;
    for (;;) {
        buf.insert(begin(buf) + pos, i);
        if (i++ == insert_count)
            break;
        pos = (pos + skip) % buf.size() + 1;
    }
    pos = (pos + 1) % buf.size();
    return buf[pos];
}

int part2(int skip, int insert_count)
{
    int pos1 = -1; // 0 is always at position 0, pos1 will be for the value at pos 1, discard all else
    int pos = 0;
    /* for skip = 3...
       (0)           the initial state before any insertions.
        0 (1)        the spinlock steps forward three times (0, 0, 0), and then inserts the first value, 1, after it.
        0 (2) 1      the spinlock steps forward three times (0, 1, 0), and then inserts the second value, 2, after it.
        0  2 (3) 1   the spinlock steps forward three times (1, 0, 2), and then inserts the third value, 3, after it.
        0  2 (4) 3  1
        0 (5) 2  4  3  1
        0  5  2  4  3 (6) 1
        0  5 (7) 2  4  3  6  1
        0  5  7  2  4  3 (8) 6  1
        0 (9) 5  7  2  4  3  8  6  1
    */
    for (int i = 0; i <= insert_count; ) {
        if (pos == 1) // ignore all insertions except at position 1
            pos1 = i;
        ++i; // another virtual (or real if pos == 1) insert
        // a modulo operation takes a long time so we want to avoid
        // doing one 50 million times - we don't actually need the
        // modulo until we've skipped past the end of the buffer
        while ((pos += skip + 1) < i)
            ++i; // another virtual insert
        pos = (pos - 1) % i + 1;
    }
    return pos1;
}


std::string run(int part)
{
    if (part == 1) {
        assert(part1(3, 2017) == 638);

        const int answer1 = part1(349, 2017);
        assert(answer1 == 640);
        return std::to_string(answer1);
    }
    else {
        assert(part2(3, 2017) == 1226);
        assert(part2(349, 2017) == 422);

        const int answer2 = part2(349, 50000000);
        assert(answer2 == 47949463);
        return std::to_string(answer2);
    }
}

}



namespace day18 {

/*  Commentary: left my original solution more-or-less untouched. */

enum opcodes {
    op_add, op_addi,
    op_jgz, op_jgzi, op_jgzii,
    op_mod, op_modi,
    op_mul, op_muli,
    op_set, op_seti,
    op_snd,
    op_rcv
};

int get_opcode(std::string op)
{
    if (op == "add") return op_add;
    if (op == "jgz") return op_jgz;
    if (op == "mod") return op_mod;
    if (op == "mul") return op_mul;
    if (op == "set") return op_set;
    if (op == "snd") return op_snd;
    if (op == "rcv") return op_rcv;
    return -1;
}

// every instruction will occupy 3 ints, <op, arg0, arg1>
std::vector<int> compile(const char * input)
{
    std::vector<int> prog;
    std::locale loc;
    std::istringstream iss(input);
    for (std::string line; std::getline(iss, line); ) {
        std::string sop, sarg0, sarg1;
        std::istringstream issline(line);
        issline >> sop >> sarg0 >> sarg1;
        int op = get_opcode(sop), arg0 = 0, arg1 = 0;
        switch (op) {
        case op_add:
        case op_mod:
        case op_mul:
        case op_set:
            assert(std::isalpha(sarg0[0], loc));
            arg0 = sarg0[0] - 'a';
            if (std::isdigit(sarg1[0], loc) || sarg1[0] == '-') {
                ++op; // switch to immediate version of opcode
                arg1 = std::stoi(sarg1);
            }
            else
                arg1 = sarg1[0] - 'a';
            break;

        case op_jgz: // either "jgz a b" (op_jgz), "jgz a 99" (op_jgzi) or "jgz 88 99" (op_jgzii)
            {
                bool immediate_arg0 = false, immediate_arg1 = false;
                if (std::isdigit(sarg0[0], loc) || sarg0[0] == '-') {
                    immediate_arg0 = true;
                    arg0 = std::stoi(sarg0);
                }
                else
                    arg0 = sarg0[0] - 'a';
                if (std::isdigit(sarg1[0], loc) || sarg1[0] == '-') {
                    immediate_arg1 = true;
                    arg1 = std::stoi(sarg1);
                }
                else
                    arg1 = sarg1[0] - 'a';
                if (immediate_arg0) {
                    assert(immediate_arg1);
                    op = op_jgzii;
                }
                else if (immediate_arg1)
                    op = op_jgzi;
                // else op == op_jgz
            }
            break;

        case op_snd:
        case op_rcv:
            assert(std::isalpha(sarg0[0], loc));
            arg0 = sarg0[0] - 'a';
            break;

        default:
            assert(false);
            break;
        }
        prog.push_back(op);
        prog.push_back(arg0);
        prog.push_back(arg1);
    }
    return prog;
}

int64_t execute(std::vector<int> prog)
{
    int64_t last_played_frequency = 0;

    int64_t reg[26] = {0};

    int pc = 0;
    for (;;) {
        int op = prog[pc], x = prog[pc+1], y = prog[pc+2];
        pc += 3;

        switch (op) {
        case op_add:    // add X Y increases register X by the value of Y.
            reg[x] += reg[y];
            break;
        case op_addi:
            reg[x] += y;
            break;
        case op_mod:    // mod X Y sets register X to the result of X modulo Y
            reg[x] %= reg[y];
            break;
        case op_modi:
            reg[x] %= y;
            break;
        case op_mul:    // mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
            reg[x] *= reg[y];
            break;
        case op_muli:
            reg[x] *= y;
            break;
        case op_set:    // set X Y sets register X to the value of Y.
            reg[x] = reg[y];
            break;
        case op_seti:
            reg[x] = y;
            break;
        case op_jgz:    // jgz X Y jumps with an offset of the value of Y, but only if the value of X is greater than zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
            if (reg[x] > 0)
                pc += static_cast<int>(reg[y] * 3 - 3);
            assert(pc >= 0);
            assert(pc <= static_cast<int>(prog.size()) - 3);
            break;
        case op_jgzi:
            if (reg[x] > 0)
                pc += y * 3 - 3;
            assert(pc >= 0);
            assert(pc <= static_cast<int>(prog.size()) - 3);
            break;
        case op_jgzii:
            if (x > 0)
                pc += y * 3 - 3;
            assert(pc >= 0);
            assert(pc <= static_cast<int>(prog.size()) - 3);
            break;
        case op_snd:    // snd X plays a sound with a frequency equal to the value of X.
            last_played_frequency = reg[x];
            break;
        case op_rcv:    // rcv X recovers the frequency of the last sound played, but only when the value of X is not zero. (If it is zero, the command does nothing.)
            if (reg[x] != 0)
                return last_played_frequency;
            break;
        default:
            assert(false);
            break;
        }
    }

    assert(false);
    return 0;
}

int64_t part1(const char * input)
{
    const std::vector<int> prog(compile(input));
    return execute(prog);
}


int64_t execute2(std::vector<int> prog)
{
    int64_t prog_send_count[2] = {0};

    int64_t regbank[2][26] = {0};
    regbank[1][15] = 1; // reg[p] = ID
    int pcbank[2] = {0};
    std::deque<int64_t> queue[2];
    bool wait[2] = {false, false};

    for (int id = 0;; id ^= 1) {
        if (wait[id]) {
            if (wait[id ^ 1])
                break; // deadlock
            continue;
        }

        int64_t (& reg)[26] = regbank[id];
        int & pc = pcbank[id];

        int op = prog[pc], x = prog[pc+1], y = prog[pc+2];
        pc += 3;

        switch (op) {
        case op_add:    // add X Y increases register X by the value of Y.
            reg[x] += reg[y];
            break;
        case op_addi:
            reg[x] += y;
            break;
        case op_mod:    // mod X Y sets register X to the result of X modulo Y
            reg[x] %= reg[y];
            break;
        case op_modi:
            reg[x] %= y;
            break;
        case op_mul:    // mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
            reg[x] *= reg[y];
            break;
        case op_muli:
            reg[x] *= y;
            break;
        case op_set:    // set X Y sets register X to the value of Y.
            reg[x] = reg[y];
            break;
        case op_seti:
            reg[x] = y;
            break;
        case op_jgz:    // jgz X Y jumps with an offset of the value of Y, but only if the value of X is greater than zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
            if (reg[x] > 0)
                pc += static_cast<int>(reg[y] * 3 - 3);
            assert(pc >= 0);
            assert(pc <= static_cast<int>(prog.size()) - 3);
            break;
        case op_jgzi:
            if (reg[x] > 0)
                pc += y * 3 - 3;
            assert(pc >= 0);
            assert(pc <= static_cast<int>(prog.size()) - 3);
            break;
        case op_jgzii:
            if (x > 0)
                pc += y * 3 - 3;
            assert(pc >= 0);
            assert(pc <= static_cast<int>(prog.size()) - 3);
            break;
        case op_snd:    // snd X sends the value of X to the other program
            queue[id ^ 1].push_back(reg[x]);
            wait[id ^ 1] = false;
            prog_send_count[id]++;
            break;
        case op_rcv:    // rcv X receives the next value and stores it in register X
            if (queue[id].empty()) {
                wait[id] = true;
                pc -= 3; // rerun this instruction
            }
            else {
                reg[x] = queue[id].front();
                queue[id].pop_front();
            }
            break;
        default:
            assert(false);
            break;
        }
    }

    return prog_send_count[1];
}

int64_t part2(const char * input)
{
    const std::vector<int> prog(compile(input));
    return execute2(prog);
}



std::string run(int part)
{
    if (part == 1) {
        const char * test =
            "set a 1\n"
            "add a 2\n"
            "mul a a\n"
            "mod a 5\n"
            "snd a\n"
            "set a 0\n"
            "rcv a\n"
            "jgz a -1\n"
            "set a 1\n"
            "jgz a -2\n";

        assert(part1(test) == 4);

        const int64_t answer1 = part1(input);
        assert(answer1 == 3188);
        return std::to_string(answer1);
    }
    else {
        const char * test2 =
            "snd a\n"
            "snd a\n"
            "snd p\n"
            "rcv a\n"
            "rcv b\n"
            "rcv c\n"
            "rcv d\n";

        assert(part2(test2) == 3);

        const int64_t answer2 = part2(input);
        assert(answer2 == 7112);
        return std::to_string(answer2);
    }
}

}



namespace day19 {

/*  Commentary: left more-or-less as my original solution.

    Clearly in most of my solutions there is a lot of duplicate code
    between parts 1 and 2. (The second part of each puzzle is not revealed
    until part 1 has been answered correctly.) I found it expedient,
    i.e. "a means of attaining an end, especially one that is convenient
    but possibly improper or immoral", to cut and paste the part 1
    solution and modify it to whatever part 2 required. Although I
    could now combine the parts, that feels like work and I've chosen
    not to. On the other hand, looking at the execution time and thinking
    "I bet I could make that run a bit faster" feels like a fun challenge.
*/

std::string part1(const char * input)
{
    std::string letters;

    std::vector<std::string> plan;
    std::istringstream iss(input);
    for (std::string s; std::getline(iss, s); )
        plan.push_back(s);

    const int y_end = static_cast<int>(plan.size());
    const int x_end = static_cast<int>(plan[0].size());

    // find entry point
    int y = 0, x = 0;
    while (plan[0][x] != '|')
        ++x;

    enum class direction { down, up, left, right };
    direction dir = direction::down;

    std::locale loc;
    auto is_letter = [&](char c) { return std::isalpha(c, loc); };

    bool running = true;
    while (running) {
        switch (dir) {
        case direction::down:
            ++y;
            if (y == y_end || plan[y][x] == ' ')
                running = false;
            else if (is_letter(plan[y][x]))
                letters.push_back(plan[y][x]);
            else if (plan[y][x] == '+') {
                if (x > 0 && (plan[y][x-1] == '-' || is_letter(plan[y][x-1])))
                    dir = direction::left;
                else
                    dir = direction::right;
            }
            break;

        case direction::up:
            --y;
            if (y < 0 || plan[y][x] == ' ')
                running = false;
            else if (is_letter(plan[y][x]))
                letters.push_back(plan[y][x]);
            else if (plan[y][x] == '+') {
                if (x > 0 && (plan[y][x-1] == '-' || is_letter(plan[y][x-1])))
                    dir = direction::left;
                else
                    dir = direction::right;
            }
            break;

        case direction::left:
            --x;
            if (y < 0 || plan[y][x] == ' ')
                running = false;
            else if (is_letter(plan[y][x]))
                letters.push_back(plan[y][x]);
            else if (plan[y][x] == '+') {
                if (y > 0 && (plan[y-1][x] == '|' || is_letter(plan[y-1][x])))
                    dir = direction::up;
                else
                    dir = direction::down;
            }
            break;

        case direction::right:
            ++x;
            if (x == x_end || plan[y][x] == ' ')
                running = false;
            else if (is_letter(plan[y][x]))
                letters.push_back(plan[y][x]);
            else if (plan[y][x] == '+') {
                if (y > 0 && (plan[y-1][x] == '|' || is_letter(plan[y-1][x])))
                    dir = direction::up;
                else
                    dir = direction::down;
            }
            break;

        default:
            assert(false);
        }
    }

    return letters;
}


int part2(const char * input)
{
    int steps = 0; // (don't include first step, do include last step off plan)

    std::vector<std::string> plan;
    std::istringstream iss(input);
    for (std::string s; std::getline(iss, s); )
        plan.push_back(s);

    const int y_end = static_cast<int>(plan.size());
    const int x_end = static_cast<int>(plan[0].size());

    // find entry point
    int y = 0, x = 0;
    while (plan[0][x] != '|')
        ++x;

    enum class direction { down, up, left, right };
    direction dir = direction::down;

    std::locale loc;
    auto is_letter = [&](char c) { return std::isalpha(c, loc); };

    bool running = true;
    while (running) {
        switch (dir) {
        case direction::down:
            ++y; ++steps;
            if (y == y_end || plan[y][x] == ' ')
                running = false;
            else if (plan[y][x] == '+') {
                if (x > 0 && (plan[y][x-1] == '-' || is_letter(plan[y][x-1])))
                    dir = direction::left;
                else
                    dir = direction::right;
            }
            break;

        case direction::up:
            --y; ++steps;
            if (y < 0 || plan[y][x] == ' ')
                running = false;
            else if (plan[y][x] == '+') {
                if (x > 0 && (plan[y][x-1] == '-' || is_letter(plan[y][x-1])))
                    dir = direction::left;
                else
                    dir = direction::right;
            }
            break;

        case direction::left:
            --x; ++steps;
            if (y < 0 || plan[y][x] == ' ')
                running = false;
            else if (plan[y][x] == '+') {
                if (y > 0 && (plan[y-1][x] == '|' || is_letter(plan[y-1][x])))
                    dir = direction::up;
                else
                    dir = direction::down;
            }
            break;

        case direction::right:
            ++x; ++steps;
            if (x == x_end || plan[y][x] == ' ')
                running = false;
            else if (plan[y][x] == '+') {
                if (y > 0 && (plan[y-1][x] == '|' || is_letter(plan[y-1][x])))
                    dir = direction::up;
                else
                    dir = direction::down;
            }
            break;

        default:
            assert(false);
        }
    }

    return steps;
}

std::string run(int part)
{
    const char * test =
        "     |          \n"
        "     |  +--+    \n"
        "     A  |  C    \n"
        " F---|----E|--+ \n"
        "     |  |  |  D \n"
        "     +B-+  +--+ \n";

    if (part == 1) {
        assert(part1(test) == "ABCDEF");

        const std::string answer1 = part1(input);
        assert(answer1 == "ITSZCJNMUO");
        return answer1;
    }
    else {

        assert(part2(test) == 38);

        const int answer2 = part2(input);
        assert(answer2 == 17420);
        return std::to_string(answer2);
    }
}

}



namespace day20 {

/*  Commentary: I wasn't happy with my original solution. I got two gold stars
    for my answers, but they were flukes because both parts of my solution were
    wrong. For punishment, I've recoded my solution here in two different ways.

    To get an answer for part 1 a quick and dirty algorithm might be
    
        repeat N times {
            update all particles
        }
        find the closest particle to <0,0,0>

    where N is a number you guess at, say 1000 updates. Note that by quick I
    mean quick to code, not necessarily quick to execute.

    To get an answer for part 2 a quick and dirty algorithm might be similar

        repeat N times {
            update all particles
            remove any particles in the same place
        }
        count the particles that remain

    Again, N is a number you guess at. Guess too small and you get the wrong
    answer because not all particles that will eventually collide have yet
    collided. Guess too big and you'll be pointlessly waiting a long time
    for particles to collide that never will.

    One improvement we could make to the algorithm for part 2 is to repeat
    not for a fixed number of times, but only until the particle collisions
    stop. We again have to guess how long to keep updating after the last
    collision before we decide there won't be any more. Here's the method 

        repeat until there have been no collisions for N cycles {
            update all particles
            remove any particles in the same place
        }
        count the particles that remain

    These approaches are good enough to get the right answer in the spirit
    of a fun Advent of Code exercise. Essentially, these were my original
    solutions, except I had a spurious method to determine N: I thought I
    need only wait until all particles were headed away from <0,0,0>. It
    didn't occur to me that, because the acceleration could have a different
    sign to the velocity, a particle headed away from <0,0,0> could later
    change direction and head back.

    To use the quick and dirty solutions #define QANDD.

    I've also implemented a possible "proper" solution that does not require a
    guess at a sufficient value for N. 
    
    One proper solution to part 1 is to recognise that the particle with the
    lowest acceleration will be nearest <0,0,0> in the long term, which makes
    the code very simple:

        find the particle with the minimum acceleration
    
    However, if there is more than one particle with joint-lowest acceleration
    we'll need to find which of these has the lowest velocity, but only after
    updating the particles until none of them are slowing down. At that point
    for all particles their velocity is either stable or increasing and they
    will never change direction. Now we can look for the particle with the
    least velocity.

    And finally, if there is more than one particle with joint-lowest velocity
    we'll need to find which of these is nearest <0,0,0>.
    
    What is a "proper" solution to part 2? One idea might be to use the same
    quick and dirty algorithm, but instead of guessing how many updates we
    need to do before there will be no further collisions, we keep updating
    until none of the particles are slowing down, and therefore about to
    change direction, and then we keep updating until the distance between
    every pair of particles is either static or increasing. At that point we
    know there can be no more collisions.

    To use these proper solutions undefine QANDD.

    For my input data, my proper solution to part 1 is about twice as fast
    as my quick and dirty solution. But then again, my proper solution to
    part 2 takes seven times longer than my quick and dirty solution. The
    reason for that is that we need to check the distance between every pair
    of particles, and for n particles there are n(n-1)/2 unique pairs. My
    input data starts with 1,000 particles. After updating particles until
    none are slowing there are 542 particles still alive, which means 146,611
    pairs. It takes time to check that the distances between all of these
    pairs is not decreasing.

*/



struct particle {
    int id;                         // the ordinal number of the particle in the input
    std::valarray<int> p, v, a;     // position, velocity, acceleration

    particle() : id(0), p(3), v(3), a(3) {} // each p, v and a has an x, y and z component
};

// for the part 2 solution we want an ordering for std::map based on particle position only
bool operator<(const particle & lhs, const particle & rhs)
{
    if (lhs.p[0] != rhs.p[0])
        return lhs.p[0] < rhs.p[0];
    if (lhs.p[1] != rhs.p[1])
        return lhs.p[1] < rhs.p[1];
    return lhs.p[2] < rhs.p[2];
}


// return a vector of particles initialised from given 'input', where
// each input line has the form "p=<x,y,z>, v=<x,y,z>, a=<x,y,z>"
std::vector<particle> parse(const char * input)
{
    // e.g. line = "p=<-833,-499,-1391>, v=<84,17,61>, a=<-4,1,1>"
    std::vector<particle> particles;

    std::locale loc;
    std::istringstream iss(input);
    int id = 0;
    for (std::string line; std::getline(iss, line); ) {
        std::replace_if(std::begin(line), std::end(line),
            [&](char c){ return !(c == '-' || std::isdigit(c, loc)); },
            ' '); // blank everything that isn't a number
        std::istringstream lineiss(line);
        particle p;
        p.id = id++;
        lineiss >> p.p[0] >> p.p[1] >> p.p[2]
                >> p.v[0] >> p.v[1] >> p.v[2]
                >> p.a[0] >> p.a[1] >> p.a[2];
        particles.emplace_back(std::move(p));
    }

    return particles;
}

#define QANDD

#ifdef QANDD // the quick and dirty solution


int part1(const char * input)
{
    // create a vector of particle objects from the input text
    std::vector<particle> particles(parse(input));

    // guess at the number of times to update particles before the nearest is decided
    const int N = 1000;

    // repeat N times
    for (int n = 0; n < N; ++n) {
        // update all particles
        for (auto & p: particles)
            p.p += (p.v += p.a);
    }

    // return true iff p1 nearer <0,0,0> than p2
    auto cmp_p = [] (const particle & p1, const particle & p2) {
        return std::abs(p1.p).sum() < std::abs(p2.p).sum();
    };

    // return the id of the particle nearest to <0,0,0>
    return std::min_element(std::begin(particles), std::end(particles), cmp_p)->id;
}


int part2(const char * input)
{
    // create a vector of particle objects from the input text
    std::vector<particle> particles(parse(input));

    // repeat until there have been no collisions for N cycles
    const int N = 50; // guess at number of stable cycles required
    for (int n = 0; n < N; ) {
        // update all particles
        for (auto & p: particles)
            p.p += (p.v += p.a);

        // remove any particles in the same place
        const size_t nump = particles.size();
        std::map<particle, int> location;
        for (auto & p: particles)
            ++location[p];
        auto collided = [&](const particle & p) { return location[p] != 1; };
        particles.erase(std::remove_if(std::begin(particles), std::end(particles), collided),
                        std::end(particles));

        if (particles.size() == nump)
            ++n;    // another cycle with no collisions
        else
            n = 0;  // saw more collisions - reset counter
    }

    // count the particles that remain
    return particles.size();
}


#else // a possible "proper" solution


int part1(const char * input)
{
    const std::vector<particle> particles(parse(input));


    /* In the long term, the particle with the lowest acceleration will
       be the nearset to <0,0,0>, unless there is more than one particle
       with the same lowest acceleration. */

    // return true iff the acceleration of 'p1' < the acceleration of 'p2'
    auto cmp_a = [] (const particle & p1, const particle & p2) {
        return std::abs(p1.a).sum() < std::abs(p2.a).sum();
    };

    // find all the particles with the lowest acceleration
    std::vector<particle> lowesta;
    const auto mina = std::min_element(std::begin(particles), std::end(particles), cmp_a);
    const auto mina_val = std::abs(mina->a).sum();
    for (const auto & p: particles)
        if (std::abs(p.a).sum() == mina_val)
            lowesta.push_back(p);
    if (lowesta.size() == 1)    // if there is only particle with the lowest acceleration...
        return lowesta[0].id;   // ...it will be nearest <0,0,0> in the long term


    /* The particle nearest <0,0,0> in the long term will be the one of
       those in lowesta with the lowest velocity, unless there is more
       than one particle with the same lowest velocity. */

    // return true iff magnitude of 'm' will not decrease when 'n' is added to it
    auto shrinks = [] (const std::valarray<int> & n, const std::valarray<int> & m) -> bool {
        return std::abs(m + n).sum() < std::abs(m).sum();
    };

    // update all candidates until the magnitude of the velocity is decreasing for none
    for (bool repeat = true; repeat; ) {
        repeat = false;
        for (auto & p: lowesta) {
            p.p += (p.v += p.a);
            if (!repeat && shrinks(p.a, p.v))
                repeat = true;
        }
    }

    // return true iff the velocity of 'p1' < the velocity of 'p2'
    auto cmp_v = [] (const particle & p1, const particle & p2) {
        return std::abs(p1.v).sum() < std::abs(p2.v).sum();
    };

    // find all the particles with the lowest velocity
    std::vector<particle> lowestv;
    const auto minv = std::min_element(std::begin(lowesta), std::end(lowesta), cmp_v);
    const auto minv_val = std::abs(minv->v).sum();
    for (const auto & p: lowesta)
        if (std::abs(p.v).sum() == minv_val)
            lowestv.push_back(p);
    if (lowestv.size() == 1)    // if there is only particle with the lowest velocity...
        return lowestv[0].id;   // ...it will be nearest <0,0,0> in the long term


    /* The particle nearest <0,0,0> in the long term will be the one of
       those in lowestv nearest <0,0,0>. We will assume there is just one
       answer so there cannot be more than one particle the same distance
       from <0,0,0>. */

    // update all candidates until the magnitude of the position is decreasing for none
    for (bool repeat = true; repeat; ) {
        repeat = false;
        for (auto & p: lowestv) {
            p.p += (p.v += p.a);
            if (!repeat && shrinks(p.v, p.p))
                repeat = true;
        }
    }

    // return true iff the possition of 'p1' < the possition of 'p2'
    auto cmp_p = [] (const particle & p1, const particle & p2) {
        return std::abs(p1.p).sum() < std::abs(p2.p).sum();
    };

    // return the id of the one particle nearest <0,0,0>
    return std::min_element(std::begin(lowestv), std::end(lowestv), cmp_p)->id;
}


int part2(const char * input)
{
    // return true iff magnitude of 'm' will not decrease when 'n' is added to it
    auto shrinks = [] (const std::valarray<int> & n, const std::valarray<int> & m) -> bool {
        return std::abs(m + n).sum() < std::abs(m).sum();
    };

    // remove any particles in the same place in given 'ps'
    auto remove_colliders = [] (std::vector<particle> & ps) -> void {
        std::map<particle, int> location;
        for (auto & p: ps)
            ++location[p];
        auto collided = [&](const particle & p) { return location[p] != 1; };
        ps.erase(std::remove_if(std::begin(ps), std::end(ps), collided),
                 std::end(ps));
    };

    // calculate the distance between every particle and every other particle in given 'ps'
    auto distances = [] (const std::vector<particle> & ps, std::vector<size_t> & dist) -> void {
        dist.clear();
        const size_t np = ps.size();
        for (size_t i = 0; i < np; ++i)
            for (size_t j = i + 1; j < np; ++j)
                dist.push_back(std::abs(ps[i].p - ps[j].p).sum());
    };


    // create a vector of particle objects from the input text
    std::vector<particle> particles(parse(input));

    // update all particles until none are slowing down
    for (bool repeat = true; repeat; ) {
        repeat = false;
        for (auto & p: particles) {
            p.p += (p.v += p.a);
            if (!repeat && shrinks(p.a, p.v))
                repeat = true;
        }
        remove_colliders(particles);
    }

    // update all particles until none are getting closer to each other
    const size_t numpairs = particles.size() * (particles.size() - 1) / 2;
    std::vector<size_t> dist1(numpairs), dist2(numpairs);
    do {
        distances(particles, dist1);
        for (auto & p: particles)
            p.p += (p.v += p.a);
        distances(particles, dist2);
        remove_colliders(particles);
    } while (dist1 > dist2);

    // count the particles that remain
    return particles.size();
}

#endif // #else QANDD

#undef QANDD


std::string run(int part)
{
    if (part == 1) {
        struct test {
            int expected_result;
            const char * input;
        };
        test tests[] = {
            {0, "p=<3,0,0>, v=<2,0,0>, a=<-1,0,0>\n"
                "p=<4,0,0>, v=<0,0,0>, a=<-2,0,0>\n"},

            {0, "p=<8,0,0>, v=<1,0,0>, a=<1,0,0>\n"
                "p=<1,0,0>, v=<1,0,0>, a=<2,0,0>\n"},

            {1, "p=<348,-3515,5362>, v=<8,97,-150>, a=<-1,0,0>\n"
                "p=<-1271,294,5831>, v=<37,-25,-172>, a=<0,1,0>\n"},

            {1, "p=<1,0,0>, v=<2,0,0>, a=<1,0,0>\n"
                "p=<8,0,0>, v=<1,0,0>, a=<1,0,0>\n"},

            {0, "p=<1,0,0>, v=<-2,0,0>, a=<1,0,0>\n"
                "p=<8,0,0>, v=<1,0,0>, a=<1,0,0>\n"},

            {1, "p=<2,0,0>, v=<1,0,0>, a=<1,0,0>\n"
                "p=<1,0,0>, v=<1,0,0>, a=<1,0,0>\n"},

        };
        for (const auto & t: tests)
            assert(part1(t.input) == t.expected_result);


        const int answer1 = part1(input);
        assert(answer1 == 457);
        return std::to_string(answer1);
    }
    else {
        const char * test2 =
            "p=<-6,0,0>, v=<3,0,0>, a=<0,0,0>\n"    
            "p=<-4,0,0>, v=<2,0,0>, a=<0,0,0>\n"
            "p=<-2,0,0>, v=<1,0,0>, a=<0,0,0>\n"
            "p=<3,0,0>, v=<-1,0,0>, a=<0,0,0>\n";

        assert(part2(test2) == 1);

        const int answer2 = part2(input);
        assert(answer2 == 448);
        return std::to_string(answer2);
    }
}

}


namespace day21 {

/*  Comentary: my original solution had this at its core:

        for (int i = 0; i < itterations; ++i) {
            std::vector<pattern> parts(decompose(pat));
            for (int i = 0; i < static_cast<int>(parts.size()); ++i)
                parts[i] = rules.at(parts[i]);
            pat = compose(parts);
        }

    The solution below keeps the same logical form, but transforms
    one sub-pattern at a time. This saves many memory allocations,
    frees and mem copies and is an order of magnitude faster.
*/

// return our representation of given pattern 's'
// e.g. read_pattern(".#./..#/###") -> vector{. # . . . # # # #}
std::vector<char> read_pattern(const char * s)
{
    std::vector<char> p;
    while (*s) {
        if (*s != '/')
            p.push_back(*s);
        ++s;
    }
    return p;
}

// rotate 90 degrees right; works for 2x2 and 3x3 patterns only
std::vector<char> rotate_r(const std::vector<char> & p)
{
    switch (p.size()) {
    case 4: return {p[2], p[0], p[3], p[1]};
    case 9: return {p[6], p[3], p[0], p[7], p[4], p[1], p[8], p[5], p[2]};
    }
    assert(false);
    return {};
}

// flip top to bottom; works for 2x2 and 3x3 patterns only
std::vector<char> flip_tb(const std::vector<char> & p)
{
    switch (p.size()) {
    case 4: return {p[2], p[3], p[0], p[1]};
    case 9: return {p[6], p[7], p[8], p[3], p[4], p[5], p[0], p[1], p[2]};
    }
    assert(false);
    return {};
}

// flip left to right; works for 2x2 and 3x3 patterns only
std::vector<char> flip_lr(const std::vector<char> & p)
{
    switch (p.size()) {
    case 4: return {p[1], p[0], p[3], p[2]};
    case 9: return {p[2], p[1], p[0], p[5], p[4], p[3], p[8], p[7], p[6]};
    }
    assert(false);
    return {};
}


struct pattern_hash {
    // return a hash of given 'pat', which must be either 2x2 or 3x3
    std::size_t operator()(const std::vector<char> & pat) const
    {
        std::size_t h = 0;
        for (char p: pat)
            h = (h << 1) | (p == '#');
        if (pat.size() == 9)
            h |= (1 << 9); // so that for all patterns, hash(2x2) always differs from hash(3x3)
        return h;
    }
};

typedef std::unordered_map<std::vector<char>, std::vector<char>, pattern_hash> rules_type;

// insert all permutations of given target->replacement rule into given rules
void insert_rule_permutations(rules_type & rules, std::string target, std::string replacement)
{
    //  given target
    //      AB
    //      CD

    // --- rotate ---
    // AB  CA  DC  BD
    // CD  DB  BA  AC
    const std::vector<char> r(read_pattern(replacement.c_str()));
    std::vector<char> t(read_pattern(target.c_str()));
    for (int i = 0; i < 4; ++i) {
        t = rotate_r(t);
        rules[t] = r;
    }

    //  --- flip ---
    //     BA  CD
    //     DC  AB
    rules[flip_tb(t)] = r;
    rules[flip_lr(t)] = r;

    // -flip+rotate-
    //     AC  DB
    //     BD  CA
    t = rotate_r(t);
    rules[flip_tb(t)] = r;
    rules[flip_lr(t)] = r;
}

// return rules map from given input text containing one rule per line
rules_type read_rules(const char * s)
{
    rules_type rules;

    // each line is "p1 => p2", e.g. "..#/.../#.. => ##.#/..../...#/..##"
    std::string p1, arrow, p2;
    std::stringstream ss(s);
    while (ss >> p1 >> arrow >> p2) {
        assert(arrow == "=>");
        insert_rule_permutations(rules, p1, p2);
    }

    return rules;
}


int apply_rules(const char * start_pattern_str, const char * rules_str, int itterations)
{
    const rules_type enhancement_rules(read_rules(rules_str));

    std::vector<char> p[2]; // p1 & p2 patterns will alternate each itteration
    p[0] = read_pattern(start_pattern_str);
    std::vector<char> p1sub;

    for (int i = 0; i < itterations; ++i) {
        std::vector<char> & p1 = p[i % 2];      // p1 is always the current (source) pattern
        std::vector<char> & p2 = p[(i+1) % 2];  // p2 is always the next (destination) pattern

        const int p1_size(static_cast<int>(std::sqrt(p1.size())));
        const int p1_sub_size(p1_size % 2 == 0 ? 2 : 3);
        const int p2_sub_size(p1_sub_size == 2 ? 3 : 4);
        const int p2_size(p1_size / p1_sub_size * p2_sub_size);
        const int num_sub_patterns(p1_size / p1_sub_size);

        p1sub.resize(p1_sub_size * p1_sub_size);
        p2.resize(p2_size * p2_size);

        // for each row of sub-patterns...
        for (int row = 0; row < num_sub_patterns; ++row) {
            // for each sub-pattern in the current row...
            for (int col = 0; col < num_sub_patterns; ++col) {

                // 1. copy the next sub-pattern from p1 to p1sub
                const char * p1_src = &p1[(row * p1_size + col) * p1_sub_size];
                char * p1sub_dst = &p1sub[0];
                // for each row in the current sub-pattern of p1
                for (int r = 0; r < p1_sub_size; ++r) {
                    std::copy(p1_src, p1_src + p1_sub_size, p1sub_dst);
                    p1_src += p1_size;
                    p1sub_dst += p1_sub_size;
                }

                // 2. lookup the enhancement rule for p1sub (apparently, there will always be such a rule)
                const std::vector<char> & p2sub(enhancement_rules.at(p1sub));

                // 3. copy the new pattern to the right place in p2
                const char * p2sub_src = &p2sub[0];
                char * p2_dst = &p2[(row * p2_size + col) * p2_sub_size];
                // for each row in the current sub-pattern of p2
                for (int r = 0; r < p2_sub_size; ++r) {
                    std::copy(p2sub_src, p2sub_src + p2_sub_size, p2_dst);
                    p2sub_src += p2_sub_size;
                    p2_dst += p2_size;
                }
            }
        }
    }

    const std::vector<char> & final = p[itterations % 2];
    return std::count(std::begin(final), std::end(final), '#');
}



std::string run(int part)
{
    const char * start_pattern =
        ".#./"
        "..#/"
        "###";

    const char * test_rules =
        "../.# => ##./#../...\n"
        ".#./..#/### => #..#/..../..../#..#\n";

    if (part == 1) {
        assert(apply_rules(start_pattern, test_rules, 2) == 12);

        const int answer1 = apply_rules(start_pattern, input, 5);
        assert(answer1 == 188);
        return std::to_string(answer1);
    }
    else {
        const int answer2 = apply_rules(start_pattern, input, 18);
        assert(answer2 == 2758764);
        return std::to_string(answer2);
    }
}

}





namespace day22 {

/*  Commentary: this code is an order of magnitued faster than
    my original solution. Only a few tweaks have been made to
    the original to achieve this:

    1. Use an unordered_map with a suitable hash function
       instead of a std::map. I found the performance very
       sensitive to the hash function. For example, use
          ((nodexy.first & 0xFFF) << 12) | (nodexy.second & 0xFFF)
       instead of
          ((nodexy.first & 0xFF) << 8) | (nodexy.second & 0xFF)
       and the code takes twice as long to execute.

    2. Find the node in the map once, rather than twice, on each
       burst of activity (itteration).

    3. Mark a node as clean instead of removing it from the map.

    4. Finally, try Plan B: use a 512x512 array instead of
       the unordered_map ("sparse") array.

    The std::unordered_map version executes in 10% of the time
    compared to the std::map version and the 512x512 array
    version executes in 5% of the time compared to the std::map
    version. Of course, the choice of the Plan B array size is
    based on having already obtained an answer with a std::map
    and having seen the furthest infected nodes. My original
    aim was to get a correct answer by writing the code as
    quickly as I could. In this tidy-up I'm more interested in
    improving the execution time than I was first time around.
*/


struct node_hash {
    // return a hash of given 'nodexy'
    std::size_t operator()(const std::pair<int, int> & nodexy) const
    {
        return ((nodexy.first & 0xFF) << 8) | (nodexy.second & 0xFF);
    }
};

class sparsemap {
    std::unordered_set<std::pair<int, int>, node_hash> map_;
public:
    void infect(int x, int y)
    {
        map_.insert(std::make_pair(x, y));
    }
    void clean(int x, int y)
    {
        map_.erase(std::make_pair(x, y));
    }
    bool infectedp(int x, int y) const
    {
        return map_.find(std::make_pair(x, y)) != std::end(map_);
    }
};

// return a sparse map initialised to the given map text 's'
sparsemap create_map(const char * s, int & centre_x, int & centre_y)
{
    /* e.g. given string is
            ..#
            #..
            ...
        insert into nodemap so that top left corner is at (0,0)
    */
    sparsemap m;
    int y = 0, width = 0;
    std::stringstream ss(s);
    std::string line;
    while (std::getline(ss, line)) {
        width = static_cast<int>(line.size());
        for (int x = 0; x < width; ++x)
            if (line[x] == '#')
                m.infect(x, y);
        --y;
    }

     centre_x = width/2;
     centre_y = y/2;

    return m;
}

int part1(const char * input, int burst_count)
{
    int infections = 0;

    enum direction { north, east, south, west, dirlen };
    int dir = north;
    int x, y;
    sparsemap m(create_map(input, x, y));
    for (int i = 0; i < burst_count; ++i) {
        bool infected = m.infectedp(x, y);

        // "If the current node is infected, it turns to its right.
        // Otherwise, it turns to its left. (Turning is done in-place;
        // the current node does not change.)"
        if (infected)
            dir = (dir + 1) % dirlen;           // turn right
        else
            dir = (dir + dirlen - 1) % dirlen;  // turn left

        // If the current node is clean, it becomes infected.
        // Otherwise, it becomes cleaned. (This is done after the node
        // is considered for the purposes of changing direction.)
        if (infected)
            m.clean(x, y);
        else {
            m.infect(x, y);
            ++infections;
        }

        // The virus carrier moves forward one node in the direction
        // it is facing.
        switch (dir) {
        case north:     ++y;    break;
        case east:      ++x;    break;
        case south:     --y;    break;
        case west:      --x;    break;
        }
    }

    return infections;
}

#define PLANB

#ifdef PLANB
class nodemap {
    int width_, height_;
    std::vector<int8_t> map_;

public:
    nodemap(int width, int height, int8_t default_value)
        : width_(width), height_(height), map_(width * height, default_value)
    {
    }

    int8_t & lookup(int x, int y)
    {
        x += width_/2;
        y += height_/2;
        if (x < 0 || x >= width_ || y < 0 || y >= height_) {
            std::cout << "out of bounds (" << x << ", " << y << ")\n";
            throw "out of bounds";
        }
        return map_[y * width_ + x];
    }
};
#else
class nodemap {
    std::unordered_map<std::pair<int, int>, int8_t, node_hash> map_;

public:
    nodemap(int, int, int8_t)
    {
    }

    int8_t & lookup(int x, int y)
    {
        return map_[std::make_pair(x, y)];
    }
};
#endif

#undef PLANB


enum node_state { cleaned, weakened, infected, flagged };

// return a sparse map initialised to the given map text 's'
nodemap create_map2(const char * s, int & centre_x, int & centre_y)
{
    /* e.g. given string is
            ..#
            #..
            ...
        insert into nodemap so that top left corner is at (0,0)
    */
    nodemap m(512, 512, node_state::cleaned);
    int y = 0, width = 0;
    std::stringstream ss(s);
    std::string line;
    while (std::getline(ss, line)) {
        width = static_cast<int>(line.size());
        for (int x = 0; x < width; ++x)
            if (line[x] == '#')
                m.lookup(x, y) = node_state::infected;
        --y;
    }

     centre_x = width/2;
     centre_y = y/2;

    return m;
}

int part2(const char * input, int burst_count)
{
    int infections = 0;

    enum direction { north, east, south, west, num_dirs }; // code requires clockwise order
    int dir = north;
    int x, y;
    nodemap m(create_map2(input, x, y));

    for (int i = 0; i < burst_count; ++i) {
        auto & node = m.lookup(x, y);
        switch (node) {
        case node_state::cleaned:
            node = node_state::weakened;            // Clean nodes become weakened.
            dir = (dir + num_dirs - 1) % num_dirs;  // turn left
            break;
        case node_state::weakened:
            node = node_state::infected;            // Weakened nodes become infected.
            ++infections;
            break;
        case node_state::infected:
            node = node_state::flagged;             // Infected nodes become flagged.
            dir = (dir + 1) % num_dirs;             // turn right
            break;
        case node_state::flagged:
            node = node_state::cleaned;             // Flagged nodes become clean.
            dir = (dir + num_dirs/2) % num_dirs;    // reverse
            break;
        }
        
        // The virus carrier moves forward one node in the direction
        // it is facing.
        switch (dir) {
        case north:     ++y;    break;
        case east:      ++x;    break;
        case south:     --y;    break;
        case west:      --x;    break;
        }
    }

    return infections;
}


std::string run(int part)
{
    const char * test = 
        "..#\n"
        "#..\n"
        "...\n";

    const char * input =
        "....##.#.#.#...#.##.##.#.\n"
        "##.####..###..#.#.#.###.#\n"
        ".#.#...#.##....#......###\n"
        "...#.....##.###....##.###\n"
        "#.########.#.#####..##.#.\n"
        ".#..#..#.#..#....##.#...#\n"
        ".....#.##..#.#.....##..##\n"
        "....###....###....###.#..\n"
        "..#..#..#..#.##.#.#..##.#\n"
        ".##......#...##.#.#.##.#.\n"
        ".#####.#.#.##...###...#..\n"
        "#..###..#....#....##..#..\n"
        "###..#....#.##.##.....#..\n"
        "##.##..#.##.#..#####.#.#.\n"
        "#....#.######.#.#.#.##.#.\n"
        "###.##.#.######.#..###.#.\n"
        "#...###.#.#..##..####....\n"
        "###...##.###..###..##..#.\n"
        "..##.###...#.....##.##.##\n"
        "..##..#.###.###.....#.###\n"
        "#..###.##.#.###......####\n"
        "#.#...#..##.###.....##.#.\n"
        "#..#.##...##.##....#...#.\n"
        "..#.#..#..#...##.#..###..\n"
        "......###....#.....#....#\n";
    if (part == 1) {
        assert(part1(test, 70) == 41);
        assert(part1(test, 10000) == 5587);

        const int answer1 = part1(input, 10000);
        assert(answer1 == 5570);
        return std::to_string(answer1);
    }
    else {
        assert(part2(test, 100) == 26);
        assert(part2(test, 10000000) == 2511944);

        const int answer2 = part2(input, 10000000);
        assert(answer2 == 2512022);
        return std::to_string(answer2);
    }
}

}




namespace day23 {

/*  Commentary: left untouched, appart from replacing my eachline()
    and eachword() functions with plain std::stringstream reads.
*/

enum opcodes {
    op_jnz, op_jnzi, op_jnzii,
    op_set, op_seti,
    op_sub, op_subi,
    op_mul, op_muli
};

int get_opcode(std::string op)
{
    if (op == "jnz") return op_jnz;
    if (op == "mul") return op_mul;
    if (op == "set") return op_set;
    if (op == "sub") return op_sub;
    return -1;
}

// every instruction will occupy 3 ints
std::vector<int> compile(const char * input)
{
    std::vector<int> prog;
    std::locale loc;
    std::istringstream iss(input);
    for (std::string line; std::getline(iss, line); ) {
        std::string sop, sarg0, sarg1;
        std::istringstream issline(line);
        issline >> sop >> sarg0 >> sarg1;
        int op = get_opcode(sop), arg0 = 0, arg1 = 0;

        switch (op) {
        case op_mul:
        case op_set:
        case op_sub:
            assert(std::isalpha(sarg0[0], loc));
            arg0 = sarg0[0] - 'a';
            if (std::isdigit(sarg1[0], loc) || sarg1[0] == '-') {
                ++op; // switch to immediate version of opcode
                arg1 = std::stoi(sarg1);
            }
            else
                arg1 = sarg1[0] - 'a';
            break;

        case op_jnz: // either "jgz a b" (op_jgz), "jgz a 99" (op_jgzi) or "jgz 88 99" (op_jgzii)
            {
                bool immediate_arg0 = false, immediate_arg1 = false;
                if (std::isdigit(sarg0[0], loc) || sarg0[0] == '-') {
                    immediate_arg0 = true;
                    arg0 = std::stoi(sarg0);
                }
                else
                    arg0 = sarg0[0] - 'a';
                if (std::isdigit(sarg1[0], loc) || sarg1[0] == '-') {
                    immediate_arg1 = true;
                    arg1 = std::stoi(sarg1);
                }
                else
                    arg1 = sarg1[0] - 'a';
                if (immediate_arg0) {
                    assert(immediate_arg1);
                    op = op_jnzii;
                }
                else if (immediate_arg1)
                    op = op_jnzi;
                // else op == op_jgz
            }
            break;

        default:
            assert(false);
            break;
        }
        prog.push_back(op);
        prog.push_back(arg0);
        prog.push_back(arg1);
    }
    return prog;
}

int64_t execute(std::vector<int> prog)
{
    int64_t mul_count = 0;

    int64_t reg[26] = {0};

    int pc = 0;
    for (;;) {
        int op = prog[pc], x = prog[pc+1], y = prog[pc+2];
        pc += 3;

        switch (op) {
        case op_sub:    // add X Y decreases register X by the value of Y.
            reg[x] -= reg[y];
            break;
        case op_subi:
            reg[x] -= y;
            break;
        case op_mul:    // mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
            reg[x] *= reg[y];
            ++mul_count;
            break;
        case op_muli:
            reg[x] *= y;
            ++mul_count;
            break;
        case op_set:    // set X Y sets register X to the value of Y.
            reg[x] = reg[y];
            break;
        case op_seti:
            reg[x] = y;
            break;
        case op_jnz:    // jnz X Y jumps with an offset of the value of Y, but only if the value of X is not zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
            if (reg[x] != 0)
                pc += static_cast<int>(reg[y] * 3 - 3);
            if (pc < 0 || pc >= static_cast<int>(prog.size()) - 3)
                return mul_count; // jump out means halt
            break;
        case op_jnzi:
            if (reg[x] != 0)
                pc += y * 3 - 3;
            if (pc < 0 || pc >= static_cast<int>(prog.size()) - 3)
                return mul_count; // jump out means halt
            break;
        case op_jnzii:
            if (x != 0)
                pc += y * 3 - 3;
            if (pc < 0 || pc >= static_cast<int>(prog.size()) - 3)
                return mul_count; // jump out means halt
            break;
        default:
            assert(false);
            break;
        }
    }

    assert(false);
    return mul_count;
}

int64_t part1(const char * input)
{
    const std::vector<int> prog(compile(input));
    return execute(prog);
}


int64_t part2()
{
#if 0
    /*
        set b 65
        set c b
        jnz a 2
        jnz 1 5
        mul b 100
        sub b -100000
        set c b
        sub c -17000
        set f 1
        set d 2
        set e 2
        set g d
        mul g e
        sub g b
        jnz g 2
        set f 0
        sub e -1
        set g e
        sub g b
        jnz g -8
        sub d -1
        set g d
        sub g b
        jnz g -13
        jnz f 2
        sub h -1
        set g b
        sub g c
        jnz g 2
        jnz 1 3
        sub b -17
        jnz 1 -23
    */

    // the above is approximately like this:

    int64_t a = 1, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;

    b = 65;
    c = b;
    if (a != 0) {
        b = b * 100 + 100000;
        c = b + 17000;
    }

    for (;;) {
        f = 1;
        d = 2;
        do {
            e = 2;
            do {
                g = d * e - b;
                if (g == 0)
                    f = 0;
                ++e;
                g = e - b;
            } while (g != 0);
            ++d;
            g = d - b;
        } while (g != 0);
        if (f == 0)
            ++h;
        g = b - c;
        if (g == 0)
            break;
        b += 17;
    }

    // the above is approximately like this:

    for (b = 106500, c = 123500; b <= c; b += 17) {
        f = 1;
        for (d = 2; d <= b; ++d) {
            for (e = 2; e <= b; ++e) {
                if (b == d * e)
                    f = 0; // b is not prime
            }
        }
        if (f == 0)
            ++h;
    }

#else

    // in other words, test every 17th number between 106500 and 123500 to
    // see if its prime, set h to the count of those that are not prime,
    // which, assuming we are allowed division, could be written like this:

    auto is_prime = [](int n){
        if (n % 2 == 0)
            return false; // n is even
        const int end = static_cast<int>(std::sqrt(n));
        for (int i = 3; i <= end; i += 2)
            if (n % i == 0)
                return false;
        return true;
    };

    int h = 0;
    for (int b = 106500, c = 123500; b <= c; b += 17) {
        if (!is_prime(b))
            ++h;
    }
#endif

    return h;
}



std::string run(int part)
{
    if (part == 1) {
        const char * input =
            "set b 65\n"
            "set c b\n"
            "jnz a 2\n"
            "jnz 1 5\n"
            "mul b 100\n"
            "sub b -100000\n"
            "set c b\n"
            "sub c -17000\n"
            "set f 1\n"
            "set d 2\n"
            "set e 2\n"
            "set g d\n"
            "mul g e\n"
            "sub g b\n"
            "jnz g 2\n"
            "set f 0\n"
            "sub e -1\n"
            "set g e\n"
            "sub g b\n"
            "jnz g -8\n"
            "sub d -1\n"
            "set g d\n"
            "sub g b\n"
            "jnz g -13\n"
            "jnz f 2\n"
            "sub h -1\n"
            "set g b\n"
            "sub g c\n"
            "jnz g 2\n"
            "jnz 1 3\n"
            "sub b -17\n"
            "jnz 1 -23\n";

        const int64_t answer1 = part1(input);
        assert(answer1 == 3969);
        return std::to_string(answer1);
    }
    else {
        const int64_t answer2 = part2();
        assert(answer2 == 917);
        return std::to_string(answer2);
    }
}

}




namespace day24 {

/*  Commentary: in my original solution I actually removed (erase)
    each component from the bag of available components before
    going off to search the branches at the next level, and then
    put the component back in the bag (insert). In this solution
    I just mark the component as used - no mem moves to close
    the gap left by an erased component required. This solution
    is an order of magnitude faster than the original.
*/

class component {
    int p1, p2; // a component has a port at each end
    bool usedp; // usedp => this component is already in use in the bridge

public:
    component() = default;

    explicit component(int p1, int p2)
        : p1(p1), p2(p2), usedp(false)
    {}

    // if this component is unused and has a port of the given type,
    // return the port type at the other end, otherwise return -1
    int other_port(int port) const
    {
        if (usedp)
            return -1;
        if (p1 == port)
            return p2;
        if (p2 == port)
            return p1;
        return -1;
    }

    void set_used()   { usedp = true; }
    void set_unused() { usedp = false; }
};

// return a bag of components listed in given 'input'
std::vector<component> read_components(const char * input)
{
    std::vector<component> components;

    // each line is in the form port1/port2, e.g. "23/45"
    std::stringstream ss(input);
    int p1, p2;
    char slash;
    while (ss >> p1 >> slash >> p2) {
        assert(slash == '/');
        components.push_back(component(p1, p2));
    }

    return components;
}


// return strongest bridge found starting with given 'port' and
// using available 'components' 
int max_strength(std::vector<component> & components, int port)
{
    int max = 0;
    for (auto & c: components) {
        int other_port(c.other_port(port));
        if (other_port >= 0) {
            c.set_used();
            max = std::max(max_strength(components, other_port) + port + other_port, max);
            c.set_unused();
        }
    }
    return max;
}

int part1(const char * input)
{
    std::vector<component> components(read_components(input));
    return max_strength(components, 0);
}

// return maximum bridge (length, strength)
std::pair<int, int> max_strength3(std::vector<component> & components, int port, int length)
{
    int max_len = 0, max_strenth = 0;
    for (auto & c: components) {
        int other_port(c.other_port(port));
        if (other_port >= 0) {
            c.set_used();
            std::pair<int, int> s = max_strength3(components, other_port, length + 1);
            if (length + s.first > max_len) {
                max_len = length + s.first;
                max_strenth = port + other_port + s.second;
            }
            else if (length + s.first == max_len && port + other_port + s.second > max_strenth)
                max_strenth = port + other_port + s.second;
            c.set_unused();
        }
    }
    return std::make_pair(max_len, max_strenth);
}

int part2(const char * input)
{
    std::vector<component> components(read_components(input));
    return max_strength3(components, 0, 0).second;
}

std::string run(int part)
{
    const char * test =
        "0/2\n"
        "2/2\n"
        "2/3\n"
        "3/4\n"
        "3/5\n"
        "0/1\n"
        "10/1\n"
        "9/10\n";

    assert(part1(test) == 31);

    if (part == 1) {
        const int answer1 = part1(input);
        assert(answer1 == 1940);
        return std::to_string(answer1);
    }
    else {
        const int answer2 = part2(input);
        assert(answer2 == 1928);
        return std::to_string(answer2);
    }
}

}




namespace day25 {

/*  Commentary: the input text parsing is verbose, but the Turing machine
    performance is not too bad, so I've left the code alone.
*/

class tape {
    int cursor;
    std::vector<uint8_t> right; // containing cells 0, 1, 2, ...
    std::vector<uint8_t> left;  // containing cells -1, -2, -3, ...

public:
    tape()
    : cursor(0), right(1, 0)
    {
    }

    // return the Boolean value at the current cursor position on the tape
    bool read() const
    {
        return (cursor >= 0 ? right.at(cursor) : left.at(-cursor-1)) != 0;
    }

    // write given 'b' to tape at current cursor position
    void write(bool b)
    {
        (cursor >= 0 ? right[cursor] : left[-cursor-1]) = b;
    }

    // move cursor one cell to the left iff given 'b' is true, else move it one cell to the right
    void move_left(bool b)
    {
        if (b) {
            --cursor;
            if (cursor < 0 && -cursor >= static_cast<int>(left.size()))
                left.push_back(0);
        }
        else {
            ++cursor;
            if (cursor >= 0 && cursor >= static_cast<int>(right.size()))
                right.push_back(0);
        }
    }

    // return the total number of cells on the tape containing the value 1 (true)
    int count_ones() const
    {
        return
            std::count(std::begin(left), std::end(left), 1)
            + std::count(std::begin(right), std::end(right), 1);
    }
};

struct state {
    enum control { ctrl_write_1 = 0x01, ctrl_move_left = 0x02 };
    uint8_t control[2];
    uint8_t nextstate[2];

    void read(bool on_1, bool & write_1, bool & move_left, uint8_t & next_state) const
    {
        write_1 = (control[on_1] & ctrl_write_1) != 0;
        move_left = (control[on_1] & ctrl_move_left) != 0;
        next_state = nextstate[on_1];
    }

    void write(bool on_1, uint8_t control_flag, bool set)
    {
        if (set)
            control[on_1] |= control_flag;
        else
            control[on_1] &= ~control_flag;
    }

    void write_nextstate(bool on_1, uint8_t val)
    {
        nextstate[on_1] = val;
    }
};

struct blueprint {
    uint8_t begin_state; // 0 = State A, 1 = State B, ...
    int checksum_after_steps;
    std::vector<state> states;
};

void run_turing(const blueprint & b, tape & t)
{
    bool write_1, move_left; uint8_t next_state;

    int s = b.begin_state;

    for (int step = 0; step < b.checksum_after_steps; ++step) {
        b.states.at(s).read(t.read(), write_1, move_left, next_state);
        t.write(write_1);
        t.move_left(move_left);
        s = next_state;
    }
}

blueprint read(const char * input)
{
    /* e.g. input =
        Begin in state A.
        Perform a diagnostic checksum after 6 steps.

        In state A:
          If the current value is 0:
            - Write the value 1.
            - Move one slot to the right.
            - Continue with state B.
          If the current value is 1:
            - Write the value 0.
            - Move one slot to the left.
            - Continue with state B.
    */
    blueprint b;
    int lineno = 0;
    int state_lineno = 0;
    int state_index = -1;
    std::istringstream iss(input);
    for (std::string line; std::getline(iss, line); ) {
        ++lineno;
        if (lineno == 1) {
            // "Begin in state A."
            std::smatch sm;
            if (!std::regex_match(line, sm, std::regex("Begin in state (.)\\.")))
                throw "bad string!";
            assert(sm.size() == 2);
            b.begin_state = std::string(sm[1])[0] - 'A';
        }
        else if (lineno == 2) {
            // "Perform a diagnostic checksum after 6 steps."
            std::smatch sm;
            if (!std::regex_match(line, sm, std::regex("Perform a diagnostic checksum after (\\d+) steps\\.")))
                throw "bad string!";
            assert(sm.size() == 2);
            b.checksum_after_steps = std::stoi(sm[1]);
        }
        else if (!line.empty()) {
            ++state_lineno;
            if (state_lineno == 1) {
                // "In state A:"
                ++state_index;
                b.states.push_back(state());
            }
            else if (state_lineno == 2) {
                // "If the current value is 0:"
            }
            else if (state_lineno == 3) {
                // " - Write the value 1."
                std::smatch sm;
                if (!std::regex_match(line, sm, std::regex("    - Write the value (.)\\.")))
                    throw "bad string!";
                assert(sm.size() == 2);
                b.states[state_index].write(false, state::ctrl_write_1, std::string(sm[1]) == "1");
            }
            else if (state_lineno == 4) {
                // "- Move one slot to the right."
                std::smatch sm;
                if (!std::regex_match(line, sm, std::regex("    - Move one slot to the (right|left)\\.")))
                    throw "bad string!";
                assert(sm.size() == 2);
                b.states[state_index].write(false, state::ctrl_move_left, std::string(sm[1]) == "left");
            }
            else if (state_lineno == 5) {
                // "- Continue with state B."
                std::smatch sm;
                if (!std::regex_match(line, sm, std::regex("    - Continue with state (.)\\.")))
                    throw "bad string!";
                assert(sm.size() == 2);
                b.states[state_index].write_nextstate(false, std::string(sm[1])[0] - 'A');
            }
            else if (state_lineno == 6) {
                // "If the current value is 1:"
            }
            else if (state_lineno == 7) {
                // " - Write the value 1."
                std::smatch sm;
                if (!std::regex_match(line, sm, std::regex("    - Write the value (.)\\.")))
                    throw "bad string!";
                assert(sm.size() == 2);
                b.states[state_index].write(true, state::ctrl_write_1, std::string(sm[1]) == "1");
            }
            else if (state_lineno == 8) {
                // "- Move one slot to the right."
                std::smatch sm;
                if (!std::regex_match(line, sm, std::regex("    - Move one slot to the (right|left)\\.")))
                    throw "bad string!";
                assert(sm.size() == 2);
                b.states[state_index].write(true, state::ctrl_move_left, std::string(sm[1]) == "left");
            }
            else if (state_lineno == 9) {
                // "- Continue with state B."
                std::smatch sm;
                if (!std::regex_match(line, sm, std::regex("    - Continue with state (.)\\.")))
                    throw "bad string!";
                assert(sm.size() == 2);
                b.states[state_index].write_nextstate(true, std::string(sm[1])[0] - 'A');
                state_lineno = 0;
            }
        }
    }
    return b;
}

int part1(const char * input)
{
    blueprint b(read(input));
    tape t;

    run_turing(b, t);

    return t.count_ones();
}


std::string run(int part)
{
    if (part == 1) {
        const char * test =
            "Begin in state A.\n"
            "Perform a diagnostic checksum after 6 steps.\n"
            "\n"
            "In state A:\n"
            "  If the current value is 0:\n"
            "    - Write the value 1.\n"
            "    - Move one slot to the right.\n"
            "    - Continue with state B.\n"
            "  If the current value is 1:\n"
            "    - Write the value 0.\n"
            "    - Move one slot to the left.\n"
            "    - Continue with state B.\n"
            "\n"
            "In state B:\n"
            "  If the current value is 0:\n"
            "    - Write the value 1.\n"
            "    - Move one slot to the left.\n"
            "    - Continue with state A.\n"
            "  If the current value is 1:\n"
            "    - Write the value 1.\n"
            "    - Move one slot to the right.\n"
            "    - Continue with state A.\n";

        assert(part1(test) == 3);

        const int answer1 = part1(input); // input from puzzle_input.h
        assert(answer1 == 2794);
        return std::to_string(answer1);
    }
    else
        return "<nothing to do>";
}

}


int main()
{
    // null terminated list of solution functions in advent day order
    struct day {
        std::string (* const run)(int);
        const char * answer[2];
    };
    day days[] = {
        {day01::run, {"1390",       "1232"}},   // --- Day 1: Inverse Captcha ---
        {day02::run, {"47136",      "250"}},    // --- Day 2: Corruption Checksum ---
        {day03::run, {"371",        "369601"}}, // --- Day 3: Spiral Memory ---
        {day04::run, {"455",        "186"}},    // --- Day 4: High-Entropy Passphrases ---
        {day05::run, {"358309",     "28178177"}},// --- Day 5: A Maze of Twisty Trampolines, All Alike ---
        {day06::run, {"7864",       "1695"}},   // --- Day 6: Memory Reallocation ---
        {day07::run, {"fbgguv",     "1864"}},   // --- Day 7: Recursive Circus ---
        {day08::run, {"4066",       "4829"}},   // --- Day 8: I Heard You Like Registers ---
        {day09::run, {"15922",      "7314"}},   // --- Day 9: Stream Processing ---
        {day10::run, {"5577",       "44f4befb0f303c0bafd085f97741d51d"}},// --- Day 10: Knot Hash ---
        {day11::run, {"812",        "1603"}},   // --- Day 11: Hex Ed ---
        {day12::run, {"130",        "189"}},    // --- Day 12: Digital Plumber ---
        {day13::run, {"3184",       "3878062"}},// --- Day 13: Packet Scanners ---
        {day14::run, {"8106",       "1164"}},   // --- Day 14: Disk Defragmentation ---
        {day15::run, {"577",        "316"}},    // --- Day 15: Dueling Generators ---
        {day16::run, {"hmefajngplkidocb", "fbidepghmjklcnoa"}},// --- Day 16: Permutation Promenade ---
        {day17::run, {"640",        "47949463"}},// --- Day 17: Spinlock ---
        {day18::run, {"3188",       "7112"}},   // --- Day 18: Duet ---
        {day19::run, {"ITSZCJNMUO", "17420"}},  // --- Day 19: A Series of Tubes ---
        {day20::run, {"457",        "448"}},    // --- Day 20: Particle Swarm ---
        {day21::run, {"188",        "2758764"}},// --- Day 21: Fractal Art ---
        {day22::run, {"5570",       "2512022"}},// --- Day 22: Sporifica Virus ---
        {day23::run, {"3969",       "917"}},    // --- Day 23: Coprocessor Conflagration ---
        {day24::run, {"1940",       "1928"}},   // --- Day 24: Electromagnetic Moat ---
        {day25::run, {"2794",       "<nothing to do>"}},// --- Day 25: The Halting Problem ---
        {nullptr}
    };

    
    namespace chrono = std::chrono;
    double total_duration_ms = 0;

    for (int day = 0; days[day].run != nullptr; ++day) {
        for (int part = 1; part <= 2; ++part) {
            const auto start(chrono::high_resolution_clock::now());
            const auto answer(days[day].run(part));
            const auto stop(chrono::high_resolution_clock::now());
            const auto duration_ms(chrono::duration_cast<chrono::duration<double, std::milli>>(stop - start).count());
            total_duration_ms += duration_ms;
            printf("%2d.%d %6.2lfms %s%s\n",
                day + 1, part, duration_ms, answer.c_str(),
                (answer == days[day].answer[part - 1] ? "" : " *** WRONG ANSWER ***"));
        }
    }

    printf("total execution time %0.2lf milliseconds\n", total_duration_ms);
}
