//
// Created by lenfien on 16-10-25.
//

#include <memory>
#include <iostream>
#include "../Real/PackageListener.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<unsigned char> data = {
            0xaa, 0x01, 0x02, 0x03, 0x04, 0xbb,  0xcc,
            0xaa, 0x01, 0xcc, 0xcc, 0xcc, 0xbb, 0xbb,
            0xaa, 0xbb,
            0xaa, 0xcc, 0xaa, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0xbb,
            0xaa, 0xcc, 0xcc, 0xcc, 0xcc, 0xbb
    };

    vector<char> vc = {'a', 'b', 'c', 'd', 'e', 'f', 0, 0, 0, 0};
    std::string str (vc.data(), vc.data() + vc.size());

    cout << str << endl;

    PackageListener dataProcessor;
    dataProcessor.put(data.begin(), data.end());

    int i = 1;
    for (auto v = dataProcessor.get(); v != nullptr; v = dataProcessor.get()) {
        cout << i++ << ": " << flush;
        for (auto a : *v)
            cout << hex << (int)a << " ";
        cout << endl;
    }

    return 0;
}
