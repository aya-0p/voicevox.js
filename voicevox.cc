#include <napi.h>
#include "voicevox_core/voicevox_core.h"
#include <string>

using namespace Napi;

Napi::Number initialize(const Napi::CallbackInfo& info) {
	VoicevoxInitializeOptions options = voicevox_make_default_initialize_options();
	options.acceleration_mode = static_cast<VoicevoxAccelerationMode>(info[0].As<Napi::Number>().Int32Value());
	options.cpu_num_threads = info[1].As<Napi::Number>().Uint32Value();
	options.load_all_models = info[2].As<Napi::Boolean>().Value();
	std::string dir = info[3].As<Napi::String>().Utf8Value() + '\0';
	options.open_jtalk_dict_dir = dir.c_str();

	VoicevoxResultCode result = voicevox_initialize(options);
	return Napi::Number::New(info.Env(), result);
}

Napi::String get_version(const Napi::CallbackInfo& info) {
	const char* result = voicevox_get_version();
	return Napi::String::New(info.Env(), result);
}

Napi::Number load_model(const Napi::CallbackInfo& info) {
	uint32_t speaker_id = info[0].As<Napi::Number>().Uint32Value();
	VoicevoxResultCode result = voicevox_load_model(speaker_id);
	return Napi::Number::New(info.Env(), result);
}

Napi::Boolean is_gpu_mode(const Napi::CallbackInfo& info) {
	bool result = voicevox_is_gpu_mode();
	return Napi::Boolean::New(info.Env(), result);
}

Napi::Boolean is_model_loaded(const Napi::CallbackInfo& info) {
	uint32_t speaker_id = info[0].As<Napi::Number>().Uint32Value();
	bool result = voicevox_is_model_loaded(speaker_id);
	return Napi::Boolean::New(info.Env(), result);
}

void finalize(const Napi::CallbackInfo& info) {
	return voicevox_finalize();
}

Napi::String get_metas_json(const Napi::CallbackInfo& info) {
	const char* result = voicevox_get_metas_json();
	return Napi::String::New(info.Env(), result);
}

Napi::String get_supported_devices_json(const Napi::CallbackInfo& info) {
	const char* result = voicevox_get_supported_devices_json();
	return Napi::String::New(info.Env(), result);
}

Napi::Object audio_query(const Napi::CallbackInfo& info) {
	VoicevoxAudioQueryOptions options = voicevox_make_default_audio_query_options();
	std::string text = info[0].As<Napi::String>().Utf8Value() + '\0';
	uint32_t speaker_id = info[1].As<Napi::Number>().Uint32Value();
	options.kana = info[2].As<Napi::Boolean>().Value();
	char* output_audio_query_json = nullptr;
	VoicevoxResultCode result = voicevox_audio_query(text.c_str(), speaker_id, options, &output_audio_query_json);
	Napi::Object obj = Napi::Object::New(info.Env());
	obj.Set("result", Napi::Number::New(info.Env(), result));
	obj.Set("output", output_audio_query_json);
	voicevox_audio_query_json_free(output_audio_query_json);
	return obj;
}

Napi::Object synthesis(const Napi::CallbackInfo& info) {
	VoicevoxSynthesisOptions options = voicevox_make_default_synthesis_options();
	std::string audio_query_json = info[0].As<Napi::String>().Utf8Value() + '\0';
	uint32_t speaker_id = info[1].As<Napi::Number>().Uint32Value();
	options.enable_interrogative_upspeak = info[2].As<Napi::Boolean>().Value();
	uintptr_t output_wav_length = 0;
	uint8_t* output_wav = nullptr;
	VoicevoxResultCode result = voicevox_synthesis(audio_query_json.c_str(), speaker_id, options, &output_wav_length, &output_wav);
	Napi::Object obj = Napi::Object::New(info.Env());
	obj.Set("result", Napi::Number::New(info.Env(), result));
	obj.Set("output", Napi::Buffer<uint8_t>::New(info.Env(), output_wav, output_wav_length));
	voicevox_wav_free(output_wav);
	return obj;
}

Napi::String error_result_to_message(const Napi::CallbackInfo& info) {
	const char* result = voicevox_error_result_to_message(static_cast<VoicevoxResultCode>(info[0].As<Napi::Number>().Uint32Value()));
	return Napi::String::New(info.Env(), result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	exports.Set("initialize", Napi::Function::New(env, initialize));
	exports.Set("get_version", Napi::Function::New(env, get_version));
	exports.Set("load_model", Napi::Function::New(env, load_model));
	exports.Set("is_gpu_mode", Napi::Function::New(env, is_gpu_mode));
	exports.Set("is_model_loaded", Napi::Function::New(env, is_model_loaded));
	exports.Set("finalize", Napi::Function::New(env, finalize));
	exports.Set("get_metas_json", Napi::Function::New(env, get_metas_json));
	exports.Set("get_supported_devices_json", Napi::Function::New(env, get_supported_devices_json));
	exports.Set("audio_query", Napi::Function::New(env, audio_query));
	exports.Set("synthesis", Napi::Function::New(env, synthesis));
	exports.Set("error_result_to_message", Napi::Function::New(env, error_result_to_message));
	return exports;
}

NODE_API_MODULE(voicevox, Init)