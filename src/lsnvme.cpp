
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/range.hpp>
#include <boost/lexical_cast.hpp>

int get_filename_tail_number(const boost::filesystem::path& filename)
{
	boost::smatch r;

	if (boost::regex_search(filename.filename().string(), r, boost::regex("([0-9]+)$")))
	{
		return boost::lexical_cast<int>(r[1].str());
	}
	return 0;
}

struct compare_filename
{
	bool operator()(const boost::filesystem::path& a, const boost::filesystem::path& b)
	{
		return get_filename_tail_number(a) < get_filename_tail_number(b);
	}
};

int main(int argc, const char* argv[])
{
	boost::filesystem::directory_iterator by_bay_begin("/dev"), by_bay_end;

	std::vector<boost::filesystem::path> globed_item;

	for (auto dir_item : boost::make_iterator_range(by_bay_begin, by_bay_end))
	{
		if (dir_item.path().filename_is_dot()) continue;
		if (dir_item.path().filename_is_dot_dot()) continue;
		if (dir_item.status().type() == boost::filesystem::directory_file) continue;

		boost::smatch matched;

		if (boost::regex_match(dir_item.path().filename().string(), matched, boost::regex("nvme[0-9]+")))
		{
			globed_item.push_back(dir_item.path());
		}
	}

	std::sort(std::begin(globed_item), std::end(globed_item), compare_filename{});

	for (auto i: globed_item)
	{
		std::cout << i.string() << std::endl;
	}

	return 0;
}
