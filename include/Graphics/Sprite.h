#include "Engine.h"

namespace SuperEngine
{
    enum CollisionType
    {
        COLLISION_NONE,
        COLLISION_RECT,
        COLLISION_DIST
    };

    class Sprite
    {
    private:
        bool m_visible;
        bool m_alive;

        int m_lifeTimeLength;
        sf::Clock m_lifeTimeTimer;
        //int spriteType;

        Vector2f m_position, m_velocity;
        bool m_imageLoaded;

        int m_state, m_direction;

        sf::Color m_color;

    protected:
        // Might need inheritance, might not
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        bool m_useFrameTimer;
        // Delay before moving and frame animation is performed in milli-seconds
        int m_frameDelay;

        sf::Clock m_frametimer;

        Vector2f m_frameSize;

        int m_animationCols;
        int m_animationRows;

        bool m_collidable;
        enum CollisionType m_collisionMethod;

        int m_curframe, m_totalframes, m_animdir;
        float m_faceangle, m_moveangle;
        int m_animstartx, m_animstarty;
        float m_rotation, m_scale;

        void m_Transform();

        bool genSprite(unsigned int animationCols, unsigned int animationRows);

    public:
        //position on screen
        Vector2f getPosition() { return m_position; }
        void setPosition(const Vector2f& position) { m_position = position; }
        void setPosition(float x, float y) { m_position.x = x; m_position.y = y; }

        double getX() { return m_position.x; }
        double getY() { return m_position.y; }
        void setX(float x) { m_position.x = x; }
        void setY(float y) { m_position.y = y; }

        // movement & velocity
        Vector2f getVelocity() { return m_velocity; }
        void setVelocity(const Vector2f& val) { m_velocity = val; }
        void setVelocity(float x, float y) { m_velocity.x = x; m_velocity.y = y; }

        // Image size
        Vector2f getFrameSize() { return m_frameSize; }
        void setFrameSize(const Vector2f& val) { m_frameSize = val; }
        void setFrameSize(float x, float y) { m_frameSize.x = x; m_frameSize.y = y; }

        bool getVisible() { return m_visible; }
        void setVisible(bool val) { m_visible = val; }

        bool isAlive() { return m_alive; }
        void setAlive(bool val) { m_alive = val; }

        int getState() { return m_state; }
        void setState(int val) { m_state = val; }

        int getDirection() { return m_direction; }
        void setDirection(int val) { m_direction = val; }

        int getColumns() { return m_animationCols; }
        void setColumns(int val) { m_animationCols = val; }
        int getRows() { return m_animationRows; }
        void setRows(int val) { m_animationRows = val; }

        int getCurrentFrame() { return m_curframe; }
        void setCurrentFrame(int val) { m_curframe = val; }

        int getTotalFrames() { return m_totalframes; }
        void setTotalFrames(int val) { m_totalframes = val; }

        int getAnimationDir() { return m_animdir; }
        void setAnimationDir(int val) { m_animdir = val; }

        float getRotation() { return m_rotation; }
        void setRotation(float rotation) { m_rotation = rotation; }
        float getScale() { return m_scale; }
        void setScale(float val) { m_scale = val; }

        void setColor(const sf::Color& color) { m_color = color; }
        void setColor(float r, float g, float b, float a) { m_color = sf::Color(r, g, b, a); }
        sf::Color getColor() { return m_color; }


        bool isCollidable() { return m_collidable; }
        void setCollidable(bool value) { m_collidable = value; }

        CollisionType getCollisionMethod() { return m_collisionMethod; }
        void setCollisionMethod(CollisionType type) { m_collisionMethod = type; }

        // Timers
        bool isFrameTimer() { return m_useFrameTimer; }
        void setFrameTimer(bool val) { m_useFrameTimer = true; }

        // Timer Delay
        void setFrameDelay(int val) { m_frameDelay = val; }
        int getFrameDelay() { return m_frameDelay; }

        // Debugging
        sf::Sprite* const getSprite() { return &m_sprite; }

        // Main methods
        Sprite();
        virtual ~Sprite();
        bool loadImage(const std::string& filename, unsigned int animationCols = 1, unsigned int animationRows = 1,
                       const sf::Color& transcolor = sf::Color(255, 0, 255));
        bool setImage(const sf::Texture&, unsigned int animationCols = 1, unsigned int animationRows = 1);
        void Move(float elapsedTime);
        void Animate();
        void Draw();
    };
};
