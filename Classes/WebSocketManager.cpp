//
//  WebSocketManager.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 7/19/18.
//

#include "WebSocketManager.hpp"
#include <string.h>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
WebSocketManager::WebSocketManager()
:
_wsiSendBinary(nullptr)
, _sendBinaryTimes(0)
, _sendBinaryStatus("")
{
    
}

WebSocketManager::~WebSocketManager()
{
    
}

//void WebSocketManager::onExit()
//{
//
//
//    if (_wsiSendBinary)
//    {
//        _wsiSendBinary->closeAsync();
//    }
//
//
//    Node::onExit();
//}

void WebSocketManager::InitManager()
{
    
    
    _wsiSendBinary = new network::WebSocket();
    
    
    std::vector<std::string> protocols;
    protocols.push_back("wsapi");
    //protocols.push_back("myprotocol_2");
    
    protocols.erase(protocols.begin());
    string url = "ws://192.168.1.13:1111";
    if (!_wsiSendBinary->init(*this, url,&protocols))
    {
        CC_SAFE_DELETE(_wsiSendBinary);
    }
    else
    {
        retain(); // Retain self to avoid WebSocketManager instance be deleted immediately, it will be released in WebSocketManager::onClose.
    }
    
}

// Delegate methods
void WebSocketManager::onOpen(network::WebSocket* ws)
{
    char status[256] = { 0 };
    //sprintf(status, "Opened, url: %s, protocol: %s", ws->getUrl().c_str(), ws->getProtocol().c_str());
    
    if (ws == _wsiSendBinary)
    {
        _sendBinaryStatus = status;
        log("_sendBinaryStatus %s", _sendBinaryStatus.c_str());
    }
    else
    {
        CCASSERT(0, "error test will never go here.");
    }
}

void WebSocketManager::onMessage(network::WebSocket* ws, const network::WebSocket::Data& data)
{
    
    _sendBinaryTimes++;
    char times[100] = { 0 };
    sprintf(times, "%d", _sendBinaryTimes);
    
    std::string binaryStr = "response bin msg: ";
    
    for (int i = 0; i < data.len; ++i) {
        if (data.bytes[i] != '\0')
        {
            binaryStr += data.bytes[i];
        }
        else
        {
            binaryStr += "\'\\0\'";
        }
    }
    
    binaryStr += std::string(", ") + times;
    log("%s", binaryStr.c_str());
    _sendBinaryStatus = binaryStr;
    
}

void WebSocketManager::onClose(network::WebSocket* ws)
{
    log("onClose: websocket instance (%p) closed.", ws);
    if (ws == _wsiSendBinary)
    {
        _wsiSendBinary = nullptr;
        _sendBinaryStatus = "Send Binary WS was closed";
        log("%s", _sendBinaryStatus.c_str());
    }
    else
    {
        
        log("onClose error");
    }
    // Delete websocket instance.
    CC_SAFE_DELETE(ws);
    //log("WebSocketManager ref: %u", _referenceCount);
    //release();
}

void WebSocketManager::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error)
{
    log("Error was fired, error code: %d", static_cast<int>(error));
    char buf[100] = { 0 };
    sprintf(buf, "An error was fired, code: %d", static_cast<int>(error));
    
    if (ws == _wsiSendBinary)
    {
        _sendBinaryStatus = buf;
        log("%s", _sendBinaryStatus.c_str());
    }
    else
    {
        log("_wsiSendBinary onError");
    }
}




void WebSocketManager::onSendBinary()
{
    if (!_wsiSendBinary) {
        return;
    }
    
    if (_wsiSendBinary->getReadyState() == network::WebSocket::State::OPEN)
    {
        _sendBinaryStatus ="Send Binary WS is waiting...";
        log("%s", _sendBinaryStatus.c_str());
        
        char buf[] = "Hello WebSocket,\0 I'm\0 a\0 binary\0 message\0.";
        _wsiSendBinary->send((unsigned char*)buf, sizeof(buf));
    }
    else
    {
        std::string warningStr = "send binary websocket instance wasn't ready...";
        log("%s", warningStr.c_str());
        _sendBinaryStatus = warningStr.c_str();
        log("%s", _sendBinaryStatus.c_str());
    }
}
 void WebSocketManager::sendMessage(CCMessage * mess)
{
    
}
