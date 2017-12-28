This month [I wrote code in C++](https://github.com/anthay/Advent-of-Code-2017) to answer the [Advent of Code](https://adventofcode.com/) questions.

### Part 1 - think, research, make and learn

I read about the Advent of Code on [Hacker News](https://news.ycombinator.com/item?id=15813318) on December 8, so a bit late to the party. The problems require a knowledge of only basic mathematics and can generally be solved with no more than a few dozen lines of code.

For each problem I tried to think of a way to do just enough to get correct answer. Sometimes the way to solve the problem seemed obvious. Usually, after reading the problem, I'd spend a few minutes thinking what sort of data structure could model the the problem space and would efficiently support the sort of manipulations that would be needed.

I solved all the problems correctly first time, except day 18 where I made the registers 32-bits instead of 64-bits and didn't notice the overflow and day 24 where I typed in the wrong number by mistke.

The days that stood out to me were

- Day 11 - I wasn't sure how to represent the hexagonal cells so I searched for something like "hex grid distance" and found <http://keekerdc.com/2011/03/hexagon-grids-coordinate-systems-and-distance-calculations/> and <https://www.redblobgames.com/grids/hexagons/>, where I learned of the idea of giving each hexagon an (x, y, z) co-ordinate, which makes distance calculations simple. ![](https://upload.wikimedia.org/wikipedia/commons/f/f5/Roman_geometric_mosaic.jpg)
- Day 16 - When it came to part 2, I estimated my solution would take about 5 days to get an answer on my computer. It took some time staring at the problem and my code trying to think "what am I missing." Eventually the thought occurred to me "what if after one of the iterations the string has returned to the starting state?" Sure enough that's what happens, so the solution was then simple. When it's an artificial problem, like an exam question, you know that there _is_ a solution and if you look long enough you'll find it.

Eventually I'd obtained 50 gold stars and felt pretty good about myself. My unvarnished code is [here](https://github.com/anthay/Advent-of-Code-2017/blob/master/captcha.cpp), if you're interested.

### Part 2 - read other's solutions and learn

Then I looked at the AofC [leader board](https://adventofcode.com/2017/leaderboard/day/1) and was shocked. One person solved the first question in _57 seconds_. I'm pretty sure after 57 seconds I hadn't finished reading the question. Those guys on that leader board are in a different league.

I looked at the [subreddit](https://www.reddit.com/r/adventofcode/) to find other people's solutions. One can learn a hell of a lot by looking at how other people solved the same problems.

Advent of Code was fun.


