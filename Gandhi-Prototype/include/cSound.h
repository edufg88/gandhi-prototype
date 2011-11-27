#ifndef CSOUND_H
#define CSOUND_H

#include "../FMOD/api/inc/fmod.hpp"
#include "../FMOD/api/inc/fmod_errors.h"
#include <iostream>
#include <map>
using namespace std;

class DatosCancion;

class cSound
{
    public:
        ~cSound();
        bool inicializarAudio();
        void actualizar();
        // Carga la canci�n principal del nivel (S�lo hay una)
        bool cargarCancion(const char* ruta);
        // Carga un efecto y lo a�ade a la lista de efectos
        bool cargarEfecto(const char* ruta, string nombre);
        // Reproduce la canci�n principal
        bool playCancion();
        // Detiene la canci�n principal
        bool stopCancion();
        // Pausa o continua la canci�n principal
        void setPaused(bool p);
        // Pausa la canci�n un determinado n�mero de segundos
        void pausar(int segs);
        // Repruduce un efecto determinado
        bool playEfecto(string nombre);
        // Cambia segundo por el que se encuentra la reproduccion de la canci�n
        void setPosicion(int ms);
        
        FMOD::System* getSystem() const;
        FMOD::ChannelGroup* getChannelGroup() const;
        FMOD::Channel* getChannel() const;
        FMOD::Sound* getSound() const;

    private:
        cSound();
        FMOD::System* system;
        FMOD_RESULT result;
        FMOD::ChannelGroup *inputChannelGroup;
        FMOD::Channel *inputChannel;
        // Sonido para la canci�n principal
        FMOD::Sound* sound;
        // Sonidos para efectos
        //map<string, FMOD::Sound*> efectos;
		map<string, FMOD::Sound*, bool(*)(string, string)> efectos;
        // Contador para las pausas
        int contadorPausa;
        // Valor de la pausa
        int segundosPausa;

        bool ERRCHECK(FMOD_RESULT result);
};

#endif