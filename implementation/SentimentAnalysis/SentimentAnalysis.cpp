// SentimentAnalysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Tracy.hpp"
#include <iostream>
#include "Helper.h"
#include "IPatternMatching.h"
#include "AhoCorasickAutomaton.h"
#include "KnuthMorrisPratt.h"
#include "Analysis.cpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"

using namespace std;
using namespace boost::property_tree;

void main()
{
    ptree pt;
    ini_parser::read_ini("config.ini", pt);

    string input = pt.get<string>("file.input_path");
    int algorithm = pt.get<int>("algorithm.type");
    
    Analysis* a = new Analysis(input, algorithm);
	a->generateReport();
	return;
}