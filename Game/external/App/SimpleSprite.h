//-----------------------------------------------------------------------------
// SimpleSprite.h
// Privides a very simple DSOUND wrapper to load and play wav files.
//-----------------------------------------------------------------------------
#ifndef _SIMPLESPRITE_H_
#define _SIMPLESPRITE_H_

#include "../glut/include/GL/freeglut.h"
#include <map>
#include <vector>

//-----------------------------------------------------------------------------
// CSimpleSprite
//-----------------------------------------------------------------------------
class CSimpleSprite
{
public:
    // If width, height and UV coords are not provided then they will be derived from the texture size.
    CSimpleSprite(const char *fileName, unsigned int nColumns = 1, unsigned int nRows = 1 );
    void Update(float dt);
    void Draw();
    void SetPosition(float x, float y) { m_xpos = x; m_ypos = y; }   
    void SetAngle(float a)  { m_angle = a; }
    void SetScale(float s) { m_scale = s; }
    void SetFrame(unsigned int f);
    void SetAnimation(int id);
	void GetPosition(float &x, float &y) { x = m_xpos; y = m_ypos; }
    float GetWidth()  const { return m_width;  }
    float GetHeight() const { return m_height; }
    float GetAngle()  const { return m_angle;  }
    float GetScale()  const { return m_scale;  }
    unsigned int GetFrame()  const { return m_frame; }
	void SetColor(float r, float g, float b) { m_red = r; m_green = g; m_blue = b; }
    void CreateAnimation( unsigned int id, float speed, const std::vector<int> &frames)
    {
        sAnimation anim;        
        anim.m_id = id;
        anim.m_speed = speed;
        anim.m_frames = frames;
        m_animations.push_back(anim);        
    };

private:
    void CalculateUVs();
    GLuint m_texture;
    float m_xpos = 0.0F;
    float m_ypos = 0.0F;
    float m_width = 0.0F;
    float m_height = 0.0F;
    unsigned int   m_texWidth = 0;
    unsigned int   m_texHeight = 0;
    float m_angle = 0.0F;
    float m_scale = 1.0F;
    float m_points[8];    
    float m_uvcoords[8];
    unsigned int   m_frame;
    unsigned int   m_nColumns;
    unsigned int   m_nRows;
	float m_red = 1.0f;
	float m_green = 1.0f;
	float m_blue = 1.0f;
    int     m_currentAnim = -1;
    float   m_animTime = 0.0F;

    struct sAnimation
    {
        unsigned int m_id;
        float m_speed;
        std::vector<int> m_frames;
    };
    std::vector<sAnimation> m_animations;

    // Texture management.
    struct sTextureDef
    {
        unsigned int m_width;
        unsigned int m_height;
        GLuint m_textureID;
    };
    bool LoadTexture(const char*);
    static std::map<const char *, sTextureDef > m_textures;
    
};

#endif