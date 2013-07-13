#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>


// Used only for debugging for now, i dont know man, stop pressuring me!
#include <iostream>

// Engine parts

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define REVISION 0

extern bool gameover;

extern bool game_preload();
extern bool game_init();
extern void game_update(float elapsedTime);
extern void game_render_3d();
extern void game_render_2d();
extern void game_end();

enum DrawTypes
{
    TRIANGLE = GL_TRIANGLES,
    POLYGON = GL_POLYGON,
    POINT = GL_POINTS,
    QUAD = GL_QUADS
};

namespace SuperEngine
{
    class Engine
    {
    private:
        unsigned int m_versionMajor, m_versionMinor, m_revision;

        unsigned int m_Fps;

        unsigned int m_ScreenWidth, m_ScreenHeight, m_ColorDepth;
        bool m_Fullscreen;
        const char* m_AppTitle;

        bool m_pausemode;
        sf::Color m_ambientColor;
        // Can be changed so that the screen clears to a different color
        sf::Color m_clearColor;
        // Set processing to full speed with no milisecond delay
        bool m_maximizeProcessor;

        // Timers
        sf::Clock m_coreTimer;
        long m_frameCount_core;
        long m_frameRate_core;
        sf::Clock m_realTimer;
        long m_frameCount_real;
        long m_frameRate_real;

        sf::RenderWindow* m_pDevice;

        int Release();
        // Used for window resize events
        void RefreshView();

        bool m_drawingGl;
    public:
        Engine();
        ~Engine();

        int Init(int width, int height, int colordepth, bool fullscreen);
        void Close();
        void Update();
        void message(const std::string& message, const std::string& title = "SuperEngine");
        void fatalerror(const std::string& message, const std::string& title = "Fatal Error!");
        void Shutdown();
        void ClearScene();
        //void SetDefaultMaterial();
        //void SetAmbient(const sf::Color& color) { m_ambientColor = color; }
        int RenderStart();
        int RenderStop();
        int RenderStart_2d();
        int RenderStop_2d();

        // Used for drawing openGL types
        void StartGL(DrawTypes type);
        void EndGL();

        bool isPaused() { return m_pausemode; }
        void setPaused(bool val) { m_pausemode = val; }

        sf::RenderWindow* getDevice() { return m_pDevice; }

        void setPerspective(double fovy, double aspect, double zNear, double zFar)
        {
            gluPerspective(fovy, aspect, zNear, zFar);
        }

        int getVersionMajor() { return m_versionMajor; }
        int getVersionMinor() { return m_versionMinor; }
        int getRevision() { return m_revision; }
        const std::string getVersionText();

        long getFrameRate_core() { return m_frameRate_core; }
        long getFrameRate_real() { return m_frameRate_real; }

        void setFPS(int FPS) { m_Fps = FPS; }
        int getFPS() { return m_Fps; }

        const sf::Color getClearColor() { return m_clearColor; }
        void setClearColor(const sf::Color& val = sf::Color::Black);

        int getScreenHeight() { return m_ScreenHeight; }
        int getScreenWidth() { return m_ScreenWidth; };
        void setScreenWidth(int val) { this->m_ScreenWidth = val; }
        void setScreenHeight(int val) { this->m_ScreenHeight = val; }
        int getColorDepth() { return m_ColorDepth; }
        void setColorDepth(int val) { this->m_ColorDepth = val; }
        bool getFullscreen() { return m_Fullscreen; }
        void setFullscreen(bool val) { m_Fullscreen = val; }
        const char* getAppTitle() { return m_AppTitle; }
        void setAppTitle(const char* val) { m_AppTitle = val; }
        void setMaximizeProcessor(bool val) { m_maximizeProcessor = val; }
        bool getMaximizeProcessor() { return m_maximizeProcessor; }
    };
};

extern SuperEngine::Engine* g_pEngine;

#endif // _ENGINE_H_
