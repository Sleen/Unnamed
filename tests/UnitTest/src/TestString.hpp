#include "UnitTest.hpp"
#include "Base/StringHelper.hpp"
#include "String.hpp"

using namespace me;
using namespace unnamed;

BEGIN_TESTS(String)

TEST(Trim) {
	CHECK(StringHelper::Trim("test", 't') == "es");
	CHECK(StringHelper::Trim("  test     ", ' ') == "test");
	CHECK(StringHelper::TrimStart("  test  ", ' ') == "test  ");
	CHECK(StringHelper::TrimEnd("  test  ", ' ') == "  test");
	CHECK(StringHelper::Trim("test", "t") == "es");
	CHECK(StringHelper::Trim("  test     ", " ") == "test");
	CHECK(StringHelper::TrimStart("  test  ", " ") == "test  ");
	CHECK(StringHelper::TrimEnd("  test  ", " ") == "  test");
	CHECK(StringHelper::Trim(",.,.,.test,,..,", ",.") == "test");
	CHECK(StringHelper::Trim("test", "tes") == "");
}

TEST(Replace) {
	CHECK(StringHelper::Replace("test", 't', ' ') == " es ");
	CHECK(StringHelper::Replace("test", '1', '2') == "test");
}

TEST(Format) {
	CHECK(StringHelper::Format("%d", 1) == "1");
	CHECK(StringHelper::Format("%s", "test") == "test");
	CHECK(StringHelper::Format("test%d", 1) == "test1");
	CHECK(StringHelper::Format("test%4d", 1) == "test   1");
	CHECK(StringHelper::Format("test%.3f", 1.0f) == "test1.000");
	CHECK(StringHelper::Format("test%d,%d", 1, 2) == "test1,2");
}

TEST(Split) {
	auto r = StringHelper::Split(" 1,22.333,4444;", " ,.;", true);
	CHECK(r.size() == 4);
	CHECK(r[0] == "1");
	CHECK(r[1] == "22");
	CHECK(r[2] == "333");
	CHECK(r[3] == "4444");
	r = StringHelper::Split("1, 2", ", ", true);
	CHECK(r.size() == 2);
	CHECK(r[0] == "1");
	CHECK(r[1] == "2");
}

TEST(Other) {
	CHECK(StringHelper::StartsWith("12345", ""));
	CHECK(StringHelper::StartsWith("12345", "1"));
	CHECK(StringHelper::StartsWith("12345", "1234"));
	CHECK(StringHelper::StartsWith("12345", "12345"));
	CHECK(!StringHelper::StartsWith("12345", "123456"));
	CHECK(!StringHelper::StartsWith("12345", "2"));
	CHECK(StringHelper::EndsWith("12345", ""));
	CHECK(StringHelper::EndsWith("12345", "5"));
	CHECK(StringHelper::EndsWith("12345", "2345"));
	CHECK(StringHelper::EndsWith("12345", "12345"));
	CHECK(!StringHelper::EndsWith("12345", "123456"));
	CHECK(!StringHelper::EndsWith("12345", "4"));
	CHECK(StringHelper::ToLower("ABC") == "abc");
	CHECK(StringHelper::ToLower("123ABCdef") == "123abcdef");
	CHECK(StringHelper::ToUpper("abc") == "ABC");
	CHECK(StringHelper::ToUpper("123ABCdef") == "123ABCDEF");
}

TEST("constructor") {
    CHECK_NO_THROW(String());
    CHECK_NO_THROW(String(1));
    CHECK_NO_THROW(String(1.23456));
    CHECK_NO_THROW(String(true));
    CHECK_NO_THROW(String('a'));
    CHECK_NO_THROW(String(u'一'));
    CHECK_NO_THROW(String(U'🀅'));
    CHECK_NO_THROW(String(""));
    CHECK_NO_THROW(String(u""));
    CHECK_NO_THROW(String(U""));
    CHECK_NO_THROW(String("1234一二三四"));
    CHECK_NO_THROW(String(u"1234一二三四"));
    CHECK_NO_THROW(String(U"1234一二三四"));
    CHECK_NO_THROW(String(String()));
}

TEST("length") {
    CHECK(String().length() == 0);
    CHECK(String(123).length() == 3);
    CHECK(String("一二三").length() == 3);
    CHECK(String(U'🀅').length() == 1);
}

TEST("CharAt") {
    String s("一2🀅a");
    CHECK(s.CharAt(0) == U'一');
    CHECK(s.CharAt(1) == U'2');
    CHECK(s.CharAt(2) == U'🀅');
    CHECK(s.CharAt(3) == U'a');
    CHECK(s.CharAt(4) == 0);
}

TEST("cast to std string") {
    CHECK(String("一2🀅a").Utf8String() == "一2🀅a");
    CHECK(String("一2🀅a").Utf16String() == u"一2🀅a");
    CHECK(String("一2🀅a").Utf32String() == U"一2🀅a");
    CHECK(String().Utf8String() == "");
    CHECK(String().Utf16String() == u"");
    CHECK(String().Utf32String() == U"");
}

TEST("Swap") {
    std::string a = "123";
    std::string b = "456789";
    String aa(a);
    String bb(b);
    aa.Swap(bb);
    CHECK(aa.Utf8String() == b);
    CHECK(bb.Utf8String() == a);
}

TEST("comparation") {
    CHECK(String() == String());
    CHECK(String() == String(""));
    CHECK(String("一2🀅a") == String("一2🀅a"));
    CHECK(String("123456") != String("12345"));
    String s("一2🀅a");
    CHECK(s == s);
}

TEST("from values") {
    CHECK(String(123) == String("123"));
    CHECK(String(123.456) == String("123.456"));
    CHECK(String(true) == String("true"));
    CHECK(String('a') == String("a"));
    CHECK(String(u'一') == String("一"));
    CHECK(String(U'🀅') == String("🀅"));
    CHECK(String(U"一🀅a") == String("一🀅a"));
}

TEST("+") {
    CHECK(String(1) + String(2) == String(12));
    CHECK(String(1) + 2 == String(12));
    CHECK(1 + String(2) == String(12));
    CHECK(String() + String() == String());
    CHECK(String() + 123 == String(123));
    CHECK(123 + String() == String(123));
    CHECK((String() += 123) == String(123));
}

TEST("SubString") {
    CHECK(String("").Substring(0) == String());
    CHECK(String("").Substring(2) == String());
    CHECK(String("").Substring(0, 5) == String());
    CHECK(String("").Substring(2, 5) == String());
    CHECK(String("12345").Substring(0) == String("12345"));
    CHECK(String("12345").Substring(2) == String("345"));
    CHECK(String("12345").Substring(5) == String());
    CHECK(String("12345").Substring(0, 0) == String());
    CHECK(String("12345").Substring(0, 2) == String("12"));
    CHECK(String("12345").Substring(0, 5) == String("12345"));
    CHECK(String("12345").Substring(0, 10) == String("12345"));
    CHECK(String("12345").Substring(2, 0) == String());
    CHECK(String("12345").Substring(2, 2) == String("34"));
    CHECK(String("12345").Substring(2, 3) == String("345"));
    CHECK(String("12345").Substring(2, 10) == String("345"));
    CHECK(String("12345").Substring(5, 1) == String());
}

TEST("check prefix & suffix") {
    CHECK(String("12345").StartsWith(String()));
    CHECK(String("12345").StartsWith(String(123)));
    CHECK(String("12345").StartsWith(String(12345)));
    CHECK(!String("12345").StartsWith(String(13)));
    CHECK(!String("12345").StartsWith(String(123456)));
    CHECK(String("12345").EndsWith(String()));
    CHECK(String("12345").EndsWith(String(45)));
    CHECK(String("12345").EndsWith(String(12345)));
    CHECK(!String("12345").EndsWith(String(4)));
    CHECK(!String("12345").EndsWith(String(012345)));
}

TEST("change case") {
    CHECK(String("abc").ToUpper() == String("ABC"));
    CHECK(String("一🀅aB").ToUpper() == String("一🀅AB"));
    CHECK(String("一🀅aB").ToLower() == String("一🀅ab"));
}

TEST("trim") {
    CHECK(String().Trim() == String());
    CHECK(String().TrimStart() == String());
    CHECK(String().TrimEnd() == String());
    CHECK(String("   \t  \n ").Trim() == String());
    CHECK(String("   \t  \n ").TrimStart() == String());
    CHECK(String("   \t  \n ").TrimEnd() == String());
    CHECK(String("   \t12 34  \n ").Trim() == String("12 34"));
    CHECK(String("1234").Trim() == String("1234"));
    CHECK(String("  1234").Trim() == String("1234"));
    CHECK(String("1234  ").Trim() == String("1234"));
    CHECK(String("  1234  ").TrimStart() == String("1234  "));
    CHECK(String("  1234  ").TrimEnd() == String("  1234"));
    CHECK(String(" 'hello, world.' ").Trim(String(" ,.'")) == String("hello, world"));
}

TEST("Replace") {
    CHECK(String("cbabcabc").Replace('a', 'b') == String("cbbbcabc"));
    CHECK(String("cbabcabc").ReplaceAll('a', 'b') == String("cbbbcbbc"));
    CHECK(String("aa").Replace(String("a"), String("aa")) == String("aaa"));
    CHECK(String("aa").ReplaceAll(String("a"), String("aa")) == String("aaaa"));
}

TEST("Split") {
    String s(",a,一二，,123,");
    auto r = s.Split(String(",，"), true);
    CHECK(r.size() == 3);
    CHECK(r[0] == String("a"));
    CHECK(r[1] == String("一二"));
    CHECK(r[2] == String("123"));
    r = s.Split(',');
    CHECK(r.size() == 5);
    CHECK(r[0] == String(""));
    CHECK(r[1] == String("a"));
    CHECK(r[2] == String("一二，"));
    CHECK(r[3] == String("123"));
    CHECK(r[4] == String(""));
}

BENCHMARK("CharAt       // random access", 10000) {
    the_little_prince_ch.CharAt(260);
    the_little_prince_ch.CharAt(530);
}

BENCHMARK("CharAt       // ascending iteration", 1000) {
    for (int i=0;i<the_little_prince_ch.length();i++) {
        the_little_prince_ch.CharAt(i);
    }
}

BENCHMARK("CharAt       // descending iteration", 1000) {
    static std::u32string s = the_little_prince_ch.Utf32String();
    for (int i=the_little_prince_ch.length()-1;i>=0;i--) {
        the_little_prince_ch.CharAt(i);
    }
}

BENCHMARK("check prefix & suffix", 1000) {
    String s("	当我还只有六岁的时候，在一本描写原始森林的名叫《真实的故事》的书中，看到了一副精彩的插画，画的是一条蟒蛇正在吞食一只大野兽。页头上就是那副画的摹本。");
    the_little_prince_ch.StartsWith(s);
}

BENCHMARK("check prefix & suffix    // static", 1000) {
    static String s("	当我还只有六岁的时候，在一本描写原始森林的名叫《真实的故事》的书中，看到了一副精彩的插画，画的是一条蟒蛇正在吞食一只大野兽。页头上就是那副画的摹本。");
    the_little_prince_ch.StartsWith(s);
}

BENCHMARK("copy", 1000) {
    String s(the_little_prince_ch);
}

BENCHMARK("+", 1000) {
    String s = the_little_prince_ch + the_little_prince_en;
}

BENCHMARK("+        // std::string", 1000) {
    static auto s1 = the_little_prince_ch.Utf8String();
    static auto s2 = the_little_prince_ch.Utf8String();
    auto s = s1 + s2;
}

BENCHMARK("trim", 1000) {
    the_little_prince_ch.Trim();
}

BENCHMARK("IndexOf", 1000) {
    the_little_prince_ch.IndexOf(String("测试他"));
}

BENCHMARK("IndexOf      // reuse the pattern", 1000) {
    static String s("测试他");
    the_little_prince_ch.IndexOf(s);
}

BENCHMARK("IndexOf      // single character", 1000) {
    the_little_prince_ch.IndexOf(u'球');
}

BENCHMARK("replace all", 1000) {
    the_little_prince_ch.ReplaceAll(String("他们"), String("They"));
}

BENCHMARK("replace all massive", 1) {
    String s = String("aaaaaaaaaa").ReplaceAll(String("a"), String("aaaaaaaaaa")).ReplaceAll(String("a"), String("aaaaaaaaaa")).ReplaceAll(String("a"), String("aaaaaaaaaa")).ReplaceAll(String("a"), String("aaaaaaaaaa"));
}

BENCHMARK("split", 100) {
    auto words = the_little_prince_en.Split(String(" ,.\"?:;\r\n"), true);
}

String the_little_prince_en {R"(    Once when I was six years old I saw a magnificent picture in a book, called True Stories from Nature, about the primeval forest. It was a picture of a boa constrictor in the act of swallowing an animal. Here is a copy of the drawing.
    
    In the book it said: "Boa constrictors swallow their prey whole, without chewing it. After that they are not able to move, and they sleep through the six months that they need for digestion."
    
    I pondered deeply, then, over the adventures of the jungle. And after some work with a colored pencil I succeeded in making my first drawing. My Drawing Number One. It looked like this:
    
    I showed my masterpiece to the grown-ups, and asked them whether the drawing frightened them.
    
    But they answered: "Frighten? Why should any one be frightened by a hat?"
    
    My drawing was not a picture of a hat. It was a picture of a boa constrictor digesting an elephant. But since the grown-ups were not able to understand it, I made another drawing: I drew the inside of the boa constrictor, so that the grown-ups could see it clearly. They always need to have things explained. My Drawing Number Two looked like this:
    
    The grown-ups' response, this time, was to advise me to lay aside my drawings of boa constrictors, whether from the inside or the outside, and devote myself instead to geography, history, arithmetic and grammar. That is why, at the age of six, I gave up what might have been a magnificent career as a painter. I had been disheartened by the failure of my Drawing Number One and my Drawing Number Two. Grown-ups never understand anything by themselves, and it is tiresome for children to be always and forever explaining things to them.
    
    So then I chose another profession, and learned to pilot airplanes. I have flown a little over all parts of the world; and it is true that geography has been very useful to me. At a glance I can distinguish China from Arizona. If one gets lost in the night, such knowledge is valuable.
    
    In the course of this life I have had a great many encounters with a great many people who have been concerned with matters of consequence. I have lived a great deal among grown-ups. I have seen them intimately, close at hand. And that hasn't much improved my opinion of them.
    
    Whenever I met one of them who seemed to me at all clear-sighted, I tried the experiment of showing him my Drawing Number One, which I have always kept. I would try to find out, so, if this was a person of true understanding. But, whoever it was, he, or she, would always say:
        
    "That is a hat."
        
    Then I would never talk to that person about boa constrictors, or primeval forests, or stars. I would bring myself down to his level. I would talk to him about bridge, and golf, and politics, and neckties. And the grown-up would be greatly pleased to have met such a sensible man.)"};

String the_little_prince_ch {R"(	当我还只有六岁的时候，在一本描写原始森林的名叫《真实的故事》的书中，看到了一副精彩的插画，画的是一条蟒蛇正在吞食一只大野兽。页头上就是那副画的摹本。

	这本书中写道：“这些蟒蛇把它们的猎获物不加咀嚼地囫囵吞下，尔后就不能再动弹了；它们就在长长的六个月的睡眠中消化这些食物。”

	当时，我对丛林中的奇遇想得很多，于是，我也用彩色铅笔画出了我的第一副图画。我的第一号作品。它是这样的：

	我把我的这副杰作拿给大人看，我问他们我的画是不是叫他们害怕。

	他们回答我说：“一顶帽子有什么可怕的？”

	我画的不是帽子，是一条巨蟒在消化着一头大象。于是我又把巨蟒肚子里的情况画了出来，以便让大人们能够看懂。这些大人总是需要解释。我的第二号作品是这样的：

	大人们劝我把这些画着开着肚皮的，或闭上肚皮的蟒蛇的图画放在一边，还是把兴趣放在地理、历史、算术、语法上。就这样，在六岁的那年，我就放弃了当画家这一美好的职业。我的第一号、第二号作品的不成功，使我泄了气。这些大人们，靠他们自己什么也弄不懂，还得老是不断地给他们作解释。这真叫孩子们腻味。

	后来，我只好选择了另外一个职业，我学会了开飞机，世界各地差不多都飞到过。的确，地理学帮了我很大的忙。我一眼就能分辨出中国和亚里桑那。要是夜里迷失了航向，这是很有用的。

	这样，在我的生活中，我跟许多严肃的人有过很多的接触。我在大人们中间生活过很长时间。我仔细地观察过他们，但这并没有使我对他们的看法有多大的改变。

	当我遇到一个头脑看来稍微清楚的大人时，我就拿出一直保存着的我那第一号作品来测试测试他。我想知道他是否真的有理解能力。可是，得到的回答总是：“这是顶帽子。”我就不和他谈巨蟒呀，原始森林呀，或者星星之类的事。我只得迁就他们的水平，和他们谈些桥牌呀，高尔夫球呀，政治呀，领带呀这些。于是大人们就十分高兴能认识我这样一个通情达理的人。)"};

END_TESTS()
