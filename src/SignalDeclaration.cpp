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
 * @file SignalDeclaration.cpp
 * @author Michael Muehlberghuber (mbgh,michmueh)
 * @date 21 August 2014
 * @brief Contains the class implementation of signal declarations.
 * @version 1.0
 */

#include "SignalDeclaration.h"

// ****************************************************************************
// Constructors/Destructors
// ****************************************************************************
/**
 * @brief Default constructor creates a "noname" signal with width 0.
 */
SignalDeclaration::SignalDeclaration() : name(""), width(0), printBase(16) {
}

/**
 * @brief Constructor allowing to set the signal's name and width.
 * @param _name Name of the signal.
 * @param _width Width of the signal in bits.
 */
SignalDeclaration::SignalDeclaration(string _name, int _width) : printBase(16) {
  name  = _name;
  width = _width;
}

/**
 * @copydoc SignalDeclaration::SignalDeclaration(string _name, int _width)
 * @param _printBase The number base in which the signal should be printed per
 *   default.
 */
SignalDeclaration::SignalDeclaration(string _name, int _width, int _printBase) {
  name      = _name;
  width     = _width;
  printBase = _printBase;
}

/**
 * @brief Destructor
 */
SignalDeclaration::~SignalDeclaration() {
}
