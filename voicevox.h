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

  Napi::Value voicevoxOpenJtalkRcNew(const Napi::CallbackInfo &info);
  Napi::Value voicevoxOpenJtalkRcUseUserDict(const Napi::CallbackInfo &info);
  Napi::Value voicevoxOpenJtalkRcDelete(const Napi::CallbackInfo &info);
  Napi::Value voicevoxGetVersion(const Napi::CallbackInfo &info);
  Napi::Value voicevoxVoiceModelNewFromPath(const Napi::CallbackInfo &info);
  Napi::Value voicevoxVoiceModelId(const Napi::CallbackInfo &info);
  Napi::Value voicevoxVoiceModelGetMetasJson(const Napi::CallbackInfo &info);
  Napi::Value voicevoxVoiceModelDelete(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerNew(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerDelete(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerLoadVoiceModel(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerUnloadVoiceModel(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerIsGpuMode(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerIsLoadedVoiceModel(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateMetasJson(const Napi::CallbackInfo &info);
  Napi::Value voicevoxCreateSupportedDevicesJson(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateAudioQueryFromKana(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateAudioQuery(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateAccentPhrasesFromKana(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerCreateAccentPhrases(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerReplaceMoraData(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerReplacePhonemeLength(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerReplaceMoraPitch(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerSynthesis(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerTtsFromKana(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesizerTts(const Napi::CallbackInfo &info);
  Napi::Value voicevoxErrorResultToMessage(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictNew(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictLoad(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictAddWord(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictUpdateWord(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictRemoveWord(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictToJson(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictImport(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictSave(const Napi::CallbackInfo &info);
  Napi::Value voicevoxUserDictDelete(const Napi::CallbackInfo &info);
  Napi::Value voicevoxInitialize(const Napi::CallbackInfo &info);
  Napi::Value voicevoxLoadModel(const Napi::CallbackInfo &info);
  Napi::Value voicevoxIsGpuMode(const Napi::CallbackInfo &info);
  Napi::Value voicevoxIsModelLoaded(const Napi::CallbackInfo &info);
  Napi::Value voicevoxFinalize(const Napi::CallbackInfo &info);
  Napi::Value voicevoxGetMetasJson(const Napi::CallbackInfo &info);
  Napi::Value voicevoxGetSupportedDevicesJson(const Napi::CallbackInfo &info);
  Napi::Value voicevoxPredictDuration(const Napi::CallbackInfo &info);
  Napi::Value voicevoxPredictIntonation(const Napi::CallbackInfo &info);
  Napi::Value voicevoxDecode(const Napi::CallbackInfo &info);
  Napi::Value voicevoxAudioQuery(const Napi::CallbackInfo &info);
  Napi::Value voicevoxAccentPhrases(const Napi::CallbackInfo &info);
  Napi::Value voicevoxMoraLength(const Napi::CallbackInfo &info);
  Napi::Value voicevoxMoraPitch(const Napi::CallbackInfo &info);
  Napi::Value voicevoxMoraData(const Napi::CallbackInfo &info);
  Napi::Value voicevoxSynthesis(const Napi::CallbackInfo &info);
  Napi::Value voicevoxTts(const Napi::CallbackInfo &info);
  Napi::Value initialize(const Napi::CallbackInfo &info);
  Napi::Value loadModel(const Napi::CallbackInfo &info);
  Napi::Value isModelLoaded(const Napi::CallbackInfo &info);
  Napi::Value finalize(const Napi::CallbackInfo &info);
  Napi::Value metas(const Napi::CallbackInfo &info);
  Napi::Value supportedDevices(const Napi::CallbackInfo &info);
  Napi::Value yukarinSForward(const Napi::CallbackInfo &info);
  Napi::Value yukarinSaForward(const Napi::CallbackInfo &info);
  Napi::Value decodeForward(const Napi::CallbackInfo &info);
  Napi::Value lastErrorMessage(const Napi::CallbackInfo &info);
  Napi::Value voicevoxLoadOpenjtalkDict(const Napi::CallbackInfo &info);
  Napi::Value voicevoxTtsV12(const Napi::CallbackInfo &info);
  Napi::Value voicevoxTtsFromKana(const Napi::CallbackInfo &info);
  Napi::Value initializeV10(const Napi::CallbackInfo &info);
  Napi::Value initializeV5(const Napi::CallbackInfo &info);
  Napi::Value yukarinSForwardV5(const Napi::CallbackInfo &info);
  Napi::Value yukarinSaForwardV5(const Napi::CallbackInfo &info);
  Napi::Value decodeForwardV5(const Napi::CallbackInfo &info);

private:
  DLL dll;
  std::unordered_map<uint32_t, uintptr_t> open_jtalk_pointers;
  std::unordered_map<uint32_t, uintptr_t> user_dict_pointers;
  std::unordered_map<uint32_t, uintptr_t> model_pointers;
  std::unordered_map<uint32_t, uintptr_t> synthesizer_pointers;
};

#endif