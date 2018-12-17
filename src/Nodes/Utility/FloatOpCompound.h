/*

Droplet : FloatOpCompound

This takes in a list of values and performs the operation 
sequentially through them.

Author : Mike Malinowski : www.twisted.space

*/
#include <maya/MPxNode.h>


class FloatOpCompound : public MPxNode
{
public:

	//-------------------------------------------
	static void* creator();

	//-------------------------------------------
	static MStatus initialize();

	//-------------------------------------------
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

	//-------------------------------------------
	// These are our input plugs
	static MObject values;
	static MObject operation;

	//-------------------------------------------
	// These are our output plugs
	static MObject result;

};
