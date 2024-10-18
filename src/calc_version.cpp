#include "calc_version.hpp"

calc_version::calc_version(std::string input){
    this->input = input;
    this->ISO88591 = false;
    this->UTF8 = false;

    this->encoding_type = get_encoding_type(); 
}


void calc_version::encode_data(){
    switch(this->encoding_type){
        case EncodingType::INVALID:
            std::cout << "Invalid Input" << std::endl;
            break;
        case EncodingType::NUMERIC:
            encode_numeric();
            break;
        case EncodingType::ALPHANUMERIC:
            encode_alphanumeric();
            break;
        case EncodingType::BYTE:
            encode_byte();
            break;
    }
}

void calc_version::encode_byte(){
    int bit_index = 0;
    for(unsigned char c : this->input){
        std::bitset<8> byte_bits(c); 
        for(int i = 0; i < 8; i++){ //swap to flip bits
            this->binary_input[bit_index++] = byte_bits[i];
        }
    }
    std::cout << "Test|| Byte Encoding: " << this->binary_input << std::endl;
}

void calc_version::encode_numeric(){
    /*
     * TODO
     */
}

void calc_version::encode_alphanumeric(){
    /*
     * TODO
     */
}

EncodingType calc_version::get_encoding_type(){
    if(isNumeric()) return EncodingType::NUMERIC;
    else if(isAlphanumeric()) return EncodingType::ALPHANUMERIC;
    else if(isValidISO88591()){
        this->ISO88591 = true;
        return EncodingType::BYTE;
    }
    else if(isValidUTF8()){
        this->UTF8 = true;
        return EncodingType::BYTE;
    }
    return EncodingType::INVALID;
}

bool calc_version::isNumeric(){
    return this->input.find_first_not_of("0123456789") == std::string::npos;
}

bool calc_version::isAlphanumeric(){
    return this->input.find_first_not_of("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:") == std::string::npos;
}

bool calc_version::isValidISO88591(){
    for(char c : this->input){
        unsigned char byte = static_cast<unsigned char>(c);
        if(byte > 255) return false;
    }
    return true;
}

bool calc_version::isValidUTF8(){
    try{
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wide_string = converter.from_bytes(this->input);
        return true;
    }catch (const std::range_error&){
        return false;
    }
}
