#pragma once

// Maya Includes
#include <maya/MPxNode.h>


// --------------------------------------------------------
// All Droplet nodes inherit from this base which ensures
// consistency in accessing the plugin identifer and node
// name.
class DropletNode : public MPxNode
{
public:
    static const int Identifier = 0;
    static const char* NodeName() { return "undefined"; }
};
