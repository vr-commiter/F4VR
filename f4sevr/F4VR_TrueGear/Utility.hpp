#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <iterator>
#include <f4se/GameSettings.h>
#include "dirent.h"


template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return select_randomly(start, end, gen);
}



static inline std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

static inline void skipComments(std::string& str)
{
	auto pos = str.find("#");
	if (pos != std::string::npos)
	{
		str.erase(pos);
	}
}

static inline void skipTactExtension(std::string& str)
{
	auto pos = str.find(".tact");
	if (pos != std::string::npos)
	{
		str.erase(pos);
	}
}

static inline std::vector<std::string> get_all_files_names_within_folder(std::string folder)
{
	std::vector<std::string> names;
	
	DIR *directory = opendir(folder.c_str());
	struct dirent *direntStruct;

	if (directory != nullptr) {
		while (direntStruct = readdir(directory)) {
			names.emplace_back(direntStruct->d_name); 
		}
	}
	closedir(directory);

	return names;
}

static inline bool stringStartsWith(std::string str, std::string prefix)
{
	// std::string::find returns 0 if toMatch is found at starting
	if (str.find(prefix) == 0)
		return true;
	else
		return false;
}

static inline float randf(float lo, float hi)
{
	if (hi == 0)
		return 0;

	srand(time(NULL));
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = hi - lo;
	float r = random * diff;
	return lo + r;
}

static inline size_t randomGenerator(size_t min, size_t max) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	//rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

	return dist(rng);
}

static inline size_t randomGeneratorLowMoreProbable(size_t lowermin, size_t lowermax, size_t highermin, size_t highermax, int probability) {

	std::mt19937 rng;
	rng.seed(std::random_device()());

	std::uniform_int_distribution<std::mt19937::result_type> dist(1, probability);

	if(dist(rng) == 1)
	{
		//higher
		rng.seed(std::random_device()());

		std::uniform_int_distribution<std::mt19937::result_type> distir(highermin, highermax);

		return distir(rng);
	}
	else
	{
		rng.seed(std::random_device()());

		std::uniform_int_distribution<std::mt19937::result_type> distir(lowermin, lowermax);

		return distir(rng);
	}	
}

static inline int randi(int lo, int hi)
{
	if (hi == 0)
		return 0;

	srand(time(NULL));
	int n = hi - lo + 1;
	int i = rand() % n;
	if (i < 0) 
		i = -i;
	return lo + i;
}


static inline bool Contains(std::string str, std::string ministr)
{
	if (str.find(ministr) != std::string::npos) {
		return true;
	}
	else
		return false;
}


// Names should be the full INI setting name followed by a colon and it's category
// For example: bAlwaysShowHands:VR
static inline double vlibGetSetting(const char * name) {
	Setting * setting = GetINISetting(name);
	double value;
	if (!setting)
		return -1;
	if (setting->GetDouble(&value))
		return value;
	return -1;
}