#include "disassembler.h"

void disassemble()
{
	ifstream input; 
	string filePath;
	cout << "Enter path to input binary file: ";
fileOpening:
	cin >> filePath;
	input.open(filePath.c_str(), ifstream::binary);
	if (input.is_open())
	{
		cout << "File was succesfully opened!" << endl;
	}
	else
	{
		cout << endl << "Error with file opening! Please, enter path to file again: ";
		goto fileOpening;
	}
	ofstream output;
	string pathToOutput;
	cout << "Enter path to output file: ";
openFile:
	cin >> pathToOutput;
	output.open(pathToOutput.c_str(), ifstream::out);
	if (output.is_open())
	{
		cout << "Disassembling is in process..." << endl;
		int opcode, line = 1, addrLil, addrBig, byte1, byte2;
		while (!input.eof())
		{
			opcode = input.get();
			try
			{
				switch (opcode)
				{
					case 0XC6: //commands with immediate byte 
					case 0XCE:
					case 0XE6:
					case 0XFE:
					case 0XDB:
					case 0X3E:
					case 0X06:
					case 0X0E:
					case 0X16:
					case 0X1E:
					case 0X26:
					case 0X2E:
					case 0X36:
					case 0XF6:
					case 0XD3:
					case 0XD6:
					case 0XDE:
					case 0XEE:
						byte1 = input.get();
						output << line << ": " << commandTable.at(opcode) << hex << byte1 << endl;
						byte1 = 0;
						break;
					case 0XCD: //commands with address
					case 0XCC:
					case 0XC4:
					case 0XF4:
					case 0XFC:
					case 0XDC:
					case 0XD4:
					case 0XEC:
					case 0XE4:
					case 0XC3:
					case 0XCA:
					case 0XC2:
					case 0XF2:
					case 0XFA:
					case 0XDA:
					case 0XEA:
					case 0XD2:
					case 0XE2:
					case 0X3A:
					case 0X2A:
					case 0X22:
					case 0X32:
						addrLil = input.get();
						addrBig = input.get();
						output << line << ": " << commandTable.at(opcode) << hex << addrBig << addrLil << endl;
						addrLil = 0;
						addrBig = 0;
						break;
					case 0X01: //command with two immediate bytes
					case 0X21:
					case 0X31:
						byte1 = input.get();
						byte2 = input.get();
						output << line << ": " << commandTable.at(opcode) << hex << byte2 << byte1 << endl;
						byte1 = 0;
						byte2 = 0;
						break;
					default: //commands without any data
						output << line << ": " << commandTable.at(opcode) << endl;
				}
			}
			catch (out_of_range e) //if there are no such opcode in commandTable map container
			{
				output << line << ": " << "unknown opcode" << endl;
			}
			line++;
			opcode = 0;
		}
	}
	else
	{
		cout << endl <<"Error with file opening! Please, enter path to file again: ";
		goto openFile;
	}
	cout << "Disassembling was succesfully finished!" << endl;
	input.close();
	output.close();
}
