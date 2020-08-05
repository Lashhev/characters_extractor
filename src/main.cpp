#include "character_extractor.hpp"

int main(int argc, char* argv[])
{
    CharacterSampleExtractor extr = CharacterSampleExtractor();
    extr.process_dir(argv[1], argv[2]);
    return 0;
}

