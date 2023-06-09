import bindings from "bindings";
const voicevoxCore: VoicevoxCore = bindings("voicevox");

/**
 * voicevox_coreの利用を開始する
 * - 実行しないとvoicevoxを利用できません
 * @param dlPath 動的ライブラリへのパス
 *
 */
export const initialize = (dlPath: string) =>
  new Promise<void>((resolve, reject) => {
    const { error } = voicevoxCore.initialize(String(dlPath));
    if (error) return reject(error);
    return resolve();
  });

/**
 * voicevox_coreの利用を終了する
 * - 実行するとvoicevoxを利用ができなくなります
 * - 再度initializeを実行すると利用できます
 */
export const finalize = () =>
  new Promise<void>((resolve, reject) => {
    const { error } = voicevoxCore.finalize();
    if (error) return reject(error);
    return resolve();
  });

export const core = {
  /**
   * 初期化する
   * @param options 初期化オプション
   */
  voicevoxInitialize: (options: VoicevoxInitializeOptions) =>
    new Promise<void>((resolve, reject) => {
      const { error } = voicevoxCore.voicevoxInitialize(
        options.accelerationMode,
        options.cpuNumThreads,
        options.loadAllModels,
        options.openJTalkDictDir
      );
      if (error) return reject(error);
      return resolve();
    }),
  /**
   * voicevoxのバージョンを取得する
   * @return SemVerでフォーマットされたバージョン
   */
  voicevoxGetVersion: () =>
    new Promise<string>((resolve, reject) => {
      const { error, result } = voicevoxCore.voicevoxGetVersion();
      if (error) return reject(error);
      return resolve(result);
    }),
  /**
   * モデルを読み込む
   * @param speakerId 読み込むモデルの話者ID
   */
  voicevoxLoadModel: (speakerId: number) =>
    new Promise<void>((resolve, reject) => {
      const { error } = voicevoxCore.voicevoxLoadModel(Number(speakerId));
      if (error) return reject(error);
      return resolve();
    }),
  /**
   * ハードウェアアクセラレーションがGPUモードか判定する
   * @return GPUモードならtrue、そうでないならfalse
   */
  voicevoxIsGpuMode: () =>
    new Promise<boolean>((resolve, reject) => {
      const { error, result } = voicevoxCore.voicevoxIsGpuMode();
      if (error) return reject(error);
      return resolve(result);
    }),
  /**
   * 指定したspeaker_idのモデルが読み込まれているか判定する
   * @return モデルが読み込まれているのであればtrue、そうでないならfalse
   */
  voicevoxIsModelLoaded: (speakerId: number) =>
    new Promise<boolean>((resolve, reject) => {
      const { error, result } = voicevoxCore.voicevoxIsModelLoaded(speakerId);
      if (error) return reject(error);
      return resolve(result);
    }),
  /**
   * このライブラリの利用を終了し、確保しているリソースを解放する
   */
  voicevoxFinalize: () =>
    new Promise<void>((resolve, reject) => {
      const { error } = voicevoxCore.voicevoxFinalize();
      if (error) return reject(error);
      return resolve();
    }),
  /**
   * メタ情報を取得する
   * @return メタ情報
   */
  voicevoxGetMetas: <T extends boolean>(getJsonString?: T) =>
    new Promise<T extends true ? string : Array<VoicevoxMeta>>(
      (resolve, reject) => {
        const { error, result } = voicevoxCore.voicevoxGetMetasJson();
        if (error) return reject(error);
        return resolve(getJsonString ? result : JSON.parse(result));
      }
    ),
  /**
   * サポートデバイス情報を取得する
   * @return サポートデバイス情報
   */
  voicevoxGetSupportedDevices: <T extends boolean>(getJsonString?: T) =>
    new Promise<T extends true ? string : VoicevoxSupportedDevices>(
      (resolve, reject) => {
        const { error, result } =
          voicevoxCore.voicevoxGetSupportedDevicesJson();
        if (error) return reject(error);
        return resolve(getJsonString ? result : JSON.parse(result));
      }
    ),
  /**
   * AudioQuery を実行する
   * @param text テキスト
   * @param speakerId 話者ID
   * @param options AudioQueryのオプション
   * @return AudioQuery
   */
  voicevoxAudioQuery: <T extends boolean>(
    text: string,
    speakerId: number,
    options: VoicevoxAudioQueryOptions,
    getJsonString?: T
  ) =>
    new Promise<T extends true ? string : VoicevoxAudioQuery>(
      (resolve, reject) => {
        const { error, result } = voicevoxCore.voicevoxAudioQuery(
          String(text),
          Number(speakerId),
          Boolean(options.kana)
        );
        if (error) return reject(error);
        return resolve(getJsonString ? result : JSON.parse(result));
      }
    ),
  /**
   * AudioQuery から音声合成する
   * @param audioQueryJson AudioQuery
   * @param speakerId  話者ID
   * @param options AudioQueryから音声合成オプション
   * @return wavデータ
   */
  voicevoxSynthesis: (
    audioQueryJson: string | VoicevoxAudioQuery,
    speakerId: number,
    options: VoicevoxSynthesisOptions
  ) =>
    new Promise<Buffer>((resolve, reject) => {
      const { error, result } = voicevoxCore.voicevoxSynthesis(
        typeof audioQueryJson === "object"
          ? JSON.stringify(audioQueryJson)
          : String(audioQueryJson),
        speakerId,
        options.enableInterrogativeUpspeak
      );
      if (error) return reject(error);
      return resolve(result);
    }),
};

interface VoicevoxCore {
  initialize: (dlPath: string) => InitializeResult;
  finalize: () => FinalizeResult;
  voicevoxInitialize: (
    accelerationMode: number,
    cpuNumThreads: number,
    loadAllModels: boolean,
    openJTalkDictDir: string
  ) => VoicevoxInitializeResult;
  voicevoxGetVersion: () => VoicevoxGetVersionsResult;
  voicevoxLoadModel: (speakerId: number) => VoicevoxLoadModelResult;
  voicevoxIsGpuMode: () => VoicevoxIsGpuModeResult;
  voicevoxIsModelLoaded: (speakerId: number) => VoicevoxIsModelLoadedResult;
  voicevoxFinalize: () => VoicevoxFinalizeResult;
  voicevoxGetMetasJson: () => VoicevoxGetMetasJsonResult;
  voicevoxGetSupportedDevicesJson: () => VoicevoxGetSupportedDevicesResult;
  voicevoxAudioQuery: (
    text: string,
    speakerId: number,
    kana: boolean
  ) => VoicevoxAudioQueryResult;
  voicevoxSynthesis: (
    audioQueryJson: string,
    speakerId: number,
    enableInterrogativeUpspeak: boolean
  ) => VoicevoxSynthesisResult;
}
interface Result {
  error: string;
}
interface InitializeResult extends Result {}
interface FinalizeResult extends Result {}
interface VoicevoxInitializeResult extends Result {}
interface VoicevoxGetVersionsResult extends Result {
  result: string;
}
interface VoicevoxLoadModelResult extends Result {}
interface VoicevoxIsGpuModeResult extends Result {
  result: boolean;
}
interface VoicevoxIsModelLoadedResult extends Result {
  result: boolean;
}
interface VoicevoxFinalizeResult extends Result {}
interface VoicevoxGetMetasJsonResult extends Result {
  result: string;
}
interface VoicevoxGetSupportedDevicesResult extends Result {
  result: string;
}
interface VoicevoxAudioQueryResult extends Result {
  result: string;
}
interface VoicevoxSynthesisResult extends Result {
  result: Buffer;
}

/**
 * 初期化オプション
 */
export interface VoicevoxInitializeOptions {
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
  openJTalkDictDir: string;
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
 * Audio query のオプション
 */
export interface VoicevoxAudioQueryOptions {
  /**
   * aquestalk形式のkanaとしてテキストを解釈する
   */
  kana: boolean;
}

/**
 * `voicevoxSynthesis` のオプション
 */
export interface VoicevoxSynthesisOptions {
  /**
   * 疑問文の調整を有効にする
   */
  enableInterrogativeUpspeak: boolean;
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
