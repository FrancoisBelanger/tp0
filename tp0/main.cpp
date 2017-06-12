//
//  Francois Belanger 94 245 437
//
//  main.cpp
//  tp0
//
//  Created by François Bélanger on 17-05-15.
//  Copyright © 2017. All rights reserved.
//

//TODO: fbr to remove
#include <iostream>

#include <fstream>
#include <sstream>
#include <chrono>
//TODO faire le menage
#include <algorithm>
#include <set>

using namespace std;
using namespace chrono;

#define KEYWORDS set<string> keywords = { "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case",\
"catch", "char", "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else",\
"enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "import", "long", "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq",\
"nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "requires", "return", "short", "unsigned", "signed", "sizeof", "static", "static_assert",\
"static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "using", "virtual", "void", "volatile",\
"wchar_t", "while", "xor", "xor_eq" };


//TODO: passer au memory map
//milliseconds totalT0 = milliseconds{ 0 };
string t0(const string fname)
{
	//auto before = chrono::high_resolution_clock::now();
	ifstream file{ fname };
	stringstream ss;
	string line;
	string backslach_n{ '\n' };

	//TODO: fbr utiliser des iterateurs de stream
	while (getline(file, line))
		ss << line << backslach_n;

	//totalT0 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
	return ss.str();
}

//milliseconds totalT1 = milliseconds{ 0 };
string t1(string& toClean)
{
	//auto before = chrono::high_resolution_clock::now();
	//TODO: a remanier.
	for (string::size_type i = 0; (i = toClean.find("&", i)) != string::npos;)
	{
		toClean.replace(i, string{ "&" }.length(), "&amp;");
		i += string{ "&amp;" }.length();
	}
	for (string::size_type i = 0; (i = toClean.find("<", i)) != string::npos;)
	{
		toClean.replace(i, string{ "<" }.length(), "&lt;");
		i += string{ "&lt;" }.length();
	}
	for (string::size_type i = 0; (i = toClean.find(">", i)) != string::npos;)
	{
		toClean.replace(i, string{ ">" }.length(), "&gt;");
		i += string{ "&gt;" }.length();
	}

	//totalT1 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
	return toClean;
}

//milliseconds totalT2 = milliseconds{ 0 };
string t2(string& inLine)
{
	//auto before = chrono::high_resolution_clock::now();
	string spanOpen = "<span id=\"t2\">";
	string spanClose = "</span>";
	string word;
	KEYWORDS;

	istringstream i{ inLine };
	ostringstream o;
	bool tag = false;

	auto lastIdx = i.tellg();
	while (i >> word)
	{
		//cout << i.tellg() - lastIdx << " " << (i.tellg() - lastIdx) - word.length() << endl;
		//ajouter les char manquant
		o << inLine.substr(lastIdx, (i.tellg() - lastIdx) - word.length());
		if (keywords.find(word) != end(keywords))
		{
			o << spanOpen << word << spanClose;
		}
		else
		{
			o << word;
		}
		lastIdx = i.tellg();
	}
	o << '\n';

	//totalT2 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
	return o.str();
}

//TODO: a refaire
//milliseconds totalT3 = milliseconds{ 0 };
string t3(string& inFile)
{
	//auto before = chrono::high_resolution_clock::now();

	string spanOpen = "<span id=\"t3\">";
	string spanClose = "</span>";
	for (string::size_type i = 0; (i = inFile.find("//", i)) != string::npos;)
	{
		inFile.insert(i, spanOpen);
		i += spanOpen.length();
		auto end = inFile.find("\n", i);
		i = end;
		inFile.insert(end + 1, spanClose);
		i += spanClose.length();
	}
	for (string::size_type i = 0; (i = inFile.find("/*", i)) != string::npos;)
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
string t4(string& inFile)
{
	auto before = chrono::high_resolution_clock::now();

	string spanOpen = "<span style = 'color:purple'>";
	string spanClose = "</span>";
	for (string::size_type i = 0; (i = inFile.find("#", i)) != string::npos;)
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

//TODO: a templater sur le type de process?
//milliseconds totalT5 = milliseconds{ 0 };
void t5(const string& fname, const string& data)
{
	//auto before = chrono::high_resolution_clock::now();
	//TODO: ajouter le type d'execution en parametre
	ofstream file{ fname + ".html" };

	//TODO: add header
	file << "<!DOCTYPE html>\n<html>\n<head>\n";
	file << "<title>" << fname << "</title>\n";
	//TODO: add css
	file << "<link rel=\"stylesheet\" type=\"text/css\" href=\"tp0.css\">\n";
	file << "</head>\n<body>\n<pre>";
	//add decorated lines
	file << data;

	//TODO: add end tag
	file << "</pre>\n</body>\n</html>";

	//totalT5 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
}

int main(int argc, const char * argv[])
{
	auto before = chrono::high_resolution_clock::now();
	string fname = "main.cpp";

	if (argc >= 2)
	{
		//TODO: initialiser un vecteur avec tout les nom de fichier
		fname = argv[1];
	}
	else
	{
		//TODO: initialiser un vecteur de nom de fichier
	}

	for (int j = 0; j < 10; ++j)
	{
		auto before = chrono::high_resolution_clock::now();

		for (int i = 0; i < 1000; ++i)
			t5(fname, t4(t3(t2(t1(t0(fname))))));

		cout << "total: " << duration_cast<milliseconds>(high_resolution_clock::now() - before).count() << endl;
	}
	//cout << "t0 " << totalT0.count() << endl;
	//cout << "t1 " << totalT1.count() << endl;
	//cout << "t2 " << totalT2.count() << endl;
	//cout << "t3 " << totalT3.count() << endl;
	//cout << "t4 " << totalT4.count() << endl;
	//cout << "t5 " << totalT5.count() << endl;
	char a;
	cin >> a;
}

/*

#include <regex>

int main()
{

}

<!DOCTYPE html>
<html>
<head>
<title>Page Title</title>
<link rel="stylesheet" type="text/css" href="tp0.css">
</head>
<body>

<h1>This is a Heading</h1>
<p>This is a paragraph.</p>

</body>
</html>
*/