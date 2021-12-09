#include <iostream>

#include "feat/wave-reader.h"
#include "online2/online-timing.h"

#include "sio/sio.h"

int main() {
    using namespace sio;

    float sample_rate = 16000;

    float chunk_secs = 0.2;
    int chunk_samples = (chunk_secs > 0) ? int(sample_rate * chunk_secs) : std::numeric_limits<int>::max();
    assert(chunk_samples > 0);

    std::ifstream wav_scp("testdata/MINI/wav.scp");
    std::string line;
    while (std::getline(wav_scp, line)) {
        std::vector<std::string> fields = absl::StrSplit(line, absl::ByAnyChar(" \t,:;"));
        if (fields.size() != 2) continue;

        std::string& audio_key  = fields[0];
        std::string& audio_path = fields[1];
        SIO_DEBUG << audio_key << " " << audio_path;

        kaldi::WaveData wave_data;
        std::ifstream stream(audio_path, std::ifstream::binary);
        wave_data.Read(stream);
        kaldi::SubVector<float> audio(wave_data.Data(), 0); // only use channel 0

        assert(wave_data.SampFreq() == sample_rate);

        kaldi::OnlineTimer decoding_timer(audio_key);
        //recognizer->StartSession(audio_key.c_str());
        int samples_done = 0;
        while (samples_done < audio.Dim()) {
            int samples_remaining = audio.Dim() - samples_done;
            int n = chunk_samples < samples_remaining ? chunk_samples : samples_remaining;
    
            kaldi::SubVector<float> audio_chunk(audio, samples_done, n);
            //recognizer->AcceptAudioChunk(audio_chunk.Data(), audio_chunk.SizeInBytes(), audio_format);
    
            samples_done += n;
            decoding_timer.WaitUntil(samples_done / sample_rate);
    
            //if (opts.do_endpointing && recognizer->EndOfSentenceDetected()) {
            //    break;
            //}
            SIO_DEBUG << samples_done << " samples decoded.";
        }
        SIO_INFO << "Decoded " << samples_done << " samples for " << audio_key;
        //recognizer->StopSession();
    }

    return 0;
}
