// PacketDecoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <assert.h>

const char*		hex_char_to_bin(char c);
std::string		hex_str_to_bin_str(const std::string& hex);
std::string		UnPackBits(const std::string& packet, long long bits, std::vector<long long>& numbers);
std::string		UnPackPackets(const std::string& packet, long long numPackets, std::vector<long long>& numbers);
void			UnPack(const std::string& packet);
long long		DoOperation(int packetTypeId, const std::vector<long long>& numbers);


int answer;
long long answer2;

long long DoOperation(int packetTypeId, const std::vector<long long>& numbers)
{
	long long result = 0;

	switch (packetTypeId)
	{
	case 0:
	{
		long long sum = 0;
		for (auto& iter : numbers)
		{
			sum += iter;
		}
		
		result = sum;

		printf("Sum of values = %lld\n", sum);
		break;
	}
	case 1:
	{
		long long product = 1;
		for (auto& iter : numbers)
		{
			product *= iter;
		}

		result = product;

		printf("Product of values = %lld\n", product);
		break;
	}
	case 2:
	{
		long long min = LLONG_MAX;
		for (auto& iter : numbers)
		{
			if (iter < min)
			{
				min = iter;
			}
		}

		result = min;

		printf("Min of values = %lld\n", min);
		break;
	}
	case 3:
	{
		long long max = 0;
		for (auto& iter : numbers)
		{
			if (iter > max)
			{
				max = iter;
			}
		}

		result = max;

		printf("Max of values = %lld\n", max);
		break;
	}
	case 5:
	{
		assert(numbers.size() == 2);

		if (numbers.at(0) > numbers.at(1))
		{
			result = 1;
		}
		break;
	}
	case 6:
	{
		assert(numbers.size() == 2);

		if (numbers.at(0) < numbers.at(1))
		{
			result = 1;
		}
		break;
	}
	case 7:
	{
		assert(numbers.size() == 2);

		if (numbers.at(0) == numbers.at(1))
		{
			result = 1;
		}
		break;
	}
	default:
		break;
	}

	return result;
}

const char* hex_char_to_bin(char c)
{
	// TODO handle default / error
	switch (toupper(c))
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	default: return "0000";
	}
}

std::string hex_str_to_bin_str(const std::string& hex)
{
	std::string bin;
	for (unsigned i = 0; i != hex.length(); ++i)
		bin += hex_char_to_bin(hex[i]);

	return bin;
}

// Unpack the remaining packet to the amount of bits given, also hold the values of the literal values in each packet in numbers vector
std::string UnPackBits(const std::string& packet, long long bits, std::vector<long long>& numbers)
{
	int currBits = 0;
	int currPacket = 0;
	int packetVersion = 0;
	int packetTypeID = 0;
	int packetLengthId = 0;
	std::string packetCpy = packet;

	while (currBits != bits)
	{
		int bitsUsed = packet.length() - packetCpy.length();
		if (bitsUsed == bits)
			break;

		packetVersion = (1 * (packetCpy[2] - '0')) + (2 * (packetCpy[1] - '0')) + (4 * (packetCpy[0] - '0'));
		packetTypeID =	(1 * (packetCpy[5] - '0')) + (2 * (packetCpy[4] - '0')) + (4 * (packetCpy[3] - '0'));
		packetLengthId = packetCpy[6] - '0';

		printf("\nSub packet %d:\n", currPacket);
		printf("Sub packet %d: Version: %d\n", currPacket, packetVersion);
		printf("Sub packet %d: Type ID: %d\n", currPacket, packetTypeID);
		printf("Sub packet %d: Length ID: %d\n", currPacket, packetLengthId);

		answer += packetVersion;

		if (packetTypeID == 4)
		{
			int index = 6;
			std::string number("");

			while (true)
			{
				number += packetCpy[index + 1];
				number += packetCpy[index + 2];
				number += packetCpy[index + 3];
				number += packetCpy[index + 4];

				if (packetCpy[index] == '0')
					break;

				index += 5;
			}

			long long result = std::strtoull(number.c_str(), 0, 2);

			printf("Sub packet %d: %s = %lld\n", currPacket, number.c_str(), result);

			if (currBits != bits)
			{
				index += 5;
				currBits += index;
				packetCpy = packetCpy.substr(index, packetCpy.length());
			}

			numbers.push_back(result);

			printf("Sub packet %d: %d bits of %lld\n", currPacket, currBits, bits);
		}
		else
		{
			int index = 7;
			std::vector<long long> values;

			if (packetLengthId == 0)
			{
				int bitsUsed = packet.length() - packetCpy.length();

				std::string numberStr = packetCpy.substr(index, 15);
				std::string restStr = packetCpy.substr(index + 15, packetCpy.length());
				long long bits = std::strtoull(numberStr.c_str(), 0, 2);

				printf("%lld bits of sub packets\n", bits);

				packetCpy = UnPackBits(restStr, bits, values);

				long long res = DoOperation(packetTypeID, values);
				numbers.push_back(res);
			}
			else
			{
				std::string numberStr = packetCpy.substr(index, 11);
				std::string restStr = packetCpy.substr(index + 11, packetCpy.length());
				long long packets = std::strtoull(numberStr.c_str(), 0, 2);

				printf("%lld sub packets\n", packets);

				packetCpy = UnPackPackets(restStr, packets, values);

				long long res = DoOperation(packetTypeID, values);
				numbers.push_back(res);
			}
		}

		currPacket++;
	}

	return packetCpy;
}

std::string UnPackPackets(const std::string& packet, long long numPackets, std::vector<long long>& numbers)
{
	int packetVersion = 0;
	int packetTypeID = 0;
	int packetLengthId = 0;
	int currPacket = 0;
	std::string packetCpy = packet;

	while (currPacket != numPackets)
	{
		packetVersion = (1 * (packetCpy[2] - '0')) + (2 * (packetCpy[1] - '0')) + (4 * (packetCpy[0] - '0'));
		packetTypeID = (1 * (packetCpy[5] - '0')) + (2 * (packetCpy[4] - '0')) + (4 * (packetCpy[3] - '0'));
		packetLengthId = packetCpy[6] - '0';

		printf("\nSub packet.%d:\n", currPacket);
		printf("Sub packet %d: Version: %d\n", currPacket, packetVersion);
		printf("Sub packet %d: Type ID: %d\n", currPacket, packetTypeID);
		printf("Sub packet %d: Length ID: %d\n", currPacket, packetLengthId);

		answer += packetVersion;

		if (packetTypeID == 4)
		{
			int index = 6;
			std::string number("");

			while (true)
			{
				number += packetCpy[index + 1];
				number += packetCpy[index + 2];
				number += packetCpy[index + 3];
				number += packetCpy[index + 4];

				if (packetCpy[index] == '0')
					break;

				index += 5;
			}

			long long result = std::strtoull(number.c_str(), 0, 2);

			printf("Sub packet %d: %s = %lld\n", currPacket, number.c_str(), result);

			if (currPacket != numPackets)
			{
				index += 5;
				packetCpy = packetCpy.substr(index, packetCpy.length());
			}

			numbers.push_back(result);

		}
		else
		{
			int index = 7;
			std::vector<long long> values;

			if (packetLengthId == 0)
			{
				int bitsUsed = packet.length() - packetCpy.length();

				std::string numberStr = packetCpy.substr(index, 15);
				std::string restStr = packetCpy.substr(index + 15, packetCpy.length());
				long long bits = std::strtoull(numberStr.c_str(), 0, 2);

				printf("%lld bits of sub packets\n", bits);

				packetCpy = UnPackBits(restStr, bits, values);

				long long res = DoOperation(packetTypeID, values);
				numbers.push_back(res);
			}
			else
			{
				std::string numberStr = packetCpy.substr(index, 11);
				std::string restStr = packetCpy.substr(index + 11, packetCpy.length());
				long long packets = std::strtoull(numberStr.c_str(), 0, 2);

				printf("%lld sub packets\n", packets);

				packetCpy = UnPackPackets(restStr, packets, values);

				long long res = DoOperation(packetTypeID, values);
				numbers.push_back(res);
			}
		}

		currPacket++;
	}

	return packetCpy;
}

// Function used to unpack the starting input string
// This is needed to know how to begin unpacking the entire string
void UnPack(const std::string& packet)
{
	// First 3 bits are the packet version
	int packetVersion = (1 * (packet[2] - '0')) + (2 * (packet[1] - '0')) + (4 * (packet[0] - '0'));

	// Next 3 bits are the packet type ID
	int packetTypeID =	(1 * (packet[5] - '0')) + (2 * (packet[4] - '0')) + (4 * (packet[3] - '0'));

	// The sixth bit is the packet length ID 
	int packetLengthId = packet[6] - '0';

	printf("Packet Version: %d\n", packetVersion);
	printf("Packet Type ID: %d\n", packetTypeID);
	printf("Packet Length ID: %d\n", packetLengthId);

	// For part 1 add up the packet version numbers
	answer += packetVersion;

	// If the starting input happens to be just a literal value
	if (packetTypeID == 4)
	{
		// This is a literal value packet, lets extract all the literal values within it

		int index = 6;
		std::string number("");

		while (true)
		{
			// All literal values are made up of 4 bits
			number += packet[index + 1];
			number += packet[index + 2];
			number += packet[index + 3];
			number += packet[index + 4];

			printf("%s = %lld\n", number.c_str(), std::strtoull(number.c_str(), 0, 2));

			// If the value at this index is 0 then there are no more literal values in this packet
			if (packet[index] == '0')
				break;

			index += 5;
		}
	}
	else
	{
		// This packet has more sub packets within it
		int index = 7;
		std::vector<long long> values;
		long long res = 0;

		// The sub packet tells us the amount of bits of sub packets it has
		if (packetLengthId == 0)
		{
			std::string numberStr = packet.substr(index, 15);
			std::string restStr = packet.substr(index + 15, packet.length());
			long long bits = std::strtoull(numberStr.c_str(), 0, 2);

			printf("%lld bits of sub packets\n", bits);

			UnPackBits(restStr, bits, values);

			res = DoOperation(packetTypeID, values);
			
		}
		// This packet tells us how many sub packets it has 
		else
		{
			std::string numberStr = packet.substr(index, 11);
			std::string restStr = packet.substr(index + 11, packet.length());
			long long packets = std::strtoull(numberStr.c_str(), 0, 2);

			printf("%lld sub packets\n", packets);

			UnPackPackets(restStr, packets, values);

			res = DoOperation(packetTypeID, values);
		}

		answer2 = res;
	}
}

int main(int argc, char* argv[])
{
	// build a read-Stream
	std::ifstream source;

	// Open the sample problem
	source.open(argv[1], std::ios_base::in);

	// Check if there was a problem opening the file
	if (!source)
	{
		std::cout << "Can't open file!";
	}

	for (std::string hexStr; std::getline(source, hexStr);)
	{
		answer = 0; 
		answer2 = 0;

		// Convert the hex string to binary so we can work with it
		std::string binStr = hex_str_to_bin_str(hexStr);

		// Print out the hex and binary strings for debugging
		printf("%s\n", hexStr.c_str());
		printf("%s\n", binStr.c_str());

		// Unpack the binary string 
		UnPack(binStr);

		// Print our answers 
		printf("\nAnswer 1: %d\n", answer);
		printf("Answer 2: %lld\n", answer2);
	}
}

