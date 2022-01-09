#include <gtest/gtest.h>
#include <string>

#include "sio/audio.h"

namespace sio {

TEST(Audio, LoaderAndResampler) {
    std::string audio_path = "testdata/MINI/audio/audio1.wav";
    std::vector<float> audio;
    float sample_rate = 0.0f;

    // audio loading
    ReadAudio(audio_path, &audio, &sample_rate);
    EXPECT_EQ(audio.size(), 20480);
    EXPECT_EQ(sample_rate, 16000);

    /*
    // audio resampling
    Resampler resampler(16000, 8000);
    EXPECT_EQ(resampler.SourceSampleRate(), 16000.0);
    EXPECT_EQ(resampler.TargetSampleRate(),  8000.0);

    kaldi::Vector<float> resampled;
    resampler.Forward(audio.data(), audio.size(), sample_rate, &resampled, true);
    EXPECT_EQ(resampled.Dim(), 10240);
    */
}

} // namespace sio
