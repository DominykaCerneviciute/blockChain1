#pragma once
#include <string>
#include <bitset>
#include <iostream>
#include <cmath>
#include <vector>

using std::cout;
using std::string;
using std::bitset;
using std::endl;
using std::vector;
using std::hex;

int ascii(char c);
char hex(string sh);
char bitwiseOr(char p, char k);
char bitwiseXor(char p, char k);
char bitwiseAnd(char p, char k);
void procesas(string& kzn, string hash, string& done);
void full(string& hashString1, string& hashString2, char (*fun)(char, char));