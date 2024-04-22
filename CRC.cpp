#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <cmath>

using namespace std;

class IPAddress {
private:
    string ip;
    int subnetMask;
    string binaryIP;
    vector<int> octets;
    char ipClass;

public:
    IPAddress(string ip, int subnetMask) : ip(ip), subnetMask(subnetMask) {
        parseIP();
        calculateClass();
    }

    void parseIP() {
        stringstream ss(ip);
        string octet;
        while (getline(ss, octet, '.')) {
            octets.push_back(stoi(octet));
            binaryIP += bitset<8>(stoi(octet)).to_string();
        }
    }

    void calculateClass() {
        if (octets[0] >= 0 && octets[0] <= 127)
            ipClass = 'A';
        else if (octets[0] >= 128 && octets[0] <= 191)
            ipClass = 'B';
        else if (octets[0] >= 192 && octets[0] <= 223)
            ipClass = 'C';
        else if (octets[0] >= 224 && octets[0] <= 239)
            ipClass = 'D';
        else if (octets[0] >= 240 && octets[0] <= 255)
            ipClass = 'E';
    }

    void calculateNetworkAddress() {
        string networkAddress = binaryIP;
        for (int i = subnetMask; i < 32; ++i) {
            networkAddress[i] = '0';
        }
        cout << "Network Address: " << binaryToDecimal(networkAddress) << endl;
    }

    void calculateBroadcastAddress() {
        string broadcastAddress = binaryIP;
        for (int i = subnetMask; i < 32; ++i) {
            broadcastAddress[i] = '1';
        }
        cout << "Broadcast Address: " << binaryToDecimal(broadcastAddress) << endl;
    }

    void calculateFirstLastIPAddress() {
        string firstIPAddress = binaryIP;
        string lastIPAddress = binaryIP;
        for (int i = subnetMask; i < 32; ++i) {
            if (i < 31) {
                firstIPAddress[i] = '0';
                lastIPAddress[i] = '1';
            } else {
                lastIPAddress[i] = '0';
            }
        }
        cout << "First IP Address: " << binaryToDecimal(firstIPAddress) << endl;
        cout << "Last IP Address: " << binaryToDecimal(lastIPAddress) << endl;
    }

    int binaryToDecimal(string binary) {
        int decimal = 0;
        int power = 0;
        for (int i = binary.length() - 1; i >= 0; --i) {
            if (binary[i] == '1') {
                decimal += pow(2, power);
            }
            ++power;
        }
        return decimal;
    }

    void printInfo() {
        cout << "IP Address: " << ip << endl;
        cout << "Subnet Mask: " << subnetMask << endl;
        cout << "Class: " << ipClass << endl;
        calculateNetworkAddress();
        calculateBroadcastAddress();
        calculateFirstLastIPAddress();
    }
};

int main() {
    string ip;
    int subnetMask;

    cout << "Enter IP Address: ";
    cin >> ip;
    cout << "Enter Subnet Mask: ";
    cin >> subnetMask;

    IPAddress ipAddress(ip, subnetMask);
    ipAddress.printInfo();

    return 0;
}