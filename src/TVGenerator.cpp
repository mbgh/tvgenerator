/******************************************************************************
 *
 * A test vector file generator for hardware designs.
 * Copyright (C) 2014 ETHZ Zurich, Integrated Systems Laboratory
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

/**
 * @file TVGenerator.cpp
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 21 August 2014
 * @brief A test vector file generator for hardware designs.
 * @version 0.1
 *
 * This file provides the implementation of a test vector file generator for
 * hardware designs. It is intended to create nicely formated files (incl.
 * file headers, comments, etc.) for both stimuli and expected responses either
 * combined in a single file or each within a single file. It uses my personal
 * @c StdLogicVector class in order to represent signals/numbers of arbitrary
 * precision.
 */

#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <time.h>
#include <math.h>

#include "TVGenerator.h"
#include "StdLogicVector.h"

using namespace std;

// ****************************************************************************
// Constructors/Destructors
// ****************************************************************************

/**
 * @brief The default constructor creates a new TVGenerator per default using a
 *   single file for both stimuli and expected responses.
 */
TVGenerator::TVGenerator() : isSingleFileBased_(true), testVectorCount_(0),
		stimuliCount_(0), expRspCount_(0){
}

/**
 * @brief Destructor
 */
TVGenerator::~TVGenerator() {
}


// ****************************************************************************
// Utility functions
// ****************************************************************************
/**
 * @brief Write the test vector file header.
 *
 * If we are using a single-file based TVGenerator, the header will be written
 * to the configured file containing both stimuli and expected test vectors. In
 * case we use a two-file approach (i.e., writing stimuli in one file and
 * expected responses in another file), both headers will be written.
 */
void TVGenerator::WriteTVFileHeader() {
  if (isSingleFileBased_) {
    // Write header to combined test vector file.
  	WriteTVFileHeader(tvFile_, tvFileSettings_);
  } else {
  	// Write header to both separate stimuli and expected responses file.
  	WriteTVFileHeader(stimFile_, stimFileSettings_);
  	WriteTVFileHeader(expRspFile_, expRspFileSettings_);
  }
}
/**
 * @copydoc TVGenerator::WriteTVFileHeader()
 * @param _fileSettings The test vector file settings to which the header
 *   should be written.
 */
void TVGenerator::WriteTVFileHeader(ofstream & _tvFile, TVFileSettings & _tvFileSettings) {

  // Get current time.
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d, %X", &tstruct);

  WriteTVFileHeaderEntry(_tvFile, _tvFileSettings, "File:", _tvFileSettings.getFilePath());
  WriteTVFileHeaderEntry(_tvFile, _tvFileSettings, "Author:", _tvFileSettings.getAuthor());
  WriteTVFileHeaderEntry(_tvFile, _tvFileSettings, "Project:", _tvFileSettings.getProjectName());
  WriteTVFileHeaderEntry(_tvFile, _tvFileSettings, "Created:", buf);
  WriteTVFileHeaderEntry(_tvFile, _tvFileSettings, "Content:", _tvFileSettings.getContent());
  WriteSignalCaptions(_tvFile, _tvFileSettings);
}

/**
 * @brief Write a single file header line.
 * @param _prefix The prefix to be used for the file header line.
 * @param _entry The actual value of the file header line.
 */
void TVGenerator::WriteTVFileHeaderEntry(ofstream & _tvFile, TVFileSettings & _fileSettings,
		string _prefix, string _entry) {
  const int prefixWidth = 10;
  _tvFile << _fileSettings.getCommentIndicator() << " " << _prefix <<
      string(prefixWidth - _prefix.length(), ' ') << _entry << endl;
}

/**
 * @brief Writes the provided values for the given test vector setting to the
 *   file.
 * @param _tvFile The file stream to which the vectors should be written.
 * @param _fileSettings The corresponding settings of the test vector file.
 * @param _signalValues The values of the signals to be written to the test
 *   vector file.
 * @param _comment The comment which should be attached to the end of the test
 *   vector file entry.
 * @return 0 if successfully, otherwise an exception will be thrown.
 */
int TVGenerator::WriteTVLine(ofstream & _tvFile, TVFileSettings & _fileSettings,
		vector<StdLogicVector> _signalValues, string _comment, int & _tvCount) {

	// Check whether number of provided signal values matches the number of
	// signal declarations set up during the initialization.
	if (_signalValues.size() != _fileSettings.getTVDeclarations().size()) {
		throw invalid_argument("Number of signal values does not match number of "
				"determined signals during the signal declaration.");
	}

	// Check whether signal caption should be repeated before writing the actual
	// test vector entry.
	if (_tvCount > 0 && _tvCount % _fileSettings.getSignalCaptionInterval() == 0) {
		WriteSignalCaptions(_tvFile, _fileSettings);
	}

	for (size_t sig = 0; sig < _signalValues.size(); ++sig) {
		string baseString = _signalValues[sig].ToString(
				_fileSettings.getTVDeclarations()[sig].GetPrintBase(), true);
		_tvFile << baseString;
		if (sig != _signalValues.size() - 1) {
			_tvFile << " ";
		} else {
			if (_fileSettings.isEnableLineEndComments() && !_comment.empty()) {
				_tvFile << string(_fileSettings.getCommentSpaces(), ' ') <<
						_fileSettings.getCommentIndicator() << " " << _comment;
			}
			_tvFile << endl;
		}
	}

	_tvCount++;

	return 0;
}

/**
 * @brief Write an arbitrary line to a provided test vector file.
 * @param _tvFile The test vector file, to which the arbitrary line should be
 *   written.
 * @param _tvFileSettings The corresponding test vector file settings.
 * @param _line The file to be written to the test vector file.
 * @param _comment The comment to be attached to the end of the line.
 */
void TVGenerator::WriteArbitraryTVLine(ofstream & _tvFile,
		TVFileSettings & _tvFileSettings, string _line, string _comment) {
	_tvFile << _line;

	if (tvFileSettings_.isEnableLineEndComments() && !_comment.empty()) {
		_tvFile << string(tvFileSettings_.getCommentSpaces(), ' ') <<
				tvFileSettings_.getCommentIndicator() << " " << _comment;
	}

	_tvFile << endl;
}

/**
 * @brief Write a comment line to the provided test vector file.
 * @param _tvFile The test vector file, to which the arbitrary line should be
 *   written.
 * @param _tvFileSettings The corresponding test vector file settings.
 * @param _comment The comment to be written to the test vector file.
 */
void TVGenerator::WriteTVCommentLine(ofstream & _tvFile,
		TVFileSettings & _tvFileSettings, string _comment) {
	_tvFile << _tvFileSettings.getCommentIndicator() << " " << _comment << endl;
}

/**
 * @brief Write the description of the signals into the test vector file.
 * @param _tvFile The test vector file to which the signal caption should be
 *   written.
 * @param _tvFileSettings The corresponding test vector file settings.
 */
void TVGenerator::WriteSignalCaptions(ofstream & _tvFile, TVFileSettings & _tvFileSettings)
{
	const vector<SignalDeclaration> & sigDecls = _tvFileSettings.getTVDeclarations();

	// Create an empty comment line in the test vector file.
	_tvFile << _tvFileSettings.getCommentIndicator() << endl;

	for (size_t i = 0; i < sigDecls.size(); ++i) {

		// Create the string (signal caption), describing the next signal.
		_tvFile << GeneratePreSignalCaptionString(_tvFileSettings, i);
		_tvFile << sigDecls[i].GetName();

		// If specified, append the width of the signal in the caption of the
		// respective signal.
		if (sigDecls[i].IsAppendWidthInCaption()) {
			_tvFile << " (" << sigDecls[i].GetWidth() << " bit)";
		}

		_tvFile << endl;
	}

	_tvFile << GeneratePreSignalCaptionString(_tvFileSettings, sigDecls.size());

	// If specified, append the last header column indicating the start of the
	// line-end comments.
	if (_tvFileSettings.isEnableLineEndComments()) {
		_tvFile << string(_tvFileSettings.getCommentSpaces() -
				_tvFileSettings.getSignalDistance(), ' ');
		_tvFile << _tvFileSettings.getCommentsColumnHeader() << endl;
		_tvFile << GeneratePreSignalCaptionString(_tvFileSettings, sigDecls.size());
		_tvFile << string(_tvFileSettings.getCommentSpaces() -
				_tvFileSettings.getSignalDistance(), ' ');
		_tvFile << _tvFileSettings.getColumnIndicator();
	}
	_tvFile << endl;
}

/**
 * @brief Create the leading string for a certain signal.
 *
 * Create the leading string of a certain signal, which should be written into
 * the signal caption of the test vector file (i.e., all the column indicators
 * required in front of the actual signal name, which allow an easier alignment
 * of the signal columns).
 *
 * @param _tvFileSettings The corresponding test vector file settings.
 * @param _sigIndex The index of the signal for which the leading string should
 *   be created.
 * @return The created string in front of the actual signal name.
 */
string TVGenerator::GeneratePreSignalCaptionString(const TVFileSettings & _tvFileSettings,
		const int _sigIndex)
{
	int offset 				= 0;
	float widthDigits	= 0;
	float logBase 		= 0;
	stringstream ssResult;
	SignalDeclaration currSigDecl;

	const vector<SignalDeclaration> & sigDecls = _tvFileSettings.getTVDeclarations();

	ssResult << _tvFileSettings.getCommentIndicator();

	for (int i = 0; i < _sigIndex; ++i) {
		currSigDecl = sigDecls[i];

		offset = (i == 0) ?
				_tvFileSettings.getCommentIndicator().length() :
				_tvFileSettings.getColumnIndicator().length();

		// Determine the number of digits required in the specified number base to
		// represent the value of the current signal.
		logBase 		= log(currSigDecl.GetPrintBase()) / log(2);
		widthDigits = ceil((float)currSigDecl.GetWidth()/ logBase);

		ssResult << string(widthDigits - offset, ' ');
		ssResult << string(_tvFileSettings.getSignalDistance(), ' ');

		if (_sigIndex > 1 && i!= _sigIndex-1) {
			ssResult << _tvFileSettings.getColumnIndicator();
		}
	}
	return ssResult.str();
}



// ****************************************************************************
// Public methods
// ****************************************************************************

/**
 * @brief Initialize the TVGenerator using a single settings object.
 * @param _tvFileSettings The settings to be used in order to initialize the
 *   TVGenerator.
 *
 * Per default the TVGenerator is initialized using a single test vector file
 * (i.e., a file containing both stimuli and the expected responses).
 */
void TVGenerator::Initialize(TVFileSettings _tvFileSettings) {
  isSingleFileBased_ = true;
  tvFileSettings_   = _tvFileSettings;
  tvFile_.open(tvFileSettings_.getFilePath().c_str());

  WriteTVFileHeader();
}

/**
 * @brief Initialize the TVGenerator using two separate settings objects.
 * @param _stimFileSettings The settings to be used in order to initialize the
 *   stimuli file.
 * @param _expRspFileSettings The settings to be used in order to initialize
 *   the expected responses file.
 *
 * Using this initialization functions allows you to create stimuli and expected
 * responses in two different files.
 */
void TVGenerator::Initialize(TVFileSettings _stimFileSettings,
		TVFileSettings _expRspFileSettings){
	isSingleFileBased_	= false;
	stimFileSettings_		= _stimFileSettings;
	expRspFileSettings_	= _expRspFileSettings;
	stimFile_.open(stimFileSettings_.getFilePath().c_str());
	expRspFile_.open(expRspFileSettings_.getFilePath().c_str());

	WriteTVFileHeader();
}

/**
 * @brief Finalizes the TVGenerator object.
 *
 * Must be called after using the TVGenerator in order to close open file
 * connections, etc.
 */
void TVGenerator::Finalize() {
  if (tvFile_) {
    tvFile_.close();
  }
  if (stimFile_) {
    stimFile_.close();
  }
  if (expRspFile_) {
    expRspFile_.close();
  }
}

/**
 * @brief Write a single test vector line to the test vector file.
 * @param _signalValues The values of the signals to be used.
 * @param _comment The comment which will be added to the end of the test vector
 *   line in case it has been enabled in the test vector file settings.
 * @return 0 when successfully. Throws an exception otherwise.
 */
int TVGenerator::WriteTestVectorLine(vector<StdLogicVector> _signalValues,
      string _comment) {
  if (!isSingleFileBased_) {
    throw logic_error("Bad function call: Test vector has *not* been set up "
        "for single file application. Hence, do not use the "
        "'WriteTestVectorLine' function but the "
        "'WriteStimuliLine/WriteExpectedResponseLine' functions.");
  }
  return WriteTVLine(
  			tvFile_, tvFileSettings_, _signalValues, _comment, testVectorCount_);
}

/**
 * @brief Write a single stimuli to the stimuli file.
 * @param _stimuliValues The values of the stimuli signals to be written.
 * @param _comment The comment to be attached at the end of the stimuli line.
 * @return 0 when successfully. Throws an exception otherwise.
 */
int TVGenerator::WriteStimuliLine(vector<StdLogicVector> & _stimuliValues,
		string _comment) {
	if ( isSingleFileBased_) {
		throw logic_error("Bad function call: Test vector has been set up "
				"for single file application. Hence, use the 'WriteTestVectorLine'"
				"function instead of 'WriteStimuliLine/WriteExpRspLine'");
	}
	return WriteTVLine(
			stimFile_, stimFileSettings_, _stimuliValues, _comment, stimuliCount_);
}

/**
 * @brief Write an expected response to the expected responses file.
 * @param _expRspValues The values of the expected response signals to be written.
 * @param _comment The comment to be attached to the end of the expected response
 *   file.
 * @return 0 when successfully. Throws an exception otherwise.
 */
int TVGenerator::WriteExpRspLine(vector<StdLogicVector> & _expRspValues,
		string _comment) {
	if ( isSingleFileBased_) {
		throw logic_error("Bad function call: Test vector has been set up "
				"for single file application. Hence, use the 'WriteTestVectorLine'"
				"function instead of 'WriteStimuliLine/WriteExpRspLine'");
	}
	return WriteTVLine(
			expRspFile_, expRspFileSettings_, _expRspValues, _comment, expRspCount_);
}


/**
 * @brief Write an arbitrary line to the common test vector file.
 * @param _line The arbitrary line to be written to the file.
 */
void TVGenerator::WriteArbitraryTVLine(string _line) {
	WriteArbitraryTVLine(_line, "");
}

/**
 * @copydoc TVGenerator::WriteArbitraryTVLine(string _line)
 * @param _comment The comment to be attached to the arbitrary test vector line.
 */
void TVGenerator::WriteArbitraryTVLine(string _line, string _comment) {
	if (!isSingleFileBased_) {
		throw logic_error("Bad function call: Test vector generator has *not* been "
				"set up for single file application. Hence, do not use the "
				"'WriteCustomTVLine' function but the "
				"'WriteCustomStimuliLine/WriteCustomExpRspLine' functions.");
	}
	WriteArbitraryTVLine(tvFile_, tvFileSettings_, _line, _comment);
}

/**
 * @brief Write an arbitrary line to the stimuli file.
 * @param _line The arbitrary line to be written to the stimuli file.
 */
void TVGenerator::WriteArbitraryStimuliLine(string _line) {
	WriteArbitraryStimuliLine(_line, "");
}
/**
 * @copydoc TVGenerator::WriteArbitraryStimuliLine(string _line)
 * @param _comment The comment to be attached to the arbitrary line of the
 *   stimuli file.
 */

void TVGenerator::WriteArbitraryStimuliLine(string _line, string _comment) {
	if (isSingleFileBased_) {
		throw logic_error("Bad function call: Test vector generator has been set up "
				"for single file application. Hence, do not use the "
				"'WriteCustomStimuliLine/WriteCustomExpRspLine' functions but the "
				"'WriteCustomTVLine' function instead.");
		}
	WriteArbitraryTVLine(stimFile_, stimFileSettings_, _line, _comment);
}

/**
 * @brief Write an arbitrary line to the expected response file.
 * @param _line The arbitrary line to be written to the expected response file.
 */
void TVGenerator::WriteArbitraryExpRspLine(string _line) {
	WriteArbitraryExpRspLine(_line, "");
}

/**
 * @copydoc TVGenerator::WriteArbitraryExpRspLine(string _line)
 * @param _comment The comment to be attached to the arbitrary line of the
 *   expected stimuli file.
 */
void TVGenerator::WriteArbitraryExpRspLine(string _line, string _comment) {
	if (isSingleFileBased_) {
		throw logic_error("Bad function call: Test vector generator has been set up "
				"for single file application. Hence, do not use the "
				"'WriteCustomStimuliLine/WriteCustomExpRspLine' functions but the "
				"'WriteCustomTVLine' function instead.");
	}
	WriteArbitraryTVLine(expRspFile_, expRspFileSettings_,_line, _comment);
}

/**
 * @brief Write a comment line to the common test vector file.
 * @param _comment The comment to be written to the test vector file.
 */
void TVGenerator::WriteTVCommentLine(string _comment) {
	WriteTVCommentLine(tvFile_, tvFileSettings_, _comment);
}

/**
 * @brief Write a comment line to the stimuli test vector file.
 * @param _comment The comment to be written to the stimuli file.
 */
void TVGenerator::WriteStimuliCommentLine(string _comment) {
	WriteTVCommentLine(stimFile_, stimFileSettings_, _comment);
}

/**
 * @brief Write a comment line to the expected response file.
 * @param _comment The comment to be written to the expected response file.
 */
void TVGenerator::WriteExpRspCommentLine(string _comment) {
	WriteTVCommentLine(expRspFile_, expRspFileSettings_, _comment);
}

