#include <napi.h>
#include "voicevox.h"
#include <iostream>

Napi::Object CreateObject(const Napi::CallbackInfo &info)
{
  return Voicevox::NewInstance(info.Env(), info);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
  Napi::Object new_exports = Napi::Function::New(env, CreateObject);
  return Voicevox::Init(env, new_exports);
}

NODE_API_MODULE(voicevox, InitAll)
