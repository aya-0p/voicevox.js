/**
 * 無料で使える中品質なテキスト読み上げソフトウェア、VOICEVOXのコア。
 *
 * # 注意
 * - 型には忠実に守ること
 * - 関数の引数の数は合わせること
 * - ポインタ名は同じ種類同士でかぶらないこと
 *   - なお、別のものとはかぶっても良い
 * - ポインタ名はC++における`uint32_t`(`unsigned int`, 0~4294967295)の範囲内であること
 *
 * これらの要件を満たさない場合即座にプログラムが終了する可能性がある
 */
export declare class VoicevoxCore {
  constructor(path: string);

  /**
   * OpenJtalkRc を<b>構築</b>(_construct_)する。
   *
   * 解放は voicevoxOpenJtalkRcDelete で行う。
   *
   * @param {string} openJtalkDicDir 辞書ディレクトリを指すUTF-8のパス
   * @param {number} openJtalkPointerName 構築先Open JTalkポインタ名
   *
   * @returns 結果コード
   *
   * \example{
   * ```js
   * voicevoxOpenJtalkRcNew("./open_jtalk_dic_utf_8-1.11", 0);
   * ```
   * }
   *
   * \safety{
   *  - `openJtalkPointerName`は他の`OpenJtalkRc`とかぶってはいけない。
   *
   * }
   */
  voicevoxOpenJtalkRcNew(openJtalkDicDir: string, openJtalkPointerName: number): ResultCode;

  /**
   * OpenJtalkの使うユーザー辞書を設定する。
   *
   * この関数を呼び出した後にユーザー辞書を変更した場合、再度この関数を呼び出す必要がある。
   *
   * @param {number} openJtalkPointerName Open JTalkポインタ名
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   *
   * \safety{
   * - `openJtalkPointerName`は`voicevoxOpenJtalkRcNew`で設定したものでなければならず、また`voicevoxOpenJtalkRcDelete`で解放されていてはいけない。
   * - `userDictPointerName`は`voicevoxUserDictNew`で設定したものでなければならず、また`voicevoxUserDictDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxOpenJtalkRcUseUserDict(openJtalkPointerName: number, userDictPointerName: number): ResultCode;

  /**
   * OpenJtalkRc を<b>破棄</b>(_destruct_)する。
   *
   * @param {number} openJtalkPointerName 破棄対象Open JTalkポインタ名
   *
   * \example{
   * ```js
   * voicevoxOpenJtalkRcDelete(0);
   * ```
   * }
   *
   * \safety{
   * - `openJtalkPointerName`は`voicevoxOpenJtalkRcNew`で設定したものでなければならず、また既にこの関数で解放されていてはいけない。
   *
   * }
   */
  voicevoxOpenJtalkRcDelete(openJtalkPointerName: number): {};

  /**
   * voicevoxのバージョンを取得する。
   * @return SemVerでフォーマットされたバージョン。
   */
  voicevoxGetVersion(): { result: string };

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
   */
  voicevoxVoiceModelNewFromPath(path: string, modelPointerName: number): ResultCode;

  /**
   * VoicevoxVoiceModel からIDを取得する。
   *
   * @param {number} modelPointerName 音声モデルポインタ名
   *
   * @returns 音声モデルID
   *
   * \safety{
   * - `modelPointerName`は`voicevoxVoiceModelNewFromPath`で設定したものでなければならず、また`voicevoxVoiceModelDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxVoiceModelId(modelPointerName: number): { result: string };

  /**
   * VoicevoxVoiceModel からメタ情報を取得する。
   *
   * @param {number} modelPointerName 音声モデルポインタ名
   *
   * @returns メタ情報のJSON文字列
   *
   * \safety{
   * - `modelPointerName`は`voicevoxVoiceModelNewFromPath`で設定したものでなければならず、また`voicevoxVoiceModelDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxVoiceModelGetMetasJson(modelPointerName: number): { result: string };

  /**
   * VoicevoxVoiceModel を<b>破棄</b>(_destruct_)する。
   *
   * @param {number} modelPointerName 破棄対象音声モデルポインタ名
   *
   * \safety{
   * - `modelPointerName`は`voicevoxVoiceModelNewFromPath`で設定したものでなければならず、また既にこの関数で解放されていてはいけない。
   *
   * }
   */
  voicevoxVoiceModelDelete(modelPointerName: number): {};

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
   * - `openJtalkPointerName`は`voicevoxOpenJtalkRcNew`で設定したものでなければならず、また`voicevoxOpenJtalkRcDelete`で解放されていてはいけない。
   * - `synthesizerPointerName`は他の`VoicevoxSynthesizer`とかぶってはいけない。
   *
   * }
   */
  voicevoxSynthesizerNew(openJtalkPointerName: number, synthesizerPointerName: number, accelerationMode: number, cpuNumThreads: number): ResultCode;

  /**
   * VoicevoxSynthesizer を<b>破棄</b>(_destruct_)する。
   *
   * @param {number} synthesizerPointerName 破棄対象音声シンセサイザポインタ名
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また既にこの関数で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerDelete(synthesizerPointerName: number): {};

  /**
   * 音声モデルを読み込む。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {number} modelPointerName 音声モデルポインタ名
   *
   * @returns 結果コード
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   * - `modelPointerName`は`voicevoxVoiceModelNewFromPath`で設定したものでなければならず、また`voicevoxVoiceModelDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerLoadVoiceModel(synthesizerPointerName: number, modelPointerName: number): ResultCode;

  /**
   * 音声モデルの読み込みを解除する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} modelId 音声モデルID
   *
   * @returns 結果コード
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerUnloadVoiceModel(synthesizerPointerName: number, modelId: string): ResultCode;

  /**
   * ハードウェアアクセラレーションがGPUモードか判定する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   *
   * @returns GPUモードかどうか
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerIsGpuMode(synthesizerPointerName: number): { result: boolean };

  /**
   * 指定したIDの音声モデルが読み込まれているか判定する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   * @param {string} modelId 音声モデルID
   *
   * @returns モデルが読み込まれているかどうか
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerIsLoadedVoiceModel(synthesizerPointerName: number, modelId: string): { result: boolean };

  /**
   * 今読み込んでいる音声モデルのメタ情報を、JSONで取得する。
   *
   * @param {number} synthesizerPointerName 音声シンセサイザポインタ名
   *
   * @return メタ情報のJSON文字列
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerCreateMetasJson(synthesizerPointerName: number): { result: string };

  /**
   * このライブラリで利用可能なデバイスの情報を、JSONで取得する。
   *
   * あくまで本ライブラリが対応しているデバイスの情報であることに注意。GPUが使える環境ではなかったとしても`cuda`や`dml`は`true`を示しうる。
   *
   * @returns 結果コード, サポートデバイス情報のJSON文字列
   *
   * \example{
   * ```js
   * const { result, resultCode } = voicevoxCreateSupportedDevicesJson();
   * ```
   * }
   */
  voicevoxCreateSupportedDevicesJson(): ResultCode & { result: string };

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
   * const { result, resultCode } = voicevoxSynthesizerCreateAudioQueryFromKana(
   *   0,
   *   "コンニチワ'",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   * }
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerCreateAudioQueryFromKana(synthesizerPointerName: number, kana: string, styleId: number): ResultCode & { result: string };

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
   * const { result, resultCode } = voicevoxSynthesizerCreateAudioQuery(
   *   0,
   *   "こんにちは",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   * }
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerCreateAudioQuery(synthesizerPointerName: number, text: string, styleId: number): ResultCode & { result: string };

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
   * const { result, resultCode } = voicevoxSynthesizerCreateAccentPhrasesFromKana(
   *   0,
   *   "コンニチワ'",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   * }
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerCreateAccentPhrasesFromKana(synthesizerPointerName: number, kana: string, styleId: number): ResultCode & { result: string };

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
   * const { result, resultCode } = voicevoxSynthesizerCreateAccentPhrases(
   *   0,
   *   "こんにちは",
   *   2, // "四国めたん (ノーマル)"
   * );
   * ```
   * }
   *
   * \safety{
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerCreateAccentPhrases(synthesizerPointerName: number, text: string, styleId: number): ResultCode & { result: string };

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
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerReplaceMoraData(synthesizerPointerName: number, accentPhrasesJson: string, styleId: number): ResultCode & { result: string };

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
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerReplacePhonemeLength(synthesizerPointerName: number, accentPhrasesJson: string, styleId: number): ResultCode & { result: string };

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
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerReplaceMoraPitch(synthesizerPointerName: number, accentPhrasesJson: string, styleId: number): ResultCode & { result: string };

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
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerSynthesis(synthesizerPointerName: number, audioQueryJson: string, styleId: number, enableInterrogativeUpspeak: boolean): ResultCode & { result: Buffer };

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
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerTtsFromKana(synthesizerPointerName: number, kana: string, styleId: number, enableInterrogativeUpspeak: boolean): ResultCode & { result: Buffer };

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
   * - `synthesizerPointerName`は`voicevoxSynthesizerNew`で設定したものでなければならず、また`voicevoxSynthesizerDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxSynthesizerTts(synthesizerPointerName: number, text: string, styleId: number, enableInterrogativeUpspeak: boolean): ResultCode & { result: Buffer };

  /**
   * 結果コードに対応したメッセージ文字列を取得する。
   *
   * @param {number} resultCode 結果コード
   *
   * @returns 結果コードに対応したメッセージ文字列
   *
   * \examples{
   * ```js
   * const actual = voicevoxErrorResultToMessage(VOICEVOX_RESULT_OK);
   * const EXPECTED = "エラーが発生しませんでした";
   * actual === EXPECTED; // true
   * ```
   * --
   * ```js
   * const actual = voicevoxErrorResultToMessage(VOICEVOX_RESULT_LOAD_MODEL_ERROR);
   * const EXPECTED = "modelデータ読み込みに失敗しました";
   * actual === EXPECTED; // true
   * ```
   * }
   */
  voicevoxErrorResultToMessage(resultCode: number): { result: string };

  /**
   * ユーザー辞書を<b>構築</b>(_construct_)する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   *
   * \safety{
   * - `userDictPointerName`は 他の`UserDict`とかぶってはいけない。
   *
   * }
   */
  voicevoxUserDictNew(userDictPointerName: number): {};

  /**
   * ユーザー辞書にファイルを読み込ませる。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {string} dictPath 読み込む辞書ファイルのパス
   *
   * @returns 結果コード
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNew`で設定したものでなければならず、また`voicevoxUserDictDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxUserDictLoad(userDictPointerName: number, dictPath: string): ResultCode;

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
   * - `userDictPointerName`は`voicevoxUserDictNew`で設定したものでなければならず、また`voicevoxUserDictDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxUserDictAddWord(userDictPointerName: number, surface: string, pronunciation: string, accentType: number, priority: number, wordType: number): ResultCode & { result: Buffer };

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
   * - `userDictPointerName`は`voicevoxUserDictNew`で設定したものでなければならず、また`voicevoxUserDictDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxUserDictUpdateWord(userDictPointerName: number, surface: string, pronunciation: string, accentType: number, priority: number, wordType: number, uuid: Buffer): ResultCode;

  /**
   * ユーザー辞書から単語を削除する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {Buffer} uuid 更新する単語のUUID
   *
   * @returns 結果コード
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNew`で設定したものでなければならず、また`voicevoxUserDictDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxUserDictRemoveWord(userDictPointerName: number, uuid: Buffer): ResultCode;

  /**
   * ユーザー辞書の単語をJSON形式で出力する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   *
   * @returns 結果コード, ユーザー辞書のJSON文字列
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNew`で設定したものでなければならず、また`voicevoxUserDictDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxUserDictToJson(userDictPointerName: number): ResultCode & { result: string };

  /**
   * 他のユーザー辞書をインポートする。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {number} otherDictPointerName インポートするユーザー辞書ポインタ名
   *
   * @returns 結果コード
   *
   * \safety{
   * - `userDictPointerName`と`otherDictPointerName`は`voicevoxUserDictNew`で設定したものでなければならず、また`voicevoxUserDictDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxUserDictImport(userDictPointerName: number, otherDictPointerName: number): ResultCode;

  /**
   * ユーザー辞書をファイルに保存する。
   *
   * @param {number} userDictPointerName ユーザー辞書ポインタ名
   * @param {string} path 保存先のファイルパス
   *
   * @returns 結果コード
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNew`で設定したものでなければならず、また`voicevoxUserDictDelete`で解放されていてはいけない。
   *
   * }
   */
  voicevoxUserDictSave(userDictPointerName: number, path: string): ResultCode;

  /**
   * ユーザー辞書を<b>破棄</b>(_destruct_)する。
   *
   * @param {number} userDictPointerName 破棄対象ユーザー辞書ポインタ名
   *
   * \safety{
   * - `userDictPointerName`は`voicevoxUserDictNew`で設定したものでなければならず、また既にこの関数で解放されていてはいけない。
   *
   * }
   */
  voicevoxUserDictDelete(userDictPointerName: number): {};
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
