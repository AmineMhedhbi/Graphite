g++ -Wall ../helpers/typeconversion/int_string_conversion.cc ../helpers/configfile/config_file.cc ../topology_builder.cc ../network_topology.cc test_network_topology.cc -o test
./test
rm test
