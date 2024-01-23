#include "voicevox_core.h"
#include <cstddef>
#include <iostream>
#include "napi.h"
#ifdef _WIN32
#include <windows.h>
#define DLL HMODULE
DLL dll_load(const char *path)
{
  return LoadLibraryA(path);
}

void dll_free(DLL &dll)
{
  FreeLibrary(dll);
  return;
}

template <typename T>
T load_func(DLL &dll, const char *func_name)
{
  if (dll == NULL)
  {
    std::cout << "dll_not_found" << std::endl;
    throw "dll_not_loaded";
  }
  void *fn = GetProcAddress(dll, func_name);
  if (fn == NULL)
  {
    std::cout << "fn_not_found" << std::endl;
    throw "fn_not_found";
  }
  return reinterpret_cast<T>(fn);
}
#else
#include <dlfcn.h>
#define DLL void *
DLL dll_load(const char *path)
{
  DLL dll = dlopen(path, RTLD_NOW);
  if (dll == NULL)
    Napi::Error::Fatal(path, "is not dll");
  return dll;
}

void dll_free(DLL &dll)
{
  dlclose(dll);
  return;
}

template <typename T>
T load_func(DLL &dll, const char *func_name)
{
  if (dll == NULL)
    Napi::Error::Fatal("", "dll not loaded");
  void *fn = dlsym(dll, func_name);
  if (fn == NULL)
    Napi::Error::Fatal(func_name, "not found, Did you load voicevox_core?");
  return reinterpret_cast<T>(fn);
}
#endif

VoicevoxResultCode voicevox_open_jtalk_rc_new(DLL &dll,
                                              const char *open_jtalk_dic_dir,
                                              struct OpenJtalkRc **out_open_jtalk)
{
  return load_func<VoicevoxResultCode (*)(const char *, struct OpenJtalkRc **)>(dll, "voicevox_open_jtalk_rc_new")(open_jtalk_dic_dir, out_open_jtalk);
}

VoicevoxResultCode voicevox_open_jtalk_rc_use_user_dict(DLL &dll,
                                                        const struct OpenJtalkRc *open_jtalk,
                                                        const struct VoicevoxUserDict *user_dict)
{
  return load_func<VoicevoxResultCode (*)(const struct OpenJtalkRc *, const struct VoicevoxUserDict *)>(dll, "voicevox_open_jtalk_rc_use_user_dict")(open_jtalk, user_dict);
}

void voicevox_open_jtalk_rc_delete(DLL &dll,
                                   struct OpenJtalkRc *open_jtalk)
{
  return load_func<void (*)(struct OpenJtalkRc *)>(dll, "voicevox_open_jtalk_rc_delete")(open_jtalk);
}

struct VoicevoxInitializeOptions voicevox_make_default_initialize_options(DLL &dll)
{
  return load_func<VoicevoxInitializeOptions (*)(void)>(dll, "voicevox_make_default_initialize_options")();
}

const char *voicevox_get_version(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "voicevox_get_version")();
}

VoicevoxResultCode voicevox_voice_model_new_from_path(DLL &dll,
                                                      const char *path,
                                                      struct VoicevoxVoiceModel **out_model)
{
  return load_func<VoicevoxResultCode (*)(const char *, struct VoicevoxVoiceModel **)>(dll, "voicevox_voice_model_new_from_path")(path, out_model);
}

VoicevoxVoiceModelId voicevox_voice_model_id(DLL &dll,
                                             const struct VoicevoxVoiceModel *model)
{
  return load_func<VoicevoxVoiceModelId (*)(const struct VoicevoxVoiceModel *)>(dll, "voicevox_voice_model_id")(model);
}

const char *voicevox_voice_model_get_metas_json(DLL &dll,
                                                const struct VoicevoxVoiceModel *model)
{
  return load_func<const char *(*)(const struct VoicevoxVoiceModel *)>(dll, "voicevox_voice_model_get_metas_json")(model);
}

void voicevox_voice_model_delete(DLL &dll,
                                 struct VoicevoxVoiceModel *model)
{
  return load_func<void (*)(struct VoicevoxVoiceModel *)>(dll, "voicevox_voice_model_delete")(model);
}

VoicevoxResultCode voicevox_synthesizer_new(DLL &dll,
                                            const struct OpenJtalkRc *open_jtalk,
                                            struct VoicevoxInitializeOptions options,
                                            struct VoicevoxSynthesizer **out_synthesizer)
{
  return load_func<VoicevoxResultCode (*)(const struct OpenJtalkRc *, struct VoicevoxInitializeOptions, struct VoicevoxSynthesizer **)>(dll, "voicevox_synthesizer_new")(open_jtalk, options, out_synthesizer);
}

void voicevox_synthesizer_delete(DLL &dll,
                                 struct VoicevoxSynthesizer *synthesizer)
{
  return load_func<void (*)(struct VoicevoxSynthesizer *)>(dll, "voicevox_synthesizer_delete")(synthesizer);
}

VoicevoxResultCode voicevox_synthesizer_load_voice_model(DLL &dll,
                                                         const struct VoicevoxSynthesizer *synthesizer,
                                                         const struct VoicevoxVoiceModel *model)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const struct VoicevoxVoiceModel *)>(dll, "voicevox_synthesizer_load_voice_model")(synthesizer, model);
}

VoicevoxResultCode voicevox_synthesizer_unload_voice_model(DLL &dll,
                                                           const struct VoicevoxSynthesizer *synthesizer,
                                                           VoicevoxVoiceModelId model_id)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, VoicevoxVoiceModelId)>(dll, "voicevox_synthesizer_unload_voice_model")(synthesizer, model_id);
}
bool voicevox_synthesizer_is_gpu_mode(DLL &dll,
                                      const struct VoicevoxSynthesizer *synthesizer)
{
  return load_func<bool (*)(const struct VoicevoxSynthesizer *)>(dll, "voicevox_synthesizer_is_gpu_mode")(synthesizer);
}

bool voicevox_synthesizer_is_loaded_voice_model(DLL &dll,
                                                const struct VoicevoxSynthesizer *synthesizer,
                                                VoicevoxVoiceModelId model_id)
{
  return load_func<bool (*)(const struct VoicevoxSynthesizer *, VoicevoxVoiceModelId)>(dll, "voicevox_synthesizer_is_loaded_voice_model")(synthesizer, model_id);
}

char *voicevox_synthesizer_create_metas_json(DLL &dll,
                                             const struct VoicevoxSynthesizer *synthesizer)
{
  return load_func<char *(*)(const struct VoicevoxSynthesizer *)>(dll, "voicevox_synthesizer_create_metas_json")(synthesizer);
}

VoicevoxResultCode voicevox_create_supported_devices_json(DLL &dll,
                                                          char **output_supported_devices_json)
{
  return load_func<VoicevoxResultCode (*)(char **)>(dll, "voicevox_create_supported_devices_json")(output_supported_devices_json);
}

VoicevoxResultCode voicevox_synthesizer_create_audio_query_from_kana(DLL &dll,
                                                                     const struct VoicevoxSynthesizer *synthesizer,
                                                                     const char *kana,
                                                                     VoicevoxStyleId style_id,
                                                                     char **output_audio_query_json)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, char **)>(dll, "voicevox_synthesizer_create_audio_query_from_kana")(synthesizer, kana, style_id, output_audio_query_json);
}

VoicevoxResultCode voicevox_synthesizer_create_audio_query(DLL &dll,
                                                           const struct VoicevoxSynthesizer *synthesizer,
                                                           const char *text,
                                                           VoicevoxStyleId style_id,
                                                           char **output_audio_query_json)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, char **)>(dll, "voicevox_synthesizer_create_audio_query")(synthesizer, text, style_id, output_audio_query_json);
}

VoicevoxResultCode voicevox_synthesizer_create_accent_phrases_from_kana(DLL &dll,
                                                                        const struct VoicevoxSynthesizer *synthesizer,
                                                                        const char *kana,
                                                                        VoicevoxStyleId style_id,
                                                                        char **output_accent_phrases_json)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, char **)>(dll, "voicevox_synthesizer_create_accent_phrases_from_kana")(synthesizer, kana, style_id, output_accent_phrases_json);
}

VoicevoxResultCode voicevox_synthesizer_create_accent_phrases(DLL &dll,
                                                              const struct VoicevoxSynthesizer *synthesizer,
                                                              const char *text,
                                                              VoicevoxStyleId style_id,
                                                              char **output_accent_phrases_json)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, char **)>(dll, "voicevox_synthesizer_create_accent_phrases")(synthesizer, text, style_id, output_accent_phrases_json);
}

VoicevoxResultCode voicevox_synthesizer_replace_mora_data(DLL &dll,
                                                          const struct VoicevoxSynthesizer *synthesizer,
                                                          const char *accent_phrases_json,
                                                          VoicevoxStyleId style_id,
                                                          char **output_accent_phrases_json)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, char **)>(dll, "voicevox_synthesizer_replace_mora_data")(synthesizer, accent_phrases_json, style_id, output_accent_phrases_json);
}

VoicevoxResultCode voicevox_synthesizer_replace_phoneme_length(DLL &dll,
                                                               const struct VoicevoxSynthesizer *synthesizer,
                                                               const char *accent_phrases_json,
                                                               VoicevoxStyleId style_id,
                                                               char **output_accent_phrases_json)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, char **)>(dll, "voicevox_synthesizer_replace_phoneme_length")(synthesizer, accent_phrases_json, style_id, output_accent_phrases_json);
}

VoicevoxResultCode voicevox_synthesizer_replace_mora_pitch(DLL &dll,
                                                           const struct VoicevoxSynthesizer *synthesizer,
                                                           const char *accent_phrases_json,
                                                           VoicevoxStyleId style_id,
                                                           char **output_accent_phrases_json)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, char **)>(dll, "voicevox_synthesizer_replace_mora_pitch")(synthesizer, accent_phrases_json, style_id, output_accent_phrases_json);
}

struct VoicevoxSynthesisOptions voicevox_make_default_synthesis_options(DLL &dll)
{
  return load_func<VoicevoxSynthesisOptions (*)(void)>(dll, "voicevox_make_default_synthesis_options")();
}

VoicevoxResultCode voicevox_synthesizer_synthesis(DLL &dll,
                                                  const struct VoicevoxSynthesizer *synthesizer,
                                                  const char *audio_query_json,
                                                  VoicevoxStyleId style_id,
                                                  struct VoicevoxSynthesisOptions options,
                                                  uintptr_t *output_wav_length,
                                                  uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, struct VoicevoxSynthesisOptions, uintptr_t *, uint8_t **)>(dll, "voicevox_synthesizer_synthesis")(synthesizer, audio_query_json, style_id, options, output_wav_length, output_wav);
}

struct VoicevoxTtsOptions voicevox_make_default_tts_options(DLL &dll)
{
  return load_func<VoicevoxTtsOptions (*)(void)>(dll, "voicevox_make_default_tts_options")();
}

VoicevoxResultCode voicevox_synthesizer_tts_from_kana(DLL &dll,
                                                      const struct VoicevoxSynthesizer *synthesizer,
                                                      const char *kana,
                                                      VoicevoxStyleId style_id,
                                                      struct VoicevoxTtsOptions options,
                                                      uintptr_t *output_wav_length,
                                                      uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, struct VoicevoxTtsOptions, uintptr_t *, uint8_t **)>(dll, "voicevox_synthesizer_tts_from_kana")(synthesizer, kana, style_id, options, output_wav_length, output_wav);
}

VoicevoxResultCode voicevox_synthesizer_tts(DLL &dll,
                                            const struct VoicevoxSynthesizer *synthesizer,
                                            const char *text,
                                            VoicevoxStyleId style_id,
                                            struct VoicevoxTtsOptions options,
                                            uintptr_t *output_wav_length,
                                            uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxSynthesizer *, const char *, VoicevoxStyleId, struct VoicevoxTtsOptions, uintptr_t *, uint8_t **)>(dll, "voicevox_synthesizer_tts")(synthesizer, text, style_id, options, output_wav_length, output_wav);
}

void voicevox_json_free(DLL &dll,
                        char *json)
{
  return load_func<void (*)(char *)>(dll, "voicevox_json_free")(json);
}

void voicevox_wav_free(DLL &dll,
                       uint8_t *wav)
{
  return load_func<void (*)(uint8_t *)>(dll, "voicevox_json_free")(wav);
}

const char *voicevox_error_result_to_message(DLL &dll,
                                             VoicevoxResultCode result_code)
{
  return load_func<const char *(*)(VoicevoxResultCode)>(dll, "voicevox_error_result_to_message")(result_code);
}

struct VoicevoxUserDictWord voicevox_user_dict_word_make(DLL &dll,
                                                         const char *surface,
                                                         const char *pronunciation)
{
  return load_func<VoicevoxUserDictWord (*)(const char *, const char *)>(dll, "voicevox_user_dict_word_make")(surface, pronunciation);
}

struct VoicevoxUserDict *voicevox_user_dict_new(DLL &dll)
{
  return load_func<struct VoicevoxUserDict *(*)(void)>(dll, "voicevox_user_dict_new")();
}

VoicevoxResultCode voicevox_user_dict_load(DLL &dll,
                                           const struct VoicevoxUserDict *user_dict,
                                           const char *dict_path)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxUserDict *, const char *)>(dll, "voicevox_user_dict_load")(user_dict, dict_path);
}

VoicevoxResultCode voicevox_user_dict_add_word(DLL &dll,
                                               const struct VoicevoxUserDict *user_dict,
                                               const struct VoicevoxUserDictWord *word,
                                               uint8_t (*output_word_uuid)[16])
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxUserDict *, const struct VoicevoxUserDictWord *, uint8_t(*)[16])>(dll, "voicevox_user_dict_add_word")(user_dict, word, output_word_uuid);
}

VoicevoxResultCode voicevox_user_dict_update_word(DLL &dll,
                                                  const struct VoicevoxUserDict *user_dict,
                                                  const uint8_t (*word_uuid)[16],
                                                  const struct VoicevoxUserDictWord *word)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxUserDict *, const uint8_t(*)[16], const struct VoicevoxUserDictWord *)>(dll, "voicevox_user_dict_update_word")(user_dict, word_uuid, word);
}

VoicevoxResultCode voicevox_user_dict_remove_word(DLL &dll,
                                                  const struct VoicevoxUserDict *user_dict,
                                                  const uint8_t (*word_uuid)[16])
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxUserDict *, const uint8_t(*)[16])>(dll, "voicevox_user_dict_remove_word")(user_dict, word_uuid);
}

VoicevoxResultCode voicevox_user_dict_to_json(DLL &dll,
                                              const struct VoicevoxUserDict *user_dict,
                                              char **output_json)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxUserDict *, char **)>(dll, "voicevox_user_dict_to_json")(user_dict, output_json);
}

VoicevoxResultCode voicevox_user_dict_import(DLL &dll,
                                             const struct VoicevoxUserDict *user_dict,
                                             const struct VoicevoxUserDict *other_dict)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxUserDict *, const struct VoicevoxUserDict *)>(dll, "voicevox_user_dict_import")(user_dict, other_dict);
}

VoicevoxResultCode voicevox_user_dict_save(DLL &dll,
                                           const struct VoicevoxUserDict *user_dict,
                                           const char *path)
{
  return load_func<VoicevoxResultCode (*)(const struct VoicevoxUserDict *, const char *)>(dll, "voicevox_user_dict_save")(user_dict, path);
}

void voicevox_user_dict_delete(DLL &dll,
                               struct VoicevoxUserDict *user_dict)
{
  return load_func<void (*)(struct VoicevoxUserDict *)>(dll, "voicevox_user_dict_delete")(user_dict);
}

VoicevoxResultCode voicevox_initialize(DLL &dll,
                                       struct VoicevoxInitializeOptionsV14 options)
{
  return load_func<VoicevoxResultCode (*)(struct VoicevoxInitializeOptionsV14)>(dll, "voicevox_initialize")(options);
}

VoicevoxResultCode voicevox_load_model(DLL &dll,
                                       uint32_t speaker_id)
{
  return load_func<VoicevoxResultCode (*)(uint32_t)>(dll, "voicevox_load_model")(speaker_id);
}

bool voicevox_is_gpu_mode(DLL &dll)
{
  return load_func<bool (*)(void)>(dll, "voicevox_is_gpu_mode")();
}

bool voicevox_is_model_loaded(DLL &dll,
                              uint32_t speaker_id)
{
  return load_func<bool (*)(uint32_t)>(dll, "voicevox_is_model_loaded")(speaker_id);
}

void voicevox_finalize(DLL &dll)
{
  return load_func<void (*)(void)>(dll, "voicevox_finalize")();
}

const char *voicevox_get_metas_json(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "voicevox_get_metas_json")();
}

const char *voicevox_get_supported_devices_json(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "voicevox_get_supported_devices_json")();
}

VoicevoxResultCode voicevox_predict_duration(DLL &dll,
                                             uintptr_t length,
                                             int64_t *phoneme_vector,
                                             uint32_t speaker_id,
                                             uintptr_t *output_predict_duration_data_length,
                                             float **output_predict_duration_data)
{
  return load_func<VoicevoxResultCode (*)(uintptr_t, int64_t *, uint32_t, uintptr_t *, float **)>(dll, "voicevox_predict_duration")(length, phoneme_vector, speaker_id, output_predict_duration_data_length, output_predict_duration_data);
}

void voicevox_predict_duration_data_free(DLL &dll,
                                         float *predict_duration_data)
{
  return load_func<void (*)(float *)>(dll, "voicevox_predict_duration_data_free")(predict_duration_data);
}

VoicevoxResultCode voicevox_predict_intonation(DLL &dll,
                                               uintptr_t length,
                                               int64_t *vowel_phoneme_vector,
                                               int64_t *consonant_phoneme_vector,
                                               int64_t *start_accent_vector,
                                               int64_t *end_accent_vector,
                                               int64_t *start_accent_phrase_vector,
                                               int64_t *end_accent_phrase_vector,
                                               uint32_t speaker_id,
                                               uintptr_t *output_predict_intonation_data_length,
                                               float **output_predict_intonation_data)
{
  return load_func<VoicevoxResultCode (*)(uintptr_t, int64_t *, int64_t *, int64_t *, int64_t *, int64_t *, int64_t *, uint32_t, uintptr_t *, float **)>(dll, "voicevox_predict_intonation")(length, vowel_phoneme_vector, consonant_phoneme_vector, start_accent_vector, end_accent_vector, start_accent_phrase_vector, end_accent_phrase_vector, speaker_id, output_predict_intonation_data_length, output_predict_intonation_data);
}

void voicevox_predict_intonation_data_free(DLL &dll,
                                           float *predict_intonation_data)
{
  return load_func<void (*)(float *)>(dll, "voicevox_predict_intonation_data_free")(predict_intonation_data);
}

VoicevoxResultCode voicevox_decode(DLL &dll,
                                   uintptr_t length,
                                   uintptr_t phoneme_size,
                                   float *f0,
                                   float *phoneme_vector,
                                   uint32_t speaker_id,
                                   uintptr_t *output_decode_data_length,
                                   float **output_decode_data)
{
  return load_func<VoicevoxResultCode (*)(uintptr_t, uintptr_t, float *, float *, uint32_t, uintptr_t *, float **)>(dll, "voicevox_decode")(length, phoneme_size, f0, phoneme_vector, speaker_id, output_decode_data_length, output_decode_data);
}

void voicevox_decode_data_free(DLL &dll,
                               float *decode_data)
{
  return load_func<void (*)(float *)>(dll, "voicevox_decode_data_free")(decode_data);
}

struct VoicevoxAudioQueryOptions voicevox_make_default_audio_query_options(DLL &dll)
{
  return load_func<VoicevoxAudioQueryOptions (*)(void)>(dll, "voicevox_make_default_audio_query_options")();
}

VoicevoxResultCode voicevox_audio_query(DLL &dll,
                                        const char *text,
                                        uint32_t speaker_id,
                                        struct VoicevoxAudioQueryOptions options,
                                        char **output_audio_query_json)
{
  return load_func<VoicevoxResultCode (*)(const char *, uint32_t, struct VoicevoxAudioQueryOptions, char **)>(dll, "voicevox_audio_query")(text, speaker_id, options, output_audio_query_json);
}

VoicevoxResultCode voicevox_synthesis(DLL &dll,
                                      const char *audio_query_json,
                                      uint32_t speaker_id,
                                      struct VoicevoxSynthesisOptions options,
                                      uintptr_t *output_wav_length,
                                      uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const char *, uint32_t, struct VoicevoxSynthesisOptions, uintptr_t *, uint8_t **)>(dll, "voicevox_synthesis")(audio_query_json, speaker_id, options, output_wav_length, output_wav);
}

VoicevoxResultCode voicevox_tts(DLL &dll,
                                const char *text,
                                uint32_t speaker_id,
                                struct VoicevoxTtsOptionsV14 options,
                                uintptr_t *output_wav_length,
                                uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const char *, uint32_t, struct VoicevoxTtsOptionsV14, uintptr_t *, uint8_t **)>(dll, "voicevox_tts")(text, speaker_id, options, output_wav_length, output_wav);
}

void voicevox_audio_query_json_free(DLL &dll,
                                    char *audio_query_json)
{
  return load_func<void (*)(char *)>(dll, "voicevox_audio_query_json_free")(audio_query_json);
}

struct VoicevoxInitializeOptionsV14 voicevox_make_default_initialize_options_v14(DLL &dll)
{
  return load_func<VoicevoxInitializeOptionsV14 (*)(void)>(dll, "voicevox_make_default_initialize_options")();
}

struct VoicevoxTtsOptionsV14 voicevox_make_default_tts_options_v14(DLL &dll)
{
  return load_func<VoicevoxTtsOptionsV14 (*)(void)>(dll, "voicevox_make_default_tts_options_v14")();
}

bool initialize_v(DLL &dll,
                bool use_gpu,
                int cpu_num_threads,
                bool load_all_models)
{
  return load_func<bool (*)(bool, int, bool)>(dll, "initialize")(use_gpu, cpu_num_threads, load_all_models);
}

bool load_model(DLL &dll,
                int64_t speaker_id)
{
  return load_func<bool (*)(int64_t)>(dll, "load_model")(speaker_id);
}

bool is_model_loaded(DLL &dll,
                     int64_t speaker_id)
{
  return load_func<bool (*)(int64_t)>(dll, "is_model_loaded")(speaker_id);
}

void finalize_v(DLL &dll)
{
  return load_func<void (*)(void)>(dll, "finalize")();
}

const char *metas_v(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "metas")();
}

const char *supported_devices(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "supported_devices")();
}

bool yukarin_s_forward(DLL &dll,
                       int64_t length,
                       int64_t *phoneme_list,
                       int64_t *speaker_id,
                       float *output)
{
  return load_func<VoicevoxResultCode (*)(int64_t, int64_t *, int64_t *, float *)>(dll, "yukarin_s_forward")(length, phoneme_list, speaker_id, output);
}

bool yukarin_sa_forward(DLL &dll,
                        int64_t length,
                        int64_t *vowel_phoneme_list,
                        int64_t *consonant_phoneme_list,
                        int64_t *start_accent_list,
                        int64_t *end_accent_list,
                        int64_t *start_accent_phrase_list,
                        int64_t *end_accent_phrase_list,
                        int64_t *speaker_id,
                        float *output)
{
  return load_func<VoicevoxResultCode (*)(int64_t, int64_t *, int64_t *, int64_t *, int64_t *, int64_t *, int64_t *, int64_t *, float *)>(dll, "yukarin_sa_forward")(length, vowel_phoneme_list, consonant_phoneme_list, start_accent_list, end_accent_list, start_accent_phrase_list, end_accent_phrase_list, speaker_id, output);
}

bool decode_forward(DLL &dll,
                    int64_t length,
                    int64_t phoneme_size,
                    float *f0,
                    float *phoneme,
                    int64_t *speaker_id,
                    float *output)
{
  return load_func<VoicevoxResultCode (*)(int64_t, int64_t, float *, float *, int64_t *, float *)>(dll, "decode_forward")(length, phoneme_size, f0, phoneme, speaker_id, output);
}

const char *last_error_message(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "last_error_message")();
}

VoicevoxResultCode voicevox_load_openjtalk_dict(DLL &dll,
                                                const char *dict_path)
{
  return load_func<VoicevoxResultCode (*)(const char *)>(dll, "voicevox_load_openjtalk_dict")(dict_path);
}

VoicevoxResultCode voicevox_tts_v13(DLL &dll,
                                    const char *text,
                                    int64_t speaker_id,
                                    int *output_binary_size,
                                    uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const char *, int64_t, int *, uint8_t **)>(dll, "voicevox_tts")(text, speaker_id, output_binary_size, output_wav);
}

VoicevoxResultCode voicevox_tts_from_kana(DLL &dll,
                                          const char *text,
                                          int64_t speaker_id,
                                          int *output_binary_size,
                                          uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const char *, int64_t, int *, uint8_t **)>(dll, "voicevox_tts_from_kana")(text, speaker_id, output_binary_size, output_wav);
}

bool initialize_v11(DLL &dll,
                    const char *root_dir_path,
                    bool use_gpu,
                    int cpu_num_threads)
{
  return load_func<bool (*)(const char *, bool, int)>(dll, "initialize")(root_dir_path, use_gpu, cpu_num_threads);
}

bool initialize_v9(DLL &dll,
                   const char *root_dir_path,
                   bool use_gpu)
{
  return load_func<bool (*)(const char *, bool)>(dll, "initialize")(root_dir_path, use_gpu);
}

bool yukarin_s_forward_v7(DLL &dll,
                          int length,
                          long *phoneme_list,
                          long *speaker_id,
                          float *output)
{
  return load_func<VoicevoxResultCode (*)(int, long *, long *, float *)>(dll, "yukarin_s_forward")(length, phoneme_list, speaker_id, output);
}

bool yukarin_sa_forward_v7(DLL &dll,
                           int length,
                           long *vowel_phoneme_list,
                           long *consonant_phoneme_list,
                           long *start_accent_list,
                           long *end_accent_list,
                           long *start_accent_phrase_list,
                           long *end_accent_phrase_list,
                           long *speaker_id,
                           float *output)
{
  return load_func<VoicevoxResultCode (*)(int, long *, long *, long *, long *, long *, long *, long *, float *)>(dll, "yukarin_sa_forward")(length, vowel_phoneme_list, consonant_phoneme_list, start_accent_list, end_accent_list, start_accent_phrase_list, end_accent_phrase_list, speaker_id, output);
}

bool decode_forward_v7(DLL &dll,
                       int length,
                       int phoneme_size,
                       float *f0,
                       float *phoneme,
                       long *speaker_id,
                       float *output)
{
  return load_func<VoicevoxResultCode (*)(int, int, float *, float *, long *, float *)>(dll, "decode_forward")(length, phoneme_size, f0, phoneme, speaker_id, output);
}
