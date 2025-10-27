// (c) 2025 Beem Media. All rights reserved.

#define _CRT_SECURE_NO_WARNINGS

#include <codecvt>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cassert>

#include <boost/algorithm/string/trim.hpp>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/allocators.h>

struct GamesListItem
{
	std::string Name = "";
	std::string Notes = "";
	std::int32_t PlatformId = 0;
	std::string DateCompleted = "";
	std::string DateSubmitted = "";
	std::tm DateCompletedTm = {};
	std::tm DateSubmittedTm = {};
	bool ShowYearOnly = false;
	bool ShowFuzzyYear = false;
	bool bFlagPartialDate = false;

	void AddToArray(rapidjson::Value& InArray, rapidjson::Document::AllocatorType& a) const
	{
		using namespace rapidjson;

		Value NewValue(kObjectType);

		const char* format_string = "%Y-%m-%dT%H:%M:%S";


		std::string DateCompletedStr;
		{
			char Tmp[128] = {};
			std::size_t Size = std::strftime(Tmp, 128, format_string, &DateCompletedTm);
			DateCompletedStr = Tmp;
		}

		std::string DateSubmittedStr;
		{
			char Tmp[128] = {};
			std::size_t Size = std::strftime(Tmp, 128, format_string, &DateSubmittedTm);
			DateSubmittedStr = Tmp;
		}

		NewValue.AddMember("name", Name, a);
		NewValue.AddMember("notes", Notes, a);
		NewValue.AddMember("platformId", PlatformId, a);
		NewValue.AddMember("dateCompleted", DateCompletedStr, a);
		NewValue.AddMember("dateSubmitted", DateSubmittedStr, a);
		NewValue.AddMember("showYearOnly", ShowYearOnly, a);
		NewValue.AddMember("showFuzzyYear", ShowFuzzyYear, a);

		InArray.PushBack(NewValue, a);
	}
};

struct PlatformsItem
{
	std::int32_t Id = 0;
	std::string Name = "";
	std::string ShortName = "";
	std::string SortName = "";

	void AddToArray(rapidjson::Value& InArray, rapidjson::Document::AllocatorType& a) const
	{
		using namespace rapidjson;

		Value NewValue(kObjectType);

		NewValue.AddMember("id", Id, a);
		NewValue.AddMember("name", Name, a);
		NewValue.AddMember("shortName", ShortName, a);
		NewValue.AddMember("sortName", SortName, a);

		InArray.PushBack(NewValue, a);
	}
};

class IGLProcessor
{
private:
	bool m_bSucceeded = false;
	rapidjson::Document m_OutDocument;

	std::vector<GamesListItem> m_GamesTable;
	std::vector<PlatformsItem> m_Platforms;

	std::string m_CurHeader;
	std::int32_t m_CurHeaderAsYear = 0;

public:
	IGLProcessor(const std::filesystem::path& InputFilename)
	{
		std::ifstream InFile;
		InFile.open(InputFilename);
		if (!InFile.is_open())
		{
			std::cout << "Input file not found." << std::endl;
			return;
		}

		std::string CurLine;
		while (std::getline(InFile, CurLine))
		{
			ProcessLine(CurLine);
		}

		SynchronizeDates();

		CreateDocument();
		m_bSucceeded = true;
	}

	bool Succeeded() const { return m_bSucceeded; }

	bool WriteTo(const std::filesystem::path& OutFilename) const
	{
		std::ofstream OutFile(OutFilename);

		if (!OutFile.is_open())
		{
			std::cout << "Failed to open output file." << std::endl;
			return false;
		}

		rapidjson::OStreamWrapper osw(OutFile);
		rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);

		m_OutDocument.Accept(writer);

		return true;
	}

private:
	void SynchronizeDates()
	{
		// Fix all date formats:
		std::chrono::time_point now = std::chrono::system_clock::now();
		std::time_t CurTime(0);
		std::time(&CurTime);
		std::tm SubmitDate = *std::localtime(&CurTime);

		std::tm LastCompleteDate = {};
		for (auto& Item : m_GamesTable)
		{
			SubmitDate.tm_sec--;
			std::mktime(&SubmitDate);
			Item.DateSubmittedTm = SubmitDate;

			if (Item.bFlagPartialDate)
			{
				if (Item.DateCompletedTm.tm_year != LastCompleteDate.tm_year)
				{
					LastCompleteDate = Item.DateCompletedTm;
				}

				Item.DateCompletedTm = LastCompleteDate;
				Item.DateCompletedTm.tm_mday--;
				std::mktime(&Item.DateCompletedTm);
			}

			LastCompleteDate = Item.DateCompletedTm;
		}
	}

	void FixDate(GamesListItem& Item)
	{
		// Date format "2025-10-26T18:12:44"

		std::string Date = Item.DateCompleted;
		std::vector<std::string> Components;
		Components.push_back("");
		for (const char c : Date)
		{
			if (c == '/')
			{
				Components.push_back("");
			}
			else
			{
				Components.back() += c;
			}
		}

		if (Components.size() == 3)
		{
			std::tm Date = {};
			Date.tm_mon = std::stoi(Components[0]) - 1;
			Date.tm_mday = std::stoi(Components[1]);
			Date.tm_year = std::stoi(Components[2]) - 1900;

			Item.DateCompletedTm = Date;
			Item.DateSubmittedTm = Date;
		}
		else if (Components.size() == 1)
		{
			std::tm Date = {};
			Date.tm_year = std::stoi(Components[0]);

			Item.DateCompletedTm = Date;
			Item.DateSubmittedTm = Date;
		}
		else
		{
			assert(false);
		}
	}

	void ProcessLine(const std::string& CurLine)
	{
		// std::cout << "Line: " << CurLine << std::endl;

		const bool bIsHeader = IsHeader(CurLine);

		if (bIsHeader)
		{
			std::cout << "Header found: " << CurLine << std::endl;
			m_CurHeader = CurLine;
			m_CurHeaderAsYear = IsDigitsOnly(CurLine) ? std::stoi(CurLine) : 0;
		}
		else
		{
			std::string ParseLine = CurLine;
			boost::algorithm::trim(ParseLine);
			if (ParseLine.length() == 0)
			{
				return;
			}

			std::cout << "Game found: " << ParseLine << std::endl;

			// General format: Game Name (Platform) Date - Notes. 
			// Date and Notes are optional, sometimes game name can 
			// include parenthesis, which can throw off parsing.

			std::size_t ReadPos = 0;
			auto ReadNextChar = [&ParseLine,&ReadPos]() -> char
				{
					if (ReadPos < ParseLine.length())
					{
						const char Out = ParseLine[ReadPos];
						ReadPos++;
						return Out;
					}
					return 0;
				};

			enum class Phase
			{
				Name,
				Platform,
				Date,
				Notes,
			};

			std::string Name;
			std::string Platform;
			std::string Date;
			std::string Notes;

			Phase p = Phase::Name;
			std::string* DestStr = &Name;

			for (auto c = ReadNextChar(); c != 0; c = ReadNextChar())
			{
				if (p == Phase::Name && c == '(')
				{
					p = Phase::Platform;
					DestStr = &Platform;
				}
				else if (p == Phase::Platform && c == ')')
				{
					p = Phase::Date;
					DestStr = &Date;
				}
				else if (p == Phase::Date && (c == '-' || c == '–'))
				{
					p = Phase::Notes;
					DestStr = &Notes;
				}
				// Special Cases
				else if (c == '(' && p == Phase::Date)
				{
					// Parenthesis was in Name.
					Name += "(";
					Name += Platform;
					Name += ')';
					Date = "";
					Platform = "";
					p = Phase::Platform;
					DestStr = &Platform;
				}
				else
				{
					(*DestStr) += c;
				}
			}

			boost::algorithm::trim(Name);
			boost::algorithm::trim(Platform);
			boost::algorithm::trim(Date);
			boost::algorithm::trim(Notes);

			GamesListItem NewItem;
			NewItem.Name = Name;
			NewItem.PlatformId = PlatformToID(Platform);
			NewItem.DateCompleted = Date;
			NewItem.DateSubmitted = Date;
			NewItem.Notes = Notes;

			if (m_CurHeaderAsYear == 0)
			{
				NewItem.ShowFuzzyYear = true;
				NewItem.bFlagPartialDate = true;
			}

			if (Date.length() == 0)
			{
				NewItem.ShowYearOnly = true;
				NewItem.DateCompleted = std::format("12/31/{0}", m_CurHeaderAsYear > 0 ? m_CurHeaderAsYear : 1998);
				NewItem.DateSubmitted = NewItem.DateCompleted;
				NewItem.bFlagPartialDate = true;
			}
			
			FixDate(NewItem);

			m_GamesTable.push_back(NewItem);
		}
	}

	std::int32_t PlatformToID(const std::string& PlatformName)
	{
		for (auto& Item : m_Platforms)
		{
			if (Item.Name == PlatformName)
			{
				return Item.Id;
			}
		}

		// Need to create a new platform:
		std::int32_t NewId = static_cast<std::int32_t>(m_Platforms.size()) + 1;
		PlatformsItem NewPlatform;
		NewPlatform.Id = NewId;
		NewPlatform.Name = PlatformName;
		NewPlatform.ShortName = PlatformName;
		NewPlatform.SortName = PlatformName;
		m_Platforms.push_back(NewPlatform);
		return NewId;
	}

	static bool IsHeader(const std::string& CurLine)
	{
		return CurLine.length() > 0 && !std::isspace(CurLine[0]);
	}

	static bool IsDigitsOnly(const std::string& CurLine)
	{
		for (auto& c : CurLine)
		{
			if (!std::isdigit(c))
			{
				return false;
			}
		}

		return true;
	}

	void CreateDocument()
	{
		using namespace rapidjson;
		
		Value& Root = m_OutDocument.SetObject();

		auto WriteArray = [this](auto& Input, const auto& ArrayName) -> void
			{
				{
					Value ItemDatas(kArrayType);
					for (auto& Item : Input)
					{
						Item.AddToArray(ItemDatas, m_OutDocument.GetAllocator());
					}

					m_OutDocument.AddMember(ArrayName, ItemDatas, m_OutDocument.GetAllocator());
				}
			};

		WriteArray(m_GamesTable, "gameDatas");
		WriteArray(m_Platforms, "platformDatas");
	}
};

int main(int argc, char* argv[])
{
	std::cout <<  "ImportGamesList (c) 2025 Beem Media. All rights reserved." << std::endl;

	if (argc < 3)
	{
		std::cout << "Usage: ImportGameList \"$InRawFile\" \"$OutJson\"" << std::endl;
		return -1;
	}

	std::filesystem::path InputFilename(argv[1]);
	std::filesystem::path OutputFilename(argv[2]);

	IGLProcessor Proc(InputFilename);	

	if (!Proc.Succeeded())
	{
		return -1;
	}
	
	if (!Proc.WriteTo(OutputFilename))
	{
		return -1;
	}

	// std::cin.ignore();
}