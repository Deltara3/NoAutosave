#include "./GameAPI/C/GameAPI/Game.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

bool32 DialogRunner_NotifyAutoSave_Hook(bool32 skippedState) {
    globals->notifiedAutosave = true;
    RSDK.LoadScene();
    return false;
}

void InitModAPI(void) {
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "DialogRunner_NotifyAutoSave"), DialogRunner_NotifyAutoSave_Hook, true);
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
    #if MANIA_USE_PLUS
        LinkGameLogicDLL(info);
    #else
        LinkGameLogicDLL(*info);
    #endif
    globals = Mod.GetGlobals();
    modID = id;
    InitModAPI();
    return true;
}
#endif