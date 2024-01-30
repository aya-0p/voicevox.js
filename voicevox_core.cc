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
    Napi::Error::Fatal(func_name, "not found, did you load voicevox_core?");
  return reinterpret_cast<T>(fn);
}
#endif

const char *voicevox_get_version_v0_14(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "voicevox_get_version")();
}

struct VoicevoxSynthesisOptions voicevox_make_default_synthesis_options_v0_14(DLL &dll)
{
  return load_func<VoicevoxSynthesisOptions (*)(void)>(dll, "voicevox_make_default_synthesis_options")();
}

void voicevox_wav_free_v0_12(DLL &dll,
                             uint8_t *wav)
{
  return load_func<void (*)(uint8_t *)>(dll, "voicevox_json_free")(wav);
}

const char *voicevox_error_result_to_message_v0_12(DLL &dll,
                                                   VoicevoxResultCode result_code)
{
  return load_func<const char *(*)(VoicevoxResultCode)>(dll, "voicevox_error_result_to_message")(result_code);
}

VoicevoxResultCode voicevox_initialize_v0_14(DLL &dll,
                                             struct VoicevoxInitializeOptionsV0_14 options)
{
  return load_func<VoicevoxResultCode (*)(struct VoicevoxInitializeOptionsV0_14)>(dll, "voicevox_initialize")(options);
}

VoicevoxResultCode voicevox_load_model_v0_14(DLL &dll,
                                             uint32_t speaker_id)
{
  return load_func<VoicevoxResultCode (*)(uint32_t)>(dll, "voicevox_load_model")(speaker_id);
}

bool voicevox_is_gpu_mode_v0_14(DLL &dll)
{
  return load_func<bool (*)(void)>(dll, "voicevox_is_gpu_mode")();
}

bool voicevox_is_model_loaded_v0_14(DLL &dll,
                                    uint32_t speaker_id)
{
  return load_func<bool (*)(uint32_t)>(dll, "voicevox_is_model_loaded")(speaker_id);
}

void voicevox_finalize_v0_14(DLL &dll)
{
  return load_func<void (*)(void)>(dll, "voicevox_finalize")();
}

const char *voicevox_get_metas_json_v0_14(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "voicevox_get_metas_json")();
}

const char *voicevox_get_supported_devices_json_v0_14(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "voicevox_get_supported_devices_json")();
}

VoicevoxResultCode voicevox_predict_duration_v0_14(DLL &dll,
                                                   uintptr_t length,
                                                   int64_t *phoneme_vector,
                                                   uint32_t speaker_id,
                                                   uintptr_t *output_predict_duration_data_length,
                                                   float **output_predict_duration_data)
{
  return load_func<VoicevoxResultCode (*)(uintptr_t, int64_t *, uint32_t, uintptr_t *, float **)>(dll, "voicevox_predict_duration")(length, phoneme_vector, speaker_id, output_predict_duration_data_length, output_predict_duration_data);
}

void voicevox_predict_duration_data_free_v0_14(DLL &dll,
                                               float *predict_duration_data)
{
  return load_func<void (*)(float *)>(dll, "voicevox_predict_duration_data_free")(predict_duration_data);
}

VoicevoxResultCode voicevox_predict_intonation_v0_14(DLL &dll,
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

void voicevox_predict_intonation_data_free_v0_14(DLL &dll,
                                                 float *predict_intonation_data)
{
  return load_func<void (*)(float *)>(dll, "voicevox_predict_intonation_data_free")(predict_intonation_data);
}

VoicevoxResultCode voicevox_decode_v0_14(DLL &dll,
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

void voicevox_decode_data_free_v0_14(DLL &dll,
                                     float *decode_data)
{
  return load_func<void (*)(float *)>(dll, "voicevox_decode_data_free")(decode_data);
}

struct VoicevoxAudioQueryOptions voicevox_make_default_audio_query_options_v0_14(DLL &dll)
{
  return load_func<VoicevoxAudioQueryOptions (*)(void)>(dll, "voicevox_make_default_audio_query_options")();
}

VoicevoxResultCode voicevox_audio_query_v0_14(DLL &dll,
                                              const char *text,
                                              uint32_t speaker_id,
                                              struct VoicevoxAudioQueryOptions options,
                                              char **output_audio_query_json)
{
  return load_func<VoicevoxResultCode (*)(const char *, uint32_t, struct VoicevoxAudioQueryOptions, char **)>(dll, "voicevox_audio_query")(text, speaker_id, options, output_audio_query_json);
}

VoicevoxResultCode voicevox_synthesis_v0_14(DLL &dll,
                                            const char *audio_query_json,
                                            uint32_t speaker_id,
                                            struct VoicevoxSynthesisOptions options,
                                            uintptr_t *output_wav_length,
                                            uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const char *, uint32_t, struct VoicevoxSynthesisOptions, uintptr_t *, uint8_t **)>(dll, "voicevox_synthesis")(audio_query_json, speaker_id, options, output_wav_length, output_wav);
}

VoicevoxResultCode voicevox_tts_v0_14(DLL &dll,
                                      const char *text,
                                      uint32_t speaker_id,
                                      struct VoicevoxTtsOptionsV0_14 options,
                                      uintptr_t *output_wav_length,
                                      uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const char *, uint32_t, struct VoicevoxTtsOptionsV0_14, uintptr_t *, uint8_t **)>(dll, "voicevox_tts")(text, speaker_id, options, output_wav_length, output_wav);
}

void voicevox_audio_query_json_free_v0_14(DLL &dll,
                                          char *audio_query_json)
{
  return load_func<void (*)(char *)>(dll, "voicevox_audio_query_json_free")(audio_query_json);
}

struct VoicevoxInitializeOptionsV0_14 voicevox_make_default_initialize_options_v0_14(DLL &dll)
{
  return load_func<VoicevoxInitializeOptionsV0_14 (*)(void)>(dll, "voicevox_make_default_initialize_options")();
}

struct VoicevoxTtsOptionsV0_14 voicevox_make_default_tts_options_v0_14(DLL &dll)
{
  return load_func<VoicevoxTtsOptionsV0_14 (*)(void)>(dll, "voicevox_make_default_tts_options")();
}

bool initialize_v0_12(DLL &dll,
                      bool use_gpu,
                      int cpu_num_threads,
                      bool load_all_models)
{
  return load_func<bool (*)(bool, int, bool)>(dll, "initialize")(use_gpu, cpu_num_threads, load_all_models);
}

bool load_model_v0_12(DLL &dll,
                      int64_t speaker_id)
{
  return load_func<bool (*)(int64_t)>(dll, "load_model")(speaker_id);
}

bool is_model_loaded_v0_12(DLL &dll,
                           int64_t speaker_id)
{
  return load_func<bool (*)(int64_t)>(dll, "is_model_loaded")(speaker_id);
}

void finalize_v0_10(DLL &dll)
{
  return load_func<void (*)(void)>(dll, "finalize")();
}

const char *metas_v0_5(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "metas")();
}

const char *supported_devices_v0_10(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "supported_devices")();
}

bool yukarin_s_forward_v0_8(DLL &dll,
                            int64_t length,
                            int64_t *phoneme_list,
                            int64_t *speaker_id,
                            float *output)
{
  return load_func<bool (*)(int64_t, int64_t *, int64_t *, float *)>(dll, "yukarin_s_forward")(length, phoneme_list, speaker_id, output);
}

bool yukarin_sa_forward_v0_8(DLL &dll,
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
  return load_func<bool (*)(int64_t, int64_t *, int64_t *, int64_t *, int64_t *, int64_t *, int64_t *, int64_t *, float *)>(dll, "yukarin_sa_forward")(length, vowel_phoneme_list, consonant_phoneme_list, start_accent_list, end_accent_list, start_accent_phrase_list, end_accent_phrase_list, speaker_id, output);
}

bool decode_forward_v0_8(DLL &dll,
                         int64_t length,
                         int64_t phoneme_size,
                         float *f0,
                         float *phoneme,
                         int64_t *speaker_id,
                         float *output)
{
  return load_func<bool (*)(int64_t, int64_t, float *, float *, int64_t *, float *)>(dll, "decode_forward")(length, phoneme_size, f0, phoneme, speaker_id, output);
}

const char *last_error_message_v0_5(DLL &dll)
{
  return load_func<const char *(*)(void)>(dll, "last_error_message")();
}

VoicevoxResultCode voicevox_load_openjtalk_dict_v0_12(DLL &dll,
                                                      const char *dict_path)
{
  return load_func<VoicevoxResultCode (*)(const char *)>(dll, "voicevox_load_openjtalk_dict")(dict_path);
}

VoicevoxResultCode voicevox_tts_v0_12(DLL &dll,
                                      const char *text,
                                      int64_t speaker_id,
                                      int *output_binary_size,
                                      uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const char *, int64_t, int *, uint8_t **)>(dll, "voicevox_tts")(text, speaker_id, output_binary_size, output_wav);
}

VoicevoxResultCode voicevox_tts_from_kana_v0_12(DLL &dll,
                                                const char *text,
                                                int64_t speaker_id,
                                                int *output_binary_size,
                                                uint8_t **output_wav)
{
  return load_func<VoicevoxResultCode (*)(const char *, int64_t, int *, uint8_t **)>(dll, "voicevox_tts_from_kana")(text, speaker_id, output_binary_size, output_wav);
}

bool initialize_v0_10(DLL &dll,
                      const char *root_dir_path,
                      bool use_gpu,
                      int cpu_num_threads)
{
  return load_func<bool (*)(const char *, bool, int)>(dll, "initialize")(root_dir_path, use_gpu, cpu_num_threads);
}

bool initialize_v0_5(DLL &dll,
                     const char *root_dir_path,
                     bool use_gpu)
{
  return load_func<bool (*)(const char *, bool)>(dll, "initialize")(root_dir_path, use_gpu);
}

bool yukarin_s_forward_v0_5(DLL &dll,
                            int length,
                            long *phoneme_list,
                            long *speaker_id,
                            float *output)
{
  return load_func<bool (*)(int, long *, long *, float *)>(dll, "yukarin_s_forward")(length, phoneme_list, speaker_id, output);
}

bool yukarin_sa_forward_v0_5(DLL &dll,
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
  return load_func<bool (*)(int, long *, long *, long *, long *, long *, long *, long *, float *)>(dll, "yukarin_sa_forward")(length, vowel_phoneme_list, consonant_phoneme_list, start_accent_list, end_accent_list, start_accent_phrase_list, end_accent_phrase_list, speaker_id, output);
}

bool decode_forward_v0_5(DLL &dll,
                         int length,
                         int phoneme_size,
                         float *f0,
                         float *phoneme,
                         long *speaker_id,
                         float *output)
{
  return load_func<bool (*)(int, int, float *, float *, long *, float *)>(dll, "decode_forward")(length, phoneme_size, f0, phoneme, speaker_id, output);
}
