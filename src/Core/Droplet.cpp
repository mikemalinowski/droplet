/*

This holds the node registration and deregistration
code.

Author : Mike Malinowski : www.twisted.space
*/
#pragma once

// Maya Includes
#include <maya/MFnPlugin.h>

// Droplet Includes
#include "Droplet.h"
#include "DropletNode.h"
#include "../Nodes/Stacks/FloatStackSum.h"
#include "../Nodes/Stacks/FloatStackMinus.h"
#include "../Nodes/Stacks/FloatStackRange.h"
#include "../Nodes/Stacks/FloatStackMin.h"
#include "../Nodes/Stacks/FloatStackMax.h"
#include "../Nodes/Stacks/FloatStackMultiply.h"
#include "../Nodes/Stacks/FloatStackDivide.h"
#include "../Nodes/Stacks/AngleStackSum.h"

// Other Includes
#include <vector>

// -----------------------------------------------------------
// This is a shorthand function for registering a node against
// the typed plugin.
template<typename T>
void RegisterNode(MFnPlugin &plugin) {
    MString nodePrefix = "dp";
    MStatus status = plugin.registerNode(
            nodePrefix + T::NodeName(),
            T::Identifier,
            T::creator,
            T::initialize
    );
}

// ------------------------------------------------------------
// This is the plugin entry function which registers all nodes,
// commands and callbacks.
MStatus initializePlugin(MObject obj) {

	// -- Define our plugin details
	MFnPlugin plugin(obj, "Mike Malinowski", "1.0", "Any");

    MStatus status;
    RegisterNode<FloatStackSum>(plugin);
    RegisterNode<FloatStackMinus>(plugin);
    RegisterNode<FloatStackRange>(plugin);
    RegisterNode<FloatStackMin>(plugin);
    RegisterNode<FloatStackMax>(plugin);
    RegisterNode<FloatStackMultiply>(plugin);
    RegisterNode<FloatStackDivide>(plugin);
    RegisterNode<AngleStackSum>(plugin);

    return MStatus::kSuccess;
}

// --------------------------------------------------------
// This is an entry point function to the plugin which unregisters
// and commands, nodes or callbacks
MStatus uninitializePlugin(MObject obj) {

    MFnPlugin plugin(obj);
    MStatus status;

    status = plugin.deregisterNode(FloatStackSum::Identifier);
    status = plugin.deregisterNode(FloatStackMinus::Identifier);
    status = plugin.deregisterNode(FloatStackRange::Identifier);
    status = plugin.deregisterNode(FloatStackMin::Identifier);
    status = plugin.deregisterNode(FloatStackMax::Identifier);
    status = plugin.deregisterNode(FloatStackMultiply::Identifier);
    status = plugin.deregisterNode(FloatStackDivide::Identifier);
    status = plugin.deregisterNode(AngleStackSum::Identifier);

    return MStatus::kSuccess;
}