import * as voicevoxCore from "./voicevox"
/**
 * デフォルトの初期化オプションを生成する
 * @return デフォルト値が設定された初期化オプション
 */
export function makeDefaultInitializeOptions(): VoicevoxInitializeOptions {
  return {
    accelerationMode: VoicevoxAccelerationMode.VOICEVOX_ACCELERATION_MODE_AUTO,
    cpuNumThreads: 0,
    loadAllModels: true,
    openJTalkDir: ""
  };
}

/**
 * 初期化する
 * @param options 初期化オプション
 */
export function initializeSync(options: VoicevoxInitializeOptions): void {
  const result = voicevoxCore.initialize(
    options.accelerationMode, 
    options.cpuNumThreads, 
    options.loadAllModels, 
    options.openJTalkDir
  ) as VoicevoxResultCode;
  if (result !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new Error(voicevoxCore.errorResultToMessage(result));
  return;
}

/**
 * 初期化する
 * @param options 初期化オプション
 */
export function initialize(options: VoicevoxInitializeOptions): Promise<void> {
  return new Promise<void>((resolve, reject) => {
    const result = voicevoxCore.initialize(
      options.accelerationMode, 
      options.cpuNumThreads, 
      options.loadAllModels, 
      options.openJTalkDir
    ) as VoicevoxResultCode;
    if (result !== VoicevoxResultCode.VOICEVOX_RESULT_OK) return reject(new Error(voicevoxCore.errorResultToMessage(result)));
    return resolve();
  })
}

/**
 * voicevoxのバージョンを取得する
 * @return SemVerでフォーマットされたバージョン
 */
export function getVersion(): string {
  return voicevoxCore.getVersion();
}

/**
 * モデルを読み込む
 * @param speakerId 読み込むモデルの話者ID
 */
export function loadModelSync(speakerId: number): void {
  const result = voicevoxCore.loadModel(speakerId) as VoicevoxResultCode;
  if (result !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new Error(voicevoxCore.errorResultToMessage(result));
  return;
}

/**
 * モデルを読み込む
 * @param speakerId 読み込むモデルの話者ID
 */
export function loadModel(speakerId: number): Promise<void> {
  return new Promise<void>((resolve, reject) => {
    const result = voicevoxCore.loadModel(speakerId) as VoicevoxResultCode;
    if (result !== VoicevoxResultCode.VOICEVOX_RESULT_OK) return reject(new Error(voicevoxCore.errorResultToMessage(result)));
    return resolve();
  });
}

/**
 * ハードウェアアクセラレーションがGPUモードか判定する
 * @return GPUモードならtrue、そうでないならfalse
 */
export function isGpuMode(): boolean {
  return voicevoxCore.isGpuMode();
}

/**
 * 指定したspeaker_idのモデルが読み込まれているか判定する
 * @return モデルが読み込まれているのであればtrue、そうでないならfalse
 */
export function isModelLoaded(speakerId: number): boolean {
  return voicevoxCore.isModelLoaded(speakerId);
}

/**
 * このライブラリの利用を終了し、確保しているリソースを解放する
 */
export function finalize(): void {
  voicevoxCore.finalize();
}

/**
 * メタ情報をjsonで取得する
 * @return メタ情報のjson
 */
export function getMetasJson(): Array<VoicevoxMeta> {
  return JSON.parse(voicevoxCore.getMetasJson());
}

/**
 * サポートデバイス情報をjsonで取得する
 * @return サポートデバイス情報のjson
 */
export function getSupportedDevicesJson(): VoicevoxSupportedDevices {
  return JSON.parse(voicevoxCore.getSupportedDevicesJson());
}

/**
 * デフォルトの AudioQuery のオプションを生成する
 * @return デフォルト値が設定された AudioQuery オプション
 */
export function makeDefaultAudioQueryOptions(): VoicevoxAudioQueryOptions {
  return {
    kana: false
  };
}

/**
 * AudioQuery を実行する
 * @param text テキスト
 * @param speakerId 話者ID
 * @param options AudioQueryのオプション
 * @return AudioQuery を json でフォーマットしたもの
 */
export function audioQuerySync(
  text: string,
  speakerId: number,
  options: VoicevoxAudioQueryOptions
): VoicevoxAudioQuery {
  const { result, output } = voicevoxCore.audioQuery(text, speakerId, options.kana);
  if ((result as VoicevoxResultCode) !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new Error(voicevoxCore.errorResultToMessage(result));
  return JSON.parse(output);
}

/**
 * AudioQuery を実行する
 * @param text テキスト
 * @param speakerId 話者ID
 * @param options AudioQueryのオプション
 * @return AudioQuery を json でフォーマットしたもの
 */
export function audioQuery(
  text: string,
  speakerId: number,
  options: VoicevoxAudioQueryOptions
): Promise<VoicevoxAudioQuery> {
  return new Promise<VoicevoxAudioQuery>((resolve, reject) => {
    const { result, output } = voicevoxCore.audioQuery(text, speakerId, options.kana);
    if ((result as VoicevoxResultCode) !== VoicevoxResultCode.VOICEVOX_RESULT_OK) return reject(new Error(voicevoxCore.errorResultToMessage(result)));
    return resolve(JSON.parse(output));
  })
}

/**
 * デフォルトの `voicevox_synthesis` のオプションを生成する
 * @return デフォルト値が設定された `voicevox_synthesis` のオプション
 */
export function makeDefaultSynthesisOptions(): VoicevoxSynthesisOptions {
  return {
    enableInterrogativeUpspeak: true
  }
}

/**
 * AudioQuery から音声合成する
 * @param audioQueryJson jsonフォーマットされた AudioQuery
 * @param speakerId  話者ID
 * @param options AudioQueryから音声合成オプション
 * @return wav データ
 */
export function synthesisSync(
  audioQueryJson: VoicevoxAudioQuery | string,
  speakerId: number,
  options: VoicevoxSynthesisOptions
): Buffer {
  const { result, output } = voicevoxCore.synthesis(
    typeof audioQueryJson === "string" ? audioQueryJson : JSON.stringify(audioQueryJson),
    speakerId,
    options.enableInterrogativeUpspeak
  );
  if ((result as VoicevoxResultCode) !== VoicevoxResultCode.VOICEVOX_RESULT_OK) throw new Error(voicevoxCore.errorResultToMessage(result));
  return output;
}

/**
 * AudioQuery から音声合成する
 * @param audioQueryJson jsonフォーマットされた AudioQuery
 * @param speakerId  話者ID
 * @param options AudioQueryから音声合成オプション
 * @return wav データ
 */
export function synthesis(
  audioQueryJson: VoicevoxAudioQuery | string,
  speakerId: number,
  options: VoicevoxSynthesisOptions
): Promise<Buffer> {
  return new Promise<Buffer>((resolve, reject) => {
    const { result, output } = voicevoxCore.synthesis(
      typeof audioQueryJson === "string" ? audioQueryJson : JSON.stringify(audioQueryJson),
      speakerId,
      options.enableInterrogativeUpspeak
    );
    if ((result as VoicevoxResultCode) !== VoicevoxResultCode.VOICEVOX_RESULT_OK) return reject(new Error(voicevoxCore.errorResultToMessage(result)));
    return resolve(output);
  })
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
   * CPU利用数を指定
   * 0を指定すると環境に合わせたCPUが利用される
   */
  cpuNumThreads: number;
  /**
   * 全てのモデルを読み込む
   */
  loadAllModels: boolean;
  /**
   * open_jtalkの辞書ディレクトリ
   */
  openJTalkDir: string;
}

/**
 * ハードウェアアクセラレーションモードを設定する設定値
 */
export enum VoicevoxAccelerationMode {
  /**
   * 実行環境に合った適切なハードウェアアクセラレーションモードを選択する
   */
  VOICEVOX_ACCELERATION_MODE_AUTO = 0,
  /**
   * ハードウェアアクセラレーションモードを"CPU"に設定する
   */
  VOICEVOX_ACCELERATION_MODE_CPU = 1,
  /**
   * ハードウェアアクセラレーションモードを"GPU"に設定する
   */
  VOICEVOX_ACCELERATION_MODE_GPU = 2,
}

/**
 * メタ情報
 */
interface VoicevoxMeta {
  /**
   * 名前
   */
  name: string;
  /**
   * スピーカースタイルの一覧
   */
  styles: Array<VoicevoxSpeakerStyle>;
  /**
   * スピーカーのUUID
   */
  speaker_uuid: string;
  /**
   * スピーカーのバージョン
   */
  version: string;
}

/**
 * スピーカースタイル
 */
interface VoicevoxSpeakerStyle {
  /**
   * スタイル名
   */
  name: string;
  /**
   * スタイルID
   */
  id: number;
}

interface VoicevoxSupportedDevices {
  /**
   * CPUに対応しているか
   */
  cpu: boolean;
  /**
   * CUDA(Nvidia GPU)に対応しているか
   */
  cuda: boolean;
  /**
   * DirectML(Nvidia GPU/Radeon GPU等)に対応しているか
   */
  dml: boolean;
}

/**
 * 音声合成クエリ
 */
interface VoicevoxAudioQuery {
  /**
   * アクセント句のリスト
   */
  accent_phrases: Array<VoicevoxAccentPhrase>;
  /**
   * 全体の話速
   */
  speed_scale: number;
  /**
   * 全体の音高
   */
  pitch_scale: number;
  /**
   * 全体の抑揚
   */
  intonation_scale: number;
  /**
   * 全体の音量
   */
  volume_scale: number;
  /**
   * 音声の前の無音時間
   */
  pre_phoneme_length: number;
  /**
   * 音声の後の無音時間
   */
  post_phoneme_length: number;
  /**
   * 音声データの出力サンプリングレート
   */
  output_sampling_rate: number;
  /**
   * 音声データをステレオ出力するか否か
   */
  output_stereo: boolean;
  /**
   * AquesTalkライクな読み仮名
   */
  kana: string;
}

/**
 * アクセント句
 */
interface VoicevoxAccentPhrase {
  /**
   * モーラのリスト
   */
  moras: Array<VoicevoxMora>;
  /**
   * アクセント箇所
   */
  accent: number;
  /**
   * 後ろに無音を付けるかどうか
   * モーラ（子音＋母音）ごとの情報
   */
  pause_mora: null | VoicevoxMora;
  /**
   * 疑問系かどうか
   */
  is_interrogative: boolean;
}

/**
 * モーラ
 */
interface VoicevoxMora {
  /**
   * 文字
   */
  text: string;
  /**
   * 子音の音素
   */
  consonant: null | string;
  /**
   * 子音の音長
   */
  consonant_length: null | number;
  /**
   * 母音の音素
   */
  vowel: string;
  /**
   * 母音の音長
   */
  vowel_length: number;
  /**
   * 音高
   */
  pitch: number;
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

/**
 * `voicevox_synthesis` のオプション
 */
interface VoicevoxSynthesisOptions {
  /**
   * 疑問文の調整を有効にする
   */
  enableInterrogativeUpspeak: boolean;
}

/**
 * 処理結果を示す結果コード
 */
enum VoicevoxResultCode {
  /**
   * 成功
   */
  VOICEVOX_RESULT_OK = 0,
  /**
   * open_jtalk辞書ファイルが読み込まれていない
   */
  VOICEVOX_RESULT_NOT_LOADED_OPENJTALK_DICT_ERROR = 1,
  /**
   * modelの読み込みに失敗した
   */
  VOICEVOX_RESULT_LOAD_MODEL_ERROR = 2,
  /**
   * サポートされているデバイス情報取得に失敗した
   */
  VOICEVOX_RESULT_GET_SUPPORTED_DEVICES_ERROR = 3,
  /**
   * GPUモードがサポートされていない
   */
  VOICEVOX_RESULT_GPU_SUPPORT_ERROR = 4,
  /**
   * メタ情報読み込みに失敗した
   */
  VOICEVOX_RESULT_LOAD_METAS_ERROR = 5,
  /**
   * ステータスが初期化されていない
   */
  VOICEVOX_RESULT_UNINITIALIZED_STATUS_ERROR = 6,
  /**
   * 無効なspeaker_idが指定された
   */
  VOICEVOX_RESULT_INVALID_SPEAKER_ID_ERROR = 7,
  /**
   * 無効なmodel_indexが指定された
   */
  VOICEVOX_RESULT_INVALID_MODEL_INDEX_ERROR = 8,
  /**
   * 推論に失敗した
   */
  VOICEVOX_RESULT_INFERENCE_ERROR = 9,
  /**
   * コンテキストラベル出力に失敗した
   */
  VOICEVOX_RESULT_EXTRACT_FULL_CONTEXT_LABEL_ERROR = 10,
  /**
   * 無効なutf8文字列が入力された
   */
  VOICEVOX_RESULT_INVALID_UTF8_INPUT_ERROR = 11,
  /**
   * aquestalk形式のテキストの解析に失敗した
   */
  VOICEVOX_RESULT_PARSE_KANA_ERROR = 12,
  /**
   * 無効なAudioQuery
   */
  VOICEVOX_RESULT_INVALID_AUDIO_QUERY_ERROR = 13,
}