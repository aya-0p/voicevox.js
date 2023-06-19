import bindings from "bindings";
const sharevoxCore: SharevoxCore = bindings("sharevox");

/**
 * sharevox_coreの利用を開始する
 * - 実行しないとsharevoxを利用できません
 * @param dlPath 動的ライブラリへのパス
 *
 */
export const initialize = (dlPath: string) =>
  new Promise<void>((resolve, reject) => {
    const { error } = sharevoxCore.initialize(String(dlPath));
    if (error) return reject(error);
    return resolve();
  });

/**
 * sharevox_coreの利用を終了する
 * - 実行するとsharevoxを利用ができなくなります
 * - 再度initializeを実行すると利用できます
 */
export const finalize = () =>
  new Promise<void>((resolve, reject) => {
    const { error } = sharevoxCore.finalize();
    if (error) return reject(error);
    return resolve();
  });

export const core = {
  /**
   * 初期化する
   * @param options 初期化オプション
   */
  sharevoxInitialize: (options: SharevoxInitializeOptions) =>
    new Promise<void>((resolve, reject) => {
      const { error } = sharevoxCore.sharevoxInitialize(
        options.accelerationMode,
        options.cpuNumThreads,
        options.loadAllModels,
        options.openJTalkDictDir
      );
      if (error) return reject(error);
      return resolve();
    }),
  /**
   * sharevoxのバージョンを取得する
   * @return SemVerでフォーマットされたバージョン
   */
  sharevoxGetVersion: () =>
    new Promise<string>((resolve, reject) => {
      const { error, result } = sharevoxCore.sharevoxGetVersion();
      if (error) return reject(error);
      return resolve(result);
    }),
  /**
   * モデルを読み込む
   * @param speakerId 読み込むモデルの話者ID
   */
  sharevoxLoadModel: (speakerId: number) =>
    new Promise<void>((resolve, reject) => {
      const { error } = sharevoxCore.sharevoxLoadModel(Number(speakerId));
      if (error) return reject(error);
      return resolve();
    }),
  /**
   * ハードウェアアクセラレーションがGPUモードか判定する
   * @return GPUモードならtrue、そうでないならfalse
   */
  sharevoxIsGpuMode: () =>
    new Promise<boolean>((resolve, reject) => {
      const { error, result } = sharevoxCore.sharevoxIsGpuMode();
      if (error) return reject(error);
      return resolve(result);
    }),
  /**
   * 指定したspeaker_idのモデルが読み込まれているか判定する
   * @return モデルが読み込まれているのであればtrue、そうでないならfalse
   */
  sharevoxIsModelLoaded: (speakerId: number) =>
    new Promise<boolean>((resolve, reject) => {
      const { error, result } = sharevoxCore.sharevoxIsModelLoaded(speakerId);
      if (error) return reject(error);
      return resolve(result);
    }),
  /**
   * このライブラリの利用を終了し、確保しているリソースを解放する
   */
  sharevoxFinalize: () =>
    new Promise<void>((resolve, reject) => {
      const { error } = sharevoxCore.sharevoxFinalize();
      if (error) return reject(error);
      return resolve();
    }),
  /**
   * メタ情報を取得する
   * @return メタ情報
   */
  sharevoxGetMetas: <T extends boolean>(getJsonString?: T) =>
    new Promise<T extends true ? string : Array<SharevoxMeta>>(
      (resolve, reject) => {
        const { error, result } = sharevoxCore.sharevoxGetMetasJson();
        if (error) return reject(error);
        return resolve(getJsonString ? result : JSON.parse(result));
      }
    ),
  /**
   * サポートデバイス情報を取得する
   * @return サポートデバイス情報
   */
  sharevoxGetSupportedDevices: <T extends boolean>(getJsonString?: T) =>
    new Promise<T extends true ? string : SharevoxSupportedDevices>(
      (resolve, reject) => {
        const { error, result } =
          sharevoxCore.sharevoxGetSupportedDevicesJson();
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
  sharevoxAudioQuery: <T extends boolean>(
    text: string,
    speakerId: number,
    options: SharevoxAudioQueryOptions,
    getJsonString?: T
  ) =>
    new Promise<T extends true ? string : SharevoxAudioQuery>(
      (resolve, reject) => {
        const { error, result } = sharevoxCore.sharevoxAudioQuery(
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
  sharevoxSynthesis: (
    audioQueryJson: string | SharevoxAudioQuery,
    speakerId: number,
    options: SharevoxSynthesisOptions
  ) =>
    new Promise<Buffer>((resolve, reject) => {
      const { error, result } = sharevoxCore.sharevoxSynthesis(
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

interface SharevoxCore {
  initialize: (dlPath: string) => InitializeResult;
  finalize: () => FinalizeResult;
  sharevoxInitialize: (
    accelerationMode: number,
    cpuNumThreads: number,
    loadAllModels: boolean,
    openJTalkDictDir: string
  ) => SharevoxInitializeResult;
  sharevoxGetVersion: () => SharevoxGetVersionsResult;
  sharevoxLoadModel: (speakerId: number) => SharevoxLoadModelResult;
  sharevoxIsGpuMode: () => SharevoxIsGpuModeResult;
  sharevoxIsModelLoaded: (speakerId: number) => SharevoxIsModelLoadedResult;
  sharevoxFinalize: () => SharevoxFinalizeResult;
  sharevoxGetMetasJson: () => SharevoxGetMetasJsonResult;
  sharevoxGetSupportedDevicesJson: () => SharevoxGetSupportedDevicesResult;
  sharevoxAudioQuery: (
    text: string,
    speakerId: number,
    kana: boolean
  ) => SharevoxAudioQueryResult;
  sharevoxSynthesis: (
    audioQueryJson: string,
    speakerId: number,
    enableInterrogativeUpspeak: boolean
  ) => SharevoxSynthesisResult;
}
interface Result {
  error: string;
}
interface InitializeResult extends Result {}
interface FinalizeResult extends Result {}
interface SharevoxInitializeResult extends Result {}
interface SharevoxGetVersionsResult extends Result {
  result: string;
}
interface SharevoxLoadModelResult extends Result {}
interface SharevoxIsGpuModeResult extends Result {
  result: boolean;
}
interface SharevoxIsModelLoadedResult extends Result {
  result: boolean;
}
interface SharevoxFinalizeResult extends Result {}
interface SharevoxGetMetasJsonResult extends Result {
  result: string;
}
interface SharevoxGetSupportedDevicesResult extends Result {
  result: string;
}
interface SharevoxAudioQueryResult extends Result {
  result: string;
}
interface SharevoxSynthesisResult extends Result {
  result: Buffer;
}

/**
 * 初期化オプション
 */
export interface SharevoxInitializeOptions {
  /**
   * ハードウェアアクセラレーションモード
   */
  accelerationMode: SharevoxAccelerationMode;
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
export enum SharevoxAccelerationMode {
  /**
   * 実行環境に合った適切なハードウェアアクセラレーションモードを選択する
   */
  SHAREVOX_ACCELERATION_MODE_AUTO = 0,
  /**
   * ハードウェアアクセラレーションモードを"CPU"に設定する
   */
  SHAREVOX_ACCELERATION_MODE_CPU = 1,
  /**
   * ハードウェアアクセラレーションモードを"GPU"に設定する
   */
  SHAREVOX_ACCELERATION_MODE_GPU = 2,
}

/**
 * Audio query のオプション
 */
export interface SharevoxAudioQueryOptions {
  /**
   * aquestalk形式のkanaとしてテキストを解釈する
   */
  kana: boolean;
}

/**
 * `sharevoxSynthesis` のオプション
 */
export interface SharevoxSynthesisOptions {
  /**
   * 疑問文の調整を有効にする
   */
  enableInterrogativeUpspeak: boolean;
}
/**
 * メタ情報
 */
interface SharevoxMeta {
  /**
   * 名前
   */
  name: string;
  /**
   * スピーカースタイルの一覧
   */
  styles: Array<SharevoxSpeakerStyle>;
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
interface SharevoxSpeakerStyle {
  /**
   * スタイル名
   */
  name: string;
  /**
   * スタイルID
   */
  id: number;
}
interface SharevoxSupportedDevices {
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
interface SharevoxAudioQuery {
  /**
   * アクセント句のリスト
   */
  accent_phrases: Array<SharevoxAccentPhrase>;
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
interface SharevoxAccentPhrase {
  /**
   * モーラのリスト
   */
  moras: Array<SharevoxMora>;
  /**
   * アクセント箇所
   */
  accent: number;
  /**
   * 後ろに無音を付けるかどうか
   * モーラ（子音＋母音）ごとの情報
   */
  pause_mora: null | SharevoxMora;
  /**
   * 疑問系かどうか
   */
  is_interrogative: boolean;
}

/**
 * モーラ
 */
interface SharevoxMora {
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
