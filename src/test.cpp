#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
typedef unsigned char BYTE;

int main(void) {
    std::ifstream file("/Users/parasadhikary/Downloads/school/ece30862/project1/Structured_Tests_Final/Manually_Generated_Tests/Basics.bin", std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<BYTE> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<BYTE>(file),
               std::istream_iterator<BYTE>());

    for(auto i: vec) {
        int value = i;
        std::cout << "data: " << value << std::endl;
    }

    std::cout << "file size: " << vec.size() << std::endl;
    return 1;
}
