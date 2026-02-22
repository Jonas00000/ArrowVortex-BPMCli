#include <Editor/FindTempo.h>
#include <Editor/Music.h>
#include <Editor/Sound.h>
#include <Core/Core.h>
#include <Core/String.h>
#include <System/File.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdarg>
#include <cstdio>

// Minimal mock environment for ArrowVortex core
namespace Vortex {
    // Redirect HUD messages to stderr
    void LogToStderr(const char* fmt, va_list args) {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }

    void HudInfo(const char* fmt, ...) {
        va_list args; va_start(args, fmt); LogToStderr(fmt, args); va_end(args);
    }
    void HudError(const char* fmt, ...) {
        va_list args; va_start(args, fmt); LogToStderr(fmt, args); va_end(args);
    }
    void HudWarning(const char* fmt, ...) {
        va_list args; va_start(args, fmt); LogToStderr(fmt, args); va_end(args);
    }
    void HudNote(const char* fmt, ...) {
        va_list args; va_start(args, fmt); LogToStderr(fmt, args); va_end(args);
    }

    // Dummy implementations for missing format loaders
    SoundSource* LoadMP3(FileReader* file, String& title, String& artist) { return nullptr; }
    SoundSource* LoadWav(FileReader* file, String& title, String& artist) { return nullptr; }

    // Headless Music implementation required by TempoDetector
    class HeadlessMusic : public Music {
    public:
        Sound mySound;
        String title = "Headless Title";
        String artist = "Headless Artist";

        // Core functionality needed for analysis
        bool loadFile(const char* path) {
            return mySound.load(path, false, title, artist);
        }
        
        double getSongLength() override {
            if (mySound.getFrequency() == 0) return 0.0;
            return (double)mySound.getNumFrames() / mySound.getFrequency();
        }
        
        const Sound& getSamples() override { return mySound; }
        
        // Stubs for pure virtual methods not used in analysis
        void saveSettings(XmrNode& settings) override {}
        void tick() override {}
        void onChanges(int changes) override {}
        void unload() override { mySound.clear(); }
        void load() override {} 
        void pause() override {}
        void play() override {}
        void seek(double seconds) override {}
        void setVolume(int percentage) override {}
        int getVolume() override { return 100; }
        void setMuted(bool mute) override {}
        bool isMuted() override { return false; }
        void setSpeed(int percentage) override {}
        int getSpeed() override { return 100; }
        void toggleBeatTick() override {}
        void toggleNoteTick() override {}
        void startOggConversion() override {}
        bool isPaused() override { return true; }
        double getPlayTime() override { return 0.0; }
        StringRef getTitle() override { return title; }
        StringRef getArtist() override { return artist; }
    };

    Music* gMusic = nullptr;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_ogg>" << std::endl;
        return 1;
    }

    Vortex::HeadlessMusic music;
    Vortex::gMusic = &music;

    if (!music.loadFile(argv[1])) {
        std::cout << R"({"error": "Failed to load audio file"})" << std::endl;
        return 1;
    }

    // Run Detection on the full song
    Vortex::TempoDetector* detector = Vortex::TempoDetector::New(0.0, music.getSongLength());
    if (!detector) {
        std::cout << R"({"error": "Failed to create detector"})" << std::endl;
        return 1;
    }

    while (!detector->hasResult()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // Output JSON result
    const auto& results = detector->getResult();
    if (results.empty()) {
        std::cout << R"({"error": "No BPM detected"})" << std::endl;
    } else {
        const auto& best = results[0];
        printf("{\"bpm\": %.3f, \"offset\": %.3f}\n", best.bpm, best.offset);
    }

    delete detector;
    return 0;
}
