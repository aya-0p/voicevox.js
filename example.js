/**
 * @version 0.16.x
 */
const { VoicevoxAccelerationMode } = require("./index");
const { Voicevox } = require("./v0.15");
const fs = require("node:fs/promises");
const path = require("node:path");

(async () => {
  const voicevox = new Voicevox("fullpath/to/libvoicevox_core.so");
  const voicevoxOpenJtalkRc = await voicevox.openJtalkRcNew("fullpath/to/open_jtalk_dic_dir");
  const voicevoxInitializeOptions = Voicevox.makeDefaultInitializeOptions();
  voicevoxInitializeOptions.accelerationMode = VoicevoxAccelerationMode.VOICEVOX_ACCELERATION_MODE_CPU;
  voicevoxInitializeOptions.cpuNumThreads = 4;
  const voicevoxSynthesizer = await voicevox.synthesizerNew(voicevoxOpenJtalkRc, voicevoxInitializeOptions);
  voicevoxOpenJtalkRc.delete();
  const voiceModels = await fs.readdir("fullpath/to/voice_model_dir");
  for (const voiceModelFileName of voiceModels) {
    const voiceModel = await voicevox.voiceModelNewFromPath(path.join("fullpath/to/voice_model_dir", voiceModelFileName));
    await voicevoxSynthesizer.loadVoiceModel(voiceModel);
    voiceModel.delete();
  }
  const audioQuery = await voicevoxSynthesizer.createAudioQuery("こんにちは", 0);
  const voicevoxSynthesisOptions = Voicevox.makeDefaultSynthesisOptions();
  voicevoxSynthesisOptions.enableInterrogativeUpspeak = true;
  const wav = await voicevoxSynthesizer.synthesis(audioQuery, 0, voicevoxSynthesisOptions);
  await fs.writeFile("fullpath/to/output.wav", wav);
  voicevoxSynthesizer.delete();
})();
