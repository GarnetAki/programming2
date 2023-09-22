#include <cmath>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <map>
#include <clocale>
#include "curl/curl.h"
#include "../../../../../json.hpp"

unsigned int time_cur;

struct memory {
	double sum = 0;
	std::vector <double> values;
};

inline bool IsKeyDown(int Key)
{
	return (GetKeyState(Key) & 0x8000) != 0;
}

void WantToAsk(int Key, const std::map <std::string, memory> &bablo, int cnt)
{
	if (!IsKeyDown(Key)) return;
	while (IsKeyDown(Key)) {};
	std::cout << "print name of currency\n";
	std::string str;
	std::cin >> str;
	std::cout << "average value:" << bablo[str].sum / cnt << '\n';
	nth_element(bablo[str].values.begin(), bablo[str].values.begin() + cnt / 2, bablo[str].values.end());
	std::cout << "middle value:" << bablo[str].values[cnt / 2] << '\n';
	std::cout << "if you wanna continue, press f1 again" << '\n';
	while (!IsKeyDown(Key)) {};
	while (IsKeyDown(Key)) {};
	std::cout << "continued\n";
	time_cur = (unsigned int)time(NULL);
}

void WannaExit(int Key) {
	if (!IsKeyDown(Key)) return;
	while (IsKeyDown(Key)) {};
	exit(EXIT_SUCCESS);
}

void PauseByKey(int Key)
{
	if (!IsKeyDown(Key)) return;
	while (IsKeyDown(Key)) {};
	std::cout << "paused\n";
	while (!IsKeyDown(Key)) {};
	while (IsKeyDown(Key)) {};
	std::cout << "continued\n";
	time_cur = (unsigned int)time(NULL);
}

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

int main() {
	system("chcp 65001 > nul");
	CURL* curl = curl_easy_init(); 
	CURLcode tmp;
	std::string buffer;
	const std::string url("https://www.cbr-xml-daily.ru/daily_json.js");

	int tWin = 10;
	int cnt = 0;

	std::map <std::string, memory> bablo;

	std::cout << "enter the amount of seconds for time-window" << '\n';
	std::cin >> tWin;
	if (tWin < 1)tWin = 10;
	
	long httpCode(0);
	std::unique_ptr<std::string> httpData(new std::string());

	time_cur = (unsigned int)time(NULL);
	while (1) {
		if ((unsigned int)time(NULL) - time_cur >= tWin) {
			time_cur = (unsigned int)time(NULL);
			nlohmann::json json;
			tmp = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			tmp = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			tmp = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
			tmp = curl_easy_perform(curl);
			json = nlohmann::json::parse(buffer);
			for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
				if(it.key() == "Valute")
					for (auto& it2 : *it) {
						std::cout << it2["CharCode"] << " - " << it2["Value"] << '\n';
						bablo[it2["CharCode"].dump()].cnt++;
						bablo[it2["CharCode"].dump()].sum += std::stod(it2["Value"].dump());
						bablo[it2["CharCode"].dump()].values.push_back(std::stod(it2["Value"].dump()));
					}
			}
			cnt++;
			json.clear();
			buffer.clear();
		}
		WannaExit(VK_F12);
		PauseByKey(VK_F2);
		WantToAsk(VK_F1, bablo, cnt);
	}
}