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
																												 InstanceMethod("voicevoxInitialize", &Voicevox::voicevoxInitialize),
																												 InstanceMethod("voicevoxLoadModel", &Voicevox::voicevoxLoadModel),
																												 InstanceMethod("voicevoxIsGpuMode", &Voicevox::voicevoxIsGpuMode),
																												 InstanceMethod("voicevoxIsModelLoaded", &Voicevox::voicevoxIsModelLoaded),
																												 InstanceMethod("voicevoxFinalize", &Voicevox::voicevoxFinalize),
																												 InstanceMethod("voicevoxGetMetasJson", &Voicevox::voicevoxGetMetasJson),
																												 InstanceMethod("voicevoxGetSupportedDevicesJson", &Voicevox::voicevoxGetSupportedDevicesJson),
																												 InstanceMethod("voicevoxPredictDuration", &Voicevox::voicevoxPredictDuration),
																												 InstanceMethod("voicevoxPredictIntonation", &Voicevox::voicevoxPredictIntonation),
																												 InstanceMethod("voicevoxDecode", &Voicevox::voicevoxDecode),
																												 InstanceMethod("voicevoxAudioQuery", &Voicevox::voicevoxAudioQuery),
																												 InstanceMethod("voicevoxSynthesis", &Voicevox::voicevoxSynthesis),
																												 InstanceMethod("voicevoxTts", &Voicevox::voicevoxTts),
																												 InstanceMethod("initialize", &Voicevox::initialize),
																												 InstanceMethod("loadModel", &Voicevox::loadModel),
																												 InstanceMethod("isModelLoaded", &Voicevox::isModelLoaded),
																												 InstanceMethod("finalize", &Voicevox::finalize),
																												 InstanceMethod("metas", &Voicevox::metas),
																												 InstanceMethod("supportedDevices", &Voicevox::supportedDevices),
																												 InstanceMethod("yukarinSForward", &Voicevox::yukarinSForward),
																												 InstanceMethod("yukarinSaForward", &Voicevox::yukarinSaForward),
																												 InstanceMethod("decodeForward", &Voicevox::decodeForward),
																												 InstanceMethod("lastErrorMessage", &Voicevox::lastErrorMessage),
																												 InstanceMethod("voicevoxLoadOpenjtalkDict", &Voicevox::voicevoxLoadOpenjtalkDict),
																												 InstanceMethod("voicevoxTtsV13", &Voicevox::voicevoxTtsV13),
																												 InstanceMethod("voicevoxTtsFromKana", &Voicevox::voicevoxTtsFromKana),
																												 InstanceMethod("initializeV11", &Voicevox::initializeV11),
																												 InstanceMethod("initializeV9", &Voicevox::initializeV9),
																												 InstanceMethod("yukarinSForwardV7", &Voicevox::yukarinSForwardV7),
																												 InstanceMethod("yukarinSaForwardV7", &Voicevox::yukarinSaForwardV7),
																												 InstanceMethod("decodeForwardV7", &Voicevox::decodeForwardV7),
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
	try
	{
		voicevox_open_jtalk_rc_delete(this->dll, open_jtalk);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	this->open_jtalk_pointers.erase(open_jtalk_pointer_name);
	return obj;
}

Napi::Value Voicevox::voicevoxGetVersion(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *result;
	try
	{
		result = voicevox_get_version(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	const char *result;
	try
	{
		result = voicevox_voice_model_get_metas_json(this->dll, model);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	try
	{
		voicevox_voice_model_delete(this->dll, model);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	VoicevoxInitializeOptions options;
	try
	{
		options = voicevox_make_default_initialize_options(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	try
	{
		voicevox_synthesizer_delete(this->dll, synthesizer);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	bool result;
	try
	{
		result = voicevox_synthesizer_is_gpu_mode(this->dll, synthesizer);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	bool result;
	try
	{
		result = voicevox_synthesizer_is_loaded_voice_model(this->dll, synthesizer, model_id);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	char *result;
	try
	{
		result = voicevox_synthesizer_create_metas_json(this->dll, synthesizer);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::String::New(env, copy_str(result)));

	try
	{
		voicevox_json_free(this->dll, result);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	try
	{
		voicevox_json_free(this->dll, output_supported_devices_json);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	try
	{
		voicevox_json_free(this->dll, output_audio_query_json);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	try
	{
		voicevox_json_free(this->dll, output_accent_phrases_json);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	try
	{
		voicevox_json_free(this->dll, output_accent_phrases_json);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	try
	{
		voicevox_json_free(this->dll, output_accent_phrases_json);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	try
	{
		voicevox_json_free(this->dll, output_accent_phrases_json);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	VoicevoxSynthesisOptions options;
	try
	{
		options = voicevox_make_default_synthesis_options(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	options.enable_interrogative_upspeak = load_bool(info, 3);
	uintptr_t output_wav_length;
	uint8_t *output_wav;
	VoicevoxResultCode resultCode = voicevox_synthesizer_synthesis(this->dll, synthesizer, audio_query_json, style_id, options, &output_wav_length, &output_wav);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::Buffer<uint8_t>::Copy(env, output_wav, output_wav_length));
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
	VoicevoxTtsOptions options;
	try
	{
		options = voicevox_make_default_tts_options(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	options.enable_interrogative_upspeak = load_bool(info, 3);
	uintptr_t output_wav_length;
	uint8_t *output_wav;
	VoicevoxResultCode resultCode = voicevox_synthesizer_tts_from_kana(this->dll, synthesizer, kana, style_id, options, &output_wav_length, &output_wav);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	obj.Set("result", Napi::Buffer<uint8_t>::Copy(env, output_wav, output_wav_length));
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
	return obj;
}

Napi::Value Voicevox::voicevoxErrorResultToMessage(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	VoicevoxResultCode resultCode = static_cast<VoicevoxResultCode>(load_uint32_t(info, 0));
	const char *result;
	try
	{
		result = voicevox_error_result_to_message(this->dll, resultCode);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::String::New(env, copy_str(result)));
	return obj;
}

Napi::Value Voicevox::voicevoxUserDictNew(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t user_dict_pointer_name = load_uint32_t(info, 0);
	VoicevoxUserDict *userDict;
	try
	{
		userDict = voicevox_user_dict_new(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	VoicevoxUserDictWord word;
	try
	{
		word = voicevox_user_dict_word_make(this->dll, surface, pronunciation);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	word.accent_type = static_cast<uintptr_t>(load_uint32_t(info, 3));
	word.priority = load_uint32_t(info, 4);
	word.word_type = static_cast<VoicevoxUserDictWordType>(load_uint32_t(info, 5));
	uint8_t output_word_uuid[16];
	VoicevoxResultCode resultCode = voicevox_user_dict_add_word(this->dll, user_dict, &word, &output_word_uuid);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	Napi::Buffer<uint8_t> buffer = Napi::Buffer<uint8_t>::New(env, 16);
	for (size_t i = 0; i < 16; i++)
	{
		buffer[i] = output_word_uuid[i];
	}
	obj.Set("result", buffer);
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
	VoicevoxUserDictWord word;
	try
	{
		word = voicevox_user_dict_word_make(this->dll, surface, pronunciation);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	word.accent_type = static_cast<uintptr_t>(load_uint32_t(info, 3));
	word.priority = load_uint32_t(info, 4);
	word.word_type = static_cast<VoicevoxUserDictWordType>(load_uint32_t(info, 5));
	uint8_t word_uuid[16];
	Napi::Buffer<uint8_t> uuid = info[6].As<Napi::Buffer<uint8_t>>();
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
	Napi::Buffer<uint8_t> uuid = info[1].As<Napi::Buffer<uint8_t>>();
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
	try
	{
		voicevox_json_free(this->dll, output_json);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
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
	try
	{
		voicevox_user_dict_delete(this->dll, user_dict);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	this->user_dict_pointers.erase(user_dict_pointer_name);
	return obj;
}

Napi::Value Voicevox::voicevoxInitialize(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	VoicevoxInitializeOptionsV14 options;
	try
	{
		options = voicevox_make_default_initialize_options_v14(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	options.acceleration_mode = static_cast<VoicevoxAccelerationMode>(load_uint32_t(info, 0));
	options.cpu_num_threads = static_cast<uint16_t>(load_uint32_t(info, 1));
	options.load_all_models = load_bool(info, 2);
	options.open_jtalk_dict_dir = load_string(info, 3);
	VoicevoxResultCodeV14 resultCode = voicevox_initialize(this->dll, options);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxLoadModel(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t speaker_id = load_uint32_t(info, 0);
	VoicevoxResultCodeV14 resultCode = voicevox_load_model(this->dll, speaker_id);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxIsGpuMode(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	bool result;
	try
	{
		result = voicevox_is_gpu_mode(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::voicevoxIsModelLoaded(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	uint32_t speaker_id = load_uint32_t(info, 0);
	bool result;
	try
	{
		result = voicevox_is_model_loaded(this->dll, speaker_id);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::voicevoxFinalize(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	try
	{
		voicevox_finalize(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	return obj;
}

Napi::Value Voicevox::voicevoxGetMetasJson(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *result;
	try
	{
		result = voicevox_get_metas_json(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::String::New(env, result));
	return obj;
}

Napi::Value Voicevox::voicevoxGetSupportedDevicesJson(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *result;
	try
	{
		result = voicevox_get_supported_devices_json(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::String::New(env, result));
	return obj;
}

Napi::Value Voicevox::voicevoxPredictDuration(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array phoneme = info[0].As<Napi::Array>();
	uintptr_t length = phoneme.Length();
	std::vector<int64_t> phoneme_vector(length, 0);
	for (uintptr_t i = 0; i < length; i++)
	{
		Napi::Value value = phoneme[i];
		bool lossless;
		phoneme_vector[i] = value.As<Napi::BigInt>().Int64Value(&lossless);
	}
	uint32_t speaker_id = load_uint32_t(info, 1);
	uintptr_t output_decode_data_length;
	float *output_predict_duration_data;
	VoicevoxResultCodeV14 resultCode = voicevox_predict_duration(this->dll, length, phoneme_vector.data(), speaker_id, &output_decode_data_length, &output_predict_duration_data);
	Napi::Array result = Napi::Array::New(env, output_decode_data_length);
	for (uintptr_t i = 0; i < output_decode_data_length; i++)
	{
		result[i] = Napi::Number::New(env, output_predict_duration_data[i]);
	}
	try
	{
		voicevox_predict_duration_data_free(this->dll, output_predict_duration_data);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", result);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxPredictIntonation(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array vowel_phoneme = info[0].As<Napi::Array>();
	Napi::Array consonant_phoneme = info[1].As<Napi::Array>();
	Napi::Array start_accent = info[2].As<Napi::Array>();
	Napi::Array end_accent = info[3].As<Napi::Array>();
	Napi::Array start_accent_phrase = info[4].As<Napi::Array>();
	Napi::Array end_accent_phrase = info[5].As<Napi::Array>();
	uintptr_t length = vowel_phoneme.Length();
	std::vector<int64_t> vowel_phoneme_vector(length, 0);
	std::vector<int64_t> consonant_phoneme_vector(length, 0);
	std::vector<int64_t> start_accent_vector(length, 0);
	std::vector<int64_t> end_accent_vector(length, 0);
	std::vector<int64_t> start_accent_phrase_vector(length, 0);
	std::vector<int64_t> end_accent_phrase_vector(length, 0);
	for (uintptr_t i = 0; i < length; i++)
	{
		bool lossless;
		Napi::Value vowel_phoneme_value = vowel_phoneme[i];
		vowel_phoneme_vector[i] = vowel_phoneme_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value consonant_phoneme_value = consonant_phoneme[i];
		consonant_phoneme_vector[i] = consonant_phoneme_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value start_accent_value = start_accent[i];
		start_accent_vector[i] = start_accent_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value end_accent_value = end_accent[i];
		end_accent_vector[i] = end_accent_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value start_accent_phrase_value = start_accent_phrase[i];
		start_accent_phrase_vector[i] = start_accent_phrase_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value end_accent_phrase_value = end_accent_phrase[i];
		end_accent_phrase_vector[i] = end_accent_phrase_value.As<Napi::BigInt>().Int64Value(&lossless);
	}
	uint32_t speaker_id = load_uint32_t(info, 6);
	uintptr_t output_predict_intonation_data_length;
	float *output_predict_intonation_data;
	VoicevoxResultCodeV14 resultCode = voicevox_predict_intonation(this->dll, length, vowel_phoneme_vector.data(), consonant_phoneme_vector.data(), start_accent_vector.data(), end_accent_vector.data(), start_accent_phrase_vector.data(), end_accent_phrase_vector.data(), speaker_id, &output_predict_intonation_data_length, &output_predict_intonation_data);
	Napi::Array result = Napi::Array::New(env, output_predict_intonation_data_length);
	for (uintptr_t i = 0; i < output_predict_intonation_data_length; i++)
	{
		result[i] = Napi::Number::New(env, output_predict_intonation_data[i]);
	}
	try
	{
		voicevox_predict_intonation_data_free(this->dll, output_predict_intonation_data);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", result);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxDecode(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array f0 = info[0].As<Napi::Array>();
	uintptr_t length = f0.Length();
	std::vector<float> f0_vector(length, 0);
	for (uintptr_t i = 0; i < length; i++)
	{
		Napi::Value value = f0[i];
		f0_vector[i] = value.As<Napi::Number>().FloatValue();
	}
	Napi::Array phoneme = info[1].As<Napi::Array>();
	uintptr_t phoneme_size = phoneme.Length();
	std::vector<float> phoneme_vector(phoneme_size, 0);
	for (uintptr_t i = 0; i < phoneme_size; i++)
	{
		Napi::Value value = phoneme[i];
		phoneme_vector[i] = value.As<Napi::Number>().FloatValue();
	}
	uint32_t speaker_id = load_uint32_t(info, 2);
	uintptr_t output_decode_data_length;
	float *output_decode_data;
	VoicevoxResultCodeV14 resultCode = voicevox_decode(this->dll, length, phoneme_size, f0_vector.data(), phoneme_vector.data(), speaker_id, &output_decode_data_length, &output_decode_data);
	Napi::Array result = Napi::Array::New(env, output_decode_data_length);
	for (uintptr_t i = 0; i < output_decode_data_length; i++)
	{
		result[i] = Napi::Number::New(env, output_decode_data[i]);
	}
	try
	{
		voicevox_decode_data_free(this->dll, output_decode_data);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", result);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxAudioQuery(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	VoicevoxAudioQueryOptions options;
	try
	{
		options = voicevox_make_default_audio_query_options(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	const char *text = load_string(info, 0);
	uint32_t speaker_id = load_uint32_t(info, 1);
	options.kana = load_bool(info, 2);
	char *output_audio_query_json;
	VoicevoxResultCodeV14 resultCode = voicevox_audio_query(this->dll, text, speaker_id, options, &output_audio_query_json);
	obj.Set("result", Napi::String::New(env, copy_str(output_audio_query_json)));
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	try
	{
		voicevox_audio_query_json_free(this->dll, output_audio_query_json);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	return obj;
}

Napi::Value Voicevox::voicevoxSynthesis(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	VoicevoxSynthesisOptions options;
	try
	{
		options = voicevox_make_default_synthesis_options(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	const char *audio_query_json = load_string(info, 0);
	uint32_t speaker_id = load_uint32_t(info, 1);
	options.enable_interrogative_upspeak = load_bool(info, 2);
	uintptr_t output_wav_length;
	uint8_t *output_wav;
	VoicevoxResultCodeV14 resultCode = voicevox_synthesis(this->dll, audio_query_json, speaker_id, options, &output_wav_length, &output_wav);
	obj.Set("result", Napi::Buffer<uint8_t>::Copy(env, output_wav, output_wav_length));
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxTts(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	VoicevoxTtsOptionsV14 options;
	try
	{
		options = voicevox_make_default_tts_options_v14(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	const char *text = load_string(info, 0);
	uint32_t speaker_id = load_uint32_t(info, 1);
	options.enable_interrogative_upspeak = load_bool(info, 2);
	options.kana = load_bool(info, 3);
	uintptr_t output_wav_length;
	uint8_t *output_wav;
	VoicevoxResultCodeV14 resultCode = voicevox_tts(this->dll, text, speaker_id, options, &output_wav_length, &output_wav);
	obj.Set("result", Napi::Buffer<uint8_t>::Copy(env, output_wav, output_wav_length));
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::initialize(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	bool use_gpu = load_bool(info, 0);
	int cpu_num_threads = static_cast<int>(load_uint32_t(info, 1));
	bool load_all_models = load_bool(info, 2);
	bool result;
	try
	{
		result = initialize_v(this->dll, use_gpu, cpu_num_threads, load_all_models);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::loadModel(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	int64_t speaker_id = static_cast<int64_t>(load_uint32_t(info, 0));
	bool result;
	try
	{
		result = load_model(this->dll, speaker_id);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::isModelLoaded(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	int64_t speaker_id = static_cast<int64_t>(load_uint32_t(info, 0));
	bool result;
	try
	{
		result = is_model_loaded(this->dll, speaker_id);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::finalize(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	try
	{
		finalize_v(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	return obj;
}

Napi::Value Voicevox::metas(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *result;
	try
	{
		result = metas_v(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::String::New(env, result));
	return obj;
}

Napi::Value Voicevox::supportedDevices(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *result;
	try
	{
		result = supported_devices(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::String::New(env, result));
	return obj;
}

Napi::Value Voicevox::yukarinSForward(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array phonemeList = info[0].As<Napi::Array>();
	int64_t speaker_id = static_cast<int64_t>(load_uint32_t(info, 1));
	uint32_t length = phonemeList.Length();
	std::vector<int64_t> phoneme_list(length, 0);
	for (uint32_t i = 0; i < length; i++)
	{
		bool lossless;
		Napi::Value phoneme_list_value = phonemeList[i];
		phoneme_list[i] = phoneme_list_value.As<Napi::BigInt>().Int64Value(&lossless);
	}
	bool result;
	std::vector<float> output(length, 0.0);
	try
	{
		result = yukarin_s_forward(this->dll, static_cast<int64_t>(length), phoneme_list.data(), &speaker_id, output.data());
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	Napi::Array output_arr = Napi::Array::New(env, length);
	for (uint32_t i = 0; i < length; i++)
	{
		output_arr[i] = Napi::Number::New(env, output[i]);
	}
	obj.Set("result", output_arr);
	obj.Set("result2", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::yukarinSaForward(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array vowelPhonemeList = info[0].As<Napi::Array>();
	Napi::Array consonantPhonemeList = info[1].As<Napi::Array>();
	Napi::Array startAccentList = info[2].As<Napi::Array>();
	Napi::Array endAccentList = info[3].As<Napi::Array>();
	Napi::Array startAccentPhraseList = info[4].As<Napi::Array>();
	Napi::Array endAccentPhraseList = info[5].As<Napi::Array>();
	int64_t speaker_id = static_cast<int64_t>(load_uint32_t(info, 6));
	uint32_t length = vowelPhonemeList.Length();
	std::vector<int64_t> vowel_phoneme_list(length, 0);
	std::vector<int64_t> consonant_phrase_list(length, 0);
	std::vector<int64_t> start_accent_list(length, 0);
	std::vector<int64_t> end_accent_list(length, 0);
	std::vector<int64_t> start_accent_phrase_list(length, 0);
	std::vector<int64_t> end_accent_phrase_list(length, 0);
	for (uint32_t i = 0; i < length; i++)
	{
		bool lossless;
		Napi::Value vowel_phoneme_value = vowelPhonemeList[i];
		vowel_phoneme_list[i] = vowel_phoneme_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value consonant_phrase_value = consonantPhonemeList[i];
		consonant_phrase_list[i] = consonant_phrase_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value start_accent_value = startAccentList[i];
		start_accent_list[i] = start_accent_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value end_accent_value = endAccentList[i];
		end_accent_list[i] = end_accent_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value start_accent_phrase_value = startAccentPhraseList[i];
		start_accent_phrase_list[i] = start_accent_phrase_value.As<Napi::BigInt>().Int64Value(&lossless);
		Napi::Value end_accent_phrase_value = endAccentPhraseList[i];
		end_accent_phrase_list[i] = end_accent_phrase_value.As<Napi::BigInt>().Int64Value(&lossless);
	}
	bool result;
	std::vector<float> output(length, 0.0);
	try
	{
		result = yukarin_sa_forward(this->dll, static_cast<int64_t>(length), vowel_phoneme_list.data(), consonant_phrase_list.data(), start_accent_list.data(), end_accent_list.data(), start_accent_phrase_list.data(), end_accent_phrase_list.data(), &speaker_id, output.data());
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	Napi::Array output_arr = Napi::Array::New(env, length);
	for (uint32_t i = 0; i < length; i++)
	{
		output_arr[i] = Napi::Number::New(env, output[i]);
	}

	obj.Set("result", output_arr);
	obj.Set("result2", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::decodeForward(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array f0_ = info[0].As<Napi::Array>();
	Napi::Array phoneme_arr = info[1].As<Napi::Array>();
	int64_t speaker_id = static_cast<int64_t>(load_uint32_t(info, 2));
	uint32_t length = f0_.Length();
	uint32_t phoneme_length = phoneme_arr.Length();
	std::vector<float> f0(length, 0.0);
	std::vector<float> phoneme(phoneme_length, 0.0);
	for (uint32_t i = 0; i < length; i++)
	{
		Napi::Value f0_value = f0_[i];
		f0[i] = f0_value.As<Napi::Number>().FloatValue();
	}
	for (uint32_t i = 0; i < phoneme_length; i++)
	{
		Napi::Value phoneme_value = phoneme_arr[i];
		phoneme[i] = phoneme_value.As<Napi::Number>().FloatValue();
	}
	bool result;
	std::vector<float> output(length * 256, 0.0);
	try
	{
		result = decode_forward(this->dll, static_cast<int64_t>(length), static_cast<int64_t>(phoneme_length), f0.data(), phoneme.data(), &speaker_id, output.data());
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	Napi::Array output_arr = Napi::Array::New(env, length);
	for (uint32_t i = 0; i < length; i++)
	{
		output_arr[i] = Napi::Number::New(env, output[i]);
	}
	obj.Set("result", output_arr);
	obj.Set("result2", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::lastErrorMessage(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *result;
	try
	{
		result = last_error_message(this->dll);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::String::New(env, result));
	return obj;
}

Napi::Value Voicevox::voicevoxLoadOpenjtalkDict(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *dict_path = load_string(info, 0);
	VoicevoxResultCodeV13 resultCode = voicevox_load_openjtalk_dict(this->dll, dict_path);
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxTtsV13(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *text = load_string(info, 0);
	int64_t speaker_id = static_cast<int64_t>(load_uint32_t(info, 1));
	int output_binary_size;
	uint8_t *output_wav;
	VoicevoxResultCodeV13 resultCode = voicevox_tts_v13(this->dll, text, speaker_id, &output_binary_size, &output_wav);
	obj.Set("result", Napi::Buffer<uint8_t>::Copy(env, output_wav, output_binary_size));
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::voicevoxTtsFromKana(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *text = load_string(info, 0);
	int64_t speaker_id = static_cast<int64_t>(load_uint32_t(info, 1));
	int output_binary_size;
	uint8_t *output_wav;
	VoicevoxResultCodeV13 resultCode = voicevox_tts_from_kana(this->dll, text, speaker_id, &output_binary_size, &output_wav);
	obj.Set("result", Napi::Buffer<uint8_t>::Copy(env, output_wav, output_binary_size));
	obj.Set("resultCode", Napi::Number::New(env, resultCode));
	return obj;
}

Napi::Value Voicevox::initializeV11(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *root_dir_path = load_string(info, 0);
	bool use_gpu = load_bool(info, 1);
	int cpu_num_threads = static_cast<int>(load_uint32_t(info, 2));
	bool result;
	try
	{
		result = initialize_v11(this->dll, root_dir_path, use_gpu, cpu_num_threads);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::initializeV9(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	const char *root_dir_path = load_string(info, 0);
	bool use_gpu = load_bool(info, 1);
	bool result;
	try
	{
		result = initialize_v9(this->dll, root_dir_path, use_gpu);
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	obj.Set("result", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::yukarinSForwardV7(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array phonemeList = info[0].As<Napi::Array>();
	long speaker_id = static_cast<long>(load_uint32_t(info, 1));
	int length = static_cast<int>(phonemeList.Length());
	std::vector<long> phoneme_list(length, 0);
	for (int i = 0; i < length; i++)
	{
		bool lossless;
		Napi::Value phoneme_list_value = phonemeList[i];
		phoneme_list[i] = static_cast<long>(phoneme_list_value.As<Napi::BigInt>().Int64Value(&lossless));
	}
	bool result;
	std::vector<float> output(length, 0.0);
	try
	{
		result = yukarin_s_forward_v7(this->dll, length, phoneme_list.data(), &speaker_id, output.data());
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	Napi::Array output_arr = Napi::Array::New(env, length);
	for (int i = 0; i < length; i++)
	{
		output_arr[i] = Napi::Number::New(env, output[i]);
	}
	obj.Set("result", output_arr);
	obj.Set("result2", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::yukarinSaForwardV7(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array vowelPhonemeList = info[0].As<Napi::Array>();
	Napi::Array consonantPhonemeList = info[1].As<Napi::Array>();
	Napi::Array startAccentList = info[2].As<Napi::Array>();
	Napi::Array endAccentList = info[3].As<Napi::Array>();
	Napi::Array startAccentPhraseList = info[4].As<Napi::Array>();
	Napi::Array endAccentPhraseList = info[5].As<Napi::Array>();
	long speaker_id = static_cast<long>(load_uint32_t(info, 6));
	int length = vowelPhonemeList.Length();
	std::vector<long> vowel_phoneme_list(length, 0);
	std::vector<long> consonant_phrase_list(length, 0);
	std::vector<long> start_accent_list(length, 0);
	std::vector<long> end_accent_list(length, 0);
	std::vector<long> start_accent_phrase_list(length, 0);
	std::vector<long> end_accent_phrase_list(length, 0);
	for (int i = 0; i < length; i++)
	{
		bool lossless;
		Napi::Value vowel_phoneme_value = vowelPhonemeList[i];
		vowel_phoneme_list[i] = static_cast<long>(vowel_phoneme_value.As<Napi::BigInt>().Int64Value(&lossless));
		Napi::Value consonant_phrase_value = consonantPhonemeList[i];
		consonant_phrase_list[i] = static_cast<long>(consonant_phrase_value.As<Napi::BigInt>().Int64Value(&lossless));
		Napi::Value start_accent_value = startAccentList[i];
		start_accent_list[i] = static_cast<long>(start_accent_value.As<Napi::BigInt>().Int64Value(&lossless));
		Napi::Value end_accent_value = endAccentList[i];
		end_accent_list[i] = static_cast<long>(end_accent_value.As<Napi::BigInt>().Int64Value(&lossless));
		Napi::Value start_accent_phrase_value = startAccentPhraseList[i];
		start_accent_phrase_list[i] = static_cast<long>(start_accent_phrase_value.As<Napi::BigInt>().Int64Value(&lossless));
		Napi::Value end_accent_phrase_value = endAccentPhraseList[i];
		end_accent_phrase_list[i] = static_cast<long>(end_accent_phrase_value.As<Napi::BigInt>().Int64Value(&lossless));
	}
	bool result;
	std::vector<float> output(length, 0.0);
	try
	{
		result = yukarin_sa_forward_v7(this->dll, length, vowel_phoneme_list.data(), consonant_phrase_list.data(), start_accent_list.data(), end_accent_list.data(), start_accent_phrase_list.data(), end_accent_phrase_list.data(), &speaker_id, output.data());
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	Napi::Array output_arr = Napi::Array::New(env, length);
	for (int i = 0; i < length; i++)
	{
		output_arr[i] = Napi::Number::New(env, output[i]);
	}

	obj.Set("result", output_arr);
	obj.Set("result2", Napi::Boolean::New(env, result));
	return obj;
}

Napi::Value Voicevox::decodeForwardV7(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array f0_ = info[0].As<Napi::Array>();
	Napi::Array phoneme_arr = info[1].As<Napi::Array>();
	long speaker_id = static_cast<long>(load_uint32_t(info, 2));
	int length = static_cast<int>(f0_.Length());
	int phoneme_length = static_cast<int>(phoneme_arr.Length());
	std::vector<float> f0(length, 0.0);
	std::vector<float> phoneme(phoneme_length, 0.0);
	for (int i = 0; i < length; i++)
	{
		Napi::Value f0_value = f0_[i];
		f0[i] = f0_value.As<Napi::Number>().FloatValue();
	}
	for (int i = 0; i < phoneme_length; i++)
	{
		Napi::Value phoneme_value = phoneme_arr[i];
		phoneme[i] = phoneme_value.As<Napi::Number>().FloatValue();
	}
	bool result;
	std::vector<float> output(length * 256, 0.0);
	try
	{
		result = decode_forward(this->dll, length, phoneme_length, f0.data(), phoneme.data(), &speaker_id, output.data());
	}
	catch (const std::exception &e)
	{
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
		return obj;
	}
	Napi::Array output_arr = Napi::Array::New(env, length);
	for (int i = 0; i < length; i++)
	{
		output_arr[i] = Napi::Number::New(env, output[i]);
	}
	obj.Set("result", output_arr);
	obj.Set("result2", Napi::Boolean::New(env, result));
	return obj;
}
