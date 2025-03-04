# D3D12 Root Signature Dumper

Simple utility to convert binary D3D12 root signatures (v1.1 RSGs) to text.

## Building

- CMake is expected to be set up beforehand. Visual Studio 2022 is recommended.

```
git clone --recurse-submodules https://github.com/Nukem9/d3d12-root-signature-dumper.git
cmake --preset final
cmake --build --preset final-release
```

## Usage
```
.\dxc.exe -dumpbin myshader.bin -Qstrip_rootsignature -Fo myrootsignature.rsg
.\RootSigDumper.exe myrootsignature.rsg > out.txt
.\cat out.txt

RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT),
RootConstants(num32BitConstants=3, b0), /* Index = 0 */
DescriptorTable(
SRV(t0, space=8, flags=DESCRIPTORS_VOLATILE),
UAV(u0, space=8, flags=DESCRIPTORS_VOLATILE)
), /* Index = 1 */
RootConstants(num32BitConstants=26, b3) /* Index = 2 */
```

## License

- [MIT](LICENSE)
