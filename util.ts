/**
 * voicevox.jsにより生成されたエラー
 */
export class VoicevoxJsError extends Error {}
/**
 * voicevox coreにより生成されたエラー
 */
export class VoicevoxError extends Error {}
/**
 * Buffer形式のuuidを文字列に変換
 * @example
 * ```js
 * bufferToUuid(uuid); // "01234567-89ab-cdef-0123-456789abcdef"
 * ```
 */
export function bufferToUuid(buf: Buffer) {
  if (buf.length !== 16) throw new VoicevoxJsError("有効なBufferUuidではありません。");
  let str = "";
  for (let i = 0; i < buf.length; i++) {
    str += buf[i].toString(16).padStart(2, "0");
    if (i === 4 || i === 6 || i === 8 || i === 10) str += "-";
  }
  return str;
}

/**
 * 文字列のuuidをBuffer形式に変換
 * @example
 * ```js
 * uuidToBuffer(uuid); // <Buffer 01 23 45 67 89 ab cd ef 01 23 45 67 89 ab cd ef>
 * ```
 */
export function uuidToBuffer(uuid: string) {
  const t = Buffer.from(uuid.replaceAll("-", ""), "hex");
  if (t.length !== 16) throw new VoicevoxJsError("uuidが不正な値です");
  const buf = Buffer.alloc(16).fill(0);
  for (let i = 15; i >= 0; i--) {
    buf[i] = t[i];
  }
  return buf;
}

export function checkValidOption<T extends { [key: string]: any }>(obj: T, interfaceName: string, options: Array<[keyof T, "boolean" | "number" | "string", true?]>) {
  if (obj == null) throw new VoicevoxJsError(`有効な${interfaceName}ではありません(存在しない)`);
  for (const [name, type, isInteger] of options) {
    if (typeof obj[name] !== type) throw new VoicevoxJsError(`有効な${interfaceName}ではありません(${String(name)}が${type}でない)`);
    if (type === "number" && isInteger && !Number.isSafeInteger(obj[name])) throw new VoicevoxJsError(`有効な${interfaceName}ではありません(${String(name)}が整数でない)`);
  }
}

export function checkValidNumber(num: number, name: string, isInteger: boolean) {
  if (typeof num !== "number") throw new VoicevoxJsError(`${name}がnumberではありません`);
  if (isInteger && !Number.isSafeInteger(num)) throw new VoicevoxJsError(`${name}が整数ではありません`);
}

export function checkValidBigint(num: bigint, name: string) {
  if (typeof num !== "bigint") throw new VoicevoxJsError(`${name}がbigintではありません`);
}

export function checkValidBoolean(bol: boolean, name: string) {
  if (typeof bol !== "boolean") throw new VoicevoxJsError(`${name}がbooleanではありません`);
}

export function checkValidString(str: string, name: string) {
  if (typeof str !== "string") throw new VoicevoxJsError(`${name}がstringではありません`);
}

export function checkValidObject(obj: any, name: string, src: any, srcname: string) {
  if (!(obj instanceof src)) throw new VoicevoxJsError(`${name}が${srcname}ではありません`);
}

export function checkValidArray<T extends string | number | bigint>(arr: Array<T>, name: string, type: "string" | "number" | "bigint", isInteger?: boolean) {
  if (arr == null) throw new VoicevoxJsError(`有効な${name}ではありません(存在しない)`);
  if (!(arr instanceof Array)) throw new VoicevoxJsError(`有効な${name}ではありません(Arrayでない)`);
  try {
    for (const obj of arr) {
      switch (type) {
        case "string":
          checkValidString(obj as any, "中身");
          break;
        case "number":
          checkValidNumber(obj as any, "中身", isInteger as boolean);
          break;
        case "bigint":
          checkValidBigint(obj as any, "中身");
          break;
      }
    }
  } catch (e: any) {
    throw new VoicevoxJsError(`有効な${name}ではありません(${e.message})`);
  }
}

export interface VoicevoxSupportedDevicesJson {
  cpu: boolean;
  cuda: boolean;
  dml: boolean;
}

export interface VoicevoxMetaJson {
  name: string;
  styles: Array<VoicevoxStyleJson>;
  version: string;
  speaker_uuid: string;
}

export interface VoicevoxStyleJson {
  id: number;
  name: string;
}

export interface VoicevoxAudioQueryJson {
  accent_phrases: Array<VoicevoxAccentPhraseJson>;
  speed_scale: number;
  pitch_scale: number;
  intonation_scale: number;
  volume_scale: number;
  pre_phoneme_length: number;
  post_phoneme_length: number;
  output_sampling_rate: number;
  output_stereo: boolean;
  kana: string;
}

export function checkVoicevoxAudioQueryJson(obj: VoicevoxAudioQueryJson) {
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

export interface VoicevoxAccentPhraseJson {
  moras: Array<VoicevoxMoraJson>;
  accent: number;
  pause_mora: VoicevoxMoraJson | null;
  is_interrogative: boolean;
}

export function checkVoicevoxAccentPhraseJson(arr: Array<VoicevoxAccentPhraseJson>) {
  if (!(arr instanceof Array)) throw new VoicevoxJsError("有効なVoicevoxAccentPhraseJsonではありません(配列でない)");
  for (const obj of arr) {
    checkValidOption(obj, "VoicevoxAccentPhraseJson", [
      ["accent", "number", true],
      ["is_interrogative", "boolean"],
    ]);
    if (!(obj.moras instanceof Array)) throw new VoicevoxJsError("有効なVoicevoxAccentPhraseJsonではありません(一部の要素のmorasが配列でない)");
    for (const obj2 of obj.moras) {
      checkVoicevoxMoraJson(obj2);
    }
    if (obj.pause_mora !== null) checkVoicevoxMoraJson(obj.pause_mora);
  }
}

export interface VoicevoxMoraJson {
  text: string;
  consonant: string | null;
  consonant_length: number | null;
  vowel: string;
  vowel_length: number;
  pitch: number;
}

export function checkVoicevoxMoraJson(obj: VoicevoxMoraJson) {
  checkValidOption(obj, "VoicevoxMoraJson", [
    ["pitch", "number"],
    ["text", "string"],
    ["vowel", "string"],
    ["vowel_length", "number"],
  ]);
  if (obj.consonant !== null && typeof obj.consonant !== "string") throw new VoicevoxJsError("有効なVoicevoxMoraJsonではありません(consonantがstringまたはnullでない)");
  if (obj.consonant !== null && typeof obj.consonant_length !== "number") throw new VoicevoxJsError("有効なVoicevoxMoraJsonではありません(consonant_lengthがnumberまたはnullでない)");
}
