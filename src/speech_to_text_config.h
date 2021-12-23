#ifndef SIO_SPEECH_TO_TEXT_CONFIG_H
#define SIO_SPEECH_TO_TEXT_CONFIG_H

#include "sio/error.h"
#include "sio/str.h"
#include "sio/feature.h"
#include "sio/config_loader.h"

namespace sio {
struct SpeechToTextConfig {
  bool online = true;

  std::string mean_var_norm_file;
  std::string tokenizer;
  std::string model;
  std::string graph;
  std::string context;

  bool do_endpointing = false;

  FeatureConfig feature;

  Error Register(ConfigLoader* loader, const std::string module = "") {
    loader->Add(module, ".online", &online);
    loader->Add(module, ".mean_var_norm_file", &mean_var_norm_file);
    loader->Add(module, ".tokenizer", &tokenizer);
    loader->Add(module, ".model", &model);
    loader->Add(module, ".graph", &graph);
    loader->Add(module, ".context", &context);
    loader->Add(module, ".do_endpointing", &do_endpointing);

    loader->Add(module + ".feature", ".type", &feature.feature_type);
    loader->Add(module + ".feature", ".fbank_config", &feature.fbank_config);

    return Error::OK;
  }

  Error Load(const std::string& config_file) {
    ConfigLoader loader;
    Register(&loader);
    loader.Load(config_file);
    loader.Print();

    return Error::OK;
  }

}; // class SpeechToTextConfig
}  // namespace sio
#endif
