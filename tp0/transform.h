//
//  Francois Belanger 94 245 437
//
//  transform.h
//  tp0
//
//  Created by Fran�ois B�langer on 17-05-15.
//  Copyright � 2017. All rights reserved.
//

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <fstream>
#include <sstream>
//FIXME dev test
//#include <set>
#include <unordered_set>

//FIXME dev test
//#define KEYWORDS std::set<std::string> keywords = { "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case",\
//"catch", "char", "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else",\
//"enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "import", "long", "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq",\
//"nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "requires", "return", "short", "unsigned", "signed", "sizeof", "static", "static_assert",\
//"static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "using", "virtual", "void", "volatile",\
//"wchar_t", "while", "xor", "xor_eq" };

#define KEYWORDS std::unordered_set<std::string> keywords = { "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case",\
"catch", "char", "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else",\
"enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "import", "long", "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq",\
"nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "requires", "return", "short", "unsigned", "signed", "sizeof", "static", "static_assert",\
"static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "using", "virtual", "void", "volatile",\
"wchar_t", "while", "xor", "xor_eq" }

//TODO: passer au memory map
//milliseconds totalT0 = milliseconds{ 0 };
std::string t0(const std::string fname)
{
	//auto before = chrono::high_resolution_clock::now();
	std::ifstream file{ fname };
	std::stringstream ss;
	std::string line;
	std::string backslach_n{ '\n' };

	//TODO a reactiver
	//ss << fname << backslach_n;
	//TODO: fbr utiliser des iterateurs de stream
	while (getline(file, line))
		ss << line << backslach_n;

	//totalT0 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
	return ss.str();
}

//TODO: passer par mouvement?
//TODO: retour par mouvement?
//milliseconds totalT1 = milliseconds{ 0 };
std::string t1(std::string& toClean)
{
	//auto before = chrono::high_resolution_clock::now();
	//TODO: a remanier.
	std::ostringstream out;
	std::string amp{"&amp"};
	std::string less{"&lt"};
	std::string more{ "&gt" };
	for (auto x : toClean)
	{
		if (x == '&')
			out << amp;
		else if (x == '<')
			out << less;
		else if (x == '>')
			out << more;
		else
			out << x;

	}
	//totalT1 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
	return out.str();
}

std::string t2(std::string& inLine, const std::unordered_set<std::string>& keywords)
{
	//auto before = chrono::high_resolution_clock::now();
	const std::string spanOpen = "<span id=\"t2\">";
	const std::string spanClose = "</span>";
	std::string word;

	std::istringstream i{ inLine };
	std::ostringstream o;

	auto lastIdx = i.tellg();
	int lookAhead = i.peek();
	while (lookAhead != EOF)
	{
		if ((lookAhead >= 'a' && lookAhead <= 'z') || (lookAhead >= 'A' && lookAhead <= 'Z') || (lookAhead >= '0' && lookAhead <= '9') || lookAhead == '_')
		{
			word.push_back(i.get());
		}
		else
		{
			if (keywords.count(word)==1)
			{
				o << spanOpen << word << spanClose;
			}
			else
			{
				o << word;
			}
			word.clear();

			while (!(lookAhead >= 'a' && lookAhead <= 'z') && !(lookAhead >= 'A' && lookAhead <= 'Z') && !(lookAhead >= '0' && lookAhead <= '9') && lookAhead != '_' && lookAhead != EOF)
			{
				word.push_back(i.get());
				lookAhead = i.peek();
			}
			o << word;
			word.clear();
		}
		lookAhead = i.peek();
	}

	o << '\n';
	//std::cout << o.str();
	//totalT2 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
	return o.str();
}

//TODO: a refaire
////milliseconds totalT3 = milliseconds{ 0 };
//std::string t3(std::string& inFile)
//{
//	//auto before = chrono::high_resolution_clock::now();
//
//	std::string spanOpen = "<span id=\"t3\">";
//	std::string spanClose = "</span>";
//	for (std::string::size_type i = 0; (i = inFile.find("//", i)) != std::string::npos;)
//	{
//		inFile.insert(i, spanOpen);
//		i += spanOpen.length();
//		auto end = inFile.find("\n", i);
//		i = end;
//		inFile.insert(end + 1, spanClose);
//		i += spanClose.length();
//	}
//	for (std::string::size_type i = 0; (i = inFile.find("/*", i)) != std::string::npos;)
//	{
//		inFile.insert(i, spanOpen);
//		i += spanOpen.length();
//		auto end = inFile.find("*/", i);
//		i = end;
//		inFile.insert(end + 2, spanClose);
//		i += spanClose.length();
//	}
//
//
//	//totalT3 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
//	return inFile;
//}
//milliseconds totalT3 = milliseconds{ 0 };
std::string t3(std::string& inFile)
{
	//auto before = chrono::high_resolution_clock::now();

	std::string spanOpen = "<span id=\"t3\">";
	std::string spanClose = "</span>";

	std::string word;
	std::istringstream i{ inFile };
	std::ostringstream o;
	int lookAhead = i.peek();

	while (lookAhead != EOF)
	{
		while (lookAhead != '/' && lookAhead != EOF)
		{
			word.push_back(i.get());
			lookAhead = i.peek();
		}
		o << word;
		word.clear();
		word.push_back(i.get());
		lookAhead = i.peek();

		if (lookAhead == '/')
		{
			word = spanOpen + word;
			while (lookAhead != '\n' && lookAhead != EOF)
			{
				word.push_back(i.get());
				lookAhead = i.peek();
			}
			word += spanClose;
			o << word;
			word.clear();
		}
		else if (lookAhead == '*')
		{
			word = spanOpen + word;
			while (lookAhead != '/' && lookAhead != EOF)
			{
				if (word.back() == '*')
				{
					word.push_back(i.get());
					break;
				}
				word.push_back(i.get());
				lookAhead = i.peek();
			}
			word += spanClose;
			o << word;
			word.clear();
		}
		lookAhead = i.peek();
	}

	for (std::string::size_type i = 0; (i = inFile.find("//", i)) != std::string::npos;)
	{
		inFile.insert(i, spanOpen);
		i += spanOpen.length();
		auto end = inFile.find("\n", i);
		i = end;
		inFile.insert(end + 1, spanClose);
		i += spanClose.length();
	}
	for (std::string::size_type i = 0; (i = inFile.find("/*", i)) != std::string::npos;)
	{
		inFile.insert(i, spanOpen);
		i += spanOpen.length();
		auto end = inFile.find("*/", i);
		i = end;
		inFile.insert(end + 2, spanClose);
		i += spanClose.length();
	}


	//totalT3 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
	return inFile;
}

//TODO: a refaire
//milliseconds totalT4 = milliseconds{ 0 };
std::string t4(std::string& inFile)
{
	//auto before = chrono::high_resolution_clock::now();

	std::string spanOpen = "<span style = 'color:purple'>";
	std::string spanClose = "</span>";
	for (std::string::size_type i = 0; (i = inFile.find("#", i)) != std::string::npos;)
	{
		inFile.insert(i, spanOpen);
		i += spanOpen.length();
		auto end = inFile.find(" ", i);
		i = end;
		inFile.insert(end, spanClose);
		i += spanClose.length();
	}

	//totalT4 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
	return inFile;
}


//FIXME dev test
//#define HEADER_1 std::string{"<!DOCTYPE html>\n<html>\n<head>\n<title>"}
//#define HEADER_2 std::string{"</title>\n<link rel=\"stylesheet\" type=\"text/css\" href=\"tp0.css\">\n</head>\n<body>\n<pre>"}
//#define FOOTER std::string{"</pre>\n</body>\n</html>"}
std::string HEADER_1{ "<!DOCTYPE html>\n<html>\n<head>\n<title>" };
std::string	HEADER_2{ "</title>\n<link rel=\"stylesheet\" type=\"text/css\" href=\"tp0.css\">\n</head>\n<body>\n<pre>" };
std::string FOOTER{"</pre>\n</body>\n</html>"};
//TODO: faire le menage dans les parametres
//milliseconds totalT5 = milliseconds{ 0 };
void t5(const std::string& fname, const std::string& data, bool concurrent)
{
	//auto before = chrono::high_resolution_clock::now();
	std::ofstream file{ fname + (concurrent ? ".parallele.html" : ".sequential.html") };

	//header
	//file << "<!DOCTYPE html>\n<html>\n<head>\n";
	//file << "<title>" << fname << "</title>\n";
	//file << "<link rel=\"stylesheet\" type=\"text/css\" href=\"tp0.css\">\n";
	//file << "</head>\n<body>\n<pre>";
	file << HEADER_1;
	file << fname << HEADER_2;

	//decorated lines
	file << data;

	//end tag
	file << FOOTER;

	//totalT5 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
}

#endif // !_TRANSFORM_H_

