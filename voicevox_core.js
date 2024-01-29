module.exports.VoicevoxCore = exports.VoicevoxCore = require("bindings")("voicevox");
exports.VoicevoxResultCodeV12 = exports.VoicevoxResultCodeV14 = exports.VoicevoxUserDictWordType = exports.VoicevoxAccelerationMode = void 0;
var VoicevoxAccelerationMode;
(function (VoicevoxAccelerationMode) {
  VoicevoxAccelerationMode[(VoicevoxAccelerationMode["VOICEVOX_ACCELERATION_MODE_AUTO"] = 0)] = "VOICEVOX_ACCELERATION_MODE_AUTO";
  VoicevoxAccelerationMode[(VoicevoxAccelerationMode["VOICEVOX_ACCELERATION_MODE_CPU"] = 1)] = "VOICEVOX_ACCELERATION_MODE_CPU";
  VoicevoxAccelerationMode[(VoicevoxAccelerationMode["VOICEVOX_ACCELERATION_MODE_GPU"] = 2)] = "VOICEVOX_ACCELERATION_MODE_GPU";
})(VoicevoxAccelerationMode || (exports.VoicevoxAccelerationMode = VoicevoxAccelerationMode = {}));
var VoicevoxUserDictWordType;
(function (VoicevoxUserDictWordType) {
  VoicevoxUserDictWordType[(VoicevoxUserDictWordType["VOICEVOX_USER_DICT_WORD_TYPE_PROPER_NOUN"] = 0)] = "VOICEVOX_USER_DICT_WORD_TYPE_PROPER_NOUN";
  VoicevoxUserDictWordType[(VoicevoxUserDictWordType["VOICEVOX_USER_DICT_WORD_TYPE_COMMON_NOUN"] = 1)] = "VOICEVOX_USER_DICT_WORD_TYPE_COMMON_NOUN";
  VoicevoxUserDictWordType[(VoicevoxUserDictWordType["VOICEVOX_USER_DICT_WORD_TYPE_VERB"] = 2)] = "VOICEVOX_USER_DICT_WORD_TYPE_VERB";
  VoicevoxUserDictWordType[(VoicevoxUserDictWordType["VOICEVOX_USER_DICT_WORD_TYPE_ADJECTIVE"] = 3)] = "VOICEVOX_USER_DICT_WORD_TYPE_ADJECTIVE";
  VoicevoxUserDictWordType[(VoicevoxUserDictWordType["VOICEVOX_USER_DICT_WORD_TYPE_SUFFIX"] = 4)] = "VOICEVOX_USER_DICT_WORD_TYPE_SUFFIX";
})(VoicevoxUserDictWordType || (exports.VoicevoxUserDictWordType = VoicevoxUserDictWordType = {}));
var VoicevoxResultCodeV14;
(function (VoicevoxResultCodeV14) {
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_OK"] = 0)] = "VOICEVOX_RESULT_OK";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_NOT_LOADED_OPENJTALK_DICT_ERROR"] = 1)] = "VOICEVOX_RESULT_NOT_LOADED_OPENJTALK_DICT_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_LOAD_MODEL_ERROR"] = 2)] = "VOICEVOX_RESULT_LOAD_MODEL_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_GET_SUPPORTED_DEVICES_ERROR"] = 3)] = "VOICEVOX_RESULT_GET_SUPPORTED_DEVICES_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_GPU_SUPPORT_ERROR"] = 4)] = "VOICEVOX_RESULT_GPU_SUPPORT_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_LOAD_METAS_ERROR"] = 5)] = "VOICEVOX_RESULT_LOAD_METAS_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_UNINITIALIZED_STATUS_ERROR"] = 6)] = "VOICEVOX_RESULT_UNINITIALIZED_STATUS_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_INVALID_SPEAKER_ID_ERROR"] = 7)] = "VOICEVOX_RESULT_INVALID_SPEAKER_ID_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_INVALID_MODEL_INDEX_ERROR"] = 8)] = "VOICEVOX_RESULT_INVALID_MODEL_INDEX_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_INFERENCE_ERROR"] = 9)] = "VOICEVOX_RESULT_INFERENCE_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_EXTRACT_FULL_CONTEXT_LABEL_ERROR"] = 10)] = "VOICEVOX_RESULT_EXTRACT_FULL_CONTEXT_LABEL_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_INVALID_UTF8_INPUT_ERROR"] = 11)] = "VOICEVOX_RESULT_INVALID_UTF8_INPUT_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_PARSE_KANA_ERROR"] = 12)] = "VOICEVOX_RESULT_PARSE_KANA_ERROR";
  VoicevoxResultCodeV14[(VoicevoxResultCodeV14["VOICEVOX_RESULT_INVALID_AUDIO_QUERY_ERROR"] = 13)] = "VOICEVOX_RESULT_INVALID_AUDIO_QUERY_ERROR";
})(VoicevoxResultCodeV14 || (exports.VoicevoxResultCodeV14 = VoicevoxResultCodeV14 = {}));
var VoicevoxResultCodeV12;
(function (VoicevoxResultCodeV12) {
  VoicevoxResultCodeV12[(VoicevoxResultCodeV12["VOICEVOX_RESULT_SUCCEED"] = 0)] = "VOICEVOX_RESULT_SUCCEED";
  VoicevoxResultCodeV12[(VoicevoxResultCodeV12["VOICEVOX_RESULT_NOT_LOADED_OPENJTALK_DICT"] = 1)] = "VOICEVOX_RESULT_NOT_LOADED_OPENJTALK_DICT";
})(VoicevoxResultCodeV12 || (exports.VoicevoxResultCodeV12 = VoicevoxResultCodeV12 = {}));

