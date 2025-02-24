#include "global.h"
#include "TDObjects.h"
#include "glm/gtx/quaternion.hpp"

namespace glb {

	void setObjectAttribute(TDShape* shape, const char* a1, const char* a2) {
		if (!shape || !a1 || !a2) {
			return;
		}

		td::small_string p1 = td::small_string(a1);
		td::small_string p2 = td::small_string(a2);
		glb::oSOA(shape, &p1, &p2);
	}

	bool isGameFocused = false;

	loadTDBIN oLtDBin;
	validateFileExistance oValidate;
	doQuicksave oDoQuicksave;
	doQuickload oDoQuickload;
	loadResource oLoadResource;

	TDObjectList* TDOL;
	TDPlayer* player;
	TDGame* game;
	TDRenderer* renderer;
	TDScene* scene;
	tdMain oTDmain;
	wrappedDoDamage oWrappedDamage;
	setBodySomething oSetBody;
	ConstructJoint oConstructJoint;
	AttachJoint oAttachJoint;
	handleBombObjs oHandleBombObjs;
	setShapeParentBody oSetShapeParentBody;
	unknReadVoxData oIUnReadVox;
	isActiveWindow oIsActive;
	updateShapeBody tdUpdateShapeBody;
	createTextureThing oCreateTextureThing;
	constructScreen tdConstructScreen;
	updateScreen tdUpdateScreen;
	unknGraphicsInitFunction oUnknGraphicsInitFunction;
	validatePath oValidatePath;
	initScreenSecondary tdInitScreenSecondary;
	raycastCrashA tdRaycastCrashA;
	raycastCrashB tdRaycastCrashB;

	float steamDrmIntegrity;
	joinConstructor tdConstructJoint;
	initBall tdInitBall;
	initHinge tdInitHinge;
	initPrismatic tdInitPrismatic;
	initWire tdInitWire;
	attachJoint tdAttachJoint;
	updateJoint tdUpdateJoint;

	interestingUpdateFunc tdUpdateFunc;
	highlightShape oHighlightShape;
	outlineShape oOutlineShape;
	outlineBody oOutlineBody;
	SetObjectAttribute oSOA;
	SetObjectAttributeSingle oSOAS;
	spreadFire oSpreadFire;
	environmentUpdate oEnvUpdate;
	createLight oCreateLight;
	deleteBody oTdDelBdy;
	cameraPositioning oCamPos;
	damageObject oDamageObject;
	modApiLinker oMAL;
	damagePlayer oDamagePlayer;
	idfk killme;
	tPaint oPaint;
	tSpawnVox oSpawnVox;
	CreateTexture oCreateTexture;
	CreatePhysics oCreatePhysics;
	UpdateShapes oUpdateShapes;
	B_Constructor oB_Constructor;
	S_Constructor oS_Constructor;
	SetDynamic oSetDynamic;
	TMalloc oTMalloc;
	TFree oTFree;
	TRealloc oTRealloc;
	frameDrawLine oFDL;
	rayCast oRC;
	spawnFire oSpawnFire;
	createProjectile oPewpew;

	tGetString GetString;

	tMakeHole oMakeHole;
	convertPath oConvertPath;

	TluaAlloc LuaAllocF;
	tRegisterGameFunctions RegisterGameFunctions;
	tRegisterLuaFunction tdRegisterLuaFunction;
	tluaL_loadbuffer oluaL_loadbuffer;
	tluaD_pcall oluaD_pcall;
	tluaD_call oluaD_call;

	tluaL_error oluaL_error;
	tlua_pushfstring olua_pushfstring;
	tlua_pushlstring olua_pushlstring;
	tlua_createtable olua_createtable;
	tluaV_gettable oluaV_gettable;
	tluaV_settable oluaV_settable;
	tluaS_newlstr oluaS_newlstr;
	tlua_index2adr olua_index2adr;

	tHasTag oHasTag;

	createExplosion TDcreateExplosion;
	spawnParticle TDspawnParticle;

	createExplosionWrapped TDcreateExplosionWrapped;
	spawnParticleWrapped TDspawnParticleWrapped;
	ReadSubobjectsFromVox TDreadSubobjects;

	apiQuatEuler oQuatEul;
	addContextItem oAddCItem;

	uintptr_t moduleBase;
	twglSwapBuffers owglSwapBuffers;
	bool displayMenu = false;
	HWND gWnd;
	hk_SetCursorPos ocursor;
	HMODULE hMdl;
	uintptr_t plankPatchFunction;
}

namespace math {
	//gives the position of worldPosition in relation to parentPosition
	glm::vec3 localisePosition(glm::quat parentRotation, glm::vec3 parentPosition, glm::vec3 worldPosition) {
		glm::mat4 RotationMatrix = glm::toMat4(parentRotation);
		glm::vec3 localPos = glm::vec3((glm::inverse(RotationMatrix)) * -glm::vec4(parentPosition.x - worldPosition.x, parentPosition.y - worldPosition.y, parentPosition.z - worldPosition.z, 0.f));
		return localPos;
	}

	//gives the rotation of offsetRotation in relation to parentRotation
	glm::quat localiseRotation(glm::quat parentRotation, glm::quat offsetRotation) {
		return glm::inverse(parentRotation) * offsetRotation;
	}

	//gives the position of localPosition in relation to the world
	glm::vec3 expandPosition(glm::quat parentRotation, glm::vec3 parentPosition, glm::vec3 localPosition) {
		glm::mat4 RotationMatrix = glm::toMat4(parentRotation);
		return parentPosition + glm::vec3(RotationMatrix * glm::vec4(localPosition.x, localPosition.y, localPosition.z, 0.f));
	}

	//gives the rotation of worldRotation in relation to parentRotation
	glm::quat expandRotation(glm::quat parentRotation, glm::quat worldRotation) {
		return parentRotation * worldRotation;
	}

	glm::vec3 v3_td2glm(td::Vec3 in) {
		return glm::vec3(in.x, in.y, in.z);
	}

	glm::quat q_td2glm(td::Vec4 in) {
		return *(glm::quat*)&in;
	}

	td::Vec3 v3_glm2td(glm::vec3 in) {
		return { in.x, in.y, in.z };
	}

	td::Vec4 q_glm2td(glm::quat in) {
		return *(td::Vec4*)(&in);
	}

	float randFloat(float min, float max) {
		return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}
}

namespace utils {
	void highlightBody(TDBody* body, float opacity) {
		Entity* shapePtr = body->pChild;
		while (shapePtr != 0) {
			glb::oHighlightShape(glb::renderer, (TDShape*)shapePtr, opacity);
			shapePtr = shapePtr->pSibling;
		}
	}
}