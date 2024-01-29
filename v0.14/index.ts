import { VoicevoxAccelerationMode, VoicevoxCore, VoicevoxResultCodeV14 } from "../voicevox_core";
import { VoicevoxAudioQueryJson, VoicevoxError, VoicevoxMetaJson, VoicevoxSupportedDevicesJson, checkValidArray, checkValidNumber, checkValidOption, checkValidString, checkVoicevoxAudioQueryJson } from "../util";

const Core = Symbol("Core");

/**
 * voicevox_coreを利用してVOICEVOXを使う
 * @version 0.14.x
 */
export class Voicevox {
  [Core]: VoicevoxCore;
  /**
   * @param path libvoicevox_core.so, libvoicevox_core.solib, voicevox_core.dllを指すパス
   */
  constructor(path: string) {
    checkValidString(path, "path");
    this[Core] = new VoicevoxCore(path);
  }

  /**
   * voicevoxのバージョンを取得する。
   * @returns {Promise<string>} SemVerでフォーマットされたバージョン。
   */
  getVersion(): Promise<string> {
    return new Promise<string>((resolve) => {
      const { result } = this[Core].voicevoxGetVersionV0_14();
      resolve(result);
    });
  }

  /**
   * 初期化する
   * @param {VoicevoxInitializeOptions} options 初期化オプション
   * @returns {Promise<void>}
   */
  voicevoxInitializeV0_14(options: VoicevoxInitializeOptions): Promise<void> {
    return new Promise<void>((resolve) => {
      checkVoicevoxInitializeOptions(options);
      const { resultCode } = this[Core].voicevoxInitializeV0_14(options.accelerationMode, options.cpuNumThreads, options.loadAllModels, options.openJtalkDictDir);
      if (resultCode !== VoicevoxResultCodeV14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve();
    });
  }

  /**
   * モデルを読み込む
   * @param {number} speakerId 読み込むモデルの話者ID
   * @returns {Promise<void>}
   */
  voicevoxLoadModelV0_14(speakerId: number): Promise<void> {
    return new Promise<void>((resolve) => {
      checkValidNumber(speakerId, "speakerId", true);
      const { resultCode } = this[Core].voicevoxLoadModelV0_14(speakerId);
      if (resultCode !== VoicevoxResultCodeV14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve();
    });
  }
  /**
   * ハードウェアアクセラレーションがGPUモードか判定する
   * @return {Promise<boolean>} GPUモードならtrue、そうでないならfalse
   */
  voicevoxIsGpuModeV0_14(): Promise<boolean> {
    return new Promise<boolean>((resolve) => {
      const { result } = this[Core].voicevoxIsGpuModeV0_14();
      resolve(result);
    });
  }

  /**
   * 指定したspeaker_idのモデルが読み込まれているか判定する
   * @param speakerId 話者ID
   * @returns {Promise<boolean>} モデルが読み込まれているのであればtrue、そうでないならfalse
   */
  voicevoxIsModelLoadedV0_14(speakerId: number): Promise<boolean> {
    return new Promise<boolean>((resolve) => {
      checkValidNumber(speakerId, "speakerId", true);
      const { result } = this[Core].voicevoxIsModelLoadedV0_14(speakerId);
      resolve(result);
    });
  }

  /**
   * このライブラリの利用を終了し、確保しているリソースを解放する
   * @returns {Promise<void>}
   */
  voicevoxFinalizeV0_14(): Promise<void> {
    return new Promise<void>((resolve) => {
      this[Core].voicevoxFinalizeV0_14();
      resolve();
    });
  }

  /**
   * メタ情報を取得する
   * @returns {Promise<VoicevoxMetaJson>} メタ情報
   */
  voicevoxGetMetasJsonV0_14(): Promise<VoicevoxMetaJson> {
    return new Promise<VoicevoxMetaJson>((resolve) => {
      const { result } = this[Core].voicevoxGetMetasJsonV0_14();
      resolve(JSON.parse(result));
    });
  }

  /**
   * サポートデバイス情報を取得する
   * @returns {Promise<VoicevoxSupportedDevicesJson>} サポートデバイス情報
   */
  voicevoxGetSupportedDevicesJsonV0_14(): Promise<VoicevoxSupportedDevicesJson> {
    return new Promise<VoicevoxSupportedDevicesJson>((resolve) => {
      const { result } = this[Core].voicevoxGetSupportedDevicesJsonV0_14();
      resolve(JSON.parse(result));
    });
  }

  /**
   * 音素ごとの長さを推論する
   * @param {Array<bigint>} phoneme 音素データ
   * @param {number} speakerId 話者ID
   * @returns {Promise<Array<number>>} データ
   */
  voicevoxPredictDurationV0_14(phoneme: Array<bigint>, speakerId: number): Promise<Array<number>> {
    return new Promise<Array<number>>((resolve) => {
      checkValidArray(phoneme, "phoneme", "bigint");
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxPredictDurationV0_14(phoneme, speakerId);
      if (resultCode !== VoicevoxResultCodeV14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(result);
    });
  }

  /**
   * モーラごとのF0を推論する
   * @param {Array<bigint>} vowelPhoneme 母音の音素データ
   * @param {Array<bigint>} consonantPhoneme 子音の音素データ
   * @param {Array<bigint>} startAccent アクセントの開始位置のデータ
   * @param {Array<bigint>} endAccent アクセントの終了位置のデータ
   * @param {Array<bigint>} startAccentPhrase アクセント句の開始位置のデータ
   * @param {Array<bigint>} endAccentPhrase アクセント句の終了位置のデータ
   * @param {number} speakerId 話者ID
   * @returns {Promise<Array<number>>} データ
   */
  voicevoxPredictIntonationV0_14(vowelPhoneme: Array<bigint>, consonantPhoneme: Array<bigint>, startAccent: Array<bigint>, endAccent: Array<bigint>, startAccentPhrase: Array<bigint>, endAccentPhrase: Array<bigint>, speakerId: number): Promise<Array<number>> {
    return new Promise<Array<number>>((resolve) => {
      checkValidArray(vowelPhoneme, "vowelPhoneme", "bigint");
      checkValidArray(consonantPhoneme, "consonantPhoneme", "bigint");
      checkValidArray(startAccent, "startAccent", "bigint");
      checkValidArray(endAccent, "endAccent", "bigint");
      checkValidArray(startAccentPhrase, "startAccentPhrase", "bigint");
      checkValidArray(endAccentPhrase, "endAccentPhrase", "bigint");
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxPredictIntonationV0_14(vowelPhoneme, consonantPhoneme, startAccent, endAccent, startAccentPhrase, endAccentPhrase, speakerId);
      if (resultCode !== VoicevoxResultCodeV14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(result);
    });
  }

  /**
   * decodeを実行する
   * @param {Array<number>} f0 基本周波数
   * @param {Array<number>} phoneme 音素データ
   * @param {number} speakerId 話者ID
   * @returns {Promise<Array<number>>} データ
   */
  voicevoxDecodeV0_14(f0: Array<number>, phoneme: Array<number>, speakerId: number): Promise<Array<number>> {
    return new Promise<Array<number>>((resolve) => {
      checkValidArray(f0, "f0", "number", false);
      checkValidArray(phoneme, "phoneme", "number", false);
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxDecodeV0_14(f0, phoneme, speakerId);
      if (resultCode !== VoicevoxResultCodeV14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(result);
    });
  }

  /**
   * AudioQuery を実行する
   * @param {string} text テキスト
   * @param {number} speakerId 話者ID
   * @param {VoicevoxAudioQueryOptions} options AudioQueryのオプション
   * @returns {Promise<VoicevoxAudioQueryJson>} AudioQuery
   */
  voicevoxAudioQueryV0_14(text: string, speakerId: number, options: VoicevoxAudioQueryOptions): Promise<VoicevoxAudioQueryJson> {
    return new Promise<VoicevoxAudioQueryJson>((resolve) => {
      checkValidString(text, "text");
      checkValidNumber(speakerId, "speakerId", true);
      checkVoicevoxAudioQueryOptions(options);
      const { result, resultCode } = this[Core].voicevoxAudioQueryV0_14(text, speakerId, options.kana);
      if (resultCode !== VoicevoxResultCodeV14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * AudioQuery から音声合成する
   * @param {VoicevoxAudioQueryJson} audioQueryJson AudioQuery
   * @param {number} speakerId 話者ID
   * @param {VoicevoxSynthesisOptions} options AudioQueryから音声合成オプション
   * @returns {Promise<Buffer>} wav データ
   */
  voicevoxSynthesisV0_14(audioQueryJson: VoicevoxAudioQueryJson, speakerId: number, options: VoicevoxSynthesisOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      checkVoicevoxAudioQueryJson(audioQueryJson);
      checkValidNumber(speakerId, "speakerId", true);
      checkVoicevoxSynthesisOptions(options);
      const { result, resultCode } = this[Core].voicevoxSynthesisV0_14(JSON.stringify(audioQueryJson), speakerId, options.enableInterrogativeUpspeak);
      if (resultCode !== VoicevoxResultCodeV14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(result);
    });
  }

  /**
   * テキスト音声合成を実行する
   * @param {string} text テキスト
   * @param {number} speakerId 話者ID
   * @param {VoicevoxTtsOptions} options テキスト音声合成オプション
   * @returns {Promise<Buffer>} wav データ
   */
  voicevoxTtsV0_14(text: string, speakerId: number, options: VoicevoxTtsOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      checkValidString(text, "text");
      checkValidNumber(speakerId, "speakerId", true);
      checkVoicevoxTtsOptions(options);
      const { result, resultCode } = this[Core].voicevoxTtsV0_14(text, speakerId, options.enableInterrogativeUpspeak, options.kana);
      if (resultCode !== VoicevoxResultCodeV14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(result);
    });
  }
}

/**
 * 初期化オプション
 */
interface VoicevoxInitializeOptions {
  /**
   * ハードウェアアクセラレーションモード
   */
  accelerationMode: VoicevoxAccelerationMode;
  /**
   * CPU利用数を指定 0を指定すると環境に合わせたCPUが利用される
   */
  cpuNumThreads: number;
  /**
   * 全てのモデルを読み込む
   */
  loadAllModels: boolean;
  /**
   * open_jtalkの辞書ディレクトリ
   */
  openJtalkDictDir: string;
}

function checkVoicevoxInitializeOptions(obj: VoicevoxInitializeOptions) {
  checkValidOption(obj, "VoicevoxInitializeOptions", [
    ["accelerationMode", "number"],
    ["cpuNumThreads", "number"],
    ["loadAllModels", "boolean"],
    ["openJtalkDictDir", "string"],
  ]);
}

/**
 * Audio query のオプション
 */
interface VoicevoxAudioQueryOptions {
  /**
   * aquestalk形式のkanaとしてテキストを解釈する
   */
  kana: boolean;
}

function checkVoicevoxAudioQueryOptions(obj: VoicevoxAudioQueryOptions) {
  checkValidOption(obj, "VoicevoxAudioQueryOptions", [["kana", "boolean"]]);
}

interface VoicevoxSynthesisOptions {
  /**
   * 疑問文の調整を有効にする
   */
  enableInterrogativeUpspeak: boolean;
}

function checkVoicevoxSynthesisOptions(obj: VoicevoxSynthesisOptions) {
  checkValidOption(obj, "VoicevoxSynthesisOptions", [["enableInterrogativeUpspeak", "boolean"]]);
}

/**
 * テキスト音声合成オプション
 */
interface VoicevoxTtsOptions {
  /**
   * aquestalk形式のkanaとしてテキストを解釈する
   */
  kana: boolean;
  /**
   * 疑問文の調整を有効にする
   */
  enableInterrogativeUpspeak: boolean;
}

function checkVoicevoxTtsOptions(obj: VoicevoxTtsOptions) {
  checkValidOption(obj, "VoicevoxTtsOptions", [
    ["enableInterrogativeUpspeak", "boolean"],
    ["kana", "boolean"],
  ]);
}
