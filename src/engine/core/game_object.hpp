#pragma once

#include <string>
#include <map>

struct Pos2d {
    float x;
    float y;
    float rot;

    Pos2d();
    Pos2d(float x, float y);
    Pos2d(float x, float y, float rot);

    Pos2d operator+(Pos2d pos) const;
    Pos2d operator-(Pos2d pos) const;
    Pos2d operator*(Pos2d pos) const;
    Pos2d operator/(Pos2d pos) const;

    Pos2d operator+=(Pos2d pos);
    Pos2d operator-=(Pos2d pos);
    Pos2d operator*=(Pos2d pos);
    Pos2d operator/=(Pos2d pos);
};

class GameObject {
   public:
    GameObject(std::string name, Pos2d pos = Pos2d());
    GameObject(std::string name, GameObject *parent, Pos2d pos = Pos2d());
	~GameObject();

    void Update();

    std::string GetName() const;

    void SetActive(bool active);
    bool GetActive() const;

    void SetVisible(bool visible);
    bool GetVisible() const;

    void SetPosition(Pos2d pos);
    void SetRotation(float rot);
    void SetRotation(Pos2d rot);

    Pos2d GetPosition() const;
    Pos2d GetGlobalPosition() const;
    float GetRotation() const;
    float GetGlobalRotation() const;

    void SetScale(float scaleX, float scaleY);
    void SetScaleX(float scaleX);
    void SetScaleY(float scaleY);
    
    float GetScaleX() const;
    float GetScaleY() const;

    GameObject GetParent() const;

    GameObject AddChild(GameObject *child);
    GameObject AddChildToLocal(GameObject *child);
    GameObject RemoveChild(std::string name);
    void DeleteChild(std::string name);
    
    GameObject *operator+=(Pos2d pos);
    GameObject *operator-=(Pos2d pos);
    GameObject *operator*=(Pos2d pos);
    GameObject *operator/=(Pos2d pos);

  private:
    const std::string mName;

    bool mActive;
    bool mVisible;

    Pos2d mPos;
    float mScaleX;
    float mScaleY;

    GameObject *pParent;
    std::map<std::string, GameObject *> children;
};
