/**
 * @version 0.16.x
 */
(async () => {
  const { VoicevoxAccelerationMode, VoicevoxAccelerationModeV0_14 } = require("./index");
  const { Voicevox } = require("./v0.16");
  const fs = require("node:fs/promises");
  const path = require("node:path");
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

/**
 * version 0.14.x では一部利用できない関数が存在するため注意してください(例では利用していません)
 * @version 0.15.x
 * @version 0.14.x
 */
(async () => {
  const { VoicevoxAccelerationModeV0_14 } = require("./index");
  const { Voicevox } = require("./v0.14"); // or require("./v0.15");
  const fs = require("node:fs/promises");
  const path = require("node:path");
  const voicevox = new Voicevox("fullpath/to/libvoicevox_core.so");
  const voicevoxInitializeOptions = Voicevox.voicevoxMakeDefaultInitializeOptions();
  voicevoxInitializeOptions.accelerationMode = VoicevoxAccelerationModeV0_14.VOICEVOX_ACCELERATION_MODE_CPU;
  voicevoxInitializeOptions.cpuNumThreads = 4;
  voicevoxInitializeOptions.loadAllModels = false;
  voicevoxInitializeOptions.openJtalkDictDir = "fullpath/to/open_jtalk_dic_dir";
  await voicevox.voicevoxInitialize(voicevoxInitializeOptions);
  await voicevox.voicevoxLoadModel(0);
  const voicevoxAudioQueryOptions = Voicevox.voicevoxMakeDefaultAudioQueryOptions();
  voicevoxAudioQueryOptions.kana = false;
  const audioQuery = await voicevox.voicevoxAudioQuery("こんにちは", 0, voicevoxAudioQueryOptions);
  const voicevoxSynthesisOptions = Voicevox.voicevoxMakeDefaultSynthesisOptions();
  voicevoxSynthesisOptions.enableInterrogativeUpspeak = true;
  const wav = await voicevox.voicevoxSynthesis(audioQuery, 0, voicevoxSynthesisOptions);
  await fs.writeFile("fullpath/to/output.wav", wav);
  await voicevox.voicevoxFinalize();
})();
