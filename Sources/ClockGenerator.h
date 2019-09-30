/*
 * Generator.h
 *
 * Clock Generator Module
 */
#ifndef SOURCES_CLOCKGENERATOR_H_
#define SOURCES_CLOCKGENERATOR_H_

<<<<<<< HEAD
static constexpr unsigned MIN_FREQUENCY = 1000;
=======
static constexpr unsigned MIN_FREQUENCY = 100;
>>>>>>> master
static constexpr unsigned MAX_FREQUENCY = 100000;

/**
 * Initialise the generator before first use
 */
void generatorInitialise();

/**
 * Set generator Frequency
 *
 * @param frequency [MIN_FREQUENCY ... MAX_FREQUENCY]
 */
<<<<<<< HEAD
//void generatorSetFrequency(unsigned frequency);
//
//#endif /* SOURCES_CLOCKGENERATOR_H_ */
=======
void generatorSetFrequency(unsigned frequency);

#endif /* SOURCES_CLOCKGENERATOR_H_ */
>>>>>>> master
