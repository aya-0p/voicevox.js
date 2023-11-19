import { VoicevoxCore, VoicevoxResultCode, VoicevoxAccelerationMode, VoicevoxUserDictWordType } from "./voicevox_core";

export * from "./voicevox_core";

const Pointer = Symbol("Pointer");
const Core = Symbol("Core");
const Deleted = Symbol("Deleted");

/**
 * voicevox_coreを利用してVOICEVOXを使う
 */
export class Voicevox {
  [Core]: VoicevoxCore;
  #openJtalkPointerCounter: number = 0;
  #voiceModelCounter: number = 0;
  #synthesizerPointer: number = 0;
  #userDictCounter: number = 0;
  /**
   * @param path libvoicevox_core.so, libvoicevox_core.solib, voicevox_core.dllへのパス
   */
  constructor(path: string) {
    this[Core] = new VoicevoxCore(path);
  }

  /**
   * OpenJtalkRc を<b>構築</b>(_construct_)する。
   *
   * 解放は voicevoxOpenJtalkRcDelete で行う。
   *
   * @param {string} openJtalkDicDir 辞書ディレクトリを指すパス
   * @returns {Promise<VoicevoxOpenJtalkRc>}
   *
   * @example
   * ```js
   * voicevoxOpenJtalkRcNew("/home/user/open_jtalk_dic_utf_8-1.11");
   * ```
   */
  voicevoxOpenJtalkRcNew(openJtalkDicDir: string): Promise<VoicevoxOpenJtalkRc> {
    return new Promise<VoicevoxOpenJtalkRc>((resolve) => {
      if (typeof openJtalkDicDir !== "string") throw "openJtalkDicDirが文字列ではありません";
      const openJtalkPointerName = this.#openJtalkPointerCounter;
      this.#openJtalkPointerCounter++;
      const { resultCode } = this[Core].voicevoxOpenJtalkRcNew(openJtalkDicDir, openJtalkPointerName);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(new VoicevoxOpenJtalkRc(this, openJtalkPointerName));
    });
  }

  /**
   * voicevoxのバージョンを取得する。
   * @returns {Promise<string>} SemVerでフォーマットされたバージョン。
   */
  voicevoxGetVersion(): Promise<string> {
    return new Promise<string>((resolve) => {
      const { result } = this[Core].voicevoxGetVersion();
      resolve(result);
    });
  }

  /**
   * VVMファイルから VoicevoxVoiceModel を<b>構築</b>(_construct_)する。
   *
   * @param {string} path vvmファイルへのUTF-8のファイルパス
   *
   * @returns {Promise<VoicevoxVoiceModel>}
   */
  voicevoxVoiceModelNewFromPath(path: string): Promise<VoicevoxVoiceModel> {
    return new Promise<VoicevoxVoiceModel>((resolve) => {
      if (typeof path !== "string") throw "pathが文字列ではありません";
      const modelPonterName = this.#voiceModelCounter;
      this.#voiceModelCounter++;
      const { resultCode } = this[Core].voicevoxVoiceModelNewFromPath(path, modelPonterName);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(new VoicevoxVoiceModel(this, modelPonterName));
    });
  }

  /**
   * VoicevoxSynthesizer を<b>構築</b>(_construct_)する。
   *
   * @param {VoicevoxOpenJtalkRc} openJtalkRc Open JTalkのオブジェクト
   * @param {VoicevoxInitializeOptions} options オプション
   *
   * @returns {Promise<VoicevoxSynthesizer>}
   */
  voicevoxSynthesizerNew(openJtalkRc: VoicevoxOpenJtalkRc, options: VoicevoxInitializeOptions): Promise<VoicevoxSynthesizer> {
    return new Promise<VoicevoxSynthesizer>((resolve) => {
      if (!(openJtalkRc instanceof VoicevoxOpenJtalkRc)) throw "openJtalkRcがVoicevoxOpenJtalkRcではありません";
      if (!("accelerationMode" in options)) throw "optionsがVoicevoxInitializeOptionsではありません";
      if (!("cpuNumThreads" in options)) throw "optionsがVoicevoxInitializeOptionsではありません";
      const synthesizerPointerName = this.#synthesizerPointer++;
      const { resultCode } = this[Core].voicevoxSynthesizerNew(openJtalkRc[Pointer], synthesizerPointerName, options.accelerationMode, options.cpuNumThreads);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(new VoicevoxSynthesizer(this, synthesizerPointerName));
    });
  }

  /**
   * このライブラリで利用可能なデバイスの情報を、JSONで取得する。
   *
   * あくまで本ライブラリが対応しているデバイスの情報であることに注意。GPUが使える環境ではなかったとしても`cuda`や`dml`は`true`を示しうる。
   *
   * @returns {Promise<string>} サポートデバイス情報のJSON文字列
   *
   * @example
   * ```js
   * const result = voicevoxCreateSupportedDevicesJson();
   * ```
   */
  voicevoxCreateSupportedDevicesJson(): Promise<string> {
    return new Promise<string>((resolve) => {
      const { result, resultCode } = this[Core].voicevoxCreateSupportedDevicesJson();
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * ユーザー辞書をb>構築</b>(_construct_)する。
   *
   * @returns {Promise<VoicevoxUserDict>}
   */
  voicevoxUserDictNew(): Promise<VoicevoxUserDict> {
    return new Promise<VoicevoxUserDict>((resolve) => {
      const userDictPointerName = this.#userDictCounter++;
      this[Core].voicevoxUserDictNew(userDictPointerName);
      resolve(new VoicevoxUserDict(this, userDictPointerName));
    });
  }

  /**
   * デフォルトの初期化オプションを生成する
   * @returns {VoicevoxInitializeOptions} デフォルト値が設定された初期化オプション
   *
   * @static
   */
  static voicevoxMakeDefaultInitializeOptions(): VoicevoxInitializeOptions {
    return {
      accelerationMode: VoicevoxAccelerationMode.VOICEVOX_ACCELERATION_MODE_AUTO,
      cpuNumThreads: 0,
    };
  }

  /**
   * デフォルトの `voicevoxSynthesizerSynthesis` のオプションを生成する
   * @returns {VoicevoxSynthesisOptions} デフォルト値が設定された `voicevoxSynthesizerSynthesis` のオプション
   *
   * @static
   */
  static voicevoxMakeDefaultSynthesisOptions(): VoicevoxSynthesisOptions {
    return {
      enableInterrogativeUpspeak: false,
    };
  }

  /**
   * デフォルトの `voicevoxSynthesizerTts` のオプションを生成する
   * @returns {VoicevoxTtsOptions} デフォルト値が設定された `voicevoxSynthesizerTts` のオプション
   *
   * @static
   */
  static voicevoxMakeDefaultTtsOptions(): VoicevoxTtsOptions {
    return {
      enableInterrogativeUpspeak: false,
    };
  }

  /**
   * VoicevoxUserDictWord を最低限のパラメータで作成する。
   *
   * @param {string} surface 表記
   * @param {string} pronunciation 読み
   * @returns {VoicevoxUserDictWord}
   *
   * @static
   */
  static voicevoxUserDictWordMake(surface: string, pronunciation: string): VoicevoxUserDictWord {
    return {
      surface,
      priority: 0,
      pronunciation,
      accentType: 0,
      wordType: VoicevoxUserDictWordType.VOICEVOX_USER_DICT_WORD_TYPE_PROPER_NOUN,
    };
  }
}

/**
 * テキスト解析器としてのOpen JTalk。
 *
 * <b>構築</b>(_construction_)は Voicevox#voicevoxOpenJtalkRcNew で行い、<b>破棄</b>(_destruction_)は VoicevoxOpenJtalkRc#voicevoxOpenJtalkRcDelete で行う。
 *
 *
 * @example
 * ```js
 * const voicevox = new Voicevox("/home/user/voicevox/libvoicevox_core.so");
 * // ⋮
 * const voicevoxOpenJtalkRc = voicevox.voicevoxOpenJtalkRcNew("/home/user/open_jtalk_dic_utf_8-1.11");
 * // ⋮
 * voicevoxOpenJtalkRc.voicevoxOpenJtalkRcDelete();
 * ```
 */
class VoicevoxOpenJtalkRc {
  #voicevoxBase: Voicevox;
  [Pointer]: number;
  [Deleted]: boolean = false;
  get deleted(): boolean {
    return this[Deleted];
  }
  constructor(base: Voicevox, pointer: number) {
    this.#voicevoxBase = base;
    this[Pointer] = pointer;
  }

  /**
   * OpenJtalkの使うユーザー辞書を設定する。
   *
   * この関数を呼び出した後にユーザー辞書を変更した場合、再度この関数を呼び出す必要がある。
   *
   * @param {VoicevoxUserDict} userDict ユーザー辞書
   *
   * @returns {Promise<void>}
   */
  voicevoxOpenJtalkRcUseUserDict(userDict: VoicevoxUserDict): Promise<void> {
    return new Promise<void>((resolve) => {
      if (!(userDict instanceof VoicevoxUserDict)) throw "userDictがVoicevoxUserDictではありません";
      if (this[Deleted]) throw "Open JTalkは破棄済みです";
      const { resultCode } = this.#voicevoxBase[Core].voicevoxOpenJtalkRcUseUserDict(this[Pointer], userDict[Pointer]);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve();
    });
  }

  /**
   * OpenJtalkRc を<b>破棄</b>(_destruct_)する。
   *
   * @returns {Promise<void>}
   *
   * @example
   * ```js
   * voicevoxOpenJtalkRc.voicevoxOpenJtalkRcDelete();
   * ```
   */
  voicevoxOpenJtalkRcDelete(): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "Open JTalkは破棄済みです";
      this.#voicevoxBase[Core].voicevoxOpenJtalkRcDelete(this[Pointer]);
      resolve();
    });
  }
}

/**
 * 音声シンセサイザ。
 *
 * <b>構築</b>(_construction_)は Voicevox#voicevoxSynthesizerNew で行い、<b>破棄</b>(_destruction_)は VoicevoxSynthesizer#voicevoxSynthesizerDelete で行う。
 */
class VoicevoxSynthesizer {
  [Pointer]: number;
  #voicevoxBase: Voicevox;
  [Deleted]: boolean = false;
  get deleted(): boolean {
    return this[Deleted];
  }
  constructor(base: Voicevox, pointer: number) {
    this.#voicevoxBase = base;
    this[Pointer] = pointer;
  }

  /**
   * VoicevoxSynthesizer を<b>破棄</b>(_destruct_)する。
   *
   * @returns {Promise<void>}
   */
  voicevoxSynthesizerDelete(): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      this.#voicevoxBase[Core].voicevoxSynthesizerDelete(this[Pointer]);
      resolve();
    });
  }

  /**
   * 音声モデルを読み込む。
   * @param {VoicevoxVoiceModel} model 音声モデル
   *
   * @returns {Promise<void>}
   */
  voicevoxSynthesizerLoadVoiceModel(model: VoicevoxVoiceModel): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (!(model instanceof VoicevoxVoiceModel)) throw "voiceModelがVoicevoxVoiceModelではありません";
      const { resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerLoadVoiceModel(this[Pointer], model[Pointer]);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve();
    });
  }

  /**
   * 音声モデルの読み込みを解除する。
   *
   * @param {VoicevoxVoiceModelId} modelId 音声モデルID
   *
   * @returns {Promise<void>}
   */
  voicevoxSynthesizerUnloadVoiceModel(modelId: VoicevoxVoiceModelId): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof modelId !== "string") throw "modelIdがVoicevoxVoiceModelId(=string)ではありません";
      const { resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerUnloadVoiceModel(this[Pointer], modelId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve();
    });
  }

  /**
   * ハードウェアアクセラレーションがGPUモードか判定する。
   *
   * @returns {Promise<boolean>} GPUモードかどうか
   */
  voicevoxSynthesizerIsGpuMode(): Promise<boolean> {
    return new Promise<boolean>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      const { result } = this.#voicevoxBase[Core].voicevoxSynthesizerIsGpuMode(this[Pointer]);
      resolve(result);
    });
  }

  /**
   * 指定したIDの音声モデルが読み込まれているか判定する。
   *
   * @param {VoicevoxVoiceModelId} modelId 音声モデルID
   *
   * @returns {Promise<boolean>} モデルが読み込まれているかどうか
   */
  voicevoxSynthesizerIsLoadedVoiceModel(modelId: VoicevoxVoiceModelId): Promise<boolean> {
    return new Promise<boolean>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof modelId !== "string") throw "modelIdがVoicevoxVoiceModelId(=string)ではありません";
      const { result } = this.#voicevoxBase[Core].voicevoxSynthesizerIsLoadedVoiceModel(this[Pointer], modelId);
      resolve(result);
    });
  }

  /**
   * 今読み込んでいる音声モデルのメタ情報を、JSONで取得する。
   *
   * @returns {Promise<string>} メタ情報のJSON文字列
   */
  voicevoxSynthesizerCreateMetasJson(): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      const { result } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateMetasJson(this[Pointer]);
      resolve(result);
    });
  }

  /**
   * AquesTalk風記法から、AudioQueryをJSONとして生成する。
   *
   * @param {string} kana AquesTalk風記法
   * @param {VoicevoxStyleId} styleId スタイルID
   *
   * @returns {Promise<string>}
   *
   * @example
   * ```js
   * voicevoxSynthesizerCreateAudioQueryFromKana(
   *   "コンニチワ'",
   *   2 //"四国めたん (ノーマル)"
   * );
   * ```
   */
  voicevoxSynthesizerCreateAudioQueryFromKana(kana: string, styleId: VoicevoxStyleId): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof kana !== "string") throw "kanaがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateAudioQueryFromKana(this[Pointer], kana, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * 日本語テキストから、AudioQueryをJSONとして生成する。
   *
   * @param {string} text UTF-8の日本語テキスト
   * @param {VoicevoxStyleId} styleId スタイルID
   *
   * @returns {Promise<string>}
   *
   * @example
   * ```js
   * voicevoxSynthesizerCreateAudioQuery(
   *   "こんにちは",
   *   2 //"四国めたん (ノーマル)"
   * );
   * ```
   */
  voicevoxSynthesizerCreateAudioQuery(text: string, styleId: VoicevoxStyleId): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof text !== "string") throw "textがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateAudioQuery(this[Pointer], text, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * AquesTalk風記法から、AccentPhrase (アクセント句)の配列をJSON形式で生成する。
   *
   * @param {string} kana AquesTalk風記法
   * @param {VoicevoxStyleId} styleId スタイルID
   *
   * @returns {Promise<string>}
   *
   * @example
   * ```js
   * voicevoxSynthesizerCreateAccentPhrasesFromKana(
   *   "コンニチワ'",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   */
  voicevoxSynthesizerCreateAccentPhrasesFromKana(kana: string, styleId: VoicevoxStyleId): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof kana !== "string") throw "kanaがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateAccentPhrasesFromKana(this[Pointer], kana, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * 日本語テキストから、AccentPhrase (アクセント句)の配列をJSON形式で生成する。
   *
   * @param {string} text UTF-8の日本語テキスト
   * @param {VoicevoxStyleId} styleId スタイルID
   *
   * @returns {Promise<string>}
   *
   * @example
   * ```js
   * voicevoxSynthesizerCreateAccentPhrases(
   *   "こんにちは",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   */
  voicevoxSynthesizerCreateAccentPhrases(text: string, styleId: VoicevoxStyleId): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof text !== "string") throw "textがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateAccentPhrases(this[Pointer], text, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * AccentPhraseの配列の音高・音素長を、特定の声で生成しなおす。
   *
   * @param {string} accentPhrasesJson AccentPhraseの配列のJSON文字列
   * @param {VoicevoxStyleId} styleId スタイルID
   *
   * @returns {Promise<string>}
   */
  voicevoxSynthesizerReplaceMoraData(accentPhrasesJson: string, styleId: VoicevoxStyleId): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof accentPhrasesJson !== "string") throw "accentPhrasesJsonがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerReplaceMoraData(this[Pointer], accentPhrasesJson, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * AccentPhraseの配列の音素長を、特定の声で生成しなおす。
   *
   * @param {string} accentPhrasesJson AccentPhraseの配列のJSON文字列
   * @param {VoicevoxStyleId} styleId スタイルID
   *
   * @returns {Promise<string>}
   */
  voicevoxSynthesizerReplacePhonemeLength(accentPhrasesJson: string, styleId: VoicevoxStyleId): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof accentPhrasesJson !== "string") throw "accentPhrasesJsonがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerReplacePhonemeLength(this[Pointer], accentPhrasesJson, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * AccentPhraseの配列の音高を、特定の声で生成しなおす。
   *
   * @param {string} accentPhrasesJson AccentPhraseの配列のJSON文字列
   * @param {VoicevoxStyleId} styleId スタイルID
   *
   * @returns {Promise<string>}
   */
  voicevoxSynthesizerReplaceMoraPitch(accentPhrasesJson: string, styleId: VoicevoxStyleId): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof accentPhrasesJson !== "string") throw "accentPhrasesJsonがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerReplaceMoraPitch(this[Pointer], accentPhrasesJson, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * AudioQueryから音声合成を行う。
   *
   * @param {string} audioQueryJson AudioQueryのJSON文字列
   * @param {VoicevoxStyleId} styleId スタイルID
   * @param {VoicevoxSynthesisOptions} options オプション
   *
   * @returns {Promise<Buffer>}
   */
  voicevoxSynthesizerSynthesis(audioQueryJson: string, styleId: VoicevoxStyleId, options: VoicevoxSynthesisOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof audioQueryJson !== "string") throw "audioQueryJsonがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      if (!("enableInterrogativeUpspeak" in options)) throw "optionsがVoicevoxSynthesisOptionsではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerSynthesis(this[Pointer], audioQueryJson, styleId, options.enableInterrogativeUpspeak);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * AquesTalk風記法から音声合成を行う。
   *
   * @param {string} kana AquesTalk風記法
   * @param {VoicevoxStyleId} styleId スタイルID
   * @param {VoicevoxSynthesisOptions} options オプション
   *
   * @returns {Promise<Buffer>}
   */
  voicevoxSynthesizerTtsFromKana(kana: string, styleId: VoicevoxStyleId, options: VoicevoxTtsOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof kana !== "string") throw "kanaがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      if (!("enableInterrogativeUpspeak" in options)) throw "optionsがVoicevoxTtsOptionsではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerTtsFromKana(this[Pointer], kana, styleId, options.enableInterrogativeUpspeak);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * 日本語テキストから音声合成を行う。
   *
   * @param {string} text UTF-8の日本語テキスト
   * @param {VoicevoxStyleId} styleId スタイルID
   * @param {VoicevoxSynthesisOptions} options オプション
   *
   * @returns {Promise<Buffer>}
   */
  voicevoxSynthesizerTts(text: string, styleId: VoicevoxStyleId, options: VoicevoxTtsOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      if (this[Deleted]) throw "VoicevoxSynthesizerは破棄されています";
      if (typeof text !== "string") throw "textがstringではありません";
      if (typeof styleId !== "number") throw "styleIdがVoicevoxStyleId(=number)ではありません";
      if (!("enableInterrogativeUpspeak" in options)) throw "optionsがVoicevoxTtsOptionsではありません";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerTts(this[Pointer], text, styleId, options.enableInterrogativeUpspeak);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }
}

/**
 * ユーザー辞書。
 */
class VoicevoxUserDict {
  [Pointer]: number;
  #voicevoxBase: Voicevox;
  [Deleted]: boolean = false;
  get deleted(): boolean {
    return this[Deleted];
  }
  constructor(base: Voicevox, pointer: number) {
    this.#voicevoxBase = base;
    this[Pointer] = pointer;
  }

  /**
   * ユーザー辞書にファイルを読み込ませる。
   *
   * @param {string} dictPath 読み込む辞書ファイルのパス
   *
   * @returns {Promise<void>}
   */
  voicevoxUserDictLoad(dictPath: string): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxUserDictは破棄されています";
      if (typeof dictPath !== "string") throw "dictPathがstringではありません";
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictLoad(this[Pointer], dictPath);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve();
    });
  }

  /**
   * ユーザー辞書に単語を追加する。
   *\
   * @param {VoicevoxUserDictWord} word 追加する単語
   *
   * @returns {Promise<string>} 追加した単語のUUID
   */
  voicevoxUserDictAddWord(word: VoicevoxUserDictWord): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxUserDictは破棄されています";
      if (!("surface" in word)) throw "wordはVoicevoxUserDictWordではありません";
      if (!("pronunciation" in word)) throw "wordはVoicevoxUserDictWordではありません";
      if (!("accentType" in word)) throw "wordはVoicevoxUserDictWordではありません";
      if (!("priority" in word)) throw "wordはVoicevoxUserDictWordではありません";
      if (!("wordType" in word)) throw "wordはVoicevoxUserDictWordではありません";
      const { resultCode, result } = this.#voicevoxBase[Core].voicevoxUserDictAddWord(this[Pointer], word.surface, word.pronunciation, word.accentType, word.priority, word.wordType);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * ユーザー辞書の単語を更新する。
   *
   * @param {string} wordUuid 更新する単語のUUID
   * @param {VoicevoxUserDictWord} word 新しい単語のデータ
   *
   * @returns {Promise<void>}
   */
  voicevoxUserDictUpdateWord(wordUuid: string, word: VoicevoxUserDictWord): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxUserDictは破棄されています";
      if (!("surface" in word)) throw "wordはVoicevoxUserDictWordではありません";
      if (!("pronunciation" in word)) throw "wordはVoicevoxUserDictWordではありません";
      if (!("accentType" in word)) throw "wordはVoicevoxUserDictWordではありません";
      if (!("priority" in word)) throw "wordはVoicevoxUserDictWordではありません";
      if (!("wordType" in word)) throw "wordはVoicevoxUserDictWordではありません";
      if (typeof wordUuid !== "string") throw "wordUuidがstringではありません";
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictUpdateWord(this[Pointer], word.surface, word.pronunciation, word.accentType, word.priority, word.wordType, wordUuid);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve();
    });
  }

  /**
   * ユーザー辞書から単語を削除する。
   *
   * @param {string} wordUuid 更新する単語のUUID
   *
   * @returns {Promise<void>}
   */
  voicevoxUserDictRemoveWord(wordUuid: string): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxUserDictは破棄されています";
      if (typeof wordUuid !== "string") throw "wordUuidがstringではありません";
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictRemoveWord(this[Pointer], wordUuid);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve();
    });
  }

  /**
   * ユーザー辞書の単語をJSON形式で出力する。
   *
   * @returns {Promise<string>}
   */
  voicevoxUserDictToJson(): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxUserDictは破棄されています";
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxUserDictToJson(this[Pointer]);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve(result);
    });
  }

  /**
   * 他のユーザー辞書をインポートする。
   *
   * @param {VoicevoxUserDict} otherDict インポートするユーザー辞書
   *
   * @returns {Promise<void>}
   */
  voicevoxUserDictImport(otherDict: VoicevoxUserDict): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxUserDictは破棄されています";
      if (!(otherDict instanceof VoicevoxUserDict)) throw "otherDictがVoicevoxUserDictではありません";
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictImport(this[Pointer], otherDict[Pointer]);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve();
    });
  }

  /**
   * ユーザー辞書をファイルに保存する。
   *
   * @param {string} path 保存先のファイルパス
   *
   * @returns {Promise<void>}
   */
  voicevoxUserDictSave(path: string): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxUserDictは破棄されています";
      if (typeof path !== "string") throw "pathがstringではありません";
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictSave(this[Pointer], path);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result;
      resolve();
    });
  }

  /**
   * ユーザー辞書を<b>破棄</b>(_destruct_)する。
   *
   * @returns {Promise<void>}
   */
  voicevoxUserDictDelete(): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxUserDictは破棄されています";
      this.#voicevoxBase[Core].voicevoxUserDictDelete(this[Pointer]);
      this[Deleted] = true;
      resolve();
    });
  }
}

/**
 * 音声モデル。
 *
 * VVMファイルと対応する。
 * <b>構築</b>(_construction_)は Voicevox#voicevoxVoiceModelNewFromPath で行い、<b>破棄</b>(_destruction_)は VoicevoxVoiceModel#voicevoxVoiceModelDelete で行う。
 */
class VoicevoxVoiceModel {
  [Pointer]: number;
  #voicevoxBase: Voicevox;
  [Deleted]: boolean = false;
  get deleted(): boolean {
    return this[Deleted];
  }
  constructor(base: Voicevox, pointer: number) {
    this.#voicevoxBase = base;
    this[Pointer] = pointer;
  }

  /**
   * VoicevoxVoiceModel からIDを取得する。
   *
   * @returns {Promise<VoicevoxVoiceModelId>} 音声モデルID
   */
  voicevoxVoiceModelId(): Promise<VoicevoxVoiceModelId> {
    return new Promise<VoicevoxVoiceModelId>((resolve) => {
      if (this[Deleted]) throw "VoicevoxVoiceModelは破棄済みです";
      const { result } = this.#voicevoxBase[Core].voicevoxVoiceModelId(this[Pointer]);
      resolve(result);
    });
  }

  /**
   * VoicevoxVoiceModel からメタ情報を取得する。
   *
   * @returns {Promise<string>} メタ情報のJSON文字列
   */
  voicevoxVoiceModelGetMetasJson(): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw "VoicevoxVoiceModelは破棄済みです";
      const { result } = this.#voicevoxBase[Core].voicevoxVoiceModelGetMetasJson(this[Pointer]);
      resolve(result);
    });
  }

  /**
   * VoicevoxVoiceModel を<b>破棄</b>(_destruct_)する。
   *
   * @returns {Promise<void>}
   */
  voicevoxVoiceModelDelete(): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw "VoicevoxVoiceModelは破棄済みです";
      this.#voicevoxBase[Core].voicevoxVoiceModelDelete(this[Pointer]);
      resolve();
    });
  }
}

/**
 * 音声モデルID。
 */
type VoicevoxVoiceModelId = string;

/**
 * スタイルID。
 *
 * VOICEVOXにおける、ある<b>話者</b>(_speaker_)のある<b>スタイル</b>(_style_)を指す。
 */
type VoicevoxStyleId = number;

/**
 * Voicevox#voicevoxSynthesizerNew のオプション。
 */
interface VoicevoxInitializeOptions {
  /**
   * ハードウェアアクセラレーションモード
   */
  accelerationMode: VoicevoxAccelerationMode;
  /**
   * CPU利用数を指定
   * 0を指定すると環境に合わせたCPUが利用される
   */
  cpuNumThreads: number;
}

/**
 * VoicevoxSynthesizer#VoicevoxSynthesizerSynthesis のオプション。
 */
interface VoicevoxSynthesisOptions {
  /**
   * 疑問文の調整を有効にする
   */
  enableInterrogativeUpspeak: boolean;
}

/**
 * VoicevoxSynthesizer#VoicevoxSynthesizerSynthesis のオプション。
 */
interface VoicevoxSynthesisOptions {
  /**
   * 疑問文の調整を有効にする
   */
  enableInterrogativeUpspeak: boolean;
}

/**
 * VoicevoxSynthesizer#VoicevoxSynthesizerTts のオプション。
 */
interface VoicevoxTtsOptions {
  /**
   * 疑問文の調整を有効にする
   */
  enableInterrogativeUpspeak: boolean;
}

/**
 * ユーザー辞書の単語。
 */
interface VoicevoxUserDictWord {
  /**
   * 表記
   */
  surface: string;
  /**
   * 読み
   */
  pronunciation: string;
  /**
   * アクセント型
   */
  accentType: number;
  /**
   * 単語の種類
   */
  wordType: VoicevoxUserDictWordType;
  /**
   * 優先度
   */
  priority: number;
}
