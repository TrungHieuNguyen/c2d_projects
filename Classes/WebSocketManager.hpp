//
//  WebSocketManager.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 7/19/18.
//

#ifndef WebSocketManager_hpp
#define WebSocketManager_hpp
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/WebSocket.h"
#include "Network/CCMessage.h"
#include <stdio.h>
class WebSocketManager  : public cocos2d::Sprite, public cocos2d::network::WebSocket::Delegate
{
public:
    CREATE_FUNC(WebSocketManager);
    
    WebSocketManager();
    virtual ~WebSocketManager();
    
    //virtual void onExit() override;
    
    virtual void onOpen(cocos2d::network::WebSocket* ws)override;
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)override;
    virtual void onClose(cocos2d::network::WebSocket* ws)override;
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)override;
    
    
    void onSendBinary();
    void InitManager();
    virtual void sendMessage(CCMessage * mess);
    
private:
    cocos2d::network::WebSocket* _wsiSendBinary;
    int _sendBinaryTimes;
    std::string  _sendBinaryStatus;
    
};
#endif /* WebSocketManager_hpp */
