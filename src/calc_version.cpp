#include "calc_version.hpp"

calc_version::calc_version(std::string input){
    this->input = input;
    this->ISO88591 = false;
    this->UTF8 = false;
    this->ec = M;   
    this->version = find_version();

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
    add_indicators();
}

void calc_version::add_indicators(){
    int string_length = this->input.length();
    int total_bits = (this->version > Type::VER9) ? 16 : 8;
    std::vector<bool> bits;
    while(string_length > 0){
        bits.push_back(string_length % 2);
        string_length /=2;
    }
    std::reverse(bits.begin(), bits.end());

    while(bits.size() < total_bits){
        bits.insert(bits.begin(), 0);
    }
    
    std::cout << "length indicator: ";
    for(bool b : bits){
        std::cout << b;
    }

    std::bitset<4> mode_indicator(this->mode[this->encoding_type]);
    std::cout << "\nmode: " << mode_indicator << std::endl;

    
}

void calc_version::encode_byte(){
    int bit_index = 0;
    for(unsigned char c : this->input){
        std::bitset<8> byte_bits(c); 
        for(int i = 7; i >= 0; i--){ //swap to flip bits
            this->binary_input.push_back(byte_bits[i]);
        }
    }
    for(bool bit : binary_input)
        std::cout << bit;
    std::cout << std::endl; 

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

Type calc_version::find_version(){
    int version = 0;
    std::cout << "Enter Version: ";
    std::cin >> version;
    /*
     * TODO
     */
    return Type(version);
}

void calc_version::start_generator(){
    gen g(Type(this->version), this->input);

    g.gen_qr();
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
