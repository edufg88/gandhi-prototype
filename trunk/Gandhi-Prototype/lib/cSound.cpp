#include "cSound.h"

cSound* cSound::instance = NULL;

cSound* cSound::GetInstance()
{
	if (instance == NULL)
	{
		instance = new cSound();
	}

	return instance;
}

cSound::cSound(){}

cSound::~cSound()
{
	cout << "BORRANDO INTERFAZ AUDIO" << endl;
	// Cerramos todo el sistema de sonido
	inputChannel->setPaused(true);
	inputChannel->stop();
	result = sound->release();
	ERRCHECK(result);
	result = inputChannelGroup->release();
	ERRCHECK(result);
	result = system->close();
	ERRCHECK(result);
	result = system->release();
	ERRCHECK(result);
}

bool cSound::inicializarAudio()
{
	bool res = true;
	// Creamos Sistema FMOD
	result = FMOD::System_Create(&system);
	res = ERRCHECK(result);
	// Inicializamos FMOD
	result = system->init(100, FMOD_INIT_NORMAL, 0);
	res = ERRCHECK(result);
	// Inicializamos el grupo de canales
	result = system->createChannelGroup("ICG1", &inputChannelGroup);
	res = ERRCHECK(result);
	// Hay que cargar siempre una canción
	cargarCancion("media/sounds/Kalimba.mp3");
	return res;
}

void cSound::actualizar()
{
	/*
	// Controlamos la pausa
	if(segundosPausa > 0)
	{
		if ((Gosu::milliseconds() - contadorPausa) > segundosPausa*1000)
		{
			setPaused(false);
			segundosPausa = 0;
		}
	}
	*/

	// Actualizamos el sistema
	result = system->update();

	ERRCHECK(result);
}

bool cSound::cargarCancion(const char* ruta)
{
	result = system->createStream(ruta, FMOD_2D | FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound);
	return (ERRCHECK(result));
}

bool cSound::playCancion()
{
	bool res = true;
	result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &inputChannel);
	res = ERRCHECK(result);
	result = inputChannel->setChannelGroup(inputChannelGroup);
	res = ERRCHECK(result);
	result = inputChannel->setPaused(false);
	res = ERRCHECK(result);

	return res;
}

bool cSound::stopCancion()
{
	bool res = true;
	setPosicion(0);
	result = inputChannel->stop();
	res = ERRCHECK(result);
	return res;
}

void cSound::setPosicion(int ms)
{
	inputChannel->setPosition(ms, FMOD_TIMEUNIT_MS);
}

void cSound::pausar(int segs)
{
	/*
	contadorPausa = Gosu::milliseconds();
	segundosPausa = segs;
	*/
	setPaused(true);
}

void cSound::setPaused(bool p)
{
	result = inputChannel->setPaused(p);
}

bool cSound::cargarEfecto(const char* ruta, string nombre)
{
	FMOD::Sound* efecto;
	result = system->createSound(ruta, FMOD_2D | FMOD_SOFTWARE | FMOD_LOOP_OFF, 0, &efecto);
	// Almacenamos el efecto para acceder a el cuando sea necesario
	efectos[nombre] = efecto;

	return (ERRCHECK(result));
}
		
bool cSound::playEfecto(string nombre)
{
	result = system->playSound(FMOD_CHANNEL_FREE, efectos[nombre], false, &inputChannel);
	return (ERRCHECK(result));
}

FMOD::System* cSound::getSystem() const
{
	return system;
}

FMOD::ChannelGroup* cSound::getChannelGroup() const
{
	return inputChannelGroup;
}

FMOD::Channel* cSound::getChannel() const
{
	return inputChannel;
}

FMOD::Sound* cSound::getSound() const
{
	return sound;
}

bool cSound::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		//cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << endl;
		return false;
	}

	return true;
}