#pragma once

#include "SDL_config.h"
#include "gen.hpp"
#include <map>
#include <algorithm>
#include <bitset>
#include <codecvt>
#include <locale>
#include <stdexcept>

enum EncodingType {
    INVALID,
    NUMERIC,
    ALPHANUMERIC,
    BYTE
};

enum ec_level{
    L,
    M,
    Q,
    H
};

class calc_version{
    private:
        std::map<EncodingType, int> mode = {{NUMERIC, 1}, {ALPHANUMERIC, 2}, {BYTE, 4}};
        std::string input;
        static const int MAX_BITS = 256;
        //std::bitset<MAX_BITS> binary_input;
        std::vector<bool> binary_input;

        bool ISO88591, UTF8;
        Type version;
        ec_level ec;

    public:
        calc_version(std::string input);
        
        bool isNumeric();
        bool isAlphanumeric();
        
        bool isValidISO88591();
        bool isValidUTF8();
        EncodingType encoding_type;
        EncodingType get_encoding_type();
        void encode_data();
        void encode_numeric();
        void encode_alphanumeric();
        void encode_byte();
        void add_indicators();
        Type find_version();

        void start_generator();
};
