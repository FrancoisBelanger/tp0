#ifndef _TRANSFORM_H_

#include <fstream>
#include <sstream>
#include <set>

#define KEYWORDS std::set<std::string> keywords = { "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case",\
"catch", "char", "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else",\
"enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "import", "long", "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq",\
"nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "requires", "return", "short", "unsigned", "signed", "sizeof", "static", "static_assert",\
"static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "using", "virtual", "void", "volatile",\
"wchar_t", "while", "xor", "xor_eq" };

//TODO: passer au memory map
//milliseconds totalT0 = milliseconds{ 0 };
std::string t0(const std::string fname)
{
	//auto before = chrono::high_resolution_clock::now();
	std::ifstream file{ fname };
	std::stringstream ss;
	std::string line;
	std::string backslach_n{ '\n' };

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
	for (std::string::size_type i = 0; (i = toClean.find("&", i)) != std::string::npos;)
	{
		toClean.replace(i, std::string{ "&" }.length(), "&amp;");
		i += std::string{ "&amp;" }.length();
	}
	for (std::string::size_type i = 0; (i = toClean.find("<", i)) != std::string::npos;)
	{
		toClean.replace(i, std::string{ "<" }.length(), "&lt;");
		i += std::string{ "&lt;" }.length();
	}
	for (std::string::size_type i = 0; (i = toClean.find(">", i)) != std::string::npos;)
	{
		toClean.replace(i, std::string{ ">" }.length(), "&gt;");
		i += std::string{ "&gt;" }.length();
	}

	//totalT1 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
	return toClean;
}

//milliseconds totalT2 = milliseconds{ 0 };
std::string t2(std::string& inLine)
{
	//auto before = chrono::high_resolution_clock::now();
	std::string spanOpen = "<span id=\"t2\">";
	std::string spanClose = "</span>";
	std::string word;
	KEYWORDS;

	std::istringstream i{ inLine };
	std::ostringstream o;
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
std::string t3(std::string& inFile)
{
	//auto before = chrono::high_resolution_clock::now();

	std::string spanOpen = "<span id=\"t3\">";
	std::string spanClose = "</span>";
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

//TODO: faire le menage dans les parametres
//milliseconds totalT5 = milliseconds{ 0 };
void t5(const std::string& fname, const std::string& data, bool concurrent)
{
	//auto before = chrono::high_resolution_clock::now();
	std::ofstream file{ fname + (concurrent ? ".parallele.html" : ".sequential.html") };

	//header
	file << "<!DOCTYPE html>\n<html>\n<head>\n";
	file << "<title>" << fname << "</title>\n";
	file << "<link rel=\"stylesheet\" type=\"text/css\" href=\"tp0.css\">\n";
	file << "</head>\n<body>\n<pre>";

	//decorated lines
	file << data;

	//end tag
	file << "</pre>\n</body>\n</html>";

	//totalT5 += duration_cast<milliseconds>(high_resolution_clock::now() - before);
}

#endif // !_TRANSFORM_H_

