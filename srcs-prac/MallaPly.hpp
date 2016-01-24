/**********************************************************************
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
**********************************************************************/

#ifndef __MALLA_PLY
#define __MALLA_PLY
#include "MallaInd.hpp"

class MallaPly : public MallaInd {
public:
  MallaPly(const char * filename, std::string nombre = "Malla PLY");
};

#endif
