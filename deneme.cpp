#include <iostream>
#include <iomanip>
#include <sstream>

class MD5 {
public:
    MD5();
    void update(const std::string& message);
    std::string digest();

private:
    void transform(const unsigned char block[64]);
    void encode(unsigned char* output, const unsigned int* input, size_t length);
    void decode(unsigned int* output, const unsigned char* input, size_t length);
    void finalize();

private:
    unsigned int state[4];
    unsigned int count[2];
    unsigned char buffer[64];
};

MD5::MD5() {
    state[0] = 0x67452301;
    state[1] = 0xEFCDAB89;
    state[2] = 0x98BADCFE;
    state[3] = 0x10325476;

    count[0] = count[1] = 0;
}

void MD5::update(const std::string& message) {
    const unsigned char* input = reinterpret_cast<const unsigned char*>(message.c_str());
    size_t length = message.length();

    size_t i, index, partLen;

    index = (count[0] >> 3) & 0x3F;

    if ((count[0] += (length << 3)) < (length << 3))
        count[1]++;
    count[1] += (length >> 29);

    partLen = 64 - index;

    if (length >= partLen) {
        memcpy(&buffer[index], input, partLen);
        transform(buffer);

        for (i = partLen; i + 63 < length; i += 64)
            transform(&input[i]);

        index = 0;
    } else {
        i = 0;
    }

    memcpy(&buffer[index], &input[i], length - i);
}

std::string MD5::digest() {
    unsigned char bits[8];
    unsigned int index, padLen;

    encode(bits, count, 8);

    index = (count[0] >> 3) & 0x3F;
    padLen = (index < 56) ? (56 - index) : (120 - index);

    update("\x80", 1);
    while (index++ < 56)
        update("\0", 1);

    update(bits, 8);

    std::string result;
    encode(reinterpret_cast<unsigned char*>(&result[0]), state, 16);

    return result;
}

void MD5::transform(const unsigned char block[64]) {
    // MD5 transformasyon fonksiyonu
    // Kodu önceki cevapta gönderdim.
    // ...
}

void MD5::encode(unsigned char* output, const unsigned int* input, size_t length) {
    // Kodu önceki cevapta gönderdim.
    // ...
}

void MD5::decode(unsigned int* output, const unsigned char* input, size_t length) {
    // Kodu önceki cevapta gönderdim.
    // ...
}

void MD5::finalize() {
    // Kodu önceki cevapta gönderdim.
    // ...
}

int main() {
    MD5 md5;
    std::string userInput;

    std::cout << "Metni girin: ";
    std::getline(std::cin, userInput);

    md5.update(userInput);
    md5.finalize();

    std::cout << "MD5 Şifresi: " << md5.digest() << std::endl;

    return 0;
}
