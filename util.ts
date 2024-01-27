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

export function checkValidBoolean(bol: boolean, name: string) {
  if (typeof bol !== "boolean") throw new VoicevoxJsError(`${name}がbooleanではありません`);
}

export function checkValidString(str: string, name: string) {
  if (typeof str !== "string") throw new VoicevoxJsError(`${name}がstringではありません`);
}

export function checkValidObject(obj: any, name: string, src: any, srcname: string) {
  if (!(obj instanceof src)) throw new VoicevoxJsError(`${name}が${srcname}ではありません`);
}