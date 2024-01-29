/**
 * 無料で使える中品質なテキスト読み上げソフトウェア、VOICEVOXのコア。
 *
 * # 注意
 * - 型には忠実に守ること
 * - 関数の引数の数は合わせること
 * - ポインタ名は同じ種類同士でかぶらないこと
 *   - なお、別のものとはかぶっても良い
 * - ポインタ名(voicevox_core version 0.16.x\~)はC++における`uint32_t`(`unsigned int`, 0\~4294967295)の範囲内であること
 *
 * これらの要件を満たさない場合即座にプログラムが終了する可能性がある
 */
export declare class VoicevoxCore {
  constructor(path: string);

  /**
   * OpenJtalkRc を<b>構築</b>(_construct_)する。
   *
   * 解放は voicevoxOpenJtalkRcDeleteV0_16 で行う。
   *
   * @param {string} openJtalkDicDir 辞書ディレクトリを指すUTF-8のパス
   * @param {number} openJtalkPointerName 構築先Open JTalkポインタ名
   *
   * @returns 結果コード
   *
   * \example{
   * ```js
   * voicevoxOpenJtalkRcNewV0_16("./open_jtalk_dic_utf_8-1.11", 0);
   * ```
   * }
   *
   * \safety{
   *  - `openJtalkPointerName`は他の`OpenJtalkRc`とかぶってはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxOpenJtalkRcNewV0_16(openJtalkDicDir: string, openJtalkPointerName: number): ResultCode;

  /**
   * OpenJtalkの使うユーザー辞書を設定する。
   *
   * この関数を呼び出した後にユーザー辞書を変更した場合、再度この関数を呼び出す必要がある。
   *
   * @param {number} openJtalkPointerName Open JTalkポインタ名
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   *
   * \safety{
   * - `openJtalkPointerName`は`voicevoxOpenJtalkRcNew`で設定したものでなければならず、また`voicevoxOpenJtalkRcDeleteV0_16`で解放されていてはいけない。
   * - `userDictPointerName`は`voicevoxUserDictNewV0_16`で設定したものでなければならず、また`voicevoxUserDictDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxOpenJtalkRcUseUserDictV0_16(openJtalkPointerName: number, userDictPointerName: number): ResultCode;

  /**
   * OpenJtalkRc を<b>破棄</b>(_destruct_)する。
   *
   * @param {number} openJtalkPointerName 破棄対象Open JTalkポインタ名
   *
   * \example{
   * ```js
   * voicevoxOpenJtalkRcDeleteV0_16(0);
   * ```
   * }
   *
   * \safety{
   * - `openJtalkPointerName`は`voicevoxOpenJtalkRcNew`で設定したものでなければならず、また既にこの関数で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxOpenJtalkRcDeleteV0_16(openJtalkPointerName: number): {};

  /**
   * voicevoxのバージョンを取得する。
   * @return SemVerでフォーマットされたバージョン。
   *
   * この関数はv0.14.x, v0.15.x, v0.16.xで利用できます
   */
  voicevoxGetVersionV0_14(): { result: string };

  /**
   * VVMファイルから VoicevoxVoiceModel を<b>構築</b>(_construct_)する。
   *
   * @param {string} path vvmファイルへのUTF-8のファイルパス
   * @param {number} modelPointerName 構築先ポインタ名
   *
   * @returns 結果コード
   *
   * \safety{
   * - `modelPointerName`は他の`VoicevoxVoiceModel`とかぶってはいけない
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxVoiceModelNewFromPathV0_16(path: string, modelPointerName: number): ResultCode;

  /**
   * VoicevoxVoiceModel からIDを取得する。
   *
   * @param {number} modelPointerName 音声モデルポインタ名
   *
   * @returns 音声モデルID
   *
   * \safety{
   * - `modelPointerName`は`voicevoxVoiceModelNewFromPathV0_16`で設定したものでなければならず、また`voicevoxVoiceModelDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxVoiceModelIdV0_16(modelPointerName: number): { result: string };

  /**
   * VoicevoxVoiceModel からメタ情報を取得する。
   *
   * @param {number} modelPointerName 音声モデルポインタ名
   *
   * @returns メタ情報のJSON文字列
   *
   * \safety{
   * - `modelPointerName`は`voicevoxVoiceModelNewFromPathV0_16`で設定したものでなければならず、また`voicevoxVoiceModelDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxVoiceModelGetMetasJsonV0_16(modelPointerName: number): { result: string };

  /**
   * VoicevoxVoiceModel を<b>破棄</b>(_destruct_)する。
   *
   * @param {number} modelPointerName 破棄対象音声モデルポインタ名
   *
   * \safety{
   * - `modelPointerName`は`voicevoxVoiceModelNewFromPathV0_16`で設定したものでなければならず、また既にこの関数で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxVoiceModelDeleteV0_16(modelPointerName: number): {};

  /**
   * VoicevoxSynthesizer を<b>構築</b>(_construct_)する。
   *
   * @param {number} openJtalkPointerName Open JTalkのポインタ名
   * @param {number} synthesizerPointerName 構築先音声シンセサイザポインタ名
   * @param {number} accelerationMode ハードウェアアクセラレーションモード
   * @param {number} cpuNumThreads CPU利用数を指定 0を指定すると環境に合わせたCPUが利用される
   *
   * @returns 結果コード
   *
   * \safety{
   * - `openJtalkPointerName`は`voicevoxOpenJtalkRcNew`で設定したものでなければならず、また`voicevoxOpenJtalkRcDeleteV0_16`で解放されていてはいけない。
   * - `synthesizerPointerName`は他の`VoicevoxSynthesizer`とかぶってはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerNewV0_16(openJtalkPointerName: number, synthesizerPointerName: number, accelerationMode: number, cpuNumThreads: number): ResultCode;

  /**
   * VoicevoxSynthesizer を<b>破棄</b>(_destruct_)する。
   *
   * @param {number} synthesizerPointerName 破棄対象音声シンセサイザポインタ名
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また既にこの関数で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerDeleteV0_16(synthesizerPointerName: number): {};

  /**
   * 音声モデルを読み込む。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {number} modelPointerName 音声モデルポインタ名
   *
   * @returns 結果コード
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   * - `modelPointerName`は`voicevoxVoiceModelNewFromPathV0_16`で設定したものでなければならず、また`voicevoxVoiceModelDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerLoadVoiceModelV0_16(synthesizerPointerName: number, modelPointerName: number): ResultCode;

  /**
   * 音声モデルの読み込みを解除する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} modelId 音声モデルID
   *
   * @returns 結果コード
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerUnloadVoiceModelV0_16(synthesizerPointerName: number, modelId: string): ResultCode;

  /**
   * ハードウェアアクセラレーションがGPUモードか判定する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   *
   * @returns GPUモードかどうか
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerIsGpuModeV0_16(synthesizerPointerName: number): { result: boolean };

  /**
   * 指定したIDの音声モデルが読み込まれているか判定する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} modelId 音声モデルID
   *
   * @returns モデルが読み込まれているかどうか
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerIsLoadedVoiceModelV0_16(synthesizerPointerName: number, modelId: string): { result: boolean };

  /**
   * 今読み込んでいる音声モデルのメタ情報を、JSONで取得する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   *
   * @return メタ情報のJSON文字列
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerCreateMetasJsonV0_16(synthesizerPointerName: number): { result: string };

  /**
   * このライブラリで利用可能なデバイスの情報を、JSONで取得する。
   *
   * あくまで本ライブラリが対応しているデバイスの情報であることに注意。GPUが使える環境ではなかったとしても`cuda`や`dml`は`true`を示しうる。
   *
   * @returns 結果コード, サポートデバイス情報のJSON文字列
   *
   * \example{
   * ```js
   * const { result, resultCode } = voicevoxCreateSupportedDevicesJsonV0_16();
   * ```
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxCreateSupportedDevicesJsonV0_16(): ResultCode & { result: string };

  /**
   * AquesTalk風記法から、AudioQueryをJSONとして生成する。
   *
   * 生成したJSON文字列を解放するには ::voicevox_json_free を使う。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} kana AquesTalk風記法
   * @param {number} styleId スタイルID
   *
   * @returns 結果コード, AudioQueryのJSON文字列
   *
   * \example{
   * ```js
   * const { result, resultCode } = voicevoxSynthesizerCreateAudioQueryFromKanaV0_16(
   *   0,
   *   "コンニチワ'",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   * }
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerCreateAudioQueryFromKanaV0_16(synthesizerPointerName: number, kana: string, styleId: number): ResultCode & { result: string };

  /**
   * 日本語テキストから、AudioQueryをJSONとして生成する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} text UTF-8の日本語テキスト
   * @param {number} styleId スタイルID
   *
   * @returns 結果コード, AudioQueryのJSON文字列
   *
   * \example{
   * ```js
   * const { result, resultCode } = voicevoxSynthesizerCreateAudioQueryV0_16(
   *   0,
   *   "こんにちは",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   * }
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerCreateAudioQueryV0_16(synthesizerPointerName: number, text: string, styleId: number): ResultCode & { result: string };

  /**
   * AquesTalk風記法から、AccentPhrase (アクセント句)の配列をJSON形式で生成する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} kana AquesTalk風記法
   * @param {number} styleId スタイルID
   *
   * @returns 結果コード, AccentPhraseの配列のJSON文字列
   *
   * \example{
   * ```js
   * const { result, resultCode } = voicevoxSynthesizerCreateAccentPhrasesFromKanaV0_16(
   *   0,
   *   "コンニチワ'",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   * }
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerCreateAccentPhrasesFromKanaV0_16(synthesizerPointerName: number, kana: string, styleId: number): ResultCode & { result: string };

  /**
   * 日本語テキストから、AccentPhrase (アクセント句)の配列をJSON形式で生成する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} text UTF-8の日本語テキスト
   * @param {number} styleId スタイルID
   *
   * @returns 結果コード, AccentPhraseの配列のJSON文字列
   *
   * \example{
   * ```js
   * const { result, resultCode } = voicevoxSynthesizerCreateAccentPhrasesV0_16(
   *   0,
   *   "こんにちは",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   * }
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerCreateAccentPhrasesV0_16(synthesizerPointerName: number, text: string, styleId: number): ResultCode & { result: string };

  /**
   * AccentPhraseの配列の音高・音素長を、特定の声で生成しなおす。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} accentPhrasesJson AccentPhraseの配列のJSON文字列
   * @param {number} styleId スタイルID
   *
   * @returns 結果コード, AccentPhraseの配列のJSON文字列
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerReplaceMoraDataV0_16(synthesizerPointerName: number, accentPhrasesJson: string, styleId: number): ResultCode & { result: string };

  /**
   * AccentPhraseの配列の音素長を、特定の声で生成しなおす。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} accentPhrasesJson AccentPhraseの配列のJSON文字列
   * @param {number} styleId スタイルID
   *
   * @returns 結果コード, AccentPhraseの配列のJSON文字列
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerReplacePhonemeLengthV0_16(synthesizerPointerName: number, accentPhrasesJson: string, styleId: number): ResultCode & { result: string };

  /**
   * AccentPhraseの配列の音高を、特定の声で生成しなおす。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} accentPhrasesJson AccentPhraseの配列のJSON文字列
   * @param {number} styleId スタイルID
   *
   * @returns 結果コード, AccentPhraseの配列のJSON文字列
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerReplaceMoraPitchV0_16(synthesizerPointerName: number, accentPhrasesJson: string, styleId: number): ResultCode & { result: string };

  /**
   * AudioQueryから音声合成を行う。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} audioQueryJson AudioQueryのJSON文字列
   * @param {number} styleId スタイルID
   * @param {boolean} enableInterrogativeUpspeak 疑問文の調整を有効にする
   *
   * @returns 結果コード, WAVデータ
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerSynthesisV0_16(synthesizerPointerName: number, audioQueryJson: string, styleId: number, enableInterrogativeUpspeak: boolean): ResultCode & { result: Buffer };

  /**
   * AquesTalk風記法から音声合成を行う。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} kana AquesTalk風記法
   * @param {number} styleId スタイルID
   * @param {boolean} enableInterrogativeUpspeak 疑問文の調整を有効にする
   *
   * @returns 結果コード, WAVデータ
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerTtsFromKanaV0_16(synthesizerPointerName: number, kana: string, styleId: number, enableInterrogativeUpspeak: boolean): ResultCode & { result: Buffer };

  /**
   * 日本語テキストから音声合成を行う。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} text UTF-8の日本語テキスト
   * @param {number} styleId スタイルID
   * @param {boolean} enableInterrogativeUpspeak 疑問文の調整を有効にする
   *
   * @returns 結果コード, WAVデータ
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNewV0_16`で設定したものでなければならず、また`voicevoxSynthesizerDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxSynthesizerTtsV0_16(synthesizerPointerName: number, text: string, styleId: number, enableInterrogativeUpspeak: boolean): ResultCode & { result: Buffer };

  /**
   * 結果コードに対応したメッセージ文字列を取得する。
   *
   * @param {number} resultCode 結果コード
   *
   * @returns 結果コードに対応したメッセージ文字列
   *
   * \examples{
   * ```js
   * const actual = voicevoxErrorResultToMessageV0_12(VOICEVOX_RESULT_OK);
   * const EXPECTED = "エラーが発生しませんでした";
   * actual === EXPECTED; // true
   * ```
   * --
   * ```js
   * const actual = voicevoxErrorResultToMessageV0_12(VOICEVOX_RESULT_LOAD_MODEL_ERROR);
   * const EXPECTED = "modelデータ読み込みに失敗しました";
   * actual === EXPECTED; // true
   * ```
   * }
   *
   * この関数はv0.12.x, v0.13.x, v0.14.x, v0.15.x, v0.16.xで利用できます
   */
  voicevoxErrorResultToMessageV0_12(resultCode: number): { result: string };

  /**
   * ユーザー辞書を<b>構築</b>(_construct_)する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   *
   * \safety{
   * - `userDictPointerName`は 他の`UserDict`とかぶってはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxUserDictNewV0_16(userDictPointerName: number): {};

  /**
   * ユーザー辞書にファイルを読み込ませる。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {string} dictPath 読み込む辞書ファイルのパス
   *
   * @returns 結果コード
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNewV0_16`で設定したものでなければならず、また`voicevoxUserDictDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxUserDictLoadV0_16(userDictPointerName: number, dictPath: string): ResultCode;

  /**
   * ユーザー辞書に単語を追加する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {string} surface 表記
   * @param {string} pronunciation 読み
   * @param {number} accentType アクセント型
   * @param {number} priority 優先度
   * @param {number} wordType 単語の種類
   *
   * @returns 結果コード, 追加した単語のUUID
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNewV0_16`で設定したものでなければならず、また`voicevoxUserDictDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxUserDictAddWordV0_16(userDictPointerName: number, surface: string, pronunciation: string, accentType: number, priority: number, wordType: number): ResultCode & { result: Buffer };

  /**
   * ユーザー辞書の単語を更新する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {string} surface 表記
   * @param {string} pronunciation 読み
   * @param {number} accentType アクセント型
   * @param {number} priority 優先度
   * @param {number} wordType 単語の種類
   * @param {Buffer} uuid 更新する単語のUUID
   *
   * @returns 結果コード
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNewV0_16`で設定したものでなければならず、また`voicevoxUserDictDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxUserDictUpdateWordV0_16(userDictPointerName: number, surface: string, pronunciation: string, accentType: number, priority: number, wordType: number, uuid: Buffer): ResultCode;

  /**
   * ユーザー辞書から単語を削除する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {Buffer} uuid 更新する単語のUUID
   *
   * @returns 結果コード
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNewV0_16`で設定したものでなければならず、また`voicevoxUserDictDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxUserDictRemoveWordV0_16(userDictPointerName: number, uuid: Buffer): ResultCode;

  /**
   * ユーザー辞書の単語をJSON形式で出力する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   *
   * @returns 結果コード, ユーザー辞書のJSON文字列
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNewV0_16`で設定したものでなければならず、また`voicevoxUserDictDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxUserDictToJsonV0_16(userDictPointerName: number): ResultCode & { result: string };

  /**
   * 他のユーザー辞書をインポートする。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {number} otherDictPointerName インポートするユーザー辞書ポインタ名
   *
   * @returns 結果コード
   *
   * \safety{
   * - `userDictPointerName`と`otherDictPointerName`は`voicevoxUserDictNewV0_16`で設定したものでなければならず、また`voicevoxUserDictDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxUserDictImportV0_16(userDictPointerName: number, otherDictPointerName: number): ResultCode;

  /**
   * ユーザー辞書をファイルに保存する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {string} path 保存先のファイルパス
   *
   * @returns 結果コード
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNewV0_16`で設定したものでなければならず、また`voicevoxUserDictDeleteV0_16`で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxUserDictSaveV0_16(userDictPointerName: number, path: string): ResultCode;

  /**
   * ユーザー辞書を<b>破棄</b>(_destruct_)する。
   *
   * @param {number} userDictPointerName 破棄対象ユーザー辞書ポインタ名
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNewV0_16`で設定したものでなければならず、また既にこの関数で解放されていてはいけない。
   *
   * }
   *
   * この関数はv0.16.xで利用できます
   */
  voicevoxUserDictDeleteV0_16(userDictPointerName: number): {};

  /**
   * 初期化する
   * @param accelerationMode ハードウェアアクセラレーションモード
   * @param cpuNumThreads CPU利用数を指定 0を指定すると環境に合わせたCPUが利用される
   * @param loadAllModels 全てのモデルを読み込む
   * @param openJtalkDictDir open_jtalkの辞書ディレクトリ
   * @returns 結果コード
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxInitializeV0_14(accelerationMode: VoicevoxAccelerationMode, cpuNumThreads: number, loadAllModels: boolean, openJtalkDictDir: string): ResultCodeV14;

  /**
   * モデルを読み込む
   * @param speakerId 読み込むモデルの話者ID
   * @returns 結果コード
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxLoadModelV0_14(speakerId: number): ResultCodeV14;

  /**
   * ハードウェアアクセラレーションがGPUモードか判定する
   * @returns GPUモードならtrue、そうでないならfalse
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxIsGpuModeV0_14(): Result<boolean>;

  /**
   * 指定したspeaker_idのモデルが読み込まれているか判定する
   * @param speakerId モデルが読み込まれているのであればtrue、そうでないならfalse
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxIsModelLoadedV0_14(speakerId: number): Result<boolean>;

  /**
   * このライブラリの利用を終了し、確保しているリソースを解放する
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxFinalizeV0_14(): {};

  /**
   * メタ情報をjsonで取得する
   * @returns メタ情報のjson文字列
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxGetMetasJsonV0_14(): Result<string>;

  /**
   * サポートデバイス情報をjsonで取得する
   * @returns サポートデバイス情報のjson文字列
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxGetSupportedDevicesJsonV0_14(): Result<string>;

  /**
   * 音素ごとの長さを推論する
   * @param phoneme 音素データ
   * @param speakerId 話者ID
   * @returns 結果コード, 出力データ
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxPredictDurationV0_14(phoneme: Array<bigint>, speakerId: number): Result<Array<number>> & ResultCodeV14;

  /**
   * モーラごとのF0を推論する
   * @param vowelPhoneme 母音の音素データ
   * @param consonantPhoneme 子音の音素データ
   * @param startAccent アクセントの開始位置のデータ
   * @param endAccent アクセントの終了位置のデータ
   * @param startAccentPhrase アクセント句の開始位置のデータ
   * @param endAccentPhrase アクセント句の終了位置のデータ
   * @param speakerId 話者ID
   * @returns 結果コード, 出力データ
   *
   * # Safety
   * 入力の配列はすべて同じ長さにしてください
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxPredictIntonationV0_14(vowelPhoneme: Array<bigint>, consonantPhoneme: Array<bigint>, startAccent: Array<bigint>, endAccent: Array<bigint>, startAccentPhrase: Array<bigint>, endAccentPhrase: Array<bigint>, speakerId: number): Result<Array<number>> & ResultCodeV14;

  /**
   * decodeを実行する
   * @param f0 基本周波数
   * @param phoneme 音素データ
   * @param speakerId 話者ID
   * @returns 結果コード, 出力データ
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxDecodeV0_14(f0: Array<number>, phoneme: Array<number>, speakerId: number): Result<Array<number>> & ResultCodeV14;

  /**
   * AudioQuery を実行する
   * @param text テキスト
   * @param speakerId 話者ID
   * @param kana aquestalk形式のkanaとしてテキストを解釈する
   * @returns 結果コード, AudioQuery を json でフォーマットしたもの
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxAudioQueryV0_14(text: string, speakerId: number, kana: boolean): Result<string> & ResultCodeV14;

  /**
   * `accent_phrases` を実行する
   * @param text テキスト
   * @param speakerId 話者ID
   * @param options `accentPhrases`のオプション
   * @return 結果コード, アクセント句の情報の配列を json でフォーマットしたもの
   *
   * この関数はv0.15.xで利用できます
   */
  voicevoxAccentPhrasesV0_15(text: string, speakerId: number, kana: boolean): Result<string> & ResultCodeV15;

  /**
   * アクセント句の音素長を変更する
   * @param accentPhrasesJson アクセント句の配列を json でフォーマットしたもの
   * @param speakerId 話者ID
   * @return 結果コード, 音素長が変更されたアクセント句の情報の配列を json でフォーマットしたもの
   *
   * この関数はv0.15.xで利用できます
   */
  voicevoxMoraLengthV0_15(accentPhrasesJson: string, speakerId: number): Result<string> & ResultCodeV15;

  /**
   * アクセント句の音高を変更する
   * @param accentPhrasesJson アクセント句の配列を json でフォーマットしたもの
   * @param speakerId 話者ID
   * @return 結果コード, 音高が変更されたアクセント句の情報の配列を json でフォーマットしたもの
   *
   * この関数はv0.15.xで利用できます
   */
  voicevoxMoraPitchV0_15(accentPhrasesJson: string, speakerId: number): Result<string> & ResultCodeV15;

  /**
   * アクセント句の音高・音素長を変更する
   * @param accentPhrasesJson アクセント句の配列を json でフォーマットしたもの
   * @param speakerId 話者ID
   * @return 結果コード, 音高・音素長が変更されたアクセント句の情報の配列を json でフォーマットしたもの
   *
   * この関数はv0.15.xで利用できます
   */
  voicevoxMoraDataV0_15(accentPhrasesJson: string, speakerId: number): Result<string> & ResultCodeV15;

  /**
   * AudioQuery から音声合成する
   * @param audioQueryJson jsonフォーマットされた AudioQuery
   * @param speakerId 話者ID
   * @param enableInterrogativeUpspeak 疑問文の調整を有効にする
   * @returns 結果コード, wav データ
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxSynthesisV0_14(audioQueryJson: string, speakerId: number, enableInterrogativeUpspeak: boolean): Result<Buffer> & ResultCodeV14;

  /**
   * テキスト音声合成を実行する
   * @param text テキスト
   * @param speakerId 話者ID
   * @param enableInterrogativeUpspeak 疑問文の調整を有効にする
   * @param kana aquestalk形式のkanaとしてテキストを解釈する
   * @returns 結果コード, wav データ
   *
   * この関数はv0.14.x, v0.15.xで利用できます
   */
  voicevoxTtsV0_14(text: string, speakerId: number, enableInterrogativeUpspeak: boolean, kana: boolean): Result<Buffer> & ResultCodeV14;

  /**
   * 初期化する
   * 音声合成するための初期化を行う。他の関数を正しく実行するには先に初期化が必要
   * @param useGpu trueならGPU用、falseならCPU用の初期化を行う
   * @param cpuNumThreads 推論に用いるスレッド数を設定する。0の場合論理コア数の半分か、物理コア数が設定される
   * @param loadAllModels trueなら全てのモデルをロードする
   * @returns 成功したらtrue、失敗したらfalse
   * 何度も実行可能。use_gpuを変更して実行しなおすことも可能。
   * 最後に実行したuse_gpuに従って他の関数が実行される。
   *
   * この関数はv0.12.x, v0.13.xで利用できます
   */
  initializeV0_12(useGpu: boolean, cpuNumThreads: number, loadAllModels: boolean): Result<boolean>;

  /**
   * モデルをロードする
   * @param speakerId 話者番号
   * @returns 成功したらtrue、失敗したらfalse
   * 必ずしも話者とモデルが1:1対応しているわけではない。
   *
   * この関数はv0.12.x, v0.13.xで利用できます
   */
  loadModelV0_12(speakerId: number): Result<boolean>;

  /**
   * モデルがロード済みかどうか
   * @param speakerId 話者番号
   * @returns ロード済みならtrue、そうでないならfalse
   *
   * この関数はv0.12.x, v0.13.xで利用できます
   */
  isModelLoadedV0_12(speakerId: number): Result<boolean>;

  /**
   * 終了処理を行う
   * 終了処理を行う。以降関数を利用するためには再度初期化を行う必要がある。
   * 何度も実行可能。実行せずにexitしても大抵の場合問題ないが、
   * CUDAを利用している場合これを実行しておかないと例外が起こることがある。
   *
   * この関数はv0.10.x, v0.11.x, v0.12.x, v0.13.xで利用できます
   */
  finalizeV0_10(): {};

  /**
   * メタ情報を取得する
   * 話者名や話者IDのリストを取得する
   * @returns メタ情報が格納されたjson形式の文字列
   *
   * この関数はv0.5.x, v0.6.x, v0.7.x, v0.8.x, v0.9.x, v0.10.x, v0.11.x, v0.12.x, v0.13.xで利用できます
   */
  metasV0_5(): Result<string>;

  /**
   * 対応デバイス情報を取得する
   * cpu, cudaのうち、使用可能なデバイス情報を取得する
   * @returns 各デバイスが使用可能かどうかをboolで格納したjson形式の文字列
   *
   * この関数はv0.10.x, v0.11.x, v0.12.x, v0.13.xで利用できます
   */
  supportedDevicesV0_10(): Result<string>;

  /**
   * 音素ごとの長さを求める
   * 音素列から、音素ごとの長さを求める
   * @param phonemeList 音素列
   * @param speakerId 話者番号
   * @returns 音素ごとの長さ
   *
   * この関数はv0.8.x, v0.9.x, v0.10.x, v0.11.x, v0.12.x, v0.13.xで利用できます
   */
  yukarinSForwardV0_8(phonemeList: Array<bigint>, speakerId: number): Result<Array<number>> & { result2: boolean };

  /**
   * モーラごとの音高を求める
   * モーラごとの音素列とアクセント情報から、モーラごとの音高を求める
   * @param vowelPhonemeList 母音の音素列
   * @param consonantPhonemeList 子音の音素列
   * @param startAccentList アクセントの開始位置
   * @param endAccentList アクセントの終了位置
   * @param startAccentPhraseList アクセント句の開始位置
   * @param endAccentPhraseList アクセント句の終了位置
   * @param speakerId 話者番号
   * @returns モーラごとの音高
   *
   * この関数はv0.8.x, v0.9.x, v0.10.x, v0.11.x, v0.12.x, v0.13.xで利用できます
   */
  yukarinSaForwardV0_8(vowelPhonemeList: Array<bigint>, consonantPhonemeList: Array<bigint>, startAccentList: Array<bigint>, endAccentList: Array<bigint>, startAccentPhraseList: Array<bigint>, endAccentPhraseList: Array<bigint>, speakerId: number): Result<Array<number>> & { result2: boolean };

  /**
   * 波形を求める
   * @param f0 フレームごとの音高
   * @param phoneme フレームごとの音素
   * @param speakerId 話者番号
   * @returns 音声波形
   *
   * この関数はv0.8.x, v0.9.x, v0.10.x, v0.11.x, v0.12.x, v0.13.xで利用できます
   */
  decodeForwardV0_8(f0: Array<number>, phoneme: Array<number>, speakerId: number): Result<Array<number>> & { result2: boolean };

  /**
   * 最後に発生したエラーのメッセージを取得する
   * @returns エラーメッセージ
   *
   * この関数はv0.5.x, v0.6.x, v0.7.x, v0.8.x, v0.9.x, v0.10.x, v0.11.x, v0.12.x, v0.13.xで利用できます
   */
  lastErrorMessageV0_5(): Result<string>;

  /**
   * open jtalkの辞書を読み込む
   * @param dictPath
   * @returns 結果コード
   *
   * この関数はv0.12.x, v0.13.xで利用できます
   */
  voicevoxLoadOpenjtalkDictV0_12(dictPath: string): ResultCodeV12;

  /**
   * text to spearchを実行する
   * @param text 音声データに変換するtextデータ
   * @param speakerId 話者番号
   * @returns 結果コード, 音声データ
   *
   * この関数はv0.12.x, v0.13.xで利用できます
   */
  voicevoxTtsV0_12(text: string, speakerId: number): Result<Buffer> & ResultCodeV12;

  /**
   * text to spearchをAquesTalkライクな記法で実行する
   * @param text 音声データに変換するtextデータ
   * @param speakerId 話者番号
   * @returns 結果コード, 音声データ
   *
   * この関数はv0.12.x, v0.13.xで利用できます
   */
  voicevoxTtsFromKanaV0_12(text: string, speakerId: number): Result<Buffer> & ResultCodeV12;

  /**
   * 初期化する
   * 音声合成するための初期化を行う。他の関数を正しく実行するには先に初期化が必要
   * @param rootDirPath 必要なファイルがあるディレクトリ。相対パス・絶対パスどちらも指定可能。
   * @param useGpu trueならGPU用、falseならCPU用の初期化を行う
   * @param cpuNumThreads 推論に用いるスレッド数を設定する。0の場合論理コア数の半分か、物理コア数が設定される
   * @returns 成功したらtrue、失敗したらfalse
   * 何度も実行可能。use_gpuを変更して実行しなおすことも可能。
   * 最後に実行したuse_gpuに従って他の関数が実行される。
   *
   * この関数はv0.10.x, v0.11.xで利用できます
   */
  initializeV0_10(rootDirPath: string, useGpu: boolean, cpuNumThreads: number): Result<boolean>;

  /**
   * 初期化する
   * 音声合成するための初期化を行う。他の関数を正しく実行するには先に初期化が必要
   * @param rootDirPath 必要なファイルがあるディレクトリ。相対パス・絶対パスどちらも指定可能。
   * @param useGpu trueならGPU用、falseならCPU用の初期化を行う
   * @returns 成功したらtrue、失敗したらfalse
   * 何度も実行可能。use_gpuを変更して実行しなおすことも可能。
   * 最後に実行したuse_gpuに従って他の関数が実行される。
   *
   * この関数はv0.5.x, v0.6.x, v0.7.x, v0.8.x, v0.9.xで利用できます
   */
  initializeV0_5(rootDirPath: string, useGpu: boolean): Result<boolean>;

  /**
   * 音素ごとの長さを求める
   * 音素列から、音素ごとの長さを求める
   * @param phonemeList 音素列
   * @param speakerId 話者番号
   * @returns 音素ごとの長さ
   *
   * この関数はv0.5.x, v0.6.x, v0.7.xで利用できます
   */
  yukarinSForwardV0_5(phonemeList: Array<bigint>, speakerId: number): Result<Array<number>> & { result2: boolean };

  /**
   * モーラごとの音高を求める
   * モーラごとの音素列とアクセント情報から、モーラごとの音高を求める
   * @param vowelPhonemeList 母音の音素列
   * @param consonantPhonemeList 子音の音素列
   * @param startAccentList アクセントの開始位置
   * @param endAccentList アクセントの終了位置
   * @param startAccentPhraseList アクセント句の開始位置
   * @param endAccentPhraseList アクセント句の終了位置
   * @param speakerId 話者番号
   * @returns モーラごとの音高
   *
   * この関数はv0.5.x, v0.6.x, v0.7.xで利用できます
   */
  yukarinSaForwardV0_5(vowelPhonemeList: Array<bigint>, consonantPhonemeList: Array<bigint>, startAccentList: Array<bigint>, endAccentList: Array<bigint>, startAccentPhraseList: Array<bigint>, endAccentPhraseList: Array<bigint>, speakerId: number): Result<Array<number>> & { result2: boolean };

  /**
   * 波形を求める
   * @param f0 フレームごとの音高
   * @param phoneme フレームごとの音素
   * @param speakerId 話者番号
   * @returns 音声波形
   *
   * この関数はv0.5.x, v0.6.x, v0.7.xで利用できます
   */
  decodeForwardV0_5(f0: Array<number>, phoneme: Array<number>, speakerId: number): Result<Array<number>> & { result2: boolean };
}

interface Result<T> {
  result: T;
}

interface ResultCode {
  resultCode: VoicevoxResultCode;
}

/**
 * 処理結果を示す結果コード。
 */
export declare enum VoicevoxResultCode {
  /**
   * 成功
   */
  VOICEVOX_RESULT_OK = 0,
  /**
   * open_jtalk辞書ファイルが読み込まれていない
   */
  VOICEVOX_RESULT_NOT_LOADED_OPENJTALK_DICT_ERROR = 1,
  /**
   * サポートされているデバイス情報取得に失敗した
   */
  VOICEVOX_RESULT_GET_SUPPORTED_DEVICES_ERROR = 3,
  /**
   * GPUモードがサポートされていない
   */
  VOICEVOX_RESULT_GPU_SUPPORT_ERROR = 4,
  /**
   * スタイルIDに対するスタイルが見つからなかった
   */
  VOICEVOX_RESULT_STYLE_NOT_FOUND_ERROR = 6,
  /**
   * 音声モデルIDに対する音声モデルが見つからなかった
   */
  VOICEVOX_RESULT_MODEL_NOT_FOUND_ERROR = 7,
  /**
   * 推論に失敗した
   */
  VOICEVOX_RESULT_INFERENCE_ERROR = 8,
  /**
   * コンテキストラベル出力に失敗した
   */
  VOICEVOX_RESULT_EXTRACT_FULL_CONTEXT_LABEL_ERROR = 11,
  /**
   * 無効なutf8文字列が入力された
   */
  VOICEVOX_RESULT_INVALID_UTF8_INPUT_ERROR = 12,
  /**
   * AquesTalk風記法のテキストの解析に失敗した
   */
  VOICEVOX_RESULT_PARSE_KANA_ERROR = 13,
  /**
   * 無効なAudioQuery
   */
  VOICEVOX_RESULT_INVALID_AUDIO_QUERY_ERROR = 14,
  /**
   * 無効なAccentPhrase
   */
  VOICEVOX_RESULT_INVALID_ACCENT_PHRASE_ERROR = 15,
  /**
   * ZIPファイルを開くことに失敗した
   */
  VOICEVOX_RESULT_OPEN_ZIP_FILE_ERROR = 16,
  /**
   * ZIP内のファイルが読めなかった
   */
  VOICEVOX_RESULT_READ_ZIP_ENTRY_ERROR = 17,
  /**
   * すでに読み込まれている音声モデルを読み込もうとした
   */
  VOICEVOX_RESULT_MODEL_ALREADY_LOADED_ERROR = 18,
  /**
   * すでに読み込まれているスタイルを読み込もうとした
   */
  VOICEVOX_RESULT_STYLE_ALREADY_LOADED_ERROR = 26,
  /**
   * 無効なモデルデータ
   */
  VOICEVOX_RESULT_INVALID_MODEL_DATA_ERROR = 27,
  /**
   * ユーザー辞書を読み込めなかった
   */
  VOICEVOX_RESULT_LOAD_USER_DICT_ERROR = 20,
  /**
   * ユーザー辞書を書き込めなかった
   */
  VOICEVOX_RESULT_SAVE_USER_DICT_ERROR = 21,
  /**
   * ユーザー辞書に単語が見つからなかった
   */
  VOICEVOX_RESULT_USER_DICT_WORD_NOT_FOUND_ERROR = 22,
  /**
   * OpenJTalkのユーザー辞書の設定に失敗した
   */
  VOICEVOX_RESULT_USE_USER_DICT_ERROR = 23,
  /**
   * ユーザー辞書の単語のバリデーションに失敗した
   */
  VOICEVOX_RESULT_INVALID_USER_DICT_WORD_ERROR = 24,
  /**
   * UUIDの変換に失敗した
   */
  VOICEVOX_RESULT_INVALID_UUID_ERROR = 25,
}

/**
 * ハードウェアアクセラレーションモードを設定する設定値。
 */
export declare enum VoicevoxAccelerationMode {
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
 * ユーザー辞書の単語の種類。
 */
export declare enum VoicevoxUserDictWordType {
  /**
   * 固有名詞。
   */
  VOICEVOX_USER_DICT_WORD_TYPE_PROPER_NOUN = 0,
  /**
   * 一般名詞。
   */
  VOICEVOX_USER_DICT_WORD_TYPE_COMMON_NOUN = 1,
  /**
   * 動詞。
   */
  VOICEVOX_USER_DICT_WORD_TYPE_VERB = 2,
  /**
   * 形容詞。
   */
  VOICEVOX_USER_DICT_WORD_TYPE_ADJECTIVE = 3,
  /**
   * 接尾辞。
   */
  VOICEVOX_USER_DICT_WORD_TYPE_SUFFIX = 4,
}

interface ResultCodeV15 {
  resultCode: VoicevoxResultCodeV15;
}

export declare enum VoicevoxResultCodeV15 {
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
  /**
   * 無効なAccentPhrase
   */
  VOICEVOX_RESULT_INVALID_ACCENT_PHRASE_ERROR = 14,
}

interface ResultCodeV14 {
  resultCode: VoicevoxResultCodeV14;
}

export declare enum VoicevoxResultCodeV14 {
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

interface ResultCodeV12 {
  resultCode: VoicevoxResultCodeV12;
}

export declare enum VoicevoxResultCodeV12 {
  /**
   * 成功
   */
  VOICEVOX_RESULT_SUCCEED = 0,
  /**
   * OpenJTalk辞書がロードされていない
   */
  VOICEVOX_RESULT_NOT_LOADED_OPENJTALK_DICT = 1,
}
