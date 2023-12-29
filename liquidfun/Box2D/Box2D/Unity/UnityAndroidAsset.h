#ifndef WIN32
#pragma once
#ifndef UnityAndroidAsset
#define UnityAndroidAsset


#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

static AAssetManager* _assetManager;

// link to java class, call init from unity
extern "C" int  Java_uaa_UnityAndroidAsset_nativeInit(JNIEnv * env, jclass clazz, jobject assetManager)
{
	_assetManager = AAssetManager_fromJava(env, assetManager);
	if (_assetManager)
		return 1;
	return 0;
}

// open an asset
extern "C" AAsset* uaa_open(char* path, int mode)
{
	AAsset* asset = AAssetManager_open(_assetManager, path, mode);
	return asset;
}

// get asset length
extern "C" int uaa_get_length(void* asset)
{
	return AAsset_getLength((AAsset*)asset);
}

// close an asset
extern "C" void uaa_close(void* asset)
{
	AAsset_close((AAsset*)asset);
}

// read data to buffer
extern "C" int uaa_read(void* asset, unsigned char* buf, int offset, int count)
{
	return AAsset_read((AAsset*)asset, buf + offset, count);
}

// jump stream pointer
extern "C" long uaa_seek(void* asset, int offset, int where)
{
	return AAsset_seek((AAsset*)asset, offset, where);
}
#endif // !UnityAndroidAsset
#endif // !WIN32
