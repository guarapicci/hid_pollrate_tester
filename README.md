# hid_pollrate_tester
This console application for Windows and Linux tests how fast your input device is really responding to the computer.

###how to use
Make sure beforehand that you do have hidapi and your Operating System's corresponding C++ runtime (usually Visual C++ Redistributable or GNU C++).

- Compile:
```sh
cmake --fresh -S . -B out && cmake --build out
```

- Run:
```sh
./out/hid_pollrate_tester <VID> <PID>
```
Replacing `<VID>` with your device's Vendor ID and `<PID>` with your device's Product ID.

**note:** for windows, the actual program is at `./out/hid_pollrate_tester.exe`.
