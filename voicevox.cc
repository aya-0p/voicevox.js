#include "voicevox.h"
#include <napi.h>
#include "voicevox_core.h"
#include <map>

using namespace Napi;

const char *load_string(const Napi::CallbackInfo &info, size_t index)
{
	std::string text = info[index].As<Napi::String>().Utf8Value() + "\0";
	char *cstr = new char[text.size() + 1];
	std::char_traits<char>::copy(cstr, text.c_str(), text.size() + 1);
	return const_cast<const char *>(cstr);
}

uint32_t load_uint32_t(const Napi::CallbackInfo &info, size_t index)
{
	return info[index].As<Napi::Number>().Uint32Value();
}

bool load_bool(const Napi::CallbackInfo &info, size_t index)
{
	return info[index].As<Napi::Boolean>().Value();
}

std::string copy_str(const char *str)
{
	std::string r("");
	for (size_t i = 0; i < strlen(str); i++)
	{
		r += str[i];
	}
	return r;
}

Napi::Object Voicevox::NewInstance(Napi::Env env, const Napi::CallbackInfo &info)
{
	Napi::EscapableHandleScope scope(env);
	const std::initializer_list<napi_value> initArgList = {info[0]};
	Napi::Object obj = env.GetInstanceData<Napi::FunctionReference>()->New(initArgList);
	return scope.Escape(napi_value(obj)).ToObject();
}

Napi::Object Voicevox::Init(Napi::Env env, Napi::Object exports)
{
	Napi::Function func = DefineClass(env, "Voicevox", {
																												 InstanceMethod("voicevoxOpenJtalkRcNew", &Voicevox::voicevoxOpenJtalkRcNew),
																												 InstanceMethod("voicevoxOpenJtalkRcUseUserDict", &Voicevox::voicevoxOpenJtalkRcUseUserDict),
																												 InstanceMethod("voicevoxOpenJtalkRcDelete", &Voicevox::voicevoxOpenJtalkRcDelete),
																												 InstanceMethod("voicevoxGetVersion", &Voicevox::voicevoxGetVersion),
																												 InstanceMethod("voicevoxVoiceModelNewFromPath", &Voicevox::voicevoxVoiceModelNewFromPath),
																												 InstanceMethod("voicevoxVoiceModelId", &Voicevox::voicevoxVoiceModelId),
																												 InstanceMethod("voicevoxVoiceModelGetMetasJson", &Voicevox::voicevoxVoiceModelGetMetasJson),
																												 InstanceMethod("voicevoxVoiceModelDelete", &Voicevox::voicevoxVoiceModelDelete),
																												 InstanceMethod("voicevoxSynthesizerNew", &Voicevox::voicevoxSynthesizerNew),
																												 InstanceMethod("voicevoxSynthesizerDelete", &Voicevox::voicevoxSynthesizerDelete),
																												 InstanceMethod("voicevoxSynthesizerLoadVoiceModel", &Voicevox::voicevoxSynthesizerLoadVoiceModel),
																												 InstanceMethod("voicevoxSynthesizerUnloadVoiceModel", &Voicevox::voicevoxSynthesizerUnloadVoiceModel),
																												 InstanceMethod("voicevoxSynthesizerIsGpuMode", &Voicevox::voicevoxSynthesizerIsGpuMode),
																												 InstanceMethod("voicevoxSynthesizerIsLoadedVoiceModel", &Voicevox::voicevoxSynthesizerIsLoadedVoiceModel),
																												 InstanceMethod("voicevoxSynthesizerCreateMetasJson", &Voicevox::voicevoxSynthesizerCreateMetasJson),
																												 InstanceMethod("voicevoxCreateSupportedDevicesJson", &Voicevox::voicevoxCreateSupportedDevicesJson),
																												 InstanceMethod("voicevoxSynthesizerCreateAudioQueryFromKana", &Voicevox::voicevoxSynthesizerCreateAudioQueryFromKana),
																												 InstanceMethod("voicevoxSynthesizerCreateAudioQuery", &Voicevox::voicevoxSynthesizerCreateAudioQuery),
																												 InstanceMethod("voicevoxSynthesizerCreateAccentPhrasesFromKana", &Voicevox::voicevoxSynthesizerCreateAccentPhrasesFromKana),
																												 InstanceMethod("voicevoxSynthesizerCreateAccentPhrases", &Voicevox::voicevoxSynthesizerCreateAccentPhrases),
																												 InstanceMethod("voicevoxSynthesizerReplaceMoraData", &Voicevox::voicevoxSynthesizerReplaceMoraData),
																												 InstanceMethod("voicevoxSynthesizerReplacePhonemeLength", &Voicevox::voicevoxSynthesizerReplacePhonemeLength),
																												 InstanceMethod("voicevoxSynthesizerReplaceMoraPitch", &Voicevox::voicevoxSynthesizerReplaceMoraPitch),
																												 InstanceMethod("voicevoxSynthesizerSynthesis", &Voicevox::voicevoxSynthesizerSynthesis),
																												 InstanceMethod("voicevoxSynthesizerTtsFromKana", &Voicevox::voicevoxSynthesizerTtsFromKana),
																												 InstanceMethod("voicevoxSynthesizerTts", &Voicevox::voicevoxSynthesizerTts),
																												 InstanceMethod("voicevoxErrorResultToMessage", &Voicevox::voicevoxErrorResultToMessage),
																												 InstanceMethod("voicevoxUserDictNew", &Voicevox::voicevoxUserDictNew),
																												 InstanceMethod("voicevoxUserDictLoad", &Voicevox::voicevoxUserDictLoad),
																												 InstanceMethod("voicevoxUserDictAddWord", &Voicevox::voicevoxUserDictAddWord),
																												 InstanceMethod("voicevoxUserDictUpdateWord", &Voicevox::voicevoxUserDictUpdateWord),
																												 InstanceMethod("voicevoxUserDictRemoveWord", &Voicevox::voicevoxUserDictRemoveWord),
																												 InstanceMethod("voicevoxUserDictToJson", &Voicevox::voicevoxUserDictToJson),
																												 InstanceMethod("voicevoxUserDictImport", &Voicevox::voicevoxUserDictImport),
																												 InstanceMethod("voicevoxUserDictSave", &Voicevox::voicevoxUserDictSave),
																												 InstanceMethod("voicevoxUserDictDelete", &Voicevox::voicevoxUserDictDelete),
																										 });

	Napi::FunctionReference *constructor = new Napi::FunctionReference();
	*constructor = Napi::Persistent(func);
	env.SetInstanceData(constructor);

	exports.Set("Voicevox", func);
	return exports;
}

Voicevox::Voicevox(const Napi::CallbackInfo &info)
		: Napi::ObjectWrap<Voicevox>(info)
{
	const char *voicevox_core = load_string(info, 0);
	dll = dll_load(voicevox_core);
}

Voicevox::~Voicevox()
{
	dll_free(dll);
}

Napi::Value Voicevox::voicevoxOpenJtalkRcNew(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *open_jtalk_dic_dir = load_string(info, 0);
	uint32_t open_jtalk_pointer_name = load_uint32_t(info, 1);
	OpenJtalkRc *out_open_jtalk;
	VoicevoxResultCode resultCode = voicevox_open_jtalk_rc_new(this->dll, open_jtalk_dic_dir, &out_open_jtalk);
	this->open_jtalk_pointers.emplace(open_jtalk_pointer_name, reinterpret_cast<uintptr_t>(out_open_jtalk));
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxOpenJtalkRcUseUserDict(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t open_jtalk_pointer_name = load_uint32_t(info, 0);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 1);
	if (!this->open_jtalk_pointers.count(open_jtalk_pointer_name))
	{
		Napi::Error::New(env, "open_jtalkのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const OpenJtalkRc *open_jtalk = reinterpret_cast<const OpenJtalkRc *>(this->open_jtalk_pointers.at(open_jtalk_pointer_name));
	const VoicevoxUserDict *user_dict = reinterpret_cast<const VoicevoxUserDict *>(this->user_dict_pointers.at(user_dict_pointer_name));
	VoicevoxResultCode resultCode = voicevox_open_jtalk_rc_use_user_dict(this->dll, open_jtalk, user_dict);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxOpenJtalkRcDelete(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t open_jtalk_pointer_name = load_uint32_t(info, 0);
	if (!this->open_jtalk_pointers.count(open_jtalk_pointer_name))
	{
		Napi::Error::New(env, "open_jtalkのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	OpenJtalkRc *open_jtalk = reinterpret_cast<OpenJtalkRc *>(this->open_jtalk_pointers.at(open_jtalk_pointer_name));
	voicevox_open_jtalk_rc_delete(this->dll, open_jtalk);
	this->open_jtalk_pointers.erase(open_jtalk_pointer_name);
	return obj;
}

Napi::Value Voicevox::voicevoxGetVersion(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *result = voicevox_get_version(this->dll);
	obj.Set("result", Napi::String::New(env, copy_str(result)));
	return obj;
}

Napi::Value Voicevox::voicevoxVoiceModelNewFromPath(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *path = load_string(info, 0);
	VoicevoxVoiceModel *out_model;
	uint32_t model_pointer_name = load_uint32_t(info, 1);
	VoicevoxResultCode resultCode = voicevox_voice_model_new_from_path(this->dll, path, &out_model);
	this->model_pointers.emplace(model_pointer_name, reinterpret_cast<uintptr_t>(out_model));
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxVoiceModelId(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t model_pointer_name = load_uint32_t(info, 0);
	if (!this->model_pointers.count(model_pointer_name))
	{
		Napi::Error::New(env, "voice_modelのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxVoiceModel *model = reinterpret_cast<const VoicevoxVoiceModel *>(this->model_pointers.at(model_pointer_name));
	VoicevoxVoiceModelId result = voicevox_voice_model_id(this->dll, model);
	obj.Set("result", Napi::String::New(env, copy_str(result)));
	return obj;
}

Napi::Value Voicevox::voicevoxVoiceModelGetMetasJson(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t model_pointer_name = load_uint32_t(info, 0);
	if (!this->model_pointers.count(model_pointer_name))
	{
		Napi::Error::New(env, "voice_modelのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxVoiceModel *model = reinterpret_cast<const VoicevoxVoiceModel *>(this->model_pointers.at(model_pointer_name));
	const char *result = voicevox_voice_model_get_metas_json(this->dll, model);
	obj.Set("result", Napi::String::New(env, copy_str(result)));
	return obj;
}

Napi::Value Voicevox::voicevoxVoiceModelDelete(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t model_pointer_name = load_uint32_t(info, 0);
	if (!this->model_pointers.count(model_pointer_name))
	{
		Napi::Error::New(env, "voice_modelのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	VoicevoxVoiceModel *model = reinterpret_cast<VoicevoxVoiceModel *>(this->model_pointers.at(model_pointer_name));
	voicevox_voice_model_delete(this->dll, model);
	this->model_pointers.erase(model_pointer_name);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerNew(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t open_jtalk_pointer_name = load_uint32_t(info, 0);
	if (!this->open_jtalk_pointers.count(open_jtalk_pointer_name))
	{
		Napi::Error::New(env, "open_jtalkのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const OpenJtalkRc *open_jtalk = reinterpret_cast<const OpenJtalkRc *>(this->open_jtalk_pointers.at(open_jtalk_pointer_name));
	uint32_t out_synthesizer_pointer_name = load_uint32_t(info, 1);
	VoicevoxSynthesizer *out_synthesizer;
	VoicevoxInitializeOptions options = voicevox_make_default_initialize_options(this->dll);
	options.acceleration_mode = static_cast<VoicevoxAccelerationMode>(load_uint32_t(info, 2));
	options.cpu_num_threads = static_cast<uint16_t>(load_uint32_t(info, 3));
	VoicevoxResultCode resultCode = voicevox_synthesizer_new(this->dll, open_jtalk, options, &out_synthesizer);
	this->synthesizer_pointers.emplace(out_synthesizer_pointer_name, reinterpret_cast<uintptr_t>(out_synthesizer));
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerDelete(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	VoicevoxSynthesizer *synthesizer = reinterpret_cast<VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	voicevox_synthesizer_delete(this->dll, synthesizer);
	this->synthesizer_pointers.erase(synthesizer_pointer_name);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerLoadVoiceModel(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	uint32_t model_pointer_name = load_uint32_t(info, 1);
	if (!this->model_pointers.count(model_pointer_name))
	{
		Napi::Error::New(env, "voice_modelのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxVoiceModel *model = reinterpret_cast<const VoicevoxVoiceModel *>(this->model_pointers.at(model_pointer_name));
	VoicevoxResultCode resultCode = voicevox_synthesizer_load_voice_model(this->dll, synthesizer, model);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerUnloadVoiceModel(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	VoicevoxVoiceModelId model_id = load_string(info, 1);
	VoicevoxResultCode resultCode = voicevox_synthesizer_unload_voice_model(this->dll, synthesizer, model_id);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerIsGpuMode(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	bool result = voicevox_synthesizer_is_gpu_mode(this->dll, synthesizer);
	obj.Set("result", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerIsLoadedVoiceModel(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	VoicevoxVoiceModelId model_id = load_string(info, 1);
	bool result = voicevox_synthesizer_is_loaded_voice_model(this->dll, synthesizer, model_id);
	obj.Set("result", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerCreateMetasJson(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	char *result = voicevox_synthesizer_create_metas_json(this->dll, synthesizer);
	obj.Set("result", Napi::String::New(env, copy_str(result)));
	voicevox_json_free(this->dll, result);
	return obj;
}

Napi::Value Voicevox::voicevoxCreateSupportedDevicesJson(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	char *output_supported_devices_json;
	VoicevoxResultCode resultCode = voicevox_create_supported_devices_json(this->dll, &output_supported_devices_json);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::String::New(env, copy_str(output_supported_devices_json)));
	voicevox_json_free(this->dll, output_supported_devices_json);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerCreateAudioQueryFromKana(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *kana = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	char *output_audio_query_json;
	VoicevoxResultCode resultCode = voicevox_synthesizer_create_audio_query_from_kana(this->dll, synthesizer, kana, style_id, &output_audio_query_json);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::String::New(env, copy_str(output_audio_query_json)));
	voicevox_json_free(this->dll, output_audio_query_json);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerCreateAudioQuery(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *text = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	char *output_audio_query_json;
	VoicevoxResultCode resultCode = voicevox_synthesizer_create_audio_query(this->dll, synthesizer, text, style_id, &output_audio_query_json);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::String::New(env, copy_str(output_audio_query_json)));
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerCreateAccentPhrasesFromKana(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *kana = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	char *output_accent_phrases_json;
	VoicevoxResultCode resultCode = voicevox_synthesizer_create_accent_phrases_from_kana(this->dll, synthesizer, kana, style_id, &output_accent_phrases_json);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::String::New(env, copy_str(output_accent_phrases_json)));
	voicevox_json_free(this->dll, output_accent_phrases_json);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerCreateAccentPhrases(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *text = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	char *output_accent_phrases_json;
	VoicevoxResultCode resultCode = voicevox_synthesizer_create_accent_phrases(this->dll, synthesizer, text, style_id, &output_accent_phrases_json);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::String::New(env, copy_str(output_accent_phrases_json)));
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerReplaceMoraData(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *accent_phrases_json = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	char *output_accent_phrases_json;
	VoicevoxResultCode resultCode = voicevox_synthesizer_replace_mora_data(this->dll, synthesizer, accent_phrases_json, style_id, &output_accent_phrases_json);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::String::New(env, copy_str(output_accent_phrases_json)));
	voicevox_json_free(this->dll, output_accent_phrases_json);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerReplacePhonemeLength(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *accent_phrases_json = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	char *output_accent_phrases_json;
	VoicevoxResultCode resultCode = voicevox_synthesizer_replace_phoneme_length(this->dll, synthesizer, accent_phrases_json, style_id, &output_accent_phrases_json);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::String::New(env, copy_str(output_accent_phrases_json)));
	voicevox_json_free(this->dll, output_accent_phrases_json);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerReplaceMoraPitch(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *accent_phrases_json = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	char *output_accent_phrases_json;
	VoicevoxResultCode resultCode = voicevox_synthesizer_replace_mora_pitch(this->dll, synthesizer, accent_phrases_json, style_id, &output_accent_phrases_json);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::String::New(env, copy_str(output_accent_phrases_json)));
	voicevox_json_free(this->dll, output_accent_phrases_json);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerSynthesis(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *audio_query_json = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	VoicevoxSynthesisOptions options = voicevox_make_default_synthesis_options(this->dll);
	options.enable_interrogative_upspeak = load_bool(info, 3);
	uintptr_t output_wav_length;
	uint8_t *output_wav;
	VoicevoxResultCode resultCode = voicevox_synthesizer_synthesis(this->dll, synthesizer, audio_query_json, style_id, options, &output_wav_length, &output_wav);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::Buffer<uint8_t>::Copy(env, output_wav, output_wav_length));
	voicevox_wav_free(this->dll, output_wav);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerTtsFromKana(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *kana = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	VoicevoxTtsOptions options = voicevox_make_default_tts_options(this->dll);
	options.enable_interrogative_upspeak = load_bool(info, 3);
	uintptr_t output_wav_length;
	uint8_t *output_wav;
	VoicevoxResultCode resultCode = voicevox_synthesizer_tts_from_kana(this->dll, synthesizer, kana, style_id, options, &output_wav_length, &output_wav);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::Buffer<uint8_t>::Copy(env, output_wav, output_wav_length));
	voicevox_wav_free(this->dll, output_wav);
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesizerTts(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t synthesizer_pointer_name = load_uint32_t(info, 0);
	if (!this->synthesizer_pointers.count(synthesizer_pointer_name))
	{
		Napi::Error::New(env, "synthesizerのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxSynthesizer *synthesizer = reinterpret_cast<const VoicevoxSynthesizer *>(this->synthesizer_pointers.at(synthesizer_pointer_name));
	const char *text = load_string(info, 1);
	VoicevoxStyleId style_id = static_cast<VoicevoxStyleId>(load_uint32_t(info, 2));
	VoicevoxTtsOptions options = voicevox_make_default_tts_options(this->dll);
	options.enable_interrogative_upspeak = load_bool(info, 3);
	uintptr_t output_wav_length;
	uint8_t *output_wav;
	VoicevoxResultCode resultCode = voicevox_synthesizer_tts(this->dll, synthesizer, text, style_id, options, &output_wav_length, &output_wav);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::Buffer<uint8_t>::Copy(env, output_wav, output_wav_length));
	voicevox_wav_free(this->dll, output_wav);
	return obj;
}

Napi::Value Voicevox::voicevoxErrorResultToMessage(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	VoicevoxResultCode resultCode = static_cast<VoicevoxResultCode>(load_uint32_t(info, 0));
	const char *result = voicevox_error_result_to_message(this->dll, resultCode);
	obj.Set("result", Napi::String::New(env, copy_str(result)));
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictNew(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	VoicevoxUserDict *userDict = voicevox_user_dict_new(this->dll);
	this->user_dict_pointers.emplace(user_dict_pointer_name, reinterpret_cast<uintptr_t>(userDict));
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictLoad(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	if (!this->user_dict_pointers.count(user_dict_pointer_name))
	{
		Napi::Error::New(env, "user_dictのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxUserDict *user_dict = reinterpret_cast<const VoicevoxUserDict *>(this->user_dict_pointers.at(user_dict_pointer_name));
	const char *dict_path = load_string(info, 1);
	VoicevoxResultCode resultCode = voicevox_user_dict_load(this->dll, user_dict, dict_path);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictAddWord(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	if (!this->user_dict_pointers.count(user_dict_pointer_name))
	{
		Napi::Error::New(env, "user_dictのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxUserDict *user_dict = reinterpret_cast<const VoicevoxUserDict *>(this->user_dict_pointers.at(user_dict_pointer_name));
	const char *surface = load_string(info, 1);
	const char *pronunciation = load_string(info, 2);
	VoicevoxUserDictWord word = voicevox_user_dict_word_make(this->dll, surface, pronunciation);
	word.accent_type = static_cast<uintptr_t>(load_uint32_t(info, 3));
	word.priority = load_uint32_t(info, 4);
	word.word_type = static_cast<VoicevoxUserDictWordType>(load_uint32_t(info, 5));
	uint8_t output_word_uuid[16];
	VoicevoxResultCode resultCode = voicevox_user_dict_add_word(this->dll, user_dict, &word, &output_word_uuid);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	std::string uuid;
	for (size_t i = 0; i < 16; i++)
	{
		uuid += static_cast<char>(output_word_uuid[i]);
	}
	uuid.append("\0");
	obj.Set("result", Napi::String::New(env, uuid));
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictUpdateWord(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	if (!this->user_dict_pointers.count(user_dict_pointer_name))
	{
		Napi::Error::New(env, "user_dictのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxUserDict *user_dict = reinterpret_cast<const VoicevoxUserDict *>(this->user_dict_pointers.at(user_dict_pointer_name));
	const char *surface = load_string(info, 1);
	const char *pronunciation = load_string(info, 2);
	VoicevoxUserDictWord word = voicevox_user_dict_word_make(this->dll, surface, pronunciation);
	word.accent_type = static_cast<uintptr_t>(load_uint32_t(info, 3));
	word.priority = load_uint32_t(info, 4);
	word.word_type = static_cast<VoicevoxUserDictWordType>(load_uint32_t(info, 5));
	uint8_t word_uuid[16];
	const char *uuid = load_string(info, 6);
	for (size_t i = 0; i < 16; i++)
	{
		word_uuid[i] = uuid[i];
	}
	VoicevoxResultCode resultCode = voicevox_user_dict_update_word(this->dll, user_dict, &word_uuid, &word);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictRemoveWord(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	if (!this->user_dict_pointers.count(user_dict_pointer_name))
	{
		Napi::Error::New(env, "user_dictのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxUserDict *user_dict = reinterpret_cast<const VoicevoxUserDict *>(this->user_dict_pointers.at(user_dict_pointer_name));
	uint8_t word_uuid[16];
	const char *uuid = load_string(info, 1);
	for (size_t i = 0; i < 16; i++)
	{
		word_uuid[i] = uuid[i];
	}
	VoicevoxResultCode resultCode = voicevox_user_dict_remove_word(this->dll, user_dict, &word_uuid);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictToJson(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	if (!this->user_dict_pointers.count(user_dict_pointer_name))
	{
		Napi::Error::New(env, "user_dictのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxUserDict *user_dict = reinterpret_cast<const VoicevoxUserDict *>(this->user_dict_pointers.at(user_dict_pointer_name));
	char *output_json;
	VoicevoxResultCode resultCode = voicevox_user_dict_to_json(this->dll, user_dict, &output_json);
	obj.Set("result", Napi::String::New(env, copy_str(output_json)));
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	voicevox_json_free(this->dll, output_json);
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictImport(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	if (!this->user_dict_pointers.count(user_dict_pointer_name))
	{
		Napi::Error::New(env, "user_dictのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxUserDict *user_dict = reinterpret_cast<const VoicevoxUserDict *>(this->user_dict_pointers.at(user_dict_pointer_name));
	uint32_t other_dict_pointer_name = load_uint32_t(info, 1);
	if (!this->user_dict_pointers.count(other_dict_pointer_name))
	{
		Napi::Error::New(env, "other_dictのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxUserDict *other_dict = reinterpret_cast<const VoicevoxUserDict *>(this->user_dict_pointers.at(other_dict_pointer_name));
	VoicevoxResultCode resultCode = voicevox_user_dict_import(this->dll, user_dict, other_dict);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictSave(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	if (!this->user_dict_pointers.count(user_dict_pointer_name))
	{
		Napi::Error::New(env, "user_dictのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	const VoicevoxUserDict *user_dict = reinterpret_cast<const VoicevoxUserDict *>(this->user_dict_pointers.at(user_dict_pointer_name));
	const char *path = load_string(info, 1);
	VoicevoxResultCode resultCode = voicevox_user_dict_save(this->dll, user_dict, path);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictDelete(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	if (!this->user_dict_pointers.count(user_dict_pointer_name))
	{
		Napi::Error::New(env, "user_dictのポインタが見つかりませんでした").ThrowAsJavaScriptException();
		return obj;
	}
	VoicevoxUserDict *user_dict = reinterpret_cast<VoicevoxUserDict *>(this->user_dict_pointers.at(user_dict_pointer_name));
	voicevox_user_dict_delete(this->dll, user_dict);
	this->user_dict_pointers.erase(user_dict_pointer_name);
	return obj;
}
