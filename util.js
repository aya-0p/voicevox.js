"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.checkVoicevoxMoraJson = exports.checkVoicevoxAccentPhraseJson = exports.checkVoicevoxAudioQueryJson = exports.checkValidArray = exports.checkValidObject = exports.checkValidString = exports.checkValidBoolean = exports.checkValidBigint = exports.checkValidNumber = exports.checkValidOption = exports.uuidToBuffer = exports.bufferToUuid = exports.VoicevoxError = exports.VoicevoxJsError = void 0;
/**
 * voicevox.jsにより生成されたエラー
 */
class VoicevoxJsError extends Error {
}
exports.VoicevoxJsError = VoicevoxJsError;
/**
 * voicevox coreにより生成されたエラー
 */
class VoicevoxError extends Error {
}
exports.VoicevoxError = VoicevoxError;
/**
 * Buffer形式のuuidを文字列に変換
 * @example
 * ```js
 * bufferToUuid(uuid); // "01234567-89ab-cdef-0123-456789abcdef"
 * ```
 */
function bufferToUuid(buf) {
    if (buf.length !== 16)
        throw new VoicevoxJsError("有効なBufferUuidではありません。");
    let str = "";
    for (let i = 0; i < buf.length; i++) {
        str += buf[i].toString(16).padStart(2, "0");
        if (i === 4 || i === 6 || i === 8 || i === 10)
            str += "-";
    }
    return str;
}
exports.bufferToUuid = bufferToUuid;
/**
 * 文字列のuuidをBuffer形式に変換
 * @example
 * ```js
 * uuidToBuffer(uuid); // <Buffer 01 23 45 67 89 ab cd ef 01 23 45 67 89 ab cd ef>
 * ```
 */
function uuidToBuffer(uuid) {
    const t = Buffer.from(uuid.replaceAll("-", ""), "hex");
    if (t.length !== 16)
        throw new VoicevoxJsError("uuidが不正な値です");
    const buf = Buffer.alloc(16).fill(0);
    for (let i = 15; i >= 0; i--) {
        buf[i] = t[i];
    }
    return buf;
}
exports.uuidToBuffer = uuidToBuffer;
function checkValidOption(obj, interfaceName, options) {
    if (obj == null)
        throw new VoicevoxJsError(`有効な${interfaceName}ではありません(存在しない)`);
    for (const [name, type, isInteger] of options) {
        if (typeof obj[name] !== type)
            throw new VoicevoxJsError(`有効な${interfaceName}ではありません(${String(name)}が${type}でない)`);
        if (type === "number" && isInteger && !Number.isSafeInteger(obj[name]))
            throw new VoicevoxJsError(`有効な${interfaceName}ではありません(${String(name)}が整数でない)`);
    }
}
exports.checkValidOption = checkValidOption;
function checkValidNumber(num, name, isInteger) {
    if (typeof num !== "number")
        throw new VoicevoxJsError(`${name}がnumberではありません`);
    if (isInteger && !Number.isSafeInteger(num))
        throw new VoicevoxJsError(`${name}が整数ではありません`);
}
exports.checkValidNumber = checkValidNumber;
function checkValidBigint(num, name) {
    if (typeof num !== "bigint")
        throw new VoicevoxJsError(`${name}がbigintではありません`);
}
exports.checkValidBigint = checkValidBigint;
function checkValidBoolean(bol, name) {
    if (typeof bol !== "boolean")
        throw new VoicevoxJsError(`${name}がbooleanではありません`);
}
exports.checkValidBoolean = checkValidBoolean;
function checkValidString(str, name) {
    if (typeof str !== "string")
        throw new VoicevoxJsError(`${name}がstringではありません`);
}
exports.checkValidString = checkValidString;
function checkValidObject(obj, name, src, srcname) {
    if (!(obj instanceof src))
        throw new VoicevoxJsError(`${name}が${srcname}ではありません`);
}
exports.checkValidObject = checkValidObject;
function checkValidArray(arr, name, type, isInteger) {
    if (arr == null)
        throw new VoicevoxJsError(`有効な${name}ではありません(存在しない)`);
    if (!(arr instanceof Array))
        throw new VoicevoxJsError(`有効な${name}ではありません(Arrayでない)`);
    try {
        for (const obj of arr) {
            switch (type) {
                case "string":
                    checkValidString(obj, "中身");
                    break;
                case "number":
                    checkValidNumber(obj, "中身", isInteger);
                    break;
                case "bigint":
                    checkValidBigint(obj, "中身");
                    break;
            }
        }
    }
    catch (e) {
        throw new VoicevoxJsError(`有効な${name}ではありません(${e.message})`);
    }
}
exports.checkValidArray = checkValidArray;
function checkVoicevoxAudioQueryJson(obj) {
    checkValidOption(obj, "VoicevoxAudioQueryJson", [
        ["intonation_scale", "number"],
        ["output_sampling_rate", "number", true],
        ["output_stereo", "boolean"],
        ["pitch_scale", "number"],
        ["post_phoneme_length", "number"],
        ["pre_phoneme_length", "number"],
        ["speed_scale", "number"],
        ["volume_scale", "number"],
    ]);
    checkVoicevoxAccentPhraseJson(obj.accent_phrases);
}
exports.checkVoicevoxAudioQueryJson = checkVoicevoxAudioQueryJson;
function checkVoicevoxAccentPhraseJson(arr) {
    if (!(arr instanceof Array))
        throw new VoicevoxJsError("有効なVoicevoxAccentPhraseJsonではありません(配列でない)");
    for (const obj of arr) {
        checkValidOption(obj, "VoicevoxAccentPhraseJson", [
            ["accent", "number", true],
            ["is_interrogative", "boolean"],
        ]);
        if (!(obj.moras instanceof Array))
            throw new VoicevoxJsError("有効なVoicevoxAccentPhraseJsonではありません(一部の要素のmorasが配列でない)");
        for (const obj2 of obj.moras) {
            checkVoicevoxMoraJson(obj2);
        }
        if (obj.pause_mora !== null)
            checkVoicevoxMoraJson(obj.pause_mora);
    }
}
exports.checkVoicevoxAccentPhraseJson = checkVoicevoxAccentPhraseJson;
function checkVoicevoxMoraJson(obj) {
    checkValidOption(obj, "VoicevoxMoraJson", [
        ["pitch", "number"],
        ["text", "string"],
        ["vowel", "string"],
        ["vowel_length", "number"],
    ]);
    if (obj.consonant !== null && typeof obj.consonant !== "string")
        throw new VoicevoxJsError("有効なVoicevoxMoraJsonではありません(consonantがstringまたはnullでない)");
    if (obj.consonant !== null && typeof obj.consonant_length !== "number")
        throw new VoicevoxJsError("有効なVoicevoxMoraJsonではありません(consonant_lengthがnumberまたはnullでない)");
}
exports.checkVoicevoxMoraJson = checkVoicevoxMoraJson;
