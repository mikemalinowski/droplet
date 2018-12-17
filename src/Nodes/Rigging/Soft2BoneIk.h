/*

Droplet : Soft2BoneIk

This is an implementation of the Soft IK solver described in
Andy Nicholas' blog here:
http://www.softimageblog.com/archives/108

This is not an IK solver, but a node which can be utilised
and hooked into the chain being solved to increase the translation
of the joints to soften the IK snap.

Author : Mike Malinowski : www.twisted.space
*/
#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MStatus.h>

// Create a node class
class Soft2BoneIk : public MPxNode
{
public:

	//-------------------------------------------
	// Returns a new instance of this
	// node
	static void* creator();

	//-------------------------------------------
	// Called on the initialisation of the node
	static MStatus initialize();

	//-------------------------------------------
	// This is the caluclation method
	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

	// Attribute Declaration
	static MObject FirstBoneLength;
	static MObject SecondBoneLength;

	// Forced Stretch
	static MObject AdditionalFirstBoneStretch;
	static MObject AdditionalSecondBoneStretch;

	// Matrix Parameters
	static MObject RootTarget;
	static MObject EffectorTarget;

	// Animation Sliders
	static MObject Stretch;

	// Soft IK attributes
	static MObject SoftDistance;

	// Output Attributes
	static MObject FirstBoneResult;
	static MObject SecondBoneResult;
};
