# hid_pollrate_tester
This console application for Windows and Linux tests how fast your input device is really responding to the computer.

### how to use
Make sure beforehand that you do have hidapi and your Operating System's corresponding C++ runtime (usually Visual C++ Redistributable or GNU C++).

- Compile:
```sh
cmake --fresh -S . -B out && cmake --build out
```

- Run(linux, GNU):
```sh
./out/hid_pollrate_tester/pollrate_cli <VID> <PID>
```
- Run(windows, MSVC):
```ps
.\out\hid_pollrate_tester\Debug\pollrate_cli.exe <VID> <PID>
```
Replacing `<VID>` with your device's Vendor ID and `<PID>` with your device's Product ID.

**note:** on linux, check if your user has permissions for the device you'll test; on windows, mice and keyboard are blocked by default.
