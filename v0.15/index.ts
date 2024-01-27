import { VoicevoxCore, VoicevoxResultCode, VoicevoxAccelerationMode, VoicevoxUserDictWordType } from "../voicevox_core";
import { checkValidNumber, checkValidObject, checkValidOption, checkValidString, VoicevoxError, VoicevoxJsError, uuidToBuffer, bufferToUuid } from "../util";

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
   * @param path libvoicevox_core.so, libvoicevox_core.solib, voicevox_core.dllを指すパス
   */
  constructor(path: string) {
    this[Core] = new VoicevoxCore(path);
  }

  /**
   * `OpenJtalkRc`を構築(_construct_)する。
   * 解放は`VoicevoxOpenJtalkRc#delete`で行う。
   * @param {string} openJtalkDicDir 辞書ディレクトリを指すパス
   * @returns {Promise<VoicevoxOpenJtalkRc>}
   * @throws
   */
  openJtalkRcNew(openJtalkDicDir: string): Promise<VoicevoxOpenJtalkRc> {
    return new Promise<VoicevoxOpenJtalkRc>((resolve) => {
      checkValidString(openJtalkDicDir, "openJtalkDicDir");
      const openJtalkPointerName = this.#openJtalkPointerCounter;
      this.#openJtalkPointerCounter++;
      const { resultCode } = this[Core].voicevoxOpenJtalkRcNew(openJtalkDicDir, openJtalkPointerName);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(new VoicevoxOpenJtalkRc(this, openJtalkPointerName));
    });
  }

  /**
   * voicevoxのバージョンを取得する。
   * @returns {Promise<string>} SemVerでフォーマットされたバージョン。
   */
  getVersion(): Promise<string> {
    return new Promise<string>((resolve) => {
      const { result } = this[Core].voicevoxGetVersion();
      resolve(result);
    });
  }

  /**
   * VVMファイルから`VoicevoxVoiceModel`を構築(_construct_)する。
   * @param {string} path vvmファイルへのファイルパス
   * @returns {Promise<VoicevoxVoiceModel>}
   * @throws
   */
  voiceModelNewFromPath(path: string): Promise<VoicevoxVoiceModel> {
    return new Promise<VoicevoxVoiceModel>((resolve) => {
      checkValidString(path, "path");
      const modelPonterName = this.#voiceModelCounter;
      this.#voiceModelCounter++;
      const { resultCode } = this[Core].voicevoxVoiceModelNewFromPath(path, modelPonterName);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(new VoicevoxVoiceModel(this, modelPonterName));
    });
  }

  /**
   * `VoicevoxSynthesizer`を構築(_construct_)する。
   * @param {VoicevoxOpenJtalkRc} openJtalkRc OpenJtalkRcクラス
   * @param {VoicevoxInitializeOptions} options オプション
   * @returns {Promise<VoicevoxSynthesizer>}
   * @throws
   */
  synthesizerNew(openJtalkRc: VoicevoxOpenJtalkRc, options: VoicevoxInitializeOptions): Promise<VoicevoxSynthesizer> {
    return new Promise<VoicevoxSynthesizer>((resolve) => {
      checkValidObject(openJtalkRc, "openJtalkRc", VoicevoxOpenJtalkRc, "VoicevoxOpenJtalkRc");
      checkVoicevoxInitializeOptions(options);
      const synthesizerPointerName = this.#synthesizerPointer++;
      const { resultCode } = this[Core].voicevoxSynthesizerNew(openJtalkRc[Pointer], synthesizerPointerName, options.accelerationMode, options.cpuNumThreads);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(new VoicevoxSynthesizer(this, synthesizerPointerName));
    });
  }

  /**
   * このライブラリで利用可能なデバイスの情報を、JSONで取得する。
   * あくまで本ライブラリが対応しているデバイスの情報であることに注意。GPUが使える環境ではなかったとしても`cuda`や`dml`は`true`を示しうる。
   * @returns {Promise<VoicevoxSupportedDevicesJson>} サポートデバイス情報
   * @throws
   */
  createSupportedDevicesJson(): Promise<VoicevoxSupportedDevicesJson> {
    return new Promise<VoicevoxSupportedDevicesJson>((resolve) => {
      const { result, resultCode } = this[Core].voicevoxCreateSupportedDevicesJson();
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * ユーザー辞書を構築(_construct_)する。
   * @returns {Promise<VoicevoxUserDict>}
   */
  userDictNew(): Promise<VoicevoxUserDict> {
    return new Promise<VoicevoxUserDict>((resolve) => {
      const userDictPointerName = this.#userDictCounter++;
      this[Core].voicevoxUserDictNew(userDictPointerName);
      resolve(new VoicevoxUserDict(this, userDictPointerName));
    });
  }

  /**
   * デフォルトの初期化オプションを生成する
   * @returns {VoicevoxInitializeOptions} デフォルト値が設定された初期化オプション
   * @static
   */
  static makeDefaultInitializeOptions(): VoicevoxInitializeOptions {
    return {
      accelerationMode: VoicevoxAccelerationMode.VOICEVOX_ACCELERATION_MODE_AUTO,
      cpuNumThreads: 0,
    };
  }

  /**
   * デフォルトの`voicevoxSynthesizerSynthesis`のオプションを生成する
   * @returns {VoicevoxSynthesisOptions} デフォルト値が設定された`voicevoxSynthesizerSynthesis`のオプション
   * @static
   */
  static makeDefaultSynthesisOptions(): VoicevoxSynthesisOptions {
    return {
      enableInterrogativeUpspeak: false,
    };
  }

  /**
   * デフォルトの`voicevoxSynthesizerTts`のオプションを生成する
   * @returns {VoicevoxTtsOptions} デフォルト値が設定された`voicevoxSynthesizerTts`のオプション
   * @static
   */
  static makeDefaultTtsOptions(): VoicevoxTtsOptions {
    return {
      enableInterrogativeUpspeak: false,
    };
  }

  /**
   * `VoicevoxUserDictWord`を最低限のパラメータで作成する。
   * @param {string} surface 表記
   * @param {string} pronunciation 読み、カタカナ
   * @returns {VoicevoxUserDictWord}
   * @static
   */
  static userDictWordMake(surface: string, pronunciation: string): VoicevoxUserDictWord {
    return {
      surface,
      priority: 0,
      pronunciation,
      accentType: 0,
      wordType: VoicevoxUserDictWordType.VOICEVOX_USER_DICT_WORD_TYPE_PROPER_NOUN,
    };
  }
}

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
   * この関数を呼び出した後にユーザー辞書を変更した場合、再度この関数を呼び出す必要がある。
   * @param {VoicevoxUserDict} userDict ユーザー辞書
   * @returns {Promise<void>}
   * @throws
   */
  useUserDict(userDict: VoicevoxUserDict): Promise<void> {
    return new Promise<void>((resolve) => {
      checkValidObject(userDict, "userDict", VoicevoxUserDict, "VoicevoxUserDict");
      if (this[Deleted]) throw new VoicevoxJsError("Open JTalkは破棄済みです");
      const { resultCode } = this.#voicevoxBase[Core].voicevoxOpenJtalkRcUseUserDict(this[Pointer], userDict[Pointer]);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve();
    });
  }

  /**
   * `OpenJtalkRc`を破棄(_destruct_)する。
   * @returns {Promise<void>}
   * @throws
   */
  delete(): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("Open JTalkは破棄済みです");
      this.#voicevoxBase[Core].voicevoxOpenJtalkRcDelete(this[Pointer]);
      resolve();
    });
  }
}

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
   * `VoicevoxSynthesizer`を破棄(_destruct_)する。
   * @returns {Promise<void>}
   * @throws
   */
  delete(): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      this.#voicevoxBase[Core].voicevoxSynthesizerDelete(this[Pointer]);
      resolve();
    });
  }

  /**
   * 音声モデルを読み込む。
   * @param {VoicevoxVoiceModel} model 音声モデル
   * @returns {Promise<void>}
   * @throws
   */
  loadVoiceModel(model: VoicevoxVoiceModel): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkValidObject(model, "model", VoicevoxVoiceModel, "VoicevoxVoiceModel");
      const { resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerLoadVoiceModel(this[Pointer], model[Pointer]);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve();
    });
  }

  /**
   * 音声モデルの読み込みを解除する。
   * @param {VoicevoxVoiceModelId} modelId 音声モデルID
   * @returns {Promise<void>}
   * @throws
   */
  unloadVoiceModel(modelId: VoicevoxVoiceModelId): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkValidString(modelId, "modelId");
      const { resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerUnloadVoiceModel(this[Pointer], modelId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve();
    });
  }

  /**
   * ハードウェアアクセラレーションがGPUモードか判定する。
   * @returns {Promise<boolean>} GPUモードかどうか
   * @throws
   */
  isGpuMode(): Promise<boolean> {
    return new Promise<boolean>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      const { result } = this.#voicevoxBase[Core].voicevoxSynthesizerIsGpuMode(this[Pointer]);
      resolve(result);
    });
  }

  /**
   * 指定したIDの音声モデルが読み込まれているか判定する。
   * @param {VoicevoxVoiceModelId} modelId 音声モデルID
   * @returns {Promise<boolean>} モデルが読み込まれているかどうか
   * @throws
   */
  isLoadedVoiceModel(modelId: VoicevoxVoiceModelId): Promise<boolean> {
    return new Promise<boolean>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkValidString(modelId, "modelId");
      const { result } = this.#voicevoxBase[Core].voicevoxSynthesizerIsLoadedVoiceModel(this[Pointer], modelId);
      resolve(result);
    });
  }

  /**
   * 今読み込んでいる音声モデルのメタ情報を取得する。
   * @returns {Promise<Array<VoicevoxMetaJson>>} メタ情報
   * @throws
   */
  createMetasJson(): Promise<Array<VoicevoxMetaJson>> {
    return new Promise<Array<VoicevoxMetaJson>>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      const { result } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateMetasJson(this[Pointer]);
      resolve(JSON.parse(result));
    });
  }

  /**
   * AquesTalk風記法から、AudioQueryを生成する。
   * @param {string} kana AquesTalk風記法
   * @param {VoicevoxStyleId} styleId スタイルID
   * @returns {Promise<VoicevoxAudioQueryJson>}
   * @throws
   */
  createAudioQueryFromKana(kana: string, styleId: VoicevoxStyleId): Promise<VoicevoxAudioQueryJson> {
    return new Promise<VoicevoxAudioQueryJson>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkValidString(kana, "kana");
      checkValidNumber(styleId, "styleId", true);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateAudioQueryFromKana(this[Pointer], kana, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * 日本語テキストから、AudioQueryを生成する。
   * @param {string} text UTF-8の日本語テキスト
   * @param {VoicevoxStyleId} styleId スタイルID
   * @returns {Promise<VoicevoxAudioQueryJson>}
   * @throws
   */
  createAudioQuery(text: string, styleId: VoicevoxStyleId): Promise<VoicevoxAudioQueryJson> {
    return new Promise<VoicevoxAudioQueryJson>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkValidString(text, "text");
      checkValidNumber(styleId, "styleId", true);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateAudioQuery(this[Pointer], text, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * AquesTalk風記法から、AccentPhrase(アクセント句)の配列を生成する。
   * @param {string} kana AquesTalk風記法
   * @param {VoicevoxStyleId} styleId スタイルID
   * @returns {Promise<Array<VoicevoxAccentPhraseJson>>}
   * @throws
   */
  createAccentPhrasesFromKana(kana: string, styleId: VoicevoxStyleId): Promise<Array<VoicevoxAccentPhraseJson>> {
    return new Promise<Array<VoicevoxAccentPhraseJson>>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkValidString(kana, "kana");
      checkValidNumber(styleId, "styleId", true);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateAccentPhrasesFromKana(this[Pointer], kana, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * 日本語テキストから、AccentPhrase(アクセント句)の配列を生成する。
   * @param {string} text UTF-8の日本語テキスト
   * @param {VoicevoxStyleId} styleId スタイルID
   * @returns {Promise<Array<VoicevoxAccentPhraseJson>>}
   * @throws
   */
  createAccentPhrases(text: string, styleId: VoicevoxStyleId): Promise<Array<VoicevoxAccentPhraseJson>> {
    return new Promise<Array<VoicevoxAccentPhraseJson>>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkValidString(text, "text");
      checkValidNumber(styleId, "styleId", true);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerCreateAccentPhrases(this[Pointer], text, styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * AccentPhraseの配列の音高・音素長を、特定の声で生成しなおす。
   * @param {Array<VoicevoxAccentPhraseJson>} accentPhrasesJson AccentPhraseの配列
   * @param {VoicevoxStyleId} styleId スタイルID
   * @returns {Promise<Array<VoicevoxAccentPhraseJson>>}
   * @throws
   */
  replaceMoraData(accentPhrasesJson: Array<VoicevoxAccentPhraseJson>, styleId: VoicevoxStyleId): Promise<Array<VoicevoxAccentPhraseJson>> {
    return new Promise<Array<VoicevoxAccentPhraseJson>>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkVoicevoxAccentPhraseJson(accentPhrasesJson);
      checkValidNumber(styleId, "styleId", true);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerReplaceMoraData(this[Pointer], JSON.stringify(accentPhrasesJson), styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * AccentPhraseの配列の音素長を、特定の声で生成しなおす。
   * @param {Array<VoicevoxAccentPhraseJson>} accentPhrasesJson AccentPhraseの配列
   * @param {VoicevoxStyleId} styleId スタイルID
   * @returns {Promise<Array<VoicevoxAccentPhraseJson>>}
   * @throws
   */
  replacePhonemeLength(accentPhrasesJson: Array<VoicevoxAccentPhraseJson>, styleId: VoicevoxStyleId): Promise<Array<VoicevoxAccentPhraseJson>> {
    return new Promise<Array<VoicevoxAccentPhraseJson>>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkVoicevoxAccentPhraseJson(accentPhrasesJson);
      checkValidNumber(styleId, "styleId", true);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerReplacePhonemeLength(this[Pointer], JSON.stringify(accentPhrasesJson), styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * AccentPhraseの配列の音高を、特定の声で生成しなおす。
   * @param {Array<VoicevoxAccentPhraseJson>} accentPhrasesJson AccentPhraseの配列
   * @param {VoicevoxStyleId} styleId スタイルID
   * @returns {Promise<Array<VoicevoxAccentPhraseJson>>}
   * @throws
   */
  replaceMoraPitch(accentPhrasesJson: Array<VoicevoxAccentPhraseJson>, styleId: VoicevoxStyleId): Promise<Array<VoicevoxAccentPhraseJson>> {
    return new Promise<Array<VoicevoxAccentPhraseJson>>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkVoicevoxAccentPhraseJson(accentPhrasesJson);
      checkValidNumber(styleId, "styleId", true);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerReplaceMoraPitch(this[Pointer], JSON.stringify(accentPhrasesJson), styleId);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * AudioQueryから音声合成を行う。
   * @param {VoicevoxAudioQueryJson} audioQueryJson AudioQuery
   * @param {VoicevoxStyleId} styleId スタイルID
   * @param {VoicevoxSynthesisOptions} options オプション
   * @returns {Promise<Buffer>}
   * @throws
   */
  synthesis(audioQueryJson: VoicevoxAudioQueryJson, styleId: VoicevoxStyleId, options: VoicevoxSynthesisOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkVoicevoxAudioQueryJson(audioQueryJson);
      checkValidNumber(styleId, "styleId", true);
      checkVoicevoxSynthesisOptions(options);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerSynthesis(this[Pointer], JSON.stringify(audioQueryJson), styleId, options.enableInterrogativeUpspeak);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(result);
    });
  }

  /**
   * AquesTalk風記法から音声合成を行う。
   * @param {string} kana AquesTalk風記法
   * @param {VoicevoxStyleId} styleId スタイルID
   * @param {VoicevoxSynthesisOptions} options オプション
   * @returns {Promise<Buffer>}
   * @throws
   */
  ttsFromKana(kana: string, styleId: VoicevoxStyleId, options: VoicevoxTtsOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkValidString(kana, "kana");
      checkValidNumber(styleId, "styleId", true);
      checkVoicevoxTtsOptions(options);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerTtsFromKana(this[Pointer], kana, styleId, options.enableInterrogativeUpspeak);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(result);
    });
  }

  /**
   * 日本語テキストから音声合成を行う。
   * @param {string} text UTF-8の日本語テキスト
   * @param {VoicevoxStyleId} styleId スタイルID
   * @param {VoicevoxSynthesisOptions} options オプション
   * @returns {Promise<Buffer>}
   * @throws
   */
  tts(text: string, styleId: VoicevoxStyleId, options: VoicevoxTtsOptions): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxSynthesizerは破棄されています");
      checkValidString(text, "text");
      checkValidNumber(styleId, "styleId", true);
      checkVoicevoxTtsOptions(options);
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxSynthesizerTts(this[Pointer], text, styleId, options.enableInterrogativeUpspeak);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(result);
    });
  }
}

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
   * @param {string} dictPath 読み込む辞書ファイルのパス
   * @returns {Promise<void>}
   * @throws
   */
  load(dictPath: string): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxUserDictは破棄されています");
      checkValidString(dictPath, "dictPath");
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictLoad(this[Pointer], dictPath);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve();
    });
  }

  /**
   * ユーザー辞書に単語を追加する。
   * @param {VoicevoxUserDictWord} word 追加する単語
   * @returns {Promise<string>} 追加した単語のUUID
   * @throws
   */
  addWord(word: VoicevoxUserDictWord): Promise<string> {
    return new Promise<string>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxUserDictは破棄されています");
      checkVoicevoxUserDictWord(word);
      const { resultCode, result } = this.#voicevoxBase[Core].voicevoxUserDictAddWord(this[Pointer], word.surface, word.pronunciation, word.accentType, word.priority, word.wordType);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(bufferToUuid(result));
    });
  }

  /**
   * ユーザー辞書の単語を更新する。
   * @param {string} wordUuid 更新する単語のUUID
   * @param {VoicevoxUserDictWord} word 新しい単語のデータ
   * @returns {Promise<void>}
   * @throws
   */
  updateWord(wordUuid: string, word: VoicevoxUserDictWord): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxUserDictは破棄されています");
      checkVoicevoxUserDictWord(word);
      checkValidString(wordUuid, "wordUuid");
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictUpdateWord(this[Pointer], word.surface, word.pronunciation, word.accentType, word.priority, word.wordType, uuidToBuffer(wordUuid));
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve();
    });
  }

  /**
   * ユーザー辞書から単語を削除する。
   * @param {string} wordUuid 更新する単語のUUID
   * @returns {Promise<void>}
   * @throws
   */
  removeWord(wordUuid: string): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxUserDictは破棄されています");
      checkValidString(wordUuid, "wordUuid");
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictRemoveWord(this[Pointer], uuidToBuffer(wordUuid));
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve();
    });
  }

  /**
   * ユーザー辞書の単語を出力する。
   * @returns {Promise<VoicevoxUserDictsJson>}
   * @throws
   */
  toJson(): Promise<VoicevoxUserDictsJson> {
    return new Promise<VoicevoxUserDictsJson>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxUserDictは破棄されています");
      const { result, resultCode } = this.#voicevoxBase[Core].voicevoxUserDictToJson(this[Pointer]);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(JSON.parse(result));
    });
  }

  /**
   * 他のユーザー辞書をインポートする。
   * @param {VoicevoxUserDict} otherDict インポートするユーザー辞書
   * @returns {Promise<void>}
   * @throws
   */
  import(otherDict: VoicevoxUserDict): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxUserDictは破棄されています");
      checkValidObject(otherDict, "otherDict", VoicevoxUserDict, "VoicevoxUserDict");
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictImport(this[Pointer], otherDict[Pointer]);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve();
    });
  }

  /**
   * ユーザー辞書をファイルに保存する。
   * @param {string} path 保存先のファイルパス
   * @returns {Promise<void>}
   * @throws
   */
  save(path: string): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxUserDictは破棄されています");
      checkValidString(path, "path");
      const { resultCode } = this.#voicevoxBase[Core].voicevoxUserDictSave(this[Pointer], path);
      if (resultCode !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new VoicevoxError(this.#voicevoxBase[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve();
    });
  }

  /**
   * ユーザー辞書を破棄(_destruct_)する。
   * @returns {Promise<void>}
   * @throws
   */
  delete(): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxUserDictは破棄されています");
      this.#voicevoxBase[Core].voicevoxUserDictDelete(this[Pointer]);
      this[Deleted] = true;
      resolve();
    });
  }
}

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
   * `VoicevoxVoiceModel`からIDを取得する。
   * @returns {Promise<VoicevoxVoiceModelId>} 音声モデルID
   * @throws
   */
  id(): Promise<VoicevoxVoiceModelId> {
    return new Promise<VoicevoxVoiceModelId>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxVoiceModelは破棄済みです");
      const { result } = this.#voicevoxBase[Core].voicevoxVoiceModelId(this[Pointer]);
      resolve(result);
    });
  }

  /**
   * `VoicevoxVoiceModel`からメタ情報を取得する。
   * @returns {Promise<Array<VoicevoxMetaJson>>} メタ情報
   * @throws
   */
  getMetasJson(): Promise<Array<VoicevoxMetaJson>> {
    return new Promise<Array<VoicevoxMetaJson>>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxVoiceModelは破棄済みです");
      const { result } = this.#voicevoxBase[Core].voicevoxVoiceModelGetMetasJson(this[Pointer]);
      resolve(JSON.parse(result));
    });
  }

  /**
   * `VoicevoxVoiceModel`を破棄(_destruct_)する。
   * @returns {Promise<void>}
   * @throws
   */
  delete(): Promise<void> {
    return new Promise<void>((resolve) => {
      if (this[Deleted]) throw new VoicevoxJsError("VoicevoxVoiceModelは破棄済みです");
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
 * VOICEVOXにおける、ある話者(_speaker_)のあるスタイル(_style_)を指す。
 */
type VoicevoxStyleId = number;

/**
 * `Voicevox#voicevoxSynthesizerNew`のオプション。
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
function checkVoicevoxInitializeOptions(obj: VoicevoxInitializeOptions) {
  checkValidOption(obj, "VoicevoxInitializeOptions", [
    ["accelerationMode", "number", true],
    ["cpuNumThreads", "number", true],
  ]);
}

/**
 * `VoicevoxSynthesizer#synthesis`のオプション。
 */
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
 * `VoicevoxSynthesizer#tts`のオプション。
 */
interface VoicevoxTtsOptions {
  /**
   * 疑問文の調整を有効にする
   */
  enableInterrogativeUpspeak: boolean;
}

function checkVoicevoxTtsOptions(obj: VoicevoxTtsOptions) {
  checkValidOption(obj, "VoicevoxTtsOptions", [["enableInterrogativeUpspeak", "boolean"]]);
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
   * カタカナ
   */
  pronunciation: string;
  /**
   * アクセント型
   * 音が下がる場所を指す
   */
  accentType: number;
  /**
   * 単語の種類
   */
  wordType: VoicevoxUserDictWordType;
  /**
   * 優先度
   * 0から10
   */
  priority: number;
}

function checkVoicevoxUserDictWord(obj: VoicevoxUserDictWord) {
  checkValidOption(obj, "VoicevoxUserDictWord", [
    ["accentType", "number", true],
    ["priority", "number", true],
    ["pronunciation", "string"],
    ["surface", "string"],
    ["wordType", "number", true],
  ]);
}

interface VoicevoxSupportedDevicesJson {
  cpu: boolean;
  cuda: boolean;
  dml: boolean;
}

interface VoicevoxMetaJson {
  name: string;
  styles: Array<VoicevoxStyleJson>;
  version: string;
  speaker_uuid: string;
}

interface VoicevoxStyleJson {
  id: number;
  name: string;
}

interface VoicevoxAudioQueryJson {
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

function checkVoicevoxAudioQueryJson(obj: VoicevoxAudioQueryJson) {
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

interface VoicevoxAccentPhraseJson {
  moras: Array<VoicevoxMoraJson>;
  accent: number;
  pause_mora: VoicevoxMoraJson | null;
  is_interrogative: boolean;
}

function checkVoicevoxAccentPhraseJson(arr: Array<VoicevoxAccentPhraseJson>) {
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

interface VoicevoxMoraJson {
  text: string;
  consonant: string | null;
  consonant_length: number | null;
  vowel: string;
  vowel_length: number;
  pitch: number;
}

function checkVoicevoxMoraJson(obj: VoicevoxMoraJson) {
  checkValidOption(obj, "VoicevoxMoraJson", [
    ["pitch", "number"],
    ["text", "string"],
    ["vowel", "string"],
    ["vowel_length", "number"],
  ]);
  if (obj.consonant !== null && typeof obj.consonant !== "string") throw new VoicevoxJsError("有効なVoicevoxMoraJsonではありません(consonantがstringまたはnullでない)");
  if (obj.consonant !== null && typeof obj.consonant_length !== "number") throw new VoicevoxJsError("有効なVoicevoxMoraJsonではありません(consonant_lengthがnumberまたはnullでない)");
}

interface VoicevoxUserDictsJson {
  [key: string]: VoicevoxUserDictJson;
}

interface VoicevoxUserDictJson {
  surface: string;
  pronunciation: string;
  accent_type: number;
  word_type: VoicevoxUserDictJsonWordType;
  priority: number;
  mora_count: number;
}

enum VoicevoxUserDictJsonWordType {
  /** 固有名詞 */
  PROPER_NOUN = "PROPER_NOUN",
  /** 一般名刺 */
  COMMON_NOUN = "COMMON_NOUN",
  /** 動詞 */
  VERB = "VERB",
  /** 形容詞 */
  ADJECTIVE = "ADJECTIVE",
  /** 接尾辞 */
  SUFFIX = "SUFFIX",
}
