#include "CCMessage.h"

using namespace cocos2d;

void addChar(std::vector<char> *arr, char value) {
    arr->push_back(value);
//    log("sizeArr=%zd", arr.size());
}
char getChar(std::vector<char> * arr, int pos)
{
    try {
        if (pos<arr->size())
        {
            return arr->at(pos);
        }
    } catch (int ex) {
        
    }
    return '0';
}

CCMessage::CCMessage() {
	length = 0;
	posRead = 0;
	//data = new ArrayList(0);
//	arrData->retain();
    arrData = new std::vector<char>;

}

CCMessage::~CCMessage() {
	arrData->clear();
	//delete data;
}

int CCMessage::getCMD()
{
    char c = getChar(arrData, 0);
	signed char a;
	if (c >= 128) {
		a = c - 256;
	} else
		a = c;	//return data->get(posRead++);
	return a;
}

CCMessage* CCMessage::create(char * bytes) {
	//read int để lấy độ dài
	int len = 0; //chỉ bao gồm mảng, ko bao gồm cmd
	len = (bytes[0] << 24) + ((bytes[1] & 0xFF) << 16)
			+ ((bytes[2] & 0xFF) << 8) + (bytes[3] & 0xFF);
	int cmd = 0;
	cmd = (bytes[4] << 24) + ((bytes[5] & 0xFF) << 16)
			+ ((bytes[6] & 0xFF) << 8) + (bytes[7] & 0xFF);
	if (cmd > 255)
		return NULL;
	CCMessage * mess = new CCMessage();
	mess->setCommand(cmd);
	for (int i = 0; i < len; i++) {
		char value = bytes[i + 8];
		addChar(mess->arrData, value);

	}

//	mess->autorelease();
	return mess;
}

void CCMessage::writeByte(char value) {
	addChar(arrData, value);
	length += 1;
}

signed char CCMessage::readByte() {

	char c = getChar(arrData, posRead++);
	signed char a;
	if (c >= 128) {
		a = c - 256;
	} else
		a = c;	//return data->get(posRead++);
	return a;
}
void CCMessage::writeInt(int value) {
	char buffer[4];
	for (int i = 0; i < 4; i++) {
		buffer[i] = value >> (8 * (4 - i - 1));

		char p = buffer[i];

		//data->add(p);
		addChar(arrData, p);
		//data.insert(data.end(), &p, &p + sizeof( char));
		length += 1;

	}

}

int CCMessage::readInt() {
	char ptr[4];
	posRead += 4;
	if (posRead <= arrData->size()) {
		for (int i = 0; i < 4; i++) {
			ptr[i] = getChar(arrData, posRead - 4 + i);
		}
		return (ptr[0] << 24) + ((ptr[1] & 0xFF) << 16) + ((ptr[2] & 0xFF) << 8)
				+ (ptr[3] & 0xFF);
	}
	return -999;
}

short CCMessage::readShort() {
	posRead += sizeof(short);
	if (posRead <= arrData->size()) {
		char ptr[2];
		for (int i = 0; i < 2; i++) {
			ptr[i] = getChar(arrData, posRead - 2 + i); //data->get(posRead-2+i);
		}
		short n = ((ptr[0] & 0xFF) << 8) + (ptr[1] & 0xFF);
		return n;
	} else {
		return -99;
	}
}
void CCMessage::writeShort(short value) {

	char buffer[2];

	for (int i = 0; i < 2; i++) {
		buffer[i] = value >> (8 * (2 - i - 1));

		char p = buffer[i];

		addChar(arrData, p);
		//data->add(p);
		//data.insert(data.end(), &p, &p + sizeof( char));
		length += 1;
	}
}
bool CCMessage::canRead() {
	if (posRead < arrData->size()) {
		return true;
	} else {
		return false;
	}
}
void CCMessage::writeBoolean(bool value) {
	char p = 0;
	if (value) {
		p = 1;
	}
	addChar(arrData, p);
	//data->add(p);
	//data.insert(data.end(), &p, &p + sizeof( char));
	length += 1;
}
bool CCMessage::readBoolean() {
	posRead += 1;
	if (posRead <= arrData->size()) {
		char ptr[1];
		for (int i = 0; i < 1; i++) {
			ptr[i] = getChar(arrData, posRead - 1 + i);
		}
		if (ptr[0] == 0)
			return false;
		else {
			return true;
		}
	} else {
		return false;
	}

}

void CCMessage::writeLong(long long value) {
	char len = sizeof(long long);
	char *buffer = new char[len];

	for (int i = 0; i < len; i++) {
		buffer[i] = value >> (8 * (len - i - 1));

		char p = buffer[i];
		addChar(arrData, p);
		//data->add(p);
		//data.insert(data.end(), &p, &p + sizeof( char));
		length += 1;
	}
	delete[]buffer;
}


long long CCMessage::readLong() {

	char len = sizeof(long long);
	posRead += len;

	if (posRead <= arrData->size()) {
		char *ptr = new char[len];
		for (int i = 0; i < len; i++) {
			ptr[i] = getChar(arrData, posRead - len + i);
		}
		long long n = 0;

		for (char i = 0; i < len; i++) {
			n += (long long)(ptr[i] & 0xff) << (8 * (len - i - 1));
		}
		delete[]ptr;
		return n;
	} else {
		return -99;
	}
}

std::string CCMessage::readStringUTF() {
    std::string strKq= "" ;
    short len = this->readShort();
    posRead += len;

    if (posRead <= arrData->size()) {
		unsigned char * ptr = new unsigned char[len];
        for (int i = 0; i < len; i++) {
            ptr[i] = getChar(arrData, posRead - len + i); //data->get(posRead-len +i);
            //ptr[i] = data[posRead-len+i];
        }
        strKq = CCString::createWithData(ptr, len)->getCString();
		delete[]ptr;
        return strKq;
        
    } else {
        return StringUtils::format("");
    }
}
void CCMessage::writeStringUTF(std::string str) {
	short len = str.length();

	this->writeShort(len);

	const char * buffer = str.c_str();

	//write data

	for (int i = 0; i < len; i++) {
		char p = buffer[i];
		addChar(arrData, p);
		//data->add(p);
		//data.insert(data.end(), &p, &p + sizeof( char));
		length += 1;
	}
}
char * CCMessage::getBytes() {
	char * kq = new char[arrData->size()];
	for (int i = 0; i < arrData->size(); i++) {
		kq[i] = getChar(arrData, i);
	}

	return kq;

	//return data->data();
	//return data.data();
}
void CCMessage::writeBytes(char * value, int len) {
	for (int i = 0; i < len; i++) {
		char p = value[i];
		addChar(arrData, p);
		//data->add(p);
		//data.insert(data.end(), &p, &p + sizeof( char));
		length += 1;
	}
}

void CCMessage::writeBytes(signed char * value, int len) {
	for (int i = 0; i < len; i++) {
		char p = value[i];
		addChar(arrData, p);
		//data->add(p);
		//data.insert(data.end(), &p, &p + sizeof( char));
		length += 1;
	}
}

char * CCMessage::readBytes(int len) {
	posRead += len;
	//if (posRead <= data.size()) {
	//if (posRead <= data->size()) {
	if (posRead <= arrData->size()) {
		char * ptr = (char *) malloc(len);
		for (int i = 0; i < len; i++) {
			ptr[i] = getChar(arrData, posRead - len + i); //data->get(posRead -len + i);
			//ptr[i] = data[posRead-len+i];
		}
		return (char *) ptr;
	} else {
		return NULL;
	}
}

CCByte * CCMessage::readBytes() {
	short len = readShort();
	CCByte * myByte = new CCByte();
	myByte->autorelease();
	myByte->setLen(len);
    if (len <=0)
    {
        signed char * v = (signed char *) malloc(len);
        myByte->setByteArray(v);
        return myByte;
    }
	posRead += len;
	//if (posRead <= data.size()) {
	//if (posRead <= data->size()) {
	if (posRead <= arrData->size()) {
		signed char * ptr = (signed char *) malloc(len);
		for (int i = 0; i < len; i++) {
			ptr[i] = getChar(arrData, posRead - len + i); //data->get(posRead -len + i);
			//ptr[i] = data[posRead-len+i];
		}
		myByte->setByteArray(ptr);
		return myByte;
	} else {
		return NULL;
	}
}
CCByte::CCByte() {

}

CCByte::~CCByte() {
	if (byteArray != NULL) {
//        delete byteArray;
        CC_SAFE_DELETE(byteArray);
		byteArray = NULL;
	}
}

CCByte::CCByte(int _len) {
	len = _len;
	byteArray = (signed char *) malloc(len);
}

Sprite* CCByte::getSprite()
{
    Image* img = new Image;
    img->initWithImageData((const unsigned char * )byteArray, (long) len);
    Texture2D* texture = new Texture2D();
    texture->initWithImage(img);
    
    Sprite* sprite = Sprite::createWithTexture(texture);
    img->release();
    return sprite;
}
