/**
 * @file voicevox_core.h
 *
 * 無料で使える中品質なテキスト読み上げソフトウェア、VOICEVOXのコア。
 *
 * <dl>
 *   <dt id="voicevox-core-safety">
 *     <a href="#voicevox-core-safety">⚠️ Safety</a>
 *   </dt>
 *
 *   <dd>
 * このライブラリの利用にあたっては、いくつかの不変条件が守られている必要がある。本ドキュメントではこの不変条件を<b>安全性要件</b>(_safety
 * requirements_)と呼び、"Safety"というセクションの下に安全性要件を示す。
 *
 * 安全性要件の違反は[Rust言語における<b>未定義動作</b>(_undefined behavior_; 通称<em>UB</em>)](
 * https://doc.rust-lang.org/reference/behavior-considered-undefined.html)を引き起こす。Rustの未定義動作は、Cのそれや[C++のそれ](
 * https://cpprefjp.github.io/implementation-compliance.html#nasal-demon)や[Zigのそれ](
 * https://ziglang.org/documentation/0.10.1/#Undefined-Behavior)などとおおよそ同じであり、引き起こしてはならないものとされる。プログラム全体のどこかに未定義動作が含まれるなら、一般的に、処理系はそれについて何をしてもよい。[変数は同時にtrueでもfalseでもあってもよいし](
 * https://markshroyer.com/2012/06/c-both-true-and-false/)、あなたの鼻から悪魔が飛び出してもよい。このことは通称<b>鼻から悪魔</b>(_nasal
 * demons_)と呼ばれる。
 *
 * 未定義動作はプログラム全体に影響する。<b>運が良ければ</b>セグメンテーション違反などで異常終了するだけだが、ライブラリを呼び出している部分から離れた所で「鼻から悪魔」が起こることもある。そうなったら挙動の予測もデバッグも困難である。これが未定義動作が禁忌とされる所以である。
 *
 * `voicevox_core`全体における安全性要件は以下の通りである。
 *
 * - 「読み込みについて有効」と説明されているポインタは次の条件を満たしていなければならない。
 *     - <b>間接参照可能</b>(_dereferenceable_)である。
 *     - 参照先のメモリは他スレッドから書き込み中ではない。
 * - 「書き込みについて有効」と説明されているポインタは次の条件を満たしていなければならない。
 *     - 参照先のメモリは有効である (ただしメモリアラインメントに沿っている必要は無い)。
 *     - 参照先のメモリは他スレッドからアクセス中ではない。
 * - このライブラリで生成したオブジェクトの解放は、このライブラリが提供するAPIで行わなくてはならない(<code>free</code>や<code>HeapFree</code>で行ってはならない)。
 *
 * 次のことに注意すること。
 *
 * - 次のポインタは読み込みにおいても書き込みにおいても有効ではない。
 *     - ヌルポインタ。
 *     - 解放されたポインタ。
 * - voicevox_coreをアンロードする場合、voicevox_coreが生成したポインタが有効であり続けることは保証されない。
 *   </dd>
 * </dl>
 */

#ifndef VOICEVOX_CORE_INCLUDE_GUARD
#define VOICEVOX_CORE_INCLUDE_GUARD

/* Generated with cbindgen:0.24.3 */

#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#define DLL HMODULE
#else
#include <dlfcn.h>
#define DLL void *
#endif

DLL dll_load(const char *path);

void dll_free(DLL &dll);

/**
 * ハードウェアアクセラレーションモードを設定する設定値。
 */
enum VoicevoxAccelerationMode : int32_t
{
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
};

/**
 * 処理結果を示す結果コード。
 */
enum VoicevoxResultCode : int32_t
{
  /**
   * 成功
   */
  VOICEVOX_RESULT_OK = 0,
  /**
   * 成功
   */
  VOICEVOX_RESULT_SUCCEED = 0,
};

/**
 * ユーザー辞書の単語の種類。
 */
enum VoicevoxUserDictWordType : int32_t
{
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
};

/**
 * テキスト解析器としてのOpen JTalk。
 *
 * <b>構築</b>(_construction_)は ::voicevox_open_jtalk_rc_new で行い、<b>破棄</b>(_destruction_)は ::voicevox_open_jtalk_rc_delete で行う。
 *
 * 参照カウント方式のスマートポインタ(reference-counted smart pointer)であり、
 * ::voicevox_synthesizer_new に渡されるときには参照カウンタがインクリメントされる形でオブジェクトの共有が行われる。
 *
 * \example{
 * ```c
 * OpenJtalkRc *open_jtalk;
 * voicevox_open_jtalk_rc_new("./open_jtalk_dic_utf_8-1.11", &open_jtalk);
 * // ⋮
 * voicevox_open_jtalk_rc_delete(open_jtalk);
 * ```
 * }
 */
typedef struct OpenJtalkRc OpenJtalkRc;

/**
 * 音声シンセサイザ。
 *
 * <b>構築</b>(_construction_)は ::voicevox_synthesizer_new で行い、<b>破棄</b>(_destruction_)は ::voicevox_synthesizer_delete で行う。
 */
typedef struct VoicevoxSynthesizer VoicevoxSynthesizer;

/**
 * ユーザー辞書。
 */
typedef struct VoicevoxUserDict VoicevoxUserDict;

/**
 * 音声モデル。
 *
 * VVMファイルと対応する。
 * <b>構築</b>(_construction_)は ::voicevox_voice_model_new_from_path で行い、<b>破棄</b>(_destruction_)は ::voicevox_voice_model_delete で行う。
 */
typedef struct VoicevoxVoiceModel VoicevoxVoiceModel;

/**
 * 初期化オプション
 */
typedef struct VoicevoxInitializeOptionsV14
{
  /**
   * ハードウェアアクセラレーションモード
   */
  VoicevoxAccelerationMode acceleration_mode;
  /**
   * CPU利用数を指定
   * 0を指定すると環境に合わせたCPUが利用される
   */
  uint16_t cpu_num_threads;
  /**
   * 全てのモデルを読み込む
   */
  bool load_all_models;
  /**
   * open_jtalkの辞書ディレクトリ
   */
  const char *open_jtalk_dict_dir;
} VoicevoxInitializeOptionsV14;

/**
 * ::voicevox_synthesizer_new のオプション。
 */
typedef struct VoicevoxInitializeOptions
{
  /**
   * ハードウェアアクセラレーションモード
   */
  VoicevoxAccelerationMode acceleration_mode;
  /**
   * CPU利用数を指定
   * 0を指定すると環境に合わせたCPUが利用される
   */
  uint16_t cpu_num_threads;
} VoicevoxInitializeOptions;

/**
 * Audio query のオプション
 */
typedef struct VoicevoxAudioQueryOptions
{
  /**
   * aquestalk形式のkanaとしてテキストを解釈する
   */
  bool kana;
} VoicevoxAudioQueryOptions;

/**
 * 音声モデルID。
 */
typedef const char *VoicevoxVoiceModelId;

/**
 * スタイルID。
 *
 * VOICEVOXにおける、ある<b>話者</b>(_speaker_)のある<b>スタイル</b>(_style_)を指す。
 */
typedef uint32_t VoicevoxStyleId;

/**
 * ::voicevox_synthesizer_synthesis のオプション。
 */
typedef struct VoicevoxSynthesisOptions
{
  /**
   * 疑問文の調整を有効にする
   */
  bool enable_interrogative_upspeak;
} VoicevoxSynthesisOptions;

/**
 * テキスト音声合成オプション
 */
typedef struct VoicevoxTtsOptionsV14
{
  /**
   * aquestalk形式のkanaとしてテキストを解釈する
   */
  bool kana;
  /**
   * 疑問文の調整を有効にする
   */
  bool enable_interrogative_upspeak;
} VoicevoxTtsOptionsV14;

/**
 * ::voicevox_synthesizer_tts のオプション。
 */
typedef struct VoicevoxTtsOptions
{
  /**
   * 疑問文の調整を有効にする
   */
  bool enable_interrogative_upspeak;
} VoicevoxTtsOptions;

/**
 * ユーザー辞書の単語。
 */
typedef struct VoicevoxUserDictWord
{
  /**
   * 表記
   */
  const char *surface;
  /**
   * 読み
   */
  const char *pronunciation;
  /**
   * アクセント型
   */
  uintptr_t accent_type;
  /**
   * 単語の種類
   */
  VoicevoxUserDictWordType word_type;
  /**
   * 優先度
   */
  uint32_t priority;
} VoicevoxUserDictWord;

/**
 * `accent_phrases` のオプション
 */
typedef struct VoicevoxAccentPhrasesOptions {
  /**
   * aquestalk形式のkanaとしてテキストを解釈する
   */
  bool kana;
} VoicevoxAccentPhrasesOptions;

/**
 * ::OpenJtalkRc を<b>構築</b>(_construct_)する。
 *
 * 解放は ::voicevox_open_jtalk_rc_delete で行う。
 *
 * @param [in] open_jtalk_dic_dir 辞書ディレクトリを指すUTF-8のパス
 * @param [out] out_open_jtalk 構築先
 *
 * @returns 結果コード
 *
 * \example{
 * ```c
 * OpenJtalkRc *open_jtalk;
 * voicevox_open_jtalk_rc_new("./open_jtalk_dic_utf_8-1.11", &open_jtalk);
 * ```
 * }
 *
 * \safety{
 * - `open_jtalk_dic_dir`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `out_open_jtalk`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_open_jtalk_rc_new(DLL &dll,
                                              const char *open_jtalk_dic_dir,
                                              struct OpenJtalkRc **out_open_jtalk);

/**
 * OpenJtalkの使うユーザー辞書を設定する。
 *
 * この関数を呼び出した後にユーザー辞書を変更した場合、再度この関数を呼び出す必要がある。
 *
 * @param [in] open_jtalk Open JTalkのオブジェクト
 * @param [in] user_dict ユーザー辞書
 *
 * \safety{
 * - `open_jtalk`は ::voicevox_open_jtalk_rc_new で得たものでなければならず、また ::voicevox_open_jtalk_rc_delete で解放されていてはいけない。
 * - `user_dict`は ::voicevox_user_dict_new で得たものでなければならず、また ::voicevox_user_dict_delete で解放されていてはいけない。
 * }
 */
VoicevoxResultCode voicevox_open_jtalk_rc_use_user_dict(DLL &dll,
                                                        const struct OpenJtalkRc *open_jtalk,
                                                        const struct VoicevoxUserDict *user_dict);

/**
 * ::OpenJtalkRc を<b>破棄</b>(_destruct_)する。
 *
 * @param [in] open_jtalk 破棄対象
 *
 * \example{
 * ```c
 * voicevox_open_jtalk_rc_delete(open_jtalk);
 * ```
 * }
 *
 * \safety{
 * - `open_jtalk`は ::voicevox_open_jtalk_rc_new で得たものでなければならず、また既にこの関数で解放されていてはいけない。
 * - `open_jtalk`は以後<b>ダングリングポインタ</b>(_dangling pointer_)として扱われなくてはならない。
 * }
 */
void voicevox_open_jtalk_rc_delete(DLL &dll,
                                   struct OpenJtalkRc *open_jtalk);

/**
 * デフォルトの初期化オプションを生成する
 * @return デフォルト値が設定された初期化オプション
 */
struct VoicevoxInitializeOptions voicevox_make_default_initialize_options(DLL &dll);

/**
 * voicevoxのバージョンを取得する。
 * @return SemVerでフォーマットされたバージョン。
 */
const char *voicevox_get_version(DLL &dll);

/**
 * VVMファイルから ::VoicevoxVoiceModel を<b>構築</b>(_construct_)する。
 *
 * @param [in] path vvmファイルへのUTF-8のファイルパス
 * @param [out] out_model 構築先
 *
 * @returns 結果コード
 *
 * \safety{
 * - `path`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `out_model`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_voice_model_new_from_path(DLL &dll,
                                                      const char *path,
                                                      struct VoicevoxVoiceModel **out_model);

/**
 * ::VoicevoxVoiceModel からIDを取得する。
 *
 * @param [in] model 音声モデル
 *
 * @returns 音声モデルID
 *
 * \safety{
 * - `model`は ::voicevox_voice_model_new_from_path で得たものでなければならず、また ::voicevox_voice_model_delete で解放されていてはいけない。
 * }
 */
VoicevoxVoiceModelId voicevox_voice_model_id(DLL &dll,
                                             const struct VoicevoxVoiceModel *model);

/**
 * ::VoicevoxVoiceModel からメタ情報を取得する。
 *
 * @param [in] model 音声モデル
 *
 * @returns メタ情報のJSON文字列
 *
 * \safety{
 * - `model`は ::voicevox_voice_model_new_from_path で得たものでなければならず、また ::voicevox_voice_model_delete で解放されていてはいけない。
 * - 戻り値の文字列の<b>生存期間</b>(_lifetime_)は次にこの関数が呼ばれるか、`model`が破棄されるまでである。この生存期間を越えて文字列にアクセスしてはならない。
 * }
 */
const char *voicevox_voice_model_get_metas_json(DLL &dll,
                                                const struct VoicevoxVoiceModel *model);

/**
 * ::VoicevoxVoiceModel を<b>破棄</b>(_destruct_)する。
 *
 * @param [in] model 破棄対象
 *
 * \safety{
 * - `model`は ::voicevox_voice_model_new_from_path で得たものでなければならず、また既にこの関数で解放されていてはいけない。
 * - `model`は以後<b>ダングリングポインタ</b>(_dangling pointer_)として扱われなくてはならない。
 * }
 */
void voicevox_voice_model_delete(DLL &dll,
                                 struct VoicevoxVoiceModel *model);

/**
 * ::VoicevoxSynthesizer を<b>構築</b>(_construct_)する。
 *
 * @param [in] open_jtalk Open JTalkのオブジェクト
 * @param [in] options オプション
 * @param [out] out_synthesizer 構築先
 *
 * @returns 結果コード
 *
 * \safety{
 * - `open_jtalk`は ::voicevox_voice_model_new_from_path で得たものでなければならず、また ::voicevox_open_jtalk_rc_new で解放されていてはいけない。
 * - `out_synthesizer`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_new(DLL &dll,
                                            const struct OpenJtalkRc *open_jtalk,
                                            struct VoicevoxInitializeOptions options,
                                            struct VoicevoxSynthesizer **out_synthesizer);

/**
 * ::VoicevoxSynthesizer を<b>破棄</b>(_destruct_)する。
 *
 * @param [in] synthesizer 破棄対象
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また既にこの関数で解放されていてはいけない。
 * - `synthesizer`は以後<b>ダングリングポインタ</b>(_dangling pointer_)として扱われなくてはならない。
 * }
 */
void voicevox_synthesizer_delete(DLL &dll,
                                 struct VoicevoxSynthesizer *synthesizer);

/**
 * 音声モデルを読み込む。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] model 音声モデル
 *
 * @returns 結果コード
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `model`は ::voicevox_voice_model_new_from_path で得たものでなければならず、また ::voicevox_voice_model_delete で解放されていてはいけない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_load_voice_model(DLL &dll,
                                                         const struct VoicevoxSynthesizer *synthesizer,
                                                         const struct VoicevoxVoiceModel *model);

/**
 * 音声モデルの読み込みを解除する。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] model_id 音声モデルID
 *
 * @returns 結果コード
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `model_id`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_unload_voice_model(DLL &dll,
                                                           const struct VoicevoxSynthesizer *synthesizer,
                                                           VoicevoxVoiceModelId model_id);

/**
 * ハードウェアアクセラレーションがGPUモードか判定する。
 *
 * @param [in] synthesizer 音声シンセサイザ
 *
 * @returns GPUモードかどうか
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * }
 */
bool voicevox_synthesizer_is_gpu_mode(DLL &dll,
                                      const struct VoicevoxSynthesizer *synthesizer);

/**
 * 指定したIDの音声モデルが読み込まれているか判定する。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] model_id 音声モデルID
 *
 * @returns モデルが読み込まれているかどうか
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `model_id`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * }
 */
bool voicevox_synthesizer_is_loaded_voice_model(DLL &dll,
                                                const struct VoicevoxSynthesizer *synthesizer,
                                                VoicevoxVoiceModelId model_id);

/**
 * 今読み込んでいる音声モデルのメタ情報を、JSONで取得する。
 *
 * JSONの解放は ::voicevox_json_free で行う。
 *
 * @param [in] synthesizer 音声シンセサイザ
 *
 * @return メタ情報のJSON文字列
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * }
 */
char *voicevox_synthesizer_create_metas_json(DLL &dll,
                                             const struct VoicevoxSynthesizer *synthesizer);

/**
 * このライブラリで利用可能なデバイスの情報を、JSONで取得する。
 *
 * JSONの解放は ::voicevox_json_free で行う。
 *
 * あくまで本ライブラリが対応しているデバイスの情報であることに注意。GPUが使える環境ではなかったとしても`cuda`や`dml`は`true`を示しうる。
 *
 * @param [out] output_supported_devices_json サポートデバイス情報のJSON文字列
 *
 * @returns 結果コード
 *
 * \example{
 * ```c
 * char *supported_devices;
 * VoicevoxResultCode result = voicevox_create_supported_devices_json(&supported_devices);
 * ```
 * }
 *
 * \safety{
 * - `output_supported_devices_json`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_create_supported_devices_json(DLL &dll,
                                                          char **output_supported_devices_json);

/**
 * AquesTalk風記法から、AudioQueryをJSONとして生成する。
 *
 * 生成したJSON文字列を解放するには ::voicevox_json_free を使う。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] kana AquesTalk風記法
 * @param [in] style_id スタイルID
 * @param [out] output_audio_query_json 生成先
 *
 * @returns 結果コード
 *
 * \example{
 * ```c
 * char *audio_query;
 * voicevox_synthesizer_create_audio_query_from_kana(synthesizer, "コンニチワ'",
 *                                                   2, // "四国めたん (ノーマル)"
 *                                                   &audio_query);
 * ```
 * }
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `kana`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_audio_query_json`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_create_audio_query_from_kana(DLL &dll,
                                                                     const struct VoicevoxSynthesizer *synthesizer,
                                                                     const char *kana,
                                                                     VoicevoxStyleId style_id,
                                                                     char **output_audio_query_json);

/**
 * 日本語テキストから、AudioQueryをJSONとして生成する。
 *
 * 生成したJSON文字列を解放するには ::voicevox_json_free を使う。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] text UTF-8の日本語テキスト
 * @param [in] style_id スタイルID
 * @param [out] output_audio_query_json 生成先
 *
 * @returns 結果コード
 *
 * \example{
 * ```c
 * char *audio_query;
 * voicevox_synthesizer_create_audio_query(synthesizer, "こんにちは",
 *                                         2, // "四国めたん (ノーマル)"
 *                                         &audio_query);
 * ```
 * }
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `text`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_audio_query_json`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_create_audio_query(DLL &dll,
                                                           const struct VoicevoxSynthesizer *synthesizer,
                                                           const char *text,
                                                           VoicevoxStyleId style_id,
                                                           char **output_audio_query_json);

/**
 * AquesTalk風記法から、AccentPhrase (アクセント句)の配列をJSON形式で生成する。
 *
 * 生成したJSON文字列を解放するには ::voicevox_json_free を使う。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] kana AquesTalk風記法
 * @param [in] style_id スタイルID
 * @param [out] output_accent_phrases_json 生成先
 *
 * @returns 結果コード
 *
 * \example{
 * ```c
 * char *accent_phrases;
 * voicevox_synthesizer_create_accent_phrases_from_kana(
 *     synthesizer, "コンニチワ'",
 *     2, // "四国めたん (ノーマル)"
 *     &accent_phrases);
 * ```
 * }
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `kana`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_audio_query_json`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_create_accent_phrases_from_kana(DLL &dll,
                                                                        const struct VoicevoxSynthesizer *synthesizer,
                                                                        const char *kana,
                                                                        VoicevoxStyleId style_id,
                                                                        char **output_accent_phrases_json);

/**
 * 日本語テキストから、AccentPhrase (アクセント句)の配列をJSON形式で生成する。
 *
 * 生成したJSON文字列を解放するには ::voicevox_json_free を使う。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] text UTF-8の日本語テキスト
 * @param [in] style_id スタイルID
 * @param [out] output_accent_phrases_json 生成先
 *
 * @returns 結果コード
 *
 * \example{
 * ```c
 * char *accent_phrases;
 * voicevox_synthesizer_create_accent_phrases(synthesizer, "こんにちは",
 *                                            2, // "四国めたん (ノーマル)"
 *                                            &accent_phrases);
 * ```
 * }
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `text`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_audio_query_json`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_create_accent_phrases(DLL &dll,
                                                              const struct VoicevoxSynthesizer *synthesizer,
                                                              const char *text,
                                                              VoicevoxStyleId style_id,
                                                              char **output_accent_phrases_json);

/**
 * AccentPhraseの配列の音高・音素長を、特定の声で生成しなおす。
 *
 * 生成したJSON文字列を解放するには ::voicevox_json_free を使う。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] accent_phrases_json AccentPhraseの配列のJSON文字列
 * @param [in] style_id スタイルID
 * @param [out] output_accent_phrases_json 生成先
 *
 * @returns 結果コード
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `accent_phrases_json`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_audio_query_json`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_replace_mora_data(DLL &dll,
                                                          const struct VoicevoxSynthesizer *synthesizer,
                                                          const char *accent_phrases_json,
                                                          VoicevoxStyleId style_id,
                                                          char **output_accent_phrases_json);

/**
 * AccentPhraseの配列の音素長を、特定の声で生成しなおす。
 *
 * 生成したJSON文字列を解放するには ::voicevox_json_free を使う。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] accent_phrases_json AccentPhraseの配列のJSON文字列
 * @param [in] style_id スタイルID
 * @param [out] output_accent_phrases_json 生成先
 *
 * @returns 結果コード
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `accent_phrases_json`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_audio_query_json`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_replace_phoneme_length(DLL &dll,
                                                               const struct VoicevoxSynthesizer *synthesizer,
                                                               const char *accent_phrases_json,
                                                               VoicevoxStyleId style_id,
                                                               char **output_accent_phrases_json);

/**
 * AccentPhraseの配列の音高を、特定の声で生成しなおす。
 *
 * 生成したJSON文字列を解放するには ::voicevox_json_free を使う。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] accent_phrases_json AccentPhraseの配列のJSON文字列
 * @param [in] style_id スタイルID
 * @param [out] output_accent_phrases_json 生成先
 *
 * @returns 結果コード
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `accent_phrases_json`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_audio_query_json`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_replace_mora_pitch(DLL &dll,
                                                           const struct VoicevoxSynthesizer *synthesizer,
                                                           const char *accent_phrases_json,
                                                           VoicevoxStyleId style_id,
                                                           char **output_accent_phrases_json);

/**
 * デフォルトの `voicevox_synthesizer_synthesis` のオプションを生成する
 * @return デフォルト値が設定された `voicevox_synthesizer_synthesis` のオプション
 */
struct VoicevoxSynthesisOptions voicevox_make_default_synthesis_options(DLL &dll);

/**
 * AudioQueryから音声合成を行う。
 *
 * 生成したWAVデータを解放するには ::voicevox_wav_free を使う。
 *
 * @param [in] synthesizer 音声シンセサイザ
 * @param [in] audio_query_json AudioQueryのJSON文字列
 * @param [in] style_id スタイルID
 * @param [in] options オプション
 * @param [out] output_wav_length 出力のバイト長
 * @param [out] output_wav 出力先
 *
 * @returns 結果コード
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `audio_query_json`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_wav_length`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * - `output_wav`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_synthesis(DLL &dll,
                                                  const struct VoicevoxSynthesizer *synthesizer,
                                                  const char *audio_query_json,
                                                  VoicevoxStyleId style_id,
                                                  struct VoicevoxSynthesisOptions options,
                                                  uintptr_t *output_wav_length,
                                                  uint8_t **output_wav);

/**
 * デフォルトのテキスト音声合成オプションを生成する
 * @return テキスト音声合成オプション
 */
struct VoicevoxTtsOptions voicevox_make_default_tts_options(DLL &dll);

/**
 * AquesTalk風記法から音声合成を行う。
 *
 * 生成したWAVデータを解放するには ::voicevox_wav_free を使う。
 *
 * @param [in] synthesizer
 * @param [in] kana AquesTalk風記法
 * @param [in] style_id スタイルID
 * @param [in] options オプション
 * @param [out] output_wav_length 出力のバイト長
 * @param [out] output_wav 出力先
 *
 * @returns 結果コード
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `kana`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_wav_length`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * - `output_wav`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_tts_from_kana(DLL &dll,
                                                      const struct VoicevoxSynthesizer *synthesizer,
                                                      const char *kana,
                                                      VoicevoxStyleId style_id,
                                                      struct VoicevoxTtsOptions options,
                                                      uintptr_t *output_wav_length,
                                                      uint8_t **output_wav);

/**
 * 日本語テキストから音声合成を行う。
 *
 * 生成したWAVデータを解放するには ::voicevox_wav_free を使う。
 *
 * @param [in] synthesizer
 * @param [in] text UTF-8の日本語テキスト
 * @param [in] style_id スタイルID
 * @param [in] options オプション
 * @param [out] output_wav_length 出力のバイト長
 * @param [out] output_wav 出力先
 *
 * @returns 結果コード
 *
 * \safety{
 * - `synthesizer`は ::voicevox_synthesizer_new で得たものでなければならず、また ::voicevox_synthesizer_delete で解放されていてはいけない。
 * - `text`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_wav_length`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * - `output_wav`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_synthesizer_tts(DLL &dll,
                                            const struct VoicevoxSynthesizer *synthesizer,
                                            const char *text,
                                            VoicevoxStyleId style_id,
                                            struct VoicevoxTtsOptions options,
                                            uintptr_t *output_wav_length,
                                            uint8_t **output_wav);

/**
 * JSON文字列を解放する。
 *
 * @param [in] json 解放するJSON文字列
 *
 * \safety{
 * - `json`は以下のAPIで得られたポインタでなくてはいけない。
 *     - ::voicevox_create_supported_devices_json
 *     - ::voicevox_synthesizer_create_metas_json
 *     - ::voicevox_synthesizer_create_audio_query
 *     - ::voicevox_synthesizer_create_accent_phrases
 *     - ::voicevox_synthesizer_replace_mora_data
 *     - ::voicevox_synthesizer_replace_phoneme_length
 *     - ::voicevox_synthesizer_replace_mora_pitch
 *     - ::voicevox_user_dict_to_json
 * - 文字列の長さは生成時より変更されていてはならない。
 * - `json`は<a href="#voicevox-core-safety">読み込みと書き込みについて有効</a>でなければならない。
 * - `json`は以後<b>ダングリングポインタ</b>(_dangling pointer_)として扱われなくてはならない。
 * }
 */
void voicevox_json_free(DLL &dll,
                        char *json);

/**
 * WAVデータを解放する。
 *
 * @param [in] wav 解放するWAVデータ
 *
 * \safety{
 * - `wav`は以下のAPIで得られたポインタでなくてはいけない。
 *     - ::voicevox_synthesizer_synthesis
 *     - ::voicevox_synthesizer_tts
 * - `wav`は<a href="#voicevox-core-safety">読み込みと書き込みについて有効</a>でなければならない。
 * - `wav`は以後<b>ダングリングポインタ</b>(_dangling pointer_)として扱われなくてはならない。
 * }
 */
void voicevox_wav_free(DLL &dll,
                       uint8_t *wav);

/**
 * 結果コードに対応したメッセージ文字列を取得する。
 *
 * @param [in] result_code 結果コード
 *
 * @returns 結果コードに対応したメッセージ文字列
 *
 * \examples{
 * ```c
 * const char *actual = voicevox_error_result_to_message(VOICEVOX_RESULT_OK);
 * const char *EXPECTED = "エラーが発生しませんでした";
 * assert(strcmp(actual, EXPECTED) == 0);
 * ```
 *
 * ```c
 * const char *actual =
 *     voicevox_error_result_to_message(VOICEVOX_RESULT_LOAD_MODEL_ERROR);
 * const char *EXPECTED = "modelデータ読み込みに失敗しました";
 * assert(strcmp(actual, EXPECTED) == 0);
 * ```
 * }
 */
const char *voicevox_error_result_to_message(DLL &dll,
                                             VoicevoxResultCode result_code);

/**
 * ::VoicevoxUserDictWord を最低限のパラメータで作成する。
 *
 * @param [in] surface 表記
 * @param [in] pronunciation 読み
 * @returns ::VoicevoxUserDictWord
 */
struct VoicevoxUserDictWord voicevox_user_dict_word_make(DLL &dll,
                                                         const char *surface,
                                                         const char *pronunciation);

/**
 * ユーザー辞書を<b>構築</b>(_construct_)する。
 *
 * @returns ::VoicevoxUserDict
 */
struct VoicevoxUserDict *voicevox_user_dict_new(DLL &dll);

/**
 * ユーザー辞書にファイルを読み込ませる。
 *
 * @param [in] user_dict ユーザー辞書
 * @param [in] dict_path 読み込む辞書ファイルのパス
 * @returns 結果コード
 *
 * \safety{
 * - `user_dict`は ::voicevox_user_dict_new で得たものでなければならず、また ::voicevox_user_dict_delete で解放されていてはいけない。
 * - `dict_path`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_user_dict_load(DLL &dll,
                                           const struct VoicevoxUserDict *user_dict,
                                           const char *dict_path);

/**
 * ユーザー辞書に単語を追加する。
 *
 * @param [in] ユーザー辞書
 * @param [in] word 追加する単語
 * @param [out] output_word_uuid 追加した単語のUUID
 * @returns 結果コード
 *
 * # Safety
 * @param user_dict は有効な :VoicevoxUserDict のポインタであること
 *
 * \safety{
 * - `user_dict`は ::voicevox_user_dict_new で得たものでなければならず、また ::voicevox_user_dict_delete で解放されていてはいけない。
 * - `word->surface`と`word->pronunciation`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `output_word_uuid`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_user_dict_add_word(DLL &dll,
                                               const struct VoicevoxUserDict *user_dict,
                                               const struct VoicevoxUserDictWord *word,
                                               uint8_t (*output_word_uuid)[16]);

/**
 * ユーザー辞書の単語を更新する。
 *
 * @param [in] user_dict ユーザー辞書
 * @param [in] word_uuid 更新する単語のUUID
 * @param [in] word 新しい単語のデータ
 * @returns 結果コード
 *
 * \safety{
 * - `user_dict`は ::voicevox_user_dict_new で得たものでなければならず、また ::voicevox_user_dict_delete で解放されていてはいけない。
 * - `word_uuid`は<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * - `word->surface`と`word->pronunciation`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_user_dict_update_word(DLL &dll,
                                                  const struct VoicevoxUserDict *user_dict,
                                                  const uint8_t (*word_uuid)[16],
                                                  const struct VoicevoxUserDictWord *word);

/**
 * ユーザー辞書から単語を削除する。
 *
 * @param [in] user_dict ユーザー辞書
 * @param [in] word_uuid 削除する単語のUUID
 * @returns 結果コード
 *
 * \safety{
 * - `user_dict`は ::voicevox_user_dict_new で得たものでなければならず、また ::voicevox_user_dict_delete で解放されていてはいけない。
 * - `word_uuid`は<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_user_dict_remove_word(DLL &dll,
                                                  const struct VoicevoxUserDict *user_dict,
                                                  const uint8_t (*word_uuid)[16]);

/**
 * ユーザー辞書の単語をJSON形式で出力する。
 *
 * 生成したJSON文字列を解放するには ::voicevox_json_free を使う。
 *
 * @param [in] user_dict ユーザー辞書
 * @param [out] output_json 出力先
 * @returns 結果コード
 *
 * \safety{
 * - `user_dict`は ::voicevox_user_dict_new で得たものでなければならず、また ::voicevox_user_dict_delete で解放されていてはいけない。
 * - `output_json`は<a href="#voicevox-core-safety">書き込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_user_dict_to_json(DLL &dll,
                                              const struct VoicevoxUserDict *user_dict,
                                              char **output_json);

/**
 * 他のユーザー辞書をインポートする。
 *
 * @param [in] user_dict ユーザー辞書
 * @param [in] other_dict インポートするユーザー辞書
 * @returns 結果コード
 *
 * \safety{
 * - `user_dict`と`other_dict`は ::voicevox_user_dict_new で得たものでなければならず、また ::voicevox_user_dict_delete で解放されていてはいけない。
 * }
 */
VoicevoxResultCode voicevox_user_dict_import(DLL &dll,
                                             const struct VoicevoxUserDict *user_dict,
                                             const struct VoicevoxUserDict *other_dict);

/**
 * ユーザー辞書をファイルに保存する。
 *
 * @param [in] user_dict ユーザー辞書
 * @param [in] path 保存先のファイルパス
 *
 * \safety{
 * - `user_dict`は ::voicevox_user_dict_new で得たものでなければならず、また ::voicevox_user_dict_delete で解放されていてはいけない。
 * - `path`はヌル終端文字列を指し、かつ<a href="#voicevox-core-safety">読み込みについて有効</a>でなければならない。
 * }
 */
VoicevoxResultCode voicevox_user_dict_save(DLL &dll,
                                           const struct VoicevoxUserDict *user_dict,
                                           const char *path);

/**
 * ユーザー辞書を<b>破棄</b>(_destruct_)する。
 *
 * @param [in] user_dict 破棄対象
 *
 * \safety{
 * - `user_dict`は ::voicevox_user_dict_new で得たものでなければならず、また既にこの関数で解放されていてはいけない。
 * }
 */
void voicevox_user_dict_delete(DLL &dll,
                               struct VoicevoxUserDict *user_dict);

/**
 * デフォルトの初期化オプションを生成する
 * @return デフォルト値が設定された初期化オプション
 */
struct VoicevoxInitializeOptionsV14 voicevox_make_default_initialize_options_v14(DLL &dll);

/**
 * 初期化する
 * @param [in] options 初期化オプション
 * @return 結果コード #VoicevoxResultCode
 */
VoicevoxResultCode voicevox_initialize(DLL &dll,
                                          struct VoicevoxInitializeOptionsV14 options);

/**
 * モデルを読み込む
 * @param [in] speaker_id 読み込むモデルの話者ID
 * @return 結果コード #VoicevoxResultCode
 */
VoicevoxResultCode voicevox_load_model(DLL &dll,
                                          uint32_t speaker_id);

/**
 * ハードウェアアクセラレーションがGPUモードか判定する
 * @return GPUモードならtrue、そうでないならfalse
 */
bool voicevox_is_gpu_mode(DLL &dll);

/**
 * 指定したspeaker_idのモデルが読み込まれているか判定する
 * @return モデルが読み込まれているのであればtrue、そうでないならfalse
 */
bool voicevox_is_model_loaded(DLL &dll,
                              uint32_t speaker_id);

/**
 * このライブラリの利用を終了し、確保しているリソースを解放する
 */
void voicevox_finalize(DLL &dll);

/**
 * メタ情報をjsonで取得する
 * @return メタ情報のjson文字列
 */
const char *voicevox_get_metas_json(DLL &dll);

/**
 * サポートデバイス情報をjsonで取得する
 * @return サポートデバイス情報のjson文字列
 */
const char *voicevox_get_supported_devices_json(DLL &dll);

/**
 * 音素ごとの長さを推論する
 * @param [in] length phoneme_vector, output のデータ長
 * @param [in] phoneme_vector  音素データ
 * @param [in] speaker_id 話者ID
 * @param [out] output_predict_duration_length 出力データのサイズ
 * @param [out] output_predict_duration_data データの出力先
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param phoneme_vector 必ずlengthの長さだけデータがある状態で渡すこと
 * @param output_predict_duration_data_length uintptr_t 分のメモリ領域が割り当てられていること
 * @param output_predict_duration_data 成功後にメモリ領域が割り当てられるので ::voicevox_predict_duration_data_free で解放する必要がある
 */
VoicevoxResultCode voicevox_predict_duration(DLL &dll,
                                                uintptr_t length,
                                                int64_t *phoneme_vector,
                                                uint32_t speaker_id,
                                                uintptr_t *output_predict_duration_data_length,
                                                float **output_predict_duration_data);

/**
 * ::voicevox_predict_durationで出力されたデータを解放する
 * @param[in] predict_duration_data 確保されたメモリ領域
 *
 * # Safety
 * @param predict_duration_data 実行後に割り当てられたメモリ領域が解放される
 */
void voicevox_predict_duration_data_free(DLL &dll,
                                         float *predict_duration_data);

/**
 * モーラごとのF0を推論する
 * @param [in] length vowel_phoneme_vector, consonant_phoneme_vector, start_accent_vector, end_accent_vector, start_accent_phrase_vector, end_accent_phrase_vector, output のデータ長
 * @param [in] vowel_phoneme_vector 母音の音素データ
 * @param [in] consonant_phoneme_vector 子音の音素データ
 * @param [in] start_accent_vector アクセントの開始位置のデータ
 * @param [in] end_accent_vector アクセントの終了位置のデータ
 * @param [in] start_accent_phrase_vector アクセント句の開始位置のデータ
 * @param [in] end_accent_phrase_vector アクセント句の終了位置のデータ
 * @param [in] speaker_id 話者ID
 * @param [out] output_predict_intonation_data_length 出力データのサイズ
 * @param [out] output_predict_intonation_data データの出力先
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param vowel_phoneme_vector 必ずlengthの長さだけデータがある状態で渡すこと
 * @param consonant_phoneme_vector 必ずlengthの長さだけデータがある状態で渡すこと
 * @param start_accent_vector 必ずlengthの長さだけデータがある状態で渡すこと
 * @param end_accent_vector 必ずlengthの長さだけデータがある状態で渡すこと
 * @param start_accent_phrase_vector 必ずlengthの長さだけデータがある状態で渡すこと
 * @param end_accent_phrase_vector 必ずlengthの長さだけデータがある状態で渡すこと
 * @param output_predict_intonation_data_length uintptr_t 分のメモリ領域が割り当てられていること
 * @param output_predict_intonation_data 成功後にメモリ領域が割り当てられるので ::voicevox_predict_intonation_data_free で解放する必要がある
 */
VoicevoxResultCode voicevox_predict_intonation(DLL &dll,
                                                  uintptr_t length,
                                                  int64_t *vowel_phoneme_vector,
                                                  int64_t *consonant_phoneme_vector,
                                                  int64_t *start_accent_vector,
                                                  int64_t *end_accent_vector,
                                                  int64_t *start_accent_phrase_vector,
                                                  int64_t *end_accent_phrase_vector,
                                                  uint32_t speaker_id,
                                                  uintptr_t *output_predict_intonation_data_length,
                                                  float **output_predict_intonation_data);

/**
 * ::voicevox_predict_intonationで出力されたデータを解放する
 * @param[in] predict_intonation_data 確保されたメモリ領域
 *
 * # Safety
 * @param predict_intonation_data 実行後に割り当てられたメモリ領域が解放される
 */
void voicevox_predict_intonation_data_free(DLL &dll,
                                           float *predict_intonation_data);

/**
 * decodeを実行する
 * @param [in] length f0 , output のデータ長及び phoneme のデータ長に関連する
 * @param [in] phoneme_size 音素のサイズ phoneme のデータ長に関連する
 * @param [in] f0 基本周波数
 * @param [in] phoneme_vector 音素データ
 * @param [in] speaker_id 話者ID
 * @param [out] output_decode_data_length 出力先データのサイズ
 * @param [out] output_decode_data データ出力先
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param f0 必ず length の長さだけデータがある状態で渡すこと
 * @param phoneme_vector 必ず length * phoneme_size の長さだけデータがある状態で渡すこと
 * @param output_decode_data_length uintptr_t 分のメモリ領域が割り当てられていること
 * @param output_decode_data 成功後にメモリ領域が割り当てられるので ::voicevox_decode_data_free で解放する必要がある
 */
VoicevoxResultCode voicevox_decode(DLL &dll,
                                      uintptr_t length,
                                      uintptr_t phoneme_size,
                                      float *f0,
                                      float *phoneme_vector,
                                      uint32_t speaker_id,
                                      uintptr_t *output_decode_data_length,
                                      float **output_decode_data);

/**
 * ::voicevox_decodeで出力されたデータを解放する
 * @param[in] decode_data 確保されたメモリ領域
 *
 * # Safety
 * @param decode_data 実行後に割り当てられたメモリ領域が解放される
 */
void voicevox_decode_data_free(DLL &dll,
                               float *decode_data);

/**
 * デフォルトの AudioQuery のオプションを生成する
 * @return デフォルト値が設定された AudioQuery オプション
 */
struct VoicevoxAudioQueryOptions voicevox_make_default_audio_query_options(DLL &dll);

/**
 * AudioQuery を実行する
 * @param [in] text テキスト
 * @param [in] speaker_id 話者ID
 * @param [in] options AudioQueryのオプション
 * @param [out] output_audio_query_json AudioQuery を json でフォーマットしたもの
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param text null終端文字列であること
 * @param output_audio_query_json 自動でheapメモリが割り当てられるので ::voicevox_audio_query_json_free で解放する必要がある
 */
VoicevoxResultCode voicevox_audio_query(DLL &dll,
                                           const char *text,
                                           uint32_t speaker_id,
                                           struct VoicevoxAudioQueryOptions options,
                                           char **output_audio_query_json);

/**
 * デフォルトの `accent_phrases` のオプションを生成する
 * @return デフォルト値が設定された `accent_phrases` のオプション
 */
struct VoicevoxAccentPhrasesOptions voicevox_make_default_accent_phrases_options(DLL &dll);

/**
 * `accent_phrases` を実行する
 * @param [in] text テキスト。文字コードはUTF-8
 * @param [in] speaker_id 話者ID
 * @param [in] options `accent_phrases`のオプション
 * @param [out] output_accent_phrases_json アクセント句の情報の配列を json でフォーマットしたもの
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param text null終端文字列であること
 * @param output_accent_phrases_json 自動でheapメモリが割り当てられるので ::voicevox_accent_phrases_json_free で解放する必要がある
 */
VoicevoxResultCode voicevox_accent_phrases(DLL &dll,
                                           const char *text,
                                           uint32_t speaker_id,
                                           struct VoicevoxAccentPhrasesOptions options,
                                           char **output_accent_phrases_json);

/**
 *
 * アクセント句の音素長を変更する
 * @param [in] accent_phrases_json アクセント句の配列を json でフォーマットしたもの
 * @param [in] speaker_id 話者ID
 * @param [out] output_accent_phrases_json 音素長が変更されたアクセント句の情報の配列を json でフォーマットしたもの
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param accent_phrases_json null終端文字列であること
 * @param output_accent_phrases_json 自動でheapメモリが割り当てられるので ::voicevox_accent_phrases_json_free で解放する必要がある
 */
VoicevoxResultCode voicevox_mora_length(DLL &dll,
                                        const char *accent_phrases_json,
                                        uint32_t speaker_id,
                                        char **output_accent_phrases_json);

/**
 * アクセント句の音高を変更する
 * @param [in] accent_phrases_json アクセント句の配列を json でフォーマットしたもの
 * @param [in] speaker_id 話者ID
 * @param [out] output_accent_phrases_json 音高が変更されたアクセント句の情報の配列を json でフォーマットしたもの
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param accent_phrases_json null終端文字列であること
 * @param output_accent_phrases_json 自動でheapメモリが割り当てられるので ::voicevox_accent_phrases_json_free で解放する必要がある
 */
VoicevoxResultCode voicevox_mora_pitch(DLL &dll,
                                       const char *accent_phrases_json,
                                       uint32_t speaker_id,
                                       char **output_accent_phrases_json);

/**
 * アクセント句の音高・音素長を変更する
 * @param [in] accent_phrases_json アクセント句の配列を json でフォーマットしたもの
 * @param [in] speaker_id 話者ID
 * @param [out] output_accent_phrases_json 音高・音素長が変更されたアクセント句の情報の配列を json でフォーマットしたもの
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param accent_phrases_json null終端文字列であること
 * @param output_accent_phrases_json 自動でheapメモリが割り当てられるので ::voicevox_accent_phrases_json_free で解放する必要がある
 */
VoicevoxResultCode voicevox_mora_data(DLL &dll,
                                      const char *accent_phrases_json,
                                      uint32_t speaker_id,
                                      char **output_accent_phrases_json);


/**
 * jsonフォーマットされた AccnetPhrase データのメモリを解放する
 * @param [in] accented_phrase_json 解放する json フォーマットされた AccnetPhrase データ
 *
 * # Safety
 * @param voicevox_accent_phrases で確保されたポインタであり、かつ呼び出し側でバッファの変更を行われていないこと
 */
void voicevox_accent_phrases_json_free(DLL &dll,
                                       char *accented_phrase_json);

/**
 * AudioQuery から音声合成する
 * @param [in] audio_query_json jsonフォーマットされた AudioQuery
 * @param [in] speaker_id  話者ID
 * @param [in] options AudioQueryから音声合成オプション
 * @param [out] output_wav_length 出力する wav データのサイズ
 * @param [out] output_wav wav データの出力先
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param output_wav_length 出力先の領域が確保された状態でpointerに渡されていること
 * @param output_wav 自動で output_wav_length 分のデータが割り当てられるので ::voicevox_wav_free で解放する必要がある
 */
VoicevoxResultCode voicevox_synthesis(DLL &dll,
                                         const char *audio_query_json,
                                         uint32_t speaker_id,
                                         struct VoicevoxSynthesisOptions options,
                                         uintptr_t *output_wav_length,
                                         uint8_t **output_wav);

/**
 * デフォルトのテキスト音声合成オプションを生成する
 * @return テキスト音声合成オプション
 */
struct VoicevoxTtsOptionsV14 voicevox_make_default_tts_options_v14(DLL &dll);

/**
 * テキスト音声合成を実行する
 * @param [in] text テキスト
 * @param [in] speaker_id 話者ID
 * @param [in] options テキスト音声合成オプション
 * @param [out] output_wav_length 出力する wav データのサイズ
 * @param [out] output_wav wav データの出力先
 * @return 結果コード #VoicevoxResultCode
 *
 * # Safety
 * @param output_wav_length 出力先の領域が確保された状態でpointerに渡されていること
 * @param output_wav は自動で output_wav_length 分のデータが割り当てられるので ::voicevox_wav_free で解放する必要がある
 */
VoicevoxResultCode voicevox_tts(DLL &dll,
                                   const char *text,
                                   uint32_t speaker_id,
                                   struct VoicevoxTtsOptionsV14 options,
                                   uintptr_t *output_wav_length,
                                   uint8_t **output_wav);

/**
 * jsonフォーマットされた AudioQuery データのメモリを解放する
 * @param [in] audio_query_json 解放する json フォーマットされた AudioQuery データ
 *
 * # Safety
 * @param wav 確保したメモリ領域が破棄される
 */
void voicevox_audio_query_json_free(DLL &dll,
                                    char *audio_query_json);

/**
 * @fn
 * 初期化する
 * @brief 音声合成するための初期化を行う。他の関数を正しく実行するには先に初期化が必要
 * @param use_gpu trueならGPU用、falseならCPU用の初期化を行う
 * @param cpu_num_threads 推論に用いるスレッド数を設定する。0の場合論理コア数の半分か、物理コア数が設定される
 * @param load_all_models trueなら全てのモデルをロードする
 * @return 成功したらtrue、失敗したらfalse
 * @detail
 * 何度も実行可能。use_gpuを変更して実行しなおすことも可能。
 * 最後に実行したuse_gpuに従って他の関数が実行される。
 */
bool initialize_v(DLL &dll,
                  bool use_gpu,
                  int cpu_num_threads,
                  bool load_all_models);

/**
 * モデルをロードする
 * @param speaker_id 話者番号
 * @return 成功したらtrue、失敗したらfalse
 * @detail
 * 必ずしも話者とモデルが1:1対応しているわけではない。
 */
bool load_model(DLL &dll,
                int64_t speaker_id);

/**
 * @fn
 * モデルがロード済みかどうか
 * @param speaker_id 話者番号
 * @return ロード済みならtrue、そうでないならfalse
 */
bool is_model_loaded(DLL &dll,
                     int64_t speaker_id);

/**
 * @fn
 * 終了処理を行う
 * @brief 終了処理を行う。以降関数を利用するためには再度初期化を行う必要がある。
 * @detail
 * 何度も実行可能。実行せずにexitしても大抵の場合問題ないが、
 * CUDAを利用している場合これを実行しておかないと例外が起こることがある。
 */
void finalize_v(DLL &dll);

/**
 * @fn
 * メタ情報を取得する
 * @brief 話者名や話者IDのリストを取得する
 * @return メタ情報が格納されたjson形式の文字列
 */
const char *metas_v(DLL &dll);

/**
 * @fn
 * 対応デバイス情報を取得する
 * @brief cpu, cudaのうち、使用可能なデバイス情報を取得する
 * @return 各デバイスが使用可能かどうかをboolで格納したjson形式の文字列
 */
const char *supported_devices(DLL &dll);

/**
 * @fn
 * 音素ごとの長さを求める
 * @brief 音素列から、音素ごとの長さを求める
 * @param length 音素列の長さ
 * @param phoneme_list 音素列
 * @param speaker_id 話者番号
 * @return 音素ごとの長さ
 */
bool yukarin_s_forward(DLL &dll,
                       int64_t length,
                       int64_t *phoneme_list,
                       int64_t *speaker_id,
                       float *output);

/**
 * @fn
 * モーラごとの音高を求める
 * @brief モーラごとの音素列とアクセント情報から、モーラごとの音高を求める
 * @param length モーラ列の長さ
 * @param vowel_phoneme_list 母音の音素列
 * @param consonant_phoneme_list 子音の音素列
 * @param start_accent_list アクセントの開始位置
 * @param end_accent_list アクセントの終了位置
 * @param start_accent_phrase_list アクセント句の開始位置
 * @param end_accent_phrase_list アクセント句の終了位置
 * @param speaker_id 話者番号
 * @return モーラごとの音高
 */
bool yukarin_sa_forward(DLL &dll,
                        int64_t length,
                        int64_t *vowel_phoneme_list,
                        int64_t *consonant_phoneme_list,
                        int64_t *start_accent_list,
                        int64_t *end_accent_list,
                        int64_t *start_accent_phrase_list,
                        int64_t *end_accent_phrase_list,
                        int64_t *speaker_id,
                        float *output);

/**
 * @fn
 * 波形を求める
 * @brief フレームごとの音素と音高から、波形を求める
 * @param length フレームの長さ
 * @param phoneme_size 音素の種類数
 * @param f0 フレームごとの音高
 * @param phoneme フレームごとの音素
 * @param speaker_id 話者番号
 * @return 音声波形
 */
bool decode_forward(DLL &dll,
                    int64_t length,
                    int64_t phoneme_size,
                    float *f0,
                    float *phoneme,
                    int64_t *speaker_id,
                    float *output);

/**
 * @fn
 * 最後に発生したエラーのメッセージを取得する
 * @return エラーメッセージ
 */
const char *last_error_message(DLL &dll);

/**
 * @fn
 * open jtalkの辞書を読み込む
 * @return 結果コード
 */
VoicevoxResultCode voicevox_load_openjtalk_dict(DLL &dll,
                                                   const char *dict_path);

/**
 * @fn
 * text to spearchを実行する
 * @param text 音声データに変換するtextデータ
 * @param speaker_id 話者番号
 * @param output_binary_size 音声データのサイズを出力する先のポインタ
 * @param output_wav 音声データを出力する先のポインタ。使用が終わったらvoicevox_wav_freeで開放する必要がある
 * @return 結果コード
 */
VoicevoxResultCode voicevox_tts_v12(DLL &dll,
                                       const char *text,
                                       int64_t speaker_id,
                                       int *output_binary_size,
                                       uint8_t **output_wav);

/**
 * @fn
 * text to spearchをAquesTalkライクな記法で実行する
 * @param text 音声データに変換するtextデータ
 * @param speaker_id 話者番号
 * @param output_binary_size 音声データのサイズを出力する先のポインタ
 * @param output_wav 音声データを出力する先のポインタ。使用が終わったらvoicevox_wav_freeで開放する必要がある
 * @return 結果コード
 */
VoicevoxResultCode voicevox_tts_from_kana(DLL &dll,
                                             const char *text,
                                             int64_t speaker_id,
                                             int *output_binary_size,
                                             uint8_t **output_wav);

/**
 * @fn
 * 初期化する
 * @brief 音声合成するための初期化を行う。他の関数を正しく実行するには先に初期化が必要
 * @param root_dir_path 必要なファイルがあるディレクトリ。相対パス・絶対パスどちらも指定可能。文字コードはUTF-8
 * @param use_gpu trueならGPU用、falseならCPU用の初期化を行う
 * @param cpu_num_threads 推論に用いるスレッド数を設定する。0の場合論理コア数の半分か、物理コア数が設定される
 * @return 成功したらtrue、失敗したらfalse
 * @detail
 * 何度も実行可能。use_gpuを変更して実行しなおすことも可能。
 * 最後に実行したuse_gpuに従って他の関数が実行される。
 */
bool initialize_v10(DLL &dll,
                    const char *root_dir_path,
                    bool use_gpu,
                    int cpu_num_threads);

/**
 * @fn
 * 初期化する
 * @brief 音声合成するための初期化を行う。他の関数を正しく実行するには先に初期化が必要
 * @param root_dir_path 必要なファイルがあるディレクトリ。相対パス・絶対パスどちらも指定可能。文字コードはUTF-8
 * @param use_gpu trueならGPU用、falseならCPU用の初期化を行う
 * @return 成功したらtrue、失敗したらfalse
 * @detail
 * 何度も実行可能。use_gpuを変更して実行しなおすことも可能。
 * 最後に実行したuse_gpuに従って他の関数が実行される。
 */
bool initialize_v5(DLL &dll,
                   const char *root_dir_path,
                   bool use_gpu);

/**
 * @fn
 * 音素ごとの長さを求める
 * @brief 音素列から、音素ごとの長さを求める
 * @param length 音素列の長さ
 * @param phoneme_list 音素列
 * @param speaker_id 話者番号
 * @return 音素ごとの長さ
 */
bool yukarin_s_forward_v5(DLL &dll,
                          int length,
                          long *phoneme_list,
                          long *speaker_id,
                          float *output);

/**
 * @fn
 * モーラごとの音高を求める
 * @brief モーラごとの音素列とアクセント情報から、モーラごとの音高を求める
 * @param length モーラ列の長さ
 * @param vowel_phoneme_list 母音の音素列
 * @param consonant_phoneme_list 子音の音素列
 * @param start_accent_list アクセントの開始位置
 * @param end_accent_list アクセントの終了位置
 * @param start_accent_phrase_list アクセント句の開始位置
 * @param end_accent_phrase_list アクセント句の終了位置
 * @param speaker_id 話者番号
 * @return モーラごとの音高
 */
bool yukarin_sa_forward_v5(DLL &dll,
                           int length,
                           long *vowel_phoneme_list,
                           long *consonant_phoneme_list,
                           long *start_accent_list,
                           long *end_accent_list,
                           long *start_accent_phrase_list,
                           long *end_accent_phrase_list,
                           long *speaker_id,
                           float *output);

/**
 * @fn
 * 波形を求める
 * @brief フレームごとの音素と音高から、波形を求める
 * @param length フレームの長さ
 * @param phoneme_size 音素の種類数
 * @param f0 フレームごとの音高
 * @param phoneme フレームごとの音素
 * @param speaker_id 話者番号
 * @return 音声波形
 */
bool decode_forward_v5(DLL &dll,
                       int length,
                       int phoneme_size,
                       float *f0,
                       float *phoneme,
                       long *speaker_id,
                       float *output);

#endif /* VOICEVOX_CORE_INCLUDE_GUARD */
