//
// FindPattern.h
//

#include <Windows.h>
#include <psapi.h>

#pragma once

namespace Utils {

	namespace Pattern {

		bool DataCompare(PBYTE pData, PBYTE bSig, char* szMask) {
			for (; *szMask; ++szMask, ++pData, ++bSig) {
				if (*szMask == 'x' && *pData != *bSig)
					return false;
			}
			return (*szMask) == 0;
		}

		PBYTE FindPattern(PBYTE dwAddress, DWORD dwSize, PBYTE pbSig, char* szMask, long offset) {
			size_t length = strlen(szMask);
			for (size_t i = NULL; i < dwSize - length; i++) {
				if (DataCompare(dwAddress + i, pbSig, szMask))
					return dwAddress + i + offset;
			}
			return 0;
		}
	}

	namespace Variables {

		unsigned __int64 ImageBase;
		HMODULE ImageModuleHandle;
		MODULEINFO ImageModuleInfo;
	}

	namespace Mordhau {

		enum bone_ids : int32_t
		{
			Global = 0,
			Position,
			Hips,
			LowerBack,
			LowerBackAdjust,
			LowerBackBelly,
			Spine,
			SpineAdjust,
			Spine1,
			Spine1Adjust,
			RightOuterBreast,
			RightInnerBreast,
			LeftOuterBreast,
			LeftInnerBreast,
			LeftShoulder,
			LeftArm,
			LeftForearm,
			LeftHand,
			LeftHandFinger05_01,
			LeftHandFinger05_02,
			LeftHandFinger05_03,
			LeftHandFinger01_01,
			LeftHandFinger01_02,
			LeftHandFinger01_03,
			LeftHandFinger02_01,
			LeftHandFinger02_02,
			LeftHandFinger02_03,
			LeftHandFinger03_01,
			LeftHandFinger03_02,
			LeftHandFinger03_03,
			LeftHandFinger04_01,
			LeftHandFinger04_02,
			LeftHandFinger04_03,
			LeftWeapon,
			LeftForearmAdjust,
			LeftForeArmTwist,
			LeftForearmTwistAdjust,
			LeftArmAdjust,
			LeftShoulderAdjust,
			LeftTrapezius,
			RightShoulder,
			RightArm,
			RightForearm,
			RightHand,
			RightHandFinger05_01,
			RightHandFinger05_02,
			RightHandFinger05_03,
			RightHandFinger01_01,
			RightHandFinger01_02,
			RightHandFinger01_03,
			RightHandFinger02_01,
			RightHandFinger02_02,
			RightHandFinger02_03,
			RightHandFinger03_01,
			RightHandFinger03_02,
			RightHandFinger03_03,
			RightHandFinger04_01,
			RightHandFinger04_02,
			RightHandFinger04_03,
			RightWeapon,
			RightForearmAdjust,
			RightForeArmTwist,
			RightForearmTwistAdjust,
			RightArmAdjust,
			RightShoulderAdjust,
			RightTrapezius,
			Neck,
			NeckAdjust,
			head,
			HeadAdjust,
			Mandible,
			LeftLips,
			LeftLipsAdjust,
			RightLips,
			RightLipsAdjust,
			MandibleAdjust,
			Tongue01,
			Tongue02,
			LeftLowMaxilar,
			LeftLowMaxilarAdjust,
			RightLowMaxilar,
			RightLowMaxilarAdjust,
			LipsInferior,
			LipsInferiorAdjust,
			LeftLipsInferior,
			LeftLipsInferiorAdjust,
			RightLipsInferior,
			RightLipsInferiorAdjust,
			LeftCheek,
			LeftCheekAdjust,
			LipsSuperior,
			LipsSuperiorAdjust,
			LeftLipsSuperiorMiddle,
			LeftLipsSuperiorMiddleAdjust,
			RightLipsSuperiorMiddle,
			RightLipsSuperiorMiddleAdjust,
			UpperLips,
			UpperLipsAdjust,
			NoseBase,
			NoseBaseAdjust,
			NoseMiddle,
			NoseMiddleAdjust,
			NoseTop,
			NoseTopAdjust,
			RightCheek,
			RightCheekAdjust,
			LeftLowCheek,
			LeftLowCheekAdjust,
			RightLowCheek,
			RightLowCheekAdjust,
			LeftEyebrowLow,
			LeftEyebrowLowAdjust,
			RightEyebrowLow,
			RightEyebrowLowAdjust,
			LeftEyebrowMiddle,
			LeftEyebrowMiddleAdjust,
			RightEyebrowMiddle,
			RightEyebrowMiddleAdjust,
			LeftEyebrowUp,
			LeftEyebrowUpAdjust,
			RightEyebrowUp,
			RightEyebrowUpAdjust,
			LeftEar,
			LeftEarAdjust,
			RightEar,
			RightEarAdjust,
			LeftEye,
			LeftEyeGlobe,
			LeftEyeAdjust,
			LeftUpperLid,
			LeftUpperLidAdjust,
			LeftLowerLid,
			LeftLowerLidAdjust,
			RightEye,
			RightEyeGlobe,
			RightEyeAdjust,
			RightUpperLid,
			RightUpperLidAdjust,
			RightLowerLid,
			RightLowerLidAdjust,
			LeftNose,
			LeftNoseAdjust,
			RightNose,
			RightNoseAdjust,
			LeftUpLeg,
			LeftLeg,
			LeftFoot,
			LeftToeBase,
			LeftLegAdjust,
			LeftUpLegAdjust,
			LeftGluteus,
			RightUpLeg,
			RightLeg,
			RightFoot,
			RightToeBase,
			RightLegAdjust,
			RightUpLegAdjust,
			RightGluteus,
			Global_RightHand,
			RightUpLeg_RightLeg,
			LeftUpLeg_LeftLeg,
			Global_LeftHand,
			Hips_LeftFoot,
			Hips_RightFoot,
			Position_LeftFoot,
			Position_RightFoot,
			Spine1_Spine1,
			LowerBack_Spine,
			LowerBack_Spine1
		};
	}

	void allocate_console( )
	{
		AllocConsole( );
		freopen( "CONOUT$", "w", stdout );
	}
}
