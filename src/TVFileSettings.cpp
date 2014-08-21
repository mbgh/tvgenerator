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
 * @file TVFileSettings.cpp
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 21 August 2014
 * @brief A class for setting the properties of a test vector file.
 * @version 1.0
 *
 * This file provides the implementation of a test vector file setting class,
 * which allows to set several properties for a test vector file.
 */

#include "TVFileSettings.h"

// ****************************************************************************
// Constructors/Destructors
// ****************************************************************************
/**
 * @brief Default constructor
 *
 * The default constructor sets the comment-indicating character to '%', adds a
 * single space before a line ending comment and also enables the line ending
 * comments.
 */
TVFileSettings::TVFileSettings() :
		filePath_(""), projectName_(""), content_(""), author_(""),
    commentIndicator_("%"), commentSpaces_(1),
    enableLineEndComments_(true), enablePreLineComments_(false) {
}

/**
 * @brief Constructor, which allows to set several parameters of the test vector
 *   file settings.
 * @param _filePath The path where to store the test vector file.
 * @param _author Name of the author generating the test vector file.
 * @param _content The actual content of the test vector file.
 * @param _projectName Name of the project the test vector will be used for.
 */
TVFileSettings::TVFileSettings(string _filePath, string _author,
    string _content, string _projectName) :
    commentIndicator_("%"), commentSpaces_(1),
    enableLineEndComments_(true), enablePreLineComments_(false) {

  filePath_     = _filePath;
  author_       = _author;
  content_      = _content;
  projectName_  = _projectName;
}

/**
 * @copydoc TVFileSettings::TVFileSettings(string _filePath, string _author,
    string _content, string _projectName)
 * @param _commentIndicator The character to be used to indicate that a comment
 *   starts.
 * @param _commentSpaces Number of spaces before the line ending comment.
 */
TVFileSettings::TVFileSettings(string _filePath, string _author,
    string _content, string _projectName, string _commentIndicator,
    int _commentSpaces) :
    enableLineEndComments_(true), enablePreLineComments_(false) {

  filePath_         = _filePath;
  author_           = _author;
  content_          = _content;
  projectName_      = _projectName;
  commentIndicator_ = _commentIndicator;
  commentSpaces_    = _commentSpaces;
}

/**
 * @brief Destructor
 */
TVFileSettings::~TVFileSettings() {
}

/**
 * @brief Add another signal to the test vector line by providing its signal
 *   declaration.
 * @param _sigDeclaration The signal declaration of the signal to be added to
 *   the test vector.
 */
void TVFileSettings::AddSignal(const SignalDeclaration & _sigDeclaration) {
  tvDeclarations_.push_back(_sigDeclaration);
}
