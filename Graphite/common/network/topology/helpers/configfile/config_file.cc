#include "config_file.h"

#include <assert.h>

#define DELIMITER_EMPTY_SPACE ' '

std::string trim(std::string const& source,
                 char const* delims = " \t\r\n")
{
    std::string result(source);
    std::string::size_type index = result.find_last_not_of(delims);
    if(index != std::string::npos)
        result.erase(++index);

    index = result.find_first_not_of(delims);
    if(index != std::string::npos)
        result.erase(0, index);
    else
        result.erase();
    return result;
}

ConfigFile::ConfigFile(std::string const& configFile,
                       int num_clusters)
{
    std::ifstream file(configFile.c_str());

    std::string line;
    std::string name;
    std::string value;
    std::string inSection;
    int posEqual;

    int nxn_matrix_size = -1;
    int num_clusters_counted = 0;
    bool is_first_matrix_row_read = false;

    std::string connectivity_section;
    switch(num_clusters){
        case 2: connectivity_section = "network_topology_two_clusters" ;
                break;
        case 4: connectivity_section = "network_topology_four_clusters" ;
                break;
        case 8: connectivity_section = "network_topology_eight_clusters" ;
                break;
        case 16: connectivity_section = "network_topology_sixteen_clusters" ;
                 break;
        case 32: connectivity_section = "network_topology/thirtytwo_clusters" ;
                 break;
        case 64: connectivity_section = "network_topology/sixtyfour_clusters" ;
                 break;
        default: connectivity_section = "network_topology_eight_clusters" ;
                 break;
    }

    while (std::getline(file,line))
    {
        if (! line.length()) continue;
        if (line[0] == '#') continue;
        if (line[0] == ';') continue;

        if (line[0] == '[')
        {
            inSection = trim(line.substr(1,line.find(']')-1));
            continue;
        }

        if (inSection != connectivity_section)
        {
            posEqual=line.find('=');
            name  = trim(line.substr(0,posEqual));
            value = trim(line.substr(posEqual+1));

            content_[inSection+'/'+name]=Alchemist(value);
        }
        else if (inSection == connectivity_section)
        {
            std::vector<int> cluster_connectivity_row = split(line, DELIMITER_EMPTY_SPACE);

            if (!is_first_matrix_row_read)
            {
                is_first_matrix_row_read = true;
                nxn_matrix_size = cluster_connectivity_row.size();
                connectivity_matrix_.resize(nxn_matrix_size);
                connectivity_matrix_[num_clusters_counted] = cluster_connectivity_row;
                num_clusters_counted++;
            }
            else
            {
                assert((int)cluster_connectivity_row.size() == nxn_matrix_size);
                connectivity_matrix_[num_clusters_counted] = cluster_connectivity_row;
                num_clusters_counted++;
            }
        }
    }
    assert((int)connectivity_matrix_.size() == nxn_matrix_size);
}

Alchemist const& ConfigFile::Value(std::string const& section,
                                   std::string const& entry) const
{

    std::map<std::string,Alchemist>::const_iterator ci
            = content_.find(section + '/' + entry);

    if (ci == content_.end()) throw "does not exist";

    return ci->second;
}

Alchemist const& ConfigFile::Value(std::string const& section,
                                   std::string const& entry,
                                   int value)
{
    try
    {
        return Value(section, entry);
    }
    catch(const char *)
    {
        return content_.insert(
                std::make_pair(section+'/'+entry, Alchemist(value))).first->second;
    }
}

Alchemist const& ConfigFile::Value(std::string const& section,
                                   std::string const& entry,
                                   std::string const& value)
{
    try
    {
        return Value(section, entry);
    }
    catch(const char *)
    {
        return content_.insert(
                std::make_pair(section+'/'+entry, Alchemist(value))).first->second;
    }
}

std::vector<int> ConfigFile::split(const std::string& string_to_split,
                                    const char& delimiter)
{
    std::string next;
    std::vector<int> result;

    for (std::string::const_iterator it = string_to_split.begin(); it != string_to_split.end(); it++) {
        if (*it == delimiter)
        {
            if (!next.empty())
            {
                result.push_back(Alchemist(next));
                next.clear();
            }
        }
        else
        {
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(Alchemist(next));
    
    return result;
}

void ConfigFile::print_connectivity_matrix()
{
    for (int i = 0; i < (int)connectivity_matrix_.size(); ++i)
    {
        for (int j = 0; j < (int)connectivity_matrix_.size(); ++j)
        {
            std::cout << connectivity_matrix_[i][j] << DELIMITER_EMPTY_SPACE;
        }
        std::cout << std::endl;
    }
}

