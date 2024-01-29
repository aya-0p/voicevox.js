#ifndef VOICEVOX
#define VOICEVOX

#include <napi.h>
#include "voicevox_core.h"
#include <map>

class Voicevox : public Napi::ObjectWrap<Voicevox>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Env env, const Napi::CallbackInfo &info);

  Voicevox(const Napi::CallbackInfo &info);
  ~Voicevox();

  Napi::Value voicevoxGetVersionV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxErrorResultToMessageV0_12(const Napi::CallbackInfo &info);
  Napi::Value voicevoxInitializeV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxLoadModelV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxIsGpuModeV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxIsModelLoadedV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxFinalizeV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxGetMetasJsonV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxGetSupportedDevicesJsonV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxPredictDurationV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxPredictIntonationV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxDecodeV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxAudioQueryV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesisV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxTtsV0_14(const Napi::CallbackInfo &info);
  Napi::Value initializeV0_12(const Napi::CallbackInfo &info);
  Napi::Value loadModelV0_12(const Napi::CallbackInfo &info);
  Napi::Value isModelLoadedV0_12(const Napi::CallbackInfo &info);
  Napi::Value finalizeV0_10(const Napi::CallbackInfo &info);
  Napi::Value metasV0_5(const Napi::CallbackInfo &info);
  Napi::Value supportedDevicesV0_10(const Napi::CallbackInfo &info);
  Napi::Value yukarinSForwardV0_8(const Napi::CallbackInfo &info);
  Napi::Value yukarinSaForwardV0_8(const Napi::CallbackInfo &info);
  Napi::Value decodeForwardV0_8(const Napi::CallbackInfo &info);
  Napi::Value lastErrorMessageV0_5(const Napi::CallbackInfo &info);
  Napi::Value voicevoxLoadOpenjtalkDictV0_12(const Napi::CallbackInfo &info);
  Napi::Value voicevoxTtsV0_12(const Napi::CallbackInfo &info);
  Napi::Value voicevoxTtsFromKanaV0_12(const Napi::CallbackInfo &info);
  Napi::Value initializeV0_10(const Napi::CallbackInfo &info);
  Napi::Value initializeV0_5(const Napi::CallbackInfo &info);
  Napi::Value yukarinSForwardV0_5(const Napi::CallbackInfo &info);
  Napi::Value yukarinSaForwardV0_5(const Napi::CallbackInfo &info);
  Napi::Value decodeForwardV0_5(const Napi::CallbackInfo &info);

private:
  DLL dll;
  std::unordered_map<uint32_t, uintptr_t> open_jtalk_pointers;
  std::unordered_map<uint32_t, uintptr_t> user_dict_pointers;
  std::unordered_map<uint32_t, uintptr_t> model_pointers;
  std::unordered_map<uint32_t, uintptr_t> synthesizer_pointers;
};

#endif