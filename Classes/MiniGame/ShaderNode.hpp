//
//  ShaderNode.hpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 9/13/17.
//
//

#ifndef ShaderNode_hpp
#define ShaderNode_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"


class ShaderNode : public cocos2d::Node
{
public:
    CREATE_FUNC(ShaderNode);
    static ShaderNode* shaderNodeWithVertex(const std::string &vert, const std::string &frag);
    
    virtual void update(float dt) override;
    virtual void setPosition(const cocos2d::Vec2 &newPosition) override;
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    
protected:
    ShaderNode();
    ~ShaderNode();
    
    bool initWithVertex(const std::string &vert, const std::string &frag);
    void loadShaderVertex(const std::string &vert, const std::string &frag);
    
    void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
    cocos2d::Vec2 _center;
    cocos2d::Vec2 _resolution;
    float      _time;
    std::string _vertFileName;
    std::string _fragFileName;
    cocos2d::CustomCommand _customCommand;
};
#endif /* ShaderNode_hpp */