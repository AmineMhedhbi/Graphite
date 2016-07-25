#ifndef CONFIG_FILE_H__
#define CONFIG_FILE_H__

#include <map>
#include <vector>
#include <fstream>

#include "../typeconversion/int_string_conversion.h"

class ConfigFile
{
    public:
        ConfigFile(std::string const& configFile, int num_clusters);

        Alchemist const& Value(std::string const& section, std::string const& entry) const;
        Alchemist const& Value(std::string const& section, std::string const& entry, int value);
        Alchemist const& Value(std::string const& section, std::string const& entry, std::string const& value);

    private:
        std::map<std::string,Alchemist> content_;
        std::vector< std::vector<int> > connectivity_matrix_;
        std::vector<int> split(const std::string& string_to_split, const char& delimiter);

    public:
        std::vector< std::vector<int> > get_connectivity_matrix() { return connectivity_matrix_; }
        void print_connectivity_matrix();
};

#endif // CONFIG_FILE_H__
