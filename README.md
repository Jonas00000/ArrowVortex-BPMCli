# ArrowVortex-BPMCli

A headless, command-line tool for detecting BPM and offset from OGG audio files. This is a specialized fork of [ArrowVortex](https://arrowvortex.ddns.net/) designed for automation and scripting.

## Features

*   **Headless:** Runs without a GUI, perfect for embedding in scripts (Python, Node, etc.).
*   **JSON Output:** Outputs clean, parseable JSON.
    ```json
    {"bpm": 140.000, "offset": 0.025}
    ```

## Usage

```bash
BpmCli.exe "path/to/song.ogg"
```

### Output

**Success:**
```json
{"bpm": 120.000, "offset": 0.015}
```

**Error:**
```json
{"error": "Failed to load audio file"}
```

## Building

**Requirements:**
*   CMake 3.10+
*   C++ Compiler (MSVC or MinGW)
*   Standard ArrowVortex dependencies (LibOgg, LibVorbis - included in `lib/`)

**Build:**
```bash
cmake -S . -B build
cmake --build build --config Release
```

## Credits & License

This project is a fork of **ArrowVortex** and retains the **GNU General Public License v3.0 (GPLv3)**.

*   **Original Author:** Bram 'Fietsemaker' van de Wetering
*   **Contributors:** @uvcat7 and volunteer developers
*   **BpmCli Modifications:** Jonas00000

See the `LICENSE` file for full license details.
