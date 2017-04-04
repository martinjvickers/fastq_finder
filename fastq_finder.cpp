#include <iostream>
#include <seqan/sequence.h>  // CharString, ...
#include <seqan/file.h>
#include <seqan/arg_parse.h>
#include <seqan/seq_io.h>
#include <seqan/gff_io.h>
#include <math.h>       /* sqrt */
#include <seqan/store.h> /* FragmentStore */
#include <queue>
#include <vector>
#include <ctime>
#include "boost/multi_array.hpp"
#include <cassert>
#include <boost/unordered_map.hpp>
#include <string>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <iomanip>

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


using namespace seqan;
using namespace std;

struct ModifyStringOptions
{
        CharString inputFileName;
	string instrument_id;
	int run_number;
	string flowcell_id;
	bool verbose;
};

seqan::ArgumentParser::ParseResult parseCommandLine(ModifyStringOptions & options, int argc, char const ** argv)
{
	seqan::ArgumentParser parser("fastq finder");
	addOption(parser, seqan::ArgParseOption("i", "input-file", "Path to the input file", seqan::ArgParseArgument::INPUT_FILE, "IN"));
	setRequired(parser, "input-file");

	//inputs
	//addArgument(parser, seqan::ArgParseArgument(seqan::ArgParseArgument::STRING, "TEXT"));
	addOption(parser, seqan::ArgParseOption("id", "instrument_id", "Instrument ID.", seqan::ArgParseArgument::STRING, "TEXT"));
	setRequired(parser, "instrument_id");	

	addOption(parser, seqan::ArgParseOption("r", "run_num", "Run Number of the instrument.", seqan::ArgParseArgument::INTEGER, "INT"));
	setRequired(parser, "run_num");

	
	addOption(parser, seqan::ArgParseOption("v", "verbose", "Prints the file name even if it doesn't match."));

	setShortDescription(parser, "Fastq match");
	setVersion(parser, "0.0.1");
	setDate(parser, "April 2017");
	addUsageLine(parser, "-i totest.fastq.gz -id HWI-ST665R -r 135 [\\fIOPTIONS\\fP] ");

	addDescription(parser, "Given a fastq file, and some information, this program will tell you if your fastq file is a match.");
	seqan::ArgumentParser::ParseResult res = seqan::parse(parser, argc, argv);

	// If parsing was not successful then exit with code 1 if there were errors.
	// Otherwise, exit with code 0 (e.g. help was printed).
	if (res != seqan::ArgumentParser::PARSE_OK)
		return res;

	getOptionValue(options.inputFileName, parser, "input-file");
	getOptionValue(options.instrument_id, parser, "instrument_id");
	getOptionValue(options.run_number, parser, "run_num");
	options.verbose = isSet(parser, "verbose");

	return seqan::ArgumentParser::PARSE_OK;

}

/*
*/
int main(int argc, char const ** argv)
{

	//parse our options
	ModifyStringOptions options;
	seqan::ArgumentParser::ParseResult res = parseCommandLine(options, argc, argv);

	StringSet<CharString> ids;
	StringSet<Dna5String> seqs;

	SeqFileIn seqFileIn;
	if(!open(seqFileIn, toCString(options.inputFileName)))
	{
		std::cerr << "ERROR: Could not open the file. " << toCString(options.inputFileName) << endl;
		return 1;
	}
	
	try{
		readRecords(ids, seqs, seqFileIn, 1); // read all records
	} 
	catch (Exception const & e)
	{
		std::cout << "ERROR: with file " << toCString(options.inputFileName) << " "  << e.what() << std::endl;
		
		return 1;
	}
	
	for (unsigned i = 0; i < length(ids); ++i)
	{
		vector<string> strs;
		string meh = toCString(ids[i]);
		boost::split(strs, meh, boost::is_any_of(":"));
		if(!options.instrument_id.compare(strs[0]) && options.run_number == stoi(strs[1])){
			cout << toCString(options.inputFileName) << " matches instrument ID " << options.instrument_id << " and run_num " << options.run_number << endl;
		} 
		else if(options.verbose == true)
		{
			cout << toCString(options.inputFileName) << " NO MATCH."<< endl;
		}

	}

	close(seqFileIn);

	return 0;
}
