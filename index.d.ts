export declare class Voicevox {
  constructor(openJtalkDicDirPath: string, modelPaths: Array<string>);
  synthesize(text: string, styleId: number, options?: SynthesizeOptions): Promise<Buffer>;
}
export interface SynthesizeOptions {
  speed?: number;
  pitch?: number;
  intonation?: number;
  volume?: number;
}