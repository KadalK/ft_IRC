#include "../include/Bot.hpp"
#include <stdio.h>
#include <sstream>
#include <iostream>

Bot::Bot(){}

static std::string escapeJSON(const std::string& s)
{
	std::string out;

	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '"') out += "\\\"";
		else if (s[i] == '\\') out += "\\\\";
		else if (s[i] == '\n') out += "\\n";
		else out += s[i];
	}

	return out;
}

static std::string extractResponse(const std::string& json)
{
	const std::string key = "\"response\":";
	size_t pos = json.find(key);
	if (pos == std::string::npos)
		return "";

	pos += key.length();

	// skip jusqu'à la première quote ouvrante
	while (pos < json.size() && json[pos] != '"')
		pos++;
	if (pos == json.size()) return "";

	pos++; // après l’ouverture du guillemet
	std::string out;
	bool escape = false;

	for (; pos < json.size(); ++pos)
	{
		char c = json[pos];
		if (escape) {
			if (c == 'n') out += '\n';
			else if (c == 't') out += '\t';
			else if (c == 'r') out += '\r';
			else if (c == '\\' || c == '"') out += c;
			// on ignore les autres pour éviter erreurs
			escape = false;
		} else if (c == '\\') {
			escape = true;
		} else if (c == '"') {
			break; // fin de la chaîne
		} else {
			out += c;
		}
	}
	return out;
}


std::string parseIRCRawMsg(const std::string& rawMsg)
{
	size_t i = 0;
	size_t pos = std::string::npos;

	if (rawMsg.size() > 0 && rawMsg[0] == ':')
	{
		i = rawMsg.find(' ');
		if (i == std::string::npos)
			return "";
	}

	pos = rawMsg.find(" :", i);

	if (pos == std::string::npos)
		return "";

	pos += 2; // skip " :"

	return rawMsg.substr(pos);
}

std::string exec(const std::string& cmd)
{
	char buffer[128];
	std::string result;

	FILE* pipe = popen(cmd.c_str(), "r");
	if (!pipe)
		return "error";

	while (fgets(buffer, sizeof(buffer), pipe))
		result += buffer;

	pclose(pipe);
	return result;
}

std::string Bot::talk(const std::string& rawMsg)
{
	//std::string msg = escapeJSON(parseIRCRawMsg(rawMsg));
	std::string msg = escapeJSON(rawMsg);
	std::ostringstream ss;
	ss << "curl -s http://localhost:11434/api/generate "
	   << "-H \"Content-Type: application/json\" "
	   << "-d \"{"
	   << "\\\"model\\\":\\\"monique\\\","
	   << "\\\"prompt\\\":\\\"" << msg << "\\\","
	   << "\\\"stream\\\":false"
	   << "}\"";
	//std::cout << ss.str() << std::endl;
	std::string json = exec(ss.str());
	//std::cout << json << std::endl;
	return extractResponse(json);
}

Bot::~Bot(){}


