import bindings from "bindings";
const voicevox = bindings("voicevox");

export function initialize(
  accelerationMode: number,
  cpuNumThreads: number,
  loadAllModels: boolean,
  openJTalkDictDir: string
): number {
  return voicevox.initialize(
    accelerationMode,
    cpuNumThreads,
    loadAllModels,
    openJTalkDictDir
  );
}

export function getVersion(): string {
  return voicevox.get_version();
}

export function loadModel(speakerId: number): number {
  return voicevox.load_model(speakerId);
}

export function isGpuMode(): boolean {
  return voicevox.is_gpu_mode();
}

export function isModelLoaded(speakerId: number): boolean {
  return voicevox.is_model_loaded(speakerId);
}

export function finalize(): void {
  voicevox.finalize();
}

export function getMetasJson(): string {
  return voicevox.get_metas_json();
}

export function getSupportedDevicesJson(): string {
  return voicevox.get_supported_devices_json();
}

export function audioQuery(
  text: string,
  speakerId: number,
  kana: boolean
): VoicevoxAudioQueryResult {
  return voicevox.audio_query(
    text,
    speakerId,
    kana
  );
}

export function synthesis(
  audioQueryJson: string,
  speakerId: number,
  enableInterrogativeUpspeak: boolean
): VoicevoxSynthesisResult {
  return voicevox.synthesis(
    audioQueryJson,
    speakerId,
    enableInterrogativeUpspeak
  );
}

export function errorResultToMessage(resultCode: number): string {
  return voicevox.error_result_to_message(resultCode);
}

interface VoicevoxAudioQueryResult {
  result: number;
  output: string;
}

interface VoicevoxSynthesisResult {
  result: number;
  output: Buffer;
}