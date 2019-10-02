/*
 * Generator.h
 *
 * Clock Generator Module
 */
#ifndef SOURCES_CLOCKGENERATOR_H_
#define SOURCES_CLOCKGENERATOR_H_

static constexpr unsigned MIN_FREQUENCY = 5;
static constexpr unsigned MAX_FREQUENCY = 5000000;

/**
 * Initialise the generator before first use
 */
void generatorInitialise();

/**
 * Set generator Frequency
 *
 * @param frequency [MIN_FREQUENCY ... MAX_FREQUENCY]
 */

//void generatorSetFrequency(unsigned frequency);
//
//#endif /* SOURCES_CLOCKGENERATOR_H_ */

void generatorSetFrequency(unsigned frequency);

#endif /* SOURCES_CLOCKGENERATOR_H_ */

