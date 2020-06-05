/*

Droplet : Attributes

Constains all the functionality within the dp::attributes
namespace. The aim is to take code that usually requires
multiple lines of input and boils it down to one or two.

Author : Mike Malinowski : www.twisted.space

*/
#pragma once

// Maya Includes
#include <maya/MFnData.h>
#include <maya/MAngle.h>
#include <maya/MObject.h>
#include <maya/MVector.h>
#include <maya/MGlobal.h>
#include <maya/MPxNode.h>
#include <maya/MStatus.h>
#include <maya/MMatrix.h>
#include <maya/MMessage.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnCompoundAttribute.h>

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
		inline void DefineAsInput(MFnAttribute& attrFn)
		{
			attrFn.setKeyable(true);
			attrFn.setWritable(true);
			attrFn.setStorable(true);
			attrFn.setCached(true);
			attrFn.setIndexMatters(true);
		}

		// ----------------------------------------------------
		// Sets all the required properties of an AttributeFn
		// object to show it as an input. This includes keyable
		// writable and storable.
		inline void DefineAsOutput(MFnAttribute& attrFn)
		{
			attrFn.setKeyable(false);
			attrFn.setWritable(false);
			attrFn.setStorable(false);
		}

		// ------------------------------------------------
		// Creates a float attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, float value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false)
		{

			MFnNumericAttribute attrFn;

			// -- Create the attribute
			attr = attrFn.create(name, name, MFnNumericData::kFloat, value);
			attrFn.setArray(isArray);
			attrFn.setUsesArrayDataBuilder(dataBuilder);

			if (isInput) {
				DefineAsInput(attrFn);
			}
			else {
				DefineAsOutput(attrFn);
			}

			node.addAttribute(attr);
		}

		// ------------------------------------------------
		// Creates an int attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, int value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false)
		{

			MFnNumericAttribute attrFn;

			// -- Create the attribute
			attr = attrFn.create(name, name, MFnNumericData::kInt, value);
			attrFn.setArray(isArray);
			attrFn.setUsesArrayDataBuilder(dataBuilder);

			if (isInput) {
				DefineAsInput(attrFn);
			}
			else {
				DefineAsOutput(attrFn);
			}
			node.addAttribute(attr);
		}

		// ------------------------------------------------
		// Creates a bool attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, bool value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false)
		{

			MFnNumericAttribute attrFn;

			// -- Create the attribute
			attr = attrFn.create(name, name, MFnNumericData::kInt, value);
			attrFn.setArray(isArray);
			attrFn.setUsesArrayDataBuilder(dataBuilder);

			if (isInput) {
				DefineAsInput(attrFn);
			}
			else {
				DefineAsOutput(attrFn);
			}
			node.addAttribute(attr);
		}

		// -------------------------------------------------
		// Creates an Angle attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, MAngle value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false)
		{

			MFnUnitAttribute attrFn;

			// -- Create the attribute
			attr = attrFn.create(name, name, value);
			attrFn.setArray(isArray);
			attrFn.setUsesArrayDataBuilder(dataBuilder);

			if (isInput) {
				DefineAsInput(attrFn);
			}
			else {
				DefineAsOutput(attrFn);
			}
			node.addAttribute(attr);
		}

		// -------------------------------------------------
		// Creates an Angle attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, MMatrix value, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false)
		{

			MFnMatrixAttribute attrFn;

			// -- Create the attribute
			attr = attrFn.create(name, name, attrFn.kDouble);
			attrFn.setArray(isArray);
			attrFn.setUsesArrayDataBuilder(dataBuilder);

			if (isInput) {
				DefineAsInput(attrFn);
			}
			else {
				DefineAsOutput(attrFn);
			}
			node.addAttribute(attr);
		}

		void Create(const char* name, const char*, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false)
		{

			MFnTypedAttribute attrFn;

			// -- Create the attribute
			attr = attrFn.create(name, name, MFnData::kString);
			attrFn.setArray(isArray);
			attrFn.setUsesArrayDataBuilder(dataBuilder);

			if (isInput) {
				DefineAsInput(attrFn);
			}
			else {
				DefineAsOutput(attrFn);
			}
			node.addAttribute(attr);
		}
		
		void Create(const char* name, MMessage message, static MPxNode node, MObject& attr, bool isInput, bool isArray = false, bool dataBuilder = false)
		{

			MFnMessageAttribute attrFn;

			// -- Create the attribute
			attr = attrFn.create(name, name);
			attrFn.setArray(isArray);
			attrFn.setUsesArrayDataBuilder(dataBuilder);

			if (isInput) {
				DefineAsInput(attrFn);
			}
			else {
				DefineAsOutput(attrFn);
			}
			node.addAttribute(attr);
		}
		
		/*
		// ------------------------------------------------
		// Creates an enum attribute and adds the attribute
		// to the node. You can use the isInput property to
		// define whether or not the attribute should be an
		// input or an output.
		void Create(const char* name, std::vector<const char*> values, static MPxNode node, MObject& attr, bool isInput, bool dataBuilder = false)
		{

			MFnEnumAttribute attrFn;

			// -- Create the attribute
			attr = attrFn.create(name, name);

			if (isInput) {
				DefineAsInput(attrFn);
			}
			else {
				DefineAsOutput(attrFn);
			}

			// -- Add all the enumerators
			short index = 0;
			for (const char* item : values) {
				attrFn.addField(item, index);
				index++;
			}
			node.addAttribute(attr);
		}
		*/
		// -----------------------------------------------------
		// Creates a numeric collection attribute which ties the
		// three given numerical attributes together
		void Create(const char* name, MObject& attr, MObject& x, MObject& y, MObject& z)
		{
			MFnNumericAttribute attrFn;
			attr = attrFn.create(name, name, x, y, z);
		}

		// --------------------------------------------------------
		// Creates a compound attribute with three children. This
		// accepts and value type which has support for the
		// dp::attributes::Create function.
		// This will create and add all the plugs.
		template <class T>
		inline void CreateCompound(const char* name, T value, static MPxNode node, MObject& c, MObject& x, MObject& y, MObject& z, bool isInput = true)
		{
			std::string nameX = std::string(name) + "X";
			Create(nameX.c_str(), value, node, x, isInput);

			std::string nameY = std::string(name) + "Y";
			Create(nameY.c_str(), value, node, y, isInput);

			std::string nameZ = std::string(name) + "Z";
			Create(nameZ.c_str(), value, node, z, isInput);

			MFnNumericAttribute attrFn;
			c = attrFn.create(name, name, x, y, z);
			node.addAttribute(c);
		}
	}
}