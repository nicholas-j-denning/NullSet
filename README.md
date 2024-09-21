# Null Set Modules for VCV Rack

![Screenshot](https://github.com/nicholas-j-denning/NullSet/blob/main/Screenshot.png)

## Poly LFT

Easily create poly triangle shaped LFOs with evenly spread phases. Useful for scanning wavetables.

- Poly: Number of channels of polyphony
- Rate: Frequency
- Min: Minimum of output range
- Max: Maximum of output range

## Poly Auto Pan

Spread a polyphonic signal across a stereo output with a panning LFO. Signals will be spread with evenly distributed phases.

- In: Polyphonic audio input
- Rate: LFO frequency
- Trim: Adjust output level

## Roman Quantizer

Quantize polyphonic signals to a sequence of chords using Roman numeral notation.

- Right Click: Set chord per step
- In: Polyphonic signal to quantize
- Steps: Number of steps in the sequence
- Key: Musical key
- Trnsps: Transpose output
- Step: Trigger sequence step forward
- Reset: Reset sequence to beginning
- Pattrn: Switch between different sequences
- Root: Outputs root note of current chord
- Out: Outputs quantized polyphonic signal

## Quick Melody

Generate a melody by aliasing an oscillator with random frequency. Can also generate polyphonic chords.

- Clock: Clock input
- Pttrn: Trigger new random melody
- Min: Set lowest note for melody
- Max: Set highest note for melody

## Weighted Quantizer

Quantizer with adjustable note weights.

- In: Polyphonic signal input
- Notes: Weight for notes. For a random input, this is effectively probabilities.
- Out: Quantized polyphonic output

## Labeled Patchbay

8 channel polyphonic patchbay with labels and attenuverters

## 16 Squared

Compact 16 step 16 channel polyphonic sequencer. Only the values of the current step are displayed or adjustable.

- Fwd: Step forward trigger
- Back: Step backward trigger
- Reset: Reset sequence trigger
- Steps: Number of steps
- Poly: Number of polyphony channels
