#include "../include/Bot.hpp"
#include <stdio.h>

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
	std::string key = "\"response\":";
	size_t pos = json.find(key);

	if (pos == std::string::npos)
		return "";

	pos += key.length();

	// skip spaces and quotes
	while (pos < json.size() &&
		  (json[pos] == ' ' || json[pos] == '\"'))
		pos++;

	size_t end = pos;

	while (end < json.size() &&
		  json[end] != '\"' &&
		  json[end] != '\n' &&
		  json[end] != '}')
		end++;

	return json.substr(pos, end - pos);
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
	std::string clean = escapeJSON(parseIRCRawMsg(rawMsg));

	std::string cmd =
		"curl -s http://localhost:11434/api/generate "
		"-H \"Content-Type: application/json\" "
		"-d '{"
		"\"model\":\"monique\","
		"\"prompt\":\"" + clean + "\","
		"\"stream\":false"
		"}'";

	std::string raw = exec(cmd);
	return extractResponse(raw);
}

Bot::~Bot(){}


