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

  Napi::Value voicevoxGetOnnxruntimeLibVersionedFilenameV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxGetOnnxruntimeLibUnversionedFilenameV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxOnnxruntimeLoadOnceV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxOpenJtalkRcNewV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxOpenJtalkRcUseUserDictV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxOpenJtalkRcDeleteV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxGetVersionV0_14(const Napi::CallbackInfo &info);
  Napi::Value voicevoxVoiceModelNewFromPathV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxVoiceModelIdV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxVoiceModelGetMetasJsonV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxVoiceModelDeleteV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerNewV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerDeleteV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerLoadVoiceModelV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerUnloadVoiceModelV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerIsGpuModeV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerIsLoadedVoiceModelV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateMetasJsonV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxCreateSupportedDevicesJsonV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateAudioQueryFromKanaV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateAudioQueryV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateAccentPhrasesFromKanaV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateAccentPhrasesV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerReplaceMoraDataV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerReplacePhonemeLengthV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerReplaceMoraPitchV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerSynthesisV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerTtsFromKanaV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerTtsV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxErrorResultToMessageV0_12(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictNewV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictLoadV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictAddWordV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictUpdateWordV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictRemoveWordV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictToJsonV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictImportV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictSaveV0_16(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictDeleteV0_16(const Napi::CallbackInfo &info);
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
  Napi::Value voicevoxAccentPhrasesV0_15(const Napi::CallbackInfo &info);
  Napi::Value voicevoxMoraLengthV0_15(const Napi::CallbackInfo &info);
  Napi::Value voicevoxMoraPitchV0_15(const Napi::CallbackInfo &info);
  Napi::Value voicevoxMoraDataV0_15(const Napi::CallbackInfo &info);
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
  const VoicevoxOnnxruntime *onnxruntime_pointer;
  std::unordered_map<uint32_t, OpenJtalkRc *> open_jtalk_pointers;
  std::unordered_map<uint32_t, VoicevoxUserDict *> user_dict_pointers;
  std::unordered_map<uint32_t, VoicevoxVoiceModel *> model_pointers;
  std::unordered_map<uint32_t, VoicevoxSynthesizer *> synthesizer_pointers;
};

#endif