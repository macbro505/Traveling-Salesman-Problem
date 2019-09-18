#pragma once
//Do not change
#define NO_PARENT -1 //(-1 means that theres no parent chosen) DO NOT CHANGE THIS
//Changeable properties
#define NUMBER_OF_PARTICIPANTS 5 /// number of patricipanting chromosomes to become parents (10 for population 200 and 15 cities)
#define MUTATION_OCCURENCE_PERCENTAGE 20
#define MAX_PERCENTAGE_OF_NO_IMPROVEMENT_SUCCESIVE_GENERATIONS 80
#define CROSSOVER_PROBABILITY 85
#define MAX_NUMBER_OF_GENERATIONS 120
#define NUMBER_OF_CITIES 15
//only one should be 1 and the other 0////////////////////////////////////////////////////////////////////////////////////
#define PERCENTAGE_CONDITION 0 //(1 - use percentage of no improvement in consecutive generation as termination condition)
#define MAX_NUMBER_CONDITION 1 //(1 - use max number generation as termination condition)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUMBER_OF_CHROMOSOMES 200
#define SCREEN_WIDHT 1920
#define SCREEN_HEIGHT 1080
#define USE_EDGE_RECOMBINATION_CROSSOVER 1 // 0-ordered crossover 1- edge recombination crossover
#define WAITING_TIME 1000 //in miliseconds