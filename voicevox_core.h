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
 * 初期化オプション
 */
typedef struct VoicevoxInitializeOptionsV0_14
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
} VoicevoxInitializeOptionsV0_14;

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
 * ::voicevox_synthesis_v0_14 のオプション。
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
typedef struct VoicevoxTtsOptionsV0_14
{
  /**
   * aquestalk形式のkanaとしてテキストを解釈する
   */
  bool kana;
  /**
   * 疑問文の調整を有効にする
   */
  bool enable_interrogative_upspeak;
} VoicevoxTtsOptionsV0_14;

/**
 * voicevoxのバージョンを取得する。
 * @return SemVerでフォーマットされたバージョン。
 */
const char *voicevox_get_version_v0_14(DLL &dll);

/**
 * デフォルトの `voicevox_synthesizer_synthesis_v0_16` のオプションを生成する
 * @return デフォルト値が設定された `voicevox_synthesizer_synthesis_v0_16` のオプション
 */
struct VoicevoxSynthesisOptions voicevox_make_default_synthesis_options_v0_14(DLL &dll);

/**
 * WAVデータを解放する。
 *
 * @param [in] wav 解放するWAVデータ
 *
 * \safety{
 * - `wav`は以下のAPIで得られたポインタでなくてはいけない。
 *     - ::voicevox_synthesizer_synthesis_v0_16
 *     - ::voicevox_synthesizer_tts_v0_16
 * - `wav`は<a href="#voicevox-core-safety">読み込みと書き込みについて有効</a>でなければならない。
 * - `wav`は以後<b>ダングリングポインタ</b>(_dangling pointer_)として扱われなくてはならない。
 * }
 */
void voicevox_wav_free_v0_12(DLL &dll,
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
 * const char *actual = voicevox_error_result_to_message_v0_12(VOICEVOX_RESULT_OK);
 * const char *EXPECTED = "エラーが発生しませんでした";
 * assert(strcmp(actual, EXPECTED) == 0);
 * ```
 *
 * ```c
 * const char *actual =
 *     voicevox_error_result_to_message_v0_12(VOICEVOX_RESULT_LOAD_MODEL_ERROR);
 * const char *EXPECTED = "modelデータ読み込みに失敗しました";
 * assert(strcmp(actual, EXPECTED) == 0);
 * ```
 * }
 */
const char *voicevox_error_result_to_message_v0_12(DLL &dll,
                                                   VoicevoxResultCode result_code);

/**
 * デフォルトの初期化オプションを生成する
 * @return デフォルト値が設定された初期化オプション
 */
struct VoicevoxInitializeOptionsV0_14 voicevox_make_default_initialize_options_v0_14(DLL &dll);

/**
 * 初期化する
 * @param [in] options 初期化オプション
 * @return 結果コード #VoicevoxResultCode
 */
VoicevoxResultCode voicevox_initialize_v0_14(DLL &dll,
                                             struct VoicevoxInitializeOptionsV0_14 options);

/**
 * モデルを読み込む
 * @param [in] speaker_id 読み込むモデルの話者ID
 * @return 結果コード #VoicevoxResultCode
 */
VoicevoxResultCode voicevox_load_model_v0_14(DLL &dll,
                                             uint32_t speaker_id);

/**
 * ハードウェアアクセラレーションがGPUモードか判定する
 * @return GPUモードならtrue、そうでないならfalse
 */
bool voicevox_is_gpu_mode_v0_14(DLL &dll);

/**
 * 指定したspeaker_idのモデルが読み込まれているか判定する
 * @return モデルが読み込まれているのであればtrue、そうでないならfalse
 */
bool voicevox_is_model_loaded_v0_14(DLL &dll,
                                    uint32_t speaker_id);

/**
 * このライブラリの利用を終了し、確保しているリソースを解放する
 */
void voicevox_finalize_v0_14(DLL &dll);

/**
 * メタ情報をjsonで取得する
 * @return メタ情報のjson文字列
 */
const char *voicevox_get_metas_json_v0_14(DLL &dll);

/**
 * サポートデバイス情報をjsonで取得する
 * @return サポートデバイス情報のjson文字列
 */
const char *voicevox_get_supported_devices_json_v0_14(DLL &dll);

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
 * @param output_predict_duration_data 成功後にメモリ領域が割り当てられるので ::voicevox_predict_duration_data_free_v0_14 で解放する必要がある
 */
VoicevoxResultCode voicevox_predict_duration_v0_14(DLL &dll,
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
void voicevox_predict_duration_data_free_v0_14(DLL &dll,
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
 * @param output_predict_intonation_data 成功後にメモリ領域が割り当てられるので ::voicevox_predict_intonation_data_free_v0_14 で解放する必要がある
 */
VoicevoxResultCode voicevox_predict_intonation_v0_14(DLL &dll,
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
void voicevox_predict_intonation_data_free_v0_14(DLL &dll,
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
 * @param output_decode_data 成功後にメモリ領域が割り当てられるので ::voicevox_decode_data_free_v0_14 で解放する必要がある
 */
VoicevoxResultCode voicevox_decode_v0_14(DLL &dll,
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
void voicevox_decode_data_free_v0_14(DLL &dll,
                                     float *decode_data);

/**
 * デフォルトの AudioQuery のオプションを生成する
 * @return デフォルト値が設定された AudioQuery オプション
 */
struct VoicevoxAudioQueryOptions voicevox_make_default_audio_query_options_v0_14(DLL &dll);

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
 * @param output_audio_query_json 自動でheapメモリが割り当てられるので ::voicevox_audio_query_json_free_v0_14 で解放する必要がある
 */
VoicevoxResultCode voicevox_audio_query_v0_14(DLL &dll,
                                              const char *text,
                                              uint32_t speaker_id,
                                              struct VoicevoxAudioQueryOptions options,
                                              char **output_audio_query_json);

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
 * @param output_wav 自動で output_wav_length 分のデータが割り当てられるので ::voicevox_wav_free_v0_12 で解放する必要がある
 */
VoicevoxResultCode voicevox_synthesis_v0_14(DLL &dll,
                                            const char *audio_query_json,
                                            uint32_t speaker_id,
                                            struct VoicevoxSynthesisOptions options,
                                            uintptr_t *output_wav_length,
                                            uint8_t **output_wav);

/**
 * デフォルトのテキスト音声合成オプションを生成する
 * @return テキスト音声合成オプション
 */
struct VoicevoxTtsOptionsV0_14 voicevox_make_default_tts_options_v0_14(DLL &dll);

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
 * @param output_wav は自動で output_wav_length 分のデータが割り当てられるので ::voicevox_wav_free_v0_12 で解放する必要がある
 */
VoicevoxResultCode voicevox_tts_v0_14(DLL &dll,
                                      const char *text,
                                      uint32_t speaker_id,
                                      struct VoicevoxTtsOptionsV0_14 options,
                                      uintptr_t *output_wav_length,
                                      uint8_t **output_wav);

/**
 * jsonフォーマットされた AudioQuery データのメモリを解放する
 * @param [in] audio_query_json 解放する json フォーマットされた AudioQuery データ
 *
 * # Safety
 * @param wav 確保したメモリ領域が破棄される
 */
void voicevox_audio_query_json_free_v0_14(DLL &dll,
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
bool initialize_v0_12(DLL &dll,
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
bool load_model_v0_12(DLL &dll,
                      int64_t speaker_id);

/**
 * @fn
 * モデルがロード済みかどうか
 * @param speaker_id 話者番号
 * @return ロード済みならtrue、そうでないならfalse
 */
bool is_model_loaded_v0_12(DLL &dll,
                           int64_t speaker_id);

/**
 * @fn
 * 終了処理を行う
 * @brief 終了処理を行う。以降関数を利用するためには再度初期化を行う必要がある。
 * @detail
 * 何度も実行可能。実行せずにexitしても大抵の場合問題ないが、
 * CUDAを利用している場合これを実行しておかないと例外が起こることがある。
 */
void finalize_v0_10(DLL &dll);

/**
 * @fn
 * メタ情報を取得する
 * @brief 話者名や話者IDのリストを取得する
 * @return メタ情報が格納されたjson形式の文字列
 */
const char *metas_v0_5(DLL &dll);

/**
 * @fn
 * 対応デバイス情報を取得する
 * @brief cpu, cudaのうち、使用可能なデバイス情報を取得する
 * @return 各デバイスが使用可能かどうかをboolで格納したjson形式の文字列
 */
const char *supported_devices_v0_10(DLL &dll);

/**
 * @fn
 * 音素ごとの長さを求める
 * @brief 音素列から、音素ごとの長さを求める
 * @param length 音素列の長さ
 * @param phoneme_list 音素列
 * @param speaker_id 話者番号
 * @return 音素ごとの長さ
 */
bool yukarin_s_forward_v0_8(DLL &dll,
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
bool yukarin_sa_forward_v0_8(DLL &dll,
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
bool decode_forward_v0_8(DLL &dll,
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
const char *last_error_message_v0_5(DLL &dll);

/**
 * @fn
 * open jtalkの辞書を読み込む
 * @return 結果コード
 */
VoicevoxResultCode voicevox_load_openjtalk_dict_v0_12(DLL &dll,
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
VoicevoxResultCode voicevox_tts_v0_12(DLL &dll,
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
VoicevoxResultCode voicevox_tts_from_kana_v0_12(DLL &dll,
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
bool initialize_v0_10(DLL &dll,
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
bool initialize_v0_5(DLL &dll,
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
bool yukarin_s_forward_v0_5(DLL &dll,
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
bool yukarin_sa_forward_v0_5(DLL &dll,
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
bool decode_forward_v0_5(DLL &dll,
                         int length,
                         int phoneme_size,
                         float *f0,
                         float *phoneme,
                         long *speaker_id,
                         float *output);

#endif /* VOICEVOX_CORE_INCLUDE_GUARD */
