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
 * @file SignalDeclaration.h
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 21 August 2014
 * @brief Contains a class for declaration of signals.
 * @version 1.0
 */

#ifndef TVDECLARATION_H_
#define TVDECLARATION_H_

#include <string>

using namespace std;

/**
 * @class SignalDeclaration
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 21 August 2014
 * @brief Signal declaration class.
 * @version 1.0
 */
class SignalDeclaration {

private:
	// **************************************************************************
	// Members
	// **************************************************************************
  string name;
  int width;
  int printBase;
  bool appendWidthInCaption_;

  void init();

public:
  // **************************************************************************
  // Constructors/Destructors
  // **************************************************************************
  SignalDeclaration();
  SignalDeclaration(string _name, int _width);
  SignalDeclaration(string _name, int _width, int _printBase);
  SignalDeclaration(const string _name, const int _width, const int _printBase,
  		const bool _appendWidthInCaption);
  virtual ~SignalDeclaration();

  // **************************************************************************
  // Getter/Setter
  // **************************************************************************
  int GetPrintBase() { return printBase; };
  int GetWidth() const { return width; };
  string GetName() const { return name; };
  bool IsAppendWidthInCaption() const { return appendWidthInCaption_; };
};

#endif /* TVDECLARATION_H_ */
