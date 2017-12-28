// My unvarnished solutions to https://adventofcode.com/2017

#include <iostream>
#include <cassert>
#include <sstream>
#include <limits>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <cstdint>
#include <map>
#include <regex>
#include <deque>


// call f(line) for every line in given s
template <typename func>
void eachline(const char * s, func f)
{
    std::istringstream lines(s);
    std::string line;
    while (std::getline(lines, line))
        f(line);
}

// call f(n) for each int in given s
template <typename func>
void eachint(std::string s, func f)
{
    std::istringstream numbers(s);
    int n;
    while (numbers >> n)
        f(n);
}

template <typename func>
void eachword(std::string s, func f)
{
    std::istringstream words(s);
    std::string word;
    while (words >> word)
        f(word);
}

std::vector<std::string> split(std::string s)
{
    std::vector<std::string> result;
    std::istringstream words(s);
    std::string word;
    while (words >> word)
        result.push_back(word);
    return result;
}





void day01()
{
    struct local {

        static int captcha(const std::string s)
        {
            if (s.empty())
                return 0;

            char prev = 0;
            int sum = 0;
            for (auto c: s) {
                if (c == prev)
                    sum += c - '0';
                prev = c;
            }
            if (s.back() == s.front())
                sum += s.front() - '0';
            return sum;
        }


        static int captcha2(const std::string s)
        {
            const int len = s.size();
            if (len == 0)
                return 0;

            int sum = 0;
            for (int i = 0; i < len; ++i) {
                if (s[i] == s[(i + len / 2) % len])
                    sum += s[i] - '0';
            }
            return sum;
        }
    };


    const std::string input{"\
82317536746839978781792591955653325794933784832649781841433412843796827\
88518559178822225126625428318115396632681141871952894291898364781898929\
29261479288488324935672874199322488916792823226132512344756982993295126\
82929539287667557797618379938125285274844872981177398691894155994617469\
44992651752768158611996715467871381527675219481185217357632445748912726\
48766988187612919293299528277784849656125983978118871923395161918838853\
26985192981421128537769425452118591341852317689528884624716428515883684\
45761489225786919778983848113833773768236969923939838755997989537648222\
21799638175754296484433728542865437549935999779267925688137896785237684\
88127957611181392881527999211768742563776159527582688441395796227549654\
61884862647423491918913628848748756595463191585555385849335742224855473\
76941121237644659165484616818927895985768133672422143484694612491527119\
64331443354827874326838485944876484775324989525725151188644756218281182\
74911298396748213136426357769991314661642612786847135485969889237193822\
71811126956174156347911683236448572471624217628864237184956966459419467\
47633196877357235176149625755921112861775534356519528538787754312343279\
19595595658641534765455489561934548474291254387229751472883423413196845\
16275271692519986659188331363884647432116156989251857434622675136631531\
11457774487818622221269234493118385646858826958893975314139376666732334\
51216968414288135984394249684886554812761191289485457945866524228415191\
54916855795763338699193118677384386999928446877386622197687399816881894\
43996614639636587848217962729871552781953555793867681567188136245592645\
74836134419725187881514665834441359644955768658663278765363789664721736\
53351777429247819214393431839941818829875335181538856135952853377899629\
62793663943864555444469226539767251138898427491823612535824333193511938\
62788433113852782596161148992233558144692913791714859516653421917841295\
74916346975147983549271339286151999379196792777311471388845898279651497\
77179875981654869677869899919981424886311686979638161563742162243861939\
41566358543266646516247854435356941566492841213424915682394928959116411\
45796789761445749727947266122954861277715599835861894522232655817648694\
4695689777438164612198225816646583996426313832539918"};

    assert(local::captcha("1122") == 3);
    assert(local::captcha("1111") == 4);
    assert(local::captcha("1234") == 0);
    assert(local::captcha("91212129") == 9);

    int answer = local::captcha(input);
    assert(answer == 1390);
    std::cout << "1.1 " << answer  << '\n';

    assert(local::captcha2("1212") == 6);
    assert(local::captcha2("1221") == 0);
    assert(local::captcha2("123425") == 4);
    assert(local::captcha2("123123") == 12);
    assert(local::captcha2("12131415") == 4);

    int answer2 = local::captcha2(input);
    assert(answer2 == 1232);
    std::cout << "1.2 " << answer2  << '\n';
}


void day02()
{
    char * input =
        "4347	3350	196	162	233	4932	4419	3485	4509	4287	4433	4033	207	3682	2193	4223\n"
        "648	94	778	957	1634	2885	1964	2929	2754	89	972	112	80	2819	543	2820\n"
        "400	133	1010	918	1154	1008	126	150	1118	117	148	463	141	940	1101	89\n"
        "596	527	224	382	511	565	284	121	643	139	625	335	657	134	125	152\n"
        "2069	1183	233	213	2192	193	2222	2130	2073	2262	1969	2159	2149	410	181	1924\n"
        "1610	128	1021	511	740	1384	459	224	183	266	152	1845	1423	230	1500	1381\n"
        "5454	3936	250	5125	244	720	5059	202	4877	5186	313	6125	172	727	1982	748\n"
        "3390	3440	220	228	195	4525	1759	1865	1483	5174	4897	4511	5663	4976	3850	199\n"
        "130	1733	238	1123	231	1347	241	291	1389	1392	269	1687	1359	1694	1629	1750\n"
        "1590	1394	101	434	1196	623	1033	78	890	1413	74	1274	1512	1043	1103	84\n"
        "203	236	3001	1664	195	4616	2466	4875	986	1681	152	3788	541	4447	4063	5366\n"
        "216	4134	255	235	1894	5454	1529	4735	4962	220	2011	2475	185	5060	4676	4089\n"
        "224	253	19	546	1134	3666	3532	207	210	3947	2290	3573	3808	1494	4308	4372\n"
        "134	130	2236	118	142	2350	3007	2495	2813	2833	2576	2704	169	2666	2267	850\n"
        "401	151	309	961	124	1027	1084	389	1150	166	1057	137	932	669	590	188\n"
        "784	232	363	316	336	666	711	430	192	867	628	57	222	575	622	234\n";

    struct local {
        static int csum(const char * s)
        {
            int result = 0;

            eachline(s, [&](std::string line) {
                int smallest = std::numeric_limits<int>::max();
                int biggest =  std::numeric_limits<int>::min();
                eachint(line, [&](int n) {
                    if (n < smallest)
                        smallest = n;
                    if (n > biggest)
                        biggest = n;
                });
                result += biggest - smallest;
            });

            return result;
        }

        static int csum2(const char * s)
        {
            int result = 0;

            eachline(s, [&](std::string line) {
                std::vector<int> v;
                eachint(line, [&](int n) { v.push_back(n); });

                auto even_dividers_divided = [&]() -> int
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
                    return 0;
                };

                result += even_dividers_divided();
            });

            return result;
        }
    };

    const char * test1 =
        "5 1 9 5\n"
        "7 5 3\n"
        "2 4 6 8\n";

    assert(local::csum(test1) == 18);

    const int answer = local::csum(input);
    assert(answer == 47136);
    std::cout << "2.1 " << answer  << '\n';


    const char * test2 =
        "5 9 2 8\n"
        "9 4 7 3\n"
        "3 8 6 5\n";

    assert(local::csum2(test2) == 9);

    const int answer2 = local::csum2(input);
    assert(answer2 == 250);
    std::cout << "2.2 " << answer2  << '\n';
}


namespace day03 {

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
    /*
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


void run()
{
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
    std::cout << "3.1 " << answer  << '\n';


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
    std::cout << "3.2 " << sum  << '\n';
}

}


namespace day04 {


bool valid_passphrase(const std::string s)
{
    bool valid = true;
    std::set<std::string> dict;
    eachword(s, [&](std::string word) {
        std::sort(begin(word), end(word));
        if (dict.find(word) != end(dict))
            valid = false;
        dict.insert(word);
    });
    return valid;
}


void run()
{
    const char * input =
        "bdwdjjo avricm cjbmj ran lmfsom ivsof\n"
        "mxonybc fndyzzi gmdp gdfyoi inrvhr kpuueel wdpga vkq\n"
        "bneh ylltsc vhryov lsd hmruxy ebnh pdln vdprrky\n"
        "fumay zbccai qymavw zwoove hqpd rcxyvy\n"
        "bcuo khhkkro mpt dxrebym qwum zqp lhmbma esmr qiyomu\n"
        "qjs giedut mzsubkn rcbugk voxk yrlp rqxfvz kspz vxg zskp\n"
        "srceh xdwao reshc shecr\n"
        "dcao isz wwse bbdgn ewsw qkze pwu\n"
        "lbnvl lviftmr zqiv iadanl fdhrldn dlaani lxy dhfndrl fkoukx\n"
        "raovmz pdysjsw hqps orsyqw rrwnzcz vrzoam jjljt\n"
        "wgt gzi icpwp qeefgbe msadakj jbbrma sbj dufuujx zex\n"
        "cfzx bvyu eswr hafcfy klw bgnhynv qrf aop\n"
        "rzlq atrzcpb hpl pajjw cdxep ean aptzcrb rzcbapt\n"
        "xogpf ucc nsukoz umtfbw xfvth ozusnk fopxg ubp iflb\n"
        "xot nqcdyu kpwix szo cyxv hpmp hwtrc zso nyuqdc aha\n"
        "mkzf cat tkjprc izxdggf obspan lmlbg bsyspf twox\n"
        "lfmfrd ooclx tcl clt\n"
        "dxvnyd nxwojj arutn eyqocj swzao tmh juvpezm\n"
        "teu eman rlmdmk xkbodv fvrcm zorgy wmwe\n"
        "hmo fdayx duciqf cgt duciqf\n"
        "imjnv vfmsha cyrusow xjswoq nclrmjy sjxowq ynjrcml\n"
        "rwbsay alsi bmzpvw ozq aduui nihwx glwdiz ixmkgfx\n"
        "vtjzc ntkh zekj qrbkjhn zekj lyfnbg\n"
        "afaig jqhli oie lhwyduh kqfnraz nfrzaqk mayfg iljqh\n"
        "inb zum zmu dnl zjxg vrdziq ypdnsvt\n"
        "uhbzmre mpdxm alkbmsq aopjmkl mqxenry ayvkrf zxvs qkfqva\n"
        "fimjr ccv cnug crdsv\n"
        "bqyve lhxdj ydu qbyve vihwjr vyodhc\n"
        "vmng dyttyf noagpji tdtyfy ewiest ogg\n"
        "kgscfj klmsv vmksl vmlks\n"
        "qlvh veo wruft wtm fbrlvjr evo wvwmny dhp bvrlrfj lvt vgzuyyw\n"
        "mxuro orxmu tivu tjdq ojjvju cdd\n"
        "kjexme gxbysxp yxrum hinrklv fxehytd qkt tqk umryx nim\n"
        "kywnux wab tzrft dsaz jgwuw dubarmi fle wjguvr umjp uzncwj mzz\n"
        "qokwh zrda xywufk tbxhhj eejqaoa hwoqk zer hwt hbjxth xyf hmh\n"
        "eregs qdx tdequa agrlrg mwwpba qjie yrjvhr txujk\n"
        "iyot fxwdcb zvwfv vfzwv wvkw ncwbr wdejrr ltcdza\n"
        "waix eza znmonya ldfghws ialwfvc dey ubsz uhbnh svgekg nonzyam\n"
        "bryz tfbqn xznfmw xiplgww wwxigpl jxzcgxl rzyb\n"
        "cqvl rrcoqxs staeuqr hzzow cwv tsvol dio coc ddavii uuojy\n"
        "txbn qvkkyh gbqnjtq ndpkqr srt bkpqfmm ytycev ypcv bpqmmfk\n"
        "uqkjmul dour zgq ztango yrrjhrg ufxnmuw\n"
        "ekxbcv vkxbec xbcevk jiq bar\n"
        "wczff qdu cwffz hhk wlvyg\n"
        "zjlconc osgsro dajzo hqih ehml\n"
        "hnio shccluw cpu ivaby tormn vkef abv vkef ivaby\n"
        "xgbdeso xiizs omqwy sbtnnt khago evviclw xyu dtvg wsyxfuc humewp\n"
        "cnzu bia vdyqrf wwb qveum hmh ouupgc owli\n"
        "pjpmfxa dvd lxgh ndy gwph oebfkqv vtlxdg efl ekj dyn\n"
        "mvan nmdkc ucyshia mavn ecst poo\n"
        "oybm pjwm bmyo wovgu xykziaq obmy eiirhqd\n"
        "xkvomx yxvv oxxpth elh vxvy lhe ycn\n"
        "okxglw gmaangx gnxaamg yduzrr nzwxtnd rcxcu xjjvno yat cin gaxnamg yss\n"
        "oicgs rrol zvnbna rrol\n"
        "abb edpnxuo peoudxn bab ceay\n"
        "ncpkfz gvwunb fckpzn caafx pkcfzn tsfl\n"
        "fnrt ymenkpq wodubcm niv nvi ziluu cuowbdm zocg pdakwt mlzxkex nuxqclo\n"
        "uouxcgl stgua otadr ideannq wizxunv iqsdpj mxddt ldst ucxogul\n"
        "rbrwyhk wqoz zqwo ikwgexl atpu iza\n"
        "smo yolp pcahlu muljxkq cbkljmz zlbcmkj zvbmgz eaiv ncv zplifm yplo\n"
        "ocutdhz zmnaap llgv llzpl loavju guzkfq saay rxyhng cwxzx lcv anrnzs\n"
        "etyzx tcm upxrtvd imyoiu rdpj fed dmm\n"
        "gonqa szteh szteh razdqh phyff upf knfqfaf knfqfaf fpsgl kakag\n"
        "mcju mixskop isrwat lcr nfyi lcr aaevr nfyi pqrbk gnful\n"
        "xfmr fkmnq fbnhd mxrf litniid xbae frxm zcenf\n"
        "yuh lzojtj rqsh hyu\n"
        "vbjgql yeshsuv lokt efqota wpwjfu ykyq rxc fxxh ycqfkk gndts vdf\n"
        "wnylmr kkuruxm azr xukrkum dohkwx dmdb\n"
        "bjiyrwf dvf fdv vdf gnokekr\n"
        "jsaq hcww iayqtu llv gdpxdrd hwlo nosjit wpm lcab fcgwr\n"
        "fxjp bys nnf xzllckh bys hvojw zcwtgwz wye ccyvjv\n"
        "grafa hbb ghk wkdpsf ufa uoqmysd\n"
        "yvacf kssbff iovrm mvrio cfbpb avh zzje\n"
        "gqd qmsen wkvrfz vhtsa zrwfkv gul zkvwrf\n"
        "hrbi svaogb aogsvb bgrk hibr jbtkr\n"
        "ljl ryc mrewrge yky\n"
        "fcqyymt emk qcmyytf mcfvusb luy qany cbsvumf\n"
        "oknt mcozuc ccmuoz uoccmz\n"
        "uziil xobutwf acnof iqgwl diso\n"
        "sekq fxbtsuv ddnnqg rnemlt dngnqd hhgjfus stxvubf\n"
        "lajcp qgiw fyz blrlcd pviwv buh wnkk\n"
        "wolqfk nvpapfc rwcqxfz xobno yzjfz irpj wolqfk wbnwjt\n"
        "vmabj noiljne hhqf holxkbk swwzx ylgj lnmxy lqodhk abjvm bmsrf\n"
        "bpnp yrz pjepxxs jlmhuy vihlx zacm inuazhc xsxjepp\n"
        "tryl kryh eonvaad ucevssk umkxg lqej nswopjj svkeucs bmh stosxxz\n"
        "cfdwd dmfdrvm ibuhsz nwtgmb pjt dmfdrvm cqdcm fzjjz afa ibuhsz\n"
        "erwp abn jwx ynmkkj rhgg abn epd atqhs rst rhgg\n"
        "jtnp cegdsoy gfuvfbg gdmn ahlsc\n"
        "jgrp diu jrgp onjnml nojmnl vxockc\n"
        "lakqyuw khq dcpiwt ykwlqua hkq plklx ujbckec hjcvur jnp pvyf\n"
        "usuvoo jkih ylafyy yhio jureyj\n"
        "uazisdf cnwlfnf ewodatr woaddkd wbla qmn atdrowe\n"
        "bnyepaa ntqh xppe ydtsw ppex\n"
        "yewjwsp jxylmtk ijese ewry ijese kbja nfml zeuwcsh juimz\n"
        "qbvmf nca zsfreo uurgaiz twe fbqmv ncwi etdcsk atowfp\n"
        "jeotslx kgdpzp wxlcww pdd dcn ddp\n"
        "macllv ldl kyluine lbt hbxbr wxcaspp ezwvc qxkeu\n"
        "ivg gxv zsf ucr uff yrz\n"
        "tdlwbny bqlrlz tbynwdl lwtbdny\n"
        "tnekq pdaievs ttwpfh xfm fcaa\n"
        "zqqhl zbf fbz uqrv bfz ffwavhk foccg\n"
        "vcw ebqdd cwv eddbq nrmq\n"
        "hpiusz sizphu xzq sgyehk wgagkv hsygek\n"
        "vagkxa iou frqdnnr ipcg uxvh vvh eskf katgpiq aqktigp gzvseyi\n"
        "xkwgd kzfxk pgdy fmtvq ngf rshx zti pamviob ely knz\n"
        "hwo rteohu qzwoe rotuhe wzb\n"
        "bsqgg tid dti gtats dit\n"
        "sjtux djwxv dljwjq xwvjd xnqfvx veqdrtl uxtsj nnkjn wnhilaf unirrp\n"
        "fruuqjk gtote gooklg bzwhim zfnccmm ezipnf cxwdxa wfu fdca\n"
        "zcyxb byzxc cxbyz pgcqco ivlxz\n"
        "wrjh zfdinsf ihw xwosiah hdg xpiabno bilyy azdeczg javuwa\n"
        "rinlv dcpt qhencba mmb njxw gadc\n"
        "qwcpua qzyzt cxjsgh kumh byiimas qhsgf qytzz rqqruwp ismyiba xydcxz rwkscqa\n"
        "xbzefi hltca ibzxfe fkx xizbfe wvaynts\n"
        "oyuce vzk ouxvj gfh efgbv ubc nyb bxnbhd mtwboe whksy ovmrt\n"
        "ljrebp tacn bpjler utphw wmfw rcnha\n"
        "drdnic eyodes rcnidd yseeod\n"
        "umxmsf kfroz ukhjin awpnnnu ooyyohh tuv rafano jze\n"
        "bakz lfzpjyg gfkqcgn kzh zwpvk gqfngck\n"
        "jpaony ojpnya hmro xaaz tovary aaxz iel pbg\n"
        "swvbgc bbhjp yvrcddd rhj clfu eao afrkegn qvvb yvcx nxjmdo rcvtx\n"
        "conbjy jeqtri wvujt jeqtri rkhllgw tsdt zowreo qxr qbpragn kuzmplw wvujt\n"
        "jrpxyp hchljy rkowqb eeaf ltllebb gtksrwx iazx vnsfmc zzrxw hlcjyh\n"
        "piehb cjdzt eqn kuje rls oaewoz lrqwt lcrrq\n"
        "hdjowxv uknhlv hluknv pokxg\n"
        "txiqxfr fyyp pyyf xfxtrqi tvm rtvby cfx trx nwrf kqrxtat alwot\n"
        "wdaadr stexpow ardawd uejqxc\n"
        "wwgwjel wwgwjel mtjt wwgwjel\n"
        "mczx uua lgceb dqru vkcea tcet ruz\n"
        "jkt yroojr qdrtdu wze ovwz fdmqnr xxsyfd kchytwl hctlkwy gyd\n"
        "eif irnrce iamhxgh bmis uxye azrwdi sznv yuowb vdlqqxu\n"
        "dxdjyj hngqwzs yhwku qhsctfe rhbc rchb tqhcfse\n"
        "fxyxnzs qtxevin rvtxtc iqnxtve\n"
        "zgbpk mwzxx bgpkz wkpkn\n"
        "rjiym iub lcyw agbtlb bzhx osv rbtf\n"
        "emmyu uoflio tinih skpqaj rbor gezbhhv ine mij qlqte uuj ycns\n"
        "owmwc uhxv pyho ftjh jzsg blqn bszyo bob trbycy mkru\n"
        "mwgz bbqsmpp fgzs bihhg bbn pjxxexs qrqmt htsxfwo qltqp vqqaxi\n"
        "lpr wcvy sxjqq ltd rftdgv pdnog ymu\n"
        "qhcos shuy icdhucu lrikh rwslv yxbgibl rcomhn wakirz\n"
        "civdmee owlzocl vedecim rogmjnn pix pohcmk dsjm yworm\n"
        "vzdpxp lvt inufv yofqt omm qfoty qrlseqy amkt kjcvg vgkjc\n"
        "huhq quhh levzsws sjuun ofgqr cjhp nfxbbft rnt wtbd tbzab\n"
        "tjftkx xpfcv hvftvhw lpypbjg batrn fhwhtvv uthl arbtn brb sthv\n"
        "ogr uyuxdco bpjgir edztxv sxtgu jzfmx ihnauz zwegqkr kvkw\n"
        "mhxthf pervvn gshy jig ezjteq ckkcpy gww\n"
        "tiljyki rpe prcojy tjkylii moxu\n"
        "pjsdqc lgqydfd lohck emrtejw axwmo wuuv rfi qzyncmw gjijdfb bljfd xrs\n"
        "ywjab gynzi relf kziy xmsby izyk ocwoho kqnyh bwayj\n"
        "bhjlz uonz jhmzuq eiajoos zjnbj tomj bmyv hjlbz fgw jjbnz\n"
        "kszz xzw xzw prtznyb\n"
        "ghzk vxhwt thxwv slwpayp qxegmi dawdwo kgzh\n"
        "ibpcvuf wnuwxu sbf jsj bfjynl cdp jbylnf\n"
        "epaxr vfhf hvff azepadz pwf sbo pgfzya hslyo rqqj rmklw hwtta\n"
        "yyolko pwbvxvg xdwl yfje hftep kzzsr kho jeyf yvslxpw kfyv\n"
        "xmk juyjxy eqno mdwklum reg dgn cirh wmxfyj bnxlgo dlobk\n"
        "oyv gshqyot jgcqe dsf gyohqst gqgeojo egoogjq dmqpyp\n"
        "sypianq yss lmhu ulmh itilh ndkda lhiit\n"
        "qbxxl bxxql ikald nfap qixwbqq\n"
        "jtqhqty ljysnl nwoj toa bmmyj pal\n"
        "ahktew sxody nkvsf pbxyt baws wgwfwej bevgzm jus hcvajfy kzrb jwgwewf\n"
        "jzsb szbj ujngwf nfuuf lfiuxdu uufnf orsy\n"
        "vgo hto isstyul gau wsmxoqw\n"
        "uxw itwf epaw hec wape hemol rpwyosc xzxmrll eetz zui kagca\n"
        "mjncux muv rygdeis rygdeis\n"
        "qgkqjvf iprzibd fkvqqgj llcrl vbh vlf lllrc zwrunt\n"
        "dslsa wvoex eqbwj tjem gbx ayn xcan fnacl xggxon gnwjlh\n"
        "yzosv hcxjiz yvon gcgd\n"
        "bixpny ecln sda eymt bjiwk\n"
        "rlcad lrdca adoqfzs rgty mds pwb kmwj\n"
        "wkai pmryffq rrdmodc wgyx taz yxwg nkap\n"
        "auynzwc vzg uapdv qkrh\n"
        "ldmuysp oyu kpn ejbl mfifa bzs hwyn brlw qpzqx uyilao ysdumpl\n"
        "czoxoj pwnultl wezolbw lyk aonesgb\n"
        "nqy nhb nle yycp lgtbo ojf dytwyh ufa\n"
        "rwr eph obg peh pejret prjtee ovgz\n"
        "vdqf vdqf ycjrg ovzl lelbe vdqf\n"
        "gvagdqm gvdgqam dmb zaxe nepzwn\n"
        "emwh bkkbgec qwdgk mhvfsrf wmdfpp ekzuua\n"
        "mbqw lgkyazt ckyhvnq uladwo owt\n"
        "qwiwd pbo tkjoqda zapo dygqopv zzdlwfn\n"
        "qty dhb iinncba ytq kvh idgoevt chx waq\n"
        "ulffsvk vplsz ulffsvk uxsh cpwgxd ikgcacx nrirke uowcjvn\n"
        "gknmxr grkxnm fco dilyyj grmxkn\n"
        "saqxkh uhue nvu fef xsuxq ekyyoc bcaavd\n"
        "qltwqa vrmpv vhra nof yprauc vkreojm eaq igiy mec\n"
        "wvheiyg uthy gpvcs nhnjrne mqaejr tfnsly zfbhn entcc nystfl cpq\n"
        "zxv jzk dwsjgrd gqqxhp xqxu naunwc yeh qzpkz awcnnu aoosa icadax\n"
        "vpmqmg qmvpgm tqs mvpqmg\n"
        "inehzu zwxeoy jxia fcyzxc hwikd\n"
        "bzwnp kamsen ajpn kdls bzh xqcb bzwnp cmjnfa wmgx\n"
        "hbuhc qgvhxy smzkxh zzebox hbcuh net wyrdppc yvgxqh\n"
        "oeum oemu iyags xaipdi euom\n"
        "tqljgoq ghtdhw xhnni lux qltojqg lki zxztda pcqjif acpzvwy\n"
        "ydijaq kbyjxpu onyd hsfgz geqvbg\n"
        "rwoih xog dtbzyr ryzbdt tdbyzr\n"
        "vcdxf zosw pardxfz bmb mscmain lwfc jvq hbszcqh fxomsmm ahnugx\n"
        "zutsemg pqzil ddv nsstz gmeuzst bedvy xkzzjpw xlqbd\n"
        "xxf ltnnu yeb hbml agj meovtjr qrul kexerkw xxf\n"
        "tqrpd hhcx bmdv nlmr pnu pajdtc rpatqi yekedx oeiuew epsshog\n"
        "ttbfpv plairk toh jagfsg njnqpa tmwh vwqp irtxv\n"
        "vdky uwc tkkkztp vdky vdky qlcw lza\n"
        "rzie yundymy pwgx wtwtbg kpiw mewnb liveysj uvsbn\n"
        "jgfvyny hacg pzra arpz uowswu puzsfu hoe heo vrq naup\n"
        "hqv vrl uko qgpikho lligvxa wdld qgpikho\n"
        "whvby yomxwj dieffc jkprinh dsaqy yfrnba woyq yexeb mjn cbszn xeswvvo\n"
        "wowtgu rciyg rlas bra quyfec ihe thuu asxhscu bsbdpbi ogxosu\n"
        "vydsaet tvnkjq piedkzj foeiqz zqivt iatsju tjnqvk drauaf vqitz invoz\n"
        "cppn jqzw zmxr qksuas iifmjg xtkgf cppn cppn jpsd\n"
        "nkifpsq cxdx bokxhm ebww kghagrp bofhrl grc cheuzyj\n"
        "ibgrlvm hrcx jjuoh ipmt\n"
        "hcoqkh fzt rgravb cimauj jxjq blct qhc vjxw pqpg qzp\n"
        "jycxz xcv czxjy vxc\n"
        "liljaur cgmg neldxb xfummcq yfhiukd dnqhl iolxn cmewhb\n"
        "hpvoihj fkwokod txy uuktw vmqqb dpldzh yxmcay cyaxmy xycaym wekr\n"
        "ccnaf wuxc ecadb vbgpt ccntf sezo skjdkbf fnctc\n"
        "hqdtwho kdhyman bjtcjvr bwllva ncyffyr\n"
        "xprn jrrvmj pdw yvexm ewbflbe eapml rvrmjj xmevy rxyzhf\n"
        "wjcbpy qdgtcp cfjh muww fhg sgfdleo nelpte yucqa aavev\n"
        "rci vqypsqt xmg rzii\n"
        "gramh wwprtc ampdhw dajr\n"
        "ovrm mdyhpbl mdylbph aykz\n"
        "cbmo fxs nuugu guunu upt ljjuhjw nituh utp kxqc\n"
        "rhabal rhabal rhabal vah lfrs\n"
        "nrq qway ftzp rtjcks mbygdtd hsiqbh wypqb rtjcks cllp hsiqbh\n"
        "ywa anhcf nvd puqkwg molrwck wsctx xvd molrwck\n"
        "wox jzq jfen wcvus cswvu oxw irg lmu tpj viahm jesic\n"
        "qenad neqad smlgi ydwzq ppdemvs ucyuf qtunm eoqx jlgv\n"
        "sucpl nrdwbl ltvetok npbw ozzw hafyay sjmui sjmui jkqlq pyn pbuopx\n"
        "nxgaiu ybyl meo kgh saqjaz xhbqr otelcyp vkwc\n"
        "iqrl ldjlwvl ajhrl dnhutr gkknyqs mcvluet fgyu ogiz cxo aiunl orb\n"
        "psd cyq xpoyqny yqc kozqh vonfd uhozwz pds hcpw\n"
        "tvaxder tulwmw qiw avddbmh irog vynjzcc refx efxr emnvk\n"
        "myjx npqk whm egw kpy igrrohg ukglx ldnuqw caqg ynx fckhnsh\n"
        "dafv bkdoqg zcqvbco xgikoac cvbqczo\n"
        "rtzhpwk ukuyp bayhzp upkuy ahbpyz\n"
        "oarcuv pnlkxvw fqdkj hwzsz nauwl lpufibz vzfbgc unkluxy rwh xuknuyl\n"
        "vxhsaj ppdxw qrswqtu ulwv uqtqwsr ppxwd\n"
        "cww cww cww scu\n"
        "wiiikwa bfpewt zbgxfkl iqpk tpbwfe aazdcxj ipqk icggn fwn fjr\n"
        "net ovxuwpz yvzmzd yvzmzd\n"
        "xgar czuhp vuhisaq fgrqxy evvrtf mnmar lsk\n"
        "hld mxuedug itswju vmmejqx snzslqj toe bbmugph mgubhpb mowj nrjnzu\n"
        "qbz ouhye hsldmp lcf hyhlrb ewvle zko\n"
        "cke mupaq quapm eck\n"
        "owu zdt lales tzd apjjo fhpx bmuktbw dvehpz\n"
        "libvl zxypk azazc vtsom ohdzycb\n"
        "kiowxnc scxygrf ckxnwio ycxsrgf\n"
        "vcjj fqz lfawfx mps zhv qykch vhz psu zud spu fnpvkx\n"
        "scfvum fuktgk tua ieosetl wwmjtt exnsw wwmttj plvd pfb kku pdbom\n"
        "wkfw snukd wkfw gyaojdf bjw htagy cdsp\n"
        "beh gatqxcu ibrooxr ssww orrioxb eenkqz\n"
        "jlv affah mtbemf tylh aafhf\n"
        "zqfajd uwzrw csouuip qzadjf\n"
        "gsnlrw tcel hha tfbzrp ild aenqa\n"
        "iirfxef kdux yvj vbzgj\n"
        "ibx pfll rgkp nancij llpf xib gbkfy\n"
        "uvw kkbavj pznsnk okigtxl ogitxkl eobbs xhaz wroabn ltogxki\n"
        "bivdf lotvmoh vrb kpaeeue tdab qhukcb qmy kuqf kesu\n"
        "egs hbsfeu esg twxko uib\n"
        "ocraimu qilp ijmx eco nhevqp juxf ksejr bcqqau uhpt\n"
        "pyx jmpglf juokd dxszjw cml vcjge pfg\n"
        "gxwrt btmimse dkpbha idmz mtignka ngakmti\n"
        "dpjhm jyalra hukf imocr lkgt rqywn quhe fukh\n"
        "nbau xyc bdh yni xaawxm cyx xwaaxm akx gyodqe htbifc\n"
        "bywdxe bfrp rvb rndl onal jghiwb nuta aint qlciwcx\n"
        "fpic yrqce land soxhci qzc zoebsq hcdohcc fzhcl iyxb dqinum hchdcoc\n"
        "zok ghgp zok lmk\n"
        "ozfz zofz dkdekzb sqc\n"
        "gfti zuqvg cexmtyl qwuqnj stepb erduqhy cuoizcs qudyreh kqvfdd guzqv\n"
        "jrugz jzugr lmqu jgihgo hjfbz duxkn unxkd\n"
        "ckiys dbqmi ckiys ckiys\n"
        "iylp uvvdp pluifaa djo\n"
        "esxec rwvel djxppqf jymwt ilm aiz upn aiz wrfefwi rwvel\n"
        "nitgjr pokxuy puhdwg qtxpb veylp zqvzkbd lrvpcgu zuy rnigjt ibci\n"
        "jboyzq ogcldr hlon ywav jqqtz qjzqt vyaw cok\n"
        "aqdw jxn hqknh azbylg\n"
        "jya qpxtmsj hqrtsgg qjtpxsm\n"
        "pofcs sxw dlvru dlvur swx\n"
        "yphvvb qqyyfsp sjkbff dqyerxe jxzes oof\n"
        "pwbya txk bbwsj ywgimd kmdpc bawpy lbnt\n"
        "bkbazff ldmaq tyfl acqurpy ndnrp\n"
        "asw ctiv mnxzyc weeuwb gsn bzk irbyhxl cgqomj izy zbk\n"
        "yrxcrbt bcrryxt pofe wwzl\n"
        "vuaqez kbtuyai vuaqez dxqud uvo gmhtg dxqud\n"
        "tpzs gqdxpxo zzpgta uurjx xpqxodg\n"
        "cil lsv vznqw vro zqzvjhm jhgauzw uxnwk lci zpgpu frjvyzo tsv\n"
        "zfvcuim gwn gnw dxfppok\n"
        "btb goof iwadca aac tbb jha uvzi\n"
        "qah ned ipmure kyta ffhrwe njz paq kaag xmlui\n"
        "rkmw vrblwyy gpax hxsf zpbza gypuwf jbib ypcjwd vrlybyw\n"
        "yfjljn uxpvg huik jsnah nkhsg yfjljn lqzsz\n"
        "hagjlqx agnax jqalxgh rvjgtc mjrmph azznzcq gxajlqh\n"
        "ipki bhoabp rmiyl dmjyxl zzsmap aju\n"
        "tyjrr rigrf ciq qic avmwu jtr wpq\n"
        "vuf cosgytm toycgms ufv qzpcbrs\n"
        "epzgxr lydrsj ezxrpg expzgr\n"
        "ecm prj kmak makk jpr\n"
        "ccwyq txy okj matxa socoa\n"
        "zrjphq gigayv ywkfmru yrwukmf fxjjrha gqkxx zhjy tisutx kufrywm izjfj igg\n"
        "lfhgsro gsroflh wrpo lofhgsr\n"
        "kgkgj wkhnab ubrjaoa ubrjaoa ubrjaoa ggdgh\n"
        "hztutpn epnqmz ffcroq mnqpez niibpn kdloak xjui ozttj lyzsc pzgq inpnib\n"
        "kruz sjqp mmd hhdxjgc mauouma asevvo upjwqi hxcgjhd etqzagp\n"
        "zylf qime cho oraid svytv gqrjufv mker cho vnkyiin tjms\n"
        "dotjul qyv hnh cibtg gdpauyx wzp\n"
        "fabtira ejxoeor cqyethv ndjrq hnxn joq otng lrr csytrub\n"
        "txhgepd fwdaanm nawdamf pxine qqrn pronw exnip qwkimt rvy\n"
        "kuxzhi jln urzxtw rzu ebsuylm tscru qwlhfgq nnu nuchvz vuht\n"
        "cqgu camlr umkltcf stx izp rtdwxff wkfvs\n"
        "jhje cxix lefcrsu nebv idfzhic xqri xkft\n"
        "utzxb znb ietupd uqgbhje aobip oawjwm hetyan uqtqv hpwzyri kwxyu\n"
        "jvzvbt xuyvp aegdkb srbw bzabpf lyfriez cruyfu\n"
        "nhi nih aeb ihn\n"
        "hcf zypt djcm pkjx pvhh\n"
        "rhvxcfk exydvk ids hybme hnk yfchvs mjbo meocn\n"
        "rpboxr rxoprb hdzje zhedj\n"
        "ziildbo apzvatr vsv isndq ebxyy ntm tdttg wkvdh qnids vkdhw xxolip\n"
        "ywu uyw ipcjz pjzci xjn kvgk vsocprw\n"
        "euzo njlpv ndrlhi drlnhi ivmjkb fjrtxta skvgmrd\n"
        "gbyvj dkck gevpfvb lhadhx rgjcdn yraxh bdk oen vqryd bkr\n"
        "vgkp hncttxb wgxh gdyjo bbdfzvc xhgw rznzgda yxrrlo gxhw\n"
        "ifjlb fpecyic svhjp ilmj oxgr svhaf\n"
        "vbqky lhccj xtmm xzjyykn oqmdq qywir bswly\n"
        "euxxziv totzer vsxfx leo djho uoeaz edaig fbu lumbi\n"
        "ooqtwq pvo kid vpo jxin bod btqc fbyuz\n"
        "jhabi mronu htqqyz umjcbv sgnbp wyn cetmt pcjf\n"
        "tnrkcyl dduuhxh rylkctn pwj rtynkcl mzzfomr\n"
        "rxx ldqffi ulappk nltawbn tplhb kyb cqyi\n"
        "vzkw gviooah vxh xeae ohvcad oaiwcj dkx\n"
        "sdofdjt hcifv dqws sia mlwm vfich kavh myzue roops mzuye\n"
        "uxs nlbmjp nlbmjp tlaxa tlaxa\n"
        "ynnisp twx xtw jgkc yinpns\n"
        "kumorsm wav xhx bpvz clqc ffmadzl ndny ymslo lobv\n"
        "ljzabj tqhves mezh pwn wue dwfqq lynvtt boeknvi xqbd pkud tzlanis\n"
        "lgq qiikzl oihnsr pivtjmu qhic yvmeebg rxu qgl yuxnqse dvu faxqez\n"
        "ldk mlwja vmdqr yzlxiua amlubt ejmzfx nonm zhkxbn gaqbnqq\n"
        "ttc ctt kneknx smtnaft abljip tct\n"
        "uybhbiw zwojzlm cfxoopp abulenj znz zzn opllzmm yufk witwxzp\n"
        "qvkybwi rdbxb qiuizmo fqgne jgot jxz dqhapn\n"
        "vzinf ehaley amnk laheye invfz\n"
        "pedakl ivld agzyhr wmzba tzzzg bazwm wjwgux thrnxkn\n"
        "cmyhae nwfs nfsw kmh pxkaffq\n"
        "vdf szupev tyunp qiiu deevxmy wozvtt nelnr kgdexy gparqj hajavz biizn\n"
        "pwspk skpwp ontbjee pkspw cfbj\n"
        "ihsmh djxtak wkzllao oyr djxtak prc\n"
        "uhvihqq jrgf hdfek pdrfpt tghz gthz awae wcygi wujti svq fhedk\n"
        "gnfhsj odqlt netmsul rviio nkzw nkzw\n"
        "xyvc clxw cyxv lxcw\n"
        "duegck pkviu npwsp zdx wpvn dmxgnv ixv fybs xteru\n"
        "vih kgk hads boaddu daiwo hozoufv nef vtcplc isiw\n"
        "tzqoo dqlgvno jzlay sywx ecej addt ecej addt mnfcu\n"
        "ymgmby zegudpx ipsjai ger wcwjw brzebb\n"
        "eqekxlx itra xekelxq exqkexl\n"
        "rciu ojaa ircu nxjga puvmwou remgu\n"
        "sltth pprimb slnxopq avtir hvpv ppww fhfap wisn kzs jcuuuuf\n"
        "xbppc ydpbq zhjh oym iljzvk vsb\n"
        "ueye shtps uccehi ccheiu dqm yeeu\n"
        "gwywf lcpv qza qza gzuovj jfzffyh oybfxqv\n"
        "aawi ynsvdco azdoz cqr tnyquq xlyvbx eca kcalpes\n"
        "zumgzhy rou kguqa vubw bwgd qprxcg etnbev nqmi\n"
        "fyd tuoz uwclqn cgl lrpkf irz dizv nxze clg jghx jbpt\n"
        "kwuanos eorjr tcahp kwuanos cyrpfji zxayggd kwuanos jkqt qqvbork lizk\n"
        "vtu ovje vhg ovje vtu zcy hrhtr puawfgv\n"
        "bliz exp wot svxv epx\n"
        "jiqgxwj yips hjsatc jgsrno msfp vxvbt bba bqmw xjgpgog\n"
        "vpvypp ggwp wggp gndp hedpse afji hcqgof\n"
        "hxueubt hiynoa qqzaj ohb qway\n"
        "akq nfnes sdrlza nfnes weq\n"
        "udxpdpx gctuv llhxuow rqtetm hdbnpte oebapv civy oeobu ftgivd pykj\n"
        "pbgbvn jgmr xrz dfn gosjobw ndf\n"
        "gnf dtbsnc fwcmml tscdnb fgn qgadusl eifpk\n"
        "vmnv yuxrup qcphi tanc tnca kjrv cphqi\n"
        "hclggs sghglc fgplp odn pfglp emkrulf whwtmbs qnuyg\n"
        "wcxtr ani ain sha hsa zxbkf bzxokat qezo ljqxi xqcwfmd dxo\n"
        "waiq smpbu dbyka uibxjrg nze wiqa rfpts ddjsjv jqqjez bpusm\n"
        "lpcxf vsbj owjwc tuqj vkrgrh jsjdepv oil lxrjox frsxsi clr\n"
        "vzunp prwk nnd rfs vpuzn\n"
        "pqpqv lvsk sqxf nhobsm hakbn ywj\n"
        "xxu uxx szqnmi lnwtmx\n"
        "akq nmlw fupwsth jduvhva\n"
        "nac wwlxqck hpbce vxxqa fyp xvxqa kxwclqw yvlmv bfwi\n"
        "pzxjbj nvwv mdooiez vvftp enjrsck iypu uhru fpx omtd\n"
        "llxgp qwf pwaj cuhb scloot hbcu jgp vjw ooclst\n"
        "sisd akawvzd wvdzkaa gyoij ikt eeeosb jiwiup\n"
        "tche vxj sbctqv jvx gosur usgor ibo yqxo qqgd zspl\n"
        "cidd welisl fxblxqk qxbklfx fbdoqcz glhq iylodvz zvds ghlq\n"
        "cnsa hrxst mrnkqtj bptq jmi cpbcofs kveyeur uzmga modphm rtx kntqjrm\n"
        "dvyup usfaq rtghoec bvcos fqsua zohwwg\n"
        "onf vncybi dlaxni oqyqqkn\n"
        "okfwa qyyx ebnv llql nphq etdt ytgivlo jwgwz kiob\n"
        "ann vqnqvpx wth lpwid bjvzw xpwqxcj azg ioeyzzp onwf\n"
        "smy epzomx xep yid zctvrfj astdj cfg fgc eriuxt\n"
        "rljqgin wzobzrh cuwtx vcsbx tmg tuysq vxipgho\n"
        "ewp rsrnsj wgeyin lrji ddgt utol xxwut fjiwopa\n"
        "upu ftvqbk tfkvbq fdwga rmu puu hbiasjw\n"
        "cfl lmqkb lfc wbtlfi uqsjs ejgmphi tbliwf nzcela gzb\n"
        "zop unwmiu acull mkwh hvruknw rfk mmhaz iqmenq fifino\n"
        "iczua bjut tlgf zicau jtbu\n"
        "mtka ipd mdifj kps\n"
        "irqkysw xfsjl tedx yckkbx iktxb sqxn pbfvubv uudzppz\n"
        "mdrn cihat wcext kufs awwtjok pfjg\n"
        "wdevt tyo zzbp pqlqq wdevt\n"
        "yhatqkv ntuhw tdfd buxazh xbcsv bas gkv rbzi tddf jbj bsa\n"
        "malip hiiy qezz yhii wlfojre\n"
        "zqnfll bssveq lprwbep bhqml tztbt\n"
        "npnxotu yupdytb jptqo klfydfe fpucmfq svxcqr unopxnt\n"
        "gdpz gwj iytiohu efk ctjzf asade abhotq brmhu tbtdur zzksbh\n"
        "kxft klzslf tjdzciy lzslkf\n"
        "ejei ezmemvg xlt zte tbwhz dgnfpao zotck wus uaz gbwbb\n"
        "dgednf vypmbs eiytot empfmny\n"
        "uopmui uehue wdvzt adpfcif mutl ifaztka vydi xumtz orstno\n"
        "dleero olxiq gxnlfm nfmxlg wloeavr olhrwg hrjd yicj ymyeex qav gxyjgfq\n"
        "hevj rqcne zycgb qgqtn rqcne ptfvu yyyu zlm hevj\n"
        "zrkhuh sttnkt hkuzhr vqtu\n"
        "ppsfm kcao qjq dgadglx cxaawjn pbucfu fed qgioarc dfe ricoaqg\n"
        "vmawf oktunea zraoir gkt zraoir jcvkqoq\n"
        "mqgml ecawug ugwace szwul iwbmooj owmiojb\n"
        "auggaw cypcuw npci vuyxijd pofswjx vdkrgx xylk rom ksj\n"
        "qmwx jgsrdj ikva xzxw avik\n"
        "zzhcqu rbg pywjdn wyndpj zchuqz\n"
        "wzd wqycftu yldezp zovuy oydia hovewe\n"
        "kfid qkkk thak qhbf rvzlzvu uuxh pbj hkat gow oeqcw knqqzha\n"
        "sua itv hfpg bdqye bznlrk hfpg bdqye kvir kaai ggtz jqn\n"
        "ulggl guitamm tkpckso fupacz otxtqpd jxnqc\n"
        "ueesb ndyik vjftz jgqqv nrcf\n"
        "krh dqpmsw fybzynl zhjbvkw exefc rhs neq ldprb bhhvxm pjwirun\n"
        "ymavl qwxr yavml wagwc ekokrpq zewppw iumcgin cxdvwx\n"
        "wwdukav kuawvwd kowv dkwvuwa\n"
        "eazot bil tzu vdwwbm fvauwrq\n"
        "esq tixokph yspf ztoxfut lgzush pwv swh pwv auqhuu tixokph\n"
        "pdbeyxi poio mugfkb brwbbx aao uszw fokjeb uswz\n"
        "sbs ryjr ptispi tvnhu htunv vthnu\n"
        "czjmg hbdjhvi jrkoy fpgwc syafy aar kvnq eaecsb wqzpx\n"
        "twtp dvl uvyje qtlzj dsvyr qpjnj eyoigx bhgpccy gwn dtuf\n"
        "mxit xunctu vbyks wmqc jriuupl ybvks uncutx nsoxwrb ykt prc\n"
        "yye mgf uhc irowpc dsdv iwaxod ftavlj dxzp tcch tcch mefz\n"
        "rxe xwrrgl xwrrgl duu rxe xbbgoe\n"
        "ucsz akswcd ojrmqq cox hgfh lxwu ltnnf cenikcp\n"
        "opjhdp svwezr svwezr opjhdp\n"
        "qojlkl ircxqnt utfmdg fcvr vehkcvt ufmzcpv xwlh ddavv xel bwlz fii\n"
        "rzkayeh iursm zhily hdnq fqydfvt uwoy hptpiqu tdqy bgr xdr\n"
        "ymruz umzry hbltwya jhwhzk flh tahylbw bdbaimb qscbp ntkuf\n"
        "uxpato owsqyao vaog oenomkc usrmnc epua vzkppls\n"
        "qxqczbk qyguz alawj xgjawtw wxtjgwa snfcdmz\n"
        "fjfgos rmpd mgs vbk dlls jkljao eoovdfb ucdvaoq qmjmqku ney porr\n"
        "nmcrqz zcoxpk dlnzksd ymh zyg spxss ruyk bychq gsgv eusiuid mnrqcz\n"
        "jbzadnx lzl sdamer okoico frqisrm lxet agriw\n"
        "xceoqr qai vahc jjzifsn exg\n"
        "igjpn wfy ukn aag quro wklsq cjq bgtjrdz gmub wyhh\n"
        "fzlwnm mygfn vkzwvw zvhsex gfki\n"
        "ijvzgai ebmeq wssfmbq uguh sfuutm nwkgmex dxael liakdxs rnf sky yowpxc\n"
        "bjzkyjh fced nji esowk qxsubsk qgtts\n"
        "nkdgo bbjfq fgnxnhd gfjchl jetdb xubsgj eiju ldlm oxsx znft bbqfj\n"
        "xovcnob pxfe pmstes yzkdm iqlvha nmcziix fexp ivqalh rxecqps\n"
        "xpyew xudfud wwqe qhfjlcu epv fnrbgyv ihli qngtx yjlfg ozqbzn esp\n"
        "timl gcohx vqzic gzm shwlkkv icqzv urchuc\n"
        "xpqq gaqzwo cci dowahsr gaqzwo\n"
        "jjsagdl umbpxre kyre zvaryft tmw pxpnjy\n"
        "aqovcz nunq nnuq xjrvvh autjmit jiatumt\n"
        "elg lps lge zjjot hwz tmqrup xaxxmo zlbzp uftd fukdad kvpymsm\n"
        "iokwzal ywti zbdmzbu lprywe wbgbwza ypogbga kzliwao wstqi eqm keaeaj gbabwwz\n"
        "lwfpk mhufe eddzgd ljxyqy vhzkct uemhf\n"
        "lwqil fzugdo faq feppo usl llwqi\n"
        "nje hthr ropq qvcepu bexszfj avmzjvv zajmvvv fhcd xnc cnx qnuaux\n"
        "kvksn dphbyz nsx wrcc ccrw\n"
        "nzpa pzzunfv ygzjy gxrrtcj hrt trh pwxpg yifgjmo fnupzzv wbzx\n"
        "aepti rbojui ypvhe ubojri tcema aan dntkw qjx bfvmyos tcm hvoqytn\n"
        "qpwq exu jvsiwj gsw avr vbemldy\n"
        "xsbzpf xbzyvx xax sxh vpxt gccy xxa zhgbwoa hwwxoky fhvdxfc pvtx\n"
        "pnsa ovtjolz tyutl eyjjzt jvtoolz owbypvr tytlu ewtzgec\n"
        "cyg dwwk eihsp aeuk bbnay aluwyz hdmv uaek mwt ihpse wjhnkeg\n"
        "fhzx vjetz vjub tejvz\n"
        "ewwyb jidhu pyvyenn igtnyd tiwr akwkkbi myz xxjwb jjrdeg\n"
        "jbkuw kwir rkiw ubwkj\n"
        "bltffuw lftwufb hhsh wfbtulf nrxaa rlszi toijxnz czlci\n"
        "bqrm pga zgblgcw pgwhhn lcgzwbg bcgzlgw yqb\n"
        "mhjj vjoa gnjlc kclcr ito ofksy giavy fpqeioj\n"
        "bkiqmif izidbui sttxxi bswhkxp sduuw\n"
        "mjgnvw mjgwnv ojzyuv gvj\n"
        "qxn kkhc whd fgwk auzugg augzgu kqfov wfgk\n"
        "spdxbnu xpfofsb bpfsoxf ahjywql spbxoff\n"
        "bwqxhlm wbqlxmh kqgpl fyzgf guhkvgx ovk qhmp gnrmu wvd wedj\n"
        "vvwf hcnc vvwsngj qedzoxm hcnc qedzoxm kjthdi cbwqep qtvu\n"
        "gio iqklmro noqablo bab jiqc rwebyg rqkloim wzmgs uunl amqs iwj\n"
        "snxj szobqt zcgvwv wiyqknu\n"
        "uto jteikwd cew gqsks hmvjtcy sach\n"
        "zpgl qnkoex amhufmr figns upv xezrl rjleak nwrna\n"
        "pzkvrdz dtonazj gtr gfxucuf lstjl lsjtl rgkope kzpdzrv lyptn zfxjys ttk\n"
        "ddxgm lumlgki jhv doft kok swy ckds swy ddxgm lbfbdv\n"
        "qfs rcufzgz iaiqw qfs qfs\n"
        "nvkbo sgv mquwb ritpye nbkov poex hraorm qrrr qdt qefl\n"
        "irxannd fiud ehyb ggx plqg pvvn uuptop tcvbm abuf bcfnmw\n"
        "qwya ukblz epmbfr vmlon yqwa\n"
        "hlo mmv vmm mvm\n"
        "svzpxun yugbbe sbbpxs dmy xspbbs zhpovyf fyovhzp cpbt pke\n"
        "zgk gft zybs zrgcoo ypu bue htgo\n"
        "xnesq srsx pkzaoh cfqzugh\n"
        "lntd nvxetbv clykjpd svmibpx evxtvnb yldkpjc\n"
        "jsqq tzwak hephg eqwczd ioisa yim tmdifn mceip\n"
        "kuwqz wzkqu zwchmj lfec uexne iztp llityt\n"
        "kvamkpc pvbryqh ion cwizjde gln kcpvmak pzzlw gnl\n"
        "ydeqf bfaab sydqhbp smsxdjr pynrs cqymt\n"
        "onb eiab bno nob\n"
        "mqslq scnelxv hyllrf scnelxv mqslq wmnbk\n"
        "pttu kubby lgop bbyuk gsk skg ikktlbb inbyvz\n"
        "xznvl zwtdj vbxdyd clhw\n"
        "hgy zudelp ickc drfjgn iyws xhc\n"
        "zzv wik iorhat qkb kjb lykdz vrce yjsjwj\n"
        "gyw xzgbi efus uuy\n"
        "hwcy ujdun bjjuvd jbdvju onnk xeyy mmp onkn qyzl\n"
        "jwfm ptjwrbl hhuv uolz adyweh qpj wxyogp igvnojq jmfw pqs fsnirby\n";

    int valid_count = 0;
    eachline(input, [&](std::string line) {
        int valid = 1;
        std::set<std::string> dict;
        eachword(line, [&](std::string word) {
            if (dict.find(word) != end(dict))
                valid = 0;
            dict.insert(word);
        });
        valid_count += valid;
    });

    assert(valid_count == 455);
    std::cout << "4.1 " << valid_count  << '\n';


    assert(valid_passphrase("abcde fghij"));
    assert(!valid_passphrase("abcde xyz ecdab"));
    assert(valid_passphrase("a ab abc abd abf abj"));
    assert(valid_passphrase("iiii oiii ooii oooi oooo"));
    assert(!valid_passphrase("oiii ioii iioi iiio"));

    valid_count = 0;
    eachline(input, [&](std::string line) {
        valid_count += valid_passphrase(line);
    });

    assert(valid_count == 186);
    std::cout << "4.2 " << valid_count  << '\n';
}

}


namespace day05 {

const std::vector<int> input{
    2, 1, -1, -2, 0, -1, 1, -1, -7, -6, 1, -4, -1, -12, -7, -3, -12,
    -5, -6, -13, -7, -17, -13, -11, -3, -7, -3, -2, -6, -27, -20, -15,
    -23, -23, -33, 0, -10, -35, -29, -6, -10, -5, -20, -38, -30, -38,
    -12, -23, 1, -4, -48, -45, -1, -30, -38, -27, -23, -53, -36, 0,
    -3, -45, -32, -39, -32, -46, -23, -40, -10, -54, -38, -37, -44,
    1, -56, -11, -74, -41, -73, -34, -31, -42, -49, -75, -8, -48, -49,
    -82, -21, -58, -40, -75, -66, -31, -34, -35, -52, -23, -56, -58,
    -60, -18, -34, -50, -27, -1, -3, -6, -70, -93, -36, -15, -1, -51,
    0, -110, -7, -7, -56, -14, -66, -93, -56, -100, -19, -54, -79,
    -81, -19, -112, -13, -24, -40, -90, -8, -10, -14, -27, -62, -45,
    -137, -53, -53, -89, -48, -86, -139, -91, -146, -109, -52, -6,
    -32, -6, -113, -78, -12, -4, -113, -42, -145, -23, -64, -97, -98,
    -77, -155, -133, -65, -64, -59, -164, -155, -27, -65, -57, -133,
    -140, -95, -104, -46, -16, -139, -55, -15, -26, -63, -141, -93,
    -146, -51, -104, -84, -82, -87, -149, -19, -77, -154, -118, -96,
    -117, -96, -140, -47, -188, -158, -141, -192, -63, -58, -191,
    -63, -52, -135, -142, -109, -42, -134, -4, -11, -135, -13, -24,
    -39, -4, -183, -158, -25, -136, -35, -49, -54, -78, -18, -92, -19,
    -142, -40, -237, -119, -147, -198, -132, -73, -238, -106, -82, -51, 
    -72, -9, -44, -151, -164, -35, -74, -252, -219, -40, -154, -229, 
    -169, -130, -238, -64, -171, -174, -161, -67, -205, -160, -112, -191, 
    1, -60, -147, 0, -43, -67, -190, -256, -66, -189, -76, -86, -91, -243, 
    -10, -142, -163, -52, -112, -162, -169, -269, -98, -188, -282, -212, 
    -286, -28, -33, -6, -114, -89, -237, -90, -95, -202, -266, -72, -215, 
    -50, -52, -78, -286, -32, -235, -7, -56, -194, -6, -32, -73, -48, -77, 
    -69, -43, -279, -236, -79, -286, -105, -295, -61, -320, -130, -99, 
    -90, -238, -294, -120, -9, -302, -327, -165, -267, -228, -250, -153, 
    -28, -126, -187, -138, -163, -140, -26, -217, -197, -180, -338, -39, 
    -71, -6, -56, -151, -272, -276, -246, -189, -183, -38, -249, 0, -185, 
    -8, -193, -213, -296, -3, -340, -76, -97, -87, -1, -172, -235, -38, 
    -274, -169, -70, -162, -320, -78, -222, -69, -222, -219, -213, -313, 
    -179, -182, -253, -135, -206, -54, -167, -101, -397, -367, -54, -143, 
    -147, -156, -293, -144, -47, -254, -169, -307, -223, -339, -398, -414, 
    -23, -107, -235, -302, -321, -111, -167, -345, -55, -64, -315, -266, 
    -191, -265, -248, -426, -47, -409, -212, -212, -401, -87, -389, -146, 
    -97, -65, -286, -447, -168, -26, -371, -153, -297, -285, -164, -215, 
    -336, -14, -416, -278, -233, -234, -392, -113, -80, -237, -342, -85, 
    0, -145, -75, -101, -88, -292, -285, -344, -254, -47, -310, -227, -60, 
    -320, -102, -364, -131, -338, -17, -239, -124, -266, -380, -421, -217, 
    -311, -287, -233, -223, -242, -16, -326, -407, -482, -470, -247, -365, 
    -75, -278, -44, -404, -195, -348, -81, -309, -181, -176, -97, -274, 
    -204, -485, -458, -364, -22, -89, -448, -235, -53, -50, -510, -89, 
    -114, -158, -199, -189, -204, -528, -278, -274, -149, -208, -485, -313, 
    -325, -246, -173, -478, -164, -153, -76, -407, -447, -109, -334, -199, 
    -50, -361, -449, -338, -409, -66, -282, -510, -288, -380, -562, -543, 
    -534, -500, -288, -526, -439, -142, -284, -421, -30, -243, -185, -433, 
    -326, -102, -540, -391, -197, -580, -305, -436, -559, 2, -30, -204, 
    -97, -204, -207, -79, -329, -157, -284, -581, -182, -458, -232, -111, 
    -352, -601, 0, -245, -292, -167, -549, -456, -277, -63, -104, -493, 
    -585, -369, -121, -122, -180, -466, -509, -405, -53, -555, -454, 
    -549, -486, -80, -463, -385, -538, -274, -75, -90, -500, -434, -167, 
    -142, -587, -92, -182, -95, -205, -49, -574, -352, -638, -204, -25, 
    -375, -456, -400, -572, -37, -151, -81, 2, -19, -579, -106, -344, 
    -339, -188, -517, -12, -403, -623, -619, -429, -53, -227, -11, -548, 
    -426, -115, -481, -425, -9, -43, -209, -145, -168, -241, -331, -521, 
    -77, -642, -397, -37, -98, -333, -281, -162, -361, -119, -696, -440, 
    -663, -347, -295, -692, -32, -331, -623, -275, -646, -517, -16, -193, 
    -537, -403, -75, -607, -74, -393, -333, -665, -448, -419, -119, -213, 
    -635, -668, -178, -46, -175, -537, -160, -467, -271, -594, -240, -262, 
    -666, -205, -48, -319, -738, -240, -697, -685, -711, -98, -134, -28, 
    -731, -317, -319, -288, -236, -425, -401, -625, -638, -496, -23, -751, 
    -643, -382, -717, -269, -275, -764, -672, -758, -605, -530, -244, -526, 
    -357, -175, -667, -282, -551, -642, -83, -116, -751, -381, -447, -266, 
    -297, -88, -575, -246, -189, -662, -450, -91, -471, -209, -609, -151, 
    -630, -345, -625, -743, -377, -789, -56, -370, -250, -661, -792, -560, 
    -585, -231, -673, -725, -194, -317, -455, -234, -282, -516, -784, -2, 
    -652, -427, -31, -755, -527, -725, -47, -606, -210, -172, -773, -819, 
    -636, -348, -376, -700, -727, -156, -574, -414, -34, -439, -413, -604, 
    -648, -381, -529, -82, -736, -816, -595, -352, -417, -836, -691, -660, 
    -464, -314, -748, -698, -49, -97, -721, -294, -441, -446, -415, -187, 
    -212, -506, -550, -131, -231, -637, -334, -853, -383, -407, -219, -518, 
    -743, -83, -773, -162, -570, -611, -574, -355, -56, -775, -663, -131, 
    -357, -560, -335, -390, -667, -516, -897, -752, -786, -246, -893, -693, 
    -692, -647, -422, -361, -148, -231, -775, -62, -404, -783, -387, -559, 
    -703, -403, -776, -588, -633, -831, -779, -23, -216, -381, -287, -517, 
    -402, -814, -756, -646, -535, -270, -282, -157, -367, -356, -925, -333, 
    -375, -469, -931, -347, -455, -942, -815, -311, -690, -65, -691, -64, 
    -361, -409, -886, -488, -303, -806, -73, -653, -356, -71, -523, -370, 
    -685, -526, -528, -519, -179, -762, -652, -388, -568, -296, -601, -822, 
    -656, -258, -304, -670, -731, -352, -82, 0, -116, -294, -652, -702, 
    -933, -12, -348, -15, -662, -311, -695, -357, -872, -847, -791, -129, 
    -574, -281, -42, -626, -36, -60, -864, -871, -246, -943, -500, -253, 
    -684, -545, -1011, -330, -666, -468, -780, -596, -872, -812, -924, 
    -836, -379, -528, -464, -99, -675, -317, -58, -641, -590, -227, -296, 
    -303, -798, -39, -824, -300, -469, -251, -182, -40, -115, -997, -572, 
    -743, -13, -557, -542, -832, -884, -385, -224, -932, -757, -405, 
    -690, -745, -1008, -657, -846, -565, -508, -792, -245, -298, -793, -278};


int jumps(std::vector<int> tbl)
{
    int steps = 1;

    int pc = 0;
    for (int pc = 0; ; ++steps) {
        int offset = tbl[pc]++;
        if (pc + offset < 0 || pc + offset >= static_cast<int>(tbl.size()))
            break;
        pc += offset;
    }

    return steps;
}

uint64_t jumps2(std::vector<int> tbl)
{
    uint64_t steps = 1;

    int pc = 0;
    for (int pc = 0; ; ++steps) {
        int offset = tbl[pc];
        tbl[pc] += (offset >= 3) ? -1 : +1;
        if (pc + offset < 0 || pc + offset >= static_cast<int>(tbl.size()))
            break;
        pc += offset;
    }

    return steps;
}

void run()
{

    /*
    (0) 3  0  1  -3  - before we have taken any steps.
    (1) 3  0  1  -3  - jump with offset 0 (that is, don't jump at all). Fortunately, the instruction is then incremented to 1.
     2 (3) 0  1  -3  - step forward because of the instruction we just modified. The first instruction is incremented again, now to 2.
     2  4  0  1 (-3) - jump all the way to the end; leave a 4 behind.
     2 (4) 0  1  -2  - go back to where we just were; increment -3 to -2.
     2  5  0  1  -2  - jump 4 steps forward, escaping the maze.
     In this example, the exit is reached in 5 steps.
     */
    const std::vector<int> test{0, 3, 0, 1, -3};
    assert(jumps(test) == 5);

    const int steps = jumps(input);
    assert(steps == 358309);
    std::cout << "5.1 " << steps  << '\n';

    assert(jumps2(test) == 10);
    const uint64_t steps2 = jumps2(input);
    assert(steps2 == 28178177);
    std::cout << "5.2 " << steps2  << '\n';
}

}


namespace day06 {

const std::vector<int> input{
    0,	5,	10,	0,	11,	14,	13,	4,	11,	8,	8,	7,	1,	4,	12,	11};


int next(int size, int i)
{
    ++i;
    if (i >= size)
        i = 0;
    return i;
}

int redistribution_cycles(std::vector<int> banks)
{
    int cycle_count = 0;

    const int num_banks = static_cast<int>(banks.size());
    std::set<std::vector<int>> state;
    do {
        state.insert(banks);
        ++cycle_count;

        int start = 0;
        int high = 0;
        for (int i = 0; i < num_banks; ++i)
            if (banks[i] > high) {
                high = banks[i];
                start = i;
            }

        int blocks = banks[start];
        banks[start] = 0;
        for (int i = next(num_banks, start); blocks != 0; i = next(num_banks, i)) {
            --blocks;
            ++banks[i];
        }
    } while (state.find(banks) == end(state));

    return cycle_count;
}


int redistribution_cycles2(std::vector<int> banks)
{
    int cycle_index = 0;

    const int num_banks = static_cast<int>(banks.size());
    std::map<std::vector<int>, int> state;
    do {
        state[banks] = cycle_index++;

        int start = 0;
        int high = 0;
        for (int i = 0; i < num_banks; ++i)
            if (banks[i] > high) {
                high = banks[i];
                start = i;
            }

        int blocks = banks[start];
        banks[start] = 0;
        for (int i = next(num_banks, start); blocks != 0; i = next(num_banks, i)) {
            --blocks;
            ++banks[i];
        }
    } while (state.find(banks) == end(state));

    return cycle_index - state[banks];
}


void run()
{
    std::set<std::vector<int>> x;
    x.insert({1,2,3});
    x.insert({4,5,6});
    assert(x.find({1,2,3}) != end(x));
    assert(x.find({4,5,6}) != end(x));
    assert(x.find({1,2,4}) == end(x));

    const std::vector<int> test{0, 2, 7, 0};
    assert(redistribution_cycles(test) == 5);

    const int cycle_count = redistribution_cycles(input);
    assert(cycle_count == 7864);
    std::cout << "6.1 " << cycle_count  << '\n';

    assert(redistribution_cycles2(test) == 4);
    const int cycle_count2 = redistribution_cycles2(input);
    assert(cycle_count2 == 1695);
    std::cout << "6.2 " << cycle_count2  << '\n';
}

}


namespace day07 {

const char * input = {
    "xsddbi (61)\n"
    "nqtowev (11)\n"
    "xwohr (82)\n"
    "flejt (36)\n"
    "idwpug (54)\n"
    "uoxzkp (51)\n"
    "choeijs (54)\n"
    "gmsjkn (65)\n"
    "txszqu (687) -> mvjqmad, lwqlyjq, jlgnsu\n"
    "zhlfdac (15)\n"
    "htouwcr (74)\n"
    "vlbsr (56)\n"
    "titbn (9)\n"
    "bvrpb (86)\n"
    "wuwjp (54)\n"
    "umnqkb (160) -> nbrvl, bcmbao, vfimqtl\n"
    "uwnml (29)\n"
    "cdvhmy (42)\n"
    "xghhu (306) -> molth, atqewc\n"
    "vcvayah (71)\n"
    "fujwb (187) -> tyjyc, xyemll\n"
    "zqnjd (91) -> jxsmuey, uelnii, vcwezm, uxnwtp\n"
    "wphtnvm (72)\n"
    "xgihtsx (15)\n"
    "fwvvidu (80)\n"
    "lonwb (1656) -> rydrp, mgyixhn, cjhtxo\n"
    "qyasuw (41)\n"
    "vbvug (6)\n"
    "mkrjamh (154) -> ecbog, owaebx\n"
    "ghvpg (98)\n"
    "eazvkxv (66)\n"
    "jguufio (61)\n"
    "udpcyt (71)\n"
    "xerbuu (38)\n"
    "sxzpils (70)\n"
    "looigzn (10)\n"
    "znmumx (77)\n"
    "uxzwwe (67)\n"
    "wuegrv (99)\n"
    "owttcz (91)\n"
    "vkhazkn (37) -> oactn, ftxif, rxlbou, bkfav\n"
    "rddnfg (10) -> mvgmbru, zlazoqs\n"
    "zzsqfm (99)\n"
    "fhjzpjw (19)\n"
    "zwxwfin (50)\n"
    "ocdzc (26)\n"
    "cohps (52)\n"
    "dxhrpq (46)\n"
    "yeheld (55)\n"
    "ekxczvo (81)\n"
    "pxlzcx (589) -> vjvit, cnblx, bwiqe, pjsbxvk, ipqjxa, zkikz\n"
    "offkzc (95) -> wymlvix, felrwte, bzublv\n"
    "bavyg (22) -> szszezd, lurhq, ltncvl, fmwvok, frikrv, tumwln, xjtujzp\n"
    "awjwff (18)\n"
    "sjhwgq (8316) -> ydqgvnf, oztasey, qkmkwgl\n"
    "vmyrdkl (53)\n"
    "mzrwaa (48)\n"
    "njqemt (30)\n"
    "objssr (91) -> xujmi, oqihtt\n"
    "bcpbvya (75)\n"
    "fqayb (69)\n"
    "vwksn (19) -> zwxxii, owttcz\n"
    "czmzol (145) -> qzayss, ufrrrzi\n"
    "inija (25)\n"
    "eppufdw (555) -> brwsjee, laoouso, jgfcyze\n"
    "mmtzk (39) -> utispep, onkhx\n"
    "zoofu (129) -> cyczt, qargs\n"
    "msryw (260)\n"
    "etvpko (18)\n"
    "wxudgdd (84)\n"
    "ymkax (45) -> znmumx, hnjuqgw\n"
    "uxbjym (87)\n"
    "msskm (69)\n"
    "nmtia (75)\n"
    "jawbtmo (46)\n"
    "bpelccj (187) -> ctzhawr, qhldpg\n"
    "dbexmj (365) -> bijprk, iotkxfd\n"
    "bxcdldt (16)\n"
    "fhdqcbx (25) -> gefut, mulybo\n"
    "iunkpe (15)\n"
    "yzvqo (80)\n"
    "fbgguv (57) -> bkomu, tynxlau, sfruur, zxvbb, khupkt, xkntkvz\n"
    "yaripcu (8)\n"
    "acfmyv (79)\n"
    "sohuv (18)\n"
    "aahhxau (233) -> rbauxvx, neliq\n"
    "yuhmnjs (98)\n"
    "xpzpv (206) -> mxtxm, kgzyk, yzpaxlz, vfxqcbq, lcgtwj\n"
    "ovhhkoc (52)\n"
    "stwubkv (70) -> uzzeydh, zknpmnc\n"
    "otbxl (54)\n"
    "bfroq (39)\n"
    "nkbmoin (341) -> vgqmfj, weygson, knbems, gdmlk, ecfrqpl, tbaai, sfohocq\n"
    "twazofk (258) -> dntwqr, vugavk\n"
    "venvbai (32)\n"
    "pcqpqjk (38)\n"
    "apqby (37) -> xkzlyvh, vlsjsgg\n"
    "tgsicj (59)\n"
    "rsvixyg (32)\n"
    "whjcp (245)\n"
    "rmnkgss (22)\n"
    "zbmwego (55)\n"
    "lptmne (17) -> fkjlcz, jinwsas, qnevjto, wfjks\n"
    "rtyegs (76) -> nhbbd, yqqun\n"
    "cavlg (1148) -> lsaroxx, evkau, gldgrng\n"
    "kqswas (504) -> ntcddy, bwqmns, vtvsd, oxoqy\n"
    "tmvfp (46)\n"
    "dlhyzjw (79)\n"
    "xsfwcgq (657) -> inknun, seihhya, qrlhp, bchtcht, rswqvx\n"
    "ekleund (68)\n"
    "rihlj (72)\n"
    "oldrtya (66)\n"
    "yiqnfd (62)\n"
    "sgpiiir (14)\n"
    "vbojbp (66)\n"
    "qnscqms (197) -> mernsee, ubjuhxp, mlfxnna\n"
    "vfxzkq (660) -> ukrqfm, pnsvthy, qdcos\n"
    "kkeuh (273) -> urfhlf, hjtkb\n"
    "sakhif (30)\n"
    "yrdhq (71)\n"
    "ckcjr (50) -> owgsk, vdnphf\n"
    "ndvdj (10)\n"
    "zzcqptv (87)\n"
    "aemyrqj (23)\n"
    "vbauj (49)\n"
    "rcumpgx (18)\n"
    "ijyhvsj (25)\n"
    "gazaoty (83)\n"
    "lugwl (228)\n"
    "msrrlv (90)\n"
    "enxbya (19)\n"
    "wlyzbz (99)\n"
    "gmrqpdk (40)\n"
    "gefut (75)\n"
    "bafnaij (57)\n"
    "jgfcyze (166) -> ziqyhi, wrwgm, hdikur, bmqhrtg\n"
    "rcmyfr (281)\n"
    "pohdy (87) -> frcqooy, idhvksi\n"
    "wkfjzs (81)\n"
    "dcgphc (16)\n"
    "bgqvm (38)\n"
    "ltgnnr (87)\n"
    "xjtujzp (1565) -> soryrk, zkvopb, xufneyr\n"
    "idhvksi (69)\n"
    "yjnrjde (65)\n"
    "lfykdub (61)\n"
    "dnjydir (41)\n"
    "ifgfg (197) -> jcbgta, aemyrqj\n"
    "grlofut (23)\n"
    "tjaqrw (96)\n"
    "gjgcvyp (85)\n"
    "kwavcf (254) -> vmpmig, djeee\n"
    "mdnqs (101) -> tpmhs, essvr\n"
    "gqlyhql (159) -> uwrhuw, ypanow\n"
    "vjzfc (25)\n"
    "guauivo (42) -> puvhc, bjcsjrr, ccjtpv, ibwve, evbvdgl, stwubkv, kwxpnrs\n"
    "pbohgz (74) -> sbfiv, igbhyk, rhxcyd\n"
    "bkomu (42437) -> krbpgmk, ekgbf, yqlxeb, ogyiesm, poypmax\n"
    "yjoyyvl (55) -> sjioze, nigkvxl, itjxq\n"
    "efobdsd (218) -> yqnso, glqspl\n"
    "zxvbb (56366) -> fvkxwt, xlanm, gxitq\n"
    "cvrga (47) -> vagjk, ghvpg\n"
    "mwrnosj (52)\n"
    "dxffr (15)\n"
    "dcsxekv (41)\n"
    "kbmse (68)\n"
    "tqyldbt (59)\n"
    "nvtyg (31)\n"
    "jnzqvia (67) -> divak, cmgvs\n"
    "rhxcyd (44)\n"
    "hnjuqgw (77)\n"
    "vdnphf (89)\n"
    "qqnywdg (160) -> lrjnzf, luhxcq, whgpim\n"
    "sfizdf (1053) -> aahhxau, shiiodm, cvnfak, whjcp\n"
    "zdawjkr (34)\n"
    "tracdgp (27)\n"
    "tcvgl (305) -> ljfvbjd, bafnaij\n"
    "iuwwa (42)\n"
    "iekwfia (52)\n"
    "odoxr (72)\n"
    "uravet (102) -> hzzxjxa, mvdzfo\n"
    "jvnuwap (66)\n"
    "kjdjdr (76) -> kpdmptf, hsqhwef\n"
    "vycgaoz (82) -> jqulm, ziwlgdb\n"
    "ifdkle (202)\n"
    "gtpyffj (812) -> kcpwmyz, emkzxk, hwuabde, efgqua\n"
    "oxoqy (17) -> lktbqq, zukio, bcpbvya\n"
    "kfngejn (49)\n"
    "anhjp (75)\n"
    "xwwzp (14358) -> lonfrp, eppufdw, nmxqs\n"
    "wcpyi (205)\n"
    "wzxqipp (88)\n"
    "ekgbf (6702) -> bckbud, fzzlnwi, cvprip\n"
    "ziwlgdb (63)\n"
    "bxqjg (70)\n"
    "bverp (49)\n"
    "rlgbvvj (13)\n"
    "sqvxf (37)\n"
    "ltncvl (977) -> sktewq, hydeeqe, ibdjxl\n"
    "fxqng (90)\n"
    "jcdmhvd (157) -> twgrfm, dxhrpq\n"
    "kpgatn (41)\n"
    "znpvlac (97) -> vmyrdkl, aideelj\n"
    "vifbi (634) -> rkwkwd, onqax, cfrcco, onamlmy, zoofu, vwosnfn\n"
    "gezqw (12)\n"
    "hagrq (97) -> fhecgzf, mefajk, uyrxc, gdclwzu\n"
    "gdclwzu (60)\n"
    "sczyp (19)\n"
    "cvlkltp (151) -> guiej, vffqp\n"
    "fimqsn (125) -> ehvxt, xyoiv, mikast\n"
    "lktbqq (75)\n"
    "tyjyc (55)\n"
    "xoqvvx (18) -> xawfk, ojrjqv\n"
    "bcmbao (89)\n"
    "qntpdh (93)\n"
    "iieico (12)\n"
    "modms (37)\n"
    "xwwfi (82) -> cpjkea, hsexbak, dxaemlq, wlyzbz\n"
    "xxoil (23)\n"
    "uelnii (82)\n"
    "shiiodm (53) -> hclea, nrduy\n"
    "hqwkq (42)\n"
    "twgrfm (46)\n"
    "yrozpm (246) -> btukw, fbyju\n"
    "onqax (301) -> vtlvs, ccnpjdf\n"
    "klhfca (81)\n"
    "lvcsn (95)\n"
    "jpcseag (92)\n"
    "tgwgno (202) -> yyyub, ofcyw\n"
    "ztjquwi (545) -> ptawnqq, ziprwty, yzfzbw, hpqux, baaqr, bwugxhi\n"
    "ealyedu (71)\n"
    "debir (48)\n"
    "ppossv (51)\n"
    "kzxyyd (62)\n"
    "bchtcht (185) -> rsvixyg, cppdkv\n"
    "ndeop (9)\n"
    "htujh (695) -> nzhnurq, btbnj, ghsxqq\n"
    "lkwogh (53)\n"
    "ofyuao (159) -> llhiw, nbjpcc\n"
    "vxlypal (9)\n"
    "dvipr (67) -> udnmqte, osnjzpt, swujbg\n"
    "ybnehoi (50) -> hatmr, alkizae\n"
    "xkntkvz (44502) -> lwugjj, cstmu, rsjffj, pxlzcx, jtmuv\n"
    "fhvyhk (252) -> boqgjn, rzzezfx\n"
    "krmbsc (47)\n"
    "jkymeqw (26)\n"
    "xjypx (70)\n"
    "jytapdu (15) -> vqvwkm, jpcseag, kgkpfg\n"
    "btrepl (15)\n"
    "umnkslz (13)\n"
    "lxbsif (72)\n"
    "adunt (71)\n"
    "cupeghk (67)\n"
    "xcckt (7)\n"
    "mutwmaa (39)\n"
    "qmpncds (39)\n"
    "ypanow (88)\n"
    "zhhhntj (51)\n"
    "tcqnso (85)\n"
    "uakcbox (68)\n"
    "sckgsn (38)\n"
    "bgpjb (136) -> aqaems, jkymeqw\n"
    "gxitq (83) -> wshlljj, krpda, aasxby, ywhjz, stnnf, nfkmi\n"
    "ulehitr (187) -> knrtys, mnfep\n"
    "galojia (25)\n"
    "pjxauhw (61)\n"
    "wvhvw (229) -> xcckt, duzgl\n"
    "cpjkea (99)\n"
    "jqulm (63)\n"
    "gpqhjv (20) -> wzxqipp, ykxnd, dhsopiv\n"
    "ipqjxa (51) -> gsmcgor, inlcow, hdmcpq, xhmornc, lisfhnn\n"
    "ofwtjhw (38)\n"
    "pkceuqw (62) -> isqxwp, evkrnfo, pcqpqjk\n"
    "hmnvh (97)\n"
    "cxcah (75)\n"
    "fkjof (90)\n"
    "iinxvw (14)\n"
    "ckypedd (61)\n"
    "vxwobup (543) -> sejkvk, olrdlw, hfxsib\n"
    "hpqux (196) -> ocdzc, xlvjz\n"
    "gyuyu (173) -> xfurlrr, etlce\n"
    "rffwau (96)\n"
    "bfulyh (154) -> tjuqz, tzqdwe, ayeqoz\n"
    "llhiw (88)\n"
    "vmsmdqx (72)\n"
    "aasxby (832) -> lvcdsgp, dhejgd, nzvpgv\n"
    "qlkjhsi (25)\n"
    "chhhge (34)\n"
    "rveuz (18)\n"
    "cmbnwse (112) -> jphmpr, tlkhxww\n"
    "ppqdnd (175)\n"
    "szvty (18)\n"
    "crbcsqt (382) -> oakbrw, dswjpxm\n"
    "xqxgd (76)\n"
    "dxddn (12)\n"
    "usitmiz (81)\n"
    "vqrtnp (44)\n"
    "axkhzf (94)\n"
    "tzszs (299) -> jieijuo, ndeop\n"
    "frjtwx (94)\n"
    "tzqdwe (32)\n"
    "sjioze (46)\n"
    "yzpaxlz (216) -> heqbpd, dphmg\n"
    "lewbxa (43)\n"
    "knbems (173) -> looigzn, qdkrr\n"
    "bwqmns (210) -> dcgphc, wwzli\n"
    "vtwdqkd (61) -> vcvayah, wyhnmbs\n"
    "owgsk (89)\n"
    "dpfvy (54)\n"
    "qongfb (48)\n"
    "qilhudr (125) -> qbcar, wuwjp, umxurvd\n"
    "aahqtsf (1755) -> hfhswyd, znpvlac, bruqu\n"
    "dxaemlq (99)\n"
    "gybikf (185) -> uwnml, noqjuo\n"
    "vjvit (194) -> jdhewio, wwhlo, crbcsqt\n"
    "zkikz (194) -> ttqpi, ifdkle, qdyzunw, wkcrce, jcezw, qeiijk\n"
    "wphgd (7)\n"
    "nmxqs (180) -> sftqzaf, gyuyu, tkvmtol, vwksn, doppnr\n"
    "bpgdb (190) -> jxpixqi, kygcziz\n"
    "tmigcw (151) -> gmsjkn, njmlk\n"
    "lodcj (54)\n"
    "loxjzpo (59)\n"
    "fxfznc (32)\n"
    "hwuabde (207) -> mvamo, bverp\n"
    "ixroc (98)\n"
    "wdzhfmw (126) -> galojia, ibyrsdo\n"
    "bznst (20)\n"
    "dkoike (123) -> wuckr, mfbnys, gmrqpdk\n"
    "atyaqz (112) -> asmysiq, paoitb, okpdcz\n"
    "bsfsayz (13)\n"
    "ffhxi (15)\n"
    "rgkrl (85)\n"
    "fhecgzf (60)\n"
    "lwugjj (361) -> hykxm, hechfb, edtkfvv, lonwb\n"
    "qtraszq (13)\n"
    "qargs (95)\n"
    "adwir (18)\n"
    "bnmshvm (145) -> vfmlyg, ychjmik\n"
    "isqxwp (38)\n"
    "yblsbf (83)\n"
    "azzysl (36) -> anhjp, ixnlvyo, mmndzs, alaug\n"
    "ysdqkw (87)\n"
    "olevfy (158) -> wuipwl, etvpko, bavaf\n"
    "tvcxl (25) -> vlmzodk, vbojbp, oldrtya\n"
    "fhyvz (40)\n"
    "hzfwtzf (75)\n"
    "gdmlk (5) -> bgavnd, iqpcu\n"
    "utojr (82) -> nuytv, frjtwx, guurpo\n"
    "kcpwmyz (97) -> oykqvif, ukrjos, mwrnosj, bdjlzf\n"
    "qvndh (115) -> fyeuhqh, kmbrqv, kgqgct, qtraszq\n"
    "fvjcbib (98)\n"
    "ziiijv (85)\n"
    "lbnenyf (75) -> tdhxy, ozlqcn\n"
    "nbwkld (54)\n"
    "blpjnzf (123) -> gapzarg, syxkp\n"
    "jhruwih (84)\n"
    "ecbog (27)\n"
    "ccqldu (46)\n"
    "izyxppl (58)\n"
    "lfwru (177) -> smiucuf, libtrl\n"
    "cvnfak (123) -> lfykdub, yxqaa\n"
    "jwjrj (89)\n"
    "ytbyct (73) -> yaehsu, cxcah\n"
    "oqihtt (68)\n"
    "mvjqmad (359) -> swaxyxe, perbvgz\n"
    "vahnoue (42)\n"
    "egrimlf (42)\n"
    "uewchd (1998) -> oqqme, vaeeqvi\n"
    "hbtur (295) -> mgqkhic, jkvgvz\n"
    "qekpce (78)\n"
    "anehvd (75) -> frezf, wvdoa\n"
    "laeaf (38)\n"
    "hipfszh (149) -> dxavaum, qkapxbc, adwir\n"
    "parvx (15)\n"
    "ayeqoz (32)\n"
    "weunegg (85)\n"
    "cbbtbz (85)\n"
    "fkjwn (67)\n"
    "takxgz (49)\n"
    "heqbpd (6)\n"
    "yxpnzkn (212) -> dxavw, nxpozme, wdjcb\n"
    "vkwsodp (38)\n"
    "asmysiq (51)\n"
    "ilvblzm (85)\n"
    "laohhtn (86)\n"
    "onoyb (86)\n"
    "sfwaimh (24)\n"
    "grtrt (96)\n"
    "oekhu (40)\n"
    "jxqzmuv (7)\n"
    "vtlvs (9)\n"
    "jjdmu (84)\n"
    "qzobjfo (158) -> vetsll, utsfqn, dcsxekv\n"
    "uwrfay (60)\n"
    "guurpo (94)\n"
    "kpnxkyy (32)\n"
    "aqugisv (965) -> rddnfg, qozmho, pbohgz, lupyc\n"
    "dswjpxm (11)\n"
    "smiucuf (53)\n"
    "mfamq (74)\n"
    "agfnncm (95)\n"
    "qshoazt (1737) -> ockzlpp, yeheld, judfhye\n"
    "wngzh (9094) -> guauivo, aiwvi, vxruziw, ikqijv\n"
    "hawmd (40)\n"
    "kxkwxoj (32) -> pyvwl, akdffhk\n"
    "qdpoyl (4734) -> aahqtsf, lnontej, lfiteup, oaopxo\n"
    "ftkflbo (27)\n"
    "ukrjos (52)\n"
    "fdzqz (70)\n"
    "dvncmy (1046) -> hzfwtzf, nmtia, ygiyze, zuquy\n"
    "gsfnr (96)\n"
    "cprbzvp (28)\n"
    "tyywgp (57)\n"
    "gsmocx (118) -> krmbsc, ywmif\n"
    "laoouso (122) -> xvdkt, eogzpga\n"
    "yzfzbw (178) -> vjevs, paqihg\n"
    "cxhuwiw (46)\n"
    "vfimqtl (89)\n"
    "dkcqdx (132) -> wemjk, kyuneoo\n"
    "dszip (73) -> vzbpn, xqxgd\n"
    "chljtta (157) -> dpfvy, nbwkld\n"
    "zzcagx (165) -> wuvmf, nrvsqf\n"
    "xfglmz (740) -> nrlhen, rfkcylj, ymkax\n"
    "pnsvthy (103) -> cadasac, rpxmv, azkmt\n"
    "xokmont (84)\n"
    "divak (77)\n"
    "lonfrp (60) -> pohdy, bnmshvm, oheank, qwlze, dszip\n"
    "yngqiv (236) -> cayigxg, ixomyeb\n"
    "lfiteup (1188) -> qnsqwm, qdpnnex, cmbnwse, onaatvy\n"
    "mefajk (60)\n"
    "eqbwx (23)\n"
    "zuoczei (64) -> ismrc, dbexmj, oeqqj\n"
    "kygcziz (14)\n"
    "nwxyrtn (87) -> kpgatn, egcjfjo\n"
    "loljfo (10)\n"
    "bruqu (17) -> uwylbft, qntpdh\n"
    "wohvpbn (67)\n"
    "qgvqg (315) -> iekwfia, qhrxvzj\n"
    "wwhlo (36) -> hcyjfzz, dbuqsj, latmzh, geztlsi\n"
    "oheank (225)\n"
    "ujpgmwm (50)\n"
    "ndgzf (37)\n"
    "rgzrnnl (52)\n"
    "vgjgz (24)\n"
    "fvwll (147) -> axkhzf, mqpbpgq\n"
    "iqtemv (69)\n"
    "yfrmup (6)\n"
    "rzzezfx (56)\n"
    "qkpaxtt (76) -> wohvpbn, fkjwn\n"
    "tjuqz (32)\n"
    "ztfhz (8)\n"
    "wayftw (17)\n"
    "qbcar (54)\n"
    "neliq (6)\n"
    "yxqaa (61)\n"
    "lupyc (114) -> rsqihar, moivx, xxoil, vggstn\n"
    "dlkhb (56)\n"
    "uctlk (36)\n"
    "ssyfvrj (56)\n"
    "ibwve (36) -> zfmas, sddvn\n"
    "brwsjee (46) -> uqpprye, ejovcx\n"
    "wgcgdvt (13)\n"
    "ndhitxf (141) -> uoxzkp, ppossv\n"
    "seblnmz (31)\n"
    "osnjzpt (36)\n"
    "cihzh (85)\n"
    "dtkdwp (42)\n"
    "xmogef (10)\n"
    "btbnj (186) -> jxqzmuv, tycgm, xewbn, rjayavy\n"
    "gcrbrn (90)\n"
    "jiaho (7)\n"
    "czuwoe (325) -> hxzjg, cfiyqh\n"
    "hxzjg (6)\n"
    "zfshwt (80)\n"
    "frycrnj (44)\n"
    "owcwvug (85)\n"
    "cnsbonb (64)\n"
    "gwudp (77)\n"
    "xsjbc (89)\n"
    "fvkxwt (7466) -> zuoczei, gjwzw, qsyocuq\n"
    "whgpim (68)\n"
    "tzhoqw (84)\n"
    "bbbms (56)\n"
    "ubhlb (350)\n"
    "zzbzwdm (34)\n"
    "cwixiq (35) -> jvnuwap, hkweu\n"
    "ecytwe (249)\n"
    "ckombz (80)\n"
    "bzbfpkb (156) -> zhrsp, rgzrnnl\n"
    "vfkjif (42)\n"
    "oinyx (42)\n"
    "necqpdx (48)\n"
    "qpden (7)\n"
    "ruabtb (88) -> xvwio, lhbwbik\n"
    "btukw (52)\n"
    "rkofvt (1150) -> gkqgru, xoqvvx, iqler, dhaxwd\n"
    "utyrttu (89) -> wjaocmd, xwohr, rxflxr\n"
    "nnnkplx (23)\n"
    "kgzyk (90) -> iqymm, asrwh\n"
    "ukrqfm (96) -> yuiicxp, qjnhwpq\n"
    "aulgwyb (852) -> rhjxbx, weguko, ppqdnd, csmul, srscbv, kriwb\n"
    "jppsaym (95)\n"
    "vfmlyg (40)\n"
    "weygson (129) -> kpnxkyy, wdcltyl\n"
    "vzbpn (76)\n"
    "foibc (12)\n"
    "hsqhwef (48)\n"
    "hpgwq (18)\n"
    "crothf (108) -> pwfdn, hawmd\n"
    "nfmicyi (65)\n"
    "cjeauo (97)\n"
    "ptawnqq (65) -> kcjwb, bvknwgq, xsddbi\n"
    "oicysoz (33) -> awgjkiv, ndszsz\n"
    "rdvtzr (11)\n"
    "swqym (72)\n"
    "cppdkv (32)\n"
    "uuapl (38)\n"
    "yriibfp (27)\n"
    "nfklqi (22)\n"
    "xhmornc (148) -> dnjydir, icnav, qyasuw\n"
    "lhbwbik (72)\n"
    "wshlljj (1198) -> ojqqw, olevfy, iwiaa\n"
    "mjtuzfr (23) -> ukaflr, zzsqfm\n"
    "zxavxe (34) -> swqym, yreenth, ubvheu\n"
    "pxhwr (7)\n"
    "wyhnmbs (71)\n"
    "nigkvxl (46)\n"
    "perbvgz (23)\n"
    "kyuneoo (64)\n"
    "djeee (15)\n"
    "lkfdr (85)\n"
    "evkau (63)\n"
    "tridq (59)\n"
    "eepdcje (37) -> cxhuwiw, damyp, tmvfp\n"
    "nzdbs (50)\n"
    "ejnqcb (74)\n"
    "dfzwcc (74)\n"
    "efgqua (62) -> klhfca, usitmiz, aceqrlu\n"
    "mqpbpgq (94)\n"
    "boqgjn (56)\n"
    "bxkxp (81)\n"
    "vbzwk (48)\n"
    "gldgrng (63)\n"
    "kgkpfg (92)\n"
    "jutgp (84)\n"
    "zouxmz (48)\n"
    "uktpcar (155) -> ebwgi, pozpmyh\n"
    "dhaxwd (167) -> pxhwr, qxyramq, wphgd\n"
    "yreenth (72)\n"
    "iciuuh (63) -> gslii, fqaefy, hwuwj\n"
    "xifaq (38)\n"
    "oqdukh (56)\n"
    "hasyyr (24)\n"
    "khzbxke (174) -> ftkflbo, tracdgp\n"
    "zoryb (73) -> eusnn, exqkey\n"
    "ebnqn (9)\n"
    "pncxkcd (156) -> izpxjp, myckhlw\n"
    "qqmlvk (96)\n"
    "qpxgye (93)\n"
    "qybit (79)\n"
    "stbgj (10)\n"
    "smsoi (53)\n"
    "zlpxr (136) -> iuauic, dznlyl\n"
    "wfwbq (42)\n"
    "frcqooy (69)\n"
    "zxrmy (70)\n"
    "mxvaxl (60)\n"
    "wwzli (16)\n"
    "jpnhog (8)\n"
    "pablb (107) -> muopf, oekhu, thzqscd\n"
    "mxgyt (51)\n"
    "xkzlyvh (80)\n"
    "fkrog (46)\n"
    "qcntm (13) -> lvcsn, kpqwup, gosgwz, moiqr\n"
    "wzybp (73)\n"
    "urkya (70)\n"
    "lqbnqnl (91)\n"
    "sycbr (76) -> mutwmaa, qmpncds, bfroq, khsdxn\n"
    "alzvh (2766) -> gtpyffj, fzgto, uewchd\n"
    "bwaye (245) -> rveuz, rcumpgx\n"
    "wfdkce (50)\n"
    "xmbujw (94) -> jguufio, shyxzeh, pjxauhw, ytirlv\n"
    "jrkbay (75)\n"
    "knrtys (63)\n"
    "ubjuhxp (51)\n"
    "urbkrn (416) -> seblnmz, kgfhvte\n"
    "urfhlf (9)\n"
    "wyohotq (145) -> vlbsr, oqdukh, ssyfvrj\n"
    "lurhq (1328) -> cibzqvo, sycbr, ruabtb\n"
    "aqaems (26)\n"
    "ysakcag (82)\n"
    "hydeeqe (97) -> jutgp, wxudgdd, bqtxl\n"
    "ecanv (17) -> dxloi, whaax\n"
    "bmyahis (55) -> qpxgye, ajkztpj, ywkpvle\n"
    "qlxgnl (7)\n"
    "tdwxgv (22)\n"
    "qdyzunw (182) -> stbgj, loljfo\n"
    "ftxif (57)\n"
    "xminmbj (69)\n"
    "cvwsj (86) -> stdfrj, fvjcbib, ixroc, ksqrqx\n"
    "vfxqcbq (84) -> vlgiuef, dojviv\n"
    "cpmpyvq (19)\n"
    "frikrv (36) -> yngqiv, wsoahhs, pncxkcd, gpqhjv, zlpxr, fdumfc, kwavcf\n"
    "ikqijv (429) -> jcqhl, nwxyrtn, vjxldb, mmtzk, gnffg\n"
    "wuipwl (18)\n"
    "latmzh (92)\n"
    "uyrxc (60)\n"
    "pyoma (1498) -> oicysoz, qsbcfm, eepdcje, fhdqcbx, zzcagx, dvipr\n"
    "sttus (85)\n"
    "essvr (61)\n"
    "pibqmuz (19) -> kgvbcq, wuegrv\n"
    "xfurlrr (14)\n"
    "cmgvs (77)\n"
    "qkluh (73) -> weunegg, ziiijv\n"
    "nqylf (225) -> bvenb, njozyy, amxjb, stujlz\n"
    "hfymm (14) -> uakcbox, kbmse, qvyrm\n"
    "mernsee (51)\n"
    "nnyago (76) -> mxvaxl, uwrfay\n"
    "brlzr (15)\n"
    "jpwwg (65)\n"
    "muopf (40)\n"
    "oxzmr (360) -> ydowp, nnnkplx, grlofut\n"
    "xpvukx (86)\n"
    "erbssqe (66)\n"
    "irhslmm (33)\n"
    "yiteow (83)\n"
    "kthnd (77) -> zbmwego, pvliyn, svsjobu, bzfew\n"
    "uzzeydh (53)\n"
    "stdfrj (98)\n"
    "fblafmm (11)\n"
    "qpjzx (27)\n"
    "gjqwe (313)\n"
    "uizop (48)\n"
    "tzvld (393)\n"
    "iqler (88) -> vnelda, ujpgmwm\n"
    "xljycl (41)\n"
    "rdomgf (10) -> sggimr, jegoty, owcwvug, tcqnso\n"
    "fnzskbi (42)\n"
    "vkleczw (93) -> uxzwwe, cupeghk\n"
    "tdhxy (95)\n"
    "iiiof (38)\n"
    "qvyrm (68)\n"
    "eogzpga (44)\n"
    "naxce (126) -> inija, cvvegrx\n"
    "hxfvc (18) -> lqbnqnl, qguphyk\n"
    "vwosnfn (293) -> umnkslz, rlgbvvj\n"
    "khuess (49)\n"
    "akdffhk (78)\n"
    "kriwb (19) -> ziayhmx, zouujb, kcqgcgl\n"
    "bmqhrtg (11)\n"
    "dbuqsj (92)\n"
    "aftzw (81)\n"
    "nrvsqf (5)\n"
    "emhxtcg (534) -> uktpcar, yjoyyvl, blwhz, bvbtxh, jkoyyzg, cdnwq\n"
    "kcqgcgl (52)\n"
    "fzgto (67) -> qcntm, tzvld, yohxzv, ttmnf, hbtur\n"
    "ymxwlpc (92) -> ngjngv, jcdmhvd, nqylf, ecytwe, iciuuh\n"
    "alkizae (61)\n"
    "emkzxk (257) -> krfqcf, sybpjci\n"
    "sejkvk (203) -> kojry, tdwxgv\n"
    "yunpioi (33)\n"
    "qmnji (89)\n"
    "dpyxxkv (162) -> dtkdwp, rehst\n"
    "vsfgg (12529) -> mtrde, xpzpv, etwpt, dvncmy\n"
    "ttmnf (239) -> qrzjlw, gwudp\n"
    "qdkrr (10)\n"
    "okpdcz (51)\n"
    "zsigmj (69) -> eazvkxv, ticdma\n"
    "oaopxo (2220) -> jeopf, wphtnvm\n"
    "uxnwtp (82)\n"
    "kodrhj (90)\n"
    "tflwng (93)\n"
    "jzpdbe (29)\n"
    "spgwj (172)\n"
    "wmukud (34)\n"
    "geztlsi (92)\n"
    "kpqwup (95)\n"
    "jcbgta (23)\n"
    "ksfss (18)\n"
    "zuquy (75)\n"
    "qozmho (146) -> btrepl, gljkci, parvx, onwgja\n"
    "vlsjsgg (80)\n"
    "bdwbjzh (38)\n"
    "lvdff (191) -> wqokqz, zyaab\n"
    "mvgmbru (98)\n"
    "krolgpf (27)\n"
    "ixreefh (108) -> auqyep, jgnklq\n"
    "ivlac (48)\n"
    "nhteaei (70)\n"
    "pwhmf (204) -> iujytuv, iieico\n"
    "dpoat (79)\n"
    "ubvheu (72)\n"
    "ygiyze (75)\n"
    "atqewc (16)\n"
    "sawpop (92) -> piyqfs, wfamtnm\n"
    "uwylbft (93)\n"
    "yqnso (27)\n"
    "ccjtpv (158) -> oipqc, vxlypal\n"
    "hkweu (66)\n"
    "gfasdd (11)\n"
    "jsuak (24)\n"
    "vugavk (38)\n"
    "duzgl (7)\n"
    "odxyfb (686) -> biglt, irjov, pibqmuz\n"
    "umxurvd (54)\n"
    "qgcvk (881) -> oizmgt, apqby, ecanv\n"
    "jphmpr (91)\n"
    "cvrqij (84)\n"
    "blwhz (23) -> cihzh, sttus\n"
    "guiej (70)\n"
    "wjaocmd (82)\n"
    "ruvfo (50) -> dlhyzjw, skdylgb\n"
    "ksqrqx (98)\n"
    "pwhplm (61)\n"
    "nfhaii (6)\n"
    "wfamtnm (58)\n"
    "qbzeji (317)\n"
    "okxucaz (54)\n"
    "nzvpgv (290) -> kwmao, ofgeu\n"
    "jlwzgg (61)\n"
    "bsqilyq (82)\n"
    "gosgwz (95)\n"
    "syxkp (79)\n"
    "epydl (42)\n"
    "fhhrji (186) -> faudqy, bxcdldt\n"
    "evkrnfo (38)\n"
    "mulybo (75)\n"
    "xvdkt (44)\n"
    "qdpnnex (120) -> nwyulno, uxbjym\n"
    "nnxqmb (297)\n"
    "urqox (57)\n"
    "dphmg (6)\n"
    "wymlvix (64)\n"
    "yfnlhlh (57)\n"
    "oykqvif (52)\n"
    "wexhnbh (196)\n"
    "gzctkm (40)\n"
    "vcwezm (82)\n"
    "vjxldb (169)\n"
    "ufrrrzi (31)\n"
    "gatjls (152) -> gkxebo, xmogef\n"
    "zujrs (72)\n"
    "qidmgsc (301) -> hpgwq, szvty\n"
    "oboju (147) -> cprbzvp, xbytmo\n"
    "wdcltyl (32)\n"
    "xsmcfs (95)\n"
    "mnfep (63)\n"
    "ajxsrs (296) -> vwslb, wmukud\n"
    "vksnzty (97)\n"
    "ccnpjdf (9)\n"
    "cciwr (22)\n"
    "inknun (149) -> mfutay, nzdbs\n"
    "ckzuyha (85)\n"
    "nkdxy (225) -> ccqldu, fkrog\n"
    "sfohocq (13) -> fkjof, gcrbrn\n"
    "aefqoq (84)\n"
    "pknqf (246)\n"
    "xujmi (68)\n"
    "olofh (164) -> uqtiwgu, xsmcfs\n"
    "fqaefy (62)\n"
    "thneux (88) -> choeijs, lodcj\n"
    "swujbg (36)\n"
    "zfmas (70)\n"
    "dojviv (72)\n"
    "stujlz (6)\n"
    "shyxzeh (61)\n"
    "bzublv (64)\n"
    "jubtls (68)\n"
    "aideelj (53)\n"
    "jieijuo (9)\n"
    "iqpcu (94)\n"
    "xiwnu (12)\n"
    "grrxl (84)\n"
    "sftqzaf (43) -> qybit, dpoat\n"
    "bqoptf (74)\n"
    "alaug (75)\n"
    "sawkpue (271) -> modms, ssrqm, ndgzf, sqvxf\n"
    "bnjwfrz (63)\n"
    "xklrgp (149) -> yfrmup, nfhaii, uspmxw\n"
    "jbarvch (275) -> qtqcv, prvldv\n"
    "pmgngjy (74)\n"
    "qitnlrh (70)\n"
    "sbfiv (44)\n"
    "bijprk (8)\n"
    "sktewq (253) -> fxfznc, venvbai, rxgry\n"
    "gcdzhfy (70)\n"
    "zyzet (19)\n"
    "zffpxgw (217) -> hpcmne, ajiubh\n"
    "ajiubh (37)\n"
    "ywmif (47)\n"
    "egzpjym (202) -> hasyyr, vgjgz\n"
    "jopcvyb (448) -> tgwgno, uyhlbf, rdomgf, yrozpm, qnscqms, ubhlb\n"
    "jkoyyzg (79) -> urqox, yfnlhlh\n"
    "auciw (18)\n"
    "prlhyb (7)\n"
    "jtqijee (171) -> auciw, awqgdfk, uceyfx, awjwff\n"
    "dxloi (90)\n"
    "gxpuofv (65) -> cxptwu, zrwnma, mxgyt\n"
    "moiqr (95)\n"
    "rfkcylj (16) -> ckypedd, xjufehm, nbkzvz\n"
    "rkwkwd (97) -> dfzwcc, pmgngjy, ejnqcb\n"
    "fkjlcz (177) -> mjrog, qmnji\n"
    "cider (27)\n"
    "cfiyqh (6)\n"
    "ywkpvle (93)\n"
    "nbkzvz (61)\n"
    "ndszsz (71)\n"
    "kwzgwt (83)\n"
    "rgxwwc (27)\n"
    "prvldv (6)\n"
    "iotkxfd (8)\n"
    "mfutay (50)\n"
    "vgkltqq (16) -> wzxyc, uodhr, xsjbc\n"
    "dehjjod (82)\n"
    "yyyub (74)\n"
    "dfwpczh (16) -> bkjppqe, yuhmnjs\n"
    "zejjjo (109) -> aoipta, bbbms\n"
    "zrwnma (51)\n"
    "bwiqe (98) -> dtburx, bpgdb, fhhrji, hfymm, tgqwgb, gxpuofv\n"
    "ktcdxoo (973) -> efobdsd, jtmps, zmjqiv\n"
    "tvinpl (220) -> iglmzsi, zujrs\n"
    "dkkkntv (78)\n"
    "qwlze (163) -> nvtyg, hzywspw\n"
    "bzbvwgh (7) -> kbwpk, czuwoe, tpekc, qidmgsc, hagrq\n"
    "brghw (48)\n"
    "kojry (22)\n"
    "cstmu (8193) -> mkrjamh, vycgaoz, ruvfo, sawpop\n"
    "kjmse (87)\n"
    "umutl (36) -> grtrt, tjaqrw\n"
    "olrdlw (67) -> fxqng, irvolb\n"
    "emrbwzz (7)\n"
    "iyxsjhc (80)\n"
    "ueasp (94)\n"
    "jdhewio (390) -> qpden, olspso\n"
    "szszezd (909) -> tvcxl, mdnqs, waxkga, gyjvtjm, ytbyct\n"
    "egdrn (74) -> fdzqz, urkya, nhteaei, xjypx\n"
    "eoaoxqm (753) -> khzbxke, pwhmf, kapxuq\n"
    "uyhlbf (350)\n"
    "qkmkwgl (68) -> tyywgp, xjhvuc\n"
    "hbwec (56)\n"
    "mfbnys (40)\n"
    "jegoty (85)\n"
    "ukaflr (99)\n"
    "fmwvok (1044) -> cksiby, uravet, wexhnbh, nnyago, thneux\n"
    "rjayavy (7)\n"
    "xybiuiq (53) -> egrimlf, cdvhmy, hqwkq, wfwbq\n"
    "xlanm (10383) -> bwmrksn, fimqsn, naxce, zjtjt\n"
    "tumwln (348) -> qgvqg, sawkpue, tcvgl, zqnjd\n"
    "onamlmy (195) -> kzxyyd, yiqnfd\n"
    "gljkci (15)\n"
    "vjevs (35)\n"
    "vuzxr (82)\n"
    "ccuehkp (93)\n"
    "jtmps (56) -> wixoky, vmsmdqx, lxbsif\n"
    "xvwio (72)\n"
    "thzqscd (40)\n"
    "yuiicxp (56)\n"
    "xrkqv (137) -> xgihtsx, iunkpe\n"
    "yacmhtk (19)\n"
    "mcjlm (575) -> qkluh, bsfgu, ndhitxf, jtqijee, ifgfg, wvhvw\n"
    "bmfhjo (170) -> bznst, xcgwl\n"
    "wrwgm (11)\n"
    "kwxpnrs (132) -> rmnkgss, cciwr\n"
    "mmndzs (75)\n"
    "dkjlges (80)\n"
    "mpnnffx (142) -> wayftw, epaaasn\n"
    "xsfefyb (674) -> xybiuiq, jnzqvia, eywfmfs\n"
    "zukio (75)\n"
    "npjcdl (68)\n"
    "mikast (17)\n"
    "rbauxvx (6)\n"
    "ipxns (75)\n"
    "frezf (95)\n"
    "rxflxr (82)\n"
    "ejzsbli (237) -> djsss, rkhyewd\n"
    "ullvx (79)\n"
    "cxetjr (1657) -> fujwb, nnxqmb, kthnd\n"
    "vmpmig (15)\n"
    "kgqgct (13)\n"
    "fupwuk (49)\n"
    "mctsts (17)\n"
    "pozpmyh (19)\n"
    "dfrcge (27)\n"
    "ywhjz (482) -> exesam, odbyxq, xghhu, xmbujw\n"
    "ytirlv (61)\n"
    "eajmafa (81)\n"
    "dxavw (16)\n"
    "rswqvx (249)\n"
    "pwfdn (40)\n"
    "cayigxg (24)\n"
    "doppnr (201)\n"
    "rehst (42)\n"
    "rxezd (318) -> sohuv, ksfss\n"
    "hfhswyd (85) -> tqyldbt, tridq\n"
    "aoipta (56)\n"
    "tpmhs (61)\n"
    "zkvopb (23) -> nxqzuy, jpwwg\n"
    "aceqrlu (81)\n"
    "utispep (65)\n"
    "zmtfcll (70)\n"
    "sfruur (62) -> twbxgv, evows, xwwzp, vsfgg, zsasjr\n"
    "utsfqn (41)\n"
    "tdknh (69)\n"
    "fwocscd (158) -> krolgpf, gbmfzzu\n"
    "zouujb (52)\n"
    "mvdzfo (47)\n"
    "wfjks (83) -> ekleund, kikntw, jubtls, npjcdl\n"
    "bvbtxh (136) -> zyzet, pflvdx, ontrln\n"
    "obzomb (23) -> ullvx, acfmyv, mzywzs\n"
    "khupkt (63041) -> alzvh, sjhwgq, lyxzfqz\n"
    "zhrsp (52)\n"
    "vxruziw (439) -> tpvzavf, xrkqv, qvndh, xklrgp, cwixiq\n"
    "svcafxb (423) -> jbarvch, mawwtx, stkcndh\n"
    "dhejgd (82) -> tzhoqw, cvrqij, xokmont\n"
    "erfldtn (82)\n"
    "predg (84)\n"
    "waxkga (169) -> rgxwwc, yriibfp\n"
    "kvpsfgk (17)\n"
    "tlmxygb (70) -> rvyqbq, olofh, egdrn, pkudedc, rxezd, csnhv, jrgougl\n"
    "nzhnurq (114) -> zwxwfin, lwvcp\n"
    "fzvdchs (59)\n"
    "rsqihar (23)\n"
    "vtvsd (114) -> cnsbonb, ajhizdz\n"
    "zykcrir (60)\n"
    "ockzlpp (43) -> chxsxbr, vbvug\n"
    "fdumfc (134) -> lninq, ykowao\n"
    "nqjuj (19)\n"
    "akzcjd (63)\n"
    "qhrxvzj (52)\n"
    "kpdmptf (48)\n"
    "gtpew (23) -> iyxsjhc, fwvvidu, mdshsxt, yzvqo\n"
    "stkcndh (183) -> cohps, legrbb\n"
    "nbrfpbr (872) -> iedrlkp, rtyegs, hxfvc\n"
    "nxqzuy (65)\n"
    "ojrjqv (85)\n"
    "egcjfjo (41)\n"
    "mlfxnna (51)\n"
    "nhbbd (62)\n"
    "ykxnd (88)\n"
    "bwfqr (89)\n"
    "wuvmf (5)\n"
    "kmbrqv (13)\n"
    "uwrhuw (88)\n"
    "oaqvt (50)\n"
    "wqzic (42)\n"
    "yxsaf (80)\n"
    "cvvegrx (25)\n"
    "faudqy (16)\n"
    "qeiijk (188) -> jiaho, qlxgnl\n"
    "moqped (94)\n"
    "zmjqiv (94) -> jwjrj, bwfqr\n"
    "jdxfsa (1869) -> lugwl, ckcjr, umutl\n"
    "wsmmlrl (70)\n"
    "hjtkb (9)\n"
    "wdjcb (16)\n"
    "jlgnsu (65) -> wxvuup, ilvblzm, ckzuyha, cbbtbz\n"
    "pjsbxvk (770) -> dfwpczh, gsmocx, fwocscd\n"
    "iiwwr (284) -> hmnvh, vksnzty\n"
    "sysvory (145) -> udpcyt, yrdhq, ealyedu, kmufvuk\n"
    "wvdoa (95)\n"
    "dcqinx (36)\n"
    "rugnh (52)\n"
    "uspmxw (6)\n"
    "ajhizdz (64)\n"
    "onkhx (65)\n"
    "gbmfzzu (27)\n"
    "zjtjt (14) -> xqshwdz, khjag\n"
    "pzlhzky (48)\n"
    "vonesxw (19)\n"
    "aiwvi (242) -> walkm, ixreefh, gatjls, spgwj, kjdjdr, ybnehoi\n"
    "pflvdx (19)\n"
    "rvyqbq (214) -> bxqjg, sxzpils\n"
    "bdmah (57)\n"
    "tgqwgb (78) -> zxrmy, qvmbysw\n"
    "dbnoug (31) -> xnvdqbe, mtowovz, bzbncmc\n"
    "hclea (96)\n"
    "sggimr (85)\n"
    "weithhz (56)\n"
    "mzywzs (79)\n"
    "vfykuuv (87)\n"
    "zwxxii (91)\n"
    "etlce (14)\n"
    "ixomyeb (24)\n"
    "xqshwdz (81)\n"
    "exesam (300) -> fhjzpjw, qxjknv\n"
    "djimr (1615) -> ltgnnr, kjmse\n"
    "cadasac (35)\n"
    "pyvwl (78)\n"
    "hdikur (11)\n"
    "bkfav (57)\n"
    "nrduy (96)\n"
    "uqpprye (82)\n"
    "kmrmxw (29)\n"
    "xjhvuc (57)\n"
    "aflcmu (407) -> ezycquw, kaecmob\n"
    "utamsb (75) -> llrrzrn, erbssqe\n"
    "bavaf (18)\n"
    "umhjck (87) -> zepjndx, bdmah\n"
    "ngjngv (123) -> jqnnot, bnjwfrz\n"
    "kcjwb (61)\n"
    "cibzqvo (178) -> dfrcge, uuixxr\n"
    "gjgwki (78)\n"
    "rgelh (66) -> tmigcw, jmzvi, tjslk, blpjnzf, qzobjfo, rcmyfr, bwaye\n"
    "uceyfx (18)\n"
    "epaaasn (17)\n"
    "biglt (73) -> rihlj, odoxr\n"
    "bsfgu (215) -> iinxvw, sgpiiir\n"
    "hatmr (61)\n"
    "txtdw (8)\n"
    "fdaqst (25)\n"
    "dxavaum (18)\n"
    "ticdma (66)\n"
    "plkmpm (78) -> bieok, grrxl\n"
    "ywzai (152) -> khuess, vbauj\n"
    "mdshsxt (80)\n"
    "weguko (91) -> iuwwa, epydl\n"
    "kaecmob (10)\n"
    "psmztc (11)\n"
    "qzayss (31)\n"
    "tbdhh (104) -> sfwaimh, orihc, jsuak\n"
    "wxvuup (85)\n"
    "mhpxyvm (734) -> xdkya, zsigmj, umhjck\n"
    "oqqme (17)\n"
    "judfhye (25) -> brlzr, dxffr\n"
    "qsbcfm (37) -> fqayb, xminmbj\n"
    "bvknwgq (61)\n"
    "hwuwj (62)\n"
    "zgoinf (345) -> xljycl, ghfcfj\n"
    "vbvxs (31) -> akzcjd, vnynj, eanoucd, txxfz\n"
    "mqlgoq (86)\n"
    "csmul (75) -> wfdkce, oaqvt\n"
    "fzzlnwi (63) -> vgkltqq, vbvxs, lfwru\n"
    "ywegjjk (6058) -> rgelh, sfizdf, mcjlm, ztjquwi\n"
    "gyjvtjm (179) -> paynlu, nfklqi\n"
    "ecfrqpl (133) -> okniwp, njqemt\n"
    "xcgwl (20)\n"
    "nsxrvpg (313) -> nqtowev, fblafmm\n"
    "iwiaa (188) -> ztfhz, txtdw, jpnhog\n"
    "nxpozme (16)\n"
    "dxpxept (36)\n"
    "tbaai (25) -> vrqbi, jjdmu\n"
    "imxro (58)\n"
    "onwgja (15)\n"
    "gnqwwbt (75)\n"
    "nbjpcc (88)\n"
    "ontrln (19)\n"
    "jxpixqi (14)\n"
    "llrrzrn (66)\n"
    "hdmcpq (131) -> qitnlrh, wsmmlrl\n"
    "vlgiuef (72)\n"
    "bieok (84)\n"
    "hpcmne (37)\n"
    "qxjknv (19)\n"
    "qguphyk (91)\n"
    "aukjf (179) -> okxucaz, otbxl\n"
    "vggstn (23)\n"
    "vlmzodk (66)\n"
    "bqtxl (84)\n"
    "vilskw (181) -> vahnoue, wqzic\n"
    "wzxyc (89)\n"
    "upsmxqn (470) -> bmyahis, xanbjlw, twazofk\n"
    "fwohcn (30)\n"
    "zknpmnc (53)\n"
    "afelswv (52)\n"
    "kapxuq (82) -> wzybp, tdstv\n"
    "awgjkiv (71)\n"
    "vaeeqvi (17)\n"
    "ydqgvnf (110) -> flejt, dxpxept\n"
    "cdcvlb (27)\n"
    "uqtiwgu (95)\n"
    "jaerxmv (38)\n"
    "mxtxm (90) -> tdknh, pjbwq\n"
    "wvtac (60)\n"
    "ziprwty (71) -> pshwly, jwojmds, tgsicj\n"
    "rhjxbx (9) -> mhdkdt, kwzgwt\n"
    "pqlwekx (87)\n"
    "rpxmv (35)\n"
    "yenln (12) -> wklmops, ulehitr, dbnoug, wyohotq, gjqwe\n"
    "skdylgb (79)\n"
    "brnhg (94)\n"
    "qhldpg (74)\n"
    "srsenpj (84)\n"
    "whaax (90)\n"
    "etjste (205)\n"
    "ntcddy (8) -> qekpce, gjgwki, dkkkntv\n"
    "ljfvbjd (57)\n"
    "irjov (61) -> bzdgxs, zkbeehu\n"
    "bvenb (6)\n"
    "tlkhxww (91)\n"
    "icnav (41)\n"
    "myckhlw (64)\n"
    "iglmzsi (72)\n"
    "oztasey (158) -> dxddn, foibc\n"
    "oakbrw (11)\n"
    "hawtu (54)\n"
    "zkbeehu (78)\n"
    "hzzxjxa (47)\n"
    "felrwte (64)\n"
    "ogyiesm (5127) -> eoaoxqm, lptmne, titze\n"
    "ojqqw (52) -> yxsaf, zfshwt\n"
    "odbyxq (338)\n"
    "gkxebo (10)\n"
    "bvcghhs (29)\n"
    "mvamo (49)\n"
    "wemjk (64)\n"
    "olspso (7)\n"
    "uasqon (97)\n"
    "liwlcz (728) -> fhvyhk, qqnywdg, ajxsrs, utojr, tvinpl\n"
    "rkhyewd (49)\n"
    "wuckr (40)\n"
    "hzywspw (31)\n"
    "ofgeu (22)\n"
    "hcyjfzz (92)\n"
    "ieebfpb (71)\n"
    "aclihvm (8)\n"
    "xyoiv (17)\n"
    "okniwp (30)\n"
    "jfchk (1360) -> hbwec, weithhz\n"
    "kwmao (22)\n"
    "piqids (229) -> fbusld, xifaq, vkwsodp\n"
    "ryctwjl (19)\n"
    "sybpjci (24)\n"
    "klnxfd (1174) -> zoryb, wcpyi, etjste\n"
    "mjrog (89)\n"
    "zyaab (50)\n"
    "xanbjlw (258) -> uuapl, sckgsn\n"
    "xdkya (143) -> bvcghhs, jzpdbe\n"
    "dznlyl (74)\n"
    "lcgtwj (160) -> pxsokyl, chhhge\n"
    "cvprip (282) -> qkpaxtt, bmfhjo, tqimh\n"
    "paynlu (22)\n"
    "ixnlvyo (75)\n"
    "qjnhwpq (56)\n"
    "qnsqwm (106) -> brnhg, trcyfi\n"
    "jeopf (72)\n"
    "vnelda (50)\n"
    "nwyulno (87)\n"
    "njozyy (6)\n"
    "yjrar (13) -> jppsaym, agfnncm\n"
    "gyzorus (49)\n"
    "pjbwq (69)\n"
    "hechfb (31) -> aflcmu, sjdpe, ofdehn, zgoinf, umnqkb\n"
    "jrgougl (54) -> jrkbay, elpwvoy, gnqwwbt, ipxns\n"
    "wsoahhs (188) -> zouxmz, brghw\n"
    "rhlepi (85)\n"
    "qopkhc (69) -> cvrga, ujtej, gybikf, dkoike, guhjkd\n"
    "lvcdsgp (178) -> afelswv, ovhhkoc, rugnh\n"
    "dhsopiv (88)\n"
    "jwojmds (59)\n"
    "auqyep (32)\n"
    "jkodco (46) -> adunt, ztook\n"
    "pxsokyl (34)\n"
    "ieohkpr (10)\n"
    "velhob (109) -> gyzorus, kfngejn\n"
    "cfrcco (217) -> zhhhntj, jcvimc\n"
    "xlvjz (26)\n"
    "tnhet (78) -> onoyb, laohhtn, mqlgoq\n"
    "ejovcx (82)\n"
    "yaehsu (75)\n"
    "kqueox (7)\n"
    "evows (4599) -> xsfwcgq, txszqu, uypxc, aulgwyb, qshoazt, dyfnpt, rkofvt\n"
    "dtburx (130) -> frycrnj, vqrtnp\n"
    "qtqcv (6)\n"
    "mgyixhn (32) -> msskm, iqtemv\n"
    "bckbud (249) -> iqjbdok, mjtuzfr, zejjjo\n"
    "njmlk (65)\n"
    "ebwgi (19)\n"
    "lsaroxx (63)\n"
    "xjufehm (61)\n"
    "htbmh (29)\n"
    "molth (16)\n"
    "lninq (75)\n"
    "lwqlyjq (309) -> qongfb, pzlhzky\n"
    "yqlxeb (79) -> ymxwlpc, cavlg, odxyfb, xsfefyb, mhpxyvm, htujh, xfglmz\n"
    "vagjk (98)\n"
    "ssrqm (37)\n"
    "damyp (46)\n"
    "svsjobu (55)\n"
    "djsss (49)\n"
    "udnmqte (36)\n"
    "lzeihwp (83)\n"
    "oplzouv (74) -> fqfnocq, ntftmt, piqids, dbpkf, gtpew\n"
    "puvhc (137) -> bsfsayz, ssxuat, brlbdjx\n"
    "nxmksiq (40)\n"
    "amxjb (6)\n"
    "gnffg (119) -> vjzfc, ijyhvsj\n"
    "inlcow (271)\n"
    "tfqxv (1437) -> zmtfcll, gcdzhfy\n"
    "lnontej (19) -> bpelccj, utyrttu, gqlyhql, fvwll, ejzsbli, nsxrvpg, ofyuao\n"
    "gjwzw (207) -> egzpjym, ywzai, bfulyh, zxavxe\n"
    "oactn (57)\n"
    "bwugxhi (56) -> vbzwk, krrvyl, ivlac, mzrwaa\n"
    "legrbb (52)\n"
    "vetsll (41)\n"
    "iujytuv (12)\n"
    "qkapxbc (18)\n"
    "kgfhvte (31)\n"
    "uypxc (82) -> bpzjm, dkcqdx, msryw, aqlqmq, yxpnzkn, obzomb, bzbfpkb\n"
    "gslii (62)\n"
    "fyeuhqh (13)\n"
    "wxbao (84)\n"
    "nfkmi (894) -> drzge, bgpjb, jkodco, kxkwxoj, crothf\n"
    "fqfnocq (305) -> yacmhtk, vonesxw\n"
    "ykowao (75)\n"
    "jxsmuey (82)\n"
    "cejnfcx (89) -> rhlepi, rgkrl, gjgcvyp, lkfdr\n"
    "wattsr (23)\n"
    "bzfew (55)\n"
    "guhjkd (162) -> cdcvlb, cider, qpjzx\n"
    "ayhdd (184) -> laeaf, udiio, bgqvm, ofwtjhw\n"
    "onaatvy (51) -> aftzw, ekxczvo, wkfjzs\n"
    "uodhr (89)\n"
    "cnblx (498) -> vkleczw, pablb, objssr, pzjvq\n"
    "bdjlzf (52)\n"
    "tynxlau (32867) -> ywegjjk, bavyg, qdpoyl, wngzh\n"
    "soryrk (69) -> fnzskbi, oovqoi\n"
    "nrlhen (153) -> wattsr, eqbwx\n"
    "kgvbcq (99)\n"
    "zsasjr (77) -> jopcvyb, pyoma, jdxfsa, liwlcz, cxetjr, vifbi, tlmxygb\n"
    "orihc (24)\n"
    "titze (609) -> czmzol, velhob, truximz, utamsb\n"
    "igbhyk (44)\n"
    "jgnklq (32)\n"
    "bjcsjrr (138) -> bpemyk, nqjuj\n"
    "ismrc (90) -> cjeauo, uasqon, prxmxv\n"
    "fbusld (38)\n"
    "kikntw (68)\n"
    "cksiby (128) -> zzbzwdm, zdawjkr\n"
    "rgkapf (77) -> dkjlges, ckombz, vpnjbha\n"
    "oovqoi (42)\n"
    "ujtej (57) -> ccuehkp, tflwng\n"
    "yanvh (44)\n"
    "mawwtx (29) -> bvrpb, xpvukx, jhbqc\n"
    "jinwsas (235) -> gzctkm, nxmksiq, fhyvz\n"
    "gapzarg (79)\n"
    "sjdpe (263) -> erfldtn, vuzxr\n"
    "vnynj (63)\n"
    "jqnnot (63)\n"
    "rxlbou (57)\n"
    "xewbn (7)\n"
    "tiwkyz (117) -> lewbxa, btnnorn\n"
    "kbwpk (307) -> ffhxi, polumk\n"
    "gkqgru (14) -> pqlwekx, ysdqkw\n"
    "baaqr (94) -> btnyx, fdszkhp\n"
    "jmzvi (89) -> rzwjli, uizop, necqpdx, debir\n"
    "mtowovz (94)\n"
    "wklmops (201) -> mbkbmql, dlkhb\n"
    "xnvdqbe (94)\n"
    "ofdehn (95) -> yiteow, yblsbf, gazaoty, lzeihwp\n"
    "brlbdjx (13)\n"
    "xawfk (85)\n"
    "krfqcf (24)\n"
    "khsdxn (39)\n"
    "qrlhp (61) -> moqped, ueasp\n"
    "rzwjli (48)\n"
    "polumk (15)\n"
    "bwmrksn (14) -> bxkxp, eajmafa\n"
    "vwslb (34)\n"
    "qdcos (132) -> ryctwjl, sczyp, enxbya, cpmpyvq\n"
    "uuixxr (27)\n"
    "yqqun (62)\n"
    "bpemyk (19)\n"
    "trcyfi (94)\n"
    "ttqpi (72) -> nfmicyi, yjnrjde\n"
    "zepjndx (57)\n"
    "fbyju (52)\n"
    "nbrvl (89)\n"
    "pshwly (59)\n"
    "uskfp (84)\n"
    "cdnwq (41) -> xerbuu, iiiof, jaerxmv, bdwbjzh\n"
    "dntwqr (38)\n"
    "welvrkn (74)\n"
    "krpda (826) -> azzysl, ayhdd, tnhet\n"
    "jhbqc (86)\n"
    "zlazoqs (98)\n"
    "seihhya (81) -> jhruwih, aefqoq\n"
    "jcqhl (5) -> glxogmc, bsqilyq\n"
    "hsexbak (99)\n"
    "wixoky (72)\n"
    "awqgdfk (18)\n"
    "walkm (84) -> cxuijad, yanvh\n"
    "jcezw (34) -> wxbao, predg\n"
    "iqjbdok (41) -> msrrlv, kodrhj\n"
    "krrvyl (48)\n"
    "bkjppqe (98)\n"
    "srscbv (83) -> jawbtmo, wmvniap\n"
    "nuytv (94)\n"
    "glxogmc (82)\n"
    "iuauic (74)\n"
    "jtmuv (2257) -> terkw, bzbvwgh, emhxtcg, nkbmoin\n"
    "noqjuo (29)\n"
    "xbytmo (28)\n"
    "khjag (81)\n"
    "mhdkdt (83)\n"
    "elpwvoy (75)\n"
    "edtkfvv (1462) -> tbdhh, mpnnffx, wdzhfmw, pkceuqw\n"
    "qxyramq (7)\n"
    "swaxyxe (23)\n"
    "pvliyn (55)\n"
    "ztook (71)\n"
    "ofcyw (74)\n"
    "txxfz (63)\n"
    "tqimh (196) -> prlhyb, kqueox\n"
    "ezycquw (10)\n"
    "lyxzfqz (30) -> qgcvk, jfchk, upsmxqn, nbrfpbr, jmbueky, kqswas\n"
    "poypmax (7848) -> atyaqz, vkhazkn, chljtta, anehvd, vilskw, lbnenyf\n"
    "xyemll (55)\n"
    "pkudedc (256) -> takxgz, fupwuk\n"
    "sxvig (60)\n"
    "jkvgvz (49)\n"
    "ssxuat (13)\n"
    "vrqbi (84)\n"
    "tjslk (281)\n"
    "moivx (23)\n"
    "oizmgt (137) -> sakhif, fwohcn\n"
    "vpnjbha (80)\n"
    "izpxjp (64)\n"
    "pzjvq (85) -> ieebfpb, yprusb\n"
    "tycgm (7)\n"
    "lrjnzf (68)\n"
    "yprusb (71)\n"
    "oeqqj (259) -> pwhplm, jlwzgg\n"
    "libtrl (53)\n"
    "ozlqcn (95)\n"
    "jmbueky (38) -> iiwwr, cvwsj, yvwecfs\n"
    "eywfmfs (73) -> mfamq, bqoptf\n"
    "udiio (38)\n"
    "plsep (96)\n"
    "ghsxqq (46) -> srsenpj, uskfp\n"
    "qnevjto (283) -> dcqinx, uctlk\n"
    "lwvcp (50)\n"
    "chxsxbr (6)\n"
    "hfxsib (247)\n"
    "fdszkhp (77)\n"
    "tkvmtol (117) -> vfkjif, oinyx\n"
    "xycva (275) -> aclihvm, yaripcu\n"
    "mtrde (1154) -> gsfnr, plsep\n"
    "jcvimc (51)\n"
    "vqvwkm (92)\n"
    "asrwh (69)\n"
    "hykxm (1428) -> dpyxxkv, plkmpm, pknqf\n"
    "twbxgv (13182) -> yenln, qrgqcd, tfqxv\n"
    "ziayhmx (52)\n"
    "oipqc (9)\n"
    "cjhtxo (137) -> gfasdd, psmztc, rdvtzr\n"
    "iqymm (69)\n"
    "ehvxt (17)\n"
    "bzbncmc (94)\n"
    "irvolb (90)\n"
    "cxuijad (44)\n"
    "bgavnd (94)\n"
    "dhuof (39) -> ysakcag, dehjjod\n"
    "wkcrce (182) -> ndvdj, ieohkpr\n"
    "qvmbysw (70)\n"
    "prxmxv (97)\n"
    "evbvdgl (158) -> titbn, ebnqn\n"
    "glqspl (27)\n"
    "azkmt (35)\n"
    "eanoucd (63)\n"
    "rydrp (156) -> mbniyi, emrbwzz\n"
    "vffqp (70)\n"
    "tpvzavf (117) -> fdaqst, qlkjhsi\n"
    "ajkztpj (93)\n"
    "krbpgmk (4302) -> svcafxb, vfxzkq, vxwobup, qopkhc\n"
    "mgqkhic (49)\n"
    "bpzjm (142) -> loxjzpo, fzvdchs\n"
    "ntftmt (195) -> welvrkn, htouwcr\n"
    "etwpt (59) -> cejnfcx, oxzmr, sysvory\n"
    "owaebx (27)\n"
    "ctzhawr (74)\n"
    "btnnorn (43)\n"
    "vbmqrqx (13)\n"
    "csnhv (248) -> smsoi, lkwogh\n"
    "lisfhnn (91) -> zykcrir, sxvig, wvtac\n"
    "drzge (162) -> vbmqrqx, wgcgdvt\n"
    "ibyrsdo (25)\n"
    "kkmidak (15)\n"
    "sddvn (70)\n"
    "gsmcgor (79) -> rffwau, qqmlvk\n"
    "rsjffj (80) -> klnxfd, oplzouv, djimr, ktcdxoo, aqugisv\n"
    "dyfnpt (468) -> xwwfi, urbkrn, kryczad\n"
    "exqkey (66)\n"
    "ydowp (23)\n"
    "truximz (91) -> imxro, izyxppl\n"
    "qrgqcd (309) -> rgkapf, tzszs, qbzeji, nkdxy\n"
    "btnyx (77)\n"
    "qsyocuq (346) -> qilhudr, aukjf, offkzc\n"
    "wmvniap (46)\n"
    "eusnn (66)\n"
    "terkw (474) -> yjrar, hipfszh, oboju, tiwkyz, vtwdqkd, dhuof\n"
    "aqlqmq (230) -> zhlfdac, kkmidak\n"
    "ziqyhi (11)\n"
    "piyqfs (58)\n"
    "kryczad (478)\n"
    "paoitb (51)\n"
    "tpekc (271) -> irhslmm, yunpioi\n"
    "qrzjlw (77)\n"
    "aslvy (29)\n"
    "yvwecfs (478)\n"
    "paqihg (35)\n"
    "itjxq (46)\n"
    "ibdjxl (262) -> kmrmxw, htbmh, aslvy\n"
    "cxptwu (51)\n"
    "ghfcfj (41)\n"
    "yohxzv (359) -> kvpsfgk, mctsts\n"
    "kmufvuk (71)\n"
    "mbniyi (7)\n"
    "rxgry (32)\n"
    "stnnf (88) -> jytapdu, kkeuh, xycva, zffpxgw, cvlkltp, lvdff\n"
    "ychjmik (40)\n"
    "bzdgxs (78)\n"
    "cyczt (95)\n"
    "luhxcq (68)\n"
    "iedrlkp (176) -> xiwnu, gezqw\n"
    "vgqmfj (85) -> idwpug, hawtu\n"
    "tdstv (73)\n"
    "mbkbmql (56)\n"
    "dbpkf (169) -> zzcqptv, vfykuuv\n"
    "wqokqz (50)\n"
    "xufneyr (153)\n"};

struct info {
    std::string name;
    int weight;
    std::vector<std::string> names;
};

info parse(std::string s)
{
    info result;

    // e.g. "luhxcq (68) -> xiwnu, gezqw"
    std::smatch sm;
    if (!std::regex_match(s, sm, std::regex("(\\w+)\\s*\\((\\d+)\\)(.*)")))
        throw "bad string!";
    assert(sm.size() == 4);
    result.name = sm[1];
    result.weight = stoi(sm[2]);
    s = sm[3];

    if (!s.empty()) {
        // e.g. " -> xiwnu, gezqw"
        if (!std::regex_match(s, sm, std::regex("\\s*->\\s*(.*)")))
            throw "bad string!";

        s = sm[1];
        while (std::regex_match(s, sm, std::regex("(\\w+)\\s*,?\\s*(.*)"))) {
            result.names.push_back(sm[1]);
            s = sm[2];
        }
    }

    return result;
}

void test_parse()
{
    const info i0 = parse("luhxcq (68)");
    assert(i0.name == "luhxcq");
    assert(i0.weight == 68);
    assert(i0.names.empty());

    const info i1 = parse("iedrlkp (1) -> xiwnu");
    assert(i1.name == "iedrlkp");
    assert(i1.weight == 1);
    assert(i1.names.size() == 1);
    assert(i1.names[0] == "xiwnu");

    const info i2 = parse("iedrlkp (176) -> xiwnu, gezqw");
    assert(i2.name == "iedrlkp");
    assert(i2.weight == 176);
    assert(i2.names.size() == 2);
    assert(i2.names[0] == "xiwnu");
    assert(i2.names[1] == "gezqw");
}


std::string find_orphan(const std::string input)
{
    std::set<std::string> parents, children;
    eachline(input.c_str(), [&](std::string line) {
        const info i = parse(line);
        parents.insert(i.name);
        for (auto n: i.names)
            children.insert(n);
    });

    std::set<std::string> orphan;
    std::set_difference(
        parents.begin(), parents.end(),
        children.begin(), children.end(), 
        std::inserter(orphan, orphan.begin()));

    assert(orphan.size() == 1);
    return *orphan.begin();
}

int sum(const std::map<std::string, info> & data, std::string base)
{
    const info & i = data.at(base);
    int s = i.weight;
    for (auto n: i.names)
        s += sum(data, n);
    return s;
}

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
    eachline(input.c_str(), [&](std::string line) {
        const info i = parse(line);
        data[i.name] = i;
    });

    return balance(data, base);
}

void run()
{
    test_parse();
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
    assert(find_orphan(test) == "tknk");

    const std::string orphan = find_orphan(input);
    std::cout << "7.1 " << orphan  << '\n';
    assert(orphan == "fbgguv");

    assert(part2(test, "tknk") == 60);
    const int excess_weight = part2(input, "fbgguv");
    std::cout << "7.2 " << excess_weight  << '\n';
    assert(excess_weight == 1864);
}

}


namespace day08 {

const char * input =
    "ebu inc 626 if iq < 0\n"
    "obc dec -809 if sdw == -2\n"
    "vb inc 568 if k > -2\n"
    "wl dec 721 if wui <= 2\n"
    "xbh dec -310 if bx != 1\n"
    "qun inc 741 if qun > -4\n"
    "k dec 661 if sdw != 0\n"
    "wui inc 628 if k >= -4\n"
    "qet inc 563 if skh == 0\n"
    "ebu dec 197 if wl < -716\n"
    "qun dec 239 if sdw < 7\n"
    "n dec 655 if azg == 0\n"
    "iq inc -857 if kxm <= -9\n"
    "qet inc -959 if tzy > 5\n"
    "azg inc -643 if qun >= 510\n"
    "ebu inc 537 if c >= -8\n"
    "eh inc -677 if bx >= -1\n"
    "c dec -267 if ebu < 341\n"
    "sdw dec 811 if tzy != -1\n"
    "wui inc -775 if qet >= 562\n"
    "iq inc 215 if azg >= -8\n"
    "qun inc 949 if sdw > -813\n"
    "xjo inc -652 if vb != 563\n"
    "skh inc -560 if n < -645\n"
    "xjo dec 978 if ne == 5\n"
    "skh dec 913 if k > -6\n"
    "iq inc 783 if azg != 1\n"
    "skh inc 955 if ne == 0\n"
    "xbh inc -981 if n > -660\n"
    "eh inc -361 if vb == 578\n"
    "iq dec 304 if obc != -3\n"
    "eh inc 408 if tzy >= -2\n"
    "w inc -576 if tzy == 0\n"
    "iq dec 102 if udh < 7\n"
    "k inc -627 if qet > 558\n"
    "xjo inc -232 if ne == 0\n"
    "azg dec -739 if j > -5\n"
    "a dec -141 if qet == 567\n"
    "a dec -731 if a < 2\n"
    "i dec -839 if as < 8\n"
    "v dec 855 if xbh >= -672\n"
    "wl dec -602 if wl == -721\n"
    "obc inc -613 if ebu == 340\n"
    "j inc 605 if wui >= -148\n"
    "kxm dec -192 if skh > -521\n"
    "skh dec 551 if skh >= -512\n"
    "xbh dec 340 if bx != -9\n"
    "qet inc 156 if w <= -575\n"
    "azg dec 627 if eh < -276\n"
    "qet inc 7 if ne != 5\n"
    "vjx inc -922 if as == 0\n"
    "vjx inc -680 if k <= -623\n"
    "as dec -807 if w != -576\n"
    "tzy inc -808 if qun != 1458\n"
    "wui dec -905 if a <= 740\n"
    "bx inc 371 if n != -655\n"
    "xbh inc 721 if n != -664\n"
    "xbh inc 79 if w == -576\n"
    "udh dec 217 if azg > 738\n"
    "eh dec 300 if a > 721\n"
    "k inc 684 if xbh >= -215\n"
    "i inc -281 if qet >= 717\n"
    "v dec -408 if kxm > 187\n"
    "as inc 923 if xbh <= -202\n"
    "v dec 640 if vjx < -1592\n"
    "kxm inc 537 if xbh < -215\n"
    "xbh dec 426 if eh == -564\n"
    "obc dec -269 if c < 272\n"
    "udh dec -256 if wl == -119\n"
    "xbh inc -519 if v <= -1083\n"
    "eh inc 134 if wl >= -117\n"
    "azg dec 485 if eh >= -576\n"
    "obc dec -134 if as != 925\n"
    "wui inc 549 if udh < 42\n"
    "eh dec -323 if obc >= -219\n"
    "a dec 553 if w < -575\n"
    "vjx dec 311 if qet == 726\n"
    "vjx dec 602 if as != 930\n"
    "tzy dec -588 if udh < 41\n"
    "i inc 479 if eh < -238\n"
    "eh inc 602 if j != 609\n"
    "wl inc -800 if sdw == -811\n"
    "qet dec -493 if k >= 48\n"
    "obc dec -469 if v >= -1084\n"
    "ne dec 100 if skh == -518\n"
    "c inc 574 if tzy >= -225\n"
    "wui dec -390 if bx > -7\n"
    "ebu dec 786 if v < -1079\n"
    "kxm inc -637 if i == 1037\n"
    "as dec 378 if w == -576\n"
    "ne dec -946 if v <= -1092\n"
    "udh inc -433 if obc <= -220\n"
    "azg dec 660 if w >= -581\n"
    "v inc 61 if qun == 1451\n"
    "v inc 644 if v <= -1025\n"
    "udh inc 531 if k >= 52\n"
    "obc inc 381 if n <= -655\n"
    "xjo inc -485 if a != 174\n"
    "tzy dec -526 if obc > 179\n"
    "azg inc -831 if skh == -518\n"
    "sdw dec 288 if sdw <= -808\n"
    "kxm inc 759 if kxm != -451\n"
    "n inc -847 if c > 839\n"
    "skh dec 384 if tzy != -220\n"
    "i dec -532 if obc > 163\n"
    "a inc 570 if eh == 356\n"
    "c dec 437 if wui > 1687\n"
    "i inc -403 if vb >= 564\n"
    "wui dec -223 if azg >= -1238\n"
    "vb dec 370 if vb != 574\n"
    "qun inc -251 if skh == -518\n"
    "n inc 490 if iq < 594\n"
    "kxm inc -542 if v >= -376\n"
    "c dec 49 if kxm == 314\n"
    "a inc -970 if xbh >= -734\n"
    "skh inc -258 if j == 605\n"
    "kxm dec 180 if j == 605\n"
    "j dec 243 if k >= 54\n"
    "vb inc 832 if azg >= -1231\n"
    "udh dec 662 if tzy >= -229\n"
    "c inc -327 if bx != -6\n"
    "obc dec 973 if kxm == 128\n"
    "udh dec 543 if vb <= 196\n"
    "n inc 534 if qun < 1208\n"
    "xjo dec -734 if eh < 362\n"
    "j dec 629 if azg == -1237\n"
    "wl dec -205 if qet <= 1219\n"
    "qet dec -811 if a <= -214\n"
    "azg inc -936 if sdw >= -1099\n"
    "udh dec 222 if azg < -2172\n"
    "j inc -526 if obc < 174\n"
    "ebu inc -725 if n >= -484\n"
    "eh inc 120 if i == 1166\n"
    "wl dec 292 if n >= -487\n"
    "k inc -718 if c == 28\n"
    "qet inc -472 if ne < -109\n"
    "ne inc -426 if qet == 2030\n"
    "a dec 351 if iq < 600\n"
    "sdw inc -446 if qet >= 2023\n"
    "i inc 666 if qun <= 1194\n"
    "obc dec -915 if udh > -315\n"
    "tzy inc 281 if a == -573\n"
    "udh inc -18 if as == 545\n"
    "k inc 767 if as >= 552\n"
    "as inc 84 if xjo != -641\n"
    "vjx dec -321 if qun != 1204\n"
    "v inc 799 if i > 1162\n"
    "qet dec -575 if obc > 1079\n"
    "vb dec -671 if obc < 1077\n"
    "bx inc -976 if vb == 198\n"
    "tzy dec 316 if qun == 1200\n"
    "skh dec -352 if qet <= 2600\n"
    "sdw dec 407 if qet <= 2605\n"
    "c dec -398 if iq != 597\n"
    "i dec 943 if a < -569\n"
    "wui dec -455 if as != 625\n"
    "skh inc 392 if k > -668\n"
    "qun inc 162 if k != -667\n"
    "xbh dec -311 if sdw == -1962\n"
    "sdw dec 219 if wl < -1012\n"
    "vb inc 610 if qun < 1372\n"
    "bx dec 314 if azg != -2170\n"
    "xjo inc 298 if wl >= -1007\n"
    "iq dec -229 if vjx != -2194\n"
    "obc dec -71 if kxm >= 127\n"
    "k dec 936 if n > -485\n"
    "azg dec -282 if v >= 417\n"
    "j dec 8 if qet < 2614\n"
    "j dec 599 if tzy >= -254\n"
    "w inc -111 if v >= 416\n"
    "skh inc -365 if wui <= 2375\n"
    "vb inc 830 if qun <= 1362\n"
    "bx dec -992 if qun >= 1366\n"
    "obc inc -254 if obc != 1150\n"
    "azg dec -557 if udh >= -326\n"
    "c inc -438 if sdw >= -1953\n"
    "eh inc 41 if as < 635\n"
    "eh inc -725 if sdw != -1958\n"
    "azg dec 515 if vb <= 1640\n"
    "vb dec 149 if qet >= 2597\n"
    "a inc 431 if wui < 2381\n"
    "qun inc 596 if c >= -14\n"
    "i dec -520 if a != -151\n"
    "v dec -500 if j == -803\n"
    "wui inc -581 if vjx == -2204\n"
    "vb inc -753 if a < -139\n"
    "tzy inc 309 if j > -796\n"
    "xbh inc -182 if w > -685\n"
    "qun dec -315 if j < -792\n"
    "as dec 688 if eh < -202\n"
    "bx inc -348 if ne > -533\n"
    "n dec 198 if w >= -690\n"
    "eh inc 179 if azg == -2406\n"
    "qun dec -636 if eh == -19\n"
    "skh dec 684 if a == -137\n"
    "i dec -501 if wl < -1005\n"
    "w inc -894 if obc >= 903\n"
    "qun dec 529 if ebu < -1172\n"
    "sdw inc -303 if eh != -34\n"
    "wui inc -912 if bx >= -1630\n"
    "wui inc 222 if bx != -1643\n"
    "ebu inc -907 if c < -17\n"
    "tzy inc -871 if tzy > -256\n"
    "bx inc -119 if iq > 591\n"
    "udh dec 56 if n > -678\n"
    "qun inc -839 if vjx <= -2189\n"
    "udh inc 867 if j < -791\n"
    "w inc 26 if i <= 1247\n"
    "i inc 633 if vb <= 745\n"
    "v inc -384 if skh >= -757\n"
    "ebu inc 876 if ne >= -529\n"
    "udh inc 116 if a <= -145\n"
    "a dec 179 if a >= -146\n"
    "ne dec 643 if c == -12\n"
    "c dec -490 if bx > -1764\n"
    "qet inc 286 if ebu > -291\n"
    "as dec -213 if i < 1884\n"
    "sdw inc -80 if wui != 2597\n"
    "xjo inc 59 if azg != -2406\n"
    "n inc 640 if azg > -2399\n"
    "k dec 444 if wl >= -1006\n"
    "sdw inc -45 if qun != 1437\n"
    "kxm inc -330 if bx >= -1757\n"
    "wui inc 934 if i == 1884\n"
    "qet dec 295 if azg > -2416\n"
    "j inc 435 if xbh > -736\n"
    "a inc -454 if eh >= -36\n"
    "obc dec -533 if iq == 592\n"
    "w inc 388 if ne > -1170\n"
    "wui inc 866 if udh >= 474\n"
    "wl inc -858 if vb != 736\n"
    "wl inc -90 if vb < 745\n"
    "wui dec 794 if vb >= 727\n"
    "w dec -198 if eh <= -22\n"
    "n dec 203 if qun != 1431\n"
    "a inc 252 if bx <= -1757\n"
    "udh dec 589 if vjx != -2194\n"
    "azg inc 10 if azg < -2403\n"
    "vb inc -293 if xbh > -739\n"
    "udh inc -737 if a != -519\n"
    "j dec -582 if obc >= 1433\n"
    "xjo dec -892 if xjo == -337\n"
    "qun inc 668 if obc <= 1443\n"
    "udh inc -124 if bx == -1757\n"
    "azg inc -210 if wui < 2665\n"
    "i inc -312 if wl > -1087\n"
    "ebu dec 356 if k > -2041\n"
    "qet inc 928 if skh == -749\n"
    "tzy inc 299 if i != 1874\n"
    "vb dec 151 if vb <= 447\n"
    "qun dec 936 if eh < -25\n"
    "eh inc 782 if vjx < -2191\n"
    "n inc 515 if j < 226\n"
    "udh inc 482 if obc > 1434\n"
    "azg dec -244 if n < -356\n"
    "n inc -192 if kxm == -196\n"
    "wl inc -573 if bx > -1760\n"
    "sdw inc 423 if vjx >= -2195\n"
    "c dec -72 if wui <= 2670\n"
    "k inc 984 if a == -523\n"
    "eh inc -288 if a > -525\n"
    "ebu dec 855 if a < -514\n"
    "kxm dec -261 if a > -533\n"
    "wui inc -58 if udh == 100\n"
    "sdw inc -304 if skh <= -742\n"
    "vjx dec -86 if qet < 3247\n"
    "w dec 163 if v >= 32\n"
    "kxm inc 231 if ne != -1169\n"
    "vb inc -291 if udh <= 97\n"
    "v dec 759 if iq >= 584\n"
    "xjo inc 390 if xbh < -728\n"
    "bx dec -760 if j > 215\n"
    "wl dec 370 if kxm > 57\n"
    "kxm inc 871 if vb >= 285\n"
    "c dec 4 if n > -556\n"
    "i dec 813 if v > -734\n"
    "v dec 129 if udh <= 100\n"
    "qun dec -762 if ebu == -1150\n"
    "v dec -415 if as >= 151\n"
    "ne dec 366 if obc == 1440\n"
    "udh inc 298 if a <= -533\n"
    "tzy inc -245 if wl != -2038\n"
    "i dec 992 if as > 151\n"
    "c inc -400 if a == -523\n"
    "wl dec 317 if qun < 1933\n"
    "azg dec 174 if tzy < -1067\n"
    "vb dec -780 if vb < 302\n"
    "udh dec 273 if ne < -1166\n"
    "obc inc -669 if wl <= -2354\n"
    "as dec 843 if k >= -1064\n"
    "as inc 902 if kxm < 944\n"
    "qun inc -154 if i >= 69\n"
    "j dec -894 if azg > -2334\n"
    "as inc 233 if w > -1140\n"
    "xjo dec 14 if xjo >= 940\n"
    "sdw dec 999 if tzy != -1066\n"
    "qun inc -351 if wl > -2363\n"
    "kxm inc -503 if qet >= 3230\n"
    "kxm dec -843 if bx != -1003\n"
    "obc dec -318 if sdw > -3187\n"
    "wl inc -243 if n >= -564\n"
    "a inc -873 if sdw < -3179\n"
    "bx dec 602 if wl >= -2601\n"
    "wui dec 237 if c >= 145\n"
    "wui inc -999 if qun >= 1420\n"
    "w dec 329 if bx != -1599\n"
    "a inc -550 if xbh > -735\n"
    "ebu inc 359 if azg != -2328\n"
    "tzy inc 965 if tzy >= -1067\n"
    "wui inc -608 if c >= 141\n"
    "vjx inc -168 if as <= 447\n"
    "qun dec -183 if qet < 3241\n"
    "xbh inc -456 if tzy <= -1069\n"
    "j dec 581 if j != 1110\n"
    "qun inc 677 if udh >= -173\n"
    "udh dec 783 if xjo > 924\n"
    "kxm inc 775 if w == -1132\n"
    "k dec -961 if v == -440\n"
    "qet dec 970 if skh != -753\n"
    "qet dec 566 if vb >= 1064\n"
    "sdw inc -639 if j == 1110\n"
    "ebu dec -22 if kxm <= 2051\n"
    "as dec 9 if tzy == -1072\n"
    "w inc -513 if obc < 1083\n"
    "k dec 669 if sdw <= -3822\n"
    "obc inc -795 if c >= 142\n"
    "n inc -980 if bx == -1599\n"
    "obc inc 176 if qet <= 1697\n"
    "j inc 517 if tzy != -1065\n"
    "wui inc 394 if qun != 2276\n"
    "tzy dec -833 if ne == -1170\n"
    "eh dec 112 if k < -88\n"
    "wui inc -648 if udh > -964\n"
    "wl dec 918 if w < -1125\n"
    "qun dec 846 if skh >= -755\n"
    "sdw dec 287 if tzy == -1064\n"
    "udh inc 902 if as != 443\n"
    "skh dec 793 if ebu > -777\n"
    "w dec 689 if j > 1621\n"
    "j dec 415 if azg == -2326\n"
    "obc dec -869 if k > -101\n"
    "c dec -524 if eh == 353\n"
    "j dec 519 if a > -1949\n"
    "n inc -811 if xbh > -1193\n"
    "udh dec 980 if qet == 1702\n"
    "iq inc 358 if qun == 1428\n"
    "w dec -719 if vb <= 1076\n"
    "wl inc -543 if vjx >= -2284\n"
    "vb inc -778 if wui == 517\n"
    "iq inc -611 if azg != -2330\n"
    "xbh dec 716 if azg < -2326\n"
    "obc inc 997 if tzy > -1067\n"
    "vb inc -645 if kxm <= 2058\n"
    "iq dec -703 if sdw != -3819\n"
    "xjo inc -766 if xjo < 924\n"
    "obc inc 345 if c > 670\n"
    "i dec 435 if qet > 1697\n"
    "kxm inc 895 if ne <= -1173\n"
    "kxm inc 387 if udh < -1041\n"
    "k dec 851 if wui <= 508\n"
    "vjx inc -957 if iq >= -26\n"
    "wui dec -102 if wui < 523\n"
    "ebu inc -441 if qet < 1710\n"
    "qet dec -774 if vjx < -3224\n"
    "skh inc -554 if qun >= 1431\n"
    "xbh dec -924 if sdw < -3816\n"
    "a dec 250 if qun <= 1438\n"
    "xjo dec -430 if wui != 619\n"
    "sdw inc -845 if kxm >= 2044\n"
    "udh dec 607 if a <= -2191\n"
    "w inc -940 if v >= -440\n"
    "w inc -224 if bx == -1599\n"
    "ne dec 856 if v != -441\n"
    "tzy inc 431 if vjx == -3233\n"
    "azg inc 370 if skh <= -2091\n"
    "tzy inc 530 if qet > 2468\n"
    "w inc 371 if vjx != -3233\n"
    "kxm inc 348 if azg < -1959\n"
    "n inc -611 if a <= -2190\n"
    "k inc 365 if c < 681\n"
    "kxm dec -734 if skh <= -2093\n"
    "n inc 243 if w == -2266\n"
    "skh inc 537 if j > 684\n"
    "j dec -127 if wl <= -4066\n"
    "n inc -903 if a > -2199\n"
    "udh inc 685 if kxm == 2785\n"
    "j inc 656 if v > -435\n"
    "vb dec 193 if bx == -1599\n"
    "eh inc -251 if ebu == -1210\n"
    "qun inc 882 if ebu > -1215\n"
    "k dec 705 if w == -2266\n"
    "xbh inc -92 if sdw != -4657\n"
    "w dec -689 if iq != -19\n"
    "qun inc 962 if sdw > -4671\n"
    "wui inc -476 if obc == 1504\n"
    "azg inc 946 if i > -360\n"
    "ebu inc 50 if n <= -3616\n"
    "iq inc -284 if a == -2196\n"
    "vjx inc -470 if v == -440\n"
    "w dec 888 if ebu < -1151\n"
    "a dec 369 if ebu <= -1153\n"
    "udh dec 3 if kxm > 2777\n"
    "qet dec -606 if tzy <= -106\n"
    "kxm inc -483 if sdw <= -4661\n"
    "vb dec 706 if tzy > -120\n"
    "udh inc 111 if kxm >= 2296\n"
    "iq dec 77 if xbh == -354\n"
    "tzy dec -534 if sdw != -4655\n"
    "tzy dec -300 if tzy >= 421\n"
    "ne dec 258 if skh <= -1552\n"
    "qet dec 363 if i == -357\n"
    "ebu dec -16 if bx != -1591\n"
    "eh inc -420 if a <= -2567\n"
    "qet inc 674 if azg >= -1962\n"
    "k inc 891 if azg != -1956\n"
    "ne dec 730 if wl < -4058\n"
    "ebu dec 497 if wui != 147\n"
    "udh inc -969 if j <= 699\n"
    "tzy dec 536 if eh != 101\n"
    "xjo inc -70 if tzy < 193\n"
    "xjo dec -873 if tzy < 188\n"
    "udh inc -923 if k != -442\n"
    "qet dec -56 if tzy != 193\n"
    "wui dec -982 if sdw < -4661\n"
    "iq dec 690 if qet > 3805\n"
    "azg inc -961 if i > -360\n"
    "udh dec 856 if wui != 1113\n"
    "bx inc -710 if j <= 701\n"
    "n inc 914 if i < -360\n"
    "eh dec -772 if qet != 3812\n"
    "ne dec 70 if vb < -470\n"
    "j dec -460 if i <= -355\n"
    "qun dec -837 if c != 674\n"
    "w inc 961 if azg <= -1948\n"
    "ebu dec -192 if k > -439\n"
    "w inc 795 if xbh >= -359\n"
    "wl inc 68 if v <= -436\n"
    "eh inc 555 if qun >= 3288\n"
    "vb inc 322 if eh != 95\n"
    "xjo inc 995 if sdw != -4669\n"
    "k dec 623 if w != -1388\n"
    "udh inc 533 if azg > -1960\n"
    "xbh dec 700 if ebu <= -1441\n"
    "xbh dec 570 if udh > -3070\n"
    "vb dec -434 if w == -1398\n"
    "as inc 173 if bx != -2300\n"
    "w inc 634 if bx == -2309\n"
    "vjx dec -719 if i <= -361\n"
    "w dec -796 if c <= 677\n"
    "i dec -410 if azg != -1956\n"
    "udh inc -738 if as != 602\n"
    "vjx inc -617 if ebu <= -1446\n"
    "ne dec -518 if ne == -3091\n"
    "vjx dec 135 if n == -2704\n"
    "wl dec 78 if tzy == 187\n"
    "tzy dec 753 if wl > -4075\n"
    "ebu dec 679 if c >= 683\n"
    "tzy dec -276 if w <= 34\n"
    "a dec 82 if wui < 1126\n"
    "skh inc 473 if azg < -1948\n"
    "udh inc -26 if tzy < -289\n"
    "xjo inc 407 if eh == 102\n"
    "i dec 909 if kxm >= 2306\n"
    "udh dec -97 if xjo > 3564\n"
    "tzy dec -858 if eh != 110\n"
    "ne inc -102 if c != 678\n"
    "iq dec -655 if iq >= -1063\n"
    "tzy dec -283 if obc <= 1497\n"
    "vjx dec 874 if udh < -3728\n"
    "xjo dec -521 if tzy > 576\n"
    "ne dec -532 if skh == -1086\n"
    "j dec 316 if i != -362\n"
    "sdw dec -256 if vjx >= -4612\n"
    "ebu dec -695 if v > -443\n"
    "azg dec 154 if k >= -1062\n"
    "vjx dec 933 if sdw <= -4399\n"
    "bx inc 696 if iq > -1069\n"
    "skh inc -130 if wui <= 1126\n"
    "eh dec -961 if c >= 669\n"
    "bx inc 482 if k >= -1061\n"
    "vb dec 177 if wui == 1121\n"
    "n dec 169 if i == -355\n"
    "eh dec 29 if xjo == 3558\n"
    "xjo inc 59 if xbh == -1624\n"
    "xjo inc 435 if wl <= -4074\n"
    "udh dec -642 if skh >= -1224\n"
    "iq dec 794 if udh != -3098\n"
    "eh dec -962 if c > 673\n"
    "wui inc 489 if as <= 613\n"
    "iq dec -353 if v <= -435\n"
    "iq inc -293 if n == -2704\n"
    "n dec -667 if vb > 102\n"
    "j dec 763 if eh == 2025\n"
    "kxm inc 100 if i >= -367\n"
    "tzy inc 757 if j <= 82\n"
    "i inc -902 if i != -359\n"
    "ne inc 3 if i < -1261\n"
    "vb dec 272 if qet != 3818\n"
    "skh dec -348 if j <= 76\n"
    "w dec 399 if eh == 2027\n"
    "skh inc 995 if c != 680\n"
    "wl inc 343 if a > -2653\n"
    "eh dec 628 if eh >= 2017\n"
    "w dec 544 if azg >= -2116\n"
    "bx inc 54 if xbh != -1624\n"
    "as dec -724 if vb == -165\n"
    "tzy dec 48 if vjx == -5543\n"
    "sdw inc -837 if as != 1333\n"
    "i inc 692 if obc != 1496\n"
    "k dec -395 if tzy > 1283\n"
    "ne dec -925 if vjx > -5549\n"
    "xbh dec -670 if wl > -3735\n"
    "obc dec 947 if wui >= 1619\n"
    "k dec -480 if sdw != -5245\n"
    "a inc -919 if vb > -158\n"
    "wui inc 8 if qet == 3812\n"
    "i inc -855 if eh == 1397\n"
    "azg inc -41 if j > 74\n"
    "xbh dec -945 if v > -431\n"
    "xjo dec -95 if iq >= -1802\n"
    "w dec -122 if kxm <= 2405\n"
    "xjo inc -721 if bx >= -1833\n"
    "xbh dec -182 if ebu < -751\n"
    "obc dec 694 if wui >= 1614\n"
    "tzy inc 755 if qet <= 3815\n"
    "vjx dec -537 if c < 682\n"
    "v dec 631 if qun > 3275\n"
    "j dec -573 if xjo >= 2895\n"
    "ebu dec 592 if xbh <= -776\n"
    "xjo dec -748 if skh == 128\n"
    "iq inc 30 if j < 657\n"
    "bx dec 693 if sdw <= -5240\n"
    "wui inc -953 if qet < 3817\n"
    "qet inc 969 if xjo > 2909\n"
    "as dec 963 if as < 1344\n"
    "wl inc -997 if as != 372\n"
    "xbh dec 514 if w <= -383\n"
    "tzy inc 343 if xjo <= 2905\n"
    "azg inc 470 if ne < -1725\n"
    "kxm dec 126 if bx >= -2527\n"
    "vjx dec -213 if c != 684\n"
    "wl dec -491 if as >= 377\n"
    "a dec -769 if azg <= -2114\n"
    "obc dec 576 if qun >= 3286\n"
    "udh inc 227 if obc != 805\n"
    "ne inc 528 if v < -1062\n"
    "as inc 124 if skh <= 135\n"
    "a inc -896 if skh <= 131\n"
    "k dec 949 if ebu == -754\n"
    "c dec -541 if iq > -1783\n"
    "wl dec -662 if udh > -2863\n"
    "xjo inc -41 if qun != 3284\n"
    "n dec -486 if iq > -1775\n"
    "vjx dec 982 if obc > 803\n"
    "kxm dec 349 if azg >= -2115\n"
    "ebu dec -19 if bx >= -2515\n"
    "xbh dec 199 if kxm < 1937\n"
    "ebu dec -907 if wl > -4066\n"
    "w inc 196 if bx == -2520\n"
    "bx inc -534 if udh > -2871\n"
    "skh inc 296 if iq < -1777\n"
    "azg inc 169 if v < -1063\n"
    "ne inc -187 if qet >= 3820\n"
    "qun dec -15 if skh != 130\n"
    "skh inc -909 if c < 1220\n"
    "obc dec 583 if obc < 812\n"
    "ebu dec -879 if qun < 3298\n"
    "a dec 818 if obc >= 219\n"
    "sdw dec 169 if as < 505\n"
    "as inc 971 if sdw != -5422\n"
    "wl dec 453 if a <= -4361\n"
    "a dec 584 if udh > -2866\n"
    "n dec 486 if w != -192\n"
    "w dec -423 if iq > -1784\n"
    "ebu inc 681 if as <= 1470\n"
    "skh dec -585 if sdw <= -5421\n"
    "qun dec -569 if n != -2038\n"
    "bx inc -705 if qun >= 3857\n"
    "w inc -198 if iq <= -1773\n"
    "ne inc -345 if k <= -2005\n"
    "vjx inc -368 if n > -2044\n"
    "eh dec -267 if v == -1071\n"
    "j inc 959 if c != 1222\n"
    "c dec -544 if ebu < 1718\n"
    "c dec -14 if xbh >= -1490\n"
    "eh dec -746 if as <= 1458\n"
    "azg dec 746 if tzy <= 2376\n"
    "a inc -306 if c >= 1781\n"
    "i inc 655 if azg == -2692\n"
    "a inc -201 if eh >= 1666\n"
    "bx inc 426 if qet == 3812\n"
    "n dec 234 if c < 1776\n"
    "azg dec -43 if qun < 3867\n"
    "a dec 527 if a == -4945\n"
    "iq dec 317 if qun != 3865\n"
    "iq dec -685 if ne >= -1547\n"
    "azg inc 309 if v == -1071\n"
    "as inc 269 if udh <= -2866\n"
    "a dec 764 if obc == 227\n"
    "eh inc 918 if qun > 3861\n"
    "udh dec 450 if wl <= -4509\n"
    "eh dec -56 if j <= 1615\n"
    "wui dec -557 if wl >= -4519\n"
    "skh dec 479 if bx > -3340\n"
    "skh dec 359 if kxm > 1917\n"
    "as dec -754 if xjo <= 2868\n"
    "eh inc -50 if wui >= 1213\n"
    "xjo dec 883 if j != 1606\n"
    "qet inc -687 if vjx < -6145\n"
    "k dec 899 if udh != -3318\n"
    "azg dec 242 if ebu != 1710\n"
    "w dec -837 if as == 2217\n"
    "ne dec 419 if obc > 225\n"
    "skh dec -258 if qet != 3820\n"
    "kxm dec -149 if azg != -2581\n"
    "qet inc 264 if tzy == 2381\n"
    "xjo dec -46 if qun <= 3866\n"
    "w dec -772 if ebu > 1705\n"
    "eh inc 7 if ne > -1955\n"
    "xbh dec 149 if vb > -159\n"
    "w inc 830 if xjo >= 2906\n"
    "xbh dec -341 if v < -1062\n"
    "obc dec -849 if w == 1633\n"
    "qet dec 632 if ne >= -1959\n"
    "j inc 599 if bx >= -3333\n"
    "ebu dec -326 if vjx != -6133\n"
    "i inc 752 if udh == -3313\n"
    "iq dec 305 if skh < -1366\n"
    "k dec 641 if eh == 2588\n"
    "vb inc -652 if eh < 2597\n"
    "skh inc -926 if v >= -1076\n"
    "j inc -59 if k > -3556\n"
    "wl dec 958 if wui < 1230\n"
    "obc inc 871 if xjo < 2919\n"
    "j inc -220 if k < -3540\n"
    "c dec -411 if qet >= 3806\n"
    "wl dec 874 if w < 1634\n"
    "skh dec 285 if udh <= -3306\n"
    "udh inc 627 if i != -1431\n"
    "bx dec -633 if xbh != -1140\n"
    "i inc -815 if wl >= -6354\n"
    "c inc 892 if qet > 3811\n"
    "wl inc 794 if azg != -2568\n"
    "obc inc 103 if skh < -2566\n"
    "k inc -188 if ebu < 2049\n"
    "k dec -356 if vjx != -6149\n"
    "sdw inc -314 if k > -3384\n"
    "wl inc 198 if j < 1934\n"
    "a inc -533 if i != -2251\n"
    "ne dec -231 if iq <= -1084\n"
    "ne inc -339 if tzy <= 2382\n"
    "kxm dec 641 if w != 1640\n"
    "iq dec 492 if skh <= -2567\n"
    "sdw dec -229 if obc >= 2047\n"
    "skh inc -194 if ebu <= 2041\n"
    "xjo inc 275 if azg >= -2583\n"
    "iq dec 826 if obc == 2053\n"
    "sdw dec -993 if kxm > 1444\n"
    "obc dec 15 if ebu == 2035\n"
    "skh inc 297 if c <= 3080\n"
    "sdw dec 748 if udh == -2684\n"
    "v inc 793 if c <= 3083\n"
    "obc dec -62 if qun >= 3861\n"
    "vjx inc -703 if xjo >= 3188\n"
    "wl dec 68 if ne >= -2077\n"
    "udh inc 199 if iq < -1579\n"
    "azg inc 991 if n == -2271\n"
    "bx inc -554 if vb != -812\n"
    "w dec -754 if kxm != 1445\n"
    "vb inc -301 if iq <= -1582\n"
    "udh inc 849 if wui < 1231\n"
    "qun dec 495 if xbh == -1144\n"
    "n dec -349 if w == 2387\n"
    "n inc 172 if wl < -5416\n"
    "wui inc -192 if wl <= -5426\n"
    "vb dec 676 if kxm != 1436\n"
    "n inc -365 if as >= 2224\n"
    "eh dec -938 if vb != -1492\n"
    "j dec -936 if j >= 1923\n"
    "eh inc -889 if qet != 3802\n"
    "tzy inc 629 if iq <= -1574\n"
    "bx dec -333 if c <= 3073\n"
    "j inc 118 if c <= 3085\n"
    "bx inc 217 if eh >= 2640\n"
    "xbh dec -587 if wl >= -5428\n"
    "kxm inc 9 if tzy != 3011\n"
    "qet inc 433 if c != 3074\n"
    "tzy dec 408 if obc > 2108\n"
    "ne inc -17 if vb >= -1502\n"
    "tzy dec -223 if azg == -1586\n"
    "azg dec -925 if azg >= -1580\n"
    "bx dec -645 if tzy >= 2823\n"
    "eh dec 870 if sdw > -6252\n"
    "obc dec -355 if udh != -1645\n"
    "ne inc -191 if obc != 2477\n"
    "c inc -88 if wl < -5417\n"
    "skh inc -36 if sdw > -6251\n"
    "w inc -404 if sdw <= -6247\n"
    "as inc 126 if vb <= -1491\n"
    "iq dec -456 if c != 2991\n"
    "skh dec -407 if v > -278\n"
    "a dec 621 if iq > -1135\n"
    "xjo dec -514 if kxm != 1447\n"
    "wui dec -912 if iq != -1124\n"
    "xjo dec 373 if c == 2982\n"
    "ne inc 61 if ebu != 2048\n"
    "qet inc -691 if iq == -1125\n"
    "as inc 553 if vjx > -6148\n"
    "qun inc -479 if qun == 3370\n"
    "tzy dec -851 if ebu == 2039\n"
    "xbh inc -52 if skh >= -2514\n"
    "udh dec -853 if wl == -5423\n"
    "udh dec 868 if i != -2245\n"
    "wl inc 665 if w < 1986\n"
    "qet inc -975 if w == 1983\n"
    "kxm dec 677 if kxm < 1446\n"
    "i dec 964 if j != 2978\n"
    "i dec 719 if a <= -7385\n"
    "w inc 142 if qun > 2887\n"
    "xbh inc 547 if sdw >= -6256\n"
    "ebu inc 102 if azg > -1592\n"
    "i inc -255 if v <= -272\n"
    "udh inc 681 if c < 2987\n"
    "a inc 535 if qun >= 2887\n"
    "udh dec -66 if xjo < 3707\n"
    "vjx inc -496 if j != 2985\n"
    "tzy inc -131 if v == -278\n"
    "wui inc 414 if azg >= -1579\n"
    "vb dec -579 if qun < 2896\n"
    "v inc -275 if kxm != 767\n"
    "vb inc -848 if w > 2127\n"
    "j dec -601 if vjx > -6641\n"
    "bx dec 311 if wl < -4756\n"
    "n dec -995 if kxm != 764\n"
    "iq inc -35 if sdw == -6247\n"
    "sdw inc 153 if v >= -271\n"
    "iq dec 219 if j == 3589\n"
    "tzy dec 183 if j > 3577\n"
    "a inc 193 if a > -6858\n"
    "qet inc -847 if xjo >= 3697\n"
    "iq dec -515 if n <= -755\n"
    "j inc -690 if j == 3581\n"
    "v dec -478 if a == -6662\n"
    "n inc 602 if wl < -4753\n"
    "xjo dec 532 if ne > -2213\n"
    "i inc 958 if bx != -3556\n"
    "k inc -587 if a <= -6662\n"
    "c dec -82 if eh > 1763\n"
    "vjx inc 668 if j < 2891\n"
    "ebu inc -357 if as < 2906\n"
    "n dec -283 if ne == -2216\n"
    "w dec 778 if iq <= -640\n"
    "vb dec 408 if ebu < 1784\n"
    "azg dec 271 if vjx != -6639\n"
    "udh dec -46 if ebu != 1784\n"
    "k dec 628 if azg >= -1592\n"
    "vb inc -962 if obc < 2467\n"
    "wl dec 408 if v != 198\n"
    "a dec 554 if vjx < -6631\n"
    "c inc 442 if udh > -1591\n"
    "i dec -417 if eh >= 1763\n"
    "qet dec -856 if c > 3519\n"
    "iq dec -144 if as < 2899\n"
    "sdw inc -229 if skh != -2507\n"
    "i dec -920 if i < -2800\n"
    "qet dec -244 if n != 138\n"
    "vb dec 811 if k != -4600\n"
    "k inc 560 if qet != 1976\n"
    "v dec 42 if w != 1342\n"
    "a inc -588 if skh > -2514\n"
    "qet inc 56 if obc < 2472\n"
    "i inc -870 if eh < 1770\n"
    "ebu dec -915 if w >= 1345\n"
    "xbh dec 455 if i <= -2752\n"
    "xbh dec 384 if xjo <= 3699\n"
    "wl inc -895 if xjo != 3692\n"
    "kxm inc -190 if sdw <= -6475\n"
    "vjx dec 450 if xjo != 3698\n"
    "skh dec 0 if skh > -2514\n"
    "xjo dec 896 if udh >= -1589\n"
    "udh inc 811 if k > -4587\n"
    "eh inc 520 if n != 130\n"
    "iq inc 873 if i == -2756\n"
    "eh dec -76 if skh == -2506\n"
    "ne inc -833 if wl <= -6057\n"
    "tzy inc -687 if xbh == -901\n"
    "n dec -232 if iq >= 223\n"
    "vjx inc -968 if qet == 2032\n"
    "as inc 503 if c == 3512\n"
    "a inc 952 if qun != 2892\n"
    "c dec -290 if wui >= 2128\n"
    "a dec -777 if wui != 2140\n"
    "qun inc -472 if tzy >= 2664\n"
    "vb inc -589 if qet < 2041\n"
    "tzy dec -548 if v > 153\n"
    "wui inc 152 if ebu <= 2706\n"
    "w dec 905 if tzy != 3224\n"
    "udh dec -241 if obc <= 2473\n"
    "v dec -532 if sdw <= -6473\n"
    "bx inc 818 if wui == 2281\n"
    "skh dec 547 if a != -6070\n"
    "qet inc 146 if a <= -6067\n"
    "n inc -528 if iq != 232\n"
    "qet dec -864 if ne < -3044\n"
    "qet inc -121 if azg < -1583\n"
    "i inc 363 if vjx > -7609\n"
    "k dec -105 if ne > -3040\n"
    "a inc 480 if i <= -2398\n"
    "udh inc 173 if ne == -3049\n"
    "n inc -712 if as < 3405\n"
    "j dec 597 if bx == -3565\n"
    "sdw inc -637 if vb < -2311\n"
    "qet dec -871 if obc == 2458\n"
    "tzy dec -927 if bx <= -3560\n"
    "xjo inc -471 if w == 442\n"
    "wl inc 976 if j < 2304\n"
    "tzy dec -505 if xbh <= -894\n"
    "a inc 929 if azg == -1586\n"
    "eh inc -265 if n < -877\n"
    "w dec -393 if obc < 2469\n"
    "a inc 406 if xjo > 2324\n"
    "c inc -437 if j < 2301\n"
    "a inc -589 if i <= -2399\n"
    "c inc -101 if obc < 2471\n"
    "iq inc -478 if iq <= 232\n"
    "xjo dec 635 if v >= 685\n"
    "w dec 485 if vjx == -7604\n"
    "wl dec 490 if eh >= 1571\n"
    "wl dec 923 if k == -4595\n"
    "azg inc -237 if bx == -3558\n"
    "azg dec 820 if vb >= -2322\n"
    "kxm inc -371 if qet < 2918\n"
    "i dec 405 if wl != -6507\n"
    "qun dec -596 if udh > -1178\n"
    "v dec 973 if wui == 2286\n"
    "as dec 840 if sdw <= -7121\n"
    "udh dec 373 if w <= 831\n"
    "ebu dec 372 if iq > -253\n"
    "n inc 469 if qet == 2916\n"
    "udh dec -123 if obc > 2457\n"
    "wui inc 517 if c != 3270\n"
    "wl dec -729 if kxm < 578\n"
    "vb dec 934 if wui >= 2800\n"
    "qet inc -307 if wui >= 2803\n"
    "sdw inc -935 if c <= 3266\n"
    "tzy dec 14 if w < 841\n"
    "k dec 167 if eh <= 1579\n"
    "j dec 438 if bx >= -3573\n"
    "obc dec -452 if azg >= -2415\n"
    "xjo dec -41 if ne > -3056\n"
    "qet inc -482 if qet != 2614\n"
    "obc dec 390 if bx >= -3571\n"
    "v inc 289 if azg <= -2410\n"
    "k dec -777 if azg <= -2397\n"
    "xjo dec 658 if azg <= -2406\n"
    "c dec -681 if ebu > 2332\n"
    "n dec 877 if ebu != 2334\n"
    "ne inc -602 if azg > -2410\n"
    "w inc -334 if eh == 1574\n"
    "c dec 64 if sdw < -8051\n"
    "bx inc -76 if udh > -1043\n"
    "vjx dec -169 if c >= 3263\n"
    "as inc 941 if vb != -3248\n"
    "i dec 131 if xjo < 1084\n"
    "as dec 222 if n <= -1750\n"
    "i inc -249 if wui < 2811\n"
    "obc dec 28 if tzy == 4635\n"
    "n inc -816 if xjo <= 1087\n"
    "obc dec 872 if qet >= 2624\n"
    "vjx inc -201 if ne == -3649\n"
    "eh dec 602 if iq >= -250\n"
    "w dec -596 if i != -3188\n"
    "w dec 212 if vjx < -7436\n"
    "xbh dec 523 if kxm == 577\n"
    "n inc 962 if v <= -281\n"
    "iq dec 30 if c <= 3268\n"
    "obc dec -300 if sdw == -8050\n"
    "vjx inc 125 if eh <= 984\n"
    "sdw inc -470 if j >= 1854\n"
    "vb inc 295 if udh >= -1045\n"
    "skh dec -79 if wui > 2795\n"
    "skh dec 307 if iq <= -272\n"
    "azg inc -74 if j != 1865\n"
    "qun inc 745 if as == 3182\n"
    "i dec -928 if wui < 2809\n"
    "obc inc 63 if wui >= 2800\n"
    "xjo inc 114 if ne < -3644\n"
    "qun dec -92 if as <= 3185\n"
    "obc inc -363 if w != 1211\n"
    "tzy inc 194 if ne == -3651\n"
    "xjo dec 569 if as < 3185\n"
    "i dec 295 if j >= 1848\n"
    "ne inc 946 if w == 1219\n"
    "skh dec -149 if j >= 1866\n"
    "kxm inc -579 if c != 3271\n"
    "a dec -979 if iq < -275\n"
    "xbh dec 281 if k == -3985\n"
    "xbh inc 88 if obc != 2207\n"
    "vjx dec 881 if udh <= -1042\n"
    "i inc 641 if qun < 3117\n"
    "vb dec -132 if vjx != -8192\n"
    "udh inc 952 if obc <= 2195\n"
    "ne dec 562 if iq > -287\n"
    "xbh inc 673 if wui <= 2800\n"
    "bx inc -737 if kxm != 8\n"
    "w inc -766 if wui >= 2798\n"
    "tzy dec 838 if vjx > -8198\n"
    "i inc 435 if obc != 2195\n"
    "a inc -582 if wui > 2796\n"
    "azg inc -87 if vjx == -8194\n"
    "udh dec 634 if ne >= -3274\n"
    "j dec 235 if kxm != -2\n"
    "v dec 143 if vb < -3114\n"
    "as inc 70 if bx > -4308\n"
    "w inc 864 if n < -1616\n"
    "bx inc 959 if n < -1604\n"
    "tzy dec 933 if i != -1469\n"
    "ne dec 369 if ebu > 2320\n"
    "v inc 387 if qet >= 2621\n"
    "qun inc 616 if k != -3985\n"
    "xbh dec 901 if skh != -3276\n"
    "k dec 770 if bx > -3347\n"
    "c inc 345 if azg > -2567\n"
    "sdw inc 485 if udh != -1672\n"
    "ebu dec 697 if xbh == -2515\n"
    "qun inc -223 if obc < 2203\n"
    "vb dec -329 if as == 3250\n"
    "i dec -828 if qet == 2614\n"
    "i dec 457 if ebu > 2317\n"
    "c inc 859 if vb >= -2794\n"
    "vjx dec -324 if xbh < -2519\n"
    "tzy dec 350 if sdw >= -8037\n"
    "wl dec -546 if a <= -4346\n"
    "ne dec -422 if vb <= -2784\n"
    "iq dec 933 if udh == -1682\n"
    "vb dec -354 if w < 461\n"
    "as inc 222 if ne == -3211\n"
    "i inc -488 if c == 4123\n"
    "v inc 466 if bx < -3338\n"
    "vb dec -779 if iq < -1208\n"
    "i inc -54 if i > -1581\n"
    "vb inc -124 if as > 3248\n"
    "qet inc -25 if i >= -1586\n"
    "ebu dec -572 if qet == 2589\n"
    "bx dec 699 if k >= -4763\n"
    "iq inc -184 if kxm != 2\n"
    "kxm dec 986 if xbh <= -2515\n"
    "j inc 904 if vb != -1773\n"
    "a dec 862 if vb == -1778\n"
    "wui inc -604 if ne >= -3223\n"
    "a dec 682 if qun == 2884\n"
    "qun inc -315 if iq <= -1395\n"
    "n dec -930 if qet < 2598\n"
    "n inc -532 if iq <= -1406\n"
    "w inc -921 if xjo > 618\n"
    "bx dec 728 if a > -5891\n"
    "skh dec 463 if sdw > -8038\n"
    "i inc -119 if c != 4128\n"
    "n inc 651 if ebu >= 2894\n"
    "xjo dec 978 if eh != 982\n"
    "i inc -948 if n == -28\n"
    "skh inc -459 if v < 41\n"
    "j inc 625 if kxm == -988\n"
    "skh inc 38 if k >= -4757\n"
    "eh inc 207 if eh > 968\n"
    "k dec 771 if sdw < -8027\n"
    "vjx dec 73 if qet <= 2592\n"
    "j dec -53 if iq >= -1403\n"
    "vb inc 952 if vjx <= -8263\n"
    "azg dec -345 if as > 3240\n"
    "w dec -802 if ebu <= 2901\n"
    "azg dec -861 if iq <= -1394\n"
    "xbh dec 160 if xbh > -2522\n"
    "vb dec 170 if wui != 2201\n"
    "xbh dec -607 if azg <= -1361\n"
    "obc inc -204 if as >= 3245\n"
    "n dec 717 if wl == -5769\n"
    "tzy inc -417 if qet < 2594\n"
    "qet inc 516 if kxm > -990\n"
    "tzy dec -355 if azg < -1356\n"
    "xbh inc 946 if eh >= 1192\n"
    "iq dec 221 if ebu <= 2904\n"
    "c inc -692 if vb > -1006\n"
    "xjo dec -599 if obc < 2004\n"
    "ne inc -255 if vb >= -1000\n"
    "vjx inc 144 if sdw != -8038\n"
    "tzy inc -905 if ne >= -3467\n"
    "j inc -71 if qet < 3108\n"
    "as inc 289 if skh == -4165\n"
    "i dec -621 if azg > -1371\n"
    "xjo dec 703 if w == 334\n"
    "wl inc 657 if azg < -1358\n"
    "n inc 152 if sdw < -8041\n"
    "skh inc 258 if vjx == -8123\n"
    "iq inc -613 if w >= 330\n"
    "azg dec -55 if azg < -1366\n"
    "w inc -504 if n == -745\n"
    "vjx inc -100 if kxm < -996\n"
    "j dec -699 if tzy > 3577\n"
    "wui inc -120 if i > -2038\n";

void perform(std::map<std::string, int> & regs, std::string reg, std::string op, int val)
{
    if (op == "inc")
        regs[reg] += val;
    else if (op == "dec")
        regs[reg] -= val;
    else {
        assert(false);
    }
}

const std::map<std::string, int> execute(const char * input)
{
    // map reg name -> value
    std::map<std::string, int> result;

    eachline(input, [&](std::string line) {
        // e.g. "b inc 5 if a > 1"
        // assume there is always a space between each symbol
        const std::vector<std::string> symbols(split(line));
        const std::string & reg      = symbols[0];
        const std::string & op       = symbols[1];
        const int val      = std::stoi(symbols[2]);
        const std::string & predreg  = symbols[4];
        const std::string & pred     = symbols[5];
        const int predval  = std::stoi(symbols[6]);

        if (pred == "<") {
            if (result[predreg] < predval)
                perform(result, reg, op, val);
        }
        else if (pred == "<=") {
            if (result[predreg] <= predval)
                perform(result, reg, op, val);
        }
        else if (pred == "==") {
            if (result[predreg] == predval)
                perform(result, reg, op, val);
        }
        else if (pred == "!=") {
            if (result[predreg] != predval)
                perform(result, reg, op, val);
        }
        else if (pred == ">=") {
            if (result[predreg] >= predval)
                perform(result, reg, op, val);
        }
        else if (pred == ">") {
            if (result[predreg] > predval)
                perform(result, reg, op, val);
        }
        else {
            assert(false);
        }
    });

    return result;
}


int compute(const char * input)
{
    const std::map<std::string, int> regs(execute(input));
    int result = std::numeric_limits<int>::min();
    for (auto reg: regs)
        if (reg.second > result)
            result = reg.second;
    return result;
}



int execute_find_highest(const char * input)
{
    int highest_value = 0;

    std::map<std::string, int> result;

    eachline(input, [&](std::string line) {
        // e.g. "b inc 5 if a > 1"
        // assume there is always a space between each symbol
        const std::vector<std::string> symbols(split(line));
        const std::string & reg      = symbols[0];
        const std::string & op       = symbols[1];
        const int val      = std::stoi(symbols[2]);
        const std::string & predreg  = symbols[4];
        const std::string & pred     = symbols[5];
        const int predval  = std::stoi(symbols[6]);

        if (pred == "<") {
            if (result[predreg] < predval)
                perform(result, reg, op, val);
        }
        else if (pred == "<=") {
            if (result[predreg] <= predval)
                perform(result, reg, op, val);
        }
        else if (pred == "==") {
            if (result[predreg] == predval)
                perform(result, reg, op, val);
        }
        else if (pred == "!=") {
            if (result[predreg] != predval)
                perform(result, reg, op, val);
        }
        else if (pred == ">=") {
            if (result[predreg] >= predval)
                perform(result, reg, op, val);
        }
        else if (pred == ">") {
            if (result[predreg] > predval)
                perform(result, reg, op, val);
        }
        else {
            assert(false);
        }
        if (result[reg] > highest_value)
            highest_value = result[reg];
    });

    return highest_value;
}



void run()
{
    const char * test = 
        "b inc 5 if a > 1\n"
        "a inc 1 if b < 5\n"
        "c dec -10 if a >= 1\n"
        "c inc -20 if c == 10\n";

    assert(compute(test) == 1);

    const int result = compute(input);
    std::cout << "8.1 " << result << '\n';
    assert(result == 4066);

    assert(execute_find_highest(test) == 10);
    const int highest_value = execute_find_highest(input);
    std::cout << "8.2 " << highest_value << '\n';
    assert(highest_value == 4829);
}

}


namespace day09 {

const char * input =
"{{{{{{{<!!\"!!!>},<>},{<o!>},<u!!i!!'!>,<!!!>,e{'e!!!>},<!i>}},{{<\"o!!\"!>,<>},<!io<>},{{},<!!!>!>,<o\"e!<!!!>{,!!!>{a!o,au!>},<>}}},{{{<"
"e!}>},{{<!>,,e!!!>!!,>},{<a!!!>'!!!>!!!!,!!!>!!!>!>},<<{\"!!>}},{{<!>>,<!>},<i!>!<>},{<!!<u,a\"!>},<o{{!!{!!!>i,!>,<i{!u>,{<a!>e}o!>!>"
"e>}}}},{{<i<!>,<!!!>,<ei,!>a>,{}},{<!!!>},<e'>,{}},{{<!!!!u<,'}!>,<\"o<>}}}},{{{{{{<!>,<"
"o!!!auii!!!!!>!!!>,<{>}},<},!!!>!!!!!>>},{<'u<\"{>,{<!!!!e!>,<'a!!i<!>,>}},{}},{{<i}<!u<{!!!}!!e!{!,>}},{<!!e,!>i>,{}}},{{<"
"i!!!>},<{''i!!!>,!e!>},<!>\"a{>,<!!'u!!!>},<>}},{{{},<i!>},<<!>},<\">},{{<!>,<o!!!!e{uee!!}o<ei{i!>,<!!!>,<>},<,!>},<"
"a!>>},{{},{<}i,!'!!<!!!>}>}}}},{{{{{},{},{{<i!>,<!\"!!!>!!!>''>,{}},{{<!>},<u!a!!!>!u!\"'!!{!!!>!!!>!!i!!!>,<,a!!!>"
"i!>},<\">,{}},{<!!!eoo!!!!ai'!!u!!!>!o>,{<,!!!>aai}{}}\"'>}},{{},<i'ia,!!!>"
"o!>,<\"!!u!>>}},{<!!!>{u!!!>,<,<!>},<'<}<'\"!>},<!u>}}},{{{{<}!!a}!>},<'>},{}},{{{{{},{{<"
"i{!'u}}{>,{{{{<}!>,<!!!!uau!{''!!}ua>}}},{}}},{{{<!!},!!\"\"!!!>,<i!'!{!>},<o>},{<a!u!!\"<!>},<\"!,{<<"
"e!!<!!u!>},<!o!!{}>}}}}},<,o}!>,<!!!!'!'a!!{>}},{{{<<>},{{<ui{!!i!>{'!!!>},<'>}}},{<{!!!>},<!a!e!!!>o'i!!<'!>,<"
"o!!e!!\"!>,<!>>},{<{a>}}}},{{{{<\"{!!!>,e!!!>\"a!!}!!!,!>>},<o!!!>>},{{<o!{}!!!>},<!!,!!\",!>!!!>!>,<ee!>,<!>!u>,<!oo\"u}!!ua!>},<!>},<"
"iie>}},{{<!!!>>},<!!e{!!!!!!!>},<}!!{}!!}<,>}}},{}},{{{<!>!>},<e\",!>,<!>,<!>{!!<!>"
"oi>},{<!>!!!>{}o!!!>!>}a!!>}}}},{{{{},{<\"!!u\">}},{{{<\"e!>,<"
"u{<}>},{}},{<!!!>,!!!>!>,<,!}!!!!'ei!!i,>,{<!!a\"ua!!!>>}}},{}},{{<!!a!!!>!!}eu!!}{{a\"\">}},{{<u!>,<!>},<!!!>"
"oi!!!>!>!>},<'e{u!'}!>,<!>},<!e>,{<u!!!>}!u<!a>}},{{{<!><!>},<!!!>ii,>}}},{<!>u{'!!!>{i!o}}e!!!>},<a!!!>,<>}},{}}},{{{{{{<"
"ao!!>},{}}},{{<\"!!<!>},<>},{<>}}},{<{>},{{<!!!>e!>},<u!!,!!ou}i'e\"i>},{{{{}}},{<o!!'!o!!!!!>!ao{<!>>}}}}},{{{{<}}!!!>o!><}o!!{!!!>"
"i!!,>},{{<!!!>'!!!><!>,<>}}},{{{{<o!>!>},<,!!!>o{i{>},{{{{<!>},<a!uo\",!>,<!>},<e!>{,}!>},<!>,<>}},{}},{}}}},{{<a!>},<\"i!!!!!>,<!!!>\"!!oa!!!"
">!!{!!!!!>!a>,<<{!!!>,<!>\"}!>},<!>,<!\"!!!\"!!ou!>{u!!!>>},{{<<!>,<!!'!!'o\"!!!!o\"}!i>}},{<}!!}!!}<{>,<!!!>,u!>},<o!ae'u!>},<!>},<<"
"u!e>}}},{{{{<!>eui\",o!!!>!>\"i>,{<!!!,!!u!!>}},{{<!<>}},{<'!>,<ia!!!!!>},<ea!!!o!>!!!>!<'!e!>},<>,<>}},{{{{<"
"a!!!>!!!>,<'o>}}}}},{{{<!!!>},<,a'a'!!!>,iu\"'!>,<}>,{}},{{<!>!>,<<!!!!!>>,<!!!>!>>},{{<,!>,<"
"oe!\"!>!!u!',ia'\"!>,<!>,<,>},<<!!!!'!!!}}!!!e!!!>,!>},<}!!!!!>,<>},{<\"ia!!a!!!!}i!>'>,<\"aio!>,<\"e\"e{!!i!!!>o!{!>!!!!\"\">}},{{{{{<\",u!!{"
"!!{!!<!>},<!u!!,!!!!!>!!!!!!!><\"!>},<>},{{<'!\"o,!>},<!>,<\",!!!!uu!!i!!!>!!\"!!!>,<>}}},{{<'!!!!a<<!!!!{u!!,!>},<!>},<o!>},<"
"ouu!!!!!\"!!!>>,<!!!>}'{!!a!!\"!>},<,ao!!!!!!!>!>!!,<!!!>}>},{},{{{<'!!{\"}iu!!e!>!>uo!!}!>,<,!>a>},<<!!!>,!ae!>!>,<a<!!,>}}}},{{{<"
"u!<>},{}},{{{{{{}},<!!!>a!>},<{>}},{<!!<<!>!!!>i!!!>!>},<}{,!!a>,<!>!>\"<,e!ee!>,<}!>}\"!!!>!!!>o>},{{{},{{},{{{},{<<<'!!!>!>u'i,{!!!>!<!!!>"
"a!>,<>}},<!>!!!><!!!!i!!!>}!,\"!!!>!!!>>}}}}},{}}},{{<<eo!!!>!!!!!!!>{{!!!>"
"iou,a'!>,<,>},{}}},{{{}}},{<{!!!>!>,<!!!>},<!!!!}!!!!,a!\"\"}ie!\"a>}}},{<!!!!!>!!'',eu!e!>!!!>!>},<>,{{<e''u!>!>,<"
"a!ui}u!>,<>}}},{{<'>}}},{},{{},{{}},{}}},{}},{{{{{<!!\"\"!!,a<>}},{<',<!!!><!!!!},\"}>}},{{{{<>}}}}}}},{{{<}>,<<u{!>},<!!\"i!aeu!>"
"o\"o}o>}}},{{{{{<u!!ee,e>},{<u!!!>!>,<!>},<o>}},{},{<!>o{!!!!i{!>},<o!>\"!!u}<e\"}!!i\">,<i!!!\"e!>,<!>,<>}},{{{{<"
"u!>},<!!!>'!!!>!!!!!>}{!>}a!>,<u'!>{!!!>'>,<o\"!>,<u>},{<!!uoa>,{{<!!!>,<u}>}}}},{{{{<!>},<!!!><"
"u<>}}}}},{{<!!!<<!!!!,{!!!>!>!!a>},{{<>}}},{<'\"a{a}{!'e!!\"u'u\"!\"o!!!>,<i\">,<!!!>!!!!<u}!>,<}<!!u>}},{{}}},{{{{{<!!!!a!!u<!>},<,e!!!>"
"iu,>,<'a,uu!!'}!!!>},<},a<!!!>e>},<>},{<{'>,{{}}},{<a!>},<!>,<!!,,u!>},<!><,a>,{}}}},{{{{<"
"eu!!!>},<>}}},{{<!!''!>},<}o!!{>},{},{<>}},{{{{}}},{<}!}u!,,!!!!u!!i}!!!><'!!>,<eo>}},{{{{}}},{{{<!'!!\"!>},<{!!!>!i!{e!!>}},{{}}},{<!>"
"ua<<!},!\"!>,<!!<!!!>'e<a>,<!!!>!,!u!>,<}\"<e!!'!!!>},<!!u!<a>}}},{{{{<{!>,<\"!!io!}ei,!!!>"
"o,!>!!}!>,<<'!>,<!!!{>},{}},{{{<!>},<!!\"!!!,i!!oe!!}{!>o\"!>!!!!,a'!>,<>},{{<i!!i!>},<}!!!!!>a}!!!!'}!!\"a>,<!!!>,<"
"e!!!!!>!>,<>}}},{{{},{<}!!eu\"eii>}},{{<!!!>},<>}},{{{<{'!>},<!!!>{>}}}},{<\"o!!!>i,!>},<oo}!!}<!>},<<>,<a!!!!!<>}},{{<,,!>},<e<!>!!!!}i>},<"
"i'!>,<>}},{},{{<,<\"!!!!!!!!!>!'u{>,<{>},{{<>},<{o!>,!!{!!<ooi!!!>,<!>,<!!!}\"e!>,<!!\">}}},{{{{{<au>,{<!>!>,<\"e!},>,{<eo},'!!>}}}},{<"
"e!!>,{<\"!'a{!>{i,!!!>,'!!!>!!!i!i!!!!o!>},<i!!!>>}},{<{!!,!>!>},<\"!>,<uau!!,i!>},<o!>,<\">,{{<',i,!!!>{}oi>},{<ee,!!!>!!!>"
"ai!!!>!>!!'>}}}}},{{{<'!>,<i{!>},<!!i>},{{<a!o!>,<!!!>\"!\"\"'!!\"!>},<e,e'!>},<!!>}},{{<<>},{<u,!>!!>}}},{{},<'\"!>a>}},{{<eo!<'!!'>},{{{<"
"i}<<\"!!!>},<e'!>!!i!!\"e<!!o<u>},{<!>,<o!e\"!!!>io!!,,!!!!!>{!ooo<,a>}},{},{{<!!!>o!!\"e'!!i<!!!><!!<o>}}}},{{{<<"
"e!!!>\"i!!u<'!!a!\"!!!a\"io,!>},<>}},{}}},{{{{{<!!,oe>},{{<u!!!!!>}}!>},<!>},<!>!!!>,<!!>}},{{}}},{{{{<'>},{<uoi<u!!e{>}},{<"
"e!!!!ao}!!!>,<'}o!!\"\"!!!>>}},{<uieoai\"a>}},{{},{{<,!}>},{<!>},<"
"u'!{!>},<{\"a,{{}auo!!{\">}},{{{},{}},{<!!!>,'!>{!!!>!!!!u{!,!>!!!>!!i!!o!a,>,{{},{<!>,<!>,<!>,<\"a\"<,o>}}}}},{{{},{<!e!!!><!!}>}},{{<!>},<"
"o>}}}},{{{<!>,<{i!!'!!!>ii,}>,{<ee!!!>},<o>}},{<!!!!!!!!!>!!{'ao>}},{{{{<!>},<!>\"\",!!!>,'!!!>}oe}},}!>,<>}}},{<!!ie'!!'{i!!i<}'o!!}<>}},{{{<"
"<aeo!!,a!!ui>}},{},{{<'!!<{!o!\"!!!>},<!!u!!!>>}}}},{{{<!!!>!!!>},<!!!>},<!>},<!>"
"i!\">,{{<!!'<!>},<\"u!!!>!!!!!>'>}}},{{{<!>,<}!!!!'!!!!e!>!>},<!!a!uo<aa!!ao,o>,<!!!!e!!!>"
"iu'!!aa!!>},{<'o!!!>{!!!!!>!!}!i!!!>!!!>!!!>!}a}!!\"!i!!!>!!!>>,<\"'<{!>,<!>,<!!<}!!!>!<i!!\"!\"!>,<!>},<<}a>}}},{{<"
"e<>}}},{{{{}},{{<,!>,<}!>},<!!!!a{a>},{<i,a!!!!!>i!!ao!!!>>,<!!!>>}},{{{<>,<eu\"<',!>}!!{!!oa!!!>!u\"'!!!>,<!>,<>},<,ee'}'!!uo!!!>,<}!!'<"
"u{>},{<!!!>!!!>e!!!>},<!>},<\"!>},<!<"
"aa!!!{}\"!>!!,a!>,<!>},<>},{{},{<!o>}}}},{{<!!!>}!>!>,<!>},<<!>,<!>{}<!a!'!!i!aa\"{>,{<!!i!!!>!!ia!>'!oa>}},{{<o!>,<\"!!!e!!<<!>,<!>"
"o!!i>,<!e!>!>,<o<!!!>o!>},<!!!>u!!!>!!>},{},{{{<\"!>,<oao!>,!!!!u!e!!!{}u!!,!!}!!!>>}},{<!!,ei!!!>!}!>}!!ua!>!!!!!>!!!>\"!'!!!\">,<,!!!>,<"
"e!ai!'!>,<,{>}}},{{<a,!!!>,<a!!!>'i!>!!!<!>},<,}!!!!!!o\">,{<!!!>,'e'!!!!!a!!i!u!>},<<'!!!>}e,>}}}},{{{{<{e!a!>},<ui,!!!!{>,<"
"uia!i}aoa<<>}}}}},{},{{{{{<<!!'!!,>},{{<<}\"u!!!!!>o\",!>},<!>},<a>},{}}},{{{<!,'!!<!!!>u!>,<!!!>{!>},<>}},{}}},{{{{}},<!<>},{{{<"
"i!{!>,<!>!>},<}a!>,<a>,{<<!>},<!>},<!!'!>!>!!!>>}},{<>},{<!!!<\"!!<!!!>!!!>,<!>},<<!>},<'>}},{<!{<!>,<a!!ae,!!!>'a!!!>'\"!!!ue!!>,<a<"
"u!>},<{{!!!>o!!!>i{!,>},{{<,!!!>},<'i!>,<u\">},<'!>!>},<{!!{!!!>!>},<o!!ui!>},<!!}>}}}},{{<,\"<e{>},{<!>,<!u!>},<>,<u<!!}o>}},{{{}}},{{{{<"
"a!>},<!!!!!>aeoo\"!>,<>},<e,!a!!i\"ee}!>!>,<>},{},{}}}}}},{{{{{{{<u!>!!',!!!>},<i!>aia!!!!'!>,<\">,<!!!>!>,<!!!>!!ie!>"
"o,<>},{<'!!e\"!!!\"!,\">,{{{<<!!uu>}},<o<i!!!>,>}}},{<!>ueo\">,<i!>},<o<>}}},{{{<!!!!!!!>!!!!!>,!!!>u'!iaa<"
"uu}>}},{<!!'o{!>!>!<'!>},<!>},<!!!>!{o'!!!>>},{<e!u!>,<!!!>!\"!!e}!>},<,i<aea>,{<\"!!!>!!!>!>},<}>}}},{{{{{{}}},<,!!u!>i}u!>,<!!!><!>,<"
"i{>},{{<!>!ai!u>,<!>,!>},<<!!!>i!>},<\"!!u!uu!!{>},{},{<}!!,!!!>i{o\"a!!'ioi>,{}}}}},{{{},{<i,{!!!!\"!{o!>,<ou!!!!'\"!!o>}},{{{<i,!>!!!>,!>,<"
"a!>},<!!a!!!!!>,<<{!!!!>},{<!'!>>}}},{<>}}}},{{{}},{{<,>,{{<!\"a!>,!>,<'a\"!>>},{}}},{{{{<,,e}}i<!!!>{ia'o!>},<"
"a<>,{}}}}}},{{{<\"!!!>\"\">},{{<!>},<<\"a!>,<<{!>},<!!,e,!!!{>}}},{<a\",a!!!i!>},<>,{{<oe!!!>!<"
"eo'e!'!!i,i{!!!!!!!>,<!>,<!!{>}}},{{<!o,!!oi!>,<!!'\"{!\"!!u>},<'{!!!>!>,<,u}!>!>},<!!>}}},{{{{<!>,<!>!!!>!!!>o!!ae!!!!!!!!!>{!>},<!!!>"
"a'au,>},{{{<,!!!>,<!>},<'>}},{}},{<eea!><,>,{<!!!!!>!{!u!>,<u'{!!}!!!!!>u>}}}},{{{{{{{{<!>}\"e!>},<!!'u}>,{<u!o!a<e!!\"o!!!!!!\"!!}a>}}}},{},{"
"<u}u\"!!!!<i!!i}>}},{{<'{!!'!!!>!ii!!o!!!>a!>},<!iu<{a>},<>}},{{<!!<!!!>a}e!>,<!!!!e,,e!<>},<',e!u!!u>}},{<>,<e,!>,<!!uui!>,<>}},{{{},{<"
"a!'!!',,\"o,>}},{<o,!!a>},{<!>},<{!!!!ai!>,<!>,<u!!i!>,<!!<!!!>i}!>e>}},{{<>,{<,'!uu!!!>,!o!!!>"
"u{!!!!!ea,e,>}}},{{{{}},{{<{!>,o!>!>},<,<,!!!><\"}''oa!!!>!>>},{{<{!!uou!!<i>}}}},{{<!!!>,<!'a!!<>},{<!i!!!!!>>}},{{<<\"}!>},<\"{o!>},<'!>"
"ie!!a!!a\"o!>},<!!!>>,{{{<!!i!>,{!!!!!>!!e!!!!i!>,<>}}}},{<aa!!,u,e>,{<!>!>,<<!!!>!<u,>}},{{},{<}io{!,!!>}}}}},{{{{<\"\"'!!!>!!!'{'u!i<>},{<"
"a,e!!o!!!!\">}},{{{<u}a!>},<!>,<!!a!e,<!!ei!>,<,a!!!>,<\">}}}},{{{}},{{{<,<ei!!!>u',\"!!o'!!!>>}},<!>},<\"e,<!!!>!}!o!>},<!!iuo{!>,<"
"u!>},<>}}}}}}},{{{},{{},<!>},<ia!!!>,'!u>}},{{<au'i!!u!!!o!!>,{}},{{<!>!>,<!!e!>e{!!}!!!>\"i!!!<>},<>},{{<!>{,!!,{!!!>\"!!!ea!{u!>o<"
"o>}}}},{{{{{}},<!!!!!!!e!>,<!>,<{<>},{{<o{a{{u!!\">}}},{{},{{<!!!>,<{!!uu!!!>{>,{}},<!!<"
"e!i!!!{!!!>!!\"<,<!>,<!>},<>}},{{{{<!!!!!>'oo!!!>,o>,{<!!!!!>!>,<,!>},<'!>,<ioa>,{{<!!<>},<'i!>"
"a'i!>,<}!!'!>!!\">}}},{{{{}},{<!!!>>}},{},{{<\"u!!u!\"!>,<u>},<u!!!>!>e<<u<!>},<"
"a<!i\",o!{!>,<,>}},{{<!>,<!!!>}!!!>{oiaou!!}eu!!i\">},{{{},<!>},<>},<\"a'}a!>{ao!!!>!!!>!>!>,<!!!>"
"i!!'eo>}}},{{<!!io>}},{<!}e!\">}}},{{{<!a!!i!!e!!!!!>o!>},<!,aa,i\"o!>,<e,>},<a!!{<!!!>!!u!>},<!o{!!!>!>,<!>,<{e>},{{<>},<"
"o!oo>},{{{<,!>,,,o'!o>,{}},{{},{}},{{<!iueieo!!!>!>,<}!>},<'!>},<{!>,<ii>}}},{{{}}},{{<o<!>},<!!,i!>!><!,e!>uo\"e}'<>},{{<,!!'!!!>!!eo!>},<"
"o!>,<!!'oe!!!'ea>}}}}}}}},{{{{}},{{{{{<oeo,!>},<!!}{!o<!>},<!>!>,<oo!>!!!!>}},{{},{{<>,{<!!!>a{,'\"!!a>}},{<}!u\"\"<}ei!!<'e{>,{<i<i!>,<"
"u>}},{{<,!!a,!!!{,}',u\"a!!!>{<iaa>},{{<!!{a'!!!a!>},<u!>,<!>},<!!iiii!!!>,<\"!>,<}!>,<"
"ae>},<}\"!>!!!>{!!i!'aa!!''>}}}}},{{<}!>,<',aa<!!!!<!!>,{<'!!!>'a!!!>!>,<"
"e<!!a,,<\"!!>}},{{<\"!!!!!>,!>},<!>>},<{{!>},<!>,<{!!ee!i>},{}},{<!>!>,<!!!>},<,,!>,<!!'!}!ueeueoaao{u>,<'i}}{!>},<\">}},{<>}},{{},{{{{<"
"u>}},<!>},<!!i'{!>,<!>,<<u{{!>\"!>,<!!!o!>,<!!\"e!>},<>},{}},{{{<,<!!!>!{!>},<<!!!>'!>},<o>,{<,!a<u!>}!!!!!>!!!>>}}},{{<}!>},<!>},<u'!>e<"
"eo,!!!>!\"!!ao!ua>}},{{<a!}'!>},<}'oa!oa!>},<!,a!>u!>a'e>},{{{<!!!!e!>{>},{}},<o>}}}}},{{{<iue!>},<>,<!><,u!!!!!>"
"ae<{{>}},{{<!!!!,!>!>!!!!!>!!'!<!!oo!>,<!>,<!!i!!!>>},<,,!!}!}!>o\">},{}},{{{<i!!eio{{!>,<}>},{<'uou!a{,'i!!!>!>"
"o{>}},{{<\"!>},<!!!!!!!>,>}}}}},{{{{{<'!><!>,<au!!!io!!!>!!!>},<!>,<!!!>!>},<!!!>}!!>},{<\"!>},<!i!>},<,'!!{i!a!!!!!>a\"!!!!a'u!!>}},{<},,!>},"
"<e!!!>\"!>},<<u>,{<>}}}},{{<,<!!!>}<!oi!>}'!>,<'i!>>,{<!{i!!!>uo!!oie>}}},{{{<u'{>}}}},{{{{{{<a!!>}},<a!!\"'!!i,,!!uo!><e!!!>ui>},{{<i{o!!!>"
"a!!!>u!!{ai>,<!>!!!i\"!>},<a{}!>'!!!!''<ae!>a!!!>},<>}},{{<ea'e!>!ao!!!>>,<i!!!>!>!!!!!><u!>}!>"
"a>}}},{{},{},{{<!!ue!>},<'>}}},{{{{{<!<<<,\"o!>,<a<!>},<,>},{<u!!!!!\"!!!!!!\"!>},<!>!!<!!!>,<!a'!!}!!>}},{{<!>},<!>},<!!i{!!!>!>"
"o!!\"u!!o>},{{},{}}},{{{<\"e\"io!!i!>,<i!!!!o\"',>},{{{<!>},<!>},<"
"e!>!>},<!>},<!!,!!}<,<>}}}}}},{{<!!!>,<!!!'a!>,<,\"!o!!!>!>'>},{<}e>}}}},{{{{{},<{o!>,<o{,\"i,!!e!!e!>},<!!a}!>},<>},{<!>!>},<'!>},<i!>,<"
"u!i'!!!>}!!!>!!,oo{>,<u!>},<,{i!>!>,<'u!!!>,<i>}},<\"!>,<!!,,'!!!!i>},{{<u!>i\">},{<'u'''!!!>e!>!!u'!>,<!a!\"!!ua>,<\"!}<"
"u'eo!a!>,<\"}!,}a\"!>},<>}},{{<!>}e!!'!!!>>},{<!!{!>},<>}}}},{{{{{{{}},{<>}},{}},{{{{<!i{!{!!!>\"a!!o!!!>'eo!>},<!>!o!>},<>,<"
"a!\"!>},<!!}!u!!<!!!!,a'<i!>,<!!\"!{o>},<iu{!>,<!\"!u<>},{<,i!>,<,}!>},<!><{!!'!>},<>,<!>!u!!!>!!!!\",!>,<!{}i!!!>"
"e!!e>},{{},<!>},<!>},<'!!'!!!>!>},<}<!!\"!!!>'!>,<{>}},{},{{{<!!e}au\",u!!!>}!!u,}!!!>'!!!!!>'!!!>>,<!>,<oa,!}\"u!>!!o!!a>},{{<!>},<!!{'o!>"
"oo!>!>!!'e!!u,>}}},{{}},{<!>,<\"!!uu!>!!eu>}},{{{<!>},<u!o\"'!!!>!!ue\"ea!}}>,{{<!>'>}}},{{<!>},<!>},<i!!o!>},<ia}ee!!!!ao!>,<!>,<"
"ua>,{<!!!!!>!!!>u,<!>,<e!!ea<>}}},{<'<!>ou'!ao,>,{<a!>,<!!!!i>}}},{<!>,<\"!o!>,<,e!>,<<\"!>,<\",<a>},{}}},{{{<>}},{{},{}}},{{{<!>"
"e!o>},{},{<{ua!>!>,<!}!!,!!!>i'<!!u!!{!>,<>,<!!!>>}},{{{{<!!!!!!!!u!!!>i!a!>!!!!i!!{<!!!!}!>,<!!oo<\"a!!!!!>>},{<!!!>!!aau'!>},<!!a!!{!>},<"
"a>}},{{},{<!>'a}!>,<!!!{!!!>\"!,>}}},{{{{{<\"<<!>},<o{oao{!!!>!}{'!>},<>},<,e,!!!>,<!o!ioiu!!<!>,<e>},{<!u<i,!>\"}!!!>!>>}},<'eoa{'>}},{{<"
"e>},{<>},{<}!>!!o!ue,o{\"!!e'!>!!<!!!>>,{<>}}}},{{{{<!>},<!!a!>,<!!!>!!>},<!>\"e!a<a\"{!>,<!i}<a!>,<}!>>},{<!!e>,{<o{}!i!!<{!!!!{!o'<!>},<!>},"
"<o>}},{{<!!o!>!!!>!>>}}},{{{},{<e,o!!!>!>\"{'u!{e!>},<!o!>},<!!'!!e>}},{{<!!!>\"!}!!!>o!ao'e!}!>!>>}},{<e'!>},<u}!>},<!>},<{<''!!!>"
"u!i'!!!>!>},<!>i>,{{},<!>},<eua,{!!!!\"!>},<u!>},<!>,<!,\"oi>}}},{{<i,{\"}!>,<e,e\"!!!>}}i!{!!!!!>,<>,{}},{{<e!!!>!>,<,!>,<a}u!>!>"
"i!>},<!!a{>},{<u}{}}!!!!!>!!!>{<ae!>,<oo!>,<a{>}},{<\"<'<!!'\"o!!!!i!!i!>},<!>,<!o!!e!>},<!<!!!a>,<!>u!!'!!!>!>,<{{uui!>,<\"!!\"!!>}}},{{{<"
"e!>},<!!\"i!!{ee!!,euu\"<!>,<u!!!>!!u,>},{{<!!!!!><'!,!>ee!>},<<!>,<oa!>,<!!!>>}},{{<u!!!!!>{{i!>,<{oi!><<>},{{<'<"
"o\"!!eo!>!!!>},<>}}}},{{{<!>!'!>,<!!!>e!>!!!u,>,{<!>\"u!!a{!>,<>}},{<e!>},<"
"e!u\",{{ei!>!>,<!!!\"ui,>,{<!!!><!!!!!><}!!\"eo!!!\">}}},{{{<{,!!i!!!!!aa!>,<!>,<>},<ei!>,<oo}!!!><!>,<,!>},<o<!!!>!!!>!u!!!>,>},{{{{<"
"i<,}ii>},<oa!>,<\"eu!!'!!!>!!!!o!!!!!>,<!!!>>},{{{<,>},<'oa!!!!u}e!!}}!>,<ea{\"!>!!,>}}},{{<u!!\"<'>},{<!>},<}!!>}},{{<!>,<>},{<!e!!e!!o{u!>"
"i!>,<',}e\"'>}}},{<!!!>e!!}e{}'}!!>,{}}}},{{{{{<aaae\"'!!\"<u!>},<>}},{<!>u!!au!>,<!!<<'>,<<,o!!!!!>iie>},{{{<"
"uo{}!>,<!>},<>,{<!ie!!o<<!!!!!>!!!!!!>}},<o!!!u!!!>i}<!!!>},<{!>,<!u!!!>,<e'!!{ieu>}}}}},{{{<!!{a!>i{u<}i<!!\"!!!>!!,>},{{{}},<{a!e!>"
"o!<!>\"o>}},{{{<'!!u!!u>},{{},{<!><!e'e!!\"!>>}}},{{<!!!!}{a!!!>!!au{i>},<{e!>!>},<!>},<}o>},{{<!<!>,<}e!e'>}}}}}}},{{{{<e'!i!><!>,<!!'!!<"
"a!>,<,!!!>>}},{<!!<!>},<'iu>,{<e{!u!!!>},<<>}}},{{{<<{,!!,!!u!!}}!!u!!!>i>},{<"
"ae!!!>'o{o\"{!!!<,!!}u!!!>!u!!>}},{<}'!!!>!>\"!!'},}i!>,!>,<'\">}}}},{{{},{{},{<eeuo!>},<>}},{{<'\"!!<e!>,<>,<a'!>,<!!!>},<!!aa!!!>eu!!!>,<"
"i!!!>>},{}}},{{{<i!>!!o!!'>,<!>!aa'!>},<',{>},{}}},{{{{},<{!!!>,<!>,>}}},{{{{<!!!>a'!!u!>,<a}}!>,<!}!>!>,<>},<<"
"e!>,<!>},<!,}}\"!<!!!!!>!\"u>}},{{}}}}},{{{{<!}!!\"o!>},<!!'i}!>},<!>'\"ui{a{>},{<!>},<e!!!>oe!!!><<<,<',!ee!!!!o{>}},{{<!!o'!>,<!!!e}i!}>,<!"
">o!!'<oa>},{{}}}},{{{<!!\"'e{u}>},{{},{<ue'!>!!!!!!}!,'{i,,!,}!>,<!!!>!>,<>}}},{{},{{{<<"
"e!>,<}a!>,<>}},{<!\"!!!>!>!}{ii!>},<{\"e!>},<'aooe>,<!>!>,<!!<i\"!>,<!>a!!!!oa,o>},{<!!!>},<ei!>,<>,<!>},<''i!>!>,<u!!!!}!>>}}},{{},{{<"
"a!!!>!ia!!o!!!>},<!!!>},<!'!!!>ia>,<o{!>oa!!!>}'\"!!a}{!>},<!!!!!>!>,<'}>}}},{{{<\"!>,a,!!!>ui!!!!\">},<{<!!e!!!>"
"i!!a,!!!>'>},{<!>},<!\"e\"}ue!>,<!!}}!!a!>},<!!'}!>,<!<\"u>,<<\"!!!>,'{i\"u!>,<ou,eo>}}}},{{{{{},{{{<!>},<!{!>!!ou}!>,<"
"i!iu!>},<<!!uo<>},<<!u,}a!>!{>},<{!!u<!>,<<!>e'!!!{<e!u!!!>!!a!>,<,>},{}},{}},{{{}},{{{{<!>},<u{\"!!!!>},<!>},<e!!e!>},<!>,<"
"io!!iau!>!!!!!>'!u>},<e!>,<!>,<<e!<u,}e\"!>,<!!!>!>!!>},{{<}i!!>},{<!!\"!!,,,!>,<u\"!!!>,<eo}a\"!>,e'},>}},{}},{{{<!!!>,<a>}},{{{{},<"
"e!!\"!!i!!'!>\"!!!>!>,<>},{<<}u!>},<o'!\"!!u!!!>>},{{<}!!!>},<,o!>ai{\"!>e!!!>},<a>},<<iaa<!>}},\"a!>},<"
"eu>}},{{{<!!!!o'}u!!u!!'e!{!!e!>},<{!{}i!>,<u!>,<>}},<ia!!!!!!!>!>},<!!!>'>},{<!>,<<ee>,{<}!!u{ea}!<e\">}}},{<>,<!!!!o!!!>}<"
"oa\"i!>>}},{{},{{{{<<!!{!!\"!>,<}!!<!\"i!>,<,a,i>},{<{!'<{a!>\"!>},<"
"ue<>}},{<!!!>,<,u!>!!'i!'!>},<,,>,{<,!,!u!>\"!>},<{!>},<}a}'!,>}}},{{<!>!>},<!>{!!!>e!!e!>},<!!<eo!!o'!!!!!>!>,<>},<o>},{{{<!>},<"
"u!!!>!!!>'<{<!>!!'e!>},<a!!!>u}oo>}},{<ee'a,'{!!!!!o!ooi!uu>,{<au!uu,!!}\"!>,<ie<>}}}}}},{{{<}e<!>,<o!au!>},<}!!!>!!!>a}u!>},<!!!>,'}>},{{{<"
"i!>!!!>,<!>!,!>,!eu<a}>},<!'!!!!'!!!>{,>},<u}i!>>}},{}},{}},{{{{},{<,i!!!>!!}!!!>u!!!>!>\">}}},{<!{<!!!>,!>,<!>!>},<"
"i!>},<}!!!i>,<>}},{{{<!>,<!>},<',i}}>},{{<{i!>>}},{{<ei!>,<!>!>,<a!!!>!{!>},<>,{<"
"ae\"'>}},{{<!!!>!>},<!>},<!!ia!!\"'\"!!o!!!>!>,<}'!><!>},<\"!!!>>,<<!!i!>,<!>e'!!!>!>},<uoui!!}u>},{}},{<o!>!!!>!>,<"
"a}eii>}}},{{{{{}}},{{<!'!>},<au,!!!>\">}},{<{oi}!>!>ai!>\">,{<!>},<\">}}},{{{<e!!{!>},<>},{}}}}}}}},{{{{<e<!!!>!!\"o!>},<>},{{{<u!!,,!>},<"
"o!!!!,!!!>},<aii>}},<}{!{a!>uo!>>}},{{{{}},{<e'{e>}},{{<!>!!uo\"o!!i'ae!>},<!!!>,!>,<i!!'>,<!>!!!>"
"u>},{{},{}}},{{{{<!!!>'!>,<,i!!!>>,<!\"e>},{}},{{{<o!!!>},<!!!>!>,<!{a!>e{,!>,<!<o{!>},<!!{>},{{{<''<!!!o!>,<!>"
"i{!!!>}!>},<\"a!!!a!>,<!!!!!\"'a>}},{{<,!!!>,<!!<'}!>,<!!!>{\"\"uu!oo!!e,!>,<'!!a>},{<,\",!>,<>}},{<!!i!>,<!!!!!'!>!!!>\"!!,<"
"o!!{!><!>},<}!o>,{<,!>!'!>{uo!!!>>}}}},{{<o!!}!>,<\"ooi>},{{<iiu,!!o!>,<aa!e<'>,<!!!>,<u!i{u!!!>},<!!!!!>,<!>},<o>},<!e,}'oe'i!>!>"
"e>}}},{{<!><'!>,<i<i'!!!!'<!>},<aoa>},{{<!!!>>}},{{},{<e!!{'{>}}},{{{{}}},{{<e<{i!>},<,!!!>\"!>'a!!''>,{<,!>},<!>,!!\"!>!!!!!!!>\"e!!o!!!>"
"a<!!{!u!>,<>}},{{},{<!!\"!,!!!i!!!>!!o!>,,{!<!!!>\"a\"u!\">}}}}},{{{<a<>}},{{{<!><{!>},<oo!>},<}}!a{!!!!,!>>},{<!!!\"'!!!>ueu!>,<!>,<!>},<"
"e!!!><>}}}},{{{{<'a!>},<!!!>u!!!>!!!>},<!!'\"}a>},<!!'{>}},{{{},{<!>!!!>!!,u<i!>!>},<,'!>},<i,>}},{{<,{a{\"\"!>,<!e!!!>!!,!>}'<}>},{<o!>"
"oa!>},<aa!!oe{!>\">}}}}},{{{<{,u}u<}\"!>},<!e>}}}}},{{{{{},{{{{<!>,<>},{}},{{<<>}},{{<o!e!!'<}!!!>iae!>,<>}}},{<>}}},{{},{{{<a'!>},<>},<!>!!!"
">o!!o!>,<>},{<<a!>},<>}}},{{{{<!>},<!!e,i!!!>,<u<!>},<o<'<!<!!o{!eo>}},{{<oo!>a\"o!!!>"
"u!>},<!a'!!!!!!'!i>},<!!\"{\"!!!><>}},{{<!>,<>},{{<!>!!!>ea!>},<'<{io>},<!!!>!>,<!!!!i{!!!>!}!>!!!>,\",a<"
"a{!e}>}}}},{{{{{{{{<!>,<!!''!>},<{!!{!!!>!!\"!>},<a!,<u>},{{{{<>},<,<o!!!>\">},{{{{<u!uu!!<!!!!}>},<!!!>,'a,{!!!!iie,!!!!>},{<}o'o!<!!!>"
"u!!,<''!!!!>,{<}'\"o,u!!!><u!!!>},<!!!>!}!!!>!!<\">}}},{{}},{<!!!>\"!>},<!>,<e{oi,>,{<!>!!!>!>},<!!,,!!}u!>!!!!!>,<\"!!!>,<,!>,<ie}!>,<"
"i{>}}}}},{{<u}a!>},<!!i!\"<\">},{{{{<{'{!<!>,<!!!>>}},{}}}}},{{<a!!!>>}}},{<!>,<!>,<!!!>\"!>,<"
"i!!u,}{>,<'}!!!\"{!>},<!>},<!!!!i!>},<}a!>\"\"!>,<!!!!!>u>},{<!>,!>,<ie<a!!!>u\"!>,<>}},{{{}},{<}!!a!e!!!>,!!!!!>>,{<!>{,,!,!!o{}''!>},<!>,<!"
"{\"'oo!>>}},{{{{}},<!>},<}ai\"!>},<!!{!,!{}''o!!{!!!>,>},{},{}}}},{{<!}a{i>},{{<}!!!>,<!>,!!!>\"!\"ieia}!>},<'!>,<"
"i>,{<!>,!}!!!!o{a''!>!!!>>}},{<u!!a!'!!}i!!u'!!,,,!!!>{o,>,{<ae!>},<\"u,!!!>},<i!!!!!>},<!>},<!!a!!>}}}}}},{{{<!!,i!!!!ie>,{<!>},<!>o!!!>!'}<"
"oe!!\",!!iu!!!>>,{<!!<!>a','\"!a!!!>i!e{o!>!!'!>,<>}}},{{{},{<<<>,{{{<"
"ai!!!>!!i{e}eia\"!>},<'!>'!e>},{<<,!!>}}}}},{{{},{<,i<}<!!\"!>}>}}}}}},{{},{{<'>},<!!!!!>!>},<}>},{{{<e!>e{<}!>,<<o>}},{<!>,<e<o!>!\"\"!!!>"
"au!>},<o!!!>{!!a}e{!!!>>}}},{{},{{<!!o!>},<i>,<!o!!oae\"!!<!!>}},{}}},{{{{}},{<!>},<{,{{!',a>,<<,!>,<}!>},<!!e!>!!uu\",i<i<"
"u!!\">}},{{{{<!!aoa!>},<e{}!>},<!,!!u}aa>},{}},{{{<!!!>i'!oa!a!!a}'}!!!>e}>},<<!>,<u'!!!!{!!\"<!>,<!!!>}}{u!>,<<\"!!>}},{{},{<"
"i>}}},{{<',!!!>!!!>!>,<>,<i!>aeoao<<!>{!>,<>},{{<,u!!!!e!>>},{{{<u!>},<!>},<!>!>},<!!}{,i<!>!!!>\"\"o<>}},{{<}>},<!>,<}!!!>},<!>,<"
"i,{!>,<\"uo!e!!<!!!>}!>,<>}}}},{{{<,!',u!<,!!\"ie\">}}}},{{{{<!!!><!!<ae<!>>},{}},{{{{{<ui!>!>,<!>{,e!!ee!>,<"
"e!i>,<!!!!!>{aio!!},>},<!!<\"!!!!!!a<"
"ou,>},{<!!,!!!!!o!>!>,<!!e!!!>,!>,<!!aaii!>'<!!!>!>>,<,!{!!!!!>\"io>}}}}},{{<<'!u!>!!'{!!,!!!!i!>}!>!!a,!!!>,<a>,<!!!>!!!>\"!!!>'}!!<<>},{{<"
"oi<!,<!>},<<e!!>},{<\"a}!>>},{<o!>,<<\"i<!!!!!>e'e}i>,{}}},{{<oei!!,!!!>},<,}{!!o>}}},{{},{}}}}},{{<u!!!>"
"oo>,<'e<\"!!>},{{<!!!>{>}},{{{{<}o!!!!\"{i'!!!!i>},{<u!'}<!!i!!i,i!!!>!a!!e\">}}},{<!>},<!>,<'u>}}},{{{{<{{i!>},<>}}},{{<"
"o!!a<>,<!!}!!{!!!>,<{!!!>,<!!u!>,<!!!>,<!>>},{<{o!!<a\"<!>,!!!>,<!>!!,auo}!!!>!!}!!\">,<!!<,\">}},{{<{!>ei'ie!>},<}!!{e!>},<!>},<!!!><o>,<"
"ie,},!>},<{!!<!!!>e\">},{<!>\"!!>,{}},{<{i{u!>},<o!>},<!>},<>,<{!!!!!>!!i!!!!!>!!\"{!>},<<<'o>}}}},{{{{{<ei!>},<!!!>!!!!ia{u!!a}}i\"!>},<"
"ii>}},{{}},{<!i''!!!>!!}!!'!!i!a\"!!>,<i}!!\"aa!!!>!>},<!>!ii!!!>u,}>}}},{{{<u!!!>{'e{ai\"!!}!>},<<!!!!!>"
"e!!!!!>!>,<\">,{<!!!!!'}!>,<'!!!>}\"<'!!!!!>o!!!>i<\"<>,{<e!>{!!!>}!>,<}>}}},{{<u>},{<i!!e!!e!!!>},<!!\"e'{>,{<!!e!<>}}}},{{<"
"u>}},{{},{<!>},<!!!!,'!>\"ie!>},<'u>,{<!>\"e!><{}!>,<!>},<!>},<!!!>}u\"i<!!aa{>}},{{}}}},{{<!a!\"u'\"!!{!>,<!!,!>oe!>,<>},{{<u!!!>!!!>i!!!>},"
"<a,!>!>,<{!!,i!>},<!>},<>,{<{!>,<{!!!>,<{<o>}},{{<i\"!'ai\"!!oa!>,<e!!\"!>},<!!!>!>!!\"!!!>!>!!{>,{<!\"!a!!!>!>!a!!u>}},{{{<e!!\"<"
"u'!!!!!i!!'<!!!>,ai!!}!!!>!>},<!!!>,<>},<!>,<ii,!>}!>},<>}},{<!!!>},<>,{<au!>}!!,u>}}},{{{<!!!>!>},<!>,<!>,<!o!>,<!!!!i!a!!\"i>}},{<"
"i!!i!!!>>},{{<u!!ai!oau'a,'{u>},<!!\"!!!!>}}}}},{{{{{<a!>u\"}\"\"!ei<}o<!>,<>,<'>},{{{<>}},<!>,<!>},<}!{,!>,<!!{!{!!u<!!!>!oo>},{{}}},{<"
"u!!!>!!'u,!!o\"!>,<}i\">},{{{<!>,<\",'!>},<\"{ai!!',!>a>}},<i!!!>},<i!>},<ei!{!!<{!>},<'!>,<{!!!'{o<ue>}},{{{<"
"io!>!!!>},<},io!>,<}!!a}o!>!!!>,!!!'>},{{<!!!>!!!>\"o>},<'!!}>},{{{<!>\">}},{<!!!>e!>,<'{!>}'!<u>,{{}}}}},{{{{{<,!>},<!,'e'!>,<i!\"<i!>"
"aue'}>}},<!u'!!a!>\"!>},<u!>,<!\"<!>,<i!>},<!>},<!!oa>},<!>},<o{!>},<>}}},{{},{{<!>},<!>u\"},!><<a!i!!u>},{<u,a!!<e<{>},{<!>},<!>,<}<"
"u!!!>'>,{<u<}!>},<e!><u!!!!!>!>!>},<>}}}}},{{{{<!!ae>},<>},{{{<!>},<!>},<e'!!u!>,<!!!>!!!>{',iou>}},{{<\"{{!!!>},<'}i!!a!!!>!>,<"
"i!<>},{{<>},<!!!o>}}},{{}}},{{{<!>},<!!!>u!!,!!!!!><>}},{{<}!!\"!>},<!>},<!!a!!!>a!!!>!!!>"
"a!>},<\"iu>},{<\"<<!!{!!!>\"!!a>,{<!>},<!>,<}o!!!!!>\"!>},<!!eua}ie>}}}},{{{<!>!>,<ii!!e!e'{i!!oo!>},<!!!>}{i<u>},<!!<!!}\"!!!>"
"a\"ui}<>},{{<,!>,<iia'o!\"!>!>,<'u!!!}e}e>},<!>},<i!>},<eu!!!>!>!ao!!!>'o!>,<!i{!>,e>},{{{<!!a\"!!<!>,o'>}},{{{<i!>>}},{{<<<!!!o!!,,o<"
"ai>},<!>,<e,!!!>,'>}}}}},{{{<',!>u<}!!u'!>},<ai!!'>},{}},{{<<"
"u!!!>!!!>{!!!>,!>,<!>},<!}!!!>!!!>>},{{<}\",!>},<!>,!',!>!!<>}}},{{{{<{>},<!!!!<{!!!>>}},{{},{<,<uu'{\">}}}},{{{{{<!!!>},<!!}>},<!>"
"i!>!!!!!>!!\"!>},<}!!!{!',o>},{<!!!>a!!!!!>},<!><o'{!>}!!<\"!>},<!>},<!a>}},{{<!u'}!!}!!!<,a\"a!>,<u!!\">}}},{{{<"
"i!>},<!!'}>,<<\"u!>!>!>},<!!!>e!!!>u}>},{<!>},<\"!>,<o!>},<!!u<}>},{<e,oi'!\">,{{<}\"!!!>},<e!!!>a!!!!!><e!!!!!!!>}!'i!o>},{<o!!\"eu<"
"u,!!e!!!!!!!e!\"a!',!!!<ee{!!\"o>}}}},{{{{<!>,<\">},{}},{{}},{{{},{<!!>}},{{<{a!!!>,aa!!!>!>},<!>,<}}!!!>!>},<!!'!!!\"au>},<!!!>!}!!!>,<a'!>"
"o'}!u!>,<',!!oe!!\"!!!!>},{{{{<!!a<}!!\",,!iua!>},<!>\",a'>,<!e>}},<{!!!>!i!!!!''a!>},<!!!>!!u,e,'>},<!>oi!\"!>,<!>},<,o\"e\"o\"!>,<!>>}}},{{"
"<i\"'!!}\"}!!\"u{!{,'u!!>,{<'i!!ea>}},{{<>},<!>,<!}!o!>,<\"}}!>!>o>},{{<o'!!!!{>}}},{{{<o,'!!!>\"<!>},<!!\"ie,{'{!>},<,a>}},{{}}},{{{<"
"o'!!}a!!>,{<u!>{u{uu!'!>,<i!!!!e!>!>},<<!!!>,<a,a>}},{{<e!!!!\"'!>},<o!><>},<!!i!!!>!!!!!><o>},{{{<\"u!!a!>},<}!!!>{!>,<>},<,{!!a!!>},<e<!>"
"o<,!!!>i!!!>!!!>},<}i!>},<!>\"\"!!>}},{{{{{{<{>}},{{<oi,'!>},<>},{{<!!!e!!'e!e!!e,!,!>!!!!!>>}}},{{<!!!>!!!!!!!>,<<a,aa!>},<"
"i>,{{<'!!!>!}!!'a>}}},{<'!>,<e>}}},{{<!>>},<o!>},<'e!!,!>,<!>a<!{>}},{{<!{!!'!!!>},<u!,u{,!!i!e!!'!'!>!!!>"
"oi>,<!u!!!>!!!!!>,<!!\"!>!!!!e,!!<!>,<!!!>i>}},{}},{}},{{},{<!<}<e!>,<!!!>>,{<!>},<!>},<!!!>!>,<'<{',e>}},{<!>u'}!!!>ui!!}\">,<!!e!<!>,<"
"u!ie!!!>!>>}}}}},{{},{{{{},{{<>},{}}}},{{{<\"}!>!!!>>}},{{{<<''!>,<u<\"!o!!!>>},{}},{{<!!!>'\"<!>},<!!!>,<!>,<"
"i!!!>,!!!>!>},<>,{}},{<,{e!!!!!>},<>,<a'!>},<!!}!!!>>},{<>,{}}}}},{{{<<{>}}}},{{{<!>}i{!>},<!>!!!>},<''!>,<"
"u!!u>},<{i'\"!!!>!!!!!>!>!!!>!!i>}},{{{},{{<\"!>,<!!!!!!!>,{{!!ue}!>>},{<!!}!>,<{!>'!>},<o{<!>},<!!!>\",,!!u!!\"o>}}}}}},{{{<!>,<"
"a'i!>,<>,<!!{,<!>},<}e>},{{},{<,!!e>}},{<!!!>,<!>,<'e},!!!>}!>ei{}}!!'{!'>,<,<o,!,iu\"}ue>}},{{<a!>\"eo{!>,<,!>,<!!!!a!>,<'aai!>!>},<i'>},{{{"
"<i!!!\"{i!>,<!>,<!>},<>},{}},{{{{{<!ao!,a}!\"!!!ee!>}!!!>>},<a,!>,<,!>},<a!>,<<\"!!'\">}}},{<!!'!!i!>!>,<>,{}}}},{<"
"o!>},<!'{!>!o!>},<}!!}a!!!>>}}}},{{{{},<o{iu}\"e!!!>,!!\"o!>},<!!!>\"!!a!>},<<!!<,>},{<,>,{<!>},<!!'<\"i!!}!>},<!u<o!!!!!>,<>,{<"
"u<,!!a\"<!>,<!!!o!!aa}i}e}>,{}}}}},{{{{},{<!,u>}},{{<!!i!>!>,<!>},<,!>!>,<e!!u>,{<!'a!!!>,<!!!!,o!{!!i>}},{{{<!!\"o!!!>i{\"!>"
"o!!!!!>>}},<<!!uu!>},<'ou<aeeaie!},i>},{{{<!!'a>},{<!>,<!!!>eae!>,<"
"ou!!u}>,<>}},{<,i\"u}!!'i'!!!>{!>},<!!{o!ii!>\">}}}},{{<!>'ua\"'>}},{{{},{{<!>!!!>a<'>},{<i!>,<!>,<!!!>,<!>},<a,,>,{<>}}}},{<,u!>"
"aa{aeo!e,<>,{<!!>}}}}}},{{},{{{<''>,<}a!>},<ao!>},<{!!\"!!}e}u!!a!>},<{!!u{>},{<ueo>,<}!<>}},{{<aeu!!i}!o!>},<!!!>i'}\"{,<o>,{<"
"ii!!!>},<>}}},{{{{<!>,<!!'o\"o!!!>i{,i>}},{<<\"o,o}!!!aa\"e!!!>o>,<{!>,<ua{a>}},{{{{{},<'ui!!!>,<!!i>}},{<e<}!e!!u>},{<!!!a!!!>oo!!,!!!>,<"
"o>}},{{<'uo}o!!<e!!!>},<u,\"a>}},{{},{{},{<!>>}}}}}}}}";


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

void run()
{
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

    const int part1 = parse(input);
    std::cout << "9.1 " << part1 << '\n';
    assert(part1 == 15922);

    assert(count_cancelled("<>") == 0);
    assert(count_cancelled("<random characters>") == 17);
    assert(count_cancelled("<<<<>") == 3);
    assert(count_cancelled("<{!>}>") == 2);
    assert(count_cancelled("<!!>") == 0);
    assert(count_cancelled("<!!!>>") == 0);
    assert(count_cancelled("<{o\"i!a,<{i<a>") == 10);

    const int part2 = count_cancelled(input);
    std::cout << "9.2 " << part2 << '\n';
    assert(part2 == 7314);
}

}


namespace day10 {

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


void run()
{
    std::vector<int> test_string{0, 1, 2, 3, 4};
    const std::vector<int> test_input{3, 4, 1, 5};
    assert(knot(test_string, test_input) == 12);

    std::vector<int> string(256);
    for (int i = 0; i < 256; ++i)
        string[i] = i;
    const int part1 = knot(string, {102,255,99,252,200,24,219,57,103,2,226,254,1,0,69,216});
    std::cout << "10.1 " << part1 << '\n';
    assert(part1 == 5577);

    assert(knothash("") == "a2582a3a0e66e6e86e3812dcb672a272");
    assert(knothash("AoC 2017") == "33efeb34ea91902bb2f59c9920caa6cd");
    assert(knothash("1,2,3") == "3efbe78a8d82f29979031a4aa0b16a9d");
    assert(knothash("1,2,4") == "63960835bcdc130f0b66d7ff4f6a5a8e");

    const std::string answer2 = knothash("102,255,99,252,200,24,219,57,103,2,226,254,1,0,69,216");
    std::cout << "10.2 " << answer2 << '\n';
    assert(answer2 == "44f4befb0f303c0bafd085f97741d51d");
}

}


namespace day11 {

const char * input =
"n,ne,ne,se,se,se,se,s,se,se,sw,s,s,s,s,s,sw,sw,s,sw,sw,sw,sw,s,sw,sw,sw,nw,nw,n,nw,n,sw,sw,nw,nw,nw,nw,nw,n,s,nw,nw,nw,n,se,nw,n,s,ne,se,n,n,n"
"w,ne,n,nw,nw,n,nw,sw,n,n,n,n,n,s,n,n,n,ne,ne,ne,ne,se,n,ne,n,n,n,n,ne,ne,sw,n,n,ne,ne,ne,ne,ne,ne,sw,ne,se,ne,ne,ne,ne,se,ne,ne,sw,ne,s,n,n,s,"
"se,ne,se,n,se,ne,se,se,ne,ne,ne,ne,ne,ne,ne,se,ne,ne,se,se,se,ne,se,s,nw,se,ne,se,n,se,se,s,se,se,se,sw,n,se,se,se,se,se,se,n,se,s,se,sw,se,nw"
",se,se,se,se,se,se,se,sw,sw,s,nw,s,se,nw,se,se,s,s,se,se,s,se,nw,nw,se,s,se,se,s,s,s,s,se,s,s,s,nw,s,se,ne,s,s,n,s,s,sw,s,nw,se,nw,s,s,s,n,s,s"
",s,nw,s,sw,s,s,s,se,s,s,n,nw,s,s,s,s,s,sw,s,s,se,s,s,s,s,sw,ne,s,s,s,s,s,sw,ne,s,s,s,sw,sw,nw,s,s,s,sw,nw,s,ne,sw,s,s,s,s,s,sw,s,sw,ne,sw,sw,s"
"w,s,sw,sw,nw,s,s,s,s,s,n,sw,sw,ne,sw,sw,s,nw,sw,sw,s,sw,sw,sw,nw,sw,s,sw,s,sw,ne,s,sw,nw,sw,sw,sw,se,sw,sw,sw,sw,sw,sw,sw,se,sw,sw,sw,n,s,sw,s"
"w,sw,sw,sw,nw,sw,sw,se,sw,sw,sw,sw,sw,se,sw,sw,sw,sw,nw,sw,sw,nw,sw,sw,sw,nw,nw,sw,sw,sw,sw,nw,sw,nw,ne,sw,sw,sw,n,ne,nw,sw,se,nw,sw,nw,nw,sw,"
"sw,sw,ne,nw,sw,sw,sw,sw,ne,sw,s,sw,sw,sw,sw,nw,s,se,sw,nw,nw,nw,nw,s,sw,sw,sw,nw,s,nw,nw,se,n,sw,nw,nw,nw,sw,nw,sw,nw,ne,n,se,nw,nw,sw,s,sw,nw"
",nw,sw,sw,s,nw,nw,nw,nw,nw,sw,sw,sw,s,sw,nw,nw,nw,sw,sw,nw,nw,sw,se,nw,nw,nw,sw,s,ne,s,sw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,sw,nw,n,nw,nw,nw,nw"
",nw,s,sw,nw,nw,nw,nw,sw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,s,nw,n,nw,nw,n,nw,nw,nw,nw,nw,s,nw,n,nw,nw,se,n,ne,s,nw,nw,nw,nw,nw,nw,nw,nw,se"
",s,se,nw,s,nw,se,nw,n,n,sw,nw,nw,nw,nw,nw,n,nw,nw,nw,n,n,nw,n,n,nw,nw,sw,sw,s,nw,nw,nw,ne,s,se,n,ne,nw,nw,nw,n,n,nw,n,sw,n,s,n,nw,nw,n,n,se,n,"
"n,nw,n,n,n,nw,nw,n,n,ne,ne,nw,se,nw,n,n,nw,n,n,sw,nw,n,nw,n,n,n,n,n,n,nw,sw,n,nw,n,se,nw,n,nw,n,n,n,n,n,n,nw,sw,n,n,n,nw,n,nw,n,nw,nw,s,nw,n,n"
",n,n,nw,nw,nw,n,n,n,n,nw,n,nw,n,ne,s,n,nw,nw,n,n,nw,n,n,n,n,n,n,nw,s,n,n,nw,se,n,n,n,n,nw,n,n,s,n,se,n,n,n,n,n,se,n,n,nw,n,se,n,n,n,n,n,n,ne,s"
"e,se,nw,n,nw,n,n,ne,se,n,n,n,n,ne,n,n,s,n,n,n,n,s,s,sw,ne,n,n,n,se,n,n,n,se,n,n,ne,ne,n,n,ne,ne,ne,n,n,n,n,n,ne,ne,s,n,n,sw,n,n,n,sw,ne,n,n,n,"
"ne,ne,ne,ne,n,ne,nw,ne,n,ne,n,ne,sw,sw,s,n,ne,n,n,ne,s,ne,nw,n,ne,ne,se,n,ne,n,ne,sw,n,n,ne,ne,ne,n,ne,n,ne,n,nw,ne,n,ne,ne,s,nw,ne,n,n,ne,ne,"
"n,n,n,n,n,n,s,n,n,ne,n,ne,n,n,n,sw,n,sw,ne,s,ne,ne,n,s,n,n,n,n,s,s,nw,ne,s,ne,ne,n,n,ne,ne,n,n,n,sw,ne,n,ne,ne,s,n,ne,ne,ne,ne,n,ne,s,n,ne,nw,"
"ne,ne,ne,n,n,se,n,ne,ne,ne,se,n,ne,ne,n,n,ne,ne,n,se,ne,ne,nw,ne,ne,s,n,ne,ne,ne,ne,ne,ne,ne,ne,n,ne,ne,ne,n,n,ne,n,ne,n,s,nw,ne,ne,ne,sw,ne,n"
"e,s,n,s,nw,ne,s,n,ne,n,ne,n,ne,ne,ne,nw,ne,nw,ne,n,ne,s,ne,n,se,n,ne,s,ne,ne,s,se,n,ne,ne,ne,ne,ne,ne,ne,n,ne,se,ne,ne,ne,ne,ne,ne,ne,ne,ne,ne"
",ne,ne,ne,ne,ne,ne,n,ne,sw,ne,nw,s,s,ne,ne,ne,ne,ne,ne,se,ne,se,se,ne,nw,ne,nw,s,ne,se,se,ne,se,ne,nw,ne,n,ne,s,se,ne,ne,sw,n,nw,ne,se,ne,s,ne"
",ne,s,nw,ne,ne,ne,se,ne,nw,ne,ne,se,ne,ne,ne,ne,ne,ne,s,ne,ne,se,ne,nw,ne,ne,ne,ne,s,ne,ne,n,s,ne,ne,nw,se,ne,s,n,s,ne,ne,nw,ne,sw,ne,se,se,ne"
",s,n,se,ne,s,ne,ne,ne,ne,se,se,n,se,ne,se,se,ne,se,ne,nw,ne,ne,ne,se,n,ne,se,se,ne,ne,ne,ne,ne,ne,ne,s,se,ne,sw,se,n,ne,se,ne,ne,se,se,se,ne,s"
"e,ne,ne,se,se,ne,se,ne,ne,se,nw,se,nw,se,s,se,ne,se,s,se,se,s,sw,se,ne,ne,ne,se,s,ne,se,se,se,se,se,ne,ne,ne,se,se,se,n,se,ne,se,ne,ne,se,se,n"
"e,ne,ne,nw,n,ne,se,n,ne,nw,se,ne,n,se,se,se,ne,ne,se,s,n,ne,s,se,se,s,ne,se,ne,se,se,se,se,se,ne,se,ne,ne,se,se,ne,ne,se,ne,se,nw,n,se,ne,ne,s"
"e,n,se,se,se,se,ne,se,se,se,se,se,se,n,se,se,s,se,se,se,se,se,ne,s,se,nw,se,se,se,ne,se,nw,ne,nw,se,se,se,s,se,se,s,s,s,se,ne,se,se,se,se,se,s"
"e,se,se,ne,se,se,ne,ne,se,se,se,se,ne,sw,sw,se,sw,se,nw,n,se,se,nw,n,se,ne,se,se,n,se,se,se,se,s,se,se,se,se,se,ne,se,s,ne,ne,ne,se,se,ne,se,s"
"e,ne,se,se,se,se,se,se,se,se,s,se,se,se,ne,se,se,s,se,se,se,n,se,se,se,se,sw,se,se,se,se,se,se,ne,n,se,se,se,ne,se,se,se,ne,se,se,s,se,n,se,se"
",nw,se,se,ne,n,se,se,se,sw,se,se,nw,se,n,nw,se,se,se,se,se,se,se,se,se,se,se,s,se,se,se,se,n,sw,se,se,se,sw,se,se,s,se,se,se,se,s,se,se,se,se,"
"sw,sw,se,se,s,se,n,se,n,s,se,se,se,se,ne,s,sw,sw,s,se,se,nw,se,n,s,se,se,se,se,s,nw,nw,s,s,n,nw,se,se,se,se,se,sw,se,s,sw,se,ne,se,se,se,se,nw"
",se,se,sw,n,se,se,se,se,se,sw,se,ne,s,se,nw,s,n,se,se,se,se,nw,ne,se,se,s,se,se,ne,se,se,s,se,se,se,se,nw,s,s,se,se,s,se,se,se,se,s,se,se,se,s"
"w,se,n,n,se,nw,se,sw,se,se,se,se,se,se,se,n,ne,s,se,ne,s,se,nw,s,s,se,nw,se,se,se,s,ne,se,s,se,sw,se,s,se,se,se,se,se,se,se,s,s,se,se,se,s,se,"
"se,se,se,se,nw,se,s,n,se,se,se,ne,se,sw,se,nw,s,s,n,sw,n,se,ne,se,s,se,n,se,se,se,se,se,ne,se,sw,s,nw,s,se,ne,s,se,se,se,s,se,s,sw,s,n,s,se,se"
",se,se,s,se,se,se,se,s,se,se,nw,ne,se,s,s,nw,s,se,s,se,se,se,se,s,se,nw,s,s,se,se,ne,s,se,s,nw,se,n,nw,s,se,s,s,s,sw,ne,se,s,s,nw,se,s,se,s,s,"
"s,s,nw,s,s,s,se,s,se,se,se,n,se,s,se,s,n,sw,se,se,s,nw,se,s,se,ne,ne,se,se,nw,ne,se,se,s,se,se,nw,sw,se,ne,ne,s,s,se,n,s,n,se,ne,s,s,se,sw,s,s"
",se,se,s,s,se,se,s,s,ne,s,sw,se,s,se,sw,s,s,s,se,s,ne,s,n,nw,s,s,s,s,sw,s,s,n,s,s,sw,s,s,se,s,sw,se,s,se,se,n,s,se,s,nw,se,s,se,se,s,nw,s,se,s"
",n,s,s,s,s,s,s,s,s,se,sw,s,s,s,se,s,ne,n,s,se,se,se,ne,s,se,ne,s,sw,s,ne,s,ne,s,s,sw,s,n,s,s,nw,s,sw,s,sw,s,s,s,n,s,s,n,s,nw,s,s,s,s,se,se,s,n"
"e,s,se,s,s,s,s,s,s,s,s,se,s,s,s,s,s,sw,se,s,s,s,s,n,se,s,s,s,s,ne,nw,nw,s,s,se,s,s,s,s,s,s,s,s,s,s,ne,s,se,se,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,"
"n,n,s,s,s,s,n,se,s,n,nw,s,n,s,s,s,s,s,s,s,s,n,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,se,s,s,s,s,n,s,s,s,s,s,sw,s,sw,s,sw,s,s,s,s,s,s,n,s,s,s,s,s,"
"s,s,se,s,s,s,n,s,n,s,s,s,ne,ne,s,sw,nw,s,s,s,s,sw,s,s,s,s,se,nw,s,s,sw,s,sw,s,s,nw,s,s,n,s,sw,s,n,s,n,nw,s,n,s,s,s,s,s,s,sw,n,s,s,s,s,sw,s,s,s"
",s,s,s,nw,se,s,s,nw,s,s,s,s,s,sw,s,sw,s,s,nw,se,sw,s,s,s,s,nw,sw,sw,nw,sw,s,s,sw,nw,s,sw,s,s,s,s,sw,s,s,s,s,s,s,s,s,s,s,s,ne,s,s,s,s,s,se,nw,s"
",s,n,s,s,s,sw,s,s,sw,s,s,s,s,s,s,nw,sw,s,s,sw,n,s,s,sw,sw,s,ne,s,nw,se,s,nw,sw,s,s,s,sw,s,s,s,sw,s,nw,se,sw,s,sw,s,s,s,s,sw,sw,sw,s,s,s,nw,ne,"
"sw,s,sw,n,s,s,se,ne,sw,sw,nw,s,s,s,s,s,sw,sw,s,s,s,sw,sw,s,s,s,n,s,ne,nw,sw,sw,s,s,sw,nw,sw,s,sw,se,s,n,s,s,s,s,s,s,nw,sw,sw,sw,n,nw,sw,s,s,s,"
"se,s,s,nw,s,s,s,s,nw,s,s,sw,s,ne,s,sw,s,sw,s,s,sw,sw,sw,sw,s,s,s,s,sw,s,s,sw,nw,s,s,s,ne,s,s,s,sw,s,se,s,sw,s,s,s,s,sw,s,sw,s,ne,sw,se,s,s,sw,"
"s,n,sw,se,sw,sw,s,s,sw,ne,se,s,se,sw,sw,sw,sw,s,sw,nw,s,s,s,s,sw,n,sw,nw,sw,s,sw,sw,sw,s,sw,s,sw,sw,s,sw,sw,sw,s,sw,s,s,sw,s,sw,s,sw,sw,s,s,s,"
"sw,s,n,sw,sw,sw,s,sw,sw,sw,s,ne,sw,sw,sw,se,s,s,s,s,sw,s,sw,n,n,s,s,se,s,sw,sw,nw,sw,nw,sw,s,s,ne,n,sw,s,s,s,s,s,sw,sw,sw,s,sw,ne,s,sw,se,sw,s"
"w,s,sw,ne,s,sw,sw,sw,sw,sw,sw,s,sw,sw,s,s,sw,s,sw,ne,sw,sw,sw,s,sw,sw,s,s,sw,sw,sw,s,sw,s,se,sw,se,sw,sw,sw,sw,sw,s,sw,sw,sw,se,sw,sw,sw,ne,s,"
"sw,sw,sw,sw,se,s,n,s,s,sw,sw,sw,sw,s,sw,sw,n,se,s,sw,n,sw,sw,s,n,sw,s,sw,n,n,s,ne,sw,sw,sw,ne,sw,sw,sw,sw,sw,sw,s,se,sw,se,sw,sw,sw,sw,sw,sw,s"
",sw,sw,s,s,sw,n,sw,sw,sw,sw,nw,sw,nw,sw,s,sw,ne,s,sw,ne,sw,se,sw,s,sw,n,sw,sw,nw,ne,s,sw,sw,s,se,se,sw,s,se,se,sw,s,sw,sw,se,sw,ne,sw,ne,sw,n,"
"s,sw,s,s,sw,sw,sw,sw,s,s,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,se,ne,sw,nw,sw,sw,sw,sw,sw,sw,ne,sw,s,s,s,s,sw,s,sw,s,sw,s,s"
"w,sw,sw,sw,s,sw,sw,s,sw,ne,se,s,s,nw,sw,n,sw,sw,s,sw,sw,sw,se,sw,sw,nw,sw,sw,sw,sw,sw,sw,sw,sw,s,n,ne,sw,s,sw,sw,n,ne,sw,sw,sw,se,sw,sw,ne,sw,"
"sw,se,sw,sw,sw,n,sw,sw,sw,sw,sw,sw,sw,sw,nw,nw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,ne,sw,sw,sw,nw,ne,s,sw,s,sw,sw,sw,ne,sw,sw,sw,sw,sw,sw,sw,sw,s"
"e,s,se,sw,n,sw,sw,s,sw,n,n,s,sw,sw,sw,nw,sw,sw,sw,sw,sw,se,sw,sw,sw,nw,ne,sw,n,sw,nw,sw,sw,sw,n,sw,sw,sw,sw,se,sw,se,nw,nw,sw,sw,sw,sw,sw,sw,s"
"w,s,sw,sw,n,sw,sw,ne,sw,sw,sw,sw,sw,se,sw,sw,n,sw,sw,se,sw,sw,sw,sw,sw,sw,sw,ne,sw,sw,n,sw,nw,sw,sw,sw,se,s,sw,sw,n,sw,sw,sw,sw,s,n,sw,ne,sw,s"
"w,n,s,sw,sw,se,sw,sw,nw,sw,ne,sw,sw,sw,ne,sw,se,sw,sw,sw,sw,nw,sw,nw,s,sw,sw,sw,sw,sw,sw,sw,sw,ne,sw,ne,sw,nw,s,sw,sw,nw,sw,sw,sw,se,nw,sw,sw,"
"ne,nw,sw,sw,sw,sw,sw,ne,nw,se,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,s,sw,s,s,sw,s,nw,sw,sw,sw,sw,nw,sw,se,sw,sw,se,sw,sw,nw,sw,sw,sw,s,"
"sw,sw,nw,sw,nw,sw,sw,sw,sw,se,sw,sw,sw,s,nw,sw,ne,sw,s,sw,sw,nw,sw,nw,sw,sw,nw,n,sw,sw,sw,sw,nw,sw,s,ne,sw,sw,sw,sw,nw,sw,sw,sw,sw,sw,nw,sw,s,"
"sw,sw,sw,n,sw,nw,nw,sw,se,sw,sw,sw,sw,n,sw,sw,sw,sw,sw,sw,s,sw,nw,sw,nw,s,sw,sw,sw,nw,nw,sw,sw,sw,se,s,sw,sw,nw,sw,nw,sw,sw,sw,n,sw,sw,nw,sw,s"
"w,n,sw,se,sw,nw,nw,nw,sw,sw,nw,nw,sw,sw,ne,sw,sw,sw,n,sw,nw,nw,sw,nw,s,sw,sw,nw,sw,sw,sw,s,sw,n,sw,sw,sw,ne,nw,sw,sw,sw,nw,nw,sw,ne,sw,nw,sw,n"
"w,sw,n,nw,sw,sw,sw,nw,s,s,se,sw,sw,sw,nw,sw,sw,nw,nw,sw,sw,n,sw,n,sw,nw,n,sw,nw,nw,se,sw,sw,sw,sw,sw,sw,ne,s,nw,sw,sw,sw,sw,sw,sw,nw,se,ne,se,"
"sw,nw,nw,sw,sw,sw,sw,ne,nw,sw,sw,sw,sw,nw,sw,n,sw,sw,se,nw,sw,nw,nw,sw,sw,nw,nw,sw,sw,sw,nw,s,nw,nw,nw,nw,sw,sw,ne,sw,nw,sw,sw,sw,sw,sw,se,sw,"
"sw,sw,nw,ne,n,s,s,sw,sw,n,sw,sw,sw,sw,sw,s,nw,ne,sw,nw,sw,sw,nw,se,ne,sw,nw,se,sw,sw,sw,nw,s,sw,sw,sw,s,nw,sw,n,se,sw,sw,sw,nw,nw,s,sw,nw,sw,s"
"w,nw,nw,sw,n,sw,sw,nw,sw,sw,sw,nw,sw,n,sw,nw,nw,sw,nw,sw,nw,nw,nw,ne,ne,sw,sw,sw,sw,sw,sw,sw,sw,nw,sw,sw,sw,ne,sw,sw,nw,s,ne,s,nw,ne,sw,sw,sw,"
"n,se,nw,sw,nw,sw,nw,sw,n,se,sw,sw,nw,s,sw,ne,nw,sw,sw,nw,ne,nw,sw,sw,nw,nw,sw,sw,n,nw,sw,nw,sw,se,sw,nw,sw,sw,nw,ne,sw,se,nw,se,nw,nw,sw,nw,nw"
",nw,se,se,sw,sw,nw,nw,sw,sw,nw,nw,sw,nw,nw,sw,sw,s,nw,nw,sw,nw,sw,nw,sw,sw,sw,nw,sw,se,n,sw,nw,nw,sw,nw,sw,ne,nw,nw,sw,sw,nw,nw,nw,sw,nw,sw,sw"
",n,nw,nw,n,nw,nw,s,sw,se,nw,sw,sw,sw,sw,nw,sw,sw,sw,sw,se,s,sw,sw,nw,nw,s,nw,nw,sw,nw,ne,nw,nw,nw,sw,nw,ne,sw,ne,nw,sw,sw,s,sw,ne,sw,sw,sw,nw,"
"nw,sw,nw,nw,nw,sw,nw,nw,sw,nw,nw,nw,se,nw,nw,nw,sw,nw,nw,sw,sw,sw,nw,sw,ne,se,nw,sw,nw,sw,ne,nw,sw,n,sw,nw,nw,nw,nw,nw,nw,nw,ne,nw,nw,sw,sw,sw"
",sw,se,n,sw,nw,n,nw,nw,s,ne,nw,n,nw,n,nw,nw,nw,s,nw,sw,sw,nw,s,n,ne,nw,ne,nw,nw,nw,se,ne,n,s,sw,sw,sw,sw,nw,nw,ne,sw,nw,n,ne,nw,nw,nw,sw,nw,nw"
",nw,nw,sw,nw,nw,sw,nw,se,nw,nw,nw,nw,ne,n,sw,nw,nw,nw,nw,sw,sw,nw,nw,sw,nw,s,nw,nw,s,nw,sw,sw,sw,nw,ne,s,nw,sw,sw,nw,s,sw,nw,sw,sw,nw,s,nw,nw,"
"nw,se,nw,nw,sw,sw,sw,sw,sw,nw,sw,s,nw,se,nw,ne,se,sw,sw,nw,nw,nw,nw,se,nw,nw,s,nw,nw,n,nw,ne,nw,nw,nw,nw,sw,s,nw,nw,nw,nw,s,sw,sw,nw,nw,nw,nw,"
"sw,nw,n,n,sw,sw,nw,sw,nw,nw,sw,nw,s,nw,ne,nw,nw,nw,nw,nw,nw,sw,n,sw,nw,nw,nw,nw,nw,nw,sw,nw,nw,ne,nw,nw,se,nw,sw,nw,nw,ne,nw,nw,nw,n,nw,nw,nw,"
"sw,nw,nw,nw,nw,nw,sw,nw,sw,nw,nw,sw,ne,nw,n,ne,sw,nw,sw,nw,nw,nw,nw,sw,nw,n,nw,ne,nw,sw,nw,nw,sw,sw,nw,sw,nw,nw,nw,nw,se,nw,se,nw,nw,nw,sw,nw,"
"nw,nw,nw,n,s,nw,nw,nw,nw,nw,nw,sw,nw,nw,nw,nw,sw,sw,nw,sw,nw,nw,sw,sw,nw,nw,nw,nw,ne,nw,nw,sw,sw,nw,s,nw,sw,nw,ne,nw,nw,nw,nw,nw,nw,nw,sw,nw,s"
"w,s,nw,nw,nw,nw,nw,n,nw,s,ne,nw,nw,sw,se,nw,nw,nw,s,nw,n,se,nw,nw,nw,nw,s,nw,n,sw,nw,s,nw,sw,nw,sw,nw,nw,nw,nw,nw,nw,n,sw,nw,nw,nw,n,nw,nw,nw,"
"nw,ne,nw,nw,nw,nw,nw,nw,nw,sw,nw,nw,nw,nw,nw,nw,nw,sw,nw,nw,ne,nw,nw,nw,nw,nw,sw,nw,nw,nw,sw,se,sw,nw,sw,ne,nw,nw,nw,nw,nw,nw,sw,n,nw,nw,sw,nw"
",nw,nw,nw,ne,nw,nw,nw,nw,nw,sw,nw,nw,nw,nw,nw,se,nw,nw,nw,sw,nw,sw,sw,nw,nw,ne,nw,s,sw,nw,nw,nw,nw,nw,nw,sw,nw,nw,nw,nw,nw,nw,nw,s,nw,nw,nw,nw"
",nw,nw,ne,nw,nw,nw,s,nw,nw,nw,nw,n,nw,nw,nw,nw,nw,nw,s,nw,nw,nw,n,nw,nw,nw,nw,nw,nw,nw,nw,s,nw,nw,n,nw,nw,nw,nw,se,nw,n,ne,nw,nw,nw,n,nw,nw,nw"
",se,n,nw,ne,n,nw,n,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,se,nw,s,nw,nw,nw,nw,ne,nw,nw,n,n,nw,nw,sw,nw,n,s,nw,nw,nw,nw,nw,n,s,n"
"w,nw,nw,nw,s,nw,n,nw,nw,nw,sw,nw,n,nw,nw,se,s,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,s,nw,nw,sw,se,s,nw,nw,nw,sw,nw,nw,nw,n,nw,n,nw,nw,nw,nw,nw,n"
"w,nw,ne,n,n,nw,n,n,nw,nw,se,nw,nw,s,s,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,nw,n,nw,nw,n,nw,nw,nw,sw,nw,nw,nw,se,nw,nw,nw,nw,nw,nw,n,nw,n,n,nw,ne,se,s"
",nw,nw,nw,nw,nw,nw,sw,nw,sw,n,nw,ne,nw,n,nw,nw,nw,ne,nw,nw,nw,nw,nw,n,nw,nw,n,nw,nw,ne,nw,nw,nw,se,nw,n,nw,nw,nw,nw,sw,nw,nw,nw,nw,nw,nw,nw,ne"
",nw,nw,nw,nw,nw,n,nw,sw,nw,n,n,nw,nw,se,n,n,nw,nw,nw,ne,se,n,se,nw,nw,n,se,nw,nw,n,ne,n,nw,nw,n,nw,nw,n,n,nw,nw,sw,nw,nw,n,nw,n,nw,n,nw,nw,nw,"
"sw,nw,nw,nw,nw,se,nw,nw,nw,nw,nw,n,nw,nw,n,s,n,ne,n,ne,se,nw,nw,n,nw,s,nw,nw,n,nw,nw,sw,nw,sw,nw,nw,nw,n,nw,nw,ne,nw,ne,se,sw,n,sw,n,nw,nw,nw,"
"nw,ne,se,nw,nw,nw,nw,n,nw,nw,nw,nw,sw,nw,sw,n,nw,n,n,nw,n,nw,nw,n,nw,nw,nw,nw,nw,nw,sw,nw,nw,s,nw,nw,nw,n,n,nw,se,n,n,nw,nw,ne,sw,nw,n,n,nw,n,"
"n,nw,nw,sw,n,nw,nw,nw,n,nw,nw,nw,nw,n,nw,n,nw,nw,nw,nw,nw,nw,n,n,n,nw,nw,nw,n,nw,nw,nw,nw,n,nw,nw,sw,s,nw,nw,nw,n,nw,n,n,nw,se,se,ne,nw,nw,s,n"
"w,n,nw,nw,nw,n,s,nw,nw,s,nw,se,se,nw,nw,n,nw,n,nw,sw,nw,nw,s,nw,n,nw,se,ne,nw,nw,nw,s,n,nw,nw,nw,n,nw,ne,nw,n,s,nw,nw,nw,nw,s,n,n,nw,nw,nw,se,"
"nw,n,nw,nw,n,nw,nw,nw,nw,s,nw,nw,nw,nw,nw,se,ne,nw,nw,sw,n,nw,sw,nw,s,n,nw,ne,nw,sw,nw,nw,n,nw,nw,nw,n,nw,nw,se,n,n,sw,sw,nw,ne,nw,n,nw,ne,nw,"
"nw,s,nw,nw,nw,n,sw,n,se,s,n,nw,nw,nw,nw,nw,nw,n,nw,n,s,n,n,nw,nw,nw,n,n,se,nw,n,ne,n,nw,n,nw,nw,nw,nw,n,n,n,ne,nw,nw,sw,n,n,nw,nw,nw,nw,ne,n,n"
"w,nw,n,nw,se,nw,nw,nw,ne,nw,nw,nw,nw,nw,nw,nw,n,n,n,sw,nw,n,n,ne,se,sw,nw,n,nw,n,sw,nw,sw,n,n,n,nw,nw,nw,n,sw,nw,n,nw,nw,n,nw,n,n,ne,nw,n,n,n,"
"nw,nw,nw,nw,n,nw,s,nw,n,nw,nw,n,ne,n,nw,n,n,s,nw,nw,n,s,ne,n,nw,ne,nw,nw,ne,n,nw,n,nw,nw,nw,nw,nw,ne,s,se,ne,nw,ne,nw,n,n,nw,n,n,nw,n,nw,nw,n,"
"nw,s,ne,nw,n,s,n,nw,nw,nw,n,n,nw,n,n,nw,nw,ne,nw,nw,nw,n,se,n,nw,n,n,nw,se,nw,ne,nw,n,nw,nw,n,n,n,se,n,nw,ne,n,ne,n,ne,nw,n,n,se,nw,n,n,n,nw,n"
",ne,n,nw,n,n,se,nw,nw,n,n,s,n,ne,n,nw,sw,n,nw,n,s,n,n,nw,ne,ne,n,sw,n,nw,n,nw,nw,n,n,sw,nw,nw,nw,nw,sw,n,nw,n,nw,n,nw,n,nw,n,n,nw,n,nw,nw,nw,s"
"w,nw,nw,nw,nw,n,n,n,se,s,ne,nw,nw,n,nw,s,n,nw,n,ne,nw,n,nw,n,ne,nw,ne,n,ne,se,n,nw,n,nw,nw,n,nw,s,s,n,nw,nw,n,n,n,nw,nw,n,nw,nw,nw,n,n,n,s,nw,"
"nw,n,nw,nw,n,nw,n,sw,n,n,s,nw,nw,sw,nw,nw,nw,n,n,n,nw,nw,s,nw,nw,nw,nw,s,nw,n,ne,n,nw,n,n,nw,nw,s,n,nw,sw,nw,nw,nw,nw,nw,nw,nw,n,nw,nw,n,nw,nw"
",sw,s,se,n,ne,nw,ne,s,nw,nw,se,n,nw,nw,n,n,nw,nw,n,nw,n,n,nw,nw,n,nw,nw,sw,sw,se,n,n,s,se,se,nw,se,n,n,se,ne,n,nw,nw,nw,n,n,n,nw,n,sw,n,nw,n,s"
"e,se,n,nw,n,sw,n,se,n,n,n,nw,n,nw,n,ne,n,n,nw,nw,n,n,se,n,n,n,n,n,nw,n,n,n,n,nw,nw,n,n,nw,nw,n,nw,s,n,n,n,nw,nw,se,se,n,n,se,n,nw,nw,ne,sw,ne,"
"sw,n,n,sw,nw,nw,se,n,se,sw,sw,nw,n,nw,n,nw,nw,n,n,nw,se,n,nw,n,ne,n,n,nw,nw,n,nw,n,nw,se,n,n,n,n,s,s,n,n,s,nw,nw,nw,nw,nw,nw,nw,n,ne,se,n,nw,n"
",n,n,n,nw,nw,n,se,sw,n,s,n,n,n,nw,se,nw,n,n,n,ne,nw,n,n,nw,n,n,n,nw,n,n,n,n,n,n,n,n,se,n,sw,sw,nw,nw,nw,n,nw,nw,n,n,n,sw,s,n,nw,n,n,nw,n,nw,n,"
"nw,n,nw,n,n,sw,n,n,n,n,n,n,nw,n,n,nw,nw,n,n,nw,n,n,nw,n,n,ne,n,n,n,n,n,se,n,sw,nw,nw,n,n,n,s,n,n,nw,n,n,n,n,n,n,n,se,n,n,nw,sw,nw,ne,n,nw,s,n,"
"n,n,s,n,nw,nw,n,sw,n,n,sw,n,n,s,n,n,n,n,n,n,n,nw,n,n,n,n,n,n,n,nw,sw,sw,ne,n,s,nw,n,nw,sw,nw,ne,n,n,n,n,n,nw,se,n,nw,n,n,ne,sw,n,ne,n,n,n,n,n,"
"n,n,nw,n,n,n,nw,n,nw,n,n,n,n,nw,n,n,nw,nw,n,n,n,se,se,n,n,s,sw,n,se,n,n,nw,n,n,n,s,nw,n,n,se,n,nw,se,sw,n,n,ne,n,n,n,n,n,sw,nw,n,nw,n,n,n,nw,n"
",nw,ne,n,n,n,n,n,n,n,se,nw,nw,n,n,n,n,sw,n,sw,s,sw,nw,nw,nw,n,n,sw,nw,n,n,n,n,n,n,n,n,s,nw,n,n,n,n,n,n,nw,nw,nw,s,n,n,n,nw,ne,n,n,ne,s,n,n,n,"
"s,n,n,n,n,sw,sw,nw,n,n,n,n,nw,ne,n,n,s,se,n,n,n,nw,n,n,s,n,n,n,n,n,n,nw,n,n,n,n,sw,n,n,nw,s,se,n,nw,n,n,nw,n,nw,nw,n,ne,sw,nw,se,nw,n,n,n,n,n"
",sw,nw,n,n,n,n,n,n,nw,n,n,n,nw,n,nw,n,n,s,n,n,nw,sw,n,n,n,n,s,nw,nw,n,n,se,n,n,n,n,n,n,n,sw,nw,n,n,n,n,n,s,n,sw,n,sw,sw,se,sw,n,sw,n,n,nw,n,n"
"e,n,s,n,n,n,n,n,n,n,s,n,n,s,n,n,se,n,n,n,n,n,se,nw,se,sw,n,s,sw,n,n,n,se,n,ne,n,n,n,n,n,n,nw,se,nw,n,n,n,n,sw,nw,sw,s,se,ne,s,sw,se,se,s,nw,s"
"e,se,se,se,n,se,ne,se,ne,ne,sw,ne,se,n,ne,ne,sw,n,ne,n,n,n,n,n,n,n,se,n,ne,n,n,n,n,nw,n,nw,n,nw,se,nw,nw,sw,nw,n,s,nw,se,sw,nw,nw,nw,nw,nw,nw"
",nw,nw,ne,nw,nw,sw,nw,ne,nw,se,sw,sw,sw,nw,sw,nw,sw,sw,se,sw,nw,se,sw,sw,sw,sw,sw,n,sw,sw,n,sw,sw,s,n,nw,sw,s,sw,sw,n,sw,s,se,sw,s,s,n,sw,s,n"
"e,s,n,s,n,n,s,sw,sw,se,s,n,s,s,ne,s,s,sw,sw,s,s,s,s,sw,sw,s,nw,s,n,s,n,s,s,ne,s,s,s,se,ne,se,s,sw,s,nw,sw,s,s,se,se,nw,se,se,se,se,s,se,se,ne"
",s,s,se,se,se,se,se,se,se,nw,se,s,s,se,se,nw,nw,s,sw,ne,s,s,s,se,se,s,se,nw,se,ne,se,ne,n,s,ne,se,se,s,sw,ne,se,se,se,se,nw,se,sw,se,se,s,se,"
"se,se,sw,s,se,se,se,se,se,nw,sw,se,se,n,se,se,se,se,se,se,se,ne,se,se,ne,ne,se,se,se,ne,se,se,n,ne,ne,se,se,sw,sw,n,se,se,ne,ne,ne,ne,ne,ne,s"
"e,ne,se,ne,se,ne,n,se,se,se,ne,se,ne,se,n,ne,ne,ne,ne,se,ne,sw,se,ne,ne,ne,ne,s,ne,se,ne,n,ne,se,ne,se,n,se,ne,ne,ne,s,se,n,ne,ne,se,ne,ne,s,"
"ne,ne,ne,s,ne,nw,ne,sw,ne,ne,ne,ne,nw,ne,sw,ne,ne,ne,ne,s,n,n,ne,s,ne,ne,ne,ne,ne,ne,ne,n,n,n,n,s,n,ne,ne,ne,ne,nw,ne,se,ne,ne,n,n,ne,ne,ne,n"
"e,n,ne,n,ne,sw,nw,se,ne,nw,ne,n,n,ne,s,s,n,nw,nw,nw,se,ne,ne,se,n,ne,n,n,n,n,ne,ne,n,se,n,sw,n,n,n,s,ne,ne,ne,n,ne,n,n,n,s,nw,s,n,n,n,n,n,nw,"
"n,n,s,ne,n,n,n,ne,n,n,n,s,ne,n,s,s,n,ne,n,n,ne,ne,n,n,se,n,n,ne,n,ne,sw,nw,n,n,n,ne,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,s,ne,n,n,sw,n,n,n,n,nw,n,nw"
",sw,se,n,n,n,n,n,n,n,sw,n,nw,n,nw,nw,nw,n,n,n,ne,nw,n,n,nw,n,n,n,sw,n,s,nw,n,n,n,n,n,n,n,n,n,n,n,n,n,nw,n,nw,se,n,n,nw,s,se,n,sw,n,n,n,sw,n,n"
",n,nw,se,sw,n,n,nw,nw,n,nw,n,s,n,se,nw,nw,n,n,n,nw,n,nw,nw,se,n,nw,nw,nw,nw,n,n,nw,s,n,n,nw,n,n,nw,nw,n,nw,n,nw,nw,nw,n,nw,n,n,nw,s,nw,nw,ne,"
"n,nw,n,sw,nw,n,sw,sw,sw,n,nw,n,nw,nw,n,s,nw,nw,nw,s,nw,ne,nw,n,nw,n,nw,nw,nw,n,nw,n,n,nw,nw,n,nw,n,nw,nw,n,n,nw,nw,s,nw,sw,nw,nw,s,nw,nw,nw,n"
",n,nw,nw,ne,nw,nw,nw,nw,nw,s,nw,nw,sw,nw,se,nw,s,nw,nw,nw,n,nw,nw,nw,se,nw,nw,nw,nw,sw,s,sw,nw,nw,nw,nw,ne,nw,nw,nw,nw,nw,nw,se,nw,ne,nw,se,n"
"w,sw,nw,ne,sw,se,nw,nw,sw,sw,nw,se,nw,se,se,nw,nw,nw,se,nw,nw,nw,nw,s,nw,sw,nw,se,nw,sw,nw,nw,nw,sw,nw,s,nw,se,nw,nw,nw,ne,nw,nw,nw,nw,ne,nw,"
"se,nw,sw,sw,sw,n,ne,nw,nw,se,nw,s,sw,sw,nw,n,sw,s,sw,nw,nw,nw,nw,nw,sw,se,nw,sw,nw,nw,sw,s,nw,se,sw,sw,nw,nw,sw,nw,nw,sw,sw,n,n,ne,sw,sw,sw,n"
"w,sw,sw,sw,sw,sw,sw,nw,nw,nw,sw,nw,n,sw,sw,se,sw,nw,nw,sw,nw,nw,sw,ne,nw,nw,sw,nw,s,ne,sw,ne,sw,sw,nw,sw,sw,sw,nw,nw,nw,sw,sw,sw,s,nw,nw,sw,s"
"e,se,nw,sw,nw,nw,sw,nw,sw,sw,nw,sw,nw,sw,sw,sw,nw,sw,nw,nw,sw,sw,ne,sw,nw,nw,nw,nw,sw,sw,sw,nw,sw,sw,s,sw,nw,nw,sw,sw,sw,sw,sw,sw,sw,sw,nw,nw"
",se,sw,sw,n,sw,sw,sw,sw,sw,n,sw,nw,sw,sw,sw,sw,s,sw,sw,n,sw,sw,sw,se,sw,sw,sw,nw,sw,nw,s,sw,sw,sw,sw,sw,sw,sw,s,sw,sw,nw,ne,ne,sw,sw,sw,se,sw"
",sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,n,n,sw,sw,sw,se,sw,sw,n,sw,sw,sw,sw,sw,s,sw,sw,sw,sw,sw,sw,sw,n,sw,s,s,se,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,"
"s,sw,se,sw,sw,se,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,sw,n,sw,se,sw,sw,s,n,sw,nw,sw,sw,sw,sw,s,sw,s,sw,sw,sw,s,sw,sw,sw,sw,sw,sw,s,s,sw,sw,sw,"
"s,n,s,ne,sw,s,s,sw,s,sw,s,sw,sw,sw,s,sw,sw,se,nw,sw,sw,sw,s,sw,sw,sw,s,sw,sw,s,sw,s,s,nw,s,s,sw,s,s,sw,sw,sw,sw,s,nw,s,sw,sw,s,sw,s,sw,n,nw,n"
"w,s,s,ne,sw,se,s,sw,s,sw,sw,n,sw,nw,sw,sw,sw,sw,sw,n,sw,se,sw,sw,se,sw,se,sw,sw,se,sw,sw,n,sw,s,sw,sw,nw,s,se,n,ne,sw,sw,sw,s,se,nw,sw,sw,sw,"
"n,se,sw,s,s,sw,s,s,sw,sw,s,s,ne,sw,nw,s,sw,se,nw,s,n,sw,sw,sw,sw,s,s,s,s,s,s,s,s,s,sw,sw,se,nw,s,sw,sw,ne,se,s,n,sw,sw,nw,s,s,sw,nw,s,s,s,sw,"
"sw,s,sw,sw,s,s,sw,sw,s,s,s,sw,n,nw,s,sw,s,sw,nw,sw,s,se,s,s,s,s,sw,s,s,sw,sw,s,s,s,sw,se,s,nw,s,ne,s,s,s,sw,s,s,nw,sw,s,s,s,n,s,sw,s,s,s,sw,s"
",s,n,s,s,s,s,s,s,se,sw,s,s,s,s,se,s,s,nw,s,s,s,n,s,s,s,sw,sw,n,s,s,s,s,se,s,se,s,s,s,s,s,s,s,se,se,sw,se,ne,s,s,nw,s,s,s,sw,se,s,s,sw,s,s,s,n"
"e,s,n,sw,s,s,s,n,s,ne,s,se,ne,ne,s,s,s,s,s,sw,s,s,s,s,nw,sw,s,s,s,s,s,s,s,n,s,s,se,s,s,s,s,s,s,s,s,s,nw,se,s,s,se,ne,s,s,s,s,se,s,s,s,s,nw,ne"
",s,se,s,s,s,s,s,s,s,s,s,se,s,s,s,s,s,se,s,sw,s,s,s,se,s,s,s,sw,se,se,s,sw,s,s,ne,s,s,s,s,s,nw,s,nw,s,nw,n,s,s,s,ne,ne,s,s,ne,nw,s,s,s,nw,se,s"
"e,s,s,s,s,s,se,s,s,s,s,s,s,nw,s,se,nw,s,ne,s,s,s,s,s,s,s,s,ne,s,ne,s,s,s,s,se,se,se,se,s,s,ne,s,s,s,se,s,s,s,s,ne,se,se,se,ne,ne,se,se,s,se,s"
",nw,se,s,se,nw,n,ne,s,se,se,se,se,s,se,s,s,s,s,nw,se,s,s,nw,s,s,s,s,s,s,s,s,ne,s,s,se,nw,se,s,s,s,se,sw,n,s,se,se,se,se,s,s,n,s,s,se,s,s,ne,s"
"e,se,se,s,se,s,se,s,se,n,s,sw,se,s,se,s,s,s,se,s,nw,ne,s,s,se,s,s,s,se,se,s,sw,s,s,s,s,s,se,ne,se,nw,se,se,se,se,nw,se,se,se,s,sw,ne,s,se,s,s"
",s,s,s,se,s,n,s,s,n,se,sw,se,se,n,se,se,s,se,se,ne,se,s,s,s,s,se,n,se,s,s,s,n,s,se,s,s,se,se,s,s,s,s,s,se,se,n,s,s,s,s,s,se,se,se,s,se,ne,s,s"
"e,se,s,se,se,n,se,s,se,s,se,se,se,se,s,s,ne,s,se,se,s,s,s,se,se,s,ne,sw,n,s,s,sw,se,s,sw,s,se,se,n,n,s,s,s,s,s,se,n,s,se,se,se,s,s,s,se,s,sw,"
"s,se,se,s,nw,sw,se,se,se,se,ne,sw,n,se,se,se,nw,s,se,se,se,nw,se,se,se,se,ne,sw,nw,ne,se,s,s,se,sw,ne,se,sw,se,n,se,ne,s,se,se,ne,s,s,se,se,s"
"e,se,se,s,se,se,se,se,se,se,se,s,sw,se,nw,se,s,s,ne,se,se,se,se,sw,se,se,n,se,sw,se,s,se,se,se,n,se,se,se,se,se,se,sw,n,s,se,se,se,se,se,se,n"
",se,se,se,s,se,s,se,se,se,s,se,s,nw,sw,s,s,se,se,se,se,se,s,se,s,se,se,se,se,se,se,se,se,se,s,se,se,se,se,se,se,se,se,se,nw,se,se,se,se,se,n,"
"se,n,se,s,se,se,ne,s,se,s,s,s,se,se,se,se,ne,se,se,ne,se,se,se,sw,s,se,se,se,se,se,se,n,se,se,se,se,se,se,nw,se,se,se,se,n,se,se,s,se,ne,se,s"
"e,se,se,se,n,se,se,sw,ne,se,se,n,se,se,nw,se,se,s,se,ne,n,se,se,s,se,se,sw,s,sw,se,se,ne,se,se,se,se,nw,se,ne,se,se,se,s,se,nw,se,se,se,se,se"
",se,ne,se,se,se,se,se,se,s,se,ne,se,se,s,se,se,se,se,se,se,se,se,se,se,nw,se,se,se,se,ne,n,ne,se,sw,se,ne,se,se,se,se,sw,se,se,se,se,se,sw,se"
",sw,nw,se,se,se,se,ne,ne,se,ne,s,se,se,ne,se,se,se,se,n,ne,se,se,se,s,se,nw,se,se,se,n,se,se,ne,se,s,se,n,se,se,ne,se,se,se,se,se,se,ne,s,se,"
"ne,ne,se,se,nw,ne,se,se,se,s,se,ne,se,ne,se,se,nw,se,ne,se,se,se,se,se,ne,se,se,se,se,se,se,ne,se,nw,se,nw,ne,sw,se,se,se,se,se,se,se,ne,se,s"
"e,n,se,se,se,se,se,ne,se,se,nw,se,ne,se,n,ne,se,se,s,se,se,sw,ne,se,se,se,se,se,nw,se,s,se,se,se,se,se,se,n,ne,sw,ne,ne,n,se,se,se,nw,ne,ne,n"
"e,se,ne,n,se,se,se,se,se,n,se,ne,se,s,se,se,ne,se,se,se,ne,ne,se,se,ne,se,se,ne,nw,nw,se,ne,se,se,se,ne,se,ne,se,se,sw,ne,ne,nw,se,se,ne,se,s"
"w,ne,se,ne,ne,n,se,ne,nw,ne,s,ne,se,ne,se,se,se,ne,ne,se,se,ne,ne,se,ne,se,s,sw,nw,n,ne,se,n,ne,se,se,se,nw,se,se,se,n,se,se,se,ne,ne,se,ne,s"
"e,ne,ne,ne,se,se,ne,se,ne,se,se,se,ne,s,se,ne,ne,se,se,ne,ne,ne,ne,se,ne,se,sw,se,ne,ne,nw,se,ne,ne,ne,ne,se,sw,se,s,se,nw,se,ne,se,ne,se,ne,"
"ne,se,ne,se,se,se,ne,ne,se,ne,se,se,se,se,ne,se,sw,se,se,se,ne,se,nw,se,se,se,n,ne,ne,ne,s,sw,ne,nw,ne,s,ne,ne,se,se,sw,se,se,se,se,se,nw,se,"
"ne,ne,nw,ne,se,ne,n,nw,ne,ne,se,se,ne,ne,sw,se,se,ne,sw,se,s,ne,se,sw,se,ne,se,ne,ne,ne,sw,s,ne,se,ne,n,sw,ne,se,se,se,ne,ne,nw,sw,se,ne,ne,n"
"e,ne,ne,se,ne,se,ne,se,se,ne,sw,ne,ne,ne,ne,se,ne,se,ne,ne,ne,ne,ne,s,ne,ne,se,se,ne,se,ne,ne,n,s,se,ne,ne,se,ne,sw,nw,ne,n,se,nw,se,ne,ne,sw"
",se,sw,ne,ne,ne,ne,ne,se,se,ne,ne,ne,n,ne,se,se,ne,se,n,ne,ne,se,se,ne,n,se,ne,se,se,se,nw,ne,se,ne,ne,nw,nw,ne,ne,ne,ne,ne,se,n,ne,ne,s,se,s"
",ne,sw,ne,ne,ne,se,se,nw,n,ne,se,sw,ne,ne,ne,sw,ne,nw,s,s,ne,s,ne,ne,ne,ne,nw,ne,ne,ne,ne,ne,ne,n,ne,ne,ne,ne,sw,ne,nw,ne,ne,se,ne,ne,ne,ne,n"
"e,sw,ne,ne,ne,ne,ne,ne,s,se,ne,se,ne,ne,ne,nw,sw,ne,n,se,se,ne,se,ne,se,n,ne,se,ne,se,s,ne,ne,ne,nw,ne,ne,ne,se,se,se,ne,ne,nw,ne,ne,se,sw,se"
",ne,ne,se,ne,se,se,ne,se,ne,sw,ne,ne,se,se,ne,se,s,nw,ne,ne,nw,ne,ne,ne,se,ne,se,ne,se,ne,ne,ne,ne,n,ne,ne,s,ne,ne,ne,sw,nw,s,ne,ne,ne,ne,n,n"
"e,nw,ne,se,ne,se,ne,ne,n,se,ne,ne,se,ne,ne,ne,ne,ne,ne,se,ne,ne,ne,ne,ne,ne,ne,ne,sw,ne,nw,ne,ne,ne,ne,ne,ne,ne,ne,ne,ne,se,ne,ne,sw,ne,nw,ne"
",ne,ne,ne,ne,ne,ne,ne,ne,ne,ne,s,ne,nw,ne,ne,ne,ne,sw,ne,s,s,ne,ne,ne,ne,ne,ne,sw,ne,ne,ne,ne,ne,ne,ne,nw";


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


void run()
{
    assert(final_distance("ne,ne,ne") == 3);
    assert(final_distance("ne,ne,sw,sw") == 0);
    assert(final_distance("ne,ne,s,s") == 2);
    assert(final_distance("se,sw,se,sw,sw") == 3);
    assert(final_distance("n,sw,s,se,ne,n,nw,s") == 0);

    const int part1 = final_distance(input);
    std::cout << "11.1 " << part1 << '\n';
    assert(part1 == 812);

    assert(furthest_distance("ne,ne,ne") == 3);
    assert(furthest_distance("ne,ne,sw,sw") == 2);
    assert(furthest_distance("ne,ne,s,s") == 2);
    assert(furthest_distance("se,sw,se,sw,sw") == 3);
    assert(furthest_distance("n,sw,s,se,ne,n,nw,s") == 1);

    const int part2 = furthest_distance(input);
    std::cout << "11.2 " << part2 << '\n';
    assert(part2 == 1603);
}

}


namespace day12 {


const char * input =
    "0 <-> 795\n"
    "1 <-> 156\n"
    "2 <-> 715\n"
    "3 <-> 1361, 1698\n"
    "4 <-> 551, 672\n"
    "5 <-> 514\n"
    "6 <-> 1806\n"
    "7 <-> 1700\n"
    "8 <-> 599, 1068, 1850\n"
    "9 <-> 580, 1517\n"
    "10 <-> 521\n"
    "11 <-> 461\n"
    "12 <-> 896\n"
    "13 <-> 464\n"
    "14 <-> 526\n"
    "15 <-> 15\n"
    "16 <-> 627, 997\n"
    "17 <-> 725\n"
    "18 <-> 1803\n"
    "19 <-> 129, 1608, 1712\n"
    "20 <-> 1005\n"
    "21 <-> 252, 386, 1818\n"
    "22 <-> 32, 1168, 1266, 1757\n"
    "23 <-> 212, 664\n"
    "24 <-> 983\n"
    "25 <-> 1271, 1356\n"
    "26 <-> 545\n"
    "27 <-> 639\n"
    "28 <-> 509\n"
    "29 <-> 686, 959, 1521\n"
    "30 <-> 172\n"
    "31 <-> 1721\n"
    "32 <-> 22\n"
    "33 <-> 436\n"
    "34 <-> 96, 116, 661, 1102\n"
    "35 <-> 827, 1274, 1533\n"
    "36 <-> 483, 586\n"
    "37 <-> 556\n"
    "38 <-> 709\n"
    "39 <-> 551, 1196\n"
    "40 <-> 42\n"
    "41 <-> 485\n"
    "42 <-> 40, 475, 930\n"
    "43 <-> 121\n"
    "44 <-> 202, 759\n"
    "45 <-> 45, 721, 764\n"
    "46 <-> 903\n"
    "47 <-> 616, 1053\n"
    "48 <-> 1933\n"
    "49 <-> 334, 476, 516, 1212\n"
    "50 <-> 717, 1412\n"
    "51 <-> 331\n"
    "52 <-> 1953\n"
    "53 <-> 53, 853\n"
    "54 <-> 430\n"
    "55 <-> 1635\n"
    "56 <-> 826, 1985\n"
    "57 <-> 1375\n"
    "58 <-> 868, 1887\n"
    "59 <-> 908, 1307\n"
    "60 <-> 582\n"
    "61 <-> 1298\n"
    "62 <-> 1373\n"
    "63 <-> 1200, 1644\n"
    "64 <-> 547, 771, 1443\n"
    "65 <-> 235, 340, 522, 1472, 1597\n"
    "66 <-> 1605\n"
    "67 <-> 75\n"
    "68 <-> 365\n"
    "69 <-> 69\n"
    "70 <-> 1781\n"
    "71 <-> 1519\n"
    "72 <-> 1355\n"
    "73 <-> 73, 176\n"
    "74 <-> 1155\n"
    "75 <-> 67, 769, 1080\n"
    "76 <-> 470, 474, 1115\n"
    "77 <-> 1564\n"
    "78 <-> 78, 1128, 1351\n"
    "79 <-> 784\n"
    "80 <-> 80, 962, 1566\n"
    "81 <-> 1784\n"
    "82 <-> 1977\n"
    "83 <-> 892\n"
    "84 <-> 705, 892, 958, 1717\n"
    "85 <-> 493, 644, 714, 1624\n"
    "86 <-> 1079, 1547\n"
    "87 <-> 1186, 1240\n"
    "88 <-> 215, 250, 1918\n"
    "89 <-> 485\n"
    "90 <-> 595, 786, 1419, 1825, 1870\n"
    "91 <-> 1366, 1874\n"
    "92 <-> 217, 225\n"
    "93 <-> 577, 1734\n"
    "94 <-> 94\n"
    "95 <-> 1476\n"
    "96 <-> 34, 560, 1061\n"
    "97 <-> 199\n"
    "98 <-> 1311\n"
    "99 <-> 1040\n"
    "100 <-> 1397\n"
    "101 <-> 1578\n"
    "102 <-> 1719\n"
    "103 <-> 1268, 1663\n"
    "104 <-> 106, 677, 846\n"
    "105 <-> 650\n"
    "106 <-> 104, 1315\n"
    "107 <-> 1802\n"
    "108 <-> 1723, 1885\n"
    "109 <-> 658\n"
    "110 <-> 646\n"
    "111 <-> 124, 710, 1819\n"
    "112 <-> 841\n"
    "113 <-> 696\n"
    "114 <-> 1685, 1923\n"
    "115 <-> 1565\n"
    "116 <-> 34, 1116\n"
    "117 <-> 1532, 1842\n"
    "118 <-> 1058, 1225, 1495\n"
    "119 <-> 224, 1536\n"
    "120 <-> 542, 1229\n"
    "121 <-> 43, 986\n"
    "122 <-> 921\n"
    "123 <-> 345, 1655, 1848, 1974\n"
    "124 <-> 111, 1259\n"
    "125 <-> 1797\n"
    "126 <-> 126\n"
    "127 <-> 127, 260, 732, 1117, 1251\n"
    "128 <-> 1151\n"
    "129 <-> 19, 782\n"
    "130 <-> 130\n"
    "131 <-> 1582\n"
    "132 <-> 505, 592, 1545\n"
    "133 <-> 953\n"
    "134 <-> 1567\n"
    "135 <-> 559, 591, 1791\n"
    "136 <-> 868, 1449, 1470, 1954\n"
    "137 <-> 374\n"
    "138 <-> 303, 1601, 1710\n"
    "139 <-> 1011\n"
    "140 <-> 140, 1947\n"
    "141 <-> 252\n"
    "142 <-> 803, 1706\n"
    "143 <-> 1622\n"
    "144 <-> 832\n"
    "145 <-> 145\n"
    "146 <-> 904, 921, 1720\n"
    "147 <-> 611, 1788\n"
    "148 <-> 188\n"
    "149 <-> 264\n"
    "150 <-> 746, 1850\n"
    "151 <-> 151, 347\n"
    "152 <-> 393\n"
    "153 <-> 182\n"
    "154 <-> 154, 349, 673, 1039\n"
    "155 <-> 697, 1258\n"
    "156 <-> 1, 384, 453, 1232, 1995\n"
    "157 <-> 1492\n"
    "158 <-> 1245\n"
    "159 <-> 1194\n"
    "160 <-> 222, 1241\n"
    "161 <-> 1377\n"
    "162 <-> 162\n"
    "163 <-> 1825\n"
    "164 <-> 1837\n"
    "165 <-> 955, 1811\n"
    "166 <-> 825, 1817\n"
    "167 <-> 1338\n"
    "168 <-> 1037, 1290\n"
    "169 <-> 169\n"
    "170 <-> 1490\n"
    "171 <-> 553\n"
    "172 <-> 30, 308\n"
    "173 <-> 1573, 1604\n"
    "174 <-> 1297\n"
    "175 <-> 265, 1070, 1960\n"
    "176 <-> 73, 497\n"
    "177 <-> 1639, 1697\n"
    "178 <-> 494, 1490\n"
    "179 <-> 623\n"
    "180 <-> 185, 1056\n"
    "181 <-> 181\n"
    "182 <-> 153, 1678\n"
    "183 <-> 504, 601\n"
    "184 <-> 635, 1246\n"
    "185 <-> 180, 621\n"
    "186 <-> 1798\n"
    "187 <-> 1375\n"
    "188 <-> 148, 405, 950, 1322\n"
    "189 <-> 534, 1908\n"
    "190 <-> 1582\n"
    "191 <-> 361, 1879\n"
    "192 <-> 1814\n"
    "193 <-> 533, 1307, 1389\n"
    "194 <-> 1262\n"
    "195 <-> 1450\n"
    "196 <-> 335\n"
    "197 <-> 750\n"
    "198 <-> 285, 297, 671\n"
    "199 <-> 97, 199, 280, 1292\n"
    "200 <-> 200, 1584\n"
    "201 <-> 1519\n"
    "202 <-> 44, 1492, 1605, 1857, 1888\n"
    "203 <-> 363, 416, 504\n"
    "204 <-> 832\n"
    "205 <-> 350, 1385\n"
    "206 <-> 206\n"
    "207 <-> 584\n"
    "208 <-> 889, 1254, 1596\n"
    "209 <-> 996, 1402\n"
    "210 <-> 691, 977\n"
    "211 <-> 463\n"
    "212 <-> 23, 1318\n"
    "213 <-> 600, 933\n"
    "214 <-> 1657\n"
    "215 <-> 88, 274, 1264\n"
    "216 <-> 216, 301\n"
    "217 <-> 92, 217, 766\n"
    "218 <-> 986, 1439\n"
    "219 <-> 1217, 1294\n"
    "220 <-> 368, 736, 1543, 1704\n"
    "221 <-> 367, 806, 1273, 1804\n"
    "222 <-> 160, 682, 1257, 1660\n"
    "223 <-> 223\n"
    "224 <-> 119, 259\n"
    "225 <-> 92\n"
    "226 <-> 482, 1472\n"
    "227 <-> 1325\n"
    "228 <-> 379, 1914\n"
    "229 <-> 529, 765\n"
    "230 <-> 534\n"
    "231 <-> 1456\n"
    "232 <-> 924, 952\n"
    "233 <-> 1423, 1661, 1715\n"
    "234 <-> 429\n"
    "235 <-> 65\n"
    "236 <-> 1134, 1613\n"
    "237 <-> 237\n"
    "238 <-> 1728\n"
    "239 <-> 1543\n"
    "240 <-> 698, 832, 1022\n"
    "241 <-> 948, 1066, 1172, 1552\n"
    "242 <-> 594, 888\n"
    "243 <-> 965\n"
    "244 <-> 739, 1428\n"
    "245 <-> 1039\n"
    "246 <-> 471\n"
    "247 <-> 1414, 1650\n"
    "248 <-> 254, 1152\n"
    "249 <-> 383, 976\n"
    "250 <-> 88\n"
    "251 <-> 941, 1484\n"
    "252 <-> 21, 141, 803\n"
    "253 <-> 253\n"
    "254 <-> 248, 395\n"
    "255 <-> 909, 1334\n"
    "256 <-> 1001\n"
    "257 <-> 558, 1050, 1946\n"
    "258 <-> 516, 961\n"
    "259 <-> 224, 564, 630\n"
    "260 <-> 127, 1041, 1938\n"
    "261 <-> 697, 761\n"
    "262 <-> 262, 1928\n"
    "263 <-> 1068\n"
    "264 <-> 149, 818\n"
    "265 <-> 175\n"
    "266 <-> 1767, 1955\n"
    "267 <-> 326\n"
    "268 <-> 553\n"
    "269 <-> 1557, 1907\n"
    "270 <-> 971\n"
    "271 <-> 1039\n"
    "272 <-> 1053, 1176\n"
    "273 <-> 1248\n"
    "274 <-> 215\n"
    "275 <-> 590, 1539\n"
    "276 <-> 479, 749\n"
    "277 <-> 434, 827, 1014\n"
    "278 <-> 1219\n"
    "279 <-> 931, 1971\n"
    "280 <-> 199, 559\n"
    "281 <-> 1079\n"
    "282 <-> 996, 1746\n"
    "283 <-> 1970\n"
    "284 <-> 1376, 1692\n"
    "285 <-> 198, 1521, 1977\n"
    "286 <-> 623, 857, 1446\n"
    "287 <-> 1781, 1920\n"
    "288 <-> 417\n"
    "289 <-> 1073\n"
    "290 <-> 1411\n"
    "291 <-> 759, 1267, 1931\n"
    "292 <-> 448\n"
    "293 <-> 1426, 1675\n"
    "294 <-> 947, 1749\n"
    "295 <-> 1489, 1702\n"
    "296 <-> 791\n"
    "297 <-> 198\n"
    "298 <-> 372, 539, 566, 1183\n"
    "299 <-> 306, 1799\n"
    "300 <-> 300, 1762\n"
    "301 <-> 216\n"
    "302 <-> 1671\n"
    "303 <-> 138, 867\n"
    "304 <-> 671, 1553\n"
    "305 <-> 1018, 1186\n"
    "306 <-> 299, 321\n"
    "307 <-> 1125, 1976\n"
    "308 <-> 172, 383\n"
    "309 <-> 1037, 1766\n"
    "310 <-> 1345\n"
    "311 <-> 849, 1989\n"
    "312 <-> 312\n"
    "313 <-> 1052, 1595\n"
    "314 <-> 1405, 1923\n"
    "315 <-> 426, 543\n"
    "316 <-> 536, 968, 1363, 1529, 1572, 1906\n"
    "317 <-> 317, 747\n"
    "318 <-> 495, 1658\n"
    "319 <-> 556, 910\n"
    "320 <-> 845, 1225\n"
    "321 <-> 306, 321, 399, 1248, 1951\n"
    "322 <-> 1409\n"
    "323 <-> 323, 1046, 1287\n"
    "324 <-> 1103\n"
    "325 <-> 1681\n"
    "326 <-> 267, 758, 901\n"
    "327 <-> 411, 1475\n"
    "328 <-> 1789\n"
    "329 <-> 473, 1361\n"
    "330 <-> 639, 1763\n"
    "331 <-> 51, 331\n"
    "332 <-> 492, 1526, 1552\n"
    "333 <-> 888, 1362\n"
    "334 <-> 49\n"
    "335 <-> 196, 335, 1914\n"
    "336 <-> 457\n"
    "337 <-> 1452\n"
    "338 <-> 426\n"
    "339 <-> 339, 689, 928, 1037\n"
    "340 <-> 65, 1403, 1516, 1559\n"
    "341 <-> 1393\n"
    "342 <-> 380, 452\n"
    "343 <-> 1126, 1267, 1823\n"
    "344 <-> 1429\n"
    "345 <-> 123\n"
    "346 <-> 364, 1898\n"
    "347 <-> 151, 515, 1114\n"
    "348 <-> 621, 1263, 1501, 1907\n"
    "349 <-> 154\n"
    "350 <-> 205, 596, 775, 1627\n"
    "351 <-> 755, 1186\n"
    "352 <-> 644\n"
    "353 <-> 943, 1117\n"
    "354 <-> 917, 1980\n"
    "355 <-> 1036, 1858\n"
    "356 <-> 900, 1210, 1940\n"
    "357 <-> 489\n"
    "358 <-> 1611\n"
    "359 <-> 359\n"
    "360 <-> 360, 1838\n"
    "361 <-> 191, 1729\n"
    "362 <-> 1090, 1692\n"
    "363 <-> 203, 363\n"
    "364 <-> 346, 1373\n"
    "365 <-> 68, 365\n"
    "366 <-> 469, 873\n"
    "367 <-> 221\n"
    "368 <-> 220\n"
    "369 <-> 1594, 1712\n"
    "370 <-> 1150\n"
    "371 <-> 1705\n"
    "372 <-> 298, 974, 1206, 1882\n"
    "373 <-> 1044, 1753\n"
    "374 <-> 137, 697, 1902\n"
    "375 <-> 510, 722\n"
    "376 <-> 1431, 1502\n"
    "377 <-> 377, 1098\n"
    "378 <-> 552, 971, 1054\n"
    "379 <-> 228, 684, 1256\n"
    "380 <-> 342\n"
    "381 <-> 1896\n"
    "382 <-> 967, 1146, 1224, 1816\n"
    "383 <-> 249, 308\n"
    "384 <-> 156, 807\n"
    "385 <-> 510\n"
    "386 <-> 21, 1184, 1756\n"
    "387 <-> 440, 1016, 1505\n"
    "388 <-> 938, 1418, 1810\n"
    "389 <-> 1300\n"
    "390 <-> 1305, 1863\n"
    "391 <-> 458, 1911\n"
    "392 <-> 506, 808, 924\n"
    "393 <-> 152, 1258\n"
    "394 <-> 394\n"
    "395 <-> 254\n"
    "396 <-> 656\n"
    "397 <-> 1872\n"
    "398 <-> 1679\n"
    "399 <-> 321\n"
    "400 <-> 528, 1560\n"
    "401 <-> 1527\n"
    "402 <-> 464, 1145, 1496\n"
    "403 <-> 477\n"
    "404 <-> 627\n"
    "405 <-> 188, 1866\n"
    "406 <-> 720, 1174, 1272\n"
    "407 <-> 1048\n"
    "408 <-> 674\n"
    "409 <-> 1869\n"
    "410 <-> 1548\n"
    "411 <-> 327, 836, 1622, 1967\n"
    "412 <-> 1803, 1978\n"
    "413 <-> 523, 1511\n"
    "414 <-> 414, 694\n"
    "415 <-> 1022, 1988\n"
    "416 <-> 203\n"
    "417 <-> 288, 449, 1758\n"
    "418 <-> 418, 778, 900, 1062, 1639, 1789\n"
    "419 <-> 419, 1764\n"
    "420 <-> 991\n"
    "421 <-> 690\n"
    "422 <-> 567, 883, 1182, 1921\n"
    "423 <-> 870\n"
    "424 <-> 503\n"
    "425 <-> 1014\n"
    "426 <-> 315, 338, 901, 1336\n"
    "427 <-> 1966\n"
    "428 <-> 1606\n"
    "429 <-> 234, 1567, 1682\n"
    "430 <-> 54, 1157, 1177, 1894\n"
    "431 <-> 798, 926\n"
    "432 <-> 1683\n"
    "433 <-> 523, 854\n"
    "434 <-> 277\n"
    "435 <-> 471, 1002\n"
    "436 <-> 33, 810, 873, 1011\n"
    "437 <-> 1327, 1534\n"
    "438 <-> 1470, 1825\n"
    "439 <-> 1293, 1566\n"
    "440 <-> 387, 1006\n"
    "441 <-> 560, 1690\n"
    "442 <-> 442, 587\n"
    "443 <-> 1324, 1450\n"
    "444 <-> 1655\n"
    "445 <-> 1387, 1499\n"
    "446 <-> 1637, 1663\n"
    "447 <-> 447\n"
    "448 <-> 292, 1407, 1533, 1874\n"
    "449 <-> 417\n"
    "450 <-> 878, 1780\n"
    "451 <-> 451\n"
    "452 <-> 342, 960, 1981\n"
    "453 <-> 156\n"
    "454 <-> 1215\n"
    "455 <-> 647, 1336\n"
    "456 <-> 675, 1080, 1792\n"
    "457 <-> 336, 626, 1002\n"
    "458 <-> 391\n"
    "459 <-> 619\n"
    "460 <-> 695, 997, 1181\n"
    "461 <-> 11, 795, 1020\n"
    "462 <-> 1433\n"
    "463 <-> 211, 1038, 1361\n"
    "464 <-> 13, 402\n"
    "465 <-> 1159, 1674\n"
    "466 <-> 1386, 1405, 1493\n"
    "467 <-> 581, 1677\n"
    "468 <-> 911\n"
    "469 <-> 366\n"
    "470 <-> 76, 676\n"
    "471 <-> 246, 435, 1331, 1685\n"
    "472 <-> 938, 1136, 1755\n"
    "473 <-> 329\n"
    "474 <-> 76, 856, 1645\n"
    "475 <-> 42, 804, 1546\n"
    "476 <-> 49\n"
    "477 <-> 403, 854, 1165, 1962\n"
    "478 <-> 1254\n"
    "479 <-> 276\n"
    "480 <-> 1364\n"
    "481 <-> 623\n"
    "482 <-> 226, 949\n"
    "483 <-> 36, 993\n"
    "484 <-> 484\n"
    "485 <-> 41, 89, 880, 1008, 1994\n"
    "486 <-> 1523, 1588\n"
    "487 <-> 1122\n"
    "488 <-> 728\n"
    "489 <-> 357, 573\n"
    "490 <-> 717, 841, 1020, 1280\n"
    "491 <-> 1920\n"
    "492 <-> 332\n"
    "493 <-> 85, 1585\n"
    "494 <-> 178, 1800\n"
    "495 <-> 318, 631, 897, 1482\n"
    "496 <-> 1649\n"
    "497 <-> 176\n"
    "498 <-> 1828\n"
    "499 <-> 499, 1134\n"
    "500 <-> 657, 1331\n"
    "501 <-> 809\n"
    "502 <-> 628, 787, 1358\n"
    "503 <-> 424, 503\n"
    "504 <-> 183, 203\n"
    "505 <-> 132, 1402\n"
    "506 <-> 392, 990\n"
    "507 <-> 1027, 1638, 1684\n"
    "508 <-> 710, 716\n"
    "509 <-> 28, 509\n"
    "510 <-> 375, 385, 629, 1814\n"
    "511 <-> 892\n"
    "512 <-> 1175\n"
    "513 <-> 513, 1737\n"
    "514 <-> 5, 699, 1610, 1935\n"
    "515 <-> 347, 1471\n"
    "516 <-> 49, 258, 1514\n"
    "517 <-> 1361\n"
    "518 <-> 1174\n"
    "519 <-> 927\n"
    "520 <-> 520, 1456\n"
    "521 <-> 10, 1581\n"
    "522 <-> 65, 1448\n"
    "523 <-> 413, 433, 1215\n"
    "524 <-> 524\n"
    "525 <-> 1540\n"
    "526 <-> 14, 798\n"
    "527 <-> 527, 753\n"
    "528 <-> 400\n"
    "529 <-> 229\n"
    "530 <-> 1475, 1620\n"
    "531 <-> 531\n"
    "532 <-> 1286\n"
    "533 <-> 193, 1727\n"
    "534 <-> 189, 230\n"
    "535 <-> 991, 1366\n"
    "536 <-> 316\n"
    "537 <-> 1833\n"
    "538 <-> 970, 1270\n"
    "539 <-> 298, 704, 723\n"
    "540 <-> 623\n"
    "541 <-> 1160, 1498, 1909\n"
    "542 <-> 120\n"
    "543 <-> 315\n"
    "544 <-> 842, 1289, 1365\n"
    "545 <-> 26, 1550\n"
    "546 <-> 1722, 1886\n"
    "547 <-> 64, 796, 1612\n"
    "548 <-> 1582, 1945\n"
    "549 <-> 549, 1084\n"
    "550 <-> 1041\n"
    "551 <-> 4, 39\n"
    "552 <-> 378, 1257\n"
    "553 <-> 171, 268, 1160, 1493\n"
    "554 <-> 1190\n"
    "555 <-> 1050\n"
    "556 <-> 37, 319, 1551\n"
    "557 <-> 557\n"
    "558 <-> 257, 1779\n"
    "559 <-> 135, 280\n"
    "560 <-> 96, 441\n"
    "561 <-> 1244, 1986\n"
    "562 <-> 1209, 1820\n"
    "563 <-> 1215\n"
    "564 <-> 259, 1817\n"
    "565 <-> 565\n"
    "566 <-> 298, 1203\n"
    "567 <-> 422, 884, 1113\n"
    "568 <-> 760, 1768\n"
    "569 <-> 1449\n"
    "570 <-> 598, 759, 1728\n"
    "571 <-> 571\n"
    "572 <-> 1821\n"
    "573 <-> 489, 930, 942, 1459\n"
    "574 <-> 1872\n"
    "575 <-> 813, 1073, 1335\n"
    "576 <-> 653, 1111, 1616\n"
    "577 <-> 93, 1316\n"
    "578 <-> 837, 1645, 1683\n"
    "579 <-> 906, 1113\n"
    "580 <-> 9, 1318, 1657\n"
    "581 <-> 467, 1286, 1720\n"
    "582 <-> 60, 582\n"
    "583 <-> 1678\n"
    "584 <-> 207, 891, 1115\n"
    "585 <-> 624\n"
    "586 <-> 36, 586, 1501, 1512\n"
    "587 <-> 442, 823, 1620, 1853\n"
    "588 <-> 1147\n"
    "589 <-> 1096, 1641, 1730\n"
    "590 <-> 275, 654, 726, 1981\n"
    "591 <-> 135\n"
    "592 <-> 132\n"
    "593 <-> 820\n"
    "594 <-> 242, 611, 1743\n"
    "595 <-> 90, 630, 719, 1977\n"
    "596 <-> 350, 878, 1401\n"
    "597 <-> 781, 848, 1854\n"
    "598 <-> 570\n"
    "599 <-> 8, 1070\n"
    "600 <-> 213, 779, 1118, 1483, 1886, 1957\n"
    "601 <-> 183\n"
    "602 <-> 1265\n"
    "603 <-> 1860\n"
    "604 <-> 641, 1512\n"
    "605 <-> 1001\n"
    "606 <-> 900\n"
    "607 <-> 1302\n"
    "608 <-> 885\n"
    "609 <-> 837\n"
    "610 <-> 610, 1659\n"
    "611 <-> 147, 594\n"
    "612 <-> 922, 1560\n"
    "613 <-> 1381\n"
    "614 <-> 1071, 1893\n"
    "615 <-> 629, 741, 1865\n"
    "616 <-> 47\n"
    "617 <-> 896\n"
    "618 <-> 1721, 1754, 1902\n"
    "619 <-> 459, 619, 1032\n"
    "620 <-> 679, 1449\n"
    "621 <-> 185, 348, 1301\n"
    "622 <-> 1244\n"
    "623 <-> 179, 286, 481, 540\n"
    "624 <-> 585, 1009, 1134\n"
    "625 <-> 1181, 1433\n"
    "626 <-> 457, 626, 1500, 1932\n"
    "627 <-> 16, 404\n"
    "628 <-> 502\n"
    "629 <-> 510, 615, 927\n"
    "630 <-> 259, 595\n"
    "631 <-> 495, 976, 1228\n"
    "632 <-> 1912\n"
    "633 <-> 694, 894\n"
    "634 <-> 1657\n"
    "635 <-> 184\n"
    "636 <-> 911, 1730, 1945\n"
    "637 <-> 981, 1909\n"
    "638 <-> 907\n"
    "639 <-> 27, 330, 639, 1663\n"
    "640 <-> 1229, 1939\n"
    "641 <-> 604\n"
    "642 <-> 896\n"
    "643 <-> 850\n"
    "644 <-> 85, 352, 735, 1025\n"
    "645 <-> 783\n"
    "646 <-> 110, 1825\n"
    "647 <-> 455\n"
    "648 <-> 1043\n"
    "649 <-> 1532\n"
    "650 <-> 105, 833, 1060, 1371\n"
    "651 <-> 1437, 1751\n"
    "652 <-> 1019\n"
    "653 <-> 576, 1314, 1393\n"
    "654 <-> 590\n"
    "655 <-> 716, 779\n"
    "656 <-> 396, 773, 1603\n"
    "657 <-> 500\n"
    "658 <-> 109, 738\n"
    "659 <-> 1527, 1951\n"
    "660 <-> 1685\n"
    "661 <-> 34\n"
    "662 <-> 1196, 1252\n"
    "663 <-> 1729\n"
    "664 <-> 23\n"
    "665 <-> 1224\n"
    "666 <-> 1213\n"
    "667 <-> 1786, 1919\n"
    "668 <-> 1369\n"
    "669 <-> 669, 785\n"
    "670 <-> 926, 1642\n"
    "671 <-> 198, 304\n"
    "672 <-> 4\n"
    "673 <-> 154\n"
    "674 <-> 408, 1062\n"
    "675 <-> 456\n"
    "676 <-> 470, 1194\n"
    "677 <-> 104\n"
    "678 <-> 821\n"
    "679 <-> 620\n"
    "680 <-> 687, 931\n"
    "681 <-> 959, 1711\n"
    "682 <-> 222, 1941\n"
    "683 <-> 1594\n"
    "684 <-> 379\n"
    "685 <-> 1200, 1897\n"
    "686 <-> 29, 1399\n"
    "687 <-> 680\n"
    "688 <-> 722\n"
    "689 <-> 339, 1391\n"
    "690 <-> 421, 1666\n"
    "691 <-> 210\n"
    "692 <-> 1165\n"
    "693 <-> 923, 1761\n"
    "694 <-> 414, 633, 757\n"
    "695 <-> 460, 726, 1880\n"
    "696 <-> 113, 1228, 1240\n"
    "697 <-> 155, 261, 374, 1477\n"
    "698 <-> 240\n"
    "699 <-> 514, 706\n"
    "700 <-> 746\n"
    "701 <-> 905, 1064\n"
    "702 <-> 952, 1097\n"
    "703 <-> 703, 1875\n"
    "704 <-> 539, 1328\n"
    "705 <-> 84, 1621\n"
    "706 <-> 699, 1604\n"
    "707 <-> 707\n"
    "708 <-> 708\n"
    "709 <-> 38, 1064\n"
    "710 <-> 111, 508, 1362\n"
    "711 <-> 1545\n"
    "712 <-> 899, 1139\n"
    "713 <-> 1228\n"
    "714 <-> 85, 1297\n"
    "715 <-> 2, 754, 1808\n"
    "716 <-> 508, 655\n"
    "717 <-> 50, 490\n"
    "718 <-> 1382, 1648\n"
    "719 <-> 595, 1024\n"
    "720 <-> 406, 1096, 1261\n"
    "721 <-> 45, 1213\n"
    "722 <-> 375, 688, 1632\n"
    "723 <-> 539\n"
    "724 <-> 891\n"
    "725 <-> 17, 1045\n"
    "726 <-> 590, 695, 1958\n"
    "727 <-> 747\n"
    "728 <-> 488, 728\n"
    "729 <-> 729, 1150\n"
    "730 <-> 730\n"
    "731 <-> 1181, 1273\n"
    "732 <-> 127, 1269\n"
    "733 <-> 1803\n"
    "734 <-> 1005, 1496\n"
    "735 <-> 644\n"
    "736 <-> 220\n"
    "737 <-> 1383\n"
    "738 <-> 658, 1259, 1687\n"
    "739 <-> 244\n"
    "740 <-> 946, 1163, 1279\n"
    "741 <-> 615, 1690\n"
    "742 <-> 800, 878, 1609\n"
    "743 <-> 1647\n"
    "744 <-> 744, 1778\n"
    "745 <-> 1181\n"
    "746 <-> 150, 700, 1082, 1727\n"
    "747 <-> 317, 727\n"
    "748 <-> 877\n"
    "749 <-> 276, 1040\n"
    "750 <-> 197, 750, 1201\n"
    "751 <-> 1159, 1479\n"
    "752 <-> 1642\n"
    "753 <-> 527\n"
    "754 <-> 715, 1809\n"
    "755 <-> 351, 1088, 1560\n"
    "756 <-> 756\n"
    "757 <-> 694\n"
    "758 <-> 326, 954, 1988\n"
    "759 <-> 44, 291, 570, 1038\n"
    "760 <-> 568, 1304, 1620\n"
    "761 <-> 261, 1537\n"
    "762 <-> 1943\n"
    "763 <-> 948, 1232, 1375\n"
    "764 <-> 45, 1839\n"
    "765 <-> 229, 1066\n"
    "766 <-> 217\n"
    "767 <-> 1501, 1587, 1640\n"
    "768 <-> 868, 1911\n"
    "769 <-> 75\n"
    "770 <-> 1724\n"
    "771 <-> 64, 1124, 1606\n"
    "772 <-> 1721\n"
    "773 <-> 656, 1197, 1756\n"
    "774 <-> 1422, 1835\n"
    "775 <-> 350, 844\n"
    "776 <-> 1204\n"
    "777 <-> 1073, 1448\n"
    "778 <-> 418\n"
    "779 <-> 600, 655\n"
    "780 <-> 1111, 1274\n"
    "781 <-> 597\n"
    "782 <-> 129, 1600\n"
    "783 <-> 645, 1627\n"
    "784 <-> 79, 947\n"
    "785 <-> 669\n"
    "786 <-> 90\n"
    "787 <-> 502, 816, 1625, 1821\n"
    "788 <-> 943\n"
    "789 <-> 1835\n"
    "790 <-> 1625\n"
    "791 <-> 296, 1092, 1930\n"
    "792 <-> 830\n"
    "793 <-> 1876\n"
    "794 <-> 1156, 1626, 1813\n"
    "795 <-> 0, 461\n"
    "796 <-> 547\n"
    "797 <-> 1565, 1589, 1669\n"
    "798 <-> 431, 526, 1278\n"
    "799 <-> 1643\n"
    "800 <-> 742, 1761\n"
    "801 <-> 858\n"
    "802 <-> 1367\n"
    "803 <-> 142, 252\n"
    "804 <-> 475, 1268, 1758, 1991\n"
    "805 <-> 1218, 1832\n"
    "806 <-> 221\n"
    "807 <-> 384, 1140, 1460, 1872, 1999\n"
    "808 <-> 392, 1417\n"
    "809 <-> 501, 884\n"
    "810 <-> 436\n"
    "811 <-> 1813\n"
    "812 <-> 819\n"
    "813 <-> 575\n"
    "814 <-> 1282, 1966\n"
    "815 <-> 815, 1579\n"
    "816 <-> 787, 1676\n"
    "817 <-> 1051, 1671\n"
    "818 <-> 264, 928, 1065\n"
    "819 <-> 812, 819\n"
    "820 <-> 593, 868, 1107, 1919\n"
    "821 <-> 678, 879, 1551, 1681, 1774\n"
    "822 <-> 822\n"
    "823 <-> 587\n"
    "824 <-> 1092, 1412, 1992\n"
    "825 <-> 166\n"
    "826 <-> 56, 1073\n"
    "827 <-> 35, 277\n"
    "828 <-> 1847\n"
    "829 <-> 1028\n"
    "830 <-> 792, 1007\n"
    "831 <-> 1799\n"
    "832 <-> 144, 204, 240, 1329\n"
    "833 <-> 650, 1685\n"
    "834 <-> 1379\n"
    "835 <-> 1355, 1844\n"
    "836 <-> 411\n"
    "837 <-> 578, 609, 1489\n"
    "838 <-> 1144, 1441\n"
    "839 <-> 1593\n"
    "840 <-> 1045\n"
    "841 <-> 112, 490, 1436\n"
    "842 <-> 544\n"
    "843 <-> 1371\n"
    "844 <-> 775\n"
    "845 <-> 320, 1556, 1591\n"
    "846 <-> 104, 1094\n"
    "847 <-> 847, 1654\n"
    "848 <-> 597, 1090\n"
    "849 <-> 311, 1773\n"
    "850 <-> 643, 1875\n"
    "851 <-> 858, 1524\n"
    "852 <-> 1504, 1541, 1990\n"
    "853 <-> 53\n"
    "854 <-> 433, 477\n"
    "855 <-> 1502, 1860\n"
    "856 <-> 474\n"
    "857 <-> 286, 857\n"
    "858 <-> 801, 851, 858, 1547, 1652\n"
    "859 <-> 1969\n"
    "860 <-> 1181\n"
    "861 <-> 955\n"
    "862 <-> 1350, 1624\n"
    "863 <-> 863\n"
    "864 <-> 1457\n"
    "865 <-> 1355, 1491\n"
    "866 <-> 1373\n"
    "867 <-> 303, 987\n"
    "868 <-> 58, 136, 768, 820\n"
    "869 <-> 1426, 1744\n"
    "870 <-> 423, 1608\n"
    "871 <-> 1312\n"
    "872 <-> 872, 1226\n"
    "873 <-> 366, 436\n"
    "874 <-> 1983\n"
    "875 <-> 1138, 1232\n"
    "876 <-> 1324\n"
    "877 <-> 748, 1464, 1846\n"
    "878 <-> 450, 596, 742\n"
    "879 <-> 821\n"
    "880 <-> 485\n"
    "881 <-> 1246, 1286\n"
    "882 <-> 946, 1221\n"
    "883 <-> 422, 886, 1830\n"
    "884 <-> 567, 809\n"
    "885 <-> 608, 1856\n"
    "886 <-> 883, 1787\n"
    "887 <-> 1035, 1331, 1438, 1604\n"
    "888 <-> 242, 333\n"
    "889 <-> 208, 935\n"
    "890 <-> 1211, 1847\n"
    "891 <-> 584, 724\n"
    "892 <-> 83, 84, 511, 1478, 1530, 1983\n"
    "893 <-> 1494\n"
    "894 <-> 633\n"
    "895 <-> 1045, 1124, 1745\n"
    "896 <-> 12, 617, 642, 896\n"
    "897 <-> 495\n"
    "898 <-> 898, 1586\n"
    "899 <-> 712\n"
    "900 <-> 356, 418, 606, 1026, 1074\n"
    "901 <-> 326, 426\n"
    "902 <-> 1790\n"
    "903 <-> 46, 969, 1715\n"
    "904 <-> 146, 1964\n"
    "905 <-> 701, 1273, 1410\n"
    "906 <-> 579, 1713, 1878\n"
    "907 <-> 638, 907\n"
    "908 <-> 59, 1195\n"
    "909 <-> 255, 1669\n"
    "910 <-> 319\n"
    "911 <-> 468, 636\n"
    "912 <-> 1076\n"
    "913 <-> 1067, 1101, 1397, 1790\n"
    "914 <-> 1383, 1825\n"
    "915 <-> 1827\n"
    "916 <-> 1938\n"
    "917 <-> 354, 991\n"
    "918 <-> 1013\n"
    "919 <-> 1086\n"
    "920 <-> 995\n"
    "921 <-> 122, 146\n"
    "922 <-> 612\n"
    "923 <-> 693, 1916\n"
    "924 <-> 232, 392, 1782\n"
    "925 <-> 1553\n"
    "926 <-> 431, 670\n"
    "927 <-> 519, 629\n"
    "928 <-> 339, 818\n"
    "929 <-> 1220\n"
    "930 <-> 42, 573\n"
    "931 <-> 279, 680, 1593\n"
    "932 <-> 1470, 1534\n"
    "933 <-> 213\n"
    "934 <-> 1205, 1387\n"
    "935 <-> 889\n"
    "936 <-> 1984\n"
    "937 <-> 937, 1817\n"
    "938 <-> 388, 472, 1133, 1808\n"
    "939 <-> 1147, 1750, 1884\n"
    "940 <-> 1097\n"
    "941 <-> 251\n"
    "942 <-> 573, 1994\n"
    "943 <-> 353, 788\n"
    "944 <-> 1103, 1979\n"
    "945 <-> 1824\n"
    "946 <-> 740, 882, 1716\n"
    "947 <-> 294, 784, 1381, 1960\n"
    "948 <-> 241, 763, 1368\n"
    "949 <-> 482\n"
    "950 <-> 188\n"
    "951 <-> 1711\n"
    "952 <-> 232, 702\n"
    "953 <-> 133, 1028, 1375, 1519\n"
    "954 <-> 758, 1733\n"
    "955 <-> 165, 861, 1442, 1664\n"
    "956 <-> 956, 1590\n"
    "957 <-> 957\n"
    "958 <-> 84\n"
    "959 <-> 29, 681\n"
    "960 <-> 452\n"
    "961 <-> 258\n"
    "962 <-> 80\n"
    "963 <-> 963\n"
    "964 <-> 1742\n"
    "965 <-> 243, 965\n"
    "966 <-> 1515, 1745\n"
    "967 <-> 382, 1712, 1754\n"
    "968 <-> 316\n"
    "969 <-> 903, 1777\n"
    "970 <-> 538, 1278, 1463\n"
    "971 <-> 270, 378\n"
    "972 <-> 1985\n"
    "973 <-> 1565\n"
    "974 <-> 372, 1738\n"
    "975 <-> 1734\n"
    "976 <-> 249, 631\n"
    "977 <-> 210, 1846\n"
    "978 <-> 1171\n"
    "979 <-> 1786\n"
    "980 <-> 1871\n"
    "981 <-> 637\n"
    "982 <-> 1449\n"
    "983 <-> 24, 1567\n"
    "984 <-> 1372\n"
    "985 <-> 985, 1285\n"
    "986 <-> 121, 218, 988, 1836\n"
    "987 <-> 867\n"
    "988 <-> 986, 1276, 1526\n"
    "989 <-> 1268, 1709\n"
    "990 <-> 506, 990\n"
    "991 <-> 420, 535, 917, 1390\n"
    "992 <-> 1628\n"
    "993 <-> 483, 1765\n"
    "994 <-> 1068\n"
    "995 <-> 920, 995\n"
    "996 <-> 209, 282\n"
    "997 <-> 16, 460, 1122, 1769\n"
    "998 <-> 1076, 1602\n"
    "999 <-> 1001, 1697\n"
    "1000 <-> 1648, 1915\n"
    "1001 <-> 256, 605, 999, 1091\n"
    "1002 <-> 435, 457\n"
    "1003 <-> 1382\n"
    "1004 <-> 1254\n"
    "1005 <-> 20, 734, 1651\n"
    "1006 <-> 440\n"
    "1007 <-> 830, 1007\n"
    "1008 <-> 485\n"
    "1009 <-> 624\n"
    "1010 <-> 1353\n"
    "1011 <-> 139, 436, 1675\n"
    "1012 <-> 1836\n"
    "1013 <-> 918, 1891\n"
    "1014 <-> 277, 425\n"
    "1015 <-> 1191\n"
    "1016 <-> 387\n"
    "1017 <-> 1483\n"
    "1018 <-> 305\n"
    "1019 <-> 652, 1798\n"
    "1020 <-> 461, 490, 1843\n"
    "1021 <-> 1021\n"
    "1022 <-> 240, 415, 1507\n"
    "1023 <-> 1919\n"
    "1024 <-> 719, 1925\n"
    "1025 <-> 644, 1735\n"
    "1026 <-> 900\n"
    "1027 <-> 507, 1432\n"
    "1028 <-> 829, 953, 1927\n"
    "1029 <-> 1029\n"
    "1030 <-> 1923\n"
    "1031 <-> 1505\n"
    "1032 <-> 619, 1151\n"
    "1033 <-> 1949\n"
    "1034 <-> 1115\n"
    "1035 <-> 887\n"
    "1036 <-> 355\n"
    "1037 <-> 168, 309, 339, 1835\n"
    "1038 <-> 463, 759\n"
    "1039 <-> 154, 245, 271\n"
    "1040 <-> 99, 749, 1153, 1477\n"
    "1041 <-> 260, 550\n"
    "1042 <-> 1814\n"
    "1043 <-> 648, 1091\n"
    "1044 <-> 373, 1614\n"
    "1045 <-> 725, 840, 895, 1309\n"
    "1046 <-> 323\n"
    "1047 <-> 1238, 1499, 1569\n"
    "1048 <-> 407, 1533\n"
    "1049 <-> 1856\n"
    "1050 <-> 257, 555\n"
    "1051 <-> 817, 1051\n"
    "1052 <-> 313\n"
    "1053 <-> 47, 272\n"
    "1054 <-> 378, 1648\n"
    "1055 <-> 1055\n"
    "1056 <-> 180, 1387\n"
    "1057 <-> 1057, 1793, 1924\n"
    "1058 <-> 118, 1474\n"
    "1059 <-> 1566, 1851\n"
    "1060 <-> 650\n"
    "1061 <-> 96, 1063\n"
    "1062 <-> 418, 674\n"
    "1063 <-> 1061\n"
    "1064 <-> 701, 709, 1867, 1963\n"
    "1065 <-> 818\n"
    "1066 <-> 241, 765\n"
    "1067 <-> 913\n"
    "1068 <-> 8, 263, 994\n"
    "1069 <-> 1555\n"
    "1070 <-> 175, 599, 1070\n"
    "1071 <-> 614, 1245\n"
    "1072 <-> 1086, 1685\n"
    "1073 <-> 289, 575, 777, 826\n"
    "1074 <-> 900, 1434\n"
    "1075 <-> 1492\n"
    "1076 <-> 912, 998, 1119\n"
    "1077 <-> 1183\n"
    "1078 <-> 1771, 1792\n"
    "1079 <-> 86, 281, 1167\n"
    "1080 <-> 75, 456, 1168, 1337\n"
    "1081 <-> 1741\n"
    "1082 <-> 746\n"
    "1083 <-> 1378\n"
    "1084 <-> 549, 1199\n"
    "1085 <-> 1085\n"
    "1086 <-> 919, 1072\n"
    "1087 <-> 1087, 1726\n"
    "1088 <-> 755\n"
    "1089 <-> 1089\n"
    "1090 <-> 362, 848, 1474\n"
    "1091 <-> 1001, 1043\n"
    "1092 <-> 791, 824, 1933\n"
    "1093 <-> 1190\n"
    "1094 <-> 846\n"
    "1095 <-> 1095\n"
    "1096 <-> 589, 720, 1096\n"
    "1097 <-> 702, 940\n"
    "1098 <-> 377\n"
    "1099 <-> 1099\n"
    "1100 <-> 1212\n"
    "1101 <-> 913, 1543\n"
    "1102 <-> 34, 1392, 1626, 1985\n"
    "1103 <-> 324, 944, 1348, 1494, 1981\n"
    "1104 <-> 1104\n"
    "1105 <-> 1400\n"
    "1106 <-> 1678, 1842, 1974\n"
    "1107 <-> 820\n"
    "1108 <-> 1202\n"
    "1109 <-> 1219, 1539\n"
    "1110 <-> 1144, 1179\n"
    "1111 <-> 576, 780\n"
    "1112 <-> 1357\n"
    "1113 <-> 567, 579\n"
    "1114 <-> 347, 1696\n"
    "1115 <-> 76, 584, 1034, 1981\n"
    "1116 <-> 116\n"
    "1117 <-> 127, 353, 1635\n"
    "1118 <-> 600\n"
    "1119 <-> 1076, 1445\n"
    "1120 <-> 1735, 1946\n"
    "1121 <-> 1778\n"
    "1122 <-> 487, 997, 1253\n"
    "1123 <-> 1792\n"
    "1124 <-> 771, 895, 1266\n"
    "1125 <-> 307\n"
    "1126 <-> 343\n"
    "1127 <-> 1127, 1164\n"
    "1128 <-> 78, 1700\n"
    "1129 <-> 1149, 1625\n"
    "1130 <-> 1871\n"
    "1131 <-> 1131\n"
    "1132 <-> 1207, 1208, 1861\n"
    "1133 <-> 938\n"
    "1134 <-> 236, 499, 624\n"
    "1135 <-> 1489, 1607\n"
    "1136 <-> 472\n"
    "1137 <-> 1298\n"
    "1138 <-> 875\n"
    "1139 <-> 712, 1139\n"
    "1140 <-> 807\n"
    "1141 <-> 1329\n"
    "1142 <-> 1170, 1559\n"
    "1143 <-> 1143\n"
    "1144 <-> 838, 1110, 1223\n"
    "1145 <-> 402, 1145\n"
    "1146 <-> 382, 1364\n"
    "1147 <-> 588, 939\n"
    "1148 <-> 1421, 1831\n"
    "1149 <-> 1129, 1905, 1959\n"
    "1150 <-> 370, 729\n"
    "1151 <-> 128, 1032, 1233\n"
    "1152 <-> 248, 1152, 1708, 1803\n"
    "1153 <-> 1040, 1377\n"
    "1154 <-> 1209\n"
    "1155 <-> 74, 1787\n"
    "1156 <-> 794\n"
    "1157 <-> 430, 1975\n"
    "1158 <-> 1158, 1592\n"
    "1159 <-> 465, 751, 1454\n"
    "1160 <-> 541, 553, 1175\n"
    "1161 <-> 1786, 1824\n"
    "1162 <-> 1262, 1321, 1876\n"
    "1163 <-> 740, 1283, 1903\n"
    "1164 <-> 1127\n"
    "1165 <-> 477, 692\n"
    "1166 <-> 1344, 1967\n"
    "1167 <-> 1079\n"
    "1168 <-> 22, 1080\n"
    "1169 <-> 1172, 1647\n"
    "1170 <-> 1142\n"
    "1171 <-> 978, 1171\n"
    "1172 <-> 241, 1169, 1723\n"
    "1173 <-> 1375\n"
    "1174 <-> 406, 518, 1323\n"
    "1175 <-> 512, 1160, 1343, 1982\n"
    "1176 <-> 272, 1176\n"
    "1177 <-> 430\n"
    "1178 <-> 1910\n"
    "1179 <-> 1110\n"
    "1180 <-> 1596\n"
    "1181 <-> 460, 625, 731, 745, 860, 1647\n"
    "1182 <-> 422\n"
    "1183 <-> 298, 1077\n"
    "1184 <-> 386\n"
    "1185 <-> 1729, 1972\n"
    "1186 <-> 87, 305, 351\n"
    "1187 <-> 1454, 1670\n"
    "1188 <-> 1779, 1976\n"
    "1189 <-> 1731, 1794, 1980\n"
    "1190 <-> 554, 1093, 1326, 1332, 1999\n"
    "1191 <-> 1015, 1784, 1920, 1998\n"
    "1192 <-> 1923, 1937\n"
    "1193 <-> 1333\n"
    "1194 <-> 159, 676\n"
    "1195 <-> 908, 1311, 1805\n"
    "1196 <-> 39, 662\n"
    "1197 <-> 773\n"
    "1198 <-> 1468\n"
    "1199 <-> 1084, 1826\n"
    "1200 <-> 63, 685, 1490\n"
    "1201 <-> 750\n"
    "1202 <-> 1108, 1618\n"
    "1203 <-> 566\n"
    "1204 <-> 776, 1204\n"
    "1205 <-> 934\n"
    "1206 <-> 372\n"
    "1207 <-> 1132, 1207, 1342\n"
    "1208 <-> 1132\n"
    "1209 <-> 562, 1154, 1840\n"
    "1210 <-> 356\n"
    "1211 <-> 890, 1259\n"
    "1212 <-> 49, 1100, 1385\n"
    "1213 <-> 666, 721, 1469, 1583, 1984\n"
    "1214 <-> 1734\n"
    "1215 <-> 454, 523, 563\n"
    "1216 <-> 1583\n"
    "1217 <-> 219, 1749\n"
    "1218 <-> 805, 1611\n"
    "1219 <-> 278, 1109\n"
    "1220 <-> 929, 1904, 1919\n"
    "1221 <-> 882\n"
    "1222 <-> 1462\n"
    "1223 <-> 1144, 1223, 1384\n"
    "1224 <-> 382, 665\n"
    "1225 <-> 118, 320\n"
    "1226 <-> 872, 1744, 1895\n"
    "1227 <-> 1601\n"
    "1228 <-> 631, 696, 713\n"
    "1229 <-> 120, 640, 1642, 1993\n"
    "1230 <-> 1400, 1494\n"
    "1231 <-> 1942\n"
    "1232 <-> 156, 763, 875\n"
    "1233 <-> 1151\n"
    "1234 <-> 1234\n"
    "1235 <-> 1510, 1888\n"
    "1236 <-> 1591\n"
    "1237 <-> 1912\n"
    "1238 <-> 1047\n"
    "1239 <-> 1371\n"
    "1240 <-> 87, 696, 1799\n"
    "1241 <-> 160, 1915\n"
    "1242 <-> 1242, 1900\n"
    "1243 <-> 1303\n"
    "1244 <-> 561, 622, 1942\n"
    "1245 <-> 158, 1071\n"
    "1246 <-> 184, 881, 1899\n"
    "1247 <-> 1539\n"
    "1248 <-> 273, 321\n"
    "1249 <-> 1324\n"
    "1250 <-> 1354\n"
    "1251 <-> 127\n"
    "1252 <-> 662, 1304, 1374\n"
    "1253 <-> 1122\n"
    "1254 <-> 208, 478, 1004, 1378\n"
    "1255 <-> 1995\n"
    "1256 <-> 379, 1349\n"
    "1257 <-> 222, 552\n"
    "1258 <-> 155, 393, 1574, 1647\n"
    "1259 <-> 124, 738, 1211, 1409\n"
    "1260 <-> 1862\n"
    "1261 <-> 720\n"
    "1262 <-> 194, 1162, 1349, 1458\n"
    "1263 <-> 348\n"
    "1264 <-> 215\n"
    "1265 <-> 602, 1265, 1970\n"
    "1266 <-> 22, 1124\n"
    "1267 <-> 291, 343, 1729, 1918\n"
    "1268 <-> 103, 804, 989\n"
    "1269 <-> 732\n"
    "1270 <-> 538\n"
    "1271 <-> 25, 1285\n"
    "1272 <-> 406, 1629\n"
    "1273 <-> 221, 731, 905\n"
    "1274 <-> 35, 780\n"
    "1275 <-> 1752\n"
    "1276 <-> 988\n"
    "1277 <-> 1788\n"
    "1278 <-> 798, 970\n"
    "1279 <-> 740\n"
    "1280 <-> 490, 1763\n"
    "1281 <-> 1281\n"
    "1282 <-> 814, 1341\n"
    "1283 <-> 1163\n"
    "1284 <-> 1447, 1494\n"
    "1285 <-> 985, 1271\n"
    "1286 <-> 532, 581, 881\n"
    "1287 <-> 323\n"
    "1288 <-> 1681\n"
    "1289 <-> 544, 1665, 1928\n"
    "1290 <-> 168\n"
    "1291 <-> 1435\n"
    "1292 <-> 199\n"
    "1293 <-> 439\n"
    "1294 <-> 219\n"
    "1295 <-> 1526\n"
    "1296 <-> 1296, 1411\n"
    "1297 <-> 174, 714\n"
    "1298 <-> 61, 1137, 1416, 1724, 1979\n"
    "1299 <-> 1673\n"
    "1300 <-> 389, 1464\n"
    "1301 <-> 621\n"
    "1302 <-> 607, 1788\n"
    "1303 <-> 1243, 1303\n"
    "1304 <-> 760, 1252\n"
    "1305 <-> 390, 1452\n"
    "1306 <-> 1728\n"
    "1307 <-> 59, 193\n"
    "1308 <-> 1943\n"
    "1309 <-> 1045, 1403\n"
    "1310 <-> 1938\n"
    "1311 <-> 98, 1195\n"
    "1312 <-> 871, 1478, 1834\n"
    "1313 <-> 1379\n"
    "1314 <-> 653\n"
    "1315 <-> 106, 1955, 1968\n"
    "1316 <-> 577, 1523\n"
    "1317 <-> 1826\n"
    "1318 <-> 212, 580\n"
    "1319 <-> 1371\n"
    "1320 <-> 1406\n"
    "1321 <-> 1162\n"
    "1322 <-> 188\n"
    "1323 <-> 1174, 1633\n"
    "1324 <-> 443, 876, 1249, 1832\n"
    "1325 <-> 227, 1569\n"
    "1326 <-> 1190\n"
    "1327 <-> 437\n"
    "1328 <-> 704, 1689\n"
    "1329 <-> 832, 1141, 1330\n"
    "1330 <-> 1329, 1330\n"
    "1331 <-> 471, 500, 887\n"
    "1332 <-> 1190, 1429\n"
    "1333 <-> 1193, 1792\n"
    "1334 <-> 255, 1345\n"
    "1335 <-> 575\n"
    "1336 <-> 426, 455, 1913\n"
    "1337 <-> 1080\n"
    "1338 <-> 167, 1338\n"
    "1339 <-> 1517\n"
    "1340 <-> 1866\n"
    "1341 <-> 1282\n"
    "1342 <-> 1207\n"
    "1343 <-> 1175\n"
    "1344 <-> 1166\n"
    "1345 <-> 310, 1334\n"
    "1346 <-> 1346, 1719\n"
    "1347 <-> 1375\n"
    "1348 <-> 1103\n"
    "1349 <-> 1256, 1262\n"
    "1350 <-> 862, 1350\n"
    "1351 <-> 78, 1444\n"
    "1352 <-> 1845\n"
    "1353 <-> 1010, 1922\n"
    "1354 <-> 1250, 1363\n"
    "1355 <-> 72, 835, 865, 1936\n"
    "1356 <-> 25\n"
    "1357 <-> 1112, 1357\n"
    "1358 <-> 502\n"
    "1359 <-> 1814\n"
    "1360 <-> 1468\n"
    "1361 <-> 3, 329, 463, 517\n"
    "1362 <-> 333, 710\n"
    "1363 <-> 316, 1354, 1759\n"
    "1364 <-> 480, 1146\n"
    "1365 <-> 544\n"
    "1366 <-> 91, 535\n"
    "1367 <-> 802, 1543, 1609\n"
    "1368 <-> 948, 1631, 1864\n"
    "1369 <-> 668, 1964\n"
    "1370 <-> 1370\n"
    "1371 <-> 650, 843, 1239, 1319, 1528\n"
    "1372 <-> 984, 1447\n"
    "1373 <-> 62, 364, 866, 1884\n"
    "1374 <-> 1252\n"
    "1375 <-> 57, 187, 763, 953, 1173, 1347\n"
    "1376 <-> 284, 1878\n"
    "1377 <-> 161, 1153\n"
    "1378 <-> 1083, 1254, 1378, 1856\n"
    "1379 <-> 834, 1313, 1792\n"
    "1380 <-> 1967\n"
    "1381 <-> 613, 947, 1523\n"
    "1382 <-> 718, 1003, 1796\n"
    "1383 <-> 737, 914\n"
    "1384 <-> 1223\n"
    "1385 <-> 205, 1212\n"
    "1386 <-> 466, 1623\n"
    "1387 <-> 445, 934, 1056\n"
    "1388 <-> 1456\n"
    "1389 <-> 193, 1427, 1701\n"
    "1390 <-> 991\n"
    "1391 <-> 689\n"
    "1392 <-> 1102\n"
    "1393 <-> 341, 653, 1513\n"
    "1394 <-> 1509\n"
    "1395 <-> 1409\n"
    "1396 <-> 1593, 1982\n"
    "1397 <-> 100, 913\n"
    "1398 <-> 1668\n"
    "1399 <-> 686\n"
    "1400 <-> 1105, 1230\n"
    "1401 <-> 596, 1506\n"
    "1402 <-> 209, 505, 1628\n"
    "1403 <-> 340, 1309\n"
    "1404 <-> 1754\n"
    "1405 <-> 314, 466\n"
    "1406 <-> 1320, 1796, 1883\n"
    "1407 <-> 448, 1542\n"
    "1408 <-> 1616\n"
    "1409 <-> 322, 1259, 1395, 1462\n"
    "1410 <-> 905\n"
    "1411 <-> 290, 1296\n"
    "1412 <-> 50, 824\n"
    "1413 <-> 1943, 1955, 1997\n"
    "1414 <-> 247\n"
    "1415 <-> 1415\n"
    "1416 <-> 1298\n"
    "1417 <-> 808\n"
    "1418 <-> 388, 1487, 1666\n"
    "1419 <-> 90\n"
    "1420 <-> 1435, 1486, 1947\n"
    "1421 <-> 1148, 1679\n"
    "1422 <-> 774\n"
    "1423 <-> 233\n"
    "1424 <-> 1670\n"
    "1425 <-> 1910\n"
    "1426 <-> 293, 869\n"
    "1427 <-> 1389, 1634, 1740\n"
    "1428 <-> 244, 1428, 1831\n"
    "1429 <-> 344, 1332\n"
    "1430 <-> 1985\n"
    "1431 <-> 376\n"
    "1432 <-> 1027\n"
    "1433 <-> 462, 625\n"
    "1434 <-> 1074\n"
    "1435 <-> 1291, 1420\n"
    "1436 <-> 841\n"
    "1437 <-> 651, 1616\n"
    "1438 <-> 887\n"
    "1439 <-> 218\n"
    "1440 <-> 1770, 1809\n"
    "1441 <-> 838\n"
    "1442 <-> 955, 1714\n"
    "1443 <-> 64\n"
    "1444 <-> 1351\n"
    "1445 <-> 1119, 1445\n"
    "1446 <-> 286\n"
    "1447 <-> 1284, 1372\n"
    "1448 <-> 522, 777, 1969\n"
    "1449 <-> 136, 569, 620, 982\n"
    "1450 <-> 195, 443, 1516\n"
    "1451 <-> 1451\n"
    "1452 <-> 337, 1305, 1552\n"
    "1453 <-> 1801, 1906\n"
    "1454 <-> 1159, 1187\n"
    "1455 <-> 1562\n"
    "1456 <-> 231, 520, 1388, 1775, 1833\n"
    "1457 <-> 864, 1905\n"
    "1458 <-> 1262\n"
    "1459 <-> 573\n"
    "1460 <-> 807\n"
    "1461 <-> 1599, 1706\n"
    "1462 <-> 1222, 1409\n"
    "1463 <-> 970, 1937\n"
    "1464 <-> 877, 1300, 1677\n"
    "1465 <-> 1602\n"
    "1466 <-> 1919\n"
    "1467 <-> 1467\n"
    "1468 <-> 1198, 1360, 1987\n"
    "1469 <-> 1213, 1896\n"
    "1470 <-> 136, 438, 932\n"
    "1471 <-> 515, 1952\n"
    "1472 <-> 65, 226\n"
    "1473 <-> 1585\n"
    "1474 <-> 1058, 1090\n"
    "1475 <-> 327, 530\n"
    "1476 <-> 95, 1627, 1866\n"
    "1477 <-> 697, 1040, 1827\n"
    "1478 <-> 892, 1312, 1478\n"
    "1479 <-> 751\n"
    "1480 <-> 1480\n"
    "1481 <-> 1481\n"
    "1482 <-> 495\n"
    "1483 <-> 600, 1017\n"
    "1484 <-> 251, 1717, 1920\n"
    "1485 <-> 1618, 1797\n"
    "1486 <-> 1420\n"
    "1487 <-> 1418, 1828\n"
    "1488 <-> 1545\n"
    "1489 <-> 295, 837, 1135, 1859\n"
    "1490 <-> 170, 178, 1200\n"
    "1491 <-> 865, 1500, 1858\n"
    "1492 <-> 157, 202, 1075\n"
    "1493 <-> 466, 553\n"
    "1494 <-> 893, 1103, 1230, 1284\n"
    "1495 <-> 118\n"
    "1496 <-> 402, 734\n"
    "1497 <-> 1953\n"
    "1498 <-> 541, 1662\n"
    "1499 <-> 445, 1047\n"
    "1500 <-> 626, 1491, 1922\n"
    "1501 <-> 348, 586, 767\n"
    "1502 <-> 376, 855, 1960, 1965\n"
    "1503 <-> 1755\n"
    "1504 <-> 852\n"
    "1505 <-> 387, 1031, 1854\n"
    "1506 <-> 1401\n"
    "1507 <-> 1022\n"
    "1508 <-> 1853\n"
    "1509 <-> 1394, 1509, 1732\n"
    "1510 <-> 1235\n"
    "1511 <-> 413, 1990\n"
    "1512 <-> 586, 604, 1862\n"
    "1513 <-> 1393\n"
    "1514 <-> 516\n"
    "1515 <-> 966, 1716\n"
    "1516 <-> 340, 1450\n"
    "1517 <-> 9, 1339, 1587\n"
    "1518 <-> 1518, 1912, 1956\n"
    "1519 <-> 71, 201, 953\n"
    "1520 <-> 1520\n"
    "1521 <-> 29, 285, 1906\n"
    "1522 <-> 1538, 1994\n"
    "1523 <-> 486, 1316, 1381\n"
    "1524 <-> 851\n"
    "1525 <-> 1737\n"
    "1526 <-> 332, 988, 1295\n"
    "1527 <-> 401, 659\n"
    "1528 <-> 1371\n"
    "1529 <-> 316\n"
    "1530 <-> 892\n"
    "1531 <-> 1531\n"
    "1532 <-> 117, 649\n"
    "1533 <-> 35, 448, 1048\n"
    "1534 <-> 437, 932\n"
    "1535 <-> 1630\n"
    "1536 <-> 119\n"
    "1537 <-> 761, 1869\n"
    "1538 <-> 1522\n"
    "1539 <-> 275, 1109, 1247\n"
    "1540 <-> 525, 1540\n"
    "1541 <-> 852, 1541\n"
    "1542 <-> 1407, 1694\n"
    "1543 <-> 220, 239, 1101, 1367\n"
    "1544 <-> 1972\n"
    "1545 <-> 132, 711, 1488\n"
    "1546 <-> 475\n"
    "1547 <-> 86, 858\n"
    "1548 <-> 410, 1616\n"
    "1549 <-> 1852\n"
    "1550 <-> 545, 1711\n"
    "1551 <-> 556, 821\n"
    "1552 <-> 241, 332, 1452, 1987\n"
    "1553 <-> 304, 925\n"
    "1554 <-> 1554\n"
    "1555 <-> 1069, 1727\n"
    "1556 <-> 845, 1561\n"
    "1557 <-> 269\n"
    "1558 <-> 1558\n"
    "1559 <-> 340, 1142\n"
    "1560 <-> 400, 612, 755\n"
    "1561 <-> 1556\n"
    "1562 <-> 1455, 1697\n"
    "1563 <-> 1563, 1736\n"
    "1564 <-> 77, 1564\n"
    "1565 <-> 115, 797, 973\n"
    "1566 <-> 80, 439, 1059\n"
    "1567 <-> 134, 429, 983\n"
    "1568 <-> 1570\n"
    "1569 <-> 1047, 1325\n"
    "1570 <-> 1568, 1932\n"
    "1571 <-> 1628, 1755\n"
    "1572 <-> 316\n"
    "1573 <-> 173\n"
    "1574 <-> 1258\n"
    "1575 <-> 1856\n"
    "1576 <-> 1708\n"
    "1577 <-> 1577\n"
    "1578 <-> 101, 1660\n"
    "1579 <-> 815\n"
    "1580 <-> 1580\n"
    "1581 <-> 521, 1689\n"
    "1582 <-> 131, 190, 548\n"
    "1583 <-> 1213, 1216\n"
    "1584 <-> 200\n"
    "1585 <-> 493, 1473\n"
    "1586 <-> 898\n"
    "1587 <-> 767, 1517\n"
    "1588 <-> 486\n"
    "1589 <-> 797, 1822\n"
    "1590 <-> 956\n"
    "1591 <-> 845, 1236, 1688\n"
    "1592 <-> 1158\n"
    "1593 <-> 839, 931, 1396\n"
    "1594 <-> 369, 683\n"
    "1595 <-> 313, 1731\n"
    "1596 <-> 208, 1180\n"
    "1597 <-> 65\n"
    "1598 <-> 1598\n"
    "1599 <-> 1461\n"
    "1600 <-> 782\n"
    "1601 <-> 138, 1227, 1837, 1932\n"
    "1602 <-> 998, 1465\n"
    "1603 <-> 656\n"
    "1604 <-> 173, 706, 887\n"
    "1605 <-> 66, 202\n"
    "1606 <-> 428, 771\n"
    "1607 <-> 1135\n"
    "1608 <-> 19, 870, 1608\n"
    "1609 <-> 742, 1367\n"
    "1610 <-> 514, 1703\n"
    "1611 <-> 358, 1218\n"
    "1612 <-> 547\n"
    "1613 <-> 236\n"
    "1614 <-> 1044\n"
    "1615 <-> 1697\n"
    "1616 <-> 576, 1408, 1437, 1548\n"
    "1617 <-> 1617\n"
    "1618 <-> 1202, 1485\n"
    "1619 <-> 1910\n"
    "1620 <-> 530, 587, 760\n"
    "1621 <-> 705\n"
    "1622 <-> 143, 411\n"
    "1623 <-> 1386\n"
    "1624 <-> 85, 862, 1691\n"
    "1625 <-> 787, 790, 1129\n"
    "1626 <-> 794, 1102\n"
    "1627 <-> 350, 783, 1476, 1822\n"
    "1628 <-> 992, 1402, 1571\n"
    "1629 <-> 1272, 1783\n"
    "1630 <-> 1535, 1630\n"
    "1631 <-> 1368, 1973\n"
    "1632 <-> 722\n"
    "1633 <-> 1323\n"
    "1634 <-> 1427\n"
    "1635 <-> 55, 1117\n"
    "1636 <-> 1636\n"
    "1637 <-> 446\n"
    "1638 <-> 507\n"
    "1639 <-> 177, 418\n"
    "1640 <-> 767, 1989\n"
    "1641 <-> 589\n"
    "1642 <-> 670, 752, 1229\n"
    "1643 <-> 799, 1977\n"
    "1644 <-> 63\n"
    "1645 <-> 474, 578\n"
    "1646 <-> 1829\n"
    "1647 <-> 743, 1169, 1181, 1258\n"
    "1648 <-> 718, 1000, 1054\n"
    "1649 <-> 496, 1649\n"
    "1650 <-> 247, 1806\n"
    "1651 <-> 1005\n"
    "1652 <-> 858\n"
    "1653 <-> 1684, 1747, 1949\n"
    "1654 <-> 847\n"
    "1655 <-> 123, 444, 1771\n"
    "1656 <-> 1705\n"
    "1657 <-> 214, 580, 634\n"
    "1658 <-> 318\n"
    "1659 <-> 610\n"
    "1660 <-> 222, 1578\n"
    "1661 <-> 233, 1661\n"
    "1662 <-> 1498\n"
    "1663 <-> 103, 446, 639\n"
    "1664 <-> 955, 1874\n"
    "1665 <-> 1289\n"
    "1666 <-> 690, 1418\n"
    "1667 <-> 1792\n"
    "1668 <-> 1398, 1668\n"
    "1669 <-> 797, 909, 1709\n"
    "1670 <-> 1187, 1424\n"
    "1671 <-> 302, 817\n"
    "1672 <-> 1851\n"
    "1673 <-> 1299, 1673\n"
    "1674 <-> 465, 1730\n"
    "1675 <-> 293, 1011\n"
    "1676 <-> 816, 1891\n"
    "1677 <-> 467, 1464, 1787\n"
    "1678 <-> 182, 583, 1106, 1852\n"
    "1679 <-> 398, 1421\n"
    "1680 <-> 1680\n"
    "1681 <-> 325, 821, 1288\n"
    "1682 <-> 429, 1682\n"
    "1683 <-> 432, 578\n"
    "1684 <-> 507, 1653, 1806, 1841\n"
    "1685 <-> 114, 471, 660, 833, 1072\n"
    "1686 <-> 1691\n"
    "1687 <-> 738\n"
    "1688 <-> 1591\n"
    "1689 <-> 1328, 1581, 1795\n"
    "1690 <-> 441, 741, 1854\n"
    "1691 <-> 1624, 1686\n"
    "1692 <-> 284, 362\n"
    "1693 <-> 1781\n"
    "1694 <-> 1542\n"
    "1695 <-> 1775\n"
    "1696 <-> 1114\n"
    "1697 <-> 177, 999, 1562, 1615, 1996\n"
    "1698 <-> 3, 1809\n"
    "1699 <-> 1761\n"
    "1700 <-> 7, 1128\n"
    "1701 <-> 1389, 1802\n"
    "1702 <-> 295\n"
    "1703 <-> 1610\n"
    "1704 <-> 220\n"
    "1705 <-> 371, 1656, 1867\n"
    "1706 <-> 142, 1461\n"
    "1707 <-> 1960\n"
    "1708 <-> 1152, 1576, 1961\n"
    "1709 <-> 989, 1669\n"
    "1710 <-> 138\n"
    "1711 <-> 681, 951, 1550\n"
    "1712 <-> 19, 369, 967\n"
    "1713 <-> 906, 1812\n"
    "1714 <-> 1442, 1785\n"
    "1715 <-> 233, 903\n"
    "1716 <-> 946, 1515\n"
    "1717 <-> 84, 1484\n"
    "1718 <-> 1718\n"
    "1719 <-> 102, 1346\n"
    "1720 <-> 146, 581\n"
    "1721 <-> 31, 618, 772\n"
    "1722 <-> 546\n"
    "1723 <-> 108, 1172\n"
    "1724 <-> 770, 1298\n"
    "1725 <-> 1896\n"
    "1726 <-> 1087\n"
    "1727 <-> 533, 746, 1555\n"
    "1728 <-> 238, 570, 1306\n"
    "1729 <-> 361, 663, 1185, 1267\n"
    "1730 <-> 589, 636, 1674\n"
    "1731 <-> 1189, 1595\n"
    "1732 <-> 1509\n"
    "1733 <-> 954\n"
    "1734 <-> 93, 975, 1214\n"
    "1735 <-> 1025, 1120\n"
    "1736 <-> 1563\n"
    "1737 <-> 513, 1525\n"
    "1738 <-> 974\n"
    "1739 <-> 1742\n"
    "1740 <-> 1427\n"
    "1741 <-> 1081, 1950\n"
    "1742 <-> 964, 1739, 1923\n"
    "1743 <-> 594, 1921\n"
    "1744 <-> 869, 1226\n"
    "1745 <-> 895, 966, 1829\n"
    "1746 <-> 282\n"
    "1747 <-> 1653, 1747, 1910\n"
    "1748 <-> 1982\n"
    "1749 <-> 294, 1217\n"
    "1750 <-> 939\n"
    "1751 <-> 651\n"
    "1752 <-> 1275, 1752\n"
    "1753 <-> 373, 1969\n"
    "1754 <-> 618, 967, 1404\n"
    "1755 <-> 472, 1503, 1571\n"
    "1756 <-> 386, 773, 1777\n"
    "1757 <-> 22\n"
    "1758 <-> 417, 804\n"
    "1759 <-> 1363\n"
    "1760 <-> 1935\n"
    "1761 <-> 693, 800, 1699\n"
    "1762 <-> 300\n"
    "1763 <-> 330, 1280\n"
    "1764 <-> 419\n"
    "1765 <-> 993\n"
    "1766 <-> 309\n"
    "1767 <-> 266, 1821\n"
    "1768 <-> 568\n"
    "1769 <-> 997\n"
    "1770 <-> 1440\n"
    "1771 <-> 1078, 1655, 1873\n"
    "1772 <-> 1772\n"
    "1773 <-> 849\n"
    "1774 <-> 821, 1783\n"
    "1775 <-> 1456, 1695\n"
    "1776 <-> 1889, 1943\n"
    "1777 <-> 969, 1756\n"
    "1778 <-> 744, 1121\n"
    "1779 <-> 558, 1188\n"
    "1780 <-> 450\n"
    "1781 <-> 70, 287, 1693\n"
    "1782 <-> 924\n"
    "1783 <-> 1629, 1774\n"
    "1784 <-> 81, 1191\n"
    "1785 <-> 1714\n"
    "1786 <-> 667, 979, 1161\n"
    "1787 <-> 886, 1155, 1677\n"
    "1788 <-> 147, 1277, 1302, 1950\n"
    "1789 <-> 328, 418\n"
    "1790 <-> 902, 913\n"
    "1791 <-> 135\n"
    "1792 <-> 456, 1078, 1123, 1333, 1379, 1667\n"
    "1793 <-> 1057\n"
    "1794 <-> 1189, 1794\n"
    "1795 <-> 1689\n"
    "1796 <-> 1382, 1406, 1953\n"
    "1797 <-> 125, 1485, 1797\n"
    "1798 <-> 186, 1019, 1798\n"
    "1799 <-> 299, 831, 1240\n"
    "1800 <-> 494\n"
    "1801 <-> 1453\n"
    "1802 <-> 107, 1701\n"
    "1803 <-> 18, 412, 733, 1152\n"
    "1804 <-> 221\n"
    "1805 <-> 1195\n"
    "1806 <-> 6, 1650, 1684\n"
    "1807 <-> 1807\n"
    "1808 <-> 715, 938, 1985\n"
    "1809 <-> 754, 1440, 1698\n"
    "1810 <-> 388\n"
    "1811 <-> 165\n"
    "1812 <-> 1713\n"
    "1813 <-> 794, 811\n"
    "1814 <-> 192, 510, 1042, 1359\n"
    "1815 <-> 1941\n"
    "1816 <-> 382\n"
    "1817 <-> 166, 564, 937\n"
    "1818 <-> 21\n"
    "1819 <-> 111\n"
    "1820 <-> 562\n"
    "1821 <-> 572, 787, 1767\n"
    "1822 <-> 1589, 1627\n"
    "1823 <-> 343\n"
    "1824 <-> 945, 1161\n"
    "1825 <-> 90, 163, 438, 646, 914\n"
    "1826 <-> 1199, 1317, 1881\n"
    "1827 <-> 915, 1477\n"
    "1828 <-> 498, 1487\n"
    "1829 <-> 1646, 1745\n"
    "1830 <-> 883\n"
    "1831 <-> 1148, 1428, 1882\n"
    "1832 <-> 805, 1324\n"
    "1833 <-> 537, 1456\n"
    "1834 <-> 1312\n"
    "1835 <-> 774, 789, 1037\n"
    "1836 <-> 986, 1012\n"
    "1837 <-> 164, 1601\n"
    "1838 <-> 360\n"
    "1839 <-> 764\n"
    "1840 <-> 1209, 1888\n"
    "1841 <-> 1684\n"
    "1842 <-> 117, 1106, 1948\n"
    "1843 <-> 1020\n"
    "1844 <-> 835, 1890\n"
    "1845 <-> 1352, 1845\n"
    "1846 <-> 877, 977, 1878\n"
    "1847 <-> 828, 890\n"
    "1848 <-> 123, 1926\n"
    "1849 <-> 1849\n"
    "1850 <-> 8, 150\n"
    "1851 <-> 1059, 1672\n"
    "1852 <-> 1549, 1678\n"
    "1853 <-> 587, 1508\n"
    "1854 <-> 597, 1505, 1690\n"
    "1855 <-> 1855\n"
    "1856 <-> 885, 1049, 1378, 1575\n"
    "1857 <-> 202\n"
    "1858 <-> 355, 1491\n"
    "1859 <-> 1489\n"
    "1860 <-> 603, 855\n"
    "1861 <-> 1132\n"
    "1862 <-> 1260, 1512\n"
    "1863 <-> 390\n"
    "1864 <-> 1368\n"
    "1865 <-> 615\n"
    "1866 <-> 405, 1340, 1476\n"
    "1867 <-> 1064, 1705\n"
    "1868 <-> 1868\n"
    "1869 <-> 409, 1537\n"
    "1870 <-> 90\n"
    "1871 <-> 980, 1130, 1958\n"
    "1872 <-> 397, 574, 807\n"
    "1873 <-> 1771\n"
    "1874 <-> 91, 448, 1664\n"
    "1875 <-> 703, 850\n"
    "1876 <-> 793, 1162\n"
    "1877 <-> 1877\n"
    "1878 <-> 906, 1376, 1846, 1884\n"
    "1879 <-> 191\n"
    "1880 <-> 695\n"
    "1881 <-> 1826\n"
    "1882 <-> 372, 1831\n"
    "1883 <-> 1406\n"
    "1884 <-> 939, 1373, 1878\n"
    "1885 <-> 108\n"
    "1886 <-> 546, 600\n"
    "1887 <-> 58\n"
    "1888 <-> 202, 1235, 1840\n"
    "1889 <-> 1776\n"
    "1890 <-> 1844\n"
    "1891 <-> 1013, 1676\n"
    "1892 <-> 1892\n"
    "1893 <-> 614, 1893\n"
    "1894 <-> 430\n"
    "1895 <-> 1226\n"
    "1896 <-> 381, 1469, 1725\n"
    "1897 <-> 685, 1956\n"
    "1898 <-> 346\n"
    "1899 <-> 1246\n"
    "1900 <-> 1242\n"
    "1901 <-> 1901\n"
    "1902 <-> 374, 618\n"
    "1903 <-> 1163\n"
    "1904 <-> 1220\n"
    "1905 <-> 1149, 1457\n"
    "1906 <-> 316, 1453, 1521\n"
    "1907 <-> 269, 348\n"
    "1908 <-> 189, 1908\n"
    "1909 <-> 541, 637\n"
    "1910 <-> 1178, 1425, 1619, 1747\n"
    "1911 <-> 391, 768\n"
    "1912 <-> 632, 1237, 1518\n"
    "1913 <-> 1336\n"
    "1914 <-> 228, 335\n"
    "1915 <-> 1000, 1241\n"
    "1916 <-> 923\n"
    "1917 <-> 1974\n"
    "1918 <-> 88, 1267\n"
    "1919 <-> 667, 820, 1023, 1220, 1466\n"
    "1920 <-> 287, 491, 1191, 1484\n"
    "1921 <-> 422, 1743\n"
    "1922 <-> 1353, 1500\n"
    "1923 <-> 114, 314, 1030, 1192, 1742\n"
    "1924 <-> 1057\n"
    "1925 <-> 1024\n"
    "1926 <-> 1848\n"
    "1927 <-> 1028\n"
    "1928 <-> 262, 1289\n"
    "1929 <-> 1929\n"
    "1930 <-> 791, 1986\n"
    "1931 <-> 291, 1975\n"
    "1932 <-> 626, 1570, 1601\n"
    "1933 <-> 48, 1092\n"
    "1934 <-> 1934\n"
    "1935 <-> 514, 1760\n"
    "1936 <-> 1355\n"
    "1937 <-> 1192, 1463\n"
    "1938 <-> 260, 916, 1310\n"
    "1939 <-> 640\n"
    "1940 <-> 356\n"
    "1941 <-> 682, 1815\n"
    "1942 <-> 1231, 1244\n"
    "1943 <-> 762, 1308, 1413, 1776\n"
    "1944 <-> 1944\n"
    "1945 <-> 548, 636\n"
    "1946 <-> 257, 1120\n"
    "1947 <-> 140, 1420\n"
    "1948 <-> 1842\n"
    "1949 <-> 1033, 1653\n"
    "1950 <-> 1741, 1788\n"
    "1951 <-> 321, 659\n"
    "1952 <-> 1471\n"
    "1953 <-> 52, 1497, 1796\n"
    "1954 <-> 136\n"
    "1955 <-> 266, 1315, 1413, 1955\n"
    "1956 <-> 1518, 1897\n"
    "1957 <-> 600\n"
    "1958 <-> 726, 1871\n"
    "1959 <-> 1149\n"
    "1960 <-> 175, 947, 1502, 1707\n"
    "1961 <-> 1708\n"
    "1962 <-> 477\n"
    "1963 <-> 1064\n"
    "1964 <-> 904, 1369\n"
    "1965 <-> 1502\n"
    "1966 <-> 427, 814, 1966\n"
    "1967 <-> 411, 1166, 1380\n"
    "1968 <-> 1315\n"
    "1969 <-> 859, 1448, 1753\n"
    "1970 <-> 283, 1265\n"
    "1971 <-> 279\n"
    "1972 <-> 1185, 1544\n"
    "1973 <-> 1631\n"
    "1974 <-> 123, 1106, 1917\n"
    "1975 <-> 1157, 1931\n"
    "1976 <-> 307, 1188\n"
    "1977 <-> 82, 285, 595, 1643\n"
    "1978 <-> 412\n"
    "1979 <-> 944, 1298\n"
    "1980 <-> 354, 1189\n"
    "1981 <-> 452, 590, 1103, 1115\n"
    "1982 <-> 1175, 1396, 1748\n"
    "1983 <-> 874, 892\n"
    "1984 <-> 936, 1213\n"
    "1985 <-> 56, 972, 1102, 1430, 1808\n"
    "1986 <-> 561, 1930\n"
    "1987 <-> 1468, 1552\n"
    "1988 <-> 415, 758\n"
    "1989 <-> 311, 1640\n"
    "1990 <-> 852, 1511\n"
    "1991 <-> 804\n"
    "1992 <-> 824\n"
    "1993 <-> 1229\n"
    "1994 <-> 485, 942, 1522\n"
    "1995 <-> 156, 1255\n"
    "1996 <-> 1697\n"
    "1997 <-> 1413\n"
    "1998 <-> 1191\n"
    "1999 <-> 807, 1190\n";


// e.g. parse("2 <-> 0, 3, 4") -> set{0, 2, 3, 4}
std::set<int> parse(std::string line)
{
    std::set<int> result;

    std::locale loc;
    const std::vector<std::string> tokens(split(line));
    for (auto token: tokens) {
        if (std::isdigit(token[0], loc))
            result.insert(std::stoi(token));
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
    eachline(input, [&](std::string line) {
        mapping.push_back(parse(line));
    });

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
    eachline(input, [&](std::string line) {
        mapping.push_back(parse(line));
    });

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

void run()
{
    const char * test =
        "0 <-> 2\n"
        "1 <-> 1\n"
        "2 <-> 0, 3, 4\n"
        "3 <-> 2, 4\n"
        "4 <-> 2, 3, 6\n"
        "5 <-> 6\n"
        "6 <-> 4, 5\n";

    assert(connected0(test) == 6);

    const int part1 = connected0(input);
    std::cout << "12.1 " << part1 << '\n';
    assert(part1 == 130);

    assert(connected_groups(test) == 2);

    const int part2 = connected_groups(input);
    std::cout << "12.2 " << part2 << '\n';
    assert(part2 == 189);
}

}



namespace day13 {

const char * input =
    "0: 3\n"
    "1: 2\n"
    "2: 6\n"
    "4: 4\n"
    "6: 4\n"
    "8: 10\n"
    "10: 6\n"
    "12: 8\n"
    "14: 5\n"
    "16: 6\n"
    "18: 8\n"
    "20: 8\n"
    "22: 12\n"
    "24: 6\n"
    "26: 9\n"
    "28: 8\n"
    "30: 8\n"
    "32: 10\n"
    "34: 12\n"
    "36: 12\n"
    "38: 8\n"
    "40: 12\n"
    "42: 12\n"
    "44: 14\n"
    "46: 12\n"
    "48: 12\n"
    "50: 12\n"
    "52: 12\n"
    "54: 14\n"
    "56: 14\n"
    "58: 14\n"
    "60: 12\n"
    "62: 14\n"
    "64: 14\n"
    "66: 17\n"
    "68: 14\n"
    "72: 18\n"
    "74: 14\n"
    "76: 20\n"
    "78: 14\n"
    "82: 18\n"
    "86: 14\n"
    "90: 18\n"
    "92: 14\n";

// e.g. parse("92: 14") -> pair(92, 14)
std::pair<int, int> parse(std::string line)
{
    const std::vector<std::string> tokens(split(line));
    assert(tokens.size() == 2);
    return std::make_pair(std::stoi(tokens[0]), std::stoi(tokens[1]));
}



struct layer {
    int range;

    explicit layer(int range = 0)
        : range(range)
    {
    }

    bool caught(int picosec) const
    {
        return range && (picosec % (2*range - 2)) == 0;
    }
};


int severity(const char * input)
{
    std::map<int, int> layers_input;
    eachline(input, [&](std::string line) {
        const auto p(parse(line));
        layers_input[p.first] = p.second;
    });
    assert(layers_input.size() != 0);

    const int total_layers = layers_input.rbegin()->first + 1;
    std::vector<layer> layers(total_layers);
    for (auto l: layers_input)
        layers[l.first] = layer(l.second);

    int trip_severity = 0;
    for (int picosec = 0; picosec < total_layers; ++picosec) {
        if (layers[picosec].caught(picosec))
            trip_severity += picosec * layers[picosec].range;
    }

    return trip_severity;
}


bool caught(std::vector<layer> layers, int delay_start)
{
    for (int in_layer = 0; in_layer < static_cast<int>(layers.size()); ++in_layer)
        if (layers[in_layer].caught(delay_start + in_layer))
            return true;
    return false;
}


std::vector<layer> build(const char * input)
{
    std::map<int, int> layers_input;
    eachline(input, [&](std::string line) {
        const auto p(parse(line));
        layers_input[p.first] = p.second;
    });
    assert(layers_input.size() != 0);

    const int total_layers = layers_input.rbegin()->first + 1;
    std::vector<layer> layers(total_layers);
    for (auto l: layers_input)
        layers[l.first] = layer(l.second);

    return layers;
}


int part2(const char * input)
{
    const std::vector<layer> layers(build(input));
    int delay_start = 0;
    while (caught(layers, delay_start))
        ++delay_start;
    return delay_start;
}


void run()
{
    const char * test =
        "0: 3\n"
        "1: 2\n"
        "4: 4\n"
        "6: 4\n";

    assert(severity(test) == 24);

    const int part1 = severity(input);
    std::cout << "13.1 " << part1 << '\n';
    assert(part1 == 3184);

    assert(part2(test) == 10);

    const int answer2 = part2(input);
    std::cout << "13.2 " << answer2 << '\n';
    assert(answer2 == 3878062);
}

}



namespace day14 {

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


void run()
{
    assert(used("flqrgnkx") == 8108);

    const int part1 = used("oundnydw");
    std::cout << "14.1 " << part1 << '\n';
    assert(part1 == 8106);

    assert(regions("flqrgnkx") == 1242);

    const int part2 = regions("oundnydw");
    std::cout << "14.2 " << part2 << '\n';
    assert(part2 == 1164);
}

}



namespace day15 {

class generator {
    uint64_t val_;
    uint64_t factor_;

public:
    explicit generator(uint64_t seed, uint64_t factor)
        : val_(seed), factor_(factor)
    {
    }

    uint64_t next()
    {
        return val_ = (val_ * factor_) % 2147483647ul;
    }
};


int part1(uint64_t seeda, uint64_t seedb)
{
    int count = 0;
    generator gena(seeda, 16807), genb(seedb, 48271);
    for (int i = 0; i < 40000000; ++i)
        count += (gena.next() & 0xFFFF) == (genb.next() & 0xFFFF);
    return count;
}


class generator2 {
    uint64_t val_;
    uint64_t factor_;
    uint64_t multiples_criterior_;

public:
    explicit generator2(uint64_t seed, uint64_t factor, uint64_t multiples_criterior)
        : val_(seed), factor_(factor), multiples_criterior_(multiples_criterior)
    {
    }

    uint64_t next()
    {
        do {
            val_ = (val_ * factor_) % 2147483647ul;
        } while ((val_ % multiples_criterior_) != 0);
        return val_;
    }
};

int part2(uint64_t seeda, uint64_t seedb)
{
    int count = 0;
    generator2 gena(seeda, 16807, 4), genb(seedb, 48271, 8);
    for (int i = 0; i < 5000000; ++i)
        count += (gena.next() & 0xFFFF) == (genb.next() & 0xFFFF);
    return count;
}


void run()
{
    assert(part1(65, 8921) == 588);

    const int answer1 = part1(618, 814);
    std::cout << "15.1 " << answer1 << '\n';
    assert(answer1 == 577);

    assert(part2(65, 8921) == 309);

    const int answer2 = part2(618, 814);
    std::cout << "15.2 " << answer2 << '\n';
    assert(answer2 == 316);
}

}



namespace day16 {

const char * input =
"x3/15,pc/l,x13/9,pe/f,x3/14,s2,x8/10,s15,x4/0,s4,pn/k,x9/13,s5,x3/6,s14,x9/14,s10,x5/13,ph/"
"j,x11/8,s11,x0/15,pa/d,x3/1,pg/l,x6/5,s11,x12/13,pj/d,s1,x11/0,pm/f,x4/15,s5,x3/5,ph/"
"c,x13/12,s15,x10/6,s11,x11/2,po/i,x0/9,s11,x11/15,s13,x7/3,s4,x12/13,s5,x14/11,pc/"
"e,x1/7,s6,x3/5,pk/j,x7/0,ph/f,x10/8,s8,x13/6,pl/o,x8/0,s2,x4/13,pn/c,x1/12,po/"
"g,x15/4,s8,x10/12,s4,x11/0,pp/d,x7/14,s6,pf/e,x2/15,pc/"
"b,s14,x5/10,s12,x7/8,s4,x0/1,s12,x12/3,s6,pd/o,s9,x14/7,s5,pl/g,s11,po/m,x12/8,s11,x7/"
"0,s1,x1/14,pe/c,x9/2,pa/j,s14,x8/1,ph/g,x14/3,s4,x7/1,s10,x4/11,po/f,x12/15,pj/p,x7/8,pa/"
"h,x6/3,pl/c,x1/9,pb/g,x15/3,pc/k,x0/1,s6,x11/3,s6,x1/15,ph/e,s3,x13/0,s7,x15/9,pj/"
"c,x1/10,s14,x15/3,s15,x5/2,pl/f,x10/9,pg/h,x4/6,pi/j,x5/14,s10,x3/1,s2,x0/7,pd/o,x4/8,pe/"
"a,x9/15,pj/h,x4/0,s15,x12/8,s3,x14/11,s8,x3/2,pd/e,x0/8,s10,x1/10,pn/i,x4/8,pc/"
"f,x5/14,s5,x0/7,s15,x12/11,s3,x8/6,s7,x11/15,ph/l,x12/7,s9,x10/3,s14,x12/7,pg/"
"n,x10/9,s8,x11/4,pd/a,x6/10,pc/l,x4/15,s13,x11/5,s2,x15/14,s11,x2/13,pi/b,s3,x8/5,pd/"
"g,x7/11,pn/c,x5/4,s2,x6/10,po/b,x4/15,pi/d,x11/9,ph/l,x14/0,pa/"
"m,x3/11,s11,x0/8,s10,x2/1,s11,x11/6,s13,x14/1,s7,x10/15,pj/f,s6,x1/5,s11,x10/3,pa/"
"n,s5,x15/7,s2,x9/5,pi/m,s14,x12/7,pa/b,s4,x2/14,pf/n,s13,x12/15,s3,x6/13,pk/"
"j,s15,x2/12,s7,x13/11,pl/b,x3/12,s7,x7/0,po/k,x9/2,pb/g,x8/11,s9,x14/0,s14,ph/k,x8/6,pi/"
"l,x7/4,pm/g,x11/14,ph/f,x6/9,po/d,x10/2,s11,x14/12,pi/p,x15/8,s5,x0/4,s1,x2/3,pj/o,x9/14,pm/"
"p,x5/11,pg/i,x7/9,pp/a,x10/8,s8,x3/12,pm/l,x11/7,s12,pn/"
"o,x8/3,s2,x7/13,s10,x4/2,s13,x8/7,s4,x10/6,s15,x8/3,s12,x6/1,pj/p,x4/11,s6,pf/n,x0/14,pd/"
"l,x4/2,pk/c,s1,x1/6,pa/j,x5/15,pf/d,s5,x12/13,s10,x0/10,s11,pm/k,x6/13,s5,x4/5,pf/"
"p,x6/7,s3,x9/2,s13,x6/0,s10,x7/9,pj/e,x5/6,s8,x3/0,s7,x9/1,s12,x5/4,pf/c,x9/10,s2,x5/11,pl/"
"m,x14/7,s4,x3/5,pc/i,x4/7,po/f,x13/14,pc/h,x0/5,s11,pn/a,x4/1,s13,x6/11,s15,pf/i,s11,x14/3,pj"
"/o,x10/9,s5,x11/2,s3,x5/6,s13,x7/2,s1,x4/12,ph/k,s2,x11/8,s6,x7/15,s5,pa/c,x5/9,s3,x8/1,pe/"
"k,x3/13,ph/n,x6/15,s1,x9/8,s5,x2/10,po/f,x4/9,s10,x11/5,pe/c,x9/0,s13,pb/p,x14/5,pl/"
"j,x4/6,s8,x2/0,s6,x14/12,po/p,x11/1,pa/d,x12/6,s12,x3/13,s9,x4/7,pp/"
"m,x12/11,s13,x5/14,s10,x10/0,pk/d,x11/13,s11,x7/1,pj/b,x4/"
"0,s13,x3/14,s8,x9/8,s4,x13/4,s8,x9/7,s13,x2/10,pa/n,x13/3,s7,x2/14,s5,x3/0,pd/"
"b,x1/9,s3,x7/15,s6,x9/8,s11,x15/5,s13,x13/6,pj/i,x4/8,pe/"
"p,x0/14,s1,x9/5,s3,x2/6,s2,x7/4,s1,x6/8,pa/j,x13/2,s14,x6/12,pl/i,x3/1,pp/"
"c,x15/9,s14,x4/5,s12,x12/8,pn/d,x6/1,pi/e,x5/13,s3,x12/11,s9,x5/0,pb/"
"j,x15/8,s9,x10/13,s15,x1/4,s13,x6/14,pp/k,x0/15,s8,x10/7,pa/c,x14/5,s7,pg/n,x2/12,pc/"
"l,x0/3,pj/m,x13/4,s4,x12/6,pp/o,x7/11,s11,x15/5,s7,x14/10,pl/"
"c,x3/6,s2,x0/15,s4,x8/3,s9,x2/10,pn/k,x14/11,pf/p,x13/7,s14,x6/14,ph/n,x3/0,pa/"
"l,x4/12,s1,x8/13,s1,pk/h,x1/6,s15,x9/3,s5,x4/14,s2,x15/10,s2,x13/1,s5,x10/12,pl/"
"d,x11/15,s15,pp/c,x6/12,s11,po/i,x14/7,s9,x15/13,pf/d,x9/1,pb/h,x11/10,s7,x5/1,s10,x4/10,pj/"
"a,x0/3,s7,x10/15,s8,x0/1,s15,x3/14,pn/d,x6/11,pl/b,x0/12,pd/i,x14/5,s5,x10/"
"0,s4,x5/3,s6,x14/9,s1,x0/10,pb/j,x6/1,s1,x8/4,s12,x6/10,s13,x13/14,ph/"
"i,s11,x5/3,s14,x15/10,s7,x4/6,pm/j,x14/7,s10,x0/1,pc/k,x4/5,pp/m,x2/15,ph/k,x12/9,pg/"
"o,x4/13,s5,x5/8,s11,x6/11,s10,x9/8,pk/f,x11/14,s5,x4/0,s13,x3/6,s2,x5/12,s7,x9/13,s5,x0/10,pd"
"/m,x7/2,s11,x6/4,s9,x11/8,pc/g,x9/4,s6,x14/12,s8,x10/3,pn/o,x14/11,pd/j,x8/0,ph/"
"b,x6/3,s5,x13/8,pf/j,x14/1,pc/a,x8/9,pk/j,x14/4,s4,x7/5,pf/"
"a,x11/10,s7,x12/7,s4,x3/11,s11,x13/12,s10,x0/3,pi/n,x6/10,s15,pl/a,x14/12,ph/"
"e,x8/11,s6,x3/4,s11,x15/9,s10,x6/11,pd/o,x10/5,pl/f,x15/3,s7,x9/0,pb/j,x2/10,pc/"
"n,x0/12,s7,x15/6,s10,x0/11,s8,x8/7,s13,x15/1,s2,x13/0,s12,x8/7,pe/b,x12/14,pa/f,x10/9,pe/"
"o,x14/6,s4,x8/11,pj/b,x15/5,s10,x1/8,s5,x13/10,pd/p,x12/2,po/h,x3/13,pj/c,s4,x0/9,s3,x14/4,pa"
"/i,x7/5,pf/n,s4,x0/15,po/d,x14/12,s2,x3/1,pg/i,x11/12,s1,x7/2,pp/l,x10/"
"0,s1,x5/2,s7,x14/13,s10,x10/12,s5,x11/5,pk/g,s9,x8/0,po/n,x7/11,pj/"
"m,x4/14,s9,x15/8,s4,x0/10,pn/b,x5/11,pe/o,s8,x0/3,s3,x4/12,s6,x8/2,s11,x0/14,pf/"
"p,s12,x7/12,s10,x14/1,s2,x6/4,pm/k,x8/9,pj/l,x2/"
"0,s5,x12/7,s8,x5/14,s15,x8/15,s10,x13/11,s2,x15/5,pg/k,x2/8,pi/c,s8,x7/0,pk/g,x9/11,pc/"
"l,x12/7,s1,x4/10,pi/b,x13/9,s6,x15/4,s14,x12/7,s2,x8/10,s9,x14/5,s15,x9/8,s13,x14/"
"0,s1,x5/11,s6,x13/0,pa/p,x2/3,s12,x7/11,s4,x10/8,s6,x9/7,s6,pj/b,x11/4,s11,x7/8,s3,x10/"
"0,s3,x7/15,s13,x8/10,s15,x11/0,pk/a,x15/14,s9,pb/e,x2/8,pd/p,x9/0,s14,x8/6,pb/"
"l,s13,x0/5,s1,x2/12,s14,x1/13,s9,x10/2,pa/e,x14/7,pd/l,x5/6,pc/m,x12/2,pe/"
"k,s3,x9/1,s12,x15/11,s6,x0/12,s6,x9/10,ph/g,s2,x5/3,pf/e,s4,x7/11,s2,x8/0,pa/"
"k,s14,x9/3,s14,x13/7,pl/f,x14/4,s12,x3/1,s10,x8/6,s2,x7/0,pe/d,x12/3,s14,x0/7,pi/"
"o,x4/3,s1,x8/5,pg/l,s11,x7/9,s1,x2/13,s1,x15/0,pp/b,x7/9,s15,x2/3,s2,pk/c,x10/1,pd/j,x0/8,pf/"
"o,x6/12,pc/e,x1/0,s11,x4/9,s3,pn/a,x10/11,ph/c,x13/12,pm/l,x8/2,s5,x4/0,s6,x9/11,s4,x15/13,pg"
"/c,x12/10,pl/o,x3/13,s1,x0/9,s13,x1/15,pn/e,s10,x4/6,pp/g,x15/10,pn/k,x2/8,pj/"
"i,x4/13,s12,x3/1,pp/o,x2/6,pi/g,x4/3,s4,x6/15,pm/k,s7,x0/9,pj/p,x3/5,pn/o,x10/2,pp/"
"l,x13/15,pf/g,x0/14,s3,x2/15,pa/j,s4,x14/8,s13,x9/15,s7,x10/6,pi/c,x5/9,s11,x4/"
"0,s3,x13/5,s3,x7/14,s1,pk/o,s10,x8/5,pe/i,x7/14,pm/c,x8/2,po/k,x6/9,s1,x13/7,pa/"
"b,x8/6,s7,x3/9,s11,x11/4,s7,x5/12,s9,x11/3,pg/d,x8/15,pn/j,x4/1,pa/o,x7/13,s5,pf/"
"h,x2/3,s12,x14/10,pc/e,x5/2,s14,x0/7,s7,x4/8,s11,x12/15,s7,x6/14,s15,x12/4,pf/n,x14/8,po/"
"k,s13,x2/4,s7,x1/5,pc/e,x15/4,s14,x1/14,pa/o,x3/7,s1,pk/n,x2/0,s7,x11/4,pe/"
"o,x2/10,s1,x4/13,pk/h,x12/14,pl/d,x13/6,s13,x10/4,s5,x12/5,pn/m,x1/4,s10,x14/3,pd/"
"i,x0/12,s14,x8/15,s9,x9/6,s1,x7/15,s13,x1/4,pp/c,x14/9,pd/b,s8,x1/2,pn/"
"e,x6/10,s3,x7/9,s1,x4/13,s8,pk/h,x9/8,pa/p,x14/7,s4,x3/12,s13,pd/n,x15/4,pi/"
"a,x7/8,s11,x12/3,s3,x5/10,s5,x13/11,s12,x14/10,s2,x6/15,s2,x8/14,pd/j,x4/13,po/"
"g,x15/8,s12,x11/1,s10,x9/12,pi/n,x10/11,s7,x8/2,s7,x11/13,pc/l,x3/7,s11,x11/15,s4,pb/"
"p,x4/14,s9,x15/3,s5,x13/14,s2,x10/4,s14,x12/13,pf/m,x15/5,pg/c,s3,x13/9,po/n,s2,x11/14,s8,x2/"
"0,s12,x12/9,s14,x3/10,s4,x8/9,ph/k,x7/1,pn/d,x11/14,s1,x1/5,s8,x9/2,s13,x4/14,po/h,s15,x15/"
"0,s7,x14/8,pp/f,x15/7,s7,pc/d,x6/11,s3,x3/5,pk/j,x9/4,s14,x3/1,s9,x0/11,s9,x4/5,s9,x9/2,pl/"
"e,x3/1,s6,x4/0,s8,x7/11,s1,x3/2,s3,pg/m,x10/6,pl/h,x12/8,po/f,x14/6,s7,pn/i,x0/10,pk/"
"m,x11/15,s8,x5/13,s10,x14/9,s1,x5/7,s10,x9/2,pp/j,s9,x0/7,pf/i,s14,x4/8,s15,x7/6,s10,x15/1,pd"
"/m,x2/3,pl/a,x0/9,pj/c,x4/5,pn/b,x8/0,s8,x14/15,ph/i,x11/2,s7,x14/6,pp/g,x2/3,pj/"
"d,x9/10,s9,x8/12,s3,x14/9,pi/h,x6/0,s11,pe/c,x5/4,s8,x12/3,po/m,x15/13,pe/p,x14/9,s8,x7/2,po/"
"g,x8/14,pd/j,x11/6,s14,x15/8,pe/i,x12/1,s2,x9/3,pd/k,x8/6,pa/i,x12/9,s10,x4/7,pe/"
"h,x3/11,s3,x7/8,s14,x15/3,s12,x13/11,s2,x3/15,s12,x7/11,s15,x12/5,s5,x9/4,s9,x5/14,pm/"
"o,x2/11,s15,x10/7,s2,x13/4,s15,x5/10,pd/k,x4/6,s6,x13/3,pj/f,x8/12,s1,x11/9,s7,x13/0,pa/"
"i,x8/2,pd/m,x0/10,ph/l,x14/6,pg/j,x0/3,s11,x9/15,s14,x8/4,s5,x12/1,s7,x13/8,s8,x9/5,pi/"
"l,x4/1,pm/n,s9,pi/e,x11/5,s1,x15/6,s8,x2/12,pd/g,x1/15,pp/l,x5/2,s15,pd/"
"i,x11/1,s10,x15/6,s10,x14/12,s4,x7/10,s12,x9/3,s6,x11/13,s13,x15/0,ph/a,s8,x12/11,pf/"
"e,x4/10,s7,x6/7,pc/i,x2/1,s7,x4/5,pf/b,x1/3,s15,x15/7,s11,pc/h,x10/13,pj/g,x14/11,pl/"
"f,x8/10,ph/o,x9/15,s3,x10/3,pa/e,x14/4,s5,x3/13,s8,x4/15,s4,x9/2,pc/m,x5/1,s14,x7/4,po/"
"g,x15/6,s4,x14/5,pb/m,x15/6,pg/a,s11,x10/11,pp/j,x1/12,s3,x10/14,pi/h,s15,x2/12,s12,x11/7,pp/"
"k,x5/1,pc/b,x4/8,s5,x3/14,pf/k,s12,x13/15,pp/d,x3/11,s10,pf/a,x1/15,pc/h,s14,x3/9,s3,x12/5,pp"
"/e,x13/0,pc/j,x4/7,s8,x14/11,s10,pp/n,x1/10,s10,x7/9,pg/j,x12/8,s1,x2/4,pe/c,x6/3,s6,x14/5,pi"
"/p,x3/13,ph/d,x12/0,s3,x15/4,pg/p,x3/12,s8,x2/9,s10,x14/12,s6,x15/9,pc/k,x3/6,s10,ph/"
"a,x5/12,s11,x1/8,s6,x11/3,s5,x2/13,s5,pk/l,s6,x3/1,pn/i,x4/8,pj/g,x14/2,s15,x13/7,pb/"
"k,x15/14,s2,x5/10,s13,x9/12,s10,x5/15,po/m,s12,x0/6,pi/"
"n,x2/10,s15,x1/14,s14,x6/5,s1,x2/8,s7,x6/12,pb/l,s14,x2/13,pp/g,x10/14,pi/e,x0/15,pl/"
"b,x5/13,s15,x7/4,pe/n,x0/13,pb/l,s3,x11/14,s1,x6/5,s13,x4/15,pp/m,x6/9,ph/l,s15,pk/"
"o,x12/14,pj/i,x15/3,pl/h,s3,x0/14,pf/m,x10/15,pd/e,x14/6,pb/h,x2/7,s4,x8/5,s6,x15/7,pl/"
"g,x2/8,pn/k,s15,x13/10,s6,x5/4,s10,x14/3,pi/o,x2/5,s11,x14/13,s2,x3/5,s14,pf/h,x1/13,pb/"
"k,x12/7,ph/g,s3,x11/9,s3,x10/12,pb/e,x1/2,s3,x12/15,ph/n,x6/14,pm/a,x10/12,s12,x4/5,pl/"
"d,x0/8,s13,x11/10,s15,po/g,x0/15,pd/m,x13/7,s5,x1/9,s10,x2/11,pb/c,x4/12,pf/i,x15/3,pb/"
"l,s15,x6/14,s8,x10/15,s6,x9/8,s4,x0/13,pj/g,x14/12,pp/c,x0/2,s2,x7/10,s10,x9/0,pl/"
"g,x11/12,s10,x5/1,s12,x12/15,pc/i,x6/7,pg/b,x12/4,pp/f,x5/8,s7,x9/4,pl/"
"b,x1/13,s14,x15/14,s10,pm/g,x11/5,s12,x15/4,s10,pa/l,x1/12,ph/"
"f,x10/8,s2,x0/1,s2,x12/15,s3,x14/0,pj/i,x1/7,s12,x6/8,po/g,s4,x15/0,s12,x6/8,s7,x14/"
"0,s11,x1/7,pf/j,x13/15,pl/n,x1/10,s3,x14/4,pi/m,x13/9,pa/l,x10/8,pd/k,x3/4,pn/m,x5/2,pa/"
"b,x7/13,ph/i,s7,x10/4,pl/c,x3/9,pg/o,x7/12,s4,x9/1,pa/l,x6/10,s6,x14/3,s12,x0/8,pj/"
"g,x11/2,s12,x7/6,s8,x12/1,s6,x8/2,s6,x13/3,pd/o,x11/5,pj/l,x10/15,s8,x11/6,s3,x10/1,pd/k,x13"
"/0,pg/f,x11/3,s15,x15/8,s3,x7/4,pp/d,x10/3,pm/i,x15/12,s9,x2/14,ph/l,s13,x6/1,pi/"
"j,x2/11,s2,x8/6,s3,x0/11,ph/a,x5/2,s15,x10/7,s3,x4/15,pg/n,s1,x6/1,s8,x7/0,s10,x2/8,pc/"
"l,x15/12,s1,x5/3,s13,x12/11,pd/a,x4/9,ph/g,x0/13,s10,x6/4,s6,x14/9,pp/m,s1,x13/0,ph/"
"j,x4/15,pa/f,x8/5,s6,x7/6,s3,x13/11,ph/k,x0/10,pa/f,x4/13,pi/o,x8/11,s14,x12/5,pn/"
"h,s14,x14/9,s10,x0/10,s7,x8/2,s10,x5/1,s15,pe/a,x4/0,s12,x14/15,pi/f,x1/4,pk/"
"p,x15/13,s6,x0/10,s15,x5/13,s1,x9/12,pm/g,s8,x14/5,s13,x3/15,pc/a,x6/12,s7,x15/11,po/"
"e,x12/13,pk/h,s12,x9/0,pp/o,x14/2,s1,x0/5,ph/k,x2/12,pp/c,s7,x6/3,pa/"
"l,x9/5,s12,x10/2,s7,x13/11,s15,pi/j,x1/12,s10,x15/8,s7,x5/7,pp/"
"h,x13/14,s11,x9/3,s1,x12/15,s2,x9/11,s9,po/n,x14/10,s5,x5/4,s10,x10/13,ph/"
"j,s12,x7/1,s12,x5/15,pe/p,x1/11,s11,x10/8,s13,po/i,x11/3,s7,x7/8,pg/d,x1/13,s2,x11/7,pm/"
"e,x3/5,s3,x13/0,pk/b,x6/4,s13,x15/10,s15,x4/12,s3,pf/p,x8/2,s6,x13/10,s15,x14/"
"0,s12,x6/15,s15,x10/2,pn/j,x8/15,pi/d,x11/13,pn/b,x10/6,s14,x8/2,pg/"
"e,x9/7,s6,x15/8,s13,x13/11,pb/k,x8/10,s10,x4/3,s9,x1/7,s8,x13/5,s11,x9/15,pc/g,x13/8,s4,pl/"
"a,s14,x3/7,pp/c,x0/1,s7,x11/12,s8,x7/10,s4,x4/9,pj/f,x3/13,s12,x12/15,s14,pm/"
"e,x2/3,s4,x8/13,s12,x1/9,pa/g,x5/10,pm/f,x1/8,s3,x10/4,s12,x1/"
"0,s14,x4/3,s13,x12/11,s14,x7/5,s2,x2/8,s3,x9/14,s15,x7/1,pj/c,x0/13,pk/"
"e,x15/11,s2,x0/7,s8,x2/14,po/j,s8,x12/15,ph/d,x9/8,s7,x0/11,pn/l,x2/12,pa/"
"g,x11/3,s2,x13/5,s4,x10/14,s8,pk/l,x8/0,s3,x5/1,pm/"
"b,x0/12,s11,x2/8,s8,x6/10,s3,x3/9,s11,x0/7,s8,x10/5,s7,x12/4,s14,x10/15,s15,x11/12,pf/"
"g,s2,x10/8,s4,pp/e,s13,x6/13,s4,x15/1,s14,x4/14,s10,x8/13,pg/i,x1/7,pp/e,x0/10,s6,x5/3,pk/"
"g,x0/8,s15,x14/15,pc/o,x4/9,pg/m,x6/5,s5,pc/h,x3/14,s15,x13/12,pa/i,x10/14,pe/d,s7,x5/15,ph/"
"c,x2/3,pl/p,x15/11,pj/a,x12/9,s12,x11/3,s12,x12/9,s8,x14/2,s1,x9/11,s1,x12/0,s2,x7/5,s8,pg/"
"c,x2/12,s5,x13/8,pe/h,x0/9,pd/n,x10/2,s13,x15/14,po/e,x13/0,s14,x3/7,pf/c,x11/1,pb/"
"n,s9,x6/2,s7,x0/12,pm/i,x9/10,s13,pg/c,x14/15,pl/f,x8/11,pg/b,x5/6,s11,x4/"
"0,s8,x15/13,s7,x14/11,pp/i,x6/5,pe/k,s5,x4/9,s7,pp/d,x3/10,pb/"
"g,x6/8,s1,x13/11,s10,x1/15,s3,x11/7,pa/p,x2/12,s10,x4/5,pe/f,x10/9,pa/"
"d,s9,x5/12,s9,x15/1,s5,x7/4,s6,pj/b,x11/14,s3,x0/12,pd/h,x7/9,pg/p,x14/12,s10,x13/11,s7,x9/"
"0,pk/l,x11/5,pg/p,x14/7,s14,x6/3,pa/c,x0/7,s14,x11/5,s12,x13/12,pg/"
"m,x4/10,s2,x5/12,s9,x4/3,s6,x1/8,s13,x10/7,ph/e,x0/6,pn/k,s7,x9/8,ph/j,x7/1,s14,x2/10,pk/"
"f,x13/14,s10,x1/6,s10,x14/8,pb/p,x5/3,s2,x7/0,s5,x11/12,s5,x8/4,ph/d,x3/10,s12,pn/"
"f,s12,x6/1,pc/g,x10/0,s13,x5/15,s13,x10/13,s2,x6/0,s7,x3/1,s12,po/m,x5/15,pg/b,x12/4,pn/"
"i,x11/14,s1,x15/9,s12,x12/11,s14,x5/14,s14,x1/0,s11,x13/11,s11,x3/7,s11,x2/10,s15,x12/3,pl/"
"p,x13/7,po/m,x11/6,pd/k,x9/5,s3,pg/j,x11/15,s6,x7/8,ph/a,x6/3,s11,x14/1,s5,pi/e,x11/13,pf/"
"d,x15/0,s10,pa/m,x1/2,pg/d,x8/4,s1,x2/6,pi/b,x10/1,po/j,x8/15,pp/"
"i,x1/5,s12,x13/14,s3,x6/10,s9,x2/9,s13,pj/e,s8,x10/15,s9,x9/11,s10,x12/4,pi/c,x3/0,po/"
"a,x5/1,s8,x12/15,pg/f,s13,x9/6,s9,x12/10,s2,x4/0,pb/p,x15/13,s5,x3/10,s6,x14/11,s8,x6/10,pa/"
"g,x9/4,s14,x15/2,s13,ph/k,x5/3,pj/f,x13/7,pg/"
"m,x1/11,s9,x3/7,s7,x1/6,s10,x8/7,s11,x10/2,s14,x12/7,s2,x5/0,s2,x14/10,pa/o,x13/5,pn/"
"f,x10/6,pc/d,x12/7,s2,x1/10,s10,x4/6,s10,x1/2,s6,x11/7,s12,x2/1,s15,x13/8,s15,x1/10,s9,x9/4,"
"s2,x5/7,s1,x8/6,pe/i,x11/13,s11,x8/15,pa/j,x12/7,s13,x15/5,s11,x1/0,s12,x10/2,s7,x1/4,pk/"
"f,x5/2,s12,x12/7,s13,x14/2,pb/p,x13/1,s1,pk/f,s14,pm/a,x4/15,s8,x0/2,pj/n,x5/1,po/"
"i,s3,x15/6,pj/h,x11/12,s11,x14/4,s15,x8/1,s13,x9/5,s8,pb/c,x3/15,pk/j,x12/10,pg/o,x13/3,pa/"
"l,x15/11,pg/k,x0/6,pe/c,x11/7,pf/m,x5/14,s12,x1/10,s13,x11/8,s4,x4/3,s4,x14/6,pg/"
"l,x0/5,s14,x13/2,po/e,x6/9,pn/c,x13/0,pe/g,x14/1,s6,x3/9,s14,pl/p,x0/8,pk/j,s4,x12/11,pf/"
"c,x4/10,s8,x2/5,pg/o,x13/15,s5,x12/0,pj/m,x5/14,s13,x6/11,s8,x13/4,pl/b,x7/3,s9,x5/12,s9,pe/"
"g,x4/8,s11,x13/5,s11,x12/7,pa/h,x3/1,po/n,x4/2,pp/d,x0/15,s5,x10/4,pk/b,x7/12,s14,x9/0,pd/"
"l,x13/14,s12,x10/1,pn/b,x13/2,pa/i,s13,x0/12,s6,x10/9,ph/m,x0/3,s9,x11/9,s1,x15/14,s7,pf/"
"i,x11/0,s7,x4/1,pe/h,x5/10,pj/n,x14/6,pp/"
"l,x4/7,s11,x13/12,s13,x9/11,s8,x8/4,s11,x2/9,s15,x0/4,pa/d,x15/6,s9,x9/10,pm/"
"l,x4/14,s9,x15/10,s2,x11/4,s8,x0/12,s10,x13/10,s8,x7/4,s10,x9/15,s4,x8/7,s13,x1/4,s10,x2/8,p"
"e/j,x9/10,s11,x5/15,s9,x1/12,s1,x0/2,pb/k,x10/9,s6,x11/7,pf/j,s7,x4/13,ph/"
"o,x9/10,s12,x2/5,pb/j,x13/11,pe/m,x15/2,pn/l,x7/8,pi/p,x2/6,pj/m,s9,pk/i,x0/4,pd/a,x11/13,pf"
"/n,x10/2,pp/k,s8,pd/l,x15/7,s12,x2/3,pc/m,x4/13,s9,x2/1,pk/o,s4,x7/4,pm/n,s8,pb/"
"c,x12/14,s12,x7/11,s6,x12/10,s6,x0/7,pj/k,x10/13,pl/g,x6/11,s8,pk/p,x7/"
"0,s9,x4/8,s3,x10/11,po/b,x7/4,pg/c,x1/12,po/n,s6,x10/5,pp/b,s5,x13/14,po/"
"c,x5/15,s10,x3/10,s11,pg/d,x2/5,ph/i,x15/13,s1,x2/9,s5,x6/8,s1,x15/7,s10,x8/9,s15,x12/4,po/"
"f,x8/7,pd/k,x14/1,pe/b,x5/0,s11,pk/j,x3/7,s12,x15/2,pg/"
"m,x3/1,s11,x0/13,s6,x9/7,s10,x3/8,s12,x1/13,pf/d,x4/14,po/p,x11/12,pm/l,x14/7,s12,x10/2,pg/"
"b,x14/5,pp/m,x1/13,s3,x12/10,pb/h,x3/8,pj/"
"a,x15/7,s6,x14/6,s10,x9/2,s3,x8/12,s10,x14/2,s13,x4/1,s2,x5/15,pd/i,x13/11,pj/a,s14,pf/"
"e,x15/9,s5,x13/5,s10,x4/3,s1,x9/12,pb/p,x6/2,s13,x7/14,pj/g,s15,x13/8,s11,x0/3,s7,x9/2,ph/"
"m,x10/12,s2,x3/11,s15,x1/14,s11,x13/5,s3,x0/7,pg/o,x10/4,s13,ph/i,s5,x2/12,s13,x4/8,pd/"
"f,x2/3,s3,x8/14,pc/g,x13/12,pl/b,x1/5,s11,x10/7,s9,x11/8,pa/j,x6/10,s5,x2/9,s12,x8/15,pe/"
"d,x14/1,s14,x6/3,s14,x9/5,s6,x8/15,pa/o,x12/0,s9,x13/5,s2,x11/8,pp/b,x14/13,pg/"
"h,s4,x12/2,s1,x10/9,pd/c,x4/13,s1,x5/1,s7,x3/13,s1,x14/15,s4,x4/6,s1,x10/9,pj/"
"l,x11/14,s15,x15/0,s4,x5/12,pf/g,x7/14,s9,x3/4,pe/i,x2/9,pg/f,x10/7,s8,x14/9,s12,pd/"
"j,x0/13,s3,x15/14,s14,x8/10,s7,x7/6,s14,x13/10,s1,x1/15,s11,x13/3,s15,x14/6,s14,x1/2,s14,pp/"
"f,x10/5,ph/d,s2,x2/14,pj/m,x15/13,po/c,s4,x4/2,pd/h,x9/8,s5,x7/5,s10,x0/2,pm/"
"p,s10,x6/14,s8,x12/0,po/k,x10/9,pd/j,x4/14,pb/f,x0/13,pm/"
"i,x6/10,s10,x12/7,s10,x6/1,s2,x5/2,pf/c,x12/11,pj/d,x0/14,ph/m,x9/13,pk/"
"j,x1/5,s12,x4/3,s10,x0/13,pe/d,x11/9,s9,x0/6,s12,x9/3,ph/n,x11/15,pj/o,x2/4,s3,pf/"
"h,x9/8,s3,x12/11,s9,x15/1,pg/d,s6,x6/2,s12,x3/8,s4,x7/6,s3,pm/f,x13/2,s3,x11/12,s12,x2/9,pl/"
"i,x4/15,s7,x13/10,s8,x8/14,s11,x12/2,s1,x0/13,s9,x3/1,s5,x4/14,pd/k,x7/10,s15,x8/"
"0,s5,x14/13,pj/"
"o,x9/2,s13,x8/11,s10,x6/13,s11,x7/15,s6,x1/12,s12,x13/10,s4,x6/1,s1,x15/3,s9,pl/g,x11/0,pm/"
"a,x2/15,s14,x1/0,pf/k,s10,x10/12,pp/c,s15,x1/11,pf/g,x8/5,s2,x0/4,pi/n,x2/3,s9,x6/0,pl/"
"j,x12/9,s10,pc/p,x7/2,pd/f,x9/11,pc/o,x13/15,pm/p,x12/2,s7,x11/6,s8,pk/"
"i,x14/5,s5,x1/4,s11,x13/5,s5,x12/4,pb/g,x0/15,pl/c,x3/9,po/e,s10,x5/1,s8,x10/0,pi/"
"g,x9/1,s9,x10/11,pf/e,x5/14,s4,x2/1,s8,x10/12,s12,x3/11,s7,x14/1,po/p,x7/15,s6,x13/11,pd/"
"a,x12/7,s7,pl/b,x1/6,s1,x7/5,pd/h,x15/6,s9,x14/5,pa/n,x13/6,s12,x0/1,pj/p,x10/13,pk/"
"a,x0/1,s6,x6/15,s9,x5/8,s10,pn/l,s6,x15/6,s9,x2/9,pd/k,x12/4,s6,x3/13,pm/"
"c,x15/6,s9,x5/10,s1,x13/12,s1,x3/15,s15,x7/12,s3,x13/4,s1,x1/10,s15,x7/4,pe/"
"l,s12,x5/10,s15,x1/3,s6,x8/7,pc/m,x6/0,s14,x14/11,pp/d,x4/12,pk/e,s3,ph/g,x10/15,s13,x12/"
"0,s2,x10/2,s6,pd/i,x14/7,pm/a,x13/12,s7,pg/o,s14,x3/10,pd/k,x8/11,s12,x9/6,s15,x7/"
"0,s6,x2/14,s14,x11/13,pm/i,x12/15,s1,x9/6,s6,pj/d,x4/13,pk/l,x14/0,pp/n,x8/6,po/"
"g,x5/2,s11,x13/7,s15,x12/1,s11,x8/6,s9,x10/9,s13,pn/l,x14/1,s9,x6/15,s15,x0/10,s14,x11/7,pm/"
"e,x14/4,s15,x2/11,s9,x5/3,s1,x0/1,pf/j,x11/14,s8,x6/5,s8,x12/8,pk/"
"c,x5/15,s4,x3/13,s13,x11/9,pm/d,s10,x5/14,pg/c,x9/4,s12,x2/13,pe/k,x3/9,s14,x7/13,ph/"
"g,x9/2,s2,x0/4,s10,x9/2,pf/p,x11/15,s12,x5/10,s8,x7/12,s8,x14/6,s11,x2/4,pg/i,x11/9,pb/"
"p,s13,x3/1,s6,pn/g,x4/10,pf/o,x0/5,pg/m,x7/10,s6,x14/2,pf/l,x13/3,pi/"
"c,x14/4,s4,x10/7,s12,x3/4,pg/f,x9/7,s13,x8/13,s2,x2/14,s8,x10/1,s5,x4/9,s15,x13/3,pm/"
"p,x5/14,s6,x6/10,s13,x2/5,s4,pk/o,x13/10,pn/a,x14/1,ph/c,x9/8,s4,x4/13,s8,pn/"
"m,x6/14,s3,x8/1,s11,x13/5,s9,pc/j,x14/11,s9,x0/7,pn/l,x11/13,s15,x9/1,s6,x0/12,pc/j,x8/11,pe"
"/i,x4/7,s4,x12/13,pn/j,x2/1,po/d,x0/15,s5,x7/6,s1,x14/9,pm/"
"b,s10,x12/6,s3,x8/9,s8,x11/14,s8,x6/15,s13,x5/11,s13,x13/9,pp/f,x0/1,pe/a,s10,x15/12,po/"
"m,s15,x9/4,pi/p,s9,x11/6,s6,x13/12,s1,x9/6,pl/j,x4/5,pb/"
"f,x12/3,s6,x8/13,s5,x6/10,s7,x2/15,pa/d,x3/5,pk/n,s11,x4/12,s4,x1/15,pb/f,x6/2,ph/"
"c,x1/8,s8,x5/3,pi/j,x8/1,pf/o,x4/5,s12,x6/9,pk/n,x3/13,s10,x10/0,s10,pc/"
"g,x13/3,s6,x0/2,s7,x3/6,pk/j,x1/2,s6,pc/n,x12/5,s13,x3/0,s9,pb/h,x8/11,pl/d,x2/14,pf/"
"i,x12/5,pn/e,s1,x7/9,s5,x4/10,s3,x15/7,ph/f,x6/11,pn/d,x13/8,pl/"
"a,s5,x10/9,s12,x11/4,s12,x3/7,pj/k,x2/9,s12,x6/12,pm/p,x2/5,pi/g,x6/4,pd/a,x5/1,pi/"
"l,x14/15,s11,x12/7,s7,pn/j,x2/8,s4,x1/12,s11,po/k,s3,x11/4,pn/"
"i,x7/10,s13,x12/8,s10,x1/9,s13,x6/10,pa/j,x0/9,pp/i,x7/4,s4,pe/a,x8/6,pn/g,s4,x11/4,pk/"
"a,x5/14,s7,x9/6,ph/d,s7,pk/i,x10/1,s14,x2/13,s13,x7/0,pb/"
"o,x15/1,s7,x13/10,s14,x12/15,s9,x6/13,ph/k,x4/15,s11,x8/12,s10,pl/d,x14/3,s6,pb/"
"g,x0/13,s13,x6/12,pf/n,x13/8,s4,x15/3,s10,x0/12,s15,x4/2,s8,x8/14,pp/j,x13/1,s6,x7/8,pk/"
"c,x6/1,pn/o,x11/4,s13,x1/10,s14,x13/5,pp/g,x10/11,s8,x12/13,pm/n,x8/10,pc/"
"f,x11/12,s2,x15/8,s6,x11/4,pp/b,x7/2,s13,x1/12,pa/l,x7/11,s10,x0/10,pk/p,x7/4,s15,x3/10,pn/"
"m,x2/1,pj/g,x6/5,po/i,x11/12,s2,pm/"
"d,x13/1,s11,x2/8,s14,x13/10,s2,x7/1,s10,x11/10,s14,x2/4,pc/i,x1/8,s6,x15/11,s5,x6/14,pg/"
"f,x3/11,pb/i,x9/5,s11,x0/4,s10,x2/11,pe/p,x10/5,s4,x4/1,pd/o,x14/7,s9,x5/4,pn/b,x6/0,pa/"
"h,x8/15,s2,x3/0,s8,x5/13,s10,x8/9,s12,x15/0,s7,x11/6,s1,x15/4,pi/l,x14/10,s12,x9/0,s8,pj/"
"o,x14/15,s11,x12/7,pi/a,x11/15,s2,x8/10,po/f,x1/13,s7,x4/12,ph/j,x0/14,pf/k,s5,x1/10,pb/"
"l,x13/11,pk/f,x14/3,pd/g,s9,x12/0,s2,x10/1,s6,ph/p,x0/2,s3,pa/k,x3/11,s3,x5/9,pc/g,x3/1,pa/"
"h,x7/6,pg/p,x4/0,s6,x2/1,s11,x10/12,s3,x15/0,pe/a,x4/5,s8,x7/8,pm/"
"h,x3/14,s9,x5/2,s9,x9/3,s1,x14/13,s15,x9/5,s5,x1/2,s3,x9/11,s8,x4/3,s4,x10/6,s14,x1/5,pj/"
"i,x0/7,s14,x3/6,s1,x5/0,pb/n,x1/4,s8,x10/0,s7,x2/15,s7,x14/8,s13,pe/a,x7/12,pp/"
"i,x8/13,s7,x9/11,pk/g,x8/14,s4,x1/2,s7,x8/5,pf/m,x2/12,s9,x1/15,s3,x9/7,pp/l,x15/14,pb/"
"n,x2/10,pp/m,s1,x3/6,s2,x13/9,s15,x6/11,pa/h,x3/10,po/l,x8/2,pc/g,x7/3,s1,x9/8,pl/"
"f,x0/7,s15,x14/8,s8,x11/5,s3,ph/g,x4/0,s10,x14/8,pp/i,x7/5,s4,x3/10,s13,x15/13,pg/"
"e,x9/4,s2,x11/8,s10,x5/14,s4,x1/15,s10,x14/0,s10,pl/b,x13/15,s13,x2/4,s7,x5/"
"0,s13,x3/11,s1,x5/10,s3,x11/13,s6,x15/1,s14,x4/10,s6,x6/14,s9,x8/1,pn/i,x5/0,pb/o,x13/4,pn/"
"i,x7/15,pg/e,s11,x3/6,s9,x7/5,s13,x9/13,s15,x14/12,s5,x5/3,pn/l,x9/1,s6,x2/10,s4,x1/6,pb/"
"e,x8/12,s2,x11/3,pi/p,x2/1,po/m,x15/11,s2,x1/13,ph/l,x0/8,pg/m,x14/1,s14,x3/4,pn/c,x12/"
"0,s7,x6/11,s8,x14/9,s7,x15/6,pl/j,x1/5,s10,x0/14,s6,x3/8,pg/i,x5/10,pm/"
"o,x0/3,s15,x8/1,s10,x15/11,ph/n,s6,x0/2,s7,x7/3,s15,x1/13,s6,x6/14,pp/k,x15/12,pe/"
"c,x9/2,s10,x10/6,s1,x12/1,s2,x4/14,s3,x9/8,s14,x13/4,s8,x9/8,s12,x3/1,s10,x14/13,s2,x9/4,ph/"
"d,s10,x15/10,po/g,x5/9,ph/k,x13/6,pj/a,x2/1,ph/k,x8/14,pm/g,s8,x3/7,pi/"
"k,s1,x5/11,s10,x8/15,s2,x4/0,pb/a,x3/11,s8,x5/4,s12,pn/h,x11/8,s3,x2/9,s7,x7/1,pc/l,x3/0,pa/"
"g,x11/14,s4,x13/0,pd/n,x11/7,pp/l,s14,x4/2,s1,x7/6,s3,pd/j,s9,x10/12,s7,x11/"
"0,s10,x8/5,s9,x1/9,s1,x6/14,s10,x7/0,pn/g,x9/13,pf/k,x8/14,s12,pa/i,x13/5,pc/d,x6/0,pk/"
"n,x8/9,pm/j,x12/6,s4,x2/8,s7,x10/7,po/a,x3/14,pm/c,x13/8,pa/k,x7/9,s4,x10/13,pp/j,x0/1,po/"
"k,x2/7,pf/h,x14/6,pp/a,x9/2,pl/d,x4/13,pa/m,s8,x0/1,pf/"
"o,x12/6,s1,x4/1,s14,x2/14,s4,x6/15,s12,x0/4,s10,x2/6,s9,x5/15,pj/g,x13/14,pk/"
"c,x4/11,s12,x13/1,pp/f,x0/5,pm/j,x6/9,ph/p,s15,x15/1,pa/g,x5/9,pe/d,x14/6,pk/"
"f,x15/13,s5,x7/5,s3,x4/0,pj/l,x15/13,pp/h,x1/14,pd/o,x3/0,pp/c,x6/7,ph/o,x3/14,s15,x7/0,pf/"
"i,x10/8,ph/p,x9/15,pa/d,x12/2,pc/g,x1/11,pl/n,x12/5,pf/m,x1/6,pa/i,s5,x8/11,pk/"
"p,x5/9,s1,x15/2,s8,x7/12,pa/i,x1/3,s14,x4/5,pm/d,x0/3,pi/a,s15,x4/1,s6,x11/15,s10,x4/9,s6,x8"
"/10,s4,x5/14,s14,x10/4,s1,x6/12,s1,x7/8,s5,x12/14,s7,x8/15,s1,x6/14,s3,x12/11,s13,pg/"
"k,x8/3,s2,x14/12,s12,x3/6,s9,pj/f,s12,x7/11,pd/b,x5/12,pj/i,x1/3,pf/n,x4/9,pl/"
"j,x0/3,s7,x11/15,pp/e,x3/2,s4,x6/11,pc/m,x10/2,pd/f,x11/7,pn/k,x5/14,s6,pj/"
"p,x13/9,s14,x3/4,s6,x7/6,s4,x8/12,s12,x1/14,pl/c,x8/3,s11,x2/0,s15,x7/8,s11,x3/15,po/"
"j,x13/11,s8,x6/15,ph/g,x11/12,s5,x0/4,s11,x11/1,s11,x14/12,s9,x11/3,pd/f,s5,x15/7,pp/"
"n,x0/3,pd/f,x1/11,pe/h,s10,x7/14,pk/l,x9/2,s10,x0/8,s13,x1/13,pe/a,x6/3,po/j,x9/7,ph/k,x10/"
"0,s13,x4/3,s13,x15/14,s14,x0/7,s2,x11/13,pd/o,x3/10,s4,x8/1,pm/h,x9/4,s1,pe/f,x6/0,pn/"
"p,x11/1,s5,x10/6,s4,x15/12,s8,x8/5,s10,x2/14,pj/f,x12/6,pp/e,x11/8,s5,x3/4,pi/"
"k,s12,x11/14,s9,x2/1,s12,x13/10,s6,pe/a,s3,x11/3,s4,x6/12,pc/g,x14/2,s10,x11/8,s6,pb/"
"k,x12/14,s15,x10/5,pa/g,x4/11,s6,x9/14,pk/m,x7/15,pp/f,x10/5,s1,x3/12,pc/j,x4/1,pa/g,x5/7,po"
"/j,x6/11,s4,x15/7,s2,x4/13,s4,x3/9,pb/d,x11/6,pe/l,x12/7,s3,pg/j,s7,x11/4,s13,x8/2,pk/"
"m,s6,x13/4,s13,pp/n,x15/11,pa/i,x12/3,s2,x9/4,pk/d,x1/2,s15,pn/"
"e,x11/8,s7,x7/9,s9,x8/2,s5,x12/7,pg/l,x8/5,s2,x0/11,s3,x15/8,s3,x4/9,pb/n,x12/11,s8,x2/1,pj/"
"h,x6/15,s13,x11/8,s7,x14/1,pb/l,x3/4,po/a,x15/9,s4,x13/7,pl/f,x14/0,pk/"
"b,x2/6,s9,x9/4,s4,x5/10,s11,x11/2,s9,x1/9,s11,x6/12,pi/p,s2,x4/11,pa/"
"m,x13/8,s10,x3/9,s6,x10/8,pp/k,x0/3,s2,x7/6,pc/o,x2/12,s9,x8/15,s9,x4/9,pm/d,s7,x7/"
"0,s2,x5/4,pk/a,x13/10,s7,x15/0,ph/c,s1,x4/8,s7,x3/2,pi/d,x7/1,pg/p,x3/15,s1,x1/10,s1,pc/h,x4"
"/0,s9,x12/14,s9,x1/13,s14,x9/15,pg/p,x1/13,s2,pd/e,x11/3,s10,x8/6,ph/"
"c,x9/4,s3,x3/1,s7,x11/10,pm/g,s4,x3/14,s11,x15/8,s11,x0/5,s14,x14/4,s3,x11/10,po/"
"c,s6,x4/15,pf/d,x1/11,pc/m,x2/14,pl/g,s9,x10/5,s13,x3/4,s5,x2/9,s1,x3/1,pd/i,x15/9,pm/"
"h,x14/12,pk/i,x7/10,pg/l,x13/9,pe/p,x11/15,s10,x2/3,s8,x4/"
"0,s3,x8/1,s12,x0/6,s10,x15/14,s2,x8/11,s14,x14/9,pg/m,x8/11,pi/b,x3/5,s7,x7/13,po/"
"h,x10/8,s12,x7/12,s1,x5/11,s2,x7/15,s6,x5/6,pd/e,x7/0,s6,x8/14,s12,x7/5,s7,pg/j,x4/3,s5,pn/"
"d,x11/12,pk/b,x10/5,pc/j,x6/15,pd/f,x4/5,ph/e,x3/0,pm/"
"i,x5/8,s8,x3/2,s13,x14/4,s5,x10/9,s4,x14/8,pn/p,x9/12,pl/"
"e,x11/13,s13,x3/1,s5,x2/5,s1,x1/9,pm/f,x7/10,s7,x13/0,s1,x7/5,pg/a,s12,x0/3,pc/"
"j,x10/8,s8,x5/15,s11,x8/1,s13,x3/13,s2,x6/1,po/f,x8/5,s10,x2/13,s12,x7/4,pg/"
"l,x11/14,s2,x9/7,pd/i,x13/12,po/b,x3/10,s7,x8/4,s10,x5/3,s15,x8/7,pn/f,s2,x0/12,pk/"
"i,x5/13,ph/a,s9,pl/o,x1/2,s5,x3/7,pp/i,x12/13,s9,pg/d,x7/2,pb/o,x10/6,pk/g,s11,pb/"
"l,x13/9,s8,x11/7,s1,x14/5,pn/a,s4,x2/3,s8,x7/13,pj/e,x3/8,pa/m,x11/6,pp/j,x12/14,pc/"
"n,x1/7,s5,x12/0,ph/m,x13/7,s7,pd/e,x14/8,pm/h,x11/4,pj/e,x2/6,s8,x1/15,pi/"
"p,x5/10,s2,x7/9,s12,x8/6,s10,x15/3,pe/b,s13,x4/1,s9,x0/13,s1,pc/a,x4/10,s6,x7/15,s1,x5/4,pm/"
"d,x10/13,s7,x2/0,s7,x4/7,s2,x14/12,s8,pl/n,x0/5,s15,x10/9,pi/h,x13/3,pa/b,x4/14,s11,x5/11,pk"
"/i,x14/9,pp/o,s4,x1/4,pl/m,x14/15,ph/f,s4,x8/13,pk/o,x9/6,s12,x11/3,pn/a,x8/12,s15,x11/2,pg/"
"b,x4/14,pm/h,x6/8,s8,pj/d,x0/1,s15,x13/14,pp/l,x5/12,pe/i,s5,x6/14,s6,x1/10,s14,x2/8,s7,pn/"
"d,s10,x7/13,pg/i,x8/2,pm/n,s9,x7/15,pg/b,x12/5,pe/h,x9/6,pa/g,x5/4,s14,x9/1,s8,x7/2,pd/"
"p,x13/6,pb/i,x9/14,pg/a,x13/4,s8,x14/2,s8,x9/10,s3,x12/8,s15,x15/9,s15,x2/11,pp/k,x4/9,ph/"
"i,x15/1,pe/j,x9/2,pf/o,s9,x6/10,pj/e,s15,pl/o,x3/8,pd/g,s8,x2/14,pn/e,x0/12,pj/"
"f,x11/1,s11,x9/3,ph/b,x0/4,s8,x13/14,s14,x5/11,s13,pg/l,x12/13,s15,pc/a,x14/7,s6,x2/3,pg/"
"m,x4/11,po/f,x2/5,pp/e,x0/15,s4,x8/1,s5,pb/h,x11/3,s9,x14/2,pa/m,x0/5,s10,x12/8,s6,x6/2,pg/"
"n,x0/4,s10,pk/l,x1/9,pd/o,x13/11,s6,x4/5,s5,x3/9,pk/b,x8/1,s8,x5/6,s6,x7/8,pc/"
"p,s10,x14/10,pg/n,x5/2,s12,x7/6,pk/o,x10/2,s10,x3/5,s2,x4/8,pj/i,x0/9,pg/"
"l,x1/7,s12,x11/14,s11,pc/h,x2/5,s12,x0/13,pi/d,x2/11,pa/b,x5/6,s7,x13/8,s11,x14/5,pp/"
"m,x9/2,s4,x8/1,s12,x15/10,s14,x8/13,s12,x2/0,s6,pl/b,x11/4,s12,x5/6,s15,x14/15,s10,x2/0,pd/"
"n,x15/9,pl/p,x8/14,pg/d,x12/7,s9,pc/l,s6,x3/10,pe/h,x14/7,s8,x9/8,pj/d,x3/2,pi/"
"h,x0/11,s4,x1/12,s11,x14/8,s4,x13/0,pc/m,x2/15,s12,x5/10,pp/i,x14/9,s7,x7/4,s7,x15/0,pm/"
"f,x1/10,pi/l,x14/11,s8,pb/f,x0/6,pp/g,x11/1,s5,x4/2,s6,x3/12,pe/"
"k,x11/1,s7,x0/7,s14,x6/12,s7,x7/4,pd/j,x15/3,s13,x5/8,s4,x3/11,pb/m,x0/14,s10,x4/1,pp/"
"d,x12/15,s5,x13/6,pa/i,x4/2,pb/d,x1/15,s2,x11/3,s6,pc/e,s11,pa/k,x7/14,s4,x1/5,ph/g,x7/2,pe/"
"b,x15/4,s2,x13/5,s8,x9/1,s9,x12/2,s7,x10/8,s6,x15/13,s12,x12/3,po/"
"d,x9/4,s15,x7/10,s11,x5/3,s14,pc/f,x8/6,ph/a,s4,x12/14,s3,x9/0,s12,x3/2,pc/"
"o,x0/12,s8,x3/5,s5,pk/m,x0/13,s12,pl/b,x8/14,s1,pc/p,x11/7,s7,x9/6,po/"
"f,x5/15,s6,x12/4,s13,pc/m,x9/1,s10,x14/5,s2,x3/4,s8,x5/15,s12,x0/7,s1,x13/11,pi/b,x1/12,pf/"
"l,x8/9,s4,x10/7,s10,x5/6,s3,x15/12,s3,x0/10,s8,x6/4,ph/b,x14/8,s9,x15/5,s14,x0/11,pn/"
"p,s11,x9/1,s2,x0/8,s10,x7/12,pk/f,s13,x9/15,pa/d,x7/12,pf/"
"e,x14/1,s7,x4/8,s10,x6/7,s6,x9/12,s11,x13/5,s3,x7/11,s4,x1/13,s10,x8/5,s2,x11/13,s2,x10/15,p"
"h/c,x5/11,pb/j,x1/2,s7,x0/13,pn/f,x1/3,s9,x8/2,s3,x3/13,pj/"
"h,s13,x14/2,s10,x0/7,s5,x5/11,s7,x0/9,s4,x14/11,pp/a,s14,x7/9,pc/"
"b,x0/5,s14,x9/10,s15,x15/12,s12,x13/3,s5,x10/0,pk/h,x1/11,pn/l,x9/3,pm/i,x6/5,s9,x11/7,pe/"
"f,x9/10,s8,x0/15,s4,x11/9,pb/k,x6/7,pg/l,x5/3,pp/f,x1/14,s7,x0/12,s4,x1/14,pi/c,x7/2,ph/"
"b,x11/15,s4,x2/0,pm/n,x11/14,pd/h,x7/8,pg/e,x5/9,pm/d,x0/7,s3,x4/1,s15,x0/15,pl/"
"i,s9,x14/9,s11,x4/8,pc/n,s2,x0/12,pp/d,x5/8,s15,x1/6,s11,pj/h,x4/10,s6,x1/5,pk/o,x6/10,pd/"
"g,x13/15,pb/k,s11,x12/6,s14,x15/5,pi/n,x12/0,pp/e,s15,x15/11,pj/m,s11,x14/7,s8,pb/k,x8/9,pg/"
"h,x10/12,s1,pp/l,x3/15,ph/n,x5/1,s10,pb/i,s14,x12/14,ph/n,x1/7,s14,x5/14,pe/"
"l,x0/12,s4,x8/1,pb/m,x3/0,s14,pd/c,x14/13,pj/g,x2/9,pd/e,x3/13,s7,x7/0,s12,x2/12,s3,pa/"
"h,x5/9,pd/f,x12/11,s9,x8/6,s11,x3/11,pb/a,x0/8,pe/i,x11/5,s1,x8/9,pd/"
"p,x7/3,s5,x13/12,s2,x15/1,s3,x10/12,s13,x6/11,pj/h,s1,x14/9,s2,x13/1,pb/"
"i,x5/8,s11,x9/2,s15,x0/10,pc/n,x2/1,pe/h,x15/4,pg/a,x1/10,pe/d,x0/4,pa/g,x12/10,s10,x3/7,pi/"
"o,s8,x11/14,pd/m,s11,pc/k,x1/8,pd/e,x6/0,s15,x1/3,s1,x2/8,s11,x7/3,pp/g,x12/15,pb/"
"d,x2/13,s10,x0/4,pp/g,x2/6,s13,x7/1,pm/k,x8/5,s10,pn/f,s13,x14/11,pe/"
"c,x2/3,s11,x14/13,s5,x0/7,pj/a,s12,x15/2,pp/h,x5/1,s10,pk/l,s7,x0/13,s14,pg/p,x7/3,pm/"
"l,s12,x15/13,pk/e,x0/10,po/c,s15,x4/7,pn/j,x6/10,s12,x2/3,s11,pl/m,x9/8,s11,x4/0,s6,x3/1,pe/"
"h,s1,x11/6,s2,x10/14,pk/o,x9/1,s13,x10/3,s5,x9/7,s15,x14/0,s4,x1/8,ph/"
"j,x7/10,s14,x0/2,s9,x7/1,pm/g,x13/2,pn/b,x3/6,s7,x15/7,pp/e,x2/5,s10,x8/12,s8,x7/0,ph/"
"g,x12/4,pl/k,x2/1,s7,x14/8,s2,x15/12,pi/n,x6/1,s12,x2/5,s11,x15/14,pj/"
"k,x6/9,s6,x12/8,s11,x11/15,s6,x1/4,s9,x2/8,pl/b,x11/1,s13,po/j,x10/4,s2,x9/3,pc/a,s11,x2/"
"0,s5,x15/5,po/j,x3/14,s3,x4/0,s5,x5/9,s5,pi/k,x15/4,s6,x10/6,s12,x1/14,s15,x12/0,pb/"
"d,x7/5,s9,x15/14,s1,x6/0,pa/g,x7/3,pl/m,x0/9,s12,x1/12,pe/b,x13/6,pn/j,x1/8,s2,x2/14,pm/"
"g,x6/13,s5,x10/8,s15,x11/15,pf/p,x7/1,s11,x11/9,s3,x8/0,pa/o,x3/14,s10,x6/11,pj/"
"g,x4/12,s3,x7/1,s6,x9/15,pk/f,x1/11,s9,x14/5,pa/e,x6/10,pk/o,s13,pg/"
"p,x15/11,s12,x8/10,s3,x2/6,pk/o,x1/0,s13,x6/13,pe/m,x4/5,ph/g,x3/8,pi/f,x14/6,s5,x11/3,pp/"
"d,x12/8,s2,x11/3,pc/a,x0/13,s10,x1/3,s11,x4/10,s4,x12/7,s14,x3/10,s4,pf/d,x0/12,ph/"
"k,s9,x9/10,s6,x14/8,pb/j,x6/7,pl/h,x0/4,s7,x11/10,s7,x12/6,s11,x5/4,po/"
"a,x14/7,s11,x15/4,s3,x0/12,s3,pi/c,x13/15,s2,x5/11,s2,x15/8,s8,x11/3,s15,x15/1,s8,x10/4,pb/"
"o,x8/11,s8,ph/m,x4/13,s4,x8/7,pd/k,s10,pg/l,x1/3,pb/h,x5/0,pf/d,s5,x4/10,pm/"
"n,s3,x8/2,s6,x15/3,pl/i,x10/2,s10,x14/8,pb/m,x9/15,s1,x0/1,pi/d,x6/14,pk/"
"e,x9/11,s14,x15/7,s8,x1/8,pn/h,x10/6,s4,x14/12,pe/b,x0/13,s7,x14/8,s8,x3/7,s2,x1/2,pm/"
"f,x6/7,s1,pa/p,x4/15,s10,x3/12,pl/g,x7/14,pj/k,x15/0,s2,pn/o,x4/7,s15,x1/11,s11,x12/"
"0,s13,x3/7,pf/a,x8/12,po/l,x1/14,s5,x13/7,s15,pg/m,x14/10,s5,x2/8,s12,x0/7,ph/"
"c,x13/5,s6,x6/11,pf/g,x5/10,pe/k,x3/8,s15,x12/11,pd/h,x3/7,s6,x4/0,s14,x2/10,s1,x6/12,pn/"
"o,x10/13,pa/m,x15/14,s9,x9/8,s15,x15/4,pf/c,x8/7,pi/h,x3/9,s15,x12/14,s11,pb/l,x11/15,po/"
"j,x4/8,s1,x5/2,pb/c,x12/7,s6,x3/2,pm/f,x5/8,ph/e,x15/1,s15,x8/6,s13,x3/9,s9,x2/7,s2,pi/"
"k,x8/10,s9,x1/2,pa/m,x6/15,pe/l,x9/10,pi/k,x3/7,s8,x10/11,pc/"
"p,x1/8,s2,x4/3,s8,x1/11,s4,x9/6,pa/i,x0/14,s13,x8/4,s3,x12/1,s12,x14/6,pl/"
"p,x12/15,s8,x4/11,s3,x15/10,pi/o,x7/0,s11,pb/c,s2,x11/12,pf/o,x2/0,s1,x9/7,pb/d,x2/15,pk/"
"l,x10/11,s8,x15/2,s10,x9/11,s3,x6/3,pm/p,x5/9,pk/d,x14/11,pf/g,x4/2,pb/p,x14/1,s11,pm/"
"g,x7/9,pp/k,x3/15,pb/g,x14/11,s4,x7/2,s10,x11/10,pc/o,x3/6,s6,x5/15,s7,x13/11,s12,x10/4,pg/"
"e,x2/9,pl/d,x14/8,pb/g,x3/11,s9,x9/2,s10,x10/12,s15,x5/0,s4,x8/13,s5,x15/6,s15,x13/12,ph/"
"c,x3/0,s6,x12/13,s10,x11/14,pm/f,x9/0,s13,x10/3,s13,x8/2,s4,x0/13,pl/"
"p,s14,x4/2,s5,x3/5,s13,x1/6,s11,x12/10,s7,pk/"
"j,x7/2,s2,x10/3,s10,x14/11,s12,x13/9,s14,x10/11,s12,x14/1,s12,x0/11,pd/p,s12,pb/"
"o,x9/2,s10,x7/13,s8,x14/15,pm/a,x2/7,s5,x5/6,pi/g,s15,x4/13,s15,x15/"
"0,s8,x13/3,s15,x12/10,s12,x0/3,s14,x8/13,pk/a,x9/0,pj/c,s3,x14/3,pn/"
"e,x1/9,s4,x2/3,s6,x4/8,s15,x14/3,pj/i,x5/13,s12,x7/10,pm/p,x4/8,pa/"
"k,x6/2,s6,x5/7,s7,x12/9,s12,x11/14,s4,x3/8,s6,pl/f,s14,x1/2,pk/n,x0/9,s2,x4/8,pm/l,x9/14,pa/"
"h,x8/0,pp/d,x4/12,s14,pf/b,x15/9,s2,x5/11,s9,x12/1,pp/o,x8/4,pi/b,x2/3,s5,x5/6,s9,x15/13,pn/"
"p,x1/8,pg/f,x11/4,s14,x10/15,pi/h,x1/9,s7,x7/11,s14,x0/4,pp/o,x9/15,s13,x4/3,s5,x7/6,s2,x13/"
"0,s4,ph/j,x12/3,s7,x11/2,s3,x13/14,pe/b,x5/6,pa/h,x9/15,pg/m,x2/5,pf/a,x7/11,s11,x10/1,pc/"
"e,x0/14,s15,x10/15,s7,x1/3,pg/b,x10/12,s6,x8/15,pc/p,x1/10,pm/o,x4/3,pn/"
"e,s1,x2/8,s5,x10/4,s12,x1/0,s8,x14/9,pa/f,x5/10,s6,x8/3,pn/i,x4/10,po/b,x3/6,pf/"
"g,x0/9,s3,x15/7,s4,x14/4,s9,x10/15,pn/d,s7,x5/3,s8,x10/7,s12,x1/8,pb/"
"o,s6,x3/2,s9,x13/5,s10,x10/7,s2,x15/1,pn/g,x0/9,pc/o,x6/15,pg/k,x12/4,s12,x7/5,pc/"
"e,x0/14,s12,x12/11,s8,x5/2,pn/m,x4/7,pa/i,x15/9,s5,x10/3,s11,x1/12,pm/h,x14/9,pn/g,x6/3,pe/"
"k,x12/1,s4,x7/4,s14,x2/8,pp/b,x15/1,s1,x7/8,pg/j,x11/9,s4,x15/0,s8,x11/2,pk/"
"c,x4/15,s3,x3/11,pl/p,x12/4,s1,x5/3,pn/b,x2/7,pf/l,x13/0,pn/h,x2/15,pm/a,x14/0,s14,po/"
"p,x8/11,pj/l,x14/15,pe/m,x2/3,s6,x0/7,pg/h,x13/12,s11,pe/b,s6,x8/0,pc/"
"p,x12/6,s15,x11/15,s11,x12/7,s11,x13/15,pm/"
"n,x4/9,s14,x15/11,s4,x1/6,s11,x14/10,s8,x1/15,s8,x2/5,s6,x15/6,s11,x4/"
"0,s4,x8/13,s7,x14/3,s1,x0/13,s4,pp/f,x14/1,s3,x9/15,pm/"
"a,x8/3,s12,x11/15,s1,x13/10,s5,x4/11,s2,x14/10,pg/p,x12/2,s15,x1/10,s5,x13/"
"0,s3,x10/1,s8,x14/12,s3,x5/6,s1,x0/9,s11,x7/4,s8,x13/11,pc/l,x9/5,pi/o,x0/4,s9,x11/13,pf/"
"e,x0/4,s3,x5/15,pc/d,x7/11,pp/l,x4/6,s11,x0/15,s15,x7/12,pa/"
"g,x3/2,s5,x10/12,s7,x6/9,s13,x10/15,pb/h,x0/6,s4,x2/3,pa/d,x1/10,pl/j,x4/12,s13,pb/h,x6/8,pa"
"/i,x4/1,pf/c,x10/9,pj/l,x8/4,pp/m,s9,x15/1,s13,x7/11,po/g,x15/1,pp/"
"i,x8/7,s11,x6/2,s15,x1/9,pm/h,s5,x13/6,s8,x2/12,pn/d,x0/8,pf/g,x5/13,pc/a,x12/7,s6,x1/13,pn/"
"h,x0/2,pl/b,x13/5,s13,x2/14,s15,x4/12,s14,x8/10,pi/f,x5/4,s2,x1/6,s1,x0/9,s11,x6/11,ph/"
"n,x8/2,pi/l,x11/7,pn/k,x13/14,pg/c,x2/5,pj/a,x13/14,pk/o,x5/11,s3,x12/14,pn/"
"g,x13/2,s11,x3/15,pf/b,x6/4,s15,pk/n,x9/2,s4,pd/i,x10/13,s6,pj/h,x7/14,pb/c,x6/10,pp/"
"e,x4/9,s8,x15/3,s9,pc/j,x5/10,s10,pi/e,x11/14,s5,x8/12,s5,pm/o,x0/1,s7,pi/"
"h,x5/9,s11,x0/13,s7,x14/10,s2,x15/6,s13,x0/14,pp/b,x13/10,s14,x2/12,pm/c,x11/6,pi/n,x2/8,pc/"
"k,x6/4,pd/a,x1/2,po/i,s1,x10/5,ph/b,x13/9,pn/i,x6/10,pl/k,x0/7,s2,pm/"
"p,x15/12,s11,x2/4,s7,x11/14,pf/n,s13,x10/5,s15,po/a,x14/0,s1,x3/6,s3,x10/12,s7,x7/11,ph/"
"n,s12,x8/2,pg/m,x15/10,pl/e,x6/"
"0,s13,x7/13,s8,x15/12,s5,x9/6,s2,x10/1,s10,x3/5,s9,x6/10,s15,x7/4,s12,x3/1,s8,pi/k,x2/13,pj/"
"o,x9/14,s5,pb/n,x0/13,s1,x10/8,s6,x6/14,pm/h,x5/4,pd/o,x11/9,pa/"
"f,x12/7,s2,x9/6,s3,x0/15,s15,x3/11,ph/m,x15/13,s15,pa/f,x14/2,pn/"
"m,x5/7,s11,x15/4,s15,x13/11,s1,x8/10,po/f,x1/12,s8,x15/10,ph/j,x9/5,s3,x14/1,pc/f,x12/15,pa/"
"g,x0/5,s10,x2/15,s2,pe/n,x0/5,s1,x4/1,pl/d,x14/8,pf/a,x11/10,pl/o,x5/7,pj/"
"i,s11,x2/12,s4,x13/4,s8,x6/5,pk/h,x7/3,pf/p,x6/14,po/a,x7/13,s8,x10/8,s13,x14/6,s15,x3/0,pd/"
"m,x7/5,pg/k,x13/3,s12,x8/1,pd/f,x5/11,s15,x13/4,s6,x3/2,pp/j,x0/6,s2,x11/1,pm/"
"h,x10/2,s15,x11/5,pj/c,s6,x4/7,s9,x12/13,s9,x9/0,pk/n,x13/1,pf/j,x8/11,s12,x15/0,pm/"
"d,x5/7,po/l,x3/10,pn/p,x11/13,s12,x3/2,pc/d,x0/14,s2,x15/8,s3,x5/7,s9,x8/12,s12,pk/"
"n,x2/10,s14,x9/7,s13,pj/d,x12/5,s3,x13/7,s6,x0/8,s8,x10/13,s13,pb/"
"i,s12,x0/11,s2,x6/10,s12,x8/7,s2,x10/13,pp/l,x3/11,pn/a,x9/1,s6,x3/11,pg/h,x0/2,pc/"
"a,x4/11,s11,x8/7,pb/d,x9/3,s6,x6/12,s14,pj/l,x8/7,s13,x3/4,s11,x14/7,s1,x10/1,pi/"
"a,x11/8,s2,x4/12,s10,x14/6,pd/m,x4/15,s13,x11/14,pp/c,x7/15,pg/j,x14/10,s3,x3/9,pk/"
"c,x2/7,s7,x4/9,pj/n,x7/13,ph/m,x11/1,pa/g,x13/14,ph/i,s8,pc/p,x1/8,pj/l,x13/9,pb/g,x4/12,po/"
"c,x14/5,s10,x0/2,pa/l,x14/15,s14,x9/5,s2,x14/2,pb/n,x3/0,s1,x12/4,s13,x2/5,s7,pj/"
"k,x3/15,s4,pi/b,x4/10,pn/o,s5,x0/12,pa/h,x15/2,s8,x7/14,s2,pi/j,x10/0,s2,x12/15,pe/"
"m,x8/11,s9,x5/0,pb/n,x10/8,pl/f,x1/9,s13,x14/4,s10,x2/12,s14,x0/15,s4,x4/13,s2,x11/3,s7,pm/"
"b,x7/1,pe/f,x15/5,s10,x14/7,ph/i,s15,pd/b,s9,x2/6,pi/p,x12/10,s3,pd/e,s11,x4/5,s7,x8/"
"0,s8,x1/12,s11,x8/3,pc/f,x7/12,pe/p,x2/8,s4,x10/7,s3,pd/o,x8/14,s14,x5/10,pp/a,x2/12,pi/"
"d,x6/4,ph/o,x14/15,pd/e,x3/8,pc/a,s1,x11/5,s5,x2/3,pi/d,s13,x1/0,s1,pb/c,s7,x10/11,pd/"
"m,x0/1,pl/i,x7/5,s12,x10/14,s10,pk/b,x11/13,s11,x15/4,pd/m,x11/7,s5,x10/5,s7,pg/h,x15/4,pd/"
"k,x9/7,s11,x1/13,pc/m,x9/7,pi/j,x0/2,pc/f,x3/8,s4,x6/14,s4,x0/11,s10,x7/4,pj/b,x1/11,pp/"
"o,x0/8,s8,x6/5,s4,x15/13,pm/n,x14/10,s1,x4/2,s13,x9/8,pg/e,x11/5,s9,x13/15,s6,x2/9,s5,pp/"
"m,x7/5,s7,x12/11,s5,x13/8,s8,x1/11,pf/i,x13/5,s6,x0/8,s4,x1/6,s15,x13/11,pk/"
"p,x14/1,s10,x5/2,s12,x15/9,pf/a,x5/14,s11,x8/12,s2,pg/l,x5/2,ph/e,x6/13,s12,x2/9,pf/"
"l,x0/7,pa/m,x12/5,s9,x10/14,pk/h,x0/13,pj/i,x5/15,pb/"
"p,x10/13,s13,x2/9,s3,x11/7,s7,x4/10,s1,x3/15,pn/o,x0/1,pg/b,x9/15,s6,x5/8,s9,pa/o,x0/1,pl/"
"h,x8/12,s1,x11/9,pb/o,x8/6,pc/d,x10/14,pg/h,x3/15,s5,x1/7,pc/p,x15/6,pb/"
"o,x11/10,s1,x2/3,s5,x12/4,s8,x0/2,pe/f,x3/4,s11,x0/10,s13,x7/12,pc/j,x10/9,pn/"
"k,x13/5,s2,x7/14,s6,x0/5,s1,x10/13,s10,x12/11,pg/d,x6/3,s6,x9/7,pn/i,x3/1,s5,ph/l,x13/5,pc/"
"f,x12/2,s3,pk/o,x15/7,pa/l,x0/9,s6,pm/g,x3/12,pi/"
"c,x6/13,s4,x10/8,s3,x7/4,s9,x3/12,s8,x7/2,s1,x0/14,s8,x6/13,s3,x0/4,pf/l,x2/9,s2,x11/1,ph/"
"k,s9,x0/2,s2,x14/12,s13,pa/d,x9/6,s11,x4/0,s15,x14/11,s13,x1/12,s1,x13/0,pj/"
"p,s15,x5/1,s1,x13/10,pc/g,x9/4,pf/k,s13,x6/8,s1,x7/3,s8,x4/11,s14,x8/12,s9,x11/15,pj/"
"c,x4/6,s13,x14/15,pi/o,x10/13,s15,x9/0,s7,pf/d,x13/10,s5,pj/"
"n,x9/8,s10,x10/11,s11,x2/15,s2,pb/k,x14/1,s9,x6/10,s7,x9/5,s1,x14/4,s15,x1/"
"0,s8,x7/10,s14,x2/5,s15,x13/15,s9,x2/4,s9,x15/5,pg/m,x2/9,s13,x0/11,s12,x9/2,pe/"
"j,x10/13,s15,x1/11,pb/g,x10/7,s6,x15/6,pa/p,x3/1,s10,x11/5,s6,x14/12,s6,pj/m,x8/9,pa/"
"i,x11/3,pk/c,x9/6,s6,x14/2,ph/l,x13/5,pa/d,x2/15,s8,x9/12,s5,pk/"
"p,x11/1,s12,x8/5,s14,x10/12,ph/j,x9/11,s13,x14/15,s14,x3/6,pg/l,x2/11,s12,x1/10,pi/"
"o,x13/12,s2,x5/2,s1,x7/6,s5,x14/2,ph/l,x10/8,s4,x12/0,s1,x3/6,pp/d,x15/1,pn/"
"j,x4/14,s12,x5/11,s4,x1/6,s6,x3/8,pb/i,x5/11,s3,x6/14,pe/n,x2/9,s3,x12/11,s13,x5/3,pg/"
"k,s2,x11/2,s6,x3/12,s9,x11/7,s4,x6/8,s8,x1/4,s1,x15/8,s3,x4/14,pi/c,x2/12,s1,x7/13,pp/"
"j,x11/9,pc/d,x7/5,s7,pj/h,x3/6,s5,x4/12,po/i,x1/11,s4,x7/9,s5,x1/10,pj/l,s11,x13/8,s5,x7/"
"0,s6,x8/3,s3,ph/g,x11/9,s13,x10/5,pe/i,x1/0,pp/j,s14,x8/3,s9,pf/i,s9,x4/5,s7,x9/11,pp/"
"j,x5/14,s12,pf/n,x11/3,pi/j,x5/9,s6,x0/12,s12,pm/a,x3/5,s13,x0/14,s5,x8/6,s1,x9/14,s14,pp/"
"b,x8/2,s10,x13/11,s4,x1/3,s7,x11/15,s11,x5/8,s10,x7/2,s9,x3/9,pk/h,x4/"
"0,s6,x11/14,s13,x1/7,pj/l,x9/15,s14,x4/5,s11,x15/8,s8,x3/2,pg/c,x12/10,s4,x1/6,po/"
"e,s15,x14/7,s11,x0/15,pc/j,x11/10,s1,x9/13,s13,x2/1,s2,x11/10,pe/l,x4/3,pm/k,s10,pe/"
"l,x2/11,s7,x12/5,pp/h,x14/8,s1,x15/6,pn/f,x4/13,s10,x5/9,s1,x6/0,s9,pd/"
"o,x11/14,s13,x0/4,s7,x12/11,pb/n,x14/9,s7,x6/3,pe/p,x0/2,pb/"
"g,x3/8,s1,x4/12,s3,x14/9,s12,x8/5,s11,x2/12,pa/d,x11/4,pk/o,x1/15,pb/g,x8/14,s1,x2/5,pk/"
"m,x13/7,s9,x8/1,s13,x9/4,pb/e,x12/2,s5,x3/7,pd/g,x10/2,pe/h,x14/11,s7,x1/8,s7,x12/9,pm/"
"n,x0/3,s12,x7/13,pk/o,x15/9,pa/n,x1/3,ph/c,x11/5,s8,x7/1,s3,x3/8,pn/f,x2/6,pd/k,s5,x10/0,pe/"
"h,x15/6,s11,x12/10,pc/g,x11/6,pm/j,x14/8,pe/b,x3/6,pl/"
"p,x8/7,s7,x14/4,s7,x3/5,s11,x10/1,s12,x3/5,pe/f,x8/4,pp/i,x2/6,s6,x5/13,s4,x1/12,pe/"
"k,x0/4,s1,x1/9,s9,x15/3,s12,x11/7,s5,x1/13,pj/l,x15/10,s2,x3/13,s14,x14/"
"0,s13,x7/6,s8,x11/4,s7,x5/8,pa/o,x0/12,s1,x8/4,s14,x7/11,s7,x0/14,pk/m,x3/13,pf/"
"e,x9/10,s9,x12/5,s4,x0/15,s8,x4/10,s15,x9/13,pm/j,x1/11,s1,pi/c,x6/15,s2,x13/0,pp/"
"f,s4,x8/2,s10,x14/1,s10,x10/4,pc/n,x6/13,pi/j,x15/10,pn/"
"a,x6/7,s11,x3/5,s9,x1/12,s3,x10/8,s9,x5/0,pc/l,s2,x15/2,s11,x14/4,s11,x5/1,pj/g,x0/7,pb/"
"p,x8/2,s10,pl/n,s15,x3/5,s15,x15/0,s6,x2/1,s11,x11/9,pg/o,x8/0,pa/c,x7/10,s11,pe/"
"l,x12/5,s2,x3/0,s7,x1/7,s12,x4/14,pm/p,x13/6,pa/i,x7/11,s3,x14/0,pm/c,x15/7,s6,x9/4,pf/"
"k,x7/2,s11,x1/6,s8,x5/13,s2,x3/0,s4,x8/11,s8,x1/4,s1,x7/2,s10,x15/5,s14,x14/7,pe/m,x8/9,po/"
"c,x4/7,s13,x11/9,s2,x1/14,pm/h,x0/10,s14,x9/15,pd/p,s2,x0/6,s4,x3/2,s14,pe/g,x14/13,po/"
"j,x10/8,pl/e,x11/12,s14,x15/13,pk/b,x12/7,s15,x2/10,s15,x12/5,pc/j,x1/9,s11,x11/14,po/"
"p,x8/4,pl/i,x13/3,s1,x15/7,po/h,s7,x8/9,s4,pb/j,s14,x10/11,s7,x14/2,pm/c,x6/11,s2,x3/7,ph/"
"b,x8/12,pi/a,x11/13,s13,x10/8,pp/f,x12/15,s15,x7/9,s12,x12/10,pn/d,x9/8,s3,x12/5,pj/"
"a,x6/2,pk/i,x10/11,s2,x9/12,s15,pj/d,x3/0,s11,x15/12,s12,x9/7,pe/"
"g,x2/5,s11,x10/11,s14,x0/14,s8,x9/2,s12,x0/7,pa/n,x13/1,pi/o,x3/7,pl/n,x6/14,s15,x15/5,pf/"
"c,x1/10,s5,x12/8,s13,x9/11,pj/p,x7/14,s6,x0/6,s8,x11/9,s11,x6/12,s7,pf/i,x8/15,po/"
"l,x9/14,s2,x0/10,s2,x9/14,pi/a,x1/15,s2,x4/3,pf/m,x11/12,pb/g,x15/2,ph/p,x7/1,pb/"
"n,x14/9,s13,x2/1,s11,x6/14,s5,x8/1,s8,x3/0,ph/m,x13/12,s9,x1/7,s3,x15/9,pk/"
"d,x8/1,s13,x10/11,s5,x1/2,s1,x9/14,s14,x4/0,s10,x3/11,po/b,s2,x5/13,pf/k,x8/0,pa/p,x13/14,pb"
"/o,x5/6,s15,pp/a,x10/4,s9,x8/1,s11,x5/13,pb/j,x10/14,pf/d,x2/13,pg/k,x11/12,pb/"
"p,x3/2,s2,x14/4,pm/j,x7/11,s4,x6/15,pa/g,x11/4,s13,x15/6,pj/e,x5/9,s13,x14/0,ph/"
"i,s15,x12/2,pd/j,x1/14,pg/p,x11/7,s13,x13/0,s9,x7/14,pc/o,x0/8,pm/b,x2/10,pk/"
"p,x3/15,s9,x1/13,s1,x8/15,s5,x5/3,pj/o,x2/11,s8,x4/1,s7,pm/d,x15/13,s1,x2/7,s2,x11/3,s10,pi/"
"k,x14/0,s15,x7/10,s13,x9/4,ph/e,x5/2,pm/g,x9/6,s5,x7/2,s3,x5/15,pk/"
"f,x14/12,s7,x9/1,s6,x0/12,ph/m,s2,x6/2,pb/l,x12/8,s6,x9/5,ph/i,x8/13,pd/f,x10/14,pp/"
"l,x12/13,pd/a,x2/11,pp/k,x4/14,pg/j,x13/7,pm/c,x14/4,po/g,x10/13,s10,x8/2,pn/"
"f,x3/12,s15,x13/15,po/c,x11/14,s3,x0/4,s10,x5/9,s7,x3/10,s11,x8/7,pk/f,x6/4,pa/g,x2/9,pm/"
"n,x13/5,s15,x3/11,s14,x5/9,s14,x8/1,s8,x7/14,pe/o,x15/8,pa/i,x6/7,pe/"
"h,x8/11,s3,x6/14,s15,x1/13,pn/p,x4/15,s10,x1/12,pl/c,x4/11,s5,x1/2,pk/g,s8,x13/15,s11,x6/"
"0,s2,x7/3,ph/o,x10/13,pi/a,x1/9,s12,x13/5,s13,x7/10,s6,x8/1,s10,x0/7,s10,x11/13,po/"
"m,x1/10,s7,x12/9,s4,x4/11,ph/k,x6/13,s7,x3/2,s9,x1/12,s4,x6/7,s2,x5/12,s14,pl/i,x14/6,pa/"
"j,x5/0,s7,pp/i,x13/1,pb/a,x12/5,ph/d,x4/8,pj/i,x10/6,s13,x12/0,s13,x9/8,pk/a,x14/3,s13,x4/"
"0,s12,x10/11,s9,pe/o,s11,x4/5,s14,x12/10,pa/p,x13/4,s5,x11/7,pj/g,x3/0,s4,x1/13,pc/"
"m,x8/10,s9,x6/2,pb/k,x10/7,pm/o,x12/6,pd/p,x10/11,pg/e,x7/0,pl/"
"p,x12/5,s4,x15/3,s10,x8/6,s11,x13/4,pj/o,x0/11,s15,x13/3,s5,x11/10,pi/"
"p,x9/15,s1,x13/6,s10,x7/15,pn/o,x4/2,s8,x9/13,s12,x1/8,s12,x13/6,s4,x7/3,s5,x8/6,ph/"
"g,x11/12,pd/l,x8/7,s11,ph/e,s3,x14/13,s9,x12/9,pn/j,x5/8,s1,x12/15,pk/"
"l,x14/6,s5,x15/10,s10,x11/9,s1,x6/14,pn/b,x7/5,s5,x12/8,pl/h,x15/0,s15,x7/4,s8,pp/"
"f,x12/8,s1,pg/m,x10/13,s14,x3/8,s11,x14/7,s8,x11/10,s15,x1/5,s7,pa/c,x9/"
"0,s14,x10/7,s3,x11/5,pm/b,x3/12,pd/k,s6,x15/1,s9,x11/7,ph/c,x1/4,s1,x8/14,pl/m,s6,x1/0,pn/"
"f,x11/3,po/h,x14/1,s11,pp/j,x7/4,s12,x3/"
"0,s11,x13/10,s3,x11/15,s14,x5/4,s4,x10/14,s13,x15/2,s10,x13/11,pe/b,x0/2,pd/f,s10,pj/"
"l,x3/4,s12,x12/2,s12,x7/0,s2,x12/4,s12,x10/13,pi/a,s4,x15/3,s9,x14/11,pc/k,x8/12,pm/"
"a,s2,x0/11,s6,x4/12,s3,x8/3,s14,x7/15,s1,x4/2,pc/e,x11/0,s5,x7/8,s6,x5/2,s5,pa/o,x9/11,pk/"
"i,x1/7,pe/b,x5/10,s13,x0/13,pd/f,x11/2,pc/"
"k,s15,x10/4,s1,x15/6,s10,x11/12,s6,x4/6,s10,x13/8,pg/i,x14/6,pn/p,x15/5,po/h,s8,x8/0,s2,pk/"
"n,x14/10,pc/e,x7/12,s2,x0/11,s13,x13/4,pp/g,x1/8,s10,x13/7,pf/c,x12/14,pm/e,x9/8,pc/"
"g,x3/13,s2,x1/0,s11,x12/15,pb/j,x2/7,pc/o,x9/11,s1,x14/10,pi/n,x11/4,s5,x13/1,s1,x3/0,pj/"
"b,s13,x9/10,pl/m,x2/6,pi/o,x4/14,pk/c,x7/3,pi/n,x1/0,ph/g,x5/4,pi/a,s4,x0/14,s9,x4/5,s13,x12"
"/0,s11,x8/15,pl/o,x14/3,pf/i,s12,x13/5,s1,ph/e,x1/15,pd/p,x3/13,pf/i,x9/8,s12,x5/15,s10,x10/"
"13,s13,x3/11,s14,x0/1,s14,x15/13,s9,x12/9,s6,x10/6,s3,x8/4,s2,x9/15,s7,x3/13,pb/e,x11/5,pg/"
"d,s10,x7/0,pb/f,x5/9,po/h,x10/4,s10,x6/0,pg/n,x13/2,s9,x5/11,po/d,x14/10,s10,x13/5,pa/"
"e,x14/8,ph/k,x1/0,pd/i,s8,x15/13,pj/b,x6/11,s14,x8/9,pi/d,x10/3,pn/p,x0/14,pi/g,x2/7,pa/"
"n,x14/3,s13,x12/5,s2,x9/0,s10,pp/l,x4/14,pk/m,x8/12,s10,x5/11,s9,x13/1,s2,x2/10,s4,pa/"
"d,x4/3,s6,x12/1,s9,pj/h,x7/11,s14,pc/d,x8/3,pi/h,x13/5,pd/p,x7/6,s10,po/l,x14/3,s1,x11/9,ph/"
"a,x7/10,s7,pl/n,x15/0,s4,x14/7,s4,x13/9,ph/d,s7,x11/1,pb/l,x5/14,s3,x7/"
"0,s11,x10/11,s2,x0/4,pj/g,x3/6,pf/n,s1,x11/0,pi/h,x4/3,s13,x10/13,s5,x2/3,pm/"
"j,x7/13,s9,x12/15,pl/k,x6/2,pf/e,x3/14,s15,x15/7,pp/k,x1/3,pe/"
"m,x15/8,s2,x0/9,s5,x15/11,s1,x14/7,s13,x3/5,s10,x0/2,pg/o,s10,x6/7,pj/f,x15/1,s10,x6/2,s6,x9"
"/3,s14,x0/14,s13,x11/7,s5,x1/2,s1,x9/7,s6,x3/6,s8,x2/14,s1,x6/7,s1,x11/15,s4,x13/8,s9,x7/12,"
"pi/p,x13/8,s11,x9/10,po/h,x4/14,s3,x3/8,s5,x13/10,s14,x5/0,s11,x6/13,s7,x14/5,s13,x1/0,pb/"
"d,x14/7,pc/i,x2/12,s13,ph/m,x7/8,pk/a,x4/13,pl/n,x11/6,s9,x9/10,ph/a,x7/6,s15,x8/2,pb/"
"o,x5/10,s6,x7/2,s13,x8/12,s9,pf/a,x5/4,s7,x0/3,pd/"
"m,x14/6,s8,x8/11,s11,x7/12,s9,x0/3,s12,x5/9,pj/l,x3/13,s13,x2/12,s3,x4/1,s13,x12/11,po/"
"p,x2/4,pf/i,x6/12,pl/b,x8/11,pf/i,x15/13,s14,x3/8,s8,x14/11,s12,x0/15,s2,x9/11,s2,x12/5,pd/"
"k,x10/7,s1,x8/0,s14,x7/4,pm/l,x12/15,pj/n,s13,x11/10,s14,x5/15,s12,x8/2,pg/l,x4/14,pc/"
"k,s1,x0/1,s2,x12/8,s2,x9/10,ph/j,x1/11,s11,x0/5,s6,x11/12,s15,x15/5,pb/f,x4/"
"0,s1,x7/14,s12,x12/15,s6,x9/2,s4,x8/12,s13,x0/4,s2,x10/2,s10,x1/11,s1,x15/0,pe/g,x3/13,pj/"
"h,x11/6,s14,x13/4,s12,x9/7,s9,x12/13,pf/i,x0/11,s10,x1/7,ph/c,x5/0,pk/d,x13/2,s15,x10/14,pp/"
"c,x15/7,s13,x12/1,s11,x10/14,s14,x13/3,pb/g,x10/7,s13,x15/12,pc/a,x2/5,s6,x7/8,pp/k,x0/4,pb/"
"e,x15/10,pg/d,x8/14,s15,x13/7,pn/h,x15/4,pg/f,s1,x2/0,s14,x4/9,s9,x12/6,pc/"
"j,x13/5,s6,x0/9,pa/l,x4/13,pi/m,x15/6,s11,x14/5,s11,pl/n,x4/9,s7,x0/12,pp/"
"c,x9/5,s14,x1/10,s7,x11/2,pn/i,x0/8,pm/p,x7/5,s2,x0/8,s12,x6/5,s7,x13/15,pi/"
"a,x6/3,s8,x1/4,s8,x13/7,s1,x14/12,s12,x9/1,s8,x12/8,s5,x3/6,s7,x14/11,s8,x9/4,ph/"
"p,x7/5,s14,x1/14,s9,x5/2,s6,x15/8,s11,x9/1,pe/n,x5/7,s13,pp/j,x9/10,s3,x2/6,ph/"
"c,x8/3,s7,x9/6,pg/m,x2/12,s9,x9/14,pf/i,x1/4,s8,x7/0,s7,x13/1,s5,x5/7,pk/"
"h,x9/14,s2,x13/3,s9,x8/2,s2,x13/14,pe/b,x7/11,pl/j,x12/10,pa/p,x11/8,pn/"
"m,x9/1,s13,x0/6,s14,pc/h,x7/15,s7,pk/g,x3/2,pn/m,x6/9,s2,x14/15,s10,x3/8,pd/"
"h,x9/12,s10,x13/8,pl/p,x15/0,po/g,x10/6,s14,x12/1,s9,x2/11,s5,x4/10,pe/f,x0/13,pl/"
"d,s15,x5/8,s13,ph/c,x6/13,s6,x7/2,pl/n,x5/15,pi/"
"k,x2/1,s3,x9/11,s12,x0/14,s11,x3/12,s9,x4/8,s15,x7/2,pj/"
"m,x11/13,s11,x6/10,s13,x14/1,s1,x6/10,s5,x14/9,pb/d,x0/6,s10,pc/g,x5/4,s4,x1/14,pb/"
"l,s14,x9/7,s15,x1/14,s7,x12/11,s7,x14/6,pg/d,x8/11,pc/m,x10/6,s3,x1/4,po/h,x11/5,pj/"
"k,x2/9,s3,x7/12,s15,x1/2,pc/p,x7/10,s10,x9/14,s1,x15/10,pm/k,x0/9,pb/a,s10,pn/i,s13,pj/"
"p,x4/3,s6,x10/1,s10,x9/12,pc/i,x4/14,s1,x6/12,pj/k,x11/8,s5,x14/0,s9,x9/11,ph/"
"m,x3/5,s14,x1/7,s14,x15/10,pk/f,x9/2,s9,x15/14,s14,x0/4,po/d,x11/13,s12,pe/h,x2/0,pg/"
"c,x6/7,s9,x3/8,pl/a,x2/11,s7,x6/12,s4,x13/8,s1,pk/e,x3/15,s9,x0/12,s8,x6/1,s9,x4/9,pf/"
"g,x13/3,s4,pe/a,x15/10,s11,pi/l,x13/14,s14,x6/5,s11,pe/p,x13/8,s11,x12/5,pk/d,x7/11,s15,pi/"
"e,x13/5,pm/p,x9/3,s15,x8/5,s1,pl/"
"o,x13/6,s15,x4/3,s11,x7/12,s14,x10/5,s12,x11/15,s10,x14/4,s5,x7/12,pf/m,x9/4,s3,x6/8,s7,pl/"
"i,x1/0,s3,x11/6,pc/h,x5/13,s11,x7/4,pk/"
"b,s12,x10/5,s12,x15/12,s12,x7/2,s3,x14/4,s2,x11/6,s4,x14/3,s12,x2/8,s2,x4/14,s4,x15/3,s5,pi/"
"h,s3,x12/4,po/j,x0/15,s15,x14/11,pl/f,x0/15,s13,pn/c,s4,x1/11,s7,x3/5,pm/"
"b,s15,x8/1,s4,x2/6,s11,x7/5,pi/d,s8,x1/12,s14,x10/9,pj/a,s13,x11/14,s3,x7/4,pn/"
"m,s4,x0/1,s11,x15/7,pj/d,x9/13,pi/h,x6/1,s12,x3/0,pf/j,x9/10,s5,x7/1,pp/h,x8/5,pi/"
"c,x4/2,s6,x5/14,s2,x3/6,pn/m,x11/12,pc/j,x1/8,s15,x5/13,pg/p,x15/8,ph/d,s3,x4/12,s5,x1/14,pm"
"/l,x2/5,s3,x12/1,pj/b,x7/15,ph/i,x14/13,s8,x7/10,s11,pc/f,x11/15,s3,x14/10,pb/h,x15/9,pe/"
"d,x5/1,pp/b,x7/9,s10,x2/5,s6,x7/13,s5,x5/10,s12,x1/0,s11,x6/7,s14,x13/11,s11,pc/f,x15/3,pd/"
"e,x2/7,s1,x8/11,s7,x12/1,s9,x4/7,s12,x13/5,s5,x4/0,s3,x6/9,s12,x11/2,pb/n,x8/5,s7,x4/11,pg/"
"j,x10/0,pl/f,s15,x5/11,pm/a,x1/3,s1,x0/15,s5,x13/1,pk/h,s14,x8/9,pm/"
"l,x12/6,s11,x14/4,s6,x11/13,pp/g,x8/4,pb/h,x3/0,pe/n,s13,pi/f,x7/9,pd/c,x6/4,s10,x10/8,pp/"
"a,x11/2,pn/o,x8/0,s15,x11/5,pl/k,x6/10,s7,x8/13,pc/p,x10/1,s10,x3/9,s14,x12/0,pk/"
"o,x4/8,s3,x13/10,s3,x6/11,pm/h,x13/2,pc/e,x15/3,s7,x8/10,pn/p,x1/11,pm/"
"d,x2/8,s10,x0/6,s15,x11/14,s2,x3/15,pg/k,x9/6,s9,po/m,x12/7,s15,x8/11,pn/f,x5/2,s8,x10/1,ph/"
"o,x15/3,s15,x6/2,s9,x13/15,pa/g,x2/11,s7,x8/9,pj/p,x1/6,s7,x11/8,pe/a,x2/15,s5,x5/3,pk/"
"f,x13/15,s15,x14/6,pj/n,x1/7,s15,x10/11,pl/f,x1/0,s14,x10/13,po/m,x11/3,s14,x14/2,pl/"
"c,x13/15,pk/n,s6,x8/4,pp/a,x3/12,s12,x2/11,s15,x12/9,s5,x6/10,pg/j,x5/4,pn/"
"l,x0/15,s14,x14/4,s9,x7/12,pm/g,x8/5,s8,x6/7,pb/e,x14/12,pm/p,x15/4,pb/"
"e,s2,x0/7,s14,x5/15,s5,x0/2,s6,pm/j,x7/3,s5,x15/12,s5,x0/9,pl/e,s12,x3/10,pa/"
"f,x9/2,s3,x8/5,pd/n,x13/11,s8,x9/10,po/p,x5/14,s5,x4/13,pe/"
"f,x9/12,s9,x7/14,s12,x8/4,s8,x14/5,pg/c,s2,x0/7,pl/f,x10/9,pc/d,x15/5,s15,x12/10,ph/n,x13/"
"0,s5,x7/14,s5,pg/p,x10/8,s1,x12/13,po/d,x10/4,s4,x14/3,pc/b,x2/6,s8,x8/5,po/"
"f,x4/14,s6,x2/1,s8,x7/13,pe/g,x8/2,s7,x14/13,pb/i,s7,x10/15,s6,x0/2,pe/f,x9/13,s14,x6/12,pk/"
"d,x1/2,s9,x8/6,s8,x5/11,s15,x6/12,pi/m,x7/3,pk/n,s6,x11/4,s4,pg/d,x3/10,pi/k,x8/13,s9,x15/"
"0,pc/g,s10,x9/3,s14,x15/2,pa/l,x0/8,s13,x10/11,s9,x2/5,pe/b,x11/7,pi/c,x1/15,s8,x10/2,pe/"
"h,x14/1,s1,x12/15,s4,x1/13,s12,x7/2,s6,x12/6,pg/c,x9/15,pd/p,x5/3,ph/"
"k,x9/7,s8,x15/4,s14,x0/2,s9,x10/7,pa/g,x3/2,s4,x15/4,pl/o,x8/3,s13,pc/"
"g,x9/15,s5,x6/10,s7,x9/12,s13,x6/13,pl/n,s10,x2/5,pp/b,x8/10,ph/i,x1/2,s13,x11/8,pj/"
"a,x5/14,s13,x9/2,s2,x4/5,s9,x0/13,pd/p,x4/15,s15,x11/9,s13,x7/5,s8,x12/14,pc/"
"a,x10/9,s9,x3/14,s7,x4/10,s8,x13/8,s2,x2/15,pm/n,x6/4,s4,x12/9,pp/c,x2/8,pn/"
"e,x7/9,s8,x5/12,s15,x7/10,pp/d,x3/0,pm/o,x9/4,s10,x13/12,s11,x9/3,s12,x10/0,s11,pp/"
"d,x14/2,s4,x10/0,s1,pj/b,x2/7,s1,pn/f,x10/3,pk/d,s3,x7/5,s10,x11/12,s7,x9/10,s11,x14/3,pm/"
"i,x13/4,s9,x9/2,s11,x7/14,s6,x10/9,s10,x5/2,s14,x9/1,po/n,x8/7,ph/b,x0/11,s8,x6/9,pl/"
"j,x11/13,pb/f,x5/6,pg/e,x12/8,s5,x1/10,s14,x4/3,s1,x2/15,s3,x5/0,pd/c,x8/7,pp/l,x9/0,ph/"
"i,s10,x1/12,s11,x5/7,pn/a,x2/0,s6,x11/7,pg/e,x10/14,pn/c,x13/3,pa/e,x15/9,pg/k,x5/2,pn/"
"h,x10/15,s14,x9/2,s15,x4/1,po/p,s10,x8/6,s5,x3/14,pi/m,x0/7,s6,x12/13,pe/j,x3/8,pm/"
"g,x14/13,s4,x4/0,pc/l,x7/11,pk/m,x0/9,s5,x3/1,s10,x13/9,pp/o,x3/7,s3,x13/1,ph/e,x3/6,pp/"
"k,x4/13,pf/i,x7/12,s9,x0/5,pp/b,x13/1,pe/j,s15,pp/c,s10,x12/14,s11,ph/"
"l,x3/4,s9,x15/6,s5,x11/13,s14,x7/4,s14,x14/10,pb/f,s12,x5/8,pd/i,x3/1,pm/a,x12/8,pc/k,x14/"
"0,s7,x7/13,s2,x11/12,s15,ph/g,x1/9,s3,x13/6,pn/m,x5/9,s6,x13/4,pi/o,x15/5,pa/j,s7,pn/"
"f,x3/1,pb/g,x2/10,s4,x3/14,po/e,x13/15,pc/p,x11/14,po/g,s4,x2/6,s12,x10/3,pi/e,x8/6,po/"
"l,x1/14,pg/d,x7/9,pl/b,x4/12,s9,x14/0,s15,x13/1,s12,pn/k,x0/5,s8,x3/12,s10,x5/4,pe/"
"m,s9,x9/14,s4,x3/13,s1,pc/l,x1/14,s13,x11/8,s14,x14/2,s5,x13/7,s2,x6/3,ph/"
"p,x2/15,s10,x13/5,s7,x6/10,s11,x3/9,pn/i,x8/2,s13,x10/4,s11,pe/k,s9,x13/12,s13,pd/"
"f,x2/11,s7,x6/15,pk/o,x2/4,pc/i,x12/7,s15,x0/2,s12,x5/4,pb/f,x10/14,s3,x1/5,s9,x7/12,pa/l,x1"
"5/5,s3,x4/3,s11,x6/9,s12,x13/14,s7,x4/2,s13,x0/8,s5,x14/9,s2,x6/3,s7,x0/2,s6,x3/1,s10,x8/10,"
"s7,x1/7,pn/o,x5/2,s3,x14/11,s5,x5/13,pm/j,x10/2,s4,x11/14,pd/n,x4/10,po/j,x2/8,pk/"
"h,x11/4,s13,x3/13,s15,x11/12,pd/b,x13/15,s15,x0/12,s5,pn/i,x13/11,s5,x12/3,pf/a,x2/11,s2,x13"
"/0,pi/j,x7/15,pc/e,s15,x4/9,s6,x11/14,ph/i,x7/2,s3,x8/3,pf/d,x0/9,s14,x5/10,s10,x4/9,po/"
"g,s11,x12/3,pf/m,s1,x10/9,s14,x5/8,s13,x12/11,pl/"
"e,x15/6,s8,x9/10,s1,x2/11,s3,x10/9,s14,x11/14,s5,x1/13,s10,x4/0,pm/j,x7/8,s8,x12/4,pc/"
"g,x14/9,s7,x11/5,po/m,x2/8,pe/j,x10/5,s1,x1/3,s12,x2/15,pl/m,s9,x12/9,s3,x11/4,pi/b,x7/12,pl"
"/e,x13/6,pa/d,x7/1,pk/n,x14/3,s11,x8/15,pm/g,x12/9,pc/n,x1/15,pd/f,x4/5,pk/a,x6/2,pj/"
"p,x9/7,s10,x3/13,s14,x6/1,s5,x14/9,pe/c,x8/6,pg/i,x12/14,s10,x9/1,pl/"
"o,x8/11,s9,x6/14,s4,x2/15,s11,x6/11,s1,x4/14,pg/b,x2/8,s2,x6/3,pp/h,s12,x8/1,s10,x4/10,pi/"
"c,x12/15,s15,x4/7,s15,x11/6,s10,x8/14,pm/e,s14,x13/7,s3,x8/4,pf/b,x10/9,pe/n,x5/12,pg/"
"c,x0/4,pm/l,s15,x2/3,s5,x12/11,s12,x2/14,s13,x3/12,s12,x11/9,s2,pb/c,x0/2,s4,x1/7,pp/"
"n,x15/2,pd/h,x1/3,s14,x7/14,pg/c,x10/11,pd/a,x14/13,s6,x10/0,s7,x5/6,s14,pe/h,x4/13,s13,pf/"
"k,x9/7,s5,x1/13,s13,x11/0,s5,x7/8,pd/b,s15,x2/1,s13,x12/13,pl/"
"k,x14/10,s3,x15/3,s10,x4/5,s6,x8/10,pm/d,x5/4,pk/j,s5,x10/7,pl/i,s14,x14/2,pd/n,x6/12,po/"
"j,x5/2,s5,pi/n,x12/13,s15,x11/1,s12,pm/h,x14/2,s6,x15/7,s12,x13/9,s5,x14/7,pj/"
"o,x6/3,s11,x1/15,s11,x11/9,s10,x12/8,s7,x4/10,s9,x3/5,s12,ph/e,x12/14,s12,x10/9,s8,x14/8,pk/"
"l,x7/6,pm/f,x1/13,s3,x2/12,s7,x10/8,pg/"
"i,x15/7,s6,x4/1,s8,x11/8,s8,x13/5,s5,x3/1,s12,x14/12,s5,x1/10,s2,pn/e,s11,x2/14,pi/"
"g,x15/6,pf/m,x3/13,pl/k,x9/5,pn/f,x14/1,pe/i,x11/10,pa/n,s1,x2/8,s5,x11/7,s11,x0/10,pd/"
"m,x13/7,pe/k,x9/6,s3,x15/5,pm/i,x13/11,ph/b,x12/6,pm/p,x4/10,s6,x12/5,pn/a,x15/8,pf/"
"j,s15,x4/9,s14,x7/3,s1,x0/1,s2,x5/12,s5,x0/4,pg/b,x11/13,pf/a,x3/14,pk/l,x13/0,ph/"
"n,x14/3,s13,x0/1,pe/l,x10/3,pc/b,x5/12,pd/n,x10/11,po/k,x12/2,s7,x4/8,pd/"
"n,x14/11,s14,x15/6,pk/f,x9/13,s15,x7/4,pl/i,x1/6,s12,x7/9,s6,x14/4,s14,x10/"
"0,s6,x14/4,s1,x6/13,pc/j,x9/11,s7,x2/14,s14,x10/12,s5,x4/13,s10,x7/10,s1,pm/n,x13/14,s3,x2/"
"0,pg/d,x9/14,s3,x7/5,s1,x1/4,s14,x2/10,s10,x0/5,pa/b,x9/13,po/m,x8/2,pp/g,x5/9,s14,x13/2,pj/"
"a,x14/5,s2,x15/3,s14,x1/4,pg/p,x7/2,pb/n,x6/3,s12,x2/10,s11,x9/3,s15,x12/10,s7,pk/p,x9/11,pe"
"/c,s13,x15/13,s14,x9/12,po/a,x2/0,s15,x4/9,s3,pn/p,x6/12,pk/b,x14/11,pe/i,x5/6,pn/"
"m,x14/3,s2,x12/13,s1,x0/9,s15,pj/f,x10/14,pi/h,x6/13,s11,x5/12,s3,x13/6,pe/b,x15/11,pa/"
"p,s1,x10/2,s14,x13/12,s6,x10/4,pb/k,x9/12,s12,x8/13,s14,x10/6,s12,x11/5,s7,x9/8,s11,x7/0,pl/"
"p,s4,pk/e,s13,x5/14,s7,x12/4,s8,x1/2,s12,x14/7,pm/n,x0/5,s3,x4/14,s6,x11/15,pj/"
"e,s12,x7/5,s15,x13/9,pl/d,x11/4,pa/f,x12/15,pg/"
"i,x14/1,s2,x3/12,s7,x10/15,s15,x11/14,s11,x4/15,pf/o,x1/5,pb/e,x0/10,pm/c,x6/2,s11,x4/0,ph/"
"g,x10/1,s10,x8/12,s2,x2/6,s2,x12/15,s10,x10/6,pd/n,x0/4,pg/c,x15/1,pi/"
"d,s13,x6/5,s11,x12/7,s1,x4/11,s3,x6/0,pp/f,x5/3,s3,pm/l,x0/9,pd/n,x1/11,s7,x14/3,pk/"
"m,x2/8,s7,x0/7,s15,x11/2,s3,x5/15,s10,x13/0,pa/l,x7/10,s7,x1/9,s12,x3/11,po/n,x6/12,pp/"
"a,x11/3,pk/e,x4/2,s7,x8/15,ph/f,s15,x2/10,s7,x4/9,pk/b,s12,x8/12,s13,x7/13,s9,x3/1,pd/"
"g,x0/8,s5,x3/12,s12,x15/5,pm/o,x10/11,s10,x8/7,s8,x11/0,s6,x3/8,pf/k,s13,x6/12,pb/i,x9/"
"0,s6,x10/12,s5,x6/13,s11,x9/1,s3,x0/12,s12,x6/10,s7,x11/5,s2,x3/10,s1,x11/7,s3,pg/"
"p,s1,x14/2,s6,x5/9,s8,x10/6,pe/a,s14,x13/8,ph/m,x0/3,pn/e,s7,x9/1,s1,x0/8,ph/k,s7,pa/"
"b,x4/1,s8,x8/10,s7,x0/14,pf/n,x10/2,s8,x6/9,pe/p,x5/0,s9,x6/9,pj/f,x12/3,pa/"
"l,x0/13,s14,x12/9,s6,pm/p,x6/11,s12,x13/9,s5,x5/8,s13,x10/2,pk/c,x7/11,ph/"
"a,x14/3,s13,x6/8,s4,x1/7,s14,x11/15,pp/f";





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


void run()
{
    assert(dance("abcde", "s1,x3/4,pe/b") == "baedc");

    const std::string answer1 = dance("abcdefghijklmnop", input);
    std::cout << "16.1 " << answer1 << '\n';
    assert(answer1 == "hmefajngplkidocb");

    assert(dance2("abcde", "s1,x3/4,pe/b", 1) == "baedc");
    assert(dance2("abcde", "s1,x3/4,pe/b", 2) == "ceadb");

    assert(dance3("abcde", "s1,x3/4,pe/b", 1) == "baedc");
    assert(dance3("abcde", "s1,x3/4,pe/b", 2) == "ceadb");

    assert(dancetest());
    
    const std::string answer2 = dance3("abcdefghijklmnop", input, 1000000000);
    std::cout << "16.2 " << answer2 << '\n';
    assert(answer2 == "fbidepghmjklcnoa");
}

}


namespace day17 {


int part1(int skip, int insert_count)
{
    std::vector<int> buf;
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
    int buf = -1; // 0 is always at position 0, buf will be for the value at pos 1, discard all else
    int pos = 0;
    int i = 0;
    for (;;) {
        if (pos == 1)   // ignore all insertions except at position 1
            buf = i;
        if (i++ == insert_count)
            break;
        pos = (pos + skip) % i + 1; // buf size == i because we "insert" a value on every loop
    }
    assert(buf != -1);
    return buf;
}


void run()
{
    assert(part1(3, 2017) == 638);

    const int answer1 = part1(349, 2017);
    std::cout << "17.1 " << answer1 << '\n';
    assert(answer1 == 640);

    assert(part2(3, 2017) == 1226);
    assert(part2(349, 2017) == 422);

    const int answer2 = part2(349, 50000000);
    std::cout << "17.2 " << answer2 << '\n';
    assert(answer2 == 47949463);
}

}



namespace day18 {

const char * input =
    "set i 31\n"
    "set a 1\n"
    "mul p 17\n"
    "jgz p p\n"
    "mul a 2\n"
    "add i -1\n"
    "jgz i -2\n"
    "add a -1\n"
    "set i 127\n"
    "set p 680\n"
    "mul p 8505\n"
    "mod p a\n"
    "mul p 129749\n"
    "add p 12345\n"
    "mod p a\n"
    "set b p\n"
    "mod b 10000\n"
    "snd b\n"
    "add i -1\n"
    "jgz i -9\n"
    "jgz a 3\n"
    "rcv b\n"
    "jgz b -1\n"
    "set f 0\n"
    "set i 126\n"
    "rcv a\n"
    "rcv b\n"
    "set p a\n"
    "mul p -1\n"
    "add p b\n"
    "jgz p 4\n"
    "snd a\n"
    "set a b\n"
    "jgz 1 3\n"
    "snd b\n"
    "set f 1\n"
    "add i -1\n"
    "jgz i -11\n"
    "snd a\n"
    "jgz f -16\n"
    "jgz a -19\n";


enum opcodes {
    op_add, op_addi,
    op_jgz, op_jgzi, op_jgzii,
    op_mod, op_modi,
    op_mul, op_muli,
    op_set, op_seti,
    op_snd,
    op_rcv
};
/*
set i 31        10      8       31
set a 1         10      0       1
mul p 17        8       15      17
jgz p p         2       15      15
mul a 2         8       0       2
add i -1        1       8       -1
jgz i -2        3       8       -2
add a -1        1       0       -1
set i 127       10      8       127
set p 680       10      15      680
mul p 8505      8       15      8505
mod p a         5       15      0
mul p 129749    8       15      129749
add p 12345     1       15      12345
mod p a         5       15      0
set b p         9       1       15
mod b 10000     6       1       10000
snd b           11      1       0
add i -1        1       8       -1
jgz i -9        3       8       -9
jgz a 3         3       0       3
rcv b           12      1       0
jgz b -1        3       1       -1
set f 0         10      5       0
set i 126       10      8       126
rcv a           12      0       0
rcv b           12      1       0
set p a         9       15      0
mul p -1        8       15      -1
add p b         0       15      1
jgz p 4         3       15      4
snd a           11      0       0
set a b         9       0       1
jgz 1 3         4       1       3
snd b           11      1       0
set f 1         10      5       1
add i -1        1       8       -1
jgz i -11       3       8       -11
snd a           11      0       0
jgz f -16       3       5       -16
jgz a -19       3       0       -19
*/
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

// every instruction will occupy 3 ints
std::vector<int> compile(const char * input)
{
    std::vector<int> prog;
    std::locale loc;
    eachline(input, [&](std::string line) {
        std::vector<std::string> tokens;
        eachword(line, [&](std::string word) {
            tokens.push_back(word);
        });
        assert(2 <= tokens.size() && tokens.size() <= 3);
        int op = get_opcode(tokens[0]), arg0 = 0, arg1 = 0;
        switch (op) {
        case op_add:
        case op_mod:
        case op_mul:
        case op_set:
            assert(tokens.size() == 3);
            assert(std::isalpha(tokens[1][0], loc));
            arg0 = tokens[1][0] - 'a';
            if (std::isdigit(tokens[2][0], loc) || tokens[2][0] == '-') {
                ++op; // switch to immediate version of opcode
                arg1 = std::stoi(tokens[2]);
            }
            else
                arg1 = tokens[2][0] - 'a';
            break;

        case op_jgz: // either "jgz a b" (op_jgz), "jgz a 99" (op_jgzi) or "jgz 88 99" (op_jgzii)
            {
                assert(tokens.size() == 3);
                bool immediate_arg0 = false, immediate_arg1 = false;
                if (std::isdigit(tokens[1][0], loc) || tokens[1][0] == '-') {
                    immediate_arg0 = true;
                    arg0 = std::stoi(tokens[1]);
                }
                else
                    arg0 = tokens[1][0] - 'a';
                if (std::isdigit(tokens[2][0], loc) || tokens[2][0] == '-') {
                    immediate_arg1 = true;
                    arg1 = std::stoi(tokens[2]);
                }
                else
                    arg1 = tokens[2][0] - 'a';
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
            assert(tokens.size() == 2);
            assert(std::isalpha(tokens[1][0], loc));
            arg0 = tokens[1][0] - 'a';
            break;

        default:
            assert(false);
            break;
        }
        prog.push_back(op);
        prog.push_back(arg0);
        prog.push_back(arg1);
    });
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



void run()
{
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
    std::cout << "18.1 " << answer1 << '\n';
    assert(answer1 == 3188);

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
    std::cout << "18.2 " << answer2 << '\n';
    assert(answer2 == 7112);
}

}



namespace day19 {

const char * input =
"                                                                                                   |                                                                                                     \n"
" +-------------------+               +-+ +-------+       +-------------------+                     |                                         +---+                                   +-----+       +---+ \n"
" |                   |               | | |       |       |                   |                     |                                         |   |                                   |     |       |   | \n"
" |         +---+     |   +---------------|-------|-----------------------+ +-----------------------------+                                   |   |                                   |     |       |   | \n"
" |         |   |     |   |           | | |       |       |               | | |                     |     |                                   |   |                                   |     |       |   | \n"
" |         |   +---------------------|-----------------------------------|-------------------------------------------------------------------|-----------------+           +-----------------------+   | \n"
" |         |         |   |           | | |       |       |               | | |                     |     |                                   |   |             |           |         |     |           | \n"
" |         |         |   +-------------|-|---------------|---------------|---|---------------------------|-------------------------+         |   |             |         +-|---------|-------------+   | \n"
" |         |         |               | | |       |       |               | | |                     |     |                         |         |   |             |         | |         |     |       |   | \n"
" |   +-------------------------------|-----------|-------|---------------|---|---------------------|-----|-----------------------------------|---|-------------+ +-------+ |         +-----|---+   |   | \n"
" |   |     |         |               | | |       |       |               | | |                     |     |                         |         |   |               |         |               |   |   |   | \n"
" |   +-+   |         |               | | |       |       |               +-+ |                     |     | +---------------------------------|---|---------------+         |               |   |   | +-+ \n"
" |     |   |         |               | | |       |       |                   |                     |     | |                       |         |   |                         |               |   |   | |   \n"
" |     |   |         |               | | |   +---|-------|-------------------|---------------------|-----|-|---------------------------+     | +-|-------------+           | +-----+       |   |   | |   \n"
" |     |   |         |               | | |   |   |       |                   |                     |     | |                       |   |     | | |             |           | |     |       |   |   | |   \n"
" | +---|-------------------------------|-|---------------|---------------+   |                   +---------------------+           +-------+ +-|-|-------------------------|-|-----|---------------|---+ \n"
" | |   |   |         |               | | |   |   |       |               |   |                   | |     | |           |               |   |   | |             |           | |     |       |   |   | | | \n"
" | |   +---|-------------------------|---|---|-------------------------------|-+               +-----+ +-|-----------------------------|-------|---------------|-----------|-|-----+       |   |   | | | \n"
" | |       |         |               | | |   |   |       |               |   | |               | | | | | | |           |               |   |   | |             |           | |             |   |   | | | \n"
" | | +---+ | +-+     |               | | |   |   |       |       +-----------|-+               | +-|-----|---------------+             |   |   | |             |           | |             |   |   | | | \n"
" | | |   | | | |     |               | | |   |   |       |       |       |   |                 |   | | | | |           | |             |   |   | |             |           | |             |   |   | | | \n"
" | | |   | | | |     |     +---+     | | |   |   |       |       |       |   |       +---------|---|---|-|---------------|-----------------|---|-|-------------|-------------|---------+ +-|-+ |   | | | \n"
" | | |   | | | |     |     |   |     | | |   |   |       |       |       |   |       |         |   | | | | |           | |             |   |   | |             |           | |         | | | | |   | | | \n"
" | | +-+ | | | |     |     |   | +-+ | | |   |   |       |       |       |   |       |         |   | | | | |           | |             |   |   | |             |           | +-----------+ | | |   | | | \n"
" | |   | | | | |     |     |   | | | | | |   |   |       |       |       |   |       |         |   | | | | |           | |             |   |   | |             |           |           |   | | |   | | | \n"
" | |   +-----|-|-+   |     |   | +-|-|-|-------+ |       |       | +---+ |   |       |         |   | | +-----------------------+       |   |   | |             |           |           |   | | |   | | | \n"
" | |     | | | | |   |     |   |   | | | |   | | |       |       | |   | |   |       |         |   | |   | |           | |     |       |   |   | |             |           |           |   | | |   | | | \n"
" | |     | | | +-|---------|---|---|-|-|-|---|---|---+   |       | |   | |   |       |         |   | |   | |           | |     |       |   |   | |             |           |           |   | | |   | | | \n"
" | |     | | |   |   |     |   |   | | | |   | | |   |   |       | |   | |   |       |         |   | |   | |           | |     |       |   |   | |             |           |           |   | | |   | | | \n"
" | |     | | |   |   |     |   | +-+ | | +-----|-|-------|-------------|-----|-----------------|---|-|-----|-----------|-|-----|-------|-----------------------------------|---------------|---------+ | \n"
" | |     | | |   |   |     |   | |   | |     | | |   |   |       | |   | |   |       |         |   | |   | |           | |     |       |   |   | |             |           |           |   | | |   |   | \n"
" | | +-----|-|---|-------------|-|-------------------|-------------|---|-|-----------|---------|---------|-----------------------------+   | +-|---------------|-+     +---------------|---|-|-------+ | \n"
" | | |   | | |   |   |     |   | |   | |     | | |   |   |       | |   | |   |       |         |   | |   | |           | |     |           | | | |             | |     |   |           |   | | |   | | | \n"
" | +-|-----|-|-------|-----|-----|-+ | | +-----|-|-------|---------------------------+         |   | |   | |           | |     |           | | | |             | |     |   |           +-----|-+   | | | \n"
" |   |   | | |   |   |     |   | | | | | |   | | |   |   |       | |   | |   |                 |   | |   | |           | |     |           | | | |             | |     |   |               | |     | | | \n"
" |   |   | | |   |   |     |   | | | | | |   | | |   |   |       | |   | |   |         +------I|---|-------|-----------|-|---------------------|---------------|-------|---|-+         +-------+   | | | \n"
" |   |   | | |   |   |     |   | | | | | |   | | |   |   |       | |   | |   |         |       |   | |   | |           | |     |           | | | |             | |     |   | |         |   | | |   | | | \n"
" |   |   | | |   |   |     |   +-|---|-|-|-----+ |   |   |       | |   | |   |         |       |   | |   | |       +---|-------|----Z------------|-------------|-----------|-----------|-+ | | |   | | | \n"
" |   |   | | |   |   |     |     | | | | |   |   |   |   |       | |   | |   |         |       |   | |   | |       |   | |     |           | | | |             | |     |   | |         | | | | |   | | | \n"
" |   |   +-|---------------|-----|---|-|-----|---+   |   |       | |   | |   |         |       |   | |   | |       |   | |     |     +-----------|-------------|-------------|-+       | | | | |   | | | \n"
" |   |     | |   |   |     |     | | | | |   |       |   |       | |   | |   |         |       |   | |   | |       |   | |     |     |     | | | |             | |     |   | | |       | | | | |   | | | \n"
" |   |     | |   |   |     |     +---|-|-----------+ | +-|-------+ |   | +-------------|-------|---|-----|---------|---|-|-------------------|-|---------------|-------|-----+ |       | | | | |   | | | \n"
" |   |     | |   |   |     |       | | | |   |     | | | |         |   |     |         |       |   | |   | |       |   | |     |     |     | | | |             | |     |   |   |       | | | | |   | | | \n"
" |   |     | |   |   |     |       | | | |   |     | | | |       +-|---|---------------|-------|---|-------|-------|---|-----------+ +---------------------------+     |   |   |     +-|---|-|-|-+ | | | \n"
" |   |     | |   |   |     |       | | | |   |     | | | |       | |   |     |         |       |   | |   | |       |   | |     |   |       | | | |             |       |   |   |     | | | | | | | | | | \n"
" |   |     | |   |   |     |       | | | |   |     | | | |       | |   |     |         |       |   | |   | |       |   | |     |   |       | | | |             |       |   |   |     | | | | | | | | | | \n"
" |   |     | |   |   |     |       | | | |   |     | | | |       | |   |     |         |       |   | |   | |       |   | |     |   |       | | | |             |       |   |   |     | | | | | | | | | | \n"
" |   |     | |   |   |     | +-----|---|-|---------|-|-|---------|-----------|---------|-------------|-------------------+     |   |       | | | |             |       |   |   |     | | | | | | | | | | \n"
" |   |     | |   |   |     | |     | | | |   |     | | | |       | |   |     |         |       |   | |   | |       |   |       |   |       | | | |             |       |   |   |     | | | | | | | | | | \n"
" |   |     | |   |   |     | |     | | | |   |     | | | |       | |   |     |         |       |   | |   | |       |   |       | +-|-----+ | | | |             | +-------------|-------|-|-|-+ | | | | | \n"
" |   |     | |   |   |     | |     | | | |   |     | | | |       | |   |     |         |       |   | |   | |       |   |       | | |     | | | | |             | |     |   |   |     | | | |   | | | | | \n"
" +---------|-----|---------|-|-----|-|-|-------------------------|-|---------|---------|-----------|-|---|---------|---|-------|-------------|-|-|---------+   | |     |   |   |     | | | |   | | | | | \n"
"     |     | |   |   |     | |     | | | |   |     | | | |       | |   |     |         |       |   | |   | |       |   |       | | |     | | | | |         |   | |     |   |   |     | | | |   | | | | | \n"
"     |     | |   |   |     | |     | | | |   |     | | | |       | |   |     |         |       |   | |   | |       |   |       | | |     | | | | |         |   | |     |   |   +-+   | | | |   | | | | | \n"
"     |     | |   |   |     | |     | | | |   |     | | | |       | |   |     |         |       |   | |   | |       |   |       | | |     | | | | |         |   | |     |   |     |   | | | |   | | | | | \n"
"     |     | |   |   |     | |     | +-|-|---|-------|-----------------------|---------------------|-+   | |       |   |       | | |     | | | | |         |   | |     |   |     |   | | | |   | | | | | \n"
"     |     | |   |   |     | |     |   | |   |     | | | |       | |   |     |         |       |   |     | |       |   |       | M |     | | | | |         |   | |     |   |     |   | | | |   | | | | | \n"
" +---|-------|---|-----------------|---|-|---|-----------|-------------------|---------------------|-----|---------|---|-------|-|-|-----------+ |         |   | |     |   |     |   | | | |   | | | | | \n"
" |   |     | |   |   |     | |     |   | |   |     | | | |       | |   |     |         |       |   |     | |       |   |       | | |     | | |   |         |   | |     |   |     |   | | | |   | | | | | \n"
" |   |     | |   |   |     | |     |   | |   |     | | | |       | |   |     |         |       |   |     | |       |   |       | | |     | | |   |         |   | |     |   |     |   | | | |   | | | | | \n"
" |   |     | |   |   |     | |     |   | |   |     | | | |       | |   |     |         |       |   |     | |       |   |       | | |     | | |   |         |   | |     |   |     |   | | | |   | | | | | \n"
" |   |     | |   |   |     | |     |   | |   |     | | | |       | |   |     |         |       |   |     | |       |   |       +-|-----+ | | |   |         |   | |     |   |     +---+ | | |   | | | | | \n"
" |   |     | |   |   |     | |     |   | |   |     | | | |       | |   |     |         |       |   |     | |       |   |         | |   | | | |   |         |   | |     |   |           | | |   | | | | | \n"
" |   |     | |   |   |     | |     |   | |   |     | | | |       | |   |     |         |       |   |     | |       |   |         | |   | | | |   |         |   | |     |   |           | | |   | | | | | \n"
" |   |     | |   |   |     | |     |   | |   |     | | | |       | |   |     |         |       |   |     | |       |   |         | |   | | | |   |         |   | |     |   |           | | |   | | | | | \n"
" |   |     | |   |   |     | |     |   | |   |     | | | +-------|---------------------|-+     |   |     | |       |   |         | |   | | | |   |         |   | +-+ +-------------------|-+   | | | | | \n"
" |   |     | |   |   |     | |     |   | |   |     | | |         | |   |     |         | |     |   |     | |       |   |         | |   | | | |   |         |   |   | | |   |           | |     | | | | | \n"
" |   +-+   | |   |   |     | | +-----+ | |   |     | | |       +-|-----------|---------------------|-----------------------------|-------|-|-----|-------------|-------|-----------------------|-+ | | | \n"
" |     |   | |   |   |     | | |   | | | |   |     | | |       | | |   |     |         | |     |   |     | |       |   |         | |   | | | |   |         |   |   | | |   |           | |     |   | | | \n"
" |   +-|-----|-------|-----|---|-----|-|-----|---------|-----+ | | |   |     |   +-----|-|-----|---|-+   | |       |   |         | |   | | | |   |         |   |   | | |   |           | |     |   | | | \n"
" |   | |   | |   |   |     | | |   | | | |   |     | | |     | | | |   |     |   |     | |     |   | |   | |       |   |         | |   | | | |   |         |   |   | | |   |           | |     |   | | | \n"
" |   | +---+ |   |   | +---+ | |   | | | |   | +---|---------|-|---|---------|---+     | |     |   | |   | |       |   |         | |   | | | |   |         |   |   | | |   |           | |     |   | | | \n"
" |   |       |   |   | |     | |   | | | |   | |   | | |     | | | |   |     |         | |     |   | |   | |       |   |         | |   | | | |   |         |   |   | | |   |           | |     |   | | | \n"
" |   |       |   |   | |     | | +---|---|-----|-----|-+     | | | |   |     |         | |     |   | |   | |       |   |         | |   | | +-|---|---------|-----------------------------------|---+ | | \n"
" |   |       |   |   | |     | | | | | | |   | |   | |       | | | |   |     |         | |     |   | |   | |       |   |         | |   | |   |   |         |   |   | | |   |           | |     |     | | \n"
" | +-----------------|-------|-----|---------------|-|-------|---|-----------+   +-----|-+     |   | |   | |       |   |         | |   | |   |   |         |   |   | | |   |           | |     |     | | \n"
" | | |       |   |   | |     | | | | | | |   | |   | |       | | | |   |         |     |       |   | |   | |       |   |         | |   | |   |   |         |   |   | | |   |           | |     |     | | \n"
" | | |   +---|---+   | |     | | | | | | |   | |   | |       | | | |   |         |     |       |   | |   | |       |   |         | |   | |   |   |         |   |   | | |   |           | |     |     | | \n"
" | | |   |   |       | |     | | | | | | |   | |   | |       | | | |   |         |     |       |   | |   | |       |   |         | |   | |   |   |         |   |   | | |   |           | |     |     | | \n"
" | | |   | +-|-----------------|-|---|---+   | |   | |       | | | |   |         |     |       |   +-------|-------|-------------|-|-----|-------|---------|---------|-----|-----------|-----------+ | | \n"
" | | |   | | |       | |     | | | | | |     | |   | |       | | | |   |         |     |       |     |   | |       |   |         | |   | |   |   |         |   |   | | |   |           | |     |   | | | \n"
" | | | +-|-|-|-------|-|-----|-|-|---|-|-----------+ |       | | | |   |       +-------|-------|---------|---------|-----+       | | +-|-+   |   | +---+   |   |   | | |   |           | |     |   | | | \n"
" | | | | | | |       | |     | | | | | |     | |     |       | | | |   |       | |     |       |     |   | |       |   | |       | | | |     |   | |   |   |   |   | | |   |           | |     |   | | | \n"
" | | | | | | |     +-|-|-----|-----|-|-------|-------|-------------------------+ |     |       |     |   | |       |   | +---------|-----------+ | |   |   |   |   | | |   |           | |     |   | | | \n"
" | | | | | | |     | | |     | | | | | |     | |     |       | | | |   |         |     |       |     |   | |       |   |         | | | |     | | | |   |   |   |   | | |   |           | |     |   | | | \n"
" | | | +---|-------+ | | +-+ | | | | | |     | |     |       | | +-|-------------|-------------|---------|---------+   | +-------|---|-------|---|---------|-----------------------------|-----+   | | | \n"
" | | |   | | |       | | | | | | | | | |     | |     |       | |   |   |         |     |       |     |   | |           | |       | | | |     | | | |   |   |   |   | | |   |           | |         | | | \n"
" | | |   | | |       | | +-|-|-+ +-|---|-------|-----|---+   | |   | +-----------|-----|-------------|---|-|-----------------------|-|---------------------|---|-------|---------------|-|-------+ | | | \n"
" | | |   | | |       | |   | |     | | |     | |     |   |   | |   | | |         |     |       |     |   | |           | |       | | | |     | | | |   |   |   |   | | |   |           | |       | | | | \n"
" | | |   | | |       | | +---|-+   | | |     | |     | +-----|-|---|-|-----------|-------+     |     |   | |           | |       | | | |     | | | |   |   |   |   | | |   |           | |       | | | | \n"
" | | |   | | |       | | | | | |   | | |     | |     | | |   | |   | | |         |     | |     |     |   | |           | |       | | | |     | | | |   |   |   |   | | |   |           | |       | | | | \n"
" | | |   | | |       | | | | | | +-+ | |     | |     | +-----|-----|-+ |         |     | |     |     |   | |           | |     +---|-|-|-----+ | | |   +---|-------|-------|-----------|---+     | | | | \n"
" | | |   | | |       | | | | | | |   | |     | |     |   |   | |   |   |         |     | |     |     |   | |           | |     | | | | |       | | |       |   |   | | |   |           | | |     | | | | \n"
" | | |   | | |       | | | | | | |   | |     | |     |   |   | |   |   |         |     | |     |     |   | |           | |     | | | | |       | | |       |   |   | | |   |           | | |     | | +-+ \n"
" | | |   | | |       | | | | | | |   | |     | |     |   |   | |   |   |         |     | |     |     |   | |           | |     | | | | |       | | |       |   |   | | |   |           | | |     | |     \n"
" | | |   | | |       | +---|-|-|-------|-------|-------------|-|-----------------|-------------------+   | |           | |     | | | | |     +-|-|-|-------|-------------------------------------|-----+ \n"
" | | |   | | |       |   | | | | |   | |     | |     |   |   | |   |   |         |     | |     |         | |           | |     | | | | |     | | | |       |   |   | | |   |           | | |     | |   | \n"
" | | |   | | |     +-|-------------+ O | +---|-|---------|-+ | |   |   |         |     | |     |         | |           | |     | | | | |     | | | |     +-+   | +-|-|-----------+     | | |     | | +-+ \n"
" | | |   | | |     | |   | | | | | |   | |   | |     |   | | | |   |   |         |     | |     |         | |           | |     | | | | |     | | | |     |     | | | | |   |     |     | | |     | | |   \n"
" | | |   | +-|-------|---|-------|-|---|-------------|---|-|-------|-------------------|-|-----|---------+ |           | |     | | | | |     | | | |     |     | | | | |   |     |     | | |     | | |   \n"
" | | |   |   |     | |   | | | | | |   | |   | |     |   | | | |   |   |         |     | |     |           |           | |     | | | | |     | | | |     |     | | | | |   |     |     | | |     | | |   \n"
" | | |   | +-|-----|-----|-|---|---|---|-----+ |     |   | +-------|-+ |         |     | |     |           |   +---------|-------|-|---|-----|-|-+ |     |     | | | | |   |     |     | | |     | | |   \n"
" | | |   | | |     | |   | | | | | |   | |     |     |   |   | |   | | |         |     | |     |           |   |       | |     | | | | |     | |   |     |     | | | | |   |     |     | | |     | | |   \n"
" | | |   | | |     | |   | | | | | | +---+     |     |   |   +-|-----|-|---------|-------------------------------------|---------|---|-------|-----|---+ |     | | | | |   |     |     | | |     | | |   \n"
" | | |   | | |     | |   | | | | | | | |       |     |   |     |   | | |         |     | |     |           |   |       | |     | | | | |     | |   |   | |     | | | | |   |     |     | | |     | | |   \n"
" | | |   | | |     | | +-|-|---|---|-|-|-------------|---------------|-----------------|-|-----|-----------|---|-------|-------+ | | | |     | |   |   | |     | | | | |   |     |     | | |     | | |   \n"
" | | |   | | |     | | | | | | | | | | |       |     |   |     |   | | |         |     | |     |           |   |       | |       | | | |     | |   |   | |     | | | | |   |     |     | | |     | | |   \n"
" | | | +-------------|-|-----|---|-|---|-------------|---|---+ |   | | |         |     | |     |           |   +-------|-----------|-|-------|-|---|-----|-----|-+ | | |   |     |     | | |     | | |   \n"
" | | | | | | |     | | | | | | | | | | |       |     |   |   | |   | | |         |     | |     |           |           | |       | | | |     | |   |   | |     |   | | |   |     |     | | |     | | |   \n"
" +-|-+ | | | |     | | | | | | | | | | |       |     |   +---|-|---|-|-|---------|-----|-------|-------------------------------------|---------|---------------|-----|-|---------------|---------+ | |   \n"
"   |   | | | |     | | | | | | | | | | |       |     |       | |   | | |         |     | |     |           |           | |       | | | |     | |   |   | |     |   | | |   |     |     | | |       | |   \n"
"   |   | | | |     | | | | | | | | | | |       |   +-|-------------|-|-----------|-------------|---------------------------------|---|-|-----------------------|-----|-----------------|---+       | |   \n"
"   |   | | | |     | | | | | | | | | | |       |   | |       | |   | | |         |     | |     |           |           | |       | | | |     | |   |   | |     |   | | |   |     |     | |         | |   \n"
"   |   | | | |     | | | | | | | | +-|-|-------|---|-|-------------|-------------|-------------------------------------+ |     +-|---|-------|-----|-----------|---+ | |   |     |     | |         | |   \n"
"   |   | | | |     | | | | | | | |   | |       |   | |       | |   | | |         |     | |     |           |             |     | | | | |     | |   |   | |     |     | |   |     |     | |         | |   \n"
"   |   | | | |     | | | | | | | |   | | +-------+ | | +-----|-----+ | |         |     | |     |           |             |     | | | | |     | +--N|-----|-----|-----|---+ |     +-------|-+       | |   \n"
"   |   | | | |     | | | | | | | |   | | |     | | | | |     | |     | |         |     | |     |           |             |     | | | | |     |     |   | |     |     | | | |           | | |       | |   \n"
"   | +-+ | | |     | | +---------|-----|-|-------+ | | |     +-|---+ | |         |     +-|-----|-----------|---------------------|---|-------|-----|-----------|-----|-+ | |           | | |       | |   \n"
"   | |   | | |     | |   | | | | |   | | |     |   | | |       |   | | |         |       |     |           |             |     | | | | |     |     |   | |     |     |   | |           | | |       | |   \n"
"   | | +---|-------|-|---|-|---------|-|-------+   | | |     +-------|-|-----------------|-----|-----------|-------------|-------------|-------+   |   | |     |     |   | |           | | |       | |   \n"
"   | | | | | |     | |   | | | | |   | | |         | | |     | |   | | |         |       |     |           |             |     | | | | |     | |   |   | |     |     |   | |           | | |       | |   \n"
"   | | | | | |     | |   | +-|-------+ | |         | | |     | |   | | |         |       |     |           |             |     | | | | |     | |   |   | |     |     |   | |           | | |       | |   \n"
"   | | | | | |     | |   |   | | |     | |         | | |     | |   | | |         |       |     |           |             |     | | | | |     | |   |   | |     |     |   | |           | | |       | |   \n"
"   | | | | | |     | |   |   | | |     | |         | | |     | |   | | |         |       |     |           |             |     | | | | +-------|---|---|-|-----------|-----|-----------|---|---+   | |   \n"
"   | | | | | |     | |   |   | | |     | |         | | |     | |   | | |         |       |     |           |             |     | | | |       | |   |   | |     |     |   | |           | | |   |   | |   \n"
"   | | | | | |     | +-------|-|-------|-|-------------------|-|-------|-------------------------------------------------|-----|-|-----------|-|---|-----|-----------|---|-|-----------+ | |   |   | |   \n"
"   | | | | | |     |     |   | | |     | |         | | |     | |   | | |         |       |     |           |             |     | | | |       | |   |   | |     |     |   | |             | |   |   | |   \n"
"   | | | | | |     | +---|-------|-------------------|-|-------|---|-|-----------------+ |     |           |             | +---+ | | |       | |   |   | |     |     |   | |             | |   |   | |   \n"
"   | | | | | |     | |   |   | | |     | |         | | |     | |   | | |         |     | |     |           |             | |     | | |       | |   |   | |     |     |   | |             | |   |   | |   \n"
"   | | | | | |     | |   |   | | |     | |         | | |     | |   | | |         |     | |     |           |             | |     | | |       | |   |   | |     |     |   | |             | |   |   | |   \n"
"   | | | | | |     | |   |   | | |     | |         | | |     | |   | | |         |     | |     |           |             | |     | | |       | |   |   | |     |     |   | |             | |   |   | |   \n"
"   | | | | | |     | |   |   | | |   +---|-----+   | | |     | |   | | |         |     | |     |           |             | |     | | +-------|-|---|-----|-----------|-------------------|-----+   | |   \n"
"   | | | | | |     | |   |   | | |   | | |     |   | | |     | |   | | |         |     | |     |           |             | |     | |         | |   |   | |     |     |   | |             | |       | |   \n"
"   | | | +-|-----------------|-+ |   | | |     |   | | |     | |   | | |         |     | |     |           |             | |     | |         | |   |   | +-----|-----|-+ | |   +-+       | |       | |   \n"
"   | | |   | |     | |   |   |   |   | | |     |   | | |     | |   | | |         |     | |     |           |             | |     | |         | |   |   |       |     | | | |   | |       | |       | |   \n"
"   +-------|-|-----|-|---|---|---------|-|-----|---|---|-----|-|---|---|---------------|-------|-----------|-------------|-------------------|-----------------------|-|-|-----|---------|-|---------|-+ \n"
"     | |   | |     | |   |   |   |   | | |     |   | | |     | |   | | |         |     | |     |           |             | |     | |         | |   |   |       |     | | | |   | |       | |       | | | \n"
"     | |   | |     | |   |   |   |   | | |     |   | | |   +-|-|-----|-|---------|-------|-------------------------------|-|-----|-----------------|---------------------|-----|-+       | |       | | | \n"
"     | |   | |     | |   |   |   |   | | |     |   | | |   | | |   | | |         |     | |     |           |             | |     | |         | |   |   |       |     | | | |   |         | |       | | | \n"
"     | |   +---------------------|---|-------------|---|---|-|-|-+ +-+ |         |     | |     |           | +-------------------------------|---------|---+   |     | | | |   |         | |       | | | \n"
"     | |     |     | |   |   |   |   | | |     |   | | |   | | | |     |         |     | |     |           | |           | |     | |         | |   |   |   |   |     | | | |   |         | |       | | | \n"
"     | |     |     | |   |   |   +---|---------|-----|-|---|-+ | |     +---------|-----|---------+         | |           | |   +-|-------+   | |   |   |   |   |     | | | |   |         | |       | | | \n"
"     | |     J     | |   |   |       | | |     |   | | |   |   | |               |     | |     | |         | |           | |   | | |     |   | |   |   |   |   |     | | | |   |         | |       | | | \n"
"     +---+   |     | |   |   |       | | |     |   | | |   |   | |               |     | |     | |         +-------------------|---------|-------------|---|---------|-|-------------+   | |       | | | \n"
"       | |   |     | |   |   |       | | |     |   | | |   |   | |               |     | |     | |           |           | |   | | |     |   | |   |   |   |   |     | | | |   |     |   | |       | | | \n"
"       | |   |     | |   |   |       | | |     | +-|-|--C--------+               |     | |     | |           |           | |   | | |     |   | |   |   |   |   |     | | | |   |     |   | |       | | | \n"
"       | |   |     | |   |   |       | | |     | | | | |   |   |                 |     | |     | |           |           | |   | | |     |   | |   |   |   |   |     | | | |   |     |   | |       | | | \n"
"     +-------------------|---------------|---------|-|-|---------------------------------|-----|-|-------------------------------|-|-----|-------------|-------------|---|-----|-----|---|-----------+ | \n"
"     | | |   |     | |   |   |       | | |     | | | | |   |   |                 |     | |     | |           |           | |   | | |     |   | |   |   |   |   |     | | | |   |     |   | |       |   | \n"
"     | | | +-------------|-----------------------|-|-|-|-------|---------+       |     | +-----|-------------|-------------|---|-------------|-|-+ |   |   |   |     | | | |   |     |   | |       |   | \n"
"     | | | | |     | |   |   |       | | |     | | | | |   |   |         |       |     |       | |           |           | |   | | |     |   | | | |   |   |   |     | | | |   |     |   | |       |   | \n"
"     | | | | |     | |   |   |       | | |     | | +-------|---|---------|---+   |     |       | |           +-------------------|-|-----------|-----------|---------+ | | |   |     |   | |       |   | \n"
"     | | | | |     | |   |   |       | | |     | |   | |   |   |         |   |   |     |       | |                       | |   | | |     |   | | | |   |   |   |       | | |   |     |   | |       |   | \n"
"     | | | | |     | | +---+ |       | | |     | |   | |   |   +---+     |   +---|-----------------------------------------|-+ | | |     |   | | | |   |   |   |       | | |   | +-------|-----------+ | \n"
"     | | | | |     | | | | | |       | | |     | |   | |   |       |     |       |     |       | |                       | | | | | |     |   | | | |   |   |   |       | | |   | |   |   | |       | | | \n"
"     | | | | |     | | | | | +-+     | | |     | |   +-|---|-------|-----|-------|---------------|-----------------------|---|-+ | |     |   | | | |   |   |   |       | | |   | |   |   | |       | | | \n"
"     | | | | |     | | | | |   |     | | |     | |     |   |       |     |       |     |       | |                       | | |   | |     |   | | | |   |   |   |       | | |   | |   |   | |       | | | \n"
"     | | | | |     | | | | | +-|-----------------------------------------+       |     |       | |                       | +-|-+ | |     |   +-----+   | +-----|-----------|---------|-----+       | | | \n"
"     | | | | |     | | | | | | |     | | |     | |     |   |       |             |     |       | |                       |   | | | |     |     | |     | | |   |       | | |   | |   |   |         | | | \n"
"     | | | | |     | | | | | | |     | | |     | |     |   |   +-------------------------------|---------------+         |   +-|-----------------|-----|-----------------|-|-----|-------------------+ | \n"
"     | | | | |     | | | | | | |     | | |     | |     |   |   |   |             |     |       | |             |         |     | | |     |     | |     | | |   |       | | |   | |   |   |         |   | \n"
"   +-+ | | | +-----|-----------+     | | |     +-|-----|---|---|-----------------|-------------|-|-----------------------+ +---|---+     |     | |     | | |   |       | | |   | |   |   |         |   | \n"
"   |   | | |       | | | | | |       | | |       |     |   |   |   |             |     |       | |             |           |   | |       |     | |     | | |   |       | | |   | |   |   |         |   | \n"
"   |   | | |       | | | | | |       | | |       |     |   +-+ |   |           +-|-----------------------------|-----------------|-------------|-------|---------------|---|---+ |   |   |         |   | \n"
"   |   | | |       | | | | | |       | | |       |     |     | |   |           | |     |       | |             |           |   | |       |     | |     | | |   |       | | |     |   |   |         |   | \n"
" +-|---------------|-|---|-|---------|---+       |   +-------|-------------------|-------+     | | +---+       |           |   | |       |     | |     | +-------------+ | |     |   |   |         |   | \n"
" | |   | | |       | | | | | |       | |         |   | |     | |   |           | |     | |     | | |   |       |           |   | |       |     | |     |   |   |         | |     |   |   |         |   | \n"
" +-----|---|-+     | | | | | |       | |         |   | |     | |   +-------------|-------------|---|---|-------|---------+ |   | |       |     | |     |   |   |         | |     |   |   |         |   | \n"
"   |   | | | |     | | | | | |       | |         |   | |     | |               | |     | |     | | |   |       |         | |   | |       |     | |     |   |   |         | |     |   |   |         |   | \n"
"   |   | | | |     | | | | | |       | |         |   | |     | |             +---|-------|-------|-|---|-------|-----------|---|---------------------------|---|-----------|---------|---|-----------+ | \n"
"   |   | | | |     | | | | | |       | |         |   | |     | |             | | |     | |     | | |   |       |         | |   | |       |     | |     |   |   |         | |     |   |   |         | | | \n"
"   |   | | | +-------+ | | | +-------|-|-------------|-|-----+ |             | | |     | +-----|-|-|-----------------------|---|---------|---+ | |     |   |   |         | |     |   |   |         | | | \n"
"   |   | | |       |   | | |         | |         |   | |       |             | | |     |       | | |   |       |         | |   | |       |   | | |     |   |   |         | |     |   |   |         | | | \n"
"   |   | +---------|-+ | | |       +-+ |         |   | +-------|-------------|-|-------|---------------------------------|-----|-|-+     |   | | |     |   |   |         | |     |   |   |         | | | \n"
"   |   |   |       | | | | |       |   |         |   |         |             | | |     |       | | |   |       |         | |   | | |     |   | | |     |   |   |         | |     |   |   |         | | | \n"
" +-+ +-+ +-----------|-+ | |       |   |         |   |         |             | | +-------------|-+ |   |       |         | |   | | |     |   | | |     |   |   |     +---|-|-----|-------+         | | | \n"
" |   |   | |       | |   | |       |   |         |   |         |             | |       |       |   |   |       |         | |   | | |     |   | | |     |   |   S     |   | |     |   |             | | | \n"
" | +-+   | |       | |   | |       |   |         |   |         | +-----------------------------|---|-----------+         | +-------|-----|-----|-+     |   |   |     |   | |     |   |             | | | \n"
" | |     | |       | |   | |       |   |         |   |         | |           | |       |       |   |   |                 |     | | |     |   | |       |   |   |     |   | |     |   |             | | | \n"
" +-+     | |       | |   | |       |   |         |   |         | |           | |       +-------|-------|-----------------|-----+ | +-----|-----|-------+   |   |     |   | |     |   |     +-------|-+ | \n"
"         | |       | |   | |       |   |         |   |         | |           | |               |   |   |                 |       |       |   | |           |   |     |   | |     |   |     |       |   | \n"
"         | |       | |   | |       |   |         |   |         | |           +-----------------+   |   +-----------------|---------------------|-----------|---------|-----|-----+   |     |       |   | \n"
"         | |       | |   | |       |   |         |   |         | |             |                   |                     |       |       |   | |           |   |     |   | |         |     |       |   | \n"
"         | |       | +-------------|---|--U--------------------|-+             |     +-------------|-------------------------------------------------------|---+     |   | |         |     |       |   | \n"
"         | |       |     | |       |   |         |   |         |               |     |             |                     |       |       |   | |           |         |   | |         |     |       |   | \n"
"         | |       |     | |       |   |         |   |         |               |     +-------------|-----------------------------|-----------------------------------------|---------+     |     +-|-+ | \n"
"         | |       |     | |       |   |         |   |         |               |                   |                     |       |       |   | |           |         |   | |               |     | | | | \n"
"     +---+ +-------|-------|-------|-----------------|---------------------------------------------|-------------------------------------------|---------------------|---|-|---------------|-----+ | | | \n"
"     |             |     | |       |   |         |   |         |               |                   |                     |       |       |   | |           |         |   | |               |       | | | \n"
"     |             +-----|-+       |   +---------+   |         |               |                   |         +-----------+       |       |   | |           +---------+   | |               |       | | | \n"
"     |                   |         |                 |         |               |                   |         |                   |       |   | |                         | |               |       | | | \n"
"     |                   |         |                 +-------------------------|-------------------|---------|---------------------------|---------------------------------+               |   +-----+ | \n"
"     |                   |         |                           |               |                   |         |                   |       |   | |                         |                 |   |   |   | \n"
"     |                   |         |                           +---------------------------------------------+                   |       |   +---------------------------+                 +---+   |   | \n"
"     |                   |         |                                           |                   |                             |       |     |                                                   |   | \n"
"     +-------------------+         +----------------------------------------T------------------------------------------------------------------|-------------------------------------------------+ |   | \n"
"                                                                               |                   |                             |       |     |                                                 | |   | \n"
"                                                                               +-------------------|-------------------------------+     |     |                                                 +-|---+ \n"
"                                                                                                   |                             | |     |     |                                                   |     \n"
"                                                                                                   +-----------------------------+ +-----+     +---------------------------------------------------+     \n"
"                                                                                                                                                                                                         \n";



std::string part1(const char * input)
{
    std::string letters;

    std::vector<std::string> plan;
    eachline(input, [&](std::string s) {
        plan.push_back(s);
    });
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
    eachline(input, [&](std::string s) {
        plan.push_back(s);
    });
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

void run()
{
    const char * test =
        "     |          \n"
        "     |  +--+    \n"
        "     A  |  C    \n"
        " F---|----E|--+ \n"
        "     |  |  |  D \n"
        "     +B-+  +--+ \n";

    assert(part1(test) == "ABCDEF");

    const std::string answer1 = part1(input);
    std::cout << "19.1 " << answer1 << '\n';
    assert(answer1 == "ITSZCJNMUO");

    assert(part2(test) == 38);

    const int answer2 = part2(input);
    std::cout << "19.2 " << answer2 << '\n';
    assert(answer2 == 17420);
}

}



namespace day20 {

const char * input =
    "p=<-833,-499,-1391>, v=<84,17,61>, a=<-4,1,1>\n"
    "p=<-168,3586,-2721>, v=<-61,-58,61>, a=<7,-13,8>\n"
    "p=<364,223,1877>, v=<31,-11,-71>, a=<-5,0,-3>\n"
    "p=<769,-854,-8705>, v=<-20,4,64>, a=<0,1,9>\n"
    "p=<6985,-3666,3653>, v=<-112,99,-23>, a=<-4,0,-4>\n"
    "p=<7688,-2445,1026>, v=<-55,66,-142>, a=<-8,0,6>\n"
    "p=<7281,-151,-5042>, v=<-177,99,41>, a=<-1,-5,5>\n"
    "p=<-2191,71,1322>, v=<174,17,-93>, a=<-6,-1,3>\n"
    "p=<1509,2624,-5338>, v=<-40,5,-8>, a=<0,-4,8>\n"
    "p=<1213,5658,175>, v=<120,-39,-119>, a=<-8,-6,6>\n"
    "p=<621,-6996,-7410>, v=<117,113,-9>, a=<-7,4,11>\n"
    "p=<5468,6435,-787>, v=<-33,-3,21>, a=<-6,-9,0>\n"
    "p=<-489,5399,-5375>, v=<-81,-32,-83>, a=<5,-6,12>\n"
    "p=<2591,1300,629>, v=<-103,-48,44>, a=<-5,-3,-9>\n"
    "p=<-44,-1216,-2499>, v=<-2,73,93>, a=<1,0,6>\n"
    "p=<-129,773,-272>, v=<21,-44,-20>, a=<-1,0,4>\n"
    "p=<-2033,790,-289>, v=<88,-27,-82>, a=<4,-2,11>\n"
    "p=<-10,3459,-748>, v=<5,-121,35>, a=<0,-9,1>\n"
    "p=<-2016,-978,-408>, v=<69,14,-57>, a=<6,5,9>\n"
    "p=<-1472,1419,782>, v=<82,-28,-73>, a=<1,-6,3>\n"
    "p=<-2262,1939,268>, v=<-49,75,47>, a=<6,-7,-3>\n"
    "p=<348,-3515,5362>, v=<8,97,-150>, a=<-1,0,0>\n"
    "p=<7872,7213,10510>, v=<-53,21,3>, a=<-9,-12,-16>\n"
    "p=<942,229,1456>, v=<-27,-44,-23>, a=<0,2,-1>\n"
    "p=<519,3012,1233>, v=<-58,-115,-62>, a=<3,-11,-2>\n"
    "p=<264,-48,-987>, v=<7,-47,14>, a=<-3,6,7>\n"
    "p=<39,1497,-192>, v=<-10,-54,41>, a=<1,-6,-3>\n"
    "p=<309,-3558,-1647>, v=<28,139,74>, a=<-6,12,5>\n"
    "p=<1881,-7333,4674>, v=<-12,59,9>, a=<-3,11,-10>\n"
    "p=<-3513,1502,-1774>, v=<130,46,57>, a=<-1,-6,0>\n"
    "p=<10437,13809,2349>, v=<-80,-143,-12>, a=<-16,-19,-4>\n"
    "p=<802,125,1425>, v=<-81,-70,-113>, a=<4,7,3>\n"
    "p=<190,-3394,1153>, v=<27,164,-52>, a=<-4,4,-2>\n"
    "p=<-371,720,-2706>, v=<24,-24,139>, a=<0,-2,2>\n"
    "p=<3,-708,218>, v=<-16,-3,-15>, a=<2,5,0>\n"
    "p=<20,-1388,932>, v=<-35,118,-57>, a=<4,-4,0>\n"
    "p=<-2394,-827,677>, v=<-1,-14,-24>, a=<16,7,-2>\n"
    "p=<428,669,-921>, v=<31,-66,52>, a=<-6,3,0>\n"
    "p=<496,-1099,-224>, v=<27,92,29>, a=<-6,-3,-2>\n"
    "p=<-405,-2544,-2638>, v=<44,105,90>, a=<-2,5,7>\n"
    "p=<-677,295,2547>, v=<42,-26,-8>, a=<0,1,-16>\n"
    "p=<-1893,-2194,-216>, v=<66,45,45>, a=<9,15,-4>\n"
    "p=<-2257,382,-2610>, v=<152,-19,81>, a=<1,-1,14>\n"
    "p=<620,1222,141>, v=<-46,-64,-78>, a=<0,-3,9>\n"
    "p=<200,886,701>, v=<14,-70,2>, a=<-4,1,-7>\n"
    "p=<-815,-87,-531>, v=<19,-38,105>, a=<5,6,-9>\n"
    "p=<2262,-790,1231>, v=<-121,81,-16>, a=<0,-4,-5>\n"
    "p=<-1120,-2538,-99>, v=<-3,53,-16>, a=<6,8,2>\n"
    "p=<-256,3019,-787>, v=<-30,-24,-18>, a=<4,-11,5>\n"
    "p=<-802,-2441,1418>, v=<-37,115,75>, a=<7,0,-13>\n"
    "p=<3419,-908,809>, v=<4,-2,-28>, a=<-15,4,-1>\n"
    "p=<-634,373,2657>, v=<-12,3,-72>, a=<4,-2,-5>\n"
    "p=<-214,-2252,683>, v=<100,40,22>, a=<-8,6,-5>\n"
    "p=<17,-572,1775>, v=<56,26,3>, a=<-5,0,-8>\n"
    "p=<1403,4867,578>, v=<-32,-57,-61>, a=<-3,-16,3>\n"
    "p=<-1096,4867,935>, v=<-23,-57,10>, a=<7,-16,-5>\n"
    "p=<-4750,-1076,95>, v=<140,50,-115>, a=<8,0,10>\n"
    "p=<-1453,-614,-619>, v=<126,-60,29>, a=<-5,8,0>\n"
    "p=<2433,-2706,3506>, v=<74,74,-116>, a=<-10,1,0>\n"
    "p=<-207,-1806,2921>, v=<7,-80,43>, a=<0,9,-9>\n"
    "p=<-2337,-1311,-2239>, v=<47,43,-33>, a=<2,0,7>\n"
    "p=<4833,3084,-3379>, v=<-68,67,67>, a=<-6,-11,3>\n"
    "p=<2575,-2395,-3713>, v=<-105,-9,103>, a=<-1,10,6>\n"
    "p=<1277,4975,-666>, v=<-69,-160,-47>, a=<1,-6,7>\n"
    "p=<3147,80,-1502>, v=<-131,28,-55>, a=<-1,-3,11>\n"
    "p=<2025,3369,907>, v=<-126,5,-38>, a=<3,-14,0>\n"
    "p=<-2533,-2136,-6908>, v=<16,-26,171>, a=<6,8,7>\n"
    "p=<925,4559,-3710>, v=<-63,-54,102>, a=<2,-9,3>\n"
    "p=<-492,-8181,-3047>, v=<-22,85,90>, a=<3,17,2>\n"
    "p=<-1259,-2552,346>, v=<48,-91,-54>, a=<0,14,3>\n"
    "p=<1861,-3072,-6427>, v=<-18,-17,58>, a=<-4,10,14>\n"
    "p=<379,2323,-4399>, v=<-96,59,88>, a=<6,-11,6>\n"
    "p=<1588,-4840,-3177>, v=<-48,78,14>, a=<-1,8,8>\n"
    "p=<-1038,-264,-278>, v=<53,-44,159>, a=<-1,4,-11>\n"
    "p=<808,3220,-512>, v=<-18,-97,87>, a=<-1,-2,-5>\n"
    "p=<-638,6801,4430>, v=<19,80,-43>, a=<0,-16,-5>\n"
    "p=<10446,1786,1132>, v=<-97,-35,-16>, a=<-12,-1,-1>\n"
    "p=<-710,-239,-516>, v=<38,-28,-33>, a=<1,6,9>\n"
    "p=<-297,1497,2053>, v=<61,-92,-134>, a=<-6,-2,-2>\n"
    "p=<2447,-841,-957>, v=<-75,45,66>, a=<-14,2,0>\n"
    "p=<1740,139,562>, v=<13,-25,-50>, a=<-19,2,1>\n"
    "p=<-402,937,-600>, v=<16,-7,-12>, a=<1,-8,7>\n"
    "p=<-1564,1518,884>, v=<24,19,-88>, a=<11,-17,3>\n"
    "p=<-87,-645,-362>, v=<-29,-29,-14>, a=<4,10,5>\n"
    "p=<354,-715,-40>, v=<-38,96,-67>, a=<1,-6,9>\n"
    "p=<2664,2204,765>, v=<-188,-75,-72>, a=<-1,-11,2>\n"
    "p=<-3106,3879,-4272>, v=<104,-34,139>, a=<-1,-4,-1>\n"
    "p=<-6094,-5859,-9726>, v=<39,107,13>, a=<7,3,14>\n"
    "p=<-8668,801,5898>, v=<-19,-4,23>, a=<14,-1,-10>\n"
    "p=<368,532,808>, v=<-67,-131,-44>, a=<6,15,-6>\n"
    "p=<-417,92,493>, v=<28,12,-62>, a=<3,-3,3>\n"
    "p=<1218,-1663,1788>, v=<-108,127,-175>, a=<-2,8,0>\n"
    "p=<108,592,823>, v=<36,-82,-51>, a=<-8,5,-5>\n"
    "p=<-1062,792,118>, v=<109,-69,36>, a=<0,-1,-8>\n"
    "p=<313,117,-1407>, v=<10,-40,84>, a=<-7,6,11>\n"
    "p=<2526,-4412,2808>, v=<-97,88,29>, a=<1,3,-7>\n"
    "p=<-6258,-604,-3064>, v=<95,2,64>, a=<6,1,2>\n"
    "p=<-4866,-3788,872>, v=<68,-80,40>, a=<5,12,-4>\n"
    "p=<3406,1380,632>, v=<24,6,130>, a=<-8,-3,-9>\n"
    "p=<-8898,-3356,3192>, v=<62,154,83>, a=<13,-3,-11>\n"
    "p=<3852,-267,1655>, v=<0,12,-95>, a=<-14,0,2>\n"
    "p=<793,1021,344>, v=<-59,-8,-26>, a=<2,-3,1>\n"
    "p=<1230,9,-3313>, v=<18,24,13>, a=<-6,-2,11>\n"
    "p=<-5808,-1279,574>, v=<48,68,12>, a=<17,-1,-3>\n"
    "p=<972,-346,1421>, v=<38,14,-36>, a=<-5,0,-1>\n"
    "p=<4290,4120,259>, v=<-8,-15,-38>, a=<-10,-9,2>\n"
    "p=<-5510,-948,-2233>, v=<-6,79,22>, a=<14,-3,4>\n"
    "p=<3394,2258,2611>, v=<-34,66,81>, a=<-6,-10,-12>\n"
    "p=<2512,-3034,3045>, v=<-17,110,-36>, a=<-5,0,-5>\n"
    "p=<-5482,1040,1183>, v=<80,-21,-42>, a=<8,-1,0>\n"
    "p=<2988,-7738,-3675>, v=<53,133,1>, a=<-11,10,9>\n"
    "p=<3842,4568,2849>, v=<37,27,29>, a=<-12,-13,-9>\n"
    "p=<-6014,2454,-805>, v=<-17,-57,29>, a=<16,-2,0>\n"
    "p=<-8408,-850,-203>, v=<112,-84,22>, a=<13,8,-1>\n"
    "p=<1079,-2814,-212>, v=<59,22,36>, a=<-7,6,-2>\n"
    "p=<3806,2478,-131>, v=<42,-48,-121>, a=<-13,-3,9>\n"
    "p=<3779,2532,-995>, v=<-55,62,65>, a=<-6,-11,-2>\n"
    "p=<2024,2721,-536>, v=<-74,-15,-78>, a=<0,-6,7>\n"
    "p=<2537,4260,-2615>, v=<-65,-2,69>, a=<-2,-11,2>\n"
    "p=<-919,534,4513>, v=<-63,24,-111>, a=<7,-3,-4>\n"
    "p=<-3446,8037,9158>, v=<77,-2,-125>, a=<1,-12,-7>\n"
    "p=<4942,-1503,-2128>, v=<-8,78,-52>, a=<-7,-2,6>\n"
    "p=<1252,-2259,13568>, v=<-35,62,-81>, a=<0,0,-16>\n"
    "p=<-1592,1593,1256>, v=<7,-45,-72>, a=<2,0,2>\n"
    "p=<-4184,3213,-13882>, v=<116,-90,145>, a=<0,0,13>\n"
    "p=<-6938,2781,-8662>, v=<-11,-41,-37>, a=<11,-2,15>\n"
    "p=<8362,-1197,8888>, v=<-103,-60,-25>, a=<-7,5,-12>\n"
    "p=<-3248,-387,-12442>, v=<-58,84,142>, a=<8,-4,11>\n"
    "p=<3731,-1805,-652>, v=<-101,-67,43>, a=<-6,13,-1>\n"
    "p=<-2935,-4500,1823>, v=<110,67,-58>, a=<2,12,-2>\n"
    "p=<-427,-1035,-3457>, v=<-4,-79,90>, a=<2,11,6>\n"
    "p=<4248,4487,1218>, v=<-90,-8,4>, a=<-9,-17,-5>\n"
    "p=<-955,-980,-146>, v=<-118,114,43>, a=<14,-6,-3>\n"
    "p=<-4937,-1970,767>, v=<63,21,36>, a=<14,6,-6>\n"
    "p=<2070,-1937,-4645>, v=<32,77,190>, a=<-11,1,2>\n"
    "p=<-3826,-683,-3908>, v=<139,-26,99>, a=<3,5,7>\n"
    "p=<-3444,-3030,-2594>, v=<45,15,-105>, a=<3,4,10>\n"
    "p=<2996,2920,-2244>, v=<-175,-65,119>, a=<5,-1,-3>\n"
    "p=<4988,9764,-12441>, v=<-128,-91,98>, a=<0,-8,11>\n"
    "p=<8654,3719,-10530>, v=<-142,44,89>, a=<-4,-7,9>\n"
    "p=<-1486,-5329,3276>, v=<18,136,75>, a=<1,0,-8>\n"
    "p=<3194,-1663,-2652>, v=<-82,2,87>, a=<0,2,-1>\n"
    "p=<-5971,3017,11661>, v=<-107,2,-20>, a=<13,-4,-14>\n"
    "p=<-8857,4343,4836>, v=<147,8,55>, a=<4,-6,-9>\n"
    "p=<-628,-9346,1131>, v=<36,-1,10>, a=<-1,12,-2>\n"
    "p=<-4138,4967,-4017>, v=<-54,32,82>, a=<8,-8,1>\n"
    "p=<5768,3563,-4836>, v=<-108,-52,63>, a=<-2,-2,3>\n"
    "p=<14933,-688,2418>, v=<-123,-43,17>, a=<-13,3,-4>\n"
    "p=<7224,-3092,-808>, v=<-33,112,43>, a=<-11,-1,-1>\n"
    "p=<3429,-518,-8893>, v=<14,-17,67>, a=<-7,2,12>\n"
    "p=<199,1711,-191>, v=<-15,-124,96>, a=<0,-3,-12>\n"
    "p=<-1079,997,805>, v=<111,-84,-13>, a=<-3,0,-8>\n"
    "p=<-935,-299,-1523>, v=<47,76,116>, a=<5,-8,2>\n"
    "p=<325,-1187,1867>, v=<-58,85,-108>, a=<5,2,-7>\n"
    "p=<-1697,1141,-1187>, v=<130,-161,179>, a=<2,10,-12>\n"
    "p=<859,-671,-1133>, v=<-96,29,51>, a=<4,4,7>\n"
    "p=<595,-3438,-4651>, v=<-21,165,79>, a=<0,-3,6>\n"
    "p=<63,-2794,-3615>, v=<-2,-61,-45>, a=<0,11,12>\n"
    "p=<679,1588,-1263>, v=<63,0,16>, a=<-6,-4,2>\n"
    "p=<875,-1758,-2159>, v=<-31,76,-68>, a=<0,-1,10>\n"
    "p=<-2219,-708,-535>, v=<-80,53,-68>, a=<11,-2,6>\n"
    "p=<2499,-330,7151>, v=<-60,-120,-67>, a=<-2,9,-13>\n"
    "p=<-1155,846,1047>, v=<-31,12,6>, a=<5,-3,-3>\n"
    "p=<-7454,-5579,4859>, v=<16,11,73>, a=<16,12,-16>\n"
    "p=<-88,-185,3757>, v=<92,-10,-84>, a=<-6,1,-3>\n"
    "p=<-1016,-3781,-3377>, v=<-86,114,102>, a=<8,1,1>\n"
    "p=<-1828,1642,1727>, v=<-43,-88,31>, a=<7,2,-6>\n"
    "p=<-88,1700,-42>, v=<92,30,-28>, a=<-6,-6,2>\n"
    "p=<1594,1816,3322>, v=<-26,56,36>, a=<-2,-8,-10>\n"
    "p=<-7793,5931,-1780>, v=<-51,34,-3>, a=<20,-15,4>\n"
    "p=<-383,1566,-1735>, v=<-19,40,-20>, a=<2,-6,5>\n"
    "p=<-2453,-2289,-3250>, v=<19,29,-16>, a=<4,3,8>\n"
    "p=<-863,4146,1400>, v=<28,-108,-47>, a=<0,-2,0>\n"
    "p=<-1793,5091,-2500>, v=<90,-124,145>, a=<-2,-3,-4>\n"
    "p=<982,4641,-4600>, v=<-80,-47,29>, a=<3,-7,8>\n"
    "p=<1147,3711,-3430>, v=<23,77,114>, a=<-4,-13,0>\n"
    "p=<3382,6531,1490>, v=<-160,-141,12>, a=<3,-5,-4>\n"
    "p=<-5005,12388,3235>, v=<8,3,-163>, a=<6,-16,4>\n"
    "p=<1937,-560,-1952>, v=<-30,-105,-30>, a=<-1,6,4>\n"
    "p=<-1183,-1067,10450>, v=<-50,28,-148>, a=<4,0,-6>\n"
    "p=<-286,10087,8734>, v=<27,-138,-44>, a=<-1,-6,-9>\n"
    "p=<-2080,-677,5926>, v=<-7,-22,-52>, a=<3,2,-5>\n"
    "p=<-6136,7591,5614>, v=<-43,6,-64>, a=<10,-10,-4>\n"
    "p=<5213,2911,115>, v=<6,-14,37>, a=<-7,-3,-2>\n"
    "p=<4667,-1067,-4994>, v=<-180,-12,-12>, a=<3,2,7>\n"
    "p=<7709,7552,-6320>, v=<-58,-33,42>, a=<-7,-8,6>\n"
    "p=<9932,-14,-1601>, v=<65,-99,61>, a=<-16,5,-1>\n"
    "p=<1482,689,-1116>, v=<-56,-9,100>, a=<-3,-3,-4>\n"
    "p=<1257,-1435,1944>, v=<-53,-24,-70>, a=<-2,11,-4>\n"
    "p=<11,1170,2140>, v=<-1,27,-52>, a=<0,-4,-1>\n"
    "p=<-857,4983,8092>, v=<27,-112,-116>, a=<0,-3,-9>\n"
    "p=<-51,1418,-2014>, v=<1,51,-14>, a=<0,-6,5>\n"
    "p=<1840,-2395,3287>, v=<100,-34,-41>, a=<-10,7,-4>\n"
    "p=<7172,-4534,1644>, v=<-104,3,-196>, a=<-8,9,9>\n"
    "p=<3793,1108,-2386>, v=<-59,-35,-18>, a=<-4,0,6>\n"
    "p=<4940,5324,-3099>, v=<-64,-123,5>, a=<-6,-3,6>\n"
    "p=<693,-1000,-2448>, v=<-87,-15,128>, a=<4,3,-3>\n"
    "p=<2305,-70,1985>, v=<37,-13,81>, a=<-7,1,-9>\n"
    "p=<415,68,-1398>, v=<-25,-13,98>, a=<0,1,-2>\n"
    "p=<687,816,-1415>, v=<13,51,81>, a=<-6,-11,0>\n"
    "p=<653,0,-769>, v=<-39,-36,52>, a=<0,4,-1>\n"
    "p=<-2543,1615,744>, v=<167,-104,53>, a=<-2,1,-11>\n"
    "p=<1180,1717,-2350>, v=<-34,-38,82>, a=<-4,-7,6>\n"
    "p=<2778,1700,-2231>, v=<-155,26,174>, a=<-1,-14,-5>\n"
    "p=<-2653,3627,-1955>, v=<90,35,-99>, a=<-1,-7,8>\n"
    "p=<-1765,-9323,-4693>, v=<9,138,-44>, a=<2,6,9>\n"
    "p=<11296,704,3003>, v=<-40,-133,-5>, a=<-14,6,-4>\n"
    "p=<4155,-5660,-5840>, v=<-113,115,44>, a=<0,2,6>\n"
    "p=<9890,7845,-7875>, v=<-78,-41,118>, a=<-10,-9,5>\n"
    "p=<-5798,-3292,9367>, v=<42,-6,-63>, a=<6,5,-10>\n"
    "p=<-766,-184,857>, v=<-94,-71,72>, a=<6,4,-5>\n"
    "p=<10704,-1479,709>, v=<-24,-74,114>, a=<-14,6,-7>\n"
    "p=<5675,-39,-2630>, v=<-11,-72,-112>, a=<-8,4,10>\n"
    "p=<4289,4731,1150>, v=<46,-112,-32>, a=<-9,-1,0>\n"
    "p=<-1813,-28,85>, v=<-54,-59,17>, a=<5,3,-1>\n"
    "p=<6026,10931,280>, v=<5,-80,32>, a=<-8,-10,-2>\n"
    "p=<6455,2585,-4673>, v=<-26,-46,-101>, a=<-7,-1,11>\n"
    "p=<-5479,713,-7130>, v=<120,2,-38>, a=<1,-1,11>\n"
    "p=<-6844,6407,-539>, v=<-5,-84,13>, a=<9,-4,0>\n"
    "p=<-7819,14636,-7832>, v=<80,-55,20>, a=<6,-16,9>\n"
    "p=<-19,-6814,-3308>, v=<40,155,4>, a=<-2,1,4>\n"
    "p=<2672,8474,1957>, v=<31,-57,-71>, a=<-5,-8,1>\n"
    "p=<1426,-9028,-713>, v=<-33,129,9>, a=<-1,11,1>\n"
    "p=<5296,6047,2827>, v=<24,14,-78>, a=<-13,-14,-1>\n"
    "p=<-11762,3422,-6437>, v=<171,-67,109>, a=<11,-2,5>\n"
    "p=<-14963,4181,-2972>, v=<98,114,21>, a=<21,-14,4>\n"
    "p=<3398,2476,3910>, v=<-84,-108,112>, a=<-1,2,-13>\n"
    "p=<-6207,827,-4301>, v=<-64,-7,-49>, a=<14,-1,10>\n"
    "p=<5132,-9475,425>, v=<-65,86,57>, a=<-5,11,-4>\n"
    "p=<2588,525,-602>, v=<-35,-69,-21>, a=<-15,4,7>\n"
    "p=<-444,1181,-1962>, v=<-7,-59,64>, a=<4,-2,7>\n"
    "p=<-1812,-1691,-2050>, v=<104,44,27>, a=<1,7,12>\n"
    "p=<-1756,-851,-2610>, v=<92,17,62>, a=<2,4,12>\n"
    "p=<1524,645,1982>, v=<-130,-68,-55>, a=<4,3,-8>\n"
    "p=<-228,-1843,358>, v=<22,113,38>, a=<-1,0,-7>\n"
    "p=<-1796,709,-1426>, v=<35,-4,-12>, a=<9,-5,12>\n"
    "p=<36,2301,-42>, v=<-37,-95,46>, a=<4,-6,-5>\n"
    "p=<2460,925,1254>, v=<7,-9,-120>, a=<-19,-6,5>\n"
    "p=<4431,-1315,-1309>, v=<-43,107,15>, a=<-17,-4,5>\n"
    "p=<-99,3095,-449>, v=<-37,-40,14>, a=<4,-11,1>\n"
    "p=<961,-1355,1541>, v=<-48,25,-33>, a=<0,4,-4>\n"
    "p=<1411,-445,1381>, v=<-39,53,-25>, a=<-3,-3,-4>\n"
    "p=<-272,-665,90>, v=<74,92,16>, a=<-7,-6,-3>\n"
    "p=<-2117,610,-675>, v=<29,-113,-5>, a=<14,9,6>\n"
    "p=<283,2320,945>, v=<109,-19,-41>, a=<-16,-17,-3>\n"
    "p=<-1217,-1385,-30>, v=<129,52,-8>, a=<-6,5,1>\n"
    "p=<-47,445,30>, v=<-77,82,28>, a=<10,-14,-4>\n"
    "p=<-644,-5230,-1865>, v=<-123,85,-36>, a=<10,7,7>\n"
    "p=<-4494,8840,3343>, v=<145,-84,-135>, a=<1,-16,1>\n"
    "p=<-5306,-890,-2341>, v=<0,-12,-77>, a=<13,3,11>\n"
    "p=<1417,99,2452>, v=<-17,100,-149>, a=<-3,-8,4>\n"
    "p=<767,1374,3552>, v=<22,-16,-102>, a=<-4,-3,-3>\n"
    "p=<542,1874,377>, v=<44,16,-105>, a=<-5,-7,7>\n"
    "p=<708,1037,-4669>, v=<4,-13,96>, a=<-4,-4,15>\n"
    "p=<-1040,-1927,-3377>, v=<56,33,68>, a=<0,7,11>\n"
    "p=<2019,2519,1658>, v=<5,-21,-27>, a=<-11,-11,-6>\n"
    "p=<1582,467,-2541>, v=<-62,17,134>, a=<-2,-4,0>\n"
    "p=<-3491,1892,-3016>, v=<95,-98,69>, a=<9,0,9>\n"
    "p=<-3282,2785,2304>, v=<104,-65,-31>, a=<7,-8,-9>\n"
    "p=<-3529,-1072,917>, v=<77,68,-18>, a=<11,-1,-3>\n"
    "p=<-394,-1699,4071>, v=<112,11,-104>, a=<-9,8,-11>\n"
    "p=<-2883,2729,-570>, v=<137,-19,-84>, a=<0,-10,10>\n"
    "p=<-531,-2416,-1704>, v=<25,61,47>, a=<0,5,3>\n"
    "p=<3707,-2056,2383>, v=<-55,-22,-32>, a=<-6,7,-4>\n"
    "p=<-6769,4235,-3665>, v=<95,-73,-4>, a=<11,-6,10>\n"
    "p=<2060,779,-236>, v=<-64,-71,-61>, a=<-1,3,5>\n"
    "p=<2978,-5296,9052>, v=<70,112,-139>, a=<-13,6,-14>\n"
    "p=<5064,8105,8494>, v=<0,-14,-44>, a=<-8,-12,-11>\n"
    "p=<7059,-9045,-46>, v=<-93,134,38>, a=<-6,7,-2>\n"
    "p=<-326,-4145,5974>, v=<100,84,-26>, a=<-5,2,-8>\n"
    "p=<-1166,3310,5064>, v=<16,-75,-90>, a=<1,-1,-3>\n"
    "p=<-2819,-6760,-582>, v=<63,84,-103>, a=<3,12,9>\n"
    "p=<1366,-2413,1038>, v=<20,63,75>, a=<-5,2,-8>\n"
    "p=<1580,-377,3914>, v=<-86,29,-156>, a=<0,-1,-5>\n"
    "p=<-1156,-3094,-437>, v=<58,92,-17>, a=<0,7,4>\n"
    "p=<630,1219,-874>, v=<14,-5,-4>, a=<-5,-6,5>\n"
    "p=<1409,-2999,-1900>, v=<-97,67,60>, a=<2,9,4>\n"
    "p=<-1764,573,95>, v=<50,-11,95>, a=<4,-2,-10>\n"
    "p=<-1935,-719,-1596>, v=<69,47,124>, a=<3,-1,-4>\n"
    "p=<-5054,-3765,7287>, v=<58,132,-38>, a=<10,1,-18>\n"
    "p=<146,-1685,5350>, v=<-34,-2,-112>, a=<2,5,-7>\n"
    "p=<-5691,-216,709>, v=<-66,9,26>, a=<21,0,-4>\n"
    "p=<5294,3554,280>, v=<-124,-109,29>, a=<-6,-2,-3>\n"
    "p=<-3052,-1503,5909>, v=<116,-36,-66>, a=<0,7,-12>\n"
    "p=<1147,-1971,4882>, v=<-86,63,-148>, a=<3,1,-3>\n"
    "p=<3032,-476,-4660>, v=<-118,19,30>, a=<0,0,11>\n"
    "p=<6880,1747,-2710>, v=<-23,-53,36>, a=<-18,-1,5>\n"
    "p=<1916,1757,-626>, v=<20,-24,26>, a=<-8,-4,0>\n"
    "p=<-4756,1985,-1862>, v=<198,4,-35>, a=<0,-7,9>\n"
    "p=<-4768,125,-3782>, v=<-39,-6,-30>, a=<19,0,15>\n"
    "p=<-2812,-4279,730>, v=<-83,65,-18>, a=<16,9,-1>\n"
    "p=<6800,401,-2138>, v=<-171,20,-61>, a=<-9,-3,12>\n"
    "p=<-3604,-1987,406>, v=<150,-43,-17>, a=<0,10,0>\n"
    "p=<-784,-1015,-4082>, v=<20,129,-5>, a=<1,-7,14>\n"
    "p=<-1828,1757,-1286>, v=<-149,1,41>, a=<18,-6,1>\n"
    "p=<-239,3187,1315>, v=<-37,-97,-105>, a=<6,-12,3>\n"
    "p=<249,-1405,-1861>, v=<-8,105,102>, a=<-1,-2,2>\n"
    "p=<-327,-1629,475>, v=<79,0,75>, a=<-7,12,-12>\n"
    "p=<897,3,-2845>, v=<-108,0,138>, a=<6,0,5>\n"
    "p=<753,2179,299>, v=<105,-119,-67>, a=<-18,-2,6>\n"
    "p=<1721,843,-301>, v=<-15,-27,81>, a=<-11,-3,-7>\n"
    "p=<-5674,-5952,4901>, v=<129,78,-110>, a=<1,4,-1>\n"
    "p=<1793,-4546,1994>, v=<-48,2,25>, a=<0,6,-4>\n"
    "p=<-6833,5771,-267>, v=<-16,-16,-13>, a=<10,-7,1>\n"
    "p=<1033,5828,4160>, v=<-67,2,46>, a=<2,-8,-8>\n"
    "p=<3693,-383,1623>, v=<-118,-65,-194>, a=<-9,9,11>\n"
    "p=<345,-1148,-2598>, v=<-27,-70,12>, a=<1,14,14>\n"
    "p=<-546,922,1461>, v=<89,5,62>, a=<-6,-6,-15>\n"
    "p=<687,-3965,-744>, v=<-27,77,-34>, a=<-1,15,8>\n"
    "p=<-942,-2003,2514>, v=<16,63,-63>, a=<4,5,-8>\n"
    "p=<-60,2227,417>, v=<-14,-153,25>, a=<2,3,-5>\n"
    "p=<444,-554,588>, v=<-42,-65,-70>, a=<2,10,4>\n"
    "p=<-1806,-788,3000>, v=<64,5,-128>, a=<4,4,-4>\n"
    "p=<1677,-4028,-519>, v=<-63,166,20>, a=<-3,6,1>\n"
    "p=<786,535,-1968>, v=<72,-78,72>, a=<-12,5,4>\n"
    "p=<-1029,1045,-2896>, v=<2,11,154>, a=<4,-5,-2>\n"
    "p=<1336,935,173>, v=<-2,-30,95>, a=<-5,-1,-9>\n"
    "p=<4654,-1524,660>, v=<-44,72,-26>, a=<-10,-1,0>\n"
    "p=<-1625,1466,-2174>, v=<76,-70,-52>, a=<-1,1,10>\n"
    "p=<-1014,-6008,12961>, v=<46,59,-29>, a=<-1,5,-16>\n"
    "p=<2425,-403,1067>, v=<-64,9,-67>, a=<0,0,2>\n"
    "p=<11488,5278,-7236>, v=<-10,35,-63>, a=<-15,-9,13>\n"
    "p=<-197,-726,9313>, v=<-34,76,-11>, a=<2,-3,-12>\n"
    "p=<-4339,-707,10491>, v=<114,95,-120>, a=<0,-4,-8>\n"
    "p=<-4852,-4393,-7027>, v=<69,36,29>, a=<3,4,8>\n"
    "p=<-13193,-5001,326>, v=<35,52,50>, a=<16,4,-3>\n"
    "p=<10785,-7965,5475>, v=<-167,13,-27>, a=<-6,10,-6>\n"
    "p=<8087,-156,-9687>, v=<-57,-17,-18>, a=<-8,1,14>\n"
    "p=<5311,1364,-4493>, v=<-117,9,15>, a=<-5,-4,10>\n"
    "p=<-1535,4276,3711>, v=<55,-66,-133>, a=<0,-6,0>\n"
    "p=<-4307,-1380,967>, v=<-49,136,-180>, a=<14,-6,10>\n"
    "p=<4107,2988,-4843>, v=<-132,-20,-16>, a=<-1,-6,13>\n"
    "p=<-106,-18,-2952>, v=<-145,-18,24>, a=<15,2,13>\n"
    "p=<-1987,191,-2686>, v=<124,51,90>, a=<-2,-6,5>\n"
    "p=<1262,1236,601>, v=<13,-44,-43>, a=<-8,-2,1>\n"
    "p=<1224,932,4078>, v=<-65,-18,-96>, a=<0,-3,-12>\n"
    "p=<3143,400,-140>, v=<-6,50,-4>, a=<-16,-7,1>\n"
    "p=<4359,-1500,50>, v=<-110,140,-34>, a=<-12,-6,3>\n"
    "p=<-1265,1312,4268>, v=<-24,-38,-96>, a=<9,-3,-13>\n"
    "p=<768,2262,-1223>, v=<-11,-148,73>, a=<-3,3,-1>\n"
    "p=<3641,3799,-4840>, v=<-72,134,90>, a=<-2,-14,3>\n"
    "p=<-6321,-774,-1066>, v=<11,6,14>, a=<10,1,1>\n"
    "p=<-7902,3272,753>, v=<40,-8,83>, a=<11,-5,-6>\n"
    "p=<-7188,-3511,430>, v=<89,174,5>, a=<7,-4,-1>\n"
    "p=<224,10225,-3820>, v=<11,-55,-115>, a=<-1,-14,13>\n"
    "p=<-4434,-1318,685>, v=<-132,57,15>, a=<15,-1,-2>\n"
    "p=<513,-1845,6210>, v=<-50,-50,-25>, a=<2,6,-9>\n"
    "p=<694,4542,2375>, v=<-38,-120,-122>, a=<1,-1,3>\n"
    "p=<265,-7470,1022>, v=<60,74,72>, a=<-4,9,-6>\n"
    "p=<1948,3651,6995>, v=<9,-42,-41>, a=<-4,-4,-10>\n"
    "p=<-3596,-2652,3629>, v=<-10,47,-109>, a=<7,2,0>\n"
    "p=<6502,7941,3728>, v=<-61,-2,-61>, a=<-8,-14,-3>\n"
    "p=<-758,6357,-2278>, v=<40,97,-15>, a=<-1,-17,5>\n"
    "p=<-4949,-2916,2177>, v=<65,123,-99>, a=<5,-2,2>\n"
    "p=<3466,978,2705>, v=<14,-148,4>, a=<-7,7,-5>\n"
    "p=<-2870,-5655,3398>, v=<87,-83,-17>, a=<0,15,-5>\n"
    "p=<13201,879,4322>, v=<-94,-26,-45>, a=<-18,0,-5>\n"
    "p=<3501,2002,6330>, v=<-32,90,-115>, a=<-9,-14,-12>\n"
    "p=<-5835,634,3390>, v=<7,-28,-80>, a=<19,0,-5>\n"
    "p=<753,-710,-750>, v=<20,3,-95>, a=<-4,2,10>\n"
    "p=<3585,-4550,-5310>, v=<2,13,-5>, a=<-12,14,18>\n"
    "p=<-295,562,-8829>, v=<-15,-51,158>, a=<2,2,15>\n"
    "p=<1505,-1688,2896>, v=<17,-39,-25>, a=<-6,8,-7>\n"
    "p=<-3895,87,571>, v=<103,20,94>, a=<4,-2,-9>\n"
    "p=<2280,-1763,-29>, v=<-14,-23,27>, a=<-6,7,-2>\n"
    "p=<2755,-3738,-2429>, v=<-59,-22,97>, a=<-4,13,0>\n"
    "p=<-2095,-538,1746>, v=<83,45,-5>, a=<0,-2,-5>\n"
    "p=<-745,2712,-1629>, v=<-23,-137,65>, a=<4,2,0>\n"
    "p=<-5795,4862,6121>, v=<166,-67,-128>, a=<5,-10,-9>\n"
    "p=<-443,1290,2766>, v=<-35,-95,-104>, a=<9,0,-12>\n"
    "p=<369,-1041,57>, v=<-78,94,52>, a=<7,-3,-7>\n"
    "p=<607,-362,2850>, v=<-20,-37,-95>, a=<-3,8,-14>\n"
    "p=<-394,-621,-167>, v=<-46,4,8>, a=<10,5,1>\n"
    "p=<-1034,8022,2236>, v=<0,-51,-5>, a=<3,-19,-6>\n"
    "p=<1553,-714,1118>, v=<-32,-12,173>, a=<-2,3,-16>\n"
    "p=<-5129,-1871,1014>, v=<-18,46,-39>, a=<16,2,0>\n"
    "p=<1882,457,-2228>, v=<-4,-45,66>, a=<-21,2,15>\n"
    "p=<504,-1337,-2033>, v=<-10,16,156>, a=<-5,13,0>\n"
    "p=<-523,-310,2569>, v=<111,7,-142>, a=<-11,3,-8>\n"
    "p=<49,-401,918>, v=<46,-42,-15>, a=<-8,11,-8>\n"
    "p=<1193,-2689,1022>, v=<-28,204,-114>, a=<-10,1,5>\n"
    "p=<-1316,-1610,996>, v=<81,107,-7>, a=<2,3,-10>\n"
    "p=<283,704,-785>, v=<-84,20,74>, a=<8,-10,-2>\n"
    "p=<1037,-973,2465>, v=<-37,65,-106>, a=<-7,2,-12>\n"
    "p=<634,-102,-1396>, v=<-48,-16,58>, a=<-1,4,7>\n"
    "p=<-2343,327,1347>, v=<146,14,-97>, a=<4,-5,-1>\n"
    "p=<-5127,-1697,4261>, v=<-2,-1,-85>, a=<12,4,-4>\n"
    "p=<325,449,1216>, v=<-40,-75,-70>, a=<2,4,2>\n"
    "p=<-1676,8859,4638>, v=<14,-170,-68>, a=<3,-9,-6>\n"
    "p=<-168,-3437,6436>, v=<-53,134,-115>, a=<4,-1,-7>\n"
    "p=<-1647,-2770,7103>, v=<-17,6,-78>, a=<5,6,-11>\n"
    "p=<1224,1638,3942>, v=<49,-41,-194>, a=<-6,-1,4>\n"
    "p=<-3979,2255,-780>, v=<64,-8,82>, a=<13,-10,-4>\n"
    "p=<841,145,2690>, v=<12,-39,-102>, a=<-5,3,-3>\n"
    "p=<-809,-915,1420>, v=<42,-91,-49>, a=<0,13,-2>\n"
    "p=<-867,1058,-160>, v=<66,-15,-29>, a=<4,-17,8>\n"
    "p=<-637,1278,910>, v=<76,-103,-48>, a=<-2,-5,-8>\n"
    "p=<298,733,20>, v=<-1,-43,-14>, a=<-5,-6,2>\n"
    "p=<533,1753,-310>, v=<-8,-134,8>, a=<-8,-8,4>\n"
    "p=<-237,-147,670>, v=<91,-10,-13>, a=<-12,4,-10>\n"
    "p=<-387,468,-390>, v=<40,-44,-6>, a=<0,-1,8>\n"
    "p=<953,-462,440>, v=<-83,104,-89>, a=<-2,-11,8>\n"
    "p=<48,1553,-790>, v=<13,-92,155>, a=<-3,-12,-14>\n"
    "p=<-1696,991,-291>, v=<92,-10,47>, a=<3,-7,-4>\n"
    "p=<-2626,-389,-51>, v=<34,-14,-1>, a=<18,5,0>\n"
    "p=<1040,6169,4171>, v=<25,-212,-47>, a=<-3,2,-4>\n"
    "p=<-7955,-3491,-4509>, v=<84,46,21>, a=<8,3,6>\n"
    "p=<-3405,-1671,8441>, v=<8,-24,-115>, a=<5,4,-7>\n"
    "p=<-1340,9774,2036>, v=<39,-27,-22>, a=<0,-14,-2>\n"
    "p=<-4770,1129,-4754>, v=<137,-122,136>, a=<0,5,0>\n"
    "p=<1663,5742,172>, v=<-78,-157,62>, a=<1,-4,-5>\n"
    "p=<-497,1800,-2744>, v=<58,3,-12>, a=<-3,-5,8>\n"
    "p=<2041,-1089,793>, v=<-50,-44,-31>, a=<-2,6,0>\n"
    "p=<-4169,4311,-3338>, v=<82,-62,66>, a=<5,-7,4>\n"
    "p=<1285,-603,955>, v=<-22,22,-37>, a=<-2,0,0>\n"
    "p=<-6679,-38,-891>, v=<100,-88,25>, a=<5,5,0>\n"
    "p=<5221,-73,1839>, v=<-6,-33,37>, a=<-8,2,-5>\n"
    "p=<3576,-8998,-3621>, v=<-103,-12,-59>, a=<0,15,9>\n"
    "p=<-1219,-1753,10134>, v=<70,-93,-56>, a=<-2,8,-13>\n"
    "p=<-4824,2202,5234>, v=<-7,-26,30>, a=<8,-2,-10>\n"
    "p=<2701,-9488,-4426>, v=<-78,128,-18>, a=<0,8,8>\n"
    "p=<4451,5737,-2326>, v=<106,-55,66>, a=<-13,-6,0>\n"
    "p=<-8709,6997,1069>, v=<104,-1,-31>, a=<8,-11,0>\n"
    "p=<3984,2409,-2230>, v=<15,-90,16>, a=<-8,1,3>\n"
    "p=<-4926,-3597,-3451>, v=<13,58,-32>, a=<8,3,8>\n"
    "p=<1971,-1518,-3649>, v=<93,-5,59>, a=<-9,3,3>\n"
    "p=<1344,1584,-5167>, v=<78,-116,-31>, a=<-7,4,11>\n"
    "p=<948,-6567,-1372>, v=<22,46,24>, a=<-3,9,1>\n"
    "p=<-273,-330,7076>, v=<8,27,-96>, a=<0,-1,-7>\n"
    "p=<5865,7524,-6949>, v=<9,-7,142>, a=<-11,-13,4>\n"
    "p=<-2847,-2211,4040>, v=<-33,-103,-140>, a=<7,10,1>\n"
    "p=<-9381,4488,-4111>, v=<46,-17,-29>, a=<14,-7,9>\n"
    "p=<-5605,-5309,-5145>, v=<-34,109,-66>, a=<12,3,13>\n"
    "p=<4823,1390,-1086>, v=<24,25,83>, a=<-10,-4,-3>\n"
    "p=<-3988,268,-11811>, v=<53,-9,136>, a=<4,0,13>\n"
    "p=<1424,-8147,1521>, v=<-77,42,72>, a=<2,12,-7>\n"
    "p=<-2107,1885,-2505>, v=<-21,27,41>, a=<5,-5,2>\n"
    "p=<3340,-1280,4419>, v=<-11,59,-123>, a=<-7,-1,-2>\n"
    "p=<-1039,-7892,-3208>, v=<-25,77,65>, a=<4,13,3>\n"
    "p=<3949,4172,-1439>, v=<-137,-99,19>, a=<0,-3,2>\n"
    "p=<614,-1251,446>, v=<-22,43,-151>, a=<0,0,9>\n"
    "p=<2760,3273,-5354>, v=<54,7,109>, a=<-10,-8,5>\n"
    "p=<-3417,3331,-4629>, v=<117,-115,-6>, a=<0,0,11>\n"
    "p=<5,-1048,-975>, v=<-76,51,33>, a=<5,-1,0>\n"
    "p=<-3301,-5630,2708>, v=<38,59,56>, a=<5,9,-10>\n"
    "p=<-2750,-4151,7609>, v=<-11,38,-98>, a=<7,7,-11>\n"
    "p=<-1408,2242,-1675>, v=<54,-171,126>, a=<8,0,0>\n"
    "p=<-1512,1514,184>, v=<-1,-87,-52>, a=<17,-4,5>\n"
    "p=<399,331,67>, v=<-29,-38,34>, a=<0,2,-6>\n"
    "p=<1101,539,2173>, v=<-83,-40,-79>, a=<0,0,-13>\n"
    "p=<-667,-1554,-960>, v=<53,72,71>, a=<0,7,0>\n"
    "p=<3233,2151,-2091>, v=<-142,-94,158>, a=<-15,-10,0>\n"
    "p=<-628,1423,1523>, v=<113,-73,-43>, a=<-9,-5,-11>\n"
    "p=<906,2099,-180>, v=<-68,-104,-24>, a=<0,-8,5>\n"
    "p=<10374,2759,3961>, v=<-8,-150,-47>, a=<-17,4,-4>\n"
    "p=<-6677,-3701,-2125>, v=<56,110,62>, a=<8,0,0>\n"
    "p=<-6762,-845,3859>, v=<41,26,-44>, a=<9,0,-4>\n"
    "p=<-1271,294,5831>, v=<37,-25,-172>, a=<0,1,0>\n"
    "p=<3727,-2103,-5185>, v=<-5,98,82>, a=<-6,-2,4>\n"
    "p=<293,4068,-2176>, v=<166,-101,11>, a=<-10,-1,3>\n"
    "p=<-3481,-4789,-918>, v=<-38,142,-26>, a=<8,0,3>\n"
    "p=<-265,4681,-2828>, v=<14,-89,171>, a=<0,-14,-3>\n"
    "p=<-455,811,1822>, v=<97,-53,-93>, a=<-7,1,0>\n"
    "p=<975,-2299,602>, v=<36,71,10>, a=<-8,4,-4>\n"
    "p=<-371,367,361>, v=<26,-44,-33>, a=<2,1,-1>\n"
    "p=<-171,627,-424>, v=<17,-81,95>, a=<0,3,-10>\n"
    "p=<-901,222,-604>, v=<90,20,25>, a=<0,-8,6>\n"
    "p=<629,-403,-19>, v=<-85,55,38>, a=<4,-3,-7>\n"
    "p=<-381,652,-339>, v=<27,-45,59>, a=<2,-4,-5>\n"
    "p=<-971,1542,-779>, v=<97,-156,37>, a=<0,0,7>\n"
    "p=<1769,-168,-1114>, v=<-89,15,98>, a=<-16,0,2>\n"
    "p=<5277,8455,-4580>, v=<47,-116,112>, a=<-11,-7,1>\n"
    "p=<1637,-3935,-7310>, v=<-65,58,-80>, a=<1,3,16>\n"
    "p=<-10228,-4530,-5630>, v=<22,21,142>, a=<15,6,1>\n"
    "p=<-6308,3205,-13435>, v=<0,-92,167>, a=<10,0,12>\n"
    "p=<3842,-785,-2165>, v=<-20,22,79>, a=<-5,0,-1>\n"
    "p=<-5993,-2115,7530>, v=<-81,114,-36>, a=<14,-3,-10>\n"
    "p=<6642,-3900,4345>, v=<-136,-33,19>, a=<-3,8,-8>\n"
    "p=<-6413,1315,3400>, v=<-15,-38,28>, a=<11,0,-7>\n"
    "p=<1357,6915,2210>, v=<69,-18,-64>, a=<-6,-10,0>\n"
    "p=<-2699,4182,2636>, v=<167,-122,-21>, a=<-5,-2,-5>\n"
    "p=<1795,4280,788>, v=<50,5,45>, a=<-8,-11,-5>\n"
    "p=<1543,2054,-4406>, v=<-57,-17,13>, a=<0,-4,10>\n"
    "p=<4875,-3322,-1984>, v=<56,1,57>, a=<-16,8,1>\n"
    "p=<6737,-354,508>, v=<-54,11,-3>, a=<-13,0,-1>\n"
    "p=<2299,5806,-1970>, v=<-55,-93,71>, a=<-2,-8,0>\n"
    "p=<2971,1578,2048>, v=<-79,-116,0>, a=<-2,4,-5>\n"
    "p=<7507,-5366,4414>, v=<-96,16,17>, a=<-12,12,-12>\n"
    "p=<451,1018,18>, v=<11,-9,0>, a=<-2,-2,0>\n"
    "p=<4749,-2664,-2572>, v=<-70,-95,49>, a=<-7,13,3>\n"
    "p=<-603,-266,-842>, v=<35,-39,59>, a=<0,6,-1>\n"
    "p=<-1589,3372,3289>, v=<102,-208,-112>, a=<-1,1,-9>\n"
    "p=<-1776,516,-1148>, v=<104,-85,-4>, a=<0,6,8>\n"
    "p=<2236,2199,-1454>, v=<-114,-58,32>, a=<-2,-8,6>\n"
    "p=<-1079,142,3612>, v=<-27,90,-176>, a=<10,-11,-4>\n"
    "p=<536,-436,569>, v=<-32,25,21>, a=<0,0,-6>\n"
    "p=<1267,-96,671>, v=<-75,50,6>, a=<0,-5,-5>\n"
    "p=<4240,6035,-1297>, v=<190,-50,-3>, a=<-16,-6,2>\n"
    "p=<-2124,-847,-12915>, v=<1,-54,159>, a=<3,4,10>\n"
    "p=<-1125,6812,7213>, v=<-121,5,-100>, a=<8,-10,-5>\n"
    "p=<3611,1299,-4812>, v=<17,-17,111>, a=<-6,-1,1>\n"
    "p=<-8155,4185,-3702>, v=<12,38,-71>, a=<11,-8,9>\n"
    "p=<-3012,-1698,-3591>, v=<-51,121,59>, a=<7,-4,2>\n"
    "p=<-5972,-1402,11764>, v=<181,18,-109>, a=<-1,1,-11>\n"
    "p=<-4196,10364,-39>, v=<114,-91,-170>, a=<0,-10,9>\n"
    "p=<-5824,7330,5400>, v=<-13,-142,25>, a=<9,-3,-9>\n"
    "p=<-1976,1262,9359>, v=<35,22,-63>, a=<1,-3,-10>\n"
    "p=<3138,-3783,-513>, v=<37,83,-7>, a=<-11,4,2>\n"
    "p=<-372,2967,4212>, v=<13,-69,-28>, a=<0,-3,-9>\n"
    "p=<60,672,2322>, v=<39,16,-84>, a=<-3,-3,0>\n"
    "p=<937,1299,4314>, v=<0,65,10>, a=<-3,-9,-14>\n"
    "p=<2862,2199,4314>, v=<27,-49,-16>, a=<-11,-3,-12>\n"
    "p=<-1788,-2601,1339>, v=<70,52,-66>, a=<0,4,1>\n"
    "p=<-7413,1474,1214>, v=<35,-72,69>, a=<20,1,-9>\n"
    "p=<1562,-5926,-1586>, v=<53,120,77>, a=<-9,9,-1>\n"
    "p=<3387,-701,-436>, v=<19,41,-99>, a=<-12,-1,9>\n"
    "p=<1037,1299,2789>, v=<74,-117,19>, a=<-9,5,-10>\n"
    "p=<6887,1999,2264>, v=<-212,63,27>, a=<-5,-11,-9>\n"
    "p=<-2454,3908,4493>, v=<40,-41,-104>, a=<4,-8,-5>\n"
    "p=<-1414,138,-330>, v=<54,-58,-40>, a=<0,4,4>\n"
    "p=<-530,2764,1165>, v=<-7,-105,-138>, a=<2,0,7>\n"
    "p=<-2584,-4100,4194>, v=<99,78,29>, a=<0,6,-14>\n"
    "p=<4514,-5452,2088>, v=<15,49,2>, a=<-14,12,-6>\n"
    "p=<2369,1308,1542>, v=<-51,59,-31>, a=<-3,-8,-2>\n"
    "p=<783,-4581,-1370>, v=<37,110,135>, a=<-5,5,-6>\n"
    "p=<1477,-678,-914>, v=<1,-160,64>, a=<-5,15,-2>\n"
    "p=<-791,-366,-1370>, v=<33,-23,58>, a=<0,3,0>\n"
    "p=<-743,-750,-6386>, v=<-119,68,67>, a=<12,-3,16>\n"
    "p=<-23,-234,-2210>, v=<1,-91,-82>, a=<0,8,14>\n"
    "p=<5569,3198,862>, v=<-32,-34,-35>, a=<-16,-8,0>\n"
    "p=<1321,-2850,1738>, v=<-80,18,-59>, a=<2,8,-1>\n"
    "p=<-563,2046,2626>, v=<-64,39,-96>, a=<7,-10,-1>\n"
    "p=<-383,-5370,1438>, v=<66,98,-34>, a=<-4,10,-2>\n"
    "p=<3121,1139,-482>, v=<-84,-23,29>, a=<-11,-5,0>\n"
    "p=<-653,-1530,130>, v=<39,35,-34>, a=<0,6,3>\n"
    "p=<-5063,-11650,8566>, v=<86,28,3>, a=<3,16,-13>\n"
    "p=<-2561,-6700,4390>, v=<-113,57,-29>, a=<10,7,-5>\n"
    "p=<-977,-2254,3256>, v=<65,-11,-53>, a=<-2,4,-2>\n"
    "p=<-7434,6703,7006>, v=<50,-51,19>, a=<7,-6,-10>\n"
    "p=<-3300,8809,2170>, v=<-16,-65,-97>, a=<5,-8,2>\n"
    "p=<-7278,-3242,7708>, v=<66,44,-59>, a=<6,2,-7>\n"
    "p=<13158,-11588,-3485>, v=<-78,-2,148>, a=<-13,15,-3>\n"
    "p=<4695,-3515,4705>, v=<-61,51,-42>, a=<-3,2,-4>\n"
    "p=<2002,639,-1916>, v=<-111,-71,21>, a=<0,4,9>\n"
    "p=<-347,2052,1387>, v=<48,-7,-20>, a=<-3,-11,-6>\n"
    "p=<-770,-477,2323>, v=<81,67,-34>, a=<-4,-4,-10>\n"
    "p=<697,-1323,3682>, v=<-10,-19,-138>, a=<-3,10,-7>\n"
    "p=<1141,-1102,1582>, v=<-22,-40,-140>, a=<-8,16,4>\n"
    "p=<-1813,-934,-658>, v=<129,-67,35>, a=<0,18,2>\n"
    "p=<1001,592,1162>, v=<-42,-71,-5>, a=<-4,4,-10>\n"
    "p=<-189,-1165,-1456>, v=<28,47,62>, a=<-2,5,6>\n"
    "p=<-2793,277,-658>, v=<154,-56,-10>, a=<6,5,8>\n"
    "p=<-2843,830,-240>, v=<-412,119,-35>, a=<29,-12,0>\n"
    "p=<561,-879,2757>, v=<85,-126,396>, a=<-5,1,-27>\n"
    "p=<483,-2524,422>, v=<71,-362,65>, a=<-2,20,-4>\n"
    "p=<-2418,-1522,-852>, v=<-345,-217,-122>, a=<26,15,9>\n"
    "p=<92,-3025,215>, v=<13,-435,32>, a=<0,22,-2>\n"
    "p=<3087,-796,-1114>, v=<439,-116,-159>, a=<-33,10,13>\n"
    "p=<906,70,2639>, v=<129,6,379>, a=<-10,-5,-26>\n"
    "p=<-182,-50,2623>, v=<-27,-10,377>, a=<-3,-2,-26>\n"
    "p=<2507,221,1319>, v=<357,30,182>, a=<-25,2,-15>\n"
    "p=<-1120,-1672,1737>, v=<-163,-238,246>, a=<9,12,-17>\n"
    "p=<-1240,-2710,1243>, v=<-175,-384,177>, a=<13,22,-11>\n"
    "p=<-2314,2561,328>, v=<-330,367,40>, a=<27,-24,-3>\n"
    "p=<2371,-389,-1955>, v=<334,-56,-281>, a=<-20,3,21>\n"
    "p=<-434,-2848,-913>, v=<-67,-408,-130>, a=<-1,24,10>\n"
    "p=<2056,-1628,-1558>, v=<291,-235,-227>, a=<-22,21,15>\n"
    "p=<1053,2653,-1626>, v=<154,379,-227>, a=<-10,-26,13>\n"
    "p=<-2181,1285,-1166>, v=<-310,181,-162>, a=<20,-14,9>\n"
    "p=<-2189,-1315,-2270>, v=<-311,-188,-322>, a=<22,8,16>\n"
    "p=<-1086,-2194,1448>, v=<-158,-313,199>, a=<12,17,-18>\n"
    "p=<2885,-1247,1039>, v=<413,-177,151>, a=<-27,12,-10>\n"
    "p=<1593,2580,-1214>, v=<224,368,-176>, a=<-10,-25,12>\n"
    "p=<-446,-1930,-1797>, v=<-68,-278,-259>, a=<4,20,21>\n"
    "p=<642,2024,1663>, v=<92,292,242>, a=<-10,-17,-14>\n"
    "p=<1097,-2987,1234>, v=<157,-424,177>, a=<-10,28,-5>\n"
    "p=<-2374,-1019,1757>, v=<-335,-145,250>, a=<23,10,-17>\n"
    "p=<-712,1767,1196>, v=<-101,251,170>, a=<2,-18,-15>\n"
    "p=<-1122,1692,-1744>, v=<-164,246,-247>, a=<10,-19,21>\n"
    "p=<-1846,942,-2533>, v=<-260,137,-358>, a=<18,-8,22>\n"
    "p=<-1690,2012,785>, v=<-242,290,113>, a=<19,-24,-15>\n"
    "p=<1638,-2984,539>, v=<235,-426,81>, a=<-16,26,-8>\n"
    "p=<-2618,-1700,1297>, v=<-374,-247,185>, a=<29,15,-13>\n"
    "p=<2933,153,982>, v=<419,13,142>, a=<-29,2,-8>\n"
    "p=<2567,1801,491>, v=<366,257,73>, a=<-27,-16,-7>\n"
    "p=<1783,-924,1676>, v=<254,-134,239>, a=<-16,13,-18>\n"
    "p=<2029,-1462,-1914>, v=<283,-205,-274>, a=<-24,13,19>\n"
    "p=<1217,-1225,-2739>, v=<177,-180,-391>, a=<-12,11,25>\n"
    "p=<-2157,-342,1702>, v=<-309,-51,245>, a=<22,3,-17>\n"
    "p=<-2605,-432,628>, v=<-372,-61,87>, a=<28,4,-6>\n"
    "p=<160,698,-2721>, v=<22,99,-386>, a=<-1,-6,19>\n"
    "p=<895,2760,1095>, v=<127,397,157>, a=<-9,-29,-7>\n"
    "p=<-1993,-1733,-409>, v=<-284,-248,-60>, a=<23,24,3>\n"
    "p=<948,904,3052>, v=<133,124,434>, a=<-14,-14,-26>\n"
    "p=<3186,-1032,-896>, v=<453,-148,-126>, a=<-30,9,10>\n"
    "p=<-931,3471,56>, v=<-133,496,10>, a=<5,-34,-2>\n"
    "p=<3270,-206,-851>, v=<458,-27,-118>, a=<-30,0,8>\n"
    "p=<1531,-2061,1996>, v=<215,-296,283>, a=<-10,17,-19>\n"
    "p=<316,-1984,1728>, v=<46,-288,242>, a=<-3,24,-17>\n"
    "p=<-254,-748,-2958>, v=<-36,-109,-422>, a=<3,6,33>\n"
    "p=<132,-1586,-2317>, v=<22,-223,-326>, a=<1,18,18>\n"
    "p=<2073,-1463,-1932>, v=<294,-206,-278>, a=<-18,17,17>\n"
    "p=<-1089,-45,2877>, v=<-157,-5,412>, a=<11,-1,-32>\n"
    "p=<-410,2889,1122>, v=<-61,415,166>, a=<0,-23,-13>\n"
    "p=<654,-1230,-2552>, v=<93,-174,-365>, a=<-9,16,29>\n"
    "p=<-2106,-1937,768>, v=<-295,-275,109>, a=<18,18,-3>\n"
    "p=<2929,-725,-238>, v=<414,-104,-39>, a=<-26,7,1>\n"
    "p=<840,-2609,-1590>, v=<120,-372,-227>, a=<-8,24,18>\n"
    "p=<822,-2523,1355>, v=<118,-357,187>, a=<-11,29,-9>\n"
    "p=<1470,503,-2578>, v=<211,69,-370>, a=<-16,-10,27>\n"
    "p=<1786,121,1675>, v=<259,18,240>, a=<-14,-1,-16>\n"
    "p=<3009,198,1286>, v=<431,27,183>, a=<-30,-2,-8>\n"
    "p=<1298,-2606,-100>, v=<185,-378,-14>, a=<-10,27,-1>\n"
    "p=<906,536,2696>, v=<132,79,379>, a=<-9,-5,-32>\n"
    "p=<3302,481,743>, v=<473,63,102>, a=<-35,-5,-7>\n"
    "p=<175,-2676,1265>, v=<25,-381,184>, a=<-1,22,-13>\n"
    "p=<-1819,196,2632>, v=<-260,31,377>, a=<16,-8,-26>\n"
    "p=<2983,-1160,-333>, v=<426,-170,-50>, a=<-32,12,6>\n"
    "p=<-15,2565,99>, v=<-7,367,14>, a=<-1,-29,-5>\n"
    "p=<661,-2416,1867>, v=<94,-345,268>, a=<-7,16,-18>\n"
    "p=<77,39,3045>, v=<13,4,435>, a=<4,5,-34>\n"
    "p=<820,-2014,843>, v=<117,-287,123>, a=<-4,18,-8>\n"
    "p=<-2569,-1447,-432>, v=<-366,-210,-60>, a=<25,13,4>\n"
    "p=<2156,-1773,-510>, v=<305,-257,-73>, a=<-19,16,0>\n"
    "p=<-2188,939,-1>, v=<-312,135,-1>, a=<23,-7,1>\n"
    "p=<-2478,1649,1401>, v=<-354,237,193>, a=<26,-18,-13>\n"
    "p=<-2228,2035,69>, v=<-313,290,5>, a=<25,-24,5>\n"
    "p=<-1167,2674,33>, v=<-163,380,2>, a=<10,-26,7>\n"
    "p=<-2810,737,-14>, v=<-401,103,-4>, a=<30,-7,-5>\n"
    "p=<-2518,-1475,1125>, v=<-353,-211,160>, a=<25,16,-14>\n"
    "p=<2866,-596,-822>, v=<407,-89,-119>, a=<-28,5,5>\n"
    "p=<66,1045,2622>, v=<11,146,370>, a=<-1,-10,-28>\n"
    "p=<-1326,1976,2227>, v=<-189,284,320>, a=<13,-19,-19>\n"
    "p=<199,-2682,-889>, v=<25,-382,-127>, a=<1,23,7>\n"
    "p=<-1703,293,-2055>, v=<-244,43,-290>, a=<19,-2,23>\n"
    "p=<-1725,984,2303>, v=<-247,140,329>, a=<18,-9,-21>\n"
    "p=<-2376,539,-2230>, v=<-339,73,-317>, a=<25,-6,22>\n"
    "p=<-1178,-534,-2732>, v=<-171,-76,-390>, a=<13,3,29>\n"
    "p=<-1745,-2288,426>, v=<-252,-327,60>, a=<12,24,0>\n"
    "p=<-2811,-1675,538>, v=<-402,-238,81>, a=<30,19,-5>\n"
    "p=<-948,-775,3082>, v=<-135,-110,441>, a=<9,13,-30>\n"
    "p=<549,1427,-2381>, v=<76,203,-346>, a=<-5,-15,20>\n"
    "p=<-210,2385,-1528>, v=<-27,340,-212>, a=<-1,-23,16>\n"
    "p=<3012,1221,-262>, v=<431,179,-36>, a=<-23,-12,3>\n"
    "p=<2163,2316,561>, v=<313,329,80>, a=<-16,-25,-9>\n"
    "p=<1858,1047,-2395>, v=<265,150,-344>, a=<-17,-15,24>\n"
    "p=<-1322,-391,-2833>, v=<-189,-53,-409>, a=<16,6,24>\n"
    "p=<-975,-2214,-2230>, v=<-133,-318,-318>, a=<9,17,21>\n"
    "p=<-1172,2355,1378>, v=<-170,338,198>, a=<14,-32,-18>\n"
    "p=<1778,874,-1604>, v=<256,126,-227>, a=<-21,-8,19>\n"
    "p=<1579,811,2590>, v=<219,116,374>, a=<-15,-12,-21>\n"
    "p=<-1518,-2441,1048>, v=<-216,-348,152>, a=<9,23,-10>\n"
    "p=<2204,1505,1740>, v=<315,215,250>, a=<-20,-13,-16>\n"
    "p=<-1723,-2674,890>, v=<-246,-385,127>, a=<13,27,-7>\n"
    "p=<-806,1341,1967>, v=<-114,197,283>, a=<11,-17,-18>\n"
    "p=<466,19,3093>, v=<66,2,440>, a=<-9,0,-30>\n"
    "p=<-710,-2201,-2248>, v=<-101,-317,-323>, a=<8,24,18>\n"
    "p=<3052,-96,123>, v=<436,-11,17>, a=<-26,-4,3>\n"
    "p=<2058,535,1117>, v=<296,75,164>, a=<-21,-4,-11>\n"
    "p=<2233,1477,1314>, v=<311,213,186>, a=<-23,-8,-17>\n"
    "p=<2060,-63,2115>, v=<290,-12,299>, a=<-19,-3,-14>\n"
    "p=<-503,2332,-1873>, v=<-79,335,-272>, a=<6,-28,20>\n"
    "p=<2393,-340,-1098>, v=<344,-48,-153>, a=<-21,3,10>\n"
    "p=<-2547,1377,1267>, v=<-364,200,182>, a=<28,-15,-14>\n"
    "p=<-1034,2302,-1172>, v=<-149,332,-161>, a=<12,-22,13>\n"
    "p=<-2776,-104,-523>, v=<-399,-16,-73>, a=<29,0,1>\n"
    "p=<1771,1362,-2101>, v=<250,192,-299>, a=<-20,-7,21>\n"
    "p=<2975,-496,-1298>, v=<420,-73,-184>, a=<-34,7,8>\n"
    "p=<-750,-2930,895>, v=<-105,-420,127>, a=<4,27,-8>\n"
    "p=<2358,-515,2215>, v=<332,-79,316>, a=<-21,1,-20>\n"
    "p=<1896,1218,-1722>, v=<266,171,-248>, a=<-18,-17,22>\n"
    "p=<-2787,-585,-1023>, v=<-403,-86,-149>, a=<20,1,6>\n"
    "p=<1006,-2944,-75>, v=<145,-420,-9>, a=<-10,28,2>\n"
    "p=<2223,-2611,211>, v=<316,-373,28>, a=<-22,24,4>\n"
    "p=<-3237,622,-127>, v=<-460,88,-21>, a=<32,-4,0>\n"
    "p=<2468,940,809>, v=<352,133,114>, a=<-23,-7,-14>\n"
    "p=<745,2723,-1771>, v=<104,387,-253>, a=<-7,-27,11>\n"
    "p=<3079,954,-475>, v=<441,134,-65>, a=<-32,-9,6>\n"
    "p=<2898,-724,1296>, v=<415,-103,188>, a=<-28,12,-17>\n"
    "p=<-1534,-2251,2106>, v=<-219,-323,300>, a=<18,24,-22>\n"
    "p=<1118,-1993,2096>, v=<164,-284,297>, a=<-10,21,-23>\n"
    "p=<-980,2460,-919>, v=<-138,353,-127>, a=<7,-21,9>\n"
    "p=<-1579,837,-3110>, v=<-225,114,-444>, a=<14,-8,27>\n"
    "p=<1206,-2091,1026>, v=<172,-296,143>, a=<-10,18,-8>\n"
    "p=<3433,-601,-719>, v=<487,-87,-104>, a=<-35,8,7>\n"
    "p=<725,-490,2434>, v=<98,-68,345>, a=<0,4,-22>\n"
    "p=<366,3042,837>, v=<48,428,120>, a=<-1,-28,-6>\n"
    "p=<-1110,-981,-2006>, v=<-165,-135,-286>, a=<11,9,18>\n"
    "p=<-1837,-666,-2584>, v=<-266,-94,-369>, a=<13,5,24>\n"
    "p=<-1223,-2493,1004>, v=<-174,-359,141>, a=<13,22,-9>\n"
    "p=<-282,-1529,2340>, v=<-40,-217,339>, a=<3,17,-23>\n"
    "p=<-1740,-2697,-232>, v=<-248,-384,-27>, a=<13,25,2>\n"
    "p=<-489,2888,-479>, v=<-67,413,-69>, a=<5,-28,5>\n"
    "p=<2864,-1237,-1254>, v=<414,-176,-181>, a=<-28,12,10>\n"
    "p=<-1263,-861,2591>, v=<-177,-124,376>, a=<11,7,-25>\n"
    "p=<1578,-1602,2035>, v=<227,-228,288>, a=<-12,20,-22>\n"
    "p=<1470,-2535,214>, v=<213,-361,27>, a=<-10,25,1>\n"
    "p=<-779,2562,764>, v=<-112,365,108>, a=<9,-20,-7>\n"
    "p=<2406,-243,2005>, v=<346,-31,286>, a=<-23,2,-20>\n"
    "p=<1682,382,1836>, v=<246,57,265>, a=<-16,-3,-16>\n"
    "p=<558,-2913,351>, v=<77,-416,47>, a=<-1,31,-4>\n"
    "p=<2737,-217,1442>, v=<395,-31,205>, a=<-25,2,-11>\n"
    "p=<2643,903,1168>, v=<382,131,166>, a=<-28,-9,-9>\n"
    "p=<-1097,-1662,-1197>, v=<-157,-232,-176>, a=<6,10,8>\n"
    "p=<2154,-1785,-1040>, v=<305,-253,-148>, a=<-21,16,11>\n"
    "p=<-1577,-502,2281>, v=<-223,-76,323>, a=<18,5,-23>\n"
    "p=<150,-2685,531>, v=<24,-383,76>, a=<-5,29,1>\n"
    "p=<1830,-2571,319>, v=<261,-367,44>, a=<-19,26,-4>\n"
    "p=<631,2434,-302>, v=<88,349,-46>, a=<-2,-24,0>\n"
    "p=<-1816,-2338,-1168>, v=<-262,-334,-165>, a=<17,18,13>\n"
    "p=<-1291,-189,-2567>, v=<-183,-27,-366>, a=<12,7,27>\n"
    "p=<2577,1399,469>, v=<368,197,68>, a=<-23,-7,0>\n"
    "p=<-281,3177,325>, v=<-36,453,46>, a=<2,-33,-3>\n"
    "p=<-1386,-353,2531>, v=<-204,-48,368>, a=<15,7,-20>\n"
    "p=<700,2432,-1803>, v=<100,347,-257>, a=<-10,-27,21>\n"
    "p=<-1191,-2167,318>, v=<-172,-311,46>, a=<4,21,1>\n"
    "p=<1235,1073,2522>, v=<178,158,361>, a=<-12,-13,-26>\n"
    "p=<3009,-18,-1884>, v=<425,-3,-269>, a=<-29,-1,20>\n"
    "p=<1775,-1388,-1149>, v=<253,-204,-164>, a=<-15,13,11>\n"
    "p=<-2724,644,37>, v=<-388,92,6>, a=<27,-2,7>\n"
    "p=<652,1410,2373>, v=<91,204,334>, a=<-9,-20,-21>\n"
    "p=<-680,-2082,2558>, v=<-97,-299,363>, a=<11,16,-25>\n"
    "p=<-2404,-1258,1398>, v=<-344,-180,201>, a=<27,13,-12>\n"
    "p=<-2003,440,1820>, v=<-290,62,264>, a=<18,-3,-20>\n"
    "p=<2337,-947,-1272>, v=<333,-137,-184>, a=<-23,9,11>\n"
    "p=<1364,-2612,-1713>, v=<200,-372,-246>, a=<-14,29,22>\n"
    "p=<795,-2582,895>, v=<115,-362,129>, a=<-11,22,-1>\n"
    "p=<-517,984,-2530>, v=<-77,135,-357>, a=<8,-3,25>\n"
    "p=<-668,-2394,992>, v=<-95,-340,141>, a=<7,20,-11>\n"
    "p=<-744,1390,-1984>, v=<-107,203,-288>, a=<2,-15,23>\n"
    "p=<3337,-1467,-429>, v=<471,-209,-63>, a=<-33,15,13>\n"
    "p=<-585,2326,1872>, v=<-79,332,269>, a=<1,-22,-19>\n"
    "p=<2001,-1110,1636>, v=<288,-153,229>, a=<-15,9,-12>\n"
    "p=<-682,1455,-2671>, v=<-101,207,-379>, a=<6,-19,27>\n"
    "p=<-1068,-2223,-1617>, v=<-146,-313,-232>, a=<11,20,17>\n"
    "p=<6,-794,-2839>, v=<1,-117,-402>, a=<0,10,22>\n"
    "p=<-1163,2809,-121>, v=<-168,402,-18>, a=<11,-31,1>\n"
    "p=<-1962,2406,724>, v=<-283,341,101>, a=<16,-23,-3>\n"
    "p=<508,-3140,633>, v=<72,-449,92>, a=<-4,26,-6>\n"
    "p=<1008,-2458,1931>, v=<145,-351,273>, a=<-10,23,-20>\n"
    "p=<-1239,-283,-2424>, v=<-172,-44,-347>, a=<12,-3,22>\n"
    "p=<391,-2979,-414>, v=<53,-426,-58>, a=<-9,28,4>\n"
    "p=<2090,-394,-1342>, v=<301,-58,-192>, a=<-22,3,16>\n"
    "p=<1999,1243,-1580>, v=<286,180,-224>, a=<-17,-11,15>\n"
    "p=<-216,-1168,3369>, v=<-27,-165,484>, a=<7,9,-38>\n"
    "p=<1742,-1711,1487>, v=<246,-249,208>, a=<-13,14,-14>\n"
    "p=<-2451,-229,314>, v=<-350,-34,46>, a=<20,2,-4>\n"
    "p=<305,-2475,1423>, v=<44,-355,202>, a=<-4,24,-15>\n"
    "p=<-3194,-544,371>, v=<-453,-77,53>, a=<33,8,1>\n"
    "p=<894,-1024,2681>, v=<127,-146,377>, a=<-8,13,-25>\n"
    "p=<-1218,642,2875>, v=<-170,91,409>, a=<10,-6,-27>\n"
    "p=<217,2300,576>, v=<30,326,79>, a=<-5,-23,-5>\n"
    "p=<1685,2321,494>, v=<240,329,68>, a=<-16,-25,1>\n"
    "p=<1194,1893,-2627>, v=<170,273,-380>, a=<-11,-18,26>\n"
    "p=<3427,-161,-785>, v=<490,-20,-110>, a=<-28,1,4>\n"
    "p=<-1457,-2725,663>, v=<-212,-389,92>, a=<15,26,-5>\n"
    "p=<-623,-2456,-677>, v=<-89,-353,-97>, a=<6,24,6>\n"
    "p=<-2003,262,-1900>, v=<-291,36,-275>, a=<15,-2,23>\n"
    "p=<2152,-1487,-889>, v=<307,-213,-127>, a=<-24,14,10>\n"
    "p=<2596,-1310,-825>, v=<370,-183,-114>, a=<-22,12,11>\n"
    "p=<-1268,2212,1195>, v=<-185,313,170>, a=<6,-21,-11>\n"
    "p=<-550,2547,-736>, v=<-78,363,-105>, a=<2,-27,9>\n"
    "p=<-1114,333,-2308>, v=<-166,46,-327>, a=<11,-4,23>\n"
    "p=<-1573,1832,-401>, v=<-224,264,-59>, a=<13,-17,7>\n"
    "p=<1133,868,-2422>, v=<163,130,-345>, a=<-12,-10,24>\n"
    "p=<1594,2314,-923>, v=<225,329,-131>, a=<-13,-23,7>\n"
    "p=<438,2775,-25>, v=<64,398,-1>, a=<1,-27,2>\n"
    "p=<313,-2694,-317>, v=<45,-383,-47>, a=<-1,27,3>\n"
    "p=<1577,-786,-2102>, v=<229,-113,-305>, a=<-11,4,23>\n"
    "p=<-2823,-794,-278>, v=<-407,-115,-34>, a=<29,8,3>\n"
    "p=<-719,-1430,2220>, v=<-103,-205,318>, a=<9,14,-17>\n"
    "p=<-315,2344,2368>, v=<-41,332,334>, a=<4,-21,-24>\n"
    "p=<1641,1093,-2327>, v=<229,159,-331>, a=<-19,-9,20>\n"
    "p=<-948,-825,2651>, v=<-134,-112,379>, a=<8,9,-27>\n"
    "p=<271,-758,-2783>, v=<40,-108,-392>, a=<-2,3,28>\n"
    "p=<2603,-270,-1799>, v=<371,-37,-260>, a=<-26,2,20>\n"
    "p=<1294,3159,-110>, v=<184,450,-12>, a=<-10,-31,-2>\n"
    "p=<-20,3020,548>, v=<1,426,75>, a=<-2,-26,-4>\n"
    "p=<560,1186,-2831>, v=<76,172,-409>, a=<-4,-14,26>\n"
    "p=<-2338,915,2315>, v=<-333,128,330>, a=<27,-9,-20>\n"
    "p=<-1694,-2185,-728>, v=<-239,-314,-104>, a=<17,19,9>\n"
    "p=<2313,272,1427>, v=<324,38,206>, a=<-25,-3,-15>\n"
    "p=<411,2384,918>, v=<60,335,129>, a=<-9,-23,-10>\n"
    "p=<2342,933,-1901>, v=<335,134,-271>, a=<-22,-10,27>\n"
    "p=<2206,498,-921>, v=<313,75,-131>, a=<-23,-8,9>\n"
    "p=<-1438,-2211,1044>, v=<-204,-313,142>, a=<15,25,-8>\n"
    "p=<-631,-2348,956>, v=<-87,-338,139>, a=<6,33,-12>\n"
    "p=<-1194,-2558,-576>, v=<-172,-366,-77>, a=<10,29,2>\n"
    "p=<1204,-3261,-154>, v=<176,-465,-25>, a=<-12,34,1>\n"
    "p=<1022,-2003,-2357>, v=<146,-283,-337>, a=<-18,17,25>\n"
    "p=<369,-43,-3329>, v=<46,-1,-477>, a=<1,0,33>\n"
    "p=<734,-2281,1529>, v=<103,-327,217>, a=<-10,22,-16>\n"
    "p=<1929,-2250,577>, v=<278,-320,80>, a=<-17,27,-8>\n"
    "p=<2462,788,-1145>, v=<352,110,-158>, a=<-21,-7,12>\n"
    "p=<-2112,1442,1144>, v=<-301,206,159>, a=<23,-14,-8>\n"
    "p=<-536,262,2755>, v=<-78,38,393>, a=<5,1,-23>\n"
    "p=<2621,-94,-1415>, v=<374,-11,-204>, a=<-27,0,10>\n"
    "p=<-775,391,2918>, v=<-110,55,413>, a=<4,-2,-27>\n"
    "p=<2716,392,1401>, v=<387,53,204>, a=<-33,-2,-14>\n"
    "p=<-2469,747,1452>, v=<-346,106,205>, a=<29,-8,-17>\n"
    "p=<-39,-451,-2707>, v=<-4,-72,-388>, a=<3,3,21>\n"
    "p=<-347,2381,-1062>, v=<-51,341,-144>, a=<3,-25,11>\n"
    "p=<-347,338,2665>, v=<-54,52,377>, a=<-1,-3,-23>\n"
    "p=<1079,1614,1775>, v=<158,229,249>, a=<-11,-16,-15>\n"
    "p=<1087,-2561,-354>, v=<155,-364,-50>, a=<-11,28,3>\n"
    "p=<2108,-579,-1619>, v=<298,-81,-228>, a=<-22,4,19>\n"
    "p=<939,-1919,-1931>, v=<134,-274,-268>, a=<-12,21,18>\n"
    "p=<876,-422,2874>, v=<125,-60,405>, a=<-9,4,-26>\n"
    "p=<1336,-2226,30>, v=<189,-323,4>, a=<-20,22,-2>\n"
    "p=<112,2882,1381>, v=<16,411,196>, a=<1,-21,-8>\n"
    "p=<-2344,-1273,-1683>, v=<-337,-187,-247>, a=<17,14,16>\n"
    "p=<-1653,791,-1953>, v=<-235,113,-281>, a=<17,-15,20>\n"
    "p=<-1611,1089,-1658>, v=<-230,155,-233>, a=<22,-10,20>\n"
    "p=<1997,-806,2740>, v=<284,-119,391>, a=<-17,8,-25>\n"
    "p=<938,725,2467>, v=<133,105,354>, a=<-15,-10,-27>\n"
    "p=<-322,2612,-813>, v=<-45,374,-115>, a=<3,-21,10>\n"
    "p=<-361,3022,628>, v=<-53,435,88>, a=<5,-29,-3>\n"
    "p=<1247,3103,119>, v=<184,447,22>, a=<-14,-31,6>\n"
    "p=<805,2161,-1401>, v=<115,307,-200>, a=<-7,-20,17>\n"
    "p=<1346,-670,-2502>, v=<196,-100,-358>, a=<-11,5,25>\n"
    "p=<-3002,-1297,-584>, v=<-433,-187,-88>, a=<31,15,5>\n"
    "p=<-1818,-2086,-236>, v=<-261,-299,-29>, a=<14,21,4>\n"
    "p=<-2404,-4,1476>, v=<-341,4,208>, a=<18,6,-18>\n"
    "p=<714,-641,2405>, v=<102,-89,342>, a=<-7,7,-26>\n"
    "p=<-1841,-1778,1081>, v=<-266,-255,158>, a=<16,18,-11>\n"
    "p=<-1468,-2708,-1426>, v=<-206,-386,-203>, a=<16,24,14>\n"
    "p=<1190,-400,-2780>, v=<170,-56,-397>, a=<-8,4,27>\n"
    "p=<1169,358,-3175>, v=<169,54,-448>, a=<-12,-4,27>\n"
    "p=<1242,1422,2719>, v=<176,200,387>, a=<-14,-14,-27>\n"
    "p=<-971,2621,-632>, v=<-136,380,-94>, a=<9,-25,9>\n"
    "p=<-568,-1638,2455>, v=<-82,-235,347>, a=<6,10,-28>\n"
    "p=<449,2705,-1749>, v=<64,390,-250>, a=<-4,-26,22>\n"
    "p=<1935,-1854,-1853>, v=<273,-266,-264>, a=<-21,16,16>\n"
    "p=<-733,-1101,-2582>, v=<-104,-154,-361>, a=<8,10,27>\n"
    "p=<2409,897,-1330>, v=<343,133,-189>, a=<-30,-8,11>\n"
    "p=<2572,-1490,55>, v=<370,-211,11>, a=<-21,16,4>\n"
    "p=<-2652,1556,-311>, v=<-379,225,-47>, a=<28,-15,1>\n"
    "p=<-366,-3076,62>, v=<-50,-439,10>, a=<1,29,-1>\n"
    "p=<1091,-852,2463>, v=<155,-122,356>, a=<-6,7,-27>\n"
    "p=<2155,-1659,-1501>, v=<307,-237,-212>, a=<-23,17,17>\n"
    "p=<-2627,-1109,-35>, v=<-379,-159,-2>, a=<26,14,2>\n"
    "p=<1097,1981,1025>, v=<156,279,150>, a=<-11,-19,-13>\n"
    "p=<-858,-2848,352>, v=<-121,-405,50>, a=<3,30,0>\n"
    "p=<1971,-1579,-88>, v=<283,-225,-13>, a=<-20,19,-3>\n"
    "p=<-2270,-1167,1002>, v=<-321,-170,137>, a=<17,6,-10>\n"
    "p=<-1122,-2278,1688>, v=<-160,-327,236>, a=<11,28,-16>\n"
    "p=<-2056,-2050,708>, v=<-295,-292,96>, a=<21,19,-7>\n"
    "p=<-1732,1237,1528>, v=<-250,172,221>, a=<18,-15,-13>\n"
    "p=<1,2845,383>, v=<0,407,51>, a=<-3,-26,5>\n"
    "p=<-725,2529,1838>, v=<-102,362,267>, a=<11,-28,-16>\n"
    "p=<-163,1266,-2778>, v=<-29,175,-399>, a=<0,-18,32>\n"
    "p=<2654,-1564,-875>, v=<375,-225,-125>, a=<-26,14,12>\n"
    "p=<-1683,2693,44>, v=<-244,384,4>, a=<19,-27,3>\n"
    "p=<319,1024,-3061>, v=<48,145,-438>, a=<-3,-3,30>\n"
    "p=<37,591,2588>, v=<2,87,368>, a=<-7,-5,-25>\n"
    "p=<2948,-255,-312>, v=<420,-39,-43>, a=<-27,1,-2>\n"
    "p=<669,-3210,-843>, v=<95,-456,-118>, a=<-7,32,9>\n"
    "p=<-2679,-1175,570>, v=<-381,-166,81>, a=<26,5,0>\n"
    "p=<-262,-2313,-2190>, v=<-33,-336,-313>, a=<2,21,22>\n"
    "p=<-463,2377,1405>, v=<-67,343,200>, a=<2,-23,-14>\n"
    "p=<-565,346,-3384>, v=<-82,50,-483>, a=<9,-5,30>\n"
    "p=<2690,-957,-1541>, v=<384,-136,-219>, a=<-25,13,12>\n"
    "p=<-1562,-1725,-1170>, v=<-223,-248,-171>, a=<16,12,9>\n"
    "p=<-671,1922,-2094>, v=<-90,271,-298>, a=<4,-25,19>\n"
    "p=<601,-782,-2192>, v=<88,-109,-319>, a=<-9,11,25>\n"
    "p=<2089,213,2124>, v=<301,28,299>, a=<-22,-5,-19>\n"
    "p=<2071,-1475,-1553>, v=<296,-211,-222>, a=<-18,19,14>\n"
    "p=<-1118,-2581,385>, v=<-158,-365,58>, a=<13,28,-3>\n"
    "p=<-2703,1488,-1211>, v=<-385,211,-170>, a=<30,-14,12>\n"
    "p=<1254,-2771,-1270>, v=<183,-392,-179>, a=<-12,27,11>\n"
    "p=<1645,-37,2489>, v=<235,-10,359>, a=<-18,0,-24>\n"
    "p=<1244,-1510,2257>, v=<176,-216,322>, a=<-10,17,-24>\n"
    "p=<670,-2299,-1847>, v=<94,-324,-265>, a=<-3,24,14>\n"
    "p=<-2186,1337,-464>, v=<-312,190,-66>, a=<26,-13,-1>\n"
    "p=<-2376,518,1603>, v=<-337,78,232>, a=<23,-5,-16>\n"
    "p=<-1732,-1782,-719>, v=<-245,-253,-101>, a=<14,15,8>\n"
    "p=<-724,1296,2446>, v=<-104,179,350>, a=<2,-12,-29>\n"
    "p=<-106,-734,3156>, v=<-12,-104,449>, a=<1,9,-29>\n"
    "p=<-234,-483,2732>, v=<-33,-69,386>, a=<2,4,-27>\n"
    "p=<-2392,627,-946>, v=<-339,88,-138>, a=<24,-5,17>\n"
    "p=<-897,-2959,-28>, v=<-131,-423,-2>, a=<5,27,0>\n"
    "p=<-2450,669,1113>, v=<-350,92,155>, a=<24,-9,-9>\n"
    "p=<3115,-194,-2220>, v=<445,-34,-321>, a=<-34,3,25>\n"
    "p=<-2648,-173,2094>, v=<-379,-25,301>, a=<28,5,-22>\n"
    "p=<-2165,-2445,-1136>, v=<-312,-345,-159>, a=<21,27,11>\n"
    "p=<-135,2066,-2142>, v=<-16,301,-309>, a=<-2,-15,21>\n"
    "p=<-2238,849,1298>, v=<-316,121,185>, a=<21,-4,-12>\n"
    "p=<1816,1490,1927>, v=<258,210,276>, a=<-16,-9,-19>\n"
    "p=<-369,1776,2283>, v=<-53,252,327>, a=<-3,-20,-22>\n"
    "p=<966,-109,3164>, v=<136,-15,450>, a=<-4,1,-32>\n"
    "p=<-1343,2610,857>, v=<-196,373,122>, a=<18,-28,-8>\n"
    "p=<2278,433,1258>, v=<323,65,176>, a=<-19,-1,-9>\n"
    "p=<-12,-1176,-2612>, v=<5,-164,-370>, a=<7,11,27>\n"
    "p=<-1832,466,-2493>, v=<-258,69,-359>, a=<19,-2,26>\n"
    "p=<-467,-1328,-2855>, v=<-69,-189,-407>, a=<4,13,29>\n"
    "p=<2212,1669,1865>, v=<312,240,269>, a=<-21,-18,-21>\n"
    "p=<2524,226,-1722>, v=<360,25,-246>, a=<-25,-1,17>\n"
    "p=<-2231,1435,41>, v=<-320,201,7>, a=<24,-8,-3>\n"
    "p=<1438,1133,2111>, v=<205,161,302>, a=<-17,-11,-20>\n"
    "p=<-790,-2028,-1901>, v=<-108,-286,-273>, a=<7,21,22>\n"
    "p=<-2086,1223,-1266>, v=<-298,177,-184>, a=<22,-14,13>\n"
    "p=<2143,1649,-73>, v=<311,234,-13>, a=<-21,-16,-8>\n"
    "p=<-1352,95,-2543>, v=<-192,13,-364>, a=<20,0,25>\n"
    "p=<144,2836,649>, v=<26,404,88>, a=<-4,-28,-6>\n"
    "p=<-2315,-381,-2313>, v=<-332,-54,-331>, a=<23,0,18>\n"
    "p=<2488,194,-1630>, v=<355,27,-236>, a=<-26,4,16>\n"
    "p=<-224,2463,818>, v=<-33,350,116>, a=<2,-25,-11>\n"
    "p=<-2147,-591,-1463>, v=<-306,-87,-206>, a=<17,2,14>\n"
    "p=<1819,1038,3201>, v=<260,146,457>, a=<-18,-6,-29>\n"
    "p=<1846,2232,-565>, v=<265,318,-74>, a=<-14,-22,4>\n"
    "p=<-1274,1967,-1751>, v=<-189,279,-247>, a=<12,-23,23>\n"
    "p=<-2829,1586,554>, v=<-403,221,76>, a=<26,-18,-5>\n"
    "p=<-691,2884,1024>, v=<-97,414,148>, a=<9,-30,-9>\n"
    "p=<40,-3158,579>, v=<4,-451,79>, a=<-2,31,-3>\n"
    "p=<14,-590,2904>, v=<2,-89,410>, a=<2,3,-28>\n"
    "p=<-1640,288,2031>, v=<-229,39,292>, a=<20,0,-20>\n"
    "p=<-2111,-22,822>, v=<-303,0,120>, a=<21,-3,-7>\n"
    "p=<1175,2311,-311>, v=<169,330,-46>, a=<-11,-20,2>\n"
    "p=<563,2848,-398>, v=<80,405,-55>, a=<-9,-32,3>\n"
    "p=<2943,319,-1074>, v=<420,44,-153>, a=<-30,-4,10>\n"
    "p=<3207,-36,58>, v=<452,0,9>, a=<-32,-3,-1>\n"
    "p=<-719,-2708,536>, v=<-100,-387,76>, a=<1,27,-4>\n"
    "p=<1340,-873,2808>, v=<192,-120,405>, a=<-7,8,-26>\n"
    "p=<-708,-889,2518>, v=<-96,-122,361>, a=<5,6,-25>\n"
    "p=<2505,983,-1358>, v=<357,140,-197>, a=<-30,-2,10>\n"
    "p=<406,831,-3220>, v=<56,120,-456>, a=<-4,-6,34>\n"
    "p=<899,2683,-376>, v=<128,383,-53>, a=<-8,-25,2>\n"
    "p=<1301,-1757,2505>, v=<184,-247,357>, a=<-19,17,-29>\n"
    "p=<-647,2496,-913>, v=<-92,358,-128>, a=<7,-16,5>\n"
    "p=<-1699,1246,-1636>, v=<-241,178,-233>, a=<18,-13,16>\n"
    "p=<1951,1901,-1288>, v=<274,271,-184>, a=<-20,-20,14>\n"
    "p=<2011,-1065,1073>, v=<292,-151,157>, a=<-20,14,-10>\n"
    "p=<-1761,-872,-1502>, v=<-252,-124,-213>, a=<13,4,18>\n"
    "p=<92,-382,-3013>, v=<14,-52,-432>, a=<3,4,31>\n"
    "p=<-482,-643,2587>, v=<-66,-91,366>, a=<5,6,-31>\n"
    "p=<-1939,-1497,-528>, v=<-276,-211,-71>, a=<19,13,3>\n"
    "p=<-2123,-1949,-323>, v=<-306,-275,-46>, a=<21,15,1>\n"
    "p=<-3073,48,665>, v=<-440,11,95>, a=<35,2,-6>\n"
    "p=<352,-1263,2998>, v=<52,-183,424>, a=<2,9,-32>\n"
    "p=<-1191,1016,-2178>, v=<-173,145,-314>, a=<15,-10,21>\n"
    "p=<-2760,-942,290>, v=<-395,-132,45>, a=<26,13,0>\n"
    "p=<2734,-2213,976>, v=<391,-316,142>, a=<-25,19,-12>\n"
    "p=<2131,-456,1805>, v=<304,-65,257>, a=<-18,2,-20>\n"
    "p=<1480,-150,-2818>, v=<215,-20,-405>, a=<-13,3,34>\n"
    "p=<-2797,826,-579>, v=<-399,121,-84>, a=<30,-7,8>\n"
    "p=<-193,-2709,-1780>, v=<-28,-387,-250>, a=<1,25,17>\n"
    "p=<-535,-1328,-2812>, v=<-76,-187,-406>, a=<6,14,28>\n"
    "p=<65,2411,-424>, v=<10,344,-60>, a=<-1,-28,-2>\n"
    "p=<1262,2389,1652>, v=<179,338,229>, a=<-14,-25,-15>\n"
    "p=<-1429,1644,-2031>, v=<-203,231,-290>, a=<16,-16,21>\n"
    "p=<776,2700,1814>, v=<110,383,259>, a=<-7,-28,-19>\n"
    "p=<2561,942,1239>, v=<367,134,176>, a=<-26,-7,-12>\n"
    "p=<1084,1811,2581>, v=<154,257,374>, a=<-8,-16,-24>\n"
    "p=<1918,432,-2140>, v=<270,62,-301>, a=<-23,-6,18>\n"
    "p=<566,1897,2782>, v=<79,278,395>, a=<-6,-17,-27>\n"
    "p=<114,-1391,2554>, v=<14,-201,363>, a=<-1,14,-23>\n"
    "p=<-2574,715,-1392>, v=<-368,100,-200>, a=<25,-4,8>\n"
    "p=<1987,2009,1905>, v=<283,286,272>, a=<-17,-18,-19>\n"
    "p=<1688,1514,2008>, v=<240,220,284>, a=<-12,-16,-22>\n"
    "p=<-2447,314,-1691>, v=<-347,49,-245>, a=<24,-2,17>\n"
    "p=<1217,2601,208>, v=<167,372,29>, a=<-8,-25,-1>\n"
    "p=<2370,1327,-463>, v=<340,188,-66>, a=<-25,-10,6>\n"
    "p=<1504,2376,470>, v=<210,341,72>, a=<-15,-24,0>\n"
    "p=<2009,523,2049>, v=<283,80,294>, a=<-15,-7,-21>\n"
    "p=<-2209,1407,42>, v=<-319,200,6>, a=<20,-12,0>\n"
    "p=<2353,-1161,1410>, v=<332,-165,200>, a=<-20,10,-18>\n"
    "p=<-3005,1094,34>, v=<-429,156,9>, a=<29,-11,2>\n"
    "p=<-1801,-1231,1264>, v=<-264,-175,179>, a=<21,12,-13>\n"
    "p=<-1481,2122,1247>, v=<-212,303,180>, a=<14,-16,-12>\n"
    "p=<1946,-357,1631>, v=<277,-53,229>, a=<-19,5,-16>\n"
    "p=<2078,1588,630>, v=<294,226,82>, a=<-20,-12,-6>\n"
    "p=<-396,-2512,-590>, v=<-55,-358,-91>, a=<3,25,5>\n"
    "p=<2238,1678,1694>, v=<321,243,240>, a=<-23,-22,-14>\n"
    "p=<-2286,33,829>, v=<-329,5,120>, a=<17,4,-7>\n"
    "p=<-2947,-396,1406>, v=<-418,-55,197>, a=<29,7,-20>\n"
    "p=<-2487,-1672,-1318>, v=<-355,-236,-184>, a=<25,12,8>\n"
    "p=<-2568,-938,-467>, v=<-370,-132,-65>, a=<25,5,2>\n"
    "p=<-2485,-2140,-714>, v=<-356,-303,-105>, a=<24,26,7>\n"
    "p=<-63,449,-3279>, v=<-6,64,-463>, a=<-3,-7,32>\n"
    "p=<2411,-29,-1776>, v=<345,-4,-258>, a=<-25,0,22>\n"
    "p=<2642,-810,1162>, v=<380,-114,165>, a=<-24,9,-8>\n"
    "p=<2936,-408,563>, v=<417,-64,79>, a=<-26,6,-4>\n"
    "p=<-1523,322,2370>, v=<-214,46,341>, a=<17,-1,-23>\n"
    "p=<336,2015,-1579>, v=<45,288,-225>, a=<-5,-22,14>\n"
    "p=<2712,781,1259>, v=<387,106,181>, a=<-29,-7,-12>\n"
    "p=<2073,-499,-1642>, v=<297,-71,-231>, a=<-20,3,10>\n"
    "p=<-1456,-2625,1183>, v=<-207,-375,176>, a=<17,26,-13>\n"
    "p=<-2704,1271,-1601>, v=<-385,181,-225>, a=<26,-17,16>\n"
    "p=<-838,-2449,1045>, v=<-116,-350,149>, a=<5,24,-10>\n"
    "p=<284,-1816,-2676>, v=<43,-261,-382>, a=<-2,21,26>\n"
    "p=<-2626,-1010,-880>, v=<-374,-143,-119>, a=<27,10,8>\n"
    "p=<7,-3124,27>, v=<0,-446,2>, a=<0,31,4>\n"
    "p=<3255,-402,-164>, v=<468,-58,-27>, a=<-32,1,-1>\n"
    "p=<-1460,1973,-1848>, v=<-209,280,-266>, a=<8,-26,16>\n"
    "p=<1204,-553,-2977>, v=<168,-79,-423>, a=<-14,6,29>\n"
    "p=<-2512,-668,1766>, v=<-362,-92,250>, a=<25,9,-16>\n"
    "p=<1009,-2893,-2091>, v=<146,-416,-296>, a=<-12,31,27>\n"
    "p=<42,3281,555>, v=<6,470,79>, a=<4,-28,-3>\n"
    "p=<-2671,-1394,-56>, v=<-382,-201,-6>, a=<21,16,-1>\n"
    "p=<1626,2006,-135>, v=<233,285,-14>, a=<-16,-14,3>\n";


struct particle {
    int64_t x, y, z;    // position
    int64_t vx, vy, vz; // velocity
    int64_t ax, ay, az; // acceleration

    particle()
        : x(0), y(0), z(0),
          vx(0), vy(0), vz(0),
          ax(0), ay(0), az(0)
    {}
};


std::vector<particle> parse(const char * input)
{
    std::vector<particle> particles;

    // e.g. line = "p=<-833,-499,-1391>, v=<84,17,61>, a=<-4,1,1>"
    std::regex re("p=<(-?\\d+),(-?\\d+),(-?\\d+)>, v=<(-?\\d+),(-?\\d+),(-?\\d+)>, a=<(-?\\d+),(-?\\d+),(-?\\d+)>");

    eachline(input, [&](std::string line) {
        std::smatch sm;
        if (!std::regex_match(line, sm, re))
            throw "bad string!";
        assert(sm.size() == 10);
        particle p;
        p.x = stoi(sm[1]);
        p.y = stoi(sm[2]);
        p.z = stoi(sm[3]);
        p.vx = stoi(sm[4]);
        p.vy = stoi(sm[5]);
        p.vz = stoi(sm[6]);
        p.ax = stoi(sm[7]);
        p.ay = stoi(sm[8]);
        p.az = stoi(sm[9]);
        particles.push_back(p);
    });

    return particles;
}


void update(particle & p)
{
    /*  Each tick, all particles are updated simultaneously.
        A particle's properties are updated in the following order:

        Increase the X velocity by the X acceleration.
        Increase the Y velocity by the Y acceleration.
        Increase the Z velocity by the Z acceleration.
        Increase the X position by the X velocity.
        Increase the Y position by the Y velocity.
        Increase the Z position by the Z velocity. */

    p.vx += p.ax;
    p.vy += p.ay;
    p.vz += p.az;
    p.x += p.vx;
    p.y += p.vy;
    p.z += p.vz;
}

void update(std::vector<particle> & particles)
{
    /*  Each tick, all particles are updated simultaneously.
        A particle's properties are updated in the following order:

        Increase the X velocity by the X acceleration.
        Increase the Y velocity by the Y acceleration.
        Increase the Z velocity by the Z acceleration.
        Increase the X position by the X velocity.
        Increase the Y position by the Y velocity.
        Increase the Z position by the Z velocity. */

    for (auto & p: particles)
        update(p);
}

// return true if any particle still has the potential to head towards <0,0,0>
bool heading_to_centre(const std::vector<particle> & particles)
{
    for (auto p: particles) {
        if (p.x == 0 || p.y == 0 || p.z == 0)
            update(p);
        if (p.x < 0 && (p.ax > 0 || p.ax == 0 && p.vx > 0))
            return true;
        if (p.y < 0 && (p.ay > 0 || p.ay == 0 && p.vy > 0))
            return true;
        if (p.z < 0 && (p.az > 0 || p.az == 0 && p.vz > 0))
            return true;
        if (p.x > 0 && (p.ax < 0 || p.ax == 0 && p.vx < 0))
            return true;
        if (p.y > 0 && (p.ay < 0 || p.ay == 0 && p.vy < 0))
            return true;
        if (p.z > 0 && (p.az < 0 || p.az == 0 && p.vz < 0))
            return true;
    }
    return false;
}


int nearest_to_centre(const std::vector<particle> & particles)
{
    int64_t nearest_distance = std::numeric_limits<int64_t>::max();
    int nearest = -1;
    for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
        const particle & p = particles.at(i);
        const int64_t dist = std::abs(p.x) + std::abs(p.y) + std::abs(p.z);
        if (dist < nearest_distance) {
            nearest_distance = dist;
            nearest = i;
        }
        else if (dist == nearest_distance)
            int i = 0;
    }
    assert(nearest != -1);
    return nearest;
}


int part1(const char * input)
{
    std::vector<particle> particles(parse(input));

    // wait until there are no particles heading towords <0,0,0>, then
    // find the particle nearest <0,0,0>

    while (heading_to_centre(particles))
        update(particles);
    update(particles);

    return nearest_to_centre(particles);
}


struct point {
    int64_t x, y, z;
    point() : x(0), y(0), z(0) {}
    point(int64_t x, int64_t y, int64_t z) : x(x), y(y), z(z) {}
};

bool operator<(const point & lhs, const point & rhs)
{
    if (lhs.x < rhs.x)  return true;
    if (lhs.x > rhs.x)  return false;
    if (lhs.y < rhs.y)  return true;
    if (lhs.y > rhs.y)  return false;
    if (lhs.z < rhs.z)  return true;
    return false;
}

template<typename container, typename pred>
void erase_if(container & items, const pred & p)
{
    for (auto it = items.begin(); it != items.end(); ) {
        if (p(*it))
            it = items.erase(it);
        else
            ++it;
    }
};

void remove_colliders(std::vector<particle> & particles)
{
    std::map<point, int> locations;
    for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
        particle & p = particles[i];
        ++locations[point(p.x, p.y, p.z)];
    }
    erase_if(particles, [&](const particle & p){ return locations[point(p.x, p.y, p.z)] != 1; });
}


int part2(const char * input)
{
    std::vector<particle> particles(parse(input));

    // Take first particle, test for possible future collision with every other particle,
    // if it never collides remove it from the list, repeat for the next particle, and so on.
    // Possible colliders may not actually collide because the particle they were
    // headed for may be removed in some earlier collision with some other particle.
    
    // Particles are hard. Just run the simulation a bunch of times and hope the particles
    // are all headed away from each other at the end.

    remove_colliders(particles);
    while (heading_to_centre(particles)) {
        update(particles);
        remove_colliders(particles);
    }
    // at this point there are 448 left
    for (int i = 0; i < 100000; ++i) {
        update(particles);
        remove_colliders(particles);
    }
    // there are still 448 left - maybe they'll never collide? - I'm not happy with this code

    return static_cast<int>(particles.size());
}


void run()
{
    const char * test =
        "p=<3,0,0>, v=<2,0,0>, a=<-1,0,0>\n"
        "p=<4,0,0>, v=<0,0,0>, a=<-2,0,0>\n";

    assert(part1(test) == 0);

    const int answer1 = part1(input);
    std::cout << "20.1 " << answer1 << '\n';
    assert(answer1 == 457);

    const char * test2 =
        "p=<-6,0,0>, v=<3,0,0>, a=<0,0,0>\n"    
        "p=<-4,0,0>, v=<2,0,0>, a=<0,0,0>\n"
        "p=<-2,0,0>, v=<1,0,0>, a=<0,0,0>\n"
        "p=<3,0,0>, v=<-1,0,0>, a=<0,0,0>\n";

    assert(part2(test2) == 1);

    const int answer2 = part2(input);
    std::cout << "20.2 " << answer2 << '\n';
    assert(answer2 == 448);
}

}


namespace day21 {

const char * input =
    "../.. => .##/##./.#.\n"
    "#./.. => .#./#.#/##.\n"
    "##/.. => #.#/#.#/###\n"
    ".#/#. => #../.#./.#.\n"
    "##/#. => ##./#.#/..#\n"
    "##/## => #.#/#.#/...\n"
    ".../.../... => ..##/##../##../#.#.\n"
    "#../.../... => ##.#/..#./#.#./.#..\n"
    ".#./.../... => ..#./##.#/#.##/###.\n"
    "##./.../... => ###./##.#/.###/#.#.\n"
    "#.#/.../... => ##../#..#/.###/#.#.\n"
    "###/.../... => ...#/#..#/...#/...#\n"
    ".#./#../... => ...#/.##./#.##/..#.\n"
    "##./#../... => .##./.#../.##./.#..\n"
    "..#/#../... => ####/.#../#.#./.###\n"
    "#.#/#../... => ###./.#../##../....\n"
    ".##/#../... => ##../#.#./#.#./##..\n"
    "###/#../... => #.##/#..#/.#../##..\n"
    ".../.#./... => .#.#/.###/.##./##..\n"
    "#../.#./... => .###/.##./..##/..##\n"
    ".#./.#./... => .##./.#.#/#.##/.###\n"
    "##./.#./... => ..#./..../..#./###.\n"
    "#.#/.#./... => ..../..#./..##/##..\n"
    "###/.#./... => .#.#/#..#/.###/#..#\n"
    ".#./##./... => ..../..#./.#../####\n"
    "##./##./... => ..##/#.##/..#./#.##\n"
    "..#/##./... => ..../#.##/.##./####\n"
    "#.#/##./... => ..##/#.#./.#../.##.\n"
    ".##/##./... => #.../...#/###./....\n"
    "###/##./... => .#../#.#./#.##/....\n"
    ".../#.#/... => #.#./####/#.../..#.\n"
    "#../#.#/... => ...#/.#.#/###./.#.#\n"
    ".#./#.#/... => #..#/#.../###./#.##\n"
    "##./#.#/... => .##./#.../...#/#.##\n"
    "#.#/#.#/... => #..#/##../##../.#..\n"
    "###/#.#/... => #.#./...#/.#.#/.##.\n"
    ".../###/... => .#.#/.##./..#./.#..\n"
    "#../###/... => .###/..##/#.##/.#..\n"
    ".#./###/... => #.../#.../.#../#...\n"
    "##./###/... => .###/...#/.#.#/.#..\n"
    "#.#/###/... => .#../..##/#..#/#...\n"
    "###/###/... => .###/##../##.#/#.#.\n"
    "..#/.../#.. => ##.#/..../...#/..##\n"
    "#.#/.../#.. => .#.#/###./...#/.#.#\n"
    ".##/.../#.. => ##.#/.#../####/#.##\n"
    "###/.../#.. => #.../#..#/###./....\n"
    ".##/#../#.. => #..#/..#./####/...#\n"
    "###/#../#.. => ####/###./##.#/....\n"
    "..#/.#./#.. => .##./.##./##../#..#\n"
    "#.#/.#./#.. => #..#/#..#/#.../.#..\n"
    ".##/.#./#.. => ##../##.#/#.##/..##\n"
    "###/.#./#.. => #.##/..##/.##./#.#.\n"
    ".##/##./#.. => #.##/..../##../....\n"
    "###/##./#.. => ###./.#.#/.###/.#..\n"
    "#../..#/#.. => .###/#.##/..#./.##.\n"
    ".#./..#/#.. => #..#/..##/.#.#/##..\n"
    "##./..#/#.. => ###./#.../..##/##..\n"
    "#.#/..#/#.. => #.../.##./.###/###.\n"
    ".##/..#/#.. => ...#/##.#/..#./...#\n"
    "###/..#/#.. => ###./..#./.#../...#\n"
    "#../#.#/#.. => #..#/...#/..#./.#.#\n"
    ".#./#.#/#.. => #..#/##.#/####/.##.\n"
    "##./#.#/#.. => .###/##../..../.#..\n"
    "..#/#.#/#.. => ..#./##.#/####/###.\n"
    "#.#/#.#/#.. => #.#./#.##/##.#/.###\n"
    ".##/#.#/#.. => ..#./####/##../.###\n"
    "###/#.#/#.. => .#.#/###./.#.#/#...\n"
    "#../.##/#.. => .###/..##/.#.#/..#.\n"
    ".#./.##/#.. => #.##/.#../.###/#.#.\n"
    "##./.##/#.. => .###/#.../#.../..#.\n"
    "#.#/.##/#.. => ##../...#/..#./...#\n"
    ".##/.##/#.. => ..##/.#.#/...#/####\n"
    "###/.##/#.. => ##../.###/##../###.\n"
    "#../###/#.. => ###./#..#/#.#./....\n"
    ".#./###/#.. => ..../#.#./.###/.###\n"
    "##./###/#.. => .###/##../#..#/####\n"
    "..#/###/#.. => ..../#.#./#..#/##..\n"
    "#.#/###/#.. => .#.#/..##/##.#/#..#\n"
    ".##/###/#.. => .#../...#/##../.#..\n"
    "###/###/#.. => #.../.###/###./##.#\n"
    ".#./#.#/.#. => .#.#/#.##/###./#...\n"
    "##./#.#/.#. => .#../.#../.#../.#..\n"
    "#.#/#.#/.#. => ##.#/..../###./.#..\n"
    "###/#.#/.#. => #.#./##.#/.#.#/##..\n"
    ".#./###/.#. => ##.#/..#./..#./#.#.\n"
    "##./###/.#. => ####/.###/.#.#/.##.\n"
    "#.#/###/.#. => .#../.###/##../#.#.\n"
    "###/###/.#. => #.../.##./..##/####\n"
    "#.#/..#/##. => ..../..#./##../...#\n"
    "###/..#/##. => .###/..#./#.##/###.\n"
    ".##/#.#/##. => .###/..../#.#./...#\n"
    "###/#.#/##. => ###./...#/.###/####\n"
    "#.#/.##/##. => #.##/#.../..../...#\n"
    "###/.##/##. => #.../#.../#..#/...#\n"
    ".##/###/##. => .#../###./.###/..#.\n"
    "###/###/##. => ##.#/.#../###./.#..\n"
    "#.#/.../#.# => #.#./#.#./..../...#\n"
    "###/.../#.# => ####/###./..../##.#\n"
    "###/#../#.# => .###/##.#/#.##/..#.\n"
    "#.#/.#./#.# => ###./.###/#.##/....\n"
    "###/.#./#.# => .##./###./#.#./##..\n"
    "###/##./#.# => #.../.#.#/#.##/#..#\n"
    "#.#/#.#/#.# => ..#./#.#./##../..##\n"
    "###/#.#/#.# => ..#./.#../...#/.##.\n"
    "#.#/###/#.# => ..#./###./##.#/####\n"
    "###/###/#.# => #.../#.#./#..#/.#.#\n"
    "###/#.#/### => ..##/.##./.#.#/#...\n"
    "###/###/### => .##./..##/####/###.\n";


struct pattern {
    std::vector<char> p_;

    pattern()
    {
    }

    explicit pattern(const char * s)
    {
         while (*s) {
            if (*s != '/')
                p_.push_back(*s);
            ++s;
        }
    }

    explicit pattern(const std::vector<char> & p)
        : p_(p)
    {
    }

    int size() const
    {
        return static_cast<int>(std::sqrt(p_.size()));
    }
};

bool operator<(const pattern & lhs, const pattern & rhs)
{
    return lhs.p_ < rhs.p_;
}

void print(const std::vector<char> & p, std::string msg)
{
    std::cout << msg << '\n';
    const int len = static_cast<int>(std::sqrt(p.size()));
    for (int i = 0; i < len; ++i)
        std::cout << std::string(&p[i * len], len) << '\n';
    std::cout << '\n';
}

// rotate 90 degrees right; works for 2x2 and 3x3 patterns only
pattern rotate_r(pattern pat)
{
    std::vector<char> & p = pat.p_;
    if (p.size() == 4) {
        p = {p[2], p[0], p[3], p[1]};
    }
    else if (p.size() == 9) {
        p = {p[6], p[3], p[0], p[7], p[4], p[1], p[8], p[5], p[2]};
    }
    else
        assert(false);
    return pat;
}

// flip top to bottom; works for 2x2 and 3x3 patterns only
pattern flip_tb(pattern pat)
{
    std::vector<char> & p = pat.p_;
    if (p.size() == 4) {
        std::swap(p[0], p[2]);
        std::swap(p[1], p[3]);
    }
    else if (p.size() == 9) {
        std::swap(p[0], p[6]);
        std::swap(p[1], p[7]);
        std::swap(p[2], p[8]);
    }
    else
        assert(false);
    return pat;
}

// flip left to right; works for 2x2 and 3x3 patterns only
pattern flip_lr(pattern pat)
{
    std::vector<char> & p = pat.p_;
    if (p.size() == 4) {
        std::swap(p[0], p[1]);
        std::swap(p[2], p[3]);
    }
    else if (p.size() == 9) {
        std::swap(p[0], p[2]);
        std::swap(p[3], p[5]);
        std::swap(p[6], p[8]);
    }
    else
        assert(false);
    return pat;
}

void insert_rule_permutations(std::map<pattern, pattern> & rules, std::string target, std::string replacement)
{
    /*  given
            AB
            CD
        insert
            AB  CA  DC  BD      BA  CD          AC  DB
            CD  DB  BA  AC      DC  AB          BD  CA
            --- rotate ---      -flip-      -flip+rotate-
    */
    const pattern r(replacement.c_str());
    pattern t(target.c_str());
    for (int i = 0; i < 4; ++i) {
        t = rotate_r(t);
        rules[t] = r;
    }
    rules[flip_tb(t)] = r;
    rules[flip_lr(t)] = r;
    t = rotate_r(t);
    rules[flip_tb(t)] = r;
    rules[flip_lr(t)] = r;
}

std::map<pattern, pattern> create_rules(const char * s)
{
    std::map<pattern, pattern> rules;
    eachline(s, [&](std::string line) {
        // e.g. line = "..#/.../#.. => ##.#/..../...#/..##"
        std::vector<std::string> rule;
        eachword(line, [&](std::string word) {
            rule.push_back(word);
        });
        assert(rule.size() == 3);
        assert(rule[1] == "=>");
        insert_rule_permutations(rules, rule[0], rule[2]);
    });
    return rules;
}


std::vector<pattern> decompose(const pattern & pat)
{
    std::vector<pattern> parts;

    const int len = pat.size();
    assert((pat.size() % 2 == 0) || (pat.size() % 3 == 0));
    const int part_len = (pat.size() % 2 == 0) ? 2 : 3;
    const int itterations = len / part_len;

    const std::vector<char> & p = pat.p_;
    for (int r = 0; r < itterations; ++r)
        for (int c = 0; c < itterations; ++c) {
            std::vector<char> newp;
            for (int row = 0; row < part_len; ++row) {
                const char * start = &p[r * len * part_len + c * part_len + row * len];
                const char * end = start + part_len;
                newp.insert(std::end(newp), start, end);
            }
            parts.push_back(pattern(newp));
        }

    return parts;
}

pattern compose(const std::vector<pattern> & parts)
{
    pattern pat;

    const int part_len = parts[0].size();
    const int itterations = static_cast<int>(std::sqrt(parts.size()));
    const int len = itterations * part_len;

    std::vector<char> & p = pat.p_;
    for (int r = 0; r < itterations; ++r)
        for (int row = 0; row < part_len; ++row) {
            for (int c = 0; c < itterations; ++c) {
                const char * start = &parts[r * itterations + c].p_.at(row * part_len);
                const char * end = start + part_len;
                p.insert(std::end(p), start, end);
            }
        }

    return pat;
}



int part1(const char * start_pattern_str, const char * rules_str, int itterations)
{
    pattern pat(start_pattern_str);
    const std::map<pattern, pattern> rules(create_rules(rules_str));
    for (int i = 0; i < itterations; ++i) {
        std::vector<pattern> parts(decompose(pat));
        for (int i = 0; i < static_cast<int>(parts.size()); ++i)
            parts[i] = rules.at(parts[i]);
        pat = compose(parts);
    }
    return std::count_if(std::begin(pat.p_), std::end(pat.p_), [](const char c) { return c == '#'; });
}


void run()
{
    const char * start_pattern =
        ".#./"
        "..#/"
        "###";

    const char * test_rules =
        "../.# => ##./#../...\n"
        ".#./..#/### => #..#/..../..../#..#\n";

    assert(part1(start_pattern, test_rules, 2) == 12);

    const int answer1 = part1(start_pattern, input, 5);
    std::cout << "21.1 " << answer1 << '\n';
    assert(answer1 == 188);

    const int answer2 = part1(start_pattern, input, 18);
    std::cout << "21.2 " << answer2 << '\n';
    assert(answer1 == 188);
}

}





namespace day22 {


class sparsemap {
    std::set<std::pair<int, int>> map_;
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
    eachline(s, [&](std::string line) {
        width = static_cast<int>(line.size());
        for (int x = 0; x < width; ++x)
            if (line[x] == '#')
                m.infect(x, y);
        --y;
    });

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


class sparsemap2 {
    std::map<std::pair<int, int>, int> map_;
public:
    enum state { cleaned, weakened, infected, flagged };

    void clean(int x, int y)
    {
        map_.erase(std::make_pair(x, y));
    }
    void weaken(int x, int y)
    {
        map_[std::make_pair(x, y)] = weakened;
    }
    void infect(int x, int y)
    {
        map_[std::make_pair(x, y)] = infected;
    }
    void flag(int x, int y)
    {
        map_[std::make_pair(x, y)] = flagged;
    }
    int infected_state(int x, int y) const
    {
        auto i = map_.find(std::make_pair(x, y));
        if (i == std::end(map_))
            return cleaned;
        return i->second;
    }
};


sparsemap2 create_map2(const char * s, int & centre_x, int & centre_y)
{
    /* e.g. given string is
            ..#
            #..
            ...
        insert into nodemap so that top left corner is at (0,0)
    */
    sparsemap2 m;
    int y = 0, width = 0;
    eachline(s, [&](std::string line) {
        width = static_cast<int>(line.size());
        for (int x = 0; x < width; ++x)
            if (line[x] == '#')
                m.infect(x, y);
        --y;
    });

     centre_x = width/2;
     centre_y = y/2;

    return m;
}

int part2(const char * input, int burst_count)
{
    int infections = 0;

    enum direction { north, east, south, west, dirlen };
    int dir = north;
    int x, y;
    sparsemap2 m(create_map2(input, x, y));
    for (int i = 0; i < burst_count; ++i) {
        const int s = m.infected_state(x, y);

        // If it is clean, it turns left.
        // If it is weakened, it does not turn, and will continue moving in the same direction.
        // If it is infected, it turns right.
        // If it is flagged, it reverses direction, and will go back the way it came.
        switch (s) {
        case sparsemap2::cleaned:
            dir = (dir + dirlen - 1) % dirlen;  // turn left
            m.weaken(x, y);                     // Clean nodes become weakened.
            break;
        case sparsemap2::weakened:
            m.infect(x, y);                     // Weakened nodes become infected.
            ++infections;
            break;
        case sparsemap2::infected:
            dir = (dir + 1) % dirlen;           // turn right
            m.flag(x, y);                       // Infected nodes become flagged.
            break;
        case sparsemap2::flagged:
            dir = (dir + dirlen/2) % dirlen;    // reverse
            m.clean(x, y);                      // Flagged nodes become clean.
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


void run()
{
    const char * test = 
        "..#\n"
        "#..\n"
        "...\n";

    assert(part1(test, 70) == 41);
    assert(part1(test, 10000) == 5587);

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

    const int answer1 = part1(input, 10000);
    std::cout << "22.1 " << answer1 << '\n';
    assert(answer1 == 5570);

    assert(part2(test, 100) == 26);
    assert(part2(test, 10000000) == 2511944);

    const int answer2 = part2(input, 10000000);
    std::cout << "22.2 " << answer2 << '\n';
    assert(answer2 == 2512022);
}

}




namespace day23 {


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
    eachline(input, [&](std::string line) {
        std::vector<std::string> tokens;
        eachword(line, [&](std::string word) {
            tokens.push_back(word);
        });
        assert(2 <= tokens.size() && tokens.size() <= 3);
        int op = get_opcode(tokens[0]), arg0 = 0, arg1 = 0;
        switch (op) {
        case op_mul:
        case op_set:
        case op_sub:
            assert(tokens.size() == 3);
            assert(std::isalpha(tokens[1][0], loc));
            arg0 = tokens[1][0] - 'a';
            if (std::isdigit(tokens[2][0], loc) || tokens[2][0] == '-') {
                ++op; // switch to immediate version of opcode
                arg1 = std::stoi(tokens[2]);
            }
            else
                arg1 = tokens[2][0] - 'a';
            break;

        case op_jnz: // either "jgz a b" (op_jgz), "jgz a 99" (op_jgzi) or "jgz 88 99" (op_jgzii)
            {
                assert(tokens.size() == 3);
                bool immediate_arg0 = false, immediate_arg1 = false;
                if (std::isdigit(tokens[1][0], loc) || tokens[1][0] == '-') {
                    immediate_arg0 = true;
                    arg0 = std::stoi(tokens[1]);
                }
                else
                    arg0 = tokens[1][0] - 'a';
                if (std::isdigit(tokens[2][0], loc) || tokens[2][0] == '-') {
                    immediate_arg1 = true;
                    arg1 = std::stoi(tokens[2]);
                }
                else
                    arg1 = tokens[2][0] - 'a';
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
    });
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



void run()
{
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
    std::cout << "23.1 " << answer1 << '\n';
    assert(answer1 == 3969);

    const int64_t answer2 = part2();
    std::cout << "23.2 " << answer2 << '\n';
    assert(answer2 == 917);
}

}




namespace day24 {


class bag {
    std::vector<int> a, b;
public:
    // put a component with n-type/m-type ports into bag
    void give(int n, int m)
    {
        if (n < m) {
            a.push_back(n);
            b.push_back(m);
        }
        else {
            a.push_back(m);
            b.push_back(n);
        }
    }

    // remove component with an n_type port one end and m_type port the other
    void take(int n_type, int m_type)
    {
        if (m_type < n_type)
            std::swap(n_type, m_type);
        for (unsigned i = 0; i != a.size(); ++i)
            if (a[i] == n_type && b[i] == m_type) {
                a.erase(std::begin(a) + i);
                b.erase(std::begin(b) + i);
                return;
            }
        throw "bag::take() component not found";
    }

    // return a list of "other ends" of all components that have an n_type port
    std::vector<int> matches(int n_type)
    {
        std::vector<int> result;
        for (unsigned i = 0; i != a.size(); ++i)
            if (a[i] == n_type)
                result.push_back(b[i]);
        for (unsigned i = 0; i != a.size(); ++i)
            if (b[i] == n_type)
                result.push_back(a[i]);
        return result;
    }
};


int max_strength(bag b, int n_type)
{
    int max = 0;
    std::vector<int> compatibles(b.matches(n_type));
    for (auto m_type: compatibles) {
        b.take(n_type, m_type);
        int s = max_strength(b, m_type);
        b.give(n_type, m_type);
        if (s + n_type + m_type > max)
            max = s + n_type + m_type;
    }
    return max;
}

int part1(const char * input)
{
    bag b;
    eachline(input, [&](std::string line){
        std::smatch sm;
        if (!std::regex_match(line, sm, std::regex("(\\d+)/(\\d+)")))
            throw "bad string!";
        assert(sm.size() == 3);
        b.give(stoi(sm[1]), stoi(sm[2]));
    });

    return max_strength(b, 0);
}

// return maximum bridge (length, strength)
std::pair<int, int> max_strength2(bag b, int n_type, int length)
{
    int max_len = 0, max_strenth = 0;
    std::vector<int> compatibles(b.matches(n_type));
    for (auto m_type: compatibles) {
        b.take(n_type, m_type);
        std::pair<int, int> s = max_strength2(b, m_type, length + 1);
        b.give(n_type, m_type);
        if (length + s.first > max_len) {
            max_len = length + s.first;
            max_strenth = n_type + m_type + s.second;
        }
        else if (length + s.first == max_len && n_type + m_type + s.second > max_strenth)
            max_strenth = n_type + m_type + s.second;
    }
    return std::make_pair(max_len, max_strenth);
}

int part2(const char * input)
{
    bag b;
    eachline(input, [&](std::string line){
        std::smatch sm;
        if (!std::regex_match(line, sm, std::regex("(\\d+)/(\\d+)")))
            throw "bad string!";
        assert(sm.size() == 3);
        b.give(stoi(sm[1]), stoi(sm[2]));
    });

    return max_strength2(b, 0, 0).second;
}


void run()
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

    const char * input =
        "42/37\n"
        "28/28\n"
        "29/25\n"
        "45/8\n"
        "35/23\n"
        "49/20\n"
        "44/4\n"
        "15/33\n"
        "14/19\n"
        "31/44\n"
        "39/14\n"
        "25/17\n"
        "34/34\n"
        "38/42\n"
        "8/42\n"
        "15/28\n"
        "0/7\n"
        "49/12\n"
        "18/36\n"
        "45/45\n"
        "28/7\n"
        "30/43\n"
        "23/41\n"
        "0/35\n"
        "18/9\n"
        "3/31\n"
        "20/31\n"
        "10/40\n"
        "0/22\n"
        "1/23\n"
        "20/47\n"
        "38/36\n"
        "15/8\n"
        "34/32\n"
        "30/30\n"
        "30/44\n"
        "19/28\n"
        "46/15\n"
        "34/50\n"
        "40/20\n"
        "27/39\n"
        "3/14\n"
        "43/45\n"
        "50/42\n"
        "1/33\n"
        "6/39\n"
        "46/44\n"
        "22/35\n"
        "15/20\n"
        "43/31\n"
        "23/23\n"
        "19/27\n"
        "47/15\n"
        "43/43\n"
        "25/36\n"
        "26/38\n"
        "1/10\n";

    const int answer1 = part1(input);
    std::cout << "24.1 " << answer1 << '\n';
    assert(answer1 == 3969);

    const int answer2 = part2(input);
    std::cout << "24.2 " << answer2 << '\n';
    assert(answer2 == 1928);
}

}




namespace day25 {



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


struct tape {
    int cursor;
    std::vector<uint8_t> left, right;

    tape()
    : cursor(0), right(1, 0)
    {
    }

    bool read() const
    {
        return (cursor >= 0 ? right.at(cursor) : left.at(-cursor-1)) != 0;
    }

    void write(bool b)
    {
        (cursor >= 0 ? right[cursor] : left[-cursor-1]) = b;
    }

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
    eachline(input, [&](std::string line) {
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
    });
    return b;
}

int part1(const char * input)
{
    blueprint b(read(input));
    tape t;

    run_turing(b, t);

    return
        std::count_if(std::begin(t.left), std::end(t.left), [](uint8_t n){ return n == 1; })
        + std::count_if(std::begin(t.right), std::end(t.right), [](uint8_t n){ return n == 1; });
}


void run()
{
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


    const char * input =
        "Begin in state A.\n"
        "Perform a diagnostic checksum after 12399302 steps.\n"
        "\n"
        "In state A:\n"
        "  If the current value is 0:\n"
        "    - Write the value 1.\n"
        "    - Move one slot to the right.\n"
        "    - Continue with state B.\n"
        "  If the current value is 1:\n"
        "    - Write the value 0.\n"
        "    - Move one slot to the right.\n"
        "    - Continue with state C.\n"
        "\n"
        "In state B:\n"
        "  If the current value is 0:\n"
        "    - Write the value 0.\n"
        "    - Move one slot to the left.\n"
        "    - Continue with state A.\n"
        "  If the current value is 1:\n"
        "    - Write the value 0.\n"
        "    - Move one slot to the right.\n"
        "    - Continue with state D.\n"
        "\n"
        "In state C:\n"
        "  If the current value is 0:\n"
        "    - Write the value 1.\n"
        "    - Move one slot to the right.\n"
        "    - Continue with state D.\n"
        "  If the current value is 1:\n"
        "    - Write the value 1.\n"
        "    - Move one slot to the right.\n"
        "    - Continue with state A.\n"
        "\n"
        "In state D:\n"
        "  If the current value is 0:\n"
        "    - Write the value 1.\n"
        "    - Move one slot to the left.\n"
        "    - Continue with state E.\n"
        "  If the current value is 1:\n"
        "    - Write the value 0.\n"
        "    - Move one slot to the left.\n"
        "    - Continue with state D.\n"
        "\n"
        "In state E:\n"
        "  If the current value is 0:\n"
        "    - Write the value 1.\n"
        "    - Move one slot to the right.\n"
        "    - Continue with state F.\n"
        "  If the current value is 1:\n"
        "    - Write the value 1.\n"
        "    - Move one slot to the left.\n"
        "    - Continue with state B.\n"
        "\n"
        "In state F:\n"
        "  If the current value is 0:\n"
        "    - Write the value 1.\n"
        "    - Move one slot to the right.\n"
        "    - Continue with state A.\n"
        "  If the current value is 1:\n"
        "    - Write the value 1.\n"
        "    - Move one slot to the right.\n"
        "    - Continue with state E.\n";

    const int answer1 = part1(input);
    std::cout << "25.1 " << answer1 << '\n';
    assert(answer1 == 2794);
}

}


#include <chrono>

int main()
{
    day01();        // --- Day 1: Inverse Captcha ---
    day02();        // --- Day 2: Corruption Checksum ---
    day03::run();   // --- Day 3: Spiral Memory ---
    day04::run();   // --- Day 4: High-Entropy Passphrases ---
    day05::run();   // --- Day 5: A Maze of Twisty Trampolines, All Alike ---
    day06::run();   // --- Day 6: Memory Reallocation ---
    day07::run();   // --- Day 7: Recursive Circus ---
    day08::run();   // --- Day 8: I Heard You Like Registers ---
    day09::run();   // --- Day 9: Stream Processing ---
    day10::run();   // --- Day 10: Knot Hash ---
    day11::run();   // --- Day 11: Hex Ed ---
    day12::run();   // --- Day 12: Digital Plumber ---
    day13::run();   // --- Day 13: Packet Scanners ---
    day14::run();   // --- Day 14: Disk Defragmentation ---
    day15::run();   // --- Day 15: Dueling Generators ---
    day16::run();   // --- Day 16: Permutation Promenade ---
    day17::run();   // --- Day 17: Spinlock ---
    day18::run();   // --- Day 18: Duet ---
    day19::run();   // --- Day 19: A Series of Tubes ---
    day20::run();   // --- Day 20: Particle Swarm ---
    day21::run();   // --- Day 21: Fractal Art ---
    day22::run();   // --- Day 22: Sporifica Virus ---
    day23::run();   // --- Day 23: Coprocessor Conflagration ---
    day24::run();   // --- Day 24: Electromagnetic Moat ---
    day25::run();   // --- Day 25: The Halting Problem ---
}
