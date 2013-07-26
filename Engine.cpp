#include "Engine.h"

#include <cstdlib>
#include <sstream>

namespace SuperEngine
{
    Engine::Engine()
    {
        // Seed random number generator
        std::srand(std::time(0));
        m_maximizeProcessor = false;

        m_frameCount_core = 0;
        m_frameRate_core = 0;
        m_frameCount_real = 0;
        m_frameRate_real = 0;

        m_Fps = 60;

        m_ambientColor = sf::Color(255, 255, 255, 0);
        m_clearColor = sf::Color(0, 0, 0, 255);

        m_pausemode = false;
        m_versionMajor = VERSION_MAJOR;
        m_versionMinor = VERSION_MINOR;
        m_revision = REVISION;

        // set default values
        this->setAppTitle("SuperEngine");
        this->setScreenWidth(800);
        this->setScreenHeight(600);
        this->setColorDepth(32);
        this->setFullscreen(false);

        m_pDevice = NULL;
    }

    Engine::~Engine()
    {
        Release();
    }

    bool Engine::LoadContent(const std::string& filename)
    {
        return m_log.Init(filename);
    }

    const std::string Engine::getVersionText()
    {
        std::ostringstream s;
        s << "SuperEngine v" << m_versionMajor << "." << m_versionMinor
            << "." << m_revision;
        return s.str();
    }

    void Engine::message(const std::string& message, const std::string& title)
    {
        // Create some form of message box, Using wxWidgets would probably be a good idea
        std::cerr << title << " : " << message << std::endl;
    }

    void Engine::fatalerror(const std::string& message, const std::string& title)
    {
        this->message(message, title);
        Shutdown();
    }

    void Engine::setClearColor(const sf::Color& color)
    {
        this->m_clearColor = color;
    }

    bool Engine::m_initgl()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Set at black for now, will need to divide by 255 to get normalized color
        glClearColor(0,0, 0, 1);

        // TODO: Allow reseting
        glViewport(0, 0, getScreenWidth(), getScreenHeight());

        glOrtho(0.0f, getScreenWidth(), getScreenHeight(), 0.0f, -1.0f, 1.0f);

        GLenum error = glGetError();
        if(error != GL_NO_ERROR)
        {
            m_log << "OpenGL initialization error: " << gluErrorString(error) << std::endl;

            return false;
        }

        return true;
    }

    bool Engine::Init(int width, int height, int colordepth, bool fullscreen)
    {
        // Initialize sf::Window
        // TODO: Implement fullscreen

        // TODO: Allow anti-aliazing and other options to be enabled for OpenGL
        sf::ContextSettings contextSettings;
        contextSettings.depthBits = 32;
        contextSettings.antialiasingLevel = 4;

        m_pDevice = new sf::RenderWindow(sf::VideoMode(width, height, colordepth),
                                   this->getAppTitle(), sf::Style::Default, contextSettings);

        m_pDevice->setVerticalSyncEnabled(true);
        m_pDevice->setFramerateLimit(m_Fps);

        // Initialization failed
        if(!m_pDevice)
        {
            #ifdef _DEBUG
            fatalerror("m_pDevice failed to initialize in Engine::Init");
            m_log << ERR << "m_pDevice failed to initialize in Engine::Init" << std::endl;
            #endif // _DEBUG
            return false;
        }

        m_pDevice->setActive();

        if(!game_init()) return false;

        this->setClearColor(sf::Color::Black);

        m_initgl();

        #ifdef _DEBUG
        m_log << INFO << "Engine initialized successfully" << std::endl;
        #endif // _DEBUG

        return true;
    }

    void Engine::ClearScene()
    {
        this->m_pDevice->clear(this->getClearColor());
    }

    int Engine::RenderStart()
    {
        // Check for available device
        if(!this->m_pDevice)
        {
            #ifdef _DEBUG
            std::cerr << "Device does not exist in Engine::RenderStart()" << std::endl;
            m_log << WARN << "Device does not exist in Engine::RenderStart()" << std::endl;
            #endif // _DEBUG
            return 0;
        }
        if(!this->m_pDevice->setActive()) return 0;


        return 1;
    }

    int Engine::RenderStop()
    {
        if(!this->m_pDevice)
        {
            #ifdef _DEBUG
            std::cerr << "Device is non existant in Engine::RenderStop()" << std::endl;
            m_log << WARN << "Device is non existant in Engine::RenderStop()" << std::endl;
            #endif // _DEBUG

            return 0;
        }

        // TODO:
        // Rendering has ended, display changes,
        // might need to change this later
        this->m_pDevice->display();

        return 1;
    }

    void Engine::Shutdown()
    {
        gameover = true;
    }

    void Engine::Update()
    {
        static sf::Clock timedUpdate;

        //calculate core framerate
        m_frameCount_core++;
        if(m_coreTimer.getElapsedTime().asMilliseconds() > 999)
        {
            m_frameRate_core = m_frameCount_core;
            m_frameCount_core = 0;

            m_coreTimer.restart();
        }

        // fast update with no timing
        game_update(timedUpdate.getElapsedTime().asSeconds());

        // update with 60FPS timing, so once every 16 milis
        if(timedUpdate.getElapsedTime().asMilliseconds() > (1000.0f / (float)m_Fps))
        {
            if(!this->getMaximizeProcessor())
            {
                sf::Time waitTime = sf::milliseconds(1);

                sf::sleep(waitTime);
            }

            timedUpdate.restart();
        }
        else
        {
            // calculate real framerate
            m_frameCount_real++;
            if(m_realTimer.getElapsedTime().asMilliseconds() > 999)
            {
                m_frameRate_real = m_frameCount_real;
                m_frameCount_real = 0;

                m_realTimer.restart();
            }

            this->ClearScene();

            // begin rendering
            this->RenderStart();

            game_render();


            // Done rendering
            this->RenderStop();

        }

    }

    void Engine::Close()
    {
        game_end();

        Release();
    }

    int Engine::Release()
    {
        if(m_pDevice)
        {
            m_pDevice->setActive(false);
            m_pDevice->close();

            delete m_pDevice;

            // Just for safe measures :P
            m_pDevice = NULL;

            #ifdef _DEBUG
            std::cout << "Engine closed, m_pDevice deleted" << std::endl;
            m_log << INFO << "Engine closed, m_pDevice deleted" << std::endl;
            #endif // _DEBUG
        }

        return 1;
    }

};
