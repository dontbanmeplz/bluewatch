/*
  AudioOutputULP
  Outputs to ESP32 DAC through the ULP, freeing I2S for other uses
  
  Copyright (C) 2020  Martin Laclaustra, based on bitluni's code

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Instructions:
// AudioOutputULP out = new AudioOutputULP(); // stereo
// Connect left channel on pin 25
// Connect right channel on pin 26
// OR
// Connect mono channel on either of them (stereo samples are downmixed)
// AudioOutputULP out = new AudioOutputULP(1); // mono, only DAC 1
// OR
// AudioOutputULP out = new AudioOutputULP(2); // mono, only DAC 2


#ifndef _AUDIOOUTPUTULP_H
#define _AUDIOOUTPUTULP_H

#include "AudioOutput.h"

#include <stdint.h>
#ifdef ESP32

class AudioOutputULP : public AudioOutput
{
  public:
    AudioOutputULP(int argActiveDACs=3) {if(argActiveDACs<1||argActiveDACs>2)argActiveDACs=3;activeDACs=argActiveDACs;stereoOutput=activeDACs==3;};
    ~AudioOutputULP() {};
    virtual bool begin() override;
    virtual bool ConsumeSample(int16_t sample[2]) override;
    virtual bool stop() override;
    enum : int { DAC1 = 1, DAC2 = 2 };
  private:
    int lastFilledWord = 0;
    uint8_t bufferedOddSample = 128;
    bool waitingOddSample = true; // must be set to false for mono output
    int activeDACs = 3; // 1:DAC1; 2:DAC2; 3:both;
    bool stereoOutput = true;
    const int opcodeCount = 20;
    const uint32_t dacTableStart1 = 2048 - 512;
    const uint32_t dacTableStart2 = dacTableStart1 - 512;
    uint32_t totalSampleWords = 2048 - 512 - 512 - (opcodeCount + 1); // add 512 for mono
    const int totalSamples = totalSampleWords * 2;
    const uint32_t indexAddress = opcodeCount;
    const uint32_t bufferStart = indexAddress + 1;
};

#else

#error Only the ESP32 supports ULP audio output

#endif

#endif
#ifndef _DRIVER_DAC_H_
#define _DRIVER_DAC_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    DAC_CHANNEL_1 = 1,  /*!< DAC channel 1 is GPIO25 */
    DAC_CHANNEL_2,      /*!< DAC channel 2 is GPIO26 */
    DAC_CHANNEL_MAX,
} dac_channel_t;

/**
 * @brief Set Dac output voltage.
 *
 * Dac width is 8bit ,and the voltage max is vdd
 *
 * @param channel dac channel
 * @param dac_value dac output value
 *
 * @return
 *     - ESP_OK success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
//esp_err_t dac_out_voltage(dac_channel_t channel, uint8_t dac_value);

/**
 *----------EXAMPLE TO USE DAC------------ *
 * @code{c}
 * dac_out_voltage(DAC_CHANNEL_1,200);//the dac out voltage ≈ 200*vdd/255
 * @endcode
 **/

#ifdef __cplusplus
}
#endif

#endif  /*_DRIVER_DAC_H_*/