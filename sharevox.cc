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
} SharevoxInitializeOptions;

struct SharevoxAudioQueryOptions
{
  bool kana = false;
};
struct SharevoxSynthesisOptions
{
  bool enable_interrogative_upspeak = true;
};
void *sharevox_core = nullptr;
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
  if (sharevox_core == NULL)
  {
    reason = std::string("sharevox_core not loaded.");
    error = true;
  }
  T func = reinterpret_cast<T>(NULL);
  if (!error)
    func = reinterpret_cast<T>(dlsym(sharevox_core, func_name));
  if (func == NULL)
  {
    reason = std::string("function \"") + std::string(func_name) + std::string("\" not found.");
    error = true;
  }
  return func;
}

std::string sharevox_core_error_result_to_message(int32_t &result)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<const char *(*)(int32_t)>("sharevox_error_result_to_message", reason, error);
  if (error)
  {
    return reason;
  }
  return std::string(func(result));
};

std::string sharevox_core_initialize(const char *root_dir_path, SharevoxInitializeOptions &options)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<int32_t (*)(const char *, SharevoxInitializeOptions)>("sharevox_initialize", reason, error);
  if (error)
  {
    return reason;
  }
  int32_t result = func(root_dir_path, options);
  if (result != 0)
  {
    return sharevox_core_error_result_to_message(result);
  }
  return std::string("");
};

std::string sharevox_core_get_version(std::string &version)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<const char *(*)(void)>("sharevox_get_version", reason, error);
  if (error)
  {
    return reason;
  }
  version = std::string(func());
  return std::string("");
};

std::string sharevox_core_load_model(uint32_t &speaker_id)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<int32_t (*)(uint32_t)>("sharevox_load_model", reason, error);
  if (error)
  {
    return reason;
  }
  int32_t result = func(speaker_id);
  if (result != 0)
  {
    return sharevox_core_error_result_to_message(result);
  }
  return std::string("");
};

std::string sharevox_core_is_gpu_mode(bool &is_gpu_mode)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<bool (*)(void)>("sharevox_is_gpu_mode", reason, error);
  if (error)
  {
    return reason;
  }
  is_gpu_mode = func();
  return std::string("");
};

std::string sharevox_core_is_model_loaded(uint32_t &speaker_id, bool &is_model_loaded)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<bool (*)(uint32_t)>("sharevox_is_model_loaded", reason, error);
  if (error)
  {
    return reason;
  }
  is_model_loaded = func(speaker_id);
  return std::string("");
};

std::string sharevox_core_finalize()
{
  std::string reason("");
  bool error = false;
  auto func = load_func<void (*)(void)>("sharevox_finalize", reason, error);
  if (error)
  {
    return reason;
  }
  func();
  return std::string("");
};

std::string sharevox_core_get_metas_json(std::string &metas_json)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<const char *(*)(void)>("sharevox_get_metas_json", reason, error);
  if (error)
  {
    return reason;
  }
  metas_json = std::string(func());
  return std::string("");
};

std::string sharevox_core_get_supported_devices_json(std::string &supported_devices_json)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<const char *(*)(void)>("sharevox_get_supported_devices_json", reason, error);
  if (error)
  {
    return reason;
  }
  supported_devices_json = std::string(func());
  return std::string("");
};

std::string sharevox_core_audio_query(const char *text, uint32_t &speaker_id, struct SharevoxAudioQueryOptions &options, char **output_audio_query_json)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<int32_t (*)(const char *, uint32_t, struct SharevoxAudioQueryOptions, char **)>("sharevox_audio_query", reason, error);
  if (error)
  {
    return reason;
  }
  int32_t result = func(text, speaker_id, options, output_audio_query_json);
  if (result != 0)
  {
    return sharevox_core_error_result_to_message(result);
  }
  return std::string("");
};

std::string sharevox_core_synthesis(const char *audio_query_json, uint32_t &speaker_id, struct SharevoxSynthesisOptions &options, uintptr_t *output_wav_length, uint8_t **output_wav)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<int32_t (*)(const char *, uint32_t, struct SharevoxSynthesisOptions, uintptr_t *, uint8_t **)>("sharevox_synthesis", reason, error);
  if (error)
  {
    return reason;
  }
  int32_t result = func(audio_query_json, speaker_id, options, output_wav_length, output_wav);
  if (result != 0)
  {
    return sharevox_core_error_result_to_message(result);
  }
  return std::string("");
};

std::string sharevox_core_audio_query_json_free(char *audio_query_json)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<void (*)(char *)>("sharevox_audio_query_json_free", reason, error);
  if (error)
  {
    return reason;
  }
  func(audio_query_json);
  return std::string("");
};

std::string sharevox_core_wav_free(uint8_t *wav)
{
  std::string reason("");
  bool error = false;
  auto func = load_func<void (*)(uint8_t *)>("sharevox_wav_free", reason, error);
  if (error)
  {
    return reason;
  }
  func(wav);
  return std::string("");
};

SharevoxInitializeOptions sharevox_core_make_default_initialize_options()
{
  std::string reason("");
  bool error = false;
  auto func = load_func<SharevoxInitializeOptions (*)(void)>("sharevox_make_default_initialize_options", reason, error);
  return func();
}

SharevoxAudioQueryOptions sharevox_core_make_default_audio_query_options()
{
  std::string reason("");
  bool error = false;
  auto func = load_func<SharevoxAudioQueryOptions (*)(void)>("sharevox_make_default_audio_query_options", reason, error);
  return func();
}

SharevoxSynthesisOptions sharevox_core_make_default_synthesis_options()
{
  std::string reason("");
  bool error = false;
  auto func = load_func<SharevoxSynthesisOptions (*)(void)>("sharevox_make_default_synthesis_options", reason, error);
  return func();
}

Napi::Object initialize(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string dl_path = load_string(info, 0);
  sharevox_core = dlopen(dl_path.c_str(), RTLD_NOW);
  if (sharevox_core == NULL)
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
  int result = dlclose(sharevox_core);
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

Napi::Object sharevox_initialize(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  const char *root_dir_path = load_string(info, 4).c_str();
  std::string text = load_string(info, 3);
  char* cstr = new char[text.size() + 1];
  std::char_traits<char>::copy(cstr, text.c_str(), text.size() + 1);
  SharevoxInitializeOptions options = {
    load_int32_t(info, 0),
    static_cast<uint16_t>(load_uint32_t(info, 1)),
    load_bool(info, 2),
    const_cast<const char *>(cstr)
  };
  std::string error = sharevox_core_initialize(root_dir_path, options);
  obj.Set("error", error);
  return obj;
};
Napi::Object sharevox_get_version(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string version("");
  std::string error = sharevox_core_get_version(version);
  obj.Set("error", error);
  obj.Set("result", version);
  return obj;
};

Napi::Object sharevox_load_model(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  uint32_t speaker_id = load_uint32_t(info, 0);
  std::string error = sharevox_core_load_model(speaker_id);
  obj.Set("error", error);
  return obj;
};

Napi::Object sharevox_is_gpu_mode(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  bool is_gpu_mode = false;
  std::string error = sharevox_core_is_gpu_mode(is_gpu_mode);
  obj.Set("error", error);
  obj.Set("result", is_gpu_mode);
  return obj;
};

Napi::Object sharevox_is_model_loaded(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  uint32_t speaker_id = load_uint32_t(info, 0);
  bool is_model_loaded = false;
  std::string error = sharevox_core_is_model_loaded(speaker_id, is_model_loaded);
  obj.Set("error", error);
  obj.Set("result", is_model_loaded);
  return obj;
};

Napi::Object sharevox_finalize(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string error = sharevox_core_finalize();
  obj.Set("error", error);
  return obj;
};

Napi::Object sharevox_get_metas_json(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string metas_json("");
  std::string error = sharevox_core_get_metas_json(metas_json);
  obj.Set("error", error);
  obj.Set("result", metas_json);
  return obj;
};

Napi::Object sharevox_get_supported_devices_json(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string supported_devices("");
  std::string error = sharevox_core_get_supported_devices_json(supported_devices);
  obj.Set("error", error);
  obj.Set("result", supported_devices);
  return obj;
};

Napi::Object sharevox_audio_query(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string text = load_string(info, 0);
  uint32_t speaker_id = load_uint32_t(info, 1);
  char *output_audio_query_json = nullptr;
  SharevoxAudioQueryOptions options = {false};
  options.kana = load_bool(info, 2);
  std::string error = sharevox_core_audio_query(text.c_str(), speaker_id, options, &output_audio_query_json);
  obj.Set("error", error);
  obj.Set("result", output_audio_query_json);
  std::string error_2 = sharevox_core_audio_query_json_free(output_audio_query_json);
  obj.Set("error_2", error_2);
  return obj;
};

Napi::Object sharevox_synthesis(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  std::string audio_query_json = load_string(info, 0);
  uint32_t speaker_id = load_uint32_t(info, 1);
  size_t output_wav_length = 0;
  uint8_t *output_wav = nullptr;
  SharevoxSynthesisOptions options = {false};
  options.enable_interrogative_upspeak = load_bool(info, 2);
  std::string error = sharevox_core_synthesis(audio_query_json.c_str(), speaker_id, options, &output_wav_length, &output_wav);
  obj.Set("error", error);
  obj.Set("result", Napi::Buffer<uint8_t>::New(env, output_wav, output_wav_length));
  std::string error_2 = sharevox_core_wav_free(output_wav);
  obj.Set("error_2", error_2);
  return obj;
};

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("initialize", Napi::Function::New(env, initialize));
  exports.Set("finalize", Napi::Function::New(env, finalize));

  exports.Set("sharevoxInitialize", Napi::Function::New(env, sharevox_initialize));
  exports.Set("sharevoxGetVersion", Napi::Function::New(env, sharevox_get_version));
  exports.Set("sharevoxLoadModel", Napi::Function::New(env, sharevox_load_model));
  exports.Set("sharevoxIsGpuMode", Napi::Function::New(env, sharevox_is_gpu_mode));
  exports.Set("sharevoxIsModelLoaded", Napi::Function::New(env, sharevox_is_model_loaded));
  exports.Set("sharevoxFinalize", Napi::Function::New(env, sharevox_finalize));
  exports.Set("sharevoxGetMetasJson", Napi::Function::New(env, sharevox_get_metas_json));
  exports.Set("sharevoxGetSupportedDevicesJson", Napi::Function::New(env, sharevox_get_supported_devices_json));
  exports.Set("sharevoxAudioQuery", Napi::Function::New(env, sharevox_audio_query));
  exports.Set("sharevoxSynthesis", Napi::Function::New(env, sharevox_synthesis));
  return exports;
}

NODE_API_MODULE(sharevox, Init);