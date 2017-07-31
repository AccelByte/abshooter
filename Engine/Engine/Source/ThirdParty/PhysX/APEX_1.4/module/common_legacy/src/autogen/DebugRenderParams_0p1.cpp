// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2015 NVIDIA Corporation. All rights reserved.

// This file was generated by NvParameterized/scripts/GenParameterized.pl


#include "DebugRenderParams_0p1.h"
#include <string.h>
#include <stdlib.h>

using namespace NvParameterized;

namespace nvidia
{
namespace parameterized
{

using namespace DebugRenderParams_0p1NS;

const char* const DebugRenderParams_0p1Factory::vptr =
    NvParameterized::getVptr<DebugRenderParams_0p1, DebugRenderParams_0p1::ClassAlignment>();

const uint32_t NumParamDefs = 13;
static NvParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
};

#define TENUM(type) nvidia::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NvParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 11 },
	{ TYPE_BOOL, false, (size_t)(&((ParametersStruct*)0)->Enable), NULL, 0 }, // Enable
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->Scale), NULL, 0 }, // Scale
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->LodBenefits), NULL, 0 }, // LodBenefits
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->RelativeLodBenefitsScreenPos), NULL, 0 }, // RelativeLodBenefitsScreenPos
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->RelativeLodBenefitsThickness), NULL, 0 }, // RelativeLodBenefitsThickness
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->LodDistanceScale), NULL, 0 }, // LodDistanceScale
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->RenderNormals), NULL, 0 }, // RenderNormals
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->RenderTangents), NULL, 0 }, // RenderTangents
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->RenderBitangents), NULL, 0 }, // RenderBitangents
	{ TYPE_BOOL, false, (size_t)(&((ParametersStruct*)0)->Bounds), NULL, 0 }, // Bounds
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->moduleName), CHILDREN(11), 1 }, // moduleName
	{ TYPE_REF, false, 1 * sizeof(NvParameterized::Interface*), NULL, 0 }, // moduleName[]
};


bool DebugRenderParams_0p1::mBuiltFlag = false;
NvParameterized::MutexType DebugRenderParams_0p1::mBuiltFlagMutex;

DebugRenderParams_0p1::DebugRenderParams_0p1(NvParameterized::Traits* traits, void* buf, int32_t* refCount) :
	NvParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &DebugRenderParams_0p1FactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

DebugRenderParams_0p1::~DebugRenderParams_0p1()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void DebugRenderParams_0p1::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NvParameterized::Traits* traits = mParameterizedTraits;
	int32_t* refCount = mRefCount;
	void* buf = mBuffer;

	this->~DebugRenderParams_0p1();

	NvParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NvParameterized::DefinitionImpl* DebugRenderParams_0p1::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NvParameterized::DefinitionImpl* DebugRenderParams_0p1::getParameterDefinitionTree(void) const
{
	DebugRenderParams_0p1* tmpParam = const_cast<DebugRenderParams_0p1*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NvParameterized::ErrorType DebugRenderParams_0p1::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NvParameterized::ErrorType DebugRenderParams_0p1::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void DebugRenderParams_0p1::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<DebugRenderParams_0p1::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */
/* [0] - moduleName (not an array of structs) */

void DebugRenderParams_0p1::freeParameterDefinitionTable(NvParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void DebugRenderParams_0p1::buildTree(void)
{

	uint32_t allocSize = sizeof(NvParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NvParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(ParamDefTable, 0, allocSize);

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		NV_PARAM_PLACEMENT_NEW(ParamDefTable + i, NvParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="Enable"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("Enable", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Enable/disable debug rendering", true);
		ParamDefTable[1].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="Scale"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("Scale", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Debug rendering scale", true);
		ParamDefTable[2].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="LodBenefits"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("LodBenefits", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "LOD benefit debug visualization", true);
		ParamDefTable[3].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="RelativeLodBenefitsScreenPos"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("RelativeLodBenefitsScreenPos", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("max", double(1.0), true);
		HintTable[1].init("min", double(-1.0), true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("max", double(1.0), true);
		HintTable[1].init("min", double(-1.0), true);
		HintTable[2].init("shortDescription", "The y-axis value of the relative benefits bar (-1.0 - 1.0)", true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="RelativeLodBenefitsThickness"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("RelativeLodBenefitsThickness", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "The thickness scale of the relative benefits bar", true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="LodDistanceScale"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("LodDistanceScale", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "LOD distance debug visualization", true);
		ParamDefTable[6].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="RenderNormals"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("RenderNormals", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws the normals (blue) of the rendered mesh. (scalable)", true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="RenderTangents"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("RenderTangents", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws the tangents (red) of the rendered mesh. (scalable)", true);
		ParamDefTable[8].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=9, longName="RenderBitangents"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[9];
		ParamDef->init("RenderBitangents", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws the bitangents (green) of the rendered mesh. (scalable)", true);
		ParamDefTable[9].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=10, longName="Bounds"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[10];
		ParamDef->init("Bounds", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws the bounds of every apex actor", true);
		ParamDefTable[10].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=11, longName="moduleName"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[11];
		ParamDef->init("moduleName", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		ParamDefTable[11].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		HintTable[1].init("shortDescription", "Module name", true);
		ParamDefTable[11].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */


		static const char* const RefVariantVals[] = { "BasicFSDebugRenderParams", "BasicIosDebugRenderParams", "ParticleIosDebugRenderParams", "ClothingDebugRenderParams", "DestructibleDebugRenderParams", "EmitterDebugRenderParams", "ForceFieldDebugRenderParams", "IofxDebugRenderParams", "TurbulenceFSDebugRenderParams", "ParticlesDebugRenderParams" };
		ParamDefTable[11].setRefVariantVals((const char**)RefVariantVals, 10);


		ParamDef->setArraySize(-1);
		static const uint8_t dynHandleIndices[1] = { 0, };
		ParamDef->setDynamicHandleIndicesMap(dynHandleIndices, 1);

	}

	// Initialize DefinitionImpl node: nodeIndex=12, longName="moduleName[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[12];
		ParamDef->init("moduleName", TYPE_REF, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		ParamDefTable[12].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		HintTable[1].init("shortDescription", "Module name", true);
		ParamDefTable[12].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */


		static const char* const RefVariantVals[] = { "BasicFSDebugRenderParams", "BasicIosDebugRenderParams", "ParticleIosDebugRenderParams", "ClothingDebugRenderParams", "DestructibleDebugRenderParams", "EmitterDebugRenderParams", "ForceFieldDebugRenderParams", "IofxDebugRenderParams", "TurbulenceFSDebugRenderParams", "ParticlesDebugRenderParams" };
		ParamDefTable[12].setRefVariantVals((const char**)RefVariantVals, 10);



	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[11];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(2);
		Children[2] = PDEF_PTR(3);
		Children[3] = PDEF_PTR(4);
		Children[4] = PDEF_PTR(5);
		Children[5] = PDEF_PTR(6);
		Children[6] = PDEF_PTR(7);
		Children[7] = PDEF_PTR(8);
		Children[8] = PDEF_PTR(9);
		Children[9] = PDEF_PTR(10);
		Children[10] = PDEF_PTR(11);

		ParamDefTable[0].setChildren(Children, 11);
	}

	// SetChildren for: nodeIndex=11, longName="moduleName"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(12);

		ParamDefTable[11].setChildren(Children, 1);
	}

	mBuiltFlag = true;

}
void DebugRenderParams_0p1::initStrings(void)
{
}

void DebugRenderParams_0p1::initDynamicArrays(void)
{
	moduleName.buf = NULL;
	moduleName.isAllocated = true;
	moduleName.elementSize = sizeof(NvParameterized::Interface*);
	moduleName.arraySizes[0] = 0;
}

void DebugRenderParams_0p1::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	Enable = bool(false);
	Scale = float(0);
	LodBenefits = float(0);
	RelativeLodBenefitsScreenPos = float(-0.8);
	RelativeLodBenefitsThickness = float(0.6);
	LodDistanceScale = float(0);
	RenderNormals = float(0);
	RenderTangents = float(0);
	RenderBitangents = float(0);
	Bounds = bool(false);

	initDynamicArrays();
	initStrings();
	initReferences();
}

void DebugRenderParams_0p1::initReferences(void)
{
}

void DebugRenderParams_0p1::freeDynamicArrays(void)
{
	if (moduleName.isAllocated && moduleName.buf)
	{
		mParameterizedTraits->free(moduleName.buf);
	}
}

void DebugRenderParams_0p1::freeStrings(void)
{
}

void DebugRenderParams_0p1::freeReferences(void)
{

	for (int i = 0; i < moduleName.arraySizes[0]; ++i)
	{
		if (moduleName.buf[i])
		{
			moduleName.buf[i]->destroy();
		}
	}
}

} // namespace parameterized
} // namespace nvidia
