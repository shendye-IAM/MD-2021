#ifdef MINIMIZE_CLASS
// clang-format off
MinimizeStyle(ga_hybrid,MinGeneticHybrid);
// clang-format on
#else

#ifndef LMP_MIN_GENETIC_HYBRID_H
#define LMP_MIN_GENETIC_HYBRID_H

#include "min_genetic_parent.h"
#include <map>

namespace LAMMPS_NS {

class MinGeneticHybrid : public MinGeneticParent {
 public:
  MinGeneticHybrid(class LAMMPS *);
  ~MinGeneticHybrid();
  void CalculateFitness(Population& population);
  void localMinimization();
  void init();
  void ga_setup();

   void create_minimize(int, char **, int);
   class Min *minimize;
   char *minimize_style;
   typedef Min *(*MinimizeCreator)(LAMMPS *);
   typedef std::map<std::string, MinimizeCreator> MinimizeCreatorMap;
   MinimizeCreatorMap *minimize_map;

 private:
    void new_minimize(char *, int, char **, int, int &);
    template <typename T> static Min *ga_minimize_creator(LAMMPS *);
};

}    // namespace LAMMPS_NS

#endif
#endif
