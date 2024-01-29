import { VoicevoxAccelerationModeV0_14, VoicevoxCore, VoicevoxResultCodeV0_14, VoicevoxResultCodeV0_15 } from "../voicevox_core";
import { Core, VoicevoxAccentPhraseJson, VoicevoxAudioQueryJson, VoicevoxError, VoicevoxMetaJson, VoicevoxSupportedDevicesJson, checkValidArray, checkValidNumber, checkValidOption, checkValidString, checkVoicevoxAccentPhraseJson, checkVoicevoxAudioQueryJson } from "../util";

/**
 * voicevox_coreを利用してVOICEVOXを使う
 * @description このバージョンは正式版ではありません
 * @version 0.15.x
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
  voicevoxInitialize(options: VoicevoxInitializeOptions): Promise<void> {
    return new Promise<void>((resolve) => {
      checkVoicevoxInitializeOptions(options);
      const { resultCode } = this[Core].voicevoxInitializeV0_14(options.accelerationMode, options.cpuNumThreads, options.loadAllModels, options.openJtalkDictDir);
      if (resultCode !== VoicevoxResultCodeV0_14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve();
    });
  }

  /**
   * モデルを読み込む
   * @param {number} speakerId 読み込むモデルの話者ID
   * @returns {Promise<void>}
   */
  voicevoxLoadModel(speakerId: number): Promise<void> {
    return new Promise<void>((resolve) => {
      checkValidNumber(speakerId, "speakerId", true);
      const { resultCode } = this[Core].voicevoxLoadModelV0_14(speakerId);
      if (resultCode !== VoicevoxResultCodeV0_14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve();
    });
  }
  /**
   * ハードウェアアクセラレーションがGPUモードか判定する
   * @return {Promise<boolean>} GPUモードならtrue、そうでないならfalse
   */
  voicevoxIsGpuMode(): Promise<boolean> {
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
  voicevoxIsModelLoaded(speakerId: number): Promise<boolean> {
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
  voicevoxFinalize(): Promise<void> {
    return new Promise<void>((resolve) => {
      this[Core].voicevoxFinalizeV0_14();
      resolve();
    });
  }

  /**
   * メタ情報を取得する
   * @returns {Promise<VoicevoxMetaJson>} メタ情報
   */
  voicevoxGetMetasJson(): Promise<VoicevoxMetaJson> {
    return new Promise<VoicevoxMetaJson>((resolve) => {
      const { result } = this[Core].voicevoxGetMetasJsonV0_14();
      resolve(JSON.parse(result));
    });
  }

  /**
   * サポートデバイス情報を取得する
   * @returns {Promise<VoicevoxSupportedDevicesJson>} サポートデバイス情報
   */
  voicevoxGetSupportedDevicesJson(): Promise<VoicevoxSupportedDevicesJson> {
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
  voicevoxPredictDuration(phoneme: Array<bigint>, speakerId: number): Promise<Array<number>> {
    return new Promise<Array<number>>((resolve) => {
      checkValidArray(phoneme, "phoneme", "bigint");
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxPredictDurationV0_14(phoneme, speakerId);
      if (resultCode !== VoicevoxResultCodeV0_14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
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
  voicevoxPredictIntonation(vowelPhoneme: Array<bigint>, consonantPhoneme: Array<bigint>, startAccent: Array<bigint>, endAccent: Array<bigint>, startAccentPhrase: Array<bigint>, endAccentPhrase: Array<bigint>, speakerId: number): Promise<Array<number>> {
    return new Promise<Array<number>>((resolve) => {
      checkValidArray(vowelPhoneme, "vowelPhoneme", "bigint");
      checkValidArray(consonantPhoneme, "consonantPhoneme", "bigint");
      checkValidArray(startAccent, "startAccent", "bigint");
      checkValidArray(endAccent, "endAccent", "bigint");
      checkValidArray(startAccentPhrase, "startAccentPhrase", "bigint");
      checkValidArray(endAccentPhrase, "endAccentPhrase", "bigint");
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxPredictIntonationV0_14(vowelPhoneme, consonantPhoneme, startAccent, endAccent, startAccentPhrase, endAccentPhrase, speakerId);
      if (resultCode !== VoicevoxResultCodeV0_14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
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
  voicevoxDecode(f0: Array<number>, phoneme: Array<number>, speakerId: number): Promise<Array<number>> {
    return new Promise<Array<number>>((resolve) => {
      checkValidArray(f0, "f0", "number", false);
      checkValidArray(phoneme, "phoneme", "number", false);
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxDecodeV0_14(f0, phoneme, speakerId);
      if (resultCode !== VoicevoxResultCodeV0_14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
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
  voicevoxAudioQuery(text: string, speakerId: number, options: VoicevoxAudioQueryOptions): Promise<VoicevoxAudioQueryJson> {
    return new Promise<VoicevoxAudioQueryJson>((resolve) => {
      checkValidString(text, "text");
      checkValidNumber(speakerId, "speakerId", true);
      checkVoicevoxAudioQueryOptions(options);
      const { result, resultCode } = this[Core].voicevoxAudioQueryV0_14(text, speakerId, options.kana);
      if (resultCode !== VoicevoxResultCodeV0_14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * `accent_phrases` を実行する
   * @param {string} text テキスト
   * @param {number} speakerId 話者ID
   * @param {VoicevoxAccentPhrasesOptions} options `accentPhrases`のオプション
   * @return {Promise<Array<VoicevoxAccentPhraseJson>>} アクセント句の情報の配列
   */
  voicevoxAccentPhrases(text: string, speakerId: number, options: VoicevoxAccentPhrasesOptions): Promise<Array<VoicevoxAccentPhraseJson>> {
    return new Promise<Array<VoicevoxAccentPhraseJson>>((resolve) => {
      checkValidString(text, "text");
      checkValidNumber(speakerId, "speakerId", true);
      checkVoicevoxAccentPhrasesOptions(options);
      const { result, resultCode } = this[Core].voicevoxAccentPhrasesV0_15(text, speakerId, options.kana);
      if (resultCode !== VoicevoxResultCodeV0_15.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * アクセント句の音素長を変更する
   * @param {Array<VoicevoxAccentPhraseJson>} accentPhrasesJson アクセント句の配列
   * @param speakerId 話者ID
   * @return {Promise<Array<VoicevoxAccentPhraseJson>>} 音素長が変更されたアクセント句の情報の配列
   */
  voicevoxMoraLength(accentPhrases: Array<VoicevoxAccentPhraseJson>, speakerId: number): Promise<Array<VoicevoxAccentPhraseJson>> {
    return new Promise<Array<VoicevoxAccentPhraseJson>>((resolve) => {
      checkVoicevoxAccentPhraseJson(accentPhrases);
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxMoraLengthV0_15(JSON.stringify(accentPhrases), speakerId);
      if (resultCode !== VoicevoxResultCodeV0_15.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * アクセント句の音高を変更する
   * @param {Array<VoicevoxAccentPhraseJson>} accentPhrasesJson アクセント句の配列
   * @param speakerId 話者ID
   * @return {Promise<Array<VoicevoxAccentPhraseJson>>} 音高が変更されたアクセント句の情報の配列
   */
  voicevoxMoraPitch(accentPhrases: Array<VoicevoxAccentPhraseJson>, speakerId: number): Promise<Array<VoicevoxAccentPhraseJson>> {
    return new Promise<Array<VoicevoxAccentPhraseJson>>((resolve) => {
      checkVoicevoxAccentPhraseJson(accentPhrases);
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxMoraPitchV0_15(JSON.stringify(accentPhrases), speakerId);
      if (resultCode !== VoicevoxResultCodeV0_15.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * アクセント句の音高・音素長を変更する
   * @param {Array<VoicevoxAccentPhraseJson>} accentPhrasesJson アクセント句の配列
   * @param speakerId 話者ID
   * @return {Promise<Array<VoicevoxAccentPhraseJson>>} 音高・音素長が変更されたアクセント句の情報の配列
   */
  voicevoxMoraData(accentPhrases: Array<VoicevoxAccentPhraseJson>, speakerId: number): Promise<Array<VoicevoxAccentPhraseJson>> {
    return new Promise<Array<VoicevoxAccentPhraseJson>>((resolve) => {
      checkVoicevoxAccentPhraseJson(accentPhrases);
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxMoraDataV0_15(JSON.stringify(accentPhrases), speakerId);
      if (resultCode !== VoicevoxResultCodeV0_15.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
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
  voicevoxSynthesis(audioQueryJson: VoicevoxAudioQueryJson, speakerId: number, options: VoicevoxSynthesisOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      checkVoicevoxAudioQueryJson(audioQueryJson);
      checkValidNumber(speakerId, "speakerId", true);
      checkVoicevoxSynthesisOptions(options);
      const { result, resultCode } = this[Core].voicevoxSynthesisV0_14(JSON.stringify(audioQueryJson), speakerId, options.enableInterrogativeUpspeak);
      if (resultCode !== VoicevoxResultCodeV0_14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
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
  voicevoxTts(text: string, speakerId: number, options: VoicevoxTtsOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      checkValidString(text, "text");
      checkValidNumber(speakerId, "speakerId", true);
      checkVoicevoxTtsOptions(options);
      const { result, resultCode } = this[Core].voicevoxTtsV0_14(text, speakerId, options.enableInterrogativeUpspeak, options.kana);
      if (resultCode !== VoicevoxResultCodeV0_14.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessageV0_12(resultCode).result);
      resolve(result);
    });
  }

  /**
   * デフォルトの `accent_phrases` のオプションを生成する
   * @return デフォルト値が設定された `accent_phrases` のオプション
   */
  static voicevoxMakeDefaultAccentPhrasesOptions(): VoicevoxAccentPhrasesOptions {
    return {
      kana: false,
    };
  }

  static voicevoxMakeDefaultInitializeOptions(): VoicevoxInitializeOptions {
    return {
      cpuNumThreads: 0,
      accelerationMode: VoicevoxAccelerationModeV0_14.VOICEVOX_ACCELERATION_MODE_AUTO,
      loadAllModels: true,
      openJtalkDictDir: "",
    }
  }

  /**
   * デフォルトの synthesis のオプションを生成する
   * @return デフォルト値が設定された synthesis のオプション
   */
  static voicevoxMakeDefaultSynthesisOptions(): VoicevoxSynthesisOptions {
    return {
      enableInterrogativeUpspeak: false,
    };
  }

  /**
   * デフォルトの AudioQuery のオプションを生成する
   * @return デフォルト値が設定された AudioQuery オプション
   */
  static voicevoxMakeDefaultAudioQueryOptions(): VoicevoxAudioQueryOptions {
    return {
      kana: false,
    };
  }

  /**
   * デフォルトのテキスト音声合成オプションを生成する
   * @return テキスト音声合成オプション
   */
  static voicevoxMakeDefaultTtsOptions(): VoicevoxTtsOptions {
    return {
      kana: false,
      enableInterrogativeUpspeak: false,
    };
  }
}

/**
 * 初期化オプション
 */
interface VoicevoxInitializeOptions {
  /**
   * ハードウェアアクセラレーションモード
   */
  accelerationMode: VoicevoxAccelerationModeV0_14;
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

interface VoicevoxAccentPhrasesOptions {
  /**
   * aquestalk形式のkanaとしてテキストを解釈する
   */
  kana: boolean;
}

function checkVoicevoxAccentPhrasesOptions(obj: VoicevoxAccentPhrasesOptions) {
  checkValidOption(obj, "VoicevoxAccentPhrasesOptions", [["kana", "boolean"]]);
}
