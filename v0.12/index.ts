import { VoicevoxCore, VoicevoxResultCodeV12 } from "../voicevox_core";
import { VoicevoxError, VoicevoxMetaJson, VoicevoxSupportedDevicesJson, checkValidArray, checkValidBoolean, checkValidNumber, checkValidString } from "../util";

const Core = Symbol("Core");

/**
 * voicevox_coreを利用してVOICEVOXを使う
 * @version 0.12.x
 * @version 0.13.x
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
   * 初期化する
   * 音声合成するための初期化を行う。他の関数を正しく実行するには先に初期化が必要
   * @param {boolean} useGpu trueならGPU用、falseならCPU用の初期化を行う
   * @param {number} cpuNumThreads 推論に用いるスレッド数を設定する。0の場合論理コア数の半分か、物理コア数が設定される
   * @param {boolean} loadAllModels trueなら全てのモデルをロードする
   * @returns {Promise<void>}
   * 何度も実行可能。useGpuを変更して実行しなおすことも可能。
   * 最後に実行したuseGpuに従って他の関数が実行される。
   */
  initialize(useGpu: boolean, cpuNumThreads: number, loadAllModels: boolean): Promise<void> {
    return new Promise<void>((resolve) => {
      checkValidBoolean(useGpu, "useGpu");
      checkValidNumber(cpuNumThreads, "cpuNumThreads", true);
      checkValidBoolean(loadAllModels, "loadAllModels");
      const { result } = this[Core].initialize(useGpu, cpuNumThreads, loadAllModels);
      if (!result) throw new VoicevoxError(this[Core].lastErrorMessage().result);
      resolve();
    });
  }

  /**
   * モデルをロードする
   * @param {number} speakerId 話者番号
   * @returns {Promise<void>}
   * 必ずしも話者とモデルが1:1対応しているわけではない。
   */
  loadModel(speakerId: number): Promise<void> {
    return new Promise<void>((resolve) => {
      checkValidNumber(speakerId, "speakerId", true);
      const { result } = this[Core].loadModel(speakerId);
      if (!result) throw new VoicevoxError(this[Core].lastErrorMessage().result);
      resolve();
    });
  }

  /**
   * モデルがロード済みかどうか
   * @param {number} speakerId 話者番号
   * @returns {Promise<boolean>}
   */
  isModelLoaded(speakerId: number): Promise<boolean> {
    return new Promise<boolean>((resolve) => {
      checkValidNumber(speakerId, "speakerId", true);
      const { result } = this[Core].isModelLoaded(speakerId);
      resolve(result);
    });
  }

  /**
   * 終了処理を行う
   * 終了処理を行う。以降関数を利用するためには再度初期化を行う必要がある。
   * 何度も実行可能。実行せずにexitしても大抵の場合問題ないが、
   * CUDAを利用している場合これを実行しておかないと例外が起こることがある。
   * @returns {Promise<void>}
   */
  finalize(): Promise<void> {
    return new Promise<void>((resolve) => {
      this[Core].finalize();
      resolve();
    });
  }

  /**
   * メタ情報を取得する
   * 話者名や話者IDのリストを取得する
   * @returns {Promise<VoicevoxMetaJson>} メタ情報
   */
  metas(): Promise<VoicevoxMetaJson> {
    return new Promise<VoicevoxMetaJson>((resolve) => {
      const { result } = this[Core].metas();
      resolve(JSON.parse(result));
    });
  }

  /**
   * 対応デバイス情報を取得する
   * cpu, cudaのうち、使用可能なデバイス情報を取得する
   * @returns {Promise<VoicevoxSupportedDevicesJson>} 各デバイスが使用可能かどうか
   */
  supportedDevices(): Promise<VoicevoxSupportedDevicesJson> {
    return new Promise<VoicevoxSupportedDevicesJson>((resolve) => {
      const { result } = this[Core].supportedDevices();
      resolve(JSON.parse(result));
    });
  }

  /**
   * 音素ごとの長さを求める
   * 音素列から、音素ごとの長さを求める
   * @param {Array<bigint>} phonemeList 音素列
   * @param {number} speakerId 話者番号
   * @returns {Promise<Array<number>>} 音素ごとの長さ
   */
  yukarinSForward(phonemeList: Array<bigint>, speakerId: number): Promise<Array<number>> {
    return new Promise<Array<number>>((resolve) => {
      checkValidArray(phonemeList, "phonemeList", "bigint");
      checkValidNumber(speakerId, "speakerId", true);
      const { result, result2 } = this[Core].yukarinSForward(phonemeList, speakerId);
      if (!result2) throw new VoicevoxError(this[Core].lastErrorMessage().result);
      resolve(result);
    });
  }

  /**
   * モーラごとの音高を求める
   * モーラごとの音素列とアクセント情報から、モーラごとの音高を求める
   * @param {Array<bigint>} vowelPhonemeList 母音の音素列
   * @param {Array<bigint>} consonantPhonemeList 子音の音素列
   * @param {Array<bigint>} startAccentList アクセントの開始位置
   * @param {Array<bigint>} endAccentList アクセントの終了位置
   * @param {Array<bigint>} startAccentPhraseList アクセント句の開始位置
   * @param {Array<bigint>} endAccentPhraseList アクセント句の終了位置
   * @param {number} speakerId 話者番号
   * @returns {Promise<Array<number>>} モーラごとの音高
   */
  yukarinSaForward(vowelPhonemeList: Array<bigint>, consonantPhonemeList: Array<bigint>, startAccentList: Array<bigint>, endAccentList: Array<bigint>, startAccentPhraseList: Array<bigint>, endAccentPhraseList: Array<bigint>, speakerId: number): Promise<Array<number>> {
    return new Promise<Array<number>>((resolve) => {
      checkValidArray(vowelPhonemeList, "vowelPhonemeList", "bigint");
      checkValidArray(consonantPhonemeList, "consonantPhonemeList", "bigint");
      checkValidArray(startAccentList, "startAccentList", "bigint");
      checkValidArray(endAccentList, "endAccentList", "bigint");
      checkValidArray(startAccentPhraseList, "startAccentPhraseList", "bigint");
      checkValidArray(endAccentPhraseList, "endAccentPhraseList", "bigint");
      checkValidNumber(speakerId, "speakerId", true);
      const { result, result2 } = this[Core].yukarinSaForward(vowelPhonemeList, consonantPhonemeList, startAccentList, endAccentList, startAccentPhraseList, endAccentPhraseList, speakerId);
      if (!result2) throw new VoicevoxError(this[Core].lastErrorMessage().result);
      resolve(result);
    });
  }

  /**
   * 波形を求める
   * @param {Array<number>} f0 フレームごとの音高
   * @param {Array<number>} phoneme フレームごとの音素
   * @param {number} speakerId 話者番号
   * @returns {Promise<Array<number>>} 音声波形
   */
  decodeForward(f0: Array<number>, phoneme: Array<number>, speakerId: number): Promise<Array<number>> {
    return new Promise<Array<number>>((resolve) => {
      checkValidArray(f0, "f0", "number", false);
      checkValidArray(phoneme, "phoneme", "number", false);
      checkValidNumber(speakerId, "speakerId", true);
      const { result, result2 } = this[Core].decodeForward(f0, phoneme, speakerId);
      if (!result2) throw new VoicevoxError(this[Core].lastErrorMessage().result);
      resolve(result);
    });
  }

  /**
   * open jtalkの辞書を読み込む
   * @param {string} dictPath
   * @returns {Promise<void>}
   */
  voicevoxLoadOpenjtalkDict(dictPath: string): Promise<void> {
    return new Promise<void>((resolve) => {
      const { resultCode } = this[Core].voicevoxLoadOpenjtalkDict(dictPath);
      if (resultCode !== VoicevoxResultCodeV12.VOICEVOX_RESULT_SUCCEED) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve();
    });
  }

  /**
   * text to spearchを実行する
   * @param {string} text 音声データに変換するtextデータ
   * @param {number} speakerId 話者番号
   * @returns {Promise<Buffer>} 音声データ
   */
  voicevoxTts(text: string, speakerId: number): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      checkValidString(text, "text");
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxTtsV12(text, speakerId);
      if (resultCode !== VoicevoxResultCodeV12.VOICEVOX_RESULT_SUCCEED) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(result);
    });
  }

  /**
   * text to spearchをAquesTalkライクな記法で実行する
   * @param {string} text 音声データに変換するtextデータ
   * @param {number} speakerId 話者番号
   * @returns {Promise<Buffer>} 音声データ
   */
  voicevoxTtsFromKana(text: string, speakerId: number): Promise<Buffer> {
    return new Promise<Buffer>((resolve) => {
      checkValidString(text, "text");
      checkValidNumber(speakerId, "speakerId", true);
      const { result, resultCode } = this[Core].voicevoxTtsFromKana(text, speakerId);
      if (resultCode !== VoicevoxResultCodeV12.VOICEVOX_RESULT_SUCCEED) throw new VoicevoxError(this[Core].voicevoxErrorResultToMessage(resultCode).result);
      resolve(result);
    });
  }
}