//
// Created by Perfare on 2020/7/4.
//

#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/system_properties.h>
#include <dlfcn.h>
#include <jni.h>
#include <thread>
#include <sys/mman.h>
#include <linux/unistd.h>
#include <array>

#include "hack.h"
#include "il2cpp_dump.h"
#include "ZhenxiLog.h"
#include "logging.h"

#include "dlfcn_compat.h"
//#include "xdl.h"


void hack_start(const char *path, const char *game_data_dir) {
    SandHook::ElfImg elfImg(path);
    il2cpp_api_init(elfImg);
    il2cpp_dump(game_data_dir);
    LOG(INFO)<< ">>>>>>>>>> il2cpp_dump is finish ";
}


struct NativeBridgeCallbacks {
    uint32_t version;
    void *initialize;

    void *(*loadLibrary)(const char *libpath, int flag);

    void *(*getTrampoline)(void *handle, const char *name, const char *shorty, uint32_t len);

    void *isSupported;
    void *getAppEnv;
    void *isCompatibleWith;
    void *getSignalHandler;
    void *unloadLibrary;
    void *getError;
    void *isPathSupported;
    void *initAnonymousNamespace;
    void *createNamespace;
    void *linkNamespaces;

    void *(*loadLibraryExt)(const char *libpath, int flag, void *ns);
};

void hack_prepare(const char *path, const char *game_data_dir) {
    LOG(INFO)<< "hack_prepare is start ,start hack_thread";
    std::thread hack_thread(hack_start,path,game_data_dir);
    hack_thread.detach();
}