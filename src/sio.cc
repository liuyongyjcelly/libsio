#include "sio.h"

#include "sio/stt.h"
//#include "sio/tts.h"

struct sio_handle sio_create(const char* path) {
    sio::SpeechToTextModel* p = new sio::SpeechToTextModel;
    p->Load(path);
    return { (uintptr_t)p, (uintptr_t)nullptr };
}

int sio_destroy(struct sio_handle sio) {
    delete (sio::SpeechToTextModel*)sio.stt_module;
    //delete (sio::TextToSpeechModel*)sio.tts_module;
    return 0;
}

struct sio_stt_handle sio_stt_create(struct sio_handle sio) {
    sio::SpeechToText* p = new sio::SpeechToText;
    p->Load(*(sio::SpeechToTextModel*)sio.stt_module);
    return { (uintptr_t)p };
}

int sio_stt_destroy(struct sio_stt_handle stt) {
    delete (sio::SpeechToText*)stt.runtime;
    return 0;
}

int sio_stt_speech(struct sio_stt_handle stt, const float* samples, int n, float sample_rate) {
    return ((sio::SpeechToText*)stt.runtime)->Speech(samples, n, sample_rate);
}

int sio_stt_to(struct sio_stt_handle stt) {
    return ((sio::SpeechToText*)stt.runtime)->To();
}

const char* sio_stt_text(struct sio_stt_handle stt) {
    return ((sio::SpeechToText*)stt.runtime)->Text();
}

int sio_stt_reset(struct sio_stt_handle stt) {
    return ((sio::SpeechToText*)stt.runtime)->Reset();
}

