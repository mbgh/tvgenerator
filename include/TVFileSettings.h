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
 * @file TVFileSettings.h
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 21 August 2014
 * @brief A class for setting the properties of a test vector file.
 * @version 1.0
 *
 * This file provides a class for setting the properties of a test vector file,
 * used within the TVGenerator class.
 */

#ifndef TVFILESETTINGS_H_
#define TVFILESETTINGS_H_

#include <string>
#include <vector>

#include "SignalDeclaration.h"

using namespace std;

/**
 * @class TVFileSettings
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 21 August 2014
 * @brief Test vector file settings.
 * @version 1.0
 */
class TVFileSettings {

private:
	// **************************************************************************
	// Members
	// **************************************************************************
  string filePath_;             // File name.
  string projectName_;          // Project name the test vector file belongs to.
  string content_;              // Describes the content of the test vector file.
  string author_;               // Author of the test vector file.
  string commentIndicator_;     // String starting a comment.
  int commentSpaces_;           // Spaces before line comment starts.
  bool enableLineEndComments_;  // Enable/Disable comments at end of line.
  bool enablePreLineComments_;  // Enable/Disable comments right before line.

  vector<SignalDeclaration> tvDeclarations_;

public:
  // **************************************************************************
  // Constructors/Destructors
  // **************************************************************************
  TVFileSettings();
  TVFileSettings(string _filePath, string _author, string _content,
      string _projectName);
  TVFileSettings(string _filePath, string _author, string _content,
      string _projectName, const string _commentIndicator,
      const int _commentSpaces);
  virtual ~TVFileSettings();

  // **************************************************************************
  // Getter/Setter
  // **************************************************************************
  void setFilePath(const string _fileName) { filePath_ = _fileName; };
  void setProjectName(const string _projectName) { projectName_ = _projectName; };
  void setContent(const string _content) { content_ = _content; };
  void setAuthor(const string _author) { author_ = _author; };
  void enableLineEndComments(const bool _enableLineEndComments) {
    enableLineEndComments_ = _enableLineEndComments; };
  void enablePreLineComments(const bool _enablePreLineComments) {
    enablePreLineComments_ = _enablePreLineComments; };
  void setTVDeclarations(const vector<SignalDeclaration> & _tvDeclarations) {
    tvDeclarations_ = _tvDeclarations; };
  string getFilePath() const { return filePath_; };
  string getProjectName() const { return projectName_; };
  string getContent() const { return content_; };
  string getAuthor() const { return author_; };
  string getCommentIndicator() const { return commentIndicator_; };
  int getCommentSpaces() const { return commentSpaces_; };
  bool isEnableLineEndComments() const { return enableLineEndComments_; };
  bool isEnablePreLineComments() const { return enablePreLineComments_; };
  vector<SignalDeclaration> getTVDeclarations() const { return tvDeclarations_; };

  // **************************************************************************
  // Public methods
  // **************************************************************************
  void AddSignal(const SignalDeclaration & _tvDeclaration);

};

#endif /* TVFILESETTINGS_H_ */
