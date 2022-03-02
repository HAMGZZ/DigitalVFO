## JUSTIFICATION
The key justifications of why this project is being undertaken now, can be summarised in the following stages:

1. Analogue VFO designs, in both transistor and vacuum tube implementations require detailed mechanical design inputs,  and careful choices of negative temperature coefficient components. This is crucial in achieving the typical +/- 100Hz stability required for  CW and SSB operation.

2. From 1990 onwards, radio transceivers were fitted with a basic crystal controlling a PLL system to afford better stability when using digital modes like RTTY, narrow CW and of course stable SSB.  Indeed, with these 'modern' radios, it became a game to follow users of analogue VFO based radios up and down in frequency.

3. The development of sub-10Hz bandwidth digital modes like WSPR , JT4, FT8 etc since 2008 demanded that radio transceivers be fitted with a TCXO or a disciplined frequency reference in order to maintain communication.  The frequency stability required for operating these modes on the 28Mhz band needs to be under 0.4ppm.

4. The concept of this project is to allow all old shelved antique radios to be simply retrofitted with a precision TCXO based VFO,  with a fair chance of supporting modern digital modes.  While an overall 0.4ppm precision of the whole radio probably won't be achieved, it will certainly be an improvement above basic crystal based radio transceivers.

## IMPLEMENTATION
The digital VFO project is based on replicating the traditional 5.0Mhz to 5.5Mhz pseudo VFO standard found in near all radio transceivers from the 1940's to the late 1980's.

Leveraging modern cost effective components which excel in performance, a prototype was constructed using a Teensy 3.2 and an AD9833 function generator module.

The function generator can operate to 25Mhz producing sine, triangle and square wave signals. In this case we chose to only implement the Sine wave output constrained to the 4.9Mhz to 5.6Mhz limits using the Teensy.

A rotary encoder is used as the main manual VFO control, and an A/D converter pin in the Teensy is used to implement the RIT/XIT function.

A rotary encoder speed detection routine is programmed into the Teensy, affording an exponential frequency step increment when spinning the encoder VFO control.

Mechanically, the digital VFO is mounted using the rotary encoder fixing and is small enough to fit in old analogue VFO spaces found in older Kenwood and Yaesu radio transceivers.

While the digital VFO is not plug and play, as most antique radio VFO connectors are long obsolete, the electrical signals should be 100% compatible, noting the limited testing undertaken thus far.

Digital VFO power is derived from an 8v to 12v DC input, which may necessitate additional power circuitry in vacuum tube radios.

Later revision digital VFO builds may well use a different microcontroller based on performance and availability issues. The current PCB is based on the Atmel ATTiny1614

## ADVANTAGES
1. The TCXO based digital VFO implementation using the function generator produces a very stable low distortion sine wave, ensuring receiver performance is not compromised.
2. The digital VFO is a fraction of the physical size of the old can style analogue VFOs, consuming similar or less power ensuring no additional heat or power contributions.

## DISADVANTAGES
1. This digital VFO implementation makes the analogue dial frequency readouts obsolete. This comes about to the necessary mechanical removal or modification required to connect the original VFO knob to the rotary encoder.  This is not an issue with transceivers fitted with independent frequency readouts like the Yaesu FT707, FT107M, FT901, FT902 and the FT101ZD.

2. Installation requires mechanical prowess in fabricating fixings and manufacturing suitable interface cabling.
