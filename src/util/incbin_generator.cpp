#include <cstdint>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
   if (argc != 3) {
      std::cerr << "Invalid arguments. Usage: " << argv[0] << " <input binary> <output header file>\n";
      return 1;
   }

   std::ifstream in_binary = std::ifstream(argv[1], std::ios::binary);
   std::ofstream out_header = std::ofstream(argv[2], std::ios::trunc);

   if (!in_binary.is_open() || !out_header.is_open()) {
      std::cerr << "" << argv[0] << ": Could not open " << (in_binary.is_open() ? "output file \"" : "input file \"") <<
                                                           (in_binary.is_open() ? argv[2] : argv[1]) << "\"\n";
      return 2;
   }

   while (in_binary.good()) {
      uint8_t data;
      in_binary.read(reinterpret_cast<char*>(&data), 1);
      out_header << "0x" << std::hex << static_cast<unsigned int>(data) << ",";
   }
}