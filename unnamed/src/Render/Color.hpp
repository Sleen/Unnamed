#pragma once

#include <string>
#include <unordered_map>

#include "Base/Exception.hpp"

namespace me {

#ifdef RGB
#	undef RGB
#endif

#define A(c) ((c>>24)&0xff)
#define R(c) ((c>>16)&0xff)
#define G(c) ((c>>8)&0xff)
#define B(c) (c&0xff)

#define AF(c) (A(c)/255.0f)
#define RF(c) (R(c)/255.0f)
#define GF(c) (G(c)/255.0f)
#define BF(c) (B(c)/255.0f)

#define RGB(c) R(c), G(c), B(c)
#define ARGB(c) A(c), R(c), G(c), B(c)
#define RGBA(c) R(c), G(c), B(c), A(c)
#define RGBF(c) RF(c), GF(c), BF(c)
#define ARGBF(c) AF(c), RF(c), GF(c), BF(c)
#define RGBAF(c) RF(c), GF(c), BF(c), AF(c)

	class Color
	{
	public:
		//private:
		//    int color;
		//
		//public:
		//    Color(){
		//        color = 0;
		//    }
		//
		//    operator int(){
		//        return color;
		//    }
		//
		//    Color(int color){
		//        this->color = color;
		//    }
		//
		//    Color operator+(const Color& c){
		//        return (min(255, A(color) + A(c.color))) << 24
		//            | (min(255, R(color) + R(c.color))) << 16
		//            | (min(255, G(color) + G(c.color))) << 8
		//            | (min(255, B(color) + B(c.color)));
		//    }
		//
		//    Color operator-(const Color& c){
		//        return (max(0, A(color) - A(c.color))) << 24
		//            | (max(0, R(color) - R(c.color))) << 16
		//            | (max(0, G(color) - G(c.color))) << 8
		//            | (max(0, B(color) - B(c.color)));
		//    }
		//
		//    Color operator*(float s){
		//        return min(255, max(0, (int)(A(color) * s))) << 24
		//            | min(255, max(0, (int)(R(color) * s))) << 16
		//            | min(255, max(0, (int)(G(color) * s))) << 8
		//            | min(255, max(0, (int)(B(color) * s)));
		//    }
		//
		const static int Transparent = 0x00000000; 	// 0x00000000
		const static int AliceBlue = 0xFFF0F8FF; 	// 0xFFF0F8FF
		const static int AntiqueWhite = 0xFFFAEBD7; 	// 0xFFFAEBD7
		const static int Aqua = 0xFF00FFFF; 	// 0xFF00FFFF
		const static int Aquamarine = 0xFF7FFFD4; 	// 0xFF7FFFD4
		const static int Azure = 0xFFF0FFFF; 	// 0xFFF0FFFF
		const static int Beige = 0xFFF5F5DC; 	// 0xFFF5F5DC
		const static int Bisque = 0xFFFFE4C4; 	// 0xFFFFE4C4
		const static int Black = 0xFF000000; 	// 0xFF000000
		const static int BlanchedAlmond = 0xFFFFEBCD; 	// 0xFFFFEBCD
		const static int Blue = 0xFF0000FF; 	// 0xFF0000FF
		const static int BlueViolet = 0xFF8A2BE2; 	// 0xFF8A2BE2
		const static int Brown = 0xFFA52A2A; 	// 0xFFA52A2A
		const static int BurlyWood = 0xFFDEB887; 	// 0xFFDEB887
		const static int CadetBlue = 0xFF5F9EA0; 	// 0xFF5F9EA0
		const static int Chartreuse = 0xFF7FFF00; 	// 0xFF7FFF00
		const static int Chocolate = 0xFFD2691E; 	// 0xFFD2691E
		const static int Coral = 0xFFFF7F50; 	// 0xFFFF7F50
		const static int CornflowerBlue = 0xFF6495ED; 	// 0xFF6495ED
		const static int Cornsilk = 0xFFFFF8DC; 	// 0xFFFFF8DC
		const static int Crimson = 0xFFDC143C; 	// 0xFFDC143C
		const static int Cyan = 0xFF00FFFF; 	// 0xFF00FFFF
		const static int DarkBlue = 0xFF00008B; 	// 0xFF00008B
		const static int DarkCyan = 0xFF008B8B; 	// 0xFF008B8B
		const static int DarkGoldenrod = 0xFFB8860B; 	// 0xFFB8860B
		const static int DarkGray = 0xFFA9A9A9; 	// 0xFFA9A9A9
		const static int DarkGreen = 0xFF006400; 	// 0xFF006400
		const static int DarkKhaki = 0xFFBDB76B; 	// 0xFFBDB76B
		const static int DarkMagenta = 0xFF8B008B; 	// 0xFF8B008B
		const static int DarkOliveGreen = 0xFF556B2F; 	// 0xFF556B2F
		const static int DarkOrange = 0xFFFF8C00; 	// 0xFFFF8C00
		const static int DarkOrchid = 0xFF9932CC; 	// 0xFF9932CC
		const static int DarkRed = 0xFF8B0000; 	// 0xFF8B0000
		const static int DarkSalmon = 0xFFE9967A; 	// 0xFFE9967A
		const static int DarkSeaGreen = 0xFF8FBC8B; 	// 0xFF8FBC8B
		const static int DarkSlateBlue = 0xFF483D8B; 	// 0xFF483D8B
		const static int DarkSlateGray = 0xFF2F4F4F; 	// 0xFF2F4F4F
		const static int DarkTurquoise = 0xFF00CED1; 	// 0xFF00CED1
		const static int DarkViolet = 0xFF9400D3; 	// 0xFF9400D3
		const static int DeepPink = 0xFFFF1493; 	// 0xFFFF1493
		const static int DeepSkyBlue = 0xFF00BFFF; 	// 0xFF00BFFF
		const static int DimGray = 0xFF696969; 	// 0xFF696969
		const static int DodgerBlue = 0xFF1E90FF; 	// 0xFF1E90FF
		const static int Firebrick = 0xFFB22222; 	// 0xFFB22222
		const static int FloralWhite = 0xFFFFFAF0; 	// 0xFFFFFAF0
		const static int ForestGreen = 0xFF228B22; 	// 0xFF228B22
		const static int Fuchsia = 0xFFFF00FF; 	// 0xFFFF00FF
		const static int Gainsboro = 0xFFDCDCDC; 	// 0xFFDCDCDC
		const static int GhostWhite = 0xFFF8F8FF; 	// 0xFFF8F8FF
		const static int Gold = 0xFFFFD700; 	// 0xFFFFD700
		const static int Goldenrod = 0xFFDAA520; 	// 0xFFDAA520
		const static int Gray = 0xFF808080; 	// 0xFF808080
		const static int Green = 0xFF008000; 	// 0xFF008000
		const static int GreenYellow = 0xFFADFF2F; 	// 0xFFADFF2F
		const static int Honeydew = 0xFFF0FFF0; 	// 0xFFF0FFF0
		const static int HotPink = 0xFFFF69B4; 	// 0xFFFF69B4
		const static int IndianRed = 0xFFCD5C5C; 	// 0xFFCD5C5C
		const static int Indigo = 0xFF4B0082; 	// 0xFF4B0082
		const static int Ivory = 0xFFFFFFF0; 	// 0xFFFFFFF0
		const static int Khaki = 0xFFF0E68C; 	// 0xFFF0E68C
		const static int Lavender = 0xFFE6E6FA; 	// 0xFFE6E6FA
		const static int LavenderBlush = 0xFFFFF0F5; 	// 0xFFFFF0F5
		const static int LawnGreen = 0xFF7CFC00; 	// 0xFF7CFC00
		const static int LemonChiffon = 0xFFFFFACD; 	// 0xFFFFFACD
		const static int LightBlue = 0xFFADD8E6; 	// 0xFFADD8E6
		const static int LightCoral = 0xFFF08080; 	// 0xFFF08080
		const static int LightCyan = 0xFFE0FFFF; 	// 0xFFE0FFFF
		const static int LightGoldenrodYellow = 0xFFFAFAD2; 	// 0xFFFAFAD2
		const static int LightGreen = 0xFF90EE90; 	// 0xFF90EE90
		const static int LightGray = 0xFFD3D3D3; 	// 0xFFD3D3D3
		const static int LightPink = 0xFFFFB6C1; 	// 0xFFFFB6C1
		const static int LightSalmon = 0xFFFFA07A; 	// 0xFFFFA07A
		const static int LightSeaGreen = 0xFF20B2AA; 	// 0xFF20B2AA
		const static int LightSkyBlue = 0xFF87CEFA; 	// 0xFF87CEFA
		const static int LightSlateGray = 0xFF778899; 	// 0xFF778899
		const static int LightSteelBlue = 0xFFB0C4DE; 	// 0xFFB0C4DE
		const static int LightYellow = 0xFFFFFFE0; 	// 0xFFFFFFE0
		const static int Lime = 0xFF00FF00; 	// 0xFF00FF00
		const static int LimeGreen = 0xFF32CD32; 	// 0xFF32CD32
		const static int Linen = 0xFFFAF0E6; 	// 0xFFFAF0E6
		const static int Magenta = 0xFFFF00FF; 	// 0xFFFF00FF
		const static int Maroon = 0xFF800000; 	// 0xFF800000
		const static int MediumAquamarine = 0xFF66CDAA; 	// 0xFF66CDAA
		const static int MediumBlue = 0xFF0000CD; 	// 0xFF0000CD
		const static int MediumOrchid = 0xFFBA55D3; 	// 0xFFBA55D3
		const static int MediumPurple = 0xFF9370DB; 	// 0xFF9370DB
		const static int MediumSeaGreen = 0xFF3CB371; 	// 0xFF3CB371
		const static int MediumSlateBlue = 0xFF7B68EE; 	// 0xFF7B68EE
		const static int MediumSpringGreen = 0xFF00FA9A; 	// 0xFF00FA9A
		const static int MediumTurquoise = 0xFF48D1CC; 	// 0xFF48D1CC
		const static int MediumVioletRed = 0xFFC71585; 	// 0xFFC71585
		const static int MidnightBlue = 0xFF191970; 	// 0xFF191970
		const static int MintCream = 0xFFF5FFFA; 	// 0xFFF5FFFA
		const static int MistyRose = 0xFFFFE4E1; 	// 0xFFFFE4E1
		const static int Moccasin = 0xFFFFE4B5; 	// 0xFFFFE4B5
		const static int NavajoWhite = 0xFFFFDEAD; 	// 0xFFFFDEAD
		const static int Navy = 0xFF000080; 	// 0xFF000080
		const static int OldLace = 0xFFFDF5E6; 	// 0xFFFDF5E6
		const static int Olive = 0xFF808000; 	// 0xFF808000
		const static int OliveDrab = 0xFF6B8E23; 	// 0xFF6B8E23
		const static int Orange = 0xFFFFA500; 	// 0xFFFFA500
		const static int OrangeRed = 0xFFFF4500; 	// 0xFFFF4500
		const static int Orchid = 0xFFDA70D6; 	// 0xFFDA70D6
		const static int PaleGoldenrod = 0xFFEEE8AA; 	// 0xFFEEE8AA
		const static int PaleGreen = 0xFF98FB98; 	// 0xFF98FB98
		const static int PaleTurquoise = 0xFFAFEEEE; 	// 0xFFAFEEEE
		const static int PaleVioletRed = 0xFFDB7093; 	// 0xFFDB7093
		const static int PapayaWhip = 0xFFFFEFD5; 	// 0xFFFFEFD5
		const static int PeachPuff = 0xFFFFDAB9; 	// 0xFFFFDAB9
		const static int Peru = 0xFFCD853F; 	// 0xFFCD853F
		const static int Pink = 0xFFFFC0CB; 	// 0xFFFFC0CB
		const static int Plum = 0xFFDDA0DD; 	// 0xFFDDA0DD
		const static int PowderBlue = 0xFFB0E0E6; 	// 0xFFB0E0E6
		const static int Purple = 0xFF800080; 	// 0xFF800080
		const static int Red = 0xFFFF0000; 	// 0xFFFF0000
		const static int RosyBrown = 0xFFBC8F8F; 	// 0xFFBC8F8F
		const static int RoyalBlue = 0xFF4169E1; 	// 0xFF4169E1
		const static int SaddleBrown = 0xFF8B4513; 	// 0xFF8B4513
		const static int Salmon = 0xFFFA8072; 	// 0xFFFA8072
		const static int SandyBrown = 0xFFF4A460; 	// 0xFFF4A460
		const static int SeaGreen = 0xFF2E8B57; 	// 0xFF2E8B57
		const static int SeaShell = 0xFFFFF5EE; 	// 0xFFFFF5EE
		const static int Sienna = 0xFFA0522D; 	// 0xFFA0522D
		const static int Silver = 0xFFC0C0C0; 	// 0xFFC0C0C0
		const static int SkyBlue = 0xFF87CEEB; 	// 0xFF87CEEB
		const static int SlateBlue = 0xFF6A5ACD; 	// 0xFF6A5ACD
		const static int SlateGray = 0xFF708090; 	// 0xFF708090
		const static int Snow = 0xFFFFFAFA; 	// 0xFFFFFAFA
		const static int SpringGreen = 0xFF00FF7F; 	// 0xFF00FF7F
		const static int SteelBlue = 0xFF4682B4; 	// 0xFF4682B4
		const static int Tan = 0xFFD2B48C; 	// 0xFFD2B48C
		const static int Teal = 0xFF008080; 	// 0xFF008080
		const static int Thistle = 0xFFD8BFD8; 	// 0xFFD8BFD8
		const static int Tomato = 0xFFFF6347; 	// 0xFFFF6347
		const static int Turquoise = 0xFF40E0D0; 	// 0xFF40E0D0
		const static int Violet = 0xFFEE82EE; 	// 0xFFEE82EE
		const static int Wheat = 0xFFF5DEB3; 	// 0xFFF5DEB3
		const static int White = 0xFFFFFFFF; 	// 0xFFFFFFFF
		const static int WhiteSmoke = 0xFFF5F5F5; 	// 0xFFF5F5F5
		const static int Yellow = 0xFFFFFF00; 	// 0xFFFFFF00
		const static int YellowGreen = 0xFF9ACD32; 	// 0xFF9ACD32

		static int FromArgb(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue) {
			return (alpha << 24) | (red << 16) | (green << 8) | blue;
		}

		static int FromRgb(unsigned char red, unsigned char green, unsigned char blue) {
			return 0xff000000 | (red << 16) | (green << 8) | blue;
		}

		static int AlphaColor(float alpha, int color) {
			return ((int)(AF(color) * alpha * 255) << 24) | (color & 0x00ffffff);
		}

		static const std::unordered_map<std::string, int>& ColorMap() {
			static std::unordered_map<std::string, int> map;
			if (map.empty()) {
				map.insert(std::make_pair("transparent", 0x00000000));
				map.insert(std::make_pair("aliceblue", 0xfff0f8ff));
				map.insert(std::make_pair("antiquewhite", 0xfffaebd7));
				map.insert(std::make_pair("aqua", 0xff00ffff));
				map.insert(std::make_pair("aquamarine", 0xff7fffd4));
				map.insert(std::make_pair("azure", 0xfff0ffff));
				map.insert(std::make_pair("beige", 0xfff5f5dc));
				map.insert(std::make_pair("bisque", 0xffffe4c4));
				map.insert(std::make_pair("black", 0xff000000));
				map.insert(std::make_pair("blanchedalmond", 0xffffebcd));
				map.insert(std::make_pair("blue", 0xff0000ff));
				map.insert(std::make_pair("blueviolet", 0xff8a2be2));
				map.insert(std::make_pair("brown", 0xffa52a2a));
				map.insert(std::make_pair("burlywood", 0xffdeb887));
				map.insert(std::make_pair("cadetblue", 0xff5f9ea0));
				map.insert(std::make_pair("chartreuse", 0xff7fff00));
				map.insert(std::make_pair("chocolate", 0xffd2691e));
				map.insert(std::make_pair("coral", 0xffff7f50));
				map.insert(std::make_pair("cornflowerblue", 0xff6495ed));
				map.insert(std::make_pair("cornsilk", 0xfffff8dc));
				map.insert(std::make_pair("crimson", 0xffdc143c));
				map.insert(std::make_pair("cyan", 0xff00ffff));
				map.insert(std::make_pair("darkblue", 0xff00008b));
				map.insert(std::make_pair("darkcyan", 0xff008b8b));
				map.insert(std::make_pair("darkgoldenrod", 0xffb8860b));
				map.insert(std::make_pair("darkgray", 0xffa9a9a9));
				map.insert(std::make_pair("darkgreen", 0xff006400));
				map.insert(std::make_pair("darkkhaki", 0xffbdb76b));
				map.insert(std::make_pair("darkmagenta", 0xff8b008b));
				map.insert(std::make_pair("darkolivegreen", 0xff556b2f));
				map.insert(std::make_pair("darkorange", 0xffff8c00));
				map.insert(std::make_pair("darkorchid", 0xff9932cc));
				map.insert(std::make_pair("darkred", 0xff8b0000));
				map.insert(std::make_pair("darksalmon", 0xffe9967a));
				map.insert(std::make_pair("darkseagreen", 0xff8fbc8b));
				map.insert(std::make_pair("darkslateblue", 0xff483d8b));
				map.insert(std::make_pair("darkslategray", 0xff2f4f4f));
				map.insert(std::make_pair("darkturquoise", 0xff00ced1));
				map.insert(std::make_pair("darkviolet", 0xff9400d3));
				map.insert(std::make_pair("deeppink", 0xffff1493));
				map.insert(std::make_pair("deepskyblue", 0xff00bfff));
				map.insert(std::make_pair("dimgray", 0xff696969));
				map.insert(std::make_pair("dodgerblue", 0xff1e90ff));
				map.insert(std::make_pair("firebrick", 0xffb22222));
				map.insert(std::make_pair("floralwhite", 0xfffffaf0));
				map.insert(std::make_pair("forestgreen", 0xff228b22));
				map.insert(std::make_pair("fuchsia", 0xffff00ff));
				map.insert(std::make_pair("gainsboro", 0xffdcdcdc));
				map.insert(std::make_pair("ghostwhite", 0xfff8f8ff));
				map.insert(std::make_pair("gold", 0xffffd700));
				map.insert(std::make_pair("goldenrod", 0xffdaa520));
				map.insert(std::make_pair("gray", 0xff808080));
				map.insert(std::make_pair("green", 0xff008000));
				map.insert(std::make_pair("greenyellow", 0xffadff2f));
				map.insert(std::make_pair("honeydew", 0xfff0fff0));
				map.insert(std::make_pair("hotpink", 0xffff69b4));
				map.insert(std::make_pair("indianred", 0xffcd5c5c));
				map.insert(std::make_pair("indigo", 0xff4b0082));
				map.insert(std::make_pair("ivory", 0xfffffff0));
				map.insert(std::make_pair("khaki", 0xfff0e68c));
				map.insert(std::make_pair("lavender", 0xffe6e6fa));
				map.insert(std::make_pair("lavenderblush", 0xfffff0f5));
				map.insert(std::make_pair("lawngreen", 0xff7cfc00));
				map.insert(std::make_pair("lemonchiffon", 0xfffffacd));
				map.insert(std::make_pair("lightblue", 0xffadd8e6));
				map.insert(std::make_pair("lightcoral", 0xfff08080));
				map.insert(std::make_pair("lightcyan", 0xffe0ffff));
				map.insert(std::make_pair("lightgoldenrodyellow", 0xfffafad2));
				map.insert(std::make_pair("lightgreen", 0xff90ee90));
				map.insert(std::make_pair("lightgray", 0xffd3d3d3));
				map.insert(std::make_pair("lightpink", 0xffffb6c1));
				map.insert(std::make_pair("lightsalmon", 0xffffa07a));
				map.insert(std::make_pair("lightseagreen", 0xff20b2aa));
				map.insert(std::make_pair("lightskyblue", 0xff87cefa));
				map.insert(std::make_pair("lightslategray", 0xff778899));
				map.insert(std::make_pair("lightsteelblue", 0xffb0c4de));
				map.insert(std::make_pair("lightyellow", 0xffffffe0));
				map.insert(std::make_pair("lime", 0xff00ff00));
				map.insert(std::make_pair("limegreen", 0xff32cd32));
				map.insert(std::make_pair("linen", 0xfffaf0e6));
				map.insert(std::make_pair("magenta", 0xffff00ff));
				map.insert(std::make_pair("maroon", 0xff800000));
				map.insert(std::make_pair("mediumaquamarine", 0xff66cdaa));
				map.insert(std::make_pair("mediumblue", 0xff0000cd));
				map.insert(std::make_pair("mediumorchid", 0xffba55d3));
				map.insert(std::make_pair("mediumpurple", 0xff9370db));
				map.insert(std::make_pair("mediumseagreen", 0xff3cb371));
				map.insert(std::make_pair("mediumslateblue", 0xff7b68ee));
				map.insert(std::make_pair("mediumspringgreen", 0xff00fa9a));
				map.insert(std::make_pair("mediumturquoise", 0xff48d1cc));
				map.insert(std::make_pair("mediumvioletred", 0xffc71585));
				map.insert(std::make_pair("midnightblue", 0xff191970));
				map.insert(std::make_pair("mintcream", 0xfff5fffa));
				map.insert(std::make_pair("mistyrose", 0xffffe4e1));
				map.insert(std::make_pair("moccasin", 0xffffe4b5));
				map.insert(std::make_pair("navajowhite", 0xffffdead));
				map.insert(std::make_pair("navy", 0xff000080));
				map.insert(std::make_pair("oldlace", 0xfffdf5e6));
				map.insert(std::make_pair("olive", 0xff808000));
				map.insert(std::make_pair("olivedrab", 0xff6b8e23));
				map.insert(std::make_pair("orange", 0xffffa500));
				map.insert(std::make_pair("orangered", 0xffff4500));
				map.insert(std::make_pair("orchid", 0xffda70d6));
				map.insert(std::make_pair("palegoldenrod", 0xffeee8aa));
				map.insert(std::make_pair("palegreen", 0xff98fb98));
				map.insert(std::make_pair("paleturquoise", 0xffafeeee));
				map.insert(std::make_pair("palevioletred", 0xffdb7093));
				map.insert(std::make_pair("papayawhip", 0xffffefd5));
				map.insert(std::make_pair("peachpuff", 0xffffdab9));
				map.insert(std::make_pair("peru", 0xffcd853f));
				map.insert(std::make_pair("pink", 0xffffc0cb));
				map.insert(std::make_pair("plum", 0xffdda0dd));
				map.insert(std::make_pair("powderblue", 0xffb0e0e6));
				map.insert(std::make_pair("purple", 0xff800080));
				map.insert(std::make_pair("red", 0xffff0000));
				map.insert(std::make_pair("rosybrown", 0xffbc8f8f));
				map.insert(std::make_pair("royalblue", 0xff4169e1));
				map.insert(std::make_pair("saddlebrown", 0xff8b4513));
				map.insert(std::make_pair("salmon", 0xfffa8072));
				map.insert(std::make_pair("sandybrown", 0xfff4a460));
				map.insert(std::make_pair("seagreen", 0xff2e8b57));
				map.insert(std::make_pair("seashell", 0xfffff5ee));
				map.insert(std::make_pair("sienna", 0xffa0522d));
				map.insert(std::make_pair("silver", 0xffc0c0c0));
				map.insert(std::make_pair("skyblue", 0xff87ceeb));
				map.insert(std::make_pair("slateblue", 0xff6a5acd));
				map.insert(std::make_pair("slategray", 0xff708090));
				map.insert(std::make_pair("snow", 0xfffffafa));
				map.insert(std::make_pair("springgreen", 0xff00ff7f));
				map.insert(std::make_pair("steelblue", 0xff4682b4));
				map.insert(std::make_pair("tan", 0xffd2b48c));
				map.insert(std::make_pair("teal", 0xff008080));
				map.insert(std::make_pair("thistle", 0xffd8bfd8));
				map.insert(std::make_pair("tomato", 0xffff6347));
				map.insert(std::make_pair("turquoise", 0xff40e0d0));
				map.insert(std::make_pair("violet", 0xffee82ee));
				map.insert(std::make_pair("wheat", 0xfff5deb3));
				map.insert(std::make_pair("white", 0xffffffff));
				map.insert(std::make_pair("whitesmoke", 0xfff5f5f5));
				map.insert(std::make_pair("yellow", 0xffffff00));
				map.insert(std::make_pair("yellowgreen", 0xff9acd32));
			}
			return map;
		}

	private:
		static int from_hex(char c) {
			if (isdigit(c)) {
				return c - '0';
			}
			else if (c >= 'A' && c <= 'F') {
				return c - 'A' + 10;
			}
			else if (c >= 'a' && c <= 'f') {
				return c - 'a' + 10;
			}

			THROW(FormatException, "'" + std::string(1, c) + "' is not a valid hexadecimal number");
		}

		static int from_hex(const std::string& str) {
			int r = 0;
			for (int i = 0; i < str.length(); i++) {
				int n = from_hex(str[i]);
				r *= 16;
				r += n;
			}
			return r;
		}

	public:
		static int FromName(const std::string& name) {
			if (!name.empty()) {
				if (name[0] == '#') {
					try {
						if (name.length() == 4) {
							return FromRgb(
								from_hex(name[1]) * 255 / 15,
								from_hex(name[2]) * 255 / 15,
								from_hex(name[3]) * 255 / 15);
						}
						else if (name.length() == 5) {
							return FromArgb(
								from_hex(name[1]) * 255 / 15,
								from_hex(name[2]) * 255 / 15,
								from_hex(name[3]) * 255 / 15,
								from_hex(name[4]) * 255 / 15);
						}
						else if (name.length() == 7) {
							return FromRgb(
								from_hex(name.substr(1, 2)),
								from_hex(name.substr(3, 2)),
								from_hex(name.substr(5, 2)));
						}
						else if (name.length() == 9) {
							return FromArgb(
								from_hex(name.substr(1, 2)),
								from_hex(name.substr(3, 2)),
								from_hex(name.substr(5, 2)),
								from_hex(name.substr(7, 2)));
						}
					}
					catch (const FormatException& ex) {
						THROW(FormatException, "'" + name + "' is not a valid color");
					}
				}
				else {
					auto& map = ColorMap();
					auto r = map.find(StringHelper::ToLower(name));
					if (r != map.end()) {
						return r->second;
					}
				}
			}

			THROW(FormatException, "'" + name + "' is not a valid color");
		}
	};

}
