#ifndef IAUDIO_H
#define IAUDIO_H

#include <string>

/** 
* Interface that includes audio operations.
*/
class IAudio
{
    public: 

        /**
        * Called when destructing the IAudio interface.
        */
        virtual ~IAudio() {}    

        /**
        * Plays the given file.
        * @param fileChars Bytearray of audio file to play.
        * @return void
        */
        virtual void out(char fileChars[]) = 0;

        /**
        * Plays the given file.
        * @param filePath File path to the audio file to play.
        * @return void
        */
        virtual void out(std::string filePath) = 0;
};

#endif