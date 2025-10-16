// (c) 2025 Beem Media. All rights reserved.

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include <vector>
#include <filesystem>
#include <iostream>
#include <print>
#include <chrono>
#include <unordered_set>
#include <regex>
#include <conio.h>

static rapidjson::Document Main_LoadDocument(const char* Filename)
{
	rapidjson::Document d;

	// const std::filesystem::path FilePath(std::string(argv[1]));
	const size_t FileSize = std::filesystem::file_size(Filename);

	if (FileSize == 0)
	{
		return d;
	}

	std::ifstream File(Filename, std::ios::binary);
	rapidjson::IStreamWrapper StreamWrapper(File);
	d.ParseStream(StreamWrapper);
	return d;
}

static std::tm Main_parse_rfc2822_datetime(const std::string& datetime)
{
	std::tm tm = {};
	// Skip the weekday and comma
	std::istringstream ss(datetime.substr(datetime.find(' ') + 1));
	ss >> std::get_time(&tm, "%d %b %Y %H:%M:%S");
	return tm;
}

static std::string Main_tm_to_yyyy_mm_dd(const std::tm& tm)
{
	std::ostringstream oss;
	oss << std::setw(4) << std::setfill('0') << (tm.tm_year + 1900) << '-'
		<< std::setw(2) << std::setfill('0') << (tm.tm_mon + 1) << '-'
		<< std::setw(2) << std::setfill('0') << tm.tm_mday;
	return oss.str();
}

static std::string Main_TimeToDate(const std::tm& tm)
{
	std::ostringstream oss;
	oss << std::setw(4) << std::setfill('0') << (tm.tm_year + 1900) << '-'
		<< std::setw(2) << std::setfill('0') << (tm.tm_mon + 1) << '-'
		<< std::setw(2) << std::setfill('0') << tm.tm_mday << ' '
		<< std::setw(2) << std::setfill('0') << tm.tm_hour << ':'
		<< std::setw(2) << std::setfill('0') << tm.tm_min << ':'
		<< std::setw(2) << std::setfill('0') << tm.tm_sec << "";
	return oss.str();
}

static std::string Main_sanitize_and_lower(const std::string& input, const std::string& valid_chars)
{
	std::unordered_set<char> valid(valid_chars.begin(), valid_chars.end());
	std::string result;
	result.reserve(input.size());
	for (char c : input)
	{
		char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
		if (valid.count(lower))
			result += lower;
		else
			result += '-';
	}
	return result;
}

static std::string Main_CleanContent(const std::string& Input)
{
	std::string Out = Input;

	static const std::regex root_regex(R"(http://www.beemsoft.com/bs_files/)");
	Out = std::regex_replace(Out, root_regex, "assets/");

	static const std::regex img_regex(R"(<img.*src=\"([^\"]*).*>)", std::regex::icase);
	Out = std::regex_replace(Out, img_regex, "![Image](/$1)");

	return Out;
}

int main(int argc, const char** argv)
{
	const std::string ValidChars = "abcdefghijklmnopqrstuvwxyz0123456789";

	if (argc < 2)
	{
		return -1;
	}

	const rapidjson::Document d = Main_LoadDocument(argv[1]);
	const std::string Title = d["rss"]["channel"]["title"].GetString();
	std::println("The title is {}.", Title);

	const std::filesystem::path OutDir = "WebRoot";
	if (!std::filesystem::is_directory(OutDir))
	{
		std::filesystem::create_directory(OutDir);
	}
	const std::filesystem::path OutPostsDir = OutDir / "_posts";
	if (!std::filesystem::is_directory(OutPostsDir))
	{
		std::filesystem::create_directory(OutPostsDir);
	}

	const auto& Items = d["rss"]["channel"]["item"];
	for (auto& Item : Items.GetArray())
	{
		const std::string PostType = Item["post_type"]["__cdata"].GetString();
		const bool bIsPage = PostType == "page";
		const bool bIsPost = PostType == "post";

		if (bIsPage || bIsPost)
		{
			std::println("====================================================================================================");
			const std::string ItemTitle = Item["title"].GetString();
			const std::string SanitizedTitle = Main_sanitize_and_lower(ItemTitle, ValidChars);
			const std::string PublishDate = Item["pubDate"].GetString();
			const std::string PostDateGmt = Item["post_date_gmt"]["__cdata"].GetString();
			const std::tm PT = Main_parse_rfc2822_datetime(PublishDate);
			const std::string SanitizedDate = Main_tm_to_yyyy_mm_dd(PT);
			const std::string Content = Main_CleanContent(Item["encoded"][0]["__cdata"].GetString());
			std::println("Article: {}, Published: {}", ItemTitle, SanitizedDate );
			const std::string Filename = bIsPost ? std::format("{}-{}", SanitizedDate, SanitizedTitle) : std::format("{}", SanitizedTitle); 
			std::println("Filename: {}", Filename);
			// std::println("Content: {}", Content);
			std::println("====================================================================================================");

			// Write the file
			const std::filesystem::path OutFilename = Filename + ".markdown";
			const std::filesystem::path OutFullPath = (bIsPost ? OutPostsDir : OutDir) / OutFilename;
			std::ofstream OutFile(OutFullPath);
			OutFile << "---" << std::endl;
			OutFile << "layout: " << (bIsPost ? "post" : "page") << std::endl;
			OutFile << "title: \"" << ItemTitle << "\"" << std::endl;
			if (bIsPage)
			{
				OutFile << "permalink: /" << SanitizedTitle << "/" << std::endl;
			}
			if (bIsPost)
			{
				OutFile << "date: " << PostDateGmt << " +0000" << std::endl;
			}
			OutFile << "---" << std::endl;
			OutFile << Content << std::endl;
			OutFile.close();
		}
	}

	// _getch();
}