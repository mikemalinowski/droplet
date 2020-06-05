/*

Droplet : Attributes

Constains all the functionality within the dp::attributes
namespace. The aim is to take code that usually requires
multiple lines of input and boils it down to one or two.

Author : Mike Malinowski : www.twisted.space

*/
#pragma once

// Maya Includes
#include <maya/MAngle.h>
#include <maya/MObject.h>
#include <maya/MVector.h>
#include <maya/MGlobal.h>
#include <maya/MPxNode.h>
#include <maya/MStatus.h>
#include <maya/MMatrix.h>
#include <maya/MFnAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MMessage.h>

// Other Includes
#include <vector>
#include <string>


// --------------------------------------------------------
// All our utility functionality is always nested under our
// dp (droplet) namespace to prevent any name clashes.
namespace dp
{
	// ---------------------------------------------------------
	// All attribute functionality is nested under the attribute
	// namespace
	namespace attributes
	{

		// ----------------------------------------------------
		// Sets all the required properties of an AttributeFn
		// object to show it as an input. This includes keyable
		// writable and storable.
		inline void DefineAsInput(MFnAttribute& attrFn);

		// ----------------------------------------------------
		// Sets all the required properties of an AttributeFn
		// object to show it as an input. This includes keyable
		// writable and storable.
		inline void DefineAsOutput(MFnAttribute& attrFn);

		// ------------------------------------------------
		// Creates a float attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, float value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false);

		// ------------------------------------------------
		// Creates an int attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, int value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false);

		// ------------------------------------------------
		// Creates a bool attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, bool value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false);

		// -------------------------------------------------
		// Creates an Angle attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, MAngle value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false);

		// ------------------------------------------------
		// Creates a string attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, const char*, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false);

		// ------------------------------------------------
		// Creates a string attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, MMessage message, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false);

		/*
		// ------------------------------------------------
		// Creates an enum attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, std::vector<const char*> values, static MPxNode node, MObject& attr, bool isInput, dataBuilder = false);
		*/

		// -------------------------------------------------
		// Creates an Angle attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, MMatrix value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false);

		// -----------------------------------------------------
		// Creates a numeric collection attribute which ties the
		// three given numerical attributes together
		void Create(const char* name, MObject& attr, MObject& x, MObject& y, MObject& z);

		// --------------------------------------------------------
		// Creates a compound attribute with three children. This
		// accepts and value type which has support for the
		// dp::attributes::Create function.
		// This will create and add all the plugs.
		template <class T>
		inline void CreateCompound(const char* name, T value, static MPxNode node, MObject& c, MObject& x, MObject& y, MObject& z, bool isInput = true);
	}
}