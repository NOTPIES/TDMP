#pragma once
#include "types.h"
#include "mem.h"
#include "glew.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <ctime>
#include "detours.h"
#include <mutex>
#include "global.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <random>
#include "TDObjects.h"
#include "glm/glm.hpp"
#include "crashHandler.h"
#include "Script.h"
#include "Lua.hpp"
#include "td_memory.h"

struct RaycastFilter
{
    int32_t m_Mask = -1;
    int32_t m_Allowed;
    int32_t m_Ignored;
    bool m_RejectTransparent;
    uint8_t m_Pad[3];
    td::small_vector<TDBody*> m_IgnoredBodies;
    TDBody* m_IgnoredBodiesMemory[4]; // small_vector should support pre-reserved buffers... not going to add that right now.
    td::small_vector<TDShape*> m_IgnoredShapes;
};

namespace td {
    class small_string;
}

//world
typedef void(__fastcall* environmentUpdate)(uintptr_t env);
typedef bool(__fastcall* rayCast)(TDScene* scene, td::Vec3* pos, td::Vec3* rot, float dist, RaycastFilter* filter, float* outDist, td::Vec3* out, uintptr_t* out_shape, uintptr_t* out_palette);
typedef void(__fastcall* frameDrawLine)(TDRenderer* renderer, const td::Vec3& p1, const td::Vec3& p2, const td::Color& c1, const td::Color& c2, bool use_depth);
typedef void(__fastcall* highlightShape)(TDRenderer* renderer, TDShape* shape, float opacity);
typedef void(__fastcall* outlineShape)(TDRenderer* renderer, TDShape* shape, td::Color* colour, float opacity);
typedef void(__fastcall* outlineBody)(TDRenderer* renderer, TDBody* shape, td::Color* colour, float opacity);
typedef void(__fastcall* wrappedDoDamage)(TDScene* scene, td::Vec3* position, float damageA, float damageB, int unkn1, int* unkn2);
typedef void(__fastcall* setBodySomething)(uintptr_t body, __int8 a1, __int8 a2);
typedef void(__fastcall* handleBombObjs)(uintptr_t a1);
typedef void(__fastcall* setShapeParentBody)(TDShape* shape, byte unkn, TDBody* body);
typedef char(__fastcall* raycastCrashA)(void* a1, float* a2, float* a3, float* a4, float* a5);
typedef char(__fastcall* raycastCrashB)(void* a1, void* a2);

//creation
typedef uintptr_t(__fastcall* tSpawnVox) (td::small_string* path, td::small_string* subpath, float scale);
typedef uintptr_t(__fastcall* spawnParticle)(DWORD* ptr, td::particleInfo* info, td::Vec3& position, td::Vec3& velocity, float lifetime);
typedef void(__fastcall* createExplosion)(uintptr_t scene, td::Vec3* pos, float radius);
typedef void(__fastcall* createLight)(TDRenderer* renderer, td::Vec3* a2, td::Vec3* a3, float a4, float a5, float a6, float a7);
typedef void(__fastcall* spawnFire)(uintptr_t scene, td::Vec3* pos);
typedef void(__fastcall* CreateTexture) (uintptr_t ptr);
typedef void(__fastcall* CreatePhysics) (uintptr_t ptr);
typedef void(__fastcall* createProjectile)(TDScene* scene, td::Vec3* pos, td::Vec3* dir, INT32 type, float un1, int un2);
typedef void(__fastcall* deleteBody) (INT64 a1, INT64 a2, INT64 a3, INT64 a4, INT64 a5, INT64 a6, INT64 a7, INT64 a8);
typedef void(__fastcall* UpdateShapes) (uintptr_t ptr);
typedef void(__fastcall* B_Constructor) (uintptr_t ptr, uintptr_t parent);
typedef uintptr_t(__fastcall* S_Constructor) (uintptr_t ptr, uintptr_t parent);
typedef void(__fastcall* SetDynamic) (uintptr_t ptr, bool dynamic);
typedef void(__fastcall* SetObjectAttribute) (TDShape* shape, td::small_string* attribute, td::small_string* attribute2);
typedef void(__fastcall* SetObjectAttributeSingle) (TDShape* shape, td::small_string* attribute);
typedef void(__fastcall* ConstructJoint) (uintptr_t joint);
typedef void(__fastcall* AttachJoint) (void* a1, void* a2, void* a3, void* a4, void* a5);
typedef int(__fastcall* ReadSubobjectsFromVox) (td::small_string* path, int* out);
typedef void*(__fastcall* unknReadVoxData) (void* a1, void* a2);
typedef __int64(__fastcall* updateShapeBody)(uintptr_t a1, uintptr_t a2);
typedef __int64(__fastcall* constructScreen)(TDScreen* a1, uintptr_t a2);
typedef __int64(__fastcall* unknGraphicsInitFunction)(void* a1);
typedef void*(__fastcall* initScreenSecondary)(void* a1, void* a2, void* a3);

typedef void*(__fastcall* tGetString)(void* registry, td::small_string* out, td::small_string* keyName);

//lua
typedef void* (__fastcall* TluaAlloc)(void* userData, void* ptr, size_t oldSize, size_t newSize);
typedef void (*tRegisterGameFunctions)		(CScriptCore* pScriptCore);
typedef void (*tRegisterLuaFunction)		(CScriptCore_LuaState* pSCLS, td::small_string * sFunctionName, void* pFunction);
typedef int	(*tluaL_loadbuffer)				(lua_State* L, const char* buff, size_t size, const char* name);
typedef int	(*tluaD_call)				(lua_State* L, StkId func, int nResults);
typedef int	(*tluaD_pcall)				(lua_State* L, Pfunc func, void* u, ptrdiff_t old_top, ptrdiff_t ef);

//lua push functions and stuff
typedef void (*tluaL_error)				(lua_State* L, const char* fmt, ...);
typedef const char* (__fastcall* tlua_pushfstring)				(lua_State* L, const char* fmt, ...);
typedef int(__fastcall* tlua_pushlstring)				(lua_State* L, const char* s, size_t);
typedef int(__fastcall* tlua_createtable)				(lua_State* L, int narray, int nrec);
typedef int(__fastcall* tluaV_gettable)				(lua_State* L, const TValue* t, TValue* key, StkId val);
typedef int(__fastcall* tluaV_settable)				(lua_State* L, const TValue* t, TValue* key, StkId val);
typedef int(__fastcall* tluaS_newlstr)				(lua_State* L, const char* str, size_t l);
typedef TValue* (__fastcall* tlua_index2adr)				(lua_State* L, int idx);

typedef bool(__fastcall* tHasTag)				(Entity* ent, td::small_string tag);
typedef void(__fastcall* tMakeHole)				(void* a1, void* a2, td::Vec3* pos, float softDmg, float mediumDmg, float hardDmg, bool noSound, void* a3);

typedef td::small_string* (__fastcall* convertPath)(CScriptCore* special, td::small_string* output, td::small_string* path);

//a1: GAME + 0xA8
//a2: small_string* containing path
//a3: small_string* containing path with "RAW:" at the start
//a4: small_string* containing the resource type (can be blank but not null)
typedef void*(__fastcall* validatePath)(void* special, td::small_string* path, td::small_string* path_technical, td::small_string* type);

//joints
typedef void(__fastcall* joinConstructor)(TDJoint* joint, Entity* parent);
typedef void(__fastcall* initBall)(TDJoint* joint, TDShape* shape1, TDShape* shape2, td::Vec3* point1, td::Vec3* point2);
typedef void(__fastcall* initHinge)(TDJoint* joint, td::Transform* transform, float size, int64_t strengh, float springiness, bool collide, td::Vec2* limits);
typedef void(__fastcall* initPrismatic)(TDJoint* joint, td::Transform* transform, float size, bool collide, td::Vec2* limits);
typedef void(__fastcall* initWire)(TDJoint* joint, td::Vec3* p1, td::Vec3* p2, float size, td::Color color, float slack, float strengh, float maxStretch);
typedef void(__fastcall* attachJoint)(TDJoint* joint, TDShape* shape1, TDShape* shape2, td::Vec3* pos1, td::Vec3* pos2);
typedef void(__fastcall* updateJoint)(TDJoint* joint);

//misc
typedef void(__stdcall* damageObject)(uintptr_t a1, uintptr_t a2, td::Vec3* a3, float a4, float a5, uintptr_t a6, uintptr_t a7, uintptr_t a8);
typedef void(__stdcall* createExplosionWrapped)(double unkn, td::Vec3* pos, float power);
typedef void(__fastcall* spawnParticleWrapped)(double a1, __int64 a2);
typedef void(__fastcall* tdMain)(TDGame* game, void* a2);
typedef BOOL(WINAPI* hk_SetCursorPos)(int, int);
typedef BOOL(__stdcall* twglSwapBuffers)(_In_ HDC hDc);
typedef void (*tPaint) (uintptr_t* Scene, td::Vec3* Position, float size, int darken, float dispersion); 
typedef void(__fastcall* cameraPositioning)(uintptr_t a1, float a2, uintptr_t a3, uintptr_t a4);
typedef void(__fastcall* modApiLinker)(__int64 a1);
typedef char(__fastcall* idfk) (__int64 a1, __int64 a2, signed int* a3, signed int* a4, signed int* a5);
typedef void(__fastcall* damagePlayer) (TDPlayer* player, float damage);
typedef void*(__cdecl* TRealloc)(void* mem, size_t _Size);
typedef void(__fastcall* spreadFire)(__int64 a1, float v2);
typedef void(__fastcall* addContextItem)(char* a1, int a2, int a3, float* a4);
typedef bool(__fastcall* isActiveWindow)(void* a1);
typedef bool(__fastcall* createTextureThing)(void* texture, void* pixelBuffer, bool a3);
typedef void(__fastcall* updateScreen)(TDScreen* screen);
typedef void*(__fastcall* loadResource)(void* a1, void* a2, int a3);

//td maths
typedef __int64(__fastcall* apiQuatEuler)(float* a1, float* a2);
typedef __int64(__fastcall* interestingUpdateFunc)(TDBody* body, __int8 a2, __int8 a3);

//TD files
typedef bool(__fastcall* doQuicksave)(TDScene* a1);
typedef bool(__fastcall* doQuickload)(TDScene* a1);
typedef void* (__fastcall* validateFileExistance)(__int64 a1, void* a2, td::small_string* path);
typedef char(__fastcall* loadTDBIN)(__int64 a1, td::small_string* a2);

//SEE TDFUNCS.CPP FOR SIGSCANNING
namespace glb {
    void setObjectAttribute(TDShape* shape, const char* a1, const char* a2);

    extern bool isGameFocused;

    extern loadTDBIN oLtDBin;
    extern validateFileExistance oValidate;
    extern doQuicksave oDoQuicksave;
    extern doQuickload oDoQuickload;
    extern createTextureThing oCreateTextureThing;
    extern unknGraphicsInitFunction oUnknGraphicsInitFunction;
    extern validatePath oValidatePath;
    extern loadResource oLoadResource;
    extern raycastCrashA tdRaycastCrashA;
    extern raycastCrashB tdRaycastCrashB;

    extern TDObjectList* TDOL;
    extern TDPlayer* player;
    extern TDGame* game;
    extern TDRenderer* renderer;
    extern TDScene* scene;
    extern tdMain oTDmain;
    extern wrappedDoDamage oWrappedDamage;
    extern setBodySomething oSetBody;
    extern handleBombObjs oHandleBombObjs;
    extern setShapeParentBody oSetShapeParentBody;
    extern unknReadVoxData oIUnReadVox;
    extern isActiveWindow oIsActive;

    extern joinConstructor tdConstructJoint;
    extern initBall tdInitBall;
    extern initHinge tdInitHinge;
    extern initPrismatic tdInitPrismatic;
    extern initWire tdInitWire;
    extern attachJoint tdAttachJoint;
    extern updateJoint tdUpdateJoint;
    extern updateShapeBody tdUpdateShapeBody;
    extern constructScreen tdConstructScreen;
    extern updateScreen tdUpdateScreen;
    extern initScreenSecondary tdInitScreenSecondary;
    extern float steamDrmIntegrity;

    extern interestingUpdateFunc tdUpdateFunc;
    extern highlightShape oHighlightShape;
    extern outlineShape oOutlineShape;
    extern outlineBody oOutlineBody;
    extern SetObjectAttribute oSOA;
    extern SetObjectAttributeSingle oSOAS;
    extern spreadFire oSpreadFire;
    extern environmentUpdate oEnvUpdate;
    extern createLight oCreateLight;
    extern deleteBody oTdDelBdy;
    extern cameraPositioning oCamPos;
    extern damageObject oDamageObject;
    extern modApiLinker oMAL;
    extern damagePlayer oDamagePlayer;
    extern idfk killme;
    extern tPaint oPaint;
    extern tSpawnVox oSpawnVox;
    extern CreateTexture oCreateTexture;
    extern CreatePhysics oCreatePhysics;
    extern UpdateShapes oUpdateShapes;
    extern B_Constructor oB_Constructor;
    extern S_Constructor oS_Constructor;
    extern SetDynamic oSetDynamic;
    extern TRealloc oTRealloc;
    extern frameDrawLine oFDL;
    extern rayCast oRC;
    extern spawnFire oSpawnFire;
    extern createProjectile oPewpew;

    extern tGetString GetString;

    extern tMakeHole oMakeHole;
    extern convertPath oConvertPath;

    extern TluaAlloc LuaAllocF;
    extern tRegisterGameFunctions RegisterGameFunctions;
    extern tRegisterLuaFunction tdRegisterLuaFunction;
    extern tluaL_loadbuffer oluaL_loadbuffer;
    extern tluaD_pcall oluaD_pcall;
    extern tluaD_call oluaD_call;

    extern tluaL_error oluaL_error;
    extern tlua_pushfstring olua_pushfstring;
    extern tlua_pushlstring olua_pushlstring;
    extern tlua_createtable olua_createtable;
    extern tluaV_gettable oluaV_gettable;
    extern tluaV_settable oluaV_settable;
    extern tluaS_newlstr oluaS_newlstr;
    extern tlua_index2adr olua_index2adr;

    extern tHasTag oHasTag;
    
    extern createExplosion TDcreateExplosion;
    extern spawnParticle TDspawnParticle;
    extern createExplosionWrapped TDcreateExplosionWrapped;
    extern spawnParticleWrapped TDspawnParticleWrapped;
    extern ReadSubobjectsFromVox TDreadSubobjects;

    extern uintptr_t moduleBase;
    extern twglSwapBuffers owglSwapBuffers;
    extern bool displayMenu;
    extern HWND gWnd;
    extern hk_SetCursorPos ocursor;
    extern HMODULE hMdl;

    extern apiQuatEuler oQuatEul;
    extern addContextItem oAddCItem;

    extern uintptr_t plankPatchFunction;
}

namespace math {

    const float pi = 3.1415926535f;

    //gives the position of worldPosition in relation to parentPosition
    glm::vec3 localisePosition(glm::quat parentRotation, glm::vec3 parentPosition, glm::vec3 worldPosition);

    //gives the rotation of offsetRotation in relation to parentRotation
    glm::quat localiseRotation(glm::quat parentRotation, glm::quat offsetRotation);

    //gives the position of localPosition in relation to the world
    glm::vec3 expandPosition(glm::quat parentRotation, glm::vec3 parentPosition, glm::vec3 localPosition);

    //gives the rotation of worldRotation in relation to parentRotation
    glm::quat expandRotation(glm::quat parentRotation, glm::quat worldRotation);
    glm::vec3 v3_td2glm(td::Vec3 in);
    glm::quat q_td2glm(td::Vec4 in);
    td::Vec3 v3_glm2td(glm::vec3 in);
    td::Vec4 q_glm2td(glm::quat in);
    float randFloat(float min, float max);
}

namespace utils {
    void highlightBody(TDBody* body, float opacity);
}