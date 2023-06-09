#include <napi.h>
#include <string>
#include <dlfcn.h>
#include <iostream>


typedef struct 
{
  int32_t acceleration_mode = 0;
  uint16_t cpu_num_threads = 0;
  bool load_all_models = true;
  const char *open_jtalk_dict_dir = "";
} VoicevoxInitializeOptions;

struct VoicevoxAudioQueryOptions
{
  bool kana = false;
};
struct VoicevoxSynthesisOptions
{
  bool enable_interrogative_upspeak = true;
};
void *voicevox_core = nullptr;
std::string load_string(const Napi::CallbackInfo &info, size_t index)
{
  return info[index].As<Napi::String>().Utf8Value() + "\0";
}
int32_t load_int32_t(const Napi::CallbackInfo &info, size_t index)
{
  return info[index].As<Napi::Number>().Int32Value();
}
uint32_t load_uint32_t(const Napi::CallbackInfo &info, size_t index)
{
  return info[index].As<Napi::Number>().Uint32Value();
}
bool load_bool(const Napi::CallbackInfo &info, size_t index)
{
  return info[index].As<Napi::Boolean>().Value();
}
template <typename T>
T load_func(const char *func_name, std::string &reason, bool &error)
{
  if (voicevox_core == NULL)
  {
    reason = std::string("voicevox_core not loaded.");
    error = true;
  }
  T func = reinterpret_cast<T>(NULL);
  if (!error)
    func = reinterpret_cast<T>(dlsym(voicevox_core, func_name));
  if (func == NULL)
  {
    reason = std::string("function \"") + std::string(func_name) + std::string("\" not found.");
    error = true;
  }
  return func;
}

std::string voicevox_core_error_result_to_message(int32_t &result)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<const char *(*)(int32_t)>("voicevox_error_result_to_message", reason, error);
  if (error)
  {
    return reason;
  }
  return std::string(func(result));
};

std::string voicevox_core_initialize(VoicevoxInitializeOptions &options)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<int32_t (*)(VoicevoxInitializeOptions)>("voicevox_initialize", reason, error);
  if (error)
  {
    return reason;
  }
  int32_t result = func(options);
  if (result != 0)
  {
    return voicevox_core_error_result_to_message(result);
  }
  return std::string("");
};

std::string voicevox_core_get_version(std::string &version)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<const char *(*)(void)>("voicevox_get_version", reason, error);
  if (error)
  {
    return reason;
  }
  version = std::string(func());
  return std::string("");
};

std::string voicevox_core_load_model(uint32_t &speaker_id)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<int32_t (*)(uint32_t)>("voicevox_load_model", reason, error);
  if (error)
  {
    return reason;
  }
  int32_t result = func(speaker_id);
  if (result != 0)
  {
    return voicevox_core_error_result_to_message(result);
  }
  return std::string("");
};

std::string voicevox_core_is_gpu_mode(bool &is_gpu_mode)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<bool (*)(void)>("voicevox_is_gpu_mode", reason, error);
  if (error)
  {
    return reason;
  }
  is_gpu_mode = func();
  return std::string("");
};

std::string voicevox_core_is_model_loaded(uint32_t &speaker_id, bool &is_model_loaded)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<bool (*)(uint32_t)>("voicevox_is_model_loaded", reason, error);
  if (error)
  {
    return reason;
  }
  is_model_loaded = func(speaker_id);
  return std::string("");
};

std::string voicevox_core_finalize()
{
  std::string reason("");
  bool error = false;
  auto func = load_func<void (*)(void)>("voicevox_finalize", reason, error);
  if (error)
  {
    return reason;
  }
  func();
  return std::string("");
};

std::string voicevox_core_get_metas_json(std::string &metas_json)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<const char *(*)(void)>("voicevox_get_metas_json", reason, error);
  if (error)
  {
    return reason;
  }
  metas_json = std::string(func());
  return std::string("");
};

std::string voicevox_core_get_supported_devices_json(std::string &supported_devices_json)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<const char *(*)(void)>("voicevox_get_supported_devices_json", reason, error);
  if (error)
  {
    return reason;
  }
  supported_devices_json = std::string(func());
  return std::string("");
};

std::string voicevox_core_audio_query(const char *text, uint32_t &speaker_id, struct VoicevoxAudioQueryOptions &options, char **output_audio_query_json)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<int32_t (*)(const char *, uint32_t, struct VoicevoxAudioQueryOptions, char **)>("voicevox_audio_query", reason, error);
  if (error)
  {
    return reason;
  }
  int32_t result = func(text, speaker_id, options, output_audio_query_json);
  if (result != 0)
  {
    return voicevox_core_error_result_to_message(result);
  }
  return std::string("");
};

std::string voicevox_core_synthesis(const char *audio_query_json, uint32_t &speaker_id, struct VoicevoxSynthesisOptions &options, uintptr_t *output_wav_length, uint8_t **output_wav)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<int32_t (*)(const char *, uint32_t, struct VoicevoxSynthesisOptions, uintptr_t *, uint8_t **)>("voicevox_synthesis", reason, error);
  if (error)
  {
    return reason;
  }
  int32_t result = func(audio_query_json, speaker_id, options, output_wav_length, output_wav);
  if (result != 0)
  {
    return voicevox_core_error_result_to_message(result);
  }
  return std::string("");
};

std::string voicevox_core_audio_query_json_free(char *audio_query_json)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<void (*)(char *)>("voicevox_audio_query_json_free", reason, error);
  if (error)
  {
    return reason;
  }
  func(audio_query_json);
  return std::string("");
};

std::string voicevox_core_wav_free(uint8_t *wav)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<void (*)(uint8_t *)>("voicevox_wav_free", reason, error);
  if (error)
  {
    return reason;
  }
  func(wav);
  return std::string("");
};

VoicevoxInitializeOptions voicevox_core_make_default_initialize_options()
{
  std::string reason("");
  bool error = false;
  auto func = load_func<VoicevoxInitializeOptions (*)(void)>("voicevox_make_default_initialize_options", reason, error);
  return func();
}

VoicevoxAudioQueryOptions voicevox_core_make_default_audio_query_options()
{
  std::string reason("");
  bool error = false;
  auto func = load_func<VoicevoxAudioQueryOptions (*)(void)>("voicevox_make_default_audio_query_options", reason, error);
  return func();
}

VoicevoxSynthesisOptions voicevox_core_make_default_synthesis_options()
{
  std::string reason("");
  bool error = false;
  auto func = load_func<VoicevoxSynthesisOptions (*)(void)>("voicevox_make_default_synthesis_options", reason, error);
  return func();
}

Napi::Object initialize(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string dl_path = load_string(info, 0);
  voicevox_core = dlopen(dl_path.c_str(), RTLD_NOW);
  if (voicevox_core == NULL)
  {
    obj.Set("error", dlerror());
  }
  else
  {
    obj.Set("error", "");
  }
  return obj;
}

Napi::Object finalize(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  int result = dlclose(voicevox_core);
  obj.Set("result", "");
  if (result != 0)
  {
    obj.Set("error", dlerror());
  }
  else
  {
    obj.Set("error", "");
  }
  return obj;
}

Napi::Object voicevox_initialize(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string text = load_string(info, 3);
  char* cstr = new char[text.size() + 1];
  std::char_traits<char>::copy(cstr, text.c_str(), text.size() + 1);
  VoicevoxInitializeOptions options = {
    load_int32_t(info, 0),
    static_cast<uint16_t>(load_uint32_t(info, 1)),
    load_bool(info, 2),
    const_cast<const char *>(cstr)
  };
  std::cout << options.open_jtalk_dict_dir << std::endl;
  std::string error = voicevox_core_initialize(options);
  obj.Set("error", error);
  return obj;
};
Napi::Object voicevox_get_version(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string version("");
  std::string error = voicevox_core_get_version(version);
  obj.Set("error", error);
  obj.Set("result", version);
  return obj;
};

Napi::Object voicevox_load_model(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  uint32_t speaker_id = load_uint32_t(info, 0);
  std::string error = voicevox_core_load_model(speaker_id);
  obj.Set("error", error);
  return obj;
};

Napi::Object voicevox_is_gpu_mode(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  bool is_gpu_mode = false;
  std::string error = voicevox_core_is_gpu_mode(is_gpu_mode);
  obj.Set("error", error);
  obj.Set("result", is_gpu_mode);
  return obj;
};

Napi::Object voicevox_is_model_loaded(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  uint32_t speaker_id = load_uint32_t(info, 0);
  bool is_model_loaded = false;
  std::string error = voicevox_core_is_model_loaded(speaker_id, is_model_loaded);
  obj.Set("error", error);
  obj.Set("result", is_model_loaded);
  return obj;
};

Napi::Object voicevox_finalize(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string error = voicevox_core_finalize();
  obj.Set("error", error);
  return obj;
};

Napi::Object voicevox_get_metas_json(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string metas_json("");
  std::string error = voicevox_core_get_metas_json(metas_json);
  obj.Set("error", error);
  obj.Set("result", metas_json);
  return obj;
};

Napi::Object voicevox_get_supported_devices_json(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string supported_devices("");
  std::string error = voicevox_core_get_supported_devices_json(supported_devices);
  obj.Set("error", error);
  obj.Set("result", supported_devices);
  return obj;
};

Napi::Object voicevox_audio_query(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string text = load_string(info, 0);
  uint32_t speaker_id = load_uint32_t(info, 1);
  char *output_audio_query_json = nullptr;
  VoicevoxAudioQueryOptions options = {false};
  options.kana = load_bool(info, 2);
  std::string error = voicevox_core_audio_query(text.c_str(), speaker_id, options, &output_audio_query_json);
  obj.Set("error", error);
  obj.Set("result", output_audio_query_json);
  std::string error_2 = voicevox_core_audio_query_json_free(output_audio_query_json);
  obj.Set("error_2", error_2);
  return obj;
};

Napi::Object voicevox_synthesis(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string audio_query_json = load_string(info, 0);
  uint32_t speaker_id = load_uint32_t(info, 1);
  size_t output_wav_length = 0;
  uint8_t *output_wav = nullptr;
  VoicevoxSynthesisOptions options = {false};
  options.enable_interrogative_upspeak = load_bool(info, 2);
  std::string error = voicevox_core_synthesis(audio_query_json.c_str(), speaker_id, options, &output_wav_length, &output_wav);
  obj.Set("error", error);
  obj.Set("result", Napi::Buffer<uint8_t>::New(env, output_wav, output_wav_length));
  std::string error_2 = voicevox_core_wav_free(output_wav);
  obj.Set("error_2", error_2);
  return obj;
};

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("initialize", Napi::Function::New(env, initialize));
  exports.Set("finalize", Napi::Function::New(env, finalize));

  exports.Set("voicevoxInitialize", Napi::Function::New(env, voicevox_initialize));
  exports.Set("voicevoxGetVersion", Napi::Function::New(env, voicevox_get_version));
  exports.Set("voicevoxLoadModel", Napi::Function::New(env, voicevox_load_model));
  exports.Set("voicevoxIsGpuMode", Napi::Function::New(env, voicevox_is_gpu_mode));
  exports.Set("voicevoxIsModelLoaded", Napi::Function::New(env, voicevox_is_model_loaded));
  exports.Set("voicevoxFinalize", Napi::Function::New(env, voicevox_finalize));
  exports.Set("voicevoxGetMetasJson", Napi::Function::New(env, voicevox_get_metas_json));
  exports.Set("voicevoxGetSupportedDevicesJson", Napi::Function::New(env, voicevox_get_supported_devices_json));
  exports.Set("voicevoxAudioQuery", Napi::Function::New(env, voicevox_audio_query));
  exports.Set("voicevoxSynthesis", Napi::Function::New(env, voicevox_synthesis));
  return exports;
}

NODE_API_MODULE(voicevox, Init);