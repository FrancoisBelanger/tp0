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

using namespace std;

#define KEYWORDS string keywords [] = { "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case",\
"catch", "char", "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else",\
"enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "import", "long", "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq",\
"nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "requires", "return", "short", "unsigned", "signed", "sizeof", "static", "static_assert",\
"static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "using", "virtual", "void", "volatile",\
"wchar_t", "while", "xor", "xor_eq" };

//TODO: passer au memory map
string t0(const string fname)
{
	ifstream file{ fname };
	stringstream ss;
	string line;
	string backslach_n("\n");

	//TODO: fbr utiliser des iterateurs de stream
	while (getline(file, line))
		ss << line << backslach_n;

	return ss.str();
}

string t1(string& toClean)
{
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
	return toClean;
}

//TODO a revoir
//string t2(const vector<string>& cppKeywords, string& inFile)
string t2(string& inFile)
{
	string spanOpen = "<span style = 'color:blue'>";
	string spanClose = "</span>";
	KEYWORDS;

	for (const string& keyWord : keywords)
	{
		for (string::size_type i = 0; (i = inFile.find(keyWord, i)) != string::npos;)
		{
			if (inFile.substr(i, keyWord.length() + 1) == keyWord + " ")
			{
				inFile.insert(i, spanOpen);
				i += (keyWord + spanOpen).length();
				inFile.insert(i, spanClose);
				i += 7;
			}
			else
			{
				i++;
			}
		}
	}
	return inFile;
}

//TODO: a refaire
string t3(string& inFile)
{
	string spanOpen = "<span style = 'color:green'>";
	string spanClose = "</span>";
	for (string::size_type i = 0; (i = inFile.find("//", i)) != string::npos;)
	{
		inFile.insert(i, spanOpen);
		i += spanOpen.length();
		auto end = inFile.find("\n", i);
		i = end;
		inFile.insert(end + 2, spanClose);
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
	return inFile;
}

//TODO: a refaire
string t4(string& inFile)
{
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
	return inFile;
}

//TODO: a templater sur le type de process?
void t5(const string& fname, const string& data)
{
	//TODO: ajouter le type d'execution en parametre
	ofstream file{ fname + ".html" };

	//TODO: add header
	file << "<!DOCTYPE html>\n<html>\n<head>\n";
	file << "<title>" << fname << "</title>\n";
	//TODO: add css
	file << "</title>\n<link rel=\"stylesheet\" type=\"text/css\" href=\"tp0.css\">\n";
	file << "</head>\n<body>\n<pre>";
	//add decorated lines
	file << data;

	//TODO: add end tag
	file << "</pre>\n</body>\n</html>";
}

int main(int argc, const char * argv[])
{
	string fname = "main.cpp";

	string a{ "ceci est in test,	main.cpp a" };
	istringstream i(a);
	ostringstream o;

	while (i >> a)
		cout << a << " " << i.tellg() << endl;


	if (argc >= 2)
	{
		//TODO: initialiser un vecteur avec tout les nom de fichier
		fname = argv[1];
	}
	else
	{
		//TODO: initialiser un vecteur de nom de fichier
	}

	for (int i = 0; i < 1000; ++i)
		t5(fname, t4(t3(t2(t1(t0(fname))))));

	cout << "asdf";
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