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
 * @file TVGenerator.h
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 21 August 2014
 * @brief A test vector file generator for hardware designs.
 * @version 1.0
 *
 * This file provides a test vector file generator class for hardware designs.
 * It is intended to create nicely formated files (incl. file headers,
 * comments, etc.) for both stimuli and expected responses either combined in a
 * single file or each within a separate file. It uses my personal
 * @c StdLogicVector class in order to represent signals/numbers of arbitrary
 * precision.
 */

#ifndef TVGENERATOR_H_
#define TVGENERATOR_H_

#include <string>
#include <fstream>
#include <vector>

#include "SignalDeclaration.h"
#include "StdLogicVector.h"
#include "TVFileSettings.h"

using namespace std;

/**
 * @class TVGenerator
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 21 August 2014
 * @brief Test vector file generator for hardware designs.
 * @version 1.0
 */
class TVGenerator {

private:
	// **************************************************************************
	// Members
	// **************************************************************************
	bool isSingleFileBased_;
	int testVectorCount_;
	ofstream tvFile_;
	ofstream stimFile_;
	ofstream expRspFile_;
	TVFileSettings tvFileSettings_;
	TVFileSettings stimFileSettings_;
	TVFileSettings expRspFileSettings_;

	// **************************************************************************
	// Utility functions
	// **************************************************************************
	void WriteTVFileHeader();
	void WriteTVFileHeader(ofstream & _tvFile, TVFileSettings & _fileSettings);
	void WriteTVFileHeaderEntry(ofstream & _tvFile, TVFileSettings & _fileSettings,
			string _prefix, string _entry);
	void WriteArbitraryTVLine(ofstream & _tvFile, TVFileSettings & _tvFileSettings,
			string _line, string _comment);
	void WriteTVCommentLine(ofstream & _tvFile, TVFileSettings & _tvFileSettings,
			string _comment);

public:
	// **************************************************************************
	// Constructors/Destructors
	// **************************************************************************
	TVGenerator();
	virtual ~TVGenerator();

	// **************************************************************************
	// Public methods
	// **************************************************************************
	void Initialize(TVFileSettings _tvFileSettings);
	void Initialize(TVFileSettings _stimFileSettings, TVFileSettings _expRespFileSettings);
	void Finalize();

	int WriteTestVectorLine(vector<StdLogicVector> _signalValues,
	    string _comment);

	void WriteArbitraryTVLine(string _line);
	void WriteArbitraryTVLine(string _line, string _comment);
	void WriteArbitraryStimuliLine(string _line);
	void WriteArbitraryStimuliLine(string _line, string _comment);
	void WriteArbitraryExpRspLine(string _line);
	void WriteArbitraryExpRspLine(string _line, string _comment);

	void WriteTVCommentLine(string _comment);
	void WriteStimuliCommentLine(string _comment);
	void WriteExpRspCommentLine(string _comment);
};

#endif /* TVGENERATOR_H_ */
