//
//  CCMessage.h
//  cocos2dx


#ifndef __CCMESSAGE_H__
#define __CCMESSAGE_H__

#include "cocos2d.h"
#include "CCChar.h"

using namespace cocos2d;


class CCByte: public Ref
{
    CC_SYNTHESIZE(signed char * , byteArray, ByteArray);
    CC_SYNTHESIZE(short, len, Len);
    CCByte();
    CCByte(int _len);
    Sprite * getSprite();
    ~CCByte();
};


class CCMessage : public Ref {
public:
	CCMessage();

	virtual ~CCMessage();
//	Vector<CCChar *> arrData;
    std::vector<char> * arrData;
	int length;
	int posRead;
	char *bytes;

	static CCMessage * create(char * bytes);
    int getCMD();
	CC_SYNTHESIZE(int, command, Command);

private:

public:
	void writeByte(char value);
	signed char readByte();
	void writeInt(int value);
	int readInt();
	short readShort();
	void writeShort(short value);
	bool canRead();
	void writeBoolean(bool value);
	bool readBoolean();

	void writeLong(long long value);
	long long readLong();

	std::string readStringUTF();
	void writeStringUTF(std::string str);
	void writeBytes(char * value, int len);
    void writeBytes(signed char * value, int len);
	char * readBytes(int len);
    CCByte * readBytes();
	char* getBytes();

	void test() {
		unsigned char value = 10;
		//data.insert(data.end(), &value, &value+ sizeof( char));
		// data->add(value);

	}
    

};

#endif /* defined(__cocos2dx__CCMessage__) */
