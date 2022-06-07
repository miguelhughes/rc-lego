This folder is mostly a collection of 3d models I gathered from thingiverse and output of customizations I printed for customizable files.

For some of these, if you'll be printing, you'll most likely need to go to the original files & trial & error to get the sizes right.

Regarding the tt motor wrapper, there's two versions. One is more compatible with traditional lego (tt motor wrapper), and the other one is more lego technic oriented

regarding arduino-lego-mount. it needs updating, there's a hole to feed in the power input terminal, and I made a mistake in measurements so it doesn't match.

I highly recommend the [Pela Blocks](https://github.com/paulirotta/PELA-blocks) library. I was amazed at it's completeness and usefullness, as in 3d printing for lego you always get a mismatch, and parts never quite fit exactly. This amazing library has tools to adjust for your printer's standard error and then use those parameters throughout the entire library. Just brilliant. 
And there's an enormous library of parametric lego parts (pegs, blocks, different cases...), all of them customizable.

Part list: 
- arduino-lego-cover - x1 height.stl (generated from pela blocks library)
- arduino-lego-cover knobs.stl (generated from pela blocks library)
- arduino-lego-mount.stl (generated from pela blocks library)
- battery sub panel.stl (generated from pela blocks library)
- [lego wrapper for TT Motor](https://www.thingiverse.com/thing:5272973)
- [Lego Compatible DC TT Hobby Motor Mount.stl](https://www.thingiverse.com/thing:5140209)
- 18650 battery cap.stl & 18650 battery cap.f3d (these I designed myself, after I burnt 2 motor shields for placing the batteries the other way around.)
- LegoAxleToMotor.json (presets for LegoAxleToMotor.scad)
- [LegoAxleToMotor.scad](https://www.thingiverse.com/thing:1013155/files)
- Servo to Lego Axle Adapter.stl (from LegoAxleToMotor.scad, preset "servo 9g v1") After printing, heat it up and squeeze it into the servo's cog, so it takes its shape.
- TT motor to Lego Axle Adapter.stl (from LegoAxleToMotor.scad, preset "tt motor - large ones")